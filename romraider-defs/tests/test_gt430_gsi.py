"""Check GT430 advisory ratios against the centikph-to-RPM consumer."""

import ast
import operator
from pathlib import Path
import unittest
import xml.etree.ElementTree as ET


DEFINITION = (Path(__file__).resolve().parents[2]
              / "romraider-defs/T6-EVORA--F430-V000E_defs.xml")


def calculate(expression, value):
    operations = {ast.Add: operator.add, ast.Sub: operator.sub,
                  ast.Mult: operator.mul, ast.Div: operator.truediv}

    def visit(node):
        if isinstance(node, ast.Name) and node.id == "x":
            return value
        if isinstance(node, ast.Constant) and type(node.value) in (int, float):
            return node.value
        if isinstance(node, ast.BinOp) and type(node.op) in operations:
            return operations[type(node.op)](visit(node.left), visit(node.right))
        raise ValueError(f"Unsupported scaling: {expression}")

    return visit(ast.parse(expression, mode="eval").body)


class GT430GearAdvisoryTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.rom, = [rom for rom in ET.parse(DEFINITION).getroot().findall("rom")
                    if rom.findtext("romid/xmlid") == "T6-EVORA--F430-V000E"]

    def table(self, offset):
        table, = [table for table in self.rom.findall("table")
                  if int(table.get("storageaddress"), 16) == offset]
        return table

    def test_ratios_match_the_engine_speed_estimate_at_ten_kph(self):
        # C57135: expected RPM = (centikph - speed offset)*raw_ratio/1000.
        # At ten km/h and zero offset, expected RPM is exactly the raw ratio.
        for offset in (0x45B0, 0x45BC, 0x45C8):
            table = self.table(offset)
            self.assertEqual(table.get("storagetype"), "uint16")
            self.assertEqual(table.get("sizex"), "6")
            scaling, = table.findall("scaling")
            self.assertEqual(scaling.get("units"), "rpm/(km/h)")
            axis, = table.findall("table")
            self.assertEqual([cell.text for cell in axis.findall("data")],
                             [f"Gear {i}" for i in range(1, 7)])
            for raw in (0, 1, 9, 10, 100, 255, 256, 1000, 32767, 32768, 65535):
                with self.subTest(offset=offset, raw=raw):
                    expected_rpm = (1000 * raw) // 1000
                    displayed = calculate(scaling.get("expression"), raw)
                    self.assertEqual(displayed, expected_rpm / 10)
                    self.assertEqual(calculate(scaling.get("to_byte"), displayed), raw)

    def test_manual_advisory_speed_offset_keeps_direct_kph_encoding(self):
        # C57124 multiplies the raw speed offset by 100 to obtain centikph.
        table = self.table(0x45E6)
        self.assertEqual(table.get("storagetype"), "uint8")
        scaling, = table.findall("scaling")
        for raw in range(256):
            self.assertEqual(calculate(scaling.get("expression"), raw),
                             (raw * 100) / 100)


if __name__ == "__main__":
    unittest.main()
