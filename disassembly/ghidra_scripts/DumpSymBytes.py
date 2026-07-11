# READ-ONLY: for each symbol name arg, print its address, and whether the bytes
# there (up to a small window) are all 0xFF (blank) plus the first 16 bytes.
# @category Analysis
st = currentProgram.getSymbolTable()
mem = currentProgram.getMemory()

def first_addr(name):
    for s in st.getGlobalSymbols(name):
        return s.getAddress()
    for s in st.getSymbols(name):
        return s.getAddress()
    return None

for name in getScriptArgs():
    a = first_addr(name)
    if a is None:
        print("  %-24s : NOT FOUND" % name); continue
    n = 0x88
    blank = True
    bs = []
    for i in range(n):
        try:
            b = mem.getByte(a.add(i)) & 0xff
        except:
            b = None
        if i < 16:
            bs.append("--" if b is None else "%02x" % b)
        if b != 0xff:
            blank = False
    print("  %-24s @ %s  all_0xFF[0x%x]=%s  first16: %s" % (name, a, n, blank, " ".join(bs)))
print("== DONE ==")
