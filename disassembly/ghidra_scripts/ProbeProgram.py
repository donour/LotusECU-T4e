# Read-only diagnostic dump: language, memory blocks, function/symbol counts,
# and whether the listing has any disassembly yet. Generic (not emira-specific).
# @category Recon
p = currentProgram
mem = p.getMemory()
fm = p.getFunctionManager()
st = p.getSymbolTable()
listing = p.getListing()

print("==== PROGRAM ====")
print("name=%s" % p.getName())
print("path=%s" % p.getDomainFile().getPathname())
print("language=%s" % p.getLanguageID())
print("compilerSpec=%s" % p.getCompilerSpec().getCompilerSpecID())
print("imageBase=%s" % p.getImageBase())
print("executablePath=%s" % p.getExecutablePath())

print("\n==== MEMORY BLOCKS ====")
for b in mem.getBlocks():
    print("  %-16s %08x-%08x  len=0x%x  init=%s r=%s w=%s x=%s src=%s" % (
        b.getName(), b.getStart().getOffset(), b.getEnd().getOffset(),
        b.getSize(), b.isInitialized(), b.isRead(), b.isWrite(), b.isExecute(),
        b.getSourceName()))

print("\n==== COUNTS ====")
print("functionCount=%d" % fm.getFunctionCount())
print("definedDataCount=%d" % listing.getNumDefinedData())
print("instructionCount=%d" % listing.getNumInstructions())
print("symbolCount=%d" % st.getNumSymbols())

print("\n==== ENTRY POINTS ====")
for a in st.getExternalEntryPointIterator():
    print("  %s" % a)

print("\n==== SAMPLE BYTES ====")
def show(addr_hex, n=16):
    from ghidra.program.model.address import Address
    a = p.getAddressFactory().getDefaultAddressSpace().getAddress(addr_hex)
    try:
        bs = []
        for i in range(n):
            bs.append("%02x" % (mem.getByte(a.add(i)) & 0xff))
        print("  %s: %s" % (a, " ".join(bs)))
    except Exception as e:
        print("  %s: <error %s>" % (a, e))

show(0x00020000)
show(0x00800000)
show(0x00A00000)
show(0x00A00010)
