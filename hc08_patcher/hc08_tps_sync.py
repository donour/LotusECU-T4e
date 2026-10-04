#!/usr/bin/python3
"""
Sync the HC08 (ETB safety monitor) TPS max table with the ECU calibration's
"tps: scaling factor rpm" table, modifying a T6 PROG file (e.g. *_BIN.cpt) in
place. The calibration is read from a separate calibration file
(e.g. *_TAB.cpt) and is never modified.

The T6 ECU carries two copies of the TPS max-vs-rpm table: one in the
calibration (used by the main PPC), and one inside the HC08 monitor firmware
that is embedded in PROG. Editing the calibration does not update the HC08
copy (factory C132E0278 already ships with them differing at 1750-3000 rpm).
This tool raises the HC08 table wherever the calibration is higher, and fixes
the HC08 checksum.

Only increases are applied: each HC08 breakpoint becomes max(HC08, cal).
Where the calibration is lower, the HC08 value is kept and the skipped
decrease is reported. Since both tables share the same rpm breakpoints and
interpolate linearly, the resulting HC08 limit is never below either the
previous HC08 limit or the calibration limit at any rpm.

The HC08 image is protected by a 16-bit checksum that PROG verifies at runtime
against a constant built by:
    lis    r3,1
    addi   r3,r3,<sum>      ; 38 63 xx xx
    clrlwi r0,r3,16         ; only the low 16 bits matter
After changing the HC08 table, the <sum> immediate is updated to match.
"""

EPILOG = """\
inputs:
  PROG  program file, as flashed at 0x40000 (e.g. T6EVRGT430E01_BIN.cpt).
        PROG+0x80 = "HC08CODE", PROG+0x8C = flash address of the HC08 image,
        which is mapped at HC08 address 0xDC00. The HC08 checksum covers HC08
        0xDC00-0xFBFF and the vectors at 0xFFDC-0xFFFF.
  CAL   calibration file, as flashed at 0x20000 (e.g. C132E0278_TAB.cpt);
        starts with the calibration ID string, e.g. "C132E0278". Read only.

what it does:
  1. picks a profile by calibration ID (or --profile) for table locations
  2. locates the HC08 image and the checksum instruction (by pattern search,
     so its address does not need to be configured)
  3. safety checks, aborting on failure without touching the file:
       - calibration rpm axis and HC08 rpm axis agree to within one HC08 count
         (cal rpm = x*125/4+500, HC08 rpm = x*255/8). The axis is never
         written, only the table values.
       - the existing embedded checksum matches the HC08 contents
  4. computes new HC08 values = max(HC08, cal) per breakpoint. If nothing is
     raised: reports "nothing to do" (listing any skipped decreases) and exits
  5. otherwise prints a per-breakpoint table (rpm, HC08 now, cal, HC08 new,
     action: raise / keep with decrease skipped) and the old -> new checksum,
     then prompts for approval
  6. re-verifies the patched PROG, writes a timestamped .bak copy, and
     replaces the PROG file atomically (temp file + rename)

exit status:
  0  nothing to raise, or patched successfully
  1  a raise is needed (--check), or the prompt was declined
  2  error: no HC08 image in PROG, CAL too short, unknown calibration, axis
     mismatch (e.g. CAL and PROG from different firmwares), inconsistent
     checksum, checksum instruction not found or ambiguous

examples:
  %(prog)s T6EVRGT430E01_BIN.cpt C132E0278_TAB.cpt
        review the diff, then approve; patches T6EVRGT430E01_BIN.cpt
  %(prog)s T6EVRGT430E01_BIN.cpt C132E0278_TAB.cpt --check
        report only, never writes
  %(prog)s T6EVRGT430E01_BIN.cpt C132E0278_TAB.cpt -y
        apply without prompting

adding a firmware:
  Add an entry to PROFILES in this script, keyed by calibration ID:
    "C132E0278": Profile(cal_table=0x0E3E, cal_axis=0x0E2E,
                         hc08_table=0xDC42, hc08_axis=0xDC32),
  cal_* are calrom offsets (as in the romraider defs); hc08_* are HC08
  addresses (as in Ghidra). Axis conversions and the axis tolerance can be
  overridden per profile (cal_axis_rpm, hc08_axis_rpm, axis_tolerance_rpm).

configured profiles:
{profiles}
"""

import argparse, os, re, sys, tempfile, time
from dataclasses import dataclass
from typing import Callable

# T6 flash address PROG is loaded at
PROG_BASE       = 0x40000
CAL_ID_LEN      = 16

# HC08 image inside PROG: PROG+0x80 holds "HC08CODE", PROG+0x8C holds the
# image's absolute flash address. The image is mapped at HC08 address 0xDC00.
HC08_MAGIC_OFF  = 0x80
HC08_MAGIC      = b'HC08CODE'
HC08_PTR_OFF    = 0x8C
HC08_BASE       = 0xDC00
HC08_SUM_RANGES = [(0x0000, 0x2000), (0x23DC, 0x2400)]  # relative to image start

# lis r3,1 ; addi r3,r3,???? ; clrlwi r0,r3,16
CKSUM_INSN_RE   = re.compile(rb'\x3c\x60\x00\x01\x38\x63(..)\x54\x60\x04\x3e', re.S)
CKSUM_IMM_OFF   = 6  # offset of the immediate from the start of the match


@dataclass
class Profile:
    cal_table: int                       # calrom offset of table values
    cal_axis: int                        # calrom offset of rpm axis
    hc08_table: int                      # HC08 address of table values
    hc08_axis: int                       # HC08 address of rpm axis
    size: int = 16
    cal_axis_rpm: Callable[[int], float] = lambda x: x * 125 / 4 + 500
    hc08_axis_rpm: Callable[[int], float] = lambda x: x * 255 / 8
    axis_tolerance_rpm: float = 255 / 8  # one HC08 axis count


# Keyed by the calibration ID string at the start of calrom.
PROFILES = {
    "C132E0278": Profile(cal_table=0x0E3E, cal_axis=0x0E2E,
                         hc08_table=0xDC42, hc08_axis=0xDC32),
}


class SyncError(Exception):
    pass


class SUM_HC08_T6:
    """T6 HC08 checksum: 16-bit running sum of (0xFF00 | ~byte), seeded with 0x0123."""

    def __init__(self, initvalue=0x0123):
        self.initvalue = initvalue
        self.reset()

    def reset(self):
        self.crc = self.initvalue

    def update(self, data):
        for byte in data:
            self.crc = ((0xFF00 | ~byte) + self.crc) & 0xFFFF

    def get(self):
        return self.crc


def pct(x):
    return x * 100 / 255


class Firmware:
    """PROG (modified) plus calibration (read only), each indexed from its own start."""

    def __init__(self, prog, cal, profile_name=None):
        self.prog = bytearray(prog)
        self.cal = bytes(cal)

        if self.prog[HC08_MAGIC_OFF:HC08_MAGIC_OFF + 8] != HC08_MAGIC:
            raise SyncError("HC08CODE marker not found at PROG+0x80; not a T6 PROG file "
                            "(or PROG and CAL swapped?)")
        self.hc08_off = int.from_bytes(self.prog[HC08_PTR_OFF:HC08_PTR_OFF + 4], 'big') - PROG_BASE
        if not 0 <= self.hc08_off <= len(self.prog) - HC08_SUM_RANGES[-1][1]:
            raise SyncError(f"HC08 image offset {self.hc08_off:#x} is outside PROG")

        self.cal_id = self.cal[:CAL_ID_LEN].decode('ascii', 'replace').strip()
        name = profile_name or self.cal_id
        if name not in PROFILES:
            raise SyncError(f"no profile for calibration '{self.cal_id}' (known: {', '.join(PROFILES)})")
        self.profile_name = name
        self.p = PROFILES[name]
        if len(self.cal) < max(self.p.cal_table, self.p.cal_axis) + self.p.size:
            raise SyncError(f"calibration is only {len(self.cal):#x} bytes; too short for this profile")

        self.insn_off = self._find_checksum_insn()

    def _find_checksum_insn(self):
        hits = [m.start() for m in CKSUM_INSN_RE.finditer(self.prog) if m.start() % 4 == 0]
        if len(hits) != 1:
            raise SyncError(f"expected 1 HC08 checksum instruction, found {len(hits)}")
        return hits[0] + CKSUM_IMM_OFF

    def _hc08(self, addr):
        return self.hc08_off + addr - HC08_BASE

    def cal_axis(self):
        o = self.p.cal_axis
        return self.cal[o:o + self.p.size]

    def cal_table(self):
        o = self.p.cal_table
        return self.cal[o:o + self.p.size]

    def hc08_axis(self):
        o = self._hc08(self.p.hc08_axis)
        return bytes(self.prog[o:o + self.p.size])

    def hc08_table(self):
        o = self._hc08(self.p.hc08_table)
        return bytes(self.prog[o:o + self.p.size])

    def set_hc08_table(self, values):
        o = self._hc08(self.p.hc08_table)
        self.prog[o:o + self.p.size] = values

    def computed_checksum(self):
        cksum = SUM_HC08_T6()
        for start, end in HC08_SUM_RANGES:
            cksum.update(self.prog[self.hc08_off + start:self.hc08_off + end])
        return cksum.get()

    def embedded_checksum(self):
        return int.from_bytes(self.prog[self.insn_off:self.insn_off + 2], 'big')

    def set_embedded_checksum(self, value):
        self.prog[self.insn_off:self.insn_off + 2] = value.to_bytes(2, 'big')

    def check_axes(self):
        bad = []
        for i, (c, h) in enumerate(zip(self.cal_axis(), self.hc08_axis())):
            c_rpm, h_rpm = self.p.cal_axis_rpm(c), self.p.hc08_axis_rpm(h)
            if abs(c_rpm - h_rpm) > self.p.axis_tolerance_rpm:
                bad.append(f"  [{i:2}] cal {c_rpm:6.0f} rpm vs hc08 {h_rpm:6.0f} rpm")
        if bad:
            raise SyncError("calibration rpm axis does not match HC08 rpm axis:\n" + "\n".join(bad))


def raised_table(old, cal):
    """Only raise HC08 values: each breakpoint becomes max(hc08, cal)."""
    return bytes(max(o, c) for o, c in zip(old, cal))


def print_table(fw, new):
    old, cal = fw.hc08_table(), fw.cal_table()
    print(f"  {'idx':>3}  {'rpm':>5}  {'hc08 now':>9}  {'cal':>9}  {'hc08 new':>9}  action")
    for i, (a, o, c, n) in enumerate(zip(fw.cal_axis(), old, cal, new)):
        if n != o:
            action = f"raise {pct(n) - pct(o):+.1f}%"
        elif c < o:
            action = f"keep (cal {pct(c) - pct(o):+.1f}%, decrease skipped)"
        else:
            action = ""
        print(f"  {i:3}  {fw.p.cal_axis_rpm(a):5.0f}  {o:02X} {pct(o):5.1f}%  {c:02X} {pct(c):5.1f}%  "
              f"{n:02X} {pct(n):5.1f}%  {action}")


def write_in_place(path, data, backup):
    if backup:
        bak = f"{path}.{time.strftime('%Y%m%d-%H%M%S')}.bak"
        with open(path, 'rb') as src, open(bak, 'wb') as dst:
            dst.write(src.read())
        print(f"Backup written to {bak}")
    fd, tmp = tempfile.mkstemp(dir=os.path.dirname(os.path.abspath(path)), prefix='.hc08_tps_sync.')
    try:
        with os.fdopen(fd, 'wb') as f:
            f.write(data)
        os.replace(tmp, path)
    except BaseException:
        os.unlink(tmp)
        raise


def main():
    profiles = "\n".join(
        f"  {name:<10} cal table {p.cal_table:#06x}  cal axis {p.cal_axis:#06x}  "
        f"hc08 table {p.hc08_table:#06x}  hc08 axis {p.hc08_axis:#06x}  ({p.size} bytes)"
        for name, p in PROFILES.items())
    ap = argparse.ArgumentParser(
        description=__doc__,
        epilog=EPILOG.format(profiles=profiles),
        formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('prog', metavar='PROG',
                    help="T6 PROG file (e.g. *_BIN.cpt); modified in place after approval")
    ap.add_argument('cal', metavar='CAL',
                    help="calibration file (e.g. *_TAB.cpt); read only")
    ap.add_argument('--profile', metavar='NAME',
                    help="use this profile instead of the one matching the calibration ID")
    g = ap.add_mutually_exclusive_group()
    g.add_argument('--check', action='store_true',
                   help="report status and the diff only; never writes. exit 1 if a raise is needed")
    g.add_argument('--yes', '-y', action='store_true',
                   help="apply without prompting (safety checks still apply)")
    ap.add_argument('--no-backup', action='store_true',
                    help="don't write a <PROG>.<timestamp>.bak copy before patching")
    args = ap.parse_args()

    with open(args.prog, 'rb') as f:
        prog = f.read()
    with open(args.cal, 'rb') as f:
        cal = f.read()
    fw = Firmware(prog, cal, args.profile)

    print(f"Calibration : {fw.cal_id}  (profile {fw.profile_name})")
    print(f"HC08 image  : PROG+{fw.hc08_off:#x}, table @ HC08 {fw.p.hc08_table:#06x}")
    print(f"Checksum    : insn imm @ PROG+{fw.insn_off:#x}")

    fw.check_axes()

    old_sum, embedded = fw.computed_checksum(), fw.embedded_checksum()
    if old_sum != embedded:
        raise SyncError(f"HC08 checksum already inconsistent: computed {old_sum:04X}, "
                        f"embedded {embedded:04X}; refusing to patch")

    new_table = raised_table(fw.hc08_table(), fw.cal_table())
    if fw.hc08_table() == new_table:
        if fw.hc08_table() != fw.cal_table():
            print("\nCalibration is below the HC08 table at some breakpoints (decreases are not applied):")
            print_table(fw, new_table)
        print(f"\nNo calibration value exceeds the HC08 table, checksum {old_sum:04X} OK. Nothing to do.")
        return 0

    print("\nCalibration exceeds the HC08 TPS max table:")
    print_table(fw, new_table)
    fw.set_hc08_table(new_table)
    new_sum = fw.computed_checksum()
    fw.set_embedded_checksum(new_sum)
    print(f"\nHC08 checksum: {old_sum:04X} -> {new_sum:04X}")

    # Verify the patched image from scratch before writing anything
    check = Firmware(fw.prog, fw.cal, fw.profile_name)
    assert check.hc08_table() == new_table
    assert check.computed_checksum() == check.embedded_checksum() == new_sum
    assert len(fw.prog) == len(prog)

    if args.check:
        print("HC08 firmware needs updating.")
        return 1
    if not args.yes:
        if input(f"\nApply changes to {args.prog}? [y/N] ").strip().lower() not in ('y', 'yes'):
            print("Aborted, file unchanged.")
            return 1

    write_in_place(args.prog, fw.prog, backup=not args.no_backup)
    print(f"Patched {args.prog}")
    return 0


if __name__ == "__main__":
    try:
        sys.exit(main())
    except SyncError as e:
        print(f"error: {e}", file=sys.stderr)
        sys.exit(2)
