# hc08-tps: HC08 throttle monitor TPS limit vs rpm table. See module.toml.

# HC08 checksum: from 0x0123, subtract (byte + 1) for every byte of the image
# it covers (HC08 0xDC00-0xFBFF and 0xFFDC-0xFFFF), mod 0x10000. The table
# is covered, so each count it rises lowers the checksum by one.
.set HC08_CHECKSUM_STOCK, 0xDA01
.set hc08_tps_raised, 0		# Sum of (value - stock) over the table

# One table entry, as % * 255 / 100. The HC08 limit may only be raised.
.macro tps_entry stock, value
	.if (\value) < (\stock)
	.error "hc08-tps: an entry is below the stock HC08 table"
	.endif
	.byte	\value
	.set	hc08_tps_raised, hc08_tps_raised + (\value) - (\stock)
.endm

.section .patch.hc08-tps.table, "ax"
	# rpm axis (rpm * 8 / 255), unchanged
	.byte	0x19, 0x1f, 0x27, 0x2f, 0x37, 0x3f, 0x4e, 0x5e, 0x6e, 0x7d, 0x8d, 0x9c, 0xac, 0xbb, 0xcb, 0xdb
	#		stock	value		   rpm
	tps_entry	0x8d,	0x8d		#  797
	tps_entry	0xa4,	0xa4		#  988
	tps_entry	0xb7,	0xb7		# 1243
	tps_entry	0xce,	0xce		# 1498
	tps_entry	0xd4,	0xd9		# 1753
	tps_entry	0xd4,	0xd9		# 2008
	tps_entry	0xd5,	0xe6		# 2486
	tps_entry	0xd5,	0xf2		# 2996
	tps_entry	0xb4,	0xf2		# 3506
	tps_entry	0xa9,	0xf2		# 3984
	tps_entry	0xb6,	0xf2		# 4494
	tps_entry	0xcc,	0xf2		# 4973
	tps_entry	0xe4,	0xf2		# 5483
	tps_entry	0xff,	0xff		# 5961
	tps_entry	0xff,	0xff		# 6471
	tps_entry	0xff,	0xff		# 6981

.set HC08_CHECKSUM, (HC08_CHECKSUM_STOCK - hc08_tps_raised) & 0xFFFF

# HC08_check_CRC: hc08_crc16 == HC08_CHECKSUM. lis 1 + addi + clrlwi 16
# gives the 16-bit value for any checksum, with the immediate sign-extended.
.section .patch.hc08-tps.checksum, "ax"
	lis	%r3, hc08_crc16@ha
	lhz	%r0, hc08_crc16@l(%r3)
	clrlwi	%r4, %r0, 16
	lis	%r3, 1
	addi	%r3, %r3, (HC08_CHECKSUM ^ 0x8000) - 0x8000
