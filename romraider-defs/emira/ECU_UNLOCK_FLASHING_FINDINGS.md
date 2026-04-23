# Emira ECU Unlock and Calibration Flashing Findings

## Scope

This note summarizes findings from reviewing `emira.c` for paths that can set
`ecu_unlocked == true`, write the calibration region, and bypass or satisfy the
firmware signature checks. The analysis is based on the Ghidra C decompile, so
symbol names are mostly inferred and line numbers may shift if the decompile is
regenerated.

## High-Level Conclusion

There is a code-supported path to `ecu_unlocked == true`, but it is not a normal
runtime setter. The firmware sets the flag during initialization after checking
four magic bytes in the active calibration image. A practical unlock path is to
patch those calibration bytes, correct the calibration CRC, flash the patched
calibration image through an authorized programming path, and reset the ECU.

If the RSA public key area is programmed, arbitrary calibration changes are also
covered by the firmware signature check. In that state, a patched calibration is
expected to fail signature validation unless it is signed by the matching private
key, comes from an already-valid signed image, or the verification logic/keying is
changed through a separate authorized recovery path.

## Unlock Condition

The only direct assignment found for `ecu_unlocked = true` is in
`init_core_system`:

```c
if ((((*(char *)(CALBASE_addr + 0xe2) == 0xd) &&
      (*(char *)(CALBASE_addr + 0x218) == -72)) &&
     (*(char *)(CALBASE_addr + 0x290) == 0x45)) &&
    (*(char *)(CALBASE_addr + 0x337) == -44)) {
  ecu_unlocked = true;
}
```

Relevant source locations:

- `emira.c:23631` computes `caldata_crc`.
- `emira.c:23633` checks the four calibration unlock bytes.
- `emira.c:23793` exposes the current unlock state through `get_ecu_locked_state`.
- `emira.c:24823` copies calibration flash into RAM and sets `CALBASE_addr`.
- `emira.c:25489` gates the proprietary CAN `0x40`-`0x47` path on this flag.

The unlock bytes are:

| Calibration offset | Required byte |
| --- | --- |
| `0x0e2` | `0x0d` |
| `0x218` | `0xb8` |
| `0x290` | `0x45` |
| `0x337` | `0xd4` |

`CALBASE_addr` is populated from the calibration flash copy path. The decompile
copies from flash address `0x20000` into `CAL_base`, so if the active calibration
base is `0x20000`, the corresponding flash addresses are:

| Flash address | Required byte |
| --- | --- |
| `0x200e2` | `0x0d` |
| `0x20218` | `0xb8` |
| `0x20290` | `0x45` |
| `0x20337` | `0xd4` |

## Calibration CRC

The calibration has a separate CRC check from the RSA signature check. The
firmware computes:

```c
caldata_crc = CRC16((byte *)(CALBASE_addr + 0x20), DAT_40003294 + -0x22);
```

Later runtime checks compare that value against the word at
`CALBASE_addr + 0xfffe`.

Implication: any patched calibration must have the stored calibration CRC
updated. For a 64 KiB calibration block, the stored CRC appears to be the last
two bytes.

## CAN/UDS Programming Path

The UDS-style programming handlers are present:

- Service `0x10`: diagnostic session control.
- Service `0x27`: security access.
- Service `0x31`: routine control.
- Service `0x34`: request download.
- Service `0x36`: transfer data.
- Service `0x37`: transfer exit.

Important locations:

- `emira.c:16197`: security access handler.
- `emira.c:16279`: request download handler.
- `emira.c:16334`: transfer data handler.
- `emira.c:16382`: transfer exit handler.
- `emira.c:16799`: routine control handler.

The download path is gated by both programming session and security access:

- `DAT_400018be == 2`: programming session.
- `DAT_400018de == 1`: security-unlocked state.

The transfer path writes to entries selected from a fixed allowed-region table,
not arbitrary memory. The calibration region is one of the accepted regions.

## Factory/CRP Update Path

The repo already contains CRP tooling that models the T6 calibration target.
In `lib/crp08.py`, T6 calibration uses target `0x5`, and comments map that to
flash address `0x020000` with payload size up to `0x10000`.

That aligns with the decompile's calibration base of `0x20000`.

For an authorized bench workflow, the expected shape is:

1. Start from the ECU's active `calrom.bin`.
2. Patch the four unlock bytes.
3. Recompute and store the calibration CRC.
4. Package as a T6 calibration CRP.
5. Upload through the bootloader/update protocol.
6. Reset the ECU and confirm `ecu_unlocked`.

The existing `lib.calibration unlock` helper is not Emira-specific as-is. It
writes a contiguous unlock magic used by older platforms, while this firmware
checks four scattered calibration bytes.

## RSA Signature Enforcement

The firmware has a higher-level RSA signature check:

- `emira.c:19864`: `signcheck()`.
- `emira.c:19873`: hashes `CALROM` plus program/header regions.
- `emira.c:19885`: loads the RSA public key.
- `emira.c:19891`: loads the firmware signature.
- `emira.c:19954`: checks whether the RSA public key area is blank.
- `emira.c:19986`: `rsa_sign_check()`.

Critical behavior:

```c
flash_key_is_programmed = rsa_key_flash_check();
if (flash_key_is_programmed == 0) {
  signcheck_succes = true;
}
```

Implications:

- If the RSA public key area is blank, RSA verification is bypassed and the main
  software integrity requirement becomes the calibration CRC.
- If the RSA public key area is programmed, changing any calibration byte changes
  the hash covered by `signcheck()`, so the existing signature will no longer
  match.

Routine control appears to expose status:

- Routine `0x0200` calls `FUN_0081de84`, which reports key/certificate/signature
  status.
- Routine `0x0205` calls `rsa_sign_check()` directly.

## RSA Key Area and Reset/Blanking

The RSA public key area is treated as a low-memory programming target:

- Target selector `0xf` maps to address `0x900`.
- Expected size is `0x84`.
- The region is accepted for programming only if it is already blank.
- If it is not blank, the parser returns the "device not blank" path.

Relevant locations:

- `emira.c:11688`: target selector maps to `0x900`.
- `emira.c:11713`: accepts `0x900` only when `rsa_public_key` is blank.
- `emira.c:11767`: returns the device-not-blank path if the key is already
  programmed.
- `emira.c:12774`: erase/setup handling for the `0x900` target.
- `emira.c:18633`: low-level programming setup for the `0x900` target.

No clean software path was found that blanks only the RSA key after it is
programmed. Flash bits cannot be changed from programmed back to erased without
erasing the containing flash sector. The containing low sector also appears to
hold adjacent bootloader/config data around `0x800`, `0x810`, `0x818`, `0x820`,
`0x840`, `0x860`, and `0x880`, so a broad erase is high risk without a complete
backup and recovery method.

## Buffer Overflow Candidate

An unrelated diagnostic handler has a stack overflow candidate:

- `emira.c:85259`: local buffer `abStack_54[84]`.
- `emira.c:85274`: copies `*param_3` bytes into that buffer without a local cap.
- `emira.c:86097`: caller appears to derive the length from request data.

This is a memory-corruption/RCE research lead, but it is not a safe or direct
calibration flashing path. Even with code execution, persistent RSA key
replacement still faces the flash-sector erase problem described above. Treat
this as a bench-only vulnerability research item, not as the preferred unlock
workflow.

## Practical Path Forward

Recommended sequence for authorized bench work:

1. Dump the active calibration and the low security/config area.
2. Query routine `0x0200` or read `0x900..0x983` to determine whether the RSA
   key area is blank.
3. If blank:
   - Patch the four calibration unlock bytes.
   - Recompute the calibration CRC.
   - Package and flash the calibration via the factory/CRP path or UDS
     programming path.
4. If programmed:
   - Do not assume unsigned calibration changes will boot.
   - Use an already-signed image, an OEM signing route, or bench/debug access
     with full flash backup and recovery.
   - Avoid attempting to erase the RSA key sector without a complete low-sector
     image and a proven restore procedure.

## Open Questions

- Confirm whether production Emira ECUs have the RSA public key region populated.
- Confirm the exact calibration CRC length source `DAT_40003294` for the active
  calibration variant.
- Confirm whether routine `0x0200` can be queried reliably before entering
  programming mode.
- Validate the T6 CRP packaging and upload path against an actual Emira ECU on
  a bench harness.
- Determine whether any official update package already contains an unlocked
  calibration image.
