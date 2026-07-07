# DPM (Dynamic Performance Mode) - 6-level slip-based traction control.
# Port of the C132E0278 (GT430) implementation to B13200091 (S1 Evora NA).
# Variable set follows C132E0278/DPM_plan.md Phase 1.

# Constants
.set DPM_TORQUE_NO_LIMIT, 911 # Nm sentinel = "no torque cut requested"
.set DPM_MODE_MAX,          6 # Highest selectable DPM level

# dpm_control_flags bitmap
.set DPM_FLAG_ACTIVE,       0x0001 # Intervention active (torque being cut)
.set DPM_FLAG_ENABLED,      0x0002 # Intervention enabled
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
.global dpm_target_torque_reduced, dpm_target_torque_upper_limit
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
dpm_slip_integral_accumulator: .skip 4 # i32, integral controller state

# 16-bit
dpm_slip:                      .skip 2 # u16_slip_1/8%, current wheel slip
dpm_slip_target:               .skip 2 # u16_slip_1/8%, target slip setpoint
dpm_slip_error_raw:            .skip 2 # u16_slip_1/8%, slip - target (when slip > target)
dpm_slip_error_filtered:       .skip 2 # u16_slip_1/8%, filtered error (fast attack, slow decay)
dpm_target_torque_reduced:     .skip 2 # u16_torque_nm, maximum allowed torque
dpm_target_torque_upper_limit: .skip 2 # u16_torque_nm, reduced + recovery margin
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
.global dpm_init, dpm_slip_calculator

# The firmware does not zero-fill the patch .bss region, so every
# variable must be initialized explicitly here.
dpm_init:
	# Push link register on stack
	stwu	%r1, -8(%r1)
	mflr	%r0
	stw	%r0, 12(%r1)

	# Torque limits start at the "no limit" sentinel
	li	%r3, DPM_TORQUE_NO_LIMIT
	lis	%r4, dpm_target_torque_reduced@ha
	sth	%r3, dpm_target_torque_reduced@l(%r4)
	lis	%r4, dpm_target_torque_upper_limit@ha
	sth	%r3, dpm_target_torque_upper_limit@l(%r4)

	# Everything else starts at 0.
	# In particular dpm_mode_index = 0: DPM stays OFF until the
	# driver explicitly enables it.
	li	%r3, 0

	# 32-bit state
	lis	%r4, dpm_slip_filter_accumulator@ha
	stw	%r3, dpm_slip_filter_accumulator@l(%r4)
	lis	%r4, dpm_slip_integral_accumulator@ha
	stw	%r3, dpm_slip_integral_accumulator@l(%r4)

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
	stb	%r3, dpm_mode_index@l(%r4)
	lis	%r4, dpm_vehicle_speed_kph@ha
	stb	%r3, dpm_vehicle_speed_kph@l(%r4)
	lis	%r4, dpm_torque_cut_factor@ha
	stb	%r3, dpm_torque_cut_factor@l(%r4)
	lis	%r4, dpm_torque_cut_accumulated@ha
	stb	%r3, dpm_torque_cut_accumulated@l(%r4)
	lis	%r4, dpm_torque_cut_total@ha
	stb	%r3, dpm_torque_cut_total@l(%r4)
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
#   dpm_slip                 = rear-over-front overspeed, 1/8% units
# Clobbers r0, r3-r10.
dpm_calc_slip:
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
	subf	%r0, %r10, %r0
	lis	%r10, dpm_front_lr_speed_diff@ha
	sth	%r0, dpm_front_lr_speed_diff@l(%r10)

	# dpm_rear_lr_speed_diff = abs(LR - RR)
	subf	%r0, %r7, %r6	# r0 = LR - RR
	srawi	%r10, %r0, 31
	xor	%r0, %r0, %r10
	subf	%r0, %r10, %r0
	lis	%r10, dpm_rear_lr_speed_diff@ha
	sth	%r0, dpm_rear_lr_speed_diff@l(%r10)

	# dpm_slip = (front_max > 0 && rear_max > front_max)
	#            ? min((rear_max * 800) / front_max - 800, 0xFFFF)
	#            : 0
	# 800 = 100% in 1/8% units; ratio, so independent of speed scale.
	li	%r0, 0
	cmplwi	%r8, 0
	beq	slip_5
	cmplw	%r9, %r8
	ble	slip_5
	mulli	%r0, %r9, 800	# max 65535*800 = 52.4M, fits in 32 bits
	divwu	%r0, %r0, %r8
	subi	%r0, %r0, 800	# >= 0 because rear_max > front_max
	cmplwi	%r0, 0xFFFF
	ble	slip_5
	li	%r0, -1		# 0xFFFF after the halfword store
slip_5:
	lis	%r10, dpm_slip@ha
	sth	%r0, dpm_slip@l(%r10)
	blr

# Calculate wheel slip from the ABS wheel speeds and derive axle maxima,
# L-R diffs and slip. Called from the main loop hook.
# TODO: port slip target, error filtering and torque cut from
# C132E0278.c:58135-58316.
dpm_slip_calculator:
	# Push link register on stack
	stwu	%r1, -8(%r1)
	mflr	%r0
	stw	%r0, 12(%r1)

	bl	dpm_calc_slip

	# Pop link register from stack
	lwz	%r0, 12(%r1)
	mtlr	%r0
	addi	%r1, %r1, 8
	blr
