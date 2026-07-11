# GT430 torque, transmission and cruise analysis

## Scope and main conclusions

This report extends the GT430 traction and ignition work into the common torque model and all non-DPM request sources: ABS/ESP CAN requests, retained IPS transmission coordination, cruise control, manual gear determination, driver modes and launch state.

The calibration target is the six-speed manual GT430. The application is nevertheless a configurable Evora-family binary and retains a substantial IPS implementation. Transmission coding is tested at every important boundary. Under manual coding, gear is inferred locally, CAN `0xC7` requests are cleared, IPS shift requests are forced to the 911 Nm no-limit sentinel, and the rev-match state machine is bypassed. The retained IPS code is therefore useful for family comparison but is not the live GT430 manual path.

## End-to-end torque architecture

```text
driver pedal / idle / cruise virtual pedal
                |
                v
throttle request -> Alpha-N load estimate -> Alpha-N torque estimate
                                             |
measured MAF/load -> load-to-torque ----------+-> delivered combustion/net torque
actual ignition -> spark-efficiency model ----+
failed/cut cylinders -------------------------+

request sources
  ABS/TC CAN 0xB7 fast/slow
  ESP CAN 0xB7 severe cut
  IPS TCU CAN 0xC7                 [IPS coding only]
  ECU IPS rev-match/shift pair     [IPS coding only]
  DPM fast/slow                    [manual GT430 feature]
  auxiliary cruise/creep ceiling
                |
                v
torque_limit_request_arbitration()
  validated fast + slow pair
  clutch and low-RPM plausibility clamps
  source tag
                |
                v
torque_model()
  fast -> torque fraction -> cylinder cuts + spark retard
  slow -> torque -> load -> learned throttle ceiling
```

The neutral no-limit value is 911 Nm (`0x38f`). Signed CAN torque fields are encoded as quarter-Nm values biased by +400 Nm.

## Torque components

### Alpha-N predicted torque

The requested throttle plus idle air is limited by the previous torque-derived throttle target and converted through:

1. `CAL_load_alphaN_base` — RPM/throttle to predicted charge;
2. `LEA_load_alphaN_learned_trim` — learned RPM/throttle correction;
3. manifold- or ambient-density correction;
4. `CAL_torque_load_to_torque` — charge to indicated torque;
5. `CAL_torque_engine_friction_speed_component` — base friction.

This produces `torque_estimated_alphaN` and `torque_alphaN_net`. It represents the torque the current throttle path can make and is used to reject external requests that are not actually restrictive.

### Measured delivered torque

Measured `load_mass_per_stroke_raw` is independently passed through `CAL_torque_load_to_torque` to form `torque_estimated_actual_load`. The delivered-torque model then applies:

- the fraction of cylinders currently firing;
- current spark efficiency derived from retard from modeled MBT;
- speed/load friction;
- coolant/load friction;
- RPM-scaled A/C accessory load.

The result appears as `obd_ii_engine_torque` and `torque_net_engine_combustion`. Failed and intentionally cut cylinders are excluded, so torque arbitration compares requests against estimated delivered torque rather than an ideal six-cylinder value.

### Spark efficiency and friction

`CAL_torque_spark_efficiency` maps retard from `ign_mbt_modeled` to efficiency. `CAL_torque_spark_efficiency_slope` modifies the interpolation slope by RPM/load. This model is used in both directions:

- actual spark retard reduces the delivered-torque estimate;
- a fast requested torque fraction is inverted through `CAL_torque_ign_retard_base` to obtain required retard after whole-cylinder cuts are selected.

`get_engine_friction_torque()` sums speed/load, coolant/load and A/C terms. The code stores these as signed values in torque-typed 16-bit fields; repeated casts to `short` are intentional.

### ECU torque broadcast

CAN `0x102` broadcasts net and combustion torque. Net torque is a 12-bit value; combustion torque is encoded relative to the same +400 Nm convention used by incoming requests. Sensor, communication or engine faults substitute invalid sentinels. ABS/ESP and the IPS TCU therefore receive the ECU's modeled torque basis used for coordination.

## Manual gear determination

With transmission coding value 0, `gear_determination()` computes:

```text
rev_per_km = engine_rpm * 1000 / vehicle_speed
```

Six pairs in `gear_lookup[12]` bound first through sixth gear. Outside every window, or at zero speed, the result is `NO_GEAR`. A change sets `new_gear_detected_flags` and feeds pedal mapping, ignition low-gear limits, rev-limit trim, cruise gains and DPM/legacy-slip logic.

`init_gear_cal()` chooses the ratio windows from the standard/long-ratio set when coding bit 16 is clear and the close-ratio set when it is set. The GT430 manual configuration uses the close-ratio branch according to the existing coding analysis.

With IPS coding value 1, local ratio inference is bypassed and `get_determination_auto()` translates the TCU's `gear_index_auto`, including its neutral/transition encodings.

## Torque CAN requests

### ABS/ESP message 0xB7

`flexcan_a_rx_B7()` accepts four- or seven-byte forms with XOR checksum and rolling counter:

- field 1: fast TC/cruise-style torque request;
- field 2: fast ABS/ESP request;
- optional field 3: slow TC request for throttle/airflow.

The active selector bits distinguish the TC/cruise-style and ABS/ESP interpretations. Normal TC requests are accepted only when they are below `torque_alphaN_net` and may be held for `CAL_torque_ext_torque_limit_hold_count`. Without the seven-byte slow field, the slow channel normally follows the fast request.

The ABS/ESP path is intentionally much narrower: for the supported traction-control coding it accepts only a very low request (under approximately 40 Nm), effectively a severe stability intervention, and assigns the same value to both channels.

DPM mode suppresses external TC-style `0xB7` validation so the ECU-side GT430 controller owns traction torque. ABS/ESP severe intervention remains a distinct arbitration source where valid.

### IPS TCU message 0xC7

`flexcan_a_rx_C7()` decodes:

- requested engine speed;
- a second 16-bit shift/status value;
- TCU shift flags;
- a signed 12-bit quarter-Nm torque ceiling;
- an active-request bit.

The entire payload is used only when transmission coding equals IPS. Manual coding explicitly clears the active flag and validity bits and restores `torque_limit_tcu_0xc7_raw = 911`.

For IPS, the request is validated against current Alpha-N/combustion torque and held briefly across crossings. It becomes `torque_limit_tcu_0xc7_validated` only while CAN validity, the active bit and timeout state are all acceptable.

## Retained IPS shift and rev-match controller

`ips_shift_state_mgmt_1000hz()` is a second IPS torque source in addition to raw CAN `0xC7`. It tracks TCU shift flags through idle, request, speed-match, torque-recovery and cleanup states.

During speed matching it:

- clamps the TCU engine-speed request above idle;
- runs `ips_engine_speed_matching_pid_control()` on requested versus actual RPM;
- produces an ECU-calculated shift torque;
- transitions to a filtered recovery torque as engine speed and actual torque converge.

`ips_torque_reduction_request()` turns this into a fast/slow pair:

- fast = raw requested torque;
- slow = calibrated percentage of the fast request, bounded by `CAL_ips_torque_reduction_slow_floor_nm`.

The pair is tagged separately from the TCU `0xC7` request. This permits immediate ignition intervention while allowing a less aggressive throttle channel during a clutch-to-clutch shift or rev match.

For manual coding the whole state manager's active branch is skipped and both values are set to 911 Nm. Paddle input, automatic gear translation, TCU timeouts, IPS cooling and shift-speed matching are retained family code, not evidence of an automatic GT430 calibration.

## Common torque arbitration

`torque_limit_request_arbitration()` first validates each source, then selects a fast/slow pair. The major source tags are:

| Value | Source |
|---:|---|
| `0x00` | none |
| `0x01` | TC-style CAN 0xB7 |
| `0x02` | ABS/ESP CAN 0xB7 |
| `0x04` | validated TCU CAN 0xC7 |
| `0x08` | auxiliary cruise/IPS torque ceiling |
| `0x10` | ECU IPS shift/rev-match request |
| `0x20` | DPM |

Where ABS/ESP and TCU requests coexist, the fast channel generally selects the more restrictive valid ceiling. Slow-channel selection preserves the requested fast/slow relationship and never allows a nonsensical slow value below the final fast intervention.

The order of practical precedence is conditional rather than a simple fixed list:

- DPM is selected directly when active and no accepted ABS/ESP request supersedes it;
- accepted `0xB7` and IPS requests are compared by validity and magnitude;
- ECU-generated IPS shift torque is preferred over an otherwise idle TCU path;
- the auxiliary cruise ceiling can lower the result when it is restrictive and no shift request blocks it.

Before output, manual-clutch state can suppress external torque reduction when the engine is effectively free. At low RPM both fast and slow values are floored by `CAL_torque_limit_low_speed_min_torque` to prevent a stall-producing request. The selected values become:

- `torque_limit_external_request` — fast spark/cut path;
- `torque_external_request_tps_based` — slow load/throttle path.

## Cruise control

### Driver and safety state

`cruise2_200hz()` decodes the resistor-ladder switch positions (cancel, set, accelerate, coast, on), manages set/resume and target-speed changes, and cancels for brake, clutch, implausible gear/RPM ratio, active faults, limiter state and pedal override.

Manual and IPS calibrations use separate gain families. Manual further selects long-ratio versus close-ratio proportional, integral and derivative gains from coding bit 16.

### Speed PID to throttle

`cruise_control()` computes speed error and transmission/gear-specific PID terms. The 200 Hz companion maintains integrator, derivative state and rate limits. Their sum represents an airflow request, which is converted:

```text
speed PID -> airflow -> load -> CAL_load_to_tps_mapping
          -> cruise_virtual_pps_request
          -> manual/IPS pedal map
          -> cruise_tps_commanded
```

When cruise is active, the normal pedal/throttle path uses this virtual request. Accelerator override is tracked with separate enter/exit thresholds.

The variable `torque_cruise_request` in common arbitration is not the primary road-speed PID output. Its assignments are confined to auxiliary brake/IPS/creep-style limiting and the 911 Nm sentinel/hysteresis path. Normal cruise speed control is fundamentally throttle/airflow based.

## Driver modes and launch

Tour, Sport and Race primarily alter pedal maps, throttle smoothing, ignition/VVT options, exhaust behavior and flag outputs. DPM Active adds the ECU traction torque source described in the traction report.

Launch states are retained in the shared state machine but are not available in a valid GT430 coding configuration:

- the coding validator requires `launch_mode_present == 0`;
- entry from Race requires that bit to be set, manual coding, clutch state and ABS state;
- therefore a normal valid GT430 configuration routes the same Race-button event to DPM Active, not Launch.

If forced through invalid/development coding, `VM_LAUNCH` and `VM_LAUNCH_SUB1` mainly set driver/cluster flags and wait for ABS/clutch phase feedback. No separate launch torque request enters the common arbitration, and the only additional consumer found is a drive-cycle-assist eligibility gate. These are dormant family/development states rather than an active GT430 launch-control strategy.

## Manual GT430 versus retained IPS code

| Area | Manual GT430 live path | Retained IPS path |
|---|---|---|
| Gear | RPM/vehicle-speed ratio windows | TCU gear translation |
| Torque CAN `0xC7` | explicitly invalidated | decoded and held |
| Shift torque | forced to 911 Nm | ECU fast/slow shift pair |
| Rev matching | absent from shift manager | requested-RPM PID |
| Paddle input | not used for shifting | decoded for TCU/DCA logic |
| Cruise gains | close-ratio manual tables | IPS per-gear tables |
| Ignition/fuel maps | manual branches | IPS alternatives retained |
| Cooling | no IPS shift flag | shift can request cooling |

This distinction matters when interpreting symbols: presence of `CAL_*_ips`, `ips_shift_state`, TCU DTCs and CAN `0xC7` does not imply that those paths execute on the manual GT430.

## Principal calibration groups

- torque conversion: `CAL_torque_load_to_torque`, `CAL_torque_torque_to_load`, `CAL_load_to_tps_mapping`;
- friction: speed/load, coolant/load and A/C load tables;
- spark efficiency: `CAL_torque_spark_efficiency*`, `CAL_torque_ign_retard_base`;
- external request shaping: overshoot margin, hold time, low-RPM torque floor and throttle PI/rate limits;
- manual gear: standard and close-ratio window tables;
- IPS: `CAL_ips_torque_reduction_slow_scale_pct`, slow floor and speed-match controller constants;
- cruise: manual long/close-ratio and IPS PID gains, speed deadband, rate limits and override thresholds.

## Conservative disassembly improvements

- Added manual-versus-IPS comments at gear determination, CAN `0xC7` and the IPS shift manager.
- Renamed `ips_engine_speed_matching_pid_ctrl___()` to `ips_engine_speed_matching_pid_control()`.
- Corrected `CAL_ips_torque_reduction_slow_floor_nm.` and `torque_limit_tps_accumlator` names.
- Typed the torque throttle accumulator, cruise throttle request, actual-load torque, accessory torque, spark slope and efficiency factor.
- Improved CSV descriptions for validated `0xB7` and `0xC7` requests and the IPS shift floor.

## Confidence and open questions

High confidence:

- Alpha-N and measured-load torque components;
- manual gear inference and IPS coding gates;
- `0xB7` and `0xC7` request decoding;
- IPS shift fast/slow request construction;
- source-tag meanings and fast/slow output boundary;
- normal cruise PID-to-throttle path;
- launch being unavailable under valid GT430 coding.

Open/medium confidence:

1. Give semantic names to the IPS shift-state bytes and controller structure fields.
2. Fully decode `abs_esp_can_torque_request_flags` and `tcu_can_status_flags`; their validity/accepted-source subsets are known, but not every bit.
3. Rename the auxiliary `torque_cruise_request` only after its IPS/creep behavior is compared with TCU logs; the current historical name is misleading for normal cruise.
4. Quantify the close-ratio gear windows and cruise gains from a calibration dump.
5. Confirm whether the shared binary was ever deployed with IPS coding under the same calibration identifier, or merely retains link-time family code.

## Marginal value of this pass

This pass closes the system-level gap between prior traction/ignition reports:

- reconstructs both sides of the torque estimator;
- maps every major non-DPM request into the common fast/slow arbitration;
- proves manual coding neutralizes both TCU and ECU-generated IPS torque paths;
- separates normal cruise throttle control from the misleading auxiliary cruise torque variable;
- establishes that valid GT430 coding cannot enter retained launch states;
- improves the disassembly and symbol CSV with targeted, high-confidence torque/IPS names and types.
