"""Check GT430 display conversions against the reviewed consumer arithmetic.

These are definition/schema checks, not firmware or calibration-value tests.
The expected values below come from the exported arithmetic, independently of
the XML expressions. Run with ``python3 -m unittest discover -s romraider-defs/tests -v``.
"""

import ast
from fractions import Fraction
from pathlib import Path
import unittest
import xml.etree.ElementTree as ET


DEFINITION = (Path(__file__).resolve().parents[2]
              / "romraider-defs/T6-EVORA--F430-V000E_defs.xml")


def calculate(expression, value):
    """Evaluate this small arithmetic grammar exactly, without Python eval."""
    def visit(node):
        if isinstance(node, ast.Name) and node.id == "x":
            return Fraction(value)
        if isinstance(node, ast.Constant) and type(node.value) in (int, float):
            return Fraction(str(node.value))
        if isinstance(node, ast.BinOp):
            left, right = visit(node.left), visit(node.right)
            if isinstance(node.op, ast.Add):
                return left + right
            if isinstance(node.op, ast.Sub):
                return left - right
            if isinstance(node.op, ast.Mult):
                return left * right
            if isinstance(node.op, ast.Div):
                return left / right
        raise ValueError(f"Unsupported arithmetic: {expression}")
    return visit(ast.parse(expression, mode="eval").body)


class GT430MapCorrectionTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.root = ET.parse(DEFINITION).getroot()
        cls.rom, = [rom for rom in cls.root.findall("rom")
                    if rom.findtext("romid/xmlid") == "T6-EVORA--F430-V000E"]

    def table(self, offset):
        table, = [table for table in self.rom.findall("table")
                  if int(table.get("storageaddress"), 16) == offset]
        return table

    def assert_conversion(self, scaling, oracle, values=range(256)):
        for raw in values:
            with self.subTest(raw=raw):
                displayed = calculate(scaling.get("expression"), raw)
                self.assertEqual(displayed, oracle(raw))
                self.assertEqual(calculate(scaling.get("to_byte"), displayed), raw)

    def test_stft_limit_matches_the_effect_on_fuel_pulse(self):
        # C16980: delta/pulse = STFT/2000; percentage = that ratio * 100.
        self.assert_conversion(self.table(0x014E).find("scaling"),
                               lambda raw: Fraction(raw, 2000) * 100,
                               (0, 1, 20, 200, 500, 1000, 32767))

    def test_coolant_thresholds_and_temperature_difference(self):
        for offset in (0x0060, 0x0061):
            scaling = self.table(offset).find("scaling")
            self.assertEqual(scaling.get("units"), "°C")
            self.assert_conversion(scaling, lambda raw: Fraction(raw * 5, 8) - 40)
        # C20723 subtracts two encoded absolute temperatures, cancelling -40.
        self.assert_conversion(self.table(0x010E).find("scaling"),
                               lambda raw: ((Fraction((raw + 100) * 5, 8) - 40)
                                            - (Fraction(100 * 5, 8) - 40)))

    def test_vehicle_speed_matches_hundredths_kph_consumer(self):
        # C55185: raw*200 is compared with car_speed_x100.
        self.assert_conversion(self.table(0x0262).find("scaling"),
                               lambda raw: Fraction(raw * 200, 100))

    def test_gear_advisory_thresholds_and_hysteresis(self):
        for offset in (0x45D4, 0x45D5, 0x45DA):
            self.assert_conversion(self.table(offset).find("scaling"),
                                   lambda raw: raw * 4 + raw + 500)
        # C57157: (threshold - hysteresis)*5+500; the delta has no offset.
        self.assert_conversion(self.table(0x45F0).find("scaling"),
                               lambda raw: (200 * 5 + 500)
                               - ((200 - raw) * 5 + 500))
        bound = self.table(0x45E4)
        self.assertEqual(bound.get("name"), "slip: gear advisory maximum engine rpm")
        self.assertEqual(bound.find("scaling").get("units"), "rpm")
        self.assert_conversion(bound.find("scaling"), lambda raw: raw,
                               (0, 1, 1000, 7000, 65535))

    def test_torque_pi_axes_decode_the_input_bias(self):
        # C52757-52765 saturates signed load error then adds 128.
        for offset, axis_offset in ((0x07FC, 0x07F4), (0x2776, 0x276E)):
            axis, = self.table(offset).findall("table")
            self.assertEqual(int(axis.get("storageaddress"), 16), axis_offset)
            self.assert_conversion(axis.find("scaling"), lambda raw: raw - 128)
            for error in range(-128, 128):
                encoded = error + 128
                self.assertEqual(calculate(axis.find("scaling").get("expression"),
                                           encoded), error)

    def test_filter_weights_match_the_fixed_point_denominators(self):
        for offset, denominator in ((0x5C6C, 256), (0x0222, 1024)):
            # The consumers weight the previous state by denominator-coeff.
            self.assert_conversion(self.table(offset).find("scaling"),
                                   lambda raw: Fraction(raw, denominator) * 100)

    def test_mode2f_timeout_matches_200hz_decrements(self):
        self.assert_conversion(self.table(0x4438).find("scaling"),
                               lambda raw: Fraction(raw, 200),
                               (0, 1, 100, 200, 1000, 65535))

    def test_spark_efficiency_rpm_axis_uses_the_common_speed_encoding(self):
        # C15459 and C12768/12772: RPM=(speed_byte+16)*125/4.
        axis, = [axis for axis in self.table(0x3626).findall("table")
                 if axis.get("type") == "X Axis"]
        self.assertEqual(int(axis.get("storageaddress"), 16), 0x3606)
        self.assertEqual(axis.find("scaling").get("units"), "rpm")
        self.assert_conversion(axis.find("scaling"),
                               lambda raw: Fraction((raw + 16) * 125, 4))

    def test_coldstart_axis_follows_the_adjacent_idle_decay_payload(self):
        # C15778 passes 40008d09+5. NA and the later GT export independently
        # establish the packed 5-axis, 5-data, 8-axis, 8-data layout.
        table = self.table(0x06C2)
        axis, = table.findall("table")
        base = 0x40008654
        start = 0x40008D09 + 5
        self.assertEqual(int(axis.get("storageaddress"), 16), start - base)
        self.assertEqual(int(axis.get("sizex")), 8)
        self.assertEqual(start + 8, base + int(table.get("storageaddress"), 16))

    def test_startup_tps_map_is_an_unsigned_base_timing_fraction(self):
        # C15718 unsigned lookup, C15725 neutral 255, C16068 base*raw/255.
        table = self.table(0x195E)
        self.assertEqual(table.get("storagetype"), "uint8")
        self.assertEqual(table.find("scaling").get("units"), "%")
        self.assert_conversion(table.find("scaling"),
                               lambda raw: Fraction(raw, 255) * 100)
        self.assertEqual(calculate(table.find("scaling").get("expression"), 255), 100)

    def test_pressure_offsets_match_signed_word_loads(self):
        # C15207/C15215/C15404 sign-extend only these offset operands.
        for offset in (0x02EE, 0x0032, 0x0302):
            table = self.table(offset)
            self.assertEqual(table.get("storagetype"), "int16")
            self.assertEqual(table.find("scaling").get("units"), "mbar")
            self.assert_conversion(table.find("scaling"), lambda raw: raw,
                                   (-32768, -1, 0, 1, 32767))
        # Purge offset has a different, unsigned subtraction consumer.
        self.assertEqual(self.table(0x002E).get("storagetype"), "uint16")

    def test_indexed_arrays_have_consumer_labels_not_voltage_axes(self):
        expected = {0x45B0: [f"Gear {i}" for i in range(1, 7)],
                    0x45BC: [f"Gear {i}" for i in range(1, 7)],
                    0x45C8: [f"Gear {i}" for i in range(1, 7)],
                    0x45D5: [f"Gear {i}" for i in range(2, 7)],
                    0x45DA: [f"Gear {i}" for i in range(2, 7)],
                    0x4670: ["Opening", "Closing"]}
        for offset, labels in expected.items():
            with self.subTest(offset=offset):
                table = self.table(offset)
                axis, = table.findall("table")
                self.assertEqual(axis.get("type"), "Static X Axis")
                self.assertEqual(int(axis.get("sizex")), len(labels))
                self.assertEqual(int(table.get("sizex")), len(labels))
                self.assertEqual([value.text for value in axis.findall("data")], labels)
                self.assertIsNone(axis.find("scaling"))
                self.assertIsNone(axis.get("storageaddress"))

    def test_identical_scalings_are_removed_but_alternative_units_remain(self):
        for table in self.root.iter("table"):
            scalings = [tuple(sorted(scaling.attrib.items()))
                        for scaling in table.findall("scaling")]
            self.assertEqual(len(scalings), len(set(scalings)), table.get("name"))
        afr_units = {scaling.get("units")
                     for scaling in self.table(0x1BCE).findall("scaling")}
        self.assertEqual(afr_units, {"A/F", "λ"})

    def test_patched_torque_caps_keep_their_explicit_warning_and_scale(self):
        # These require an identified patched executable. Do not silently apply
        # the stock consumer's 2 Nm/count conversion to a patched definition.
        for offset in (0x16BE, 0x2966):
            table = self.table(offset)
            self.assertIn("patched", table.findtext("description").lower())
            self.assert_conversion(table.find("scaling"), lambda raw: raw * 4)

    def test_xml_preserves_crlf(self):
        data = DEFINITION.read_bytes()
        self.assertEqual(data.count(b"\n"), data.count(b"\r\n"))


if __name__ == "__main__":
    unittest.main()
