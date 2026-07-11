# Read-only: resolve U660E friction-element identity.
#  - element-index -> apply-bit table (flash ~0x1d00, read in execute_shift loop)
#  - element-id -> solenoid-index map DAT_0008dfe9 (10-byte stride)
#  - CAL_gear_clutch_bitmask + CAL_shift_clutch_element for cross-check
# @category Analysis
import jarray
mem = currentProgram.getMemory()
space = currentProgram.getAddressFactory().getDefaultAddressSpace()
def A(v): return space.getAddress(v)
def rd(off, n):
    b = jarray.zeros(n, 'b'); mem.getBytes(A(off), b)
    return [x & 0xff for x in b]

print("== element-index -> apply-bit table region (flash 0x1cf8..0x1d20) ==")
b = rd(0x1cf8, 0x28)
for r in range(0, 0x28, 8):
    print("  0x%06x  %s" % (0x1cf8+r, " ".join("%02x" % x for x in b[r:r+8])))

print("\n== DAT_0008dfe9 element-id -> solenoid map (8 entries x 10 bytes) ==")
b = rd(0x8dfe9, 8*10)
for i in range(8):
    row = b[i*10:(i+1)*10]
    print("  id %d @0x%06x: solenoid_idx=%d  rest=%s" % (
        i, 0x8dfe9+i*10, row[0], " ".join("%02x" % x for x in row[1:])))

print("\n== CAL_gear_clutch_bitmask[0..10] (0x8d9d0) ==")
b = rd(0x8d9d0, 11)
print("  " + " ".join("%02x" % x for x in b))

print("\n== CAL_shift_clutch_element 7x7 [from*7+to] (0x8db28) ==")
b = rd(0x8db28, 49)
for f in range(7):
    print("  from%d: %s" % (f, " ".join("%02x" % b[f*7+t] for t in range(7))))
print("== DONE ==")
