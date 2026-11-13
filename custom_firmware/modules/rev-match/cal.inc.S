	.balign 2                           # previous modules' entries may end on an odd byte
CALENTRY CAL_rev_match_gear_ratio
	.hword 1074, 581, 427, 331, 252, 224 # rpm per rear-wheel km/h x10, 1st..6th (CAL_slip_gear_speed_ratios_cr: close ratio)
CALENTRY CAL_rev_match_decel_arm
	.hword 40                           # 0.01 g: hard braking at or above this arms (with the brake on)
CALENTRY CAL_rev_match_arm_speed_min
	.hword 4000                         # car_speed_x100 (0.01 km/h): no arming below 40 km/h
CALENTRY CAL_rev_match_pedal_max
	.hword 20                           # accel_pedal_latched (/1023) at or below this counts as released
CALENTRY CAL_rev_match_clutch_engaged
	.hword 450                          # clutch_pos_voltage (5/1023 V) below this: engaged, gear can be confirmed
CALENTRY CAL_rev_match_clutch_fire
	.hword 750                          # at or above this: clutch down (fire delay counts)
CALENTRY CAL_rev_match_clutch_end
	.hword 700                          # below this: clutch coming up, the press is over
CALENTRY CAL_rev_match_ceiling_margin
	.hword 750                          # rpm below min(revlimit_hard, revlimit_soft_target)
CALENTRY CAL_rev_match_target_min
	.hword 2500                         # rpm: no rev match to a lower target
CALENTRY CAL_rev_match_min_rise
	.hword 300                          # rpm: target must be this far above engine speed
CALENTRY CAL_rev_match_decouple_drop
	.hword 200                          # rpm: engine must be this far below the latched gear's rpm at the rear-wheel speed
CALENTRY CAL_rev_match_max_time
	.hword 300                          # 5 ms ticks (1.5 s): longest rev match
CALENTRY CAL_rev_match_enable
	.byte 0x01                          # bit 0: run (v1 is log only, it never moves the throttle)
CALENTRY CAL_rev_match_arm_time
	.byte 20                            # 5 ms ticks (100 ms) of hard braking to arm
CALENTRY CAL_rev_match_arm_hold
	.byte 60                            # 5 ms ticks (300 ms) armed after the brake is released
CALENTRY CAL_rev_match_fire_delay
	.byte 30                            # 5 ms ticks (150 ms) clutch down before firing
CALENTRY CAL_rev_match_gear_stable
	.byte 20                            # 5 ms ticks (100 ms) of one matched gear (or of none), clutch engaged, to confirm it
CALENTRY CAL_rev_match_min_target_gear
	.byte 2                             # lowest gear to rev match into
CALENTRY CAL_rev_match_coolant_min
	.byte 176                           # coolant_temp (C = v*5/8 - 40): 70 C
CALENTRY CAL_rev_match_gear_tol
	.byte 3                             # percent: engine rpm within this of a gear's rpm matches that gear
CALENTRY CAL_rev_match_fire_window
	.byte 60                            # 5 ms ticks (300 ms) after fire_delay in which a press can still fire
