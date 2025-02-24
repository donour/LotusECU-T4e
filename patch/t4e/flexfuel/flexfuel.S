.section .data
.globl CAL_ethanol_ign_advance_adj1, CAL_ethanol_ign_advance_high_cam_base, CAL_ethanol_injtip_in_adj1, CAL_ethanol_injtip_out_adj1, CAL_ethanol_inj_efficiency, CAL_ethanol_inj_time_adj3, CAL_ethanol_inj_time_adj_cranking, CAL_ethanol_ign_advance_low_cam_base

# Calibration size must be a multiple of 4
CAL_extra:
.ascii	"XTRACAL2"
CAL_ethanol_sensor_temp_reactivity:
.byte 0x02
CAL_ethanol_sensor_content_reactivity:
.byte 0x04
CAL_ethanol_sensor_engine_speed_limit:
.byte 0x70 # 4000rpm
CAL_ethanol_sensor_engine_load_limit:
.byte 0x96 # 600mg/stroke
CAL_ethanol_ign_advance_adj1:
.space 16
CAL_ethanol_ign_advance_high_cam_base:
.space 64
CAL_ethanol_injtip_in_adj1:
.space 16
CAL_ethanol_injtip_out_adj1:
.space 16
CAL_ethanol_inj_efficiency:
.space 1024
CAL_ethanol_inj_time_adj3:
.space 256
CAL_ethanol_inj_time_adj_cranking:
.space 16
CAL_ethanol_ign_advance_low_cam_base:
.space 1024
CAL_ethanol_scale_1_low:
.byte 0 # 0 %
CAL_ethanol_scale_1_high:
.byte 216 # 85 %
CAL_ethanol_scale_2_low:
.byte 12 # 5 %
CAL_ethanol_scale_2_high:
.byte 102 # 40 %
CAL_extra_end:

.section .bss
.global ethanol_temp, ethanol_content, CAL_base_extra

.lcomm	ethanol_timer,		1
.lcomm	ethanol_temp_avg,	4
.lcomm	ethanol_temp,		1 # 0 = -40°C, 255 = 120°C
.lcomm	ethanol_content_avg,	4
.lcomm	ethanol_content,	1 # 0 = 0%, 255 = 100%
.lcomm	CAL_base_extra,	(CAL_extra_end-CAL_extra) # Copy in RAM of extra CALibration.

.section .text
.globl _start, hook_init, hook_loop, hook_timer_5ms, hook_OBD_mode_0x01, hook_ign_advance_high_cam_base, hook_ign_advance_low_cam_base, hook_ign_advance_adj1, hook_inj_time_adj_cranking, hook_inj_efficiency, hook_inj_time_adj3, hook_injtip_in_adj1, hook_injtip_out_adj1

_start:
hook_init:
	bl	copy_calibration
	bl	flexfuel_init

	# Load 128 (Erase by patch in original code)
	li	%r0, 128
	ba	hook_init_continue

hook_loop:
	bl	flexfuel
	ba	hook_loop_continue

hook_timer_5ms:
	bl	flexfuel_5ms

	# Load 10 (Erase by patch in original code)
	li	%r5, 10
	ba	hook_timer_5ms_continue

hook_ign_advance_high_cam_base:
	lis	%r12, CAL_base_extra@ha
	addi	%r12, %r12, CAL_base_extra@l
	addi	%r10, %r12, (CAL_ethanol_ign_advance_high_cam_base-CAL_extra)
	lbz	%r11, (CAL_ethanol_scale_2_low-CAL_extra)(%r12)
	lbz	%r12, (CAL_ethanol_scale_2_high-CAL_extra)(%r12)
	bl	lookup_3D_uint8_interpolated_withblend
	ba	hook_ign_advance_high_cam_base_continue

hook_ign_advance_low_cam_base:
	lis	%r12, CAL_base_extra@ha
	addi	%r12, %r12, CAL_base_extra@l
	addi	%r10, %r12, (CAL_ethanol_ign_advance_low_cam_base-CAL_extra)
	lbz	%r11, (CAL_ethanol_scale_2_low-CAL_extra)(%r12)
	lbz	%r12, (CAL_ethanol_scale_2_high-CAL_extra)(%r12)
	bl	lookup_3D_uint8_interpolated_withblend
	ba	hook_ign_advance_low_cam_base_continue

hook_ign_advance_adj1:
	lis	%r9, CAL_base_extra@ha
	addi	%r9, %r9, CAL_base_extra@l
	addi	%r7, %r9, (CAL_ethanol_ign_advance_adj1-CAL_extra)
	lbz	%r8, (CAL_ethanol_scale_1_low-CAL_extra)(%r9)
	lbz	%r9, (CAL_ethanol_scale_1_high-CAL_extra)(%r9)
	bl	lookup_2D_uint8_interpolated_withblend
	ba	hook_ign_advance_adj1_continue

hook_inj_time_adj_cranking:
	lis	%r9, CAL_base_extra@ha
	addi	%r9, %r9, CAL_base_extra@l
	addi	%r7, %r9, (CAL_ethanol_inj_time_adj_cranking-CAL_extra)
	lbz	%r8, (CAL_ethanol_scale_1_low-CAL_extra)(%r9)
	lbz	%r9, (CAL_ethanol_scale_1_high-CAL_extra)(%r9)
	bl	lookup_2D_uint8_interpolated_withblend
	ba	hook_inj_time_adj_cranking_continue

hook_inj_efficiency:
	lis	%r12, CAL_base_extra@ha
	addi	%r12, %r12, CAL_base_extra@l
	addi	%r10, %r12, (CAL_ethanol_inj_efficiency-CAL_extra)
	lbz	%r11, (CAL_ethanol_scale_1_low-CAL_extra)(%r12)
	lbz	%r12, (CAL_ethanol_scale_1_high-CAL_extra)(%r12)
	bl	lookup_3D_uint8_interpolated_withblend
	ba	hook_inj_efficiency_continue

hook_inj_time_adj3:
	lis	%r12, CAL_base_extra@ha
	addi	%r12, %r12, CAL_base_extra@l
	addi	%r10, %r12, (CAL_ethanol_inj_time_adj3-CAL_extra)
	lbz	%r11, (CAL_ethanol_scale_1_low-CAL_extra)(%r12)
	lbz	%r12, (CAL_ethanol_scale_1_high-CAL_extra)(%r12)
	bl	lookup_3D_uint8_interpolated_withblend
	ba	hook_inj_time_adj3_continue

hook_injtip_in_adj1:
	lis	%r9, CAL_base_extra@ha
	addi	%r9, %r9, CAL_base_extra@l
	addi	%r7, %r9, (CAL_ethanol_injtip_in_adj1-CAL_extra)
	lbz	%r8, (CAL_ethanol_scale_1_low-CAL_extra)(%r9)
	lbz	%r9, (CAL_ethanol_scale_1_high-CAL_extra)(%r9)
	bl	lookup_2D_uint8_interpolated_withblend
	ba	hook_injtip_in_adj1_continue

hook_injtip_out_adj1:
	lis	%r9, CAL_base_extra@ha
	addi	%r9, %r9, CAL_base_extra@l
	addi	%r7, %r9, (CAL_ethanol_injtip_out_adj1-CAL_extra)
	lbz	%r8, (CAL_ethanol_scale_1_low-CAL_extra)(%r9)
	lbz	%r9, (CAL_ethanol_scale_1_high-CAL_extra)(%r9)
	bl	lookup_2D_uint8_interpolated_withblend
	ba	hook_injtip_out_adj1_continue

.if OBD_KLINE

hook_OBD_mode_0x01:
	# %r3 is the obd pid

	# Branching
	cmplwi	%r3, 0x40
	beq	OBD_mode_0x01_pid_0x40
	cmplwi	%r3, 0x46
	beq	OBD_mode_0x01_pid_0x46
	cmplwi	%r3, 0x52
	beq	OBD_mode_0x01_pid_0x52

	# Copy %r3 (Erase by patch in original code)
	or	%r31, %r3, %r3
	ba	hook_OBD_mode_0x01_continue

OBD_mode_0x01_pid_0x40:
	lis     %r4, obd_resp@ha
	addi    %r4, %r4, obd_resp@l

	# Header
	li	%r5, 0x48
	stb	%r5, 0(%r4)
	li	%r5, 0x6B
	stb	%r5, 1(%r4)
	li	%r5, 0x10
	stb	%r5, 2(%r4)
	li	%r5, 0x41
	stb	%r5, 3(%r4)
	stb	%r3, 4(%r4)

	# Available PID 0x41-0x60
	lis	%r5, 0x6EC04000@ha
	addi	%r5, %r5, 0x6EC04000@l
	stw	%r5, 5(%r4) # PID response

	li	%r5, 0xB2 # Checksum
	stb	%r5, 9(%r4)

	li	%r5, 0x09
	lis	%r3, obd_resp_length@ha
	stb	%r5, obd_resp_length@l(%r3)

	li	%r5, 0x00
	lis	%r3, obd_resp_index@ha
	stb	%r5, obd_resp_index@l(%r3)

	# Set the first byte into SCI1 Data Register
	li	%r5, 0x48
	lis	%r3, 0x030500E@ha
	sth	%r5, 0x030500E@l(%r3)

	ba	hook_OBD_mode_0x01_jump

OBD_mode_0x01_pid_0x46:
	# Fuel temperature (reported as ambiant air)
	lis	%r4, ethanol_temp@ha
	lbz	%r4, ethanol_temp@l(%r4)

	# Convert from x*5/8-40 to x-40
	# Maximal oil temp will be 120°C!
	mulli	%r4, %r4, 160
	srawi	%r4, %r4, 8
	addze	%r4, %r4

	bl	OBD_mode_0x01_send_uint8
	ba	hook_OBD_mode_0x01_jump

OBD_mode_0x01_pid_0x52:
	# Ethanol fuel %
	lis	%r4, ethanol_content@ha
	lbz	%r4, ethanol_content@l(%r4)

	bl	OBD_mode_0x01_send_uint8
	ba	hook_OBD_mode_0x01_jump

.else

hook_OBD_mode_0x01:
	# %r30 is index in obd_req
	# %r31 is index in obd_resp

	# Store current request byte in %r3
	lis	%r3, obd_req@ha
	addi	%r3, %r3, obd_req@l
	lbzx	%r3, %r3, %r30

	# Store pointer to response array in %r4
	# Store current pointer to response byte in %r5
	lis	%r4, obd_resp@ha
	addi	%r4, %r4, obd_resp@l
	add	%r5, %r4, %r31

	# Branching
	cmplwi	%r3, 0x40
	beq	OBD_mode_0x01_pid_0x40
	cmplwi	%r3, 0x46
	beq	OBD_mode_0x01_pid_0x46
	cmplwi	%r3, 0x52
	beq	OBD_mode_0x01_pid_0x52

	# Mask %r30 (Erase by patch in original code)
	rlwinm	%r0, %r30, 0,24,31
	ba	hook_OBD_mode_0x01_continue

OBD_mode_0x01_pid_0x40:
	# Available PID 0x41-0x60
	addi	%r31, %r31, 5 # Answer 5 bytes
	stb	%r3, 0(%r5)

	lis	%r3, 0x6EC04000@ha
	addi	%r3, %r3, 0x6EC04000@l
	stw	%r3, 1(%r5)

	ba	hook_OBD_mode_0x01_jump

OBD_mode_0x01_pid_0x46:
	# Fuel temperature (reported as ambiant air)
	addi	%r31, %r31, 2 # Answer 2 bytes
	stb	%r3, 0(%r5)

	lis	%r3, ethanol_temp@ha
	lbz	%r3, ethanol_temp@l(%r3)

	# Convert from x*5/8-40 to x-40
	# Maximal oil temp will be 120°C!
	mulli	%r3, %r3, 160
	srawi	%r3, %r3, 8
	addze	%r3, %r3

	stb	%r3, 1(%r5)

	ba	hook_OBD_mode_0x01_jump

OBD_mode_0x01_pid_0x52:
	# Ethanol fuel %
	addi	%r31, %r31, 2 # Answer 2 bytes
	stb	%r3, 0(%r5)

	lis	%r3, ethanol_content@ha
	lbz	%r3, ethanol_content@l(%r3)

	stb	%r3, 1(%r5)

	ba	hook_OBD_mode_0x01_jump

.endif

copy_calibration:
	# Copy extra calibration
	lis	%r3, CAL_base_extra@ha
	addi	%r3, %r3, CAL_base_extra@l
	subi	%r3, %r3, 4
	lis	%r4, CAL_extra@ha
	addi	%r4, %r4, CAL_extra@l
	subi	%r4, %r4, 4
	li	%r5, (CAL_extra_end-CAL_extra) / 4
	mtctr	%r5
copy_loop:
	lwzu	%r5, 4(%r4)
	stwu	%r5, 4(%r3)
	bdnz	copy_loop
	blr

flexfuel_init:
	# Configure MMCSMSCR (free running counter)
	li	%r3, 0x0e00
	lis	%r4, 0x306036@ha
	sth	%r3, 0x306036@l(%r4)

	# Configure MMCSMML
	li	%r3, 0x0000
	lis	%r4, 0x306032@ha
	sth	%r3, 0x306032@l(%r4)

	# Prescaler of MMCSMSCR: 256
	# Prescaler of MCPSM: 2
	# Clock: 40000000
	#
	# 40000000 / 2 / 256 = 78125

	# We cannot read the temperature and the content at the same time, so
	# we alternate the measurement.
	#
	#	100 ms reading the temperature
	#	100 ms reading the content
	#
	# The ethanol sensor update his output every 225ms.
	#
	li	%r3, 39
	lis	%r4, ethanol_timer@ha
	stb	%r3, ethanol_timer@l(%r4)

	# Start with 20°C
	li	%r3, 96
	lis	%r4, ethanol_temp@ha
	stb	%r3, ethanol_temp@l(%r4)
	mulli	%r3, %r3, 256
	lis	%r4, ethanol_temp_avg@ha
	stw	%r3, ethanol_temp_avg@l(%r4)

	# Start with 10% ethanol
	li	%r3, 25
	lis	%r4, ethanol_content@ha
	stb	%r3, ethanol_content@l(%r4)
	mulli	%r3, %r3, 256
	lis	%r4, ethanol_content_avg@ha
	stw	%r3, ethanol_content_avg@l(%r4)

	blr

flexfuel:
	# Read MIRSM1 (Reading Flag)
	lis	%r4, 0x306C40@ha
	lhz	%r3, 0x306C40@l(%r4)
	rlwinm	%r5, %r3, 17,31,31 # Mask MDA31
	cmplwi	%r5, 0
	beq	flex_end
	rlwinm	%r5, %r3, 0,17,31 # Reset Flag
	#lis	%r4, 0x306C40@ha
	sth	%r5, 0x306C40@l(%r4)

	# Engine speed limit
	lis	%r5, CAL_base_extra@ha
	addi	%r5, %r5, CAL_base_extra@l
	lbz	%r3, (CAL_ethanol_sensor_engine_speed_limit-CAL_extra)(%r5)
	lis	%r4, engine_speed_3@ha
	lbz	%r4, engine_speed_3@l(%r4)
	cmplw	%r4, %r3
	bge	flex_end

	# Engine load limit
	#lis	%r5, CAL_base_extra@ha
	#addi	%r5, %r5, CAL_base_extra@l
	lbz	%r3, (CAL_ethanol_sensor_engine_load_limit-CAL_extra)(%r5)
	lis	%r4, load_2@ha
	lbz	%r4, load_2@l(%r4)
	cmplw	%r4, %r3
	bge	flex_end

	# Read MDA31 (Ethanol temperature or content)
	lis	%r3, 0x3060F8@ha
	lwz	%r3, 0x3060F8@l(%r3)
	rlwinm	%r4, %r3, 16,16,31 # Data A
	rlwinm	%r5, %r3, 0,16,31 # Data B
	sub	%r3, %r4, %r5 # Data A-B
	# If there is an error (division by 0 or negative number)
	cmpwi	%r3, 0
	ble	flex_end

	# Read the timer
	lis	%r4, ethanol_timer@ha
	lbz	%r4, ethanol_timer@l(%r4)
	cmplwi	%r4, 20
	bge	flex_content

	# Temperature (Duty cycle: 1ms = -40°C and 5ms = 125°C)
	# temp(in °C)   = (((%r3 / 78125 * 1000) - 1ms) * 41.25) - 40
	# temp(5/8-40c) = ((((%r3 / 78125 * 1000) - 1ms) * 41.25) - 40 + 40) * 8 / 5 = (%r3 / 1.18) - 66 = (%r3 * 528 / 625) - 66
	mulli	%r3, %r3, 528
	li	%r4, 625
	divw	%r3, %r3, %r4
	subi	%r3, %r3, 66
	cmpwi	%r3, 0
	bge	flex_1
	li	%r3, 0 # Minimum is 0
flex_1:
	cmpwi	%r3, 255
	ble	flex_2
	li	%r3, 255 # Maximum is 255
flex_2:
	# Average
	#
	# avg = (avg * (256 - reactivity))/256 + (value * reactivity)
	#
	li	%r4, 256
	lis	%r5, CAL_base_extra@ha
	addi	%r5, %r5, CAL_base_extra@l
	lbz	%r5, (CAL_ethanol_sensor_temp_reactivity-CAL_extra)(%r5)
	sub	%r6, %r4, %r5
	lis	%r7, ethanol_temp_avg@ha
	lwz	%r7, ethanol_temp_avg@l(%r7)
	mullw	%r7, %r7, %r6
	divw	%r7, %r7, %r4
	mullw	%r3, %r3, %r5
	add	%r3, %r3, %r7
	lis	%r7, ethanol_temp_avg@ha
	stw	%r3, ethanol_temp_avg@l(%r7)
	divw	%r3, %r3, %r4
	lis	%r7, ethanol_temp@ha
	stb	%r3, ethanol_temp@l(%r7)
	b	flex_end

flex_content:
	# TODO: If > 160 Hz, water contamination or sensor error.

	# Ethanol Content (Freq: 50Hz = 0% and 150Hz = 100%)
	# percent(in % ) = (78125 / %r3) - 50
	# percent(1/255) = ((78125 / %r3) - 50) / 100 * 255 = (199219 / %r3) - 127
	lis	%r4, 199219@ha
	addi	%r4, %r4, 199219@l
	divw	%r3, %r4, %r3
	subi	%r3, %r3, 127
	cmpwi	%r3, 0
	bge	flex_3
	li	%r3, 0 # Minimum is 0
flex_3:
	cmpwi	%r3, 255
	ble	flex_4
	li	%r3, 255 # Maximum is 255
flex_4:
	# Average
	#
	# avg = (avg * (256 - reactivity))/256 + (value * reactivity)
	#
	li	%r4, 256
	lis	%r5, CAL_base_extra@ha
	addi	%r5, %r5, CAL_base_extra@l
	lbz	%r5, (CAL_ethanol_sensor_content_reactivity-CAL_extra)(%r5)
	sub	%r6, %r4, %r5
	lis	%r7, ethanol_content_avg@ha
	lwz	%r7, ethanol_content_avg@l(%r7)
	mullw	%r7, %r7, %r6
	divw	%r7, %r7, %r4
	mullw	%r3, %r3, %r5
	add	%r3, %r3, %r7
	lis	%r7, ethanol_content_avg@ha
	stw	%r3, ethanol_content_avg@l(%r7)
	divw	%r3, %r3, %r4
	lis	%r7, ethanol_content@ha
	stb	%r3, ethanol_content@l(%r7)
flex_end:
	blr

flexfuel_5ms:
	# Increment the timer every 5ms
	lis	%r4, ethanol_timer@ha
	lbz	%r5, ethanol_timer@l(%r4)
	addi	%r5, %r5, 1
	# At 200ms reset the timer
	cmplwi	%r5, 40
	blt	timer_1
	li	%r5, 0
timer_1:
	#lis	%r4, ethanol_timer@ha
	stb	%r5, ethanol_timer@l(%r4)

	# At 0ms configure for temperature
	cmplwi	%r5, 0
	bne	timer_2
	# Configure MDA31 for pulse width measurement (ethanol temperature)
	li	%r3, 0x0001
	b	timer_3
timer_2:
	# At 100ms configure for content
	cmplwi	%r5, 20
	bne	timer_4
	# Configure MDA31 for period measurement (ethanol content)
	li	%r3, 0x0002
timer_3:
	# When changing mode, it's imperative to go through the DIS mode.
	li	%r5, 0
	lis	%r4, 0x3060FE@ha
	sth	%r5, 0x3060FE@l(%r4)
	# Reset MDA31 Flag
	#lis	%r4, 0x306C40@ha
	lhz	%r5, 0x306C40@l(%r4)
	rlwinm	%r5, %r5, 0,17,31 # Reset Flag
	#lis	%r4, 0x306C40@ha
	sth	%r5,  0x306C40@l(%r4)
	# Change to the desired mode
	#lis	%r4, 0x3060FE@ha
	sth	%r3, 0x3060FE@l(%r4)
timer_4:
	blr

# Params:
#	r3 : value for ethanol
#	r4 : value for gasoline
#	r5 : ethanol scale low (E0 = 0, E5 = 12 or E10 = 25)
#	r6 : ethanol scale high (E40 = 102, E85 = 216 or E100 = 255)
#
#	scale_high -= scale_low
#	ethanol_content -= scale_low
#	result = (%r3 * ethanol_content + %r4 * (scale_high - ethanol_content)) / scale_high
fuelblend:
	lis	%r7, ethanol_content@ha
	lbz	%r7, ethanol_content@l(%r7)
	cmplw	%r7, %r5
	ble	only_gas
	cmplw	%r7, %r6
	bge	only_eth
	sub	%r6, %r6, %r5
	sub	%r7, %r7, %r5
	sub	%r8, %r6, %r7
	mullw	%r3, %r3, %r7
	mullw	%r4, %r4, %r8
	add	%r3, %r3, %r4
	divw	%r3, %r3, %r6
only_eth:
	blr
only_gas:
	mr	%r3, %r4
	blr

# Params:
#	r3 : size_x
#	r4 : input_x
#	r5 : lut
#	r6 : x_axis
#
#	r7: lut ethanol
#	r8: ethanol scale low
#	r9: ethanol scale high
lookup_2D_uint8_interpolated_withblend:
	# Push link register on stack (4 bytes alignment, normally 16)
	stwu	%r1, -24(%r1)
	mflr	%r0
	stw	%r0, 28(%r1)

	# Save arguments on stack
	stb	%r3 ,  8(%r1)
	stb	%r4 ,  9(%r1)
	stw	%r7 , 10(%r1)
	stw	%r6 , 14(%r1)
	stb	%r8 , 19(%r1)
	stb	%r9 , 20(%r1)

	# 1st call and save result on stack
	bla	lookup_2D_uint8_interpolated
	stb	%r3,  18(%r1)

	# 2nd call with ethanol table
	lbz	%r3,  8(%r1)
	lbz	%r4,  9(%r1)
	lwz	%r5, 10(%r1)
	lwz	%r6, 14(%r1)
	bla	lookup_2D_uint8_interpolated

	# Both result are in %r3 and %r4
	lbz	%r4, 18(%r1)
	lbz	%r5, 19(%r1)
	lbz	%r6, 20(%r1)
	bl	fuelblend

	# Pop link register from stack
	lwz	%r0, 28(%r1)
	mtlr	%r0
	addi	%r1, %r1, 24
	blr

# Params:
#	r3 : size_x
#	r4 : size_y
#	r5 : input_x
#	r6 : input_y
#	r7 : lut
#	r8 : x_axis
#	r9 : y_axis
#
#	r10: lut ethanol
#	r11: ethanol scale low
#	r12: ethanol scale high
lookup_3D_uint8_interpolated_withblend:
	# Push link register on stack (4 bytes alignment, normally 16)
	stwu	%r1, -28(%r1)
	mflr	%r0
	stw	%r0, 32(%r1)

	# Save arguments on stack
	stb	%r3 ,  8(%r1)
	stb	%r4 ,  9(%r1)
	stb	%r5 , 10(%r1)
	stb	%r6 , 11(%r1)
	stw	%r10, 12(%r1)
	stw	%r8 , 16(%r1)
	stw	%r9 , 20(%r1)
	stb	%r11, 25(%r1)
	stb	%r12, 26(%r1)

	# 1st call and save result on stack
	bla	lookup_3D_uint8_interpolated
	stb	%r3,  24(%r1)

	# 2nd call with ethanol table
	lbz	%r3,  8(%r1)
	lbz	%r4,  9(%r1)
	lbz	%r5, 10(%r1)
	lbz	%r6, 11(%r1)
	lwz	%r7, 12(%r1)
	lwz	%r8, 16(%r1)
	lwz	%r9, 20(%r1)
	bla	lookup_3D_uint8_interpolated

	# Both result are in %r3 and %r4
	lbz	%r4, 24(%r1)
	lbz	%r5, 25(%r1)
	lbz	%r6, 26(%r1)
	bl	fuelblend

	# Pop link register from stack
	lwz	%r0, 32(%r1)
	mtlr	%r0
	addi	%r1, %r1, 28
	blr

