# aem30-0310: AEM 30-0310 X-Series inline wideband controller (Bosch LSU 4.9)
# on any of the four O2 inputs. See module.toml for the sites.
#
# The controller's 0-5 V analog output (White = Analog +, Brown = Analog -)
# replaces a narrow-band sensor's signal. Its transfer function is fixed (the
# factory resistor-trim calibration):
#   AFR (gasoline) = 2.3750 * V + 7.3125
#   Lambda         = 0.1621 * V + 0.4990
# Below 0.5 V the controller reports "sensor not ready", above 4.5 V "sensor
# error".
#
# Each channel (pre/post-cat, bank 1/2) is detected on its own, from valid
# wideband readings: above 2.5 V and at most 4.5 V. A working narrow-band
# sensor never gets above ~1 V and one shorted to voltage reads above 4.5 V,
# so neither counts. For the first 5 s after ignition on, the ECU is fed
# stoichiometric (0.45 V), the heater current limit is 3 A, and the valid
# readings (one sample per 5 ms) are counted. At the end of the window:
#  - >= 100 ms of them: wideband. The heater limit stays at 3 A and the
#    reading is re-encoded as a simulated narrow-band signal (<= 14.4 AFR ->
#    0.9 V, >= 15.0 AFR -> 0.1 V, inverted ramp in between). Below 0.5 V (not
#    ready) or above 4.5 V (sensor error) the reading is invalid and the ECU
#    is fed stoichiometric.
#  - otherwise: narrow-band. The stock heater limit is restored and the input
#    is passed through, so a faulty narrow-band sensor still sets the stock
#    DTCs, except 1.5-4.5 V: no narrow-band sensor reads that, but a wideband
#    controller not detected yet does, so the ECU is fed stoichiometric
#    instead. The channel keeps being watched: 100 ms in a row of
#    valid readings (a controller that was still warming up during the
#    window) switches it to wideband.
# A wideband channel stays wideband until the ignition is off. The window
# restarts while the ignition is off: the controller is powered by the rear
# ignition relay, not the main relay.
#
# There is no startup calibration sequence: the slope/offset correction stays
# at identity (kept so the OBD correction PIDs can report it later).

# Constants for narrow-band simulation
.set WB_RICH,  611 # (14.4 AFR - 7.3125) / 2.375 * 1023 / 5 = 610.57
.set WB_LEAN,  662 # (15.0 AFR - 7.3125) / 2.375 * 1023 / 5 = 662.26
.set NB_RICH,  184 # 0.90 V * 1023 / 5 = 184.14
.set NB_LEAN,   20 # 0.10 V * 1023 / 5 =  20.46
.set NB_STOI,   92 # 0.45 V * 1023 / 5 =  92.07

# Valid range: below 0.5 V the AEM is not ready, above 4.5 V it reports a
# sensor error. Outside it we fall back to a simulated stoichiometric signal.
.set WB_LO,  103 # First count at or above 0.50 V (0.50 V * 1023 / 5 = 102.30)
.set WB_HI,  920 # Last count at or below 4.50 V (4.50 V * 1023 / 5 = 920.70)

# Highest narrow-band reading passed through below WB_HI. Above a working
# sensor's ~1 V and the stock O2 high-voltage DTC limit (245 counts = 1.2 V in
# the B13200091 and C132E0278 cals), so readings that set that DTC still do.
.set NB_MAX, 307 # 1.50 V * 1023 / 5 = 306.90

# O2 inputs in the ADC DMA buffer
.set ADC_PRE_B1,  (adc_dma_dest+44)
.set ADC_PRE_B2,  (adc_dma_dest+46)
.set ADC_POST_B1, (adc_dma_dest+48)
.set ADC_POST_B2, (adc_dma_dest+50)

# Detection: valid readings above 2.5 V (and at most WB_HI) for 100 ms in total
# during the first 5 s, or for 100 ms in a row after it.
.set WB_DETECT, 512 # 2.50 V * 1023 / 5 = 511.50
.set WB_WINDOW, (5000/5) # 1000 samples = 5 s at 5 ms per call
.set WB_DET_SAMPLES, (100/5) # 20 samples = 100 ms of valid readings to qualify as WB

# Default identity correction (no startup calibration sequence).
.set WB_SLOPE_DEFAULT,  4096 # 1.0 in u16_factor_1/4096
.set WB_OFFSET_DEFAULT,    0 # i16_voltage_5/1023v

# Allow up to 3 A for the wideband heater.
.set WB_MAX_I, 3000

# Channel state. 0..WB_WINDOW-1 is the sampling window, at the end of which it
# becomes either ST_WB or ST_NB. ST_NB can still become ST_WB later; ST_WB is
# kept until the ignition is off.
.set ST_WB, 2001 # Wideband with narrow-band simulation
.set ST_NB, 2002 # Narrow-band passthrough

# Channel struct, 12 bytes
.set ch_state,     0 # 0..WB_WINDOW = sampling window, ST_WB, ST_NB
.set ch_det_cnt,   2 # Valid readings above 2.5 V: in total in the window, in a row after it
.set ch_slope,     4 # Correction slope, u16_factor_1/4096
.set ch_offset,    6 # Correction offset, i16_voltage_5/1023v
.set ch_corr_adc,  8 # u16_voltage_5/1023v with correction !
.set ch_ht_th,    10 # u16_current_mA, read by the heater check (sites)
.set CH_SIZE,     12

.section .bss
.balign 4
.global aem_pre_b1, aem_pre_b2, aem_post_b1, aem_post_b2
.type aem_pre_b1, @object
.type aem_pre_b2, @object
.type aem_post_b1, @object
.type aem_post_b2, @object
aem_pre_b1:	.skip	CH_SIZE
aem_pre_b2:	.skip	CH_SIZE
aem_post_b1:	.skip	CH_SIZE
aem_post_b2:	.skip	CH_SIZE
.size aem_pre_b1, CH_SIZE
.size aem_pre_b2, CH_SIZE
.size aem_post_b1, CH_SIZE
.size aem_post_b2, CH_SIZE

# Corrected controller output of each channel, for CCP / memory-peek logging
# (addresses in symbols.txt). Lambda = 0.4990 + adc * 0.8105 / 1023.
# 0 until the channel is detected as wideband.
.global aem_pre_b1_adc, aem_pre_b2_adc, aem_post_b1_adc, aem_post_b2_adc
.set aem_pre_b1_adc,  aem_pre_b1 + ch_corr_adc
.set aem_pre_b2_adc,  aem_pre_b2 + ch_corr_adc
.set aem_post_b1_adc, aem_post_b1 + ch_corr_adc
.set aem_post_b2_adc, aem_post_b2 + ch_corr_adc
.size aem_pre_b1_adc, 2
.size aem_pre_b2_adc, 2
.size aem_post_b1_adc, 2
.size aem_post_b2_adc, 2

.section .text
.global aem_init, aem_loop, aem_5ms

# Param r3 is pointer to channel struct
# Every channel starts in the sampling window. A per-channel mode in the patch
# cal (possible future change, see module.toml) would pick ST_WB or a stock
# narrow-band state here instead.
aem_init_channel:
	# Start of the sampling window
	li	%r4, 0
	sth	%r4, ch_state(%r3)
	# Clear the wideband detection counter
	#li	%r4, 0
	sth	%r4, ch_det_cnt(%r3)
	# Identity correction (no calibration sequence)
	li	%r4, WB_SLOPE_DEFAULT
	sth	%r4, ch_slope(%r3)
	li	%r4, WB_OFFSET_DEFAULT
	sth	%r4, ch_offset(%r3)
	# Set 0 for wideband value
	li	%r4, 0
	sth	%r4, ch_corr_adc(%r3)
	# Allow more current to be drawn during the window in case a wideband is
	# wired; restored to the stock threshold only if a narrow-band is decided.
	li	%r4, WB_MAX_I
	sth	%r4, ch_ht_th(%r3)
	blr

aem_init:
	# Push link register on stack
	stwu	%r1, -8(%r1)
	mflr	%r0
	stw	%r0, 12(%r1)

	lis	%r3, aem_pre_b1@ha
	addi	%r3, %r3, aem_pre_b1@l
	bl	aem_init_channel

	lis	%r3, aem_pre_b2@ha
	addi	%r3, %r3, aem_pre_b2@l
	bl	aem_init_channel

	lis	%r3, aem_post_b1@ha
	addi	%r3, %r3, aem_post_b1@l
	bl	aem_init_channel

	lis	%r3, aem_post_b2@ha
	addi	%r3, %r3, aem_post_b2@l
	bl	aem_init_channel

	# Pop link register from stack
	lwz	%r0, 12(%r1)
	mtlr	%r0
	addi	%r1, %r1, 8
	blr

# Param r3 is pointer to channel struct
# Param r4 is input adc value
# Return r3 as simulated narrow-band
aem_channel:
	lhz	%r5, ch_state(%r3)
	cmplwi	%r5, ST_WB
	beq	aem_wide
	cmplwi	%r5, ST_NB
	beq	aem_narrow
aem_stoich:
	# Simulate stoichiometric during the sampling window
	li	%r3, NB_STOI
	b	aem_out
aem_narrow:
	# Narrow-band: pass the input through, except 1.5-4.5 V. That is a
	# wideband controller not detected yet (up to 100 ms before
	# aem_5ms_channel switches the channel, or reading rich), so simulate
	# stoichiometric. Above 4.5 V passes, so a sensor shorted to voltage
	# still sets the stock DTC.
	srawi	%r3, %r4, 4
	cmplwi	%r3, NB_MAX
	ble	aem_out
	cmplwi	%r3, WB_HI
	ble	aem_stoich
	b	aem_out
aem_wide:
	# Wideband with narrow-band simulation
	srawi	%r4, %r4, 4
	lhz	%r5, ch_slope(%r3)
	mullw	%r4, %r4, %r5
	srwi	%r4, %r4, 12
	lha	%r5, ch_offset(%r3)
	add	%r4, %r4, %r5
	# Be sure to be positive
	cmpwi	%r4, 0
	bge	aem_positive
	li	%r4, 0
aem_positive:
	# Save corrected wideband for OBD request
	sth	%r4, ch_corr_adc(%r3)
	# Below 0.5 V the controller is not ready, above 4.5 V in sensor error:
	# simulate stoichiometric instead.
	cmplwi	%r4, WB_LO
	blt	aem_stoich
	cmplwi	%r4, WB_HI
	bgt	aem_stoich
	# If AFR is less/equal 14.4 then simulate a NB of 0.9v
	cmplwi	%r4, WB_RICH
	bgt	aem_not_rich
	li	%r3, NB_RICH
	b	aem_out
aem_not_rich:
	# If AFR is greater/equal 15.0 then simulate a NB of 0.1v
	cmplwi	%r4, WB_LEAN
	blt	aem_ramp
	li	%r3, NB_LEAN
	b	aem_out
aem_ramp:
	# If AFR is between 14.4-15.0 then compress and inverse the signal
	# r3 = NB_RICH - (r4 - WB_RICH) * (NB_RICH-NB_LEAN) / (WB_LEAN-WB_RICH)
	# Use reciprocal division
	subi	%r4, %r4, WB_RICH
	mulli	%r4, %r4, (NB_RICH-NB_LEAN)
	mulli	%r4, %r4, ((1<<20)/(WB_LEAN-WB_RICH))
	srwi	%r4, %r4, 20
	subfic	%r3, %r4, NB_RICH
aem_out:
	blr

# Main loop: write each channel's (simulated) narrow-band value where the
# firmware's own O2 sampling would have (skipped by the adc_skip_* sites).
aem_loop:
	# Push link register on stack
	stwu	%r1, -8(%r1)
	mflr	%r0
	stw	%r0, 12(%r1)

	lis	%r3, aem_pre_b1@ha
	addi	%r3, %r3, aem_pre_b1@l
	lis	%r4, ADC_PRE_B1@ha
	lhz	%r4, ADC_PRE_B1@l(%r4)
	bl	aem_channel
	lis	%r4, sensor_adc_pre_O2_bank1@ha
	sth	%r3, sensor_adc_pre_O2_bank1@l(%r4)

	lis	%r3, aem_pre_b2@ha
	addi	%r3, %r3, aem_pre_b2@l
	lis	%r4, ADC_PRE_B2@ha
	lhz	%r4, ADC_PRE_B2@l(%r4)
	bl	aem_channel
	lis	%r4, sensor_adc_pre_O2_bank2@ha
	sth	%r3, sensor_adc_pre_O2_bank2@l(%r4)

	lis	%r3, aem_post_b1@ha
	addi	%r3, %r3, aem_post_b1@l
	lis	%r4, ADC_POST_B1@ha
	lhz	%r4, ADC_POST_B1@l(%r4)
	bl	aem_channel
	lis	%r4, sensor_adc_post_O2_bank1@ha
	sth	%r3, sensor_adc_post_O2_bank1@l(%r4)

	lis	%r3, aem_post_b2@ha
	addi	%r3, %r3, aem_post_b2@l
	lis	%r4, ADC_POST_B2@ha
	lhz	%r4, ADC_POST_B2@l(%r4)
	bl	aem_channel
	lis	%r4, sensor_adc_post_O2_bank2@ha
	sth	%r3, sensor_adc_post_O2_bank2@l(%r4)

	# Pop link register from stack
	lwz	%r0, 12(%r1)
	mtlr	%r0
	addi	%r1, %r1, 8
	blr

# Param r3 is pointer to channel struct
# Param r4 is input adc value
aem_5ms_channel:
	# Reset and exit if ignition is off because the controller is wired to
	# the rear ignition relay and not the main relay.
	lis	%r5, ignition_on_flags@ha
	lhz	%r5, ignition_on_flags@l(%r5)
	rlwinm.	%r5, %r5, 0, 31, 31
	bne	aem_ign_on
	b	aem_init_channel
aem_ign_on:
	lhz	%r5, ch_state(%r3)
	# Narrow-band: keep watching for a controller that was not ready in the
	# window.
	cmplwi	%r5, ST_NB
	beq	aem_late
	# Otherwise only act during the initial sampling window.
	cmplwi	%r5, WB_WINDOW
	ble	aem_sample
	blr
aem_sample:
	# Sample: count the valid wideband readings, above 2.5 V and at most
	# 4.5 V. A narrow-band sensor shorted to voltage reads above 4.5 V.
	srawi	%r4, %r4, 4
	cmplwi	%r4, WB_DETECT
	ble	aem_tick
	cmplwi	%r4, WB_HI
	bgt	aem_tick
	lhz	%r6, ch_det_cnt(%r3)
	addi	%r6, %r6, 1
	sth	%r6, ch_det_cnt(%r3)
aem_tick:
	# Advance the window timer.
	addi	%r5, %r5, 1
	# Keep sampling until the 5 s window elapses.
	cmplwi	%r5, WB_WINDOW
	bne	aem_store_state
	# End of window: decide narrow-band vs wideband.
	lhz	%r6, ch_det_cnt(%r3)
	cmplwi	%r6, WB_DET_SAMPLES
	bge	aem_is_wide
	# Narrow-band sensor: restore the stock heater threshold.
	lis	%r6, CAL_sensor_O2_heater_threshold@ha
	lhz	%r6, CAL_sensor_O2_heater_threshold@l(%r6)
	sth	%r6, ch_ht_th(%r3)
	# Restart the counter for aem_late (in a row from now on).
	li	%r6, 0
	sth	%r6, ch_det_cnt(%r3)
	li	%r5, ST_NB
	b	aem_store_state
aem_is_wide:
	# Enough valid readings: wideband, keep the raised heater limit.
	li	%r5, ST_WB
aem_store_state:
	sth	%r5, ch_state(%r3)
	blr

# Narrow-band channel after the window: 100 ms in a row of valid readings is a
# controller that was still warming up during the window. Switch to wideband.
aem_late:
	srawi	%r4, %r4, 4
	li	%r6, 0
	cmplwi	%r4, WB_DETECT
	ble	aem_late_store
	cmplwi	%r4, WB_HI
	bgt	aem_late_store
	lhz	%r6, ch_det_cnt(%r3)
	addi	%r6, %r6, 1
	cmplwi	%r6, WB_DET_SAMPLES
	blt	aem_late_store
	# Wideband: raise the heater limit, then change the state.
	li	%r6, WB_MAX_I
	sth	%r6, ch_ht_th(%r3)
	li	%r5, ST_WB
	sth	%r5, ch_state(%r3)
	blr
aem_late_store:
	sth	%r6, ch_det_cnt(%r3)
	blr

# 200 Hz: detection.
aem_5ms:
	# Push link register on stack
	stwu	%r1, -8(%r1)
	mflr	%r0
	stw	%r0, 12(%r1)

	lis	%r3, aem_pre_b1@ha
	addi	%r3, %r3, aem_pre_b1@l
	lis	%r4, ADC_PRE_B1@ha
	lhz	%r4, ADC_PRE_B1@l(%r4)
	bl	aem_5ms_channel

	lis	%r3, aem_pre_b2@ha
	addi	%r3, %r3, aem_pre_b2@l
	lis	%r4, ADC_PRE_B2@ha
	lhz	%r4, ADC_PRE_B2@l(%r4)
	bl	aem_5ms_channel

	lis	%r3, aem_post_b1@ha
	addi	%r3, %r3, aem_post_b1@l
	lis	%r4, ADC_POST_B1@ha
	lhz	%r4, ADC_POST_B1@l(%r4)
	bl	aem_5ms_channel

	lis	%r3, aem_post_b2@ha
	addi	%r3, %r3, aem_post_b2@l
	lis	%r4, ADC_POST_B2@ha
	lhz	%r4, ADC_POST_B2@l(%r4)
	bl	aem_5ms_channel

	# Pop link register from stack
	lwz	%r0, 12(%r1)
	mtlr	%r0
	addi	%r1, %r1, 8
	blr

# ---- Patch sites (declared in module.toml) ----------------------------------

# O2 heater current limits: read ch_ht_th from the channel struct instead of
# CAL_sensor_O2_heater_threshold, so it can be 3 A for a wideband.
.section .patch.aem30-0310.heater_threshold_pre_b1, "ax"
	lis	%r3, aem_pre_b1@ha
	addi	%r3, %r3, aem_pre_b1@l
	lhz	%r0, ch_ht_th(%r3)

.section .patch.aem30-0310.heater_threshold_pre_b2, "ax"
	lis	%r3, aem_pre_b2@ha
	addi	%r3, %r3, aem_pre_b2@l
	lhz	%r0, ch_ht_th(%r3)

.section .patch.aem30-0310.heater_threshold_post_b1, "ax"
	lis	%r3, aem_post_b1@ha
	addi	%r3, %r3, aem_post_b1@l
	lhz	%r0, ch_ht_th(%r3)

.section .patch.aem30-0310.heater_threshold_post_b2, "ax"
	lis	%r3, aem_post_b2@ha
	addi	%r3, %r3, aem_post_b2@l
	lhz	%r0, ch_ht_th(%r3)

# Skip the firmware's write to sensor_adc_<pre|post>_O2_bankN (6 instructions):
# aem_loop writes it instead.
.section .patch.aem30-0310.adc_skip_pre_b1, "ax"
	b	.+0x18

.section .patch.aem30-0310.adc_skip_pre_b2, "ax"
	b	.+0x18

.section .patch.aem30-0310.adc_skip_post_b1, "ax"
	b	.+0x18

.section .patch.aem30-0310.adc_skip_post_b2, "ax"
	b	.+0x18
