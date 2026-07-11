# Locate startup: program entry point(s), callers of main_boot, and the
# RAM extent. Also scans flash for CodeWarrior _rom_copy_info triplets
# (romStart, ramStart, size) and _bss_init_info pairs to recover the real
# .data / .bss segment boundaries. Read-only.
# @category Recon
space = currentProgram.getAddressFactory().getDefaultAddressSpace()
mem = currentProgram.getMemory()
fm = currentProgram.getFunctionManager()
st = currentProgram.getSymbolTable()
refMgr = currentProgram.getReferenceManager()
listing = currentProgram.getListing()

# entry points
print("entry points:")
for a in st.getExternalEntryPointIterator():
    f = fm.getFunctionContaining(a)
    print("  %s  %s" % (a, f.getName() if f else "?"))

# callers of main_boot
mb = None
for s in st.getSymbols("main_boot"):
    mb = s.getAddress()
if mb:
    print("\nmain_boot @ %s callers:" % mb)
    for r in refMgr.getReferencesTo(mb):
        cf = fm.getFunctionContaining(r.getFromAddress())
        print("  from %s in %s [%s]" % (r.getFromAddress(),
              cf.getName() if cf else "?", r.getReferenceType()))

# RAM blocks
print("\nmemory blocks:")
for b in mem.getBlocks():
    print("  %-16s %08x-%08x  init=%s r=%s w=%s x=%s" % (
        b.getName(), b.getStart().getOffset(), b.getEnd().getOffset(),
        b.isInitialized(), b.isRead(), b.isWrite(), b.isExecute()))

# disassemble the reset/startup function (contains the main_boot call)
print("\n==== startup / reset function ====")
sf = fm.getFunctionContaining(space.getAddress(0x00800556))
if sf is None:
    print("  no function @ 0x00800556; dumping raw from 0x00800400")
    a = space.getAddress(0x00800400)
    for _ in range(120):
        ins = listing.getInstructionAt(a)
        if ins is None:
            a = a.add(2); continue
        print("  %s  %s" % (ins.getAddress(), ins))
        a = ins.getAddress().add(ins.getLength())
else:
    print("  function %s @ %s (%d bytes)" % (sf.getName(), sf.getEntryPoint(),
          sf.getBody().getNumAddresses()))
    it = listing.getInstructions(sf.getBody(), True)
    while it.hasNext():
        ins = it.next()
        print("  %s  %s" % (ins.getAddress(), ins))

# scan flash rodata for _rom_copy_info: triplets where
#   w0 in flash (0x0..0xC00000), w1 in RAM (0x40000000..0x40080000), w2 size<0x40000
print("\nscanning flash for rom_copy_info / bss_init triplets ...")
def rd(a):
    return mem.getInt(space.getAddress(a)) & 0xffffffff
FLASH_LO, FLASH_HI = 0x00000800, 0x00c00000
RAM_LO, RAM_HI = 0x40000000, 0x40090000
hits = []
# search the rodata area near where 0x821388 lives and the boot rodata
for region in ((0x00810000, 0x0081f000), (0x00820000, 0x00824000),
               (0x00800000, 0x00801000)):
    a = region[0]
    while a < region[1]:
        try:
            w0, w1, w2 = rd(a), rd(a + 4), rd(a + 8)
        except:
            a += 4
            continue
        if (FLASH_LO <= w0 < FLASH_HI and RAM_LO <= w1 < RAM_HI
                and 0 < w2 < 0x40000 and (w2 & 3) == 0):
            hits.append(("copy", a, w0, w1, w2))
        a += 4
for (k, a, w0, w1, w2) in hits:
    print("  @%08x  ROM %08x -> RAM %08x  size %d (0x%x)  end RAM %08x" % (
        a, w0, w1, w2, w2, w1 + w2))
if not hits:
    print("  (no copy triplets found in scanned regions)")
