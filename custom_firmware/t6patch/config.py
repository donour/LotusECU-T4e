"""Loading and validation of targets, modules and recipes (TOML files).

	targets/<name>/target.toml   one stock firmware: images, free space, hooks
	modules/<id>/module.toml     one feature: sources, hook handlers, patch sites
	recipes/<name>.toml          a target plus an ordered list of modules
"""

import os, tomllib
from dataclasses import dataclass, field
from .image import parse_sym_file, sha256_file

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
TARGETS_DIR = os.path.join(ROOT, "targets")
MODULES_DIR = os.path.join(ROOT, "modules")
RECIPES_DIR = os.path.join(ROOT, "recipes")
BASES_DIR = os.path.join(ROOT, "bases")

class ConfigError(Exception):
	pass

def _load(path):
	try:
		with open(path, "rb") as f: return tomllib.load(f)
	except FileNotFoundError:
		raise ConfigError(f"{path} not found")
	except tomllib.TOMLDecodeError as e:
		raise ConfigError(f"{path}: {e}")

def _list(v):
	if(v is None): return []
	return [v] if isinstance(v, str) else list(v)

@dataclass
class Hook:
	name: str
	at: object # Symbol name or address
	displaced: list # Original instruction at `at`, replayed by the dispatcher
	resume: object = None # Where to continue after the dispatcher (None if `displaced` branches)
	lr_live: bool = False # LR holds a return address at the site: dispatcher saves it
	live: list = field(default_factory=list) # Volatile registers live at the site: saved around handlers
	notes: str = ""

@dataclass
class CoreSite:
	name: str
	at: object
	expect: list
	replace: list
	when_hook: str = None # Only applied when this hook is in use
	notes: str = ""

@dataclass
class Region:
	base: int
	size: int
	free: int # First free byte (patch data goes here, aligned)
	stock: str = None # File name in bases/ (or path)
	sha256: str = None

@dataclass
class Target:
	name: str
	description: str
	dir: str
	sym_path: str
	symbols: dict
	prog: Region
	cal: Region
	cal_id_address: int
	cal_ids: list
	ram_free: int
	ram_budget: int
	hooks: dict
	core_sites: list
	cal_ram_base: int = None # Where the firmware copies the cal in RAM (CAL_ symbols live there)
	cal_ram_size: int = 0

	def addr(self, at, what="address"):
		if(isinstance(at, int)): return at
		if(at not in self.symbols):
			raise ConfigError(f"target {self.name}: {what} symbol '{at}' is not defined in {self.sym_path}")
		return self.symbols[at]

	# Cal flash address of a CAL_ symbol (RAM copy address) or cal flash address.
	def cal_flash_addr(self, addr, what="address"):
		if(self.cal_ram_base is not None and self.cal_ram_base <= addr < self.cal_ram_base + self.cal_ram_size):
			return self.cal.base + addr - self.cal_ram_base
		if(self.cal.base <= addr < self.cal.base + self.cal.size):
			return addr
		raise ConfigError(f"target {self.name}: {what} 0x{addr:X} is neither in the cal RAM copy nor in cal flash")

	def find_base(self, region, override=None):
		path = override
		if(path is None):
			if(region.stock is None):
				raise ConfigError(f"target {self.name}: no stock image configured, give one explicitly")
			path = region.stock
			if(not os.path.isabs(path)):
				for d in (BASES_DIR, self.dir):
					if(os.path.exists(os.path.join(d, path))):
						path = os.path.join(d, path)
						break
		if(not os.path.exists(path)):
			raise ConfigError(f"{path} not found (put stock images in {BASES_DIR})")
		return path

	def check_prog(self, path):
		if(self.prog.sha256 and sha256_file(path) != self.prog.sha256):
			raise ConfigError(f"{path} is not the {self.name} stock prog "
				f"(sha256 {sha256_file(path)}, expected {self.prog.sha256})")

def load_target(name):
	d = os.path.join(TARGETS_DIR, name)
	t = _load(os.path.join(d, "target.toml"))
	try:
		sym_path = os.path.join(d, t.get("symbols", "symbols.sym"))
		hooks = {}
		for hname, h in t.get("hooks", {}).items():
			hooks[hname] = Hook(hname, h["at"], _list(h["displaced"]), h.get("resume"),
				h.get("lr_live", False), _list(h.get("live")), h.get("notes", ""))
		core_sites = [CoreSite(s["name"], s["at"], _list(s["expect"]), _list(s["replace"]),
			s.get("when_hook"), s.get("notes", "")) for s in t.get("core_sites", [])]
		def region(r):
			return Region(r["base"], r["size"], r["free"], r.get("stock"), r.get("sha256"))
		target = Target(t.get("name", name), t.get("description", ""), d, sym_path,
			parse_sym_file(sym_path), region(t["prog"]), region(t["cal"]),
			t["cal"].get("id_address"), _list(t["cal"].get("ids")),
			t["ram"]["free"], t["ram"]["budget"], hooks, core_sites,
			t["cal"].get("ram_base"), t["cal"].get("ram_size", 0))
	except KeyError as e:
		raise ConfigError(f"{d}/target.toml: missing key {e}")
	for h in target.hooks.values():
		target.addr(h.at, f"hook '{h.name}'")
		if(len(h.displaced) != 1):
			raise ConfigError(f"target {name}: hook '{h.name}' must displace exactly one instruction")
	for s in target.core_sites: target.addr(s.at, f"core site '{s.name}'")
	return target

@dataclass
class ModuleSite:
	name: str
	at: object
	expect: object # List of instructions, or {target: [instructions]}
	notes: str = ""

	def expect_for(self, target):
		if(isinstance(self.expect, dict)):
			if(target not in self.expect):
				raise ConfigError(f"site '{self.name}' has no expected instructions for {target}")
			return _list(self.expect[target])
		return _list(self.expect)

@dataclass
class ModuleCalSite:
	"""A location in the stock cal that the module takes over (labelled unused).
	The default contents are the module's .calsite.<id>.<name> section."""
	name: str
	at: object # CAL_ symbol (RAM copy address) or cal flash address
	stock: str = "zeros" # Expected stock contents: "zeros" or hex bytes
	notes: str = ""

	def stock_bytes(self, n):
		if(self.stock == "zeros"): return bytes(n)
		return bytes.fromhex(self.stock)

@dataclass
class Module:
	id: str
	version: int
	description: str
	dir: str
	targets: list
	sources: list
	cal: str # Calibration entries, included in the patch cal block (or None)
	asflags: list
	hooks: dict # hook name -> [handler symbols]
	sites: list
	cal_sites: list = field(default_factory=list)

	def check_target(self, target):
		if(target.name not in self.targets):
			raise ConfigError(f"module {self.id} does not support target {target.name} "
				f"(supported: {', '.join(self.targets)})")
		for h in self.hooks:
			if(h not in target.hooks):
				raise ConfigError(f"module {self.id} uses hook '{h}', which target {target.name} does not define")
		for s in self.sites:
			target.addr(s.at, f"module {self.id} site '{s.name}'")
			s.expect_for(target.name)
		for s in self.cal_sites:
			target.cal_flash_addr(target.addr(s.at, f"module {self.id} cal site '{s.name}'"),
				f"module {self.id} cal site '{s.name}'")

def load_module(mid):
	d = os.path.join(MODULES_DIR, mid)
	m = _load(os.path.join(d, "module.toml"))
	try:
		module = Module(m.get("id", mid), m["version"], m.get("description", ""), d,
			_list(m["targets"]), _list(m.get("sources")), m.get("cal"), _list(m.get("asflags")),
			{k: _list(v) for k, v in m.get("hooks", {}).items()},
			[ModuleSite(s["name"], s["at"], s["expect"], s.get("notes", ""))
				for s in m.get("sites", [])],
			[ModuleCalSite(s["name"], s["at"], s.get("stock", "zeros"), s.get("notes", ""))
				for s in m.get("cal_sites", [])])
	except KeyError as e:
		raise ConfigError(f"{d}/module.toml: missing key {e}")
	if(module.id != mid):
		raise ConfigError(f"{d}/module.toml: id '{module.id}' does not match directory name")
	for f in module.sources + _list(module.cal):
		if(not os.path.exists(os.path.join(d, f))):
			raise ConfigError(f"module {mid}: {f} not found")
	names = [s.name for s in module.sites + module.cal_sites]
	if(len(names) != len(set(names))):
		raise ConfigError(f"module {mid}: duplicate site names")
	return module

@dataclass
class Recipe:
	name: str
	path: str
	target: str
	modules: list
	cal: str = None # Input calibration (your tune); default: the target's stock cal
	prog: str = None # Stock prog override (must still match the target hash)

# `path` is a recipe file, or the name of one in recipes/ (as `list` shows it).
def load_recipe(path):
	if(not os.path.exists(path)):
		named = os.path.join(RECIPES_DIR, path if path.endswith(".toml") else path + ".toml")
		if(os.path.exists(named)): path = named
	r = _load(path)
	base = os.path.dirname(os.path.abspath(path))
	def rel(p):
		return None if p is None else os.path.normpath(os.path.join(base, p))
	try:
		recipe = Recipe(r.get("name", os.path.splitext(os.path.basename(path))[0]),
			os.path.abspath(path), r["target"], _list(r["modules"]), rel(r.get("cal")), rel(r.get("prog")))
	except KeyError as e:
		raise ConfigError(f"{path}: missing key {e}")
	if(len(recipe.modules) != len(set(recipe.modules))):
		raise ConfigError(f"{path}: a module is listed twice")
	return recipe
