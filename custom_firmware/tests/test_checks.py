"""Safety checks: the build must refuse wrong firmware assumptions, and keep
tuned patch calibration across rebuilds.

	python -m unittest discover -s tests      (from custom_firmware/)
"""

import dataclasses, os, shutil, sys, tempfile, unittest

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, ROOT)

from t6patch.config import load_recipe, load_target
from t6patch.image import FlashImage, PatchError
from t6patch.pipeline import Site, build, check_expectations
from t6patch.toolchain import Toolchain

class SiteChecks(unittest.TestCase):
	@classmethod
	def setUpClass(cls):
		cls.tc = Toolchain()

	def test_wrong_symbol_is_caught(self):
		# patch/t6/T6-V00BU.sym had sensor_adc_pre_O2_bank2 = 0x40001716 (really
		# bank-1 post-cat). The wideband site expectation must reject it.
		t = load_target("B13200091")
		prog = FlashImage("prog", t.find_base(t.prog), t.prog.base, t.prog.size)
		symbols = dict(t.symbols, sensor_adc_pre_O2_bank2=0x40001716)
		site = Site("wb.adc_skip_b2", t.symbols["adc_sample_pre_O2_bank2"], "adc_skip_b2", [
			"lis %r3, adc_dma_dest@ha", "addi %r3, %r3, adc_dma_dest@l", "lhz %r0, 46(%r3)",
			"srawi %r0, %r0, 4", "clrlwi %r0, %r0, 16",
			"sth %r0, {sensor_adc_pre_O2_bank2 - _SDA_BASE_}(%r13)"])
		with tempfile.TemporaryDirectory() as work:
			shutil.copyfile(t.sym_path, os.path.join(work, "symbols.sym"))
			check_expectations(self.tc, work, "symbols.sym", [site], prog, t.symbols)
			with self.assertRaisesRegex(PatchError, "adc_skip_b2"):
				check_expectations(self.tc, work, "symbols.sym", [site], prog, symbols)

	def test_overlapping_writes_rejected(self):
		t = load_target("B13200091")
		prog = FlashImage("prog", t.find_base(t.prog), t.prog.base, t.prog.size)
		prog.write(0x42D10, b"\x60\x00\x00\x00", "module a")
		with self.assertRaisesRegex(PatchError, "module b .* overlaps module a"):
			prog.write(0x42D0C, b"\x60\x00\x00\x00" * 2, "module b")

class PatchCalRebuild(unittest.TestCase):
	RECIPE = os.path.join(ROOT, "recipes", "gt430-wideband-flexfuel.toml")

	@classmethod
	def setUpClass(cls):
		cls.tc = Toolchain()
		cls.recipe = load_recipe(cls.RECIPE)
		if(not os.path.exists(cls.recipe.cal)): raise unittest.SkipTest(f"{cls.recipe.cal} not found")

	def test_tuned_values_survive_rebuild(self):
		quiet = lambda s: None
		with tempfile.TemporaryDirectory() as work:
			first = build(self.tc, self.recipe, os.path.join(work, "a"), log=quiet)
			addr = first.elf.symbol("CAL_ethanol_sensor_engine_speed_limit").value
			self.assertEqual(first.cal.read(addr, 1), b"\x70")
			defaults = first.cal.trimmed()

			# "Tune" the patch cal entry, as RomRaider would, and rebuild.
			tuned = os.path.join(work, "tuned.bin")
			first.cal.write(addr, b"\x80")
			first.cal.save(tuned)
			second = build(self.tc, self.recipe, os.path.join(work, "b"), cal_path=tuned, log=quiet)
			self.assertIn("kept", second.cal_note)
			self.assertEqual(second.cal.read(addr, 1), b"\x80")
			self.assertEqual(second.prog.trimmed(), first.prog.trimmed())

			# A block with another layout is refused unless reset.
			other = FlashImage("cal", tuned, 0x20000, 0x10000)
			other.write(first.elf.symbol("CAL_extra").value + 8, b"\0\0\0\0")
			other.save(tuned)
			with self.assertRaisesRegex(PatchError, "reset-patch-cal"):
				build(self.tc, self.recipe, os.path.join(work, "c"), cal_path=tuned, log=quiet)
			reset = build(self.tc, self.recipe, os.path.join(work, "d"), cal_path=tuned,
				reset_patch_cal=True, log=quiet)
			self.assertEqual(reset.cal.trimmed(), defaults)

class CalSites(unittest.TestCase):
	"""race-tc's slip-target tables live in stock-cal locations labelled unused."""

	@classmethod
	def setUpClass(cls):
		cls.tc = Toolchain()
		cls.recipe = load_recipe("s1-race-tc")

	def test_defaults_then_kept(self):
		quiet = lambda s: None
		with tempfile.TemporaryDirectory() as work:
			first = build(self.tc, self.recipe, os.path.join(work, "a"), log=quiet)
			self.assertEqual(first.cal.read(0x2030E, 16), bytes([1] * 8 + list(range(2, 10))))
			self.assertEqual(first.cal.read(0x2031E, 16), bytes(8) + bytes(range(24, 193, 24)))
			self.assertTrue(all(c.note == "default values written" for c in first.cal_sites))

			tuned = os.path.join(work, "tuned.bin")
			first.cal.write(0x2032D, b"\x70")
			first.cal.save(tuned)
			second = build(self.tc, self.recipe, os.path.join(work, "b"), cal_path=tuned, log=quiet)
			self.assertEqual(second.cal.read(0x2032D, 1), b"\x70")
			self.assertTrue(all(c.note.startswith("kept") for c in second.cal_sites))

	def test_used_location_rejected(self):
		# A cal site whose stock bytes are not the declared ones must fail.
		from t6patch.config import ModuleCalSite
		from t6patch.pipeline import CalSite, apply_cal_sites
		t = load_target("B13200091")
		stock = FlashImage("stock cal", t.find_base(t.cal), t.cal.base, t.cal.size)
		class FakeElf:
			def section(self, name):
				from t6patch.elf import Section
				return Section(name, 1, 2, 0x20222, 1, b"\x01")
		site = CalSite("x.y", 0x20222, 0x40009046, "CAL_tpms_version site", ModuleCalSite("y", 0, "ff"))
		with self.assertRaisesRegex(PatchError, "really unused"):
			apply_cal_sites(FakeElf(), [site], FlashImage("cal", t.find_base(t.cal), t.cal.base, t.cal.size), stock)

if __name__ == "__main__":
	unittest.main()
