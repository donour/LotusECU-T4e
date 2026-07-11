# Map the internal layout of the learned_main block (0x4001735C..0x4001B2EC):
# list every referenced offset, the functions that READ vs WRITE it, so the
# sub-tables and their updaters become visible. Read-only.
# @category Recon
from ghidra.program.model.address import AddressSet

LO, HI = 0x4001735c, 0x4001b2ec
space = currentProgram.getAddressFactory().getDefaultAddressSpace()
refMgr = currentProgram.getReferenceManager()
fm = currentProgram.getFunctionManager()

aset = AddressSet(space.getAddress(LO), space.getAddress(HI))
it = refMgr.getReferenceDestinationIterator(aset, True)

rows = []   # (offset, n_read, n_write, writers set, readers set)
while it.hasNext():
    a = it.next()
    off = a.getOffset()
    nr = nw = 0
    writers = set()
    readers = set()
    for r in refMgr.getReferencesTo(a):
        rt = r.getReferenceType()
        cf = fm.getFunctionContaining(r.getFromAddress())
        nm = cf.getName() if cf else "?"
        if rt.isWrite():
            nw += 1
            writers.add(nm)
        elif rt.isRead():
            nr += 1
            readers.add(nm)
        else:
            readers.add(nm)
    rows.append((off, nr, nw, writers, readers))

rows.sort()
print("learned_main layout: %d referenced offsets in %08x..%08x" % (len(rows), LO, HI))
print(" offset    rd wr  writers / readers")
prev = LO
for (off, nr, nw, writers, readers) in rows:
    gap = off - prev
    gtag = ("  <-- +0x%x gap" % gap) if gap >= 0x40 else ""
    who = ("W:" + ",".join(sorted(writers))) if writers else ("R:" + ",".join(sorted(readers)))
    print("  +0x%04x  %2d %2d  %s%s" % (off - LO, nr, nw, who[:80], gtag))
    prev = off

# summarize distinct writer functions
allw = {}
for (off, nr, nw, writers, readers) in rows:
    for w in writers:
        allw.setdefault(w, []).append(off - LO)
print("\nwriter functions (%d):" % len(allw))
for w in sorted(allw, key=lambda k: min(allw[k])):
    offs = sorted(allw[w])
    print("  %-28s writes offsets +0x%04x..+0x%04x (%d)" % (
        w, offs[0], offs[-1], len(offs)))
