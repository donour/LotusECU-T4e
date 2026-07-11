# Read-only: enumerate the pointer table at 0x8f800 (162 entries). Print every
# entry whose target != the default handler 0x40b00, with index, target, and the
# function name there (or UNDEFINED). Also search for any code that loads 0x8f800
# (or INTC_IACKR 0xfff48010) to identify the table's role.
# @category Analysis
import jarray
fm = currentProgram.getFunctionManager()
mem = currentProgram.getMemory()
space = currentProgram.getAddressFactory().getDefaultAddressSpace()
rm = currentProgram.getReferenceManager()

def rd(off, n):
    buf = jarray.zeros(n, 'b')
    mem.getBytes(space.getAddress(off), buf)
    return [x & 0xff for x in buf]

BASE = 0x8f800
N = 162
DEFAULT = 0x40b00
b = rd(BASE, N*4)
print("== non-default entries in table @0x%06x (%d entries) ==" % (BASE, N))
ndef = 0
for i in range(N):
    o = i*4
    v = (b[o]<<24)|(b[o+1]<<16)|(b[o+2]<<8)|b[o+3]
    if v == DEFAULT:
        continue
    ndef += 1
    ta = space.getAddress(v)
    f = fm.getFunctionContaining(ta)
    nm = f.getName() if f is not None else "*** UNDEFINED / not a function ***"
    at_entry = (f is not None and f.getEntryPoint().getOffset() == v)
    print("  [%3d] -> 0x%06x  %s%s" % (i, v, "" if at_entry else "(mid-func) ", nm))
print("  %d non-default of %d entries; %d default(0x%06x)" % (ndef, N, N-ndef, DEFAULT))

# who references the table base 0x8f800?
print("\n== references to 0x8f800 ==")
for r in rm.getReferencesTo(space.getAddress(BASE)):
    print("  from %s  %s" % (r.getFromAddress(), r.getReferenceType()))
# who references INTC_IACKR region
print("== references to INTC 0xfff48000..0xfff48014 ==")
for a in range(0xfff48000, 0xfff48018, 4):
    for r in rm.getReferencesTo(space.getAddress(a)):
        print("  0x%08x <- %s  %s" % (a, r.getFromAddress(), r.getReferenceType()))
print("== DONE ==")
