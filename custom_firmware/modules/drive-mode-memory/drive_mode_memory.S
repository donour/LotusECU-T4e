# drive-mode-memory: keep the drive mode and the exhaust button across key
# cycles, in LEA_core_reserved. See module.toml.

.set VM_TOUR, 0
.set VM_SPORT, 1
.set VM_RACE, 3

.set DMM_LEA_BYTES, 4                       # taken from the end of LEA_core_reserved
.set DMM_SAVE, LEA_core_reserved + 1605 - DMM_LEA_BYTES
.set DMM_MODE, 0
.set DMM_EXHAUST, 1

.set EXHAUST_INPUT, 12                      # digital_input_debounced index
.set COD1_RACE, 0x0080                      # COD[1] bit 7: race mode coded
.set COD1_EXHAUST_SWITCH_HI, 0x4000         # COD[1] bit 30 (upper half): exhaust bypass override switch

.set EN_MODE, 1
.set EN_EXHAUST, 2

.section .bss
.lcomm	dmm_restored, 1, 1                  # 0: restore pending (boot, after ignition off)

.section .text
.global drive_mode_memory_5ms, drive_mode_memory_dispatch

# 200 Hz: rearm the restore while the ignition is off.
drive_mode_memory_5ms:
	lis	%r4, ignition_on_flags@ha
	lhz	%r0, ignition_on_flags@l(%r4)
	andi.	%r0, %r0, 1
	bnelr
	li	%r0, 0
	lis	%r4, dmm_restored@ha
	stb	%r0, dmm_restored@l(%r4)
	blr

# Called from set_driver_input_and_vehicle_mode_100hz in place of
# "lbz r0, vehicle_mode". r3 = this tick's button event: preserved.
# Returns r0 = vehicle_mode. Uses r4-r10, cr0.
drive_mode_memory_dispatch:
	lis	%r4, DMM_SAVE@ha
	addi	%r4, %r4, DMM_SAVE@l
	lis	%r5, vehicle_mode@ha
	lis	%r6, dmm_restored@ha
	lis	%r7, COD_base@ha
	addi	%r7, %r7, COD_base@l
	lwz	%r7, 4(%r7)                         # r7 = COD[1]
	lbz	%r0, dmm_restored@l(%r6)
	cmpwi	%r0, 0
	bne	.Ltrack

	# Restore pending. Let a button press this tick act on Tour first.
	cmpwi	%r3, 0
	bne	.Ldone
	lis	%r8, CAL_base_extra@ha
	addi	%r8, %r8, CAL_base_extra@l
	lbz	%r8, OFF_CAL_drive_mode_memory_enable(%r8)
	andi.	%r0, %r8, EN_MODE
	beq	.Lexhaust
	lbz	%r0, vehicle_mode@l(%r5)
	cmpwi	%r0, VM_TOUR
	bne	.Lexhaust                           # driver already chose a mode
	lbz	%r9, DMM_MODE(%r4)
	cmpwi	%r9, VM_SPORT
	beq	.Lset_mode
	cmpwi	%r9, VM_RACE
	bne	.Lexhaust                           # Tour, or not a valid value
	andi.	%r0, %r7, COD1_RACE
	beq	.Lexhaust                           # race mode not coded
	lis	%r10, engine_speed_2@ha
	lhz	%r0, engine_speed_2@l(%r10)
	cmpwi	%r0, 0
	beq	.Ldone                              # Race needs the engine turning: wait
.Lset_mode:
	stb	%r9, vehicle_mode@l(%r5)

.Lexhaust:
	andi.	%r0, %r8, EN_EXHAUST
	beq	.Lrestored
	andis.	%r0, %r7, COD1_EXHAUST_SWITCH_HI
	beq	.Lrestored
	lbz	%r0, DMM_EXHAUST(%r4)
	cmpwi	%r0, 1
	bne	.Lrestored
	lis	%r10, (digital_input_debounced + EXHAUST_INPUT)@ha
	stb	%r0, (digital_input_debounced + EXHAUST_INPUT)@l(%r10)   # 1; a press already made stays 1
.Lrestored:
	li	%r0, 1
	stb	%r0, dmm_restored@l(%r6)
	b	.Ldone

	# Restored: save the mode in use (Race sub-modes as Race, TC off as Tour).
.Ltrack:
	lbz	%r0, vehicle_mode@l(%r5)
	li	%r9, VM_SPORT
	cmplwi	%r0, VM_SPORT
	beq	.Lsave_mode
	li	%r9, VM_RACE
	cmplwi	%r0, VM_RACE
	bge	.Lsave_mode
	li	%r9, VM_TOUR
.Lsave_mode:
	stb	%r9, DMM_MODE(%r4)
	andis.	%r0, %r7, COD1_EXHAUST_SWITCH_HI
	beq	.Ldone
	lis	%r10, (digital_input_debounced + EXHAUST_INPUT)@ha
	lbz	%r0, (digital_input_debounced + EXHAUST_INPUT)@l(%r10)
	clrlwi	%r0, %r0, 31
	stb	%r0, DMM_EXHAUST(%r4)

.Ldone:
	lbz	%r0, vehicle_mode@l(%r5)
	blr

# EEPROM_load: leave the last DMM_LEA_BYTES of LEA_core_reserved alone.
.section .patch.drive-mode-memory.lea_reserve, "ax"
	cmplwi	%r0, 1605 - DMM_LEA_BYTES

.section .patch.drive-mode-memory.dispatch, "ax"
	bl	drive_mode_memory_dispatch
