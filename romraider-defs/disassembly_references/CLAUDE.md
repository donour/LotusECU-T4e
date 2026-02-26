# Lotus Evora ECU Disassembly Reference

## Project Purpose

This directory contains Ghidra-generated C disassembly of Lotus Evora (T6e platform) ECU firmware,
used as the basis for building RomRaider tuning definitions. The goal is to understand calibration
table locations, scaling, and units so that tuning parameters can be exposed to end users.

The firmware is **Lotus/Bosch co-developed** engine management software for the Toyota-sourced 3.5L
2GR-FE V6 engine with Lotus supercharger. All ECU variants run on the **Freescale MPC5534** except
the Emira which uses the MPC5777C.

---

## ECU Variants

| Directory    | Part Number | Vehicle                          | Market    | Notes                          |
|--------------|-------------|----------------------------------|-----------|--------------------------------|
| `E132E0288`  | E132E0288   | Lotus Evora GT (2020–2021)       | US (91 oct) | Manual + IPS; main reference  |
| `C132E0278`  | C132E0278   | Lotus Evora GT430 (2019)         | UK        | ECU-based traction control     |
| `C132E0271`  | C132E0271   | Lotus Evora 400 (2017)           | US Federal | Naturally aspirated base      |
| `B13200091`  | B13200091   | Lotus Evora NA (2011)            | US Federal | Oldest variant; NA engine      |
| `abs/`       | —           | ABS/ESP module (Bosch ESP8)      | All       | Evora 400, GT410, GT430, GT    |
| `emira/`     | —           | Lotus Emira V6 Supercharged      | EU/UK (98 RON) | MPC5777C; different arch  |

DO NOT READ `E132E0288/20251226_factor/`. It is incomplete.

---

## Architecture

### MPC5534 Peripherals Used

- **eTPU**: Crank/cam timing, ignition scheduling, fuel injection pulse width
- **EQADC**: 40+ channel 12-bit ADC; samples MAF, MAP, TPS, temperatures, O2, knock, battery voltage
- **FlexCAN A**: OBD-II (tester) + vehicle CAN (ABS/ESP, cluster, IPS, body module)
- **EMIOS**: PWM outputs for fans, pumps, VVT solenoids
- **DSPI/ESCI**: External SPI/serial devices
- **INTC**: Interrupt controller at `0xFFF48xxx`

### Memory Map

| Range              | Purpose                                   |
|--------------------|-------------------------------------------|
| `0x00000000`       | Flash: code + calibration (ROM)           |
| `0x40000000`       | RAM start                                 |
| `0x40001xxx`       | Runtime variables (frequently updated)    |
| `0x40002xxx`       | Runtime variables (less frequent)         |
| `0x4000xxxx`       | General RAM variables and learned values  |
| `0xC3F90000`       | SIU (System Integration Unit)            |
| `0xC3FA0000`       | EMIOS registers                           |
| `0xC3FC0000`       | eTPU registers                            |
| `0xFFF48000`       | INTC (Interrupt Controller)               |
| `0xFFF80000`       | EQADC registers                           |

Emira: calibration is copied to RAM at `0x4002e000` (64 KB block) at startup.

### Execution Rate Structure

The firmware schedules tasks at multiple rates from a 1000 Hz base loop:

| Rate    | Period  | Key Tasks                                                         |
|---------|---------|-------------------------------------------------------------------|
| 1000 Hz | 1 ms    | Ignition/injection scheduling, knock detection, engine speed, TC |
| 200 Hz  | 5 ms    | Closed-loop O2 fuel control, sensor sampling, CAN timeout checks |
| 100 Hz  | 10 ms   | VVT, OBD monitors, cooling, idle control, throttle               |
| 50 Hz   | 20 ms   | Torque management, rev limiter, diagnostics                       |
| 10 Hz   | 100 ms  | CAN transmit (cluster, IPS), slow monitors, adaptive updates      |
| 1 Hz    | 1000 ms | Runtime counters, cruise control, EEPROM writes, long-term learn  |

---

## Custom Type System

All calibration and runtime variables use unit-encoding typedefs. The naming convention is:

```
u<bits>_<unit_description>
```

- Prefix: `u8_`, `u16_`, `u32_` (unsigned), `i8_`, `i16_`, `i32_` (signed)
- The unit description encodes both the physical quantity and scaling factor

### Common Type Examples

| Type                       | Formula               | Example Values          |
|----------------------------|-----------------------|-------------------------|
| `u8_temp_5/8-40c`          | °C = val * 5/8 − 40   | 0 = −40°C, 128 = 40°C  |
| `u16_temp_1/10C`           | °C = val / 10         | 200 = 20.0°C            |
| `u8_rspeed_125/4+500rpm`   | RPM = val * 125/4 + 500 | 0 = 500, 100 = 3625 RPM |
| `u16_rspeed_rpm`           | RPM = val             | Direct RPM              |
| `u8_load_4mg/stroke`       | mg/stk = val * 4      | 50 = 200 mg/stroke      |
| `u8_load_1173mg/255stroke` | mg/stk = val * 1173/255 | Normalized load axis  |
| `u8_angle_1/4deg`          | deg = val / 4         | 40 = 10°                |
| `u8_angle_1/4-10deg`       | deg = val / 4 − 10    | 0 = −10°, 80 = 10°      |
| `u8_afr_1/20+5`            | AFR = val / 20 + 5    | 219 = 15.95 (stoich ~14.7) |
| `u8_factor_1/255`          | factor = val / 255    | 128 ≈ 50%               |
| `u16_factor_1/1023`        | factor = val / 1023   | TPS position 0–100%     |
| `u8_pressure_50mbar`       | mbar = val * 50       | 20 = 1000 mbar          |
| `u16_torque_nm`            | Nm = val              | Direct newton-meters     |
| `u8_torque_nm`             | Nm = val              | 0–255 Nm direct          |
| `u16_time_5ms`             | ms = val * 5          | Timer in 5 ms steps      |
| `u16_time_100ms`           | ms = val * 100        | Timeout in 100 ms steps  |
| `u8_speed_kph`             | km/h = val            | Direct km/h              |
| `u16_distance_km`          | km = val              | Direct km                |

Unresolved variables use `undefined2`, `undefined4`, or `????` suffix in the variable name.

---

## Variable Naming Conventions

| Prefix   | Meaning                                              |
|----------|------------------------------------------------------|
| `CAL_`   | Calibration constant (in flash, RomRaider-tunable)   |
| `LEA_`   | Learned / adaptive value (persisted to EEPROM)       |
| `DAT_`   | Ghidra auto-generated label (address-based name)     |
| `FUN_`   | Ghidra auto-generated function label                 |
| `obd_ii_` | OBD-II runtime state                               |
| no prefix | Analyst-assigned runtime variable name              |

`LEA_` variables are long-term learned values (knock octane adaptation, idle learn, fuel trims,
MAF compensation) that persist across ignition cycles via EEPROM emulation in flash.

---

## Calibration Table Organization (CAL_*)

### Functional Prefixes

| Prefix              | Subsystem                              |
|---------------------|----------------------------------------|
| `CAL_ign_*`         | Ignition timing (base, MBT, knock-safe, dwell, compensations) |
| `CAL_knock_*`       | Knock detection sensitivity, retard limits, AGC               |
| `CAL_inj_*`         | Injector characterization, AFR targets                        |
| `CAL_injtip_*`      | Fuel tip-in/tip-out film compensation (X-tau model)           |
| `CAL_fuel_*`        | Fuel system (DFCO, cranking enrichment, closed-loop gains)    |
| `CAL_sensor_*`      | Sensor scaling tables (MAF, MAP, temperatures, TPS)           |
| `CAL_cooling_*`     | Fan and pump control                                          |
| `CAL_ac_*`          | AC compressor control                                         |
| `CAL_tc_*`          | Traction control                                              |
| `CAL_torque_*`      | Engine torque model (friction, accessory load, limits)        |
| `CAL_idle_*`        | Idle speed control                                            |
| `CAL_vvt_*`         | Variable valve timing targets and control gains               |
| `CAL_obd_*`         | OBD-II monitor thresholds and DTC enable masks                |
| `CAL_cluster_*`     | Instrument cluster communication                              |
| `CAL_cruise_*`      | Cruise control                                                |
| `CAL_dca_*`         | Drive Cycle Assist, disabled emissions testing functionalty   |

### Table Structure Pattern

All multi-dimensional lookup tables follow this naming pattern:

```
u8_angle_1/4-10deg[400]          CAL_ign_base_manual;           // 20×20 data
u8_rspeed_125/4+500rpm[20]       CAL_ign_base_manual_X_engine_speed; // X axis (RPM)
u8_load_1173mg/255stroke[20]     CAL_ign_base_manual_Y_load;    // Y axis (load)
```

The table is stored row-major. Some lookup functions perform bilinear interpolation, some do not.
Separate tables exist for IPS (automatic) and manual transmission in key calibrations
(`_manual` vs `_ips` suffix).

### Ignition Base Tables

- `CAL_ign_base_manual` / `CAL_ign_base_ips` — base timing maps
- Compensations applied additively: coolant temp, IAT, TPS rate, RPM, manifold temp, idle error
- Per-cylinder knock retard tracked in `LEA_ign_knock_retard[6]`
- Octane adaptation in `LEA_octane_scaler[8]` (long-term, EEPROM-persisted)

### Fuel System

- `CAL_inj_afr_base` — AFR target map (type `u8_afr_1/20+5`)
- Closed-loop O2 control runs bank 1 and bank 2 independently
- O2 sensor numbering: sensor 1 = bank 1 pre-cat, sensor 2 = bank 1 post-cat,
  sensor 5 = bank 2 pre-cat, sensor 6 = bank 2 post-cat
- Fuel film (X-tau) compensation for transient enrichment: `CAL_injtip_*`
- DFCO (deceleration fuel cut)

---

## CAN Bus

FlexCAN A carries both OBD-II (ISO 15765 / ISO-TP) diagnostic traffic and internal vehicle CAN.

### OBD-II / Diagnostic Addresses

| CAN ID  | Direction         | Description                    |
|---------|-------------------|--------------------------------|
| `0x7DF` | Tester → ECU      | Functional addressing (all ECUs) |
| `0x7E0` | Tester → ECU      | Physical addressing (engine ECU) |
| `0x7E8` | ECU → Tester      | Engine ECU response              |

### Vehicle CAN Messages (ECU ↔ Other Modules)

| CAN ID  | Source        | Content                                             |
|---------|---------------|-----------------------------------------------------|
| `0x85`  | SAS transmit  | Steering Angle Sensor                               |
| `0xD2`  | ECU transmit  | IPS transmission requests                           |
| `0x102` | ECU transmit  | Torque data to ABS/ESP (Alpha-N net, combustion Nm) |
| `0x114` | ECU           | Tachometer, accelerator pedal, drivetrain mode      |
| `0x303` | Yaw transmit  | Bosch YAW sensor, lateral acceleration              |
| `0x400` | ECU transmit  | Cluster data: fuel level, coolant temp, shift lights, MIL |
| `0xA2`  | ABS           | Front wheel speeds (LF, RF, vehicle speed)          |
| `0xA4`  | ABS           | Rear wheel speeds (LR, RR), brake switch            |
| `0xA8`  | ABS           | ESP/ABS status flags (ABS active, ESP active)       |

CAN 0x400 (cluster message) carries: instantaneous fuel usage, fuel level %, coolant temperature
(u8_temp_5/8-40c encoding), traction control indicator, MIL, shift lights (3 stages), low fuel
warning, oil pressure warning, coolant over-temp warning.

CAN 0x102 torque message: 12-bit Alpha-N net torque (Nm, unsigned) and 11-bit combustion net torque
(signed, offset 400 Nm, 0.25 Nm resolution). Both fields encode 0xFFF/0x7FF as invalid/error.

### OBD Mode 0x2F (Actuator Tests)

The ECU supports UDS 0x2F (InputOutputControlByIdentifier) for production/workshop testing.
Key behaviours:
- **Most PIDs require engine-off** (NRC 0x22 returned otherwise)
- **Inactivity timeout**: commands must be repeated every ~500 ms or all tests cancel
- **Injectors and coils are mutually exclusive** — cannot test both simultaneously
- Exhaust bypass valve (PID 0x14E) is unique: can be actuated at idle (engine running, speed = 0)
- Full PID list and CAN framing documented in `LotusEvoraOBDMode0x2FGuide.md`

---

## Key Subsystems

### Knock Control

- Goertzel DSP-based knock detection, per-cylinder
- Short-term retard tracked per cylinder in runtime; long-term octane scaler in `LEA_octane_scaler`
- AGC (Automatic Gain Control) adjusts sensitivity by operating condition
- Detection window configured relative to crank angle via eTPU

### Variable Valve Timing (VVT)

- Dual independent VVT (intake and exhaust cams, both banks = 4 actuators)
- intake angle up to 40 degrees
- Target cam positions from `CAL_vvt_*` tables (RPM × load)
- Position feedback from cam sensors via eTPU
- Disabled during cold coolant conditions

### Traction Control

- TC is **ECU-based** (not ABS/ESP) on GT430 only
- TC is also in the ESP, as a safety mechanism.
- Wheel speed data received from ABS via CAN (0xA2, 0xA4)
- cruise control also in ECU (not ESP/ABS)

### Torque Model

The ECU maintains a torque model with several friction components:
- `torque_engine_friction_coolant` — temperature-dependent friction
- `torque_engine_friction_accessory` — AC compressor load
- `torque_engine_friction_comp_engine_speed` — RPM-dependent mechanical loss
- Net torques transmitted to ABS/ESP via CAN 0x102 for stability control coordination
- S2 evoras (GT, GT430, 400) have torque limit calibrations

### IPS Transmission Interface

When IPS (automated manual) transmission is fitted:
- Separate ignition and fuel tables for IPS vs manual (`_ips` suffix)
- Rev-matching PID controller adjusts engine speed during downshifts
- Torque reduction requests during gear changes

### Idle Speed Control

- Idle air managed via drive-by-wire throttle (DBW)
- `CAL_idle_*` tables control target idle speed vs coolant temp, AC load, electrical load
- Cold-start idle learn stored in `LEA_idle_cold_learning_*`

### Drive Cycle Assist (DCA)

- Enabled only a moderate speed, with steering wheel pointed forward
- Not enabled on production vehicles

---

## File Structure Reference

Each ECU directory typically contains:
- `<part>.c` — Full Ghidra disassembly (monolithic, 50,000–65,000 lines)
- `<part>.hex` — Original firmware binary in Intel HEX format
- `<part>.symbols.csv` or `<part>_cal_symbols.txt` — Exported Ghidra symbols with addresses and sizes
- `CLAUDE.md` — Per-variant firmware metadata and LLM context

---

## Differences Between Variants

| Feature                   | B13200091 (NA) | C132E0271 (400) | C132E0278 (GT430) | E132E0288 (GT) |
|---------------------------|:--------------:|:---------------:|:-----------------:|:--------------:|
| Supercharged              | No             | No              | Yes               | Yes            |
| ECU-based TC              | No             | No              | Yes               | No             |
| IPS transmission support  | No             | Yes             | Yes               | Yes            |
| US/Federal market         | Yes            | Yes             | No                | Yes            |
| Charge air cooler         | No             | Yes             | Yes               | Yes            |
| VIMS (variable intake)    | Yes            | No              | No                | No             |
| CAC pump (PID 0x151)      | No             | Yes             | Yes               | Yes            |

The NA (B13200091) is the earliest and simplest variant. The GT430 (C132E0278) has the most
aggressive traction control calibration. The GT (E132E0288) is the primary US reference target.

---

## Common Analysis Tasks

**Find a calibration parameter**: Search for `CAL_` prefix, e.g. `grep CAL_ign_base`.

**Understand a variable's units**: Find its typedef — the suffix encodes the scaling formula.

**Trace a lookup table**: Find `CAL_xxx` data + `CAL_xxx_X_*` and `CAL_xxx_Y_*` axis arrays.

**Find a DTC implementation**: Search for `LEA_obd_ii_Pxxxx_dtc_state` or the DTC code string.

**Check EEPROM-stored learned values**: Search for `LEA_` prefix — these survive power cycles.

**Identify unresolved variables**: `undefined2` type or `???`/`___` in the variable name means
the physical unit has not yet been determined.

---

## Notes and Caveats

- All variable names are **analyst-assigned** except `DAT_*` and `FUN_*` (Ghidra auto-generated)
- The disassembly is for **research and educational purposes** — Lotus/Bosch IP
- Fuel tank capacity: **60.0 liters**
- O2 sensors: bank 1 = cylinders 1–3, bank 2 = cylinders 4–6
  (sensor 1 pre-cat, sensor 2 post-cat, sensor 5 pre-cat, sensor 6 post-cat)
- Cruise control and traction control are **ECU-resident** (not in ABS/ESP module)
- The MPC5534 has no hardware floating point; all math is fixed-point integer arithmetic
- The `clip_value(value, min, max)` helper enforces limits throughout the codebase
- Lookup interpolation functions: `lookup_2D_uint8_interpolated(n_entries, x, data[], axis[])`
  and `lookup_2D_uint16_interpolated` — arguments are (size, index, data_ptr, axis_ptr)
- Drag torque control is implemented in the ESP/ABS unit
