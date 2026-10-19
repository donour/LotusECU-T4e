"""Build pipeline: recipe -> patched prog/cal images.

	1. Load target + modules, check the stock prog hash and the cal identity.
	2. Assemble every patch site's *expected* instructions at its address and
	   compare with the stock prog (catches wrong addresses / wrong firmware).
	3. Generate hook dispatchers, core-site replacements and the cal block,
	   assemble everything and link it once with a generated linker script.
	4. Write new code, site replacements and the cal block, tracking who owns
	   every changed byte (two writers on the same byte is an error).
"""

import json, os, shutil, struct, zlib
from dataclasses import dataclass, field
from . import codegen
from .config import ROOT, ConfigError, load_module, load_target
from .elf import Elf, STB_LOCAL
from .image import FlashImage, PatchError, sha256_file

CORE_DIR = os.path.join(ROOT, "core")

def align(v, a):
	return (v + a - 1) & ~(a - 1)

@dataclass
class Layout:
	rom: int
	rom_end: int
	cal: int
	cal_end: int
	ram: int
	ram_end: int

def default_layout(target):
	return Layout(
		align(target.prog.free, 16), target.prog.base + target.prog.size,
		align(target.cal.free, 16), target.cal.base + target.cal.size,
		align(target.ram_free, 16), target.ram_free + target.ram_budget)

@dataclass
class CalSite:
	key: str # Section suffix: .calsite.<key>
	addr: int # Cal flash address
	ram: int # Address the firmware (and the module) reads, in the cal RAM copy
	owner: str
	spec: object # config.ModuleCalSite (expected stock contents)
	note: str = ""

@dataclass
class Site:
	key: str # Section suffix: .patch.<key> / .expect.<key>
	addr: int
	owner: str
	expect: list # Expected original instructions (assembler text)

def _write(path, text):
	with open(path, "w", newline="\n") as f: f.write(text)

def disassemble_bytes(tc, work, addr, data):
	path = os.path.join(work, "disasm.bin")
	with open(path, "wb") as f: f.write(data)
	out = tc.run("objdump", ["-D", "-b", "binary", "-m", "powerpc:common", "-EB",
		f"--adjust-vma=0x{addr:x}", tc.path(path)])
	return [l.strip() for l in out.splitlines() if ":\t" in l]

def check_expectations(tc, work, sym_file, sites, prog, symbols):
	"""Assemble each site's expected instructions at its address and compare
	them with `prog`. Returns {key: expected bytes}."""
	src = os.path.join(work, "expect.S")
	_write(src, codegen.expect_asm([(s.key, s.expect) for s in sites], symbols))
	obj = os.path.join(work, "expect.o")
	tc.assemble(src, obj, flags=["-mregnames"])
	script = os.path.join(work, "expect.ld")
	_write(script, codegen.expect_linker_script({s.key: s.addr for s in sites}, sym_file))
	elf_path = os.path.join(work, "expect.elf")
	tc.link(script, [obj], elf_path, cwd=work)
	elf = Elf(elf_path)

	expected, errors = {}, []
	for s in sites:
		sec = elf.section(".expect." + s.key)
		if(sec is None or sec.size == 0):
			raise PatchError(f"{s.owner}: no expected instructions")
		actual = prog.read(s.addr, sec.size)
		if(actual != sec.data):
			errors.append("{:s} at 0x{:X}:\n    expected:\n      {:s}\n    found:\n      {:s}".format(
				s.owner, s.addr,
				"\n      ".join(disassemble_bytes(tc, work, s.addr, sec.data)),
				"\n      ".join(disassemble_bytes(tc, work, s.addr, actual))))
		expected[s.key] = sec.data
	if(errors):
		raise PatchError("Firmware does not match the expected instructions "
			"(wrong address in the target symbols, or a different firmware):\n  " + "\n  ".join(errors))
	return expected

def link(tc, work, sym_file, layout, objs, sites, cal_sites=()):
	script = os.path.join(work, "patch.ld")
	_write(script, codegen.linker_script(layout, {s.key: s.addr for s in sites}, sym_file,
		{s.key: s.addr for s in cal_sites}))
	elf_path = os.path.join(work, "patch.elf")
	tc.link(script, objs, elf_path, cwd=work)
	elf = Elf(elf_path)
	allowed = {".text", ".data", ".bss"} | {".patch." + s.key for s in sites} \
		| {".calsite." + s.key for s in cal_sites}
	for sec in elf.sections:
		if(sec.alloc and sec.size and sec.name not in allowed):
			raise PatchError(f"Unsupported section {sec.name} ({sec.size} bytes) in the linked patch. "
				"Code goes in .text, variables in .bss, calibration in a module cal.inc.S.")
	return elf

def apply_code(elf, sites, expected, prog):
	"""Write the new code and every site replacement into `prog`."""
	text = elf.section(".text")
	if(text is not None and text.size):
		if(not prog.is_blank(text.addr, text.size)):
			raise PatchError(f"Free prog flash at 0x{text.addr:X}+0x{text.size:X} is not blank")
		prog.write(text.addr, text.data, "patch code")
	for s in sites:
		sec = elf.section(".patch." + s.key)
		if(sec is None or sec.size == 0):
			raise PatchError(f"{s.owner}: no replacement code (section .patch.{s.key})")
		# The expected instructions may extend past the replacement: they are
		# all verified and all owned by the site, only the first ones change.
		if(sec.size > len(expected[s.key])):
			raise PatchError(f"{s.owner}: replacement is {sec.size} bytes, "
				f"longer than the {len(expected[s.key])} bytes of expected instructions")
		prog.claim(s.addr, len(expected[s.key]), s.owner)
		prog.write(s.addr, sec.data)

def apply_cal_sites(elf, cal_sites, cal, stock_cal):
	"""Module defaults for stock-cal locations. The stock cal must hold the
	declared contents there (checked against the stock image when the target
	has one, else the input cal). An input cal that still holds the stock
	contents gets the defaults; anything else is your tuning and is kept."""
	for s in cal_sites:
		sec = elf.section(".calsite." + s.key)
		if(sec is None or sec.size == 0):
			raise PatchError(f"{s.owner}: no default values (section .calsite.{s.key})")
		stock = s.spec.stock_bytes(sec.size)
		if(len(stock) != sec.size):
			raise PatchError(f"{s.owner}: expected stock contents are {len(stock)} bytes, "
				f"the defaults {sec.size}")
		ref = stock_cal or cal
		if(ref.read(s.addr, sec.size) != stock):
			raise PatchError(f"{s.owner}: the {'stock' if stock_cal else 'input'} cal at 0x{s.addr:X} "
				f"holds {ref.read(s.addr, sec.size).hex(' ')}, not the expected {stock.hex(' ')}. "
				"Is this location really unused?")
		if(cal.read(s.addr, sec.size) == stock):
			cal.write(s.addr, sec.data, s.owner)
			s.note = "default values written"
		else:
			cal.claim(s.addr, sec.size, s.owner + " (kept)")
			s.note = "kept the values already in the input cal"

def cal_layout_hash(elf, target, modules):
	data = elf.section(".data")
	entries = sorted((s.value - data.addr, s.name) for s in elf.symbols
		if s.section == ".data" and s.bind != STB_LOCAL and s.name)
	key = json.dumps([target.name, [(m.id, m.version) for m in modules], data.size, entries])
	return zlib.crc32(key.encode())

def write_cal_block(elf, target, modules, cal, reset):
	"""Write the patch cal block into `cal`. If the input cal already holds a
	block with the same layout (a previous build, maybe tuned since), its
	values are kept. Returns a short description of what happened."""
	data = elf.section(".data")
	size = elf.symbol("CAL_extra_size").value
	if(data.size != size or elf.symbol("CAL_extra").value != data.addr):
		raise PatchError("Only module cal.inc.S files may put data in the cal block "
			f"(.data is {data.size} bytes, the cal block {size})")
	block = bytearray(data.data)
	layout_hash = cal_layout_hash(elf, target, modules)
	struct.pack_into(">I", block, 8, layout_hash)

	area = target.cal.free
	area_size = cal.end - area
	existing = cal.read(data.addr, len(block))
	if(cal.is_blank(area, area_size)):
		cal.write(data.addr, block, "patch cal block")
		return layout_hash, "written with default values"
	same = existing[:8] == codegen.CAL_MAGIC and existing[8:16] == block[8:16]
	if(same and cal.is_blank(data.addr + len(block), cal.end - data.addr - len(block))
		and cal.is_blank(area, data.addr - area)):
		cal.claim(data.addr, len(block), "patch cal block (kept)")
		return layout_hash, "kept the values already in the input cal (same layout)"
	if(not reset):
		what = "an older patch cal block with a different layout" if existing[:8] == codegen.CAL_MAGIC \
			else f"non-blank data ({bytes(cal.read(area, 8))!r}...)"
		raise PatchError(f"The input cal already holds {what} at 0x{area:X}. "
			"Use --reset-patch-cal to replace it with this build's default values.")
	cal.fill(area, area_size)
	cal.write(data.addr, block, "patch cal block")
	return layout_hash, "replaced an existing block with default values (--reset-patch-cal)"

def check_cal_id(target, cal, allow_foreign):
	if(target.cal_id_address is None or not target.cal_ids): return None
	raw = cal.read(target.cal_id_address, 32).split(b"\0")[0].decode("latin-1").rstrip()
	if(raw not in target.cal_ids and not allow_foreign):
		raise ConfigError(f"Cal identifies as '{raw}', not one of the {target.name} cals "
			f"({', '.join(target.cal_ids)}). Add it to the target's [cal] ids, or use --allow-foreign-cal.")
	return raw

@dataclass
class BuildResult:
	recipe: object
	target: object
	modules: list
	out_dir: str
	layout: Layout
	prog: FlashImage
	cal: FlashImage
	elf: Elf
	sites: list
	handlers: dict
	cal_id: str
	cal_hash: int
	cal_note: str
	owners: dict = field(default_factory=dict) # Symbol -> module id / "core"
	cal_sites: list = field(default_factory=list)

def build(tc, recipe, out_dir, cal_path=None, reset_patch_cal=False, allow_foreign_cal=False, log=print):
	target = load_target(recipe.target)
	modules = [load_module(m) for m in recipe.modules]
	for m in modules: m.check_target(target)
	if("init" not in target.hooks):
		raise ConfigError(f"target {target.name} has no 'init' hook (the core runtime needs it)")

	prog_path = target.find_base(target.prog, recipe.prog)
	target.check_prog(prog_path)
	cal_path = cal_path or recipe.cal or target.find_base(target.cal)
	if(not os.path.exists(cal_path)): raise ConfigError(f"input cal {cal_path} not found")
	prog = FlashImage("prog", prog_path, target.prog.base, target.prog.size)
	cal = FlashImage("cal", cal_path, target.cal.base, target.cal.size)
	cal_id = check_cal_id(target, cal, allow_foreign_cal)
	layout = default_layout(target)

	gen = os.path.join(out_dir, "gen")
	if(os.path.isdir(gen)): shutil.rmtree(gen)
	os.makedirs(gen)
	shutil.copyfile(target.sym_path, os.path.join(gen, "symbols.sym"))
	symbols = target.symbols

	# Hook handlers, in target order; within a hook, in recipe order.
	handlers = {}
	for name in target.hooks:
		funcs = ["t6p_core_init"] if name == "init" else []
		for m in modules: funcs += m.hooks.get(name, [])
		if(funcs): handlers[name] = funcs

	sites = [Site(f"hook.{h}", target.addr(target.hooks[h].at), f"hook '{h}'",
		target.hooks[h].displaced) for h in handlers]
	core_sites = [s for s in target.core_sites if s.when_hook is None or s.when_hook in handlers]
	sites += [Site(f"core.{s.name}", target.addr(s.at), f"core site '{s.name}'", s.expect)
		for s in core_sites]
	for m in modules:
		sites += [Site(f"{m.id}.{s.name}", target.addr(s.at), f"module {m.id} site '{s.name}'",
			s.expect_for(target.name)) for s in m.sites]
	cal_sites = []
	for m in modules:
		for s in m.cal_sites:
			ram = target.addr(s.at)
			cal_sites.append(CalSite(f"{m.id}.{s.name}", target.cal_flash_addr(ram), ram,
				f"module {m.id} cal site '{s.name}'", s))

	log(f"Checking {len(sites)} patch sites against {os.path.basename(prog_path)}")
	expected = check_expectations(tc, gen, "symbols.sym", sites, prog, symbols)

	# Generated sources + core runtime.
	cal_includes = [(m.id, m.version, tc.path(os.path.join(m.dir, m.cal))) for m in modules if m.cal]
	_write(os.path.join(gen, "t6p_hooks.S"), codegen.hooks_asm(target, handlers, symbols))
	_write(os.path.join(gen, "t6p_core_sites.S"),
		codegen.replace_asm([(f"core.{s.name}", s.replace) for s in core_sites], symbols))
	_write(os.path.join(gen, "t6p_cal.S"), codegen.cal_asm(cal_includes))
	units = [(os.path.join(gen, "t6p_hooks.S"), "core", ["-mregnames"], []),
		(os.path.join(CORE_DIR, "runtime.S"), "core", [], [CORE_DIR]),
		(os.path.join(gen, "t6p_core_sites.S"), "core", ["-mregnames"], []),
		(os.path.join(gen, "t6p_cal.S"), "core", [], [])]
	for m in modules:
		units += [(os.path.join(m.dir, s), m.id, m.asflags, [m.dir, CORE_DIR]) for s in m.sources]

	log(f"Assembling {len(units)} sources")
	objs, owners = [], {}
	for i, (src, owner, flags, incs) in enumerate(units):
		obj = os.path.join(gen, f"{i:02d}_{os.path.splitext(os.path.basename(src))[0]}.o")
		tc.assemble(src, obj, flags=flags, includes=incs + [gen])
		objs.append(obj)
		o = Elf(obj)
		for s in o.globals_defined(): owners[s.name] = owner
		if(owner == "core"): continue
		m = next(m for m in modules if m.id == owner)
		declared = {f".patch.{m.id}.{s.name}" for s in m.sites} \
			| {f".calsite.{m.id}.{s.name}" for s in m.cal_sites}
		for sec in o.sections:
			if(sec.name.startswith((".patch.", ".calsite.")) and sec.name not in declared):
				raise PatchError(f"{src}: section {sec.name} is not declared in {m.id}/module.toml "
					f"(expected .patch.{m.id}.<site> or .calsite.{m.id}.<cal site>)")
		clash = sorted(s.name for s in o.globals_defined() if s.name in symbols)
		if(clash):
			raise PatchError(f"{src}: defines {', '.join(clash)}, which the target symbol file also defines")
	for m in modules:
		for h, funcs in m.hooks.items():
			for f in funcs:
				if(owners.get(f) != m.id):
					raise PatchError(f"module {m.id}: hook '{h}' handler {f} is not a global symbol of the module")

	log("Linking")
	elf = link(tc, gen, "symbols.sym", layout, objs, sites, cal_sites)
	# Cal entries are assembled in t6p_cal.S; attribute them to their module.
	by_marker = {codegen.cal_marker(m.id): m.id for m in modules}
	marks = sorted((s.value, by_marker[s.name]) for s in elf.symbols if s.name in by_marker)
	for s in elf.symbols:
		if(s.section == ".data" and s.name.startswith("CAL_")):
			mods = [m for v, m in marks if v <= s.value]
			if(mods and s.name not in ("CAL_extra", "CAL_extra_end")): owners[s.name] = mods[-1]
	apply_code(elf, sites, expected, prog)
	stock_cal = None
	if(target.cal.stock):
		stock_cal = FlashImage("stock cal", target.find_base(target.cal), target.cal.base, target.cal.size)
	apply_cal_sites(elf, cal_sites, cal, stock_cal)
	cal_hash, cal_note = write_cal_block(elf, target, modules, cal, reset_patch_cal)

	for img in (prog, cal):
		for start, end in img.changed_ranges():
			for a in range(start, end):
				if(img.owner_at(a) is None):
					raise PatchError(f"{img.name}: byte 0x{a:X} changed without an owner (pipeline bug)")

	return BuildResult(recipe, target, modules, out_dir, layout, prog, cal, elf, sites, handlers,
		cal_id, cal_hash, cal_note, owners, cal_sites)
