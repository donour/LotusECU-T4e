# Lotus T6e Torque Control System

This document describes the torque estimation and control system in the Lotus T6e ECU firmware (E132E0288).

## Overview

The T6e torque control system provides:
- **Torque estimation** from engine load and speed
- **External torque limiting** via CAN (ABS/ESP, cruise control, TCU)
- **Internal torque limiting** (temperature, engine speed, misfire protection)
- **Throttle position control** to achieve torque targets
- **Learned (LEA) adaptation** for TPS-to-load and load-to-TPS mapping

## System Architecture

```
+-----------------------------------------------------------------------------------+
|                                INPUTS                                              |
+-----------------------------------------------------------------------------------+
| Engine Speed | Throttle Pos | Coolant Temp | Air Density | Knock Retard | Gear   |
+------+-------+------+-------+------+-------+------+------+------+-------+----+---+
       |              |              |              |              |           |
       v              v              v              v              v           v
+-----------------------------------------------------------------------------------+
|                           TORQUE ESTIMATION                                        |
|                          torque_model()                                            |
+-----------------------------------------------------------------------------------+
|                                                                                    |
|  +------------------+     +-------------------+     +-------------------+          |
|  | Alpha-N Load     |     | Load-to-Torque    |     | Friction Torque   |          |
|  | Estimation       |---->| Lookup            |---->| Compensation      |          |
|  | (TPS + RPM)      |     | CAL_torque_       |     | (speed, temp, AC) |          |
|  +------------------+     | load_to_torque    |     +-------------------+          |
|          |                +-------------------+              |                     |
|          v                        |                          v                     |
|  +------------------+             |              +-------------------+             |
|  | LEA Learning     |             |              | Net Engine Torque |             |
|  | Trim Adjustment  |             |              | obd_ii_engine_    |             |
|  +------------------+             |              | torque            |             |
|                                   v              +-------------------+             |
+-----------------------------------+------------------------------------------------+
                                    |
                                    v
+-----------------------------------------------------------------------------------+
|                           TORQUE LIMITING                                          |
+-----------------------------------------------------------------------------------+
|                                                                                    |
|   +-----------------+   +-----------------+   +-----------------+                  |
|   | External Limits |   | Internal Limits |   | Engine          |                  |
|   | (CAN Requests)  |   | (Protection)    |   | Protection      |                  |
|   +-----------------+   +-----------------+   +-----------------+                  |
|   | - ABS/ESP       |   | - Coolant temp  |   | - Cylinder      |                  |
|   | - Cruise ctrl   |   | - Engine speed  |   |   failure       |                  |
|   | - TCU (IPS)     |   | - Misfire       |   | - Knock retard  |                  |
|   +-----------------+   +-----------------+   +-----------------+                  |
|          |                     |                     |                             |
|          +----------+----------+----------+----------+                             |
|                     |                                                              |
|                     v                                                              |
|           +-------------------+                                                    |
|           | Minimum Selection |                                                    |
|           | torque_limit_     |                                                    |
|           | external_and_     |                                                    |
|           | internal          |                                                    |
|           +-------------------+                                                    |
|                     |                                                              |
+---------------------+--------------------------------------------------------------+
                      |
                      v
+-----------------------------------------------------------------------------------+
|                        THROTTLE CONTROL                                            |
|                  throttle_and_torque_control()                                     |
+-----------------------------------------------------------------------------------+
|                                                                                    |
|  +------------------+     +-------------------+     +-------------------+          |
|  | Torque-to-Load   |     | Load-to-TPS       |     | PI Controller     |          |
|  | Lookup           |---->| Lookup            |---->| (Closed Loop)     |          |
|  | CAL_torque_      |     | CAL_load_to_tps_  |     | tps_apply_        |          |
|  | torque_to_load   |     | mapping + LEA     |     | torque_limit      |          |
|  +------------------+     +-------------------+     +-------------------+          |
|                                   |                         |                      |
|                                   v                         v                      |
|                          +-------------------+     +-------------------+           |
|                          | TPS Smoothing     |     | tps_commanded_    |           |
|                          | & Rate Limiting   |---->| after_limits      |           |
|                          +-------------------+     +-------------------+           |
|                                                                                    |
+-----------------------------------------------------------------------------------+
```

## Torque Estimation

### Alpha-N Load Model

The engine load is estimated from throttle position and engine speed using the Alpha-N model:

```
1. Base Load Lookup:
   load_alphaN_lookup = CAL_load_alphaN_base[engine_speed, tps]

2. Convert to mg/stroke:
   load_estimated_alphaN = (load_alphaN_lookup * 1173) / 255

3. Apply Learned Trim:
   load_adjustment = LEA_load_alphaN_learned_trim[engine_speed, tps]

4. Apply Air Density Correction:
   load_learned_alphaN = (load_adjustment * load_estimated * air_density) / 20000
```

### Load-to-Torque Conversion

```
torque_estimated = CAL_torque_load_to_torque[engine_speed, load]
```

This 16x16 table converts air mass (mg/stroke) to estimated torque (Nm).

### Friction Torque Compensation

Total friction is the sum of three components:

```
                    +-------------------+
                    | Engine Friction   |
                    | Components        |
                    +-------------------+
                            |
        +-------------------+-------------------+
        |                   |                   |
        v                   v                   v
+---------------+   +---------------+   +---------------+
| Speed-Based   |   | Temp-Based    |   | AC Compressor |
| Friction      |   | Friction      |   | Load          |
+---------------+   +---------------+   +---------------+
| CAL_torque_   |   | CAL_torque_   |   | CAL_torque_   |
| engine_       |   | engine_       |   | engine_       |
| friction_     |   | friction_     |   | ac_load_base  |
| speed_        |   | temp_         |   +---------------+
| component     |   | component     |           |
+---------------+   +---------------+           |
        |                   |                   |
        +-------------------+-------------------+
                            |
                            v
                +---------------------+
                | engine_friction_    |
                | torque (negative)   |
                +---------------------+
```

### Net Engine Torque Calculation

```c
// Actual torque from combustion
obd_ii_engine_torque = (torque_fact_base * torque_estimated * active_cylinders) / (255 * 6)

// Net torque available at crankshaft
torque_calc_net = obd_ii_engine_torque + engine_friction_torque
```

The `torque_fact_base` accounts for ignition timing efficiency relative to MBT.

## External Torque Requests

Torque limiting can be triggered by external CAN requests or internal ECU functions.

### Request Sources

| Source | Origin | Priority | Description |
|--------|--------|----------|-------------|
| ABS/ESP | CAN 0xB7 | High | Stability control intervention |
| Cruise Control | Internal ECU | Medium | Speed maintenance (calculated internally) |
| TCU (IPS) | CAN | Medium | Shift torque management |

### Request Flags (trqlimit_external_request_flags___)

| Bit | Value | Source |
|-----|-------|--------|
| 0 | 0x01 | Cruise control active (internal) |
| 1 | 0x02 | ABS/ESP active (CAN 0xB7) |
| 2 | 0x04 | TCU request active |
| 3 | 0x08 | TCU torque cut |
| 4 | 0x10 | Fast torque reduction mode |

### Torque Request Update Flow

```
trqlimit_flexcan_update()
        |
        v
+-------------------+     +-------------------+     +-------------------+
| Check COD Config  |     | Check CAN Flags   |     | Check Message     |
| (ABS enabled?)    |---->| (Valid request?)  |---->| Type (7-byte?)    |
+-------------------+     +-------------------+     +-------------------+
        |                         |                         |
        v                         v                         v
+-----------------------------------------------------------------------+
|                    Request Priority Arbitration                        |
|   1. ABS/ESP (torque_limit_external_req2) - CAN 0xB7 - Highest        |
|   2. Cruise (torque_limit_external_req1) - Internal ECU               |
|   3. Cruise TPS (torque_limit_external_req3) - Internal ECU           |
|   4. TCU (u16_torque_nm_4000173c) - IPS CAN                           |
+-----------------------------------------------------------------------+
        |
        v
+-------------------+
| torque_limit_     |
| intermediate_ign_ | (for ignition-based limiting)
| intermediate_tps_ | (for throttle-based limiting)
+-------------------+
```

### Cruise Control (Internal)

Cruise control torque requests are calculated internally by the ECU, not received via CAN:

```c
// Cruise torque is computed from driver request and cruise target
torque_cruise_request = f(cruise_speed_target, vehicle_speed, accel_pedal)

// Applied when cruise is active and driver isn't overriding
if (torque_cruise_request < torque_alphaN_net):
    torque_limit = torque_cruise_request
```

## Internal Torque Limits

### Temperature-Based Limiting

```c
torque_limit_coolant_temp = CAL_torque_limit_by_coolant[coolant_temp]
torque_limit_temp = torque_limit_coolant_temp * 2  // Scale to Nm
```

### Engine Speed-Based Limiting

Different tables for IPS and manual transmissions:

```c
if (transmission == IPS):
    torque_limit_engine_speed = CAL_torque_limit_by_engine_speed_ips[engine_speed] * 2
else:
    torque_limit_engine_speed = CAL_torque_limit_by_engine_speed_manual[engine_speed] * 2
```

### Cylinder Failure Protection

When cylinders fail (coil/misfire), torque is reduced:

```c
torque_limit_engine_protection =
    (torque_driver_net_clamped + torque_loss_from_ign_retard) * 6 / (6 - failed_cylinder_count)
```

### Final Internal Limit

```c
torque_limit = min(torque_limit_temp, torque_limit_engine_speed)
```

## Throttle Position Control

### Torque-to-TPS Conversion Path

```
torque_limit_external_and_internal
            |
            v
    +-------------------+
    | Torque-to-Load    |
    | CAL_torque_       |
    | torque_to_load    |
    +-------------------+
            |
            v
    +-------------------+
    | Air Density       |
    | Compensation      |
    | / air_density     |
    +-------------------+
            |
            v
load_target_with_torque_limit
            |
            +------------------+
            |                  |
            v                  v
    +---------------+  +---------------+
    | Calibration   |  | Learned (LEA) |
    | Load-to-TPS   |  | Load-to-TPS   |
    | CAL_load_to_  |  | LEA_torque_   |
    | tps_mapping   |  | torque_to_    |
    +---------------+  | tps_scaling   |
            |          +---------------+
            |                  |
            +--------+---------+
                     |
                     v
            +-------------------+
            | Combined TPS      |
            | (CAL * LEA / 100) |
            | torque_limit_     |
            | tps_current       |
            +-------------------+
```

### PI Controller (tps_apply_torque_limit)

A closed-loop PI controller adjusts TPS to achieve the target load:

```
                    +-------------------+
                    | Load Error        |
                    | target - actual   |
                    +-------------------+
                            |
            +---------------+---------------+
            |                               |
            v                               v
    +---------------+               +---------------+
    | Proportional  |               | Integral      |
    | Gain Lookup   |               | Gain Lookup   |
    | CAL_torque_   |               | CAL_torque_   |
    | limit_        |               | limit_        |
    | proportional  |               | integral      |
    +---------------+               +---------------+
            |                               |
            v                               v
    +---------------+               +---------------+
    | P Correction  |               | I Correction  |
    | error * gain  |               | sum(error *   |
    | / 16          |               | gain / 16)    |
    +---------------+               +---------------+
            |                               |
            +---------------+---------------+
                            |
                            v
                    +-------------------+
                    | TPS Correction    |
                    | P + I + base_tps  |
                    +-------------------+
                            |
                            v
                    +-------------------+
                    | Low-Pass Filter   |
                    | (rate limiting)   |
                    +-------------------+
                            |
                            v
                    tps_after_torque_limit
```

### TPS Smoothing

The final TPS command is smoothed to prevent harsh throttle movements:

```
Smoothing Modes:
- Increment (opening): Controlled by CAL_tpssmooth_increment_*
- Decrement (closing): Controlled by CAL_tpssmooth_decrement_*
- Parking (clutch engaged): CAL_tpssmooth_increment_parking

Smoothing factors vary by:
- Engine speed
- TPS delta rate
- Current gear
- Vehicle mode (Tour/Sport)
```

## Learned (LEA) Tables

### LEA_load_alphaN_learned_trim

**Purpose**: Corrects the Alpha-N load model based on actual vs. predicted load.

**Structure**:
- Size: 20x20 (400 cells)
- X-axis: `LEA_load_alphaN_learned_trim_X_rpm` (engine speed)
- Y-axis: `LEA_load_alphaN_learned_trim_Y_tps` (throttle position)
- Values: Scaling factor (100 = 1.0x, range ~0-200)

**Initialization**:
```c
// X-axis copied from calibration
LEA_load_alphaN_learned_trim_X_rpm = CAL_load_alphaN_base_X_engine_speed

// Table values initialized to 100 (1.0x multiplier)
LEA_load_alphaN_learned_trim[all] = 100
```

**Update Conditions**:
- Steady-state operation (low TPS rate)
- No external torque requests
- No ABS/ESP intervention
- VVT at target

### LEA_torque_torque_to_tps_scaling

**Purpose**: Adapts the load-to-TPS mapping for manufacturing variations and aging.

**Structure**:
- Size: 20x20 (400 cells)
- X-axis: `LEA_torque_torque_to_tps_scaling_X_engine_speed`
- Y-axis: `LEA_torque_torque_to_tps_scaling_Y_load`
- Values: Scaling factor (100 = 1.0x)

**Usage**:
```c
// Lookup from both calibration and learned tables
tps_from_cal = CAL_load_to_tps_mapping[rpm, load]
tps_from_lea = LEA_torque_torque_to_tps_scaling[rpm, load]

// Combined result
tps_final = (tps_from_cal * tps_from_lea) / 100
```

**Learning Bounds**:
```c
// Axis values bounded by calibration
if (LEA_axis_value > CAL_torque_torque_to_tps_scaling_rpm_range[1]):
    LEA_axis_value--  // Decrease toward bound
else if (LEA_axis_value < CAL_torque_torque_to_tps_scaling_rpm_range[0]):
    LEA_axis_value++  // Increase toward bound
```

---

## Calibration Variables Reference

### Load Estimation

| Variable | Type | Description |
|----------|------|-------------|
| `CAL_load_alphaN_base` | u8[400] | Base Alpha-N load table (20x20) |
| `CAL_load_alphaN_base_X_engine_speed` | u8[20] | X-axis: Engine speed |
| `CAL_load_alphaN_base_Y_tps` | u8[20] | Y-axis: Throttle position |
| `CAL_load_alphaN_use_tmap_density` | bool | Use manifold temp for density |

### Torque Estimation

| Variable | Type | Description |
|----------|------|-------------|
| `CAL_torque_load_to_torque` | u16[256] | Load to torque table (16x16) |
| `CAL_torque_load_to_torque_X_engine_speed` | u16[16] | X-axis: Engine speed |
| `CAL_torque_load_to_torque_Y_load` | u16[16] | Y-axis: Load (mg/stroke) |

### Friction Compensation

| Variable | Type | Description |
|----------|------|-------------|
| `CAL_torque_engine_friction_speed_component` | u8[400] | Speed-based friction (20x20) |
| `CAL_torque_engine_friction_speed_component_X_engine_speed` | u8[20] | X-axis: Engine speed |
| `CAL_torque_engine_friction_speed_component_Y_load` | u8[20] | Y-axis: Load |
| `CAL_torque_engine_friction_temp_component` | u8[64] | Temp-based friction (8x8) |
| `CAL_torque_engine_friction_temp_component_X_coolant` | u8[8] | X-axis: Coolant temp |
| `CAL_torque_engine_friction_temp_component_Y_load` | u8[8] | Y-axis: Load |
| `CAL_torque_engine_ac_load_base` | u8[16] | AC compressor load |
| `CAL_torque_engine_ac_load_scaler` | u8[8] | AC load scaling by RPM |

### Torque-to-Load Conversion

| Variable | Type | Description |
|----------|------|-------------|
| `CAL_torque_torque_to_load` | u16[256] | Torque to load table (16x16) |
| `CAL_torque_torque_to_load_X_engine_speed` | u16[16] | X-axis: Engine speed |
| `CAL_torque_torque_to_load_Y_torque` | u16[16] | Y-axis: Torque (Nm) |

### External Request Handling

| Variable | Type | Description |
|----------|------|-------------|
| `CAL_torque_external_request_minimum` | u8[256] | Minimum torque margin (16x16) |
| `CAL_torque_external_request_minimum_X_engine_speed` | u8[16] | X-axis: Engine speed |
| `CAL_torque_external_request_minimum_Y_torque` | u8[16] | Y-axis: Requested torque |

### Ignition Intervention

| Variable | Type | Description |
|----------|------|-------------|
| `CAL_torque_ign_retard_base` | u8[256] | Base ignition retard for torque reduction |
| `CAL_torque_ign_retard_base_X_engine_speed` | u8[16] | X-axis: Engine speed |
| `CAL_torque_ign_retard_base_Y_torque_reduction_factor` | u8[16] | Y-axis: Reduction factor |
| `CAL_torque_factor_base_ign_intervention` | u8[256] | Torque factor from ignition |
| `CAL_torque_factor_base_ign_intervention_X_engine_speed` | u8[16] | X-axis: Engine speed |
| `CAL_torque_factor_base_ign_intervention_Y_ign_adv` | u8[16] | Y-axis: Ignition advance |

### Torque Limiting

| Variable | Type | Description |
|----------|------|-------------|
| `CAL_torque_limit_by_coolant` | u8[4] | Torque limit by coolant temp |
| `CAL_torque_limit_by_coolant_X_coolant` | u8[4] | X-axis: Coolant temp |
| `CAL_torque_limit_by_engine_speed_manual` | u8[8] | Torque limit by RPM (manual) |
| `CAL_torque_limit_by_engine_speed_manual_X_engine_speed` | u8[8] | X-axis: Engine speed |
| `CAL_torque_limit_by_engine_speed_ips` | u8[8] | Torque limit by RPM (IPS) |
| `CAL_torque_limit_by_engine_speed_ips_X_engine_speed` | u8[8] | X-axis: Engine speed |
| `CAL_torque_limit_base_factor` | u8[256] | Base limit factor (16x16) |
| `CAL_torque_factor_base_engine_speed_load` | u8[256] | Speed/load factor (16x16) |

### PI Controller

| Variable | Type | Description |
|----------|------|-------------|
| `CAL_torque_limit_proportional` | u8[8] | P-gain by error |
| `CAL_torque_limit_proportional_X_load_error` | u8[8] | X-axis: Load error |
| `CAL_torque_proportional_limit_positive` | u16 | Max positive P correction |
| `CAL_torque_proportional_limit_negative` | u16 | Max negative P correction |
| `CAL_torque_limit_integral` | u8[8] | I-gain by error |
| `CAL_torque_limit_integral_X_load_error` | u8[8] | X-axis: Load error |
| `CAL_torque_unknown_tps_clamp3` | u16 | Max positive I correction |
| `CAL_torque_unknown_tps_clamp4` | u16 | Max negative I correction |

### Load-to-TPS Mapping

| Variable | Type | Description |
|----------|------|-------------|
| `CAL_load_to_tps_mapping` | u8[400] | Load to TPS table (20x20) |
| `CAL_load_to_tps_mapping_X_rpm` | u8[20] | X-axis: Engine speed |
| `CAL_load_to_tps_mapping_Y_load` | u8[20] | Y-axis: Load |
| `CAL_torque_torque_to_tps_scaling_rpm_range` | u8[2] | LEA learning bounds [min, max] |

### Miscellaneous

| Variable | Type | Description |
|----------|------|-------------|
| `CAL_torque_hysteresis_threshold1` | u8 | Hysteresis for torque transitions |
| `CAL_revlimit_torque_limit_confirmation_threshold` | u8 | Rev limit torque confirm (×2 Nm) |

---

## Runtime Variables Reference

### Torque Values

| Variable | Type | Description |
|----------|------|-------------|
| `obd_ii_engine_torque` | i16 | Estimated engine torque (Nm) |
| `torque_net_engine_combustion` | i16 | Net combustion torque |
| `torque_estimated_alphaN` | u16 | Torque from Alpha-N model |
| `torque_estimated_actual_load` | i16 | Torque from actual load |
| `torque_alphaN_net` | u16 | Alpha-N torque with friction |
| `engine_friction_torque` | i16 | Total friction torque (negative) |

### Load Values

| Variable | Type | Description |
|----------|------|-------------|
| `load_estimated_alphaN` | u16 | Alpha-N estimated load |
| `load_learned_alphaN` | u16 | Learned-corrected Alpha-N load |
| `load_target_with_torque_limit` | u16 | Target load for TPS control |
| `load_from_torque_adjusted` | u16 | Load calculated from torque target |

### External Limits

| Variable | Type | Description |
|----------|------|-------------|
| `torque_limit_external_req1` | u16 | CAN request 1 (cruise) |
| `torque_limit_external_req2` | u16 | CAN request 2 (ABS/ESP) |
| `torque_limit_external_req3` | u16 | CAN request 3 (cruise TPS) |
| `torque_limit_intermediate_ign_` | u16 | Selected external limit (ign) |
| `torque_limit_intermediate_tps_` | u16 | Selected external limit (tps) |
| `torque_limit_external_net` | u16 | Final external net limit |

### Internal Limits

| Variable | Type | Description |
|----------|------|-------------|
| `torque_limit` | u16 | Combined internal limit |
| `torque_limit_temp` | u16 | Temperature-based limit |
| `torque_limit_engine_speed` | u16 | RPM-based limit |
| `torque_limit_engine_protection` | u16 | Cylinder failure limit |
| `torque_limit_external_and_internal` | u16 | Min of external and internal |

### TPS Control

| Variable | Type | Description |
|----------|------|-------------|
| `torque_limit_tps_current` | u16 | Current TPS limit |
| `torque_limit_tps_target` | u16 | Target TPS after filtering |
| `tps_after_torque_limit` | u16 | TPS after torque limiting |
| `tps_commanded_after_limits` | u16 | Final commanded TPS |
| `tps_correction_proportional` | i16 | PI controller P term |
| `tps_correction_integral` | i16 | PI controller I term |

### Reduction Factors

| Variable | Type | Description |
|----------|------|-------------|
| `torque_reduction_factor` | u8 | Overall reduction (0-255) |
| `torque_reduction_factor_ign` | u8 | Ignition-based reduction |
| `torque_limit_external_factor` | u8 | External request factor |
| `torque_limit_base_factor` | u8 | Base factor from tables |
| `torque_fact_base` | u8 | Combined efficiency factor |
