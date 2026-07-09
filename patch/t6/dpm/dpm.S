#TODO: Add dpm_mode_index cycle function using TC button
#TODO: change TC button default toggle duration/timout 
#TODO: add back direction histeresis via dpm_control_flags and dpm_direct_mode_on_delay
#TODO: OBD-II data reading is incorrect and forces reboot
#TODO: tune the i term from dpm correction in state mgmt
#TODO: move the CAL tables out of the data segment

# DPM (Dynamic Performance Mode) - 6-level slip-based traction control.
# Port of the C132E0278 (GT430) implementation to B13200091 (S1 Evora NA).
# Variable set follows C132E0278/DPM_plan.md Phase 1.

# Constants
.set DPM_MIN_ACTIVATE_SPEED,  5 # kph
.set DPM_SLIP_TARGET_OFFSET,  16 # 2% in 1/8% units

.set DPM_TORQUE_NO_LIMIT, 911 # Nm sentinel = "no torque cut requested"
.set DPM_MODE_MAX,          6 # Highest selectable DPM level

# dpm_control_flags bitmap
.set DPM_FLAG_ARMED,        0x0001 # In operating window (armed); set even below threshold
.set DPM_FLAG_CUTTING,      0x0002 # Actively cutting torque (snapshot taken on its rising edge)
.set DPM_FLAG_DIRECT,       0x0004 # Direct mode active (high L-R speed diff)
.set DPM_FLAG_SLIP_VALID,   0x0008 # Slip calculation valid
.set DPM_FLAG_SYS_ENABLED,  0x0010 # DPM system enabled
.set DPM_FLAG_SYS_DISABLED, 0x0020 # System disabled (fault/inhibit)
.set DPM_FLAG_BUTTONS,      0x0040 # Button processing enabled
.set DPM_FLAG_BTN_INC,      0x0080 # Increase button pressed
.set DPM_FLAG_BTN_DEC,      0x0100 # Decrease button pressed

.section .data

# DPM runtime state.
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
.global dpm_slip, dpm_slip_target
.global dpm_slip_error_raw, dpm_slip_error_filtered
.global dpm_slip_filter_accumulator, dpm_slip_integral_accumulator
.global dpm_torque_limit_spark, dpm_torque_limit_throttle
.global dpm_torque_when_tc_activated
.global dpm_torque_cut_factor, dpm_torque_cut_accumulated, dpm_torque_cut_total
.global dpm_mode_index, dpm_control_flags
.global dpm_front_axle_speed_max, dpm_rear_axle_speed_max
.global dpm_vehicle_speed_kph
.global dpm_front_lr_speed_diff, dpm_rear_lr_speed_diff, dpm_max_lr_speed_diff
.global dpm_direct_mode_on_delay, dpm_direct_mode_off_delay
.global dpm_integral_update_timer
.global dpm_button_increase, dpm_button_decrease
.global dpm_increase_hold_time, dpm_decrease_hold_time
.global dpm_both_buttons_pressed

# 32-bit
dpm_slip_filter_accumulator:   .skip 4 # u32, slip error filter state memory
dpm_slip_integral_accumulator: .skip 2 # i16, integral controller state (signed, 8.8 fixed-ish)

# 16-bit
dpm_slip:                      .skip 2 # u16_slip_1/8%, current wheel slip
dpm_slip_target:               .skip 2 # u16_slip_1/8%, target slip setpoint
dpm_slip_error_raw:            .skip 2 # u16_slip_1/8%, slip - target (when slip > target)
dpm_slip_error_filtered:       .skip 2 # u16_slip_1/8%, filtered error (fast attack, slow decay)
dpm_torque_limit_spark:        .skip 2 # u16_torque_nm, DPM target -> spark/fast channel (deep cut)
dpm_torque_limit_throttle:     .skip 2 # u16_torque_nm, throttle/slow ceiling (spark + recovery margin)
dpm_torque_when_tc_activated:  .skip 2 # u16_torque_nm, torque snapshot at intervention start
dpm_control_flags:             .skip 2 # DPM_FLAG_* bitmap
dpm_front_axle_speed_max:      .skip 2 # u16_speed_1/100kph, max(LF, RF)
dpm_rear_axle_speed_max:       .skip 2 # u16_speed_1/100kph, max(LR, RR)
dpm_front_lr_speed_diff:       .skip 2 # u16_speed_1/100kph, abs(LF - RF)
dpm_rear_lr_speed_diff:        .skip 2 # u16_speed_1/100kph, abs(LR - RR)
dpm_max_lr_speed_diff:         .skip 2 # u16_speed_1/100kph, max of front/rear L-R diffs
dpm_direct_mode_on_delay:      .skip 2 # u16_time_5ms, countdown to enter direct mode
dpm_direct_mode_off_delay:     .skip 2 # u16_time_5ms, countdown to exit direct mode
dpm_integral_update_timer:     .skip 2 # u16_time_5ms, integral update period countdown

# 8-bit
dpm_mode_index:                .skip 1 # 0 = off, 1-6 = DPM level
dpm_vehicle_speed_kph:         .skip 1 # u8_speed_kph, front axle max / 100
dpm_torque_cut_factor:         .skip 1 # u8_factor_1/255, instantaneous cut from lookup
dpm_torque_cut_accumulated:    .skip 1 # u8_factor_1/255, integral torque cut term
dpm_torque_cut_total:          .skip 1 # u8_factor_1/255, factor + accumulated (sat. 255)
dpm_button_increase:           .skip 1 # bool, increase button state
dpm_button_decrease:           .skip 1 # bool, decrease button state
dpm_increase_hold_time:        .skip 1 # u8, 5ms counts increase held
dpm_decrease_hold_time:        .skip 1 # u8, 5ms counts decrease held
dpm_both_buttons_pressed:      .skip 1 # bool, dual-press latch

.section .text
.global dpm_init, dpm_slip_calculator, dpm_system_state_manager_200hz

# The firmware does not zero-fill the patch .bss region, so every
# variable must be initialized explicitly here.
dpm_init:
	# Push link register on stack
	stwu	%r1, -8(%r1)
	mflr	%r0
	stw	%r0, 12(%r1)

	# Torque limits start at the "no limit" sentinel
	li	%r3, DPM_TORQUE_NO_LIMIT
	lis	%r4, dpm_torque_limit_spark@ha
	sth	%r3, dpm_torque_limit_spark@l(%r4)
	lis	%r4, dpm_torque_limit_throttle@ha
	sth	%r3, dpm_torque_limit_throttle@l(%r4)

	# Everything else starts at 0.
	# In particular dpm_mode_index = 0: DPM stays OFF until the
	# driver explicitly enables it.
	li	%r3, 0

	# 32-bit state
	lis	%r4, dpm_slip_filter_accumulator@ha
	stw	%r3, dpm_slip_filter_accumulator@l(%r4)
	lis	%r4, dpm_slip_integral_accumulator@ha
	sth	%r3, dpm_slip_integral_accumulator@l(%r4)

	# 16-bit state
	lis	%r4, dpm_slip@ha
	sth	%r3, dpm_slip@l(%r4)
	lis	%r4, dpm_slip_target@ha
	sth	%r3, dpm_slip_target@l(%r4)
	lis	%r4, dpm_slip_error_raw@ha
	sth	%r3, dpm_slip_error_raw@l(%r4)
	lis	%r4, dpm_slip_error_filtered@ha
	sth	%r3, dpm_slip_error_filtered@l(%r4)
	lis	%r4, dpm_torque_when_tc_activated@ha
	sth	%r3, dpm_torque_when_tc_activated@l(%r4)
	lis	%r4, dpm_control_flags@ha
	sth	%r3, dpm_control_flags@l(%r4)
	lis	%r4, dpm_front_axle_speed_max@ha
	sth	%r3, dpm_front_axle_speed_max@l(%r4)
	lis	%r4, dpm_rear_axle_speed_max@ha
	sth	%r3, dpm_rear_axle_speed_max@l(%r4)
	lis	%r4, dpm_front_lr_speed_diff@ha
	sth	%r3, dpm_front_lr_speed_diff@l(%r4)
	lis	%r4, dpm_rear_lr_speed_diff@ha
	sth	%r3, dpm_rear_lr_speed_diff@l(%r4)
	lis	%r4, dpm_max_lr_speed_diff@ha
	sth	%r3, dpm_max_lr_speed_diff@l(%r4)
	lis	%r4, dpm_direct_mode_on_delay@ha
	sth	%r3, dpm_direct_mode_on_delay@l(%r4)
	lis	%r4, dpm_direct_mode_off_delay@ha
	sth	%r3, dpm_direct_mode_off_delay@l(%r4)
	lis	%r4, dpm_integral_update_timer@ha
	sth	%r3, dpm_integral_update_timer@l(%r4)

	# 8-bit state
	lis	%r4, dpm_mode_index@ha
	# TODO: temporarily set mode to 3 at init
	li	%r3, 3
	stb	%r3, dpm_mode_index@l(%r4)
	li	%r3, 0
	lis	%r4, dpm_vehicle_speed_kph@ha
	stb	%r3, dpm_vehicle_speed_kph@l(%r4)
	lis	%r4, dpm_torque_cut_factor@ha
	stb	%r3, dpm_torque_cut_factor@l(%r4)
	lis	%r4, dpm_torque_cut_accumulated@ha
	stb	%r3, dpm_torque_cut_accumulated@l(%r4)
	lis	%r4, dpm_torque_cut_total@ha
	stb	%r3, dpm_torque_cut_total@l(%r4)
	# TODO: ensure that button variables are used
	lis	%r4, dpm_button_increase@ha
	stb	%r3, dpm_button_increase@l(%r4)
	lis	%r4, dpm_button_decrease@ha
	stb	%r3, dpm_button_decrease@l(%r4)
	lis	%r4, dpm_increase_hold_time@ha
	stb	%r3, dpm_increase_hold_time@l(%r4)
	lis	%r4, dpm_decrease_hold_time@ha
	stb	%r3, dpm_decrease_hold_time@l(%r4)
	lis	%r4, dpm_both_buttons_pressed@ha
	stb	%r3, dpm_both_buttons_pressed@l(%r4)

	# Pop link register from stack
	lwz	%r0, 12(%r1)
	mtlr	%r0
	addi	%r1, %r1, 8
	blr


# Subfunction of dpm_slip_calculator.
# Reads the firmware wheel_speed struct (halfwords, REARS FIRST:
# LR@0, RR@2, LF@4, RF@6; u16_speed_1/100kph) and updates:
#   dpm_front_axle_speed_max = max(LF, RF)
#   dpm_rear_axle_speed_max  = max(LR, RR)
#   dpm_vehicle_speed_kph    = min(front_max / 100, 255)
#   dpm_front_lr_speed_diff  = abs(LF - RF)
#   dpm_rear_lr_speed_diff   = abs(LR - RR)
#   dpm_max_lr_speed_diff    = max(front_lr_diff, rear_lr_diff)
#   dpm_slip                 = rear-over-front overspeed, 1/8% units
#   dpm_slip_target          = per-level target (via dpm_calc_slip_target)
# Clobbers r0, r3-r11; calls dpm_calc_slip_target.
dpm_calc_slip:
	# Push link register (this function now calls dpm_calc_slip_target).
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

	# dpm_front_axle_speed_max = max(LF, RF)
	mr	%r8, %r4
	cmplw	%r8, %r5
	bge	slip_1
	mr	%r8, %r5
slip_1:
	lis	%r10, dpm_front_axle_speed_max@ha
	sth	%r8, dpm_front_axle_speed_max@l(%r10)

	# dpm_rear_axle_speed_max = max(LR, RR)
	mr	%r9, %r6
	cmplw	%r9, %r7
	bge	slip_2
	mr	%r9, %r7
slip_2:
	lis	%r10, dpm_rear_axle_speed_max@ha
	sth	%r9, dpm_rear_axle_speed_max@l(%r10)

	# dpm_vehicle_speed_kph = min(front_max / 100, 255)
	li	%r10, 100
	divwu	%r0, %r8, %r10
	cmplwi	%r0, 255
	ble	slip_3
	li	%r0, 255
slip_3:
	lis	%r10, dpm_vehicle_speed_kph@ha
	stb	%r0, dpm_vehicle_speed_kph@l(%r10)

	# dpm_front_lr_speed_diff = abs(LF - RF)
	# Branchless abs: m = x >> 31; abs = (x ^ m) - m
	subf	%r0, %r5, %r4	# r0 = LF - RF
	srawi	%r10, %r0, 31
	xor	%r0, %r0, %r10
	subf	%r11, %r10, %r0	# r11 = abs(LF - RF), kept for the max below
	lis	%r10, dpm_front_lr_speed_diff@ha
	sth	%r11, dpm_front_lr_speed_diff@l(%r10)

	# dpm_rear_lr_speed_diff = abs(LR - RR)
	subf	%r0, %r7, %r6	# r0 = LR - RR
	srawi	%r10, %r0, 31
	xor	%r0, %r0, %r10
	subf	%r0, %r10, %r0	# r0 = abs(LR - RR)
	lis	%r10, dpm_rear_lr_speed_diff@ha
	sth	%r0, dpm_rear_lr_speed_diff@l(%r10)

	# dpm_max_lr_speed_diff = max(front_lr_diff, rear_lr_diff)
	# Cornering magnitude; the direct-mode hysteresis will consume this later.
	cmplw	%r11, %r0	# front (r11) vs rear (r0), unsigned
	bge	slip_4
	mr	%r11, %r0	# rear larger -> r11 = max
slip_4:
	lis	%r10, dpm_max_lr_speed_diff@ha
	sth	%r11, dpm_max_lr_speed_diff@l(%r10)

	# dpm_slip = (front_max > 0 && rear_max > front_max)
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
	lis	%r10, dpm_slip@ha
	sth	%r3, dpm_slip@l(%r10)

	# Compute the slip target that dpm_slip is judged against.
	bl	dpm_calc_slip_target

	# Pop link register.
	lwz	%r0, 12(%r1)
	mtlr	%r0
	addi	%r1, %r1, 8
	blr

# Compute dpm_slip_target: the slip threshold dpm_slip is judged against.
# Ported from C132E0278.c:58274-58327 (the "system enabled" active path).
#
#   pedal_comp = lookup_3D(6,6, vehicle_speed_kph, (pedal>>2)&0xff,
#                          CAL_dpm_slip_target_from_pedal, _X_carspeed, _Y_pps)
#   base       = lookup_2D(16, dpm_mode_index,
#                          CAL_dpm_slip_target_base, _X_dpm_level)
#   comp       = base + pedal_comp*16
#   target     = min(comp + (direct_mode ? 0 : DPM_SLIP_TARGET_OFFSET), 0xFFFF)
#
# In direct mode (DPM_FLAG_DIRECT, set by the 5 ms state manager on sustained
# cornering) the offset is skipped, tightening the target through corners.
#
# Simplifications versus the GT430 (racecar build):
#   - the enable gating (SYS_ENABLED/SYS_DISABLED) is dropped; the target is
#     ALWAYS computed. The dead pedal-only branch (BUTTONS clear) is omitted.
#   - dpm_mode_index 0 = DPM off: target = 0xFFFF so dpm_slip can never
#     exceed it. This is the level selector, not an enable flag, so it stays.
# The CAL_dpm_* values live in static .text tables below until the flash cal
# section lands (porting plan Phase 5/7).
# Non-leaf: calls firmware lookups. Clobbers r0, r3-r9.
dpm_calc_slip_target:
	# Push link register (this function calls the firmware lookups).
	stwu	%r1, -8(%r1)
	mflr	%r0
	stw	%r0, 12(%r1)

	# DPM off (mode 0): target = 0xFFFF, skip the lookups.
	lis	%r3, dpm_mode_index@ha
	lbz	%r3, dpm_mode_index@l(%r3)
	cmplwi	%r3, 0
	bne	tgt_on
	li	%r4, -1			# 0xFFFF after the halfword store
	lis	%r5, dpm_slip_target@ha
	sth	%r4, dpm_slip_target@l(%r5)
	b	tgt_done
tgt_on:
	# pedal_comp = lookup_3D_uint8_interpolated(6, 6, speed, pedal, ...)
	li	%r3, 6			# size_x
	li	%r4, 6			# size_y
	lis	%r5, dpm_vehicle_speed_kph@ha
	lbz	%r5, dpm_vehicle_speed_kph@l(%r5)	# input_x = speed (kph)
	lis	%r6, accel_pedal_latched@ha
	lha	%r6, accel_pedal_latched@l(%r6)
	srawi	%r6, %r6, 2
	clrlwi	%r6, %r6, 24		# input_y = (pedal>>2)&0xff
	lis	%r7, CAL_dpm_slip_target_from_pedal@ha
	addi	%r7, %r7, CAL_dpm_slip_target_from_pedal@l
	lis	%r8, CAL_dpm_slip_target_from_pedal_X_carspeed@ha
	addi	%r8, %r8, CAL_dpm_slip_target_from_pedal_X_carspeed@l
	lis	%r9, CAL_dpm_slip_target_from_pedal_Y_pps@ha
	addi	%r9, %r9, CAL_dpm_slip_target_from_pedal_Y_pps@l
	bl	lookup_3D_uint8_interpolated

	# Stash the pedal contribution (pedal_comp << 4: 2% -> 1/8% units) in the
	# target slot. Memory survives the next call, so no callee-saved register
	# is needed to carry it across the base lookup.
	slwi	%r3, %r3, 4
	lis	%r4, dpm_slip_target@ha
	sth	%r3, dpm_slip_target@l(%r4)

	# base = lookup_2D_uint8_interpolated(16, dpm_mode_index, ...)
	li	%r3, 16			# size_x
	lis	%r4, dpm_mode_index@ha
	lbz	%r4, dpm_mode_index@l(%r4)	# input_x = level
	lis	%r5, CAL_dpm_slip_target_base@ha
	addi	%r5, %r5, CAL_dpm_slip_target_base@l
	lis	%r6, CAL_dpm_slip_target_base_X_dpm_level@ha
	addi	%r6, %r6, CAL_dpm_slip_target_base_X_dpm_level@l
	bl	lookup_2D_uint8_interpolated

	# comp = base + pedal_contrib  (base in r3 from lookup_2D)
	lis	%r4, dpm_slip_target@ha
	lhz	%r5, dpm_slip_target@l(%r4)	# pedal contribution stashed above
	add	%r3, %r3, %r5

	# Add the offset unless direct mode is active. In direct mode (cornering)
	# the offset is skipped to tighten the target (C132E0278.c:58317-58327).
	lis	%r6, dpm_control_flags@ha
	lhz	%r6, dpm_control_flags@l(%r6)
	andi.	%r6, %r6, DPM_FLAG_DIRECT
	bne	tgt_clamp			# direct mode -> no offset
	addi	%r3, %r3, DPM_SLIP_TARGET_OFFSET
tgt_clamp:
	cmplwi	%r3, 0xFFFF
	ble	tgt_store
	li	%r3, -1			# clamp to 0xFFFF
tgt_store:
	sth	%r3, dpm_slip_target@l(%r4)
tgt_done:
	# Pop link register.
	lwz	%r0, 12(%r1)
	mtlr	%r0
	addi	%r1, %r1, 8
	blr

# Subfunction of dpm_slip_calculator. Derives the slip error and its
# asymmetric (fast-attack / slow-decay) filter from dpm_slip and
# dpm_slip_target. Ported from C132E0278.c:58328-58349.
#   dpm_slip_error_raw = (slip > target) ? slip - target : 0
#   coeff = lookup_2D(8, vehicle_speed_kph,
#                     CAL_dpm_slip_filter_coeff, _X_carspeed)   # gain, /256
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
dpm_calc_slip_error:
	stwu	%r1, -8(%r1)
	mflr	%r0
	stw	%r0, 12(%r1)

	# dpm_slip_error_raw = (slip > target) ? slip - target : 0
	lis	%r3, dpm_slip@ha
	lhz	%r3, dpm_slip@l(%r3)
	lis	%r4, dpm_slip_target@ha
	lhz	%r4, dpm_slip_target@l(%r4)
	li	%r5, 0
	cmplw	%r3, %r4		# slip vs target, unsigned
	ble	serr_store_raw		# slip <= target -> raw = 0
	subf	%r5, %r4, %r3		# raw = slip - target
serr_store_raw:
	lis	%r6, dpm_slip_error_raw@ha
	sth	%r5, dpm_slip_error_raw@l(%r6)

	# coeff = lookup_2D_uint8_interpolated(8, vehicle_speed_kph, tbl, axis)
	li	%r3, 8
	lis	%r4, dpm_vehicle_speed_kph@ha
	lbz	%r4, dpm_vehicle_speed_kph@l(%r4)	# input_x = speed (kph)
	lis	%r5, CAL_dpm_slip_filter_coeff@ha
	addi	%r5, %r5, CAL_dpm_slip_filter_coeff@l
	lis	%r6, CAL_dpm_slip_filter_coeff_X_carspeed@ha
	addi	%r6, %r6, CAL_dpm_slip_filter_coeff_X_carspeed@l
	bl	lookup_2D_uint8_interpolated	# r3 = coeff (clobbers volatiles)

	# Reload raw (r4) and the previous filtered (r5); coeff stays in r3.
	lis	%r4, dpm_slip_error_raw@ha
	lhz	%r4, dpm_slip_error_raw@l(%r4)
	lis	%r5, dpm_slip_error_filtered@ha
	lhz	%r5, dpm_slip_error_filtered@l(%r5)

	cmplw	%r4, %r5
	beq	serr_done		# raw == filtered -> unchanged
	blt	serr_decay		# raw < filtered  -> slow decay

	# --- instant attack (raw > filtered) ---
	lis	%r6, dpm_slip_error_filtered@ha
	sth	%r4, dpm_slip_error_filtered@l(%r6)
	slwi	%r7, %r4, 8			# accumulator = raw << 8
	lis	%r6, dpm_slip_filter_accumulator@ha
	stw	%r7, dpm_slip_filter_accumulator@l(%r6)
	b	serr_done

serr_decay:
	# accumulator = ((256-coeff)*accumulator >> 8) + coeff*raw
	lis	%r6, dpm_slip_filter_accumulator@ha
	lwz	%r7, dpm_slip_filter_accumulator@l(%r6)
	subfic	%r8, %r3, 256		# 256 - coeff
	mullw	%r8, %r8, %r7		# (256-coeff) * accumulator
	srwi	%r8, %r8, 8
	mullw	%r9, %r3, %r4		# coeff * raw
	add	%r8, %r8, %r9		# new accumulator
	stw	%r8, dpm_slip_filter_accumulator@l(%r6)
	srwi	%r8, %r8, 8		# filtered = accumulator >> 8
	lis	%r6, dpm_slip_error_filtered@ha
	sth	%r8, dpm_slip_error_filtered@l(%r6)
serr_done:
	lwz	%r0, 12(%r1)
	mtlr	%r0
	addi	%r1, %r1, 8
	blr

# Subfunction of dpm_slip_calculator: the torque-cut / intervention block.
# Port of C132E0278.c:58442-58500. COMPUTE-ONLY (Stage 1): produces
# dpm_torque_limit_spark/throttle, dpm_torque_cut_factor/total and the
# ARMED/CUTTING flags, but nothing consumes them yet (torque-path injection is
# a later stage), so this is inert telemetry.
#
# Gate (all must hold, else full reset to the 911 sentinel):
#   dpm_mode_index != 0                               (replaces vehicle_mode==VM_DPM_ACTIVE)
#   CAL_dpm_min_vehicle_speed < vehicle_speed_kph < CAL_dpm_max_vehicle_speed
#   CAL_dpm_min_engine_rpm < engine_speed_16bit
#   (inj_flags & 1) == 0                              (fuel cut inactive)
#   (dpm_control_flags & DPM_FLAG_SYS_DISABLED) == 0  (set by the later ABS gate)
# The GT430 SLIP_VALID (bit 3) gate is dropped: mode 0 already forces
# target=0xFFFF -> error 0, and the mode!=0 gate covers "valid".
#
# In window, if intervention_threshold < error_filtered -> CUTTING:
#   snapshot torque on the CUTTING rising edge, set ARMED|CUTTING,
#   factor = lookup_3D_uint32(6,10, front_axle_speed_max, error_filtered, ...),
#   total  = min(factor + cut_accumulated, 255),
#   spark  = max(snapshot - snapshot*total/255, CAL_dpm_torque_min_allowed),
#   throttle = spark   (GT430 adds torque_external_request_margin, absent on
#                       the NA -> margin dropped for now).
# P-only: cut_accumulated stays 0 until the integral controller (Stage 2).
# Non-leaf: calls lookup_3D_uint32 + dpm_torque_reset_outputs. Clobbers r0,r3-r9.
dpm_calc_torque_cut:
	stwu	%r1, -8(%r1)
	mflr	%r0
	stw	%r0, 12(%r1)

	# --- gate ---
	lis	%r3, dpm_mode_index@ha
	lbz	%r3, dpm_mode_index@l(%r3)
	cmplwi	%r3, 0
	beq	tc_out_of_window		# DPM off

	lis	%r3, dpm_vehicle_speed_kph@ha
	lbz	%r3, dpm_vehicle_speed_kph@l(%r3)	# r3 = speed (kept)
	lis	%r4, CAL_dpm_max_vehicle_speed@ha
	lbz	%r4, CAL_dpm_max_vehicle_speed@l(%r4)
	cmplw	%r3, %r4
	bge	tc_out_of_window		# speed >= max
	lis	%r4, CAL_dpm_min_vehicle_speed@ha
	lbz	%r4, CAL_dpm_min_vehicle_speed@l(%r4)
	cmplw	%r3, %r4
	ble	tc_out_of_window		# speed <= min

	lis	%r3, engine_speed_16bit@ha
	lhz	%r3, engine_speed_16bit@l(%r3)
	lis	%r4, CAL_dpm_min_engine_rpm@ha
	lhz	%r4, CAL_dpm_min_engine_rpm@l(%r4)
	cmplw	%r3, %r4
	ble	tc_out_of_window		# engine_speed <= min_rpm

	lis	%r3, inj_flags@ha
	lhz	%r3, inj_flags@l(%r3)
	andi.	%r3, %r3, 1
	bne	tc_out_of_window		# fuel cut active

	lis	%r5, dpm_control_flags@ha
	lhz	%r6, dpm_control_flags@l(%r5)	# r6 = flags, r5 = base (both kept)
	andi.	%r3, %r6, DPM_FLAG_SYS_DISABLED
	bne	tc_out_of_window

	# --- in window: intervention threshold ---
	lis	%r3, dpm_slip_error_filtered@ha
	lhz	%r3, dpm_slip_error_filtered@l(%r3)
	lis	%r4, CAL_dpm_intervention_threshold@ha
	lbz	%r4, CAL_dpm_intervention_threshold@l(%r4)
	cmplw	%r3, %r4
	ble	tc_below_threshold		# error <= threshold: armed, no cut

	# --- cutting ---
	# snapshot torque on the CUTTING rising edge
	andi.	%r3, %r6, DPM_FLAG_CUTTING
	bne	tc_no_snapshot
	lis	%r3, torque_net_engine_combustion@ha
	lhz	%r3, torque_net_engine_combustion@l(%r3)
	lis	%r4, dpm_torque_when_tc_activated@ha
	sth	%r3, dpm_torque_when_tc_activated@l(%r4)
tc_no_snapshot:
	ori	%r6, %r6, (DPM_FLAG_ARMED | DPM_FLAG_CUTTING)
	sth	%r6, dpm_control_flags@l(%r5)

	# factor = lookup_3D_uint32(6, 10, front_axle_speed_max, error_filtered, ...)
	li	%r3, 6
	li	%r4, 10
	lis	%r5, dpm_front_axle_speed_max@ha
	lhz	%r5, dpm_front_axle_speed_max@l(%r5)
	lis	%r6, dpm_slip_error_filtered@ha
	lhz	%r6, dpm_slip_error_filtered@l(%r6)
	lis	%r7, CAL_dpm_torque_cut_factor@ha
	addi	%r7, %r7, CAL_dpm_torque_cut_factor@l
	lis	%r8, CAL_dpm_torque_cut_factor_X_carspeed@ha
	addi	%r8, %r8, CAL_dpm_torque_cut_factor_X_carspeed@l
	lis	%r9, CAL_dpm_torque_cut_factor_Y_slip@ha
	addi	%r9, %r9, CAL_dpm_torque_cut_factor_Y_slip@l
	bl	lookup_3D_uint32_interpolated

	clrlwi	%r3, %r3, 24			# factor = result & 0xff (0-255)
	lis	%r4, dpm_torque_cut_factor@ha
	stb	%r3, dpm_torque_cut_factor@l(%r4)

	# total = min(factor + cut_accumulated, 255)
	lis	%r4, dpm_torque_cut_accumulated@ha
	lbz	%r4, dpm_torque_cut_accumulated@l(%r4)
	add	%r3, %r3, %r4
	cmplwi	%r3, 255
	ble	tc_total_ok
	li	%r3, 255
tc_total_ok:
	lis	%r4, dpm_torque_cut_total@ha
	stb	%r3, dpm_torque_cut_total@l(%r4)	# r3 = total (kept)

	# spark = snapshot - snapshot*total/255  (unsigned; snapshot >= 0 in cut)
	lis	%r4, dpm_torque_when_tc_activated@ha
	lhz	%r4, dpm_torque_when_tc_activated@l(%r4)	# r4 = snapshot
	mullw	%r5, %r4, %r3			# snapshot * total (<= 911*255, fits 32b)
	li	%r6, 255
	divwu	%r5, %r5, %r6			# / 255
	subf	%r5, %r5, %r4			# spark = snapshot - reduction
	# floor at CAL_dpm_torque_min_allowed
	lis	%r6, CAL_dpm_torque_min_allowed@ha
	lhz	%r6, CAL_dpm_torque_min_allowed@l(%r6)
	cmplw	%r5, %r6
	bge	tc_spark_ok
	mr	%r5, %r6
tc_spark_ok:
	lis	%r7, dpm_torque_limit_spark@ha
	sth	%r5, dpm_torque_limit_spark@l(%r7)
	# throttle = spark (recovery margin dropped on NA)
	lis	%r7, dpm_torque_limit_throttle@ha
	sth	%r5, dpm_torque_limit_throttle@l(%r7)
	b	tc_done

tc_below_threshold:
	# armed but not cutting: reset outputs, keep ARMED, clear CUTTING
	bl	dpm_torque_reset_outputs
	lis	%r5, dpm_control_flags@ha
	lhz	%r6, dpm_control_flags@l(%r5)
	andi.	%r6, %r6, (0xffff & ~DPM_FLAG_CUTTING)
	ori	%r6, %r6, DPM_FLAG_ARMED
	sth	%r6, dpm_control_flags@l(%r5)
	b	tc_done

tc_out_of_window:
	# out of window: full reset, clear ARMED + CUTTING
	bl	dpm_torque_reset_outputs
	lis	%r5, dpm_control_flags@ha
	lhz	%r6, dpm_control_flags@l(%r5)
	andi.	%r6, %r6, (0xffff & ~(DPM_FLAG_ARMED | DPM_FLAG_CUTTING))
	sth	%r6, dpm_control_flags@l(%r5)
tc_done:
	lwz	%r0, 12(%r1)
	mtlr	%r0
	addi	%r1, %r1, 8
	blr

# Reset the DPM torque outputs to the "no limit" state. Leaf. Clobbers r3, r4.
dpm_torque_reset_outputs:
	li	%r3, DPM_TORQUE_NO_LIMIT		# 911
	lis	%r4, dpm_torque_limit_spark@ha
	sth	%r3, dpm_torque_limit_spark@l(%r4)
	lis	%r4, dpm_torque_limit_throttle@ha
	sth	%r3, dpm_torque_limit_throttle@l(%r4)
	lis	%r4, dpm_torque_when_tc_activated@ha
	sth	%r3, dpm_torque_when_tc_activated@l(%r4)
	li	%r3, 0
	lis	%r4, dpm_torque_cut_total@ha
	stb	%r3, dpm_torque_cut_total@l(%r4)
	lis	%r4, dpm_torque_cut_accumulated@ha
	stb	%r3, dpm_torque_cut_accumulated@l(%r4)
	lis	%r4, dpm_slip_integral_accumulator@ha
	sth	%r3, dpm_slip_integral_accumulator@l(%r4)
	blr

# ---- DPM calibration tables (real GT430 C132E0278 values) --------------
# Transcribed verbatim from the GT430 disassembly so slip-target behaves
# identically until an NA-specific tune is dialed in. Slip units are 1/8%;
# pedal-comp units are 2% (the *16 in the code above converts them to 1/8%).
# GT430 RAM cal source address noted per table.
.balign 4

# CAL_dpm_slip_target_base[16]: base slip target, u8 1/8%. GT430 @ 0x4000d654.
# Looked up by dpm_mode_index against the level axis below. That axis maps
# levels 1..5 -> 0%, 3%, 6%, 9%, 12% (level 1 = most intervention). Mode 0 is
# off (handled in code); mode 6 clamps to the level-5 value (12%).
CAL_dpm_slip_target_base:
	.byte 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0	# [0..11] level 1 -> 0%
	.byte 0x18, 0x30, 0x48, 0x60			# [12..15] 24,48,72,96 = 3,6,9,12%
CAL_dpm_slip_target_base_X_dpm_level:		# GT430 @ 0x4000d644
	.byte 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1	# [0..11] -> level 1
	.byte 2, 3, 4, 5				# [12..15] -> levels 2..5

# CAL_dpm_slip_target_from_pedal[6x6]: extra slip vs speed x pedal, u8 2%.
# GT430 @ 0x40009a0e. Row = pedal (Y), column = car speed (X);
# lut[pedal*6 + speed]. Nonzero only at high pedal + low speed (launch).
CAL_dpm_slip_target_from_pedal:
	#      speed:   s0    s1    s2    s3    s4   s5
	.byte             0,    0,    0,    0,    0,   0	# pedal row 0
	.byte             0,    0,    0,    0,    0,   0	# pedal row 1
	.byte             0,    0,    0,    0,    0,   0	# pedal row 2
	.byte          0x0a, 0x05, 0x02,    0,    0,   0	# pedal row 3
	.byte          0x64, 0x34, 0x1c, 0x0e, 0x03,   0	# pedal row 4
	.byte          0xff, 0x84, 0x48, 0x2a, 0x0a,   0	# pedal row 5
CAL_dpm_slip_target_from_pedal_X_carspeed:	# GT430 @ 0x40009a02
	.byte 5, 10, 15, 20, 30, 35			# u8 kph
CAL_dpm_slip_target_from_pedal_Y_pps:		# GT430 @ 0x40009a08
	.byte 0x1a, 0x1a, 0x1a, 0x33, 0x66, 0xcc	# 26,26,26,51,102,204 (1/255)

# CAL_dpm_slip_filter_coeff[8]: asymmetric error-filter gain vs car speed, u8
# (alpha = coeff/256; lower = slower decay = more smoothing). GT430 @ 0x4000e2c0.
CAL_dpm_slip_filter_coeff:
	.byte 6, 6, 6, 6, 6, 6, 4, 2
CAL_dpm_slip_filter_coeff_X_carspeed:		# GT430 @ 0x4000e2b8
	.byte 0, 0, 0, 0, 5, 10, 20, 30		# u8 kph

# Direct-mode calibrations (GT430 0x4000ccb0..0x4000ccb5, contiguous). u16 each.
.balign 2
# L-R wheel-speed diff above which the car is treated as cornering. 1/100 kph.
CAL_dpm_lr_diff_cornerning_threshold:		# GT430 @ 0x4000ccb0
	.short 0x2d			# 45 = 0.45 kph
# Exit debounce: DIRECT stays latched this many 5 ms ticks after cornering
# ends. Reloaded each cornering cycle.
CAL_dpm_direct_mode_off_delay:			# GT430 @ 0x4000ccb2
	.short 0x64			# 100 = 0.5 s at 200 Hz
# Entry debounce: continuous cornering must persist this many 5 ms ticks
# before DIRECT engages. Not consumed yet (on_delay logic was dropped).
CAL_dpm_direct_mode_on_delay:			# GT430 @ 0x4000ccb4
	.short 0x28			# 40 = 0.2 s at 200 Hz

# ---- Block-6 (torque cut) calibrations (real GT430 C132E0278 values) ----
.balign 2
CAL_dpm_min_engine_rpm:			.short 1800	# u16 rpm  (GT430 @ 0x4000ccae) = 0x708
CAL_dpm_torque_min_allowed:		.short 30	# u16 Nm   (GT430) = 0x1E
CAL_dpm_max_vehicle_speed:		.byte 255	# u8 kph   (GT430 @ 0x4000ccbb) = 0xff (no upper limit)
CAL_dpm_min_vehicle_speed:		.byte 5		# u8 kph   (GT430 @ 0x4000ccbc)
CAL_dpm_intervention_threshold:	.byte 16	# u8 1/8%  (GT430 @ 0x4000ccbd) = 2%

# ---- Integral (PI) controller calibrations (real GT430 C132E0278 values) ----
CAL_dpm_integral_update_period:	.short 4000	# u16_time_5ms (GT430 @ 0x4000ccb6) = 0x0FA0 = 20 s
CAL_dpm_integral_gain:			.byte 1		# uint8_t      (GT430 @ 0x4000ccbe) = 0x01
CAL_dpm_integral_limit:			.byte 0x80	# uint8_t      (GT430 @ 0x4000ccbf) = 128, clamped ±128²/256
.balign 2
# CAL_dpm_torque_cut_factor[60]: 6 (car speed, X) x 10 (slip error, Y), u16
# factor 0..255. Row-major: lut[slip*6 + speed]. GT430 @ 0x4000998a.
CAL_dpm_torque_cut_factor:
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
CAL_dpm_torque_cut_factor_X_carspeed:		# GT430 @ 0x4000996a
	.short 1000, 1000, 1500, 2000, 3000, 3500	# u16 1/100 kph = 10,10,15,20,30,35
CAL_dpm_torque_cut_factor_Y_slip:		# GT430 @ 0x40009976
	.short 20, 24, 28, 32, 48, 64, 96, 160, 400, 800  # u16 1/8% = 2.5..100%
.balign 4	# realign: instructions must start on a 4-byte boundary

# Main-loop DPM entry: derive axle maxima / L-R diffs / slip and the slip
# target (dpm_calc_slip), then the raw + filtered slip error
# (dpm_calc_slip_error), then the torque cut / intervention (dpm_calc_torque_cut).
# Called from the main loop hook. The torque-cut outputs are inert until the
# torque-path injection stage.
dpm_slip_calculator:
	# Push link register on stack
	stwu	%r1, -8(%r1)
	mflr	%r0
	stw	%r0, 12(%r1)

	# --- ABS fault gate ---
	lis	%r3, abs_esp_flags@ha
	lbz	%r3, abs_esp_flags@l(%r3)	# abs_esp_flags is u8
	andi.	%r3, %r3, 0x10			# bit 4 = ABS fault
	beq	dpm_sc_normal			# no fault -> proceed

	# ABS faulted: disable slip target, reset torque outputs
	lis	%r3, dpm_slip_target@ha
	li	%r4, -1			# 0xFFFF in low 16 bits
	sth	%r4, dpm_slip_target@l(%r3)
	bl	dpm_torque_reset_outputs
	b	dpm_sc_done

dpm_sc_normal:
	bl	dpm_calc_slip
	bl	dpm_calc_slip_error
	bl	dpm_calc_torque_cut

dpm_sc_done:
	# Pop link register from stack
	lwz	%r0, 12(%r1)
	mtlr	%r0
	addi	%r1, %r1, 8
	blr

	# 200 Hz (5 ms) DPM state machine.  Three responsibilities per tick:
	#   0. Sport-button long-press (> 1.0 s) increments dpm_mode_index
	#      (0..6, wraps to 0).  Short presses are untouched and still
	#      toggle sport mode via the firmware's existing logic.
	#   1. Direct-mode cornering hysteresis (DIRECT flag + off-delay timer).
	#   2. PI integral controller (accumulates slip error into torque cut).
	# Leaf (no calls) -> no LR frame. Clobbers r0, r3-r11.
	dpm_system_state_manager_200hz:
		# === Stage 0: sport-button edge -> mode increment ===
		# Each sport-button press toggles sport_button_enable.
		# Detect any edge (0->1 or 1->0) and increment DPM mode.
		# No hold timer needed, no raw input needed.
		lis	%r3, sport_button_enable@ha
		lbz	%r3, sport_button_enable@l(%r3)	# current state
		lis	%r4, dpm_increase_hold_time@ha
		lbz	%r5, dpm_increase_hold_time@l(%r4)	# previous state
		cmplw	%r3, %r5
		beq	dpm_btn_done			# no change -> nothing to do
		stb	%r3, dpm_increase_hold_time@l(%r4)	# save new previous

		# Edge detected: increment mode.
		lis	%r6, dpm_mode_index@ha
		lbz	%r7, dpm_mode_index@l(%r6)
		addi	%r7, %r7, 1
		cmplwi	%r7, 7			# max mode = 6; wrap to 0
		blt	dpm_btn_store_mode
		li	%r7, 0
	dpm_btn_store_mode:
		stb	%r7, dpm_mode_index@l(%r6)

	dpm_btn_done:
		# === Stage 1: cornering hysteresis ===
		# cornering = (threshold < max_lr_diff)
		lis	%r3, dpm_max_lr_speed_diff@ha
		lhz	%r3, dpm_max_lr_speed_diff@l(%r3)
		lis	%r4, CAL_dpm_lr_diff_cornerning_threshold@ha
		lhz	%r4, CAL_dpm_lr_diff_cornerning_threshold@l(%r4)

		# Load flags (r6, base r5) and off_delay base (r7) up front.
		lis	%r5, dpm_control_flags@ha
		lhz	%r6, dpm_control_flags@l(%r5)
		lis	%r7, dpm_direct_mode_off_delay@ha

		cmplw	%r4, %r3		# threshold < max_lr_diff ?
		blt	dsm_cornering

		# --- straight line: exit-debounce countdown ---
		lhz	%r8, dpm_direct_mode_off_delay@l(%r7)
		cmplwi	%r8, 0
		beq	dsm_clear		# already expired -> keep DIRECT clear
		subi	%r8, %r8, 1
		sth	%r8, dpm_direct_mode_off_delay@l(%r7)
		cmplwi	%r8, 0
		bne	dsm_integral		# still holding -> leave flags as-is, go to PI
	dsm_clear:
		andi.	%r6, %r6, (0xffff & ~DPM_FLAG_DIRECT)
		sth	%r6, dpm_control_flags@l(%r5)
		b	dsm_integral		# was dsm_ret; now continue to PI

	dsm_cornering:
		# --- cornering: engage DIRECT, reload the exit timer ---
		ori	%r6, %r6, DPM_FLAG_DIRECT
		sth	%r6, dpm_control_flags@l(%r5)
		lis	%r8, CAL_dpm_direct_mode_off_delay@ha
		lhz	%r8, CAL_dpm_direct_mode_off_delay@l(%r8)
		sth	%r8, dpm_direct_mode_off_delay@l(%r7)
		# fall through to PI controller (was blr)

	# === Stage 2: PI integral controller ===
	# if (!(flags & CUTTING)): reset timer + accumulator + accumulated cut
	# else if (timer == 0): update accumulator, clamp, derive accumulated cut
	# else: decrement timer
	dsm_integral:
		# Reload flags (r6 may be stale from cornering paths).
		lis	%r5, dpm_control_flags@ha
		lhz	%r3, dpm_control_flags@l(%r5)
		andi.	%r3, %r3, DPM_FLAG_CUTTING
		beq	dsm_int_reset		# !CUTTING -> reset integral

		# CUTTING is set: check update timer
		lis	%r4, dpm_integral_update_timer@ha
		lhz	%r3, dpm_integral_update_timer@l(%r4)
		cmplwi	%r3, 0
		beq	dsm_int_update		# timer expired -> update
		subi	%r3, %r3, 1		# timer > 0 -> decrement
		sth	%r3, dpm_integral_update_timer@l(%r4)
		blr

	dsm_int_reset:
		# Reset integral: preload timer to period, clear accumulator + output.
		lis	%r3, CAL_dpm_integral_update_period@ha
		lhz	%r3, CAL_dpm_integral_update_period@l(%r3)
		lis	%r4, dpm_integral_update_timer@ha
		sth	%r3, dpm_integral_update_timer@l(%r4)
		li	%r3, 0
		lis	%r4, dpm_slip_integral_accumulator@ha
		sth	%r3, dpm_slip_integral_accumulator@l(%r4)
		lis	%r4, dpm_torque_cut_accumulated@ha
		stb	%r3, dpm_torque_cut_accumulated@l(%r4)
		blr

	dsm_int_update:
		# Reload timer with update period.
		lis	%r3, CAL_dpm_integral_update_period@ha
		lhz	%r3, CAL_dpm_integral_update_period@l(%r3)
		sth	%r3, dpm_integral_update_timer@l(%r4)	# r4 still has timer base

		# accumulator += slip_error_filtered * gain
		lis	%r5, dpm_slip_error_filtered@ha
		lhz	%r5, dpm_slip_error_filtered@l(%r5)	# r5 = error (u16, >= 0)
		lis	%r6, CAL_dpm_integral_gain@ha
		lbz	%r6, CAL_dpm_integral_gain@l(%r6)	# r6 = gain (u8)
		mullw	%r5, %r5, %r6				# r5 = error * gain

		lis	%r7, dpm_slip_integral_accumulator@ha
		lha	%r8, dpm_slip_integral_accumulator@l(%r7)	# r8 = acc (signed 16-bit)
		add	%r8, %r8, %r5				# r8 = acc + error*gain

		# Clamp to +/- (limit * 128)
		lis	%r9, CAL_dpm_integral_limit@ha
		lbz	%r9, CAL_dpm_integral_limit@l(%r9)	# r9 = limit
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
		sth	%r8, dpm_slip_integral_accumulator@l(%r7)	# store accumulator

		# torque_cut_accumulated = accumulator >> 8 (arithmetic; acc >= 0 in practice)
		srawi	%r3, %r8, 8
		lis	%r4, dpm_torque_cut_accumulated@ha
		stb	%r3, dpm_torque_cut_accumulated@l(%r4)
		blr
