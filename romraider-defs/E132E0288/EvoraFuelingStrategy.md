# Lotus Evora Fueling Strategy

This document describes the fuel control system implemented in the Lotus T6e ECU firmware (E132E0288). The system combines MAF-based speed-density and alpha-N load calculation methods with closed-loop feedback control, transient compensation, and X-Tau wall-wetting modeling.

## Table of Contents

1. [System Overview](#system-overview)
2. [Air Mass Measurement](#air-mass-measurement)
3. [Load Calculation & Alpha-N Mode](#load-calculation--alpha-n-mode)
4. [Fuel Delivery Calculation](#fuel-delivery-calculation)
5. [Closed-Loop Operation](#closed-loop-operation)
6. [Transient Compensation](#transient-compensation)
7. [X-Tau Wall-Wetting Model](#x-tau-wall-wetting-model)
8. [Knock Enrichment](#knock-enrichment)
9. [Deceleration Fuel Cut-Off](#deceleration-fuel-cut-off)
10. [Summary of Key Calibrations](#summary-of-key-calibrations)

---

## System Overview

The T6e ECU uses a multi-mode fueling strategy that adapts to engine operating conditions, transitioning seamlessly between MAF-based and alpha-N load calculation, open-loop and closed-loop control, and applying multiple compensations for transients and environmental factors.

### Control Flow

```
┌──────────────┐    ┌──────────────┐
│  MAF Sensor  │    │   TPS/RPM    │
│  (primary)   │    │  (alpha-N)   │
└──────┬───────┘    └──────┬───────┘
       │                   │
       ▼                   ▼
┌────────────────────────────────────┐
│    Load Source Selection Logic    │
│  (MAF vs Alpha-N based on mode)   │
└────────────────┬───────────────────┘
                 │
                 ▼
┌────────────────────────────────────┐
│   X-Tau Wall-Wetting Filter        │
│  load_filtered = f(load, α, X)     │
└────────────────┬───────────────────┘
                 │
          ┌──────┴──────┐
          ▼             ▼
    ┌─────────┐   ┌──────────┐
    │ AFR     │   │ Fuel     │
    │ Target  │   │ Mass     │
    │ Lookup  │   │ Required │
    └────┬────┘   └────┬─────┘
         │             │
         └──────┬──────┘
                ▼
┌────────────────────────────────────┐
│  Injector Pulse Width Calculation  │
│  • Flow rate vs pressure           │
│  • Dead time (voltage, pressure)   │
│  • Bank balance                    │
└────────────────┬───────────────────┘
                 │
          ┌──────┴──────┐
          ▼             ▼
    ┌──────────┐  ┌──────────┐
    │ Open-Loop│  │Closed-Loop│
    │ (Target) │  │ (O2 Trim) │
    └──────────┘  └──────────┘
          │             │
          └──────┬──────┘
                 │
          ┌──────┴──────────────┐
          │                     │
    ┌─────▼─────┐   ┌───────────▼─────┐
    │  Transient│   │     Knock       │
    │   Comp    │   │   Enrichment    │
    │ (tip-in/  │   │  (from retard)  │
    │  tip-out) │   │                 │
    └─────┬─────┘   └───────────┬─────┘
          │                     │
          └──────────┬──────────┘
                     ▼
          ┌─────────────────────┐
          │  Final Pulse Width  │
          └─────────────────────┘
```

### Key Components

| Component | Description |
|-----------|-------------|
| `obd_ii_maf_flow` | Primary MAF sensor reading (10 mg/s units) |
| `load_computed_alphaN` | Alpha-N calculated load (mg/stroke) |
| `load_mass_per_stroke_raw` | Final load after X-Tau filtering |
| `afr_target` | Target AFR from lookup table (0.01 AFR units) |
| `inj_flow_rate_scaled` | Injector flow rate with efficiency compensation |
| `fuel_flags_unknown` | Bitfield controlling closed-loop state |

---

## Air Mass Measurement

### MAF Sensor Configuration

The ECU uses dual hot-wire MAF sensors with 32-point voltage-to-airflow transfer functions.

**Function:** Line 14765, 21718-21723

```c
obd_ii_maf_flow = lookup_2D_uint16_interpolated(
    32, sensor_adc_maf1, CAL_sensor_maf_scaling,
    CAL_sensor_maf_scaling_X_signal);
```

| Parameter | Type | Description |
|-----------|------|-------------|
| `CAL_sensor_maf_scaling[32]` | u16_flow_10mg/s | Airflow output values |
| `CAL_sensor_maf_scaling_X_signal[32]` | u16_voltage_5/1023v | Voltage axis (0-5V) |
| `CAL_sensor_maf_buffer_size` | u8 | Averaging filter size |

**Signal Processing:**
- ADC values right-shifted 4 bits (`>> 4`) for 12-bit → voltage conversion
- Output in 10 mg/s units (e.g., 1000 = 10 g/s)
- Dual sensor comparison for fault detection (`maf_flow_difference`)

### Speed-Density (MAP-based)

When MAF unavailable, the ECU calculates load using ideal gas law and volumetric efficiency tables.

**Function:** Line 21702-21716

```c
// Ideal gas law: Mass = (P × V × η) / (R × T)
// R = 287 J/(kg·K) for dry air
load_computed_map =
    (efficiency × MAP × cylinder_volume) /
    ((manifold_temp + 233) × 2870);
```

| Parameter | Type | Description |
|-----------|------|-------------|
| `CAL_load_cylinder_efficiency[256]` | 16x16 | VE table (RPM × MAP) |
| `CAL_load_cylinder_volume` | u16_mass_mg | Cylinder displacement (690 mg) |
| `CAL_sensor_manifold_pressure_sensor_offset` | i16_pressure_mbar | MAP sensor offset |
| `CAL_sensor_manifold_pressure_sensor_scaling` | u16 | MAP scaling factor |

---

## Load Calculation & Alpha-N Mode

### Load Source Selection Logic

**Function:** Line 21881-21894

The ECU selects between MAF and alpha-N based on operating conditions:

```c
if (((engine_is_running == false) ||
     ((engine_state_failure_flags & 0x10) != 0)) ||
    ((DAT_40001d42 != 0) && (engine_speed_2 < threshold)))
{
    u32_load_mg_stroke_40001d0c = load_computed_alphaN + load_comp_idle;
    DAT_40001d4f = 1;  // Alpha-N mode
}
else {
    u32_load_mg_stroke_40001d0c = load_computed_maf + load_comp_idle;
    DAT_40001d4f = 0;  // MAF mode
}
```

### Alpha-N Activation Conditions

| Condition | Description |
|-----------|-------------|
| Engine not running | MAF unreliable during cranking/starting |
| MAF failure flag | `engine_state_failure_flags & 0x10` |
| High throttle rate | `tps_delta_rate` exceeds threshold |
| High TPS, low RPM | `tps2 > CAL_load_source_selection_threshold_by_tps` |
| Low RPM | Below MAF minimum reliable flow rate |

### Alpha-N Calculation

**Function:** Line 52737-52761, 21775-21809

```c
// Base lookup
load_alphaN_base = lookup_3D(20, 20, engine_speed, tps,
    CAL_load_alphaN_base, CAL_load_alphaN_base_X_engine_speed,
    CAL_load_alphaN_base_Y_tps);

// Apply learned trim
load_alphaN_adjustment_learned = lookup_3D(20, 20, engine_speed, tps,
    LEA_load_alphaN_learned_trim, ...);

// Density correction
if (CAL_sensor_manifold_temp_sensor_present == 0) {
    load_computed_alphaN = (learned_trim * _load_alphaN * air_density_ambiant) / 20000;
} else {
    load_computed_alphaN = (learned_trim * _load_alphaN * air_density_manifold_temp) / 20000;
}
```

**Key Calibrations:**

| Parameter | Type | Description |
|-----------|------|-------------|
| `CAL_load_alphaN_base[400]` | 20x20 | Base alpha-N table (RPM × TPS) |
| `LEA_load_alphaN_learned_trim[400]` | 20x20 | Adaptive trim table |
| `CAL_load_alphaN_seed[16]` | 1D | Initial estimate from TPS only |
| `CAL_load_source_selection_threshold_by_tps[16]` | 1D | TPS threshold for mode switch |
| `CAL_load_alphaN_use_tmap_density` | bool | Use manifold temp vs ambient |

---

## Fuel Delivery Calculation

### Pulse Width Calculation Flow

```
AFR Target → Fuel Mass Required → Injector Flow → Pulse Time
     ↓              ↓                    ↓              ↓
  20x20 table   Air/AFR ratio    Flow vs ΔP     Voltage comp
                                 Efficiency      Temperature
                                 Bank balance    Startup offset
```

### 1. Target AFR Lookup

**Function:** Line 16198-16204

```c
afr_base_lookup = lookup_3D(20, 20, engine_speed, load,
    CAL_inj_afr_base, CAL_inj_afr_base_X_engine_speed,
    CAL_inj_afr_base_Y_engine_load);

// Convert: stored as (AFR - 5) / 0.2
_afr_target = afr_base_lookup * 5 + afr_target_trim_0p02_steps * 2 + 500;
```

**Storage encoding:**
- Value 0 → 5.0 AFR
- Value 50 → 15.0 AFR
- Value 100 → 25.0 AFR

### 2. Fuel Mass Calculation

**Function:** Line 16308-16313

```c
afr_commanded = afr_target2 - afr_enrichment_from_ign_retard;
if (afr_commanded < 800) afr_commanded = 800;  // Min 8.0 AFR

_fuel_mass_required = (load_mass_per_stroke_raw * 10000) / afr_commanded;
```

### 3. Injector Characterization

**Function:** Line 16272-16287

```c
// Flow rate vs fuel pressure
inj_flow_rate = lookup_2D(8, fuel_pressure_manifold_relative,
    CAL_inj_flow_rate, CAL_inj_flow_rate_X_fuel_pressure);

// Efficiency compensation
inj_efficiency = lookup_3D(20, 20, engine_speed, load,
    CAL_inj_efficiency, ...);

inj_flow_rate_scaled = (inj_efficiency * inj_flow_rate) / 200;
```

### 4. Dead Time Compensation

**Function:** Line 16155-16172

```c
inj_time_base = lookup_3D(8, 8, ecu_voltage, fuel_pressure,
    CAL_inj_time_base, CAL_inj_time_base_X_car_voltage,
    CAL_inj_time_base_Y_fuel_pressure);

inj_comp_air_temp_iat = lookup_2D(8, temp_engine_air,
    CAL_inj_comp_iat, CAL_inj_comp_iat_X_iat);

inj_pulse_time_us_raw = (inj_time_base * 20 * inj_comp_air_temp_iat) / 100;
```

### 5. Bank Balance

**Function:** Line 16288-16307

```c
_inj_bank_balance = lookup_3D(20, 20, engine_speed, load,
    CAL_inj_bank_balance, ...);

// Split: 200 = 50/50 split, range 170-230 (±15%)
_inj_flow_b1_ = (inj_flow_rate_scaled * (400 - inj_split_unknown)) / 200;
_inj_flow_b2_ = (inj_flow_rate_scaled * inj_split_unknown) / 200;
```

### 6. Cold Start Enrichment

**Function:** Line 16337-16349

| Enrichment Type | Table Size | Description |
|----------------|------------|-------------|
| Warm-up | 12x16 (Load × Coolant) | Continuous during warm-up |
| Startup offset | 16 points | Initial pulse addition, decays with accumulated airflow |
| Cranking | 12x14 (Coolant × MAF accum) | During cranking only |
| Cold air startup | 4x4 (IAT × MAF accum) | Additional enrichment for cold intake air |
| Running air temp | 8x4 (Load × IAT) | Continuous IAT compensation |

---

## Closed-Loop Operation

### Entry and Exit Logic

**Function:** Line 16209-16233

```c
// Entry delay selection
if (load_pct > _inj_accel_enrichment_load_threshold) {
    closedloop_entry_delay_steps = CAL_closedloop_entry_delay_power_enrich;
} else {
    closedloop_entry_delay_steps = CAL_closedloop_entry_delay_time_cruise;
}

// State machine
if (_afr_target == CAL_closedloop_afr) {
    fuel_flags_unknown &= ~0b00000010;  // Maintain closed-loop
} else if ((timer < entry_delay) && !(fuel_flags_unknown & 1)) {
    fuel_flags_unknown |= 2;  // Transition to closed-loop
    afr_target2 = CAL_closedloop_afr;
}

// Power enrichment prevents closed-loop
if (afr_target2 < CAL_closedloop_afr) {
    fuel_flags_unknown |= 1;  // Power enrichment active
}
```

### Entry Conditions (ALL required)

| Condition | Parameter | Description |
|-----------|-----------|-------------|
| AFR match | `_afr_target == CAL_closedloop_afr` | Target must equal stoich (14.64) |
| Engine runtime | `CAL_closedloop_activate_engine_timer` | Indexed by coolant temp (16 points) |
| Coolant temp | `CAL_closedloop_fuel_learn_coolant_min` | Minimum warmup threshold |
| IAT | `CAL_closedloop_fuel_learn_iat_max` | Maximum intake air temp |
| Barometric | `CAL_closedloop_fuel_learn_baro_min` | Minimum barometric pressure |
| O2 valid range | `CAL_closedloop_o2_sensor_min/max_valid` | Sensor voltage window |
| Delay timer | Cruise or power delay | Prevents rapid cycling |
| Transient limits | `CAL_closedloop_max_tipin/tipout_enleanment` | Tip-in/out within limits |

### PID Control

**Function:** Line 25905-25921

The controller uses separate gains for rich and lean correction:

```c
// Lookup gains based on operating point
P_gain_rich = lookup_3D(8, 8, rpm, load,
    CAL_closedloop_proportional_gain_rich_table, ...);
P_gain_lean = lookup_3D(8, 8, rpm, load,
    CAL_closedloop_proportional_gain_lean_table, ...);
I_gain = lookup_3D(8, 8, rpm, load,
    CAL_closedloop_integral_gain_table, ...);
D_gain = lookup_3D(8, 8, rpm, load,
    CAL_closedloop_derivative_gain_table, ...);
```

### Fuel Trim Strategy

| Trim Type | Update Rate | Storage | Description |
|-----------|-------------|---------|-------------|
| STFT | `CAL_closedloop_stft_increment_period` | RAM | Rapid correction, resets on key cycle |
| LTFT | `CAL_fuel_learn_time_step` | EEPROM (`LEA_` tables) | Slow adaptation, survives key-off |

**STFT Limits:**
- Idle: `CAL_closedloop_stft_idle_max_limit`
- Off-idle: Separate rich/lean limits per operating point

---

## Transient Compensation

### Tip-In/Tip-Out Enrichment

**Function:** Line 21300-21350

Explicit compensation based on throttle rate of change, separate from X-Tau wall-wetting.

```c
// Tip-out (deceleration enleanment)
if (tps_transient_magnitude_decay < 0) {
    decel_enleanment___ = CAL_injtip_comp_base *
        (-tps_transient_magnitude_decay *
         ((injtip_comp_negative_load * injtip_comp_negative_rpm *
           injtip_comp_negative_temp) >> 8) >> 12);
}
// Tip-in (acceleration enrichment)
else {
    accel_enrichment___ = CAL_injtip_comp_base *
        ((tps_transient_magnitude_decay *
          ((injtip_comp_positive_load * inj_tip_in_adj_gear_current *
            injtip_comp_positive_rpm * injtip_comp_positive_temp) >> 16)) >> 11);
}
```

### Compensation Factors

| Factor | Table Size | Description |
|--------|------------|-------------|
| RPM (enrich) | 16 points | Higher at low RPM (slower response) |
| RPM (enlean) | 16 points | Higher at low RPM |
| Coolant (enrich) | 16 points | Higher when cold (more wall-wetting) |
| Coolant (enlean) | 16 points | Higher when cold |
| Load (enrich) | 16 points | Higher at low load (better mixing) |
| Load (enlean) | 16 points | Higher at low load |
| Gear adjustment | 6 values | Per-gear tip-in multiplier (1st gear highest) |

### Throttle Rate Processing

**Function:** Line 10489-10493

```c
lookup2_unknown = lookup_3D(8, 8, coolant_temp, engine_speed,
    CAL_injtip_transient_throttle_response_time,
    CAL_injtip_transient_throttle_response_time_X_coolant_tmp,
    CAL_injtip_transient_throttle_response_time_Y_rpm);
injtip_transient_throttle_response_time = lookup2_unknown;
```

The `tps_transient_magnitude_decay` signal is created by:
1. Calculating TPS delta over window (`CAL_tps_delta_rate_window_size`)
2. Filtering with time constant from `CAL_injtip_transient_throttle_response_time`
3. Applying threshold checks (`CAL_injtip_in_threshold` / `CAL_injtip_out_threshold`)

---

## X-Tau Wall-Wetting Model

### Theory

Fuel film dynamics on intake port walls:

```
        Injected Fuel
              │
         ┌────┴─────┐
         │          │
    (1-X)·M    X·M  │
         │          ▼
         │     ┌─────────┐
         │     │  Film   │
         │     │ M_film  │
         │     └────┬────┘
         │          │ α·M_film
         ▼          ▼
    ┌────────────────────┐
    │  To Cylinder       │
    │  (1-X)·M + α·M     │
    └────────────────────┘
```

**Parameters:**
- **X (Chi)**: Fraction entering film (0-1)
- **α (Alpha)**: Evaporation rate = 1/τ
- **τ (Tau)**: Time constant

**Differential equation:**
```
dM_film/dt = X·M_injected - α·M_film
M_cylinder = (1-X)·M_injected + α·M_film
```

### Implementation

**Function:** Line 10343-10413

```c
// Calculate X-factor from load change
_load_unknown = u32_load_mg_stroke_40001d0c - load_mass_per_stroke_raw;
_load_for_xtau = clamp_and_scale(_load_unknown, -508, 513);

fuel_film_X_factor = lookup_2D(16, _load_for_xtau,
    CAL_injtip_fuel_film_X_factor,
    CAL_injtip_fuel_film_X_factor_X_load);

// Select alpha based on direction
if (load_filtered1 < u32_load_mg_stroke_40001d0c) {
    // Load increasing → faster response
    load_filter_alpha_xtau = lookup_2D(8, load_mass_per_time / 200,
        CAL_injtip_fuel_film_alpha_inc, ...);
} else {
    // Load decreasing → slower response
    load_filter_alpha_xtau = lookup_2D(8, load_mass_per_time / 200,
        CAL_injtip_fuel_film_alpha_dec, ...);
}

// Combine and filter
inj_fuel_fillm_xtau_coeff_combined = (fuel_film_X_factor * load_filter_alpha_xtau) / 0xff;
load_filtered1 = ((256 - coeff) * load_filtered1 + coeff * u32_load_mg_stroke_40001d0c) >> 8;
load_mass_per_stroke_raw = load_filtered1 >> 8;
```

### Calibration Strategy

| Parameter | Typical Range | Description |
|-----------|---------------|-------------|
| X-factor | 0.1 - 0.5 (26-128) | Higher at large load changes |
| Alpha (increasing) | 0.2 - 0.8 (51-204) | Faster response for tip-in |
| Alpha (decreasing) | 0.05 - 0.3 (13-77) | Slower response for tip-out |

**Physical interpretation:**
- High X → more fuel sticks to walls during tip-in
- High α → faster film evaporation, quicker response
- Asymmetry (α_inc > α_dec) → faster enrichment than enleanment

---

## Knock Enrichment

When knock control retards ignition timing, fuel enrichment provides cylinder cooling.

**Function:** Line 16234-16253

```c
if (afr_target2 < CAL_closedloop_afr) {  // Power enrichment mode only
    excess_retard = (knock_ign_retard_cyl0 / 6) -
                    ign_rpm_and_coolant_comp -
                    ign_comp_iat;

    if (excess_retard > 0) {
        afr_enrichment_from_ign_retard =
            min(255, (CAL_inj_comp_power_enrich_from_ign_retard *
                     excess_retard) >> 2);
    }
}

afr_commanded = afr_target2 - afr_enrichment_from_ign_retard;
if (afr_commanded < 800) afr_commanded = 800;  // 8.0 AFR minimum
```

**Key Points:**
- Only active during power enrichment (AFR < stoich)
- Proportional to "excess" retard above baseline compensations
- Uses bank-average knock retard (cylinder 0 value / 6)
- Gain typical: 10-30 → ~0.02 AFR per 0.25° retard
- Works with ignition retard, not as replacement

---

## Deceleration Fuel Cut-Off

**Function:** Line 21352-21384

DFCO stops injection during closed-throttle deceleration for fuel economy and emissions.

### Activation Conditions (ALL required)

| Condition | Parameter | Typical Value |
|-----------|-----------|---------------|
| Engine speed | `CAL_injtip_dfco_enable_rpm_[ips/manual]_[gear]` | 1500-2500 RPM (gear/temp dependent) |
| Vehicle speed | `CAL_injtip_dfco_enable_speed` | 15-25 km/h |
| Throttle | `CAL_injtip_dfco_enable_accel_pedal` | < 5-10% |
| Coolant temp | `CAL_injtip_dfco_enable_temp` | > 40-60°C |
| No faults | `misfire_condition_flags` check | No misfire/critical faults |

**Gear-specific RPM thresholds:**
- 1st gear: Higher threshold (maintain smoothness)
- 2nd-6th gear: Lower threshold (maximize fuel saving)

### Exit Conditions (ANY triggers)

1. RPM drops below threshold - hysteresis (200-400 RPM)
2. Throttle opens above threshold
3. Vehicle speed too low
4. Coolant temp drops
5. IPS transmission downshift initiated

**Hysteresis timers:**
- `CAL_injtip_overrun_inhibit_timer`: Minimum time between DFCO events
- `CAL_injtip_overrun_hysteresis_timer`: Re-enable delay after exit

---

## Summary of Key Calibrations

### Air Metering & Load Calculation

| Parameter | Type | Description | Line |
|-----------|------|-------------|------|
| `CAL_sensor_maf_scaling[32]` | u16_flow_10mg/s | MAF transfer function | 2046 |
| `CAL_sensor_maf_scaling_X_signal[32]` | u16_voltage_5/1023v | MAF voltage axis | 2048 |
| `CAL_load_alphaN_base[400]` | 20x20 u8 | Alpha-N base table | 52739 |
| `LEA_load_alphaN_learned_trim[400]` | 20x20 u8 | Alpha-N adaptive trim | 21764 |
| `CAL_load_cylinder_efficiency[256]` | 16x16 u32 | VE for speed-density | 21704 |
| `CAL_load_source_selection_threshold_by_tps[16]` | 1D u8 | Alpha-N activation threshold | 21773 |
| `CAL_ecu_2gr_cylinder_air_mass_mg` | u16 | Reference cylinder mass (690) | 3373 |

### Target AFR & Fuel Mass

| Parameter | Type | Description | Line |
|-----------|------|-------------|------|
| `CAL_inj_afr_base[400]` | 20x20 u8_afr_1/20+5 | Target AFR map | 2390 |
| `CAL_inj_afr_base_X_engine_speed[20]` | u8_rspeed | RPM axis | 2391 |
| `CAL_inj_afr_base_Y_engine_load[20]` | u8_load | Load axis | 2393 |

### Injector Characterization

| Parameter | Type | Description | Line |
|-----------|------|-------------|------|
| `CAL_inj_flow_rate[8]` | u16_flow_mg_s | Flow vs fuel pressure | 16274 |
| `CAL_inj_flow_rate_X_fuel_pressure[8]` | u16_pressure_mbar | Pressure axis | - |
| `CAL_inj_efficiency[400]` | 20x20 u8_factor_1/200 | VE compensation | 2397 |
| `CAL_inj_time_base[64]` | 8x8 u8 | Dead time (V × P) | 16158 |
| `CAL_inj_comp_iat[8]` | 1D u8_factor_1/255 | IAT compensation | 16162 |
| `CAL_inj_bank_balance[400]` | 20x20 u8 | Bank balance (200 = 50/50) | 16290 |

### Closed-Loop Control

| Parameter | Type | Description | Line |
|-----------|------|-------------|------|
| `CAL_closedloop_afr` | u16_afr_1/100 | Target AFR (1464 = 14.64) | 2384 |
| `CAL_closedloop_entry_delay_time_cruise` | u8_time_ms | Entry delay cruise | 2375 |
| `CAL_closedloop_entry_delay_power_enrich` | u8_time_ms | Entry delay power | 2376 |
| `CAL_closedloop_proportional_gain_rich_table[64]` | 8x8 u8_factor | P-gain rich | 3960 |
| `CAL_closedloop_proportional_gain_lean_table[64]` | 8x8 u8_factor | P-gain lean | 3962 |
| `CAL_closedloop_integral_gain_table[64]` | 8x8 u8_factor | I-gain | 961 |
| `CAL_closedloop_derivative_gain_table[64]` | 8x8 u8_factor | D-gain | 3965 |
| `CAL_closedloop_activate_engine_timer[16]` | 1D u8_time_s | Runtime req by temp | 3973 |
| `CAL_closedloop_o2_sensor_min_valid` | u16_voltage | Min O2 voltage | 3945 |
| `CAL_closedloop_o2_sensor_max_valid` | u16_voltage | Max O2 voltage | 3944 |
| `CAL_closedloop_stft_increment_period` | u8_time_5ms | STFT update rate | 3943 |
| `CAL_fuel_learn_time_step` | u8 | LTFT learning rate | 2372 |

### X-Tau Wall-Wetting

| Parameter | Type | Description | Line |
|-----------|------|-------------|------|
| `CAL_injtip_fuel_film_X_factor[16]` | 1D u8_factor_1/255 | X-factor vs load delta | 1405 |
| `CAL_injtip_fuel_film_X_factor_X_load[16]` | 1D u8_load | Load delta axis | - |
| `CAL_injtip_fuel_film_alpha_inc[8]` | 1D u8_factor_1/255 | Alpha (increasing load) | 1326 |
| `CAL_injtip_fuel_film_alpha_inc_X_mass_per_time[8]` | 1D u8 | Load rate axis | 1330 |
| `CAL_injtip_fuel_film_alpha_dec[8]` | 1D u8_factor_1/255 | Alpha (decreasing load) | 1328 |
| `CAL_injtip_fuel_film_alpha_dec_X_mass_per_time[8]` | 1D u8 | Load rate axis | 1332 |

### Transient Compensation

| Parameter | Type | Description | Line |
|-----------|------|-------------|------|
| `CAL_injtip_comp_base` | u8 | Base multiplier | 21323 |
| `CAL_injtip_comp_rpm1[16]` | 1D u8_factor | RPM enrich | 21298 |
| `CAL_injtip_comp_temp1[16]` | 1D u8_factor | Coolant enrich | 21301 |
| `CAL_injtip_comp_load1[16]` | 1D u8_factor | Load enrich | 21304 |
| `CAL_injtip_comp_negative_rpm[16]` | 1D u8_factor | RPM enlean | 21310 |
| `CAL_injtip_comp_negative_temp[16]` | 1D u8_factor | Coolant enlean | 21314 |
| `CAL_injtip_comp_negative_load[16]` | 1D u8_factor | Load enlean | 21318 |
| `CAL_injtip_in_adj_gears[6]` | 1D u8 | Per-gear tip-in | 2356 |
| `CAL_injtip_transient_throttle_response_time[64]` | 8x8 u8_time_5ms | Filter time constant | 1377 |
| `CAL_closedloop_max_tipin_enrichment` | u8_time_10us | CL tip-in limit | 3937 |
| `CAL_closedloop_max_tipout_enleanment` | u8_time_10us | CL tip-out limit | 3938 |

### Knock Enrichment

| Parameter | Type | Description | Line |
|-----------|------|-------------|------|
| `CAL_inj_comp_power_enrich_from_ign_retard` | u8_factor_1/100 | Enrichment gain | 2377 |

### DFCO

| Parameter | Type | Description | Line |
|-----------|------|-------------|------|
| `CAL_injtip_dfco_enable_speed` | u8_speed_kph | Min vehicle speed | 3276 |
| `CAL_injtip_dfco_enable_temp` | u8_temp | Min coolant temp | 3255 |
| `CAL_injtip_dfco_enable_accel_pedal` | u8_factor_1/1023 | Max pedal position | 3257 |
| `CAL_injtip_dfco_enable_rpm_ips_default[4]` | 1D u8_rspeed_10rpm | RPM threshold IPS | 3261 |
| `CAL_injtip_dfco_enable_rpm_manual_default[4]` | 1D u8_rspeed_10rpm | RPM threshold manual | 3262 |
| `CAL_injtip_dfco_enable_rpm_ips_firstgear[4]` | 1D u8_rspeed_50rpm | RPM 1st gear IPS | 3258 |
| `CAL_injtip_overrun_inhibit_timer` | u8_time | Min time between DFCO | 1375 |
| `CAL_injtip_overrun_hysteresis_timer` | u8_time | Re-enable delay | 1372 |

### Cold Start & Warm-Up

| Parameter | Type | Description | Line |
|-----------|------|-------------|------|
| `CAL_inj_enrichment_factor_load_n_coolant_ips[192]` | 12x16 u8_factor | IPS warm-up | 2381 |
| `CAL_inj_enrichment_factor_load_n_coolant_manual[192]` | 12x16 u8_factor | Manual warm-up | 2386 |
| `CAL_inj_startup_enrichment_offset[16]` | 1D u8 | Startup pulse offset | 16191 |
| `CAL_inj_cranking_enrichment_coolant_ips[168]` | 12x14 u16_factor | Cranking IPS | 2383 |
| `CAL_inj_cranking_enrichment_coolant_manual[168]` | 12x14 u16_factor | Cranking manual | 2386 |
| `CAL_inj_comp_air_temp_startup[16]` | 4x4 u8_factor | Cold air startup | 2378 |
| `CAL_inj_comp_air_temp2[64]` | 8x8 u8_factor | Running air comp | 2390 |

---

**Document Version:** 1.0
**Date:** 2025-01-24
**Firmware:** E132E0288
