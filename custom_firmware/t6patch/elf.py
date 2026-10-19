"""Minimal reader for the 32-bit big-endian ELF files made by GNU as/ld.

Only what the patch builder needs: section headers/contents and the symbol
table. Works on both relocatable objects (.o) and linked executables.
"""

import struct
from dataclasses import dataclass

SHT_SYMTAB = 2
SHT_NOBITS = 8
SHF_ALLOC = 0x2
STB_LOCAL, STB_GLOBAL, STB_WEAK = 0, 1, 2
STT_NOTYPE, STT_OBJECT, STT_FUNC, STT_SECTION, STT_FILE = 0, 1, 2, 3, 4
SHN_UNDEF, SHN_ABS, SHN_COMMON = 0, 0xFFF1, 0xFFF2

@dataclass
class Section:
	name: str
	type: int
	flags: int
	addr: int
	size: int
	data: bytes # Empty for NOBITS sections (.bss)

	@property
	def alloc(self):
		return bool(self.flags & SHF_ALLOC)

@dataclass
class Symbol:
	name: str
	value: int
	size: int
	type: int
	bind: int
	shndx: int
	section: str # Section name, "*ABS*", "*UND*" or "*COM*"

	@property
	def defined(self):
		return self.shndx != SHN_UNDEF

class Elf:
	def __init__(self, path):
		self.path = path
		with open(path, "rb") as f: d = f.read()
		if(d[:4] != b"\x7fELF" or d[4] != 1 or d[5] != 2):
			raise ValueError(f"{path}: not a 32-bit big-endian ELF file")
		e_shoff, = struct.unpack_from(">I", d, 0x20)
		e_shentsize, e_shnum, e_shstrndx = struct.unpack_from(">HHH", d, 0x2E)
		hdrs = [struct.unpack_from(">10I", d, e_shoff + i*e_shentsize)
			for i in range(e_shnum)]

		def cstr(off):
			return d[off:d.index(b"\0", off)].decode("ascii")

		shstr_off = hdrs[e_shstrndx][4]
		self.sections = []
		for name, typ, flags, addr, off, size, *_ in hdrs:
			data = b"" if typ == SHT_NOBITS else d[off:off+size]
			self.sections.append(Section(cstr(shstr_off+name), typ, flags, addr, size, data))

		self.symbols = []
		for typ, off, size, link in ((h[1], h[4], h[5], h[6]) for h in hdrs):
			if(typ != SHT_SYMTAB): continue
			str_off = hdrs[link][4]
			for i in range(1, size // 16):
				st_name, st_value, st_size, st_info, _, st_shndx = \
					struct.unpack_from(">IIIBBH", d, off + i*16)
				if(st_shndx == SHN_UNDEF): sec = "*UND*"
				elif(st_shndx == SHN_ABS): sec = "*ABS*"
				elif(st_shndx == SHN_COMMON): sec = "*COM*"
				elif(st_shndx < len(self.sections)): sec = self.sections[st_shndx].name
				else: sec = "?"
				self.symbols.append(Symbol(cstr(str_off+st_name), st_value, st_size,
					st_info & 0xF, st_info >> 4, st_shndx, sec))

	def section(self, name):
		for s in self.sections:
			if(s.name == name): return s
		return None

	# Global definition first, then local.
	def symbol(self, name):
		found = [s for s in self.symbols if s.name == name and s.defined]
		found.sort(key=lambda s: s.bind == STB_LOCAL)
		return found[0] if found else None

	def globals_defined(self):
		return [s for s in self.symbols
			if s.bind in (STB_GLOBAL, STB_WEAK) and s.defined and s.name]
