
# Firmware information

 - BOSCH ESP8 ABS and stability module
 - Lotus Evora 400, GT410, GT430, and GT

## CAN messages

  CAN ID 0xA2 - Front Wheel Speeds (7 bytes)

  Message Structure:
  Byte:    [0]      [1]       [2]    [3]     [4]     [5]     [6]
          |----RF----|--LF---|       |--LF---|---Car Speed---|Cnt+Chk|

  Signal Extraction:

  | Signal    | Formula                                                       | Bits   |
  |-----------|---------------------------------------------------------------|--------|
  | LF Wheel  | (byte[1] & 0x3F) << 8 | byte[3]                               | 14-bit |
  | RF Wheel  | (byte[1] & 0xC0) >> 6 | (byte[0] & 0x0F) << 10 | byte[1] << 2 | 14-bit |
  | Car Speed | (byte[0] & 0xF0) >> 4 | byte[4] << 4 | (byte[6] & 0x03) << 12 | 14-bit |
  | Counter   | (byte[6] & 0x3C) >> 2                                         | 4-bit  |
  | Checksum  | byte[6] = XOR(bytes 0-5)                                      | 8-bit  |

  Speed Scaling:
  wheel_speed = ((raw_value * 0x32) >> 3) * CAL_wheel_speed_multiplier / 1000
              = (raw_value * 50 / 8) * multiplier / 1000
              = raw_value * 6.25 * multiplier / 1000
  - Invalid value: 0x3FFF (16383) = wheel speed unavailable

  ---
  CAN ID 0xA4 - Rear Wheel Speeds (6 or 8 bytes)

  Signal Extraction:

  | Signal       | Formula                                                       | Bits   |
  |--------------|---------------------------------------------------------------|--------|
  | LR Wheel     | (byte[1] & 0x3F) << 8 | byte[3]                               | 14-bit |
  | RR Wheel     | (byte[1] & 0xC0) >> 6 | (byte[0] & 0x0F) << 10 | byte[1] << 2 | 14-bit |
  | Brake Switch | byte[4] & 0x03                                                | 2-bit  |
  | Counter      | (byte[0] & 0xF0) >> 4                                         | 4-bit  |
  | Checksum     | byte[5] = XOR(bytes 0-4)                                      | 8-bit  |

  If 8 bytes: bytes 6-7 contain additional data (abs_unused_field)

  ---
  CAN ID 0xA8 - ESP/ABS Status (6 bytes)

  | Signal          | Bit Position               | Description             |
  |-----------------|----------------------------|-------------------------|
  | ESP Active      | byte[1] bit 3              | ESP intervention active |
  | ABS Active      | byte[1] bit 5              | ABS intervention active |
  | Status flags    | byte[3] bit 6 (0x40000000) | ESP warning flag        |
  | Status flags    | byte[3] bit 4 (0x10000000) | Another flag            |
  | Brake pressure? | byte[2] bits 0-1           | Low bits status         |
  | abs_a8_flag2    | byte[2] & 0x07             | 3-bit field             |

---

## Firmware file

`PRJ_CodeBlock_BB68638_V0201_ECC_CSW_S.hex` / `.hex.c` (95,752 lines)
- ARM Thumb mode, little-endian, address range 0x8000–0xBFFEF (753,648 bytes)
- Version string "A132J0314A" at offset 0x00008064
- Wheelbase = 2.575 m (Lotus Evora); yaw rate sensor is external, received on CAN
- No hardware FPU: all math is fixed-point integer. `__aeabi_idiv(a,b)` = a/b, quotient in r0.
  - Ghidra may show quotient in `extraout_r1_XX` if `__aeabi_idiv` prototype is wrong — fix by
    setting return type to `int` (r0). The `extraout_r2/r3/r12_XX` index variables are compiler
    register-reuse artifacts (live values that survived the idiv call), not actual outputs.

---

## Key Functions

| Function | Line | Role |
|----------|------|------|
| `vehicle_dynamics_model___` | 33511 | Bicycle model reference yaw rate + understeer gradient |
| `esp_yaw_stability_controller` | 40836 | Yaw error thresholding, brake correction outputs |
| `FUN_0006486c` | 82827 | Main vehicle dynamics loop (calls above in sequence) |
| `FUN_0006dcc8` | 92040 | 1D linear interpolation (lookup table helper) |
| `FUN_0006ca94` | 90858 | Steering angle slew-rate limiter (±0x42/cycle → struct+0xa4) |
| `FUN_00032658` | 40580 | CAN steering angle receive handler (stores to struct+0x6c) |
| `FUN_0005f194` | 78252 | Stability condition / flag checker |
| `abs_state_machine` | 58658 | ABS state machine, 4-wheel channels |
| `wheelslip___` | 17073 | Wheel slip calculation |
| `traction_or_stability_sense___` | 22007 | Traction/stability mode selection |
| `electronic_differential_controller` | (after 82855) | Electronic diff control |
| `pressure_distribution_manager` | (after 82856) | Brake pressure distribution |

### Dynamics loop call order (`FUN_0006486c` line 82827)
```
FUN_0003b7e0()               pre-processing
FUN_000460f0()               lateral sensor / yaw channel update
FUN_0006ed78()               unknown
vehicle_dynamics_model___()  bicycle model, steering gradient  ← KEY
FUN_00021ad4()               wheel speed confidence weights
FUN_00057fd2()
FUN_00038954()               wheel/axle force processing
FUN_00069718()               stability flag monitoring
FUN_0005af20()               yaw channel deviation check
FUN_0002f8a4()               brake pressure distribution
FUN_0005f194()               stability condition flags
FUN_00072a1c()               stub (empty return)
FUN_0002a038()               pre-controller state update
FUN_0006dbb8()               stability pre-filter
esp_yaw_stability_controller()   yaw correction + brake outputs  ← KEY
electronic_differential_controller()
pressure_distribution_manager()
wheel_differential_monitor()
```

---

## vehicle_dynamics_model___ — Bicycle Model / Steering Gradient

### Global data structures

| Symbol | Role |
|--------|------|
| `DAT_000291a4` (`vehicle_state`, `int*`) | Main vehicle dynamics state vector |
| `DAT_000291a8` (`yaw_pi`, `short*`) | Yaw PI integrator state array |
| `DAT_000291ac` | Pointer to calibration parameter block |
| `DAT_000291b0` | Lateral force accumulator (residual after steering subtraction) |
| `DAT_000291b4` | Filtered lateral acceleration (low-pass) |
| `DAT_000291b8` | Reference stability gain K_ref (fixed-point 1.0 for Kus calc) |
| `DAT_000293dc` | Wheelbase geometry calibration table base pointer |
| `DAT_000293d8` | Wheelbase-related comparison value |
| `DAT_000293e0` | Road surface coupling coefficient |
| `DAT_000293e4` | Tire lateral stiffness |
| `DAT_000293e8` | Speed offset for steering gradient gain schedule |
| `DAT_000293ec` | Minimum steering angle correction limit |
| `DAT_000293f0` | Velocity-normalized steering rate constant |
| `DAT_000293f4` | Steering angle normalization table |
| `DAT_000293f8` | Output correction table base (+0x2e lateral force, +0x3a steer correction) |
| `DAT_00029358` | Yaw rate → lateral force scale factor |
| `yaw_measured_ptr___` (`DAT_0002935c`, `short*`) | Pointer to measured yaw rate (from CAN sensor) |
| `yaw_filtered_bicycle_model___` (`DAT_00029360`, `short*`) | Pointer to filtered reference yaw rate |

### vehicle_state offsets (base = DAT_000291a4, byte offsets unless noted)

| Offset | Content |
|--------|---------|
| +0x22 | Steering angle δ (raw, from CAN 0x85 after slew-rate limiting) |
| +0x5e | Lateral acceleration from sensors |
| +0x60 | Front axle neutral-steer reference |
| +0x62 | Rear axle lateral force measured |
| +0x64 | Rear axle neutral-steer reference |
| +0x98 (`int*[0x26]`) | Effective (tire-corrected) steering angle |
| +0xa2 | Lateral path curvature 1/R output |
| +0xb6 | Vehicle speed (unsigned short) |
| +0xc4 (`int*[0x31]`) | Signed steering direction counter (−25…+24) |
| +0xd9 bit0 | Status: steering correction active |
| +0x28 (`int[10]`) | Reference yaw rate derivative channel |
| **+0x2a** | **Reference yaw rate output** = rear_yaw_moment − front_tire_yaw |

### yaw_pi array channels (base = DAT_000291a8, short[])

| Index | Content |
|-------|---------|
| [0] | Speed-related input channel (used for speed_gain denominator) |
| [6] (`psVar8`) | Front axle yaw PI integrator |
| [7] (`psVar9`) | Rear axle yaw PI integrator |
| [8] | Sign-aligned copy of [6] |
| [9] (`psVar10`) | Reference yaw rate PI integrator |
| [10] (`puVar11`) | Raw speed channel input |
| [0xc] | Normalized rear yaw output |
| [0x15–0x17] | Status/flag words |

### Calibration block offsets (base = *DAT_000291ac)

| Offset | Content |
|--------|---------|
| +0x40 | Rear steering-to-force coefficient |
| +0x170 | Front steering-to-force coefficient |
| +0x3a8 | Front tire stiffness |
| +0x3c4 | Front axle lateral force calibration |
| +0x3d2 | Max lateral force deviation (clamp limit) |
| +0x04 (cornering stiff table[0]) | Front cornering stiffness Cf |
| +0x06 (cornering stiff table[1]) | Rear cornering stiffness Cr |

### Steering gradient algorithm (vehicle_dynamics_model___ phases)

**Phase 1** — Subtract steering feed-forward from lateral force accumulators.

**Phase 2** — Compute front/rear axle lateral force deviation from neutral (`front_lat_dev`, `rear_lat_dev`), clamped to ±cal[0x3d2].

**Phase 3** — Compute understeer stability factors:
```
speed_gain    = 589824 / (yaw_pi[0] + 576)          // ≈ 1/v
Kus_f_v2      = speed² / CAL_Cf                      // front cornering ratio
stab_gain_f   = K_ref / ((Kus_f_v2 + 4096) >> 16)   // 1/(1 + Kus_f × v²)
// same for rear using CAL_Cr → stab_gain_r
// min gain: 69 flat below |steer_cnt|=12, linear ramp above
```

**Phase 4** — Yaw error (lateral force residual):
```
yaw_err_force = DAT_00029358 × (yaw_measured − yaw_reference) / speed
```

**Phase 5/6** — PI update for front (`yaw_pi[6]`) and rear (`yaw_pi[7]`) yaw channels using speed_gain and stability factors.

**Phase 8** — Reference yaw rate (bicycle model):
```
L_eff   = DAT_000293dc − 101          // effective wheelbase in fixed-point units
ref_yaw = speed × eff_steer / L_eff   // ψ_ref = v·δ/L
yaw_pi[9] updated via PI step
```

**Phase 9** — Yaw error output (oversteer/understeer indicator):
```
vehicle_state[+0x2a] = rear_yaw_moment − front_tire_yaw
  positive → oversteer (rear generating excess yaw)
  negative → understeer (front generating less yaw than expected)
```

**Phase 11** — Steering gradient adaptation: quadratic speed-based correction factor
`((speed − speed_ref)/32)² / 207 + 24`, clamped to 78. Updates steering angle correction at
`DAT_000293f8 + 0x3a` and the signed steering counter at `vehicle_state[+0xc4]`.

**Phase 12** — Normalize all PI channels by cornering stiffness → `vehicle_state[+0x7a–0x82]`.

---

## esp_yaw_stability_controller — Oversteer/Understeer Thresholds

| Symbol | Role |
|--------|------|
| `DAT_00032df8` (`_yaw_sensor_`) | Yaw sensor state structure base |
| `DAT_00032df0` | Pointer to measured yaw rate channel 1 |
| `DAT_00032df4` | Pointer to measured yaw rate channel 2 |
| `DAT_00032e8c` (`puVar5`) | Calibration/output array (brake pressure outputs) |
| `DAT_00032e90` | Max corrective yaw rate (numerator) |
| `DAT_00032e8c[0x17]` | Speed-normalized yaw limit divisor |
| `int32_t_ARRAY_00032f0c[0]` | **Oversteer** yaw error threshold |
| `int32_t_ARRAY_00032f0c[1]` | **Understeer** yaw error threshold |
| `DAT_00032f58` | Yaw rate magnitude intervention threshold |
| `DAT_00032f5c` | Scaling for sensor-based correction |
| `DAT_00032f64` | Negative yaw correction limit |
| `DAT_00032f68` | Positive yaw correction limit |

Brake correction outputs:
- `puVar5[3]` = base brake pressure for yaw correction
- `puVar5[1]` = differential brake pressure between axles
- `_yaw_sensor_ + 0x1e` bit3 = stability correction counter exceeded (sustained intervention)

**ESP intervention gate** (line 41096):
```c
// Gate condition — intervention only if permission bit set AND yaw error large enough
if ((((uVar2 >> 1 | uVar2) & (*DAT_00032f48 >> 2)) >> 3 & 1) == 0) goto skip;
// Min yaw rate threshold:
*(short *)(DAT_00032f68 - 0x76)  // = DAT_00032f68 - 118 = min |yaw_err| for intervention
```
- `*DAT_00032f48` = permission byte; bit 5 must be set (after >> 2, bit 3 is tested)
- `DAT_00032f68 - 118` = minimum yaw rate error for intervention (calibration constant)

---

## Stability Control Gating

### Outer gate — main_dynamics_loop___ (line 83035)

```c
// Run all vehicle dynamics only if:
//   bit 5 of (DAT_00064984 + 0x2b) == 0  (disable flag clear)
//   OR *DAT_0006497c < 0                   (diagnostic override active)
if (((*(byte *)(DAT_00064984 + 0x2b) >> 5 & 1) == 0) || (*DAT_0006497c < '\0')) {
    // Run full dynamics chain (vehicle_dynamics_model___ → esp_yaw_stability_controller)
}
```

| Symbol | Role |
|--------|------|
| `DAT_00064984` | Pointer to main ESP state struct |
| `DAT_00064984 + 0x2b` bit 5 | Dynamics disable flag (1 = skip all dynamics) |
| `DAT_00064984 + 0x1a` | Short status (checked in "all inactive" condition) |
| `*DAT_0006497c` | Diagnostic override char; if < 0 (bit 7 set), force-enable dynamics |
| `DAT_00064980` | Base pointer for status/flag struct (related to DAT_00064984) |
| `DAT_00064980[0x14]` | Frame counter, 0–9 rollover (10-frame superloop) |
| `DAT_00064980[0x18] bit 7` | "All channels inactive" flag — set when no active intervention |

"All inactive" conditions checked after each dynamics run (all must be true):
- `pcVar1[0,1,4,5,0xb,0xc,0x12,0x16]` = 0 (8 flag bytes)
- `*(short *)(iVar2 + 0x1a) < 1`, `+0x1c < 1`, `+0x24 < 1`
- `*(short *)(iVar2 + 0x1e,0x20,0x22) >= 0` (3 signed values)

### Inner gate — esp_yaw_stability_controller (line 41096)

Permission byte `*DAT_00032f48` bit 5 AND yaw rate exceeds `*(short *)(DAT_00032f68 - 118)`.

---

## Road Surface Mu (Friction) Estimator — FUN_0003cce4 (line 49819)

**Output** — `DAT_0003d048[0x17]` = mu in **Q9 format** (0x200 = 512 = 1.0 grip)

Fixed mu reference values:
| Hex | Q9 float | Condition |
|-----|----------|-----------|
| `0x6d` | ≈0.21 | Mode 1 (startup/init) |
| `0x31` | ≈0.096 | Minimum lower bound |
| `0x52` | ≈0.16 | Alternate lower bound |
| `0xda` | ≈0.43 | Mode 4 fixed (wet/damp) |
| `0x200` | 1.0 | Dry tarmac (no scaling) |

**Gate:** bit 2 of `*(byte *)(DAT_0003d04c + 0x3f)` — if clear, all outputs zeroed.

**Mode byte:** `*(char *)(DAT_0003d04c + 1)` (1–4):
- **Mode 1**: Fixed mu = 0x6d, lower bound = 0x21 (startup)
- **Mode 2**: Table lookup mu (normal); `DAT_0003d090` if slip detected
- **Mode 3**: Table lookup (different axle), `DAT_0003d090` if slip; `DAT_0003d08c` if large yaw
- **Mode 4**: Complex; 0xda or `DAT_0003d08c` or table lookup depending on gating

Slip detection: `*DAT_0003d060 * *DAT_0003d05c < 0` (longitudinal × lateral sign flip)

### Mu calibration constants

| Address | Role |
|---------|------|
| `DAT_0003d050` | Speed-indexed mu lookup table (1D) |
| `DAT_0003d054` | Speed index input for mu table |
| `DAT_0003d090` | Low surface mu (fixed fallback when slip detected) — calibratable |
| `DAT_0003d08c` | Alternate fixed mu (used in modes 3/4) — calibratable |
| `DAT_0003d078` | Mu upper limit / ceiling |
| `DAT_0003d094` | Lateral accel reference value for lower bound calculation |
| `DAT_0003d098` | Scaling factor: lower_bound = 0x31 − |Δaccel| × DAT_0003d098 >> 10 |
| `DAT_0003d09c` | Mode 2/4 threshold: if > 0 use 0x19a (410) else use DAT_0003d090 |

### Additional outputs (same struct, base = DAT_0003d048)

| Offset | Content |
|--------|---------|
| `[0x17]` | Mu (road friction, Q9) |
| `[-0x45]` | Braking capacity lower bound (grip-dependent threshold) |
| `[-0x49]` | Secondary output (=8 in mode 3 when |yaw| > 0x1800) |
| `[0x12]` | Yaw/lateral reference value (= DAT_0003d08c in mode 3 conditions) |

---

## Wheel Speed Aggregator — FUN_00020358 (line 25964)

Reads 4 individual wheel state structs and computes cross-wheel statistics into a summary struct.

| Symbol | Role |
|--------|------|
| `DAT_00020b1c/20/24/28` | Pointers to 4 wheel state structs (LF, RF, LR, RR) |
| `DAT_00020b30` (`psVar6`) | Summary/aggregate wheel speed struct |
| `DAT_00020b2c` | Speed sentinel / invalid marker (0x1680 = 5760) |

Per-wheel speed fields (within each wheel struct):
- `+0x5b0` = one speed component
- `+0x5bc` = other speed component
- `+0x5a6`, `+0x5b4` = additional speed channels

Output in summary struct `DAT_00020b30` (short[]):
| Index | Content |
|-------|---------|
| `[0x16]` | Min of all 4 wheel speeds |
| `[0x17]` | Max of all 4 wheel speeds |
| `[0x18]` | Front lateral speed differential (|LF − RF|) |
| `[0x19]` | Rear lateral speed differential (|LR − RR|) |

Also sets `*(byte *)(wheel_struct + 0x3dd)` = `(+0x413 OR +0x271) >> 7` for each wheel (combined fault/status flag).