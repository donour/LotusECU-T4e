# C132E0278 fuel and air-path analysis

Scope: 2019 Evora GT430 ROW/manual engine application (`C132E0278.c`). This note is based on
the decompiler export and analyst-assigned symbols. Names below describe observed behavior; they
are not OEM symbols. Constants are quoted in the units encoded by the export's custom types.

## Executive summary

The normal fueling path is an air-mass system with an Alpha-N fallback/transient path:

1. `engine_load()` converts both MAF signals, computes an RPM/TPS Alpha-N estimate, adds idle
   bypass charge, and selects the load source.
2. The 1 kHz scheduler applies an X-tau-style filter to both the selected charge and MAF charge.
3. `injection()` looks up target AFR, divides selected cylinder air mass by commanded AFR, removes
   estimated purge-vapor fuel, converts the remaining fuel mass through pressure-dependent injector
   flow, and layers transient/startup/temperature corrections.
4. Bank STFT/LTFT scale the fuel-derived pulse. Voltage/pressure/temperature-dependent injector
   dead-time and an additive learned lean-time correction are then added.
5. The result is clamped to a minimum of 160 us and to the available engine-cycle window. The same
   construction is inverted by `calc_max_load_from_pw_limit()` to expose an injector-capacity load
   limit to the torque/load system.

The supercharged application does not expose a clearly identified supercharger-bypass command in
this path. The clearly recovered charge-air actuator is the charge-cooler pump, scheduled from
post-compressor/manifold temperature with full-pump fail-safe behavior.

## Call and data flow

```text
ADC / sensor conversion
  MAF1, MAF2                 MAP, baro, manifold temp       rail pressure
       |                              |                          |
       +-----------> engine_load() <--+                          |
                         |                                        |
                Alpha-N or dual-MAF charge                        |
                         |                                        |
          1 kHz X-tau load / fuel-film filter                     |
                         |                                        |
                 load_mass_per_stroke_raw                         |
                         |                                        |
                         +--------------> injection() <------------+
                                              |
                     AFR target -> air/fuel mass -> minus purge fuel
                                              |
                   injector flow / bank balance -> base opening time
                                              |
                   startup + temperature + transient corrections
                                              |
                            STFT/LTFT per bank, additive learning
                                              |
                        min/cycle-window clamp -> eTPU scheduling
```

Relevant scheduler evidence:

- The main fast loop calls `engine_load()` before `injection()`.
- The 1 kHz section around the `CAL_injtip_fuel_film_*` references computes a load-dependent X
  factor and separate alpha values for increasing/decreasing mass flow. It filters both
  `load_selected_raw` and `load_measured_maf`, then maintains `load_integrator_fuel_film_`.
- `closed_loop_200hz()` updates closed-loop control; `o2_fuel_learn_100ms()` updates persistent and
  zoned fuel learning at a slower rate.

## Air charge and load selection

`engine_load()` contains three related estimates:

- Speed-density reference: `CAL_load_ve_for_speed_density[rpm][MAP]`, cylinder volume, MAP, and
  manifold absolute temperature. The use of 287 J/(kg*K) is visible directly in the arithmetic.
- Alpha-N charge: `CAL_load_alphaN_base[rpm][TPS]`, corrected by ambient or manifold air density and
  `LEA_load_alphaN_learned_trim[rpm][TPS]`.
- Measured charge: the average of the two MAF flows multiplied by adjusted engine period. The
  decompiler lost this mul/div idiom, but the recovered expression is now restored in the C export:
  `avg(MAF1, MAF2) * engine_speed_period_adj / 100000`. The same structure is present in the later
  GT firmware, and the early Evora export has instruction-level notes for the corresponding idiom.

The next two lost outputs (`load_unknown` and `load_u8_tmp`) feed the torque-to-TPS learning and
mapping tables. Early Evora code density-normalizes MAF charge by standard pressure and temperature,
then converts it to a clamped 8-bit load. That is strong structural evidence but not enough to copy
the exact constants into GT430 without its raw instructions, so these two assignments remain marked
unresolved.

Alpha-N is selected when the engine is not running, a MAF-related failure flag is set, or the
transient hold timer is active below `CAL_load_alphaN_max_rpm`. The timer is rearmed by large TPS
opening/closing rates and by a TPS threshold indexed by RPM. Otherwise measured MAF charge is used.
`load_comp_idle` is added to either source.

The function also synthesizes MAP from selected charge and a separate VE table, produces OBD
calculated/absolute load, and derives a WOT reference charge. The latter can be reduced by
`load_limit_from_torque_limit`, showing that reported relative load and the torque model share a
common charge ceiling.

High-value load calibrations and learned state:

- `CAL_sensor_maf_scaling[_X_signal]`
- `CAL_load_ve_for_speed_density[_X_rpm][_Y_map]`
- `CAL_load_alphaN_base[_X_engine_speed][_Y_tps]`
- `CAL_load_alphaN_seed[_X_tps]`
- `CAL_load_source_selection_threshold_by_tps[_X_rpm]`
- `CAL_load_alphaN_tps_rate_opening_threshold`
- `CAL_load_alphaN_tps_rate_closing_threshold`
- `CAL_load_alphaN_hold_time`, `CAL_load_alphaN_max_rpm`
- `CAL_load_alphaN_use_tmap_density`, `CAL_tmap_use_for_load`
- `LEA_load_alphaN_learned_trim`

## Injection pulse construction

### 1. Injector offset and injection phasing

`fuel_pressure_abs2 - map` is clamped to form manifold-relative injector differential pressure.
`CAL_inj_time_base[ECU voltage][differential pressure]` yields a 20 us-granularity injector offset.
`CAL_inj_comp_iat` scales that offset using either pre-throttle IAT or manifold temperature according
to `CAL_tmap_use_for_inj`. The result is capped at 5100 us and held in
`inj_pulse_time_scaled`.

`CAL_inj_angle[rpm][load]` supplies the target injection angle. `inj_angle_offset_update_200hz()`
slews the scheduled angle by 20 internal angle units per update instead of stepping immediately.

### 2. AFR command and power enrichment

`CAL_inj_afr_base[rpm][load]` decodes as `table * 5 + 500` in AFR*100 units, with an additional
test/trim term. When the base target departs from `CAL_closedloop_afr`, the code temporarily retains
the closed-loop AFR during an entry delay. It chooses the cruise or power-enrichment delay using
`CAL_inj_accel_enrichment_load_threshold[rpm]` and `load_pct`.

When the delayed target is richer than closed-loop, `fuel_control_mode_flags` records enrichment and
the target can be made still richer by an ignition-retard-derived term using
`CAL_inj_comp_power_enrich_from_ign_retard`. `afr_commanded` is clamped no richer than 8.00:1 by the
observed arithmetic.

### 3. Fuel mass and injector flow

Required fuel mass is:

```text
inj_fuel_mass_required = load_mass_per_stroke_raw * 10000 / afr_commanded
```

Estimated purge-vapor mass is subtracted separately for bank 1 and bank 2. If purge mass meets or
exceeds the request, commanded liquid-fuel mass for that bank becomes zero.

Injector flow comes from `CAL_inj_flow_rate[differential pressure]`, clamped to 5000..20000 in the
exported flow units, then scaled by `CAL_inj_efficiency[rpm][load]`. The
`CAL_inj_bank_balance[rpm][load]` value divides effective flow between the banks; the observed ratio
is clamped to 170..230 around a nominal denominator of 200.

### 4. Multiplicative and additive corrections

The mass-derived time is multiplied by:

- `CAL_inj_enrichment_factor_load_n_coolant_{manual,ips}[load][coolant]`
- `CAL_inj_comp_air_temp2[load][air temperature]`
- `CAL_inj_comp_air_temp_startup[air temperature][MAF accumulated since start]`
- `CAL_inj_cranking_enrichment_coolant_{manual,ips}[stopped coolant][MAF accumulated]`
- a blended cranking term derived from soak time, air temperature, load, and accumulated MAF

It then receives the additive terms `inj_dfco_recovery_enrichment`, `inj_tip_adj_enrichment`,
`inj_tip_adj_enleanment`, and the post-start trim. A separate cold-start table acts as a cap while
the engine is running and accumulated MAF is below its threshold; despite the symbol's
"enrichment" name, the observed operation is `min(calculated pulse, cold-start limit)`.

### 5. Closed-loop trims, learned offset, and output limits

STFT and LTFT apply to the fuel-derived portion independently per bank. From the arithmetic:

- LTFT uses 0.1-percent units (`pulse * ltft / 1000`).
- STFT uses 0.05-percent units (`pulse * stft / 2000`).

After those multipliers, `inj_pulse_time_scaled` and `LEA_fuel_learn_lean_time_bank{1,2}` are added.
The final bank commands are clamped to at least 160 us, at most 65535 us, and at most
`engine_speed_period_2 * 8 - 250`. Duty cycle is calculated against that window.

`CAL_inj_max_duty_cycle_limit` defines a lower configurable capacity ceiling. If enabled,
`calc_max_load_from_pw_limit()` algebraically reverses nearly the entire pulse construction—trims,
transient corrections, temperature/start corrections, injector flow, purge mass, and AFR—to
produce `load_limit_from_inj`. The limiting bank is selected from the larger current pulse.

## Closed-loop and learned fuel correction

`closedloop()` selects RPM/load-dependent proportional, integral, and derivative gains for manual
cars; IPS uses scalar gains. It requires runtime/coolant-dependent activation, valid O2 activity,
the stoichiometric AFR target, and acceptably small tip-in/tip-out corrections. Bank 1 uses upstream
sensor 1 and bank 2 uses upstream sensor 5. Rich/lean switching updates STFT, with cross-bank checks
and a low-RPM lean-protection rule that prevents an already-negative trim from continuing while the
sensor reports lean.

`o2_fuel_learn_100ms()` maps stored trim zones into LTFT using MAF breakpoints, interpolating
between zones. Its learning gates include sensor/air-path fault flags, IAT, coolant, barometric
pressure, fuel level, accumulated MAF, no cranking blend, active closed loop, and no commanded purge.
It maintains:

- additive idle lean-time learning: `LEA_fuel_learn_lean_time_bank{1,2}`;
- mid-flow zoned learning: `obd_ii_fuel_learn_zone_2_bank{1,2}`;
- high-flow zoned learning: `obd_ii_fuel_learn_zone_3_bank{1,2}`.

The many still-generic `DAT_400088xx` values in this routine are clearly thresholds, bounds, and
debounce periods, but they were not renamed here because their units and exact semantics are not
yet proven.

### Purge-vapor fuel-mass production

Pass-two tracing identifies the producer, not merely the consumer, of
`evap_purge_fuel_mass_b1/b2`:

1. `idle_air_and_evap()` derives modeled purge airflow from purge command and manifold vacuum using
   `CAL_evap_purge_flow_coefficient[duty cycle][vacuum]`; the result contributes to
   `idle_bypass_airflow`.
2. `evap_update_purge_fuel_mass_for_bank(bank)` takes the negative bank fuel-trim error while the
   base target is not in power enrichment. It normalizes that error by required fuel mass, engine
   period, and purge airflow to form a signed concentration-learning error.
3. `evap_update_purge_trim_integrator_for_bank(bank)` integrates the error only while commanded
   purge flow is nonzero and the error direction agrees with bank trim movement. The integrator is
   clamped from zero to a calibrated maximum.
4. The per-bank integrator is scaled into modeled purge fuel flow, multiplied by engine period, and
   divided by 250000 to yield `u16_mass_100ug` per-cylinder-event fuel mass.
5. `injection()` subtracts that mass from the normal air/AFR-derived request independently for each
   bank.

This establishes the output unit with high confidence: the final value uses the same
`u16_mass_100ug` type and arithmetic domain as `inj_fuel_mass_required`. The intermediate
concentration/integrator scale is still unknown; it should not yet be labeled as a physical percent
or hydrocarbon fraction.

## Charge-air temperature and cooling

The sensor conversion path filters a dedicated intake/manifold temperature channel into
`obd_ii_manifold_temp`. If its failure flag (`engine_state_failure_flags & 0x800000`) is set, the
firmware estimates manifold temperature from engine-air temperature and
`CAL_sensor_tmap_expected_temp[rpm][load]`.

`cooling_chargecooler_pump_100ms()`:

- performs a 30-call startup phase;
- accepts a debug duty override;
- supports an engine-off OBD Mode 2F actuator test;
- normally schedules requested pump duty from
  `CAL_cac_pump_dutycycle[obd_ii_manifold_temp]`;
- commands full duty on the manifold-temperature failure flag;
- maps requested duty through `CAL_cac_pump_dc_drive_output` before eMIOS output.

The pump feedback path has SPI driver-status checks, measured-duty reconstruction, command/feedback
tolerance checking, and P023B/P023C-related debounce state in `cac_diagnostic_1000hz()`.

The PWM transition variable at `0x40001b0c` is now retyped from `bool` to
`cac_pwm_output_sequence_state` (`uint8_t`). The original export incremented it and rendered three
successive comparisons as `== true`; this is the characteristic result of applying a boolean type to
comparisons against 1, 2, and 3. The reconstructed sequence is:

```text
0: initialize eMIOS, enter state 1
1: force high for one 100 ms call, enter state 2
2: force low for one 100 ms call, enter state 3
3: apply normal inverse-mapped PWM
```

Any zero-to-nonzero requested-output transition restarts at state 1. The later Evora GT export has
the identical collapsed sequence, supporting common intent. The exact electrical reason for the
high/low preamble is not stated, but the state values and output order are high-confidence.

### Search for a supercharger bypass or recirculation actuator

No ECU-controlled supercharger bypass/recirculation actuator is visible in this firmware export.
The ambiguous GPDO `0xb7` feedback previously named `recirculation_pump_state_???_or_acis` is now
resolved as `cooling_recirc_pump_output_state`: every writer is in `cooling_pump_control()`, which
uses coolant/air temperature, after-run timers, transmission-cooling demand, and Mode 2F bit
`0x400000`. The output is therefore a liquid-cooling recirculation pump, not a charge bypass.

Cross-variant pin comparison also prevents a false positive: on the early naturally aspirated
firmware, GPDO `0xc9` is ACIS and GPDO `0x8f` is an intake flapper. On GT430, `0xc9` is configured for
charge-cooler pump PWM and `0x8f` is the exhaust flap. Searches of output writers, coding flags,
diagnostic actuator tests, and RPM/load valve tables found electronic throttle, exhaust flap,
coolant/transmission pumps, and charge-cooler pump controls, but no remaining candidate bypass
solenoid. The most likely interpretation is that the supercharger's bypass is mechanical/vacuum
operated or integrated outside this ECU's commanded outputs; that last statement is an inference,
not proven hardware documentation.

## Protection and enrichment interactions

- Power enrichment is fundamentally AFR-table driven and may be increased with ignition retard.
- Load/coolant and air-temperature enrichment act directly on pulse width.
- Tip-in, tip-out, post-start, cold-start, cranking, and DFCO-recovery terms are separate, so logged
  AFR target alone does not fully describe transient delivered fuel.
- Rev limiting sets injection flags and eventually fuel-cuts; it is distinct from the duty/load
  capacity limit.
- Injector saturation feeds back as `load_limit_from_inj`, allowing upstream torque/load control to
  reduce requested charge before the pulse window is exceeded.
- Manifold-temperature failure commands maximum charge-cooler pump duty and also changes load and
  injection temperature inputs to fallback/estimated paths.

## Concrete disassembly changes made with this analysis

- Renamed three `injection()` locals to distinguish injector dead-time from fuel-derived pulse:
  `injector_deadtime_20us`, `injector_deadtime_compensated_us`, and
  `_bank2_injector_flow_share`.
- Renamed the four generic `0x4000882a..0x40008836` airflow calibrations as the start/end
  breakpoints for LTFT zone-2 and zone-3 blending. Their roles are directly demonstrated by the
  interpolation arithmetic and learning-zone gates.
- Added stage comments at differential-pressure calculation, closed-loop/power-enrichment delay,
  purge subtraction, trim/additive-offset ordering, and output-window limiting.
- Added load-path comments describing dual-MAF use and Alpha-N selection.
- Added charge-cooler comments documenting temperature scheduling, fail-safe behavior, Mode 2F, and
  its recovered three-state output sequencer.
- Restored the dual-MAF charge expression while leaving the subsequent density-normalized lookup
  coordinate unresolved rather than importing unverified constants from another build.
- Renamed and documented both bank-indexed purge learning/mass functions and resolved GPDO `0xb7`
  as coolant recirculation-pump feedback in both C and the symbol CSV.

## Unresolved areas and next steps

1. Recover the GT430 instructions for the second missing MAF idiom: density normalization and the
   clamped 8-bit torque-to-TPS lookup coordinate. The primary dual-MAF charge is now restored.
2. Determine the physical scale of the purge concentration integrator. Its input, bank allocation,
   output mass unit, and consumer are resolved, but the intermediate fixed-point unit is not.
3. Resolve the exact purpose of `inj_efficiency`: its table and bounds are clear, but whether it
   represents injector characterization, global flow correction, or a composite scale remains open.
4. Map `fuel_control_mode_flags` and `injection_flags` bit-by-bit from all writers.
5. Confirm the inferred absence of an ECU-controlled supercharger bypass against wiring diagrams or
   hardware inspection; further symbol-name searching in this export is unlikely to add confidence.

## Confidence

- High: normal pulse construction order; pressure-dependent dead-time/flow; purge subtraction and
  production; bank trims; pulse clamps; primary dual-MAF expression; Alpha-N/MAF selection;
  charge-cooler temperature scheduling and PWM state order; GPDO `0xb7` coolant-pump identity.
- Medium-high: interpretation of AFR departure as power enrichment and the entry-delay behavior;
  bank-balance ratio as an effective injector-flow split.
- Medium: physical meaning of the injector-efficiency table and some startup correction names.
- Low/not asserted: unidentified `DAT_*` calibration semantics, purge-integrator physical scale,
  GT430 MAF density-normalization constants, and the inferred hardware arrangement of the
  supercharger bypass.

## Marginal value of pass two

This pass closed three operationally important gaps: measured charge is no longer zero in the C
export, purge subtraction now has a traced producer and bank-specific learning loop, and the
charge-cooler PWM output no longer contains impossible boolean branches. It also eliminated the
ambiguous “recirculation/ACIS” output as a possible supercharger-control lead.

Further work from this export alone now has lower marginal value. The next high-value evidence is
external to the decompiled C: GT430 raw instructions/p-code for the second MAF idiom, and vehicle
wiring or hardware documentation for supercharger bypass plumbing. Renaming the remaining purge
`DAT_*` state without either source would mostly replace address labels with speculative terms.
