# Read-only: characterize the INTC vector-table ISRs by the peripheral MMIO they
# touch (function body + one level of callees). Also print language id and the
# function that owns the IACKR write at 0x40b50.
# @category Analysis
import jarray
fm = currentProgram.getFunctionManager()
listing = currentProgram.getListing()
mem = currentProgram.getMemory()
space = currentProgram.getAddressFactory().getDefaultAddressSpace()

print("language = %s" % currentProgram.getLanguageID())
print("compiler = %s" % currentProgram.getCompilerSpec().getCompilerSpecID())

# MPC5534 peripheral map (base -> name); classify by high bits
PERI = [
    (0xC3F90000, 0xC3F9FFFF, "SIU"),
    (0xC3FA0000, 0xC3FAFFFF, "eMIOS"),
    (0xC3FC0000, 0xC3FDFFFF, "eTPU"),
    (0xC3FF0000, 0xC3FFFFFF, "PIT"),
    (0xFFF44000, 0xFFF47FFF, "eDMA"),
    (0xFFF48000, 0xFFF4BFFF, "INTC"),
    (0xFFF90000, 0xFFF93FFF, "DSPI_A"),
    (0xFFF94000, 0xFFF97FFF, "DSPI_B"),
    (0xFFF98000, 0xFFF9BFFF, "DSPI_C"),
    (0xFFF9C000, 0xFFF9FFFF, "DSPI_D"),
    (0xFFFB0000, 0xFFFB3FFF, "eSCI_A"),
    (0xFFFB4000, 0xFFFB7FFF, "eSCI_B"),
    (0xFFFC0000, 0xFFFC3FFF, "FlexCAN_A"),
    (0xFFFC8000, 0xFFFCBFFF, "FlexCAN_C"),
    (0xFFF80000, 0xFFF83FFF, "eQADC"),
    (0xFFF38000, 0xFFF3BFFF, "STM"),
    (0xFFF3C000, 0xFFF3FFFF, "SWT"),
]
def classify(a):
    for lo, hi, nm in PERI:
        if lo <= a <= hi:
            return nm
    return None

def peris_of(func, depth=1, seen=None):
    if seen is None:
        seen = set()
    if func is None or func.getEntryPoint() in seen:
        return set()
    seen.add(func.getEntryPoint())
    hits = set()
    body = func.getBody()
    ii = listing.getInstructions(body, True)
    callees = []
    while ii.hasNext():
        insn = ii.next()
        for r in insn.getReferencesFrom():
            ta = r.getToAddress()
            if ta is None:
                continue
            off = ta.getOffset()
            nm = classify(off)
            if nm:
                hits.add(nm)
            if depth > 0 and r.getReferenceType().isCall():
                cf = fm.getFunctionAt(ta)
                if cf is not None:
                    callees.append(cf)
    for cf in callees:
        hits |= peris_of(cf, depth-1, seen)
    return hits

# re-derive table
def rd(off, n):
    buf = jarray.zeros(n, 'b')
    mem.getBytes(space.getAddress(off), buf)
    return [x & 0xff for x in buf]
BASE = 0x8f800
N = 162
DEFAULT = 0x40b00
b = rd(BASE, N*4)
print("\nidx  vec   target     peripherals                     current-name")
for i in range(N):
    o = i*4
    v = (b[o]<<24)|(b[o+1]<<16)|(b[o+2]<<8)|b[o+3]
    if v == DEFAULT:
        continue
    f = fm.getFunctionAt(space.getAddress(v))
    if f is None:
        f = fm.getFunctionContaining(space.getAddress(v))
    hits = peris_of(f, 1) if f is not None else set()
    nm = f.getName() if f is not None else "(none)"
    print("  %3d  %3d  0x%06x  %-30s  %s" % (i, i, v, ",".join(sorted(hits)) or "-", nm))

# owner of IACKR write
tgt = space.getAddress(0x40b50)
f = fm.getFunctionContaining(tgt)
print("\nfunction containing 0x40b50 (IACKR write) = %s entry=0x%06x" % (
    f.getName() if f else "(none)", f.getEntryPoint().getOffset() if f else 0))
# also owner of the MCR/CPR block near 0x40bfc
f2 = fm.getFunctionContaining(space.getAddress(0x40bfc))
print("function containing 0x40bfc = %s entry=0x%06x" % (
    f2.getName() if f2 else "(none)", f2.getEntryPoint().getOffset() if f2 else 0))
print("== DONE ==")
