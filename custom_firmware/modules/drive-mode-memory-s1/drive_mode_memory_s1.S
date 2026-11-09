# drive-mode-memory-s1: keep Sport (and optionally TC off) across key cycles
# on the S1 NA, in LEA_core_reserved. See module.toml.

.set DMM_LEA_BYTES, 4                       # taken from the end of LEA_core_reserved
.set DMM_SAVE, LEA_core_reserved + 1610 - DMM_LEA_BYTES
.set DMM_SPORT, 0
.set DMM_TC_OFF, 1

.set IN_SPORT, 3                            # digital_input_debounced index (toggle)
.set IN_TC_OFF, 6                           # digital_input_debounced index (toggle)

.set ESP_ALIVE, 0x20                        # abs_esp_can_torque_request_flags: CAN 0xA8 arriving

.set EN_SPORT, 1                            # CAL_drive_mode_memory_s1_enable
.set EN_TC_OFF, 2

.set DONE_SPORT, 1                          # dmm_restored
.set DONE_TC_OFF, 2

.section .bss
.lcomm	dmm_restored, 1, 1                  # 0: restores pending (boot, after ignition off)

.section .text
.global drive_mode_memory_s1_5ms, drive_mode_memory_s1_ign_off

# 200 Hz.
drive_mode_memory_s1_5ms:
	# Ignition on: the conditions under which the firmware zeroes neither input.
	lis	%r4, ign_voltage_above_threshold@ha
	lbz	%r0, ign_voltage_above_threshold@l(%r4)
	cmpwi	%r0, 0
	beq	.Loff
	lis	%r4, CAL_ecu_ign_threshold@ha
	lbz	%r0, CAL_ecu_ign_threshold@l(%r4)
	slwi	%r0, %r0, 2
	lis	%r4, sensor_adc_ign_voltage@ha
	lhz	%r3, sensor_adc_ign_voltage@l(%r4)
	cmplw	%r3, %r0
	blt	.Loff

	lis	%r4, DMM_SAVE@ha
	addi	%r4, %r4, DMM_SAVE@l
	lis	%r5, digital_input_debounced@ha
	addi	%r5, %r5, digital_input_debounced@l
	lis	%r6, dmm_restored@ha
	lbz	%r7, dmm_restored@l(%r6)
	lis	%r8, CAL_base_extra@ha
	addi	%r8, %r8, CAL_base_extra@l
	lbz	%r8, OFF_CAL_drive_mode_memory_s1_enable(%r8)

	# Sport: restore once, then save.
	andi.	%r0, %r7, DONE_SPORT
	beq	.Lsport_restore
	lbz	%r0, IN_SPORT(%r5)
	clrlwi	%r0, %r0, 31
	stb	%r0, DMM_SPORT(%r4)
	b	.Ltc_off
.Lsport_restore:
	ori	%r7, %r7, DONE_SPORT
	andi.	%r0, %r8, EN_SPORT
	beq	.Ltc_off
	lbz	%r0, DMM_SPORT(%r4)
	cmpwi	%r0, 1
	bne	.Ltc_off                            # off, or not a valid value
	stb	%r0, IN_SPORT(%r5)                  # 1; a press already made stays 1

	# TC off: restore once the ESP is talking, then save.
.Ltc_off:
	andi.	%r0, %r7, DONE_TC_OFF
	beq	.Ltc_off_restore
	lbz	%r0, IN_TC_OFF(%r5)
	clrlwi	%r0, %r0, 31
	stb	%r0, DMM_TC_OFF(%r4)
	b	.Lstore
.Ltc_off_restore:
	andi.	%r0, %r8, EN_TC_OFF
	beq	.Ltc_off_done
	lbz	%r0, DMM_TC_OFF(%r4)
	cmpwi	%r0, 1
	bne	.Ltc_off_done
	lis	%r9, abs_esp_can_torque_request_flags@ha
	lhz	%r9, abs_esp_can_torque_request_flags@l(%r9)
	andi.	%r9, %r9, ESP_ALIVE
	beq	.Lstore                             # wait for the ESP
	stb	%r0, IN_TC_OFF(%r5)
.Ltc_off_done:
	ori	%r7, %r7, DONE_TC_OFF
.Lstore:
	stb	%r7, dmm_restored@l(%r6)
	blr

.Loff:
	li	%r0, 0
	lis	%r4, dmm_restored@ha
	stb	%r0, dmm_restored@l(%r4)
	blr

# shutdown(), ignition off: called in place of digital_inputs_zero.
drive_mode_memory_s1_ign_off:
	li	%r0, 0
	lis	%r4, dmm_restored@ha
	stb	%r0, dmm_restored@l(%r4)
	b	digital_inputs_zero

# EEPROM_load: leave the last DMM_LEA_BYTES of LEA_core_reserved alone.
.section .patch.drive-mode-memory-s1.lea_reserve, "ax"
	cmplwi	%r0, 1610 - DMM_LEA_BYTES

.section .patch.drive-mode-memory-s1.ign_off, "ax"
	bl	drive_mode_memory_s1_ign_off
