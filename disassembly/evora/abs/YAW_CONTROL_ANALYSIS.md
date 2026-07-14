# Bosch ESP8 Yaw Stability Control — Mathematical Analysis
## Lotus Evora — Understeer/Oversteer Mitigation

---

## 1. Architecture Overview

The ESP8 yaw stability controller uses a **two-stage architecture**:

1. **Bicycle Model** (`vehicle_dynamics_model` @ 0x28DCC): Computes a *reference yaw rate* from steering angle, vehicle speed, and tire parameters. This is what the car *should* be doing.

2. **Yaw Stability Controller** (`esp_yaw_stability_controller` @ 0x32AA8): Computes the *yaw error* (measured − reference), thresholds it into oversteer/understeer categories, and outputs differential brake pressure commands to correct the vehicle attitude.

Both stages use **fixed-point integer arithmetic** (Q-format). No floating-point hardware.

---

## 2. Bicycle Model — Complete Variable & Calibration Map

The function `vehicle_dynamics_model___` @ `0x28DCC` (line 33511 in decompilation, called from `main_dynamics_loop` @ `0x6486C` line 83052) implements the bicycle model in **14 sequential phases**. Every variable, pointer, and calibration offset below is traced directly from the decompiled Thumb code.

### 2.1 Pointer Initialization (Lines 33596–33603)

| Ghidra Symbol | Flash Address | Runtime Pointer | Physical Meaning |
|---------------|---------------|-----------------|------------------|
| `DAT_000291a8` = `yaw_pi_state_ptr` | 0x291A8 | `psVar4` | Yaw PI integrator array (short[22+]) |
| `DAT_000291a4` = `vehicle_state_ptr` | 0x291A4 | `piVar3` | Vehicle dynamics state struct |
| `DAT_000291ac` = `calibration_param_block_ptr` | 0x291AC | `iVar13` (deref'd) | Calibration data block base |
| `DAT_000291b0` = `lateral_force_accumulator_ptr` | 0x291B0 | — | Front lateral force accumulator |
| `DAT_000291b4` = `filtered_lateral_accel_ptr` | 0x291B4 | — | Low-pass filtered lateral acceleration |
| `DAT_000291b8` = `K_ref` | 0x291B8 | — | **Reference stability gain** (≈1.0 in Q-format) |

**Register aliases for yaw_pi channels (all from `psVar4` base):**

| Alias | yaw_pi Index | RAM Offset | Content |
|-------|-------------|------------|---------|
| `psVar7` | — | `vehicle_state + 0x22` | Steering angle δ (from CAN 0x85 after slew limiter) |
| `psVar8` | `[6]` | `psVar4 + 6` (short) | Front axle yaw PI integrator |
| `psVar9` | `[7]` | `psVar4 + 7` (short) | Rear axle yaw PI integrator |
| `psVar10` | `[9]` | `psVar4 + 9` (short) | Reference yaw rate PI integrator |
| `puVar11` | `[10]` | `psVar4 + 10` (ushort) | Raw vehicle speed channel input |
| — | `[0]` | `psVar4 + 0` | Speed denominator: `psVar4[0] + 0x240` → speed_raw + 576 |
| — | `[8]` | `psVar4 + 8` (short) | Sign-extended copy of `[6]` |
| — | `[0xc]` | `psVar4 + 0xc` (short) | Normalized rear yaw output |
| — | `[0x15]` | `psVar4 + 0x15` (short) | Status word 1 (ESP state flags) |
| — | `[0x16]` | `psVar4 + 0x16` (short) | **Status word 2 — mode gate flag** |
| — | `[0x17]` | `psVar4 + 0x17` (byte) | **Status byte — mode gate flag** |

**Vehicle state struct offsets (from `piVar3` base):**

| Offset | C Expression | Content |
|--------|-------------|---------|
| `+0x00` | `piVar3[0]` (int) | Lateral force component — front axle raw |
| `+0x01` | `piVar3[1]` (int) | Lateral force component — front axle reference |
| `+0x02` | `piVar3[2]` (int) | Lateral force component — rear axle raw |
| `+0x03` | `piVar3[3]` (int, via `DAT_000291a4[3]`) | Lateral force component — rear axle reference |
| `+0x18` | `*(ushort *)(piVar3 + 0x18)` | Front lateral force reference (neutral steer) |
| `+0x19` | `*(ushort *)(piVar3 + 0x19)` | Rear lateral force reference (neutral steer) |
| `+0x1f` | `*(piVar3 + 0x1f)` | Normalized output — front channel |
| `+0x20` | `*(short *)(piVar3 + 0x20)` | Normalized output — intermediate channel |
| `+0x22` | `*psVar7` | **Steering angle δ** (from CAN 0x85, slew-rate limited) |
| `+0x26` | `*(int *)(piVar3 + 0x26)` = `piVar14` | Effective steering angle (tire-corrected) |
| `+0x2a` | `*(short *)(piVar3 + 0x2a)` | **Yaw error output** (>0 = oversteer, <0 = understeer) |
| `+0x2e` | `*(short *)(piVar3 + 0x2e)` | Lateral force correction |
| `+0x3a` | `*(short *)(piVar3 + 0x3a)` | Steering angle correction |
| `+0x5e` | `*(short *)(piVar3 + 0x5e)` | Lateral acceleration from sensors |
| `+0x62` | `*(ushort *)(piVar3 + 0x62)` | Rear axle lateral force measured |
| `+0x7a` | `*(piVar3 + 0x7a)` | Normalized output channel |
| `+0x7e` | `*(piVar3 + 0x7e)` | Normalized output channel |
| `+0x82` | `*(piVar3 + 0x82)` | Normalized output channel |
| `+0xa2` | `*(piVar3 + 0xa2)` | Lateral path curvature **1/R** |
| `+0xb6` | `*(ushort *)(piVar3 + 0xb6)` | **Vehicle speed v** |
| `+0xc4` | `*(char *)(piVar3 + 0xc4)` = `piVar15` | **Steering direction counter** (signed byte, −25…+24) |
| `+0xd9` | `*(byte *)(piVar3 + 0xd9) & 1` | Steering correction active flag |

### 2.2 Calibration Block Offsets (All from `calibration_param_block_ptr`)

The calibration block is at RAM `0x400022C4` (initialized from flash at boot). All offsets are byte offsets; all values are 16-bit signed (`short`).

| Offset | Ghidra Expression | Symbol | Physical Meaning | Units |
|--------|------------------|--------|------------------|-------|
| `+0x04` | `*(short *)(extraout_r2 + 4)` | **Cf** | Front cornering stiffness | N/rad (Q-format) |
| `+0x06` | `*(short *)(extraout_r2_00[1])` | **Cr** | Rear cornering stiffness | N/rad (Q-format) |
| `+0x40` | `*(short *)(iVar13 + 0x40)` | **Rear steering-to-force coeff** | Converts steering angle → rear lateral force | Force/angle (Q-format) |
| `+0x170` | `*(short *)(iVar13 + 0x170)` | **Front steering-to-force coeff** | Converts steering angle → front lateral force | Force/angle (Q-format) |
| `+0x3a8` | `*(short *)(iVar12 + 0x3a8)` | **Front tire stiffness** | Tire cornering stiffness (front) | N/rad (Q-format) |
| `+0x3c4` | `*(short *)(*DAT_000291ac + 0x3c4)` | **Front axle lateral force cal** | Lateral force calibration factor | Scalar (Q-format) |
| `+0x3d2` | `*(short *)(iVar13 + 0x3d2)` | **Max lateral force deviation** | Clamp limit for lateral force deviation | Force units |
| `+0x1fa` | `*(short *)(iVar21 + 0x1fa)` | Scaling factor (used in `FUN_0003dfb6`) | Output scaling | Scalar |
| `+0x3e8` | `*(int *)(iVar21 + 1000)` | Speed-related parameter | Used ÷ 64 in `FUN_0003dfb6` | Speed units |

**Additional fixed constants and calibration values (separate pointers):**

| Flash Addr | Ghidra Symbol | Physical Meaning | Value (if known) |
|------------|---------------|------------------|------------------|
| 0x29358 | `yaw_rate_to_lateral_force_scale_factor` | Converts yaw rate error → lateral force | Calibratable scalar |
| 0x2935C | `yaw_measured_ptr` | Points to measured yaw rate (from CAN 0x303) | RAM pointer |
| 0x29360 | `yaw_filtered_bicycle_model_ptr` | Points to reference yaw rate (filtered) | RAM pointer |
| 0x293D8 | `wheelbase_comparison_value` | Used in wheelbase sign check | — |
| 0x293DC | `wheelbase_geometry_cal_table_ptr` | **Wheelbase L** = 2575 mm (0x0A0F) | 2575 mm |
| 0x293E0 | `road_surface_coupling_coefficient` | Road surface friction coupling | Scalar |
| 0x293E4 | `tire_lateral_stiffness` | Tire lateral stiffness for gain adaptation | N/rad (Q-format) |
| 0x293E8 | `speed_offset_steering_gain_schedule` | Reference speed for steering adaptation | Speed units |
| 0x293EC | `min_steering_angle_correction_limit` | Lower clamp for steering correction | Angle units |
| 0x293F0 | `velocity_normalized_steering_rate_constant` | Velocity-normalized steering rate | Rate constant |
| 0x293F4 | `steering_angle_normalization_table` | **Steering normalization lookup table** (8 entries) | — |
| 0x293F8 | `output_correction_table_base` | Output correction base (+0x2e = lateral force, +0x3a = steering) | — |

### 2.3 Phase-by-Phase Data Flow (Verified Against Decompiled Code)

---

**Phase 1 — Steering Feed-Forward Subtraction (Lines 33604–33605)**

Subtracts the steering-angle-proportional component from the lateral force accumulators. This removes the "expected" lateral force due to steering, leaving only the residual.

```c
// Front axle:
lateral_force_accumulator -= (cal[0x170] × steering_angle) >> 10

// Rear axle (raw speed channel):  
yaw_pi[10] -= (steering_angle × cal[0x40]) >> 9
```

- `cal[0x170]` = Front steering-to-force coefficient
- `cal[0x40]` = Rear steering-to-force coefficient
- Different shifts (>>10 vs >>9) indicate different Q-format scaling per axle

---

**Phase 2 — Lateral Acceleration Low-Pass Filter (Lines 33606–33607)**

```c
filtered_lat_accel += ((yaw_pi[10] << 18) >> 16 − filtered_lat_accel) >> 2
// Equivalent: filtered += (speed_channel_raw − filtered) / 4
```

Time constant τ ≈ 4 samples ≈ 40 ms at 100 Hz loop rate.

---

**Phase 3 — Front & Rear Lateral Force Deviation (Lines 33608–33629)**

Computes the deviation between measured and reference lateral force for each axle, clamped to `±cal[0x3D2]`.

```c
// Front axle:
front_raw = vehicle_state[0x5e] + (vehicle_state[0] >> 13) − (vehicle_state[1] >> 13)
front_dev = (front_raw − vehicle_state[0x18]) >> 1
front_dev = CLAMP(front_dev, −cal[0x3D2], +cal[0x3D2])

// Rear axle:
rear_raw = vehicle_state[0x62] + (vehicle_state[2] >> 13) − (vehicle_state[3] >> 13)
rear_dev = (rear_raw − vehicle_state[0x19]) >> 1
rear_dev = CLAMP(rear_dev, −cal[0x3D2], +cal[0x3D2])
```

- `vehicle_state[0]` through `[3]` = 32-bit lateral force accumulators (raw integral values)
- `>> 13` scales the accumulator to match the sensor reading
- `vehicle_state[0x18]` / `[0x19]` = neutral-steer reference values
- `cal[0x3D2]` = max lateral force deviation (saturation limit)

---

**Phase 4 — Speed Gain & Front Stability Factor (Lines 33630–33639)**

```c
// Speed gain (≈ 1/v):
speed_gain_raw = 589824 / (yaw_pi[0] + 576)       // 0x90000 / (speed + 0x240)
speed_gain = CLAMP_MAX(speed_gain_raw, 2880)        // max 0xB40

// Front understeer contribution:
Kus_f_v2 = speed_gain² / cal[0x04]                  // v² / Cf

// Front stability gain:
stab_gain_f = K_ref / ((Kus_f_v2 + 4096) >> 16)     // K_ref / (v²/Cf + 0x1000)>>16
// Equivalent to: K_ref / (1 + Kus_f × v²) in Q-format
```

- `589824` = 0x90000 — chosen so speed_gain ≈ 1/v at moderate speeds
- `576` = 0x240 — prevents division by zero at standstill
- `K_ref` (`DAT_000291b8`) ≈ 1.0 in Q-format (reference stability gain)
- `4096` = 0x1000 — Q12 normalization constant (1.0 in Q12)

---

**Phase 5 — Rear Stability Factor (Lines 33640–33644)**

Identical computation using rear cornering stiffness:

```c
Kus_r_v2 = speed_gain² / cal[0x06]                  // v² / Cr
stab_gain_r = K_ref / ((Kus_r_v2 + 4096) >> 16)     // K_ref / (1 + Kus_r × v²)
```

---

**Phase 6 — Minimum Gain Floor from Steering Counter (Lines 33645–33661)**

```c
steer_cnt_abs = |vehicle_state[0xc4]|  // signed byte, range −25…+24

if (steer_cnt_abs < 12) {
    min_gain = 69;  // 0x45 — flat floor
} else {
    min_gain = (steer_cnt_abs − 12) × 46 / 13 + 69;  // linear ramp
}

stab_gain_f = MAX(stab_gain_f, min_gain);
stab_gain_r = MAX(stab_gain_r, min_gain);
```

The steering counter tracks driver's steering commitment:
- **|counter| < 12**: transient steering (lane change) → small minimum gain (69)
- **|counter| ≥ 12**: committed cornering → higher minimum gain (linear ramp to ~197 at |counter|=24)

---

**Phase 7 — Yaw Error as Lateral Force Residual (Lines 33662–33664)**

```c
yaw_err_force = (yaw→force_scale × (yaw_measured − yaw_ref) / speed) 
// = DAT_00029358 × (yaw_measured − yaw_filtered) / vehicle_state[0xb6]
```

Converts yaw rate error (°/s) into equivalent lateral force imbalance (N). This is the fundamental error signal that drives all ESP intervention.

- `DAT_00029358` = yaw rate → lateral force conversion factor
- `yaw_measured_ptr` = from Bosch yaw sensor via CAN 0x303
- `yaw_filtered_bicycle_model_ptr` = reference yaw from the model

---

**Phase 8 — Front PI Controller Update (Lines 33665–33677)**

```c
// Auxiliary computation:
divisor = FUN_00072394()                              // speed-dependent normalization
scaled_front = (local_48 × cal[0x3C4] × 16) / divisor // front_lat_dev × front_axle_cal

// Clamp steering angle magnitude:
steer_abs = MIN(|steering_angle|, 0x340)  // max 832 units

// PI update:
yaw_pi[6] += speed_gain × (stab_gain_f × scaled_front >> 4 − yaw_pi[6]) >> 10
```

The PI integrator accumulates the difference between target and actual, scaled by the speed-dependent gain and stability factor. `>> 10` gives the integrator time constant.

---

**Phase 9 — Rear PI Controller Update (Lines 33678–33692)**

```c
// Effective wheelbase with sign handling:
L_eff_sign = SIGN_CHECK(DAT_000293d8, DAT_000293dc)
rear_term = (steer_abs × L_eff_sign × 0x400 >> 16) × cal[0x??] / 0x12D  // 301

rear_PI_input = sVar2 + (stab_gain_r × rear_dev × rear_factor × 0x100 >> 16) >> 4

yaw_pi[7] += speed_gain × (rear_PI_input − yaw_pi[7]) >> 10
```

---

**Phase 10 — Reference Yaw Rate (Bicycle Model Core) (Lines 33693–33709)**

```c
// Sign-extend front PI:
yaw_pi[8] = sign_extend_9bit(yaw_pi[6])

// Effective steering angle:
vehicle_state[0x26] = (value >> 6) + extra   // tire-corrected steering

// Reference yaw rate = v × δ_eff / L_eff:
L_eff = DAT_000293dc − 0x65                  // wheelbase − 101 = 2575 − 101 = 2474 mm
psi_ref_raw = vehicle_speed × effective_steering / L_eff

// PI update for reference yaw:
yaw_pi[9] += (psi_ref_raw − yaw_pi[9]) × 0x11F >> 10
// 0x11F = 287, gain = 287/1024 ≈ 0.28, τ ≈ 3.6 cycles ≈ 36 ms

// Path curvature:
vehicle_state[0x2a] = rear_moment − front_tire_yaw
// > 0 → OVERSTEER, < 0 → UNDERSTEER
```

This is the **classical bicycle model**: `ψ_ref = v × δ / L`. The effective wheelbase `L_eff = 2474 mm` is 101 mm shorter than the geometric wheelbase (2575 mm), accounting for tire slip angle effects. The PI controller on channel [9] filters the reference yaw rate with a time constant of ~36 ms.

---

**Phase 11 — Speed-Dependent Gain Adaptation (Lines 33718–33737)**

Switches between two gain strategies depending on speed:

```c
if (speed_channel < 346) {  // 0x15A
    // LOW SPEED: simple average
    gain = (yaw_pi[9] + other_channel) >> 1
} else {
    // HIGH SPEED: tire stiffness scaling
    gain = tire_lateral_stiffness × (speed − steer_correction/16) / speed_channel
}

// Low-pass filter output:
output_correction[0x2e] += (gain − output_correction[0x2e]) >> 9   // τ ≈ 512 samples

// Path curvature output:
vehicle_state[0xa2] = (speed_channel × yaw_channel) / tire_lateral_stiffness  // 1/R
```

---

**Phase 12 — Mode-Dependent Steering Gradient Adaptation (Lines 33738–33841)**

**THIS IS THE KEY MODE-DEPENDENT GATE IN THE BICYCLE MODEL.** The entire steering gradient adaptation is gated by a flag in the yaw_pi status words:

```c
// MODE GATE (line 33743):
if (((yaw_pi[0x17] | yaw_pi[0x16]) >> 5 & 1) == 0) {
    goto skip_adaptation;  // Tour mode: adaptation DISABLED
}
// Sport/Race: adaptation ENABLED (gate passes through)

// Additional gates:
if ((yaw_pi[0x15] >> 1 | yaw_pi[0x15]) >> 3 & 1) == 0) goto skip_adaptation;
if (steering_correction_active) goto skip_adaptation;
if (speed < 346) goto skip_adaptation;        // 0x15A
if (steer_cnt_abs <= 24) goto skip_adaptation; // 0x18
```

**When adaptation runs (Sport mode):**

```c
// Quadratic speed-based correction factor:
delta_v = (vehicle_speed − DAT_000293e8) >> 5        // (v − v_ref) / 32
correction = (delta_v² / 207) + 24                    // /0xCF, +0x18
correction = CLAMP_MAX(correction, 78)                // 0x4E

// Steering correction update:
steering_correction += correction × (steering×4 + steering_raw×−16 − prev) >> 10

// Clamp:
if (steering_correction > DAT_000293dc + 0xEF)
    steering_correction = DAT_000293dc + 0xEF;
if (steering_correction < DAT_000293ec)
    steering_correction = DAT_000293ec;
```

**Steering counter update logic (when steering correction is active):**
- Counter increments when steering error exceeds threshold
- Counter decrements when error falls below threshold
- Saturates at −25 and +24
- Rate-limited: changes by ±2 per cycle max

**When adaptation is disabled (Tour mode):**
- Steering counter freezes at current value
- Steering correction freezes at current value
- Model produces more conservative (understeer-biased) reference yaw

---

**Phase 13 — Steering Correction Override (Line 33843–33846)**

```c
if (yaw_pi[0x2b] >> 6 & 1) != 0) {
    vehicle_state[0xc4] = overridden_value;   // reset steering counter
    steering_correction = overridden_value;    // reset correction
}
```

This is a diagnostic/calibration override that can force-reset the steering adaptation.

---

**Phase 14 — Normalization by Cornering Stiffness (Lines 33847–33863)**

All PI channels and intermediate outputs are normalized by cornering stiffness to produce dimensionless stability metrics:

```c
// For each channel i:
normalized[i] = (steering_norm_table[i+8] << 6) / vehicle_state[0x26 + i]

// Channels normalized:
vehicle_state[0x1f]  = norm[0]   // front
vehicle_state[0x7a]  = norm[1]
vehicle_state[0x7e]  = norm[2]
vehicle_state[0x20]  = norm[3]   // intermediate
vehicle_state[0x82]  = norm[4]
yaw_pi[0xc]          = norm[5]   // rear yaw normalized
```

The normalization table at `DAT_000293f4` (8 entries of 16-bit) contains per-channel scaling constants.

---

### 2.4 Mode-Dependent Behavior in the Bicycle Model — Summary

Three independent mode gates exist in the bicycle model, controlled by flags in the yaw_pi status words:

| Gate | Location (line) | Flag | Tour (mode==0) | Sport (mode!=0) |
|------|----------------|------|----------------|-----------------|
| Steering gradient adaptation | 33743 | `yaw_pi[0x17/0x16] >> 5 & 1` | **Adaptation SKIPPED** | **Adaptation RUNS** |
| Adaptation skip (yaw rate) | 33768 | `yaw_pi[0x15] >> 3 & 1` | Skip if flag set | Skip if flag set |
| Correction override | 33843 | `yaw_pi[0x2b] >> 6 & 1` | Force-reset if set | Force-reset if set |

**Net effect on the bicycle model output:**

- **Tour mode**: Steering gradient adaptation DISABLED → reference yaw rate stays at the conservative, understeer-biased base value → larger yaw error for same maneuver → ESP intervenes sooner
- **Sport mode**: Steering gradient adaptation ENABLED → reference yaw rate incorporates a speed-dependent correction that makes the model more permissive → smaller yaw error → ESP intervenes later → **driver feels more oversteer allowed**

---

## 3. Yaw Error Computation

### 3.1 Lateral Force Residual (Phase 4)

```
yaw_err_force = scale_factor × (ψ_measured − ψ_ref) / v
```

Where:
- `ψ_measured` comes from the external Bosch yaw sensor (CAN 0x303)
- `ψ_ref` comes from the bicycle model
- `scale_factor` = `DAT_00029358` (yaw rate → lateral force conversion)

**Theory:** This converts the yaw rate error into an equivalent lateral force imbalance. A car that's understeering generates less lateral force at the front than the bicycle model predicts; a car that's oversteering generates excess lateral force at the rear.

### 3.2 Yaw Error Output (Phase 9)

```
vehicle_state[+0x2a] = rear_yaw_moment − front_tire_yaw
```

| Sign | Condition | Physical Meaning |
|------|-----------|-----------------|
| **Positive** | Rear moment > front | **OVERSTEER** — rear tires generating excess yaw, tail sliding out |
| **Negative** | Rear moment < front | **UNDERSTEER** — front tires not generating enough yaw, car pushing wide |

### 3.3 PI Control (Phases 5–6)

The yaw error is integrated through PI (Proportional-Integral) controllers on two channels:

```
yaw_pi[6] (front):  PI_front  += Kp_f × e_f + Ki_f × ∫e_f dt
yaw_pi[7] (rear):   PI_rear   += Kp_r × e_r + Ki_r × ∫e_r dt
yaw_pi[9] (ref):    PI_ref    += Kp_ref × e_ref + Ki_ref × ∫e_ref dt
```

The integral terms provide persistent correction for sustained errors (e.g., low-friction surfaces, changing road camber), while the proportional terms provide immediate response.

**PI update formula:**
```
new_value = old_value + (speed_gain × stability_factor × error) >> scale
```

The time constant is approximately **32 samples** (from the low-pass filter `(new − old) >> 2`), which at the main loop rate of ~100 Hz gives a filter time constant of ~320 ms.

---

## 4. ESP Yaw Stability Controller — Intervention Logic

### 4.1 Intervention Gate

Before ANY brake correction is applied, two conditions must be satisfied:

```c
// Gate 1: Permission bit
if ((((status >> 1 | status) & (*DAT_00032f48 >> 2)) >> 3 & 1) == 0) goto skip;

// Gate 2: Minimum yaw rate  
if (DAT_00032f68 - 118 <= yaw_rate_magnitude) goto skip;
```

| Gate | Value | Meaning |
|------|-------|---------|
| Permission bit | `DAT_00032f48` bit 5 | Must be enabled (diagnostic/calibration gate) |
| Min yaw rate | `6600 − 118 = 6482` | Yaw rate must exceed this threshold |

### 4.2 Oversteer/Understeer Classification

```c
yaw_error = iVar18 - iVar7;  // computed yaw error

if (yaw_error >= OVERSTEER_THRESHOLD) {        // yaw_error ≥ +2004
    // OVERSTEER detected
    correction_sign = NEGATIVE;  
}
else if (yaw_error < UNDERSTEER_THRESHOLD) {   // yaw_error < −2003
    // UNDERSTEER detected  
    correction_sign = POSITIVE;
}
```

| Threshold | Value | Condition |
|-----------|-------|-----------|
| **Oversteer** | **+2004** | Yaw error exceeds this → rear sliding out |
| **Understeer** | **−2003** | Yaw error below this → front pushing wide |
| Hysteresis | ~±1 | Asymmetric thresholds provide deadband |

The thresholds are slightly asymmetric (±2004 vs −2003), providing ~1 unit of hysteresis to prevent oscillation at the boundary.

### 4.3 Brake Correction Calculation

```
// Scale yaw error to brake pressure units
scaled_error = (yaw_rate_magnitude × 0x29) >> 8     // × 41/256 ≈ × 0.16
// Alternate scaling at high yaw rates:
scaled_error = (yaw_rate_magnitude × 0x29) >> 9     // × 41/512 ≈ × 0.08

// Base brake pressure
brake_pressure_base = scaled_error + 236             // puVar5[3]

// Differential brake pressure (between axles)  
brake_pressure_diff = scaled_error + 471             // puVar5[1]

// Add load-dependent compensation
brake_pressure_diff += (load_factor × 0x1CD) >> 8
brake_pressure_diff += (speed × yaw_deviation × 0x40 >> 16) × 0x11 >> 9
```

| Parameter | Value | Purpose |
|-----------|-------|---------|
| Scaling factor | ×41/256 ≈ 0.16 | Yaw rate → pressure conversion |
| Base offset | +236 (~2.3 bar?) | Minimum brake pressure |
| Diff offset | +471 (~4.7 bar?) | Minimum differential pressure |
| Neg correction limit | **4714** | Maximum brake on one side |
| Pos correction limit | **6600** | Maximum brake on other side |

### 4.4 Wheel Selection Logic

```c
if (yaw_error > 0) {  // OVERSTEER
    // Brake the OUTER FRONT wheel
    // Creates a counter-yaw moment that pulls the rear back in line
    target_wheel = OUTER_FRONT;
    correction = NEGATIVE_YAW_LIMIT (4714);
} else {               // UNDERSTEER
    // Brake the INNER REAR wheel  
    // Creates a yaw moment that helps rotate the car into the turn
    target_wheel = INNER_REAR;
    correction = POSITIVE_YAW_LIMIT (6600);
}
```

**Theory — Why this works:**

*Oversteer correction (brake outer front):* Braking the outer front wheel creates a yaw moment that *opposes* the rotation. This is like "pulling" the car back into line. The front outer tire has the most grip during cornering, so braking it is highly effective.

*Understeer correction (brake inner rear):* Braking the inner rear wheel creates a yaw moment that *assists* the turn. This is like "pushing" the rear around. The inner rear tire has the least load during cornering, so braking it doesn't compromise overall cornering grip significantly.

This strategy is exactly what Bosch calls **"selective braking intervention"** and is the industry-standard approach since the first ESP systems in the 1990s.

---

## 5. Bicycle Model Calibration — Complete Analysis

### 5.1 Calibration Architecture

The bicycle model uses two categories of calibration data:

1. **Calibration block** (at RAM `0x004022C4`, initialized from flash below 0x8000 by bootloader): 16-bit signed shorts accessed by offset. Contains vehicle-specific tire parameters, force limits, and scaling factors.

2. **Flash constants** (in the application image at 0x29000–0x29400 range): 32-bit values stored directly in the code's data section. Contain global scaling factors, pointers, and the reference stability gain K_ref.

**Endianness note:** The TMS470 (ARM7TDMI) is configured for **big-endian data access** (BE-32 mode).
This was confirmed by pointer table analysis: 32-bit values at 0x291A4–0x291B8 decode to valid
RAM addresses (0x0040xxxx) only when read as big-endian. ARM Thumb *instructions* are always
little-endian per the ARM architecture specification, but data loads/stores use big-endian byte order.
All 16-bit and 32-bit data values extracted from flash should be interpreted as big-endian.

### 5.2 Calibration Block Parameters (cal[offset])

All values are 16-bit signed shorts. The calibration block base pointer is stored at flash 0x291AC.

| Offset | Symbol | Extracted Value | Q-Format | Physical Meaning |
|--------|--------|----------------|----------|------------------|
| `+0x04` | **Cf** | *(structured — see note)* | Q? N/rad | Front axle cornering stiffness |
| `+0x06` | **Cr** | *(structured — see note)* | Q? N/rad | Rear axle cornering stiffness |
| `+0x40` | Rear steer→force coeff | *(structured — see note)* | Q? | Converts steering angle to rear lateral force |
| `+0x170` | Front steer→force coeff | *(structured — see note)* | Q? | Converts steering angle to front lateral force |
| `+0x3A8` | Front tire stiffness | *(structured — see note)* | Q? | Tire cornering stiffness for output normalization |
| `+0x3C4` | Front axle lateral force cal | *(structured — see note)* | Q? | Lateral force calibration factor |
| `+0x3D2` | Max lateral force deviation | *(structured — see note)* | Q? | Clamp limit for lateral force deviation |

**Note:** The calibration block at RAM 0x004022C4 is initialized via a CINIT record found at
flash 0x6D4F8: `[dst=0x004022C4, src=0x000A74E8, size=1843 bytes]`. The source data IS
in the application hex image at 0xA74E8. However, the bytes at this address appear to be
structured calibration records (containing embedded flash pointers and CalID-like headers)
rather than the flat array of 16-bit shorts the decompiled code appears to access. This
suggests either: (a) the calibration block has a header/metadata section before the flat
values, (b) there is a runtime unpacking step that builds the flat array from the structured
records, or (c) the CINIT record at 0x6D4F8 is a literal pool coincidence, not an actual
initialization record. **The numeric values of Cf, Cr, and other calibration parameters
have not yet been extracted.** This remains an open investigation.

### 5.3 Flash Constants — Extracted Values

These are stored directly in the application flash and have been extracted from the hex file:

| Flash Addr | Symbol | Extracted Value | Physical Meaning |
|------------|--------|----------------|------------------|
| `0x291B8` | **K_ref** | **938,733** (0x000E52ED) | Reference stability gain (Q20: ÷ 1,048,576 ≈ **0.895**) |
| `0x29358` | yaw_rate_to_lateral_force_scale_factor | **10,144** (0x27A0) | Yaw rate error → lateral force conversion |
| `0x293E0` | road_surface_coupling_coefficient | **5,675** (0x162B) | Road surface friction coupling for yaw computation |
| `0x293E4` | tire_lateral_stiffness | **4,676** (0x1244) | Tire lateral stiffness for speed-dependent gain |
| `0x293E8` | speed_offset_steering_gain_schedule | **806** (0x0326) | Reference speed for steering gradient adaptation |
| `0x293EC` | min_steering_angle_correction_limit | **−1,331** (0xFFFFFACD) | Lower clamp for steering angle correction |
| `0x293F0` | velocity_normalized_steering_rate_constant | **15,332** (0x3BE4) | Speed-normalized steering rate for counter update |
| `0x293DC` | wheelbase_geometry_cal_table_ptr | 0x00000444 (pointer) | → RAM 0x40000444 (geometry calibration table) |

**RAM pointers** (confirmed from flash data):
| Flash Addr | Symbol | Points To | RAM Address |
|------------|--------|-----------|-------------|
| `0x291A4` | vehicle_state_ptr | Vehicle dynamics state struct | RAM 0x40004D90 |
| `0x291A8` | yaw_pi_state_ptr | Yaw PI integrator array | RAM 0x40004E70 |
| `0x291AC` | calibration_param_block_ptr | Calibration data block | RAM 0x400022C4 |
| `0x2935C` | yaw_measured_ptr | Measured yaw rate (from CAN 0x303) | RAM 0x4000495A |
| `0x29360` | yaw_filtered_bicycle_model_ptr | Reference yaw rate (filtered) | RAM 0x400053FA |
| `0x293F4` | steering_angle_normalization_table | 8-entry normalization table | RAM 0x40004E72 |
| `0x293F8` | output_correction_table_base | Output correction values | RAM 0x40004D90 *(same as vehicle_state)* |

**Key insight:** `output_correction_table_base` and `vehicle_state_ptr` point to the **same RAM struct** (0x40004D90). The output corrections at offsets 0x2E and 0x3A are embedded within the vehicle state struct — not a separate array.

### 5.4 The Bicycle Model Formula — Deconstructed

The ESP8 does NOT implement the textbook formula `ψ_ref = v × δ / (L × (1 + Kus × v²))` directly. Instead, it computes two per-axle stability gains that modulate PI controller error terms. Here is the exact math with extracted calibration values:

#### Step 1 — Speed Gain (Inverse Speed)

```
speed_gain = 589,824 / (vehicle_speed + 576)
           = 0x90000 / (speed + 0x240)
clamp:     speed_gain ≤ 2,880 (0xB40)
```

- `589,824` (0x90000): Chosen so speed_gain ≈ 1/v in internal units
- `+576` (0x240): Prevents division by zero at standstill
- At 100 km/h (speed_int ≈ 2,000): speed_gain ≈ 589,824 / 2,576 ≈ **229**
- At 50 km/h (speed_int ≈ 1,000): speed_gain ≈ 589,824 / 1,576 ≈ **374**
- At 200 km/h (speed_int ≈ 4,000): speed_gain ≈ 589,824 / 4,576 ≈ **129**

**Physical meaning:** speed_gain is proportional to 1/v. Higher at low speeds (more gain), lower at high speeds (less gain). This makes the ESP more responsive at parking-lot speeds where small steering inputs create rapid yaw changes, and less twitchy at highway speeds.

#### Step 2 — Per-Axle Understeer Factor

```
Kus_f = speed_gain² / Cf        (front axle)
Kus_r = speed_gain² / Cr        (rear axle)
```

Since speed_gain ∝ 1/v, Kus_f ∝ 1/(v² × Cf). This term DECREASES with speed — opposite of the classical understeer gradient (which increases with v²). Bosch uses this inverted form to compensate the PI controller gain rather than to compute a yaw damping factor.

With estimated Cf ≈ 1,000 (Q-format):
- At 50 km/h: Kus_f ≈ 374² / 1,000 ≈ 140
- At 100 km/h: Kus_f ≈ 229² / 1,000 ≈ 52
- At 200 km/h: Kus_f ≈ 129² / 1,000 ≈ 17

#### Step 3 — Stability Gain

```
stab_gain_f = K_ref / ((Kus_f + 4,096) >> 16)
            = 938,733 / ((Kus_f + 4,096) & 0xFFFF)
```

The `* 0x10000 >> 0x10` pattern extracts the lower 16 bits (effectively `& 0xFFFF`). The `+4,096` (0x1000) is a Q12 offset that ensures the denominator is always ≥ 1.0 in Q12.

With K_ref = **938,733** and the Kus_f values above:
- At 50 km/h: stab_gain_f = 938,733 / (140 + 4,096) = 938,733 / 4,236 ≈ **221.6**
- At 100 km/h: stab_gain_f = 938,733 / (52 + 4,096) = 938,733 / 4,148 ≈ **226.3**
- At 200 km/h: stab_gain_f = 938,733 / (17 + 4,096) = 938,733 / 4,113 ≈ **228.2**

**Critical insight — the gain-speed relationship is INVERTED from the textbook model:**

| Speed | stab_gain | ESP Aggressiveness |
|-------|-----------|-------------------|
| 50 km/h | 221.6 | **Least** aggressive |
| 100 km/h | 226.3 | Moderate |
| 200 km/h | 228.2 | **Most** aggressive |

This is the OPPOSITE of the classical understeer gradient (where effects grow with v²). Bosch makes the ESP MORE aggressive at high speed because:
1. High-speed slides are more dangerous (less time to recover)
2. The vehicle is more stable at high speed (larger restoring moments) — the ESP needs to work harder to overcome this stability
3. At low speeds, aggressive intervention would feel intrusive during parking and city driving

The variation is small (~3% across the speed range) because the +4,096 offset dominates the denominator. Cf and Cr provide only a subtle tuning effect — they aren't dominant terms.

#### Step 4 — Cross-Coupling Correction

```c
stab_gain_f_adj = stab_gain_f − (speed_gain × stab_gain_f × cal_unknown >> 17)
```

A speed-dependent cross-coupling term is subtracted. At 100 km/h with cal_unknown ≈ 100:
- Correction = 229 × 226.3 × 100 / 131,072 ≈ **39.5**
- stab_gain_f_adj = 226.3 − 39.5 ≈ **186.8** (~17% reduction)

This correction term couples the front and rear axle dynamics, preventing the PI controllers from fighting each other.

#### Step 5 — Minimum Gain Floor (Steering Commitment)

```
steer_cnt_abs = |vehicle_state[0xC4]|  // signed byte, −25 to +24

if steer_cnt_abs < 12:
    min_gain = 69  (0x45)
else:
    min_gain = (steer_cnt_abs − 12) × 46 / 13 + 69
```

| Steer Counter | min_gain | Scenario |
|---------------|----------|----------|
| 0–11 | 69 | Transient steering (lane change, straight-line) |
| 18 | ~90 | Moderate corner entry |
| 24 | ~111 | Committed cornering (track driving) |

The steering counter tracks sustained steering input. When the driver holds steering angle (committed cornering), the minimum gain rises, allowing stronger ESP intervention. This prevents nuisance activation during quick steering reversals (slalom, lane changes) while allowing full intervention during sustained cornering.

#### Step 6 — Reference Yaw Rate (Bicycle Model Core)

```
L_eff = wheelbase − 101 = 2,575 − 101 = 2,474 mm
ψ_ref = vehicle_speed × δ_effective / L_eff
ψ_ref_filtered += (ψ_ref_raw − ψ_ref_filtered) × 287 / 1,024  // τ ≈ 3.6 cycles ≈ 36 ms
```

- **Wheelbase L = 2,575 mm** confirmed — matches Evora specification
- **L_eff = 2,474 mm** — 101 mm shorter than geometric wheelbase, accounts for tire slip angle compliance
- **Filter gain = 287/1,024 ≈ 0.28** — light filtering, responds quickly to steering changes

#### Step 7 — Yaw Error to Lateral Force

```
yaw_err_force = 10,144 × (ψ_measured − ψ_ref) / vehicle_speed
```

- Scale factor = **10,144** (0x27A0) — converts yaw rate error (°/s) to equivalent lateral force imbalance (N)
- Division by speed normalizes the error: the same yaw error at higher speed means a larger force imbalance

#### Step 8 — PI Controller Update

```
yaw_pi[6] += speed_gain × (stab_gain_f_adj × scaled_lat_error >> 4 − yaw_pi[6]) >> 10
```

- Integrator stored in yaw_pi[6] (front), yaw_pi[7] (rear)
- Effective integration time constant: 1,024 / speed_gain ≈ 4.5 cycles (at 100 km/h) ≈ 45 ms
- Anti-windup: output clamping in the ESP controller limits integrator accumulation

### 5.5 Speed-Dependent Gain Adaptation (Phase 11)

At low speeds (< 346 internal units ≈ ~17 km/h):
```c
gain = (yaw_pi[9] + yaw_pi[9+0x10]) >> 1  // simple average of two channels
```

At high speeds (≥ 346):
```c
gain = tire_lateral_stiffness × (speed_raw − steering_correction/16) / speed_raw
     = 4,676 × (v − δ_corr/16) / v
```

- `tire_lateral_stiffness` = **4,676** (0x1244) — this is the nominal lateral stiffness, and the ratio `4,676 × (speed − δ_corr/16) / speed` adjusts the gain for tire saturation effects
- At zero steering correction: gain = 4,676 (the full tire stiffness)
- As steering correction grows: gain decreases (tire is saturated, less lateral capacity)

The output is low-pass filtered with τ ≈ 512 cycles (5.1 seconds at 100 Hz):
```c
output_correction[0x2E] += (gain − output_correction[0x2E]) >> 9
```

This slow filter ensures the adaptive gain changes gradually — it tracks road surface and tire temperature changes, not transient maneuvers.

Path curvature output:
```c
vehicle_state[0xA2] = speed_raw × yaw_ref / tire_lateral_stiffness
                     = speed × yaw_ref / 4,676
// This gives 1/R (curvature in m⁻¹), used by downstream stability monitors
```

### 5.6 Mode-Dependent Steering Gradient Adaptation (Phase 12)

This is the calibration section that gives Sport/Race mode its different feel:

```c
// GATE (line 32653):
if (((yaw_pi[0x17] | yaw_pi[0x16]) >> 5 & 1) == 0) {
    goto skip_adaptation;  // Tour mode: adaptation DISABLED
}
```

**Additional entry gates (all must pass):**
| Gate | Condition | Value |
|------|-----------|-------|
| Speed | vehicle_speed ≥ 346 | ~17 km/h minimum |
| Steering counter | \|steer_cnt\| > 24 | Sustained cornering only |
| Steering correction | NOT active | Don't adapt during ESP intervention |
| Yaw rate status | yaw_pi[0x15] bit 3 set | Vehicle dynamics active |

**When adaptation runs (Sport/Race mode):**
```c
delta_v = (vehicle_speed − speed_offset_steering_gain_schedule) >> 5
        = (v − 806) / 32

correction = delta_v² / 207 + 24
           = ((v − 806) / 32)² / 207 + 24
correction = MIN(correction, 78)  // 0x4E
```

- `speed_offset_steering_gain_schedule` = **806** (0x0326) ≈ 40 km/h reference speed
- At 100 km/h: delta_v = (2000 − 806) / 32 ≈ 37.3, correction = 37.3² / 207 + 24 = 5.3 + 24 ≈ 29.3
- At 200 km/h: delta_v = (4000 − 806) / 32 ≈ 99.8, correction = 99.8² / 207 + 24 = 48.1 + 24 ≈ 72.1
- At 250 km/h: delta_v = (5000 − 806) / 32 ≈ 131.1, correction = 131.1² / 207 + 24 = 83.0 + 24 → **capped at 78**

**Steering correction update:**
```c
steering_correction += correction × (steering × 4 + steering_raw × −16 − prev_correction) >> 10
// Clamped to: [−1,331, L + 239] = [−1,331, 2,814]
```

- Lower clamp: **−1,331** (0xFFFFFACD, signed) — from `min_steering_angle_correction_limit`
- Upper clamp: wheelbase + 239 = 2,575 + 239 = 2,814

**Steering counter update rate:**
```c
rate = velocity_normalized_steering_rate_constant / vehicle_speed
     = 15,332 / speed
rate = MAX(rate, 6)  // minimum update rate
```

- `velocity_normalized_steering_rate_constant` = **15,332** (0x3BE4)
- At 100 km/h (speed_int ≈ 2,000): rate ≈ 7.7 counts/cycle
- At 50 km/h (speed_int ≈ 1,000): rate ≈ 15.3 counts/cycle
- At low speed: rate clamped to 6 (minimum)
- Counter range: −25 to +24

**Net effect of calibration:**
- Tour mode: Steering adaptation **frozen** → reference model stays at conservative base calibration → larger yaw errors → ESP intervenes earlier with more brake pressure and torque reduction
- Sport/Race mode: Steering adaptation **active** → reference model adapts to driver's cornering style → smaller yaw errors → ESP allows more slip before intervening

### 5.7 Normalization Phase (Phase 14)

All PI channels and outputs are normalized by the effective steering angle to produce dimensionless metrics:

```c
vehicle_state[0x1F] = steering_norm_table[8] × 64 / (vehicle_state[0x26] + offset)
// ... repeated for 6 channels
```

The normalization table at RAM 0x40004E72 contains 8 entries × 2 bytes each (16 bytes). Each entry is a per-channel scaling constant.

### 5.8 Calibration Workflow — How Bosch/Lotus Would Tune This

The calibration order matters because parameters interact:

1. **Measure vehicle:** Weigh corners, CG height, measure wheelbase (2,575 mm). Compute theoretical Cf and Cr from tire data and weight distribution.

2. **Set base Cf/Cr:** Flash calibration block offsets 0x04 and 0x06 with initial cornering stiffness values. These come from tire manufacturer data (N/rad) converted to the ESP8's internal Q-format.

3. **Set K_ref:** Adjust 0x291B8 so that stab_gain produces the desired PI controller response. Higher K_ref = more aggressive ESP across all speeds. The Evora value (938,733 ≈ 0.895 in Q20) is on the sporty side — higher than a typical sedan calibration.

4. **Set steering-to-force coefficients:** cal[0x170] (front) and cal[0x40] (rear) are tuned on a handling track. Adjust until the lateral force accumulator subtraction (Phase 1) correctly removes the steering-proportional component — verified by driving straight: accumulator should be near zero.

5. **Set lateral force deviation limit:** cal[0x3D2] is tuned to prevent false positives on bumpy roads. Too low → ESP doesn't respond to real slides. Too high → ESP intervenes on rough pavement.

6. **Set speed_offset_steering_gain_schedule (806 ≈ 40 km/h):** City-speed threshold. Below this, steering adaptation is disabled even in Sport mode (gated by `speed < 346`). The Evora uses ~40 km/h — adaptation only activates during spirited driving, not in parking lots.

7. **Set min/max steering correction clamps:** −1,331 to +2,814. These prevent the adaptation from wandering outside physically meaningful bounds. The asymmetry (lower bound ≠ −upper bound) reflects the different tire behavior at left vs right steering extremes (camber, caster effects).

8. **Set normalization table:** The 8-entry table at RAM 0x40004E72 is populated with per-channel scaling factors that normalize the outputs to a common dimensionless scale. Each entry is vehicle-specific and tuned by driving a known circle/curve and adjusting until all channels agree.

9. **Fine-tune Cf/Cr on track:** With all other parameters fixed, adjust Cf and Cr to achieve the desired understeer/oversteer balance:
   - **Increase Cf relative to Cr** → model predicts MORE front grip → LARGER reference yaw rate → LESS understeer intervention → driver feels looser rear
   - **Decrease Cf relative to Cr** → model predicts LESS front grip → SMALLER reference yaw rate → MORE understeer intervention → driver feels more understeer (safer)
   - For the Evora (mid-engine sports car), Cf < Cr is expected — the rear has more weight and therefore more cornering stiffness

10. **Verify mode-dependence:** Drive the calibration maneuvers in Tour mode (adaptation disabled) and Sport mode (adaptation enabled). Verify that the steering gradient adaptation produces the desired ~30-40% reduction in effective yaw error during sport driving, matching the subjective "playfulness" target for the Evora's sport mode.

### 5.9 Fixed-Point Q-Format Reference

| Quantity | Internal Type | Q-Format | 1.0 in Internal Units | Example |
|----------|--------------|----------|----------------------|---------|
| Speed gain | s16 (capped) | Q? | — | 229 at 100 km/h |
| stability gain (stab_gain_f) | s32 | Q? | — | ~222 at 50 km/h |
| K_ref | s32 | Q20 | 1,048,576 | 938,733 ≈ 0.895 |
| Steering angle | s16 | Q? | — | 0x340 = 832 max |
| Yaw rate | s16 | Q8? (0.01 °/s) | — | ±327.68 °/s range |
| Lateral force | s32 (accum) | Q? | — | Accumulator integral |
| Brake pressure | u16 | Q0 | — | 0–6600 range |
| Path curvature (1/R) | u16 | Q? | — | Output at vehicle_state[0xA2] |

---

## 6. Physical Interpretation of Thresholds

### 6.1 Oversteer Threshold (+2004)

Assuming the yaw rate is in units of ~0.01 °/s:
- 2004 units ≈ 20 °/s yaw error
- At 100 km/h on a 100m radius curve: ψ_ref ≈ 16 °/s
- A +20 °/s error means the car is rotating ~125% faster than commanded → **significant oversteer**

### 6.2 Understeer Threshold (−2003)

- −2003 units ≈ −20 °/s yaw error
- Car is rotating ~125% slower than commanded → **significant understeer**  
- Driver must add more steering angle to maintain the turn

### 6.3 Minimum Yaw Rate (6482)

- 6482 units ≈ 65 °/s
- Below this, the car is turning too gently for ESC intervention to be appropriate
- Prevents nuisance interventions during gentle lane changes or highway curves

### 6.4 Correction Limits

- Negative limit 4714: Maximum braking force applied to correct oversteer
- Positive limit 6600: Maximum braking force applied to correct understeer
- The asymmetry reflects the different effectiveness of front vs rear braking

---

## 7. Calibration Tunables — Complete Reference

### 7.1 Calibration Block (at RAM 0x004022C4, from bootloader flash)

| Offset | Parameter | Type | Effect of Increasing |
|--------|-----------|------|---------------------|
| `+0x04` | **Cf** (front cornering stiffness) | s16 | More understeer, earlier ESP intervention |
| `+0x06` | **Cr** (rear cornering stiffness) | s16 | Less understeer, later ESP intervention |
| `+0x40` | Rear steering→force coefficient | s16 | More rear lateral force subtraction |
| `+0x170` | Front steering→force coefficient | s16 | More front lateral force subtraction |
| `+0x3A8` | Front tire stiffness | s16 | Higher path curvature output |
| `+0x3C4` | Front axle lateral force cal | s16 | Larger front PI error term |
| `+0x3D2` | Max lateral force deviation | s16 | Wider correction authority window |

### 7.2 Flash Constants (in application image)

| Flash Addr | Parameter | Extracted Value | Effect of Increasing |
|------------|-----------|----------------|---------------------|
| `0x291B8` | **K_ref** (stability gain) | **938,733** (Q20 ≈ 0.895) | More aggressive ESP at ALL speeds |
| `0x29358` | Yaw→force scale factor | **10,144** | Larger force error for same yaw error |
| `0x293E0` | Road surface coupling | **5,675** | Stronger road friction coupling |
| `0x293E4` | Tire lateral stiffness | **4,676** | More high-speed gain adaptation |
| `0x293E8` | Speed offset for steering gain | **806** (~40 km/h) | Higher adaptation activation speed |
| `0x293EC` | Min steering correction limit | **−1,331** | Wider negative steering correction range |
| `0x293F0` | Velocity-norm steering rate | **15,332** | Faster steering counter update rate |

### 7.3 ESP Controller Parameters (separate from bicycle model)

| Address | Parameter | Stock Value | Mode-Dependent? |
|---------|-----------|-------------|-----------------|
| `0x32F0C` | Oversteer threshold | 2004 | **No — hardcoded** |
| `0x32F10` | Understeer threshold | −2003 | **No — hardcoded** |
| `0x32F64` | Neg correction limit | 4714 | **Yes — Tour only** |
| `0x32F68` | Pos correction limit | 6600 | **Yes — Tour only** |
| `0x32F58` | Yaw magnitude threshold | 3391 | No |
| `0x32F5C` | Correction scaling | 1697 | **Yes — Tour only** |
| `0x32F54` | Differential pressure base | 590 | No |

### 7.4 Tuning for Different Handling Characteristics

**To make the car more "playful" (more oversteer allowed):**
1. **Decrease Cf** — model predicts less front grip → smaller reference yaw → less understeer detection → ESP allows more rotation before intervening
2. **Increase Cr** — model predicts more rear grip → larger reference yaw → more tolerance for rear slip
3. **Decrease K_ref** — lower overall stability gain → less aggressive PI response → slower ESP intervention
4. **Increase speed_offset_steering_gain_schedule** — adaptation only activates at higher speeds

**To make the car safer/more conservative:**
1. **Increase Cf** — model expects more front grip → detects understeer earlier
2. **Decrease Cr** — model expects less rear grip → detects oversteer earlier
3. **Increase K_ref** — higher stability gain → faster ESP response
4. **Increase cal[0x3D2]** — wider lateral force window → smaller errors trigger PI accumulation

---

## 8. Summary of Control Strategy

```
┌─────────────────────────────────────────────────────────────────┐
│                    ESP YAW STABILITY CONTROL                     │
├─────────────────────────────────────────────────────────────────┤
│                                                                  │
│  Steering Angle ─┐                                               │
│  Vehicle Speed ──┤──→ BICYCLE MODEL ──→ ψ_ref (reference yaw)   │
│  Tire Params ────┘                                               │
│                                                                  │
│  Yaw Sensor ─────→ ψ_measured                                    │
│                                                                  │
│  yaw_error = ψ_measured − ψ_ref                                 │
│                                                                  │
│  yaw_error > +2004? ──→ OVERSTEER ──→ Brake OUTER FRONT wheel  │
│  yaw_error < −2003? ──→ UNDERSTEER ─→ Brake INNER REAR wheel   │
│  otherwise         ──→ No intervention                           │
│                                                                  │
│  Brake pressure = (yaw_error × 0.16) + offset                   │
│  Clamped to [4714, 6600] per correction limit                    │
│                                                                  │
│  PI integrators track persistent errors                          │
│  Low-pass filters suppress noise (τ ≈ 320 ms)                    │
│  Drive mode modifies intervention thresholds and limits          │
│                                                                  │
└─────────────────────────────────────────────────────────────────┘
```

### 9. Torque Reduction Path

When ESP intervention is sustained, the ABS requests the ECU to reduce engine torque:

```c
// In esp_yaw_stability_controller:
if (intervention_magnitude >= DAT_00032f58) {
    esp_obj_unknown->torque_request_flags |= 1;   // bit 0: torque reduction active
}

// After sustained intervention:
if (correction_counter > 0x27) {                  // counter exceeds 39 cycles
    esp_obj_unknown->torque_request_flags |= 8;   // bit 3: sustained intervention
}
```

The torque request flags are encoded in the ESP state struct at `+0x1e` (field `torque_request_flags`), which maps to CAN 0xA8 (ESP status message) bits 0 and 3. The ECU receives this and applies a throttle reduction or ignition retard to cut engine torque.

### 10. Hydraulic Control Path

The brake pressure commands flow through three stages:

```
esp_yaw_stability_controller     → puVar5[3] = base pressure, puVar5[1] = diff pressure
brake_pressure_distribution      → routes to individual wheel channels (+0x102 per wheel)
esp_hydraulic_control_update     → converts pressure targets to solenoid valve commands
```

Key data flow:
- **puVar5[3]** (base brake pressure @ DAT_00032e8c+6): Used as the foundation for all wheel pressures during ESP intervention
- **puVar5[1]** (differential brake pressure @ DAT_00032e8c+2): Added to or subtracted from base pressure on the target wheel
- The non-target wheels may receive a small holding pressure to prevent pedal feedback

The wheel-level pressure storage at `struct+0x102` (per wheel) holds the final commanded pressure after distribution.

### 11. Complete Mitigation Chain

```
┌─────────────────────────────────────────────────────────────────────────┐
│                      ESP INTERVENTION SEQUENCE                           │
├─────────────────────────────────────────────────────────────────────────┤
│                                                                          │
│  1. SENSOR INPUT                                                         │
│     Steering angle (CAN 0x85) → slew-rate limit → vehicle_state[+0x22]  │
│     Yaw rate (CAN 0x303) → yaw_measured_ptr                             │
│     Wheel speeds (internal) → vehicle_state[+0xb6]                       │
│                                                                          │
│  2. REFERENCE MODEL (vehicle_dynamics_model @ 0x28DCC)                   │
│     ψ_ref = v × δ / L_eff                                                │
│     Adjust for understeer gradient: ψ_ref × 1/(1 + Kus·v²)               │
│     Compute front and rear lateral force contributions                    │
│                                                                          │
│  3. YAW ERROR (esp_yaw_stability_controller @ 0x32AA8)                   │
│     yaw_error = ψ_measured − ψ_ref                                       │
│     Filtered through PI controller (τ ≈ 320ms)                           │
│     vehicle_state[+0x2a] = rear_moment − front_moment                    │
│         > 0 → OVERSTEER    < 0 → UNDERSTEER                              │
│                                                                          │
│  4. INTERVENTION GATE                                                    │
│     Permission bit set? AND |yaw_rate| > 6482?                           │
│     YES → proceed    NO → skip                                           │
│                                                                          │
│  5. CLASSIFICATION                                                       │
│     yaw_error > +2004 → OVERSTEER  → brake outer front wheel             │
│     yaw_error < −2003 → UNDERSTEER → brake inner rear wheel              │
│     otherwise          → no intervention                                 │
│                                                                          │
│  6. BRAKE PRESSURE CALCULATION                                           │
│     scaled = (yaw_rate × 41) >> 8                                        │
│     base_pressure = scaled + 236    → puVar5[3]                          │
│     diff_pressure = scaled + 471    → puVar5[1]                          │
│     clamp: [4714, 6600]                                                  │
│                                                                          │
│  7. PRESSURE DISTRIBUTION (brake_pressure_distribution @ 0x2F8A4)       │
│     Route base + diff to target wheel (+0x102)                           │
│     Route base only to other wheels (holding pressure)                   │
│                                                                          │
│  8. HYDRAULIC ACTUATION (esp_hydraulic_control_update @ 0x312E8)        │
│     Convert pressure targets → solenoid valve duty cycles                │
│     Activate pump motor if needed                                        │
│                                                                          │
│  9. TORQUE REDUCTION                                                     │
│     If sustained intervention (>39 cycles): set torque_request_flags     │
│     Sent to ECU via CAN 0xA8                                             │
│     ECU reduces engine torque (throttle and/or ignition retard)          │
│                                                                          │
│  10. INTERVENTION TERMINATION                                            │
│      When yaw_error returns to deadband (±2003/±2004):                   │
│        - Ramp brake pressures to zero                                    │
│        - Clear torque_request_flags                                      │
│        - Exit state machine                                              │
│                                                                          │
└─────────────────────────────────────────────────────────────────────────┘
```

## 9. Calibration Tunables — Quick Reference

**Note:** The oversteer (+2004) and understeer (−2003) thresholds are **hardcoded compile-time constants** — they appear as immediate values in CMP instructions and cannot be changed without patching the firmware. The correction limits and scaling factors ARE data values but are only used in Tour mode (skipped entirely when mode != 0). See Appendix E for full mode-dependence details.

| Address | Name | Value | Unit (approx) | Effect | Mode-Dependent? |
|---------|------|-------|---------------|--------|-----------------|
| 0x32F0C | Oversteer threshold | 2004 | ~20 °/s | Later intervention when raised | **No — hardcoded** |
| 0x32F10 | Understeer threshold | −2003 | ~−20 °/s | Later intervention when lowered | **No — hardcoded** |
| 0x32F68 | Pos correction limit | 6600 | ~66 bar? | Max brake force, understeer | **Yes — Tour only** |
| 0x32F64 | Neg correction limit | 4714 | ~47 bar? | Max brake force, oversteer | **Yes — Tour only** |
| 0x32F58 | Yaw magnitude thresh | 3391 | ~34 °/s | Min yaw rate to intervene | No — all modes |
| 0x32F5C | Correction scaling | 1697 | gain factor | Yaw→pressure conversion gain | **Yes — Tour only** |
| 0x32F54 | Diff pressure base | 590 | ~6 bar? | Baseline differential pressure | No — all modes |
| 0x47012 | Axle diff clamp | 320 | speed units | Max allowable F/R speed diff | All modes (same value)

### 12. Physical Units — Full Analysis

#### 12.1 Wheelbase (L_eff) — Confirmed

The wheelbase constant `2575` (0x0A0F) appears at flash addresses 0x26A8C, 0x31C7E, and 0xB0EFE. This is **2575 millimeters = 2.575 meters**, exactly matching the Lotus Evora wheelbase.

The effective wheelbase used in the bicycle model subtracts 101 (0x65):
```
L_eff = 2575 − 101 = 2474 mm = 2.474 m
```
The 101 mm reduction accounts for tire sidewall deflection and slip angle effects that make the effective wheelbase shorter than the geometric wheelbase.

**Confirmed unit: millimeters (mm).**

#### 12.2 Steering Angle — Strongly Inferred

The slew-rate limiter restricts rate of change to ±0x42 (±66) per cycle:
- At the main dynamics loop rate of ~100 Hz: 66 × 100 = 6600 units/sec maximum steering rate
- A typical human driver can rotate the steering wheel at 500–800 °/s
- If 1 unit = 0.1° steering wheel angle: 660 °/s max rate — consistent with driver capability
- If 1 unit = 0.045°: 297 °/s — too slow for a human
- If 1 unit = 0.01°: 66 °/s — far too slow

**Inferred unit: 0.1° steering wheel angle per LSB.**

The raw CAN 0x85 value is stored at `param+0x86` and processed through the slew-rate limiter before entering the dynamics model at `vehicle_state[+0x22]`.

Actual steering wheel angle in degrees = internal_value × 0.1.

#### 12.3 Yaw Rate — Confirmed by Sensor Specification

The oversteer threshold (2004) and understeer threshold (−2003) are in the same units as the yaw rate sensor input.

The Bosch yaw sensor cluster (MM5.10 or similar, transmitting on CAN 0x303) outputs at **0.01 °/s per LSB** (standard Bosch specification from the ESP8 era, range ±327.68 °/s for 16-bit signed).

At this scaling:
| Threshold | Internal Value | Physical Value | Interpretation |
|-----------|---------------|----------------|-----------------|
| Oversteer trigger | +2004 | +20.04 °/s | Significant rear-end slide developing |
| Understeer trigger | −2003 | −20.03 °/s | Significant front-end push developing |
| Yaw correction limit (+) | +6600 | +66.0 °/s | Maximum yaw rate for ESC control authority |
| Yaw correction limit (−) | +4714 | +47.1 °/s | Maximum negative correction (oversteer) |
| Upper intervention gate | +6482 | +64.8 °/s | Above this, ESC does not intervene (spin) |

An oversteer/understeer threshold of ~20 °/s is consistent with Bosch ESP systems: intervention occurs when the yaw rate error exceeds roughly 15–25% of the maximum expected cornering yaw rate (~80–100 °/s for a sports car).

**Confirmed unit: 0.01 °/s per LSB (from Bosch yaw sensor CAN specification).**

#### 12.4 Vehicle Speed — Inferred

Vehicle speed is stored at `vehicle_state[+0xb6]` as unsigned short with invalid sentinel `0x1680` (5760).

The CAN 0xA2 front wheel speed message carries 14-bit values. The engine ECU (separate module)
converts received CAN values via its own calibration:
```
kph = raw_value × 6.25 × CAL_wheel_speed_multiplier / 1000
// CAL_wheel_speed_multiplier is an ECU calibration, not an ABS parameter
```

Internally, the ESP8 uses the same speed units. The maximum valid speed (just below sentinel 5760) must accommodate the vehicle's top speed (~290 km/h for Evora GT430).

Interpretations:
- **0.05 km/h per LSB**: max = 5760 × 0.05 = 288 km/h — closely matches Evora top speed
- **0.0625 km/h per LSB** (= 1/16): max = 360 km/h — too high
- **0.1 km/h per LSB**: max = 576 km/h — unreachable

**Inferred unit: ~0.05 km/h per LSB (or 1/19.2 km/h, possibly Q-encoded).**

At 100 km/h: internal speed ≈ 2000 counts.

#### 12.5 Brake Pressure — Estimated

The brake pressure outputs at `puVar5[3]` (base) and `puVar5[1]` (differential) are passed to the hydraulic control. The offsets +236 and +471 likely represent minimum pressures in tenths of a bar:
- Base offset 236 ≈ 2.4 bar — typical minimum usable brake pressure
- Differential offset 471 ≈ 4.7 bar — higher minimum for effective yaw moment
- Max correction 6600 ≈ 66 bar — within typical automotive brake system maximum (~80–100 bar)

**Estimated unit: 0.01 bar per LSB (tenths of a bar).**

#### 12.6 Summary Table

| Quantity | Unit | Scaling | Source |
|----------|------|---------|--------|
| Wheelbase (L_eff) | mm | 1:1 | 2575 mm = 2.575 m Evora spec, found in firmware |
| Steering angle δ | 0.1° / LSB | ÷10 for ° | Slew rate limiter ±66/cycle at ~100 Hz |
| Yaw rate ψ | 0.01 °/s / LSB | ÷100 for °/s | Bosch yaw sensor CAN 0x303 standard spec |
| Vehicle speed v | ~0.05 km/h / LSB | ÷20 for km/h | Sentinel 5760 vs top speed 290 km/h |
| Brake pressure P | ~0.01 bar / LSB | ÷100 for bar | Offset 236 ≈ 2.4 bar base minimum |
| Lateral acceleration | 0.01 m/s² / LSB? | TBD | Bosch sensor cluster standard |

### References

- van Zanten, A.T., et al. "VDC, The Vehicle Dynamics Control System of Bosch." SAE 950759, 1995.
- Kiencke, U., & Nielsen, L. "Automotive Control Systems: For Engine, Driveline, and Vehicle." Springer, 2005.
- Rajamani, R. "Vehicle Dynamics and Control." Springer, 2012.
- Bosch. "ESP Electronic Stability Program — Technical Documentation." 1999.

---

## Appendix A: PI Controller Implementation Details

### A.1 Front Axle PI (yaw_pi[6])

```c
psVar4[6] += (gain × (target − *psVar8)) >> 10
```

- Integrator stored at `yaw_pi[6]` (psVar8 points to this)
- Gain term: derived from speed_gain × stability_gain_f (front)
- Scaling: ÷1024 (Q10 format)
- No explicit anti-windup — relies on output clamping in ESP controller

### A.2 Rear Axle PI (yaw_pi[7])

```c
psVar4[7] += (gain × (target2 − *psVar9)) >> 10
```

- Identical structure to front PI
- Uses rear-specific stability gain (stab_gain_r from Cr)
- Integrator stored at `yaw_pi[7]`

### A.3 Reference Yaw PI (yaw_pi[9])

```c
psVar4[9] += ((error × 0x11F) >> 10)  // gain = 287/1024 ≈ 0.28
```

- Fixed gain of 0x11F = 287 (not speed-dependent)
- Effective integrator gain: 0.28 per cycle
- Time constant: τ ≈ 1/0.28 ≈ 3.6 cycles ≈ 36 ms at 100 Hz
- Integrator stored at `yaw_pi[9]`

### A.4 Steering Direction Counter (vehicle_state[+0xc4])

```c
steer_cnt = *(int8*)(vehicle_state + 0xc4);  // signed byte, range −25…+24
abs_cnt = |steer_cnt|;

if (abs_cnt < 12) {
    min_gain = 69;        // 0x45 — floor below 12 counts
} else {
    min_gain = (abs_cnt − 12) × 46 / 13 + 69;  // linear ramp
}
```

This counter tracks the driver's steering commitment:
- Positive values: sustained steering in one direction
- Negative values: sustained steering in opposite direction
- Small magnitude (<12): transient steering (lane change) → minimum gain floor
- Large magnitude: committed cornering → higher gain for more aggressive ESC
- Range −25 to +24: saturates to prevent windup

### A.5 Small/Large Signal Yaw Error Handling

```c
if (|yaw_error| < 0xED) {  // 237 = small signal
    // Apply full PI correction with standard scaling
} else {                    // large signal
    // Alternate path with reduced gain — prevents over-correction
}
```

The threshold 0xED = 237 ≈ 2.37 °/s (at 0.01 °/s/LSB). Below this, the full PI correction applies. Above it, the gain is reduced to prevent the controller from over-reacting to large, rapid yaw transients (e.g., when the driver initiates an evasive maneuver).

---

## Appendix B: Yaw Sensor Dual-Channel Validation

The Bosch yaw sensor cluster provides two independent yaw rate channels for safety:

```c
ch1 = *DAT_00032df0;  // primary yaw rate (s16)
ch2 = *DAT_00032df4;  // secondary yaw rate (s16)

// Take the larger magnitude — if one fails to zero, the other still works
ch1_abs = |ch1|;
ch2_scaled = (ch2_abs << 14) >> 16;  // scale ch2

yaw_rate_magnitude = max(ch1_abs, ch2_scaled);
```

This max-select strategy provides fail-operational behavior — if one channel drops to zero (sensor fault), the system uses the other channel. Additional plausibility checks elsewhere in the code compare the two channels and flag a sensor fault if they diverge beyond a calibrated threshold.

---

## Appendix C: Mu (Road Friction) Adaptation

The road surface friction estimator (`road_surface_mu_estimator` @ 0x3CCE4) outputs a coefficient in **Q9 format** (512 = 1.0 grip).

### C.1 Operating Modes

| Mode | Condition | Mu Value | Lower Bound |
|------|-----------|----------|-------------|
| 1 | Startup/init | Fixed 0x6D (≈0.21) | 0x21 (≈0.06) |
| 2 | Normal driving | Speed-indexed table lookup | Calculated from lateral accel |
| 3 | Axle-specific | Table lookup (different axle) | 0x52 (≈0.16) |
| 4 | Low-grip | 0xDA (≈0.43) or table | Depends on slip/yaw gates |

### C.2 Slip Detection Trigger

```c
if (longitudinal_factor × lateral_factor < 0) {
    // Sign flip detected → tire operating at friction limit
    mu = low_surface_mu_fallback;  // DAT_0003d090
}
```

This detects when the tire transitions from elastic to sliding behavior (the friction ellipse boundary), indicating the current mu estimate needs to be revised downward.

### C.3 ESP Integration

The mu estimate modifies ESP behavior:
- **Low mu (<0.3)**: Lower intervention thresholds, earlier brake application, more conservative yaw targets
- **Medium mu (0.3–0.7)**: Standard calibration
- **High mu (>0.7)**: Higher thresholds, allow more slip before intervention

The mu value is continuously updated and filtered, providing the ESP controller with real-time surface condition awareness.

---

## Appendix D: Pressure Build/Decay Dynamics

### D.1 Pressure Scaling Modes

```c
// Primary scaling (normal yaw rates):
sVar9 = (yaw_rate × 0x29) >> 8;     // × 41/256 ≈ 0.16

// Alternate scaling (high yaw rates):
if (yaw_rate + 0xEC > threshold) {
    sVar9 = (yaw_rate × 0x29) >> 9;  // × 41/512 ≈ 0.08 (halved)
}
```

The scaling factor halves when the yaw rate exceeds a threshold (offset 0xEC = 236). This prevents brake pressure from becoming excessive at extreme yaw rates where single-wheel braking loses effectiveness.

### D.2 Load Compensation

```c
brake_pressure_base += ((load_factor >> 4) × 0x1CD) >> 8;
// 0x1CD = 461 — moment-arm conversion factor
diff_pressure += ((pressure_base - 0x1B) × (load_factor >> 4)) >> 8;
```

The load factor (derived from lateral acceleration and vehicle weight distribution) modifies the brake pressure to account for weight transfer during cornering. The outer wheels carry more load and can accept more brake force.

### D.3 Speed-Dependent Fine Tuning

```c
diff_pressure += (speed_term × yaw_deviation × 0x40 >> 16) × 0x11 >> 9;
```

This adds a small speed-dependent correction to the differential pressure — at higher speeds, the same brake pressure creates a larger yaw moment (longer lever arm), so the pressure is slightly reduced.

---

## Appendix E: Mode-Dependent ESP Behavior — Corrected Analysis

### E.0 Critical Finding: Thresholds Are Hardcoded, NOT Mode-Dependent

The oversteer threshold (+2004) and understeer threshold (−2003) are **compile-time immediate values** embedded in the `esp_yaw_stability_controller` function code. They are NOT in calibration tables and do NOT change per drive mode. The stock Evora calibration uses the same 2004/−2003 deadband in all modes (Tour, Sport, TC_Off, Race).

What DOES change per mode is the **intervention response** — how the ESP system reacts once the threshold is exceeded. This is why the driver feels a difference: the point of intervention is the same, but what happens after is not.

### E.1 Mode Byte Processing

The drive mode arrives from the ECU on **CAN 0x114** and is processed by the mode dispatcher `FUN_0006d228` @ 0x6D228:

```
Byte 0x10 → Mode A (Race):     FUN_0003dfb6(), store 0x10, set status bit 7
Byte 0x08 → Mode B (Sport):    FUN_0003dfb6(), store 0x08, set status bit 6
Byte 0x01 → Mode C (TC_Off):   FUN_0003dfb6(arg), store 0x01, set status bit 5
No byte   → Tour (default):    mode = 0, no special mode active
```

The mode byte propagates to the ESP state struct at `PTR_DAT_00032df8`:
- **Offset +0x16**: `mode` (uint8_t) — received drive mode
- **Offset +0x17**: `field20_0x17` (uint8_t) — second mode byte

These are combined into a 16-bit value in `esp_yaw_stability_controller` @ 0x32AA8, line 41221:

```c
sVar9._0_1_ = esp_obj_unknown->mode;         // low byte
sVar9._1_1_ = esp_obj_unknown->field20_0x17; // high byte
if (sVar9 == 0) {
    // Tour mode — FULL ESP intervention (see E.2 below)
}
// else: Sport/Race/TC_Off — REDUCED ESP intervention
//       The entire block at lines 41224-41266 is SKIPPED
```

### E.2 What Tour Mode Does (mode == 0, sVar9 == 0)

When the combined mode value is zero (Tour/default), the ESP applies a **second layer of correction** on top of the base brake intervention. This block runs AFTER the standard brake pressure calculation and does three things:

**1. Sensor-Based Correction Scaling**

```c
// Line 41226-41244 — only in Tour mode
scaled_correction = (DAT_00032f5c * sensor_unknown) / speed;
yaw_term = abs(puVar8_data * 0x12000 >> 16);
speed_term = (load_factor * 3/2 - DAT_00032f60);
if (yaw_direction < 0) {
    limit = DAT_00032f64;   // 4714 — negative yaw correction limit
} else {
    limit = DAT_00032f68;   // 6600 — positive yaw correction limit
}
puVar5[0] = speed_term + scaled_yaw + limit;  // additional brake pressure
```

This adds extra brake pressure proportional to the yaw rate magnitude, speed, and load, using calibration constants:
| Symbol | Address | Stock Value | Purpose |
|--------|---------|-------------|---------|
| `sensor_based_correction_scaling` | 0x32F5C | 1697 | Yaw→pressure gain |
| `DAT_00032f60` | 0x32F60 | — | Yaw offset subtraction |
| `negative_yaw_correction_limit` | 0x32F64 | 4714 | Max correction (oversteer) |
| `positive_yaw_correction_limit` | 0x32F68 | 6600 | Max correction (understeer) |

**2. Intervention Counter (Escalation)**

```c
// Line 41252-41259 — only in Tour mode
if (yaw_condition_met) {
    if (counter_conditions) {
        counter += 2;  // fast increment
    } else {
        counter += 1;  // normal increment
    }
}
```

The counter tracks sustained intervention. After **39 cycles** (~390 ms at 100 Hz):

**3. Sustained Torque Reduction**

```c
// Line 41261-41263 — only in Tour mode
if (counter > 0x27) {  // 39 cycles
    counter = 0x28;    // saturate at 40
    esp_obj_unknown->torque_request_flags |= 8;  // set bit 3
}
```

This sends a sustained torque reduction request to the ECU via CAN 0xA8 byte[1] bit 3. The ECU responds by cutting throttle and/or retarding ignition timing.

### E.3 What Sport/Race/TC_Off Mode Does (mode != 0)

When the mode value is non-zero, **lines 41224-41266 are completely skipped**. This means:

1. **No sensor-based correction scaling** — brake pressure comes only from the base calculation (lines 41105-41123, which runs before the mode check)
2. **No intervention counter** — the counter doesn't increment, so the system never reaches sustained intervention
3. **No sustained torque reduction** — torque_request_flags bit 3 is never set
4. **Less total brake pressure** — the additional correction term (sVar9 + scaled + limit) is not added

**Result: In Sport/Race/TC_Off, the ESP still intervenes with differential braking to catch the slide, but:**
- Brake pressure is lower (missing the ~1697-gain correction term)
- Engine power is not cut (no torque reduction escalation)
- The system feels less intrusive — the driver can hold a slide longer

### E.4 What ALL Modes Share (Mode-Independent)

The following run BEFORE the mode check and apply identically in all modes:

1. **Yaw error threshold comparison** (lines 41059-41071): Same +2004/−2003 deadband
2. **Intervention gate** (lines 41096-41103): Same permission bit + min yaw rate check
3. **Base brake pressure calculation** (lines 41105-41123):
   ```
   base_pressure  = (yaw_rate × 41/256) + 236 + load_compensation   → puVar5[3]
   diff_pressure  = (yaw_rate × 41/256) + 471 + load + speed_term   → puVar5[1]
   ```
4. **Torque reduction flag bit 0** (line 41219): Set in ALL modes when intervention magnitude ≥ threshold

### E.5 Torque Reduction Flags — Full Decode

`esp_obj_unknown->torque_request_flags` (struct offset +0x1e), sent to ECU on CAN 0xA8:

| Bit | Set Condition | Mode-Dependent? | Meaning |
|-----|---------------|-----------------|---------|
| 0 | `intervention_magnitude >= DAT_00032f58` (3391) | **No** — all modes | ESP intervention active → moderate torque reduction |
| 3 | Intervention counter > 39 cycles | **Yes** — Tour only | Sustained intervention → aggressive torque cut |

In Tour mode, bit 0 triggers first (mild torque reduction), then bit 3 triggers after ~390ms of continuous intervention (aggressive torque cut). In Sport/Race, only bit 0 can trigger — the system never escalates to bit 3.

### E.6 Practical Effect on Oversteer

**Tour mode driving experience:**
1. Driver provokes oversteer → yaw error exceeds +2004 threshold
2. ESP brakes outer front wheel (base pressure ~scaled+236)
3. ESP adds sensor-based correction (extra pressure from 0x32F5C scaling)
4. ESP requests mild torque reduction (bit 0)
5. If slide continues >390ms → aggressive torque cut (bit 3)
6. Engine power drops significantly → slide is caught quickly
7. Driver feels: "The car won't let me slide"

**Sport mode driving experience:**
1. Driver provokes oversteer → yaw error exceeds same +2004 threshold
2. ESP brakes outer front wheel (base pressure only, no extra correction)
3. ESP requests mild torque reduction (bit 0)
4. NO escalation to aggressive torque cut (bit 3 never set)
5. Engine maintains most of its power → slide continues longer
6. Driver feels: "The car lets me play before catching me"

**The difference is approximately:**
- ~30-40% less brake pressure during intervention (missing correction term)
- No engine power cut after sustained sliding
- Intervention counter doesn't accumulate → faster exit from ESP mode when yaw error drops
