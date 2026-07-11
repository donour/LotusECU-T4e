# Find .data/.bss boundaries: dump the init constructor table at 0x0081e3e0
# (walked downward to 0xffffffff by the runtime), then disassemble each
# constructor plus the early-init candidates so the RAM/flash boundary
# immediates (the data-copy source/dest and bss start/end) are visible.
# Read-only.
# @category Recon
space = currentProgram.getAddressFactory().getDefaultAddressSpace()
mem = currentProgram.getMemory()
listing = currentProgram.getListing()
fm = currentProgram.getFunctionManager()

TABLE = 0x0081e3e0
extra = [0x0080058c, 0x0080055c, 0x008005c0, 0x0080065c]

def dis(off, maxins=80):
    a = space.getAddress(off)
    f = fm.getFunctionContaining(a)
    if f is None:
        print("  (no function @ %08x)" % off)
        return
    print("---- %s @ %08x  (%d bytes) ----" % (f.getName(), f.getEntryPoint().getOffset(),
                                                f.getBody().getNumAddresses()))
    it = listing.getInstructions(f.getBody(), True)
    k = 0
    while it.hasNext() and k < maxins:
        ins = it.next()
        print("  %s  %-26s %s" % (ins.getAddress(), ins, ins.getDefaultOperandRepresentation(0)
              if ins.getNumOperands() else ""))
        k += 1

# 1) the constructor table (descending until 0xffffffff)
print("init constructor table @ %08x (descending):" % TABLE)
ctors = []
a = space.getAddress(TABLE)
for i in range(64):
    v = mem.getInt(a) & 0xffffffff
    if v == 0xffffffff:
        break
    ctors.append(v)
    print("  [%2d] %08x" % (i, v))
    a = a.subtract(4)

# 2) disassemble each constructor
print("\n==== constructors ====")
for c in ctors:
    dis(c & 0xfffffffe)

# 3) disassemble the early-init candidates
print("\n==== early-init candidates ====")
for e in extra:
    dis(e)
