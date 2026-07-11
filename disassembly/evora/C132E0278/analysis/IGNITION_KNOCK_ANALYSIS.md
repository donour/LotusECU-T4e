# GT430 ignition, knock, rev-limit and combustion-protection analysis

## Scope and principal findings

This report traces `C132E0278` from base ignition tables to the MPC5534 eTPU ignition channels, and separates four mechanisms that are easy to conflate:

1. normal base timing and environmental/operating compensation;
2. knock detection, learned retard and octane adaptation;
3. modeled torque reduction, including DPM's spark/cylinder-cut request;
4. independent rev-limit, misfire and fault protection.

The most important distinction is that there is no single generic "cylinder cut." DPM requests a modeled torque fraction that `torque_model()` decomposes into a rotating cylinder pattern plus residual spark retard. The hard rev limiter sets injection cut flags directly at the RPM threshold. Catalyst-damaging misfire sets persistent bank failure flags and removes all three cylinders on the affected bank. These paths share some final combustion-state accounting but have different initiators, hysteresis and recovery.

## Scheduling and top-level flow

```text
fast main loop
  knock_agc_configure()
  knock_detection_window_setup()
  knock DSP function selected by CAL_knock_mode
  engine_speed_and_cyl_cut_update_1000hz()
  injection()       -> hard rev-limit injection flags and injector events
  ignition()        -> base/compensated/per-cylinder timing and eTPU events
  knock()           -> correction gates, learned retard and octane retard
  torque_model()    -> modeled fast torque cut + residual spark retard
  revlimit()        -> active soft/hard RPM thresholds and airflow terms

200 Hz task
  ignition_retard_and_recovery_200hz()
  knock_ign_retard_decay_200hz()
  misfire_detect_per_cylinder_200hz()
  torque_model_200hz()
  revlimit_200hz()

main-loop diagnostic state update
  misfire_detection_update()

100 Hz task
  oil_pressure_100hz()
```

The ordering means `ignition()` applies torque/knock state computed on the preceding pass, while `knock()` and `torque_model()` update state for the next pass. This is a normal one-loop pipeline, not evidence that the values are unused.

## Base ignition to eTPU scheduling

### Base maps and reference angles

`ignition()` first calculates dwell from the 8x8 RPM/ECU-voltage `CAL_ign_dwell_time` table. It then selects a 20x20 base timing table by transmission coding:

- `CAL_ign_base_manual` for manual;
- `CAL_ign_base_ips` for IPS.

The byte representation is quarter-degree timing with a -10-degree offset; the code subtracts `0x28` to obtain the signed quarter-degree value. Two other 20x20 references are evaluated at the same RPM/load point:

- `CAL_ign_knock_safe` — conservative timing used to measure available knock-safe retard range;
- `CAL_ign_mbt_modeled` — modeled maximum-brake-torque timing used by the torque-efficiency model.

Manual low gears or neutral can apply the RPM-indexed `CAL_ign_limit_first_gear_manual`. `ign_adv_target1` is the lesser of base timing and this low-gear limit.

### Normal compensations

The base target is combined with operating-state-specific corrections:

- startup retard versus stopped coolant temperature and accumulated MAF;
- startup blend versus accumulated MAF and throttle;
- coolant compensation, with distinct manual/IPS and VVT-state tables;
- engine-air temperature compensation;
- manifold-temperature compensation scaled by RPM/load;
- TPS-rate transient compensation;
- idle-speed-error and high-RPM transient compensation;
- A/C compensation;
- roughness-detection compensation;
- diagnostic ignition trim.

The routine chooses explicit operating modes (`IGN_IDLE`, `IGN_IDLE_AC`, `IGN_CRUISE`, `IGN_CRUISE_AC`, `IGN_NORMAL`, startup-normal, fixed and cold-start). `ign_adv_min` comes from the normal or engine-off minimum timing table and clamps torque retard where applicable.

### Per-cylinder corrections and hardware boundary

After the common target is chosen, each cylinder receives:

- `CAL_ign_trim_per_cyl`;
- persistent `LEA_ign_knock_retard[cyl]`;
- current octane/knock retard `ign_retard_knock[cyl]`;
- residual torque-control retard `ign_comp_torque_reduction`;
- roughness correction where enabled.

The final quarter-degree values are stored in `obd_ii_ign_adv_per_cylinder[]`, bounded by `ign_adv_min` and the knock-retarded base path, then converted to tenths of a degree in `ign_adv_scheduled_angle[]`.

`ign_schedule_cylinder_event()` converts advance-before-TDC to a wrapped 720-degree crank angle, subtracts dwell angle, and calls either:

- `ign_update_timing()` for a firing event; or
- `ign_update_timing_no_fire()` for a suppressed event.

These write the angle and timing parameters to eTPU channels `0x12` through `0x17`. This is the exact ignition hardware boundary visible in the export.

`ignition_retard_and_recovery_200hz()` provides slew/recovery behavior when external torque control is inactive and decays per-cylinder torque-retard state after cut events.

## Knock acquisition and DSP

### Window generation

`knock_detection_window_setup()` looks up window angle and sample length from 16x16 RPM/load tables:

- `CAL_knock_sampling_window`;
- `CAL_knock_buffer_size`.

Buffer size is clamped to 64–128 samples. The common offset is added to six cylinder-specific TDC offsets and wrapped over 720 degrees. An eTPU knock-window channel (`0x1f`) schedules the next cylinder window.

### Analog gain and ADC acquisition

`knock_agc_configure()` selects one of four gain ranges from three RPM thresholds with hysteresis. Two GPIO bits choose the analog range, while `knock_agc_reference_level` takes `0xff`, `0x80`, `0x41` or `0x21` so the sampled amplitude can be normalized back to a common scale.

`knock_interrupt_adc_process()` alternates sensors by cylinder bank:

- physical cylinders 1/3/5 (zero-based even indices) use ADC DMA channel `0x34`;
- physical cylinders 2/4/6 use channel `0x35`.

It tracks per-bank minima/maxima, subtracts ADC midscale `0x200`, multiplies by `knock_sensitivity`, divides by the AGC range, and fills the signed `knock_level_scaled[128]` buffer. At window completion it advances the cylinder, schedules the next window and sets `knock_sensor_new_data_available`.

### Frequency modes

`CAL_knock_mode` selects:

| Value | Mode | Window behavior |
|---:|---|---|
| 0 | none | no DSP consumer |
| 1 | 64-sample Goertzel | two 64-sample positions are compared |
| 2 | dual-window 64 | sine/cosine energy for two windows |
| 3 | 128-point spectral/FFT | 128 samples, 64 power bins |
| 4 | three-overlapping-window Goertzel | multiple 32-sample windows plus end window |

`knock_configure_frequency_bins()` filters and sorts up to eleven configured frequency bins. Mode-specific DSP runs only when a completed buffer is available.

Only the mode-4 routine has an explicit call to `knock_detect_and_update_baseline()` in this export. Modes 1–3 populate spectral-energy arrays and clear the new-data flag, but no final detector handoff was found. This may indicate that mode 4 is the production configuration and the other algorithms are development alternatives, or that an alias/data reference was lost in decompilation. The actual `CAL_knock_mode` byte from the binary should be checked before treating modes 1–3 as production-capable.

## Knock decision, retard and learning

### Normalized detector

For mode 4, per-cylinder energy is normalized against a learned RPM/load/cylinder baseline:

```text
normalized_magnitude = total_spectral_energy * 10 / (filtered_baseline + 1)
```

The RPM/load grid is 8x8x6 and initialized to 2000 by `knock_baseline_grid_init()`. `CAL_knock_baseline_filter_alpha` filters both the local baseline and learned cell. A cell is updated only when the sample is not classified as knock, and is clamped by `CAL_knock_baseline_min_clamp`.

If normalized magnitude exceeds the RPM/load `CAL_knock_peak_threshold`, the excess—saturated at 255—becomes `knock_count_per_cyl[cyl]`, and a per-cylinder hold timer is loaded.

### Detection and learning gates

`knock()` constructs hysteretic gates for:

- minimum load (`CAL_knock_detection_load_threshold`);
- detection RPM band;
- learning load (`CAL_knock_learning_load_threshold`);
- coolant temperature;
- TPS-rate transient inhibit;
- sensor/load/RPM failure flags.

`knock_flags` is now typed as a byte state field. High-confidence meanings are:

| Mask | Meaning |
|---:|---|
| `0x01` | knock correction enabled |
| `0x02` | octane/learn update enabled |
| `0x04` | current/fallback knock retard permitted |
| `0x08` | OBD learning-duration state |
| `0x10` | load gate met |
| `0x20` | detection RPM band / baseline-learning gate |
| `0x40` | learning-load gate met |
| `0x80` | OBD high-RPM/load evaluation gate |

### Two layers of retard

There are two related per-cylinder retard layers:

1. `LEA_ign_knock_retard[]` receives event-based retard from `CAL_knock_count_to_retard`, capped by `CAL_knock_corr_limit`. A hit loads `CAL_knock_retard_hold_time`; after hold expiry, `knock_ign_retard_decay_200hz()` removes `CAL_knock_ign_retard_decay_rate` periodically.
2. `ign_retard_knock[]` is the longer-term octane-quality/fallback component. It blends the gap between base and knock-safe timing using per-cylinder `LEA_octane_scaler[]`, plus a short-term octane correction.

`octane_scaler_shortterm[]` rises with learned event retard and decays without it. `octane_scaler_learn_update()` then moves persistent `LEA_octane_scaler[]` up or down. Higher scaler values select more of the base-to-knock-safe timing gap as retard. On major sensor/state failures, the firmware applies the full base-to-knock-safe delta rather than trusting detection.

## Rev limiting

### Threshold selection

`revlimit()` builds Tour/Sport and manual/IPS soft/hard envelopes from coolant temperature and time. A cold-start envelope initially lowers them and decays toward the normal values. Per-gear trim, vehicle-speed limiting and an RPM-equivalent speed-limit estimate can lower the active threshold.

If the broad `engine_state_failure_flags` mask or misfire failed-bank flags `0x3000` are present, both thresholds are capped by `CAL_revlimit_limp_mode`. Confirmed contributors include sensor faults, knock-system faults, fuel-pressure faults, communication faults, and low oil pressure (`engine_state_failure_flags` bit `0x02000000`). Low oil pressure therefore participates through the common limp-rev-limit path; no separate oil-pressure fuel-cut routine was found.

### Soft limiter: airflow/throttle control

Above `revlimit_soft`, the 200 Hz controller accumulates overspeed time and regulates MAF/load with proportional, integral and RPM-rate terms. The result is converted through `CAL_load_to_tps_mapping` to `revlimit_tps_max`, which `throttle_and_torque_control()` uses when `CAL_revlimit_throttle_clamp` is enabled.

This is separate from DPM's slow torque-to-throttle request. Both can reduce throttle, but the rev limiter owns `revlimit_tps_max` and `revlimit_state_flags`; DPM owns the external torque fast/slow pair and `torque_limit_source_flags == 0x20`.

### Hard limiter: direct injection cut

`injection()` compares actual RPM directly with `revlimit_hard`. At or above the threshold it sets injection state bits `0x08` and, on the first/eligible event, `0x20`, increments `revlimit_fuelcut_count`, and marks escalation state. Bit `0x08` is released only below `revlimit_hard - CAL_revlimit_fuelcut_hysteresis`.

Repeated cuts or excessive time above the soft threshold set the main active/escalated limiter flags. The soft airflow controller then tightens its integrator and throttle command. This hard cut does not pass through DPM torque arbitration and does not use `torque_cut_level`.

## Misfire detection and protective cuts

`misfire_detect_per_cylinder_200hz()` derives crank-speed disturbance from consecutive cylinder-event timestamps, removes an RPM-indexed learned per-cylinder baseline, and applies learned RPM/load corrections. `misfire_detection_update()` supplies manual/IPS sensitivity maps, startup-MAF compensation, base thresholds, and catalyst-damage limits.

The monitor is inhibited for invalid temperature/RPM/load regions, rapid throttle or clutch transitions, active fuel/cylinder cuts, insufficient torque, MAF faults and other conditions. This avoids diagnosing intentionally missing combustion as misfire.

Two windows are important:

- a shorter catalyst-damage window (`P1302` path);
- a longer emissions window (`P1301` path).

When catalyst-damaging misfire is confirmed on one bank, flags `0x20` or `0x40` mark the entire bank failed, `engine_state_failure_flags` bit `0x00020000` is set, and `coilpack_failure_set()` disables that bank. If both banks fail, flags `0x3000` are set. `failed_ignition_cyl_count` counts individual coil failures plus all cylinders in a failed bank and feeds torque estimation, throttle severe-misfire limits and limp-rev-limit selection.

This differs from DPM:

| Source | Primary request | Persistence | Final effect |
|---|---|---|---|
| DPM | modeled fast/slow torque limits | only during slip episode | rotating cylinder count + residual spark retard + throttle limit |
| Hard rev limit | direct RPM threshold | hysteresis / overrun escalation | injection cut flags, then airflow tightening |
| Catalyst misfire | diagnostic bank-failure state | DTC/debounce state | permanent bank combustion disable and limp limit |
| Coil electrical fault | per-coil failure bit | diagnostic fault state | affected cylinder disabled and torque model corrected |

## Engine-protection interactions

- `engine_state_failure_flags` selects knock fallback, can inhibit normal load/knock learning, and invokes `CAL_revlimit_limp_mode` through a broad mask.
- Low oil pressure becomes failure bit `0x02000000` after a 100 Hz expected-pressure debounce and therefore invokes the limp limiter.
- Failed cylinders are excluded from average knock retard and delivered-torque estimation.
- External/DPM torque control cannot request fewer hard-cut cylinders than already failed ignition cylinders.
- Severe misfire also imposes independent throttle caps in `throttle_and_torque_control()`.
- `torque_limit_engine_protection` is an internal torque-model ceiling after slow-request and existing spark-loss compensation; despite its name, it is not a standalone temperature/oil protection controller.
- The ordinary gear/RPM and coolant torque tables (`CAL_torque_limit_by_rpm`, `CAL_torque_limit_by_coolant`) feed a separate throttle/load torque cap even when no external torque source is active.

## Principal calibration groups

### Ignition

- base/reference: `CAL_ign_base_manual`, `CAL_ign_base_ips`, `CAL_ign_knock_safe`, `CAL_ign_mbt_modeled`;
- limits: `CAL_ign_limit_first_gear_manual`, `CAL_ign_min`, `CAL_ign_min_engine_off`;
- dwell: `CAL_ign_dwell_time`;
- environment/transient: `CAL_ign_comp_coolant_*`, `CAL_ign_comp_engine_air`, `CAL_ign_comp_manifold_temp*`, `CAL_ign_comp_tps_rate`, `CAL_ign_comp_startup_*`;
- per-cylinder: `CAL_ign_trim_per_cyl`, `CAL_ign_retard_recovery_step`.

### Knock

- acquisition: `CAL_knock_sampling_window`, `CAL_knock_buffer_size`, `CAL_knock_agc_threshold`, `CAL_knock_agc_hysteresis_band`, `CAL_knock_mode`;
- detection: `CAL_knock_sensitivity`, `CAL_knock_peak_threshold`, `CAL_knock_detection_load_threshold`, RPM bounds and TPS-rate inhibit;
- baseline: `CAL_knock_baseline_filter_alpha`, `CAL_knock_baseline_min_clamp`;
- response: `CAL_knock_count_to_retard`, `CAL_knock_corr_limit`, `CAL_knock_retard_hold_time`, `CAL_knock_ign_retard_decay_rate`;
- octane learning: `CAL_knock_corr_octane_base`, scaler increment/decrement/multiplier calibrations.

### Rev limit and misfire

- envelopes: `CAL_revlimit_speedbase_*`, cold-start envelope, startup decay and limp RPM;
- soft control: per-gear airflow gains, airflow threshold, integrator limit and MAF error clamp;
- hard cut: `CAL_revlimit_fuelcut_hysteresis`, overrun-count threshold and overspeed time;
- misfire: sensitivity/base tables, catalyst-damage limit, emissions limit, RPM/load/temperature enable bounds.

## Conservative disassembly improvements in this pass

- Corrected types for `ign_comp_torque_reduction`, `ign_retard_torque_limit`, `knock_flags`, `knock_buffer_count`, `knock_curr_cylinder`, `knock_freq_bin_count`, and the 128-sample signed knock buffer.
- Renamed `knock_agc_reference_level???` to `knock_agc_reference_level`.
- Renamed `set_gpio_output_unknown()` to `knock_agc_apply_gain_gpio()`.
- Renamed `lea_reset3_unknown()` to `knock_baseline_grid_init()`.
- Corrected `revlimit_esclated_timer` to `revlimit_escalated_timer`.
- Added focused comments at base timing selection, knock ADC normalization, and the independent hard-rev injection cut.
- Updated the symbol CSV types/comments for the same high-confidence items and for the rev-limit/misfire state fields.

## Confidence and open questions

High confidence:

- base timing, compensation and per-cylinder eTPU scheduling flow;
- mode-4 knock window, normalized detection, event retard and octane learning;
- soft-throttle versus hard-injection rev-limit distinction;
- catalyst-misfire bank failure versus DPM cylinder-cut distinction;
- low-oil-pressure participation in the common limp-rev-limit mask.

Medium confidence / open:

1. Confirm the production `CAL_knock_mode` value from the binary. Only mode 4 has an explicit detector/baseline handoff in this export.
2. Recover semantic names for the DSP energy arrays and the eleven frequency-bin source pointers.
3. Decode all `revlimit_state_flags` bits; the major airflow, active, escalation and speed-limit states are traceable, but several secondary bits remain unnamed.
4. Decode the full `misfire_condition_flags` bitfield beyond the bank-failure and major inhibit/window bits.
5. Resolve the exact low-level injector-channel interpretation of `injection_flags` bits `0x08` and `0x20`; their hard-rev-limit role is explicit, but the final eTPU alias is partially obscured.
6. Confirm whether non-mode-4 DSP routines are dormant development algorithms or lost final-consumer references.

## Marginal value of this pass

This pass materially extends the previous traction work rather than restating it:

- it reaches the exact per-cylinder spark and eTPU timing boundary;
- reconstructs the analog-to-DSP-to-learned-retard knock pipeline;
- identifies a likely production-only knock mode dependency;
- proves the hard rev limiter bypasses torque arbitration and cuts injection directly;
- separates temporary DPM cylinder selection from diagnostic bank shutdown;
- links low oil pressure and major faults to the limp rev ceiling;
- corrects several misleading types/names in both the C export and symbol CSV.
