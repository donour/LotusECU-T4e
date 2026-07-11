# C132E0278 VVT, idle, and thermal-management analysis

Scope: GT430 `C132E0278.c`. Names describe behavior observed in the decompiler export and are not
OEM symbols. This analysis follows the foreground scheduler, fixed-rate tasks, interrupt feedback,
actuator writes, and fault/diagnostic paths.

## Executive summary

The firmware coordinates three strongly coupled systems:

- Four-cam VVT uses common intake and exhaust targets, separate feedback and PI output for each
  bank, startup zero-position learning, low-load alternate maps, transition slew, and four physical
  PWM outputs.
- Idle control selects a coolant-dependent RPM target by transmission/mode, constructs feed-forward
  airflow from learned base flow and accessory loads, then adds proportional and integral speed
  feedback. Its result becomes an electronic-throttle idle request rather than a separate idle valve.
- Thermal management takes the maximum of coolant and AC/air-temperature radiator-fan demands,
  coordinates an engine-bay fan, coolant recirculation and transmission pumps, and independently
  schedules the charge-cooler pump. Sensor faults generally choose conservative full-output or
  calibrated fallback behavior.

The main coupling is explicit: AC compressor load and cooling-fan loads feed idle airflow and
ignition compensation; AC requests influence fan demand; IPS shifts suppress selected fan/pump
loads; after-run cooling extends ECU shutdown time; VVT mode/error state changes idle airflow base
and ignition/fueling behavior.

## Scheduling

```text
foreground pass
  cooling_control()
    radiator fan -> engine-bay fan -> coolant/transmission pumps
  idle()
  read_accessory_states()
  vvt()
  ac_compressor() when AC hardware coding selects this system

1 kHz
  idle_airflow_decay_manager_1000hz()

200 Hz
  vvt_200hz()
  ac_200hz() elsewhere in the fixed-rate task set

100 ms / 10 Hz
  cooling_chargecooler_pump_100ms()
  vvt_update_zero_target_timers_100ms()

asynchronous
  four eTPU cam-edge ISRs update individual cam positions
```

The foreground functions calculate current demands. Fixed-rate functions provide deterministic
target slew, integral updates, decay, and timeout behavior. Cam position is updated at the actual
edge events rather than polled.

## Variable valve timing

### Hardware and feedback

`init_vvt_hardware_and_timers()` configures:

- intake bank 1 on eTPU channel `0x1c`;
- exhaust bank 1 on eTPU channel `0x0f`;
- intake bank 2 on eMIOS channel `0x11`;
- exhaust bank 2 on eMIOS channel `0x12`.

All use a period derived from `CAL_vvt_pwm_driver_divisor`. Bank-1 outputs go through eTPU channel
writes; bank-2 outputs directly update eMIOS compare/control registers with edge-safe handling for
near-zero or changing duty.

The four cam-edge ISRs read eTPU angle/time state, identify the expected cam pattern, wrap angular
deltas, and convert the edge angle into:

- `obd_ii_vvt_inlet_position_bank1`;
- `obd_ii_vvt_inlet_angle_bank2`;
- `obd_ii_vvt_exhaust_position_bank1`;
- `obd_ii_vvt_exhaust_position_bank2`.

Each valid update refreshes a per-cam activity/zero-learning marker. Before synchronization is
established the same ISRs classify edge sequences and write a synchronization direction/state back
to the eTPU crank channel.

### Target selection

Normal intake and exhaust targets come from separate 16x16 RPM/load tables:

- `CAL_vvt_intake_advance_base`
- `CAL_vvt_exhaust_advance_base`

A 6x6 low-load map exists for each side. Its use is bounded by the map axes and gated by coolant
temperature, vehicle mode bit `0x08`, transmission coding/`CAL_vvt_low_load_ips_enable`, and
`CAL_vvt_low_load_disable`. `vvt_intake_mode_flags` and `vvt_exhaust_mode_flags` remember map mode
and transition direction.

Coolant corrections are subtracted after map lookup:

- `CAL_vvt_intake_advance_coolant_offset[coolant]`
- `CAL_vvt_exhaust_comp_temp[coolant]`

Calculated targets are clamped to 172 quarter-degrees for intake and 140 quarter-degrees for
exhaust. These are common targets shared by both banks; the earlier `...bank1` names were misleading
and have been replaced by `vvt_intake_target_calculated` and `vvt_exhaust_target_calculated`.

`CAL_vvt_start_timer[coolant_temp_engine_stopped] * 20` delays normal closed-loop operation after
startup. At 200 Hz, map transitions move the active common target one quarter-degree every ten
calls, or about 5 degrees/second. Startup takes the calculated/observed position directly rather
than applying that slow transition.

### Feedback and output

Each cam has independent error, proportional contribution, and integral accumulator. Intake error
is target minus measured position. Exhaust position uses the export's opposite sign convention, so
its error is target plus the signed measured position.

The foreground loop forms:

```text
output = clamp(proportional_error + integral_accumulator, -400, +400)
driver_command = output / 2 + 400
```

The proportional path uses `CAL_vvt_error_gain_startup`; the 200 Hz task accumulates error using
`CAL_vvt_integral_gain` and clamps each integrator to approximately +/-0x19000. The resulting four
commands are scaled for their eTPU/eMIOS timer domains.

OBD Mode 2F flag `0x1000` bypasses normal feedback and applies one requested output value to all
four cam solenoids.

### Startup learning, zero-target timeout, and fallback

During the coolant-dependent start window, each cam collects position samples, extrema, average,
and activity state. Once the window completes, an average/threshold test determines whether normal
closed-loop output may begin. If a common target remains zero for
`CAL_vvt_zero_target_timeout`, the corresponding intake or exhaust timer expires, its integrator is
cleared, and output is forced to the negative limit until a nonzero target returns.

The timers were previously mislabeled as intake bank 1/bank 2. Their complete use proves that they
are common `vvt_intake_zero_target_timer` and `vvt_exhaust_zero_target_timer` values.

Cam/crank failure bits in `engine_state_failure_flags` suppress the relevant loops, clear integral
state, hold calculated targets at measured positions, and mark transitions incomplete. Separately,
`vvt_intake_fallback_angle_zero` and `vvt_exhaust_fallback_angle_zero` override map targets when their
values are 4 or greater. Exact ownership of several startup flags (`DAT_400024xx`) remains tied to
unnamed diagnostic state, so their bit names were not guessed.

`vvt_error_scale` measures the departure between low-load and normal-map intake/exhaust phasing. It
is consumed by idle airflow and by ignition/fuel paths, demonstrating that low-load VVT mode is
coordinated rather than treated as an isolated actuator change.

### Important VVT calibrations

- `CAL_vvt_*_advance_base[_X_engine_speed][_Y_load]`
- `CAL_vvt_*_advance_base_low_load[_X_engine_speed][_Y_load]`
- `CAL_vvt_low_load_map_enable_temp`
- `CAL_vvt_low_load_ips_enable`, `CAL_vvt_low_load_disable`
- `CAL_vvt_*_coolant_offset` / `CAL_vvt_exhaust_comp_temp`
- `CAL_vvt_start_timer[_X_coolant_temp]`
- `CAL_vvt_error_gain_startup`, `CAL_vvt_integral_gain`
- `CAL_vvt_zero_target_timeout`
- `CAL_vvt_pwm_driver_divisor`

## Idle-speed and idle-air control

### RPM target selection

`idle()` chooses one coolant-indexed target strategy:

- manual Tour: `CAL_idle_target_manual_tour`
- manual Sport: `CAL_idle_target_manual_sport`
- IPS normal: `CAL_idle_target_ips`
- IPS fallback: `CAL_idle_target_ips_coolant_fallback`

The encoded table value becomes `value * 4 + 500 RPM`. IPS state selects normal versus fallback;
manual vehicle mode bit `0x10` selects Tour versus Sport. A second target calculated at
`CAL_idle_sensor_fault_coolant_temp` provides the coolant-sensor fallback basis.

The target is increased by IAT compensation, vehicle-speed decay, high-RPM transient capture, and
an AC/carspeed timer term. `idle_airflow_decay_manager_1000hz()` slews several of these offsets and
manages entry/exit timers so target RPM does not step when strategy or motion state changes.

The principal error is:

```text
obd_ii_idle_speed_error = engine_speed - obd_ii_idle_speed_target_total
```

Ignition uses this error through three idle-error compensation tables for fast torque response,
while `idle()` controls slower airflow.

### Feed-forward airflow

Base expected airflow is indexed by idle target RPM. Manual modes use
`CAL_idle_airflow_expected`; IPS normal/fallback use separate still-unnamed tables. When low-load VVT
mode is active, `vvt_error_scale` and target RPM add a VVT airflow correction.

The base is temperature/start corrected and summed with:

- learned cold/warm idle airflow, separately stored for AC off/on;
- barometric-pressure and ECU-voltage compensation;
- vehicle-speed/moving airflow;
- AC compressor load (`CAL_idle_comp_ac`);
- radiator-fan duty (`CAL_idle_comp_fan`);
- engine-bay fan run-time load;
- steering angle/load;
- clutch anti-stall request;
- failed-cylinder/misfire compensation;
- ignition-startup and high-RPM transient airflow.

The final `obd_ii_idle_air_output` is clamped to `0x13ec` in its flow domain. A pressure/temperature
flow model converts airflow demand into `idle_tps_requested`; engine-off uses a baro/coolant cranking
table, while running operation is capped by `CAL_idle_tps_max_opening`. The electronic throttle path
then incorporates that request.

### PI feedback and learning

`CAL_idle_air_control_proportional[speed error]` supplies a signed proportional airflow term clamped
to +/-`0x500`. The formerly generic `CAL_idle_error_correction_unknown` table is now identified as
`CAL_idle_air_control_integral_step`: its signed output is added to
`idle_air_control_integral_term` when stable idle gates permit. The integrator is bounded by separate
positive/negative calibrations and decays outside idle or during clutch/motion transitions.

Once accumulated MAF, purge state, coolant range, and stable-idle gates permit, sustained integral
bias increments or decrements one of four persistent values:

- `LEA_idle_cold_learning_coolant`
- `LEA_idle_cold_learning_coolant_ac_on`
- `obd_ii_idle_learn` (warm, AC off)
- `LEA_idle_learn_ac_on` (warm, AC on)

The learned cold and warm endpoints are interpolated through `CAL_idle_learn_temp_range`.
`obd_ii_idle_status` distinguishes non-idle, pre-learn, excessive-integral, stable, and output-limited
states, although the precise external enumeration is not documented.

## Cooling and thermal management

### Temperature inputs and fallback

Coolant temperature is voltage-table converted and filtered. An out-of-range coolant input sets the
engine-state fault path, substitutes `CAL_sensor_coolant_temp_fallback_value`, and causes radiator
fan fail-safe operation. The cooling controller chooses ambient-air temperature where supported and
valid, otherwise engine IAT.

### Radiator fan

`cooling_fan_radiator_control()` initializes eMIOS PWM channel 3 and calculates:

- stopped-engine demand from coolant temperature;
- running coolant demand from coolant temperature and vehicle speed;
- AC-off or AC-on demand from selected air temperature and vehicle speed;
- a hot-start demand during `CAL_cooling_fan_startup_time`.

During normal running it selects the maximum of coolant demand and AC/air-temperature demand.
Vehicle speed above `CAL_cooling_fan_speed_disable_speed` and a low-RPM hysteresis state may inhibit
the fan. Coolant/IAT sensor fault bits force full target. OBD Mode 2F flag `0x100000` can request fan
duty while preserving a higher thermal demand. `CAL_cooling_fan_scaling` converts requested duty to
the inverse electrical PWM written to eMIOS.

### Engine-bay fan

If coded present, the engine-bay fan is enabled when radiator duty and selected air temperature
cross calibrated thresholds, after `CAL_cooling_engine_bay_fan_enable_delay`. It has hysteresis,
manual override state, Mode 2F flag `0x10000000`, and engine-off behavior linked to the coolant
recirculation-pump request. IPS shift cooling state suppresses or delays this load.

### Coolant recirculation and transmission pumps

`cooling_pump_control()` writes coolant recirculation pump GPDO `0xb7`. Engine-off coolant above
`CAL_cooling_recirc_reset_coolant_temp` starts an after-run timer and extends `ecu_shutdown_timer`.
Engine-running selection uses idle/motion state, air temperature, RPM hysteresis, dwell, and
transmission cooling demand. Mode 2F `0x400000` and a local override can force the pump.

An optional transmission cooling pump uses GPDO `0x7d`, coding bit `COD[1].20`, a hold timer, Mode
2F `0x80000000`, and its own override. The code prevents transmission-pump operation while the
coolant recirculation output is active, revealing electrical or hydraulic mutual exclusion.

### Charge-cooler pump and shutdown after-run

The charge-cooler pump runs at 10 Hz control cadence from manifold temperature, with full duty on
sensor failure, OBD Mode 2F support, driver-status feedback, and a reconstructed high/low PWM
transition preamble. Its detailed fuel/air interaction is covered in the dedicated fuel/air report;
here it is part of the thermal actuator set.

`shutdown()` looks up after-run time from air and coolant temperature and keeps ECU power alive long
enough to service cooling. The coolant recirculation path can independently extend that shutdown
timer. EEPROM saving and power release occur only after engine-off and hold conditions allow it.

## AC and accessory-load coordination

The AC compressor state machine uses OFF, START, RUNNING, SHUTDOWN, and fault states. Criteria
include coolant, throttle, RPM, vehicle speed, evaporator temperature, minimum runtime, diagnostics,
and Mode 2F relay control. At 10 Hz within `ac_200hz()`, evaporator-temperature P/I/D-like terms
estimate compressor load and ramp engagement/disengagement rather than presenting a step load.

That estimated load drives several consumers:

- `ac_compressor_ign_compensation_active` enables ignition torque compensation;
- `ac_load2____` indexes `CAL_idle_comp_ac` for feed-forward idle airflow;
- `ac_cooling_fan_required` selects the AC-on radiator-fan surface;
- IPS/cooling state can suppress ancillary fans around shifts.

Radiator and engine-bay fan loads are likewise fed back to idle airflow. This is a load-coordination
chain, not independent relay logic:

```text
AC evaporator control -> compressor load estimate -> ignition + idle airflow
                     \-> AC fan request -> radiator duty -> idle fan compensation
thermal demand -> engine-bay fan runtime -----------> idle bay-fan compensation
```

## Concrete disassembly and symbol improvements

- Corrected common calculated VVT target names and the intake/exhaust zero-target timers.
- Renamed `vvt_update_inlet_zero_timers_100ms()` to
  `vvt_update_zero_target_timers_100ms()` because it updates both sides.
- Identified `CAL_idle_air_control_integral_step[_X_speed_error]` and named its two runtime lookup
  results (`idle_air_control_proportional_lookup`, `idle_air_control_integral_step`).
- Added comments at VVT target selection/PI/Mode-2F output, idle composition, and radiator-fan demand
  arbitration.
- Updated matching symbol CSV entries with corrected types/roles.

## Evidence limits and unresolved areas

1. The raw binary/p-code is needed to assign exact meanings to the many VVT startup flags and
   average/extrema variables at `0x400023c0..0x4000243b`.
2. VVT `engine_state_failure_flags` bits are behaviorally separable, but mapping each bit to a
   specific DTC/cam electrical failure requires tracing the diagnostic writers in a separate pass.
3. Several idle tables are still `DAT_4000xxxx`, especially IPS airflow surfaces, VVT airflow
   correction, bay-fan load, anti-stall, and startup flow. Their role is evident but units/axes are
   not all safe to rename from this function alone.
4. `cooling_system_flags` bit meanings are partly recovered from writers, but a complete bit-field
   type would require all diagnostics and Mode 2F consumers.
5. The exact electrical/hydraulic reason for coolant/transmission pump mutual exclusion and the CAC
   PWM high/low preamble requires hardware documentation.

## Confidence and marginal value

- High: VVT target surfaces and coolant offsets; common-target nature; four independent feedback
  outputs; PI structure; zero-target timer identities; idle target selection; idle PI table role;
  accessory-load airflow composition; radiator max-demand/fail-safe logic; pump output identities.
- Medium-high: VVT startup average/validation interpretation, low-load transition flag semantics,
  and AC load estimator's physical scaling.
- Medium: some idle status/state meanings and thermal flag hysteresis semantics.
- Not asserted: OEM flag names, unnamed table units, and hardware reasons behind output sequencing.

This pass adds substantial value because it converts three large subsystems from lists of symbols
into end-to-end control flows and corrects several misleading names. The next pass in the same C
export would have lower marginal value: most remaining gains would be speculative `DAT_*` naming.
Higher-value evidence would come from the raw GT430 image/p-code, wiring diagrams, or logged cam
target/position, idle-air, fan-duty, and accessory-load channels that can validate scaling and state
transitions.
