# Read-only recon for confident labeling.
#  - peripheral MMIO addresses actually referenced, grouped by 0x4000-block,
#    with xref counts (helps identify which peripherals/registers are live)
#  - naming coverage (named vs FUN_/DAT_ defaults)
#  - functions that touch a given peripheral base (callers of CAN/ADC/etc.)
# @category Recon
from ghidra.program.model.symbol import SymbolType

fm = currentProgram.getFunctionManager()
st = currentProgram.getSymbolTable()
refMgr = currentProgram.getReferenceManager()

# ---- naming coverage -------------------------------------------------------
nfun = nfun_named = 0
for f in fm.getFunctions(True):
    nfun += 1
    if not f.getName().startswith("FUN_"):
        nfun_named += 1
print("functions: %d total, %d named, %d still FUN_*" % (
    nfun, nfun_named, nfun - nfun_named))

# ---- MMIO references grouped by peripheral block ---------------------------
# MMIO on MPC5777C lives high: 0xC3F0_0000+ (SIU/eMIOS/etc) and 0xFFE0_0000+
# (per-module). Group referenced data addresses by 0x4000 page and count xrefs.
blocks = {}   # page_base -> [addr_count, xref_count, min, max]
it = currentProgram.getListing().getDefinedData(True)
# Instead of all data, walk symbols in MMIO ranges via references from code:
seen = {}
for sym in st.getAllSymbols(False):
    a = sym.getAddress()
    if a is None or not a.isMemoryAddress():
        continue
    off = a.getOffset()
    if off < 0xC3F00000:
        continue
    # count code xrefs
    xr = 0
    for r in refMgr.getReferencesTo(a):
        xr += 1
    page = off & 0xFFFFC000
    b = blocks.setdefault(page, [0, 0, off, off])
    b[0] += 1
    b[1] += xr
    if off < b[2]:
        b[2] = off
    if off > b[3]:
        b[3] = off
    seen[off] = (sym.getName(), xr)

print("\nMMIO blocks referenced (page=base&~0x3fff):")
print("  page         syms  xrefs  range")
for page in sorted(blocks):
    b = blocks[page]
    print("  %08x   %4d  %5d  %08x-%08x" % (page, b[0], b[1], b[2], b[3]))

# ---- detail for the most-referenced MMIO addresses -------------------------
print("\ntop referenced MMIO addresses:")
tops = sorted(seen.items(), key=lambda kv: -kv[1][1])[:40]
for off, (nm, xr) in tops:
    print("  %08x  xrefs=%-4d  %s" % (off, xr, nm))
