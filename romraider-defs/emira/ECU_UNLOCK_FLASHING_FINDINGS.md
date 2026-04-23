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

## Unauthenticated Backdoor CAN Protocol (IDs 0x50, 0x51)

In addition to the standard UDS/CRP paths, a proprietary and unauthenticated CAN
protocol is present on IDs `0x50` and `0x51`:

- `emira.c:11026`: `flexcan_rx_50_51` unauthenticated receiver.
- `emira.c:11057`: Messages are collected into a 4096-byte buffer `DAT_40004700`.
- `emira.c:11574`: Command `0x06` triggers `FUN_00802740` (proprietary update).
- `emira.c:12433`: The "ECU ID" session check (`DAT_40000a94`) is initialized to
  `0` at boot, making the backdoor reachable by default.

This protocol provides an unauthenticated write primitive to several memory
targets, including the RSA public key area at `0x900`.

## RSA Signature Enforcement

The firmware has a higher-level RSA signature check:

- `emira.c:19864`: `signcheck()`.
- `emira.c:19873`: hashes `CALROM` plus program/header regions.
- `emira.c:19885`: loads the RSA public key.
- `emira.c:19891`: loads the firmware signature.
- `emira.c:19954`: checks whether the RSA public key area is blank.
- `emira.c:19986`: `rsa_sign_check()`.

### Cryptographic Weakness: Missing Padding Verification

The `signcheck` implementation contains a significant implementation flaw. While
it performs RSA decryption, it fails to validate the PKCS#1 v1.5 padding. It
only verifies that the final 20 bytes of the decrypted block match the computed
SHA1 hash:

```c
memcmp_rc1 = memcmp(certout + 108, &md, 20);
```

While forging a signature still requires the matching private key (unless a small
public exponent exploit is applicable), this omission significantly weakens the
security posture and facilitates signature forgery if the key material or
exponent are weak.

### Implications

- If the RSA public key area is blank, RSA verification is bypassed and the main
  software integrity requirement becomes the calibration CRC.
- If the RSA public key area is programmed, changing any calibration byte changes
  the hash covered by `signcheck()`, so the existing signature will no longer
  match.
- **RCE Path:** The unauthenticated 0x50/0x51 backdoor allows writing to the
  RSA public key area (`0x900`). An attacker can replace the Lotus public key
  with their own, then flash custom firmware signed with their matching private
  key.

## Exploit Path: RSA Key Swap via CAN Backdoor

This path provides a persistent unlock by replacing the ECU's root-of-trust. It
bypasses the need for the UDS `0x2E` stack overflow by using the built-in
unauthenticated CAN protocol.

1.  **Preparation:**
    - Generate a custom RSA-1024 key pair.
    - Prepare a patched calibration with the four unlock bytes and valid CRC16.
    - Sign the patched calibration using the custom private key.
2.  **Key Injection:**
    - Use the `0x50/0x51` CAN backdoor to send a Service `0x06` payload.
    - Target the RSA public key region at `0x900` with the custom public key.
    - If `0x900` is already programmed, this may require a separate erase
      primitive or a fallback to the `0x2E` RCE to drive the flash controller.
3.  **Authorized Flashing:**
    - Once the ECU trusts the custom public key, flash the signed, patched
      calibration via standard UDS Services `0x34`/`0x36`.
4.  **Verification:**
    - Reset the ECU. `signcheck()` will pass using the injected key, and
      `init_core_system` will set `ecu_unlocked = true` based on the patched
      calibration bytes.

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

Reachability refinement:

- The dispatcher at `emira.c:68846` routes UDS service `0x2E`
  (WriteDataByIdentifier) to `FUN_00a89a8c`, which calls the vulnerable
  `FUN_00a89070`.
- `FUN_00a89a8c` (`emira.c:86183-86243`) requires the active session byte to be
  `0x03` (extended diagnostic session), entered with an unauthenticated
  `0x10 03` request.
- The only gate before the `memmove` in `FUN_00a89070` is
  `FUN_00a4dfe4` (`emira.c:64856-64862`), which checks
  `FUN_00a0f338() == 0 && DAT_40003666 < 300`. That is a system-ready check,
  **not** UDS security access.
- The length used by the copy is `*(byte)(param_1 + 0x41) - 2`
  (`emira.c:86196`), so any attacker on the powertrain CAN bus who can enter
  extended session can drive up to ~253 bytes into an 84-byte stack buffer.

This is a memory-corruption/RCE research lead. It is not a safe or direct
calibration flashing path by itself, but it is the primitive that enables the
"RSA key programmed" bypass path described below.

## RSA Verification Cache Bypass

`rsa_sign_check` (`emira.c:19986-20009`) has a short-circuit that is not the
"key area blank" path:

```c
flash_key_is_programmed = rsa_key_flash_check();
if (flash_key_is_programmed == 0) { /* key blank, skip */ }
else {
  previously_verified = check_previous_verify();
  if (previously_verified != 0) { signcheck_succes = true; }   // skip signcheck()
  else { signcheck_succes = signcheck(); if (ok) cache_verify_result(); }
}
```

`check_previous_verify` (`emira.c:19943-19950`) is:

```c
memcmp(BYTE_ARRAY_4000795e, BYTE_ARRAY_0082136c, 8) == 0
```

Eight bytes of RAM at `0x4000795e` compared against a fixed constant in ROM at
`0x0082136c`. The ROM constant is known from any firmware dump, so the cache is
a plain "skip RSA this boot" flag, not a cryptographic binding.

`cache_verify_result` (`emira.c:19912-19924`) sets the cache to the ROM
constant after a successful `signcheck()`.

### Cache is persistent, not plain RAM

The 0x128-byte region containing the cache (`0x4000795c..0x40007a83`) is
backed by non-volatile storage and re-validated with its own CRC16:

- `FUN_0080f1c0` (`emira.c:15273-15283`): recomputes
  `CRC16(&DAT_4000795c, 0x126, 0xffff)` into `DAT_40007a82` and persists the
  region via `FUN_0080f0e0`.
- `FUN_0080ee9c` (`emira.c:15180-15197`): loads the region back.
- Boot-time loader `FUN_0080f244` (`emira.c:15288-15336`) calls
  `FUN_0080ee9c`, checks the CRC, and if it matches, trusts the cache.
- `FUN_0080f448` (`emira.c:15340-15355`): reloader / CRC validator with
  "zero and re-persist" on mismatch.

The CRC-over-NV pattern means a valid cache survives reset and power cycle
until an explicit clear happens.

### Cache clearers

`verification_result_clear` (`emira.c:19930-19938`) memsets the 8 bytes and
calls `FUN_0080f1c0` to persist. Its callers are all flash-erase-program
entry points for the signed regions:

- `emira.c:12980` - high-level erase path for CAL (`0x20000`).
- `emira.c:13074` - erase path for program (`PTR_DAT_00a00000`).
- `emira.c:13103` - erase path for `0xf00000`.
- `emira.c:13320` - `FUN_00808534` program-area helper.
- `emira.c:13513` - `FUN_00808e40` helper for `0xf00000`.

The cache is **not** cleared by any timer, watchdog, periodic task, session
transition, or signcheck failure - only by re-erasing a signed region through
the high-level wrapper.

### Exploit Path With RSA Key Programmed

This path does not require erasing the RSA key flash sector. The attacker
keeps the existing signed firmware and RSA key in place and forges a
"previously verified" state that survives reboot.

1. Enter extended diagnostic session:
   `0x10 03` over CAN (no security access required).
2. Trigger the stack overflow in `FUN_00a89070` via an oversize `0x2E`
   request and gain code execution in RAM.
3. From the RCE payload, program the patched calibration into the CAL
   region at `0x20000..0x2ffff`:
   - Include the four unlock bytes at `+0x0e2`, `+0x218`, `+0x290`, `+0x337`.
   - Store a correct calibration CRC16 at `CALBASE + 0xfffe`.
   - Drive the flash controller directly rather than through the high-level
     programming wrappers, so that `verification_result_clear` is not called.
4. From the RCE payload, write the 8 verify-cache bytes taken from ROM
   `0x0082136c` into RAM `0x4000795e`.
5. Recompute `CRC16(&DAT_4000795c, 0x126, 0xffff)` and store it at
   `DAT_40007a82`, then call `FUN_0080f1c0` (or its underlying
   `FUN_0080f0e0`) to persist the cache region to NV.
6. Reset.

On the next boot, `firmware_integrity_validate` -> `rsa_sign_check` sees
`check_previous_verify() == true` and returns success without running
`signcheck()`. The patched, unlocked calibration runs. The RSA public key
stays programmed and untouched.

### Re-Exploit Conditions

The bypass holds across reset and power cycle until one of these events:

- Any flash erase that goes through the high-level wrappers at
  `emira.c:12980`, `13074`, `13103`, `13320`, `13513`. In practice that
  means any subsequent OEM or bench reprogramming of CAL, program, or the
  `0xf00000` region.
- Any code path that writes over the cache region without updating the
  companion CRC, so the boot-time CRC check fails and the region is zeroed
  (`emira.c:15325`, `15349`).

After such an event, the attacker must re-run steps 1-6. The RCE primitive
itself is not consumed by exploitation; the calibration stays patched across
the bypass collapse, but a subsequent boot with a cleared cache will run
`signcheck()`, find the CAL hash no longer matches the stored signature, and
fail. At that point the only recovery is reverting to a signed calibration
(or re-executing the bypass before that boot path runs, which is not
generally possible without debug access).

### Variant: Per-Boot Bypass Without Persist

If writing the cache to NV is undesirable (to avoid leaving a forensic
artifact), the attacker can skip step 5 and re-trigger the RCE on every
boot while the ECU is in a state where
`FUN_0080f244`/`FUN_0080f448` zeros the cache. The exploit then re-seeds
`BYTE_ARRAY_4000795e` in RAM before any code path that consults
`rsa_sign_check` runs. This is noisier and timing-sensitive, but does not
touch NV. The patched calibration in CAL flash persists either way; only
the cache part of the bypass needs re-seeding.

### Caveats

- `rsa_sign_check` is only one gate. Check whether any later runtime code
  re-hashes CAL and compares to the stored signature independently of the
  cache. A quick audit of direct `signcheck()` callers vs
  `rsa_sign_check()` callers will answer this.
- Step 3 assumes the RCE payload can drive the low-level flash controller
  directly. If the only reachable write primitives go through
  `FUN_00819cd8` or `FUN_00819f30`, the attacker must either (a) call the
  clear themselves and then restore the cache after, or (b) interpose
  between the clear and any subsequent integrity check.
- The ROM constant at `0x0082136c` must be read from the running firmware
  or a dump of the same variant. It is not compile-time randomized per
  unit, based on the decompile.

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
   - Do not assume unsigned calibration changes will boot through the normal
     UDS programming flow - the high-level erase wrappers call
     `verification_result_clear`, which invalidates the "previously verified"
     cache and forces `signcheck()` to run on the modified calibration.
   - The cache-bypass path described in "RSA Verification Cache Bypass" is
     available via the `0x2E` stack overflow RCE, and works without erasing
     the RSA key sector. It survives reset and power cycle, but collapses
     the next time a signed region is re-flashed through the high-level
     wrappers.
   - Use an already-signed image, an OEM signing route, or bench/debug access
     with full flash backup and recovery if a durable, tamper-evident-proof
     path is required.
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
