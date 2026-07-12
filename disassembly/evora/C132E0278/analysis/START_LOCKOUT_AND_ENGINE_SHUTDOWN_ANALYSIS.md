# C132E0278 start lockout, combustion inhibit, and shutdown analysis

## Scope and principal conclusions

This report identifies the conditions in the C132E0278 application that can prevent starter-relay
operation, prevent the engine from reaching synchronized combustion, suppress ignition or fuel,
disable the electronic throttle, or impose a protective engine limit. It also identifies common
faults that **do not** cause a start lockout.

The principal conclusions are:

1. The ECU does control a starter-relay output. It requires a qualified start input, ignition-on
   state, variant-dependent clutch/brake/transmission conditions, a completed throttle startup
   activity window, and a valid program/calibration pairing.
2. Starter rotation is not enough to authorize normal spark and sequential injection. The eTPU must
   reach full crank/cam synchronization state 4, and the program-version/CVN integrity gate must pass.
3. A locked ECU with the wrong calibration CVN or program-version string is a true no-crank/no-run
   condition. The development magic `WTF?` bypasses both gates, but stock C132E0278 contains four
   spaces and is locked.
4. Loss of ignition input immediately withdraws starter authorization, disables cylinder ignition,
   drives the fuel-pump target to zero, and begins the orderly power-hold/shutdown sequence.
5. Hard rev limiting cuts injection; catalyst-damaging misfire and coil electrical faults suppress
   spark on affected cylinders/banks; the HC08 electronic-throttle supervisor can latch fault or
   shutdown and remove throttle authority.
6. Most sensor and OBD faults are not no-start commands. The firmware usually substitutes a value,
   inhibits learning, limits throttle, or selects the stock 4000 rpm limp rev limit.
7. No application-level immobilizer challenge/response or key-code authorization was found. An
   upstream alarm/body controller can still inhibit the physical start input or power externally,
   but that is outside the control logic recovered here.

The analysis is based on `C132E0278.c`, `C132E0278_symbols.csv`, the stock
`C132E0278_TAB.cpt`, and the focused crank/cam, throttle, sensor, ignition, CAN, and runtime reports in
this directory. Addresses are MPC5534 application addresses. Decompiled local-variable names and a
few low-level eTPU flag meanings remain imperfect, so the report distinguishes direct evidence from
inference.

## Outcome matrix

| Condition | Starter relay | Fuel pump / injection | Ignition | Throttle / other result | Confidence |
|---|---|---|---|---|---|
| Ignition input below threshold | Off | Pump target zero; key-off injection state asserted | All cylinder events suppressed | Orderly shutdown after engine stops/after-run expires | High |
| Start input absent, not yet qualified, or re-engagement window expired | Off | Normal prime/run policy otherwise | No direct change | Prevents cranking through ECU relay | High |
| Required manual clutch state absent | Off | No direct change | No direct change | Driver sees no-crank | High |
| IPS state/brake condition invalid | Off | No direct change | No direct change | Driver sees no-crank | High for family branch; dormant in this manual calibration |
| ETB startup/calibration activity in progress | Off | No direct change | No direct change | Temporary no-crank until activity clears | High |
| Program-version mismatch or CVN mismatch while locked | Off | Initial crank/batch behavior may occur only if starter is forced externally; normal synchronized run is denied | Normal synchronized spark is denied | True application integrity lockout | High |
| Crank/cam eTPU never reaches sync state 4 | Starter may crank | Prime and a limited initial batch event can occur; sustained sequential operation is not armed | Normal synchronized spark is not armed | Crank-no-start | High for sync-state gate; individual sensor attribution is conditional |
| Ignition startup delay not complete | Already cranking | Initial startup scheduling only | Normal per-cylinder scheduling delayed | Normal startup sequencing, not a fault | High |
| Hard rev limit exceeded | Unchanged | Direct injection cut with hysteresis | Not the primary hard-cut mechanism | Soft limiter also closes throttle | High |
| DFCO / intentional torque cut | Unchanged | Fuel or selected-cylinder cut | May preserve/re-enable selected sparks | Normal operating intervention, not a fault | High |
| Coil electrical fault | Unchanged | No proven blanket injector shutdown | Affected cylinder spark suppressed | Cylinder excluded from torque/combustion accounting | High for spark; unresolved for paired injector cutoff |
| Catalyst-damaging misfire | Unchanged | No separate blanket injector-cut statement is justified by the recovered C | All three cylinders of affected bank lose spark; both banks can remove all combustion | Limp rev limit and severe-misfire throttle cap | High |
| HC08/MPC hard ETB fault | Starter logic is not directly latched off after startup activity clears | Base fuel/spark logic can remain active | Base fuel/spark logic can remain active | Motor PWM/bridge disabled; HC08 shutdown interlock can latch; engine may fail to start or stall for lack of air | High software behavior; medium physical interlock effect |
| Ordinary sensor fault | Normally available | Uses fallback/open-loop policy | Uses fallback/knock-safe policy | Limp, substitute, or learning inhibit; normally not no-start | High |
| Low oil pressure | Unchanged | No direct oil-pressure fuel cut found | No direct oil-pressure spark cut found | Failure bitmap selects 4000 rpm limp limit | High |

## 1. Starter-relay authorization

### Hardware boundary

`set_driver_input_brake_clutch_100hz()` at `0x0004DC9C` owns normal starter permission. The
qualified command is represented by `obd_ii_relay_status.bit4` and
`driver_input_flags[1].bit0`. `read_serial_peripherals()` at `0x00049B48` writes the relay-status
byte through DSPI-B on each foreground pass, making bit `0x10` an actual output-expander command,
not merely an OBD status bit.

The debounced start request is `digital_input_debounced[5]` at `0x40003045`. Fourteen digital inputs
are sampled at 100 Hz. On ignition-off, the start-input qualification timer is reset to 40 ticks.
After ignition-on, the input must first be inactive long enough to clear that startup window and then
active for the additional ten-tick qualification represented by `DAT_400018DB`. This prevents a
button held through key-on or a bouncing input from immediately engaging the relay.

The common start-request predicate is false when any of these is true:

- `ignition_on_flags.bit0` is clear;
- `runtime_since_start >= DAT_40008774`;
- the qualified start-input latch is clear;
- `throttle_actuator_activity` is true.

Stock `DAT_40008774` is `0x0190` = 400 ticks. `runtime_since_start` advances at 200 Hz, so the ECU
withdraws starter authorization approximately 2.0 seconds after the engine is considered running.
It is zero while the engine is stopped, so this is primarily a starter re-engagement/overrun guard,
not a fixed cranking timeout.

### Manual GT430 branch

The calibration is manual (`COD[0].bits13..15 == 0`). For model-year/VIN coding before the
firmware's `'H'` threshold, the qualified start predicate is sufficient. For later coding, normal
permission additionally requires either:

- clutch-input type zero, meaning the branch does not require the potentiometer/discrete
  disengaged bit; or
- `clutch_pos_sensor.bit2`, the qualified clutch-disengaged state.

The start input must also have completed the stable-input countdown. Consequently a missing,
mis-coded, electrically failed, or not-fully-disengaged clutch input can produce a no-crank on the
later manual branch.

### IPS family branch

The same binary retains an IPS path, although it is dormant for this GT430 manual coding. It permits
start only when the transmission state is `0` or `9`, the brake is qualified (or the calibrated
vehicle-speed exception is met), and the common start predicate is true. A brake/clutch inactive
timer delays the visible relay command in part of this path.

### Coding-error fallback

`main_diagnostic_flags.bit4` is set when all eight primary coding bytes are `0xFF` and is reported
through the P0610 vehicle-options monitor. In this state the normal manual/IPS split is bypassed. The
fallback requires the common start predicate plus a brake/speed condition. This is changed start
interlock behavior, not an unconditional P0610 no-start.

### Integrity gate applied to the starter

Before any normal starter branch, the routine requires:

```text
(!prog_version_mismatch && calculated_CVN == CAL_ecu_cvn) || ecu_unlocked
```

Failure clears relay bit `0x10`, clears the driver-input start bit, and sets
`DAT_40001736`. This is the first of two independent applications of the same integrity gate.

### Starter DTCs do not themselves latch out the relay

P0616 and P0617 monitor starter-relay feedback/circuit state and update
`ignition_on_flags.bits5..6`. The recovered code does not use the matured P0616/P0617 DTC state as a
persistent starter authorization veto. A physical open/short can of course prevent cranking even
though the diagnostic code is not the command source.

Mode 2F control identifier `0x0184` can also pulse the starter relay while ignition input is off and
engine speed is zero. That is a bounded workshop output test, not part of normal start authorization.

## 2. Ignition-voltage and ECU power-state lockout

`ecu_power_hold_and_shutdown_manager()` at `0x0005B570` compares
`sensor_adc_ign_voltage` with `CAL_ecu_ign_threshold << 2`. The stock threshold byte is `0x55`.
With the internal 0..5 V ADC representation this is about 1.67 V at the ADC input; connector-level
voltage depends on the ECU input divider and should not be inferred from that number alone.

When ignition voltage is below threshold:

- `ignition_on_flags.bits0` and `4` are cleared;
- normal start permission is withdrawn at the next 100 Hz input update;
- `injection()` asserts its key-off state bit `0x10` and substitutes minimum pulse-time values;
- each ignition-cylinder ISR disables its eTPU ignition channel because
  `ignition_on_flags.bit0 == 0`;
- `fuel_pressure_lookup_target()` returns zero and resets the pump state;
- `fuel_pump()` commands zero once its target/prime/crank activity conditions no longer apply;
- the ECU waits for zero engine speed and cooling/diagnostic after-run conditions, saves learned data
  once when supply permits, and releases its power-hold GPIO.

The exact final injector-channel interpretation of `injection_flags.bit4` is obscured by the eTPU
ABI, so bit `0x10` should be called the key-off injection state rather than independently claimed as
the sole hardware cutoff. Spark suppression and the zero fuel-pump target are direct and sufficient
to establish engine shutdown behavior.

When ignition voltage rises above threshold, the manager sets `ignition_on_flags.bit0`, asserts the
power-hold output, and refreshes the calibrated after-run timer. There is no separate application
immobilizer state in this transition.

## 3. Program/calibration integrity no-start

### How the checks are formed

`copyCAL2RAM()` at `0x00042A40` copies the calibration shadow, calculates CRC-16/ARC over the
calibration payload, and stores the result in `calibration_verification_number` at `0x40001FA0`.
The stored expected CVN is `CAL_ecu_cvn` at `0x4000EFFE`.

`copyCOD2RAM()` at `0x000C1FD4` compares 31 bytes of `CAL_prog_version` at `0x4000E028` with the
application-side version block at `0x40008080`. A difference sets `prog_version_mismatch` at
`0x4000278F`.

`CAL_ecu_unlock_magic` at `0x4000EFFA` controls the bypass. Exactly `WTF?` sets
`ecu_unlocked=true`; every other four-byte value leaves it false.

### Second gate: synchronized combustion authorization

`inj_interrupt()` at `0x000462C8` changes `engine_running_state` from 0 to 1 only when:

```text
eTPU synchronization state == 4
AND
((program version matches AND calculated CVN equals stored CVN) OR ecu_unlocked)
```

Only after this transition are the synchronized ignition channels, injector channels, MAF/MAP
event, and knock-window event armed for normal operation. A failed integrity check sets
`DAT_40001736` and leaves `engine_running_state` at zero.

Thus the same mismatch blocks both the ECU-controlled starter relay and, if the relay is bypassed or
the engine is externally cranked, normal synchronized combustion.

### Stock and supplied tuned artifacts

The stock CPT contains:

```text
CAL_ecu_unlock_magic = "    "
calculated CVN        = 0x3378
stored CAL_ecu_cvn    = 0x3378
```

It therefore passes while locked. The supplied 2026 tuned CPT contains `WTF?` and does not carry a
normally matching locked CVN; it relies on `ecu_unlocked` to bypass the gates. Removing `WTF?`
without recomputing the CVN produces a true no-start. See `CPT_DEFINITION_VALIDATION.md` for the
artifact-specific CRC calculations.

## 4. Crank/cam synchronization and startup event gating

### Authoritative gate

The eTPU crank channel exposes a crank state, cycle position, and synchronization state.
`inj_interrupt()` treats synchronization state 4 as the authoritative full-sync state. Before that
state is reached, `engine_running_state` remains zero and foreground `ignition()` and `injection()`
do not perform their normal synchronized scheduling because both require:

```text
engine_running_state == 1 && ign_startup_delay_counter == 0
```

The first unsynchronized crank activity can configure a limited all-cylinder/batch injection event.
It should therefore not be stated that a no-sync engine receives literally no fuel. The defensible
result is: no full synchronization means no normal synchronized spark and no sustained sequential
combustion authorization, so the engine will crank without starting.

### What can prevent state 4

At a system level, the causes include:

- absent or invalid crank edges;
- a crank pattern that never reaches the eTPU's valid state;
- missing/implausible cam phase information when the eTPU needs it to resolve the 720-degree cycle;
- repeated synchronization loss or eTPU reinitialization.

P0335 is the crank diagnostic and P0341/P0346/P0366/P0391 are the four cam diagnostics, but a stored
or matured cam DTC is not itself a direct software shutdown command. The causal statement must be
made in the forward direction: a signal failure that prevents eTPU sync state 4 causes no-start.
Some individual cam faults after synchronization instead disable VVT/learning and permit continued
operation.

### Engine-running hysteresis

`engine_speed_and_cyl_cut_update_1000hz()` separately derives `engine_is_running` from filtered
engine period. Stock values are:

- `CAL_ecu_engine_running_period_max = 0xA769` (approximately the 350 rpm entry threshold);
- `CAL_ecu_engine_stopped_period_min = 0xFFFF` (approximately the 229 rpm exit threshold).

This hysteresis affects runtime timers, fueling state, starter re-engagement, and diagnostics. It is
not a security authorization check.

### Normal startup delay

`coil_driver_state_machine()` initializes `ign_startup_delay_counter` to 12. The ignition event ISRs
count it down and arm the six channels at the transition. This is a deliberate event-ordering delay,
not a fault lockout. A stuck/reinitializing eTPU can keep recreating the symptom, but the value itself
is normal.

## 5. Direct fuel and spark suppression while running

### Hard rev-limit fuel cut

`injection()` at `0x00051F58` compares actual RPM with `revlimit_hard`. At or above the threshold it
sets injection state bits `0x08` and `0x01`, records/escalates repeated cut activity, and suppresses
combustion independently of DPM torque arbitration. Bit `0x08` is released only below:

```text
revlimit_hard - CAL_revlimit_fuelcut_hysteresis
```

The stock hysteresis is 600 rpm. `revlimit()` at `0x000C3448` also closes throttle through the soft
airflow controller before/escalating around the hard cut.

When the aggregate failure mask or both-bank misfire state requests limp operation, the normal rev
envelope is capped by stock `CAL_revlimit_limp_mode = 4000 rpm`. Reaching that cap invokes the same
hard injection-cut path; the fault bitmap itself is not an immediate zero-RPM fuel cut.

### DFCO and commanded torque cuts

`injtip()` sets `inj_flags.bit0` for deceleration fuel cutoff after RPM, coolant, speed, pedal,
clutch, cruise, and hysteresis conditions are satisfied. It sequentially restores cylinders on exit.
Traction/DPM and other torque sources can request rotating cylinder suppression plus residual spark
retard and throttle limitation.

These can feel like ignition/fuel interruption but are intentional operating controls, not error
lockouts. They must be excluded when diagnosing an intermittent no-start.

### Coil electrical failures

The six ignition event ISRs at `0x00047934..0x000484EC` test one bit of
`coilpack_failure_flags` for each physical cylinder. A set bit disables that cylinder's eTPU
ignition channel and removes it from active-cylinder/torque calculations. P0351..P0356 mature these
per-coil states.

The recovered application code proves spark suppression. It does not expose a sufficiently clear
paired injector-channel command to claim that every P035x event also shuts the corresponding
injector, so that stronger statement is intentionally not made here.

### Catalyst-damaging misfire bank shutdown

`misfire_detection_update()` at `0x0007BBC8` can set `misfire_condition_flags.bit5` for bank 1 or
bit 6 for bank 2 when the catalyst-damage monitor matures. The same six ignition ISRs then disable
all three ignition channels belonging to that bank:

```text
bank 1: cylinders 1, 3, 5  (internal indices 0, 2, 4)
bank 2: cylinders 2, 4, 6  (internal indices 1, 3, 5)
```

`coilpack_failure_set()` at `0x0007DD40` can additionally latch individual coil failure bits from
the per-cylinder counts. `failed_ignition_cyl_count` feeds torque estimation, severe-misfire throttle
limits, and limp-rev-limit selection. With both banks failed, normal combustion torque is zero and
all six spark channels are suppressed.

This is an engine-protection shutdown of combustion, not the response to an ordinary P030x emissions
misfire alone. The catalyst-damage thresholds, bank flags, and debounce state must mature.

## 6. Electronic-throttle fault and shutdown paths

### MPC local fault

`tps_control_1000hz()` at `0x000AC330` disables throttle PWM and bridge enable, enters
`ETB_FAULT`, and sets `engine_state_failure_flags.bit16` when any of the following terminal
supervisory conditions is present:

- confirmed local dual-TPS/system fault;
- pre-existing hard ETB failure bit;
- left-foot-brake terminal fault state;
- latched P2107 communication/CRC path;
- HC08 `throttle_actuator_state >= TSL_FAULT`.

Single TPS or pedal-track faults normally use the surviving track. A default calibration after low
voltage or a recoverable calibration problem can continue in degraded mode. These are not all
equivalent to ETB fault.

### HC08 terminal states

The HC08 safety supervisor independently checks redundant throttle signals, captured position,
command plausibility, communication, and self-tests:

- `TSL_FAULT` (9) asserts the fault interlock;
- `TSL_SHUTDOWN` (10) asserts fault plus shutdown interlocks;
- both are monotonic until HC08 reset.

P2104 reports forced-idle/severe fault, P2105 reports `TSL_SHUTDOWN`, P2106 reports degraded
authority, and P2107 reports supervisor/communication failure. The MPC also calls
`throttle_disable()` at `0x000AAB6C`, producing zero PWM and bridge disable.

This path does not explicitly clear `engine_running_state` or set the hard-rev injection flag. Its
primary authority is air/throttle and the independent hardware interlock. A closed, spring-returned,
or electrically inhibited throttle can prevent starting or stall the engine, but the connector-level
effect of the HC08 discrete shutdown pin requires schematic/bench confirmation.

`throttle_actuator_activity` is separately used in the starter predicate. Active key-on throttle
calibration/self-test can therefore cause a temporary no-crank even before a terminal ETB fault is
declared.

## 7. Fuel-pump behavior and fuel-pressure faults

`fuel_pressure_lookup_target()` at `0x000C8FAC` and `fuel_pump()` at `0x000C92E8` form the visible
pump authority path.

The pump command is zero when:

- ignition voltage is below threshold;
- ignition-on state is absent;
- the target is zero; or
- both crank-activity and prime timers have expired.

Every valid crank event reloads `fuel_pump_crank_activity_timer` from stock
`DAT_400087A6 = 600`. Both pump activity timers decrement in the 200 Hz routine, giving a nominal
three-second hold when not refreshed. This stops the pump after a stall or failed crank signal while
allowing prime/crank operation.

A failed fuel-pressure sensor sets aggregate bit `0x04000000`, but the firmware reconstructs
pressure from the commanded differential target plus barometric pressure and continues open-loop
pump control. It does not command no-start.

Likewise P0627/U0109 pump-controller/relay-state diagnostics, P0087 low pressure, and P0088 high
pressure are monitor paths in the recovered application; their matured DTC states are not direct
software fuel-cut commands. The underlying hardware failure can still cause a real crank-no-start by
producing no fuel pressure.

Diagnostic Mode 2F can override the pump output for workshop testing. That override is a separate
test path and should be cleared before interpreting normal pump behavior.

## 8. Faults that normally do not lock out starting

The following table is important because equating every DTC with a shutdown would substantially
misrepresent this firmware.

| Fault family | Normal firmware response |
|---|---|
| P0562/P0563 system voltage | Diagnose and compensate injector dead time/dwell; P0562 can alter safe learned-data save policy. No explicit DTC-state no-start gate. Actual brownout can reset the ECU. |
| Coolant/IAT faults | Calibrated temperature substitution; conservative thermal, enrichment, and learning behavior. |
| MAF fault | Alpha-N/load fallback and limp rev-limit eligibility, not immediate shutdown. |
| MAP fault | Calculated manifold-pressure substitution. |
| Barometer fault | Calibrated pressure fallback. |
| Fuel-pressure sensor fault | Target-plus-baro pressure reconstruction and open-loop pump control. |
| One pedal/TPS track fault | Select surviving plausible track and degrade authority. |
| Dual pedal fault | Driver demand forced toward zero/fault value; engine can still idle if ETB remains controllable. |
| Knock sensor/cam/VVT faults | Disable learning/closed-loop feature, apply knock-safe or fallback state, and select limp limit as applicable. A signal failure that prevents initial crank sync is the separate no-start case. |
| Low oil pressure/P052x | Warning and aggregate failure bit `0x02000000`; selects 4000 rpm limp limit. No separate oil fuel/spark cut found. |
| ABS, wheel-speed, steering, IMU, traction/DPM faults | Disable traction/cruise/performance authority; do not inhibit base combustion. |
| P0601/P0606 stored monitor state | Diagnostic reporting. A watchdog/machine reset interrupts all outputs while reset occurs, but the matured DTC is not itself a persistent no-start command. |
| P0630 VIN missing / P0610 coding error | Alter coding diagnostics and, for blank primary coding, starter fallback logic. Neither DTC state alone is the CVN/program integrity lock. |
| O2, trim, catalyst, EVAP faults | Disable dependent monitoring/learning or use base fueling; ordinary instances do not stop the engine. Catalyst-damaging active misfire is the distinct protective bank-spark case. |

## 9. No application immobilizer was found

Searches of the receive map, diagnostic dispatcher, start-relay predicate, calibration integrity
gate, and combustion-state transition found no rolling key code, transponder challenge, body-module
authorization bit, or application SecurityAccess service controlling start.

This does not prove that the vehicle has no immobilizer. It means the recovered C132E0278
application does not implement one in the visible start/fuel/spark path. An external immobilizer can
still withhold the start-input GPIO, starter supply, ECU ignition supply, or another hardware enable.
The application diagnostic protocol also lacks UDS SecurityAccess (`0x27`); the `WTF?` calibration
magic is a development bypass for image integrity and memory access, not a vehicle key handshake.

## 10. Symptom-oriented diagnosis

### No crank from the ECU-controlled relay

Check, in order:

1. ignition ADC above the calibrated threshold and `ignition_on_flags.bit0` set;
2. start input `digital_input_debounced[5]` transitions inactive after key-on, then remains active
   through its qualification delay;
3. `throttle_actuator_activity` has cleared;
4. clutch-disengaged state/coding for the later manual branch;
5. blank-coding `main_diagnostic_flags.bit4` fallback and its brake condition;
6. `prog_version_mismatch`, calculated CVN, stored CVN, and `ecu_unlocked`;
7. commanded `obd_ii_relay_status.bit4`, DSPI driver status, relay wiring, and P0616/P0617 feedback.

### Cranks but does not start

Check, in order:

1. eTPU crank state and full sync state 4;
2. `engine_running_state` transition and integrity gate;
3. `ign_startup_delay_counter` progress rather than repeated reset;
4. ignition-on bit at each cylinder ISR;
5. fuel-pump target, prime/crank activity timers, PWM command, and physical rail pressure;
6. all-bank misfire flags and `coilpack_failure_flags`;
7. HC08 state, ETB initialization state, PWM/bridge enable, and actual throttle position.

### Starts then stalls or loses power

Check ignition-voltage dropout first, then crank synchronization loss, pump activity refresh, HC08
fault/shutdown, catalyst-damage bank flags, hard/limp rev-limit state, and intentional DFCO/torque-cut
flags. Stored sensor DTCs should be interpreted through their active fallback bits rather than assumed
to be the shutdown cause.

## 11. Remaining uncertainties and recommended verification

1. Recover the proprietary eTPU microfunction ABI to map every `injection_flags` bit to the exact
   channel action and prove whether coil/misfire protection also cancels the paired injector event.
2. Capture start input, clutch state, relay command, crank sync state, and HC08 state on a stock
   manual GT430 to validate the debounce timing and exact clutch-coding branch.
3. Trace the HC08 PTD3/PTD4 interlocks and MPC throttle bridge signals on the schematic/PCB to prove
   their physical effect during `TSL_FAULT` and `TSL_SHUTDOWN`.
4. Determine which individual cam-signal combinations are sufficient for initial eTPU sync state 4;
   do not infer that every P034x/P036x/P039x code is a no-start.
5. Confirm connector-level scaling of the ignition ADC threshold and real brownout behavior.
6. Identify the physical body/alarm wiring feeding digital input index 5 to document any external
   immobilizer authority outside this firmware.

## Confidence summary

- **High:** starter relay is ECU-controlled; common start predicate; manual/IPS/fallback branches;
  program/CVN double gate; stock unlock/CVN values; sync-state-4 combustion gate; ignition-off spark
  and pump shutdown; hard-rev injection cut; coil/misfire spark suppression; sensor fallback policy;
  4000 rpm stock limp limit.
- **Medium-high:** timing interpretation of the start qualification state from its 100 Hz counters;
  approximate RPM equivalents of the engine-period thresholds.
- **Medium:** exact connector-level effect of HC08 shutdown; whether all protective spark cuts have a
  paired injector cancellation hidden inside the eTPU microcode.
- **Not found:** application-level immobilizer/key authorization or a generic "any DTC = no-start"
  latch.
