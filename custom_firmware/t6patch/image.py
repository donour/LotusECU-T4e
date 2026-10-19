"""Flash images (prog / cal) with write-ownership tracking.

Every write records who made it, so two patches touching the same bytes is a
build error that names both, and the report can explain every changed byte.
"""

import hashlib, re

class PatchError(Exception):
	pass

def sha256_file(path):
	with open(path, "rb") as f: return hashlib.sha256(f.read()).hexdigest()

# Parse a GNU ld symbol script ("name = 0x1234;" lines, /* */ and # comments).
_SYM_COMMENT = re.compile(r"/\*.*?\*/", re.S)
_SYM_ASSIGN = re.compile(r"^\s*([A-Za-z_.$][\w.$]*)\s*=\s*(0[xX][0-9a-fA-F]+|\d+)\s*;", re.M)

def parse_sym_file(path):
	with open(path, "r", encoding="utf-8") as f: text = f.read()
	text = _SYM_COMMENT.sub("", text)
	text = "\n".join(l for l in text.splitlines() if not l.lstrip().startswith("#"))
	return {m[1]: int(m[2], 0) for m in _SYM_ASSIGN.finditer(text)}

class FlashImage:
	def __init__(self, name, path, base, size):
		with open(path, "rb") as f: raw = f.read()
		if(len(raw) > size):
			raise PatchError(f"{path}: {len(raw):#x} bytes, larger than the {name} region ({size:#x})")
		self.name = name
		self.path = path
		self.base = base
		self.size = size
		self.data = bytearray(raw) + b"\xFF" * (size - len(raw))
		self.original = bytes(self.data)
		self.owners = [] # (start, end, owner)

	@property
	def end(self):
		return self.base + self.size

	def _offset(self, addr, n):
		if(addr < self.base or addr + n > self.end):
			raise PatchError(f"{self.name}: {addr:#x}+{n:#x} is outside {self.base:#x}-{self.end:#x}")
		return addr - self.base

	def read(self, addr, n):
		o = self._offset(addr, n)
		return bytes(self.data[o:o+n])

	def is_blank(self, addr, n):
		return self.read(addr, n) == b"\xFF" * n

	def owner_at(self, addr):
		for s, e, who in self.owners:
			if(s <= addr < e): return who
		return None

	# Record ownership of a range without changing it.
	def claim(self, addr, n, owner):
		self._offset(addr, n)
		for s, e, who in self.owners:
			if(addr < e and s < addr + n):
				raise PatchError(f"{self.name}: {owner} ({addr:#x}-{addr+n:#x}) "
					f"overlaps {who} ({s:#x}-{e:#x})")
		self.owners.append((addr, addr + n, owner))

	# Without an owner the range must already be claimed.
	def write(self, addr, data, owner=None):
		if(owner is not None): self.claim(addr, len(data), owner)
		o = self._offset(addr, len(data))
		self.data[o:o+len(data)] = data

	def fill(self, addr, n, value=0xFF):
		o = self._offset(addr, n)
		self.data[o:o+n] = bytes([value]) * n

	# [(start, end)] address ranges that differ from the input file.
	def changed_ranges(self):
		ranges = []
		start = None
		for i, (a, b) in enumerate(zip(self.data, self.original)):
			if(a != b and start is None): start = i
			elif(a == b and start is not None):
				ranges.append((self.base + start, self.base + i))
				start = None
		if(start is not None): ranges.append((self.base + start, self.end))
		return ranges

	# Same convention as patch/build.py: drop trailing 0xFF, keep 4-byte alignment.
	def trimmed(self):
		n = len(self.data.rstrip(b"\xFF"))
		return bytes(self.data[:(n + 3) & ~3])

	def save(self, path):
		with open(path, "wb") as f: f.write(self.trimmed())
