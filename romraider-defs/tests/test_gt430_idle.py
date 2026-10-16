"""Check GT430 idle display encodings against the exported consumers.

The byte oracle comes from the saturating (RPM error + 512) / 4 lookup input.
The word oracle uses the consumer's XOR and signed extension, independently of
the XML arithmetic. These checks do not establish stock calibration values.
"""

import ast
import operator
from pathlib import Path
import unittest
import xml.etree.ElementTree as ET


DEFINITION = (Path(__file__).resolve().parents[2]
              / "romraider-defs/T6-EVORA--F430-V000E_defs.xml")
WORD_SAMPLES = (0, 1, 127, 128, 255, 256, 32766, 32767,
                32768, 32769, 65534, 65535)


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


def signed_xor_word(raw):
    return int.from_bytes((raw ^ 0x8000).to_bytes(2, "big"), "big", signed=True)


class GT430IdleTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.rom, = [rom for rom in ET.parse(DEFINITION).getroot().findall("rom")
                    if rom.findtext("romid/xmlid") == "T6-EVORA--F430-V000E"]

    def table(self, offset):
        table, = [table for table in self.rom.findall("table")
                  if int(table.get("storageaddress"), 16) == offset]
        return table

    def assert_conversion(self, element, raw, expected):
        scaling, = element.findall("scaling")
        shown = calculate(scaling.get("expression"), raw)
        self.assertEqual(shown, expected)
        self.assertEqual(calculate(scaling.get("to_byte"), shown), raw)

    def test_ignition_idle_axes_decode_four_rpm_error_steps(self):
        # C15878-15919: lookup index is clamp((error+512)//4, 0, 255).
        for root_offset, axis_offset in ((0x0CB6, 0x0CA6), (0x074C, 0x073C),
                                         (0x0352, 0x0342)):
            table = self.table(root_offset)
            self.assertEqual(table.get("storagetype"), "uint8")
            self.assertEqual(table.get("sizex"), "16")
            axis, = table.findall("table")
            self.assertEqual(int(axis.get("storageaddress"), 16), axis_offset)
            self.assertEqual(axis.get("storagetype"), "uint8")
            self.assertEqual(axis.get("sizex"), "16")
            self.assertEqual(axis.find("scaling").get("units"), "rpm")
            for raw in range(256):
                with self.subTest(root=root_offset, raw=raw):
                    rpm_error = (raw << 2) - 512
                    self.assertEqual(min(255, max(0, (rpm_error + 512) // 4)), raw)
                    self.assert_conversion(axis, raw, rpm_error)

    def test_word_controller_axes_decode_signed_rpm_error_bias(self):
        # C28321/28331: signed RPM error is shifted into an unsigned axis.
        for root_offset, axis_offset in ((0x416E, 0x414E), (0x425E, 0x423E)):
            axis, = self.table(root_offset).findall("table")
            self.assertEqual(int(axis.get("storageaddress"), 16), axis_offset)
            self.assertEqual(axis.get("storagetype"), "uint16")
            self.assertEqual(axis.get("sizex"), "16")
            self.assertEqual(axis.find("scaling").get("units"), "rpm")
            for raw in WORD_SAMPLES:
                with self.subTest(root=root_offset, raw=raw):
                    rpm_error = signed_xor_word(raw)
                    self.assertEqual((rpm_error + 0x8000) & 0xFFFF, raw)
                    self.assert_conversion(axis, raw, rpm_error)

    def test_word_payloads_preserve_offset_binary_storage_and_expose_counts(self):
        # C28323/28333: result XOR 0x8000, interpreted as signed short.
        for root_offset in (0x416E, 0x425E):
            table = self.table(root_offset)
            self.assertEqual(table.get("storagetype"), "uint16")
            self.assertEqual(table.get("sizex"), "16")
            self.assertEqual(table.find("scaling").get("units"), "#")
            self.assertIn("controller counts", table.findtext("description"))
            for raw in WORD_SAMPLES:
                with self.subTest(root=root_offset, raw=raw):
                    self.assert_conversion(table, raw, signed_xor_word(raw))

    def test_antistall_threshold_uses_tenths_kph_coordinates(self):
        # C28426-28434: threshold is compared with car_speed_x100 / 10.
        table = self.table(0x0026)
        self.assertEqual(table.get("storagetype"), "uint8")
        self.assertEqual(table.get("sizex"), "1")
        self.assertEqual(table.find("scaling").get("units"), "km/h")
        for raw in range(256):
            with self.subTest(raw=raw):
                speed_centikph_at_threshold = raw * 10
                self.assertEqual(speed_centikph_at_threshold // 10, raw)
                self.assert_conversion(table, raw, speed_centikph_at_threshold / 100)


if __name__ == "__main__":
    unittest.main()
