# Fix the RAM memory map:
#   - scan for the true SRAM extent (highest referenced 0x4000xxxx..0x4008xxxx addr)
#   - fill the undeclared RAM gaps with uninitialized blocks so high globals resolve
#   - add crt0 segment-boundary labels recovered from the startup loops
#   - name the reset/startup routine _start
#
# Dry-run by default (scan + plan). Pass "apply" (and drop -readOnly) to write.
# @category MemoryMap
from ghidra.program.model.symbol import SourceType
from ghidra.app.cmd.function import CreateFunctionCmd

APPLY = "apply" in [a.lower() for a in getScriptArgs()]
RAM_LO, RAM_HI = 0x40000000, 0x40090000

mem = currentProgram.getMemory()
st = currentProgram.getSymbolTable()
fm = currentProgram.getFunctionManager()
space = currentProgram.getAddressFactory().getDefaultAddressSpace()

# ---- 1) find the RAM extent actually used ---------------------------------
mx, mn, cnt = 0, 0xffffffff, 0
above = []
for sym in st.getAllSymbols(False):
    a = sym.getAddress()
    if a is None or not a.isMemoryAddress():
        continue
    o = a.getOffset()
    if RAM_LO <= o < RAM_HI:
        cnt += 1
        if o > mx:
            mx = o
        if o < mn:
            mn = o
        if o > 0x4000FFFF:
            above.append((o, sym.getName()))
print("RAM symbols: %d, span %08x .. %08x" % (cnt, mn, mx))
above.sort()
print("highest 12 RAM symbols above current 0x4000FFFF block:")
for (o, nm) in above[-12:]:
    print("  %08x  %s" % (o, nm))

# MPC5777C system SRAM is 256 KB at 0x40000000; the calibration RAM copy
# (calibration_in_memory @ 0x4002e000-0x4003dfff) sits at its top, confirming
# the extent.  Use the hardware top (the symbol scan undercounts because
# addresses outside any block never get symbols).
SRAM_TOP = 0x4003FFFF
top = SRAM_TOP
if mx > top:
    top = (mx + 0xFFF) & ~0xFFF
    top -= 1
print("\nSRAM top (hardware): %08x  (max referenced symbol %08x)" % (top, mx))

# ---- 2) existing blocks + gap computation ---------------------------------
print("\nexisting blocks in RAM range:")
covered = []
for b in mem.getBlocks():
    s, e = b.getStart().getOffset(), b.getEnd().getOffset()
    if e < RAM_LO or s >= RAM_HI:
        continue
    print("  %-22s %08x-%08x init=%s" % (b.getName(), s, e, b.isInitialized()))
    covered.append((s, e))
covered.sort()

# gaps between RAM_LO..top not covered
gaps = []
cur = RAM_LO
for (s, e) in covered:
    if s > cur:
        gaps.append((cur, min(s - 1, top)))
    cur = max(cur, e + 1)
    if cur > top:
        break
if cur <= top:
    gaps.append((cur, top))
gaps = [(s, e) for (s, e) in gaps if s <= e]
print("\nRAM gaps to fill:")
for (s, e) in gaps:
    print("  %08x-%08x  (%d bytes)" % (s, e, e - s + 1))

# ---- 3) crt0 boundary labels (from startup loop decode) -------------------
LABELS = [
    (0x008222C8, "__DATA_ROM"),
    (0x40000764, "__DATA_RAM"),
    (0x40000A38, "__DATA_END"),
    (0x40000A58, "__BSS_START"),
    (0x400085EC, "__BSS_END"),
    (0x40008A58, "_SDA_BASE_"),
    (0x400095F0, "__stack_top"),
    (0x008004CC, "__ram_trampoline_src"),
]
START = 0x00800400

if not APPLY:
    print("\n(dry-run) re-run with 'apply' (no -readOnly) to fill gaps + add labels.")
else:
    print("\n==== APPLYING ====")
    # 1) labels + _start first (these do NOT need exclusive access)
    for (addr, nm) in LABELS:
        try:
            createLabel(space.getAddress(addr), nm, True)
            print("  label %08x = %s" % (addr, nm))
        except:    # noqa  (catch Java exceptions too)
            print("  !! label %s failed" % nm)
    f = fm.getFunctionContaining(space.getAddress(START))
    if f is None:
        try:
            if CreateFunctionCmd(space.getAddress(START)).applyTo(currentProgram, monitor):
                f = fm.getFunctionContaining(space.getAddress(START))
        except:
            pass
    if f is not None:
        try:
            f.setName("_start", SourceType.USER_DEFINED)
            print("  named _start @ %s" % f.getEntryPoint())
        except:
            print("  !! _start rename failed")
    else:
        print("  !! could not create function @ %08x" % START)
    # 2) memory blocks last (these REQUIRE exclusive access to the program)
    blocks_ok = True
    for (s, e) in gaps:
        ln = e - s + 1
        nm = "sram_%08x" % s
        try:
            blk = mem.createUninitializedBlock(nm, space.getAddress(s), ln, False)
            blk.setRead(True)
            blk.setWrite(True)
            blk.setExecute(False)
            blk.setVolatile(True)
            print("  created block %s %08x-%08x" % (nm, s, e))
        except:    # noqa
            blocks_ok = False
            print("  !! block %08x-%08x NOT created (needs EXCLUSIVE checkout)" % (s, e))
    if not blocks_ok:
        print("\n  Memory-map edits need exclusive access. In the GUI: check out")
        print("  'emira' exclusively (or this local non-shared copy), then re-run apply,")
        print("  or add the gap blocks manually via Window > Memory Map (+):")
        for (s, e) in gaps:
            print("    %08x  len 0x%x  RW, uninitialized, volatile" % (s, e - s + 1))
    print("== DONE (review + save/commit in GUI) ==")
