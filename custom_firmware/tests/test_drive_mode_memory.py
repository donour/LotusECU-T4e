"""drive-mode-memory: its sites on the stock GT430 prog, and the save/restore
logic run on the built machine code with ppcsim.py.

	python -m unittest discover -s tests      (from custom_firmware/)
"""

import os, sys, tempfile, unittest

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(HERE)
sys.path.insert(0, ROOT)
sys.path.insert(0, HERE)

from ppcsim import CPU
from t6patch.config import load_recipe
from t6patch.pipeline import build
from t6patch.toolchain import Toolchain

RECIPE = "gt430-federal-drive-mode-memory"
TOUR, SPORT, TC_OFF, RACE, LAUNCH, LAUNCH_SUB1, DPM = range(7)
SAVE_OFF = 1601 # In LEA_core_reserved
COD1_RACE, COD1_EXHAUST = 1 << 7, 1 << 30

class ECU:
	"""The module's handlers as the firmware calls them: drive_mode_memory_5ms
	at 200 Hz, drive_mode_memory_dispatch from the mode function's normal path."""

	def __init__(self, res, enable=3, cod1=COD1_RACE | COD1_EXHAUST):
		self.t = res.target.symbols
		self.cpu = CPU(res.elf)
		s = self.cpu.symbols
		self.cpu.mem[s["CAL_base_extra"] + s["OFF_CAL_drive_mode_memory_enable"]] = enable
		self.cpu.wr32(self.t["COD_base"] + 4, cod1)
		self.save = self.t["LEA_core_reserved"] + SAVE_OFF
		self.exhaust_addr = self.t["digital_input_debounced"] + 12
		self.ignition(True)

	def ignition(self, on):
		self.cpu.wr16(self.t["ignition_on_flags"], int(on))
		self.cpu.call("drive_mode_memory_5ms")

	def rpm(self, v): self.cpu.wr16(self.t["engine_speed_2"], v)

	@property
	def mode(self): return self.cpu.mem.get(self.t["vehicle_mode"], 0)
	@mode.setter
	def mode(self, v): self.cpu.mem[self.t["vehicle_mode"]] = v

	@property
	def exhaust(self): return self.cpu.mem.get(self.exhaust_addr, 0)
	@exhaust.setter
	def exhaust(self, v): self.cpu.mem[self.exhaust_addr] = v

	def saved(self): return (self.cpu.mem.get(self.save, 0), self.cpu.mem.get(self.save + 1, 0))
	def preset(self, mode, exhaust):
		self.cpu.mem[self.save], self.cpu.mem[self.save + 1] = mode, exhaust

	def dispatch(self, event=0):
		self.cpu.r[3] = event
		self.cpu.call("drive_mode_memory_dispatch")
		self.assertEqual(self.cpu.r[3], event, "r3 (button event) preserved")
		self.assertEqual(self.cpu.r[0], self.mode, "returns r0 = vehicle_mode")

class DriveModeMemory(unittest.TestCase):
	@classmethod
	def setUpClass(cls):
		r = load_recipe(RECIPE)
		if(r.cal and not os.path.exists(r.cal)): raise unittest.SkipTest(f"no input cal for {RECIPE}")
		with tempfile.TemporaryDirectory() as work:
			cls.res = build(Toolchain(), r, work, log=lambda s: None)

	def ecu(self, **kw):
		e = ECU(self.res, **kw)
		e.assertEqual = self.assertEqual
		return e

	def test_sites(self):
		t, prog = self.res.target.symbols, self.res.prog
		self.assertEqual(prog.read(t["eeprom_load_reserved_clear_limit"], 4), bytes.fromhex("28000641")) # cmplwi r0,1601
		ins = int.from_bytes(prog.read(t["vehicle_mode_dispatch"], 4), "big")
		self.assertEqual(ins >> 26, 18)
		self.assertEqual(ins & 3, 1) # bl
		li = ins & 0x03FFFFFC
		self.assertEqual(t["vehicle_mode_dispatch"] + li, self.res.elf.symbol("drive_mode_memory_dispatch").value)

	def test_sport_restored_and_saved(self):
		e = self.ecu()
		e.preset(SPORT, 0)
		e.dispatch()
		self.assertEqual(e.mode, SPORT)
		e.mode = TOUR # driver goes back to Tour
		e.dispatch()
		self.assertEqual(e.saved(), (TOUR, 0))

	def test_race_waits_for_engine(self):
		e = self.ecu()
		e.preset(RACE, 1)
		for _ in range(5): e.dispatch()
		self.assertEqual((e.mode, e.exhaust), (TOUR, 0))
		self.assertEqual(e.saved(), (RACE, 1), "nothing saved while waiting")
		e.rpm(150)
		e.dispatch()
		self.assertEqual((e.mode, e.exhaust), (RACE, 1), "exhaust restored after the mode")

	def test_race_not_coded(self):
		e = self.ecu(cod1=COD1_EXHAUST)
		e.preset(RACE, 0)
		e.rpm(800)
		e.dispatch()
		self.assertEqual(e.mode, TOUR)

	def test_button_event_and_driver_choice_win(self):
		e = self.ecu()
		e.preset(SPORT, 0)
		e.dispatch(event=4) # a press this tick: not restored yet
		self.assertEqual(e.mode, TOUR)
		e.mode = RACE # the press took effect
		e.rpm(800)
		e.dispatch()
		self.assertEqual(e.mode, RACE)
		e.dispatch()
		self.assertEqual(e.saved()[0], RACE)

	def test_mode_mapping(self):
		e = self.ecu()
		e.dispatch() # restore (Tour)
		for m, want in ((SPORT, SPORT), (TC_OFF, TOUR), (RACE, RACE), (LAUNCH, RACE),
				(LAUNCH_SUB1, RACE), (DPM, RACE), (TOUR, TOUR)):
			e.mode = m
			e.dispatch()
			self.assertEqual(e.saved()[0], want, f"mode {m}")
			self.assertEqual(e.mode, m, "tracking never changes the mode")

	def test_key_cycle_without_reboot(self):
		e = self.ecu()
		e.dispatch()
		e.mode, e.exhaust = SPORT, 1
		e.dispatch()
		# Key off: the firmware forces Tour and zeroes the toggle; the normal
		# path (and so dispatch) does not run.
		e.ignition(False)
		e.mode, e.exhaust = TOUR, 0
		e.ignition(True)
		self.assertEqual(e.saved(), (SPORT, 1))
		e.dispatch()
		self.assertEqual((e.mode, e.exhaust), (SPORT, 1))

	def test_exhaust_needs_switch_and_keeps_press(self):
		e = self.ecu(cod1=COD1_RACE)
		e.preset(TOUR, 1)
		e.dispatch()
		self.assertEqual(e.exhaust, 0, "no exhaust switch coded")
		e = self.ecu()
		e.preset(TOUR, 0)
		e.exhaust = 1 # pressed before the restore
		e.dispatch()
		self.assertEqual(e.exhaust, 1)

	def test_enable_bits(self):
		e = self.ecu(enable=2)
		e.preset(SPORT, 1)
		e.dispatch()
		self.assertEqual((e.mode, e.exhaust), (TOUR, 1))
		e = self.ecu(enable=1)
		e.preset(SPORT, 1)
		e.dispatch()
		self.assertEqual((e.mode, e.exhaust), (SPORT, 0))
		e = self.ecu(enable=0)
		e.preset(SPORT, 1)
		e.dispatch()
		self.assertEqual((e.mode, e.exhaust), (TOUR, 0))

	def test_invalid_saved_mode(self):
		e = self.ecu()
		e.preset(0x55, 0)
		e.dispatch()
		self.assertEqual(e.mode, TOUR)

if __name__ == "__main__":
	unittest.main()
