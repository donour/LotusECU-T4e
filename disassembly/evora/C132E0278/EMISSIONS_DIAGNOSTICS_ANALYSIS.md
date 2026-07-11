# C132E0278 emissions control and diagnostic analysis

Scope: GT430 `C132E0278.c`. This note describes coherent control and monitor flows rather than
cataloguing every DTC. Symbol names are analyst assignments, not OEM labels.

## Executive summary

The emissions system is organized as cooperating state machines:

- Four narrowband O2 inputs have independent heater outputs/current protection, voltage-range,
  activity, switching-time, slow-response, and circuit diagnostics.
- Upstream sensors drive bank-specific closed-loop fuel control and trim learning. Downstream
  sensors are compared with upstream switching in MAF-indexed cells to estimate catalyst oxygen
  storage/efficiency.
- EVAP normal purge estimates vapor fuel mass and compensates injection. Separate diagnostic state
  machines evaluate purge/vent response and sealed-tank pressure decay for gross, small, and
  very-small leaks.
- A shared DTC lifecycle layer debounces monitor results, records drive-cycle completion, pending,
  confirmed and permanent entries, captures freeze frames, and drives readiness/MIL state.
- Confirmed prerequisite faults inhibit dependent monitors and change selected actuator behavior;
  catalyst or fuel-trim monitor failures themselves do not appear to request a torque derate.

## Scheduling and dependency flow

```text
500 us
  O2 heater current conversion and overcurrent shutdown/retry

foreground / 200 Hz
  closed-loop fuel control
  EVAP command and purge airflow/fuel-mass model
  O2 transition/activity counters
  catalyst post-O2 filter and switching-cell accumulation

100 ms
  fuel-trim learning
  EVAP timers and canister state

diagnostic dispatcher groups
  catalyst evaluation, fuel-trim thresholds, O2 response/no-activity,
  EVAP purge/vent plausibility, EVAP pressure-decay leak sizing,
  readiness and shared DTC lifecycle
```

Monitor prerequisites form a hierarchy:

```text
sensor/heater/circuit validity
          |
          +-> closed loop and O2 readiness -> fuel trim monitor
          |                              \-> purge concentration learning
          |
          +-> upstream/downstream O2 validity + stable MAF -> catalyst monitor
          |
          +-> EVAP circuits + pressure sensor + stable idle -> leak/purge monitors
```

This explains the large prerequisite expressions: they prevent a secondary emissions conclusion
when the measurement or enabling control is already known invalid.

## O2 heater and sensor state

### Heater control

Four heater outputs are mapped as follows:

- upstream bank 1: GPDO `0x60`, current ADC channel 4;
- downstream bank 1: GPDO `0x62`, current ADC channel 5;
- upstream bank 2: GPDO `99`, current ADC channel 6;
- downstream bank 2: GPDO `100`, current ADC channel 7.

At startup the 200 Hz scheduler applies a reduced-duty warmup pattern until
`CAL_sensor_o2_heater_warmup_duration`; the on fraction is derived from
`CAL_sensor_o2_heater_warmup_pwm_period`. After warmup, heaters are normally held on. OBD Mode 2F
flag `0x800000` can take control of the heater group.

`O2_heater_500us()` scales all four current channels. If current exceeds
`CAL_sensor_o2_heater_overcurrent_threshold_mA`, that heater is immediately switched off, a local
fault latch is set, a 100-count retry timer is loaded, and `o2_sensor_fault_detection()` is invoked.
Once the timer expires, the output is retried and its latch cleared. Slower diagnostics separately
compare enabled-heater current with `CAL_sensor_o2_heater_undercurrent_threshold` for open/weak
heater detection. Thus overcurrent protection is an immediate actuator safeguard, not merely a DTC.

### Voltage, activity, and switching

The upstream sensors are `obd_ii_o2_sensor1_voltage` and `...sensor5...`; downstream sensors are
`...sensor2...` and `...sensor6...`. Rich and lean classification uses
`CAL_sensor_o2_rich_voltage_threshold` and `CAL_sensor_o2_lean_voltage_threshold`.

The renamed `o2_update_voltage_activity_window()` maintains min/max voltage over a calibrated time
window, resets if the prior range is implausibly large or the state is uninitialized, and marks
activity when the sensor/paired-sensor combination crosses the expected regions.

At 200 Hz:

- `o2_leanrich_detect()` records rich/lean states and transitions;
- `obd_ii_o2_switching_counter()` accumulates rich/lean dwell times and matched transitions;
- `obd_ii_o2_transition_activity_counter()` records voltage extrema, transition counts, and
  duration sums;
- `obd_ii_o2_slow_response_monitor()` evaluates bank-specific upstream response;
- `obd_ii_o2_no_activity_monitor()` coordinates no-activity and Mode 2F test timing.

Switching tests are gated by closed loop, stable throttle/load, MAF source, temperature, runtime,
and the absence of upstream prerequisite DTCs. Per-cylinder O2 readiness is cleared when torque/fuel
cut interrupts normal combustion, preventing transient cut events from being counted as sensor
behavior.

## Closed-loop fuel trims and monitor outcomes

Upstream O2 switching controls `stft_bank1/2`; MAF-zone learning produces LTFT and additive idle
lean-time corrections. The normal control and learning details are documented in the fuel/air note.
From an emissions-diagnostic perspective:

- closed-loop entry requires warm/active sensors and the stoichiometric target;
- purge, tip-in/out, startup enrichment, sensor faults, low baro/temperature, and unstable load
  inhibit learning;
- fuel-trim monitor evaluation requires the relevant O2 circuit/activity/slow-response, EVAP purge,
  MAF, and misfire prerequisites to be healthy;
- P0171/P0172 and P0174/P0175 use bank-specific rich/lean thresholds and debounce counters;
- O2 imbalance windows separately compare bank/cylinder behavior for P219A/P219B-style monitoring.

The stored fuel-trim DTC state is primarily diagnostic. No direct torque reduction or fixed open-loop
fuel command was found on P017x confirmation. Protective behavior comes from the underlying sensor
or air-path fault flags and from normal STFT/LTFT limits, while the confirmed trim code inhibits
dependent catalyst/readiness conclusions.

## Catalyst efficiency and downstream O2 monitors

### Data collection

`catalyst_monitor_o2_filter_update_200hz()` low-pass filters each downstream O2 voltage. Large TPS
rate or transient hold state resets the filter, keeping tip events from polluting the baseline.

`obd_ii_cat_efficiency_eval()` bins operation by MAF and accumulates upstream and downstream
switching separately for each bank:

- `LEA_cat_o2_accum_b1_precat/postcat`
- `LEA_cat_o2_accum_b2_precat/postcat`

The monitor requires sufficient accumulated MAF since start, coolant/IAT/baro, closed loop, vehicle
speed, MAF range, and stable throttle. O2 circuit/heater/response, MAF/MAP, coolant/IAT, fuel-trim,
and misfire faults inhibit the relevant bank.

Upstream crossings and downstream movement around the filtered baseline increment MAF-cell
counters. Cells are marked complete until all eight active bins are populated. The final metric is:

```text
catalyst_ratio = sum(post-catalyst switching) * 1000 / sum(pre-catalyst switching)
```

A healthy catalyst suppresses downstream switching, so a ratio below the calibrated threshold
passes. A high ratio decrements a bank-specific failure debounce and eventually transitions P0420
or P0430. Learned cell accumulators are reset when configured completion/reset bits request a fresh
test.

### Additional downstream-sensor tests

`obd_ii_catalyst_monitor_200hz()` also runs explicit response sequences around rich/lean operation
and fuel cut. It measures how quickly downstream voltage enters the intermediate/lean region,
aggregates repeated trials, and evaluates stuck-rich/stuck-lean/no-activity behavior independently
from the catalyst switching ratio. This prevents a failed downstream sensor from masquerading as a
high-efficiency catalyst.

Catalyst-efficiency confirmation affects readiness, MIL/DTC storage, and future monitor gating. No
engine-protection or torque-limiting response to P0420/P0430 itself was found.

## EVAP purge control and vapor-fuel compensation

`init_evap_purge_solenoid_pwm()` configures eTPU channel `0x1b`. Normal purge command is produced by
`evap_state_control()` and `idle_air_and_evap()`, then written as a 0..10000 PWM command. OBD Mode 2F
flag `0x10000` can override purge duty.

Normal purge enable depends on:

- closed-loop operation on both banks;
- warmup/runtime timers;
- no misfire/fuel-cut condition;
- healthy purge electrical and P0441 state;
- adequate idle airflow/injector pulse reserve;
- power-enrichment and learned-vapor-concentration state.

Purge flow is modeled from duty and manifold vacuum through
`CAL_evap_purge_flow_coefficient`. The model contributes to intake/idle airflow, learns bank-specific
vapor concentration from trim response, produces `evap_purge_fuel_mass_b1/b2`, and subtracts that
fuel from injection. When purge is inhibited while its inferred fuel share is large, negative STFT
is cleared to avoid carrying a purge-induced correction into non-purge operation.

## EVAP diagnostic state machines

The export previously assigned the same function name to two distinct routines. They are now
separated in C and the symbol CSV.

### Purge-flow and vent plausibility

`obd_ii_evap_purge_flow_and_vent_monitor()` evaluates response while purge and/or vent outputs are
commanded. It classifies pressure response into debounced flow states, controls GPDO `0xc3`, and
coordinates:

- incorrect purge flow / response;
- vent-control performance;
- gross inability to draw vacuum;
- purge-solenoid and vent timing windows.

It is gated by runtime, no active purge, closed-loop/trim stability, pressure response, and absence
of purge circuit faults. P0441/P0446 outcomes are based on the sustained response class, not a single
pressure sample.

### Sealed-tank leak sizing

`obd_ii_evap_leak_size_monitor()` builds a prerequisite inhibit mask from EVAP circuit/sensor DTCs,
fuel-level validity, vehicle speed, ambient pressure, IAT/coolant, closed-loop state, and stationary
idle. When enabled, its state machine:

1. closes/commands the EVAP sealing output and waits for settling;
2. records pressure extrema and establishes a corrected target using fuel level/vapor-space tables;
3. applies purge to draw the required vacuum;
4. isolates the tank and measures pressure recovery/decay;
5. compares the result against gross, small, and very-small leak thresholds;
6. records pass/fail test results and completion state for P0455/P0442/P0456.

The test can be cancelled by motion, load, lost closed loop, temperature/baro/fuel-level range, or
prerequisite DTCs. OBD Mode 2F flag `0x4000000` can directly exercise the sealing output. The leak
monitor and normal purge state share flags and outputs, so diagnostic isolation explicitly inhibits
normal purge and its fuel-learning behavior.

## Readiness, custom/secondary monitors, and DTC lifecycle

### Diagnostic dispatch

The main diagnostic scheduler spreads monitor groups across calls using a pending-bit mask. One
group evaluates catalyst, trim, O2 response and misfire continuously; later groups rotate circuit
checks, O2 no-activity, thermostat, EVAP, catalyst/O2 secondary tests, and miscellaneous/custom
monitors. This limits foreground execution time while preserving each monitor's own fixed-rate
timers.

`obd_ii_readiness_monitor_init()` builds 19 generic monitor descriptors from calibration and learned
state. `obd_ii_catalyst_o2_monitors_main()` applies common ignition/drive-condition counters,
prerequisite DTC inhibition, and pass/fail updates. Descriptor types including `0x85` and `0x99`
receive special enable treatment; these appear to be J1979/Mode 06-style custom test categories, but
their OEM names are not present. The code also maintains J1979 ignition and OBD-condition counters.

### Shared state transitions

`obd_ii_monitor_fail_transition()` interprets the low configuration bits as different confirmation
policies. Across those policies it can:

- mark the monitor complete for the drive cycle;
- reset pass/fail debounce counters;
- add a pending DTC;
- record a confirmed or Mode 08 test DTC;
- capture a compact emissions snapshot and a standard freeze frame;
- add a permanent DTC when the configured standard requires it;
- set MIL/lifecycle flags and remember the DTC responsible for freeze-frame priority.

Observed learned-state roles include bit `0x08` for completed-this-cycle, bit `0x20` for pending-list
insertion, bit `0x80` for one-time confirmation recording, and bit `0x40` as monitor inhibition/not
eligible in many monitor routines. Other bits vary with confirmation policy and should not be given
one universal enum without a full lifecycle pass.

`obd_ii_monitor_pass()` marks completion and updates lifecycle flags; `obdii_update_dtc_state()`
handles aging/drive-cycle transitions. Readiness bits are cleared only when both bank monitors reach
an accepted pass/confirmed terminal state. Distance, warmup, ignition-cycle, pending, confirmed,
unknown/test and permanent arrays are maintained separately.

Freeze-frame capture includes RPM, MAF, speed, load, coolant, IAT, TPS, STFT/LTFT, rail pressure,
MAP, commanded AFR/purge, O2 voltages and charge-cooler temperature. This is useful evidence that
the custom diagnostics are integrated into the same OBD lifecycle rather than being standalone
service counters.

## Protective and fallback effects

- O2 heater overcurrent immediately disables the physical output and schedules a retry.
- O2 electrical/heater/activity faults prevent closed-loop readiness, fuel-trim learning and
  catalyst conclusions; torque/fuel cut clears per-cylinder O2 readiness.
- EVAP purge/vent/pressure faults inhibit normal purge learning and leak tests, release diagnostic
  output overrides, and keep vapor fuel compensation from being applied in invalid states.
- Misfire, unstable airflow, power enrichment and transient throttle inhibit trim/catalyst/EVAP
  monitors to prevent false failures.
- Catalyst-efficiency and fuel-trim confirmation primarily affect MIL/readiness/DTC storage. No
  direct torque derate attributable solely to those confirmed codes was found.
- Sensor faults may still have independent engine-control fallbacks through
  `engine_state_failure_flags`; those control fallbacks should not be conflated with the DTC
  lifecycle state itself.

## Concrete disassembly and symbol improvements

- Split duplicate `obd_ii_evap_leak_detection_monitor` names into
  `obd_ii_evap_purge_flow_and_vent_monitor` and `obd_ii_evap_leak_size_monitor`, including the two
  scheduler calls and their distinct CSV addresses.
- Renamed `o2_sensor_range_check_unknown()` to `o2_update_voltage_activity_window()` and named its
  min/max/timer/flag parameters.
- Renamed `init_evap_purge_solenoid_unknown()` to `init_evap_purge_solenoid_pwm()`.
- Added focused comments at the EVAP monitor split and shared DTC failure-transition policy.

## Evidence limits and unresolved areas

1. The many catalyst and O2 `DAT_40001xxx` state bits can be grouped behaviorally, but complete
   named structs require raw p-code and all reset/Mode 2F paths.
2. Exact physical units for catalyst learned accumulators and some downstream response timers are
   not recoverable from table types alone; only the final ratio scale of 1000 is explicit.
3. The EVAP leak-state progression and output roles are clear, but pressure sign convention,
   orifice-equivalent leak thresholds, and GPDO `0xc3` hardware naming need wiring/calibration docs.
4. Generic readiness descriptor types `0x85`/`0x99` are treated specially, but their OEM/standard
   labels are not encoded in the export.
5. A full bit-accurate DTC-state enum needs a dedicated analysis of pass, fail, aging, clear-code,
   permanent-DTC and EEPROM serialization paths across every confirmation policy.

## Confidence and marginal value

- High: heater mapping/protection; O2 activity-window role; catalyst switching ratio and bank
  prerequisites; EVAP monitor split; purge compensation; leak-test phase structure; pending/
  confirmed/freeze-frame lifecycle; absence of catalyst-code-specific torque derate.
- Medium-high: individual EVAP state meanings and readiness descriptor grouping.
- Medium: exact DTC state-bit semantics outside the observed common roles.
- Not asserted: OEM monitor names, leak-orifice units, or undocumented hardware pressure polarity.

This pass has high marginal value because it removes a duplicate-function collision, joins control
and diagnostic halves of O2/EVAP/catalyst behavior, and distinguishes monitor inhibition from actual
engine protection. Further work from the C export alone has diminishing returns: it would mostly
rename dense state bits. Higher-value next evidence is raw p-code, calibration values, Mode 06 scan
results, wiring diagrams, and drive-cycle logs containing O2 voltages, heater currents, purge duty,
tank pressure, catalyst counters and readiness transitions.
