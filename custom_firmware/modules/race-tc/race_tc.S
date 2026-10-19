#TODO: OBD-II data reading is incorrect and forces reboot
#TODO: tune the i term from race TC correction in state mgmt
#TODO: move the CAL tables out of the data segment

# race-tc: race traction control, 9-level slip-based torque cut.
# Built from the GT430's (C132E0278) slip control, which the GT430 firmware
# calls DPM (dpm_* symbols there), ported to B13200091 (S1 Evora NA).
# Variable set follows C132E0278/DPM_plan.md Phase 1.

# Constants
.set RACE_TC_SLIP_TARGET_STRAIGHT_LINE_OFFSET, 16 # 2% in 1/8% units, skipped while cornering
.set RACE_TC_MAX_LEVEL,         9 # Button cycles 0 (off), 1..9, 0

.set RACE_TC_TORQUE_NO_LIMIT,   911 # Nm sentinel = "no torque cut requested"

# race_tc_control_flags bitmap
.set RACE_TC_FLAG_ARMED,        0x0001 # In operating window (armed); set even below threshold
.set RACE_TC_FLAG_CUTTING,      0x0002 # Actively cutting torque (snapshot taken on its rising edge)
.set RACE_TC_FLAG_DIRECT,       0x0004 # Direct mode active (high L-R speed diff)
.set RACE_TC_FLAG_SLIP_VALID,   0x0008 # Slip calculation valid
.set RACE_TC_FLAG_SYS_ENABLED,  0x0010 # race TC system enabled
.set RACE_TC_FLAG_SYS_DISABLED, 0x0020 # System disabled (fault/inhibit)
.set RACE_TC_FLAG_BUTTONS,      0x0040 # Button processing enabled
.set RACE_TC_FLAG_BTN_INC,      0x0080 # Increase button pressed
.set RACE_TC_FLAG_BTN_DEC,      0x0100 # Decrease button pressed

.section .data

# race TC runtime state.
#
# These are defined as explicit .bss labels rather than .comm. On PowerPC
# EABI the assembler diverts small .comm objects (<= the -G small-data
# threshold, default 8 bytes) into .sbss. The combined Makefile only sets
# -Tbss $(RAM) and never places .sbss, so those symbols would link at VMA 0
# (showing up as uRam0000xxxx in the disassembly) instead of the 0x4000xxxx
# SRAM block. Explicit .bss placement avoids the diversion and also gives a
# deterministic layout for the later OBD readback patch.
#
# Ordered widest-first (4/2/1 byte) so every field stays naturally aligned
# with no padding.
.section .bss
.balign 4
.global race_tc_slip, race_tc_slip_target
.global race_tc_slip_error_raw, race_tc_slip_error_filtered
.global race_tc_slip_filter_accumulator, race_tc_slip_integral_accumulator
.global race_tc_torque_limit_spark, race_tc_torque_limit_throttle
.global race_tc_torque_when_tc_activated
.global race_tc_torque_cut_p_term, race_tc_torque_cut_i_term, race_tc_torque_cut_fraction
.global race_tc_mode_index, race_tc_control_flags
.global race_tc_front_axle_speed_max, race_tc_rear_axle_speed_max
.global race_tc_vehicle_speed_kph
.global race_tc_front_lr_speed_diff, race_tc_rear_lr_speed_diff, race_tc_max_lr_speed_diff
.global race_tc_cornering_detect_timer, race_tc_cornering_release_timer
.global race_tc_integral_update_timer
.global race_tc_increase_hold_time
.global race_tc_both_buttons_pressed

# 32-bit
race_tc_slip_filter_accumulator:   .skip 4 # u32, slip error filter state memory
race_tc_slip_integral_accumulator: .skip 2 # i16, integral controller state (signed, 8.8 fixed-ish)

# 16-bit
race_tc_slip:                      .skip 2 # u16_slip_1/8%, current wheel slip
race_tc_slip_target:               .skip 2 # u16_slip_1/8%, target slip setpoint
race_tc_slip_error_raw:            .skip 2 # u16_slip_1/8%, slip - target (when slip > target)
race_tc_slip_error_filtered:       .skip 2 # u16_slip_1/8%, filtered error (fast attack, slow decay)
race_tc_torque_limit_spark:        .skip 2 # u16_torque_nm, race TC target -> spark/fast channel (deep cut)
race_tc_torque_limit_throttle:     .skip 2 # u16_torque_nm, throttle/slow ceiling (spark + recovery margin)
race_tc_torque_when_tc_activated:  .skip 2 # u16_torque_nm, torque snapshot at intervention start
race_tc_control_flags:             .skip 2 # RACE_TC_FLAG_* bitmap
race_tc_front_axle_speed_max:      .skip 2 # u16_speed_1/100kph, max(LF, RF)
race_tc_rear_axle_speed_max:       .skip 2 # u16_speed_1/100kph, max(LR, RR)
race_tc_front_lr_speed_diff:       .skip 2 # u16_speed_1/100kph, abs(LF - RF)
race_tc_rear_lr_speed_diff:        .skip 2 # u16_speed_1/100kph, abs(LR - RR)
race_tc_max_lr_speed_diff:         .skip 2 # u16_speed_1/100kph, max of front/rear L-R diffs
race_tc_cornering_detect_timer:    .skip 2 # u16_time_5ms, countdown to enter direct mode
race_tc_cornering_release_timer:   .skip 2 # u16_time_5ms, countdown to exit direct mode
race_tc_integral_update_timer:     .skip 2 # u16_time_5ms, integral update period countdown

# 8-bit
race_tc_mode_index:                .skip 1 # 0 = off, 1-RACE_TC_MAX_LEVEL = race TC level
race_tc_vehicle_speed_kph:         .skip 1 # u8_speed_kph, front axle max / 100
race_tc_torque_cut_p_term:         .skip 1 # u8_factor_1/255, proportional cut from lookup
race_tc_torque_cut_i_term:         .skip 1 # u8_factor_1/255, integral torque cut term
race_tc_torque_cut_fraction:       .skip 1 # u8_factor_1/255, p_term + i_term (sat. 255)
race_tc_increase_hold_time:        .skip 1 # u8, 5ms counts increase held
race_tc_both_buttons_pressed:      .skip 1 # bool, dual-press latch

.section .text
.global race_tc_init, race_tc_slip_calculator, race_tc_system_state_manager_200hz

# The firmware does not zero-fill the patch .bss region, so every
# variable must be initialized explicitly here.
race_tc_init:
	# Push link register on stack
	stwu	%r1, -8(%r1)
	mflr	%r0
	stw	%r0, 12(%r1)

	# Torque limits start at the "no limit" sentinel
	li	%r3, RACE_TC_TORQUE_NO_LIMIT
	lis	%r4, race_tc_torque_limit_spark@ha
	sth	%r3, race_tc_torque_limit_spark@l(%r4)
	lis	%r4, race_tc_torque_limit_throttle@ha
	sth	%r3, race_tc_torque_limit_throttle@l(%r4)

	# Everything else starts at 0.
	# In particular race_tc_mode_index = 0: race TC stays OFF until the
	# driver explicitly enables it.
	li	%r3, 0

	# 32-bit state
	lis	%r4, race_tc_slip_filter_accumulator@ha
	stw	%r3, race_tc_slip_filter_accumulator@l(%r4)
	lis	%r4, race_tc_slip_integral_accumulator@ha
	sth	%r3, race_tc_slip_integral_accumulator@l(%r4)

	# 16-bit state
	lis	%r4, race_tc_slip@ha
	sth	%r3, race_tc_slip@l(%r4)
	lis	%r4, race_tc_slip_target@ha
	sth	%r3, race_tc_slip_target@l(%r4)
	lis	%r4, race_tc_slip_error_raw@ha
	sth	%r3, race_tc_slip_error_raw@l(%r4)
	lis	%r4, race_tc_slip_error_filtered@ha
	sth	%r3, race_tc_slip_error_filtered@l(%r4)
	lis	%r4, race_tc_torque_when_tc_activated@ha
	sth	%r3, race_tc_torque_when_tc_activated@l(%r4)
	lis	%r4, race_tc_control_flags@ha
	sth	%r3, race_tc_control_flags@l(%r4)
	lis	%r4, race_tc_front_axle_speed_max@ha
	sth	%r3, race_tc_front_axle_speed_max@l(%r4)
	lis	%r4, race_tc_rear_axle_speed_max@ha
	sth	%r3, race_tc_rear_axle_speed_max@l(%r4)
	lis	%r4, race_tc_front_lr_speed_diff@ha
	sth	%r3, race_tc_front_lr_speed_diff@l(%r4)
	lis	%r4, race_tc_rear_lr_speed_diff@ha
	sth	%r3, race_tc_rear_lr_speed_diff@l(%r4)
	lis	%r4, race_tc_max_lr_speed_diff@ha
	sth	%r3, race_tc_max_lr_speed_diff@l(%r4)
	lis	%r4, race_tc_cornering_detect_timer@ha
	sth	%r3, race_tc_cornering_detect_timer@l(%r4)
	lis	%r4, race_tc_cornering_release_timer@ha
	sth	%r3, race_tc_cornering_release_timer@l(%r4)
	lis	%r4, race_tc_integral_update_timer@ha
	sth	%r3, race_tc_integral_update_timer@l(%r4)

	# 8-bit state
	lis	%r4, race_tc_mode_index@ha
	stb	%r3, race_tc_mode_index@l(%r4)
	lis	%r4, race_tc_vehicle_speed_kph@ha
	stb	%r3, race_tc_vehicle_speed_kph@l(%r4)
	lis	%r4, race_tc_torque_cut_p_term@ha
	stb	%r3, race_tc_torque_cut_p_term@l(%r4)
	lis	%r4, race_tc_torque_cut_i_term@ha
	stb	%r3, race_tc_torque_cut_i_term@l(%r4)
	lis	%r4, race_tc_torque_cut_fraction@ha
	stb	%r3, race_tc_torque_cut_fraction@l(%r4)
	lis	%r4, race_tc_increase_hold_time@ha
	stb	%r3, race_tc_increase_hold_time@l(%r4)
	lis	%r4, race_tc_both_buttons_pressed@ha
	stb	%r3, race_tc_both_buttons_pressed@l(%r4)

	# Pop link register from stack
	lwz	%r0, 12(%r1)
	mtlr	%r0
	addi	%r1, %r1, 8
	blr


# Subfunction of race_tc_slip_calculator.
# Reads the firmware wheel_speed struct (halfwords, REARS FIRST:
# LR@0, RR@2, LF@4, RF@6; u16_speed_1/100kph) and updates:
#   race_tc_front_axle_speed_max = max(LF, RF)
#   race_tc_rear_axle_speed_max  = max(LR, RR)
#   race_tc_vehicle_speed_kph    = min(front_max / 100, 255)
#   race_tc_front_lr_speed_diff  = abs(LF - RF)
#   race_tc_rear_lr_speed_diff   = abs(LR - RR)
#   race_tc_max_lr_speed_diff    = max(front_lr_diff, rear_lr_diff)
#   race_tc_slip                 = rear-over-front overspeed, 1/8% units
#   race_tc_slip_target          = per-level target (via race_tc_calc_slip_target)
# Clobbers r0, r3-r11; calls race_tc_calc_slip_target.
race_tc_calc_slip:
	# Push link register (this function now calls race_tc_calc_slip_target).
	stwu	%r1, -8(%r1)
	mflr	%r0
	stw	%r0, 12(%r1)

	# Load the four wheel speeds.
	lis	%r3, wheel_speed@ha
	addi	%r3, %r3, wheel_speed@l
	lhz	%r6, 0(%r3)	# LR
	lhz	%r7, 2(%r3)	# RR
	lhz	%r4, 4(%r3)	# LF
	lhz	%r5, 6(%r3)	# RF

	# race_tc_front_axle_speed_max = max(LF, RF)
	mr	%r8, %r4
	cmplw	%r8, %r5
	bge	slip_1
	mr	%r8, %r5
slip_1:
	lis	%r10, race_tc_front_axle_speed_max@ha
	sth	%r8, race_tc_front_axle_speed_max@l(%r10)

	# race_tc_rear_axle_speed_max = max(LR, RR)
	mr	%r9, %r6
	cmplw	%r9, %r7
	bge	slip_2
	mr	%r9, %r7
slip_2:
	lis	%r10, race_tc_rear_axle_speed_max@ha
	sth	%r9, race_tc_rear_axle_speed_max@l(%r10)

	# race_tc_vehicle_speed_kph = min(front_max / 100, 255)
	li	%r10, 100
	divwu	%r0, %r8, %r10
	cmplwi	%r0, 255
	ble	slip_3
	li	%r0, 255
slip_3:
	lis	%r10, race_tc_vehicle_speed_kph@ha
	stb	%r0, race_tc_vehicle_speed_kph@l(%r10)

	# race_tc_front_lr_speed_diff = abs(LF - RF)
	# Branchless abs: m = x >> 31; abs = (x ^ m) - m
	subf	%r0, %r5, %r4	# r0 = LF - RF
	srawi	%r10, %r0, 31
	xor	%r0, %r0, %r10
	subf	%r11, %r10, %r0	# r11 = abs(LF - RF), kept for the max below
	lis	%r10, race_tc_front_lr_speed_diff@ha
	sth	%r11, race_tc_front_lr_speed_diff@l(%r10)

	# race_tc_rear_lr_speed_diff = abs(LR - RR)
	subf	%r0, %r7, %r6	# r0 = LR - RR
	srawi	%r10, %r0, 31
	xor	%r0, %r0, %r10
	subf	%r0, %r10, %r0	# r0 = abs(LR - RR)
	lis	%r10, race_tc_rear_lr_speed_diff@ha
	sth	%r0, race_tc_rear_lr_speed_diff@l(%r10)

	# race_tc_max_lr_speed_diff = max(front_lr_diff, rear_lr_diff)
	# Cornering magnitude; the direct-mode hysteresis will consume this later.
	cmplw	%r11, %r0	# front (r11) vs rear (r0), unsigned
	bge	slip_4
	mr	%r11, %r0	# rear larger -> r11 = max
slip_4:
	lis	%r10, race_tc_max_lr_speed_diff@ha
	sth	%r11, race_tc_max_lr_speed_diff@l(%r10)

	# race_tc_slip = (front_max > 0 && rear_max > front_max)
	#            ? min((rear_max * 800) / front_max - 800, 0xFFFF)
	#            : 0
	# 800 = 100% in 1/8% units; ratio, so independent of speed scale.
	# Accumulate in r3, not r0: subi/addi encode rA=r0 as the literal 0
	# rather than the register, so `subi %r0,%r0,800` would compute 0-800.
	li	%r3, 0
	cmplwi	%r8, 0
	beq	slip_5
	cmplw	%r9, %r8
	ble	slip_5
	mulli	%r3, %r9, 800	# max 65535*800 = 52.4M, fits in 32 bits
	divwu	%r3, %r3, %r8
	subi	%r3, %r3, 800	# >= 0 because rear_max > front_max
	cmplwi	%r3, 0xFFFF
	ble	slip_5
	li	%r3, -1		# 0xFFFF after the halfword store
slip_5:
	lis	%r10, race_tc_slip@ha
	sth	%r3, race_tc_slip@l(%r10)

	# Compute the slip target that race_tc_slip is judged against.
	bl	race_tc_calc_slip_target

	# Pop link register.
	lwz	%r0, 12(%r1)
	mtlr	%r0
	addi	%r1, %r1, 8
	blr

# Compute race_tc_slip_target: the slip threshold race_tc_slip is judged against.
# Ported from C132E0278.c:58274-58327 (the "system enabled" active path).
#
#   pedal_comp = lookup_3D(6,6, vehicle_speed_kph, (pedal>>2)&0xff,
#                          CAL_race_tc_slip_target_from_pedal, _X_carspeed, _Y_pps)
#   base       = lookup_2D(16, race_tc_mode_index,
#                          CAL_racetc_slip_target_base, _X_dpm_level)
#   comp       = base + pedal_comp*16
#   target     = min(comp + (direct_mode ? 0 : RACE_TC_SLIP_TARGET_STRAIGHT_LINE_OFFSET), 0xFFFF)
#
# In direct mode (RACE_TC_FLAG_DIRECT, set by the 5 ms state manager on sustained
# cornering) the offset is skipped, tightening the target through corners.
#
# Simplifications versus the GT430 (racecar build):
#   - the enable gating (SYS_ENABLED/SYS_DISABLED) is dropped; the target is
#     ALWAYS computed. The dead pedal-only branch (BUTTONS clear) is omitted.
#   - race_tc_mode_index 0 = race TC off: target = 0xFFFF so race_tc_slip can never
#     exceed it. This is the level selector, not an enable flag, so it stays.
# The slip-target base table and its level axis, and the torque-cut P-term
# table and its axes, are stock-cal locations (CAL_racetc_*, tunable in the
# cal file); the other CAL_race_tc_* values still live in static .text tables
# below.
# Non-leaf: calls firmware lookups. Clobbers r0, r3-r9.
race_tc_calc_slip_target:
	# Push link register (this function calls the firmware lookups).
	stwu	%r1, -8(%r1)
	mflr	%r0
	stw	%r0, 12(%r1)

	# race TC off (mode 0): target = 0xFFFF, skip the lookups.
	lis	%r3, race_tc_mode_index@ha
	lbz	%r3, race_tc_mode_index@l(%r3)
	cmplwi	%r3, 0
	bne	tgt_on
	li	%r4, -1			# 0xFFFF after the halfword store
	lis	%r5, race_tc_slip_target@ha
	sth	%r4, race_tc_slip_target@l(%r5)
	b	tgt_done
tgt_on:
	# pedal_comp = lookup_3D_uint8_interpolated(6, 6, speed, pedal, ...)
	li	%r3, 6			# size_x
	li	%r4, 6			# size_y
	lis	%r5, race_tc_vehicle_speed_kph@ha
	lbz	%r5, race_tc_vehicle_speed_kph@l(%r5)	# input_x = speed (kph)
	lis	%r6, accel_pedal_latched@ha
	lha	%r6, accel_pedal_latched@l(%r6)
	srawi	%r6, %r6, 2
	clrlwi	%r6, %r6, 24		# input_y = (pedal>>2)&0xff
	lis	%r7, CAL_race_tc_slip_target_from_pedal@ha
	addi	%r7, %r7, CAL_race_tc_slip_target_from_pedal@l
	lis	%r8, CAL_race_tc_slip_target_from_pedal_X_carspeed@ha
	addi	%r8, %r8, CAL_race_tc_slip_target_from_pedal_X_carspeed@l
	lis	%r9, CAL_race_tc_slip_target_from_pedal_Y_pps@ha
	addi	%r9, %r9, CAL_race_tc_slip_target_from_pedal_Y_pps@l
	bl	lookup_3D_uint8_interpolated

	# Stash the pedal contribution (pedal_comp << 4: 2% -> 1/8% units) in the
	# target slot. Memory survives the next call, so no callee-saved register
	# is needed to carry it across the base lookup.
	slwi	%r3, %r3, 4
	lis	%r4, race_tc_slip_target@ha
	sth	%r3, race_tc_slip_target@l(%r4)

	# base = lookup_2D_uint8_interpolated(16, race_tc_mode_index, ...)
	li	%r3, 16			# size_x
	lis	%r4, race_tc_mode_index@ha
	lbz	%r4, race_tc_mode_index@l(%r4)	# input_x = level
	lis	%r5, CAL_racetc_slip_target_base@ha		# stock-cal location (RAM copy)
	addi	%r5, %r5, CAL_racetc_slip_target_base@l
	lis	%r6, CAL_racetc_slip_target_base_X_dpm_level@ha
	addi	%r6, %r6, CAL_racetc_slip_target_base_X_dpm_level@l
	bl	lookup_2D_uint8_interpolated

	# comp = base + pedal_contrib  (base in r3 from lookup_2D)
	lis	%r4, race_tc_slip_target@ha
	lhz	%r5, race_tc_slip_target@l(%r4)	# pedal contribution stashed above
	add	%r3, %r3, %r5

	# Add the offset unless direct mode is active. In direct mode (cornering)
	# the offset is skipped to tighten the target (C132E0278.c:58317-58327).
	lis	%r6, race_tc_control_flags@ha
	lhz	%r6, race_tc_control_flags@l(%r6)
	andi.	%r6, %r6, RACE_TC_FLAG_DIRECT
	bne	tgt_clamp			# direct mode -> no offset
	addi	%r3, %r3, RACE_TC_SLIP_TARGET_STRAIGHT_LINE_OFFSET
tgt_clamp:
	cmplwi	%r3, 0xFFFF
	ble	tgt_store
	li	%r3, -1			# clamp to 0xFFFF
tgt_store:
	sth	%r3, race_tc_slip_target@l(%r4)
tgt_done:
	# Pop link register.
	lwz	%r0, 12(%r1)
	mtlr	%r0
	addi	%r1, %r1, 8
	blr

# Subfunction of race_tc_slip_calculator. Derives the slip error and its
# asymmetric (fast-attack / slow-decay) filter from race_tc_slip and
# race_tc_slip_target. Ported from C132E0278.c:58328-58349.
#   race_tc_slip_error_raw = (slip > target) ? slip - target : 0
#   coeff = lookup_2D(8, vehicle_speed_kph,
#                     CAL_race_tc_slip_filter_coeff, _X_carspeed)   # gain, /256
#   raw > filtered (rising)  -> instant attack:
#         filtered = raw;  accumulator = raw << 8
#   raw < filtered (falling) -> slow decay (exponential low-pass):
#         accumulator = ((256-coeff)*accumulator >> 8) + coeff*raw
#         filtered    = accumulator >> 8
#   raw == filtered          -> unchanged
# accumulator is 8.8 fixed point (filtered << 8). All values are non-negative,
# so the GT430 signed-rounding corrections are no-ops and unsigned arithmetic
# is exact (products stay within 32 bits across the full u16 error range).
# Non-leaf: calls lookup_2D. Clobbers r0, r3-r9.
race_tc_calc_slip_error:
	stwu	%r1, -8(%r1)
	mflr	%r0
	stw	%r0, 12(%r1)

	# race_tc_slip_error_raw = (slip > target) ? slip - target : 0
	lis	%r3, race_tc_slip@ha
	lhz	%r3, race_tc_slip@l(%r3)
	lis	%r4, race_tc_slip_target@ha
	lhz	%r4, race_tc_slip_target@l(%r4)
	li	%r5, 0
	cmplw	%r3, %r4		# slip vs target, unsigned
	ble	serr_store_raw		# slip <= target -> raw = 0
	subf	%r5, %r4, %r3		# raw = slip - target
serr_store_raw:
	lis	%r6, race_tc_slip_error_raw@ha
	sth	%r5, race_tc_slip_error_raw@l(%r6)

	# coeff = lookup_2D_uint8_interpolated(8, vehicle_speed_kph, tbl, axis)
	li	%r3, 8
	lis	%r4, race_tc_vehicle_speed_kph@ha
	lbz	%r4, race_tc_vehicle_speed_kph@l(%r4)	# input_x = speed (kph)
	lis	%r5, CAL_race_tc_slip_filter_coeff@ha
	addi	%r5, %r5, CAL_race_tc_slip_filter_coeff@l
	lis	%r6, CAL_race_tc_slip_filter_coeff_X_carspeed@ha
	addi	%r6, %r6, CAL_race_tc_slip_filter_coeff_X_carspeed@l
	bl	lookup_2D_uint8_interpolated	# r3 = coeff (clobbers volatiles)

	# Reload raw (r4) and the previous filtered (r5); coeff stays in r3.
	lis	%r4, race_tc_slip_error_raw@ha
	lhz	%r4, race_tc_slip_error_raw@l(%r4)
	lis	%r5, race_tc_slip_error_filtered@ha
	lhz	%r5, race_tc_slip_error_filtered@l(%r5)

	cmplw	%r4, %r5
	beq	serr_done		# raw == filtered -> unchanged
	blt	serr_decay		# raw < filtered  -> slow decay

	# --- instant attack (raw > filtered) ---
	lis	%r6, race_tc_slip_error_filtered@ha
	sth	%r4, race_tc_slip_error_filtered@l(%r6)
	slwi	%r7, %r4, 8			# accumulator = raw << 8
	lis	%r6, race_tc_slip_filter_accumulator@ha
	stw	%r7, race_tc_slip_filter_accumulator@l(%r6)
	b	serr_done

serr_decay:
	# accumulator = ((256-coeff)*accumulator >> 8) + coeff*raw
	lis	%r6, race_tc_slip_filter_accumulator@ha
	lwz	%r7, race_tc_slip_filter_accumulator@l(%r6)
	subfic	%r8, %r3, 256		# 256 - coeff
	mullw	%r8, %r8, %r7		# (256-coeff) * accumulator
	srwi	%r8, %r8, 8
	mullw	%r9, %r3, %r4		# coeff * raw
	add	%r8, %r8, %r9		# new accumulator
	stw	%r8, race_tc_slip_filter_accumulator@l(%r6)
	srwi	%r8, %r8, 8		# filtered = accumulator >> 8
	lis	%r6, race_tc_slip_error_filtered@ha
	sth	%r8, race_tc_slip_error_filtered@l(%r6)
serr_done:
	lwz	%r0, 12(%r1)
	mtlr	%r0
	addi	%r1, %r1, 8
	blr

# Subfunction of race_tc_slip_calculator: the torque-cut / intervention block.
# Port of C132E0278.c:58442-58500. Produces race_tc_torque_limit_spark/throttle,
# race_tc_torque_cut_p_term/fraction and the ARMED/CUTTING flags. While CUTTING,
# race_tc_torque_arbitration_filter (race_tc_hooks.S) applies the limits as
# min() on the firmware's external torque request and sets the ABS source bit,
# so torque_model turns them into spark retard, cylinder cut and a throttle cap.
#
# Gate (all must hold, else full reset to the 911 sentinel):
#   race_tc_mode_index != 0                               (replaces vehicle_mode==VM_DPM_ACTIVE)
#   CAL_race_tc_min_vehicle_speed < vehicle_speed_kph < CAL_race_tc_max_vehicle_speed
#   CAL_race_tc_min_engine_rpm < engine_speed_16bit
#   (inj_flags & 1) == 0                              (fuel cut inactive)
#   (race_tc_control_flags & RACE_TC_FLAG_SYS_DISABLED) == 0  (set by the later ABS gate)
# The GT430 SLIP_VALID (bit 3) gate is dropped: mode 0 already forces
# target=0xFFFF -> error 0, and the mode!=0 gate covers "valid".
#
# In window, if intervention_threshold < error_filtered -> CUTTING:
#   snapshot torque on the CUTTING rising edge, set ARMED|CUTTING,
#   p_term   = lookup_3D_uint32(6,10, front_axle_speed_max, error_filtered, ...),
#   fraction = min(p_term + i_term, 255),
#   spark    = max(snapshot - snapshot*fraction/255, CAL_race_tc_torque_min_allowed),
#   throttle = spark   (GT430 adds a CAL_dpm_torque_margin_factor recovery
#                       margin, absent on the NA -> margin dropped for now).
# i_term comes from the integral controller in race_tc_system_state_manager_200hz.
# Non-leaf: calls lookup_3D_uint32 + race_tc_torque_reset_outputs. Clobbers r0,r3-r9.
race_tc_calc_torque_cut:
	stwu	%r1, -8(%r1)
	mflr	%r0
	stw	%r0, 12(%r1)

	# --- gate ---
	lis	%r3, race_tc_mode_index@ha
	lbz	%r3, race_tc_mode_index@l(%r3)
	cmplwi	%r3, 0
	beq	tc_out_of_window		# race TC off

	lis	%r3, race_tc_vehicle_speed_kph@ha
	lbz	%r3, race_tc_vehicle_speed_kph@l(%r3)	# r3 = speed (kept)
	lis	%r4, CAL_race_tc_max_vehicle_speed@ha
	lbz	%r4, CAL_race_tc_max_vehicle_speed@l(%r4)
	cmplw	%r3, %r4
	bge	tc_out_of_window		# speed >= max
	lis	%r4, CAL_race_tc_min_vehicle_speed@ha
	lbz	%r4, CAL_race_tc_min_vehicle_speed@l(%r4)
	cmplw	%r3, %r4
	ble	tc_out_of_window		# speed <= min

	lis	%r3, engine_speed_16bit@ha
	lhz	%r3, engine_speed_16bit@l(%r3)
	lis	%r4, CAL_race_tc_min_engine_rpm@ha
	lhz	%r4, CAL_race_tc_min_engine_rpm@l(%r4)
	cmplw	%r3, %r4
	ble	tc_out_of_window		# engine_speed <= min_rpm

	lis	%r3, inj_flags@ha
	lhz	%r3, inj_flags@l(%r3)
	andi.	%r3, %r3, 1
	bne	tc_out_of_window		# fuel cut active

	lis	%r5, race_tc_control_flags@ha
	lhz	%r6, race_tc_control_flags@l(%r5)	# r6 = flags, r5 = base (both kept)
	andi.	%r3, %r6, RACE_TC_FLAG_SYS_DISABLED
	bne	tc_out_of_window

	# --- in window: intervention threshold ---
	lis	%r3, race_tc_slip_error_filtered@ha
	lhz	%r3, race_tc_slip_error_filtered@l(%r3)
	lis	%r4, CAL_race_tc_intervention_threshold@ha
	lbz	%r4, CAL_race_tc_intervention_threshold@l(%r4)
	cmplw	%r3, %r4
	ble	tc_below_threshold		# error <= threshold: armed, no cut

	# --- cutting ---
	# snapshot torque on the CUTTING rising edge
	andi.	%r3, %r6, RACE_TC_FLAG_CUTTING
	bne	tc_no_snapshot
	lis	%r3, torque_net_engine_combustion@ha
	lhz	%r3, torque_net_engine_combustion@l(%r3)
	lis	%r4, race_tc_torque_when_tc_activated@ha
	sth	%r3, race_tc_torque_when_tc_activated@l(%r4)
tc_no_snapshot:
	ori	%r6, %r6, (RACE_TC_FLAG_ARMED | RACE_TC_FLAG_CUTTING)
	sth	%r6, race_tc_control_flags@l(%r5)

	# p_term = lookup_3D_uint32(6, 10, front_axle_speed_max, error_filtered, ...)
	li	%r3, 6
	li	%r4, 10
	lis	%r5, race_tc_front_axle_speed_max@ha
	lhz	%r5, race_tc_front_axle_speed_max@l(%r5)
	lis	%r6, race_tc_slip_error_filtered@ha
	lhz	%r6, race_tc_slip_error_filtered@l(%r6)
	lis	%r7, CAL_racetc_torque_cut_p_term@ha		# stock-cal location (RAM copy)
	addi	%r7, %r7, CAL_racetc_torque_cut_p_term@l
	lis	%r8, CAL_racetc_torque_cut_p_term_X_carspeed@ha
	addi	%r8, %r8, CAL_racetc_torque_cut_p_term_X_carspeed@l
	lis	%r9, CAL_racetc_torque_cut_p_term_Y_slip@ha
	addi	%r9, %r9, CAL_racetc_torque_cut_p_term_Y_slip@l
	bl	lookup_3D_uint32_interpolated

	clrlwi	%r3, %r3, 24			# p_term = result & 0xff (0-255)
	lis	%r4, race_tc_torque_cut_p_term@ha
	stb	%r3, race_tc_torque_cut_p_term@l(%r4)

	# fraction = min(p_term + i_term, 255)
	lis	%r4, race_tc_torque_cut_i_term@ha
	lbz	%r4, race_tc_torque_cut_i_term@l(%r4)
	add	%r3, %r3, %r4
	cmplwi	%r3, 255
	ble	tc_fraction_ok
	li	%r3, 255
tc_fraction_ok:
	lis	%r4, race_tc_torque_cut_fraction@ha
	stb	%r3, race_tc_torque_cut_fraction@l(%r4)	# r3 = fraction (kept)

	# spark = snapshot - snapshot*fraction/255  (unsigned; snapshot >= 0 in cut)
	lis	%r4, race_tc_torque_when_tc_activated@ha
	lhz	%r4, race_tc_torque_when_tc_activated@l(%r4)	# r4 = snapshot
	mullw	%r5, %r4, %r3			# snapshot * fraction (<= 911*255, fits 32b)
	li	%r6, 255
	divwu	%r5, %r5, %r6			# / 255
	subf	%r5, %r5, %r4			# spark = snapshot - reduction
	# floor at CAL_race_tc_torque_min_allowed
	lis	%r6, CAL_race_tc_torque_min_allowed@ha
	lhz	%r6, CAL_race_tc_torque_min_allowed@l(%r6)
	cmplw	%r5, %r6
	bge	tc_spark_ok
	mr	%r5, %r6
tc_spark_ok:
	lis	%r7, race_tc_torque_limit_spark@ha
	sth	%r5, race_tc_torque_limit_spark@l(%r7)
	# throttle = spark (recovery margin dropped on NA)
	lis	%r7, race_tc_torque_limit_throttle@ha
	sth	%r5, race_tc_torque_limit_throttle@l(%r7)
	b	tc_done

tc_below_threshold:
	# armed but not cutting: reset outputs, keep ARMED, clear CUTTING
	bl	race_tc_torque_reset_outputs
	lis	%r5, race_tc_control_flags@ha
	lhz	%r6, race_tc_control_flags@l(%r5)
	andi.	%r6, %r6, (0xffff & ~RACE_TC_FLAG_CUTTING)
	ori	%r6, %r6, RACE_TC_FLAG_ARMED
	sth	%r6, race_tc_control_flags@l(%r5)
	b	tc_done

tc_out_of_window:
	# out of window: full reset, clear ARMED + CUTTING
	bl	race_tc_torque_reset_outputs
	lis	%r5, race_tc_control_flags@ha
	lhz	%r6, race_tc_control_flags@l(%r5)
	andi.	%r6, %r6, (0xffff & ~(RACE_TC_FLAG_ARMED | RACE_TC_FLAG_CUTTING))
	sth	%r6, race_tc_control_flags@l(%r5)
tc_done:
	lwz	%r0, 12(%r1)
	mtlr	%r0
	addi	%r1, %r1, 8
	blr

# Reset the race TC torque outputs to the "no limit" state. Leaf. Clobbers r3, r4.
race_tc_torque_reset_outputs:
	li	%r3, RACE_TC_TORQUE_NO_LIMIT		# 911
	lis	%r4, race_tc_torque_limit_spark@ha
	sth	%r3, race_tc_torque_limit_spark@l(%r4)
	lis	%r4, race_tc_torque_limit_throttle@ha
	sth	%r3, race_tc_torque_limit_throttle@l(%r4)
	lis	%r4, race_tc_torque_when_tc_activated@ha
	sth	%r3, race_tc_torque_when_tc_activated@l(%r4)
	li	%r3, 0
	lis	%r4, race_tc_torque_cut_fraction@ha
	stb	%r3, race_tc_torque_cut_fraction@l(%r4)
	lis	%r4, race_tc_torque_cut_i_term@ha
	stb	%r3, race_tc_torque_cut_i_term@l(%r4)
	lis	%r4, race_tc_slip_integral_accumulator@ha
	sth	%r3, race_tc_slip_integral_accumulator@l(%r4)
	blr

# ---- race TC calibration tables (real GT430 C132E0278 values) --------------
# Transcribed verbatim from the GT430 disassembly so slip-target behaves
# identically until an NA-specific tune is dialed in. Slip units are 1/8%;
# pedal-comp units are 2% (the *16 in the code above converts them to 1/8%).
# GT430 RAM cal source address noted per table.
.balign 4

# CAL_race_tc_slip_target_from_pedal[6x6]: extra slip vs speed x pedal, u8 2%.
# GT430 @ 0x40009a0e. Row = pedal (Y), column = car speed (X);
# lut[pedal*6 + speed]. Nonzero only at high pedal + low speed (launch).
CAL_race_tc_slip_target_from_pedal:
	#      speed:   s0    s1    s2    s3    s4   s5
	.byte             0,    0,    0,    0,    0,   0	# pedal row 0
	.byte             0,    0,    0,    0,    0,   0	# pedal row 1
	.byte             0,    0,    0,    0,    0,   0	# pedal row 2
	.byte          0x0a, 0x05, 0x02,    0,    0,   0	# pedal row 3
	.byte          0x64, 0x34, 0x1c, 0x0e, 0x03,   0	# pedal row 4
	.byte          0xff, 0x84, 0x48, 0x2a, 0x0a,   0	# pedal row 5
CAL_race_tc_slip_target_from_pedal_X_carspeed:	# GT430 @ 0x40009a02
	.byte 5, 10, 15, 20, 30, 35			# u8 kph
CAL_race_tc_slip_target_from_pedal_Y_pps:		# GT430 @ 0x40009a08
	.byte 0x1a, 0x1a, 0x1a, 0x33, 0x66, 0xcc	# 26,26,26,51,102,204 (1/255)

# CAL_race_tc_slip_filter_coeff[8]: asymmetric error-filter gain vs car speed, u8
# (alpha = coeff/256; lower = slower decay = more smoothing). GT430 @ 0x4000e2c0.
CAL_race_tc_slip_filter_coeff:
	.byte 6, 6, 6, 6, 6, 6, 4, 2
CAL_race_tc_slip_filter_coeff_X_carspeed:		# GT430 @ 0x4000e2b8
	.byte 0, 0, 0, 0, 5, 10, 20, 30		# u8 kph

# Direct-mode calibrations (GT430 0x4000ccb0..0x4000ccb5, contiguous). u16 each.
.balign 2
# L-R wheel-speed diff above which the car is treated as cornering. 1/100 kph.
CAL_race_tc_cornering_lr_speed_diff_threshold:		# GT430 @ 0x4000ccb0
	.short 0x2d			# 45 = 0.45 kph
# Exit debounce: DIRECT stays latched this many 5 ms ticks after cornering
# ends. Reloaded each cornering cycle.
CAL_race_tc_cornering_release_delay:			# GT430 @ 0x4000ccb2
	.short 0x64			# 100 = 0.5 s at 200 Hz
# Entry debounce: continuous cornering must persist this many 5 ms ticks
# before DIRECT engages. Not consumed yet (detect-timer logic was dropped).
CAL_race_tc_cornering_detect_delay:			# GT430 @ 0x4000ccb4
	.short 0x28			# 40 = 0.2 s at 200 Hz

# ---- Block-6 (torque cut) calibrations (real GT430 C132E0278 values) ----
.balign 2
CAL_race_tc_min_engine_rpm:			.short 1800	# u16 rpm  (GT430 @ 0x4000ccae) = 0x708
CAL_race_tc_torque_min_allowed:		.short 30	# u16 Nm   (GT430) = 0x1E
CAL_race_tc_max_vehicle_speed:		.byte 255	# u8 kph   (GT430 @ 0x4000ccbb) = 0xff (no upper limit)
CAL_race_tc_min_vehicle_speed:		.byte 5		# u8 kph   (GT430 @ 0x4000ccbc)
CAL_race_tc_intervention_threshold:	.byte 16	# u8 1/8%  (GT430 @ 0x4000ccbd) = 2%

# ---- Integral (PI) controller calibrations (real GT430 C132E0278 values) ----
CAL_race_tc_integral_update_period:	.short 4000	# u16_time_5ms (GT430 @ 0x4000ccb6) = 0x0FA0 = 20 s
CAL_race_tc_torque_cut_i_gain:			.byte 1		# uint8_t      (GT430 @ 0x4000ccbe) = 0x01
CAL_race_tc_torque_cut_i_limit:			.byte 0x80	# uint8_t      (GT430 @ 0x4000ccbf) = 128, clamped ±128²/256
# The torque-cut P-term table and its axes are stock-cal locations
# (CAL_racetc_torque_cut_p_term*); defaults are in the cal sites at the end.
.balign 4	# realign: instructions must start on a 4-byte boundary

# Main-loop race TC entry: derive axle maxima / L-R diffs / slip and the slip
# target (race_tc_calc_slip), then the raw + filtered slip error
# (race_tc_calc_slip_error), then the torque cut / intervention (race_tc_calc_torque_cut).
# Called from the main loop hook. The torque-cut outputs are inert until the
# torque-path injection stage.
race_tc_slip_calculator:
	# Push link register on stack
	stwu	%r1, -8(%r1)
	mflr	%r0
	stw	%r0, 12(%r1)

	# --- ABS fault gate ---
	lis	%r3, abs_esp_flags@ha
	lbz	%r3, abs_esp_flags@l(%r3)	# abs_esp_flags is u8
	andi.	%r3, %r3, 0x10			# bit 4 = ABS fault
	beq	race_tc_sc_normal			# no fault -> proceed

	# ABS faulted: disable slip target, reset torque outputs
	lis	%r3, race_tc_slip_target@ha
	li	%r4, -1			# 0xFFFF in low 16 bits
	sth	%r4, race_tc_slip_target@l(%r3)
	bl	race_tc_torque_reset_outputs
	b	race_tc_sc_done

race_tc_sc_normal:
	bl	race_tc_calc_slip
	bl	race_tc_calc_slip_error
	bl	race_tc_calc_torque_cut

race_tc_sc_done:
	# Pop link register from stack
	lwz	%r0, 12(%r1)
	mtlr	%r0
	addi	%r1, %r1, 8
	blr

	# 200 Hz (5 ms) race TC state machine.  Three responsibilities per tick:
	#   0. Sport-button long-press (> 1.0 s) increments race_tc_mode_index
	#      (0..RACE_TC_MAX_LEVEL, wraps to 0).  Short presses are untouched and still
	#      toggle sport mode via the firmware's existing logic.
	#   1. Direct-mode cornering hysteresis (DIRECT flag + release timer).
	#   2. PI integral controller (accumulates slip error into torque cut).
	# Leaf (no calls) -> no LR frame. Clobbers r0, r3-r11.
	race_tc_system_state_manager_200hz:
		# === Stage 0: sport-button long-press (> 1.0 s) -> mode increment ===
		# Uses digital_input_raw_state[3] (0x40002C9B), which tracks
		# the physical button level even when the debounce is in toggle
		# mode.  1 = pressed, 0 = released.  Single-shot: fires once
		# per press, release required for next trigger.
		lis	%r3, sport_button_raw_state@ha
		lbz	%r3, sport_button_raw_state@l(%r3)
		cmplwi	%r3, 0
		beq	race_tc_btn_released

		# Pressed.  Skip if already triggered this hold.
		lis	%r4, race_tc_both_buttons_pressed@ha
		lbz	%r5, race_tc_both_buttons_pressed@l(%r4)
		cmplwi	%r5, 0
		bne	race_tc_btn_done

		# Count hold ticks.
		lis	%r6, race_tc_increase_hold_time@ha
		lbz	%r5, race_tc_increase_hold_time@l(%r6)
		addi	%r5, %r5, 1
		cmplwi	%r5, 200			# 200 * 5 ms = 1.0 s
		blt	race_tc_btn_store_hold

		# Threshold: increment mode, set triggered.
		li	%r5, 1
		stb	%r5, race_tc_both_buttons_pressed@l(%r4)
		li	%r5, 0
		stb	%r5, race_tc_increase_hold_time@l(%r6)
		lis	%r7, race_tc_mode_index@ha
		lbz	%r8, race_tc_mode_index@l(%r7)
		addi	%r8, %r8, 1
		cmplwi	%r8, RACE_TC_MAX_LEVEL + 1
		blt	race_tc_btn_store_mode
		li	%r8, 0
	race_tc_btn_store_mode:
		stb	%r8, race_tc_mode_index@l(%r7)
		b	race_tc_btn_done

	race_tc_btn_store_hold:
		stb	%r5, race_tc_increase_hold_time@l(%r6)
		b	race_tc_btn_done

	race_tc_btn_released:
		lis	%r4, race_tc_increase_hold_time@ha
		li	%r5, 0
		stb	%r5, race_tc_increase_hold_time@l(%r4)
		lis	%r4, race_tc_both_buttons_pressed@ha
		stb	%r5, race_tc_both_buttons_pressed@l(%r4)

	race_tc_btn_done:
		# === Stage 1: cornering hysteresis ===
		# cornering = (threshold < max_lr_diff)
		lis	%r3, race_tc_max_lr_speed_diff@ha
		lhz	%r3, race_tc_max_lr_speed_diff@l(%r3)
		lis	%r4, CAL_race_tc_cornering_lr_speed_diff_threshold@ha
		lhz	%r4, CAL_race_tc_cornering_lr_speed_diff_threshold@l(%r4)

		# Load flags (r6, base r5) and release-timer base (r7) up front.
		lis	%r5, race_tc_control_flags@ha
		lhz	%r6, race_tc_control_flags@l(%r5)
		lis	%r7, race_tc_cornering_release_timer@ha

		cmplw	%r4, %r3		# threshold < max_lr_diff ?
		blt	dsm_cornering

		# --- straight line: exit-debounce countdown ---
		lhz	%r8, race_tc_cornering_release_timer@l(%r7)
		cmplwi	%r8, 0
		beq	dsm_clear		# already expired -> keep DIRECT clear
		subi	%r8, %r8, 1
		sth	%r8, race_tc_cornering_release_timer@l(%r7)
		cmplwi	%r8, 0
		bne	dsm_integral		# still holding -> leave flags as-is, go to PI
	dsm_clear:
		andi.	%r6, %r6, (0xffff & ~RACE_TC_FLAG_DIRECT)
		sth	%r6, race_tc_control_flags@l(%r5)
		b	dsm_integral		# was dsm_ret; now continue to PI

	dsm_cornering:
		# --- cornering: engage DIRECT, reload the exit timer ---
		ori	%r6, %r6, RACE_TC_FLAG_DIRECT
		sth	%r6, race_tc_control_flags@l(%r5)
		lis	%r8, CAL_race_tc_cornering_release_delay@ha
		lhz	%r8, CAL_race_tc_cornering_release_delay@l(%r8)
		sth	%r8, race_tc_cornering_release_timer@l(%r7)
		# fall through to PI controller (was blr)

	# === Stage 2: PI integral controller ===
	# if (!(flags & CUTTING)): reset timer + accumulator + i_term
	# else if (timer == 0): update accumulator, clamp, derive i_term
	# else: decrement timer
	dsm_integral:
		# Reload flags (r6 may be stale from cornering paths).
		lis	%r5, race_tc_control_flags@ha
		lhz	%r3, race_tc_control_flags@l(%r5)
		andi.	%r3, %r3, RACE_TC_FLAG_CUTTING
		beq	dsm_int_reset		# !CUTTING -> reset integral

		# CUTTING is set: check update timer
		lis	%r4, race_tc_integral_update_timer@ha
		lhz	%r3, race_tc_integral_update_timer@l(%r4)
		cmplwi	%r3, 0
		beq	dsm_int_update		# timer expired -> update
		subi	%r3, %r3, 1		# timer > 0 -> decrement
		sth	%r3, race_tc_integral_update_timer@l(%r4)
		blr

	dsm_int_reset:
		# Reset integral: preload timer to period, clear accumulator + output.
		lis	%r3, CAL_race_tc_integral_update_period@ha
		lhz	%r3, CAL_race_tc_integral_update_period@l(%r3)
		lis	%r4, race_tc_integral_update_timer@ha
		sth	%r3, race_tc_integral_update_timer@l(%r4)
		li	%r3, 0
		lis	%r4, race_tc_slip_integral_accumulator@ha
		sth	%r3, race_tc_slip_integral_accumulator@l(%r4)
		lis	%r4, race_tc_torque_cut_i_term@ha
		stb	%r3, race_tc_torque_cut_i_term@l(%r4)
		blr

	dsm_int_update:
		# Reload timer with update period.
		lis	%r3, CAL_race_tc_integral_update_period@ha
		lhz	%r3, CAL_race_tc_integral_update_period@l(%r3)
		sth	%r3, race_tc_integral_update_timer@l(%r4)	# r4 still has timer base

		# accumulator += slip_error_filtered * gain
		lis	%r5, race_tc_slip_error_filtered@ha
		lhz	%r5, race_tc_slip_error_filtered@l(%r5)	# r5 = error (u16, >= 0)
		lis	%r6, CAL_race_tc_torque_cut_i_gain@ha
		lbz	%r6, CAL_race_tc_torque_cut_i_gain@l(%r6)	# r6 = gain (u8)
		mullw	%r5, %r5, %r6				# r5 = error * gain

		lis	%r7, race_tc_slip_integral_accumulator@ha
		lha	%r8, race_tc_slip_integral_accumulator@l(%r7)	# r8 = acc (signed 16-bit)
		add	%r8, %r8, %r5				# r8 = acc + error*gain

		# Clamp to +/- (limit * 128)
		lis	%r9, CAL_race_tc_torque_cut_i_limit@ha
		lbz	%r9, CAL_race_tc_torque_cut_i_limit@l(%r9)	# r9 = limit
		slwi	%r10, %r9, 7				# r10 = limit * 128 (upper)
		cmpw	%r8, %r10
		bgt	dsm_int_clamp_hi
		neg	%r11, %r10				# r11 = -(limit*128) (lower)
		cmpw	%r8, %r11
		blt	dsm_int_clamp_lo
		b	dsm_int_store

	dsm_int_clamp_hi:
		mr	%r8, %r10
		b	dsm_int_store
	dsm_int_clamp_lo:
		mr	%r8, %r11
	dsm_int_store:
		sth	%r8, race_tc_slip_integral_accumulator@l(%r7)	# store accumulator

		# i_term = accumulator >> 8 (arithmetic; acc >= 0 in practice)
		srawi	%r3, %r8, 8
		lis	%r4, race_tc_torque_cut_i_term@ha
		stb	%r3, race_tc_torque_cut_i_term@l(%r4)
		blr

# ---- Cal sites (declared in module.toml) ------------------------------------
# Default values for stock-cal locations labelled for race-tc. t6patch writes
# them into the cal when it still holds the stock zeros there, and keeps your
# tuned values otherwise. The code reads the firmware's RAM copy
# (CAL_racetc_* symbols), like any other calibration.

# CAL_racetc_slip_target_base[16]: base slip target, u8 1/8%. GT430 @ 0x4000d654.
# Looked up by race_tc_mode_index against the level axis below. That axis maps
# levels 1..9 -> 0, 3, 6, ... 24% in 3% steps (level 1 = most intervention;
# levels 1-5 match the GT430). Mode 0 is off (handled in code). A level above
# the last axis entry uses the last value.
.section .calsite.race-tc.slip_target_base, "a"
	.byte 0, 0, 0, 0, 0, 0, 0, 0			# [0..7] level 1 -> 0%
	.byte 24, 48, 72, 96, 120, 144, 168, 192	# [8..15] 3,6,9,12,15,18,21,24%

# CAL_racetc_slip_target_base_X_dpm_level[16]: level axis. GT430 @ 0x4000d644.
.section .calsite.race-tc.slip_target_base_X_level, "a"
	.byte 1, 1, 1, 1, 1, 1, 1, 1			# [0..7] -> level 1
	.byte 2, 3, 4, 5, 6, 7, 8, 9			# [8..15] -> levels 2..9

# CAL_racetc_torque_cut_p_term[60]: proportional torque cut, u16 factor 0..255
# (fraction of the torque at activation). 6 car speeds (X) x 10 slip errors (Y),
# row-major: lut[slip*6 + speed]. GT430 C132E0278 values, @ 0x4000998a.
.section .calsite.race-tc.torque_cut_p_term, "a"
	#      speed:  s0   s1   s2   s3   s4   s5
	.short          0,   0,   0,   0,   0,   0	# slip row 0 (2.5%)
	.short          7,   7,   7,  10,  15,  20	# 1 (3.0%)
	.short          8,   8,   8,  15,  23,  32	# 2 (3.5%)
	.short         10,  10,  10,  20,  30,  42	# 3 (4.0%)
	.short         18,  18,  18,  34,  51,  85	# 4 (6.0%)
	.short         25,  25,  25,  46,  71, 128	# 5 (8.0%)
	.short         38,  38,  38,  64, 102, 192	# 6 (12%)
	.short         60,  60,  60, 102, 154, 192	# 7 (20%)
	.short        112, 112, 112, 192, 192, 192	# 8 (50%)
	.short        192, 192, 192, 192, 192, 192	# 9 (100% slip)

# CAL_racetc_torque_cut_p_term_X_carspeed[6]: front axle speed, u16 1/100 kph
# (10, 10, 15, 20, 30, 35 kph). GT430 @ 0x4000996a.
.section .calsite.race-tc.torque_cut_p_term_X_carspeed, "a"
	.short 1000, 1000, 1500, 2000, 3000, 3500

# CAL_racetc_torque_cut_p_term_Y_slip[10]: filtered slip error, u16 1/8%
# (2.5 .. 100%). GT430 @ 0x40009976.
.section .calsite.race-tc.torque_cut_p_term_Y_slip, "a"
	.short 20, 24, 28, 32, 48, 64, 96, 160, 400, 800
