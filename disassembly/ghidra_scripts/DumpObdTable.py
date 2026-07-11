# Dump the obd_ii_handlers_mode01 table: pid, handler, handler2, length.
# Struct is 0x14 bytes: pid@0, handler@8, handler2@0xc, field@0x11 (len). Read-only.
# @category Recon
sym = None
for s in currentProgram.getSymbolTable().getSymbols("obd_ii_handlers_mode01"):
    sym = s
    break
if sym is None:
    print("symbol obd_ii_handlers_mode01 not found")
else:
    base = sym.getAddress()
    mem = currentProgram.getMemory()
    fm = currentProgram.getFunctionManager()
    STRIDE = 0x14
    N = 59
    print("obd_ii_handlers_mode01 @ %s" % base)
    print("idx pid   handler     handler2    len  curname")
    for i in range(N):
        a = base.add(i * STRIDE)
        pid = mem.getByte(a) & 0xff
        h = mem.getInt(a.add(0x8)) & 0xffffffff
        h2 = mem.getInt(a.add(0xc)) & 0xffffffff
        ln = mem.getByte(a.add(0x11)) & 0xff
        nm = ""
        if h:
            ha = currentProgram.getAddressFactory().getDefaultAddressSpace().getAddress(h)
            f = fm.getFunctionAt(ha)
            nm = f.getName() if f else "(no func @ %08x)" % h
        print("%3d 0x%02x  %08x    %08x    %3d  %s" % (i, pid, h, h2, ln, nm))
