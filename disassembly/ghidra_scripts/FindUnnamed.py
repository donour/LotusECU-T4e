# READ-ONLY: list still-unnamed FUN_/thunk functions in a flash range, ranked by
# caller count (most-referenced first = highest-leverage to name). Skips tiny thunks.
# Args: optional "startHex endHex minCallers" (defaults: a00000 b00000 3).
# @category Analysis
fm = currentProgram.getFunctionManager()
space = currentProgram.getAddressFactory().getDefaultAddressSpace()

args = list(getScriptArgs())
start = int(args[0], 16) if len(args) > 0 else 0xa00000
end   = int(args[1], 16) if len(args) > 1 else 0xb00000
mincall = int(args[2]) if len(args) > 2 else 3

rows = []
for f in fm.getFunctions(True):
    ep = f.getEntryPoint()
    a = ep.getOffset()
    if a < start or a >= end:
        continue
    nm = f.getName()
    if not (nm.startswith("FUN_") or nm.startswith("thunk_FUN_")):
        continue
    nc = len(list(f.getCallingFunctions(monitor)))
    if nc < mincall:
        continue
    body = f.getBody().getNumAddresses()
    rows.append((nc, body, nm, str(ep)))

rows.sort(reverse=True)
print("=== unnamed FUN_ in [%06x,%06x), callers>=%d : %d funcs ===" % (start, end, mincall, len(rows)))
print("callers  bytes  name @addr")
for nc, body, nm, addr in rows[:80]:
    print("  %4d  %5d  %-18s @%s" % (nc, body, nm, addr))
print("== DONE ==")
