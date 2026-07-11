# Read-only: find who references the neighbor curves at 0x4000cd62 / 0x4000ce32.
#  - dump 16B at each (axis+data) + current symbols
#  - ReferenceManager refs to base and base+8
#  - scan flash for BE32 pointer values to base (embedded pointer tables)
# @category Analysis
import jarray
listing = currentProgram.getListing()
mem = currentProgram.getMemory()
st = currentProgram.getSymbolTable()
fm = currentProgram.getFunctionManager()
rm = currentProgram.getReferenceManager()
space = currentProgram.getAddressFactory().getDefaultAddressSpace()
def A(v): return space.getAddress(v)
def rd(off, n):
    b = jarray.zeros(n, 'b'); mem.getBytes(A(off), b)
    return [x & 0xff for x in b]

TARGETS = [0x4000cd62, 0x4000ce32]

for base in TARGETS:
    b = rd(base, 16)
    s = st.getPrimarySymbol(A(base))
    print("\n== 0x%08x  sym=%s ==" % (base, s.getName() if s else "(none)"))
    print("  axis = %s" % " ".join("%3d" % x for x in b[0:8]))
    print("  data = %s" % " ".join("%3d" % x for x in b[8:16]))
    for off in (base, base + 8):
        for r in rm.getReferencesTo(A(off)):
            fa = r.getFromAddress()
            f = fm.getFunctionContaining(fa)
            print("  ref to 0x%08x from %s (%s) %s" % (
                off, fa, f.getName() if f else "?", r.getReferenceType()))

# scan flash for embedded BE32 pointers to either base
print("\n== flash words == (pointer scan 0..0x100000)")
FLASH = 0x100000
raw = bytearray(FLASH)
for blk in mem.getBlocks():
    bs = blk.getStart().getOffset(); be = blk.getEnd().getOffset()
    if be < 0 or bs >= FLASH or not blk.isInitialized():
        continue
    lo = max(bs, 0); hi = min(be, FLASH - 1); n = hi - lo + 1
    buf = jarray.zeros(n, 'b'); mem.getBytes(A(lo), buf)
    for i in range(n):
        raw[lo + i] = buf[i] & 0xff
tset = set(TARGETS)
for o in range(0, FLASH - 3, 2):   # check 2-byte alignment too
    v = (raw[o] << 24) | (raw[o+1] << 16) | (raw[o+2] << 8) | raw[o+3]
    if v in tset:
        d = listing.getDataContaining(A(o))
        dn = d.getDataType().getName() if (d and d.isDefined()) else "-"
        s2 = st.getPrimarySymbol(A(o)) or (st.getPrimarySymbol(d.getAddress()) if d else None)
        print("  0x%06x contains ptr 0x%08x  (data=%s sym=%s)" % (
            o, v, dn, s2.getName() if s2 else "-"))

# also scan every OTHER initialized block (RAM shadow etc.) for embedded pointers
print("\n== non-flash initialized blocks ==")
for blk in mem.getBlocks():
    bs = blk.getStart().getOffset() & 0xffffffff
    if bs < FLASH or not blk.isInitialized():
        continue
    n = blk.getSize()
    print("  scanning %-12s 0x%08x..0x%08x (0x%x)" % (blk.getName(), bs, bs + n - 1, n))
    buf = jarray.zeros(n, 'b'); mem.getBytes(blk.getStart(), buf)
    for o in range(0, n - 3, 2):
        v = ((buf[o]&0xff) << 24) | ((buf[o+1]&0xff) << 16) | ((buf[o+2]&0xff) << 8) | (buf[o+3]&0xff)
        if v in tset:
            print("  0x%08x contains ptr 0x%08x" % (bs + o, v))
print("== DONE ==")
