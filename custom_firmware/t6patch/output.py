"""Build outputs: flash images, CRP files, symbol map, disassembly and report."""

import json, os, re, shutil, sys
from .config import ROOT
from .elf import STB_LOCAL, STT_FUNC, STT_OBJECT, STT_NOTYPE
from .image import sha256_file

sys.path.insert(0, os.path.dirname(ROOT))
from lib.crp08 import CRP08

CRP_VARIANT = [v[0] for v in CRP08.variants].index("T6")

def write_crp(path, cal_bin=None, prog_bin=None):
	crp = CRP08()
	if(cal_bin): crp.add_cal(cal_bin, CRP_VARIANT)
	if(prog_bin): crp.add_prog(prog_bin, CRP_VARIANT)
	crp.write_file(path)

_DIS_SECTION = re.compile(r"^Disassembly of section (\S+):")
_DIS_LINE = re.compile(r"^\s*([0-9a-f]+):\s+((?:[0-9a-f]{2} ){4})\s*(.*)$")

def parse_objdump(text):
	"""{section: [(addr, hex bytes, instruction)]}"""
	out, cur = {}, None
	for line in text.splitlines():
		m = _DIS_SECTION.match(line)
		if(m):
			cur = out.setdefault(m[1], [])
			continue
		m = _DIS_LINE.match(line)
		if(m and cur is not None):
			cur.append((int(m[1], 16), m[2].strip(), " ".join(m[3].split())))
	return out

def _fmt_dis(lines):
	return "\n".join(f"    {a:06x}:  {b}   {i}" for a, b, i in lines)

def _symbols_in(elf, section, include_local):
	syms = [s for s in elf.symbols if s.section == section and s.name
		and s.type in (STT_FUNC, STT_OBJECT, STT_NOTYPE)
		and (include_local or s.bind != STB_LOCAL)
		and not s.name.startswith(("__patch_", "t6p_cal_"))] # Linker script markers
	return sorted({(s.value, s.name): s for s in syms}.values(), key=lambda s: (s.value, s.name))

def _sizes(syms, end):
	"""Symbol sizes, falling back to the distance to the next symbol."""
	out = []
	for i, s in enumerate(syms):
		nxt = syms[i+1].value if i + 1 < len(syms) else end
		out.append(s.size if s.size else nxt - s.value)
	return out

def write_outputs(tc, res):
	out = res.out_dir
	name = res.recipe.name
	prog_bin = os.path.join(out, "prog.bin")
	cal_bin = os.path.join(out, "calrom.bin")
	res.prog.save(prog_bin)
	res.cal.save(cal_bin)
	write_crp(os.path.join(out, f"{name}.crp"), cal_bin, prog_bin)
	write_crp(os.path.join(out, f"{name}-prog-only.crp"), None, prog_bin)
	gen = os.path.join(out, "gen")
	shutil.copyfile(os.path.join(gen, "patch.elf"), os.path.join(out, "patch.elf"))

	patch_dis = tc.disassemble(os.path.join(gen, "patch.elf"))
	with open(os.path.join(out, "patch.dis"), "w", newline="\n") as f: f.write(patch_dis)
	after = parse_objdump(patch_dis)
	before = parse_objdump(tc.disassemble(os.path.join(gen, "expect.elf")))

	elf = res.elf
	text, data, bss = elf.section(".text"), elf.section(".data"), elf.section(".bss")
	ram_end = elf.symbol("__patch_ram_end").value

	# Symbol map (also handy for dev-mode CAN memory peeks).
	rows = []
	for sec in (".text", ".data", ".bss"):
		for s in _symbols_in(elf, sec, include_local=(sec == ".bss")):
			rows.append(f"{s.value:08X} {sec:6s} {res.owners.get(s.name, '-'):10s} {s.name}")
	with open(os.path.join(out, "symbols.txt"), "w", newline="\n") as f:
		f.write("\n".join(rows) + "\n")

	module_cal = any(m.cal or m.cal_sites for m in res.modules)
	manifest = {
		"recipe": name,
		"target": res.target.name,
		"modules": [{"id": m.id, "version": m.version} for m in res.modules],
		"stock_prog_sha256": res.target.prog.sha256,
		"input_cal": res.cal.path,
		"input_cal_sha256": sha256_file(res.cal.path),
		"cal_layout_hash": f"0x{res.cal_hash:08X}",
		"layout": {k: f"0x{v:X}" for k, v in vars(res.layout).items()},
		"prog_bin_sha256": sha256_file(prog_bin),
		"calrom_bin_sha256": sha256_file(cal_bin),
	}
	with open(os.path.join(out, "manifest.json"), "w", newline="\n") as f:
		json.dump(manifest, f, indent=2)
		f.write("\n")

	t = res.target
	r = [f"# Build report: {name}", "",
		"| | |", "|---|---|",
		f"| Target | {t.name}: {t.description} |",
		f"| Stock prog | `{os.path.basename(res.prog.path)}` (sha256 `{t.prog.sha256[:16]}...`) |",
		f"| Input cal | `{res.cal.path}` ({res.cal_id or 'unchecked id'}) |",
		f"| Modules (call order) | {', '.join(f'{m.id} v{m.version}' for m in res.modules) or 'none'} |",
		f"| Cal block | 0x{data.addr:X}, {data.size} bytes, layout hash 0x{res.cal_hash:08X}: {res.cal_note} |",
		"",
		"## Flash and RAM", "",
		"| Region | Start | End | Used | Limit |", "|---|---|---|---|---|",
		f"| Patch code (prog flash) | 0x{text.addr:X} | 0x{text.addr+text.size:X} | {text.size} | 0x{res.layout.rom_end:X} |",
		f"| Patch cal block (cal flash) | 0x{data.addr:X} | 0x{data.addr+data.size:X} | {data.size} | 0x{res.layout.cal_end:X} |",
		f"| Patch RAM | 0x{bss.addr:X} | 0x{ram_end:X} | {ram_end-bss.addr} | 0x{res.layout.ram_end:X} (budget {t.ram_budget}) |",
		"",
		"Patch RAM sits in the stack headroom above the firmware's last RAM segment.",
		"",
		"## Flashing", "",
		f"- `{name}.crp`: cal + prog. Prog and cal are a matched pair; flash both.",
		f"- `{name}-prog-only.crp`: prog only. " + (
			"**Not safe for this build**: modules read calibration (cal block or cal sites) "
			"that a stock cal does not have." if module_cal else
			"OK for this build: no module reads calibration from the cal."),
		"",
		"## Hooks", "",
		"| Hook | Site | Handlers (call order) |", "|---|---|---|"]
	for h, funcs in res.handlers.items():
		r.append(f"| {h} | 0x{t.addr(t.hooks[h].at):X} | {', '.join(funcs)} |")
	if(res.cal_sites):
		r += ["", "## Cal sites", "",
			"Stock-cal locations taken over by modules. Cal offset = RomRaider storageaddress.", "",
			"| Owner | Read at (RAM) | Cal flash | Cal offset | Bytes | State |", "|---|---|---|---|---|---|"]
		for c in res.cal_sites:
			size = elf.section(".calsite." + c.key).size
			r.append(f"| {c.owner} | 0x{c.ram:08X} | 0x{c.addr:X} | 0x{c.addr - res.cal.base:X} | {size} | {c.note} |")
	r += ["", "## Patch sites", ""]
	for s in res.sites:
		r += [f"### {s.owner}: 0x{s.addr:X}", "", "```", "before:",
			_fmt_dis(before.get(".expect." + s.key, [])), "after:",
			_fmt_dis(after.get(".patch." + s.key, [])), "```", ""]
	r += ["## RAM variables", "", "| Address | Size | Symbol | Module |", "|---|---|---|---|"]
	syms = _symbols_in(elf, ".bss", include_local=True)
	for s, size in zip(syms, _sizes(syms, elf.symbol("__patch_bss_end").value)):
		r.append(f"| 0x{s.value:08X} | {size} | {s.name} | {res.owners.get(s.name, '-')} |")
	r += ["", "## Code symbols", "", "| Address | Symbol | Module |", "|---|---|---|"]
	for s in _symbols_in(elf, ".text", include_local=False):
		r.append(f"| 0x{s.value:06X} | {s.name} | {res.owners.get(s.name, '-')} |")
	r += ["", "## Changed bytes vs input images", "",
		"Every changed byte belongs to one of these writes (checked by the build).", "",
		"| Image | Range | Bytes changed | Owner |", "|---|---|---|---|"]
	for img in (res.prog, res.cal):
		for start, end, who in sorted(img.owners):
			a, b = start - img.base, end - img.base
			changed = sum(x != y for x, y in zip(img.data[a:b], img.original[a:b]))
			r.append(f"| {img.name} | 0x{start:X}-0x{end:X} | {changed} of {end-start} | {who} |")
	with open(os.path.join(out, "report.md"), "w", newline="\n", encoding="utf-8") as f:
		f.write("\n".join(r) + "\n")
	return manifest
