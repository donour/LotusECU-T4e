"""Minimal PowerPC interpreter for testing patch code on the host.

Runs functions of a linked patch (t6patch.elf.Elf) against a sparse,
zero-filled memory: 32-bit big-endian, user-level integer instructions only,
no CTR, no interrupts. It implements what the modules use so far; anything
else raises NotImplementedError, so extend it as modules need more.
"""

import struct

M32 = 0xFFFFFFFF

def sx16(v):
	return v - 0x10000 if v & 0x8000 else v

def s32(v):
	v &= M32
	return v - (1 << 32) if v & 0x80000000 else v

def rotl(v, n):
	v &= M32
	return ((v << n) | (v >> (32 - n))) & M32 if n else v

def mask(mb, me):
	m = 0
	for i in range(32):
		if((mb <= me and mb <= i <= me) or (mb > me and (i >= mb or i <= me))): m |= 1 << (31 - i)
	return m

class CPU:
	RETURN = 0xFFFFFFF0 # LR on entry: returning here ends call()
	STACK = 0x4000FF00
	LIMIT = 100000 # Instructions per call

	def __init__(self, elf):
		text = elf.section(".text")
		self.text_addr, self.text = text.addr, text.data
		self.symbols = {s.name: s.value for s in elf.symbols if s.name}
		self.mem = {}
		self.r = [0] * 32
		self.cr = 0
		self.lr = 0
		self.stubs = {} # address -> fn(cpu): firmware functions the patch calls, run in Python

	def rd16(self, a):
		return (self.mem.get(a, 0) << 8) | self.mem.get(a + 1, 0)

	def wr16(self, a, v):
		self.mem[a] = (v >> 8) & 0xFF
		self.mem[a + 1] = v & 0xFF

	def rd32(self, a):
		return (self.rd16(a) << 16) | self.rd16(a + 2)

	def wr32(self, a, v):
		self.wr16(a, (v >> 16) & 0xFFFF)
		self.wr16(a + 2, v & 0xFFFF)

	def _cmp(self, field, a, b):
		bits = 8 if a < b else 4 if a > b else 2
		sh = 28 - 4 * field
		self.cr = (self.cr & ~(0xF << sh)) | (bits << sh)

	def call(self, func, *args):
		"""Call `func` (symbol or address) with args in r3...; returns r3."""
		for i, a in enumerate(args): self.r[3 + i] = a & M32
		self.r[1] = self.STACK
		self.lr = self.RETURN
		pc = self.symbols[func] if isinstance(func, str) else func
		for _ in range(self.LIMIT):
			if(pc == self.RETURN): return self.r[3]
			if(pc in self.stubs):
				self.stubs[pc](self)
				pc = self.lr
				continue
			off = pc - self.text_addr
			if(not 0 <= off < len(self.text)): raise RuntimeError(f"pc 0x{pc:X} outside the patch code")
			ins = struct.unpack(">I", self.text[off:off + 4])[0]
			pc = self._step(pc, ins)
		raise RuntimeError(f"{func}: more than {self.LIMIT} instructions")

	def _step(self, pc, ins):
		r = self.r
		op = ins >> 26
		D, A, B = (ins >> 21) & 31, (ins >> 16) & 31, (ins >> 11) & 31
		imm = ins & 0xFFFF
		ea = ((0 if A == 0 else r[A]) + sx16(imm)) & M32
		if(op == 14): r[D] = ea                                     # addi, li
		elif(op == 15): r[D] = ((0 if A == 0 else r[A]) + (sx16(imm) << 16)) & M32  # addis, lis
		elif(op == 7): r[D] = (s32(r[A]) * sx16(imm)) & M32         # mulli
		elif(op == 8): r[D] = (sx16(imm) - s32(r[A])) & M32         # subfic
		elif(op == 24): r[A] = r[D] | imm                           # ori, nop
		elif(op == 25): r[A] = r[D] | (imm << 16)                   # oris
		elif(op == 10): self._cmp(D >> 2, r[A], imm)                # cmplwi
		elif(op == 11): self._cmp(D >> 2, s32(r[A]), sx16(imm))     # cmpwi
		elif(op == 32): r[D] = self.rd32(ea)                        # lwz
		elif(op == 40): r[D] = self.rd16(ea)                        # lhz
		elif(op == 42): r[D] = sx16(self.rd16(ea)) & M32            # lha
		elif(op == 36 or op == 37):                                 # stw, stwu
			self.wr32(ea, r[D])
			if(op == 37): r[A] = ea
		elif(op == 44): self.wr16(ea, r[D] & 0xFFFF)                # sth
		elif(op == 46):                                             # lmw
			for i in range(D, 32): r[i] = self.rd32((ea + 4 * (i - D)) & M32)
		elif(op == 47):                                             # stmw
			for i in range(D, 32): self.wr32((ea + 4 * (i - D)) & M32, r[i])
		elif(op == 34): r[D] = self.mem.get(ea, 0)                  # lbz
		elif(op == 38): self.mem[ea] = r[D] & 0xFF                  # stb
		elif(op == 28 or op == 29):                                 # andi., andis.
			r[A] = r[D] & (imm if op == 28 else imm << 16)
			self._cmp(0, s32(r[A]), 0)
		elif(op == 21):                                             # rlwinm[.]
			r[A] = rotl(r[D], B) & mask((ins >> 6) & 31, (ins >> 1) & 31)
			if(ins & 1): self._cmp(0, s32(r[A]), 0)
		elif(op == 18):                                             # b, bl, ba, bla
			li = ins & 0x03FFFFFC
			if(li & 0x02000000): li -= 0x04000000
			if(ins & 1): self.lr = pc + 4
			return (li if ins & 2 else pc + li) & M32
		elif(op == 16):                                             # bc (no CTR)
			if(not D & 4): raise NotImplementedError(f"bc with CTR at 0x{pc:X}")
			bd = ins & 0xFFFC
			if(bd & 0x8000): bd -= 0x10000
			if(ins & 3): raise NotImplementedError(f"bca/bcl at 0x{pc:X}")
			if(D & 16 or ((self.cr >> (31 - A)) & 1) == ((D >> 3) & 1)): return (pc + bd) & M32
		elif(op == 19 and ((ins >> 1) & 0x3FF) == 16 and not ins & 1):  # blr, b<cond>lr (no CTR)
			if(not D & 4): raise NotImplementedError(f"bclr with CTR at 0x{pc:X}")
			if(D & 16 or ((self.cr >> (31 - A)) & 1) == ((D >> 3) & 1)): return self.lr
		elif(op == 31):
			xo = (ins >> 1) & 0x3FF
			spr = ((B << 5) | A) if xo in (339, 467) else None
			xea = ((0 if A == 0 else r[A]) + r[B]) & M32              # indexed EA
			if(xo == 824): r[A] = (s32(r[D]) >> B) & M32             # srawi
			elif(xo == 0): self._cmp(D >> 2, s32(r[A]), s32(r[B]))   # cmpw
			elif(xo == 32): self._cmp(D >> 2, r[A], r[B])            # cmplw
			elif(xo == 235): r[D] = (s32(r[A]) * s32(r[B])) & M32    # mullw
			elif(xo == 266): r[D] = (r[A] + r[B]) & M32              # add
			elif(xo == 40): r[D] = (r[B] - r[A]) & M32               # subf
			elif(xo == 459):                                         # divwu
				if(r[B] == 0): raise NotImplementedError(f"divwu by 0 at 0x{pc:X}")
				r[D] = r[A] // r[B]
			elif(xo == 444):                                         # or, mr, or., mr.
				r[A] = r[D] | r[B]
				if(ins & 1): self._cmp(0, s32(r[A]), 0)
			elif(xo == 279): r[D] = self.rd16(xea)                   # lhzx
			elif(xo == 407): self.wr16(xea, r[D] & 0xFFFF)           # sthx
			elif(xo == 339 and spr == 8): r[D] = self.lr             # mflr
			elif(xo == 467 and spr == 8): self.lr = r[D]             # mtlr
			else: raise NotImplementedError(f"{ins:08X} (op 31, xo {xo}) at 0x{pc:X}")
		else:
			raise NotImplementedError(f"{ins:08X} (op {op}) at 0x{pc:X}")
		return pc + 4
