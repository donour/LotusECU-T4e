"""aem30-0310: patch sites on both targets, the conflict with wideband, and
the detection / narrow-band simulation logic, run on each recipe's built
machine code with a small PowerPC interpreter (ppcsim.py).

	python -m unittest discover -s tests      (from custom_firmware/)
"""

import dataclasses, os, shutil, sys, tempfile, unittest

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(HERE)
sys.path.insert(0, ROOT)
sys.path.insert(0, HERE)

from ppcsim import CPU
from t6patch.config import ConfigError, load_module, load_recipe, load_target
from t6patch.image import FlashImage, PatchError
from t6patch.pipeline import Site, build, check_expectations
from t6patch.toolchain import Toolchain

RECIPES = ("s1-race-tc-aem30-0310", "gt430-federal-aem30-0310")

# Channel name: (offset in adc_dma_dest, firmware variable aem_loop writes)
CHANNELS = {
	"pre_b1": (44, "sensor_adc_pre_O2_bank1"),
	"pre_b2": (46, "sensor_adc_pre_O2_bank2"),
	"post_b1": (48, "sensor_adc_post_O2_bank1"),
	"post_b2": (50, "sensor_adc_post_O2_bank2"),
}
# From aem30_0310.S
CH_STATE, CH_HT_TH = 0, 10 # Channel struct offsets
ST_WB, ST_NB = 2001, 2002
NB_STOI, NB_RICH, NB_LEAN = 92, 184, 20
WB_MAX_I = 3000
STOCK_HT = 1500 # CAL_sensor_O2_heater_threshold in these tests, mA

def counts(volts):
	return round(volts * 1023 / 5)

class ECU:
	"""A build's aem30-0310 handlers, run as the firmware runs them: aem_init
	once, aem_5ms every 5 ms, aem_loop to produce the narrow-band values."""

	def __init__(self, res):
		self.elf = res.elf
		self.t = res.target.symbols
		self.cpu = CPU(res.elf)
		self.cpu.wr16(self.t["CAL_sensor_O2_heater_threshold"], STOCK_HT)
		self.ignition(True)
		self.cpu.call("aem_init")

	def ignition(self, on):
		self.cpu.wr16(self.t["ignition_on_flags"], int(on))

	def set(self, volts, ch="pre_b1"):
		# The firmware reads adc_dma_dest >> 4.
		self.cpu.wr16(self.t["adc_dma_dest"] + CHANNELS[ch][0], counts(volts) << 4)

	def run(self, seconds, volts=None, ch="pre_b1"):
		"""aem_5ms every 5 ms. `volts`: the channel's input, a value or f(sample index)."""
		for i in range(round(seconds * 200)):
			if(volts is not None): self.set(volts(i) if callable(volts) else volts, ch)
			self.cpu.call("aem_5ms")

	def ecu(self, volts=None, ch="pre_b1"):
		"""Run aem_loop: the value the firmware then sees for the channel (ADC counts)."""
		if(volts is not None): self.set(volts, ch)
		self.cpu.call("aem_loop")
		return self.cpu.rd16(self.t[CHANNELS[ch][1]])

	def state(self, ch="pre_b1"):
		return self.cpu.rd16(self.elf.symbol("aem_" + ch).value + CH_STATE)

	def heater_limit(self, ch="pre_b1"):
		return self.cpu.rd16(self.elf.symbol("aem_" + ch).value + CH_HT_TH)

class AEM30_0310(unittest.TestCase):
	@classmethod
	def setUpClass(cls):
		cls.tc = Toolchain()
		cls.module = load_module("aem30-0310")
		cls.builds = {}
		for name in RECIPES:
			r = load_recipe(name)
			if(r.cal and not os.path.exists(r.cal)): continue
			with tempfile.TemporaryDirectory() as work:
				cls.builds[name] = build(cls.tc, r, work, log=lambda s: None)
		if(not cls.builds): raise unittest.SkipTest("no input cal for any aem30-0310 recipe")

	def each(self, scenario):
		for name, res in self.builds.items():
			with self.subTest(recipe=name):
				scenario(ECU(res))

	# ---- Sites and recipe checks --------------------------------------------

	def test_sites_match_both_targets(self):
		for name in self.module.targets:
			t = load_target(name)
			prog = FlashImage("prog", t.find_base(t.prog), t.prog.base, t.prog.size)
			sites = lambda: [Site(f"aem.{s.name}", t.addr(s.at), s.name, s.expect_for(t.name))
				for s in self.module.sites]
			swapped = dict(t.symbols, sensor_adc_post_O2_bank1=t.symbols["sensor_adc_post_O2_bank2"],
				sensor_adc_post_O2_bank2=t.symbols["sensor_adc_post_O2_bank1"])
			with tempfile.TemporaryDirectory() as work:
				shutil.copyfile(t.sym_path, os.path.join(work, "symbols.sym"))
				check_expectations(self.tc, work, "symbols.sym", sites(), prog, t.symbols)
				with self.assertRaisesRegex(PatchError, "adc_skip_post_b1"):
					check_expectations(self.tc, work, "symbols.sym", sites(), prog, swapped)

	def test_heater_sites_read_their_channel(self):
		for name, res in self.builds.items():
			t = res.target
			for ch, at in (("pre_b1", "load_pre_O2_heater_threshold_bank1"),
					("pre_b2", "load_pre_O2_heater_threshold_bank2"),
					("post_b1", "load_post_O2_heater_threshold_bank1"),
					("post_b2", "load_post_O2_heater_threshold_bank2")):
				lis, addi, lhz = (int.from_bytes(res.prog.read(t.symbols[at] + i, 4), "big") for i in (0, 4, 8))
				ha, lo = lis & 0xFFFF, addi & 0xFFFF
				addr = ((ha << 16) + lo - (0x10000 if lo & 0x8000 else 0)) & 0xFFFFFFFF
				self.assertEqual(addr, res.elf.symbol(f"aem_{ch}").value, f"{name}: {at}")
				self.assertEqual(lhz & 0xFFFF, CH_HT_TH, f"{name}: {at} reads ch_ht_th")
			for at in ("adc_sample_pre_O2_bank1", "adc_sample_pre_O2_bank2",
					"adc_sample_post_O2_bank1", "adc_sample_post_O2_bank2"):
				self.assertEqual(res.prog.read(t.symbols[at], 4), bytes.fromhex("48000018"), f"{name}: {at}")

	def test_conflicts_with_wideband(self):
		# Rejected when the recipe is loaded (before any --stages build) and by build itself.
		with tempfile.TemporaryDirectory() as work:
			path = os.path.join(work, "both.toml")
			with open(path, "w") as f:
				f.write('target = "B13200091"\nmodules = ["race-tc", "aem30-0310", "wideband"]\n')
			with self.assertRaisesRegex(ConfigError, "aem30-0310 and wideband cannot be used together"):
				load_recipe(path)
			r = dataclasses.replace(load_recipe("s1-race-tc-wideband"), modules=["wideband", "aem30-0310"])
			with self.assertRaisesRegex(ConfigError, "cannot be used together"):
				build(self.tc, r, work, log=lambda s: None)

	# ---- Detection and narrow-band simulation (interpreted machine code) ----

	def test_narrow_band(self):
		def scenario(e):
			e.run(20, lambda i: (0.1, 0.9)[i // 40 % 2])
			self.assertEqual(e.state(), ST_NB)
			self.assertEqual(e.heater_limit(), STOCK_HT)
			self.assertEqual(e.ecu(0.7), counts(0.7), "passed through")
		self.each(scenario)

	def test_ready_at_key_on(self):
		def scenario(e):
			e.run(4.995, 3.1)
			self.assertLess(e.state(), 1000, "still in the 5 s window")
			self.assertEqual(e.ecu(3.1), NB_STOI, "stoichiometric during the window")
			e.run(0.005, 3.1)
			self.assertEqual(e.state(), ST_WB)
			self.assertEqual(e.heater_limit(), WB_MAX_I)
		self.each(scenario)

	def test_warming_up_after_window(self):
		# Not ready (below 0.5 V) for 12 s: narrow-band at 5 s, wideband after
		# 100 ms of valid readings.
		def scenario(e):
			e.run(5, 0.3)
			self.assertEqual(e.state(), ST_NB)
			self.assertEqual(e.heater_limit(), STOCK_HT)
			e.run(7, 0.3)
			e.run(0.095, 3.1)
			self.assertEqual(e.state(), ST_NB, "19 valid samples")
			e.run(0.005, 3.1)
			self.assertEqual(e.state(), ST_WB, "20 valid samples")
			self.assertEqual(e.heater_limit(), WB_MAX_I)
			e.run(10, 0.3)
			self.assertEqual(e.state(), ST_WB, "wideband until ignition off")
			self.assertEqual(e.ecu(0.3), NB_STOI)
		self.each(scenario)

	def test_narrow_band_passthrough_band(self):
		# Passed through up to 1.5 V (stock high-voltage DTC limit is 1.2 V) and
		# above 4.5 V (shorted to voltage); 1.5-4.5 V only comes from a wideband.
		def scenario(e):
			e.run(5, 0.3)
			for volts, want in ((1.2, counts(1.2)), (1.5, counts(1.5)), (1.51, NB_STOI),
					(2.0, NB_STOI), (4.497, NB_STOI), (4.502, counts(4.502)), (5.0, counts(5.0))):
				self.assertEqual(e.ecu(volts), want, f"{volts} V")
		self.each(scenario)

	def test_no_raw_wideband_before_detection(self):
		# A controller that warms up after the window: the ECU never sees its raw
		# voltage, before or after the channel switches.
		def scenario(e):
			e.run(5, 0.3)
			for i in range(20):
				self.assertEqual(e.state(), ST_NB)
				self.assertEqual(e.ecu(3.1), NB_STOI, f"sample {i}")
				e.run(0.005, 3.1)
			self.assertEqual(e.state(), ST_WB)
			self.assertTrue(NB_LEAN < e.ecu(3.1) < NB_RICH, "simulated narrow-band")
		self.each(scenario)

	def test_late_detection_needs_a_row(self):
		def scenario(e):
			e.run(5, 0.3)
			e.run(0.095, 3.1)
			e.run(0.005, 0.4)
			e.run(0.095, 3.1)
			self.assertEqual(e.state(), ST_NB, "count restarts after an invalid sample")
			e.run(0.005, 3.1)
			self.assertEqual(e.state(), ST_WB)
		self.each(scenario)

	def test_valid_band_edges(self):
		def scenario(e):
			e.run(5, 0.3)
			e.run(1, 2.5)
			self.assertEqual(e.state(), ST_NB, "2.5 V (512 counts) is not above 2.5 V")
			e.run(1, 4.502)
			self.assertEqual(e.state(), ST_NB, "921 counts is above 4.5 V")
			e.run(0.1, 4.497)
			self.assertEqual(e.state(), ST_WB, "920 counts is valid")
		self.each(scenario)

	def test_window_counts_in_total(self):
		def scenario(e):
			e.run(5, lambda i: 3.1 if i % 50 == 0 else 0.3) # 20 isolated valid samples
			self.assertEqual(e.state(), ST_WB)
		self.each(scenario)

	def test_shorted_narrow_band_stays_narrow_band(self):
		# A narrow-band shorted to 12 V reads ADC full scale: passed through, so
		# the stock high-voltage DTC still works. From key-on and mid-drive.
		def scenario(e):
			e.run(20, 5.0)
			self.assertEqual(e.state(), ST_NB)
			self.assertEqual(e.ecu(5.0), counts(5.0))
		self.each(scenario)
		def mid_drive(e):
			e.run(10, 0.45)
			e.run(20, 5.0)
			self.assertEqual(e.state(), ST_NB)
		self.each(mid_drive)

	def test_sensor_error_from_key_on(self):
		def scenario(e):
			e.run(5, lambda i: 4.8 if i % 2 else 0.3)
			e.run(10, 4.7)
			self.assertEqual(e.state(), ST_NB)
			self.assertEqual(e.ecu(4.7), counts(4.7), "passed through")
		self.each(scenario)

	def test_ignition_off_restarts_window(self):
		def scenario(e):
			e.run(5, 3.1)
			e.ignition(False)
			e.run(1, 0.0)
			self.assertEqual(e.state(), 0)
			self.assertEqual(e.heater_limit(), WB_MAX_I)
			e.ignition(True)
			e.run(5, 3.1)
			self.assertEqual(e.state(), ST_WB)
		self.each(scenario)

	def test_simulated_narrow_band(self):
		def scenario(e):
			e.run(5, 3.1)
			for volts, want, what in ((0.3, NB_STOI, "not ready"), (0.499, NB_STOI, "below 0.5 V"),
					(0.51, NB_RICH, "8.5 AFR"), (2.9, NB_RICH, "14.2 AFR"), (3.4, NB_LEAN, "15.4 AFR"),
					(4.497, NB_LEAN, "18 AFR"), (4.51, NB_STOI, "sensor error")):
				self.assertEqual(e.ecu(volts), want, f"{volts} V ({what})")
			self.assertTrue(NB_LEAN < e.ecu(3.11) < NB_RICH, "14.7 AFR is on the ramp")
		self.each(scenario)

	def test_channels_are_independent(self):
		# Each channel reads its own ADC input and writes its own firmware variable.
		def scenario(e):
			e.set(3.1, "pre_b1")    # AEM, ready
			e.set(0.7, "pre_b2")    # narrow-band
			e.set(5.0, "post_b1")   # narrow-band shorted to voltage
			e.set(0.3, "post_b2")   # AEM, warming up
			e.run(5)
			e.run(0.1, 3.1, "post_b2")
			self.assertEqual([e.state(c) for c in CHANNELS], [ST_WB, ST_NB, ST_NB, ST_WB])
			self.assertEqual([e.heater_limit(c) for c in CHANNELS], [WB_MAX_I, STOCK_HT, STOCK_HT, WB_MAX_I])
			e.set(3.4, "pre_b1")
			e.set(2.9, "post_b2")
			e.cpu.call("aem_loop")
			self.assertEqual([e.cpu.rd16(e.t[CHANNELS[c][1]]) for c in CHANNELS],
				[NB_LEAN, counts(0.7), counts(5.0), NB_RICH])
		self.each(scenario)

if __name__ == "__main__":
	unittest.main()
