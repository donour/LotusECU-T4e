"""Validate symbol CSV structure without changing exported symbol identities.

The identity digests were captured from each record's four valid leading fields
before repairing quoting in the comment field. Sorting preserves multiplicity
while avoiding a dependency on export order. Comments normalize only CRLF to LF.
"""

import csv
import hashlib
import json
from pathlib import Path
import unittest


ROOT = Path(__file__).resolve().parents[2]
SYMBOL_ROOT = ROOT / "disassembly/evora"
EXPORTS = {
    "B13200091/B13200091-symbols.csv": (
        5116,
        "f01132f5900cc42e2b39f60f4124ab10c9ae8794b00c1160a2436c650e8fa695",
    ),
    "C132E0278/C132E0278_symbols.csv": (
        4744,
        "19069bd4154fa9b67121584dc84e07bef5f62f88a2fa75aa94680134a5be14be",
    ),
}


EXPECTED_COMMENTS = {
    ("B13200091/B13200091-symbols.csv", "CAL_cruise_maf_feedforward", "4000ecb0"):
        ' Role in cruise logic\n'
        '\n'
        '  When the cruise controller enters "speed acquisition" mode (flag 0x2000000 in obd_ii_cruise_status)\\, it uses this table to know the expected\n'
        '  steady-state airflow at the target speed. It then ramps u16_flow_10mg_s_400014b0 (the working MAF setpoint) down toward that target\\, with a\n'
        '  proportional blend when the vehicle is still below the target speed (lines 51007–51027). Once the actual MAF drops below the feedforward\n'
        '  target\\, the flag clears and the PID takes over.\n'
        '\n'
        '  This is a classic feedforward / open-loop preload for cruise control — avoids overshoot by starting from a physically-motivated airflow\n'
        '  estimate rather than relying purely on feedback.\n',
    ("C132E0278/C132E0278_symbols.csv", "CAL_torque_limit_base_factor", "4000bb0a"):
        '  // Used in cylinder cut calculation\n'
        '  // "42/255 is the amount of torque reduction per cylinder from a hard cut"\n'
        '  (0xff - torque_limit_base_factor) * (6 - torque_cut_level_as_cyl_count)\n'
        '\n'
        '  What It Represents\n'
        '\n'
        "  This is the base torque capacity/efficiency factor at each RPM×load operating point. It's used to:\n"
        '\n'
        '  1. Compare against external torque requests - torque_limit_external_factor (from TC\\, ABS\\, stability control)\n'
        '  2. Calculate cylinder cuts needed - when external request is below base factor\\, determines how many cylinders to cut\n'
        '  3. Define engine torque envelope - maps where the engine can produce full torque vs. derated',
    ("C132E0278/C132E0278_symbols.csv", "CAL_dpm_direct_mode_off_delay", "4000ccb2"):
        '"Direct mode" (flag bit 2) likely means more aggressive TC intervention when there\'s significant left-right wheel speed difference - i.e.\\, one wheel spinning more than the other.',
    ("C132E0278/C132E0278_symbols.csv", "CAL_dpm_direct_mode_on_delay", "4000ccb4"):
        '"Direct mode" (flag bit 2) likely means more aggressive TC intervention when there\'s significant left-right wheel speed difference - i.e.\\, one wheel spinning more than the other.',
}


class SymbolExportTests(unittest.TestCase):
    def read_rows(self, relative_path):
        with (SYMBOL_ROOT / relative_path).open(newline="", encoding="utf-8") as source:
            return list(csv.reader(source, strict=True))

    def test_every_record_has_five_columns_and_a_valid_location(self):
        for relative_path in EXPORTS:
            with self.subTest(export=relative_path):
                rows = self.read_rows(relative_path)
                self.assertEqual(rows[0], ["Name", "Location", "Type", "Data Type", "EOL Comment"])
                for ordinal, row in enumerate(rows[1:], 1):
                    self.assertEqual(len(row), 5, (relative_path, ordinal, row))
                    self.assertRegex(row[1], r"\A[0-9a-fA-F]{8}\Z")

    def test_first_four_fields_preserve_original_identity_multisets(self):
        for relative_path, (expected_count, expected_digest) in EXPORTS.items():
            with self.subTest(export=relative_path):
                rows = self.read_rows(relative_path)[1:]
                self.assertEqual(len(rows), expected_count)
                identities = sorted(row[:4] for row in rows)
                encoded = json.dumps(identities, ensure_ascii=False, separators=(",", ":")).encode("utf-8")
                self.assertEqual(hashlib.sha256(encoded).hexdigest(), expected_digest)

    def test_repaired_comments_are_complete_and_attached_to_their_symbols(self):
        exports = {name: self.read_rows(name)[1:] for name in EXPORTS}
        for (relative_path, name, location), expected in EXPECTED_COMMENTS.items():
            with self.subTest(export=relative_path, name=name, location=location):
                matches = [row for row in exports[relative_path]
                           if row[:2] == [name, location]]
                self.assertEqual(len(matches), 1)
                self.assertEqual(matches[0][4].replace("\r\n", "\n"), expected)


if __name__ == "__main__":
    unittest.main()
