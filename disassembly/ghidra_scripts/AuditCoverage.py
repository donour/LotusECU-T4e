# Completeness audit of the program's initialized memory:
#  - coverage ratio (bytes in functions vs total initialized)
#  - every undefined run (neither code-in-function nor defined data), with first
#    bytes and flags for RTI (0x80) / RTS (0x81) terminators (ISR / thunk candidates)
#  - function map in address order with inter-function gaps
# Read-only. @category Analysis
fm = currentProgram.getFunctionManager()
listing = currentProgram.getListing()
mem = currentProgram.getMemory()

def bytestr(a, n):
    out = []
    for i in range(n):
        try: out.append("%02x" % (mem.getByte(a.add(i)) & 0xff))
        except: out.append("--")
    return " ".join(out)

def has_op(a, end, op):
    x = a
    while x.compareTo(end) <= 0:
        try:
            if (mem.getByte(x) & 0xff) == op: return True
        except: pass
        x = x.next()
    return False

total = infunc = 0
for b in mem.getBlocks():
    if not b.isInitialized(): continue
    total += b.getSize()
for f in fm.getFunctions(True):
    infunc += f.getBody().getNumAddresses()
print("initialized=0x%x  in-function=0x%x  coverage=%.1f%%" % (
    total, infunc, 100.0*infunc/total if total else 0))

print("\n== undefined runs (not in a function, not defined data) ==")
nundef = 0
for b in mem.getBlocks():
    if not b.isInitialized(): continue
    a = b.getStart(); end = b.getEnd(); run = None
    while a is not None and a.compareTo(end) <= 0:
        infn = fm.getFunctionContaining(a) is not None
        cu = listing.getDataContaining(a)
        defined_data = (cu is not None and cu.isDefined())
        undef = (not infn) and (not defined_data)
        if undef:
            if run is None: run = a
        else:
            if run is not None:
                rl = a.subtract(run); nundef += rl
                rti = has_op(run, a.previous(), 0x80); rts = has_op(run, a.previous(), 0x81)
                print("  %s..%s  len=0x%-4x %s%s  [%s ...]" % (
                    run, a.previous(), rl, "RTI " if rti else "", "RTS" if rts else "",
                    bytestr(run, min(rl, 16))))
                run = None
        a = a.next()
    if run is not None:
        rl = end.subtract(run) + 1; nundef += rl
        print("  %s..%s  len=0x%-4x  [%s ...]" % (run, end, rl, bytestr(run, min(rl, 16))))
print("total undefined = 0x%x bytes" % nundef)

print("\n== function map (addr order) with gaps ==")
prev_end = None
for f in sorted(fm.getFunctions(True), key=lambda f: f.getEntryPoint().getOffset()):
    s = f.getEntryPoint()
    if prev_end is not None:
        gap = s.subtract(prev_end)
        if gap > 0:
            print("        ---- gap 0x%x ----" % gap)
    e = f.getBody().getMaxAddress()
    print("  %s..%s  %s" % (s, e, f.getName()))
    prev_end = e.next()
print("== DONE ==")
