"""Regression: t6patch's linker script, expectation check and site writer
reproduce, byte for byte, images built by the old patch/build.py.

Each fixture takes the legacy sources from git, links them with t6patch's
generated linker script at the legacy addresses, applies the same sites the
old build.py patched (now written as assembly), and compares the trimmed
prog/cal with the md5 of the legacy output.

	python -m unittest discover -s tests      (from custom_firmware/)

Needs the cross binutils, git, and the input images (skipped if missing).
"""

import hashlib, os, subprocess, sys, tempfile, unittest

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(HERE)
REPO = os.path.dirname(ROOT)
sys.path.insert(0, ROOT)

from t6patch import codegen
from t6patch.image import FlashImage, parse_sym_file
from t6patch.pipeline import Layout, Site, apply_code, check_expectations, link
from t6patch.toolchain import Toolchain

HOOK_SITES = [
	("init", "hook_init_loc", ["lwz %r0, 20(%r1)"], ["ba hook_init"]),
	("loop", "hook_loop_loc", ["b hook_loop_continue"], ["ba hook_loop"]),
	("tick", "hook_timer_5ms_loc", ["li %r0, 10"], ["ba hook_timer_5ms"]),
]

def wideband_sites(wb_ht_th=18):
	sites = []
	for bank in (1, 2):
		sites.append((f"wb_heater_b{bank}", f"load_pre_O2_heater_threshold_bank{bank}",
			["lis %r3, CAL_base@ha", "addi %r3, %r3, CAL_base@l",
				"lhz %r0, {CAL_sensor_O2_heater_threshold - CAL_base}(%r3)"],
			[f"lis %r3, wb_bank{bank}@ha", f"addi %r3, %r3, wb_bank{bank}@l",
				f"lhz %r0, {wb_ht_th}(%r3)"]))
		sites.append((f"wb_adc_b{bank}", f"adc_sample_pre_O2_bank{bank}",
			["lis %r3, 0x4000"], ["b .+0x18"]))
	return sites

FREERAM = ["lis %r3, __patch_bss_end@ha", "addi %r0, %r3, __patch_bss_end@l"]
FREERAM_EXPECT = ["lis %r3, 0x4001", "addi %r0, %r3, -0x1000"]

FIXTURES = [
	{
		# 20260706/s1_dpm: DPM on B13200091. Same image as
		# patch/dpm-b132e0091-prog-only.crp.
		"name": "s1_dpm",
		"commit": "a15fc67",
		"files": ["patch/t6/combined/hook.S", "patch/t6/combined/cal.S",
			"patch/t6/combined/obd_can.S", "patch/t6/dpm/dpm.S", "patch/t6/T6-V00BU.sym"],
		"sources": ["patch/t6/combined/hook.S", "patch/t6/combined/cal.S",
			"patch/t6/combined/obd_can.S", "patch/t6/dpm/dpm.S"],
		"asflags": ["--defsym", "DPM=1"],
		"include": "patch/t6/combined",
		"sym": "patch/t6/T6-V00BU.sym",
		"prog": "bases/T6EGLBU01_BIN.cpt",
		"cal": "bases/B132E0091_TAB.cpt",
		"layout": Layout(0xCA770, 0x100000, 0x261DA, 0x40000, 0x4000F000, 0x40010000),
		"sites": HOOK_SITES + [
			("loop_corr", "hook_loop_correction", ["ble hook_loop_continue"], ["ble hook_loop_loc"]),
			("arb", "hook_torque_limit_arbitration", ["blr"], ["ba hook_arbitration_dpm"]),
			("freeram", "hook_freeram_counter", FREERAM_EXPECT, FREERAM),
		],
		"prog_md5": "70de74ea3cbe32f3c9541414e3f1d78f",
		"cal_md5": "f89653282a2bd3624e5bcd4768fac2a7",
	},
	{
		# master_t6e: wideband + flexfuel (+ OBD) on the GT430.
		"name": "gt430_wb_ff",
		"commit": "8cc93b6",
		"files": ["patch/t6/combined/hook.S", "patch/t6/combined/cal.S",
			"patch/t6/combined/obd_can.S", "patch/t6/flexfuel/flexfuel.S",
			"patch/t6/flexfuel/cal.inc.S", "patch/t6/wideband/wideband.S", "patch/t6/T6-GT430.sym"],
		"sources": ["patch/t6/combined/hook.S", "patch/t6/combined/cal.S",
			"patch/t6/combined/obd_can.S", "patch/t6/flexfuel/flexfuel.S",
			"patch/t6/wideband/wideband.S"],
		"asflags": ["--defsym", "FLEXFUEL=1", "--defsym", "WIDEBAND=1"],
		"include": "patch/t6/combined",
		"sym": "patch/t6/T6-GT430.sym",
		"prog": "../patch/T6EVRGT430E01_BIN.cpt", # The hand-patched prog of the legacy builds
		"cal": "../patch/C132E0278_TAB.20260628-93octane.cpt",
		"layout": Layout(0xD8988, 0x100000, 0x269AC, 0x40000, 0x4000F000, 0x40010000),
		"sites": HOOK_SITES + [
			("loop_corr", 0x42FBC, ["ble hook_loop_continue"], ["ble hook_loop_loc"]),
			("obd01", "hook_OBD_mode_0x01_loc", ["rlwinm %r0, %r31, 0, 24, 31"], ["ba hook_OBD_mode_0x01"]),
			("obd22", "hook_OBD_mode_0x22_loc", ["rlwinm %r4, %r0, 0, 16, 31"], ["ba hook_OBD_mode_0x22"]),
			("freeram", 0x42FE8, FREERAM_EXPECT, FREERAM),
			("pcr184", 0x4285C, ["li %r0, 0x0100"], ["li %r0, 0x0500"]),
		] + wideband_sites(),
		"prog_md5": "cec84e62498975ddd313da1aeac2ca11",
		"cal_md5": "b55b330e24a00daabf8e143a8423843b",
	},
]

def md5(data):
	return hashlib.md5(data).hexdigest()

class LegacyRegression(unittest.TestCase):
	@classmethod
	def setUpClass(cls):
		cls.tc = Toolchain()

	def run_fixture(self, fx):
		for k in ("prog", "cal"):
			if(not os.path.exists(os.path.join(ROOT, fx[k]))):
				self.skipTest(f"{fx[k]} not found")
		with tempfile.TemporaryDirectory() as work:
			for f in fx["files"]:
				dst = os.path.join(work, f)
				os.makedirs(os.path.dirname(dst), exist_ok=True)
				blob = subprocess.run(["git", "show", f"{fx['commit']}:{f}"], cwd=REPO,
					capture_output=True, check=True).stdout
				with open(dst, "wb") as fh: fh.write(blob)
			gen = os.path.join(work, "gen")
			os.makedirs(gen)
			with open(os.path.join(work, fx["sym"]), "rb") as a, \
				open(os.path.join(gen, "symbols.sym"), "wb") as b: b.write(a.read())
			symbols = parse_sym_file(os.path.join(gen, "symbols.sym"))
			at = lambda a: a if isinstance(a, int) else symbols[a]
			sites = [Site(k, at(a), k, exp) for k, a, exp, _ in fx["sites"]]

			prog = FlashImage("prog", os.path.join(ROOT, fx["prog"]), 0x40000, 0xC0000)
			cal = FlashImage("cal", os.path.join(ROOT, fx["cal"]), 0x20000, 0x20000)
			expected = check_expectations(self.tc, gen, "symbols.sym", sites, prog, symbols)

			objs = []
			for i, src in enumerate(fx["sources"]):
				obj = os.path.join(gen, f"{i:02d}.o")
				self.tc.assemble(os.path.join(work, src), obj, flags=fx["asflags"],
					includes=[os.path.join(work, fx["include"])])
				objs.append(obj)
			sites_src = os.path.join(gen, "sites.S")
			with open(sites_src, "w", newline="\n") as f:
				f.write(codegen.replace_asm([(k, rep) for k, _, _, rep in fx["sites"]], symbols))
			self.tc.assemble(sites_src, os.path.join(gen, "sites.o"), flags=["-mregnames"])
			objs.append(os.path.join(gen, "sites.o"))

			elf = link(self.tc, gen, "symbols.sym", fx["layout"], objs, sites)
			apply_code(elf, sites, expected, prog)
			data = elf.section(".data")
			self.assertTrue(cal.is_blank(data.addr, data.size))
			cal.write(data.addr, data.data, "legacy cal")

			self.assertEqual(md5(prog.trimmed()), fx["prog_md5"], "prog differs from the legacy build")
			self.assertEqual(md5(cal.trimmed()), fx["cal_md5"], "cal differs from the legacy build")

	def test_s1_dpm(self):
		self.run_fixture(FIXTURES[0])

	def test_gt430_wideband_flexfuel(self):
		self.run_fixture(FIXTURES[1])

if __name__ == "__main__":
	unittest.main()
