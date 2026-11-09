"""drive-mode-memory-s1: its sites on the stock S1 NA prog, and the
save/restore logic run on the built machine code with ppcsim.py, with the
firmware's ignition-off sequence played around it.

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

RECIPE = "s1-race-tc-drive-mode-memory"
SAVE_OFF = 1606 # In LEA_core_reserved
IN_SPORT, IN_TC_OFF = 3, 6
TOGGLES = (3, 6, 10, 13) # digital_input_config flags bit 1
THRESHOLD = 0x40 # CAL_ecu_ign_threshold: on at >= 256 counts
V_ON, V_OFF = 700, 100
ESP_ALIVE = 0x20

class ECU:
	"""drive_mode_memory_s1_5ms as interrupt_timer_2000hz runs it, and the
	firmware state it reads, changed in the order the main loop changes it."""

	def __init__(self, res, enable=1, esp=True):
		self.t = res.target.symbols
		self.cpu = CPU(res.elf)
		s = self.cpu.symbols
		self.cpu.mem[s["CAL_base_extra"] + s["OFF_CAL_drive_mode_memory_s1_enable"]] = enable
		self.cpu.mem[self.t["CAL_ecu_ign_threshold"]] = THRESHOLD
		self.cpu.wr16(self.t["abs_esp_can_torque_request_flags"], ESP_ALIVE if esp else 0)
		self.cpu.stubs[self.t["digital_inputs_zero"]] = self._inputs_zero
		self.save = self.t["LEA_core_reserved"] + SAVE_OFF
		self.inputs = self.t["digital_input_debounced"]

	def _inputs_zero(self, cpu):
		for i in TOGGLES: cpu.mem[self.inputs + i] = 0

	# Main loop steps (adc_sample, shutdown, read_accessory_states).
	def voltage(self, v): self.cpu.wr16(self.t["sensor_adc_ign_voltage"], v)
	def shutdown(self):
		"""The ignition parts of shutdown(), with the patched call."""
		v = self.cpu.rd16(self.t["sensor_adc_ign_voltage"])
		flags = self.cpu.rd16(self.t["ignition_on_flags"])
		if(v < THRESHOLD << 2):
			if(flags & 1): self.cpu.call("drive_mode_memory_s1_ign_off")
			self.cpu.wr16(self.t["ignition_on_flags"], flags & 0xFFEE)
		else:
			self.cpu.wr16(self.t["ignition_on_flags"], flags | 1)
	def accessory_states(self):
		v = self.cpu.rd16(self.t["sensor_adc_ign_voltage"])
		self.cpu.mem[self.t["ign_voltage_above_threshold"]] = int(v >= THRESHOLD << 2)

	def tick(self):
		"""200 Hz: the handler, then (as at 100 Hz) the input zeroing of
		set_driver_input_and_vehicle_mode_100hz."""
		self.cpu.call("drive_mode_memory_s1_5ms")
		if(not self.cpu.mem.get(self.t["ign_voltage_above_threshold"], 0)):
			self.cpu.mem[self.inputs + IN_SPORT] = self.cpu.mem[self.inputs + IN_TC_OFF] = 0

	def ignition(self, on, ticks=2):
		"""One main loop pass with the new voltage, then some ticks."""
		self.voltage(V_ON if on else V_OFF)
		self.shutdown()
		self.accessory_states()
		for _ in range(ticks): self.tick()

	def get(self, i): return self.cpu.mem.get(self.inputs + i, 0)
	def set(self, i, v): self.cpu.mem[self.inputs + i] = v
	def esp(self, alive): self.cpu.wr16(self.t["abs_esp_can_torque_request_flags"], ESP_ALIVE if alive else 0)
	def saved(self): return (self.cpu.mem.get(self.save, 0), self.cpu.mem.get(self.save + 1, 0))
	def preset(self, sport, tc_off):
		self.cpu.mem[self.save], self.cpu.mem[self.save + 1] = sport, tc_off

class DriveModeMemoryS1(unittest.TestCase):
	@classmethod
	def setUpClass(cls):
		r = load_recipe(RECIPE)
		if(r.cal and not os.path.exists(r.cal)): raise unittest.SkipTest(f"no input cal for {RECIPE}")
		with tempfile.TemporaryDirectory() as work:
			cls.res = build(Toolchain(), r, work, log=lambda s: None)

	def ecu(self, **kw): return ECU(self.res, **kw)

	def test_sites(self):
		t, prog = self.res.target.symbols, self.res.prog
		self.assertEqual(prog.read(t["eeprom_load_reserved_clear_limit"], 4), bytes.fromhex("28000646")) # cmplwi r0,1606
		ins = int.from_bytes(prog.read(t["shutdown_ign_off_inputs_zero"], 4), "big")
		self.assertEqual((ins >> 26, ins & 3), (18, 1)) # bl
		li = ins & 0x03FFFFFC
		if(li & 0x02000000): li -= 0x04000000
		self.assertEqual(t["shutdown_ign_off_inputs_zero"] + li, self.res.elf.symbol("drive_mode_memory_s1_ign_off").value)

	def test_sport_restored_and_saved(self):
		e = self.ecu()
		e.preset(1, 0)
		e.ignition(True)
		self.assertEqual(e.get(IN_SPORT), 1)
		e.set(IN_SPORT, 0) # driver presses Sport: Tour
		e.tick()
		self.assertEqual(e.saved(), (0, 0))

	def test_nothing_before_main_loop(self):
		e = self.ecu()
		e.preset(1, 0)
		for _ in range(5): e.tick() # boot: ISR running, ignition_on_flags not set yet
		self.assertEqual((e.get(IN_SPORT), e.saved()), (0, (1, 0)))

	def test_key_cycle_without_reboot(self):
		e = self.ecu()
		e.ignition(True)
		e.set(IN_SPORT, 1)
		e.tick()
		e.ignition(False)
		self.assertEqual(e.get(IN_SPORT), 0, "the firmware zeroes it")
		self.assertEqual(e.saved(), (1, 0))
		e.ignition(True)
		self.assertEqual(e.get(IN_SPORT), 1)

	def test_off_between_main_loop_steps(self):
		"""A tick at each point of the key-off pass: the zeros are never saved,
		and nothing is written back to the inputs."""
		flags = self.res.target.symbols["ignition_on_flags"]
		for at in range(3):
			e = self.ecu()
			e.ignition(True)
			e.set(IN_SPORT, 1)
			e.tick()
			e.voltage(V_OFF) # adc_sample
			if(at == 0): e.tick()
			e.cpu.call("drive_mode_memory_s1_ign_off") # shutdown(): inputs zeroed...
			if(at == 1): e.tick()
			e.cpu.wr16(flags, e.cpu.rd16(flags) & 0xFFEE) # ... then bit 0 cleared
			if(at == 2): e.tick()
			self.assertEqual(e.get(IN_SPORT), 0, f"tick at step {at}")
			e.accessory_states()
			e.tick()
			self.assertEqual(e.saved(), (1, 0), f"tick at step {at}")
			e.ignition(True)
			self.assertEqual(e.get(IN_SPORT), 1, f"tick at step {at}")

	def test_on_before_accessory_states(self):
		"""Key on: ticks after shutdown() has set bit 0 but before
		read_accessory_states has set ign_voltage_above_threshold, while the
		100 Hz code still zeroes the inputs."""
		e = self.ecu()
		e.preset(1, 0)
		e.voltage(V_ON)
		e.shutdown()
		for _ in range(3): e.tick()
		self.assertEqual(e.saved(), (1, 0))
		e.accessory_states()
		e.tick()
		self.assertEqual(e.get(IN_SPORT), 1)

	def test_dip_between_ticks(self):
		"""The ignition voltage drops and comes back within two main loop
		passes and no tick: the shutdown site still rearms the restore."""
		e = self.ecu()
		e.ignition(True)
		e.set(IN_SPORT, 1)
		e.tick()
		e.ignition(False, ticks=0)
		e.ignition(True, ticks=0)
		self.assertEqual(e.get(IN_SPORT), 0)
		e.tick()
		self.assertEqual((e.get(IN_SPORT), e.saved()), (1, (1, 0)))

	def test_tc_off_saved_not_restored_by_default(self):
		e = self.ecu()
		e.preset(1, 1)
		e.ignition(True)
		self.assertEqual((e.get(IN_SPORT), e.get(IN_TC_OFF)), (1, 0))
		self.assertEqual(e.saved(), (1, 0), "TC off is still saved")
		e.set(IN_TC_OFF, 1)
		e.tick()
		self.assertEqual(e.saved(), (1, 1))

	def test_tc_off_waits_for_esp(self):
		e = self.ecu(enable=3, esp=False)
		e.preset(0, 1)
		e.ignition(True, ticks=5)
		self.assertEqual(e.get(IN_TC_OFF), 0)
		e.set(IN_SPORT, 1) # Sport is saved meanwhile
		e.tick()
		self.assertEqual(e.saved(), (1, 1), "TC off not saved while waiting")
		e.esp(True)
		e.tick()
		self.assertEqual((e.get(IN_SPORT), e.get(IN_TC_OFF)), (1, 1))
		e.set(IN_TC_OFF, 0)
		e.tick()
		self.assertEqual(e.saved(), (1, 0))

	def test_press_before_restore_kept(self):
		e = self.ecu()
		e.preset(0, 0)
		e.voltage(V_ON); e.shutdown(); e.accessory_states() # no 100 Hz zeroing from here
		e.set(IN_SPORT, 1)
		e.tick()
		self.assertEqual(e.get(IN_SPORT), 1)

	def test_enable_bits(self):
		for enable, want in ((0, (0, 0)), (1, (1, 0)), (2, (0, 1)), (3, (1, 1))):
			e = self.ecu(enable=enable)
			e.preset(1, 1)
			e.ignition(True)
			self.assertEqual((e.get(IN_SPORT), e.get(IN_TC_OFF)), want, f"enable {enable}")

	def test_invalid_saved_value(self):
		e = self.ecu(enable=3)
		e.preset(0x55, 0x55)
		e.ignition(True)
		self.assertEqual((e.get(IN_SPORT), e.get(IN_TC_OFF)), (0, 0))
		self.assertEqual(e.saved(), (0, 0))

if __name__ == "__main__":
	unittest.main()
