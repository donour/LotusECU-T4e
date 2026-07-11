# Read-only: inspect the execute_shift per-gear-pair flash tables before typing.
# Dumps bytes, current data/labels, and decodes the pointer arrays.
# @category Analysis
import jarray
listing = currentProgram.getListing()
mem = currentProgram.getMemory()
fm = currentProgram.getFunctionManager()
st = currentProgram.getSymbolTable()
space = currentProgram.getAddressFactory().getDefaultAddressSpace()
def A(v): return space.getAddress(v)

def rd(off, n):
    b = jarray.zeros(n, 'b'); mem.getBytes(A(off), b)
    return [x & 0xff for x in b]

def cur(off):
    d = listing.getDataAt(A(off))
    s = st.getPrimarySymbol(A(off))
    dt = (d.getDataType().getName()+("[%d]"%d.getNumComponents() if d.isArray() else "")) if (d and d.isDefined()) else "-"
    return (s.getName() if s else "(none)"), dt

def dump(off, n, label):
    b = rd(off, n)
    nm, dt = cur(off)
    print("\n-- %s @0x%06x  sym=%s type=%s --" % (label, off, nm, dt))
    for r in range(0, n, 16):
        print("  0x%06x  %s" % (off+r, " ".join("%02x" % x for x in b[r:r+16])))

# the 3 from*7+to byte tables (7x7 = 49 bytes)
for off, lbl in [(0x8daf4,"profile_index"),(0x8db28,"clutch_elem"),(0x8db5c,"shift_type")]:
    dump(off, 0x31, lbl)

# per-target-gear bitmask (index 0..10)
dump(0x8d9d0, 0x18, "gear_clutch_bitmask")

# pointer arrays: 0x8dbdc and 0x8dc28 (0x8dc28-0x8dbdc=0x4c=19 ptrs)
for base, lbl in [(0x8dbdc,"pressure_ptrs_A"),(0x8dc28,"pressure_ptrs_B")]:
    print("\n== pointer array %s @0x%06x ==" % (lbl, base))
    b = rd(base, 19*4)
    for i in range(19):
        o=i*4; v=(b[o]<<24)|(b[o+1]<<16)|(b[o+2]<<8)|b[o+3]
        tag=""
        if 0 < v < 0x100000:
            tb = rd(v, 16)
            tag = "-> 0x%06x : data[%s] axis[%s]" % (v,
                  " ".join("%02x"%x for x in tb[8:16]), " ".join("%02x"%x for x in tb[0:8]))
        print("  [%2d] 0x%06x = 0x%08x  %s" % (i, base+o, v, tag))
print("\n== DONE ==")
