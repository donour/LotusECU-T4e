# Lotus T6e Rev Limiter System

This document describes the rev limiter implementation in the Lotus T6e ECU firmware (E132E0288).

## Overview

The T6e rev limiter uses a multi-stage control system that combines:
- **Fuel cut** (hard limit) - Immediate injection disable above threshold
- **Airflow reduction** (soft limit) - PID-controlled throttle/MAF reduction approaching limit
- **Torque management** - Throttle clamping via torque model integration

The system supports both manual transmission (EA60) and IPS (U660E) automatic transmission vehicles, with different calibrations for Tour and Sport modes.

## System Architecture

```
                                    +------------------+
                                    |   INPUTS         |
                                    +------------------+
                                    | - Engine Speed   |
                                    | - Coolant Temp   |
                                    | - Vehicle Mode   |
                                    | - Gear Position  |
                                    | - Runtime        |
                                    | - Failure Flags  |
                                    +--------+---------+
                                             |
                                             v
+-----------------------------------------------------------------------------------+
|                              REV LIMIT CALCULATION                                 |
|                                   revlimit()                                       |
+-----------------------------------------------------------------------------------+
|                                                                                    |
|   +------------------+     +-------------------+     +-------------------+         |
|   | Mode Selection   |     | Cold Start        |     | Limp Mode         |         |
|   | (IPS/Manual,     |---->| Offset            |---->| Override          |         |
|   |  Tour/Sport)     |     | Calculation       |     | (if faults)       |         |
|   +------------------+     +-------------------+     +-------------------+         |
|           |                        |                         |                     |
|           v                        v                         v                     |
|   +------------------------------------------------------------------+            |
|   |              ENVELOPE CALCULATION                                 |            |
|   |   revlimit_hard = envelope_min - cold_start_offset               |            |
|   |   revlimit_soft = envelope_max - cold_start_offset               |            |
|   +------------------------------------------------------------------+            |
|                                    |                                              |
+------------------------------------+----------------------------------------------+
                                     |
              +----------------------+----------------------+
              |                      |                      |
              v                      v                      v
     +----------------+     +------------------+    +------------------+
     | FUEL CUT       |     | AIRFLOW CONTROL  |    | TORQUE CLAMP     |
     | (Hard Limit)   |     | (Soft Limit)     |    | (Throttle Limit) |
     +----------------+     +------------------+    +------------------+
     | Injection ISR  |     | PID Controller   |    | TPS Clamping     |
     | engine_speed > |     | - P: rpm delta   |    | revlimit_tps_max |
     | revlimit_hard  |     | - I: integrator  |    +------------------+
     +----------------+     | - D: rpm rate    |
                            +------------------+
                                     |
                                     v
                            +------------------+
                            | IPS CAN TX       |
                            | (100Hz)          |
                            | revlimit_hard    |
                            +------------------+
```

## Execution Flow

### Main Functions

| Function | Scheduling | Purpose |
|----------|------|---------|
| `revlimit()` | continuous | Calculate rev limits, envelope selection, PID gains, escalation |
| `revlimit_200hz()` | 200Hz | MAF control, integrator updates, derivative calculation |
| Injection ISR | Per-cylinder | Fuel cut decision based on `revlimit_hard` |

## Rev Limit Envelope

The rev limiter uses a **dual-threshold envelope**:

```
RPM
 ^
 |     revlimit_hard (fuel cut)
 |  ========================== Hard Limit
 |        |                |
 |        |  Airflow       |
 |        |  Reduction     |
 |        |  Zone          |
 |        |                |
 |  ========================== Soft Limit
 |     revlimit_soft (intervention starts)
 |
 +---------------------------------> Time
```

### Envelope Selection

The base envelope is selected based on:
1. **Transmission type**: IPS (automatic) vs Manual
2. **Vehicle mode**: Sport vs Tour
3. **Engine condition**: Normal vs degraded (tour tables if faults present)

```
if (vehicle_in_sport_mode && no_faults && vvt_ok):
    if (transmission == IPS):
        table = CAL_revlimit_speedbase_ips_sport
    else:
        table = CAL_revlimit_speedbase_manual_sport
else:
    if (transmission == IPS):
        table = CAL_revlimit_speedbase_ips_tour
    else:
        table = CAL_revlimit_speedbase_manual_tour
```

### 3D Table Lookup

Each envelope table is a 4x4 3D lookup indexed by:
- **X-axis**: Coolant temperature
- **Y-axis**: Timer value (0 to 0xFFFF, interpolated)

The lookup is performed twice:
- `revlimit_rpm_envelope_min` = lookup with Y=0 (hard limit)
- `revlimit_rpm_envelope_max` = lookup with Y=0xFFFF (soft limit)

## Cold Start Protection

When the engine is cold and recently started, rev limits are reduced:

```
if (runtime < CAL_revlimit_startup_delay * 50) AND
   (coolant_temp_at_start <= CAL_revlimit_coolant_coldstart_threshold):

    offset = normal_limit - cold_limit
    revlimit_hard = normal_hard - offset
    revlimit_soft = normal_soft - offset
```

The offsets decay over time at a rate of `CAL_revlimit_startup_offset_decrement` per 200Hz tick.

## Gear-Based Trim

Rev limits can be adjusted per gear:

```
revlimit_current = revlimit_soft - (revlimit_trim_per_gear * 2)
```

The trim is looked up from `CAL_revlimit_trim_per_gear` indexed by current gear.

## Limp Mode Override

When certain faults are present, the rev limit is reduced:

```
Fault conditions (engine_state_failure_flags & 0xdceea77):
- VVT inhibit flags
- Misfire conditions

if (faults_present):
    revlimit_limp_mode_active = true
    if (CAL_revlimit_limp_mode < calculated_limit):
        revlimit_hard = CAL_revlimit_limp_mode
        revlimit_soft = CAL_revlimit_limp_mode - (hard - soft)
```

## PID Airflow Control

The soft rev limiter uses a PID-like controller to reduce airflow as RPM approaches the limit.

### Control Diagram

```
                    revlimit_current
                          |
                          v
    engine_speed_2 --->(-)---> revlimit_engine_speed_delta (error)
                                        |
              +-------------------------+-------------------------+
              |                         |                         |
              v                         v                         v
    +------------------+     +-------------------+     +-------------------+
    | PROPORTIONAL     |     | INTEGRAL          |     | DERIVATIVE        |
    | Term             |     | Term              |     | Term              |
    +------------------+     +-------------------+     +-------------------+
    | rpm_delta *      |     | accumulator +=    |     | (delta - prev) /  |
    | gain_from_delta  |     | rpm_delta / 10    |     | delta             |
    | / 5              |     |                   |     | (at 100Hz)        |
    +------------------+     +-------------------+     +-------------------+
    | Per-gear gain:   |     | Per-gear gain:    |     | Per-gear gain:    |
    | CAL_revlimit_    |     | CAL_revlimit_     |     | CAL_revlimit_     |
    | airflow_gain_    |     | airflow_gain_     |     | airflow_gain_     |
    | from_rpm_delta   |     | from_integrator   |     | from_rpm          |
    +--------+---------+     +---------+---------+     +---------+---------+
             |                         |                         |
             v                         v                         v
    revlimit_flow_         revlimit_flow_          revlimit_airflow_
    proportional_term      integral_term           rpm_term
             |                         |                         |
             +------------+------------+------------+------------+
                          |
                          v
              +-----------------------+
              | MAF Flow Calculation  |
              | revlimit_maf_flow =   |
              | maf_bounded + P + I   |
              +-----------------------+
                          |
                          v
              +-----------------------+
              | Load Calculation      |
              | revlimit_load =       |
              | (maf * period)/100k   |
              | - idle_offset         |
              +-----------------------+
                          |
                          v
              +-----------------------+
              | TPS Lookup            |
              | revlimit_tps_max =    |
              | load_to_tps(load)     |
              +-----------------------+
```

### Integrator Behavior

The integrator (`revlimit_escalation_integrator`) accumulates RPM error:

```c
// Clamped to +/- (CAL_revlimit_integrator_limit * 250)
if (revlimit_active):
    integrator += revlimit_engine_speed_delta / 10
else:
    integrator = 0
```

### Escalation Logic

When repeated fuel cuts occur, the system escalates throttle reduction:

```c
if (revlimit_fuelcut_count > CAL_revlimit_overrun_count_threshold):
    revlimit_state_flags |= 0x01  // Limiter active
    revlimit_esclated_timer = 40

    // Decrement integrator aggressively
    step = CAL_revlimit_escalation_integrator_step[gear] * 25
    integrator -= step
```

## Fuel Cut Logic

The fuel cut occurs in the injection interrupt service routine:

```c
if (engine_speed_2 >= revlimit_hard):
    injection_flags |= 0x09           // Enable fuel cut
    if (!(injection_flags & 0x20)):
        revlimit_fuelcut_count++      // Count consecutive cuts
        injection_flags |= 0x29
else if (engine_speed_2 <= revlimit_hard - CAL_revlimit_fuelcut_hysteresis):
    injection_flags &= ~0x08          // Re-enable fuel
```

The hysteresis prevents rapid on/off cycling at the rev limit.

## State Flags (revlimit_state_flags)

| Bit | Hex | Description |
|-----|-----|-------------|
| 0 | 0x0001 | Rev limiter active (fuel cut triggered) |
| 1 | 0x0002 | MAF increasing state |
| 2 | 0x0004 | MAF decreasing state |
| 3 | 0x0008 | Torque clamp path enabled |
| 4 | 0x0010 | Torque clamp engaged / transient step active |
| 6 | 0x0040 | Limiter event detected (pre-clamp pending) |
| 7 | 0x0080 | RPM target clipped to estimated max |
| 8 | 0x0100 | Hard-capped to `CAL_revlimit_max_with_speedlimit` |
| 9 | 0x0200 | RPM estimate valid/in-bounds for clip logic |
| 10 | 0x0400 | Speed-limit margin adjustment active |
| 11 | 0x0800 | MAF arbitration mode (overspeed/clip branch selector) |

## IPS Transmission Communication

### CAN Message Structure

The ECU transmits rev limit data to the IPS transmission controller at 100Hz via FlexCAN:

```c
flexcan_a_tx_d2_100hz(
    tps2,                           // Byte 0: Throttle position
    revlimit_state_flags & 1,       // Byte 1: Rev limiter active flag
    paddle_shift_flags,             // Byte 2: Paddle shift status
    CAL_ecu_ips_mesg_unknown << 4 | 6,  // Byte 3: IPS config flags
    cruise_speed_target / 100,      // Byte 4: Cruise target (kph)
    ips_cruise_status_flags,        // Byte 5: Cruise status
    revlimit_hard_for_ips & 0xFF,   // Byte 6: Rev limit low byte
    revlimit_hard_for_ips >> 8      // Byte 7: Rev limit high byte
);
```

### CAN Buffer Details

- Buffer index: 0x12
- Arbitration ID: 0x1A4 (embedded in `0x3480000 >> 18`)
- Data length: 8 bytes
- Transmission rate: 100Hz

### IPS-Specific Variables

| Variable | Purpose |
|----------|---------|
| `revlimit_hard_for_ips` | Rev limit value sent to transmission (= `revlimit_hard`) |
| `revlimit_active_gear_ips` | Gear position when limiter activated (for gear-change detection) |

The transmission uses this data to:
1. Coordinate shift timing around the rev limit
2. Adjust shift points based on limiter state
3. Manage torque reduction during shifts

## Vehicle Speed Limiter Integration

The rev limiter can also enforce vehicle speed limits (for IPS cars or when explicitly enabled):

```c
if (ips_enforce_speed_limit || CAL_vehicle_speed_limit_enforce):
    speed_limit = CAL_vehicle_speed_limit * 200  // in 1/100 kph
    rpm_at_speed_limit = (speed_limit * engine_speed) / car_speed

    if (rpm_at_speed_limit < revlimit):
        revlimit = rpm_at_speed_limit
```

The speed limiter uses ramping logic (`speed_limit_target_ramped`) to smoothly approach the limit.

---

## Calibration Variables Reference

### Rev Limit Envelope Tables

| Variable | Type | Description |
|----------|------|-------------|
| `CAL_revlimit_speedbase_manual_sport` | u16[16] | Manual transmission, Sport mode rev limit table (4x4) |
| `CAL_revlimit_speedbase_manual_tour` | u16[16] | Manual transmission, Tour mode rev limit table (4x4) |
| `CAL_revlimit_speedbase_ips_sport` | u16[16] | IPS transmission, Sport mode rev limit table (4x4) |
| `CAL_revlimit_speedbase_ips_tour` | u16[16] | IPS transmission, Tour mode rev limit table (4x4) |
| `CAL_revlimit_speedbase_*_X_coolant_temp` | u16[4] | X-axis: Coolant temperature breakpoints |
| `CAL_revlimit_speedbase_*_Y_timer` | u16[4] | Y-axis: Timer value breakpoints |

### Cold Start Parameters

| Variable | Type | Description |
|----------|------|-------------|
| `CAL_revlimit_coldstart_rpm_envelope` | u16[4] | Cold start rev limit envelope |
| `CAL_revlimit_coldstart_rpm_envelope_X_index` | u16[4] | Index axis for cold start lookup |
| `CAL_revlimit_coolant_coldstart_threshold` | u8 | Coolant temp below which cold start logic applies |
| `CAL_revlimit_startup_delay` | u8 | Time after start to use cold start limits (×250ms) |
| `CAL_revlimit_startup_offset_decrement` | u8 | Decay rate for cold start offset (per 200Hz tick) |

### PID Gains (Per-Gear)

| Variable | Type | Description |
|----------|------|-------------|
| `CAL_revlimit_airflow_gain_from_rpm_delta` | u8[7] | P-term gain (proportional to RPM error) |
| `CAL_revlimit_airflow_gain_from_integrator` | u8[7] | I-term gain (accumulated error) |
| `CAL_revlimit_airflow_gain_from_rpm` | u8[7] | D-term gain (rate of change) |
| `CAL_revlimit_airflow_gain_from_rpm_delta_X_gear` | u8[7] | P-term gear axis |
| `CAL_revlimit_airflow_gain_from_integrator_X_gear` | u8[7] | I-term gear axis |
| `CAL_revlimit_airflow_gain_from_rpm_X_gear` | u8[7] | D-term gear axis |

### Escalation Parameters

| Variable | Type | Description |
|----------|------|-------------|
| `CAL_revlimit_overrun_count_threshold` | u8 | Fuel cut count before escalation begins |
| `CAL_revlimit_escalation_integrator_step` | u8[7] | Integrator decrement step per gear |
| `CAL_revlimit_escalation_integrator_step_X_gear` | u8[7] | Gear axis for escalation step |
| `CAL_revlimit_integrator_limit` | u8 | Maximum integrator value (×250) |

### Limiting Parameters

| Variable | Type | Description |
|----------|------|-------------|
| `CAL_revlimit_limp_mode` | u16 | Rev limit when faults present (RPM) |
| `CAL_revlimit_max_with_speedlimit` | u16 | Maximum rev limit when speed limiting (RPM) |
| `CAL_revlimit_fuelcut_hysteresis` | u16 | Hysteresis for fuel cut re-enable (RPM) |
| `CAL_revlimit_overspeed_time` | u8 | Time above limit before escalation (×100ms) |
| `CAL_revlimit_rpm_rate_limit` | u8 | D-term clamp value (×25) |

### Airflow Control

| Variable | Type | Description |
|----------|------|-------------|
| `CAL_revlimit_airflow_threshold` | u8[7] | Initial MAF bound per gear (×200 = mg/s) |
| `CAL_revlimit_airflow_threshold_X_gear` | u8[7] | Gear axis for airflow threshold |
| `CAL_revlimit_flow_proportional_term` | u8 | P-term output clamp (×100) |
| `CAL_revlimit_flow_unknown2` | u8 | I-term output clamp (×100) |
| `CAL_revlimit_maf_error_max_10g` | u8 | Maximum MAF adjustment step (×10g/s) |

### Gear Trim

| Variable | Type | Description |
|----------|------|-------------|
| `CAL_revlimit_trim_per_gear` | u8[7] | Rev limit reduction per gear (×2 RPM) |
| `CAL_revlimit_trim_per_gear_X_gear` | u8[7] | Gear axis for trim lookup |

### Throttle Clamp

| Variable | Type | Description |
|----------|------|-------------|
| `CAL_revlimit_throttle_clamp` | bool | Enable throttle position clamping |
| `CAL_revlimit_torque_limit_confirmation_threshold` | u8 | Torque threshold for clamp activation (×2 Nm) |
| `CAL_revlimit_enforce_delay_after_start` | u8 | Delay before enforcing limits after start (×50ms) |

### Speed Limiting

| Variable | Type | Description |
|----------|------|-------------|
| `CAL_vehicle_speed_limit` | u8 | Top speed limit (kph, ×200 internally) |
| `CAL_vehicle_speed_limit_enforce` | bool | Enable speed limiting (non-IPS) |
| `CAL_vehicle_speed_limit_enforce_margin` | u8 | Speed ramping margin |

---

## Runtime Variables Reference

### Limit Values

| Variable | Address | Type | Description |
|----------|---------|------|-------------|
| `revlimit_hard` | RAM | u16 | Current hard rev limit (fuel cut threshold) |
| `revlimit_soft` | RAM | u16 | Current soft rev limit (intervention starts) |
| `revlimit_current` | RAM | u16 | Soft limit after gear trim |
| `revlimit_hard_for_ips` | 0x40001864 | u16 | Value transmitted to IPS |

### PID State

| Variable | Address | Type | Description |
|----------|---------|------|-------------|
| `revlimit_engine_speed_delta` | RAM | i16 | Error: limit - actual RPM |
| `revlimit_escalation_integrator` | 0x400029aa | i16 | Integral accumulator |
| `revlimit_rpm_error_rate` | 0x400029ac | i16 | Derivative term |
| `revlimit_derivative_prescaler` | 0x400029b5 | u8 | Derivative update divider |

### Airflow Control

| Variable | Address | Type | Description |
|----------|---------|------|-------------|
| `revlimit_maf_flow_raw` | RAM | u16 | Target MAF flow (mg/s ÷ 10) |
| `revlimit_maf_flow_bounded` | RAM | u16 | Bounded MAF flow |
| `revlimit_flow_proportional_term` | RAM | i16 | P-term output |
| `revlimit_flow_integral_term` | RAM | i16 | I-term output |
| `revlimit_load` | RAM | u16 | Calculated load for TPS lookup |
| `revlimit_tps_max` | RAM | u16 | Maximum TPS from rev limiter |

### Status

| Variable | Address | Type | Description |
|----------|---------|------|-------------|
| `revlimit_state_flags` | 0x40001346 | u16 | State machine flags |
| `revlimit_fuelcut_count` | RAM | u8 | Consecutive fuel cut counter |
| `revlimit_esclated_timer` | RAM | u8 | Escalation holdoff timer |
| `revlimit_limp_mode_active` | RAM | bool | Fault-induced limit active |
