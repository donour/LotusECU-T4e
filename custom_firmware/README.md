# custom_firmware: composable T6 ECU patches

`t6patch` builds patched T6 (MPC5534) firmware from a **recipe**: one stock
firmware (**target**) plus an ordered list of feature **modules**. All modules
are assembled and linked together in one pass, so they share one allocator
for flash, cal and RAM, can reference each other's symbols, and any conflict
fails the build. Module order in the recipe is the call order at each hook.

It replaces the T6 half of `patch/build.py`. The low-level pipeline is checked
against that script: rebuilding its outputs with t6patch's linker script and
site writer gives byte-identical images (`tests/test_legacy.py`), including the
race-tc image in `patch/dpm-b132e0091-prog-only.crp` (built when the module was called dpm).

## Quick start

Requirements: Python 3.11+, and `powerpc-linux-gnu` binutils, either on PATH
or inside WSL (`sudo apt install binutils-powerpc-linux-gnu`). WSL is detected
automatically. Put the stock images in `bases/` (see `bases/README.md`).

```
cd custom_firmware
python -m t6patch list                                  # targets, modules, recipes
python -m t6patch check B13200091                       # hook sites vs stock prog
python -m t6patch build s1-race-tc-wideband --stages   # recipe name or .toml path
python -m unittest discover -s tests
```

`build` writes to `build/<recipe>/`:

| File | |
|---|---|
| `<recipe>.crp` | cal + prog, ready for the CRP08 uploader |
| `<recipe>-prog-only.crp` | prog only. The report says whether that is safe for this build |
| `prog.bin`, `calrom.bin` | raw patched regions |
| `report.md` | flash/RAM usage, hooks, every patch site before/after, RAM variable addresses, every changed byte and its owner |
| `symbols.txt` | address map, e.g. for dev-mode CAN memory peeks |
| `patch.elf`, `patch.dis` | linked patch and its disassembly |
| `manifest.json` | inputs, module versions, hashes |
| `stages/NN-.../` | with `--stages`: the same for each prefix of the module list, for bisecting on the car |

## Layout

```
t6patch/      the tool (stdlib only; binutils do the assembling)
core/         runtime linked into every build (RAM zeroing, cal block copy)
targets/      one directory per stock firmware: target.toml + symbols.sym
modules/      one directory per feature: module.toml + sources
recipes/      target + ordered module list (+ your cal)
tests/        legacy regression + safety checks
bases/        stock images (not committed)
```

## Concepts

**Target** (`targets/<name>/target.toml`): the stock prog (pinned by sha256),
where free flash/cal/RAM starts, the RAM budget, accepted cal id strings,
**hooks**, and **core sites**. `symbols.sym` is a GNU ld symbol file
(Ghidra export or hand-written). Every name a module uses must resolve there
or in another module.

**Hooks** are places where modules run code. The hook instruction is replaced
by `ba t6p_hook_<name>`. The generated dispatcher calls every module's
handlers in recipe order, replays the displaced instruction, and resumes.
`lr_live` / `live` in the target say which registers it has to preserve at
that site. Current hooks:

| Hook | B13200091 | C132E0278 | |
|---|---|---|---|
| `init` | yes | yes | once at startup (core init runs first) |
| `loop` | yes | yes | every main loop |
| `tick_5ms` | yes | yes | 200 Hz |
| `torque_arbitration_exit` | yes | no | end of torque_limit_request_arbitration, to tighten torque limits |
| `tpms_frame_packed` | yes | no | cluster_send_data, 10 Hz: CAN 0x402 TPMS frame packed, before it is marked for sending |

**Sites** are in-place edits of firmware instructions. Each declares the
instructions it expects to find. They are assembled at the site address and
compared with the stock prog before anything is written. A wrong address, a
wrong symbol, or the wrong firmware stops the build and prints both
disassemblies. The expectation can cover more instructions than are replaced,
so the surrounding code is verified too. Two writers on the same byte is an
error.

**Patch cal block**: module calibration (`cal.inc.S`, `CALENTRY` entries)
goes into one block after the stock cal: `T6PCAL01`, a layout hash, the size,
then each module's entries. At init it is copied to RAM (`CAL_base_extra`), and
modules read `OFF_<name>(CAL_base_extra)`. If the input cal already has a
block with the same layout (a previous build that you tuned in RomRaider),
its values are kept. A block with a different layout is refused unless you
pass `--reset-patch-cal`.

**Cal sites** are locations inside the stock cal that you have labelled
unused (in Ghidra and the target's `symbols.sym`, by their `CAL_` RAM address)
and that a module takes over. The firmware's `copyCAL2RAM` copies them to RAM
with the rest of the cal, so the module reads them like any calibration and
they can be tuned in RomRaider at the cal offset the report gives. The stock
cal must hold the declared contents there (`stock = "zeros"`). An input cal
that still holds them gets the module's defaults; any other contents are your
tuning and are kept.

**RAM**: patch variables start at `0x4000F000`, inside the stack headroom
that `freeram_fill` paints with 0x55. The budget defaults to 1 KB; measure
`free_ram_count` on the car before raising it. The core zeroes all patch RAM
at init, so modules do not need to.

## Writing a module

`modules/<id>/module.toml`:

```toml
id = "wideband"
version = 1                       # bump when its cal layout or behaviour changes
targets = ["B13200091", "C132E0278"]
sources = ["wideband.S"]
cal = "cal.inc.S"                 # optional
[hooks]                           # handler symbols, called in this order
init = "wideband_init"
tick_5ms = ["wideband_5ms"]
[[sites]]
name = "adc_skip_b1"
at = "adc_sample_pre_O2_bank1"    # symbol or address
expect = [                        # or { B13200091 = [...], C132E0278 = [...] }
	"lis %r3, adc_dma_dest@ha",
	"sth %r0, {sensor_adc_pre_O2_bank1 - _SDA_BASE_}(%r13)",
]
```

- Handlers are normal functions (`bl`/`blr`, PowerPC SysV ABI). They may
  clobber r0, r3-r12, CR0/1/5-7, CTR and XER, and must preserve r1, r2 and
  r13-r31. **r13 is the firmware's small-data anchor** (`_SDA_BASE_`).
- A site's replacement goes in section `.patch.<module id>.<site name>`
  (`"ax"`), in any of the module's sources. It may be shorter than `expect`.
- In `expect` text, target symbols resolve at link time (relative branches
  are encoded correctly). `{expr}` is computed by t6patch with the target
  symbols, for arithmetic the assembler cannot do on undefined symbols.
- A cal site is declared as `[[cal_sites]]` (`name`, `at` = `CAL_` symbol,
  `stock`), with its default values in section `.calsite.<module id>.<name>`
  (`"a"`). Code reads it through the `CAL_` symbol (the RAM copy).
- Code goes in `.text`, variables in `.bss`, calibration through `cal.inc.S`
  (patch cal block) or cal sites. Anything else (e.g. `.sdata`) fails the build.
- A module may not define a symbol the target symbol file also defines.

## Modules

| Module | Targets | Notes |
|---|---|---|
| `race-tc` | B13200091 | Race traction control, from `20260706/s1_dpm` (a15fc67), where it was called dpm; renamed with identical machine code. The torque-arbitration filter moved out of `hook.S` into the module (`race_tc.S`, with the other hook handlers). v2: the dash display rewrites only the CAN 0x402 frame (hook `tpms_frame_packed`), and only while race-tc is on, so TPMS works normally with it off. v3: the slip-target base table and its level axis are cal sites (`CAL_racetc_slip_target_base`, `..._X_dpm_level`, cal offsets 0x31E / 0x30E). v4: 9 levels instead of 6 (`RACE_TC_MAX_LEVEL`); default slip-target bases 0–24 % in 3 % steps. |
| `wideband` | both | From `patch/t6/wideband`. Its sites are now verified across the whole skipped ADC sequence. |
| `flexfuel` | C132E0278 | From `patch/t6/flexfuel`. Pad RG4 site located on the GT430 only. |

## Differences from patch/build.py

- No `.ifdef` combinations: modules declare hooks and sites instead of editing
  `hook.S`, the Makefile and `build.py`.
- Patch sites are assembly plus verified expectations, not Python-encoded
  opcodes. Symbols resolve in the linker, with no `@ha`/`@l` arithmetic in
  Python.
- A generated linker script places `.sbss`/`COMMON`, aligns the cal block and
  RAM to 16 bytes, and enforces the flash, cal and RAM budgets.
- Patch RAM is zeroed by the core. The free-RAM scan starts at the aligned end
  of patch RAM.
- The OBD handlers are no longer linked in (they were dead code on the NA).
- **B13200091 symbol fix**: `T6-V00BU.sym` had `sensor_adc_pre_O2_bank2`
  (0x40001714) and `sensor_adc_post_O2_bank1` (0x40001716) swapped. Wideband
  on the NA with the old symbols would have overwritten bank-1 post-cat O2 and
  left bank-2 pre-cat frozen. The site expectation now catches this (see
  `tests/test_checks.py`).

## Not done yet

- **OBD dispatch.** Module PIDs (wideband 0x24/0x25 and 0x0403/0x0404,
  flexfuel 0x52/0x0401) are not wired. The NA OBD hooks were disabled on
  s1_dpm because they forced a reboot, and the register conventions differ
  between targets. The plan is a per-target glue plus a uniform handler ABI.
- RomRaider definition generation for the patch cal block (port
  `patch/t4e/combined/gen_defs.awk`).
- Cal block migration when a module's cal layout changes (today:
  `--reset-patch-cal`).
- A boot-time check that the prog and cal belong together, with modules left
  disabled otherwise.
- Calibration transforms (Python, recorded in the cal block so they never run
  twice), needed for load rescaling.
- The GT430 base: `T6EVRGT430E01_BIN.cpt` differs from the Ghidra
  `C132E0278.hex` in 159 bytes. Confirm it is what is on the car.
