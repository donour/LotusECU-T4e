# race TC hook handlers that used to live inline in patch/t6/combined/hook.S
# (20260706/s1_dpm, a15fc67), now ordinary functions called by the t6patch
# hook dispatchers.

.section .text
.global race_tc_dash_display, race_tc_torque_arbitration_filter

# tpms_frame_packed handler (cluster_send_data, 10 Hz): show race TC on the dash's
# tyre-pressure display while race TC is on.
#
# Only the outgoing CAN 0x402 frame (tpms_output) is rewritten; the TPMS data
# itself (tpms_pressure, tire_pressure_valid_and_error), the TPMS warning
# light and OBD PIDs 0x215/0x216 are untouched. With race_tc_mode_index == 0 the
# frame is left as the firmware packed it, so a working TPMS displays normally.
#
# The frame is the one v1 (then named dpm) produced by overwriting the TPMS inputs, so the
# dash reads the same as before:
#   p0, p1 = (race_tc_slip_target * 5) >> 4   (slip target, 1/8% * 2.5)
#   p2, p3 = race_tc_mode_index * 2.5
#   tpms_output[0..3] = p0, p2, p1, p3, each << 1 (the firmware's packing)
#   tpms_output[4] low nibble (per-tyre OK) = 0, as packed from flags 0x0200
#   with CAL_tpms_version == 0.
# Leaf. Clobbers r3-r6.
race_tc_dash_display:
	lis	%r3, race_tc_mode_index@ha
	lbz	%r6, race_tc_mode_index@l(%r3)
	cmplwi	%r6, 0
	beqlr					# race TC off: leave the real TPMS frame
	lis	%r4, tpms_output@ha
	addi	%r4, %r4, tpms_output@l
	# Front = slip target * 5/16, then the firmware's << 1
	lis	%r3, race_tc_slip_target@ha
	lhz	%r3, race_tc_slip_target@l(%r3)
	slwi	%r5, %r3, 2			# r5 = x * 4
	add	%r5, %r5, %r3			# r5 = (x * 4) + x = x * 5
	srawi	%r3, %r5, 4
	slwi	%r3, %r3, 1			# stb keeps the low byte, as the firmware's u8 shift
	stb	%r3, 0(%r4)			# p0
	stb	%r3, 2(%r4)			# p1
	# Rear = mode * 2.5, then << 1
	slwi	%r5, %r6, 1			# *2
	srwi	%r3, %r6, 1			# /2
	add	%r3, %r5, %r3			# *2.5
	slwi	%r3, %r3, 1
	stb	%r3, 1(%r4)			# p2
	stb	%r3, 3(%r4)			# p3
	# Per-tyre OK flags clear. With CAL_tpms_version != 0 the firmware does
	# not pack byte 4 (0x59D28), so neither do we.
	lis	%r3, CAL_tpms_version@ha
	lbz	%r3, CAL_tpms_version@l(%r3)
	cmplwi	%r3, 0
	bnelr
	lbz	%r3, 4(%r4)
	rlwinm	%r3, %r3, 0, 24, 27
	stb	%r3, 4(%r4)
	blr

# torque_arbitration_exit handler: runs at the end of
# torque_limit_request_arbitration, after it has selected the winning source
# and stored the spark/throttle limits in:
#   torque_limit_external_request      (fast/spark)
#   torque_external_request_tps_based  (slow/throttle)
# and set torque_limit_source_flags to the winning source bits.
#
# Applies race TC's limit as a min() override: if race TC is actively cutting AND
# race TC's limit is tighter than the arbitration result, race TC's limit replaces it.
# It also sets bit 0x02 (ABS) in source_flags when race TC is cutting, so the
# torque_model master gate sees a non-zero source even when ABS/TCU are idle.
#
# Leaf. Clobbers r3-r5.
race_tc_torque_arbitration_filter:
	# Guard: if race TC is not cutting, return immediately.
	lis	%r3, race_tc_control_flags@ha
	lhz	%r3, race_tc_control_flags@l(%r3)
	andi.	%r3, %r3, 0x0002
	beq	arb_race_tc_done

	# --- spark / fast channel ---
	lis	%r3, race_tc_torque_limit_spark@ha
	lhz	%r3, race_tc_torque_limit_spark@l(%r3)	# r3 = race TC spark

	# TODO: verify torque_limit_external_request address
	# Load the arbitrated fast limit.  Keep base in r5, value in r4.
	lis	%r5, torque_limit_external_request@ha
	lhz	%r4, torque_limit_external_request@l(%r5)	# r4 = arbitrated (r5 = base)

	cmplw	%r3, %r4
	bge	arb_race_tc_throttle			# race TC >= arbitrated -> skip
	sth	%r3, torque_limit_external_request@l(%r5)	# race TC tighter -> override

arb_race_tc_throttle:
	# --- throttle / slow channel ---
	lis	%r3, race_tc_torque_limit_throttle@ha
	lhz	%r3, race_tc_torque_limit_throttle@l(%r3)	# r3 = race TC throttle

	# TODO: verify torque_external_request_tps_based address
	lis	%r5, torque_external_request_tps_based@ha
	lhz	%r4, torque_external_request_tps_based@l(%r5)	# r4 = arbitrated (r5 = base)

	cmplw	%r3, %r4
	bge	arb_race_tc_flags				# race TC >= arbitrated -> skip
	sth	%r3, torque_external_request_tps_based@l(%r5)	# race TC tighter -> override

arb_race_tc_flags:
	# Ensure the torque_model master gate sees a non-zero source.
	lis	%r4, torque_limit_source_flags@ha
	lbz	%r3, torque_limit_source_flags@l(%r4)
	ori	%r3, %r3, 0x02			# set ABS bit
	stb	%r3, torque_limit_source_flags@l(%r4)

arb_race_tc_done:
	blr
