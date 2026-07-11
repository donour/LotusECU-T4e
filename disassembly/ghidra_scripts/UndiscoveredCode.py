# Read-only audit for missed/misclassified code in flash (0x0..0x100000).
#  1) Bound the real code region (min/max flash function entry).
#  2) Census the 4-byte function-start signatures of known functions (VLE prologue).
#  3) Find UNDEFINED runs that sit INSIDE the code region (true missed-code suspects).
#  4) Scan 4-byte-aligned flash words for pointers landing on undefined/mid-data
#     addresses inside the code region = candidate indirect-call targets to missed code.
#  5) Scan those undefined-in-code runs for the dominant prologue signature at
#     even offsets = candidate function starts even without a referencing pointer.
#  6) Flag any DEFINED DATA inside the code region whose first bytes match a prologue
#     (data-that-is-actually-code).
# @category Analysis
import jarray
fm = currentProgram.getFunctionManager()
listing = currentProgram.getListing()
mem = currentProgram.getMemory()
space = currentProgram.getAddressFactory().getDefaultAddressSpace()

FLASH = 0x100000

# ---- read whole flash into a flat bytearray (block by block; tolerate gaps) ----
raw = bytearray(FLASH)
init = bytearray(FLASH)
for b in mem.getBlocks():
    bs = b.getStart().getOffset()
    be = b.getEnd().getOffset()
    if be < 0 or bs >= FLASH or not b.isInitialized():
        continue
    lo = max(bs, 0)
    hi = min(be, FLASH - 1)
    n = hi - lo + 1
    buf = jarray.zeros(n, 'b')
    mem.getBytes(space.getAddress(lo), buf)
    for i in range(n):
        raw[lo + i] = buf[i] & 0xff
        init[lo + i] = 1

# ---- 1) function bounds + 2) prologue census ----
entries = []
prol = {}
for f in fm.getFunctions(True):
    off = f.getEntryPoint().getOffset()
    if off >= FLASH:
        continue
    entries.append(off)
    if init[off] and init[off + 3]:
        k = "%02x %02x %02x %02x" % (raw[off], raw[off+1], raw[off+2], raw[off+3])
        prol[k] = prol.get(k, 0) + 1
entries.sort()
eset = set(entries)
CODE_LO = entries[0]
CODE_HI = entries[-1]
print("flash functions: %d ; entry range 0x%06x .. 0x%06x (span 0x%x)" % (
    len(entries), CODE_LO, CODE_HI, CODE_HI - CODE_LO))
top_prol = sorted(prol.items(), key=lambda kv: -kv[1])
print("== top function-start 4-byte signatures ==")
for k, v in top_prol[:12]:
    print("  %5d  %s" % (v, k))
sig2 = {}   # first-2-byte prologue -> count
for k, v in prol.items():
    kk = k[:5]
    sig2[kk] = sig2.get(kk, 0) + v
good2 = set(kk for kk, v in sig2.items() if v >= 3)   # halfword prologues seen >=3x
print("== dominant 2-byte prologues (>=3 funcs) ==", sorted(good2))

def U32(o):
    return (raw[o] << 24) | (raw[o+1] << 16) | (raw[o+2] << 8) | raw[o+3]
def U16(o):
    return (raw[o] << 8) | raw[o+1]

def is_undef(a):
    cu = listing.getCodeUnitAt(a)
    return cu is not None and cu.getMnemonicString() in ("??", "undefined")
def in_insn(a):
    return listing.getInstructionContaining(a) is not None
def in_func(a):
    return fm.getFunctionContaining(a) is not None

# ---- 3) undefined runs INSIDE code region ----
print("\n== undefined runs INSIDE code region [0x%06x..0x%06x] ==" % (CODE_LO, CODE_HI))
undef_in_code = []   # (start_off, end_off_exclusive)
o = CODE_LO
run = None
while o <= CODE_HI:
    a = space.getAddress(o)
    u = (not in_func(a)) and is_undef(a)
    if u:
        if run is None:
            run = o
    else:
        if run is not None:
            undef_in_code.append((run, o))
            run = None
    o += 1
if run is not None:
    undef_in_code.append((run, CODE_HI + 1))
tot = 0
for s, e in sorted(undef_in_code, key=lambda x: -(x[1]-x[0])):
    tot += e - s
    print("  0x%06x .. 0x%06x  (0x%x bytes)  first: %02x %02x %02x %02x" % (
        s, e, e - s, raw[s] & 0xff, raw[s+1] & 0xff, raw[s+2] & 0xff, raw[s+3] & 0xff))
print("  total undefined-in-code = 0x%x bytes across %d runs" % (tot, len(undef_in_code)))
uic = set()
for s, e in undef_in_code:
    for x in range(s, e):
        uic.add(x)

# ---- 4) pointers (4B aligned) into undefined/mid-insn code addrs ----
print("\n== candidate indirect-call targets: aligned BE words -> non-entry code addr ==")
cand = {}
for o in range(0, FLASH - 3, 4):
    v = U32(o)
    if CODE_LO <= v <= CODE_HI and (v & 1) == 0:
        if v in eset:
            continue
        ta = space.getAddress(v)
        # interesting only if target is undefined or lands mid-instruction (not a clean insn head)
        if v in uic or (in_insn(ta) and listing.getInstructionAt(ta) is None):
            cand.setdefault(v, []).append(o)
for v in sorted(cand):
    locs = cand[v]
    tag = "UNDEF" if v in uic else "mid-insn"
    print("  target 0x%06x  [%s]  referenced-from %s%s" % (
        v, tag, ["0x%06x" % l for l in locs[:6]], " +%d" % (len(locs)-6) if len(locs) > 6 else ""))
if not cand:
    print("  (none)")

# ---- 5) prologue signatures inside undefined-in-code runs ----
print("\n== prologue-signature hits inside undefined-in-code runs (even offsets) ==")
hits = []
for s, e in undef_in_code:
    o = s if s % 2 == 0 else s + 1
    while o + 1 < e:
        if ("%02x %02x" % (raw[o] & 0xff, raw[o+1] & 0xff)) in good2:
            hits.append(o)
        o += 2
for o in hits[:60]:
    print("  0x%06x  %02x %02x %02x %02x" % (o, raw[o]&0xff, raw[o+1]&0xff, raw[o+2]&0xff, raw[o+3]&0xff))
print("  total prologue hits in undefined-in-code:", len(hits))

# ---- 6) defined DATA in code region whose head matches a prologue ----
print("\n== defined DATA inside code region with prologue-looking head ==")
dhits = []
di = listing.getDefinedData(space.getAddress(CODE_LO), True)
while di.hasNext():
    d = di.next()
    a = d.getAddress()
    off = a.getOffset()
    if off > CODE_HI:
        break
    if off < CODE_LO:
        continue
    try:
        if ("%02x %02x" % (raw[off]&0xff, raw[off+1]&0xff)) in good2:
            dhits.append((off, d.getDataType().getName(), d.getLength()))
    except:
        pass
for off, tn, ln in dhits[:40]:
    print("  0x%06x  type=%-16s len=%d  head %02x %02x %02x %02x" % (
        off, tn, ln, raw[off]&0xff, raw[off+1]&0xff, raw[off+2]&0xff, raw[off+3]&0xff))
print("  total data-with-prologue-head:", len(dhits))
print("== DONE ==")
