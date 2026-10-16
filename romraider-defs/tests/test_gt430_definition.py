"""Check the GT430 definition against the reviewed exported arithmetic.

Run from the repository root:
    python3 -m unittest discover -s romraider-defs/tests -v
"""

import ast
import csv
import operator
from pathlib import Path
import unittest
import xml.etree.ElementTree as ET


ROOT = Path(__file__).resolve().parents[2]
DEFINITION = ROOT / "romraider-defs/T6-EVORA--F430-V000E_defs.xml"
SYMBOLS = ROOT / "disassembly/evora/C132E0278/C132E0278_symbols.csv"


def evaluate(expression, value):
    """Evaluate only the arithmetic used by these XML scalings."""
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

    return visit(ast.parse(expression, mode="eval").body)


class GT430DefinitionTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        roms = ET.parse(DEFINITION).getroot().findall("rom")
        cls.rom, = [rom for rom in roms
                    if rom.findtext("romid/xmlid") == "T6-EVORA--F430-V000E"]
        with SYMBOLS.open(newline="") as source:
            cls.symbols = list(csv.DictReader(source))
        cls.cal_base = cls.symbol_address("CAL_base")

    @classmethod
    def symbol_address(cls, name):
        symbol, = [row for row in cls.symbols if row["Name"] == name]
        return int(symbol["Location"], 16)

    def table_at(self, offset):
        table, = [table for table in self.rom.findall("table")
                  if int(table.get("storageaddress"), 16) == offset]
        return table

    def test_trim_encoding_matches_signed_xor_for_every_byte(self):
        table = self.table_at(0x005A)
        self.assertEqual(table.get("storagetype"), "uint8")
        self.assertEqual(table.get("sizex"), "6")
        scaling = table.find("scaling")
        for raw in range(256):
            with self.subTest(raw=raw):
                # Firmware: signed 8-bit (raw ^ 0x80), in quarter degrees.
                quarter_degrees = raw ^ 0x80
                if quarter_degrees & 0x80:
                    quarter_degrees -= 256
                degrees = evaluate(scaling.get("expression"), raw)
                self.assertEqual(degrees, quarter_degrees / 4)
                self.assertEqual(evaluate(scaling.get("to_byte"), degrees), raw)
        self.assertEqual(evaluate(scaling.get("expression"), 128), 0)

    def test_trim_axis_identifies_the_six_array_entries(self):
        axis, = self.table_at(0x005A).findall("table")
        self.assertEqual(axis.get("type"), "Static X Axis")
        self.assertEqual([cell.text for cell in axis.findall("data")],
                         [f"Cyl #{i}" for i in range(1, 7)])
        self.assertIsNone(axis.find("scaling"))
        self.assertIsNone(axis.get("storageaddress"))

    def test_deadtime_uses_the_stored_temperature_axis(self):
        table = self.table_at(0x18EE)
        self.assertEqual(table.get("name"), "inj: deadtime comp iat")
        self.assertEqual(table.get("storagetype"), "uint8")
        self.assertEqual(table.get("sizex"), "8")
        axis, = table.findall("table")
        self.assertEqual(axis.get("type"), "X Axis")
        self.assertEqual(axis.get("storagetype"), "uint8")
        self.assertEqual(axis.get("endian"), "big")
        self.assertEqual(axis.get("sizex"), "8")
        axis_offset = int(axis.get("storageaddress"), 16)
        # CSV retains the older symbol names at the same addresses.
        self.assertEqual(axis_offset, self.symbol_address("CAL_inj_comp_iat_X_iat")
                         - self.cal_base)
        self.assertEqual(axis_offset + 8, 0x18EE)
        self.assertEqual(self.symbol_address("CAL_inj_comp_iat") - self.cal_base,
                         0x18EE)
        self.assertEqual(axis.findall("data"), [])
        scaling = axis.find("scaling")
        self.assertEqual(scaling.get("units"), "°C")
        for raw in range(256):
            temperature = evaluate(scaling.get("expression"), raw)
            self.assertEqual(temperature, raw * 0.625 - 40)
            self.assertEqual(evaluate(scaling.get("to_byte"), temperature), raw)
            self.assertEqual(evaluate(table.find("scaling").get("expression"), raw),
                             raw)

    def test_stopped_coolant_bounds_have_distinct_names_at_csv_addresses(self):
        for suffix, offset in (("min", 0x004D), ("max", 0x004E)):
            with self.subTest(bound=suffix):
                table = self.table_at(offset)
                self.assertEqual(table.get("name"),
                                 f"ign: comp coolant engine stopped {suffix}")
                self.assertEqual(table.get("storagetype"), "uint8")
                self.assertEqual(table.get("sizex"), "1")
                self.assertEqual(offset, self.symbol_address(
                    f"CAL_ign_comp_coolant_engine_stopped_{suffix}") - self.cal_base)


if __name__ == "__main__":
    unittest.main()
