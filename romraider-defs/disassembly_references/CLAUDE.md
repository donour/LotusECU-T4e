## Project Overview

This directory contains various diassembly projects from Ghidra.

 - E132E0288: Lotus Evora GT
 - C132E0278: Lotus Evora GT430
 - abs: antilock brake system

## Architecture and Data Types

### Custom Type System

The disassembly uses extensive custom typedefs that encode both the data type and physical units. This is critical for understanding calibration values:

- **Naming convention**: `u8_` (unsigned 8-bit), `u16_` (unsigned 16-bit), `u32_` (unsigned 32-bit), `i8_`/`i16_`/`i32_` (signed variants)
- **Unit encoding in type name**: The portion after the data size indicates the physical unit and scaling

Examples:
- `u8_temp_5/8-40c`: Unsigned 8-bit temperature, formula: (value * 5/8) - 40°C
- `u16_rspeed_rpm`: Unsigned 16-bit engine speed in RPM
- `u8_angle_1/4deg`: Unsigned 8-bit angle in 1/4 degree increments
- `u8_load_4mg/stroke`: Unsigned 8-bit load in 4mg per stroke
- `u16_factor_1/1023`: Unsigned 16-bit scaling factor (0-1023)
- `u8_pressure_50mbar`: Unsigned 8-bit pressure in 50 millibar increments

### Hardware Peripheral Structures

The code defines structures for MPC5500-series microcontroller peripherals:
- `struct_dspi_mmio`: SPI peripheral registers
- `struct_emios_unified_channel_register`: Enhanced modular I/O system
- `flexcan_msg_buffer`: FlexCAN message buffers
- `struct_esci_control_registers`: Serial communication interface
- EQADC (Enhanced Queued ADC) register arrays

## Calibration Data (CAL_* symbols)

### Organization

All calibration parameters use the `CAL_` prefix and are organized by functional area:

- **Ignition**: `CAL_ign_*` (base timing, knock control, MBT, dwell)
- **Injection/Fuel**: `CAL_injtip_*`, `CAL_fuel_*`
- **Sensors**: `CAL_sensor_*` (MAF, coolant, IAT, TPS, etc.)
- **Cooling**: `CAL_cooling_*` (fan control, pump control)
- **Knock**: `CAL_knock_*` (detection, retard, octane scaling)
- **AC**: `CAL_ac_*` (compressor control)
- **Traction/TC**: `CAL_tc_*` (traction control)
- **OBD**: `CAL_obd_*` (diagnostics)

### Table Structures

Multi-dimensional calibration tables follow this pattern:
- Table data: `CAL_xxx` (1D or 2D array)
- X-axis: `CAL_xxx_X_<parameter>` (e.g., `_X_rpm`, `_X_load`)
- Y-axis: `CAL_xxx_Y_<parameter>` (for 2D tables)

Example:
```c
u8_angle_1/4-10deg[400] CAL_ign_base_manual;              // 20x20 table
u8_rspeed_125/4+500rpm[20] CAL_ign_base_manual_X_engine_speed;  // X-axis
u8_load_1173mg/255stroke[20] CAL_ign_base_manual_Y_load;        // Y-axis
```

## Working with This Code

### Finding Calibration Parameters

 - Search for `CAL_` prefix for definitions

### Understanding Memory Layout

- Runtime variables typically in `0x40001xxx` and `0x40002xxx` ranges

### Common Tasks

**Analyzing ignition timing**: Search for `CAL_ign_base_*` tables (separate for IPS transmission and manual)

**Finding sensor scaling**: Look for `CAL_sensor_*_scaling` and corresponding voltage/signal arrays

**Modifying fuel parameters**: Search `CAL_injtip_*` and `CAL_fuel_*` prefixes

**Understanding knock control**: Review `CAL_knock_*` parameters and related `_ign_retard_` settings

## Notes

- This is reverse-engineered code from binary firmware - variable names are analyst-assigned
- Function names like `FUN_xxxxxxxx` indicate Ghidra auto-generated labels
- Data locations like `DAT_xxxxxxxx` indicate Ghidra auto-generated labels 
- Memory-mapped hardware registers have addresses like `0xfff48xxx` (INTC), `0xfff8xxxx` (EQADC)
- The disassembly is part of a larger RomRaider tuning definition project for Lotus vehicles
- PowerPC32 architecture (MPC5500 series microcontroller)
- o2 sensor 1 is bank one pre cat, sensor 2 is bank 1 post cat. Sensor 5 is bank 2 precat; sensor 6 is bank2 post cat.