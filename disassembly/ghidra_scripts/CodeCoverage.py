# Report code coverage of executable memory: bytes in defined functions vs undefined.
# Lists the largest undefined runs inside executable blocks (candidate missed code).
# Read-only. @category Analysis
from ghidra.program.model.listing import CodeUnit

fm = currentProgram.getFunctionManager()
listing = currentProgram.getListing()
mem = currentProgram.getMemory()

# build a set of addresses covered by functions
func_bytes = 0
for f in fm.getFunctions(True):
    func_bytes += f.getBody().getNumAddresses()

print("== executable memory blocks ==")
total_exec = 0
for b in mem.getBlocks():
    if not b.isExecute():
        continue
    total_exec += b.getSize()
    print("  %-16s %s - %s  size=0x%x  (r=%s w=%s x=%s init=%s)" % (
        b.getName(), b.getStart(), b.getEnd(), b.getSize(),
        b.isRead(), b.isWrite(), b.isExecute(), b.isInitialized()))

print("\nexec bytes total = 0x%x ; in-function bytes = 0x%x ; ratio = %.1f%%" % (
    total_exec, func_bytes, 100.0 * func_bytes / total_exec if total_exec else 0))

# find undefined runs inside executable blocks
print("\n== largest undefined runs in executable blocks (>= 0x40 bytes) ==")
runs = []
for b in mem.getBlocks():
    if not (b.isExecute() and b.isInitialized()):
        continue
    addr = b.getStart()
    end = b.getEnd()
    run_start = None
    a = addr
    while a is not None and a.compareTo(end) <= 0:
        cu = listing.getCodeUnitAt(a)
        is_undef = (cu is not None and cu.getMnemonicString() in ("??", "undefined"))
        # treat "not in a function and is a data ?? byte" as undefined code candidate
        infunc = fm.getFunctionContaining(a) is not None
        undef_here = (not infunc) and is_undef
        if undef_here:
            if run_start is None:
                run_start = a
        else:
            if run_start is not None:
                rlen = a.subtract(run_start)
                if rlen >= 0x40:
                    runs.append((rlen, run_start, a))
                run_start = None
        nxt = a.next()
        a = nxt
    if run_start is not None:
        rlen = end.subtract(run_start) + 1
        if rlen >= 0x40:
            runs.append((rlen, run_start, end))

runs.sort(reverse=True)
for rlen, s, e in runs[:40]:
    print("  0x%06x bytes  %s .. %s" % (rlen, s, e))
print("\ntotal undefined runs >=0x40:", len(runs), " summing 0x%x bytes" % sum(r[0] for r in runs))
print("== DONE ==")
