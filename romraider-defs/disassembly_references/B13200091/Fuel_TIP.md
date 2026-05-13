# Transient Throttle Fueling — B13200091 (Lotus Evora NA 2011)

## Overview

Two separate mechanisms work together during throttle transients:

1. **Alpha-N load selection** — switches the load signal source from MAF to TPS during transients
2. **Injtip enrichment/enleanment** — adds or removes fuel based on filtered TPS rate of change

They're complementary: Alpha-N gives the right load *target* when the MAF is lying (air column inertia), and injtip compensates for fuel *film* wetting the intake ports (X-tau model).

---

## Part 1: MAF → Alpha-N Switching

Every 200 Hz cycle, the ECU checks whether to use MAF-computed load or TPS-computed (Alpha-N) load:

```c
if (tps_rate_current > CAL_load_alphaN_tps_rate_opening_threshold ||
    tps_rate_current < -CAL_load_alphaN_tps_rate_closing_threshold ||
    tps_2 > load_selection_tps_threshold) {
    transient_load_timer = CAL_load_alphaN_hold_time;   // countdown in 5ms steps
}

if (transient_load_timer != 0 && engine_speed < CAL_load_alphaN_max_rpm) {
    load_selected_raw = load_computed_alphaN + load_comp_idle;   // TPS-based
} else {
    load_selected_raw = load_computed_maf + load_comp_idle;      // MAF-based
}
```

| Calibration | Type | Effect |
|---|---|---|
| `CAL_load_alphaN_tps_rate_opening_threshold` | `u16_factor_1/255` | TPS opening rate to trigger Alpha-N |
| `CAL_load_alphaN_tps_rate_closing_threshold` | `u16_factor_1/255` | TPS closing rate to trigger Alpha-N |
| `CAL_load_alphaN_hold_time` | `u8_time_5ms` | How long to stay in Alpha-N after trigger |
| `CAL_load_alphaN_max_rpm` | `u16_rspeed_rpm` | Alpha-N only allowed below this RPM |

---

## Part 2: X-Tau Fuel Film Compensation

After load source selection, a 1st-order lag filter models fuel film on intake port walls:

```c
_load_filtered_xtau1 = (0x100 - CAL_inj_fuel_fillm_xtau_coeff) * load_filtered1;
load_filtered1 = (_load_filtered_xtau1 >> 8) + CAL_inj_fuel_fillm_xtau_coeff * load_selected_raw;
```

`load_filtered1 = (1 - α) × load_filtered1 + α × load_selected_raw`  
where α = `CAL_inj_fuel_fillm_xtau_coeff / 256`.

Higher coefficient → faster response (less lag compensation). Lower → heavier wetting modeled.

**Stock value: 0xFF (≈100%, α ≈ 0.996).** At this setting the filter is a near pass-through — `load_filtered1` tracks `load_selected_raw` essentially unchanged each 5 ms cycle, so the X-tau fuel film compensation is **effectively disabled in the stock tune**. Transient fueling is handled entirely by the injtip enrichment/enleanment mechanism (Part 3). To re-enable meaningful wall-wetting compensation, lower this value (e.g. 200–240) and expect to reduce `CAL_injtip_time_base` accordingly to avoid double-compensation.

---

## Part 3: Injtip Enrichment/Enleanment

### 3.1 Throttle Rate Computation and Filtering

The ECU maintains a 16-entry circular buffer of TPS samples. Every 200 Hz cycle:

```c
// Step 1: shift buffer
for (i = 15; 0 < i; i--) buffer[i] = buffer[i-1];
buffer[0] = tps_current;

// Step 2: compute raw rate over window
n = min(CAL_tps_delta_rate_window_size, 15);
tps_rate_raw = buffer[0] - buffer[n];

// Step 3: asymmetric attack/decay filtering → tps_rate_transient
```

**Attack (immediate):** If `tps_rate_raw` exceeds the threshold, `tps_rate_transient` jumps immediately.  
**Decay (slow):** A cycle counter (`tps_rate_decay_divider`) delays each step downward toward zero.

Two-level opening threshold (lines 14292–14299):
```c
if (tps_rate_raw > CAL_injtip_in_threshold[1]) {
    if (tps_rate_raw > CAL_injtip_in_threshold[0]) {
        tps_rate_transient = CAL_injtip_in_threshold[0];  // hard clamp
    } else if (tps_rate_transient < tps_rate_raw) {
        tps_rate_transient = tps_rate_raw;                // follow raw
    }
}
```

Closing deadband and clamp (lines 14280–14290):
```c
if (tps_rate_raw < 0) {
    if (tps_rate_raw < -DAT_40008fa8) {                  // below deadband
        if (tps_rate_raw < -DAT_40008fa6) {
            tps_rate_transient = -DAT_40008fa6;           // hard clamp (closing)
        } else if (tps_rate_raw < tps_rate_transient) {
            tps_rate_transient = tps_rate_raw;
        }
    }
}
```

Decay step (lines 14261–14278):
```c
if (tps_rate_transient > 0) {                            // enrichment decaying
    if (++counter >= DAT_40008fa0) {
        counter = 0;
        tps_rate_transient -= injtip_in_rpm_decay;
        if (tps_rate_transient < 0) tps_rate_transient = 0;
    }
} else if (tps_rate_transient < 0) {                     // enleanment decaying
    if (++counter >= DAT_40008fa1) {
        counter = 0;
        tps_rate_transient += injtip_out_rpm_decay;
        if (tps_rate_transient > 0) tps_rate_transient = 0;
    }
}
```

### 3.2 Enrichment/Enleanment Calculation (injtip(), lines 23309–23541)

**Step 1:** Gear selection (lines 23320–23342)

```c
switch (car_gear_current) {
    case NO_GEAR: inj_tip_in_adj_gear_current = CAL_injtip_in_adj_gears[0]; break;
    case GEAR_1:  inj_tip_in_adj_gear_current = CAL_injtip_in_adj_gears[1]; break;
    // ... gears 2–5 ...
    case GEAR_6:  inj_tip_in_adj_gear_current = CAL_injtip_in_adj_gears_6;  break;
}
```

**Step 2:** Table lookups by RPM and coolant temp (lines 23343–23362)

```c
injtip_in_rpm_decay     = lookup(engine_speed, CAL_injtip_in_rpm_decay,     CAL_injtip_in_rpm_decay_X_rpm);
injtip_in_rpm_scale     = lookup(engine_speed, CAL_injtip_in_rpm_scale,     CAL_injtip_in_rpm_scale_X_rpm);
injtip_in_coolant_scale = lookup(coolant_temp, CAL_injtip_in_coolant_scale, CAL_injtip_in_coolant_scale_X_coolant_temp);
injtip_out_rpm_decay    = lookup(engine_speed, CAL_injtip_out_rpm_decay,    CAL_injtip_out_rpm_decay_X_rpm);
injtip_out_rpm_scale    = lookup(engine_speed, CAL_injtip_out_rpm_scale,    CAL_injtip_out_rpm_scale_X_rpm);
injtip_out_coolant_scale= lookup(coolant_temp, CAL_injtip_out_coolant_scale,CAL_injtip_out_coolant_scale_X_coolant_temp);
```

**Step 3:** Pulse-width calculation (lines 23363–23383)

Throttle **opening** → enrichment:
```
enrichment_pw = CAL_injtip_time_base
              × gear_adj              (/ 128)
              × injtip_in_rpm_scale   (/ 128)
              × injtip_in_coolant_scale (/ 64)
              × tps_rate_transient    (/ 128)
```

Throttle **closing** → enleanment:
```
enleanment_pw = CAL_injtip_time_base
              × injtip_out_rpm_scale   (/ 128)
              × injtip_out_coolant_scale (/ 64)
              × (-tps_rate_transient)  (/ 128)
```

Note: gear adjustment is **not** applied to enleanment.

**Step 4:** Engine running gate (lines 23384–23392)

```c
if (!engine_is_running || (misfire_condition_flags & 0x860) != 0) {
    transient_enrichment_pw = 0;
    transient_enleanment_pw = 0;
} else {
    transient_enrichment_pw = enrichment_pw;
    transient_enleanment_pw = enleanment_pw;
}
```

**Step 5:** DFCO interaction (lines 23394–23533)  
Injtip suppresses DFCO fuel cut for `CAL_injtip_overrun_inhibit_timer` after an active enrichment event, then applies `CAL_injtip_overrun_hysteresis_timer` to prevent rapid cycling.

---

## Part 4: Tuner Calibration Reference

### 4.1 Primary Controls

| Calibration | Type | Size | ROM Addr | Line | What it controls |
|---|---|---|---|---|---|
| `CAL_injtip_time_base` | `u8_time_us` | 1 | 40008f9e | 3480 | **Master gain** — scales all enrichment and enleanment. Set to 0 to disable injtip entirely. |
| `CAL_injtip_in_threshold[0]` | `u16_factor_1/1023` | 2 | 40008fa2 | 1495 | **Opening rate hard clamp** — `tps_rate_transient` cannot exceed this. Limits max enrichment. |
| `CAL_injtip_in_threshold[1]` | `u16_factor_1/1023` | 2 | 40008fa2 | 1495 | **Opening rate soft threshold** — rate must exceed this before [0] is evaluated. Acts as a deadband. |
| `CAL_tps_delta_rate_window_size` | `u8_count` | 1 | 40008f9f | 1463 | **Rate detection window** — number of 5ms samples to diff (max 15). Larger = smoother but slower detection. |

### 4.2 Gear-Dependent Enrichment

Applies to tip-in (opening) only — not tip-out.

| Calibration | Type | Size | ROM Addr | Line | Notes |
|---|---|---|---|---|---|
| `CAL_injtip_in_adj_gears` | `u8_factor_1/128` | 6 | 40008e75 | 3502 | Elements [0]–[5] = no gear, 1st–5th |
| `CAL_injtip_in_adj_gears_6` | `u8_factor_1/128` | 1 | 40008ed5 | 3503 | 6th gear (stored separately) |

Scale: 128 = 1.0× (unity), 64 = 0.5×, 192 = 1.5×. Lower gears should be higher to compensate for aggressive driveshaft acceleration.

### 4.3 RPM-Dependent Scale Tables (Opening)

Both tables have 16 elements, looked up with bilinear interpolation at 200 Hz.

| Calibration | Type | Size | ROM Addr | Line | What it controls |
|---|---|---|---|---|---|
| `CAL_injtip_in_rpm_scale` | `u8_factor_1/128` | 16 | 40009b1a | 3510 | Enrichment gain vs RPM. Typically reduced at high RPM. |
| `CAL_injtip_in_rpm_scale_X_rpm` | `u8_rspeed_125/4+500rpm` | 16 | 40009b0a | 3511 | RPM breakpoints for above |
| `CAL_injtip_in_rpm_decay` | `u8_dt_factor_1/100/5ms` | 16 | 40009b3a | 3508 | Step size by which `tps_rate_transient` decays per divider tick (opening side) |
| `CAL_injtip_in_rpm_decay_X_rpm` | `u8_rspeed_125/4+500rpm` | 16 | 40009b2a | 3509 | RPM breakpoints for above |

### 4.4 Coolant Temperature Scale Tables (Opening)

| Calibration | Type | Size | ROM Addr | Line | What it controls |
|---|---|---|---|---|---|
| `CAL_injtip_in_coolant_scale` | `u8_factor_1/64` | 16 | 40009b5a | 3513 | Enrichment gain vs coolant temp. Cold = more enrichment. |
| `CAL_injtip_in_coolant_scale_X_coolant_temp` | `u8_temp_5/8-40c` | 16 | 40009b4a | 3512 | Coolant temp breakpoints for above |

### 4.5 RPM-Dependent Scale Tables (Closing)

| Calibration | Type | Size | ROM Addr | Line | What it controls |
|---|---|---|---|---|---|
| `CAL_injtip_out_rpm_scale` | `u8_factor_1/128` | 16 | 40009b7a | 3517 | Enleanment gain vs RPM |
| `CAL_injtip_out_rpm_scale_X_rpm` | `u8_rspeed_125/4+500rpm` | 16 | 40009b6a | 3516 | RPM breakpoints for above |
| `CAL_injtip_out_rpm_decay` | `u8_dt_factor_1/100/5ms` | 16 | 40009b9a | 3514 | Step size by which `tps_rate_transient` decays per divider tick (closing side) |
| `CAL_injtip_out_rpm_decay_X_rpm` | `u8_rspeed_125/4+500rpm` | 16 | 40009b8a | 3515 | RPM breakpoints for above |

### 4.6 Coolant Temperature Scale Tables (Closing)

| Calibration | Type | Size | ROM Addr | Line | What it controls |
|---|---|---|---|---|---|
| `CAL_injtip_out_coolant_scale` | `u8_factor_1/64` | 16 | 40009bba | 3519 | Enleanment gain vs coolant temp |
| `CAL_injtip_out_coolant_scale_X_coolant_temp` | `u8_temp_5/8-40c` | 16 | 40009baa | 3518 | Coolant temp breakpoints for above (note: mislabeled `_X_rpm` in disassembly) |

### 4.7 Rate Filter Tuning Constants (DAT_ variables — in ROM but not CAL_-named)

These act as calibration constants despite having Ghidra auto-generated names.

| Variable | Better Name | Type | Addr | Line | What it controls |
|---|---|---|---|---|---|
| `DAT_40008fa0` | `injtip_in_decay_divider` | `byte` | 40008fa0 | 1383 | Cycles before enrichment rate decrements one step. Higher = slower fade. |
| `DAT_40008fa1` | `injtip_out_decay_divider` | `byte` | 40008fa1 | 1382 | Cycles before enleanment rate increments one step. Higher = slower fade. |
| `DAT_40008fa6` | `tps_rate_closing_clamp` | `short` | 40008fa6 | 1385 | Hard clamp on negative `tps_rate_transient`. Limits max enleanment. |
| `DAT_40008fa8` | `tps_rate_closing_deadband` | `short` | 40008fa8 | 1384 | Minimum closing rate required to activate enleanment logic. |

### 4.8 DFCO Interaction Timers

| Calibration | Type | Size | ROM Addr | Line | What it controls |
|---|---|---|---|---|---|
| `CAL_injtip_overrun_inhibit_timer` | `u16_time_5ms` | 1 | 40008f08 | 3521 | How long to suppress DFCO fuel cut after an active injtip event |
| `CAL_injtip_overrun_hysteresis_timer` | `u16_time_5ms` | 1 | 40008f20 | 3522 | Hold-off timer preventing rapid DFCO on/off cycling |

---

## Part 5: Axis Decoding Reference

**RPM axis** (`u8_rspeed_125/4+500rpm`):  
`RPM = (value × 125 / 4) + 500`  
→ 0 = 500 RPM, 48 ≈ 2000 RPM, 120 ≈ 4250 RPM

**Coolant temp axis** (`u8_temp_5/8-40c`):  
`°C = (value × 5 / 8) − 40`  
→ 0 = −40°C, 64 = 0°C, 128 = 40°C, 200 ≈ 85°C

**Scaling types:**
- `u8_factor_1/128`: range [0, 1.99]. 128 = unity gain.
- `u8_factor_1/64`: range [0, 3.98]. 64 = unity gain.
- `u8_dt_factor_1/100/5ms`: decay step per 5ms tick = value / 100.
- `u16_factor_1/1023`: 16-bit [0, 1.0]. 1023 = full scale.

---

## Part 6: Complete 200 Hz Execution Flow

```
1.  Sample TPS into 16-entry circular buffer
2.  tps_rate_raw = buffer[0] − buffer[n]   (n = CAL_tps_delta_rate_window_size)
3.  Attack: if |tps_rate_raw| > threshold, tps_rate_transient jumps immediately
4.  Decay: cycle counter increments; every DAT_40008fa0 (open) or DAT_40008fa1 (close)
           cycles, tps_rate_transient steps toward zero by injtip_{in,out}_rpm_decay
5.  injtip() called:
    a. Select gear adjustment factor from CAL_injtip_in_adj_gears[]
    b. Lookup rpm_scale, rpm_decay, coolant_scale for both opening and closing
    c. If tps_rate_transient > 0: compute enrichment_pw using opening tables + gear adj
       If tps_rate_transient < 0: compute enleanment_pw using closing tables (no gear adj)
    d. Gate on engine_is_running and no misfire
6.  Final injection PW = base_fuel_pw + transient_enrichment_pw − transient_enleanment_pw
```

---

## Part 7: Variable Naming Suggestions

| Current Name | Better Name | Reason |
|---|---|---|
| `load_filtered1` | `fuel_film_load_state` | X-tau integrator state, not just "filtered load" |
| `load_selected_raw` | `load_before_xtau` | Clarifies it feeds the X-tau filter |
| `tps_delta_rate` | `tps_rate_raw` | Unfiltered; distinguishes from the filtered version |
| `tps_rate_filtered_for_ign_comp` | `tps_rate_transient` | Used for injtip AND ignition comp — `_for_ign_comp` is misleading |
| `injtip_decay_cycle_counter` | `tps_rate_decay_divider` | It's a cycle divider, not a simple counter |
| `injtip_in_enrichment_raw` | `accel_enrichment_pw_raw` | Makes clear it's a pulse-width delta in µs |
| `injtip_out_enleanment_raw` | `decel_enleanment_pw_raw` | Same |
| `inj_tip_adj_enrichment` | `transient_enrichment_pw` | Post-gating final value |
| `inj_tip_adj_enleanment` | `transient_enleanment_pw` | Same |
| `DAT_40008fa0` | `injtip_in_decay_divider` | Cycle count threshold for opening decay |
| `DAT_40008fa1` | `injtip_out_decay_divider` | Cycle count threshold for closing decay |
| `DAT_40008fa6` | `tps_rate_closing_clamp` | Hard floor on tps_rate_transient during closing |
| `DAT_40008fa8` | `tps_rate_closing_deadband` | Minimum closing rate to enter enleanment |
