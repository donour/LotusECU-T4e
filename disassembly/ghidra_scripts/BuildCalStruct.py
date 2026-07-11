# Build a `Calibration` struct from the calibration lookup call sites.
#
# Calibration tables are accessed as CALBASE_addr + <const offset>, where
# CALBASE_addr is a runtime pointer (RAM copy 0x4002e000 or flash original
# 0x20000). Because the base is dynamic, Ghidra can't auto-label the tables.
# This script scans every call to the known lookup functions, recovers the
# constant offset (and element type + length) of each table/axis pointer
# argument, and proposes members for a single `Calibration` structure.
#
# Dry-run by default: prints (and CSVs) the proposed members so they can be
# reviewed.  Pass "apply" to actually:
#   - (re)create the `Calibration` struct (size 0x10000)
#   - place an instance at flash 0x20000 and RAM 0x4002e000
#   - retype the CALBASE_addr global to `Calibration *`
#
# Usage (read-only review):
#   analyzeHeadless <proj> "Lotus ECU" -process emira -readOnly -noanalysis \
#       -scriptPath <dir> -postScript BuildCalStruct.py
# Apply (writes DB -- omit -readOnly):
#       ... -postScript BuildCalStruct.py apply
#
# @category Calibration
import os
from ghidra.app.decompiler import DecompInterface
from ghidra.util.task import ConsoleTaskMonitor
from ghidra.program.model.pcode import PcodeOp
from ghidra.program.model.data import (StructureDataType, ArrayDataType,
    UnsignedShortDataType, UnsignedCharDataType, PointerDataType, CategoryPath)

CAL_SIZE = 0x10000
CAL_RAM = 0x4002e000
CAL_FLASH = 0x20000

args = [a.lower() for a in getScriptArgs()]
APPLY = "apply" in args

fm = currentProgram.getFunctionManager()
refMgr = currentProgram.getReferenceManager()
st = currentProgram.getSymbolTable()
space = currentProgram.getAddressFactory().getDefaultAddressSpace()
monitor = ConsoleTaskMonitor()

# ---- resolve CALBASE_addr symbol (for base confirmation) -------------------
calbase_off = None
for s in st.getSymbols("CALBASE_addr"):
    calbase_off = s.getAddress().getOffset()
    break
print("CALBASE_addr @ %s" % ("%x" % calbase_off if calbase_off is not None else "??"))

# ---- build per-function arg config -----------------------------------------
# role: 'data' or 'axis'; lenkey: how to size the array from the call's
# constant args ('a0','a1','prod01','fix256'); elem: byte width or None=detect.
LOOKUPS = {
    "lookup2d_interpolated_u16": [
        (2, "data", "a0", None),   # element width detected from each overload
        (3, "axis", "a0", None),
    ],
    "lookup1d_interpolated_u8": [
        (2, "data", "fix256", 1),
    ],
    "lookup3d_interp_u16": [
        (4, "data", "prod01", 2),
        (5, "axis", "a0", 2),
        (6, "axis", "a1", 2),
    ],
}

def ptr_elem_len(func, idx):
    """Element width of a pointer parameter, or None if unknown."""
    try:
        p = func.getParameter(idx)
        dt = p.getDataType()
        inner = dt.getDataType()       # Pointer.getDataType() -> pointee
        n = inner.getLength()
        if n in (1, 2, 4):
            return n
    except:
        pass
    return None

# map entry-address offset -> (name, [(idx, role, lenkey, elem)])
targets = {}
for name in LOOKUPS:
    for func in fm.getFunctions(True):
        if func.getName() != name:
            continue
        specs = []
        for (idx, role, lenkey, elem) in LOOKUPS[name]:
            e = elem if elem is not None else ptr_elem_len(func, idx)
            specs.append((idx, role, lenkey, e))
        targets[func.getEntryPoint().getOffset()] = (name, func, specs)
        print("  target %s @ %s  specs=%s" % (
            name, func.getEntryPoint(),
            ["a%d:%s:%s:e%s" % (i, r, lk, e) for (i, r, lk, e) in specs]))

if not targets:
    print("!! no lookup functions found -- nothing to do")

# ---- p-code helpers --------------------------------------------------------
PASS_OPS = (PcodeOp.CAST, PcodeOp.COPY, PcodeOp.INT_ZEXT, PcodeOp.INT_SEXT,
            PcodeOp.SUBPIECE, PcodeOp.MULTIEQUAL, PcodeOp.INDIRECT)

def classify_base(vn, depth=0):
    """Best-effort: does this varnode trace back to CALBASE_addr?"""
    if vn is None or depth > 8:
        return "?"
    if vn.isConstant():
        v = vn.getOffset() & 0xffffffff
        if v in (CAL_RAM, CAL_FLASH):
            return "CAL"
        return "C:%x" % v
    if vn.isAddress() and calbase_off is not None and vn.getAddress().getOffset() == calbase_off:
        return "CAL"
    op = vn.getDef()
    if op is None:
        return "param"
    opc = op.getOpcode()
    if opc == PcodeOp.LOAD:
        ptr = op.getInput(1)
        if ptr.isConstant() and calbase_off is not None and (ptr.getOffset() & 0xffffffff) == calbase_off:
            return "CAL"
        return classify_base(ptr, depth + 1)
    if opc in PASS_OPS or opc == PcodeOp.INT_ADD:
        return classify_base(op.getInput(0), depth + 1)
    return "?"

def extract_off(vn, depth=0, acc=0):
    """Return (offset, base_kind) if vn == base + sum(consts), else None.
    Accumulates constants across chained INT_ADDs (base + c1 + c2)."""
    if vn is None or depth > 10 or vn.isConstant():
        return None
    op = vn.getDef()
    if op is None:
        return None
    opc = op.getOpcode()
    if opc in (PcodeOp.INT_ADD, PcodeOp.PTRADD, PcodeOp.PTRSUB):
        i0, i1 = op.getInput(0), op.getInput(1)
        c = other = None
        if i0.isConstant():
            c, other = i0.getOffset(), i1
        elif i1.isConstant():
            c, other = i1.getOffset(), i0
        if c is not None:
            if opc == PcodeOp.PTRADD and op.getNumInputs() > 2:
                c = c * op.getInput(2).getOffset()
            # try to fold further constants from the non-const operand
            sub = extract_off(other, depth + 1, acc + c)
            if sub is not None:
                return sub
            return ((acc + c) & 0xffffffff, classify_base(other))
    if opc in PASS_OPS:
        return extract_off(op.getInput(0), depth + 1, acc)
    return None

def const_arg(vn):
    """Constant value of an arg varnode, or None."""
    if vn is None:
        return None
    if vn.isConstant():
        return vn.getOffset() & 0xffffffff
    op = vn.getDef()
    if op is not None and op.getOpcode() in PASS_OPS:
        return const_arg(op.getInput(0))
    return None

# ---- scan all call sites ---------------------------------------------------
# proposals keyed by offset -> dict(len,elem,role,kind,srcs=set,sizes=set)
proposals = {}
unresolved = []     # (caller, call_addr, name, argidx) we couldn't size/offset
stats = {"calls": 0, "args": 0, "cal": 0, "other": 0}

decomp = DecompInterface()
decomp.openProgram(currentProgram)

# group call sites by caller so we decompile each caller once
callers = {}
for entryoff in targets:
    entry = space.getAddress(entryoff)
    for ref in refMgr.getReferencesTo(entry):
        if not ref.getReferenceType().isCall():
            continue
        cf = fm.getFunctionContaining(ref.getFromAddress())
        if cf is None:
            continue
        callers.setdefault(cf.getEntryPoint().getOffset(), cf)

print("\nscanning %d caller functions ..." % len(callers))

for cf in callers.values():
    res = decomp.decompileFunction(cf, 60, monitor)
    if res is None or not res.decompileCompleted():
        continue
    hf = res.getHighFunction()
    if hf is None:
        continue
    ops = hf.getPcodeOps()
    while ops.hasNext():
        op = ops.next()
        if op.getOpcode() != PcodeOp.CALL:
            continue
        tgt = op.getInput(0)
        if not tgt.isAddress():
            continue
        toff = tgt.getAddress().getOffset()
        if toff not in targets:
            continue
        name, func, specs = targets[toff]
        stats["calls"] += 1
        callsite = op.getSeqnum().getTarget()
        # gather constant size args
        a0 = const_arg(op.getInput(1)) if op.getNumInputs() > 1 else None
        a1 = const_arg(op.getInput(2)) if op.getNumInputs() > 2 else None
        # resolve every base-relative pointer arg first
        resolved = []   # [idx, role, off, kind, count, elem]
        for (idx, role, lenkey, elem) in specs:
            stats["args"] += 1
            if op.getNumInputs() <= idx + 1:
                continue
            got = extract_off(op.getInput(idx + 1))
            if got is None:
                unresolved.append((cf.getName(), callsite, name, idx))
                continue
            off, kind = got
            stats["cal" if kind == "CAL" else "other"] += 1
            if off >= CAL_SIZE:
                continue
            if lenkey == "a0":
                n = a0
            elif lenkey == "a1":
                n = a1
            elif lenkey == "prod01":
                n = (a0 * a1) if (a0 and a1) else None
            else:                       # fix256
                n = 256
            resolved.append([idx, role, off, kind, n, elem])
        # infer u8 vs u16 for a 1-D (lookup2d) pair from the pointer spacing:
        # the two arrays are adjacent, so gap == count*elem_bytes.
        if name == "lookup2d_interpolated_u16" and len(resolved) == 2:
            n = resolved[0][4]
            gap = abs(resolved[0][2] - resolved[1][2])
            e = None
            if n:
                if gap == n:
                    e = 1
                elif gap == 2 * n:
                    e = 2
            if e:
                resolved[0][5] = resolved[1][5] = e
        # emit members
        for (idx, role, off, kind, n, elem) in resolved:
            e = elem if elem else 2
            blen = (n * e) if n else e   # unknown count -> placeholder
            p = proposals.get(off)
            if p is None:
                proposals[off] = dict(len=blen, elem=e, role=role, kind=kind,
                                      srcs=set([cf.getName()]), counts=set([n]))
            else:
                p["len"] = max(p["len"], blen)
                p["elem"] = min(p["elem"], e)   # prefer the tighter width
                p["srcs"].add(cf.getName())
                p["counts"].add(n)
                if role not in p["role"]:
                    p["role"] = p["role"] + "+" + role

decomp.dispose()

# ---- right-size: cap each member at the gap to the next -------------------
# Prevents overlaps and fixes 1-D u8 tables (no size arg -> over-large default).
offs = sorted(proposals.keys())
capped_n = 0
for i, off in enumerate(offs):
    p = proposals[off]
    nxt = offs[i + 1] if i + 1 < len(offs) else CAL_SIZE
    gap = nxt - off
    if p["len"] > gap:
        p["raw"] = p["len"]
        p["len"] = gap
        capped_n += 1

# ---- report ----------------------------------------------------------------
print("\n==== proposed Calibration members (%d) ====" % len(offs))
print("  offset   len  elem role   counts         src(s)   (*=capped)")
for off in offs:
    p = proposals[off]
    cnts = ",".join(str(c) for c in sorted([c for c in p["counts"] if c]))
    print("  +0x%04x  %4d%s u%d   %-5s %-14s %s" % (
        off, p["len"], "*" if "raw" in p else " ", p["elem"] * 8, p["role"],
        cnts or "?", ",".join(sorted(p["srcs"]))[:55]))

print("\nstats: calls=%(calls)d argptrs=%(args)d base=CAL:%(cal)d other:%(other)d"
      % stats)
print("members capped to next-offset gap: %d" % capped_n)
print("unresolved arg ptrs: %d" % len(unresolved))
for (cn, ca, nm, ix) in unresolved[:25]:
    print("  ?? %s @ %s  %s arg%d" % (cn, ca, nm, ix))

# write CSV for review
try:
    tmp = os.path.join(os.environ.get("TEMP", "/tmp"), "cal_members.csv")
    f = open(tmp, "w")
    f.write("offset,byte_len,elem_bytes,role,counts,sources\n")
    for off in offs:
        p = proposals[off]
        cnts = "|".join(str(c) for c in sorted([c for c in p["counts"] if c]))
        f.write("0x%04x,%d,%d,%s,%s,%s\n" % (
            off, p["len"], p["elem"], p["role"], cnts,
            "|".join(sorted(p["srcs"]))))
    f.close()
    print("\nCSV written: %s" % tmp)
except Exception as e:
    print("CSV write failed: %s" % e)

# ---- apply -----------------------------------------------------------------
if not APPLY:
    print("\n(dry-run) re-run with 'apply' (and without -readOnly) to write the DB.")
else:
    print("\n==== APPLYING ====")
    dtm = currentProgram.getDataTypeManager()
    cat = CategoryPath("/cal")
    # fresh struct
    existing = dtm.getDataType(cat, "Calibration")
    if existing is not None:
        dtm.remove(existing, monitor)
    cal = StructureDataType(cat, "Calibration", CAL_SIZE)
    skipped = 0
    for off in offs:
        p = proposals[off]
        elem = UnsignedShortDataType() if p["elem"] == 2 else (
            UnsignedCharDataType() if p["elem"] == 1 else UnsignedShortDataType())
        cnt = max(1, p["len"] // p["elem"])
        dt = ArrayDataType(elem, cnt, p["elem"])
        nm = "%s_%04x" % ("axis" if p["role"] == "axis" else "tbl", off)
        cm = "from %s; counts=%s" % (
            ",".join(sorted(p["srcs"]))[:80],
            ",".join(str(c) for c in sorted([c for c in p["counts"] if c])))
        try:
            cal.replaceAtOffset(off, dt, p["len"], nm, cm)
        except Exception as e:
            skipped += 1
            print("  overlap/skip +0x%04x (%s): %s" % (off, nm, e))
    cal = dtm.addDataType(cal, None)
    print("  Calibration struct: %d members, %d skipped (overlaps)" % (
        len(offs) - skipped, skipped))

    # place instances where bytes/blocks exist
    for tag, a in (("flash", CAL_FLASH), ("ram", CAL_RAM)):
        addr = space.getAddress(a)
        try:
            clearListing(addr, addr.add(CAL_SIZE - 1))
            createData(addr, cal)
            createLabel(addr, "CAL_%s" % tag, True)
            print("  placed Calibration @ %s (%s)" % (addr, tag))
        except Exception as e:
            print("  could not place @ %s (%s): %s" % (addr, tag, e))

    # retype CALBASE_addr global -> Calibration*
    if calbase_off is not None:
        ca = space.getAddress(calbase_off)
        try:
            clearListing(ca, ca.add(3))
            createData(ca, PointerDataType(cal))
            print("  retyped CALBASE_addr @ %s -> Calibration*" % ca)
        except Exception as e:
            print("  could not retype CALBASE_addr: %s" % e)
    print("==== DONE (review decompilation, then save/commit in GUI) ====")
