"""Exercise bounded re-export repairs and output safety using small fixtures."""

from contextlib import redirect_stderr, redirect_stdout
import importlib.util
import io
import os
from pathlib import Path
import sys
import tempfile
import unittest
from unittest.mock import patch
import xml.etree.ElementTree as ET


DIRECTORY = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location(
    "reconcile_reviewed_metadata", DIRECTORY / "reconcile_reviewed_metadata.py")
reconcile_tool = importlib.util.module_from_spec(SPEC)
sys.modules[SPEC.name] = reconcile_tool
SPEC.loader.exec_module(reconcile_tool)


def table(name, expression, *, address="0x10", storage="uint8", count="2",
          endian="big", kind="2D", axis="stored"):
    if axis == "stored":
        axis_xml = ('<table name="temperature" type="X Axis" sizex="2" '
                    'storageaddress="0x08" storagetype="uint8" endian="big">'
                    '<scaling expression="x-40" to_byte="x+40"/></table>')
    else:
        axis_xml = ('<table name="signal" type="Static X Axis" sizex="2">'
                    '<data>0</data><data>32</data></table>')
    return (f'<table name="{name}" storageaddress="{address}" storagetype="{storage}" '
            f'sizex="{count}" type="{kind}" endian="{endian}">'
            f'<scaling expression="{expression}" to_byte="x"/>{axis_xml}'
            f'<description>{name}</description></table>').encode()


def rom(rom_id, tables):
    return b'<rom><romid><xmlid>' + rom_id.encode() + b'</xmlid></romid>' + tables + b'</rom>'


class ReconciliationTests(unittest.TestCase):
    def setUp(self):
        self.temporary = tempfile.TemporaryDirectory()
        self.addCleanup(self.temporary.cleanup)
        self.directory = Path(self.temporary.name)
        self.canonical = self.directory / "canonical.xml"
        self.other_canonical = self.directory / "other-canonical.xml"
        self.reviewed = table("reviewed", "x/4")
        self.stale = table("stale", "x", axis="static", storage="int8")
        self.untouched = table("exporter's extra table", "x+17", address="0x20")
        self.learned = table("reviewed learned", "x/10", storage="int16")
        self.other_reviewed = table("other reviewed", "x*2")
        self.other_exported = table("other exported", "x+3")
        self.canonical.write_bytes(
            b'<roms>' + rom("ROM_A", self.reviewed) + rom("ROM_A learned", self.learned)
            + b'</roms>')
        self.other_canonical.write_bytes(b'<roms>' + rom("ROM_B", self.other_reviewed) + b'</roms>')
        profiles = {"ROM_A": (self.canonical, frozenset((0x10,))),
                    "ROM_A learned": (self.canonical, frozenset((0x10,))),
                    "ROM_B": (self.other_canonical, frozenset((0x10,)))}
        self.patcher = patch.dict(reconcile_tool.PROFILES, profiles, clear=True)
        self.patcher.start()
        self.addCleanup(self.patcher.stop)
        self.original = (b'<?xml version="1.0"?>\r\n<roms><!-- keep outer bytes -->'
                         + rom("ROM_A", self.stale + b'\n<!-- unchanged -->' + self.untouched)
                         + rom("ROM_B", self.other_exported) + b'</roms>\r\n')
        self.exported = self.directory / "fresh.xml"
        self.exported.write_bytes(self.original)

    def run_cli(self, *arguments):
        output, error = io.StringIO(), io.StringIO()
        with redirect_stdout(output), redirect_stderr(error):
            code = reconcile_tool.main([str(self.exported), "--rom-id", "ROM_A", *arguments])
        return code, output.getvalue(), error.getvalue()

    def test_profile_isolation_axis_repair_and_byte_preservation(self):
        result = reconcile_tool.reconcile(self.original, "ROM_A")
        expected = self.original.replace(self.stale, self.reviewed, 1)
        self.assertEqual(result.data, expected)
        self.assertEqual(result.changed, (0x10,))
        self.assertIn(self.other_exported, result.data)
        self.assertIn(self.untouched, result.data)
        self.assertEqual(self.exported.read_bytes(), self.original)
        self.assertEqual(len(result.canonical_sha256), 64)

    def test_selecting_other_rom_never_repairs_first_rom(self):
        result = reconcile_tool.reconcile(self.original, "ROM_B")
        self.assertEqual(result.data, self.original.replace(self.other_exported,
                                                           self.other_reviewed, 1))
        self.assertIn(self.stale, result.data)

    def test_calibration_and_learned_ids_are_distinct(self):
        stale_learned = table("stale learned", "x", storage="uint16")
        data = b'<roms>' + rom("ROM_A", self.stale) + rom("ROM_A learned", stale_learned) + b'</roms>'
        result = reconcile_tool.reconcile(data, "ROM_A learned")
        self.assertEqual(result.data, data.replace(stale_learned, self.learned, 1))
        self.assertIn(self.stale, result.data)

    def test_reconciliation_is_idempotent(self):
        first = reconcile_tool.reconcile(self.original, "ROM_A")
        second = reconcile_tool.reconcile(first.data, "ROM_A")
        self.assertEqual(second.data, first.data)
        self.assertEqual(second.changed, ())

    def test_rejects_missing_duplicate_or_wrong_rom(self):
        bad_inputs = [b'<roms>' + rom("ROM_A", self.untouched) + b'</roms>',
                      b'<roms>' + rom("ROM_A", self.stale + self.stale) + b'</roms>',
                      b'<roms>' + rom("ROM_A", self.stale) + rom("ROM_A", self.stale) + b'</roms>',
                      b'<roms>' + rom("ROM_B", self.stale) + b'</roms>']
        for data in bad_inputs:
            with self.subTest(data=data), self.assertRaises(reconcile_tool.ReconciliationError):
                reconcile_tool.reconcile(data, "ROM_A")

    def test_rejects_changed_payload_layout_but_allows_signedness(self):
        for attributes in ({"address": "0x11"}, {"storage": "uint16"},
                           {"count": "3"}, {"count": "0"}, {"endian": "little"},
                           {"kind": "3D"}, {"storage": "float"}):
            data = b'<roms>' + rom("ROM_A", table("changed", "x", **attributes)) + b'</roms>'
            with self.subTest(attributes=attributes), self.assertRaises(reconcile_tool.ReconciliationError):
                reconcile_tool.reconcile(data, "ROM_A")
        # Fixture stale storage is signed int8, canonical is unsigned uint8.
        self.assertEqual(reconcile_tool.reconcile(self.original, "ROM_A").changed, (0x10,))

    def test_handles_self_closing_root_and_quoted_angle_brackets(self):
        root = b'<table name="stale > root" storageaddress="0x10" storagetype="uint8" sizex="2" type="2D" endian="big"/>'
        data = b'<roms>' + rom("ROM_A", root) + b'</roms>'
        self.assertEqual(reconcile_tool.reconcile(data, "ROM_A").data,
                         data.replace(root, self.reviewed))

    def test_rejects_doctype_and_malformed_xml(self):
        for data in (b'<!DOCTYPE roms [<!ENTITY x "test">]><roms/>', b'<roms>', b'\xff'):
            with self.subTest(data=data), self.assertRaises(reconcile_tool.ReconciliationError):
                reconcile_tool.reconcile(data, "ROM_A")

    def test_check_reports_drift_without_writes_then_passes(self):
        files_before = set(self.directory.iterdir())
        code, output, error = self.run_cli("--check")
        self.assertEqual(code, 1)
        self.assertIn("0x0010", output)
        self.assertEqual(error, "")
        self.assertEqual(set(self.directory.iterdir()), files_before)
        self.assertEqual(self.exported.read_bytes(), self.original)
        self.exported.write_bytes(reconcile_tool.reconcile(self.original, "ROM_A").data)
        self.assertEqual(self.run_cli("--check")[0], 0)

    def test_output_is_a_new_file_and_input_is_unchanged(self):
        output_path = self.directory / "reconciled.xml"
        code, output, error = self.run_cli("--output", str(output_path))
        self.assertEqual((code, error), (0, ""))
        self.assertEqual(output_path.read_bytes(), self.original.replace(self.stale, self.reviewed, 1))
        self.assertEqual(self.exported.read_bytes(), self.original)
        self.assertIn("Canonical SHA-256:", output)

    def test_invalid_geometry_does_not_create_output(self):
        self.exported.write_bytes(self.original.replace(b'storagetype="int8"',
                                                        b'storagetype="int16"', 1))
        output = self.directory / "not-created.xml"
        self.assertEqual(self.run_cli("--output", str(output))[0], 2)
        self.assertFalse(output.exists())

    def test_refuses_existing_outputs_input_and_any_canonical_file(self):
        existing = self.directory / "existing.xml"
        existing.write_bytes(b"keep existing")
        for output in (existing, self.exported, self.canonical, self.other_canonical):
            before = output.read_bytes()
            with self.subTest(output=output):
                self.assertEqual(self.run_cli("--output", str(output))[0], 2)
                self.assertEqual(output.read_bytes(), before)

    def test_refuses_symlink_and_hardlink_aliases(self):
        canonical_alias = self.directory / "canonical-link.xml"
        canonical_alias.symlink_to(self.canonical)
        input_alias = self.directory / "input-link.xml"
        input_alias.symlink_to(self.exported)
        hardlink = self.directory / "hardlink.xml"
        os.link(self.canonical, hardlink)
        for output in (canonical_alias, input_alias, hardlink):
            with self.subTest(output=output):
                self.assertEqual(self.run_cli("--output", str(output))[0], 2)
        self.assertEqual(self.exported.read_bytes(), self.original)
        self.assertIn(self.reviewed, self.canonical.read_bytes())

    def test_real_profiles_are_already_reconciled(self):
        # Exercise the shipped XML and span parser, without a second manifest.
        self.patcher.stop()
        for rom_id, (path, allowed) in reconcile_tool.PROFILES.items():
            with self.subTest(rom_id=rom_id):
                result = reconcile_tool.reconcile(path.read_bytes(), rom_id)
                self.assertEqual(result.changed, ())
                self.assertEqual(result.data, path.read_bytes())
                self.assertTrue(allowed)


if __name__ == "__main__":
    unittest.main()
