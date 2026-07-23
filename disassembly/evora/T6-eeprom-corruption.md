# T6 ECU EEPROM Corruption: Sudden Power Loss Bricking

## Platform

- **ECU**: Lotus/EFI Technology T6 engine management
- **MCU**: Freescale MPC5534 (PowerPC e200z3 core)
- **Flash**: C55FMC embedded flash with 8-bit ECC per 64-bit double-word
- **Firmware**: B13200091 (2011 Lotus Evora NA, US Federal)
- **Analysis date**: July 2026
- **Author**: Donour Sizemore

## Symptoms

- Sudden electrical loss (battery disconnect) with **key ON, engine OFF** can render the ECU non-operational
- Dash cluster displays **"ECM Comms Error"** — no CAN traffic from the ECU
- Engine will not crank or start
- The bootloader remains functional — a full reflash restores normal operation
- Not a hardware defect; reproducible across vehicles

## Root Cause

**Single-copy EEPROM persistence with no power-loss protection.** When the battery is disconnected with the key on, the ECU attempts to save learned adaptive values (LEA) to internal flash. If power is lost during the flash write, the sector is left partially programmed. On the next boot, reading the corrupted flash triggers an ECC machine-check exception before CAN is initialized, and the exception handler enters an infinite loop — permanently freezing the ECU.

## Detailed Chain of Events

### Step 1 — Key ON, Engine OFF, Main Loop Running

The main loop at `main()` (`B13200091.c:13404`) runs at approximately 1000 Hz. On every iteration it calls `shutdown()` at line 13443 to evaluate ignition state and power conditions.

### Step 2 — Battery Disconnected, shutdown() Triggered

`shutdown()` at `B13200091.c:21389` detects the voltage drop:

```c
if (sensor_adc_ign_voltage < (ushort)((ushort)CAL_ecu_ign_threshold << 2)) {
    ignition_on_flags = ignition_on_flags | 8;
}
```

The voltage falls below the threshold, and since the engine is not running (`engine_speed_16bit == 0`), the shutdown routine proceeds to save persistent data:

```c
// B13200091.c:21419-21428
if (((obd_ii_engine_speed == 0) &&
    (((lbf_state_flags & 8) != 0 || ((lbf_state_flags & 0x80) == 0)))) &&
   ((obd_ii_ecu_shutdown_timer == 0 || ...))) {
    if (shutdown_actions_done == false) {
        hc08_reset_release();
        EEPROM_save();               // ← FLASH WRITE BEGINS HERE
        shutdown_actions_done = true;
        WriteExternalEnableImmediate(1);
    }
    ...
}
```

### Step 3 — EEPROM_save() Erases and Writes Flash

`EEPROM_save()` at `B13200091.c:19410` computes CRCs over the LEA data in RAM, then writes it to flash:

```c
void EEPROM_save(void) {
    DAT_40004244 = 0x1508;
    uVar1 = CRC16((byte *)LEA_base, 0x1508);   // CRC of core block (5384 bytes)
    _LEA_crc_core = (uint)uVar1;
    obd_ii_dtc_process_all_mode_01();
    DAT_40004788 = 0x1a50;
    uVar1 = CRC16((byte *)LEA_base, 0x1a4c);   // CRC of full block (6732 bytes)
    _LEA_crc_full = (uint)uVar1;
    DAT_40001a90 = 0;
    WriteExternalEnableImmediate(0);
    EEPROM_write(LEA_base, 0x1a50);              // Write 6736 bytes to flash
}
```

`EEPROM_write()` at `B13200091.c:21236` does the actual flash programming:

```c
void EEPROM_write(int param_1, ulonglong param_2) {
    set_spr154_2c52();                     // Unlock flash controller
    lVar1 = (((param_2 & 0xffff) << 0x20) >> 0x23) * 8;  // Align to 8-byte boundary
    param_2 = param_2 & 7;                 // Remainder bytes
    watchdog_retrigger();
    flash_erase(0, 0, 4);                  // Erase LEA sector (0x10000-0x1BFFF)
    watchdog_retrigger();
    flash_write(0x10000, param_1, lVar1);  // ← VULNERABILITY WINDOW (~6736 bytes)
    watchdog_retrigger();
    if (param_2 != 0) {
        // Fill remainder with 0xFF and write final double-word
        ...
        flash_write(lVar1 + 0x10000, local_20, 8);
    }
    FUN_000573b4();                        // Verify / cleanup
    FUN_00057500();
    set_spr154_6c54();                     // Re-lock flash controller
}
```

The `flash_erase(0, 0, 4)` call maps to sector select value `4`, which targets:

```c
// B13200091.c:20940-20942
else if (DAT_400018b0 == 4) {
    DAT_400018a4 = DAT_400005ec + 0x10000;   // Start address
    DAT_400018a0 = 0xc000;                    // Size: 48 KB
}
```

This erases the flash sector spanning `0x10000–0x1BFFF`.

**The vulnerability window is the entire duration of `flash_write()`.** Writing 6736 bytes to C55FMC flash takes hundreds of milliseconds. If power is lost at any point during this write, some 64-bit double-words are programmed (with correct ECC for their new data) while others remain in the erased state (all `0xFF` with ECC for erased state). The result is an inconsistent ECC panorama across the sector.

### Step 4 — Next Boot: ECC Machine Check in copyCOD2RAM()

On the next power-up, execution proceeds through the bootloader (stored in a separate flash block at `0x00000–0x0FFFF`, unaffected) and reaches `main()`.

`main()` calls `init_devices()` at `B13200091.c:13353`, whose **first** call is `copyCAL2RAM()`:

```c
void init_devices(void) {
    copyCAL2RAM();                         // 1. ← Calls copyCOD2RAM() — READS 0x10000!
    init_gear_cal();                       //    NEVER REACHED
    init_obd_ii_config();                  //    NEVER REACHED
    ...
    init_flexcan_a();                      //    NEVER REACHED
    ...
}
```

`copyCAL2RAM()` at `B13200091.c:13282` calls `copyCOD2RAM()`:

```c
void copyCAL2RAM(void) {
    // ... calibration copy, init_intc_1() ...
    flash_erase_pending_flags = flash_erase_pending_flags | 0b00000010;  // SET BIT 1 (COD) ONLY
    copyCOD2RAM();                         // ← READS FROM 0x10000 — MACHINE CHECK!
    flash_erase_pending_flags = flash_erase_pending_flags & 0b11111101;  // NEVER REACHED
    ...
}
```

`copyCOD2RAM()` at `B13200091.c:54289` begins by reading the LEA flash area:

```c
void copyCOD2RAM(void) {
    // FIRST action: copy 32 bytes from 0x10000 (LEA flash) to RAM
    for (i = 0; i < 0x20; i = i + 1) {
        (&DAT_40008828)[i] = *(undefined1 *)(i + 0x10000);  // ← READS CORRUPTED FLASH
    }
    // THEN: read COD from 0x1C000, CRC check, rebuild if needed
    // ... NEVER REACHED ...
}
```

This is the **first read from `0x10000` in the entire boot sequence**, and it happens *before* `EEPROM_load()` at line 13361. Critically, at this point:

```
flash_erase_pending_flags = 0b00000010   (only bit 1 set — marks COD sector 0x1C000)
                                       (bit 0 NOT set — LEA sector 0x10000 is NOT marked)
```

**The MPC5534 flash controller detects an ECC error on read.** The C55FMC flash uses 8 bits of ECC per 64-bit double-word. A double-word that was partially programmed (new data written but ECC not finalized, or adjacent words in mixed states) produces an uncorrectable ECC error. This triggers **IVOR1 — Machine Check exception** on the PowerPC e200z3 core.

### Step 5 — Machine Check Handler: Erases the WRONG Sector, Then Hangs

The machine check handler (`FUN_000427c4`, named `init_flash_helper` in the C132E0278 variant symbol table) calls `FUN_000576d0()` at `B13200091.c:21293`:

```c
void FUN_000576d0(void) {
    set_spr154_2c52();                       // Unlock flash controller

    // flash_erase_pending_flags == 0b00000010 at this point
    if ((flash_erase_pending_flags & 1) != 0) {
        // BIT 0 = 0 → DOES NOT EXECUTE
        flash_erase(0, 0, 4);               // Erase LEA sector (0x10000) — SKIPPED
    }
    if ((flash_erase_pending_flags & 2) != 0) {
        // BIT 1 = 1 → EXECUTES
        flash_erase(0, 0, 8);               // Erase COD sector (0x1C000) — ERASES WRONG SECTOR
    }

    watchdog_retrigger();
    FUN_000573b4();
    set_spr154_6c54();

    do {
        // WARNING: Do nothing block with infinite loop
    } while(true);                           // ← CPU FROZEN PERMANENTLY
}
```

**The handler erases the COD sector (`0x1C000`) but leaves the corrupted LEA sector (`0x10000`) untouched.** The COD sector wasn't the problem — it may have been perfectly intact, or if it was also corrupted, erasing it is harmless. But the LEA sector, which contains the partially programmed double-words causing the ECC error, is never erased.

The handler then enters an infinite loop. The watchdog is not retriggered, no software reset is triggered. The CPU is frozen.

### Step 6 — Why Power Cycling (and a Plain Reset) Don't Fix It

This is the critical insight that explains the permanent bricking:

```
Power cycle → Bootloader → main() → init_devices() → copyCAL2RAM()
    → copyCOD2RAM() → reads 0x10000 → SAME ECC ERROR
    → machine check handler → flash_erase_pending_flags still == 0b00000010
    → erases COD sector again (already erased) → leaves LEA sector corrupted
    → infinite loop
```

**Every boot follows the exact same path.** The LEA sector at `0x10000` is never marked for erase (`flash_erase_pending_flags` bit 0 is never set before the read that triggers the exception), so the machine check handler never erases it. The corruption is permanent.

The only way out is a full reflash, which performs a bulk erase of all flash sectors (including `0x10000`) before reprogramming.

| Symptom | Mechanism |
|---|---|
| **"ECM Comms Error"** | `init_flexcan_a()` at line 13381 is never reached |
| **No engine start** | `main()` loop at line 13419 is never entered |
| **Persists across power cycles** | LEA sector corruption survives; handler erases the wrong sector on every boot |
| **A plain reset wouldn't fix it either** | Same code path, same flags, same wrong sector erased |
| **Bootloader works** | Bootloader at `0x00000–0x0FFFF` is in a different flash block |
| **Reflash fixes** | Bulk erase clears ALL sectors; reprogramming writes correct ECC for every double-word |

## Flash Memory Layout

```
0x00000000 ┌──────────────────────────┐
           │  Bootloader + Startup    │  Flash block 0 (64 KB)
           │  (Reset vector, IVOR     │  NOT affected by EEPROM writes
           │   handlers, C runtime)   │
0x00010000 ├──────────────────────────┤
           │  EEPROM: LEA Base        │  Flash sector #4 (48 KB)
           │  Learned Adaptive Values │  Written by EEPROM_save() →
           │  (6736 bytes used of     │  EEPROM_write() at shutdown
           │   48 KB sector)          │  ⚠ VULNERABLE TO POWER LOSS
0x0001C000 ├──────────────────────────┤
           │  EEPROM: Variant Codin   │  Flash sector #8 (16 KB)
           │  COD (VIN, options, CRC  │  Written by
           │  (68 bytes used)         │  EEPROM_commit_coding_to_flash()
0x00020000 ├──────────────────────────┤
           │  Calibration Data (CAL_*)│  Flash — read-only at runtime
           │  Tables, constants, axes │
0x00040000 ├──────────────────────────┤
           │  Main Application Code   │  Flash — read-only
           │  (FUN_* functions)       │
           └──────────────────────────┘
```

Both the LEA sector (`0x10000`) and COD sector (`0x1C000`) are within **flash block 1** of the MPC5534's low-address flash array. Erasing requires unlocking the C55FMC flash controller with array-specific passwords:
- `0xA1A11111` — low-address array
- `0xC3C33333` — mid-address array
- `0xB2B22222` — high-address array

## Why the CRC Check Doesn't Prevent This

`EEPROM_load()` does contain integrity checks — after loading the data from flash it computes CRC16 over both the core block (5384 bytes) and full block (6732 bytes) and compares against saved CRCs:

```c
// B13200091.c:19457-19471
_saved_crc_core = _LEA_crc_core;
_crc_core = CRC16((byte *)LEA_base, 5384);
// ... CRC comparison, conditional lea_cold_init() on mismatch ...
```

**But `EEPROM_load()` is never reached.** The machine check exception fires earlier, during `copyCOD2RAM()` inside `copyCAL2RAM()` — the very first call in `init_devices()`. `copyCOD2RAM()` does its own CRC check on the COD area (at `0x1C000`), but the ECC error fires on the LEA area (at `0x10000`) *before* any integrity check runs. The integrity checks are structurally incapable of catching ECC errors because reading the data to verify it is what triggers the fault.

Additionally, the 32-byte read in `copyCOD2RAM()` that triggers the exception has no CRC or integrity check at all — it is a raw copy of the program name prefix from the LEA flash into RAM, intended for the `prog_version_mismatch` comparison later in the same function.

## Why the Handler Erases the Wrong Sector

This is the core of the bug. The machine check handler uses `flash_erase_pending_flags` to decide which flash sectors to erase before hanging. But the flags are only set immediately before the corresponding EEPROM operation — and they're cleared immediately after. At the exact moment the first read from the corrupted `0x10000` area occurs, only the COD flag is set.

### flash_erase_pending_flags Bit Assignments

| Bit | Value | Sector | Address Range | Purpose |
|---|---|---|---|---|
| 0 | `0b00000001` | LEA | `0x10000–0x1BFFF` | Learned adaptive values |
| 1 | `0b00000010` | COD | `0x1C000–0x1FFFF` | Variant coding (VIN, options) |

### Flag State at Each Boot Stage

```
BOOT SEQUENCE                          flash_erase_pending_flags
───────────                            ────────────────────────
Power-on reset                         0b00000000  (BSS zero-init)

main()
  └─ init_devices()
       └─ copyCAL2RAM()
            ├─ init_intc_1()           0b00000000
            ├─ SET flags |= bit 1      0b00000010  ← COD flag set
            ├─ copyCOD2RAM()
            │    └─ READS 0x10000      *** ECC EXCEPTION ***
            │         Handler sees:     0b00000010
            │         → Erases COD?    YES (bit 1 = 1)
            │         → Erases LEA?    NO  (bit 0 = 0)
            │         → Infinite loop
            │
            ├─ CLEAR bit 1             NEVER REACHED
            └─ set_spr_IVOR2()         NEVER REACHED

       └─ EEPROM_load()                NEVER REACHED
            (would have set bit 0 before reading 0x10000,
             but the ECC error already fired in copyCOD2RAM)
```

The fix embedded in the normal code path is visible by looking at what `init_devices()` **intended** to do later:

```c
// B13200091.c:13360-13362 — NEVER REACHED when LEA is corrupted
flash_erase_pending_flags = flash_erase_pending_flags | 1;   // SET bit 0 (LEA)
EEPROM_load();                  // reads 0x10000 — safe if handler had bit 0
flash_erase_pending_flags = flash_erase_pending_flags & 0xfe; // CLEAR bit 0
```

If `EEPROM_load()` were the first to read `0x10000` (instead of `copyCOD2RAM()`), the handler would correctly erase the LEA sector. The bug is that `copyCOD2RAM()` reads `0x10000` **earlier**, before bit 0 is set, so the handler erases the wrong sector.

## Conditions Required for the Bug

| Condition | Required? | Reason |
|---|---|---|
| Key ON (ignition) | **Yes** | Main loop must be running; `shutdown()` called at 1000 Hz |
| Engine OFF | **Yes** | `shutdown()` only calls `EEPROM_save()` when `engine_speed_16bit == 0` |
| Battery disconnection | **Yes** | Causes instant voltage drop below `CAL_ecu_ign_threshold` |
| Power loss during `flash_write()` | **Yes** | Window is ~100-500 ms while 6736 bytes are written |
| ECC error on affected double-word | **Yes** | Only partially programmed words trigger machine check |
| Machine check handler hangs | **Yes** | `FUN_000576d0` infinite loop; no watchdog reset |

## Variants Affected

All T6-based ECUs share this EEPROM architecture:

| Variant | Vehicle | Affected? |
|---|---|---|
| B13200091 | Evora NA (2011) | **Yes** — this analysis |
| C132E0271 | Evora 400 (2017) | **Likely** — same `EEPROM_save()` flow |
| C132E0278 | Evora GT430 (2019) | **Likely** — same `init_flash_helper` handler (`000427c4`) |
| E132E0288 | Evora GT (2020–2021) | **Likely** — same T6 architecture |


## Recovery Options

### For Tuners/Technicians Encountering This in the Field

1. **Reflash the ECU** — A full flash image write erases and re-programs all sectors, including the corrupted `0x10000` area
2. There is no software-only recovery short of reflashing, since the ECU never boots far enough to respond to diagnostic commands

### For Firmware Engineers (Hypothetical Fixes)

1. **Dual-copy EEPROM (A/B scheme)**
   - Write to alternate location, verify, then update a version counter or magic number
   - On boot, read the version counter to determine which copy is valid
   - Only erase the stale copy after the new copy is fully written and verified
   - Cost: doubles flash usage for EEPROM area

2. **Journaled writes**
   - Write data in small chunks with per-chunk CRCs
   - On boot, replay or discard incomplete journals
   - The MPC5534's 16 KB minimum erase sector makes this challenging

3. **Fix the machine check handler to erase the correct sector**
   - The handler currently erases only the sector(s) marked in `flash_erase_pending_flags`, but bit 0 (LEA) is never set before the first read from `0x10000`
   - **Fix A (minimal)**: In `copyCAL2RAM()`, set `flash_erase_pending_flags \|= 1` (LEA) alongside bit 1 (COD) before calling `copyCOD2RAM()`, so the handler erases both sectors
   - **Fix B (handler-only)**: Change the machine check handler to always erase the LEA sector (`flash_erase(0, 0, 4)`) unconditionally when a machine check fires during boot, regardless of `flash_erase_pending_flags`
   - **Fix C**: After erasing, trigger a software reset instead of entering the infinite loop. The next boot would see all-0xFF data in both sectors, fail the CRC checks, rebuild COD from defaults, and run `lea_cold_init()` — recovering automatically
   - Any of these paired with Fix C (reset instead of hang) would make the ECU self-recovering

4. **Defer EEPROM writes to stable conditions**
   - Instead of writing immediately on voltage drop, write periodically when conditions are stable
   - Accept that the last few seconds of learned data may be lost on power failure
   - This is the approach used by many production ECUs

