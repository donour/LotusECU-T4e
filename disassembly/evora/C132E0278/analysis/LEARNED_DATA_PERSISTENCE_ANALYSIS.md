# Learned Data and Persistence Analysis

## Persistence envelope

The C132E0278 learned-data image is a contiguous `0x1BE4`-byte RAM block:

| Region | Address / size |
|---|---|
| Runtime image | `LEA_base = 0x400030E8` |
| Length | `0x1BE4` bytes |
| Internal-flash mirror | `EEPROM_lea_base = 0x00010000` |
| Flash address conversion | `0x10000 + (RAM address - 0x400030E8)` |

Despite the `EEPROM_*` names, the persisted copy is in internal flash. `EEPROM_load()` at `0x0005472C` calls the common loader for `0x1BE4` bytes. `EEPROM_save()` at `0x00054688` writes the same image through `EEPROM_write_learned_data()` at `0x0005B15C`.

The save manager writes once during orderly shutdown when ignition is low, engine speed is zero, shutdown hold conditions are satisfied, and ECU voltage is adequate. A confirmed P0562 path is explicitly accommodated. Completion latches `shutdown_eeprom_saved` to prevent repeated programming.

The image includes adaptive engine data, OBD learned state, trip/statistical data, catalyst/misfire history, and other persistence buffers. “LEA” must not be read as “only fuel/ignition learning.”

## Integrity and migration domains

There are two nested CRC/size domains:

| Domain | Payload | Size field | CRC field |
|---|---|---|---|
| Core adaptive | `[+0x0000, +0x1638)` | `lea_base_size` at `0x4000471C` = `0x1638` | `lea_crc_core` at `0x40004720` |
| Full image | `[+0x0000, +0x1BE0)` | `lea_write_size` at `0x40004CC4` = `0x1BE4` | `lea_crc_full` at `0x40004CC8` |

The full CRC excludes its own final four bytes but includes the full-size field. Both use the firmware CRC16/ARC implementation.

The first 32 bytes contain the saved program-version string and are compared with `ecu_prog_version` at flash `0x000CE958`. A separate calibration/version word at `0x4000471A` is checked against a flash-derived value.

Reset policy is intentionally tiered:

| Failure | Result |
|---|---|
| Core size/CRC invalid | Full factory reset |
| Calibration/version word mismatch | Full factory reset |
| Full size/CRC invalid | Reset OBD/trip portion while preserving core adaptives |
| Program-version mismatch | Reset OBD/trip portion while preserving core adaptives |
| Coding change | Clear DTC/freeze-frame state and reinitialize O2/catalyst data |

Status flags distinguish core CRC (`0x4000`), full CRC (`0x8000`), program mismatch (`0x04`), calibration mismatch (`0x08`), factory reset (`0x10`), adaptive reset (`0x20`), and OBD/trip reset (`0x40`).

## Core learned structures

### Alpha-N load correction

| Item | RAM | LEA offset | Flash mirror |
|---|---:|---:|---:|
| RPM axis, 20 x u8 | `0x40003108` | `+0x20` | `0x10020` |
| TPS axis, 20 x u8 | `0x4000311C` | `+0x34` | `0x10034` |
| Learned cells, 400 x u8 | `0x40003130` | `+0x48` | `0x10048` |

`engine_load()` at `0x00060FF8` reads this 20x20 table and obtains the active cell through `learneddata_get_table_cell_and_enable_flag`. The 200 Hz learning path moves the selected cell by one count after stabilization when coolant, accumulated MAF, TPS/RPM steadiness, injection/transient state, torque intervention, ESP, and VVT-error gates permit it. The error compares modeled Alpha-N load with measured MAF load.

Reset copies both calibrated axes and fills all 400 cells with `100` in `lea_reset3()` at `0x000549D0`.

### Torque-to-TPS scaling

| Item | RAM | LEA offset | Flash mirror |
|---|---:|---:|---:|
| RPM axis, 20 x u8 | `0x400032C0` | `+0x1D8` | `0x101D8` |
| Load axis, 20 x u8 | `0x400032D4` | `+0x1EC` | `0x101EC` |
| Scaling cells, 400 x u8 | `0x400032E8` | `+0x200` | `0x10200` |

The cells are typed as `val/100`, seeded to `100`, and multiply the calibrated load-to-TPS feed-forward surface. Learning adjusts the active cell by one count from the relationship between current TPS and learned idle-relative TPS under stable, qualified conditions and below the knock-related TPS threshold.

The table's purpose, dimensions, persistence, reset, and use in throttle feed-forward are high confidence. The exact density-normalized load value used as its Y coordinate is not recovered correctly in `engine_load()`; the decompiler currently collapses that value to zero. Original instructions or an adjacent firmware variant are required before documenting the indexing arithmetic.

### Long-term octane learning

`LEA_octane_scaler[6]` is six u16 values at `0x4000347C`, LEA offset `+0x394`, flash `0x10394`. Each cylinder saturates from `0..0xFFFF`.

`octane_scaler_update()` at `0x000779EC` builds the short-term knock evidence from volatile per-cylinder retard data. `octane_scaler_learn_update()` at `0x00077B1C` increments long-term octane evidence while the short-term result is nonzero and decrements it by a calibrated step when the short-term result is zero. Ignition blending and diagnostics consume the persisted long-term values.

`LEA_ign_knock_retard[6]` at `0x40001E30` is outside the persisted envelope despite its prefix. It is volatile input to learning, not saved long-term data.

### Fuel trims

Zoned long-term learns are four bytes:

| Bank / zone | RAM | Offset |
|---|---:|---:|
| Bank 1 zone 2 | `0x40003478` | `+0x390` |
| Bank 1 zone 3 | `0x40003479` | `+0x391` |
| Bank 2 zone 2 | `0x4000347A` | `+0x392` |
| Bank 2 zone 3 | `0x4000347B` | `+0x393` |

They use signed-centered encoding with reset value `0x80`; conversion is approximately `int8(raw ^ 0x80) * 500 / 128` into the ECU's LTFT units.

Additive idle learns are signed microseconds at `0x40003488` (bank 1) and `0x4000348A` (bank 2). `o2_fuel_learn_100ms()` at `0x0006FBF4` adjusts them at stable low airflow. Mid/high-airflow conditions update the zoned byte learns.

Learning requires closed loop and extensive air-path, temperature, barometric, fuel-level, accumulated-mass, purge, stability, and failure-bit qualification. Both banks use analogous logic. Reset sets additive values to zero and zoned values to `0x80`.

### Idle-air learning

Four persisted idle-air values distinguish warm/cold and A/C off/on:

| Condition | RAM |
|---|---:|
| Warm, A/C off | `0x4000378C` |
| Warm, A/C on | `0x4000378E` |
| Cold, A/C off | `0x40003B9C` |
| Cold, A/C on | `0x40003B9E` |

Their control use and qualification are described in `VVT_IDLE_THERMAL_ANALYSIS.md`. All four are cleared by the adaptive reset path.

## Reset, validation, and repair

`lea_full_factory_reset()` at `0x00059D4C` calls `reset_learned_adaptive_values()` at `0x00059D7C` and resets the OBD/trip region. `lea_reset3()` clears octane, knock baselines, idle learns, fuel learns, and both 20x20 adaptive maps, copying calibrated axes and seeding their cells.

Raw-binary Ghidra analysis resolves the duplicated routines and both `EEPROM_load()` call targets.
`lea_validate_and_reseed_adaptive_tables()` at `0x00059DD8` validates catalyst MAF bins and the
Alpha-N/torque-to-TPS axes, clearing or reseeding learned payloads after an axis change.
`lea_sync_adaptive_axes_from_calibration()` at `0x00059FF8` then copies the selected catalyst bins
and current calibrated axes into the persisted image.

A diagnostic reset command accepts `diag_lea_reset_trigger == 0x5352` (`SR` in big-endian byte order), runs the main adaptive reset subset, and acknowledges `0x4B4F` (likely an endian-rendered `OK`). It does not clear the entire statistical/OBD persistence envelope.

## Electronic-throttle fault-capture group

`tps_fault_capture_reset()` at `0x0005A18C` clears four adjacent 32 x u16 buffers:

| Buffer base | Extent |
|---:|---:|
| `0x40003F54` | `0x40` bytes |
| `0x40003F94` | `0x40` bytes |
| `0x40003FD4` | `0x40` bytes |
| `0x40004014` | `0x40` bytes |

The original binary supplies the missing xrefs. `tps_fault_capture_reset()` at `0x0005A18C` clears
this group, while `tps_capture_fault_data()` at `0x000AD664` produces it from the 1 kHz electronic-
throttle initialization/calibration state machine:

- `0x40003F54`: a chronological snapshot of the preceding 32 smoothed TPS track-A samples;
- `0x40003F94` and `0x40003FD4`: rolling track-A/track-B closed/calibration sample histories;
- `0x40004014`: elapsed 1 kHz calls between captured calibration faults.

The adjacent fields retain runtime and ECU-run timestamps, SIU reset status, ECU voltage, an
auxiliary ADC sample, fault/sample counts, and saturating qualification counters. This is a
persistent throttle-calibration fault forensic record, not a generic histogram group.

## Important naming cautions

- `maf_comp1_learned` at `0x40001C46` is outside `LEA_base` and is not persisted by this envelope.
- `LEA_ign_knock_retard` at `0x40001E30` is likewise volatile.
- `EEPROM_lea_base` is internal flash, not necessarily external EEPROM.
- Symbol scaling for some factor tables is supported by types and arithmetic but remains medium confidence until logged/raw values are correlated.

## Next evidence

1. Produce a complete byte map of the non-core OBD/trip region `+0x163C..+0x1BDF`.
2. Finish semantic names for the secondary throttle-fault qualification counters.
3. Verify shutdown brownout/programming behavior on hardware before altering persistence code.
