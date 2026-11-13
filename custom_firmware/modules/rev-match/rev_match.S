# rev-match v1: decide when a rev-matched downshift would fire, and log it.
# Log only: nothing here writes a firmware variable. See module.toml.

# rev_match_log: the published part (offsets 0-35) is fixed, for logging.
.set RM_FLAGS, 0            # u8  F_* below
.set RM_REASON, 1           # u8  last fire check / end result, R_* below
.set RM_GEAR_LATCHED, 2     # u8  gear confirmed before the clutch left engaged
.set RM_GEAR_TARGET, 3      # u8  reference gear - 1 (0: none)
.set RM_DECEL, 4            # s16 deceleration, 0.01 g (from car_speed_x100 over 200 ms)
.set RM_TARGET, 6           # u16 rpm in the target gear at the current speed
.set RM_CEILING, 8          # u16 rpm limit for a rev match (0 if negative)
.set RM_COUPLED, 10         # u16 rpm in the reference gear at the current speed
.set RM_DOWN_TICKS, 12      # u16 5 ms ticks the clutch has been down this press
.set RM_ACTIVE_TICKS, 14    # u16 5 ms ticks of the current (or last) rev match
.set RM_FIRE_COUNT, 16      # u16
.set RM_GEAR_ENGAGED, 18    # u8  gear confirmed in the current engaged period (0: none)
.set RM_INHIBIT, 19         # u8  R_* inhibit, 0 if none
.set RM_REAR_SPEED, 20      # u16 driven-wheel speed, (LR + RR) / 2, 0.01 km/h
.set RM_RATIO_NOW, 22       # u16 engine rpm per driven-wheel km/h, x10 (0: wheels stopped)
.set RM_RATIO_MEAS, 24      # u16[6] measured rpm per km/h x160, per gear
# Internal.
.set RM_DIV, 36             # u8  decel sample divider
.set RM_RING_IDX, 37        # u8
.set RM_RING_FILL, 38       # u8  samples written, up to 8
.set RM_ARM_CNT, 39         # u8  ticks of hard braking
.set RM_HOLD, 40            # u8  ticks left armed without the brake
.set RM_GEAR_CAND, 41       # u8  gear matched now (0: none), being debounced
.set RM_GEAR_STABLE, 42     # u8  ticks RM_GEAR_CAND has held
.set RM_WAS_ENGAGED, 43     # u8
.set RM_ARMED, 44           # u8
.set RM_ACTIVE, 45          # u8
.set RM_FIRED, 46           # u8  fired during this clutch press
.set RM_LIMIT_PREV, 48      # u16 min(revlimit_hard, revlimit_soft_target) of the last tick
.set RM_RING, 52            # u16[8] car_speed_x100 every 25 ms
.set RM_SIZE, 68

.set F_BRAKE, 0x01
.set F_HARD, 0x02
.set F_ARMED, 0x04
.set F_ENGAGED, 0x08
.set F_DOWN, 0x10
.set F_ACTIVE, 0x20
.set F_FIRED, 0x40
.set F_INHIBIT, 0x80

.set R_FIRED, 1
.set R_NO_GEAR, 2
.set R_LOW_GEAR, 3
.set R_CEILING, 4
.set R_TARGET_LOW, 5
.set R_NO_RISE, 6
.set R_COUPLED, 7
.set R_REVLIMIT, 8
.set R_CODING, 16
.set R_CLUTCH_FAULT, 17
.set R_ENGINE_OFF, 18
.set R_COLD, 19
.set R_FAULT, 20
.set R_LFB, 21
.set R_WHEEL_SPEED, 22
.set R_LIMP, 23
.set R_ESP_COMM, 24
.set R_ESP_FAULT, 25
.set R_END_CLUTCH, 32
.set R_END_PEDAL, 33
.set R_END_TIMEOUT, 34
.set R_END_CEILING, 35
.set R_END_RPM, 36
.set R_END_TARGET_LOW, 37
.set R_END_REVLIMIT, 38

.set EN_RUN, 0x01
.set DECEL_DIV, 5           # ticks per speed sample (25 ms); 8 samples = 200 ms
.set BRAKE_INPUT, 4         # digital_input_debounced index: brake light switch
.set VM_TC_OFF, 2           # vehicle_mode

# \rd = \rs, at most 0xFFFF.
.macro SAT16 rd, rs
	mr	\rd, \rs
	cmplwi	\rd, 0xFFFF
	ble	9f
	li	\rd, -1
	clrlwi	\rd, \rd, 16
9:
.endm

.section .bss
	.balign 4
	.global rev_match_log
rev_match_log:
	.skip RM_SIZE

.section .text
.global rev_match_5ms

# 200 Hz (tick_5ms). Registers kept across the sections:
#  r31 rev_match_log      r30 CAL_base_extra      r29 log flags being built
#  r28 inhibit (R_*, 0)   r27 engine rpm          r26 car_speed_x100
#  r25 clutch voltage     r24 pedal released      r23 brake on
#  r22 target rpm         r21 ceiling (signed)    r20 coupled rpm
#  r19 driven-wheel speed r18 gear matched now (0: none)
rev_match_5ms:
	stwu	%r1, -64(%r1)
	stmw	%r18, 8(%r1)
	lis	%r31, rev_match_log@ha
	addi	%r31, %r31, rev_match_log@l
	lis	%r30, CAL_base_extra@ha
	addi	%r30, %r30, CAL_base_extra@l

	lbz	%r0, OFF_CAL_rev_match_enable(%r30)
	andi.	%r0, %r0, EN_RUN
	bne	.Lrun
	li	%r0, 0                              # disabled: nothing armed or active
	stb	%r0, RM_ARMED(%r31)
	stb	%r0, RM_ACTIVE(%r31)
	stb	%r0, RM_FLAGS(%r31)
	b	.Lexit

.Lrun:
	li	%r29, 0
	lis	%r3, engine_speed_2@ha
	lhz	%r27, engine_speed_2@l(%r3)
	lis	%r3, car_speed_x100@ha
	lhz	%r26, car_speed_x100@l(%r3)
	lis	%r3, clutch_pos_voltage@ha
	lhz	%r25, clutch_pos_voltage@l(%r3)

	# Driven-wheel speed: the mean of the rear wheels, which is what the
	# engine turns with while the clutch is engaged, whatever the brake slip.
	# The ratio to engine speed is logged, and matched against each gear:
	# within CAL_rev_match_gear_tol percent of speed * ratio[g], lowest first.
	lis	%r3, wheel_speeds@ha
	addi	%r3, %r3, wheel_speeds@l
	lhz	%r19, 0(%r3)                        # LR
	lhz	%r0, 2(%r3)                         # RR
	add	%r19, %r19, %r0
	srwi	%r19, %r19, 1
	sth	%r19, RM_REAR_SPEED(%r31)
	li	%r18, 0
	li	%r4, 0
	cmpwi	%r19, 0
	beq	.Lmatch_done
	li	%r9, 1000
	mullw	%r4, %r27, %r9
	divwu	%r4, %r4, %r19
	SAT16	%r4, %r4
	lbz	%r10, OFF_CAL_rev_match_gear_tol(%r30)
	li	%r5, 0
.Lmatch_loop:
	slwi	%r6, %r5, 1
	addi	%r6, %r6, OFF_CAL_rev_match_gear_ratio
	lhzx	%r6, %r30, %r6
	mullw	%r6, %r6, %r19
	divwu	%r6, %r6, %r9                       # rpm in this gear
	cmpwi	%r6, 0
	beq	.Lmatch_next
	subf	%r7, %r6, %r27
	cmpwi	%r7, 0
	bge	1f
	subf	%r7, %r27, %r6
1:	mulli	%r7, %r7, 100
	mullw	%r8, %r6, %r10
	cmplw	%r7, %r8
	bgt	.Lmatch_next
	addi	%r18, %r5, 1
	b	.Lmatch_done
.Lmatch_next:
	addi	%r5, %r5, 1
	cmpwi	%r5, 6
	blt	.Lmatch_loop
.Lmatch_done:
	sth	%r4, RM_RATIO_NOW(%r31)

	# Pedal released: accel_pedal_latched <= CAL_rev_match_pedal_max.
	lis	%r3, accel_pedal_latched@ha
	lha	%r3, accel_pedal_latched@l(%r3)
	lhz	%r0, OFF_CAL_rev_match_pedal_max(%r30)
	li	%r24, 0
	cmpw	%r3, %r0
	bgt	1f
	li	%r24, 1
1:

	# Brake on, as left_foot_brake reads it: the switch (no P0571 fault), or
	# the ESP's brake bit (bit 0) while valid (bit 1 clear).
	li	%r23, 0
	lis	%r3, brake_switch@ha
	lbz	%r4, brake_switch@l(%r3)
	lis	%r3, digital_input_debounced@ha
	addi	%r3, %r3, digital_input_debounced@l
	lbz	%r0, BRAKE_INPUT(%r3)
	cmpwi	%r0, 0
	beq	2f
	andi.	%r0, %r4, 0x20
	bne	2f
	li	%r23, 1
	b	3f
2:	andi.	%r0, %r4, 3
	cmpwi	%r0, 1
	bne	3f
	li	%r23, 1
3:

	# Deceleration: a car_speed_x100 sample every 25 ms in an 8-slot ring;
	# decel = (speed 200 ms ago - speed now) * 145 >> 10, in 0.01 g
	# (0.01 km/h per 200 ms = 1/706.1 g). 0 until the ring is full.
	lbz	%r3, RM_DIV(%r31)
	addi	%r3, %r3, 1
	cmpwi	%r3, DECEL_DIV
	blt	.Ldiv_store
	li	%r3, 0
	lbz	%r4, RM_RING_IDX(%r31)
	slwi	%r5, %r4, 1
	addi	%r5, %r5, RM_RING
	lhzx	%r6, %r31, %r5                      # sample from 200 ms ago
	sthx	%r26, %r31, %r5
	addi	%r4, %r4, 1
	andi.	%r4, %r4, 7
	stb	%r4, RM_RING_IDX(%r31)
	lbz	%r4, RM_RING_FILL(%r31)
	li	%r7, 0
	cmpwi	%r4, 8
	bge	4f
	addi	%r4, %r4, 1
	stb	%r4, RM_RING_FILL(%r31)
	b	5f
4:	subf	%r7, %r26, %r6                      # old - new
	mulli	%r7, %r7, 145
	srawi	%r7, %r7, 10
5:	sth	%r7, RM_DECEL(%r31)
.Ldiv_store:
	stb	%r3, RM_DIV(%r31)

	# Inhibits, first one found.
	li	%r28, 0
	lis	%r3, COD_base@ha
	addi	%r3, %r3, COD_base@l
	lwz	%r4, 0(%r3)                         # COD[0]
	rlwinm	%r0, %r4, 32-13, 29, 31             # transmission: 0 manual
	cmpwi	%r0, 0
	bne	.Linh_coding
	lwz	%r4, 4(%r3)                         # COD[1]
	rlwinm	%r0, %r4, 32-21, 30, 31             # clutch sensor: 2 analog
	cmpwi	%r0, 2
	bne	.Linh_coding
	lis	%r3, clutch_pos_sensor@ha
	lbz	%r0, clutch_pos_sensor@l(%r3)
	andi.	%r0, %r0, 8                         # P0806/P0807/high voltage fault
	bne	.Linh_clutch
	lis	%r3, tc_inhibit_flags@ha
	lbz	%r0, tc_inhibit_flags@l(%r3)
	andi.	%r0, %r0, 0xF0                      # a wheel speed is invalid (ABS sensor)
	bne	.Linh_wheel
	# ABS/ESP communication: every ESP frame alive (front 0xA2, rear 0xA4,
	# status 0xA8, torque 0xB7: bits 0x02/0x08/0x20/0x80, each dropped within
	# 50-100 ms of its frame going missing), the debounced U0122 health
	# the firmware's own traction control needs, and no active U0122.
	lis	%r3, abs_esp_can_torque_request_flags@ha
	lhz	%r0, abs_esp_can_torque_request_flags@l(%r3)
	andi.	%r0, %r0, 0xAA
	cmpwi	%r0, 0xAA
	bne	.Linh_esp_comm
	lis	%r3, tc_enable_condition_1@ha
	lbz	%r0, tc_enable_condition_1@l(%r3)
	cmpwi	%r0, 0
	beq	.Linh_esp_comm
	lis	%r3, LEA_obd_ii_U0122_dtc_state@ha
	lbz	%r0, LEA_obd_ii_U0122_dtc_state@l(%r3)
	andi.	%r0, %r0, 4
	bne	.Linh_esp_comm
	# ABS/ESP fault: the debounced U0416 health (ESP status consistent with
	# the drive mode), no active U0416/U0316, and the ESP not reporting
	# itself off (abs_esp_flags 0x10) unless the driver chose TC off.
	lis	%r3, tc_enable_condition_2@ha
	lbz	%r0, tc_enable_condition_2@l(%r3)
	cmpwi	%r0, 0
	beq	.Linh_esp_fault
	lis	%r3, LEA_obd_ii_U0416_dtc_state@ha
	lbz	%r0, LEA_obd_ii_U0416_dtc_state@l(%r3)
	lis	%r3, LEA_obd_ii_U0316_dtc_state@ha
	lbz	%r4, LEA_obd_ii_U0316_dtc_state@l(%r3)
	or	%r0, %r0, %r4
	andi.	%r0, %r0, 4
	bne	.Linh_esp_fault
	lis	%r3, abs_esp_flags@ha
	lbz	%r0, abs_esp_flags@l(%r3)
	andi.	%r0, %r0, 0x10
	beq	1f
	lis	%r3, vehicle_mode@ha
	lbz	%r0, vehicle_mode@l(%r3)
	cmpwi	%r0, VM_TC_OFF
	bne	.Linh_esp_fault
1:	lis	%r3, engine_is_running@ha
	lbz	%r0, engine_is_running@l(%r3)
	cmpwi	%r0, 0
	beq	.Linh_engine
	lis	%r3, coolant_temp@ha
	lbz	%r0, coolant_temp@l(%r3)
	lbz	%r4, OFF_CAL_rev_match_coolant_min(%r30)
	cmplw	%r0, %r4
	blt	.Linh_cold
	lis	%r3, engine_state_failure_flags@ha
	lwz	%r0, engine_state_failure_flags@l(%r3)
	cmpwi	%r0, 0
	bne	.Linh_fault
	lis	%r3, tps_sensor_fault_active@ha
	lbz	%r0, tps_sensor_fault_active@l(%r3)
	cmpwi	%r0, 0
	bne	.Linh_fault
	lis	%r3, accel_pedal_fault_active@ha
	lbz	%r0, accel_pedal_fault_active@l(%r3)
	cmpwi	%r0, 0
	bne	.Linh_fault
	lis	%r3, accel_pedal_state_degraded@ha
	lbz	%r0, accel_pedal_state_degraded@l(%r3)
	cmpwi	%r0, 0
	bne	.Linh_fault
	lis	%r3, revlimit_limp_mode_active@ha
	lbz	%r0, revlimit_limp_mode_active@l(%r3)
	cmpwi	%r0, 0
	bne	.Linh_limp
	lis	%r3, lfb_state_flags@ha
	lbz	%r0, lfb_state_flags@l(%r3)
	andi.	%r0, %r0, 0x80                      # left-foot-brake throttle cut active
	bne	.Linh_lfb
	b	.Linh_done
.Linh_wheel:
	li	%r28, R_WHEEL_SPEED
	b	.Linh_done
.Linh_limp:
	li	%r28, R_LIMP
	b	.Linh_done
.Linh_esp_comm:
	li	%r28, R_ESP_COMM
	b	.Linh_done
.Linh_esp_fault:
	li	%r28, R_ESP_FAULT
	b	.Linh_done
.Linh_coding:
	li	%r28, R_CODING
	b	.Linh_done
.Linh_clutch:
	li	%r28, R_CLUTCH_FAULT
	b	.Linh_done
.Linh_engine:
	li	%r28, R_ENGINE_OFF
	b	.Linh_done
.Linh_cold:
	li	%r28, R_COLD
	b	.Linh_done
.Linh_fault:
	li	%r28, R_FAULT
	b	.Linh_done
.Linh_lfb:
	li	%r28, R_LFB
.Linh_done:
	stb	%r28, RM_INHIBIT(%r31)

	# Clutch. Engaged below CAL_rev_match_clutch_engaged. A press: down_ticks
	# counts while at or above CAL_rev_match_clutch_fire, holds between that
	# and CAL_rev_match_clutch_end, and the press ends below that.
	lhz	%r0, OFF_CAL_rev_match_clutch_engaged(%r30)
	cmplw	%r25, %r0
	bge	1f
	ori	%r29, %r29, F_ENGAGED
1:	lhz	%r3, RM_DOWN_TICKS(%r31)
	lhz	%r0, OFF_CAL_rev_match_clutch_fire(%r30)
	cmplw	%r25, %r0
	blt	2f
	ori	%r29, %r29, F_DOWN
	cmplwi	%r3, 0xFFFF
	beq	3f
	addi	%r3, %r3, 1
	b	3f
2:	lhz	%r0, OFF_CAL_rev_match_clutch_end(%r30)
	cmplw	%r25, %r0
	bge	3f
	li	%r3, 0                              # press over
	li	%r0, 0
	stb	%r0, RM_FIRED(%r31)
3:	sth	%r3, RM_DOWN_TICKS(%r31)

	# Gear. While engaged, the matched gear (or none) that has held for
	# CAL_rev_match_gear_stable ticks becomes the confirmed gear of this
	# engaged period, so a short mismatch does not drop it and neutral does.
	# When the clutch leaves engaged, the confirmed gear (0 if none) is latched.
	andi.	%r0, %r29, F_ENGAGED
	beq	.Lnot_engaged
	lbz	%r0, RM_WAS_ENGAGED(%r31)
	cmpwi	%r0, 0
	bne	1f
	li	%r0, 0                              # a new engaged period
	stb	%r0, RM_GEAR_ENGAGED(%r31)
	stb	%r0, RM_GEAR_CAND(%r31)
	stb	%r0, RM_GEAR_STABLE(%r31)
1:	lbz	%r5, RM_GEAR_CAND(%r31)
	lbz	%r6, RM_GEAR_STABLE(%r31)
	cmpw	%r18, %r5
	beq	2f
	stb	%r18, RM_GEAR_CAND(%r31)
	li	%r6, 0
	b	3f
2:	cmpwi	%r6, 255
	beq	3f
	addi	%r6, %r6, 1
3:	stb	%r6, RM_GEAR_STABLE(%r31)
	lbz	%r0, OFF_CAL_rev_match_gear_stable(%r30)
	cmplw	%r6, %r0
	blt	.Lgear_done
	stb	%r18, RM_GEAR_ENGAGED(%r31)
	cmpwi	%r18, 0
	beq	.Lgear_done
	# Measured ratio, x16 fixed point: m += (ratio_now*16 - m) >> 4.
	lhz	%r5, RM_RATIO_NOW(%r31)
	cmplwi	%r5, 4095
	ble	4f
	li	%r5, 4095
4:	slwi	%r5, %r5, 4
	slwi	%r7, %r18, 1
	addi	%r7, %r7, RM_RATIO_MEAS - 2
	lhzx	%r8, %r31, %r7
	cmpwi	%r8, 0
	beq	5f                                  # first sample
	subf	%r9, %r8, %r5
	srawi	%r9, %r9, 4
	add	%r5, %r8, %r9
5:	sthx	%r5, %r31, %r7
	b	.Lgear_done
.Lnot_engaged:
	lbz	%r0, RM_WAS_ENGAGED(%r31)
	cmpwi	%r0, 0
	beq	.Lgear_done
	lbz	%r0, RM_GEAR_ENGAGED(%r31)
	stb	%r0, RM_GEAR_LATCHED(%r31)
.Lgear_done:
	rlwinm	%r0, %r29, 32-3, 31, 31             # F_ENGAGED -> 0/1
	stb	%r0, RM_WAS_ENGAGED(%r31)

	# Arming: brake on, pedal released, fast enough and decelerating at
	# CAL_rev_match_decel_arm or more, for CAL_rev_match_arm_time ticks. Stays
	# armed while the brake is on and CAL_rev_match_arm_hold ticks after;
	# disarmed by the pedal or any inhibit.
	cmpwi	%r23, 0
	beq	1f
	cmpwi	%r24, 0
	beq	1f
	lhz	%r0, OFF_CAL_rev_match_arm_speed_min(%r30)
	cmplw	%r26, %r0
	blt	1f
	lha	%r3, RM_DECEL(%r31)
	lhz	%r0, OFF_CAL_rev_match_decel_arm(%r30)
	cmpw	%r3, %r0
	blt	1f
	ori	%r29, %r29, F_HARD
1:	cmpwi	%r28, 0
	beq	2f
	li	%r0, 0
	stb	%r0, RM_ARMED(%r31)
	stb	%r0, RM_ARM_CNT(%r31)
	stb	%r0, RM_HOLD(%r31)
	b	.Larm_done
2:	lbz	%r3, RM_ARM_CNT(%r31)
	andi.	%r0, %r29, F_HARD
	bne	3f
	li	%r3, 0
	b	4f
3:	cmpwi	%r3, 255
	beq	5f
	addi	%r3, %r3, 1
5:	lbz	%r0, OFF_CAL_rev_match_arm_time(%r30)
	cmplw	%r3, %r0
	blt	4f
	li	%r0, 1
	stb	%r0, RM_ARMED(%r31)
4:	stb	%r3, RM_ARM_CNT(%r31)
	lbz	%r0, RM_ARMED(%r31)
	cmpwi	%r0, 0
	beq	.Larm_done
	cmpwi	%r24, 0
	beq	.Ldisarm
	cmpwi	%r23, 0
	beq	6f
	lbz	%r0, OFF_CAL_rev_match_arm_hold(%r30)
	stb	%r0, RM_HOLD(%r31)
	b	.Larm_done
6:	lbz	%r3, RM_HOLD(%r31)
	cmpwi	%r3, 0
	beq	.Ldisarm
	addi	%r3, %r3, -1
	stb	%r3, RM_HOLD(%r31)
	b	.Larm_done
.Ldisarm:
	li	%r0, 0
	stb	%r0, RM_ARMED(%r31)
.Larm_done:

	# Reference gear: the latched gear during a press or a rev match; else
	# the confirmed gear while engaged, the latched one otherwise.
	# coupled = wheel speed * ratio[ref], target = wheel speed * ratio[ref - 1].
	lbz	%r4, RM_GEAR_LATCHED(%r31)
	lhz	%r0, RM_DOWN_TICKS(%r31)
	cmpwi	%r0, 0
	bne	2f
	lbz	%r0, RM_ACTIVE(%r31)
	cmpwi	%r0, 0
	bne	2f
	andi.	%r0, %r29, F_ENGAGED
	beq	2f
	lbz	%r4, RM_GEAR_ENGAGED(%r31)
2:	li	%r5, 0
	li	%r22, 0
	li	%r20, 0
	addi	%r0, %r4, -1
	cmplwi	%r0, 5
	bgt	3f
	li	%r10, 1000
	slwi	%r8, %r0, 1
	addi	%r8, %r8, OFF_CAL_rev_match_gear_ratio
	lhzx	%r9, %r30, %r8
	mullw	%r9, %r9, %r19
	divwu	%r20, %r9, %r10
	addi	%r5, %r4, -1
	cmpwi	%r5, 0
	beq	3f
	addi	%r8, %r8, -2
	lhzx	%r9, %r30, %r8
	mullw	%r9, %r9, %r19
	divwu	%r22, %r9, %r10
3:	stb	%r5, RM_GEAR_TARGET(%r31)
	SAT16	%r3, %r22
	sth	%r3, RM_TARGET(%r31)
	SAT16	%r3, %r20
	sth	%r3, RM_COUPLED(%r31)

	# Ceiling: min(revlimit_hard, revlimit_soft_target) - margin, signed. The
	# lower of this tick's and the last tick's limits is used: revlimit()
	# (main loop) stores each limit before lowering it for limp mode or the
	# speed limiter, and this interrupt can land between those stores.
	lis	%r3, revlimit_hard@ha
	lhz	%r21, revlimit_hard@l(%r3)
	lis	%r3, revlimit_soft_target@ha
	lhz	%r0, revlimit_soft_target@l(%r3)
	cmplw	%r0, %r21
	bge	1f
	mr	%r21, %r0
1:	lhz	%r0, RM_LIMIT_PREV(%r31)
	sth	%r21, RM_LIMIT_PREV(%r31)
	cmplw	%r0, %r21
	bge	1f
	mr	%r21, %r0
1:	lhz	%r0, OFF_CAL_rev_match_ceiling_margin(%r30)
	subf	%r21, %r0, %r21
	mr	%r3, %r21
	cmpwi	%r3, 0
	bge	2f
	li	%r3, 0
2:	sth	%r3, RM_CEILING(%r31)

	# Active: end on the first condition found.
	lbz	%r0, RM_ACTIVE(%r31)
	cmpwi	%r0, 0
	beq	.Lnot_active
	mr.	%r3, %r28
	bne	.Lend
	lhz	%r0, OFF_CAL_rev_match_clutch_end(%r30)
	li	%r3, R_END_CLUTCH
	cmplw	%r25, %r0
	blt	.Lend
	li	%r3, R_END_PEDAL
	cmpwi	%r24, 0
	beq	.Lend
	lhz	%r4, RM_ACTIVE_TICKS(%r31)
	lhz	%r0, OFF_CAL_rev_match_max_time(%r30)
	li	%r3, R_END_TIMEOUT
	cmplw	%r4, %r0
	bge	.Lend
	lis	%r5, revlimit_state_flags@ha
	lhz	%r0, revlimit_state_flags@l(%r5)
	andi.	%r0, %r0, 1                         # airflow limiter active
	li	%r3, R_END_REVLIMIT
	bne	.Lend
	li	%r3, R_END_CEILING
	cmpw	%r22, %r21
	bgt	.Lend
	li	%r3, R_END_RPM
	cmpw	%r27, %r21
	bge	.Lend
	lhz	%r0, OFF_CAL_rev_match_target_min(%r30)
	li	%r3, R_END_TARGET_LOW
	cmplw	%r22, %r0
	blt	.Lend
	addi	%r4, %r4, 1
	sth	%r4, RM_ACTIVE_TICKS(%r31)
	b	.Lfire_done
.Lend:
	stb	%r3, RM_REASON(%r31)
	li	%r0, 0
	stb	%r0, RM_ACTIVE(%r31)
	b	.Lfire_done

	# Not active: fire once per press, when armed and the clutch has been down
	# CAL_rev_match_fire_delay ticks (at least 1). Retried every tick for
	# CAL_rev_match_fire_window ticks more; RM_REASON says why not. After the
	# window, nothing fires on this press.
.Lnot_active:
	lbz	%r0, RM_FIRED(%r31)
	cmpwi	%r0, 0
	bne	.Lfire_done
	lbz	%r0, RM_ARMED(%r31)
	cmpwi	%r0, 0
	beq	.Lfire_done
	lhz	%r4, RM_DOWN_TICKS(%r31)
	cmpwi	%r4, 0
	beq	.Lfire_done
	lbz	%r0, OFF_CAL_rev_match_fire_delay(%r30)
	cmplw	%r4, %r0
	blt	.Lfire_done
	lbz	%r5, OFF_CAL_rev_match_fire_window(%r30)
	add	%r0, %r0, %r5
	cmplw	%r4, %r0
	bgt	.Lfire_done
	lis	%r5, revlimit_state_flags@ha
	lhz	%r0, revlimit_state_flags@l(%r5)
	andi.	%r0, %r0, 1
	li	%r3, R_REVLIMIT
	bne	.Lskip
	lbz	%r4, RM_GEAR_LATCHED(%r31)
	addi	%r0, %r4, -1
	li	%r3, R_NO_GEAR
	cmplwi	%r0, 5
	bgt	.Lskip
	lbz	%r5, RM_GEAR_TARGET(%r31)           # latched - 1 during a press
	lbz	%r0, OFF_CAL_rev_match_min_target_gear(%r30)
	li	%r3, R_LOW_GEAR
	cmpwi	%r5, 0
	beq	.Lskip
	cmplw	%r5, %r0
	blt	.Lskip
	li	%r3, R_CEILING
	cmpw	%r22, %r21
	bgt	.Lskip
	lhz	%r0, OFF_CAL_rev_match_target_min(%r30)
	li	%r3, R_TARGET_LOW
	cmplw	%r22, %r0
	blt	.Lskip
	lhz	%r0, OFF_CAL_rev_match_min_rise(%r30)
	add	%r0, %r0, %r27
	li	%r3, R_NO_RISE
	cmplw	%r22, %r0
	blt	.Lskip
	lhz	%r0, OFF_CAL_rev_match_decouple_drop(%r30)
	add	%r0, %r0, %r27
	li	%r3, R_COUPLED
	cmplw	%r0, %r20                           # rpm + drop > coupled: still coupled
	bgt	.Lskip
	li	%r0, 1
	stb	%r0, RM_ACTIVE(%r31)
	stb	%r0, RM_FIRED(%r31)
	li	%r0, 0
	sth	%r0, RM_ACTIVE_TICKS(%r31)
	lhz	%r3, RM_FIRE_COUNT(%r31)
	addi	%r3, %r3, 1
	sth	%r3, RM_FIRE_COUNT(%r31)
	li	%r3, R_FIRED
.Lskip:
	stb	%r3, RM_REASON(%r31)
.Lfire_done:

	# Log flags.
	cmpwi	%r23, 0
	beq	1f
	ori	%r29, %r29, F_BRAKE
1:	lbz	%r0, RM_ARMED(%r31)
	cmpwi	%r0, 0
	beq	2f
	ori	%r29, %r29, F_ARMED
2:	lbz	%r0, RM_ACTIVE(%r31)
	cmpwi	%r0, 0
	beq	3f
	ori	%r29, %r29, F_ACTIVE
3:	lbz	%r0, RM_FIRED(%r31)
	cmpwi	%r0, 0
	beq	4f
	ori	%r29, %r29, F_FIRED
4:	cmpwi	%r28, 0
	beq	5f
	ori	%r29, %r29, F_INHIBIT
5:	stb	%r29, RM_FLAGS(%r31)

.Lexit:
	lmw	%r18, 8(%r1)
	addi	%r1, %r1, 64
	blr
