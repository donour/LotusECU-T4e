"""t6patch command line.

	python -m t6patch build s1-race-tc [--stages] [--cal FILE]
	python -m t6patch check B13200091
	python -m t6patch list
"""

import argparse, dataclasses, os, shutil, sys
from .config import (ROOT, TARGETS_DIR, MODULES_DIR, RECIPES_DIR, ConfigError,
	load_module, load_recipe, load_target)
from .image import FlashImage, PatchError
from .pipeline import Site, build, check_expectations
from .toolchain import Toolchain, ToolError
from .output import write_outputs

def cmd_build(args):
	tc = Toolchain()
	recipe = load_recipe(args.recipe)
	out = os.path.abspath(args.out or os.path.join(ROOT, "build", recipe.name))
	jobs = []
	if(args.stages):
		for i in range(1, len(recipe.modules)):
			mods = recipe.modules[:i]
			stage = dataclasses.replace(recipe, name=f"{recipe.name}-stage{i:02d}", modules=mods)
			jobs.append((stage, os.path.join(out, "stages", f"{i:02d}-{'+'.join(mods)}")))
	jobs.append((recipe, out))
	for r, d in jobs:
		print(f"== {r.name}: {r.target} [{', '.join(r.modules) or 'no modules'}] -> {d}")
		os.makedirs(d, exist_ok=True)
		res = build(tc, r, d, cal_path=args.cal, reset_patch_cal=args.reset_patch_cal,
			allow_foreign_cal=args.allow_foreign_cal, log=lambda s: print("   " + s))
		write_outputs(tc, res)
		text = res.elf.section(".text")
		ram = res.elf.symbol("__patch_ram_end").value - res.layout.ram
		print(f"   code {text.size} bytes @0x{text.addr:X}, RAM {ram}/{res.target.ram_budget} bytes, "
			f"cal block {res.elf.section('.data').size} bytes ({res.cal_note})")
		print(f"   wrote prog.bin, calrom.bin, {r.name}.crp, report.md")

def cmd_check(args):
	tc = Toolchain()
	t = load_target(args.target)
	path = t.find_base(t.prog)
	t.check_prog(path)
	prog = FlashImage("prog", path, t.prog.base, t.prog.size)
	sites = [Site(f"hook.{h.name}", t.addr(h.at), f"hook '{h.name}'", h.displaced) for h in t.hooks.values()]
	sites += [Site(f"core.{s.name}", t.addr(s.at), f"core site '{s.name}'", s.expect) for s in t.core_sites]
	work = os.path.join(ROOT, "build", f"check-{t.name}")
	os.makedirs(work, exist_ok=True)
	shutil.copyfile(t.sym_path, os.path.join(work, "symbols.sym"))
	check_expectations(tc, work, "symbols.sym", sites, prog, t.symbols)
	for s in sites: print(f"  ok  0x{s.addr:06X}  {s.owner}")
	end = t.prog.base + t.prog.size
	print(f"  {'ok' if prog.is_blank(t.prog.free, end - t.prog.free) else 'NOT BLANK'}"
		f"  free prog flash 0x{t.prog.free:X}-0x{end:X}")
	if(t.cal.stock):
		cal = FlashImage("cal", t.find_base(t.cal), t.cal.base, t.cal.size)
		end = t.cal.base + t.cal.size
		print(f"  {'ok' if cal.is_blank(t.cal.free, end - t.cal.free) else 'NOT BLANK'}"
			f"  free cal flash 0x{t.cal.free:X}-0x{end:X} (stock cal)")
	print(f"{t.name}: {len(sites)} sites match the stock prog")

def cmd_list(args):
	def names(d, ext=None):
		if(not os.path.isdir(d)): return []
		if(ext): return sorted(f[:-len(ext)] for f in os.listdir(d) if f.endswith(ext))
		return sorted(f for f in os.listdir(d) if os.path.isdir(os.path.join(d, f)))
	print("Targets:")
	for n in names(TARGETS_DIR):
		t = load_target(n)
		print(f"  {n:12s} {t.description}  hooks: {', '.join(t.hooks)}")
	print("Modules:")
	for n in names(MODULES_DIR):
		m = load_module(n)
		print(f"  {n:12s} v{m.version}  targets: {', '.join(m.targets)}  {m.description}")
	print("Recipes:")
	for n in names(RECIPES_DIR, ".toml"):
		r = load_recipe(os.path.join(RECIPES_DIR, n + ".toml"))
		print(f"  {n:24s} {r.target}: {' -> '.join(r.modules)}")

def main(argv=None):
	p = argparse.ArgumentParser(prog="t6patch", description="Build patched Lotus T6 ECU firmware.")
	sub = p.add_subparsers(dest="cmd", required=True)
	b = sub.add_parser("build", help="build a recipe")
	b.add_argument("recipe", help="recipe name (see `list`) or .toml file")
	b.add_argument("--out", help="output directory (default build/<recipe name>)")
	b.add_argument("--stages", action="store_true",
		help="also build each prefix of the module list (for bisecting on the car)")
	b.add_argument("--cal", help="input calibration (overrides the recipe's cal)")
	b.add_argument("--reset-patch-cal", action="store_true",
		help="replace an existing patch cal block in the input cal with default values")
	b.add_argument("--allow-foreign-cal", action="store_true",
		help="accept a cal whose id string is not listed in the target")
	c = sub.add_parser("check", help="check a target's hook and core sites against its stock prog")
	c.add_argument("target")
	sub.add_parser("list", help="list targets, modules and recipes")
	args = p.parse_args(argv)
	try:
		{"build": cmd_build, "check": cmd_check, "list": cmd_list}[args.cmd](args)
	except (ConfigError, PatchError, ToolError) as e:
		print(f"error: {e}", file=sys.stderr)
		return 1
	return 0

if __name__ == "__main__":
	sys.exit(main())
