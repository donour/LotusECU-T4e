# torque-4nm: torque limit tables in 4 Nm steps. See module.toml.

.set TORQUE_NO_LIMIT, 911	# Nm; a limit at or above this is no limit

# throttle_and_torque_control: table value -> Nm.
.section .patch.torque-4nm.by_rpm, "ax"
	slwi	%r0, %r0, 2

.section .patch.torque-4nm.coolant, "ax"
	slwi	%r0, %r0, 2

.section .patch.torque-4nm.no_limit, "ax"
	cmplwi	%r0, TORQUE_NO_LIMIT
