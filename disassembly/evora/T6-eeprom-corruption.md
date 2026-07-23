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

### Step 4 — Next Boot: ECC Machine Check

On the next power-up, execution proceeds through the bootloader (stored in a separate flash block at `0x00000–0x0FFFF`, unaffected) and reaches `main()`.

`main()` calls `init_devices()` at `B13200091.c:13353`:

```c
void init_devices(void) {
    copyCAL2RAM();                         // 1. Copy calibration → RAM (different flash area)
    init_gear_cal();
    init_obd_ii_config();
    init_intc_1();                         // 2. Configure interrupt controller
    flash_erase_pending_flags = flash_erase_pending_flags | 1;
    EEPROM_load();                         // 3. ← READS FROM 0x10000 — MACHINE CHECK!
    flash_erase_pending_flags = flash_erase_pending_flags & 0xfe;
    set_spr_IVOR2();
    init_siu();                            //    (SIU init — configures pin mux, pads)
    init_eDMA();
    init_eqADC();
    init_pinmux_and_iosetup();
    ...                                    //    various peripheral inits
    init_flexcan_a();                      // 4. CAN init — BUT WE NEVER GET HERE
    init_flexcan_filters();
    ...
}
```

`EEPROM_load()` at `B13200091.c:19432` calls `load_saved_LEA(LEA_base, 0x1a50)` at line 19449, which reads from the `EEPROM_lea_base` pointer — confirmed in the symbol table as flash address `0x00010000`:

```
# data_symbols.tsv:858
00010000    EEPROM_lea_base    char[32]    32    USER_DEFINED
```

```c
int load_saved_LEA(char *param, int size) {
    pcVar4 = EEPROM_lea_base;              // = 0x00010000 (flash)
    while (size-- != 0) {
        *param++ = *pcVar4++;              // ← Reads partially programmed flash
    }
}
```

**The MPC5534 flash controller detects an ECC error on read.** The C55FMC flash uses 8 bits of ECC per 64-bit double-word. A double-word that was partially programmed (new data written but ECC not finalized, or adjacent words in mixed states) produces an uncorrectable ECC error. This triggers **IVOR1 — Machine Check exception** on the PowerPC e200z3 core.

### Step 5 — Machine Check Handler: Infinite Loop

The machine check handler (`FUN_000427c4`, named `init_flash_helper` in the C132E0278 variant symbol table) calls `FUN_000576d0()` at `B13200091.c:21293`:

```c
void FUN_000576d0(void) {
    set_spr154_2c52();                       // Unlock flash controller

    if ((flash_erase_pending_flags & 1) != 0) {
        watchdog_retrigger();
        flash_erase(0, 0, 4);               // Erase LEA sector (0x10000)
    }
    if ((flash_erase_pending_flags & 2) != 0) {
        watchdog_retrigger();
        flash_erase(0, 0, 8);               // Erase COD sector (0x1C000)
    }

    watchdog_retrigger();
    FUN_000573b4();                          // Clean up flash controller state
    set_spr154_6c54();                       // Re-lock flash controller

    do {
        // WARNING: Do nothing block with infinite loop
    } while(true);                           // ← CPU FROZEN PERMANENTLY
}
```

The handler attempts to recover by erasing the corrupted sectors (making them readable as all-0xFF), but then **hangs forever in an infinite loop**. Critically:

- The watchdog is **not** retriggered inside the infinite loop
- No software reset is triggered
- The CPU remains in this state until power is physically cycled — but cycling power restarts the same sequence, hitting the same corrupted flash

Because the machine check fires during `EEPROM_load()` (step 3 in `init_devices`), the handler runs before `init_flexcan_a()` (step 4). The ECU never initializes CAN, never enters the main loop, and never starts the engine.

### Step 6 — The ECU is Bricked

| Symptom | Mechanism |
|---|---|
| **"ECM Comms Error"** | `init_flexcan_a()` at line 13381 is never reached |
| **No engine start** | `main()` loop at line 13419 is never entered |
| **Persists across power cycles** | Corrupted flash is permanent; every boot hits the same ECC error |
| **Bootloader works** | Bootloader at `0x00000–0x0FFFF` is in a different flash block |
| **Reflash fixes** | Bulk erase clears all sectors; reprogramming writes correct ECC for every double-word |

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

`EEPROM_load()` does contain integrity checks. After loading the data from flash, it computes CRC16 over both the core block (5384 bytes) and the full block (6732 bytes) and compares against the saved CRCs:

```c
// B13200091.c:19457-19471
_saved_crc_core = _LEA_crc_core;
_crc_core = CRC16((byte *)LEA_base, 5384);
// ...
_core_block_invalid = false;
if ((_saved_crc_core != _crc_core) || (DAT_40004244 != 0x1508)) {
    _core_block_invalid = true;
}
// ...
if ((_core_block_invalid) || ...) {
    lea_cold_init();           // Reset LEA to defaults
}
```

**But the CRC check never executes** — the machine check exception fires during `load_saved_LEA()` at the first read of a corrupted double-word, *before* the CRC computation can run. The integrity check is structurally incapable of catching ECC errors because reading the data to verify it is what triggers the fault.

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

3. **Fix the machine check handler**
   - Instead of `while(true)`, trigger a software reset after erasing the bad sector
   - The next boot would see all-0xFF data, fail the CRC check, and run `lea_cold_init()` — recovering automatically
   - This is the **minimum change** that would prevent bricking

4. **Defer EEPROM writes to stable conditions**
   - Instead of writing immediately on voltage drop, write periodically when conditions are stable
   - Accept that the last few seconds of learned data may be lost on power failure
   - This is the approach used by many production ECUs

