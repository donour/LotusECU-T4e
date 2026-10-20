# federal-gt: run the GT430 (C132E0278) firmware on a Federal Evora GT.
# See module.toml for the sites.

.set VM_DPM_ACTIVE, 6		# enum_vehicle_mode
.set CRUISE_ACCEL,  2		# enum_cruise_switch_pos
.set CRUISE_COAST,  3
.set DI_DPM_UP,     0xB		# digital_input_debounced index of the DPM + button
.set DI_DPM_DOWN,   0xD		# and of the DPM - button

.section .text
.global federal_gt_dpm_buttons, federal_gt_dpm_display

# Called in place of dpm_mode_button_handler by
# dpm_system_state_manager_200hz, which calls it only while DPM is taking
# button input. In DPM mode the cruise stalk works the DPM buttons:
#   ACCEL -> digital_input_debounced[DI_DPM_UP]
#   COAST -> digital_input_debounced[DI_DPM_DOWN]
# A debounced input only changes on an edge of its pin, and these pins are
# not connected on the Federal car, so both are written on every call. Outside
# DPM mode they read released.
# Tail-calls dpm_mode_button_handler. Clobbers r0, r3-r5.
federal_gt_dpm_buttons:
	li	%r3, 0				# r3 = DPM up
	li	%r5, 0				# r5 = DPM down
	lis	%r4, vehicle_mode@ha
	lbz	%r0, vehicle_mode@l(%r4)
	cmplwi	%r0, VM_DPM_ACTIVE
	bne	fgt_buttons_store
	lis	%r4, cruise_switch_pos@ha
	lbz	%r0, cruise_switch_pos@l(%r4)
	cmplwi	%r0, CRUISE_ACCEL
	bne	fgt_buttons_coast
	li	%r3, 1
fgt_buttons_coast:
	cmplwi	%r0, CRUISE_COAST
	bne	fgt_buttons_store
	li	%r5, 1
fgt_buttons_store:
	lis	%r4, digital_input_debounced@ha
	addi	%r4, %r4, digital_input_debounced@l
	stb	%r3, DI_DPM_UP(%r4)
	stb	%r5, DI_DPM_DOWN(%r4)
	b	dpm_mode_button_handler

# Called in place of flexcan_a_tx_403(fuel_range_remaining,
# fuel_economy_instantaneous, fuel_economy_avg, dpm_index) by
# cluster_data_send_100ms. In DPM mode the frame carries DPM state in the
# fuel fields instead (the scaling of the original hand patch):
#   range (r3)         = (dpm_mode_index * 1675 + 1023) >> 10
#   instantaneous (r4) = dpm_slip
#   average (r5)       = (dpm_slip_target * 544 + 8) >> 3
# The fuel variables themselves are not changed.
# Tail-calls flexcan_a_tx_403. Clobbers r0, r7.
federal_gt_dpm_display:
	lis	%r7, vehicle_mode@ha
	lbz	%r0, vehicle_mode@l(%r7)
	cmplwi	%r0, VM_DPM_ACTIVE
	bne	fgt_display_send
	lis	%r7, dpm_mode_index@ha
	lbz	%r0, dpm_mode_index@l(%r7)
	mulli	%r3, %r0, 1675
	addi	%r3, %r3, 1023
	srwi	%r3, %r3, 10
	lis	%r7, dpm_slip@ha
	lha	%r4, dpm_slip@l(%r7)
	lis	%r7, dpm_slip_target@ha
	lhz	%r0, dpm_slip_target@l(%r7)
	mulli	%r5, %r0, 544
	addi	%r5, %r5, 8
	srwi	%r5, %r5, 3
fgt_display_send:
	b	flexcan_a_tx_403

# vin_flags, VIN[6] test: 'D' in place of 'R', variant nibble 4 in place of 3.
.section .patch.federal-gt.vin7_D, "ax"
	cmplwi	%r0, 0x44			# 'D'
	bne	vin_flags_vin7_S
	li	%r4, 4

# ...and no main_diagnostic_flags bit 2.
.section .patch.federal-gt.vin7_D_no_diag, "ax"
	nop

# flexcan_a_tx_403: byte 4 cleared, DLC 4.
.section .patch.federal-gt.tx_403_dlc4, "ax"
	li	%r0, 0
	stb	%r0, 0(%r7)
	li	%r4, 4

.section .patch.federal-gt.dpm_buttons, "ax"
	bl	federal_gt_dpm_buttons

.section .patch.federal-gt.dpm_display, "ax"
	bl	federal_gt_dpm_display
