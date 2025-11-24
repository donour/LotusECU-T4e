# Lotus Evora Knock Control System

This document describes the knock detection and control system implemented in the Lotus T6e ECU firmware (E132E0288). The system uses piezoelectric knock sensors with digital signal processing to detect combustion knock and automatically retard ignition timing to prevent engine damage.

## Table of Contents

1. [System Overview](#system-overview)
2. [Knock Detection Architecture](#knock-detection-architecture)
3. [DSP Methods](#dsp-methods)
4. [Detection Thresholds and Configuration](#detection-thresholds-and-configuration)
5. [Ignition Timing Modification](#ignition-timing-modification)
6. [Octane Scaler System](#octane-scaler-system)
7. [OBD-II Diagnostics and Reporting](#obd-ii-diagnostics-and-reporting)
8. [Misfire Detection](#misfire-detection)

---

## System Overview

The knock control system operates on a per-cylinder basis across all 6 cylinders. It samples knock sensor signals during specific crank angle windows after ignition, processes the signals using frequency-domain analysis, compares results against adaptive baseline thresholds, and applies ignition retard when knock is detected.

### Key Components

| Component | Description |
|-----------|-------------|
| `knock_sensor_v_raw` | Raw ADC reading from knock sensor |
| `knock_level_scaled` | Scaled knock sensor buffer (up to 128 samples) |
| `LEA_knock_baseline_table[384]` | Adaptive learned baseline (8x8x6 - RPM x Load x Cylinder) |
| `knock_freq_components___` | Frequency bin energy values from DSP |
| `knock_flags` | Status flags controlling knock detection state |

### Control Flow

```
┌─────────────────┐    ┌─────────────────┐
│  Knock Sensor   │    │   RPM, Load     │
│  (ADC samples)  │    │ (window config) │
└────────┬────────┘    └────────┬────────┘
         │                      │
         ▼                      │
┌─────────────────────────────────────────┐
│         DSP Processing (Goertzel)       │
│         → total_magnitude               │
└────────────────────┬────────────────────┘
                     │
                     ▼
┌─────────────────────────────────────────┐
│    Compare: magnitude vs baseline       │◄──┐
└────────────────────┬────────────────────┘   │
                     │                        │
            ┌────────┴────────┐               │
            ▼                 ▼               │
       ┌─────────┐       ┌─────────┐          │
       │  KNOCK  │       │   OK    │──────────┘
       └────┬────┘       └─────────┘   (update baseline
            │                          when not knocking)
            │
    ┌───────┴───────┐
    ▼               ▼
┌────────┐    ┌───────────┐    ┌───────────┐
│Immediat│    │ Short-term│───►│ Long-term │
│Retard  │    │ Octane    │    │ Octane    │
│(fast)  │    │ Scaler    │    │ Scaler    │
└───┬────┘    └─────┬─────┘    └─────┬─────┘
    │               └───────┬───────┘
    │                       │
    │ LEA_ign_knock_retard  │ ign_retard_knock
    │                       │
    └───────────┬───────────┘
                │
                ▼
┌─────────────────────────────────────────┐
│  Final Timing = ign_base - both_retards │
└─────────────────────────────────────────┘
```

**Key Points:**
- Baseline only updates when knock is NOT detected (adaptive noise floor)
- Two parallel retard paths: immediate (fast, ~500ms decay) and octane-based (slow, learned)
- Both retard values subtract from base ignition timing

---

## Knock Detection Architecture

### Sampling Window Configuration

The ECU schedules knock sensor sampling windows based on engine speed and load. The window timing is set relative to each cylinder's TDC.

**Window Setup Function:** `knock_detection_window_setup()` (line 28566)

```c
// Window offset from TDC is lookup from 16x16 table
knock_sampling_window_offset = lookup_3D_uint8_interpolated(
    16, 16, engine_speed_3, load_mass_per_stroke,
    CAL_knock_sampling_window,
    CAL_knock_sampling_window_X_rpm,
    CAL_knock_sampling_window_Y_load);

// Buffer size (number of ADC samples) also varies with operating conditions
knock_buffer_size = lookup_3D_uint8_interpolated(
    16, 16, engine_speed_3, load_mass_per_stroke,
    CAL_knock_buffer_size,
    CAL_knock_buffer_size_X_engine_speed,
    CAL_knock_buffer_size_Y_load);

// Buffer size clamped to 64-128 samples
if (knock_buffer_size < 64) knock_buffer_size = 64;
else if (128 < knock_buffer_size) knock_buffer_size = 128;
```

**Calibration Tables:**
- `CAL_knock_sampling_window[256]` - 16x16 table for window offset
- `CAL_knock_buffer_size[256]` - 16x16 table for sample count

### Automatic Gain Control (AGC)

The knock sensor signal is scaled by an AGC system that adjusts gain based on engine speed to maintain consistent signal levels.

**AGC Configuration:** `knock_agc_configure()` (line 46194)

| Gain Mode | RPM Threshold | Reference Level |
|-----------|---------------|-----------------|
| Mode 1 (High) | < `CAL_knock_agc_threshold[0]` | 255 |
| Mode 2 | < `CAL_knock_agc_threshold[1]` | 128 |
| Mode 3 | < `CAL_knock_agc_threshold[2]` | 65 |
| Mode 4 (Low) | Above all thresholds | 33 |

The gain transitions include hysteresis via `CAL_knock_agc_hysteresis_band` to prevent oscillation.

### Signal Scaling

Raw knock sensor values are scaled before DSP processing:

```c
// From line 46109-46111
knock_level_scaled[knock_buffer_index] =
    (ushort)((int)((knock_sensor_v_raw - 0x200) * (uint)knock_sensitivity) /
            (int)(uint)knock_agc_reference_level___);
```

---

## DSP Methods

The ECU supports four DSP methods for knock detection, selected via `CAL_knock_mode`:

```c
typedef enum enum_knock_mode {
    NONE = 0,
    goertzel_64sample = 1,      // Goertzel with 64-sample window
    goertzel_2window = 2,       // Dual 64-sample windows
    spectral_128window = 3,     // 128-point FFT
    goertzel_32sample_x3 = 4    // Three overlapping 32-sample windows (DEFAULT)
} enum_knock_mode;
```

### Default Method: Goertzel with 3 Overlapping Windows (Mode 4)

**Function:** `knock_dsp_mode4_goertzel_3_overlapping_windows()` (line 46338)

The factory calibration uses `goertzel_32sample_x3` (mode 4), which processes three overlapping 32-sample windows plus a fourth window at the end of the buffer.

**Algorithm Overview:**

1. **Window 1:** Samples 0-31 (early knock detection)
2. **Window 2:** Samples 32-63 (mid-window)
3. **Window 3:** Samples 64-95 or buffer_count-31 to buffer_count
4. **Window 4:** Last 32 samples (late knock detection)

For each frequency bin, the Goertzel algorithm computes the energy magnitude:

```c
// Goertzel coefficient lookup
goertzel_coeff = ((longlong)*(short *)(&knock_goertzel_coeff_table +
                 (((byte)(&knock_freq_bin_coeff_indices)[i] & 0x7f) * 2 + 0x10 & 0x3f) * 2)
                 & 0x7fffffffU) * 2;

// Iterative Goertzel filter
for (sample = 0; sample < 32; sample++) {
    state_new = (coeff * state_curr >> 15) - state_prev + knock_level_scaled[sample];
    state_prev = state_curr;
    state_curr = state_new;
}

// Magnitude calculation: |X[k]|^2 = s1^2 + s2^2 - 2*cos(2*pi*k/N)*s1*s2
magnitude = state_curr^2 + state_prev^2 - goertzel_coeff * state_curr * state_prev;
```

**Final Output:**
The maximum magnitude across all four windows is selected for each frequency bin:
```c
for (j = 0; j < knock_freq_bin_count; j++) {
    if (window1_magnitude[j] < window4_magnitude[j])
        window1_magnitude[j] = window4_magnitude[j];
    if (window1_magnitude[j] < window3_magnitude[j])
        window1_magnitude[j] = window3_magnitude[j];
    if (window1_magnitude[j] < window2_magnitude[j])
        window1_magnitude[j] = window2_magnitude[j];
    knock_freq_components___[j] = window1_magnitude[j];
}
```

The total magnitude for the cylinder is the sum of all frequency bin energies:
```c
total_magnitude = sum(knock_freq_components___[0..knock_freq_bin_count-1]);
knock_detect_and_update_baseline(cur_cyl, total_magnitude);
```

### Other DSP Methods

**Mode 1 - Goertzel 64-Sample:** `knock_dsp_mode1_goertzel_64sample()` (line 46238)
- Processes two 64-sample windows (early and late portions of buffer)
- Takes maximum of both windows per frequency bin

**Mode 2 - Dual Window Goertzel:** `knock_dsp_mode2_goertzel_dual_window_64()` (line 46515)
- Uses DFT-style computation with explicit sin/cos lookups
- Optional Hanning window support (`DAT_400026c9`)

**Mode 3 - 128-Point FFT:** `knock_dsp_mode3_fft_128point()` (line 46595)
- Full 128-point spectral analysis
- Requires `spectral_128window` mode and 128-sample buffer

### Frequency Bin Configuration

Frequency bins are configured in `knock_dsp_setup_bins_and_reset_state()` (line 46169):

```c
for (i = 0; i < knock_freq_bin_count; i++) {
    knock_freq_bin_coeff_indices[i] =
        (char)(((uint)(ushort)SHORT_ARRAY_40006900[i] << 6) /
               ((uint)CAL_knock_agc_scaling_threshold << 1));
}
```

The system monitors up to 11 frequency bins centered around typical knock frequencies (6-15 kHz range for the V6 engine).

---

## Detection Thresholds and Configuration

### Knock Detection Function

**Main Function:** `knock()` (line 28603)

### Enabling Conditions

Knock detection requires several conditions to be met, tracked via `knock_flags`:

| Flag Bit | Meaning | Enable Condition |
|----------|---------|------------------|
| 0x10 (bit 4) | Load threshold met | `load_mass_per_stroke > CAL_knock_detection_load_threshold[rpm]` |
| 0x20 (bit 5) | RPM in range | `CAL_knock_detection_engine_speed_min < rpm < CAL_knock_detection_engine_speed_max` |
| 0x40 (bit 6) | Learning enabled | `load_mass_per_stroke > CAL_knock_learning_load_threshold[rpm]` |
| 0x01 (bit 0) | Knock active | Load and RPM conditions met, no VVT/engine faults |
| 0x02 (bit 1) | Learning active | All above plus TPS rate inhibit timer expired |
| 0x04 (bit 2) | Temperature qualified | `coolant_temp > CAL_knock_corr_temp_threshold` |

**Enabling Logic (line 28695-28714):**
```c
// Disable knock detection if:
// - Load threshold not met
// - Engine failure flags set
// - VVT inhibit active
if ((knock_flags & 0x10) == 0 || (engine_state_failure_flags & 0x200) != 0 ||
    (vvt_bank_inhibit_flags != 0)) {
    knock_flags &= ~0b00000011;  // Clear active bits
}
else if ((knock_flags & 0x20) == 0 || coolant_temp <= CAL_knock_corr_temp_threshold) {
    knock_flags = (knock_flags & ~0x01) | 0x04;
}
else {
    knock_flags |= 0x05;  // Enable knock detection
}
```

### Sensitivity and Peak Threshold Tables

Two 8x8 calibration tables control knock detection sensitivity:

**Sensitivity:** `CAL_knock_sensitivity[64]` - Scales the raw knock signal
```c
knock_sensitivity = lookup_3D_uint8_interpolated(
    8, 8, engine_speed_3, load_mass_per_stroke,
    CAL_knock_sensitivity,
    CAL_knock_sensitivity_X_engine_speed,
    CAL_knock_sensitivity_Y_load);
```

**Peak Threshold:** `CAL_knock_peak_threshold[64]` - Detection threshold multiplier
```c
knock_peak_threshold = lookup_3D_uint8_interpolated(
    8, 8, engine_speed_3, load_mass_per_stroke,
    CAL_knock_peak_threshold,
    CAL_knock_peak_threshold_X_engine_speed,
    CAL_knock_peak_threshold_Y_load);
```

### TPS Rate Inhibit

Rapid throttle changes inhibit knock detection to avoid false positives from mechanical noise:

```c
if ((tps_delta_rate < -CAL_knock_inhibit_tps_rate1 ||
     CAL_knock_inhibit_tps_rate1 < tps_delta_rate) &&
    (tps2 <= knock_inhibit_tps_max)) {
    knock_inhibit_timer_tps_rate = CAL_knock_inhibit_timer_tps_rate;
}
```

### Adaptive Baseline Learning

**Function:** `knock_detect_and_update_baseline()` (line 28787)

The system maintains a learned baseline noise level in a 3D table indexed by RPM, load, and cylinder:

```c
// Table index calculation
rpm_table_idx = engine_speed_3 >> 5;     // 8 RPM bins
load_table_idx = load_mass_per_stroke >> 5;  // 8 load bins
table_idx = cur_cyl + load_table_idx * 6 + rpm_table_idx * 48;

// Filtered baseline per cylinder
knock_baseline_filter_unknown_per_cyl[cur_cyl] =
    ((256 - CAL_knock_baseline_filter_alpha) * knock_baseline_filter_unknown_per_cyl[cur_cyl] +
     CAL_knock_baseline_filter_alpha * LEA_knock_baseline_table[table_idx]) >> 8;
```

**Knock Threshold Calculation:**
```c
knock_threshold_unknown[cur_cyl] =
    (total_magnitude * 10) / (knock_baseline_filter_unknown_per_cyl[cur_cyl] + 1);

// Knock detected if threshold exceeds peak threshold
if (knock_peak_threshold < knock_threshold_unknown[cur_cyl]) {
    knock_event_present = true;
    knock_count_per_cyl[cur_cyl] = knock_threshold_unknown[cur_cyl] - knock_peak_threshold;
}
```

**Baseline Update (only when not knocking):**
```c
if ((knock_flags & 0x20) != 0) {  // RPM in range
    if (knock_event_present == false) {
        LEA_knock_baseline_table[table_idx] =
            (total_magnitude * CAL_knock_baseline_filter_alpha +
             (256 - CAL_knock_baseline_filter_alpha) * LEA_knock_baseline_table[table_idx]) >> 8;
    }
    // Enforce minimum baseline
    if (LEA_knock_baseline_table[table_idx] < CAL_knock_baseline_min_clamp) {
        LEA_knock_baseline_table[table_idx] = CAL_knock_baseline_min_clamp;
    }
}
```

---

## Ignition Timing Modification

### Timing Retard Application

When knock is detected, ignition timing is retarded via two mechanisms:

1. **Immediate Retard (`LEA_ign_knock_retard[6]`)** - Fast-acting per-cylinder retard
2. **Octane-Based Retard (`ign_retard_knock[6]`)** - Slower long-term adjustment

**Final Ignition Calculation (line 15693-15695):**
```c
for (cyl = 0; cyl < 6; cyl++) {
    ign_adv_with_knock_retard[cyl] =
        (ign_base - LEA_ign_knock_retard[cyl] - ign_retard_knock[cyl]) +
        ign_comp_iat + ign_rpm_and_coolant_comp;
}
```

**Ignition Limited by Knock Safe Table:**
```c
// ign_knock_safe is lookup from 20x20 table
ign_knock_safe = lookup_3D(CAL_ign_knock_safe, ...) - 40;

if (ign_adv_with_knock_retard[cyl] < obd_ii_ign_adv_per_cylinder[cyl]) {
    obd_ii_ign_adv_per_cylinder[cyl] = ign_adv_with_knock_retard[cyl];
}
```

### Knock Count to Retard Mapping

The knock event magnitude maps to retard amount via `CAL_knock_count_to_retard`:

```c
if (knock_count_per_cyl[cyl] != 0) {
    ign_retard_from_kc = lookup_2D_uint8_interpolated(
        8, knock_count_per_cyl[cyl],
        CAL_knock_count_to_retard,
        CAL_knock_count_to_retard_X_knock_count);
    knock_count_per_cyl[cyl] = 0;  // Reset counter

    // Accumulate retard with limit
    if (CAL_knock_corr_limit < LEA_ign_knock_retard[cyl] + ign_retard_from_kc) {
        LEA_ign_knock_retard[cyl] = CAL_knock_corr_limit;
    } else {
        LEA_ign_knock_retard[cyl] += ign_retard_from_kc;
    }
}
```

**Key Calibrations:**
- `CAL_knock_count_to_retard[8]` - Knock intensity to retard angle mapping
- `CAL_knock_corr_limit` - Maximum retard limit (u8_angle_1/4deg)

### Retard Decay

**Function:** `knock_ign_retard_decay_200hz()` (line 28947)

Retard decays gradually when no knock is detected:

```c
// Runs every 500ms (100 * 5ms ticks)
if (knock_ign_retard_timer_unknown2 >= 100) {
    knock_ign_retard_timer_unknown2 = 0;
    for (cyl = 0; cyl < 6; cyl++) {
        if (knock_ign_retard_unknown[cyl] == 0) {  // Hold timer expired
            if (CAL_knock_ign_retard_decay_rate < LEA_ign_knock_retard[cyl]) {
                LEA_ign_knock_retard[cyl] -= CAL_knock_ign_retard_decay_rate;
            } else {
                LEA_ign_knock_retard[cyl] = 0;
            }
        }
    }
}
```

The hold timer `knock_ign_retard_unknown[cyl]` is set to `CAL_knock_retard_hold_time` when knock is detected, preventing immediate decay.

---

## Octane Scaler System

The octane scaler system provides long-term fuel quality adaptation. Higher values indicate more knock tendency (lower octane fuel).

### Short-Term Octane Scaler

**Function:** `octane_scaler_update()` (line 28883)

```c
for (cyl = 0; cyl < 6; cyl++) {
    if (LEA_ign_knock_retard[cyl] == 0) {
        // No knock: decrement short-term scaler
        if (CAL_knock_octane_scaler_shortterm_decrement < octane_scaler_shortterm[cyl]) {
            octane_scaler_shortterm[cyl] -= CAL_knock_octane_scaler_shortterm_decrement;
        } else {
            octane_scaler_shortterm[cyl] = 0;
        }
    } else {
        // Knocking: increment proportionally to retard
        new_val = octane_scaler_shortterm[cyl] +
                  LEA_ign_knock_retard[cyl] * CAL_knock_octane_scaler_shortterm_multiplier;
        octane_scaler_shortterm[cyl] = min(new_val, 0xFFFF);
    }
}
```

### Long-Term Octane Scaler (Learned)

**Function:** `octane_scaler_learn_update()` (line 28918)

```c
for (cyl = 0; cyl < 6; cyl++) {
    if (octane_scaler_shortterm[cyl] == 0) {
        // Short-term clear: decrement learned value
        if (CAL_knock_octane_scaler_decrement < LEA_octane_scaler[cyl]) {
            LEA_octane_scaler[cyl] -= CAL_knock_octane_scaler_decrement;
        } else {
            LEA_octane_scaler[cyl] = 0;
        }
    } else {
        // Short-term active: increment learned value
        if (CAL_knock_octane_scaler_increment + LEA_octane_scaler[cyl] < 0x10000) {
            LEA_octane_scaler[cyl] += CAL_knock_octane_scaler_increment;
        } else {
            LEA_octane_scaler[cyl] = 0xFFFF;
        }
    }
}
```

### Octane-Based Timing Correction

```c
// Calculate octane correction per cylinder (line 28750-28768)
knock_octane_correction_per_cyl[cyl] =
    (CAL_knock_corr_octane_base * (octane_scaler_shortterm[cyl] >> 8)) >> 8;

// Additional retard based on minimum octane scaler across all cylinders
octane_scaler_current_min = max(LEA_octane_scaler[0..5]);

if ((knock_flags & 0x20) == 0 && engine_speed > CAL_knock_detection_engine_speed_min) {
    ign_retard_knock[cyl] = knock_octane_correction_per_cyl[cyl] +
        (ign_adv_delta_to_knock_safe * (octane_scaler_current_min >> 8)) >> 8;
} else {
    ign_retard_knock[cyl] = knock_octane_correction_per_cyl[cyl] +
        (ign_adv_delta_to_knock_safe * (LEA_octane_scaler[cyl] >> 8)) >> 8;
}
```

### AFR Enrichment from Knock Retard

Large knock retard triggers fuel enrichment for cylinder cooling:

```c
// Line 16234-16252
if (knock_ign_retard_cyl0 / 6 - ign_rpm_and_coolant_comp - ign_comp_iat > 0) {
    afr_enrichment_from_ign_retard = min(255,
        CAL_inj_comp_power_enrich_from_ign_retard *
        (knock_ign_retard_cyl0 / 6 - ign_rpm_and_coolant_comp - ign_comp_iat));
}
```

---

## OBD-II Diagnostics and Reporting

### Diagnostic Trouble Codes

The ECU monitors knock control effectiveness and can set DTCs for each cylinder:

| DTC | Description |
|-----|-------------|
| P2336 | Cylinder 1 Knock Control Limit Exceeded |
| P2337 | Cylinder 2 Knock Control Limit Exceeded |
| P2338 | Cylinder 3 Knock Control Limit Exceeded |
| P2339 | Cylinder 4 Knock Control Limit Exceeded |
| P233A | Cylinder 5 Knock Control Limit Exceeded |
| P233B | Cylinder 6 Knock Control Limit Exceeded |

**DTC Setting Conditions (line 29520-29562):**

A cylinder-specific knock DTC is set when:
1. `knock_flags & 0x80` is set (OBD check enable conditions met)
2. AND either:
   - Ignition advance at minimum (`ign_adv_min >= obd_ii_ign_adv_per_cylinder[cyl]`) AND retard applied (`LEA_ign_knock_retard[cyl] != 0`)
   - OR octane scaler maxed (`LEA_octane_scaler[cyl] == 0xFFFF`) AND short-term scaler high

```c
// OBD check enable conditions
if (CAL_knock_threshold_obd_ii_check_enable_engine_speed < engine_speed_2 &&
    CAL_knock_threshold_obd_ii_check_enable_load < load_pct) {
    knock_flags |= 0x80;  // Enable OBD monitoring
}
```

### OBD-II PID Responses

Knock retard and octane scalers are available via OBD-II diagnostic PIDs:

```c
// Knock retard per cylinder (line 31157-31160)
obd_ii_response[3] = LEA_ign_knock_retard[0];
obd_ii_response[4] = LEA_ign_knock_retard[1];
obd_ii_response[5] = LEA_ign_knock_retard[2];
// etc.

// Octane scaler per cylinder (line 31033-31034)
obd_ii_response[3] = (byte)(LEA_octane_scaler[0] >> 8);
obd_ii_response[4] = (byte)LEA_octane_scaler[0];
// etc.
```

---

## Misfire Detection

While distinct from knock detection, misfire detection works alongside it to identify combustion failures.

### Detection Method

**Function:** `misfire_detect_per_cylinder_200hz()` (line 29964)

Misfire detection uses crankshaft acceleration analysis:

```c
// Calculate cylinder-specific acceleration
cyl_accel_raw[cyl] = crank_trigger_timestamp_current[cyl] -
                     crank_trigger_timestamp_last[cyl];

// Remove baseline and compensation
cyl_accel_compensated_final[cyl] = cyl_accel_baseline_removed[cyl] - (baseline_value - 0x80);

// Detect misfire
if ((misfire_condition_flags & 2) != 0) {
    if (misfire_sensitivity < cyl_accel_compensated_final[cyl]) {
        // Normal combustion
    } else if (misfire_rpm_load_threshold_scaled < cyl_accel_compensated_final[cyl]) {
        misfires_per_cyl[cyl]++;  // Misfire detected
    }
}
```

### Misfire Calibrations

- `CAL_misfire_sensitivity_ips[64]` / `CAL_misfire_sensitivity_manual[64]` - 8x8 threshold tables
- `CAL_misfire_base_threshold_ips[256]` / `CAL_misfire_base_threshold_manual[256]` - 16x16 base threshold
- `CAL_misfire_cat_damage_limit[64]` - Catalyst damage threshold
- `CAL_misfire_emissions_limit` - Emissions compliance threshold

### Misfire-Knock Interaction

Misfire detection and knock detection share some condition flags:
- Both use `misfire_condition_flags & 0x20/0x40` for bank failure states
- Coilpack failures affect both systems via `coilpack_failure_flags`

---

## Summary of Key Calibration Parameters

### Knock Detection Calibrations

| Parameter | Type | Description |
|-----------|------|-------------|
| `CAL_knock_mode` | enum | DSP algorithm selection (default: 4 = goertzel_32sample_x3) |
| `CAL_knock_sampling_window[256]` | 16x16 | Window offset from TDC |
| `CAL_knock_buffer_size[256]` | 16x16 | Sample count per window |
| `CAL_knock_sensitivity[64]` | 8x8 | Signal scaling factor |
| `CAL_knock_peak_threshold[64]` | 8x8 | Detection threshold |
| `CAL_knock_baseline_filter_alpha` | u8 | Baseline filter coefficient |
| `CAL_knock_baseline_min_clamp` | u8 | Minimum baseline value |

### Knock Response Calibrations

| Parameter | Type | Description |
|-----------|------|-------------|
| `CAL_knock_count_to_retard[8]` | 1D | Knock intensity to retard mapping |
| `CAL_knock_corr_limit` | u8_angle | Maximum retard limit |
| `CAL_knock_ign_retard_decay_rate` | u8_angle | Retard decay rate |
| `CAL_knock_retard_hold_time` | u8_time | Hold time before decay |
| `CAL_knock_corr_temp_threshold` | u8_temp | Minimum coolant temp |

### Octane Scaler Calibrations

| Parameter | Type | Description |
|-----------|------|-------------|
| `CAL_knock_corr_octane_base` | u8_angle | Base octane timing adjustment |
| `CAL_knock_octane_scaler_shortterm_decrement` | u8 | Short-term decay rate |
| `CAL_knock_octane_scaler_shortterm_multiplier` | u8 | Short-term increment rate |
| `CAL_knock_octane_scaler_increment` | u8 | Long-term increment rate |
| `CAL_knock_octane_scaler_decrement` | u8 | Long-term decay rate |

### Operating Range Calibrations

| Parameter | Type | Description |
|-----------|------|-------------|
| `CAL_knock_detection_engine_speed_min` | u8_rspeed | Minimum RPM for detection |
| `CAL_knock_detection_engine_speed_max` | u8_rspeed | Maximum RPM for detection |
| `CAL_knock_detection_engine_speed_margin` | u8_rspeed | Hysteresis margin |
| `CAL_knock_detection_load_threshold[8]` | 1D | Load threshold vs RPM |
| `CAL_knock_learning_load_threshold[8]` | 1D | Learning enable threshold |
| `CAL_knock_inhibit_tps_rate1` | u16 | TPS rate inhibit threshold |
| `CAL_knock_inhibit_timer_tps_rate` | u8_time | TPS inhibit duration |
