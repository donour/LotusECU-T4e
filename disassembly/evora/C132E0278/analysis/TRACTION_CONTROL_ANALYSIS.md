# GT430 ECU traction-control analysis

## Scope and main conclusion

`C132E0278` contains two distinct pieces of logic that should not be treated as one controller:

1. `slip_detection_and_tc_indicator()` is an older, gear/engine-speed based slip detector. It derives candidate gears from vehicle speed, engine speed, learned/configured gear ratios, power, steering and lateral acceleration. Its directly observed outputs are state flags, a recommended gear and cluster indications. No direct torque-limit output from this routine has been found.
2. The GT430 DPM path (`dpm_slip_calculator()` plus `dpm_system_state_manager_200hz()`) is a real ECU-side closed-loop traction controller. It compares rear and front wheel speeds, constructs an adjustable slip target, and produces separate fast (spark-capable) and slow (throttle/airflow) torque limits.

The second path is the GT430's variable traction-control implementation. This conclusion is high confidence because its torque requests enter `torque_limit_request_arbitration()` under the explicit `VM_DPM_ACTIVE` gate and then feed the normal fast/slow engine torque-limiting channels.

## Execution and call flow

```text
ABS CAN interrupts
  0xA2 -> LF, RF, vehicle speed, validity flags
  0xA4 -> LR, RR, brake state, validity flags
  0xA8 -> ABS/ESP state and mode feedback
             |
             v
main loop (nominally fast / approximately 1 kHz)
  dpm_slip_calculator()
    axle maxima and left/right deltas
    rear slip and adjustable target
    asymmetric slip-error filter
    proportional table + accumulated integral cut
    fast/slow DPM torque limits
             |
             v
200 Hz task
  dpm_system_state_manager_200hz()
    CAN/fault enable gate
    DPM +/- level handling
    cornering/direct-mode hysteresis
    integral accumulation
             |
             v
torque_model() -> torque_limit_request_arbitration()
  selects DPM limits while VM_DPM_ACTIVE and flags ACTIVE+ENABLED
  fast output -> torque_limit_external_request
  slow output -> torque_external_request_tps_based
  downstream torque model uses ignition and throttle/load paths
```

The wheel-speed front acceleration helper (`wheelspeed_front_rate_200hz()`) belongs primarily to the older slip-indicator logic. The DPM controller consumes the four decoded wheel speeds directly.

## CAN inputs

### Message 0xA2

`flexcan_a_rx_wheelspeeds()` decodes:

- left-front wheel speed;
- right-front wheel speed;
- a separate vehicle-speed field;
- XOR checksum and rolling counter.

The wheel fields are packed 14-bit values. Raw `0x3fff` marks an invalid wheel. Front wheel values are scaled by `CAL_wheel_speed_multiplier_front`; the invalid LF/RF states set `dpm_wheel_speed_invalid_flags` bits `0x10` and `0x20` respectively.

### Message 0xA4

The same receiver decodes:

- left-rear and right-rear wheel speeds;
- brake-switch state in the low two bits of the retained status byte;
- XOR checksum and rolling counter;
- two extra diagnostic/status bytes when the DLC is eight.

Rear invalid states set `dpm_wheel_speed_invalid_flags` bits `0x40` and `0x80`. The rear wheel values use `CAL_wheel_speed_multiplier_rear`.

### Message 0xA8

Six bytes are received. Confirmed downstream effects include ABS/ESP state flags, two single-bit status values, and `abs_a8_flag2` (three bits). This feedback participates in vehicle-mode plausibility and can force launch/DPM modes back to Race. Exact semantic names for every A8 field remain unresolved.

### CAN health gating

Two values formerly typed and named as boolean "enable conditions" are actually counters:

- `abs_can_rx_health_counter` is charged/depleted by the U0122 communication monitor according to received ABS torque-request validity flags.
- `abs_can_plausibility_health_counter` is charged/depleted by the U0416 plausibility monitor after checking A2, A4, A8 and B7 message health/mode agreement.

Both counters must be nonzero, all four wheel-valid bits must be clear, and the ABS inhibit bit (`abs_esp_flags & 0x10`) must be clear for the DPM state manager to run. Otherwise it sets DPM disabled bit `0x20`.

## Slip calculation and target

The controller deliberately uses the faster wheel on each axle:

```text
front_reference = max(LF, RF)
rear_reference  = max(LR, RR)
slip_1_8_percent = rear_reference * 800 / front_reference - 800
```

Slip is clamped to zero unless the rear reference exceeds a nonzero front reference. The factor of 800 gives the declared unit of 1/8 percent: 10% slip produces approximately 80 counts.

It also computes `abs(LF-RF)`, `abs(LR-RR)`, and their maximum. A calibrated left/right-difference threshold with on/off delays sets DPM control bit `0x0004`. This is best described as a cornering/direct-target mode rather than a proof of wheel spin: when set, `CAL_dpm_slip_target_offset` is omitted from the target.

The target has two sources:

- without adjustable-level operation, a 6x6 vehicle-speed/pedal table provides the target;
- with adjustable-level operation, a level-indexed base target is added to the speed/pedal table contribution.

The target variables use 1/8-percent units, although the pedal table elements are declared in coarser 2-percent units and are shifted left four before addition. `CAL_dpm_slip_target_offset` is added only when direct/cornering bit `0x0004` is clear.

Only positive error is controlled:

```text
error = max(actual_slip - target_slip, 0)
```

The error filter is asymmetric. Rising error is accepted immediately; falling error is low-pass filtered using `CAL_dpm_slip_filter_coeff` versus vehicle speed. That gives rapid intervention onset and a calibrated decay/release.

## Intervention and torque outputs

DPM intervention requires all of the following in `dpm_slip_calculator()`:

- `vehicle_mode == VM_DPM_ACTIVE`;
- vehicle speed between `CAL_dpm_min_vehicle_speed` and `CAL_dpm_max_vehicle_speed`;
- engine speed above `CAL_dpm_min_engine_rpm`;
- no injector-cut state (`inj_flags & 1` clear);
- a valid target (`dpm_control_flags & 0x0008`);
- DPM not inhibited (`dpm_control_flags & 0x0020` clear);
- filtered slip error above `CAL_dpm_intervention_threshold`.

At first entry it snapshots `torque_net_engine_combustion`. A 6x10 table, `CAL_dpm_torque_cut_factor`, supplies a proportional cut versus front-axle speed and slip error. The 200 Hz supervisor periodically adds an integral term using:

- `CAL_dpm_integral_gain`;
- `CAL_dpm_integral_limit`;
- `CAL_dpm_integral_update_period`.

The proportional and integral fractions saturate at 255. They reduce the snapshotted torque to form `torque_limit_dpm_spark`, bounded below by `CAL_dpm_torque_min_allowed`. `torque_limit_dpm_throttle` is deliberately higher by a calibrated fraction of the available external-request margin. Thus the fast path can remove torque quickly with spark while the slower air path follows less aggressively.

`torque_limit_request_arbitration()` accepts the pair only while DPM is active and control bits `0x0001` and `0x0002` are both set. DPM competes with ABS/ESP CAN 0xB7 requests, transmission requests, cruise control and protection limits in the common torque arbitration. The neutral/no-limit sentinel throughout this subsystem is 911 Nm (`0x38f`).

### Fast channel to spark and cylinder cut (resolved in pass 2)

The complete high-confidence path is:

```text
torque_limit_dpm_spark
  -> torque_limit_arbitrated_fast
  -> torque_limit_external_request
  -> torque_limit_external_net (friction removed)
  -> torque_limit_external_factor (requested / estimated delivered torque)
  -> torque_cut_level + torque_allowed_factor
```

`torque_model()` treats one hard-cut cylinder as approximately `42/255` of six-cylinder torque. It chooses a whole-cylinder cut count (`torque_cut_level`) nearest the demanded reduction, then recalculates `torque_allowed_factor` for the residual torque that the remaining firing cylinders must produce.

`engine_speed_and_cyl_cut_update_1000hz()` turns `torque_cut_level` into explicit, evenly distributed cylinder patterns around a rotating anchor:

- one cut: anchor;
- two cuts: anchor and `+3`;
- three cuts: anchor, `+2`, `+4`;
- four cuts: anchor, `+1`, `+3`, `+4`;
- five cuts: all except the remaining cylinder;
- six cuts: all cylinders disabled.

The resulting per-cylinder array is still exported under the misleading name `o2_sensor_ready_per_cyl`; its primary behavior is a combustion gate (`0` cut, `0xff` enabled), while O2 and misfire code also consult it to suppress invalid monitoring. `update_per_cylinder_cut_event_state()` consumes the gates at crank-event boundaries. The final low-level alias from these gates into injector eTPU enable data is not cleanly represented in this C export, so the precise hardware write remains an open decompiler/data-reference issue rather than a control-strategy question.

For the residual fast reduction, `torque_allowed_factor` is transformed through the modeled spark-efficiency slope and `CAL_torque_ign_retard_base`. This produces `ign_comp_torque_reduction`, which is applied to all six per-cylinder ignition targets, bounded by `ign_adv_min`, converted to `ign_adv_scheduled_angle[]`, and passed to `ign_schedule_cylinder_event()` / `ign_update_timing()` for the eTPU ignition channels. This resolves the fast actuator boundary as discrete combustion cuts plus spark-angle retard, not throttle alone.

### Slow channel to electronic throttle (resolved in pass 2)

The complete slow path is:

```text
torque_limit_dpm_throttle
  -> torque_limit_arbitrated_slow
  -> torque_external_request_tps_based
  -> torque_driver_net_clamped
  -> torque_limit_engine_protection / torque_external_request_final
  -> CAL_torque_torque_to_load
  -> load_target_with_torque_limit
  -> CAL_load_to_tps_mapping + LEA_torque_torque_to_tps_scaling
  -> torque_limit_tps_current
  -> torque_model_200hz() rate filter
  -> torque_limit_tps_target
  -> throttle_and_torque_control() clamp
  -> tps_smooth
  -> obd_ii_commanded_throttle_actuator
  -> electronic-throttle position controller
```

The slow request is first prevented from being more restrictive than the fast request after friction conversion. It then participates in engine-protection compensation, is converted from torque to cylinder charge/load, and from load to learned throttle position. `torque_model_200hz()` filters its movement, with immediate behavior selected when the active source is DPM (`torque_limit_source_flags == 0x20`). `throttle_and_torque_control()` clamps the driver/idle request to that target and bypasses normal gentle smoothing during an active external torque limit. The resulting `obd_ii_commanded_throttle_actuator` is the exact application boundary into the ETB feedback/controller path.

## Driver modes and adjustable DPM level

The vehicle-mode enum is:

| Value | Mode |
|---:|---|
| 0 | Tour |
| 1 | Sport |
| 2 | TC Off |
| 3 | Race |
| 4 | Launch |
| 5 | Launch sub-state |
| 6 | DPM Active |

`set_driver_input_and_vehicle_mode_100hz()` handles button timing. From Race, the relevant long Race-button event selects Launch when launch preconditions are met; otherwise it selects `VM_DPM_ACTIVE`. DPM Active sets control bits `0x10` (system selected) and `0x40` (level buttons permitted). Leaving it clears these bits.

`dpm_mode_button_handler()` recognizes mutually exclusive increase/decrease inputs and changes `dpm_mode_index` after a bounded press duration. Ignition-off initialization selects level 1. The stored range is 1 through 6.

The cluster is informed through CAN 0x403 byte 4:

- 0: DPM not selected/available;
- 1-5: corresponding adjustable level;
- 7: internal level 6;
- 8: DPM selected but inhibited/faulted.

Pass 2 resolves internal index 6 as the deliberate ECU-intervention-off position. Every xref is consistent:

- the button handler can increment from 5 to 6 and clamps any larger value back to 6;
- decrementing from 6 returns to 5;
- the target calculator accepts only indices `< 6` and explicitly clears target-valid bit `0x0008` at 6;
- the intervention gate requires target-valid, so it resets both DPM torque limits to 911 Nm;
- vehicle mode remains `VM_DPM_ACTIVE`, retaining the DPM UI/button path;
- CAN 0x403 maps internal values above 5 to display code 7.

Thus level 6/cluster code 7 means DPM selected with ECU traction intervention off. This is distinct from `VM_TC_OFF`, which is a separate whole-vehicle ABS/ESP mode and has different A8 plausibility expectations.

## DPM control flags

The following meanings are supported by set/test sites. Names remain conceptual because the export retains a raw bitfield:

| Mask | Observed meaning | Confidence |
|---:|---|---|
| `0x0001` | controller active/current control tick | high |
| `0x0002` | intervention episode enabled/latched | high |
| `0x0004` | large left/right delta; direct/cornering target mode | medium-high |
| `0x0008` | slip target valid | high |
| `0x0010` | DPM selected by vehicle-mode logic | high |
| `0x0020` | DPM inhibited/disabled | high |
| `0x0040` | adjustable-level button handling permitted | high |
| `0x0080` | increase button state | high |
| `0x0100` | decrease button state | high |

The existing name "DIRECT" for bit `0x0004` is less certain than the behavior: its only decision input is maximum same-axle left/right speed difference, with hysteresis, and its immediate mathematical effect is omission of the target offset.

## Legacy slip-indicator path

`init_slip_detection_limits()` installs different gear-ratio and threshold pointer sets for IPS, manual long-ratio, and manual close-ratio configurations. `slip_detection_and_tc_indicator()` then:

- estimates expected engine RPM for each gear from vehicle speed;
- compares those estimates with per-gear thresholds and a power-based RPM threshold;
- applies accelerator, brake, clutch, steering-angle, steering-rate, lateral-acceleration and ABS/ESP inhibits;
- maintains per-gear hysteresis timers;
- publishes a recommended gear and cluster indication flags.

Pass 2 exhausted all references to the legacy path's outputs. `traction_flags_unknown` is read outside this routine only by cluster-output logic: bit `0x04` drives the main slip indicator, and bit `0x40` adds the higher-priority/flashing indication when `CAL_slip_detect_mode > 2`. `traction_control_gear_recommended__`, `tc_gear_tracker`, `traction_slip_detected_gear`, `traction_power_limit_gear`, and `slip_expected_engine_rpm_per_gear[]` have no consumers outside this routine. None reaches torque arbitration, throttle, ignition, injection, CAN torque request, or DPM state.

The legacy path is therefore resolved, with high confidence for this firmware export, as detection/cluster indication only. Its internally computed recommended gear appears to be dead or development-era state rather than a transmitted request.

## Calibration groups

The principal DPM calibrations are:

- slip target: `CAL_dpm_slip_target_base*`, `CAL_dpm_slip_target_from_pedal*`, `CAL_dpm_slip_target_offset`;
- operating window: `CAL_dpm_min_vehicle_speed`, `CAL_dpm_max_vehicle_speed`, `CAL_dpm_min_engine_rpm`;
- error behavior: `CAL_dpm_intervention_threshold`, `CAL_dpm_slip_filter_coeff*`;
- proportional torque cut: `CAL_dpm_torque_cut_factor*`, `CAL_dpm_torque_min_allowed`, `CAL_dpm_torque_margin_factor`;
- integral torque cut: `CAL_dpm_integral_gain`, `CAL_dpm_integral_limit`, `CAL_dpm_integral_update_period`;
- cornering/direct hysteresis: `CAL_dpm_lr_diff_cornering_threshold`, `CAL_dpm_direct_mode_on_delay`, `CAL_dpm_direct_mode_off_delay`;
- wheel scaling: `CAL_wheel_speed_multiplier_front`, `CAL_wheel_speed_multiplier_rear`.

The separate legacy detector uses the broader `CAL_slip_*` family: gear-speed ratios, per-gear thresholds, power-based thresholds, steering/cornering inhibits, cold-start relaxation and intervention timers.

## Open questions and suggested next checks

Resolved in pass 2:

- internal DPM index 6 / cluster code 7 is ECU intervention off while DPM UI mode remains selected;
- fast DPM torque reaches whole-cylinder cut selection and per-cylinder spark retard;
- slow DPM torque reaches the final electronic-throttle command;
- the legacy slip detector is cluster indication only in this export.

Remaining open questions:

1. Recover the exact electrical or CAN source of `dpm_button_increase` and `dpm_button_decrease`; this export contains consumers and diagnostic PIDs but no ordinary C assignment, suggesting an alias, direct I/O update, or missed data reference.
2. Decode all 0xA8 status fields and give semantic names to `abs_a8_flag2`, `DAT_40002555`, and `DAT_40002556` using the ABS firmware and synchronized logs.
3. Verify whether choosing the maximum wheel on each axle is purely a cornering robustness strategy or tied to a specific wheel-speed convention.
4. Recover the low-level alias/data reference connecting the per-cylinder combustion-gate array to final injector eTPU enable writes; the ignition-angle endpoint is explicit, but this one hardware boundary is obscured in the export.

Stock calibration values are now quantified: minimum DPM RPM `1800`, operating speed range
`5–255 km/h`, left/right wheel-speed threshold `0.45 km/h`, direct-mode on/off delays `0.2/0.5 s`,
integral update period `20 s`, minimum allowed torque `30 Nm`, slip target offset `2%`, intervention
threshold `2%`, and final adjustable base targets `3/6/9/12%`. The tuned CPT changes none of the
DPM definitions, so its powertrain changes must not be attributed to altered traction targets.

## Confidence summary

- DPM wheel-slip formula, gating, target construction and torque-limit production: high.
- Fast versus slow torque-channel role and actuator boundaries: high. The per-cylinder cut strategy and final throttle clamp are explicit; only the cut-gate-to-injector hardware alias is obscured.
- Adjustable level range, CAN 0x403 encoding, and intervention-off meaning of level 6/7: high from exhaustive xrefs.
- Legacy detector being indication-only: high within this firmware export after exhaustive output-xref review.
- Full semantics of ABS 0xA8 status bits and DPM bit `0x0004`: medium.
