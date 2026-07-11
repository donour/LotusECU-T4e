# Find function-pointer tables: runs of >=4 aligned 4-byte big-endian values that point into the
# code region. For each table, report how many targets are NOT yet functions (= missed code).
# Also dumps the reset/boot area and any obvious vector tables. Read-only. @category Analysis
from ghidra.program.model.address import AddressSet

mem = currentProgram.getMemory()
fm = currentProgram.getFunctionManager()
listing = currentProgram.getListing()
space = currentProgram.getAddressFactory().getDefaultAddressSpace()

CODE_LO, CODE_HI = 0x00800000, 0x00AD0000   # real app code range (excludes null/low noise)

def rd32(a):
    try:
        return mem.getInt(space.getAddress(a)) & 0xffffffff
    except:
        return None

def is_code_ptr(v):
    return v is not None and CODE_LO <= v < CODE_HI and (v & 1) == 0

def initialized_ranges():
    out = []
    for b in mem.getBlocks():
        if b.isInitialized() and b.isExecute():
            out.append((b.getStart().getOffset(), b.getEnd().getOffset()))
    return out

def has_func(v):
    return fm.getFunctionAt(space.getAddress(v)) is not None

print("== scanning for pointer tables (>=4 consecutive code pointers, 4-byte aligned) ==")
tables = []
for lo, hi in initialized_ranges():
    a = (lo + 3) & ~3
    run = []
    while a <= hi - 3:
        v = rd32(a)
        if is_code_ptr(v):
            run.append((a, v))
        else:
            if len(run) >= 3:
                tables.append(run)
            run = []
        a += 4
    if len(run) >= 3:
        tables.append(run)

# rank tables by number of undefined targets
scored = []
for t in tables:
    tgts = [v for (_, v) in t]
    undef = sum(0 if has_func(v) else 1 for v in tgts)
    scored.append((undef, len(t), t[0][0], tgts))
scored.sort(reverse=True)

total_undef_targets = set()
print("found %d candidate tables; top by #undefined targets:" % len(tables))
for undef, n, start, tgts in scored[:30]:
    uniq = len(set(tgts))
    for v in tgts:
        if not has_func(v):
            total_undef_targets.add(v)
    print("  table@0x%06x  entries=%-4d undef=%-4d uniq=%-4d  tgts=[%s%s]" % (
        start, n, undef, uniq, " ".join("0x%06x" % v for v in tgts[:8]),
        " ..." if n > 8 else ""))
print("\nDISTINCT undefined targets across top tables: %d" % len(total_undef_targets))

print("\n== reset / boot area (first words at 0x0 and 0x800000) ==")
for base in (0x0, 0x800000, 0x800400):
    vals = [rd32(base + 4*i) for i in range(8)]
    print("  0x%06x: %s" % (base, " ".join(("None" if v is None else "0x%08x" % v) for v in vals)))
print("== DONE ==")
