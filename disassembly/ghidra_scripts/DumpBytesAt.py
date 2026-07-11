# Read-only: hex-dump raw bytes at given flash offsets, and decode the pointer
# table at 0x8f800 (count distinct targets, flag which are function entries).
# @category Analysis
import jarray
fm = currentProgram.getFunctionManager()
listing = currentProgram.getListing()
mem = currentProgram.getMemory()
space = currentProgram.getAddressFactory().getDefaultAddressSpace()

def rd(off, n):
    buf = jarray.zeros(n, 'b')
    mem.getBytes(space.getAddress(off), buf)
    return [x & 0xff for x in buf]

def dump(off, n, label):
    b = rd(off, n)
    print("-- %s @0x%06x --" % (label, off))
    for r in range(0, n, 16):
        row = b[r:r+16]
        hexs = " ".join("%02x" % x for x in row)
        print("  0x%06x  %s" % (off + r, hexs))

dump(0x040ae0, 0x40, "gap around 0x40b00")
dump(0x040a30, 0x20, "refs near 0x40a40")

# decode 0x8f800 table
print("\n-- pointer table @0x8f800 (first 48 words) --")
b = rd(0x8f800, 48*4)
seen = {}
for i in range(48):
    o = i*4
    v = (b[o]<<24)|(b[o+1]<<16)|(b[o+2]<<8)|b[o+3]
    ta = space.getAddress(v) if v < 0x100000 else None
    isf = fm.getFunctionAt(ta) is not None if ta is not None else False
    nm = ""
    if ta is not None:
        f = fm.getFunctionAt(ta)
        if f is not None:
            nm = f.getName()
    print("  [%3d] 0x%06x  0x%08x  %s%s" % (i, 0x8f800+o, v, "FUNC " if isf else "     ", nm))

# how many total words in a plausible table equal 0x40b00, and table extent
print("\n-- census of value 0x00040b00 across 0x8f000..0x90000 --")
b2 = rd(0x8f000, 0x1000)
cnt = 0
first = last = None
for i in range(0, 0x1000-3, 4):
    v = (b2[i]<<24)|(b2[i+1]<<16)|(b2[i+2]<<8)|b2[i+3]
    if v == 0x40b00:
        cnt += 1
        if first is None: first = 0x8f000+i
        last = 0x8f000+i
print("  count=%d  first=0x%06x last=0x%06x" % (cnt, first or 0, last or 0))
print("== DONE ==")
