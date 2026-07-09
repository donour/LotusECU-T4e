.section .text
.global hook_init, hook_loop, hook_timer_5ms
.ifdef DPM
.global hook_arbitration_dpm
.endif

hook_init:
	bl	copy_calibration
.ifdef FLEXFUEL
	bl	flexfuel_init
.endif
.ifdef WIDEBAND
	bl	wideband_init
.endif
.ifdef DPM
	bl	dpm_init
.endif
	# Pop link register from stack (Erase by patch in original code)
	lwz	%r0, 20(%r1)
	ba	hook_init_continue

hook_loop:
.ifdef FLEXFUEL
	bl	flexfuel
.endif
.ifdef WIDEBAND
	bl	wideband
.endif
.ifdef DPM
	bl	dpm_slip_calculator
.endif
	ba	hook_loop_continue

hook_timer_5ms:
.ifdef FLEXFUEL
	bl	flexfuel_5ms
.endif
.ifdef WIDEBAND
	bl	wideband_5ms
.endif
.ifdef DPM
	bl	dpm_system_state_manager_200hz
.endif
	# Load 10 (Erase by patch in original code)
	li	%r0, 10
	ba	hook_timer_5ms_continue


.ifdef DPM
# Hook at the end of torque_limit_request_arbitration (0x000b46c4).
# Replaces the original blr.  At this point the arbitration has already
# selected the winning source and stored spark/throttle limits in:
#   torque_limit_external_request      (fast/spark, address TBD)
#   torque_external_request_tps_based  (slow/throttle, address TBD)
# and set torque_limit_source_flags to the winning source bits.
#
# This hook applies DPM's limit as a min() override: if DPM is actively
# cutting AND DPM's limit is tighter than the arbitration result, DPM's
# limit replaces it.  It also sets bit 0x02 (ABS) in source_flags when
# DPM is cutting, ensuring the torque_model master gate sees a non-zero
# source even when ABS/TCU are idle.
#
# Leaf (no calls): reuses the caller's LR.  Clobbers r0, r3-r6.
hook_arbitration_dpm:
	# Guard: if DPM is not cutting, return immediately.
	lis	%r3, dpm_control_flags@ha
	lhz	%r3, dpm_control_flags@l(%r3)
	andi.	%r3, %r3, 0x0002
	beq	arb_dpm_done

	# --- spark / fast channel ---
	lis	%r3, dpm_torque_limit_spark@ha
	lhz	%r3, dpm_torque_limit_spark@l(%r3)	# r3 = DPM spark

	# TODO: verify torque_limit_external_request address
	# Load the arbitrated fast limit.  Keep base in r5, value in r4.
	lis	%r5, torque_limit_external_request@ha
	lhz	%r4, torque_limit_external_request@l(%r5)	# r4 = arbitrated (r5 = base)

	cmplw	%r3, %r4
	bge	arb_dpm_throttle			# DPM >= arbitrated -> skip
	sth	%r3, torque_limit_external_request@l(%r5)	# DPM tighter -> override

arb_dpm_throttle:
	# --- throttle / slow channel ---
	lis	%r3, dpm_torque_limit_throttle@ha
	lhz	%r3, dpm_torque_limit_throttle@l(%r3)	# r3 = DPM throttle

	# TODO: verify torque_external_request_tps_based address
	lis	%r5, torque_external_request_tps_based@ha
	lhz	%r4, torque_external_request_tps_based@l(%r5)	# r4 = arbitrated (r5 = base)

	cmplw	%r3, %r4
	bge	arb_dpm_flags				# DPM >= arbitrated -> skip
	sth	%r3, torque_external_request_tps_based@l(%r5)	# DPM tighter -> override

arb_dpm_flags:
	# Ensure the torque_model master gate sees a non-zero source.
	lis	%r4, torque_limit_source_flags@ha
	lbz	%r3, torque_limit_source_flags@l(%r4)
	ori	%r3, %r3, 0x02			# set ABS bit
	stb	%r3, torque_limit_source_flags@l(%r4)

arb_dpm_done:
	blr
.endif
