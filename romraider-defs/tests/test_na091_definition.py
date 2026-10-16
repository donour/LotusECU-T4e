"""Check NA091 definitions against exported arithmetic and address metadata.

These checks validate presentation and encoding, not an original firmware image.
Run: python3 -m unittest discover -s romraider-defs/tests -v
"""

import ast
import csv
from functools import lru_cache
import operator
from pathlib import Path
import re
import unittest
import xml.etree.ElementTree as ET


ROOT = Path(__file__).resolve().parents[2]
DEFINITION = ROOT / "romraider-defs/T6-V00BU_defs.xml"
SYMBOLS = ROOT / "disassembly/evora/B13200091/B13200091-symbols.csv"


@lru_cache(maxsize=None)
def expression_tree(expression):
    return ast.parse(expression, mode="eval").body


def evaluate(expression, value):
    operations = {ast.Add: operator.add, ast.Sub: operator.sub,
                  ast.Mult: operator.mul, ast.Div: operator.truediv}

    def visit(node):
        if isinstance(node, ast.Name) and node.id == "x":
            return value
        if isinstance(node, ast.Constant) and type(node.value) in (int, float):
            return node.value
        if isinstance(node, ast.BinOp) and type(node.op) in operations:
            return operations[type(node.op)](visit(node.left), visit(node.right))
        raise ValueError(f"Unsupported scaling expression: {expression}")

    return visit(expression_tree(expression))


class NA091DefinitionTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.roms = ET.parse(DEFINITION).getroot().findall("rom")
        with SYMBOLS.open(newline="") as source:
            cls.symbols = list(csv.DictReader(source))

    def table_at(self, offset, learned=False):
        table, = [table for table in self.roms[int(learned)].findall("table")
                  if int(table.get("storageaddress"), 16) == offset]
        return table

    def assert_symbol_offset(self, offset, symbol_name, learned=False):
        symbol, = [row for row in self.symbols if row["Name"] == symbol_name]
        base_name = "LEA_base" if learned else "CAL_base"
        base, = [row for row in self.symbols if row["Name"] == base_name]
        self.assertEqual(int(symbol["Location"], 16) - int(base["Location"], 16),
                         offset)

    def assert_scaling(self, table, raw_values, oracle):
        scaling, = table.findall("scaling")
        forward, inverse = scaling.get("expression"), scaling.get("to_byte")
        for raw in raw_values:
            shown = evaluate(forward, raw)
            self.assertAlmostEqual(shown, oracle(raw), places=9,
                                   msg=f"{table.get('name')} raw={raw}")
            self.assertAlmostEqual(evaluate(inverse, shown), raw, places=9)

    def assert_static_labels(self, table, name, labels):
        axis, = table.findall("table")
        self.assertEqual(axis.get("type"), "Static X Axis")
        self.assertEqual(axis.get("name"), name)
        self.assertEqual([cell.text for cell in axis.findall("data")], labels)
        self.assertIsNone(axis.get("storageaddress"))
        self.assertEqual(axis.findall("scaling"), [])

    def test_speed_limit_uses_centikph_consumer_and_preserves_sentinel(self):
        table = self.table_at(0x0262)
        self.assert_symbol_offset(0x0262, "CAL_vehicle_speed_limit")
        self.assertEqual(table.get("storagetype"), "uint8")
        self.assert_scaling(table, range(256), lambda raw: (raw * 200) / 100)
        self.assertEqual(table.find("scaling").get("units"), "km/h")
        self.assertIn("255", table.findtext("description"))
        self.assertIn("no-limit", table.findtext("description"))

    def test_advisory_thresholds_decode_five_rpm_steps(self):
        names = {0x45D4: "CAL_gear_advisory_upshift_rpm_gear1",
                 0x45D5: "CAL_gear_advisory_upshift_rpm_manual",
                 0x45DA: "CAL_gear_advisory_upshift_rpm_ips"}
        for offset, name in names.items():
            with self.subTest(offset=offset):
                table = self.table_at(offset)
                self.assert_symbol_offset(offset, name)
                self.assertEqual(table.get("storagetype"), "uint8")
                self.assert_scaling(table, range(256),
                                    lambda raw: (raw << 2) + raw + 500)
                if offset != 0x45D4:
                    self.assert_static_labels(table, "gear",
                                              [f"Gear #{i}" for i in range(2, 7)])

    def test_advisory_differences_have_no_absolute_rpm_bias(self):
        for offset, name in ((0x45EF, "CAL_gsi_downshift_idle_margin"),
                             (0x45F0, "CAL_gsi_downshift_rpm_offset")):
            table = self.table_at(offset)
            self.assert_symbol_offset(offset, name)
            self.assert_scaling(table, range(256), lambda raw: (raw << 2) + raw)
            self.assertEqual(evaluate(table.find("scaling").get("expression"), 0), 0)

    def test_advisory_ratios_match_speed_to_rpm_conversion(self):
        for offset, suffix in ((0x45B0, "ips"), (0x45BC, "close_ratio"),
                               (0x45C8, "standard")):
            table = self.table_at(offset)
            self.assert_symbol_offset(offset, "CAL_gsi_rpm_per_kph_" + suffix)
            # At 10 km/h (1000 centikph), firmware estimates raw RPM.
            self.assert_scaling(table, range(65536),
                                lambda raw: ((1000 * raw) // 1000) / 10)
            self.assert_static_labels(table, "gear",
                                      [f"Gear #{i}" for i in range(1, 7)])
        for offset, name, units in ((0x45E4, "CAL_gsi_max_gear_rpm", "rpm"),
                                    (0x45E6, "CAL_gsi_speed_offset_kph", "km/h")):
            self.assert_symbol_offset(offset, name)
            self.assertEqual(self.table_at(offset).find("scaling").get("units"), units)

    def test_fuel_learning_thresholds_match_signed_word_xor(self):
        for offset, side in ((0x01E8, "lean"), (0x01EA, "rich")):
            table = self.table_at(offset)
            self.assert_symbol_offset(offset, "CAL_inj_fuel_learn_stft_" + side + "_limit")
            self.assertEqual(table.get("storagetype"), "uint16")
            self.assert_scaling(table, range(65536), lambda raw:
                                int.from_bytes((raw ^ 0x8000).to_bytes(2, "big"),
                                               "big", signed=True) / 20)
            self.assertEqual(evaluate(table.find("scaling").get("expression"), 0x8000), 0)

    def test_learned_idle_corrections_share_signed_fixed_point_scale(self):
        for offset, name in ((0x0984, "LEA_idle_cold_learning_coolant"),
                             (0x0986, "LEA_idle_cold_learning_coolant_ac_on"),
                             (0x0576, "LEA_idle_learn_ac_on")):
            table = self.table_at(offset, learned=True)
            self.assert_symbol_offset(offset, name, learned=True)
            self.assertEqual(table.get("storagetype"), "int16")
            # Signed extension is independent of the XML storage declaration.
            oracle = lambda signed: int.from_bytes(
                (signed & 0xFFFF).to_bytes(2, "big"), "big", signed=True) * 100 / (1 << 10)
            self.assert_scaling(table, range(-32768, 32768), oracle)

    def test_airbox_pairs_are_rpm_hysteresis_boundaries(self):
        for offset, suffix in ((0x0206, "tour"), (0x452E, "sport"),
                               (0x4532, "tour2"), (0x4536, "sport2")):
            table = self.table_at(offset)
            self.assert_symbol_offset(offset, "CAL_airbox_flapper_engine_speed_" + suffix)
            self.assertEqual(table.get("storagetype"), "uint16")
            self.assertEqual(table.get("sizex"), "2")
            self.assertEqual(table.find("scaling").get("units"), "rpm")
            self.assert_scaling(table, (0, 1, 255, 256, 32768, 65535), lambda raw: raw)
            self.assert_static_labels(table, "boundary", ["Lower RPM", "Upper RPM"])

    def test_ignition_trim_axis_and_existing_signed_byte_encoding(self):
        table = self.table_at(0x005A)
        self.assert_symbol_offset(0x005A, "CAL_ign_trim_per_cyl")
        self.assert_static_labels(table, "cylinder", [f"Cyl #{i}" for i in range(1, 7)])
        self.assert_scaling(table, range(256), lambda raw:
                            int.from_bytes(bytes([raw ^ 0x80]), "big", signed=True) / 4)

    def test_preserves_inventory_alternative_units_and_line_endings(self):
        self.assertEqual([len(rom.findall("table")) for rom in self.roms], [1091, 695])
        for rom in self.roms:
            for element in rom.iter("table"):
                scalings = [tuple(sorted(scaling.attrib.items()))
                            for scaling in element.findall("scaling")]
                self.assertEqual(len(scalings), len(set(scalings)), element.get("name"))
        # Alternative unit choices survive identical-record cleanup.
        self.assertEqual(sum(len(table.findall("scaling")) > 1
                             for table in self.roms[0].findall("table")), 13)
        self.assertIsNone(re.search(rb"(?<!\r)\n", DEFINITION.read_bytes()))


if __name__ == "__main__":
    unittest.main()
