# Read-only: dump the clutch pressure-vs-load curves in RAM shadow.
# Each pointer target is a 16-byte curve: axis[0..7] (load breakpoints) + data[8..15].
# Verify axis monotonicity + current symbols/types. @category Analysis
import jarray
listing = currentProgram.getListing()
mem = currentProgram.getMemory()
st = currentProgram.getSymbolTable()
space = currentProgram.getAddressFactory().getDefaultAddressSpace()
def A(v): return space.getAddress(v)
def rd(off, n):
    b = jarray.zeros(n, 'b'); mem.getBytes(A(off), b)
    return [x & 0xff for x in b]

# distinct curve targets (from the two pointer arrays), profile -> addr
CURVES = {
 "oncoming":  [(0x4000ce22,"default"),(0x4000cd82,"1_2"),(0x4000cda2,"2_3"),
               (0x4000cdc2,"3_4"),(0x4000cde2,"4_5"),(0x4000ce02,"5_6")],
 "offgoing":  [(0x4000ce12,"default"),(0x4000cd72,"1_2"),(0x4000cd92,"2_3"),
               (0x4000cdb2,"3_4"),(0x4000cdd2,"4_5"),(0x4000cdf2,"5_6")],
}
def sym(off):
    s = st.getPrimarySymbol(A(off))
    d = listing.getDataAt(A(off))
    dt = d.getDataType().getName() if (d and d.isDefined()) else "-"
    return (s.getName() if s else "(none)"), dt

for role in ("oncoming","offgoing"):
    print("== %s ==" % role)
    for addr, tag in sorted(CURVES[role]):
        b = rd(addr, 16)
        axis = b[0:8]; data = b[8:16]
        mono = all(axis[i] <= axis[i+1] for i in range(7))
        nm, dt = sym(addr)
        print("  0x%06x %-8s axis=%-24s data=%-24s mono=%s  sym=%s/%s" % (
            addr, tag, " ".join("%3d"%x for x in axis), " ".join("%3d"%x for x in data),
            mono, nm, dt))
# context around the block
print("\n-- raw 0x4000cd60..0x4000ce40 --")
b = rd(0x4000cd60, 0xe0)
for r in range(0, 0xe0, 16):
    print("  0x%06x  %s" % (0x4000cd60+r, " ".join("%02x"%x for x in b[r:r+16])))
print("== DONE ==")
