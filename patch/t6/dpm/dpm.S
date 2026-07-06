# Constants

.section .data

.section .bss
.global dpm_target_torque_reduced
.global dpm_torque_when_tc_activated
.global dpm_torque_cut_total
.global dpm_torque_cut_accumulated
.global dpm_slip_integral_accumulator

.section .txt
.global dpm_init


dpm_init:
	# Push link register on stack
	stwu	%r1, -8(%r1)
	mflr	%r0
	stw	%r0, 12(%r1)

    blr



