# GT430 Variant Differences

## Scope

This audit compares the GT430 `C132E0278` C export against:

- Evora GT `E132E0288` (2020-2021 US-market reference), and
- Evora 400 `C132E0271` (2017 Federal-market reference).

The goal is to distinguish genuinely GT430-specific behavior from common T6e code retained in all variants. Conclusions are based on control-flow presence, scheduler calls, coding gates, named calibration families, and directly comparable function bodies. They are not a byte-for-byte binary diff.

## Executive conclusion

The GT430 is not a substantially different ECU architecture. It retains the same MPC5534 scheduler, ADC/CAN hardware model, engine-control pipeline, manual/IPS coding framework, emissions monitor families, and most sensor/actuator control as the later GT and earlier Evora 400.

The one clear, substantial GT430-specific feature is the ECU-resident adjustable Driver Performance Mode (DPM):

- a separate wheel-slip calculation based on front-versus-rear wheel speeds;
- driver-selectable slip levels;
- speed/pedal-dependent target slip;
- proportional plus accumulated integral torque reduction;
- separate fast/spark and slow/throttle torque limits;
- explicit arbitration into the common torque-limit path;
- cornering/direct-mode hysteresis from left/right wheel-speed split;
- cluster reporting of the selected level; and
- inhibition on ABS/ESP, wheel-speed validity, or CAN-health faults.

The standard slip-detection/gear-advisory logic is not GT430-specific. Equivalent code is visible in both comparison exports. GT430 keeps that common logic and adds DPM alongside it.

## Comparison quality

| Export | Approximate C size | Recovered function naming | Comparison quality |
|---|---:|---|---|
| GT430 `C132E0278` | 59,000 lines | Heavily curated; 580 non-`FUN_` function names detected | Best semantic reference |
| GT `E132E0288` | 61,000 lines | Similarly curated; 596 non-`FUN_` names detected | Good structural comparison |
| Evora 400 `C132E0271` | 56,000 lines | Only about 101 non-`FUN_` names; roughly 514 functions remain address labels | Useful for control-flow confirmation, poor for name-set comparison |

GT430 and GT share 506 exact non-`FUN_` function names. That is roughly 87% of GT430's named functions before accounting for analyst renames such as `adc_sample` versus `adc_decode_dma_samples`. This supports a large common codebase, but exact-name overlap is not proof of binary identity.

The Evora 400's low name overlap is primarily an export/analysis limitation. Direct inspection shows many of the same functions and subsystem sequences under `FUN_` labels.

## Shared scheduler and runtime architecture

All three exports show the same broad execution model:

- a cooperative background engine-control loop;
- a 2 kHz timer interrupt and rate-divider structure;
- foreground sensor conversion, load, cooling, idle, fuel, ignition, VVT, knock, torque, traction/slip, cruise, rev-limit, A/C, and fuel-pump work;
- periodic 200 Hz, 100 Hz, 50 Hz, 10 Hz, and slower diagnostic/control tasks; and
- common eTPU, eQADC/eDMA, eMIOS, FlexCAN, and persistent-learning infrastructure.

GT430 does not introduce a new interrupt domain for DPM. It inserts:

- `dpm_slip_calculator()` into the background loop for manual-transmission coding; and
- `dpm_system_state_manager_200hz()` into the 200 Hz task for the same coding.

This is an important boundary: DPM is an added control layer on the shared runtime, not a separate ECU architecture.

## Genuine GT430 DPM delta

### Presence evidence

The GT430 export contains a coherent family of 23 `CAL_dpm_*` calibrations and more than 30 DPM runtime variables. Neither comparison export contains that family or the two scheduler calls.

The unique calibration set includes:

- mode-index-to-base-slip target;
- pedal/speed slip-target compensation;
- slip-error filtering;
- vehicle-speed and engine-speed enable limits;
- intervention threshold;
- speed/slip torque-cut table;
- torque floor and torque-margin split;
- integral gain, limit, and update period; and
- cornering/direct-mode on/off delays and wheel-speed-difference threshold.

This is too internally consistent to be explained by naming differences alone.

### Slip and target calculation

The GT430 DPM path uses the maximum front wheel speed as the reference axle speed and the maximum rear wheel speed as the driven axle speed. Positive rear-over-front speed produces slip in 1/8-percent units. It also computes front and rear left/right deltas for cornering discrimination.

Target slip comes from two sources:

- a pedal/speed table when adjustable level control is unavailable; or
- a selected DPM level plus pedal/speed compensation when the switch path is active.

Mode index 6 deliberately clears target validity. Vehicle mode and cluster indication remain active, but this controller cannot command a torque cut. That is an ECU-intervention-off position rather than loss of communication.

### Torque intervention

When filtered slip error exceeds the calibrated threshold, the firmware captures current combustion torque and applies:

1. a speed/slip-dependent proportional torque-cut factor, and
2. a slower, signed, saturating slip-error integral.

The combined factor produces a fast torque ceiling associated with spark authority. A calibrated fraction of the common torque margin produces a less restrictive slow ceiling for throttle/airflow authority. These DPM limits enter the same arbitration used for ABS/ESP, TCU/IPS, shift, and cruise torque requests.

This split is unique to GT430 DPM, while the downstream torque-model and actuator paths are shared.

### Safety supervision

DPM is inhibited when any of the following is observed:

- ABS/ESP inhibit state;
- invalid LF, RF, LR, or RR wheel speed;
- expired ABS CAN receive-health state; or
- failed ABS plausibility-health state.

The 200 Hz supervisor resets the level to 1 with ignition inactive, handles level buttons when enabled, applies cornering/direct-mode hysteresis, and updates the integral term. The background calculation clears its limits to the common `911 Nm` no-limit sentinel when DPM is inactive or invalid.

### Driver and cluster integration

GT430 has `VM_DPM_ACTIVE`, DPM enable/button state, and a DPM mode index. CAN message `0x403` gains a fourth argument and packs a five-bit level/status value in data byte 4. The GT and Evora 400 transmit versions only carry the three fuel-range/economy arguments.

This message-format extension is a concrete GT430-specific external interface.

## Standard traction/slip logic is shared

The function named `slip_detection_and_tc_indicator()` in GT430 and GT corresponds closely to `traction_main()` in the less-curated Evora 400 export. Shared behavior includes:

- manual/IPS/gear-ratio selection;
- expected engine speed per gear from vehicle speed;
- power-based RPM thresholds;
- steering/lateral-acceleration cornering inhibition;
- per-gear intervention timers;
- slip and power-limit gear detection; and
- cluster/driver indication behavior.

GT430 calls this standard function even after running its DPM slip calculation. Therefore references to `CAL_slip_*`, traction gear recommendation, or common slip flags should not by themselves be labelled GT430-specific.

## Manual and IPS coding

All three binaries retain manual and IPS code paths. Common coding tests use `COD[0].bits13-15` as the transmission selector and choose distinct:

- ignition/load/rev-limit calibrations;
- gear determination;
- slip gear ratios and thresholds;
- TCU CAN handling and shift torque requests;
- cruise and idle behavior;
- A/C conditions; and
- transmission-fluid pump/temperature paths.

Consequently, the presence of IPS functions in the GT430 binary does not mean the audited car was IPS, and it is not dead-code evidence of another firmware image. It is shared variant-capable production code.

The GT430-specific DPM calls are explicitly gated to transmission coding value 0, the manual path. IPS coding continues through the common ABS/ESP and TCU torque-request arbitration without invoking the adjustable DPM controller.

This is the highest-confidence transmission distinction:

```text
manual coding -> shared control + standard slip logic + GT430 DPM
IPS coding    -> shared control + standard slip logic + TCU/shift torque control
```

## Sensors and actuators

### Shared analog hardware

GT430 and GT reference the same 34 explicit `adc_dma_dest[]` indices. They contain the same recognizable channels for:

- coolant, IAT, TMAP/charge-cooler temperature;
- MAP, MAF, barometer, fuel pressure, oil pressure, and fuel level;
- dual TPS and accelerator-pedal support;
- clutch potentiometer and paddle input;
- oxygen sensors and heater currents;
- ECU/ignition voltage; and
- continuous and crank-window knock acquisition.

No GT430-only analog sensor channel was found. The Evora 400 export does not preserve the `adc_dma_dest` label, so the same mechanical index comparison cannot be made there, although its conversion flow and named sensor set are strongly similar.

### Shared coded actuators

The three exports retain coding-dependent paths for:

- main cooling fans and auxiliary engine-bay fan;
- charge-air-cooler pump and diagnostics;
- fuel-pump PWM/closed-loop pressure control;
- transmission-fluid pump and temperature;
- exhaust bypass/flap;
- A/C compressor and evaporator sensor; and
- recirculation-valve and other variant outputs.

GT430 and GT implementations are especially close, including CAC diagnostics, fuel-pump state machine, and transmission-cooler functions. Most apparent symbol-name differences in these areas are analyst wording differences, not demonstrated hardware deltas.

The DPM controller adds no dedicated engine actuator. It consumes the existing ABS wheel-speed/CAN data and feeds the shared torque-to-spark/throttle authority paths.

## Market and emissions behavior

The emissions architecture is largely shared. All three exports contain catalyst, oxygen-sensor, EVAP, misfire, fuel-system, circuit, CAN, freeze-frame, and permanent-DTC machinery. GT430's function previously named `obd_ii_mode10_processing()` is byte-for-byte semantic Mode `$0A`: it returns service `$4A` and reports permanent DTCs, matching the GT and the unnamed Evora 400 equivalent. It has been renamed accordingly.

There are real diagnostic implementation differences, but they should not automatically be attributed to UK versus US regulation:

- GT430 clears groups of learned DTC state with `& 0xf7` in lifecycle code where GT and Evora 400 use `& 0xdb`.
- Catalyst monitor pending/confirmed-state handling differs between GT430 and the two Federal exports.
- GT430 and Evora 400 use rev-limit critical-fault mask `0x0dcefbf7`; GT uses `0x0dceea77` plus a separate four-bank VVT inhibit test. The GT430/400 mask contains additional `0x1180` bits.

These differences establish distinct diagnostic/control revisions. They do not establish why those revisions differ. Model year, software branch, diagnostic-state encoding, market certification, and calibration enable levels are confounded in the available exports.

Crucially, the C exports declare calibration objects but do not include their initialized flash contents. Therefore they cannot show whether a DTC enable byte, monitor threshold, fuel/ignition table, octane target, or market switch has a different calibrated value. Claims such as “GT430 disables US monitor X” or “GT430 uses 98 RON timing” require raw calibration bytes, not merely the presence of a common code path.

## Shared retained code versus active feature

The following should be treated as retained shared capability unless calibration/coding proves activation:

| Feature observed in GT430 code | Cross-export conclusion |
|---|---|
| IPS shift matching and TCU torque requests | Shared in all variants; coding-dependent |
| Standard slip/gear indication | Shared in all variants |
| Race, launch, sport, cruise, HVAC options | Shared coding framework |
| CAC pump and diagnostics | Shared supercharged-platform control |
| Transmission-fluid pump/sensor | Shared, coding-dependent |
| Fuel-pressure closed-loop pump control | Shared in GT430/GT; older export has related fuel-pump control under fewer recovered names |
| Permanent DTC Mode `$0A` | Shared; GT430 name was misleading |
| Mode `$2F` actuator tests | Shared diagnostic framework |
| Adjustable DPM slip controller | Genuinely GT430-specific in these three exports |
| DPM level/status in CAN `0x403` byte 4 | Genuinely GT430-specific interface extension |

## High-confidence annotation changes from this audit

- Renamed `obd_ii_mode10_processing` to `obd_ii_mode0A_processing` because the request service is decimal 10 and the response is `$4A` permanent-DTC data.
- Typed and documented `dpm_control_flags` as a 16-bit DPM supervisory bitmap.
- Typed `dpm_wheel_speed_invalid_flags` as an 8-bit bitmap.
- Typed `dpm_slip_integral_accumulator` as a signed 16-bit saturating integral.
- Typed and documented decoded `traction_control_level` and `dpm_switch_installed` coding fields.

No broad renaming was performed from name-set differences alone.

## Limits and next-step value

Further cross-export work is now materially limited by missing inputs:

1. **No raw GT430, GT, or Evora 400 firmware binaries are present in these variant folders.** Without them, calibration bytes and true binary identity cannot be compared.
2. **Only GT430 has a symbol CSV.** The GT and especially Evora 400 exports lack equivalent address/name maps.
3. **No cross-build function matcher is present.** Function movement and analyst renaming make text/name diffs unreliable.
4. **The C export omits initialized global values.** It exposes table shapes and code consumers, not the actual tuned maps or market enable bytes.
5. **The Evora 400 export is lightly annotated.** More than 500 functions remain `FUN_<address>`, making apparent absence weak evidence unless scheduler/control flow is inspected directly.

The marginal value of more manual C-text comparison is therefore **low to moderate**. The main GT430 delta has been isolated. High-value continuation would require:

- raw binaries or complete flash/calibration dumps;
- Ghidra Version Tracking, BinDiff, Diaphora, or a normalized function-hash matcher;
- exported function address/size/call-graph tables for all three builds; and
- calibration-region extraction with typed table/value comparison.

With those inputs, a follow-on pass could separate code revision, market calibration, and model-specific tuning. Without them, additional “GT430-only” claims would increasingly reflect annotation differences rather than firmware differences.
