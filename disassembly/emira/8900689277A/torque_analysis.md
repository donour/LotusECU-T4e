# Emira 8900689277A — Torque Management Analysis

## Architecture

The torque management system has two main components:

### 1. torque_to_load_target() — Torque → Load → TPS chain
Converts driver torque request through a load-based model to a TPS target.  
Called from the main throttle control path at 50 Hz rate.

### 2. torque_limiter() — Torque limit arbitration  
Computes per-gear and per-coolant-temp torque ceilings, then applies them
through fast (spark-retard) and slow (throttle-reduce) paths. Separates  
manual vs IPS transmission calibrations.

---

## Calibration Tables

### Torque-to-Load Conversion (torque_to_load_target)

| Offset  | Size     | Axes                          | Purpose                                        |
|---------|----------|-------------------------------|------------------------------------------------|
| 0x3036  | 16×16 u16| X: rpm [800..6800]           | Main torque→load 3D map                        |
|         |          | Y: [0,0,40,80,120,160,200,250]|                                                |
| 0x2ff6  | 16       | engine speed RPM              | X axis for torque→load                         |
| 0x3016  | 16       | torque/load input             | Y axis for torque→load                         |
| 0x07f4  | 8        | factor [0..255]               | X axis for fast-rate torque delta comp         |
| 0x07fc  | 8  u8    | torque delta factor           | Fast torque rate compensation                  |
| 0x276e  | 8        | factor [0..255]               | X axis for slow-rate torque delta comp         |
| 0x2776  | 8  u8    | torque delta factor           | Slow torque rate compensation                  |

### Torque Limit by Coolant Temp (torque_limiter, 4×5 tables)

| Offset  | Trans     | X Axis (coolant °C)    | Y Axis          | Purpose                      |
|---------|-----------|------------------------|-----------------|------------------------------|
| 0x4f4c  | Manual    | [48,50,112,128]        | coolant temp    | X axis                       |
| 0x4f54  | Manual    | [0,2,200,400,600]      | engine speed?   | Y axis                       |
| 0x4f5e  | Manual    | —                      | torque limit    | CAL_torque_limit_by_coolant_manual |
| 0x4f86  | IPS       | [48,50,112,128]        | coolant temp    | X axis                       |
| 0x4f8e  | IPS       | [0,2,200,400,600]      | engine speed?   | Y axis                       |
| 0x4f98  | IPS       | —                      | torque limit    | CAL_torque_limit_by_coolant_ips    |

Thresholds: 48°C cold limit engages; 50°C taper; 112°C hot limit begins; 128°C maximum cut.

### Torque Max Limit by RPM (torque_limiter, 8×8 tables)

| Offset  | Trans     | X Axis (RPM)                         | Y Axis (torque Nm)                | Purpose                          |
|---------|-----------|--------------------------------------|-----------------------------------|----------------------------------|
| 0x5138  | Manual    | [1000,1500,2000,3000,4000,5000,6000,7000] | [104,208,312,416,516,620,724,828] | X axis                     |
| 0x5148  | Manual    | (same)                               | (same)                            | Y axis                     |
| 0x5158  | Manual    | —                                    | torque limit (u16)                | CAL_torque_max_by_rpm_manual     |
| 0x51d8  | IPS       | [1000,1500,2000,3000,4000,5000,6000,7000] | [104,208,312,416,516,620,724,828] | X axis                     |
| 0x51e8  | IPS       | (same)                               | (same)                            | Y axis                     |
| 0x51f8  | IPS       | —                                    | torque limit (u16)                | CAL_torque_max_by_rpm_ips        |

Output stored to DAT_400090a4 (torque max ceiling for current RPM/load).

### Torque Limit Factor by RPM × Load (torque_limiter, 16×16 tables)

| Offset  | Trans     | X Axis (RPM)                             | Y Axis (factor/load)                    | Purpose                            |
|---------|-----------|------------------------------------------|-----------------------------------------|------------------------------------|
| 0x53bc  | Manual    | [700,1000,1250,1500,1750,2000,2500,3000,3500,4000,4500,5000,5500,6000,6500,7000] | [90,90,90,90,90,138,184,251,…] | X axis |
| 0x53dc  | Manual    | (same)                                   | (same)                                  | Y axis |
| 0x53fc  | Manual    | —                                        | torque limit factor (u16)               | CAL_torque_factor_by_rpm_load_manual |
| 0x564c  | IPS       | [750,1000,1250,1500,1750,2000,2500,3000,3500,4000,4500,5000,5500,6000,6500,7000] | [90,90,90,90,90,138,184,251,…] | X axis |
| 0x566c  | IPS       | (same)                                   | (same)                                  | Y axis |
| 0x568c  | IPS       | —                                        | torque limit factor (u16)               | CAL_torque_factor_by_rpm_load_ips |

Combined result: `((factor_16x16 ^ 0x8000) * torque_max_8x8) / 0xff`

### Temperature Compensation (torque_limiter)

| Offset  | Size     | Axis values                          | Purpose                         |
|---------|----------|--------------------------------------|---------------------------------|
| 0x5388  | 8  u8    | [16,16,48,80,112,144,176,208]       | X axis (coolant temp °C?)       |
| 0x5390  | 8  u8    | —                                    | CAL_torque_limit_temp_comp      |

Output: DAT_4000834c

### Torque Limit → Ignition Retard (torque_limiter, u8 3D)

| Offset  | Size     | Purpose                                      |
|---------|----------|----------------------------------------------|
| 0x55fc  | ?×? u8   | X axis (unknown)                             |
| 0x5604  | ?×? u8   | Y axis (unknown)                             |
| 0x560c  | ?×? u8   | CAL_torque_spark_retard_limit                |

Output: _DAT_40009088 (spark retard from torque limit, doubled with <<1)

---

## Key Calibration Constants (torque_limiter)

| Cal Offset | Type  | Purpose                                          |
|------------|-------|--------------------------------------------------|
| 0x43dc     | u8    | Engine speed min for torque limiting              |
| 0x43dd     | u8    | Engine speed max for torque limiting              |
| 0x43e2     | u8    | Throttle min for torque limiting                  |
| 0x43e3     | u8    | Throttle max for torque limiting                  |
| 0x43e6     | u8    | Torque limiter enable mask                        |
| 0x437e     | u8    | Torque monitoring threshold A (upper)             |
| 0x437f     | u8    | Torque monitoring threshold B (upper)             |
| 0x4380     | u8    | Torque monitoring threshold C (lower, negated)    |
| 0x43fa     | u16   | Torque reduction amount — fast path               |
| 0x43f8     | u16   | Torque reduction amount — slow path               |
| 0x443a     | u16   | Torque limit hold duration                        |
| 0x4484     | u8    | Torque delta limit                                |
| 0x4ba6     | u8    | Torque monitor enable (slow)                      |
| 0x4ba7     | u8    | Torque monitor enable (fast)                      |
| 0x4da6     | u8    | Torque DTC debounce timer (slow)                  |
| 0x4da7     | u8    | Torque DTC debounce timer (fast)                  |

## Key Calibration Constants (torque_to_load_target)

| Cal Offset | Type  | Purpose                                          |
|------------|-------|--------------------------------------------------|
| 0x222      | u8    | Torque filtering weight (0-256 = 0-100% old)     |
| 0x32c      | u16   | Max positive torque delta per cycle               |
| 0x32e      | u16   | Max negative torque delta per cycle               |
| 0x330      | u16   | Max torque derivative (rate limiting)             |
| 0x332      | u16   | Min torque derivative (rate limiting)             |
| 0x335      | u8    | Torque derivative debounce counter                |
| 0x336      | u8    | Torque derivative error threshold                 |

---

## Comparison with Evora C132E0278

| Emira Table                          | Evora Equivalent                               | Match |
|--------------------------------------|------------------------------------------------|-------|
| Torque max by RPM (8×8)             | CAL_torque_limit_by_rpm (gear×RPM)             | Same concept, different layout |
| Torque factor by RPM×Load (16×16)   | CAL_torque_limit_base_factor (RPM×Load)        | Strong match |
| Torque limit by coolant (4×5)       | CAL_torque_limit_by_coolant                    | Strong match |
| Torque→Load 3D (16×16)              | CAL_torque_torque_to_load                      | Strong match |
| Spark retard from torque limit (3D) | CAL_torque_ign_retard_base                     | Strong match |
| Temp compensation (1×8)             | CAL_torque_engine_friction_speed_component     | Different — Emira simpler |

The Evora separates fast (spark) and slow (throttle) torque limits explicitly;
the Emira uses a single `torque_limiter` that handles both paths through
bit flags in _DAT_400035dc (0x20000 = TPS limit active, 0x80000 = spark retard active).
The neutral/no-limit sentinel in the Evora is 911 Nm (0x38f); the Emira uses
signed 16-bit clamping at ±0x7fff (32767).
