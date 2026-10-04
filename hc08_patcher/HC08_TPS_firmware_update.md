# HC08 TPS max table update (T6 ECU)

This document specifies how to raise the HC08 monitor's TPS max table in a Lotus
T6 ECU program file so that it is never below the main calibration's TPS
scaling table, and how to repair the HC08 checksum afterwards. It is written to
be sufficient for re-implementing the tool in another language (planned: C#,
inside a GUI application) without access to this repository.

The reference implementation is `hc08_tps_sync.py` in this directory
(standard library only, ~300 lines). Where this document and the script
disagree, treat it as a bug and check both against the test vectors in
[§10](#10-test-vectors).

---

## 1. Background

The T6 ECU (EFI Technology, MPC5534 PowerPC main CPU) contains a second,
small Freescale **HC08** microcontroller that acts as an electronic-throttle
safety monitor. The HC08 firmware is not flashed separately: it is embedded as
a binary blob inside the main **PROG** image, and the PPC transfers it to the
HC08.

Both processors hold a 16-entry "TPS max vs rpm" table:

| Copy | Where | Used by |
|---|---|---|
| Calibration copy | calrom, romraider name `tps: scaling factor rpm` | main PPC |
| HC08 copy | inside the HC08 image embedded in PROG | HC08 monitor |

Tuning tools (romraider etc.) only edit the calibration. Raising the
calibration table without raising the HC08 copy leaves the monitor enforcing
the old, lower values. Note that even factory firmware is not always in sync
(see [§9](#9-known-firmwares)).

The HC08 image is protected by a 16-bit checksum. PROG holds the expected
checksum as an immediate operand of a PowerPC instruction and compares it at
runtime against the value the HC08 reports. So changing a byte of the HC08
table requires updating that immediate too, or the ECU will flag the HC08.

### What the tool does, in one paragraph

Read PROG (to be modified) and CAL (read only). Pick a profile by the
calibration ID. Locate the HC08 image via the PROG header, and the checksum
instruction via a byte-pattern search. Verify the calibration and HC08 rpm
axes agree and that the existing checksum is consistent. Compute
`new[i] = max(hc08[i], cal[i])` for each of the 16 breakpoints (**increases
only, never decreases**). If nothing increases, stop. Otherwise show the
per-breakpoint table, get user approval, write the new table bytes, recompute
the HC08 checksum, patch the 16-bit immediate, re-verify, back up the original,
and atomically replace PROG.

---

## 2. Inputs

### 2.1 PROG file (modified in place)

- Example: `T6EVRGT430E01_BIN.cpt`, `test.bin.cpt` (in this directory).
- It is the raw program image as flashed at main-CPU flash address
  **`0x40000`**. File offset 0 == flash address `0x40000`.
- Size varies by firmware/modification (C132E0278 stock: `0x98988` =
  625,032 bytes; a modified build seen: `0x98CFC`). **Never assume a size**;
  never change the size.
- It contains no firmware ID string; identification comes from CAL.
- If you only have a 1 MB full flash dump, PROG is bytes `0x40000..end`
  (e.g. `dd if=full.bin of=prog.cpt bs=4 skip=65536`). The tool itself does
  **not** accept full images by design: it always takes PROG + CAL.

### 2.2 CAL file (read only)

- Example: `C132E0278_TAB.20260628-93octane.cpt` (in `../patch/`).
- Raw calibration image as flashed at main-CPU flash address `0x20000`.
  File offset 0 == flash address `0x20000`.
- Begins with an ASCII calibration ID, space padded, e.g.
  `"C132E0278        05-07-2019 9:24"`. The tool reads the first **16 bytes**,
  decodes as ASCII (replace invalid bytes), and trims whitespace → `"C132E0278"`.
- Size varies (`0x69AC` for C132E0278). It must be at least
  `max(cal_table, cal_axis) + 16` bytes.

### 2.3 Byte order

Everything multi-byte on the PPC side is **big-endian**. The table entries are
single unsigned bytes.

---

## 3. Locating the HC08 image inside PROG

| PROG offset | Size | Content |
|---|---|---|
| `0x80` | 8 | ASCII `HC08CODE` (magic) |
| `0x88` | 4 | unknown (`AA AA AA AA` stock, `00 00 00 00` in one modified build); ignore |
| `0x8C` | 4 | big-endian **absolute main-flash address** of the HC08 image |

```
hc08_off = BE32(prog[0x8C..0x90]) - 0x40000      // offset of HC08 image within PROG
```

Validation (abort if any fail):
- `prog[0x80..0x88] == "HC08CODE"` (this also catches PROG and CAL being
  passed in the wrong order: a calibration file has no magic there)
- `0 <= hc08_off <= len(prog) - 0x2400`

C132E0278: `BE32 = 0x000D13F0` → `hc08_off = 0x913F0`.

### 3.1 HC08 address space

The HC08 image is mapped at **HC08 address `0xDC00`**, so:

```
prog_offset(hc08_addr) = hc08_off + (hc08_addr - 0xDC00)
```

Evidence: the image's checksum region ends at image offset `0x2400`, which maps
to `0x10000` (the HC08 vector table is `0xFFDC..0xFFFF`), and the reset vector
at image offset `0x23FE` is `0xDC89`, inside the image. Table addresses in
profiles are HC08 addresses so they can be copied straight from a Ghidra HC08
project.

---

## 4. HC08 checksum

### 4.1 Algorithm

Two regions of the HC08 image are summed, in this order:

| Image offsets | HC08 addresses | Length |
|---|---|---|
| `0x0000 .. 0x1FFF` | `0xDC00 .. 0xFBFF` | `0x2000` |
| `0x23DC .. 0x23FF` | `0xFFDC .. 0xFFFF` (vectors) | `0x24` |

Bytes `0x2000..0x23DB` of the image are **not** covered.

Per byte, starting from seed `0x0123`, with all arithmetic mod 2^16:

```
crc = (crc + (0xFF00 | ~byte)) & 0xFFFF
```

Because `byte` is 0..255, `(0xFF00 | ~byte) & 0xFFFF == 0xFFFF - byte`, so
each step is `crc = crc - byte - 1 (mod 65536)`. Closed form:

```
checksum = (0x0123 - Σ(byte + 1)) mod 0x10000
```

Both forms are verified identical on real data.

> **C# pitfall:** `~b` on a `byte` promotes to `int` and is negative. Either
> mask (`(ushort)((crc + (0xFF00 | ~b)) & 0xFFFF)`) or, clearer, use
> `crc = (ushort)(crc + 0xFFFF - b);` with `unchecked` arithmetic.

Note: `hc08_sum.py` also contains a `SUM_HC08_T4e` class (a CRC-16 variant
for the older T4e ECU). It is **not** used for T6. Do not port it for this
feature.

### 4.2 Where PROG stores the expected checksum

PROG contains this sequence (C132E0278, PROG offset `0x337B0`):

```
3C 60 40 00   lis    r3,0x4000
A0 03 4F 30   lhz    r0,0x4F30(r3)    ; checksum reported by the HC08 (RAM 0x40004F30)
54 04 04 3E   clrlwi r4,r0,16
3C 60 00 01   lis    r3,1             ; <-- pattern starts here
38 63 DA 01   addi   r3,r3,-0x25FF    ; immediate = expected checksum (0xDA01)
54 60 04 3E   clrlwi r0,r3,16         ; keep only low 16 bits
7C 00 20 50   subf   r0,r0,r4
7C 00 00 34   cntlzw r0,r0            ; equality test
```

`lis r3,1` + `addi` (sign-extended immediate) + `clrlwi …,16` always yields
exactly the 16-bit immediate, for any value `0x0000..0xFFFF`. So patching just
the two immediate bytes is correct even when the new checksum is below
`0x8000`. (An older script's comment called this a "subtract"; it is an
`addi` and the description above is the accurate one.)

### 4.3 Finding the instruction

Search PROG for this 12-byte pattern, where `?? ??` is any two bytes:

```
3C 60 00 01  38 63 ?? ??  54 60 04 3E
```

- Only accept matches whose start offset is a multiple of 4 (PPC
  instructions are word aligned).
- Require **exactly one** match; abort on 0 or >1.
- The immediate is at `match_start + 6` (2 bytes, big-endian).
- Do **not** include the `lhz` line in the pattern: its RAM offset differs
  per firmware (`0x4D48`, `0x4D78`, `0x4F30`, `0x50E8` seen).
- Do **not** search for the current computed checksum value; search with the
  wildcard, then compare. This lets the tool report "checksum already
  inconsistent" rather than "instruction not found".

The pattern is unique in all four T6 firmwares checked (see §9). The
instruction address is therefore not part of the profile.

---

## 5. Profiles (per-firmware configuration)

Table locations must be configurable. A profile is selected by exact match of
the calibration ID (or an explicit user override).

| Field | Meaning | C132E0278 |
|---|---|---|
| `cal_table` | CAL file offset of the 16 table values | `0x0E3E` |
| `cal_axis` | CAL file offset of the 16 rpm axis values | `0x0E2E` |
| `hc08_table` | HC08 **address** of the 16 table values | `0xDC42` (image +`0x42`) |
| `hc08_axis` | HC08 **address** of the 16 rpm axis values | `0xDC32` (image +`0x32`) |
| `size` | entries per table/axis | `16` |
| `cal_axis_rpm(x)` | cal axis byte → rpm | `x * 125 / 4 + 500` |
| `hc08_axis_rpm(x)` | HC08 axis byte → rpm | `x * 255 / 8` |
| `axis_tolerance_rpm` | max allowed |cal rpm − HC08 rpm| | `255 / 8` (= 31.875, one HC08 count) |

Sources:
- Cal offsets and cal axis scaling: romraider definition
  `romraider-defs/T6-EVORA--F430-V000E_defs.xml` (GT430), table
  `tps: scaling factor rpm`, values `uint8` at `0x0E3E`, X axis `rpm`
  `uint8` at `0x0E2E`, scaling `(x*125/4)+500` rpm.
- HC08 offsets: found by inspection, identical layout in 0231/0271/0278/0288.
- HC08 axis scaling: derived. `hc08_axis[i] == round(cal_rpm[i] * 8 / 255)`
  holds exactly for all 16 C132E0278 breakpoints (i.e. 8 bits span
  0..8160 rpm). An earlier guess of `rpm/32` failed at high rpm; don't use it.

Table values in both copies use the same unit: `percent = x * 100 / 255`.

In a C# port, profiles are a natural fit for a JSON file or settings class,
e.g.

```json
{ "C132E0278": { "calTable": "0x0E3E", "calAxis": "0x0E2E",
                 "hc08Table": "0xDC42", "hc08Axis": "0xDC32", "size": 16 } }
```

Keep the axis conversions as code (or as `scale`/`offset` numbers:
cal = `3.125*x + 500`, HC08 = `31.875*x + 0`).

### 5.1 Firmwares without the table

NA Evora firmware (B132E0091) has a different HC08 layout with **no**
rpm-dependent TPS max table: the region at image `+0x32` holds other data,
and everything after `+0x32` is shifted by 32 bytes compared with 0278. There
is no profile for it, and one must not be added by copying 0278's offsets. The
axis check would also reject it.

---

## 6. Procedure (exact order)

1. **Load** PROG and CAL fully into memory. PROG becomes a mutable buffer.
2. **Validate PROG header** (§3) → `hc08_off`. Do this before reading CAL so a
   swapped-argument mistake gives the clear "not a T6 PROG file" error.
3. **Select profile**: `name = override ?? cal_id`; abort if unknown. Check
   CAL length (§2.2).
4. **Find checksum instruction** (§4.3) → `insn_off` (offset of the 2-byte
   immediate).
5. **Axis check**: for i in 0..15:
   `|cal_axis_rpm(cal[cal_axis+i]) - hc08_axis_rpm(hc08[hc08_axis+i])| <= tolerance`.
   On failure, abort and list each failing index with both rpm values. This
   is the guard against mismatched PROG/CAL pairs and wrong offsets. **The
   axis is never written.**
6. **Checksum consistency**: `computed = checksum(prog)`;
   `embedded = BE16(prog[insn_off..+2])`. If they differ, abort ("HC08
   checksum already inconsistent"): something else has already modified the
   HC08 image and the tool must not paper over it.
7. **Compute new table**: `new[i] = max(hc08_table[i], cal_table[i])`.
8. **Nothing to do?** If `new == hc08_table`: report OK (and, if
   `cal_table != hc08_table`, show the table so the user sees which
   decreases were skipped). End without writing. CLI exit code 0.
9. **Show the diff** (§7) and the checksum change.
10. **Apply in memory**: write `new` at `prog_offset(hc08_table)`; recompute
    the checksum over the patched buffer; write it big-endian at `insn_off`.
11. **Re-verify from scratch**: re-run steps 2–4 on the patched buffer and
    assert: HC08 table == `new`; computed checksum == embedded == new
    checksum; buffer length unchanged.
12. **Approval**: in report-only mode stop here (exit 1 = "update needed").
    Otherwise ask the user (default **No**). Declined → exit 1, file untouched.
13. **Backup**: copy the original PROG file to
    `<PROG>.<YYYYMMDD-HHMMSS>.bak` (unless the user opted out).
14. **Atomic write**: write the buffer to a temp file in the same directory,
    then rename over PROG (`os.replace`; in .NET `File.Replace` or
    `File.Move(tmp, path, overwrite: true)`). Delete the temp file on failure.

Expected diff after a successful run: exactly the changed table bytes plus
the 2 immediate bytes. Nothing else in PROG may change.

### 6.1 Why increases only

The user's requirement: the HC08 limit must only ever be raised. Because both
tables share the same rpm breakpoints and the HC08 interpolates linearly
between breakpoints, taking the elementwise max guarantees the resulting
HC08 curve is ≥ the previous HC08 curve **and** ≥ the calibration curve at
every rpm, not just at breakpoints. This makes the outcome easy to reason
about: running the tool can never make the monitor stricter, and running it
again is a no-op.

### 6.2 Exit codes (CLI) / outcomes (GUI)

| Code | Meaning | GUI equivalent |
|---|---|---|
| 0 | Nothing to raise, or patched successfully | Success / "Up to date" |
| 1 | A raise is needed (report-only mode), or user declined | "Update available" / "Cancelled" |
| 2 | Error (any abort condition) | Error dialog, file untouched |

### 6.3 Error conditions (all abort with no write)

| Condition | Message gist |
|---|---|
| No `HC08CODE` at PROG+0x80 | not a T6 PROG file, or PROG/CAL swapped |
| HC08 offset outside PROG | header pointer invalid |
| Unknown calibration ID | no profile for `<id>` (list known) |
| CAL too short | calibration too short for profile |
| Checksum pattern 0 or >1 matches | expected 1 HC08 checksum instruction, found N |
| Axis mismatch | list `[i] cal X rpm vs hc08 Y rpm` |
| Embedded ≠ computed checksum | HC08 checksum already inconsistent |

---

## 7. User-facing report

Header lines:

```
Calibration : C132E0278  (profile C132E0278)
HC08 image  : PROG+0x913f0, table @ HC08 0xdc42
Checksum    : insn imm @ PROG+0x337c2
```

Per-breakpoint table (one row per index). `rpm` comes from the cal axis;
percent = `x*100/255` to 1 decimal place. Action is `raise +Δ%` where
`new != old`, `keep (cal −Δ%, decrease skipped)` where `cal < old`, else blank.

```
  idx    rpm   hc08 now        cal   hc08 new  action
    3   1500  CE  80.8%  BF  74.9%  CE  80.8%  keep (cal -5.9%, decrease skipped)
    8   3500  B4  70.6%  D9  85.1%  D9  85.1%  raise +14.5%
```

Footer: `HC08 checksum: DA01 -> D95D`.

For a GUI, a 16-row grid with these columns plus colour for raise/skip, and a
chart of the three curves (HC08 now, cal, HC08 new) vs rpm would cover it.
Disable "Apply" unless at least one row is a raise and all checks pass.

---

## 8. C# porting notes

- **Reading/writing**: `File.ReadAllBytes`; mutate a `byte[]` copy; never
  touch CAL on disk.
- **Big-endian**: `BinaryPrimitives.ReadUInt32BigEndian(span)` /
  `WriteUInt16BigEndian(span, value)` (`System.Buffers.Binary`).
- **Pattern search**: no regex on bytes in .NET; do a simple loop over
  `i = 0, 4, 8, … ≤ len-12` comparing bytes 0–5 and 8–11 and skipping 6–7.
  Collect all hits, require exactly one.
- **Checksum**:
  ```csharp
  static ushort Hc08Checksum(ReadOnlySpan<byte> prog, int hc08Off)
  {
      ushort crc = 0x0123;
      foreach (var b in prog.Slice(hc08Off, 0x2000)) crc = unchecked((ushort)(crc + 0xFFFF - b));
      foreach (var b in prog.Slice(hc08Off + 0x23DC, 0x24)) crc = unchecked((ushort)(crc + 0xFFFF - b));
      return crc;
  }
  ```
- **Calibration ID**: `Encoding.ASCII.GetString(cal, 0, 16).Trim()`
  (also trim `'\0'` to be safe).
- **Atomic replace**: write `path + ".tmp"` in the same directory, then
  `File.Move(tmp, path, overwrite: true)`; wrap in try/finally to delete the
  temp file on failure.
- **Backup** before replace, using a timestamped name so earlier backups are
  never overwritten.
- **Separation**: put steps 1–11 in a pure function that takes two byte arrays
  and returns a result object (status, rows, old/new checksum, patched bytes,
  errors). The GUI only does file I/O, display, and the approval prompt. This
  also makes the test vectors in §10 straightforward unit tests.
- **Do not** add a "copy axis" option. Units differ (§5); the old
  `t6_patch_hc08_firmware.py` copied the cal axis raw into the HC08 axis,
  which is wrong.

---

## 9. Known firmwares

Values from factory full images (PROG offsets relative to PROG start).

| Cal ID | Vehicle | HC08 ptr (`PROG+0x8C`) | `hc08_off` | Pattern start | Imm offset | Stock sum | Cal tbl == HC08 tbl? |
|---|---|---|---|---|---|---|---|
| D132E0231 | 2017 Evora 400 | `0x000CEC60` | `0x8EC60` | `0x32670` | `0x32676` | `DA01` | yes |
| C132E0271 | 2018 Evora 400 | `0x000D1390` | `0x91390` | `0x32E60` | `0x32E66` | `DA01` | yes |
| C132E0278 | 2019 GT430 | `0x000D13F0` | `0x913F0` | `0x337BC` | `0x337C2` | `DA01` | **no** |
| E132E0288 | 2020 Evora GT | `0x000D5960` | `0x95960` | `0x342A4` | `0x342AA` | `DA01` | **no** |
| B132E0091 | NA Evora | — | — | — | — | — | no table (§5.1) |

All four supercharged firmwares share an identical HC08 image region
(axis `19 1F 27 2F 37 3F 4E 5E 6E 7D 8D 9C AC BB CB DB`, table
`8D A4 B7 CE D4 D4 D5 D5 B4 A9 B6 CC E4 FF FF FF`) and the same cal axis
`0A 10 18 20 28 30 40 50 60 70 80 8F 9F AF BF CF` at cal `0x0E2E`. In
0278/0288 the factory cal table has `D9 D9 D9 D9` at indices 4–7 where the
HC08 has `D4 D4 D5 D5`: Lotus raised the calibration without updating the
HC08. So factory 0278/0288 will report "raise needed".

Only C132E0278 has a profile. 0231/0271/0288 very likely use the same
offsets (bytes match), but adding them should be a deliberate step after
confirming the cal offsets in their romraider definitions.

---

## 10. Test vectors

### 10.1 Checksum function

| Input | Result |
|---|---|
| empty | `0x0123` |
| bytes `00 01 … FF` repeated 4 times (1024 bytes) | `0xFF23` |
| HC08 checksum region of any factory PROG in §9 | `0xDA01` |

### 10.2 End-to-end: `test.bin.cpt` + 93-octane calibration

Inputs (in this repo): `hc08_patcher/test.bin.cpt` (PROG, `0x98988` bytes,
C132E0278 with US patches) and
`patch/C132E0278_TAB.20260628-93octane.cpt` (CAL).

```
index        0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15
HC08 before 8D A4 B7 CE D4 D4 D5 D5 B4 A9 B6 CC E4 FF FF FF
CAL         8D A4 B7 BF BF C4 CC D9 D9 D9 D9 E6 F2 FF FF FF
HC08 after  8D A4 B7 CE D4 D4 D5 D9 D9 D9 D9 E6 F2 FF FF FF
```

- Raised: indices 7–12. Skipped decreases: indices 3–6.
- Checksum `DA01 → D95D`.
- Changed PROG offsets: exactly `0x337C2`, `0x337C3` (immediate) and
  `0x91439..0x9143E` (table). Instruction afterwards:
  `3C 60 00 01 38 63 D9 5D 54 60 04 3E`.
- A second run reports nothing to do (exit 0).

### 10.3 End-to-end: factory 0278 calibration

With factory 0278 PROG + factory 0278 CAL (cal table
`8D A4 B7 CE D9 D9 D9 D9 B4 A9 B6 CC E4 FF FF FF`), the calibration is ≥ the HC08
everywhere, so the HC08 table becomes equal to the calibration. Checksum
`DA01 → D9EF`. Changed bytes: immediate plus table indices 4–7
(`PROG+0x91436..0x91439`).

### 10.4 Negative tests

- CAL `B132E0091_TAB.cpt` with a 0278 PROG → unknown profile.
- Arguments swapped (CAL as PROG) → "HC08CODE marker not found … swapped?".
- CAL truncated to 100 bytes → too short.
- Flip one bit in the HC08 table of a valid PROG without fixing the
  immediate → "checksum already inconsistent" (computed `D9F0` vs embedded
  `D9EF` in the case tested).

---

## 11. Unverified assumptions / open questions

- **HC08 base `0xDC00`**: inferred from the checksum ranges and the reset
  vector, consistent with earlier Ghidra work. Not checked against a
  datasheet memory map for this exact part.
- **RAM `0x40004F30`** holds the HC08-reported checksum (0278): read from
  disassembly of the comparison only; the HC08→PPC transfer path was not
  traced.
- **Semantics of the HC08 table** (TPS ceiling vs rpm enforced by the
  monitor) are inferred from the matching calibration table name and values,
  not from HC08 disassembly. What the monitor does on violation, and whether
  it tolerates small mismatches (factory 0278 ships with a 2% mismatch), is
  unknown.
- **On-vehicle validation**: the output of `hc08_tps_sync.py` was verified
  byte-for-byte and by independent checksum, not by flashing. The older
  script that used the same checksum/immediate mechanism produced the
  `T6EVRGT430E01_BIN.cpt.patched_for_us.patched` file in this directory.
- **Field at `PROG+0x88`**: meaning unknown; differs between builds; not
  used.

---

## 12. Related files in this directory

| File | Status |
|---|---|
| `hc08_tps_sync.py` | Current reference implementation (this document) |
| `hc08_sum.py` | Standalone checksum printer for T4e and T6 PROG files; handy cross-check |
| `t6_patch_hc08_firmware.py` | **Obsolete.** Hardcoded 0278 offsets, copies the axis raw (wrong), writes the output twice |
| `hc08_C132E0278_patch_firmware.py` | **Obsolete.** Table-only predecessor; hardcoded offsets |
| `extract_patched_firmware_steps.txt` | Old manual workflow (dd PROG out of a full image → patch → diff → repack) |
