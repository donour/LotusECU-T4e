#!/usr/bin/python3

import sys, os

class SUM_HC08_T4e():
	def __init__(self, polynomial=0x1021, initvalue=0x0123):
		self.table = [0] * 256
		for i in range(0,256):
			c = i << 8
			for j in range(0,8):
				c = polynomial ^ (c << 1) if (c & 0x8000) else c << 1
			self.table[i] = c & 0xFFFF
		self.initvalue = initvalue
		self.reset()
	def reset(self):
		self.crc = self.initvalue
	def update_byte(self, byte):
		# CRC16 Normal: self.crc = self.table[(self.crc >> 8) ^ byte] ^ (self.crc << 8)
		self.crc = (self.crc << 8) ^ self.table[self.crc >> 8] ^ (byte + 0xAA)
		self.crc &= 0xFFFF
	def update(self, data):
		for byte in data: self.update_byte(byte)
	def get(self):
		return self.crc

class SUM_HC08_T6():
	def __init__(self, initvalue=0x0123):
		self.initvalue = initvalue
		self.reset()
	def reset(self):
		self.crc = self.initvalue
	def update_byte(self, byte):
		self.crc = (0xFF00 | ~byte) + self.crc
		self.crc &= 0xFFFF
	def update(self, data):
		for byte in data: self.update_byte(byte)
	def get(self):
		return self.crc

if __name__ == "__main__":
	print("HC08 Checksum tool for Lotus T4e/T6 ECU\n")

	if(len(sys.argv) >= 2):
		with open(sys.argv[1], 'rb') as f:	
			data = f.read()
			if(data[0x1FE0:0x1FE8] == b'HC08CODE'):
				off = int.from_bytes(data[0x1FEC:0x1FF0], 'big')-0x20000
				cksum = SUM_HC08_T4e()
				cksum.update(data[off       :off+0x2000])
				cksum.update(data[off+0x23DC:off+0x2400])
				print("Checksum T4e: 0x{:04X}".format(cksum.get()))
			elif(data[0x80:0x88] == b'HC08CODE'):
				off = int.from_bytes(data[0x8C:0x90], 'big')-0x40000
				cksum = SUM_HC08_T6()
				cksum.update(data[off       :off+0x2000])
				cksum.update(data[off+0x23DC:off+0x2400])
				print("Checksum T6 : 0x{:04X}".format(cksum.get()))
			else:
				print("HC08 code not found!")
	else:
		prog = os.path.basename(sys.argv[0])
		print("usage:")
		print(f"\t{prog} PROG")

