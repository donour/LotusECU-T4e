"""rev-match v1 (log only): the built machine code, run with ppcsim.py.

Two kinds of check:
 - Model: an independent Python model of the behaviour in module.toml,
   compared with the whole rev_match_log block after every tick of random
   input sequences (and random cal values).
 - Scenarios: braking and downshifting sequences played tick by tick, with
   the expected high-level outcome (fires or not, why, when it ends).

The module is built alone, on a synthetic cal that carries only the cal id,
so these tests need neither your tune nor the other modules.

	python -m unittest discover -s tests      (from custom_firmware/)
"""

import os, random, struct, sys, tempfile, unittest

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(HERE)
sys.path.insert(0, ROOT)
sys.path.insert(0, HERE)

from ppcsim import CPU
from t6patch.config import load_module, load_recipe
from t6patch.pipeline import build
from t6patch.toolchain import Toolchain

CAL_ID = b"LOTUS EVORA GT430 MAN MY19 ROW"
CAL_ID_OFF = 0x59D4                     # target [cal] id_address - base
LOG_SIZE = 68

# rev_match_log flags and reasons (module.toml).
F_BRAKE, F_HARD, F_ARMED, F_ENGAGED, F_DOWN, F_ACTIVE, F_FIRED, F_INHIBIT = (1 << i for i in range(8))
R_FIRED, R_NO_GEAR, R_LOW_GEAR, R_CEILING, R_TARGET_LOW, R_NO_RISE, R_COUPLED, R_REVLIMIT = range(1, 9)
R_CODING, R_CLUTCH_FAULT, R_ENGINE_OFF, R_COLD, R_FAULT, R_LFB, R_WHEEL_SPEED, R_LIMP, R_ESP_COMM, R_ESP_FAULT = range(16, 26)
R_END_CLUTCH, R_END_PEDAL, R_END_TIMEOUT, R_END_CEILING, R_END_RPM, R_END_TARGET_LOW, R_END_REVLIMIT = range(32, 39)

CAL_U16 = ["decel_arm", "arm_speed_min", "pedal_max", "clutch_engaged", "clutch_fire", "clutch_end",
	"ceiling_margin", "target_min", "min_rise", "decouple_drop", "max_time"]
CAL_U8 = ["enable", "arm_time", "arm_hold", "fire_delay", "gear_stable", "min_target_gear", "coolant_min",
	"gear_tol", "fire_window"]
RATIO = [1074, 581, 427, 331, 252, 224] # the default CAL_rev_match_gear_ratio

def s16(v):
	v &= 0xFFFF
	return v - 0x10000 if v & 0x8000 else v

def sat16(v): return min(v, 0xFFFF)

class Inputs:
	"""The firmware variables the module reads, with a warm, healthy, manual
	GT430 by default."""
	def __init__(self, **kw):
		self.rpm = 2000
		self.speed = 0              # car_speed_x100 (ESP vehicle speed)
		self.lr = self.rr = 0       # wheel_speeds.LR, .RR
		self.clutch = 300           # clutch_pos_voltage: engaged
		self.pedal = 0              # accel_pedal_latched
		self.bs = 0                 # brake_switch
		self.din4 = 0               # digital_input_debounced[4]: brake light switch
		self.cod0 = 0               # manual
		self.cod1 = 2 << 21         # analog clutch sensor
		self.clutch_sensor = 0
		self.tc_inhibit = 0
		self.esp_can = 0xAA         # abs_esp_can_torque_request_flags: every ESP frame alive
		self.tc_ok1 = 10            # tc_enable_condition_1 (U0122 health)
		self.tc_ok2 = 3             # tc_enable_condition_2 (U0416 health)
		self.u0122 = self.u0416 = self.u0316 = 0    # LEA_obd_ii_*_dtc_state
		self.esp_flags = 0          # abs_esp_flags
		self.mode = 0               # vehicle_mode (2 = TC off)
		self.running = 1
		self.coolant = 200          # 85 C
		self.fail = 0
		self.tps_fault = 0
		self.pedal_fault = 0
		self.pedal_degraded = 0
		self.limp = 0
		self.lfb = 0
		self.rl_hard = 7150
		self.rl_soft = 6800         # revlimit_soft_target
		self.rl_flags = 0
		for k, v in kw.items(): setattr(self, k, v)

class Model:
	"""rev-match v1 as module.toml describes it."""
	def __init__(self, cal):
		self.c = cal
		self.flags = self.reason = self.latched = self.gear_target = 0
		self.decel = self.target = self.ceiling = self.coupled = 0
		self.down = self.active_ticks = self.fire_count = 0
		self.gear_engaged = self.inhibit = self.rear = self.ratio_now = 0
		self.meas = [0] * 6
		self.div = self.idx = self.fill = self.arm_cnt = self.hold = 0
		self.cand = self.stable = self.was_engaged = 0
		self.armed = self.active = self.fired = 0
		self.limit_prev = 0
		self.ring = [0] * 8

	def tick(self, i):
		c = self.c
		if(not c["enable"] & 1):
			self.armed = self.active = self.flags = 0
			return
		flags = 0
		v, cv = i.speed, i.clutch
		pedal_off = s16(i.pedal) <= c["pedal_max"]
		brake = (i.din4 != 0 and not i.bs & 0x20) or (i.bs & 3) == 1

		# Driven wheels: speed, ratio to the engine, and the gear it matches.
		vr = (i.lr + i.rr) >> 1
		self.rear = vr
		g_now = self.ratio_now = 0
		if(vr):
			self.ratio_now = sat16(i.rpm * 1000 // vr)
			for g in range(6):
				rpm_g = c["gear_ratio"][g] * vr // 1000
				if(rpm_g and abs(i.rpm - rpm_g) * 100 <= rpm_g * c["gear_tol"]):
					g_now = g + 1
					break

		self.div += 1
		if(self.div >= 5):
			self.div = 0
			old = self.ring[self.idx]
			self.ring[self.idx] = v
			self.idx = (self.idx + 1) & 7
			if(self.fill < 8):
				self.fill += 1
				self.decel = 0
			else:
				self.decel = ((old - v) * 145) >> 10

		if((i.cod0 >> 13) & 7 != 0 or (i.cod1 >> 21) & 3 != 2): inh = R_CODING
		elif(i.clutch_sensor & 8): inh = R_CLUTCH_FAULT
		elif(i.tc_inhibit & 0xF0): inh = R_WHEEL_SPEED
		elif((i.esp_can & 0xAA) != 0xAA or not i.tc_ok1 or i.u0122 & 4): inh = R_ESP_COMM
		elif(not i.tc_ok2 or (i.u0416 | i.u0316) & 4 or (i.esp_flags & 0x10 and i.mode != 2)): inh = R_ESP_FAULT
		elif(not i.running): inh = R_ENGINE_OFF
		elif(i.coolant < c["coolant_min"]): inh = R_COLD
		elif(i.fail or i.tps_fault or i.pedal_fault or i.pedal_degraded): inh = R_FAULT
		elif(i.limp): inh = R_LIMP
		elif(i.lfb & 0x80): inh = R_LFB
		else: inh = 0
		self.inhibit = inh

		engaged = cv < c["clutch_engaged"]
		if(engaged): flags |= F_ENGAGED
		if(cv >= c["clutch_fire"]):
			flags |= F_DOWN
			self.down = min(self.down + 1, 0xFFFF)
		elif(cv < c["clutch_end"]):
			self.down = 0
			self.fired = 0

		if(engaged):
			if(not self.was_engaged): self.gear_engaged = self.cand = self.stable = 0
			if(g_now == self.cand): self.stable = min(self.stable + 1, 255)
			else: self.cand, self.stable = g_now, 0
			if(self.stable >= c["gear_stable"]):
				self.gear_engaged = g_now
				if(g_now):
					r = min(self.ratio_now, 4095) * 16
					m = self.meas[g_now - 1]
					self.meas[g_now - 1] = r if m == 0 else (m + ((r - m) >> 4)) & 0xFFFF
		elif(self.was_engaged):
			self.latched = self.gear_engaged
		self.was_engaged = int(engaged)

		hard = brake and pedal_off and v >= c["arm_speed_min"] and self.decel >= c["decel_arm"]
		if(hard): flags |= F_HARD
		if(inh):
			self.armed = self.arm_cnt = self.hold = 0
		else:
			if(hard):
				self.arm_cnt = min(self.arm_cnt + 1, 255)
				if(self.arm_cnt >= c["arm_time"]): self.armed = 1
			else:
				self.arm_cnt = 0
			if(self.armed):
				if(not pedal_off): self.armed = 0
				elif(brake): self.hold = c["arm_hold"]
				elif(self.hold): self.hold -= 1
				else: self.armed = 0

		ref = self.latched
		if(self.down == 0 and not self.active and engaged): ref = self.gear_engaged
		tg = target = coupled = 0
		if(1 <= ref <= 6):
			coupled = c["gear_ratio"][ref - 1] * vr // 1000
			tg = ref - 1
			if(tg): target = c["gear_ratio"][tg - 1] * vr // 1000
		self.gear_target = tg
		self.target, self.coupled = sat16(target), sat16(coupled)
		raw = min(i.rl_hard, i.rl_soft)
		ceiling = min(raw, self.limit_prev) - c["ceiling_margin"]
		self.limit_prev = raw
		self.ceiling = max(ceiling, 0)

		if(self.active):
			if(inh): r = inh
			elif(cv < c["clutch_end"]): r = R_END_CLUTCH
			elif(not pedal_off): r = R_END_PEDAL
			elif(self.active_ticks >= c["max_time"]): r = R_END_TIMEOUT
			elif(i.rl_flags & 1): r = R_END_REVLIMIT
			elif(target > ceiling): r = R_END_CEILING
			elif(i.rpm >= ceiling): r = R_END_RPM
			elif(target < c["target_min"]): r = R_END_TARGET_LOW
			else: r = 0
			if(r):
				self.reason = r
				self.active = 0
			else:
				self.active_ticks += 1
		elif(not self.fired and self.armed and self.down != 0
				and c["fire_delay"] <= self.down <= c["fire_delay"] + c["fire_window"]):
			if(i.rl_flags & 1): r = R_REVLIMIT
			elif(not 1 <= self.latched <= 6): r = R_NO_GEAR
			elif(self.gear_target == 0 or self.gear_target < c["min_target_gear"]): r = R_LOW_GEAR
			elif(target > ceiling): r = R_CEILING
			elif(target < c["target_min"]): r = R_TARGET_LOW
			elif(target < i.rpm + c["min_rise"]): r = R_NO_RISE
			elif(i.rpm + c["decouple_drop"] > coupled): r = R_COUPLED
			else:
				r = R_FIRED
				self.active = self.fired = 1
				self.active_ticks = 0
				self.fire_count = (self.fire_count + 1) & 0xFFFF
			self.reason = r

		if(brake): flags |= F_BRAKE
		if(self.armed): flags |= F_ARMED
		if(self.active): flags |= F_ACTIVE
		if(self.fired): flags |= F_FIRED
		if(inh): flags |= F_INHIBIT
		self.flags = flags

	def block(self):
		b = struct.pack(">BBBBhHHHHHHBBHH6H", self.flags, self.reason, self.latched, self.gear_target,
			self.decel, self.target, self.ceiling, self.coupled, self.down, self.active_ticks,
			self.fire_count, self.gear_engaged, self.inhibit, self.rear, self.ratio_now, *self.meas)
		b += bytes([self.div, self.idx, self.fill, self.arm_cnt, self.hold, self.cand, self.stable,
			self.was_engaged, self.armed, self.active, self.fired, 0])
		b += struct.pack(">HH8H", self.limit_prev, 0, *self.ring)
		assert len(b) == LOG_SIZE
		return b

class ECU:
	"""rev_match_5ms as the 200 Hz hook calls it, on the given inputs."""
	def __init__(self, res, **cal):
		self.res = res
		self.t = res.target.symbols
		self.cpu = CPU(res.elf)
		s = self.cpu.symbols
		self.log_addr = s["rev_match_log"]
		self.cal_base = s["CAL_base_extra"]
		block = res.elf.section(".data").data
		for k, b in enumerate(block): self.cpu.mem[self.cal_base + k] = b
		self.cal = self.read_cal()
		for k, v in cal.items(): self.set_cal(k, v)
		self.model = Model(self.cal)
		self.i = Inputs()

	def _off(self, name): return self.cal_base + self.cpu.symbols["OFF_CAL_rev_match_" + name]

	def read_cal(self):
		c = {k: self.cpu.rd16(self._off(k)) for k in CAL_U16}
		c.update({k: self.cpu.mem[self._off(k)] for k in CAL_U8})
		c["gear_ratio"] = [self.cpu.rd16(self._off("gear_ratio") + 2 * g) for g in range(6)]
		return c

	def set_cal(self, k, v):
		if(k == "gear_ratio"):
			for g, x in enumerate(v): self.cpu.wr16(self._off(k) + 2 * g, x)
		elif(k in CAL_U16): self.cpu.wr16(self._off(k), v)
		else: self.cpu.mem[self._off(k)] = v
		self.cal[k] = v

	def write_inputs(self, i):
		t, cpu = self.t, self.cpu
		cpu.wr16(t["engine_speed_2"], i.rpm)
		cpu.wr16(t["car_speed_x100"], i.speed)
		cpu.wr16(t["wheel_speeds"], i.lr)
		cpu.wr16(t["wheel_speeds"] + 2, i.rr)
		cpu.wr16(t["clutch_pos_voltage"], i.clutch)
		cpu.wr16(t["accel_pedal_latched"], i.pedal & 0xFFFF)
		cpu.mem[t["brake_switch"]] = i.bs
		cpu.mem[t["digital_input_debounced"] + 4] = i.din4
		cpu.wr32(t["COD_base"], i.cod0)
		cpu.wr32(t["COD_base"] + 4, i.cod1)
		cpu.mem[t["clutch_pos_sensor"]] = i.clutch_sensor
		cpu.mem[t["tc_inhibit_flags"]] = i.tc_inhibit
		cpu.wr16(t["abs_esp_can_torque_request_flags"], i.esp_can)
		cpu.mem[t["tc_enable_condition_1"]] = i.tc_ok1
		cpu.mem[t["tc_enable_condition_2"]] = i.tc_ok2
		cpu.mem[t["LEA_obd_ii_U0122_dtc_state"]] = i.u0122
		cpu.mem[t["LEA_obd_ii_U0416_dtc_state"]] = i.u0416
		cpu.mem[t["LEA_obd_ii_U0316_dtc_state"]] = i.u0316
		cpu.mem[t["abs_esp_flags"]] = i.esp_flags
		cpu.mem[t["vehicle_mode"]] = i.mode
		cpu.mem[t["engine_is_running"]] = i.running
		cpu.mem[t["coolant_temp"]] = i.coolant
		cpu.wr32(t["engine_state_failure_flags"], i.fail)
		cpu.mem[t["tps_sensor_fault_active"]] = i.tps_fault
		cpu.mem[t["accel_pedal_fault_active"]] = i.pedal_fault
		cpu.mem[t["accel_pedal_state_degraded"]] = i.pedal_degraded
		cpu.mem[t["revlimit_limp_mode_active"]] = i.limp
		cpu.mem[t["lfb_state_flags"]] = i.lfb
		cpu.wr16(t["revlimit_hard"], i.rl_hard)
		cpu.wr16(t["revlimit_soft_target"], i.rl_soft)
		cpu.wr16(t["revlimit_state_flags"], i.rl_flags)

	def tick(self, check=None, **kw):
		"""One 200 Hz tick. Inputs changed by keyword stay changed."""
		for k, v in kw.items():
			assert hasattr(self.i, k), k
			setattr(self.i, k, v)
		self.write_inputs(self.i)
		cpu = self.cpu
		before = dict(cpu.mem)
		saved = list(range(0x1000 + 13, 0x1000 + 32))
		for n in range(13, 32): cpu.r[n] = saved[n - 13]
		cpu.call("rev_match_5ms")
		if(check):
			check.assertEqual(cpu.r[1], CPU.STACK, "r1 restored")
			check.assertEqual(cpu.r[13:32], saved, "r13-r31 preserved")
			stack = range(CPU.STACK - 64, CPU.STACK)
			log = range(self.log_addr, self.log_addr + LOG_SIZE)
			changed = sorted(a for a in set(cpu.mem) | set(before)
				if cpu.mem.get(a, 0) != before.get(a, 0) and a not in stack and a not in log)
			check.assertEqual(changed, [], "writes nothing outside rev_match_log and its frame")
		self.model.tick(self.i)
		return self.log()

	def log(self): return bytes(self.cpu.mem.get(self.log_addr + k, 0) for k in range(LOG_SIZE))

	# Decoded fields.
	def u8(self, off): return self.cpu.mem.get(self.log_addr + off, 0)
	def u16(self, off): return self.cpu.rd16(self.log_addr + off)
	@property
	def flags(self): return self.u8(0)
	@property
	def reason(self): return self.u8(1)
	@property
	def latched(self): return self.u8(2)
	@property
	def gear_target(self): return self.u8(3)
	@property
	def decel(self): return s16(self.u16(4))
	@property
	def target(self): return self.u16(6)
	@property
	def ceiling(self): return self.u16(8)
	@property
	def coupled(self): return self.u16(10)
	@property
	def fire_count(self): return self.u16(16)
	@property
	def gear_engaged(self): return self.u8(18)
	@property
	def inhibit(self): return self.u8(19)
	@property
	def active(self): return bool(self.flags & F_ACTIVE)
	@property
	def armed(self): return bool(self.flags & F_ARMED)

def build_alone(work):
	"""rev-match alone on the GT430, with a synthetic cal."""
	cal = bytearray(b"\xFF" * 0x69AC)
	cal[CAL_ID_OFF:CAL_ID_OFF + 32] = CAL_ID.ljust(32)
	cal_path = os.path.join(work, "cal.cpt")
	with open(cal_path, "wb") as f: f.write(cal)
	recipe_path = os.path.join(work, "rev-match-alone.toml")
	with open(recipe_path, "w") as f:
		f.write('target = "C132E0278"\nmodules = ["rev-match"]\n')
	out = os.path.join(work, "out")
	os.makedirs(out)
	return build(Toolchain(), load_recipe(recipe_path), out, cal_path=cal_path, log=lambda s: None)

class Driver:
	"""A car for the scenarios. The vehicle speed changes with a deceleration.
	The rear wheels turn `slip` slower than the vehicle (brake slip). Engine
	rpm follows the rear wheels in the current gear while the clutch pedal is
	up (or `stuck`: the clutch stays engaged whatever the sensor says), and
	decays toward idle while it is down."""
	G = 9.80665

	def __init__(self, ecu, speed_kph, gear, check, slip=0.0):
		self.e, self.check = ecu, check
		self.v = speed_kph * 100.0
		self.gear = gear                # 0: neutral
		self.slip = slip
		self.stuck = False
		self.a = 0.0                    # g, positive slowing
		self.clutch = 300
		self.brake = False
		self.pedal = 0
		self.rpm = self.locked_rpm()

	def rear(self): return self.v * (1 - self.slip)
	def locked_rpm(self): return int(self.rear()) * RATIO[self.gear - 1] / 1000

	def step(self, n=1, **kw):
		for _ in range(n):
			self.v = max(0.0, self.v - self.a * self.G * 0.005 * 3.6 * 100)
			if((self.clutch < 450 or self.stuck) and self.gear):
				self.rpm = self.locked_rpm()
			else:
				self.rpm = max(800.0, self.rpm - 20)    # 4000 rpm/s with the clutch down
			rear = int(self.rear())
			self.e.tick(self.check, speed=int(self.v), lr=rear, rr=rear, rpm=int(self.rpm),
				clutch=self.clutch, din4=int(self.brake), pedal=self.pedal, **kw)

	def brake_hard(self, a=0.7, ticks=60):
		self.brake, self.a = True, a
		self.step(ticks)

	def shift(self, gear, clutch_down_ticks=80, engaged_ticks=60):
		"""Clutch down (through partial in 4 ticks), hold, select `gear`,
		clutch up (3 ticks), then engaged."""
		for cv in (500, 600, 700, 760):
			self.clutch = cv
			self.step()
		self.clutch = 800
		self.step(clutch_down_ticks)
		self.gear = gear
		for cv in (700, 600, 500):
			self.clutch = cv
			self.step()
		self.clutch = 300
		self.step(engaged_ticks)

class RevMatch(unittest.TestCase):
	@classmethod
	def setUpClass(cls):
		cls.work = tempfile.TemporaryDirectory()
		cls.res = build_alone(cls.work.name)

	@classmethod
	def tearDownClass(cls): cls.work.cleanup()

	def ecu(self, **cal): return ECU(self.res, **cal)

	def car(self, kph, gear, slip=0.0, **cal):
		"""A car that has been driving in `gear` for 300 ms."""
		e = self.ecu(**cal)
		d = Driver(e, kph, gear, self, slip)
		d.step(60)
		return e, d

	def assertModel(self, e):
		self.assertEqual(e.log().hex(), e.model.block().hex())

	# --- Model vs machine code ---

	def test_model_random(self):
		rng = random.Random(1)
		for seed in range(12):
			e = self.ecu()
			if(seed % 3 == 1):
				for k in CAL_U16: e.set_cal(k, rng.choice([0, rng.randrange(0, 1200), rng.randrange(0, 0x10000)]))
				for k in CAL_U8: e.set_cal(k, rng.randrange(0, 256))
				e.set_cal("enable", rng.choice([0, 1, 1, 1, 3]))
				e.set_cal("gear_ratio", [rng.randrange(0, 0x10000) for _ in range(6)])
			i = e.i
			follow = 0      # gear the engine follows (0: free)
			for n in range(4000):
				# Mostly slow random walks, with jumps and odd values now and then.
				i.speed = max(0, min(0xFFFF, i.speed + rng.randrange(-400, 300) + (rng.randrange(-30000, 30000) if rng.random() < 0.01 else 0)))
				if(rng.random() < 0.9):
					i.lr = max(0, min(0xFFFF, i.speed - rng.randrange(0, 1 + i.speed // 12)))
					i.rr = max(0, min(0xFFFF, i.lr + rng.randrange(-60, 60)))
				elif(rng.random() < 0.2):
					i.lr, i.rr = rng.choice([(0, 0), (0, i.speed), (0xFFFF, 0xFFFF), (rng.randrange(0x10000), rng.randrange(0x10000))])
				if(rng.random() < 0.01): follow = rng.randrange(0, 7)
				if(follow):
					i.rpm = min(0xFFFF, e.cal["gear_ratio"][follow - 1] * ((i.lr + i.rr) >> 1) // 1000 * rng.choice([100, 100, 100, 97, 103, 96, 104, 90]) // 100)
				else:
					i.rpm = max(0, min(0xFFFF, i.rpm + rng.randrange(-150, 150) + (rng.randrange(-5000, 5000) if rng.random() < 0.02 else 0)))
				if(rng.random() < 0.05): i.clutch = rng.choice([100, 300, 449, 450, 451, 600, 699, 700, 701, 749, 750, 751, 900, rng.randrange(0, 1024)])
				if(rng.random() < 0.03): i.pedal = rng.choice([0, 5, 20, 21, 300, 0xFFF0, rng.randrange(0, 0x10000)])
				if(rng.random() < 0.03): i.din4 = rng.randrange(2)
				if(rng.random() < 0.03): i.bs = rng.randrange(256) if rng.random() < 0.3 else rng.choice([0, 1, 2, 3, 0x20, 0x21])
				if(rng.random() < 0.005): i.cod0 = rng.choice([0, 0, 1 << 13, rng.randrange(1 << 32)])
				if(rng.random() < 0.005): i.cod1 = rng.choice([2 << 21, 2 << 21, 1 << 21, rng.randrange(1 << 32)])
				if(rng.random() < 0.005): i.clutch_sensor = rng.choice([0, 0, 8, rng.randrange(256)])
				if(rng.random() < 0.005): i.tc_inhibit = rng.choice([0, 0, 0x40, 0x80, 0x30, rng.randrange(256)])
				if(rng.random() < 0.005): i.esp_can = rng.choice([0xAA, 0xAA, 0xFF, 0xA8, 0x2A, 0xA2, 0x8A, rng.randrange(0x10000)])
				if(rng.random() < 0.005): i.tc_ok1 = rng.choice([10, 10, 1, 0])
				if(rng.random() < 0.005): i.tc_ok2 = rng.choice([3, 3, 1, 0])
				if(rng.random() < 0.005): i.u0122 = rng.choice([0, 0, 4, 0xFB, rng.randrange(256)])
				if(rng.random() < 0.005): i.u0416 = rng.choice([0, 0, 4, 0xFB, rng.randrange(256)])
				if(rng.random() < 0.005): i.u0316 = rng.choice([0, 0, 4, 0xFB, rng.randrange(256)])
				if(rng.random() < 0.005): i.esp_flags = rng.choice([0, 0, 0x10, 0x08, 0xEF, rng.randrange(256)])
				if(rng.random() < 0.005): i.mode = rng.choice([0, 1, 2, 3, 6, rng.randrange(256)])
				if(rng.random() < 0.005): i.running = rng.choice([1, 1, 0])
				if(rng.random() < 0.01): i.coolant = rng.randrange(256)
				if(rng.random() < 0.005): i.fail = rng.choice([0, 0, 0x400, 1 << 31])
				if(rng.random() < 0.005): i.tps_fault = rng.choice([0, 0, 1])
				if(rng.random() < 0.005): i.pedal_fault = rng.choice([0, 0, 1])
				if(rng.random() < 0.005): i.pedal_degraded = rng.choice([0, 0, 1])
				if(rng.random() < 0.005): i.limp = rng.choice([0, 0, 1])
				if(rng.random() < 0.005): i.lfb = rng.choice([0, 0, 0x80, rng.randrange(256)])
				if(rng.random() < 0.01): i.rl_hard = rng.choice([7150, 4000, 0, rng.randrange(0x10000)])
				if(rng.random() < 0.01): i.rl_soft = rng.choice([6800, 2300, 0, 65336, rng.randrange(0x10000)])
				if(rng.random() < 0.01): i.rl_flags = rng.choice([0, 0, 1, rng.randrange(0x10000)])
				e.tick(self if n % 97 == 0 else None)
				if(e.log() != e.model.block()):
					self.fail(f"seed {seed} tick {n}: machine code {e.log().hex()}\n"
						f"{' ' * 22}model {e.model.block().hex()}")

	def test_model_driving(self):
		"""The model check on braking and downshift sequences, with brake slip."""
		fired = 0
		for seed in range(8):
			rng = random.Random(100 + seed)
			e = self.ecu()
			d = Driver(e, rng.randrange(60, 200), rng.randrange(3, 7), None, rng.choice([0, 0.03, 0.08]))
			d.step(60)
			for _ in range(5):
				d.brake_hard(rng.choice([0.1, 0.3, 0.5, 0.9]), rng.randrange(10, 80))
				d.shift(max(1, d.gear - rng.choice([1, 1, 2])), rng.randrange(10, 120), rng.randrange(5, 80))
				self.assertModel(e)
				if(rng.random() < 0.3): d.brake, d.a = False, 0.05
			d.step(50)
			self.assertModel(e)
			fired += e.fire_count
		self.assertGreaterEqual(fired, 3, "the sequences do fire")

	# --- Scenarios ---

	def test_decel_units(self):
		e, d = self.car(120, 5)
		d.a = 1.0
		d.step(60)
		self.assertIn(e.decel, range(97, 101), "1 g")
		d.a = 0.4
		d.step(60)
		self.assertIn(e.decel, range(38, 41), "0.4 g")

	def test_arming(self):
		e, d = self.car(100, 5)
		d.a = 0.8
		d.step(60)
		self.assertFalse(e.armed, "hard deceleration without the brake")
		d.a = 0
		d.step(60)              # out of the 200 ms deceleration window
		d.brake_hard(0.2)
		self.assertFalse(e.armed, "brake with gentle deceleration")
		d.a = 0.6
		d.step(60)              # the 200 ms window passes 0.4 g, then 100 ms more
		self.assertTrue(e.armed)
		d.brake, d.a = False, 0.05
		d.step(59)
		self.assertTrue(e.armed, "held 300 ms after the brake")
		d.step(2)
		self.assertFalse(e.armed)
		d.brake_hard(0.6, 80)
		self.assertTrue(e.armed)
		d.pedal = 300
		d.step()
		self.assertFalse(e.armed, "the accelerator disarms")

	def test_arming_needs_speed(self):
		e, d = self.car(38, 3)
		d.brake_hard(0.8)
		self.assertFalse(e.armed, "below 40 km/h")

	def test_downshift_fires(self):
		e, d = self.car(110, 5)
		self.assertEqual(e.gear_engaged, 5)
		d.brake_hard()
		self.assertTrue(e.armed)
		for cv in (500, 600, 700, 760):
			d.clutch = cv
			d.step()
		self.assertEqual(e.latched, 5)
		d.clutch = 800
		d.step(28)
		self.assertFalse(e.active, "not before 150 ms clutch down")
		d.step(1)
		self.assertTrue(e.active)
		self.assertEqual((e.reason, e.gear_target, e.fire_count), (R_FIRED, 4, 1))
		self.assertEqual(e.target, int(d.v) * 331 // 1000)
		d.step(40)
		self.assertTrue(e.active, "follows the clutch, not a timer")
		self.assertEqual(e.target, int(d.v) * 331 // 1000, "target follows the speed")
		d.clutch = 690
		d.step()
		self.assertEqual((e.active, e.reason), (False, R_END_CLUTCH))

	def test_rear_slip(self):
		"""Hard braking with the rear wheels 10 % slower than the vehicle:
		the gear is still 5th (vehicle speed would read 6th), and the target
		is the rpm 4th will give at the rear wheels."""
		e, d = self.car(150, 5, slip=0.10)
		d.brake_hard(0.9)
		self.assertEqual(e.gear_engaged, 5)
		d.clutch = 800
		d.step(31)
		self.assertEqual((e.latched, e.gear_target, e.reason), (5, 4, R_FIRED))
		rear = int(d.v * 0.9)
		self.assertEqual((e.u16(20), e.target, e.coupled), (rear, rear * 331 // 1000, rear * 252 // 1000))

	def test_double_downshift(self):
		e, d = self.car(130, 5)
		d.brake_hard(0.8)
		d.shift(4, 60, 40)
		self.assertEqual((e.fire_count, e.latched, e.reason), (1, 5, R_END_CLUTCH))
		d.shift(3, 60, 10)      # 3rd engaged only 50 ms: not confirmed
		self.assertEqual((e.fire_count, e.latched), (2, 4))
		d.shift(2, 60, 40)
		self.assertEqual((e.fire_count, e.latched, e.reason), (2, 0, R_NO_GEAR))

	def test_unconfirmed_gear(self):
		"""A new engaged period too short to confirm the gear: no rev match,
		even though the gear before it was confirmed."""
		e, d = self.car(100, 4)
		d.brake_hard(0.8)
		d.clutch = 500
		d.step(3)
		d.clutch = 300
		d.step(5)
		d.clutch = 800
		d.step(60)
		self.assertEqual((e.fire_count, e.reason, e.latched), (0, R_NO_GEAR, 0))

	def test_gear_debounce(self):
		"""A mismatch shorter than gear_stable keeps the confirmed gear;
		neutral with the clutch up (longer) drops it."""
		e, d = self.car(100, 4)
		for _ in range(30):
			d.step()
			e.tick(self, rpm=int(d.rpm) + 600)  # every other sample is off
		self.assertEqual(e.gear_engaged, 4)
		d.step(25)
		d.gear = 0                          # out of gear, clutch pedal up: rpm falls away
		d.step(15)
		self.assertEqual(e.gear_engaged, 4)
		d.step(30)
		self.assertEqual(e.gear_engaged, 0)
		d.brake_hard(0.8)
		d.clutch = 800
		d.step(60)
		self.assertEqual((e.fire_count, e.reason), (0, R_NO_GEAR))

	def test_gear_tolerance(self):
		e = self.ecu()
		for pct, want in ((0, 4), (2, 4), (-2, 4), (4, 0), (-4, 0)):
			e.tick(self, lr=10000, rr=10000, rpm=3310 * (100 + pct) // 100)
			for _ in range(25): e.tick(self)
			self.assertEqual(e.gear_engaged, want, pct)
		e.tick(self, lr=9000, rr=11000, rpm=3310)
		for _ in range(25): e.tick(self)
		self.assertEqual((e.gear_engaged, e.u16(20), e.u16(22)), (4, 10000, 331), "the mean of the rear wheels")

	def test_ceiling(self):
		"""4th to 3rd at about 151 km/h is 6450 rpm: above min(7150, 6800) - 750."""
		e, d = self.car(160, 4)
		d.brake_hard(0.5)
		d.clutch = 800
		d.step(40)
		self.assertEqual((e.fire_count, e.reason, e.ceiling), (0, R_CEILING, 6050))
		self.assertGreater(e.target, 6050)

	def test_ceiling_boundary(self):
		"""At constant speed, armed on the brake alone (thresholds 0): a target
		equal to the ceiling fires, one rpm above does not; an active rev
		match ends when engine speed reaches the ceiling, not before."""
		def press(rl_hard, rpm_at_end=None):
			e = self.ecu(decel_arm=0, arm_time=0, arm_speed_min=0)
			e.tick(self, speed=10000, lr=10000, rr=10000, rpm=2520, din4=1, rl_hard=rl_hard, rl_soft=6800)
			for _ in range(25): e.tick(self)
			for _ in range(30): e.tick(self, clutch=800, rpm=1500)
			self.assertEqual(e.target, 3310)
			if(rpm_at_end is not None):
				e.tick(self, rpm=rpm_at_end - 1)
				self.assertTrue(e.active)
				e.tick(self, rpm=rpm_at_end)
			return e
		e = press(3310 + 750)
		self.assertEqual((e.ceiling, e.reason, e.active), (3310, R_FIRED, True))
		e = press(3309 + 750)
		self.assertEqual((e.reason, e.fire_count), (R_CEILING, 0))
		e = press(3310 + 750, rpm_at_end=3310)
		self.assertEqual((e.active, e.reason), (False, R_END_RPM))

	def test_ceiling_follows_limits(self):
		e, d = self.car(100, 4)
		d.step(1, rl_hard=6000, rl_soft=6000)           # cold engine
		d.brake_hard(0.5)
		d.clutch = 800
		d.step(40)
		self.assertEqual(e.ceiling, 5250)
		self.assertEqual(e.fire_count, 1, "about 3900 rpm fits under the cold limit")
		e, d = self.car(100, 4)
		d.step(1, rl_hard=4000, rl_soft=3800)           # a low limit
		d.brake_hard(0.5)
		d.clutch = 800
		d.step(40)
		self.assertEqual((e.fire_count, e.reason, e.ceiling), (0, R_CEILING, 3050))

	def test_limit_glitch(self):
		"""revlimit() stores a limit before lowering it; one tick reading the
		value in between must not raise the ceiling."""
		e, d = self.car(100, 4)
		d.step(1, rl_hard=4000, rl_soft=3800)
		d.brake_hard(0.5)
		d.clutch = 800
		d.step(35)
		self.assertEqual(e.reason, R_CEILING)
		d.step(1, rl_hard=7150, rl_soft=6800)
		self.assertEqual((e.fire_count, e.ceiling), (0, 3050))
		d.step(1, rl_hard=4000, rl_soft=3800)
		self.assertEqual((e.fire_count, e.ceiling), (0, 3050))
		d.step(2, rl_hard=7150, rl_soft=6800)           # a real change, two ticks
		self.assertEqual((e.fire_count, e.ceiling), (1, 6050))

	def test_rpm_at_ceiling_ends(self):
		e, d = self.car(110, 5)
		d.brake_hard(0.6)
		d.clutch = 800
		d.step(40)
		self.assertTrue(e.active)
		d.rpm = 6070            # 6050 after this tick's decay
		d.step()
		self.assertEqual((e.active, e.reason), (False, R_END_RPM))
		d.rpm = 3000
		d.step(20)
		self.assertEqual(e.fire_count, 1, "once per press")

	def test_low_gear(self):
		e, d = self.car(70, 2)
		d.brake_hard(0.6)
		d.clutch = 800
		d.step(40)
		self.assertEqual((e.fire_count, e.reason, e.gear_target), (0, R_LOW_GEAR, 1))
		e, d = self.car(70, 2, min_target_gear=1)
		d.brake_hard(0.6)
		d.clutch = 800
		d.step(40)
		self.assertEqual((e.fire_count, e.reason), (0, R_CEILING), "into 1st when allowed, if under the ceiling")

	def test_stuck_clutch_sensor(self):
		"""The clutch sensor reads down but the clutch is engaged: the engine
		keeps turning with the rear wheels, whatever their slip, so nothing
		fires."""
		for gear, kph in ((3, 120), (4, 130), (5, 150)):
			for slip in (0, 0.03, 0.05, 0.07, 0.10, 0.20):
				e, d = self.car(kph, gear, slip=slip)
				d.brake_hard(0.9)
				d.stuck = True
				d.clutch = 800
				d.step(150)
				self.assertEqual((e.latched, e.fire_count, e.reason), (gear, 0, R_COUPLED), (gear, slip))

	def test_no_rise(self):
		"""Engine already within min_rise of the target: no blip needed."""
		e, d = self.car(110, 5)
		d.brake_hard(0.6)
		for _ in range(60):
			d.clutch = 800
			d.step()
			d.rpm = d.v * 331 / 1000 - 80       # target - 100 after the decay
		self.assertEqual((e.fire_count, e.reason), (0, R_NO_RISE))

	def test_fire_window(self):
		"""A press can fire from fire_delay until fire_window later."""
		def press(released_at):
			"""The clutch pedal is down from tick 1, but the clutch only
			lets go at `released_at`; rpm is 200 under 12 ticks later."""
			e, d = self.car(110, 5)
			d.brake_hard(0.6)
			d.clutch = 800
			for n in range(1, 131):
				d.stuck = n < released_at
				d.step()
			return e
		self.assertEqual(press(1).fire_count, 1)
		self.assertEqual(press(75).fire_count, 1)
		e = press(85)
		self.assertEqual((e.fire_count, e.reason), (0, R_COUPLED), "past 150 + 300 ms after the pedal went down")

	def test_clutch_before_brake(self):
		"""The clutch already held down when the braking arms it: no rev
		match once the window has passed."""
		e, d = self.car(110, 5)
		d.clutch = 800
		d.step(100)
		d.brake_hard(0.8, 100)
		self.assertTrue(e.armed)
		self.assertEqual(e.fire_count, 0)

	def test_end_conditions(self):
		def fired(**cal):
			e, d = self.car(110, 5, **cal)
			d.brake_hard(0.6)
			d.clutch = 800
			d.step(31)
			self.assertTrue(e.active)
			d.a = 0.1           # target stays above target_min for the timeout case
			return e, d
		e, d = fired()
		d.pedal = 100
		d.step()
		self.assertEqual((e.active, e.reason), (False, R_END_PEDAL))
		e, d = fired()
		d.step(299)
		self.assertTrue(e.active)
		d.step(2)
		self.assertEqual((e.active, e.reason), (False, R_END_TIMEOUT))
		e, d = fired()
		d.step(rl_flags=1)
		self.assertEqual((e.active, e.reason), (False, R_END_REVLIMIT))
		e, d = fired()
		d.step(running=0)
		self.assertEqual((e.active, e.reason), (False, R_ENGINE_OFF))
		e, d = fired()
		d.step(rl_hard=3500)    # ceiling 2750, under the target
		self.assertEqual((e.active, e.reason), (False, R_END_CEILING))
		e, d = fired()
		e.tick(self, lr=0, rr=0)                        # rear wheel speeds lost (CAN timeout)
		self.assertEqual((e.active, e.reason, e.target), (False, R_END_TARGET_LOW, 0))

	def test_inhibits(self):
		cases = [(dict(cod0=1 << 13), R_CODING), (dict(cod1=1 << 21), R_CODING),
			(dict(clutch_sensor=8), R_CLUTCH_FAULT), (dict(tc_inhibit=0x40), R_WHEEL_SPEED),
			(dict(tc_inhibit=0x80), R_WHEEL_SPEED), (dict(tc_inhibit=0x10), R_WHEEL_SPEED),
			(dict(tc_inhibit=0x20), R_WHEEL_SPEED),
			(dict(esp_can=0xA8), R_ESP_COMM), (dict(esp_can=0xA2), R_ESP_COMM),
			(dict(esp_can=0x8A), R_ESP_COMM), (dict(esp_can=0x2A), R_ESP_COMM),
			(dict(tc_ok1=0), R_ESP_COMM), (dict(u0122=4), R_ESP_COMM),
			(dict(tc_ok2=0), R_ESP_FAULT), (dict(u0416=4), R_ESP_FAULT), (dict(u0316=4), R_ESP_FAULT),
			(dict(esp_flags=0x10), R_ESP_FAULT), (dict(esp_flags=0x10, mode=3), R_ESP_FAULT),
			(dict(running=0), R_ENGINE_OFF),
			(dict(coolant=175), R_COLD), (dict(fail=0x400), R_FAULT), (dict(tps_fault=1), R_FAULT),
			(dict(pedal_fault=1), R_FAULT), (dict(pedal_degraded=1), R_FAULT), (dict(limp=1), R_LIMP),
			(dict(lfb=0x80), R_LFB)]
		for kw, why in cases:
			e, d = self.car(110, 5)
			d.step(1, **kw)
			d.brake_hard()
			d.clutch = 800
			d.step(40)
			self.assertEqual((e.armed, e.fire_count, e.inhibit), (False, 0, why), kw)
		# Not faults: ESP off with TC off chosen; other ESP status bits;
		# other DTC state bits; frame-received bits missing between frames.
		for kw in (dict(esp_flags=0x10, mode=2), dict(esp_flags=0xEF), dict(u0122=0xFB, u0416=0xFB, u0316=0xFB),
				dict(esp_can=0xAA), dict(tc_ok1=1, tc_ok2=1)):
			e, d = self.car(110, 5)
			d.step(1, **kw)
			d.brake_hard()
			d.clutch = 800
			d.step(40)
			self.assertEqual((e.inhibit, e.fire_count), (0, 1), kw)

	def test_esp_fault_ends_rev_match(self):
		"""An ESP frame lost during a rev match ends it at once (RM_REASON 24)."""
		e, d = self.car(110, 5)
		d.brake_hard()
		d.clutch = 800
		d.step(40)
		self.assertTrue(e.active)
		d.step(1, esp_can=0xA8)
		self.assertEqual((e.active, e.reason, e.inhibit, e.armed), (False, R_ESP_COMM, R_ESP_COMM, False))
		d.step(5, esp_can=0xAA)
		self.assertEqual((e.active, e.fire_count), (False, 1), "no re-fire in the same press")
		self.assertModel(e)

	def test_brake_inputs(self):
		"""Switch without P0571, or the ESP bit while valid."""
		for din4, bs, want in ((1, 0, True), (1, 0x20, False), (0, 1, True), (0, 3, False),
				(0, 0x21, True), (0, 0x10, False)):
			e = self.ecu()
			e.tick(self, din4=din4, bs=bs)
			self.assertEqual(bool(e.flags & F_BRAKE), want, (din4, bs))

	def test_disabled(self):
		e, d = self.car(110, 5, enable=0)
		d.brake_hard()
		d.clutch = 800
		d.step(40)
		self.assertEqual((e.flags, e.fire_count), (0, 0))

	def test_reference_gear_during_press(self):
		"""clutch_engaged set above clutch_fire (a cal mistake) makes a held
		clutch read as engaged and down at once. The target still comes from
		the gear latched when the clutch left engaged, not from what that
		false engaged period confirms (nothing, with the engine free)."""
		e, d = self.car(100, 5, clutch_engaged=800)
		self.assertEqual(e.gear_engaged, 5)
		d.brake_hard()
		d.clutch = 850              # leaves engaged: 5th latched
		d.step(2)
		self.assertEqual(e.latched, 5)
		d.clutch = 760              # down (>= 750) and "engaged" (< 800)
		d.step(25)
		self.assertEqual(e.flags & (F_ENGAGED | F_DOWN), F_ENGAGED | F_DOWN)
		self.assertEqual((e.gear_engaged, e.latched, e.gear_target), (0, 5, 4))
		self.assertAlmostEqual(e.target, e.u16(20) * RATIO[3] // 1000, delta=1)
		d.step(15)
		self.assertEqual((e.fire_count, e.gear_target), (1, 4), "fires on the latched gear")
		self.assertModel(e)

	def test_measured_ratio(self):
		e, d = self.car(100, 4)
		d.step(400)
		self.assertAlmostEqual(e.u16(24 + 2 * 3) / 16, 331, delta=1.5)
		self.assertEqual(e.u16(24 + 2 * 2), 0, "3rd not seen")
		self.assertEqual(e.u16(22), 331, "live ratio")

	def test_no_sites(self):
		"""v1 is log only: its only hook is tick_5ms and it patches nothing."""
		m = load_module("rev-match")
		self.assertEqual((m.sites, m.cal_sites, set(m.hooks)), ([], [], {"tick_5ms"}))

if __name__ == "__main__":
	unittest.main()
