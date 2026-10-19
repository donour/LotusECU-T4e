# t6patch core runtime, linked into every build.
#
# t6p_core_init is the first handler of the init hook, before any module init.
#
#  1. Zero the patch RAM [__patch_bss_start, __patch_ram_end). The firmware's
#     startup copy table is not extended, so nothing else initialises it, and
#     freeram_fill paints 0x4000F000-0x4000FE00 with 0x55 at boot.
#  2. Copy the patch cal block (CAL_extra, in cal flash) to its RAM mirror
#     CAL_base_extra. Modules read calibration as OFF_<name>(CAL_base_extra).
#
# Leaf. Clobbers r3-r6.

.section .text
.global t6p_core_init

t6p_core_init:
	lis	%r3, __patch_bss_start@ha
	addi	%r3, %r3, __patch_bss_start@l
	lis	%r4, __patch_ram_end@ha
	addi	%r4, %r4, __patch_ram_end@l
	li	%r5, 0
zero_loop:
	cmplw	%r3, %r4
	bge	zero_done
	stw	%r5, 0(%r3)
	addi	%r3, %r3, 4
	b	zero_loop
zero_done:

	lis	%r3, CAL_extra@ha
	addi	%r3, %r3, CAL_extra@l
	lis	%r4, CAL_extra_end@ha
	addi	%r4, %r4, CAL_extra_end@l
	lis	%r5, CAL_base_extra@ha
	addi	%r5, %r5, CAL_base_extra@l
copy_loop:
	cmplw	%r3, %r4
	bge	copy_done
	lwz	%r6, 0(%r3)
	stw	%r6, 0(%r5)
	addi	%r3, %r3, 4
	addi	%r5, %r5, 4
	b	copy_loop
copy_done:
	blr
