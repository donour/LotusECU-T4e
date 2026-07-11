# Identify calibration tables for naming/scaling (RomRaider def work).
#
# For every lookup call site, recover for each DATA table:
#   - table offset, element width, entry count
#   - the INDEX variable being looked up (axis quantity)   <- strongest signal
#   - the DESTINATION variable the result feeds            <- what it produces
#   - the axis offset and its real breakpoint values from flash 0x20000
#   - the source function(s)
# Emits a readable report + CSV.  Read-only.
#
# Pass "apply" (and drop -readOnly) to rename the Calibration struct AXIS members
# by detected input quantity (conservative: only when the index var is clearly
# named, or breakpoints are unmistakably monotonic RPM).
#
# @category Calibration
import os
from ghidra.app.decompiler import DecompInterface
from ghidra.util.task import ConsoleTaskMonitor
from ghidra.program.model.pcode import PcodeOp
from ghidra.program.model.data import CategoryPath

CAL_SIZE = 0x10000
CAL_FLASH = 0x20000
APPLY = "apply" in [a.lower() for a in getScriptArgs()]

fm = currentProgram.getFunctionManager()
refMgr = currentProgram.getReferenceManager()
st = currentProgram.getSymbolTable()
mem = currentProgram.getMemory()
space = currentProgram.getAddressFactory().getDefaultAddressSpace()
monitor = ConsoleTaskMonitor()

calbase_off = None
for s in st.getSymbols("CALBASE_addr"):
    calbase_off = s.getAddress().getOffset()
    break

# func-name -> arg roles. idx_args = which call args are the looked-up value(s).
# ptr specs: (argidx, role, lenkey)
LOOKUPS = {
    "lookup2d_interpolated_u16": dict(
        idx=[1], ptrs=[(2, "data", "a0"), (3, "axis", "a0")]),
    "lookup1d_interpolated_u8": dict(
        idx=[1], ptrs=[(2, "data", "fix256")]),
    "lookup3d_interp_u16": dict(
        idx=[2, 3], ptrs=[(4, "data", "prod01"), (5, "axisx", "a0"), (6, "axisy", "a1")]),
}

targets = {}
for name in LOOKUPS:
    for func in fm.getFunctions(True):
        if func.getName() == name:
            targets[func.getEntryPoint().getOffset()] = (name, LOOKUPS[name])

PASS_OPS = (PcodeOp.CAST, PcodeOp.COPY, PcodeOp.INT_ZEXT, PcodeOp.INT_SEXT,
            PcodeOp.SUBPIECE, PcodeOp.MULTIEQUAL, PcodeOp.INDIRECT)

def extract_off(vn, depth=0, acc=0):
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
            sub = extract_off(other, depth + 1, acc + c)
            if sub is not None:
                return sub
            return (acc + c) & 0xffffffff
    if opc in PASS_OPS:
        return extract_off(op.getInput(0), depth + 1, acc)
    return None

def vname(vn, depth=0):
    """Best-effort human name for a varnode (high var / global symbol)."""
    if vn is None or depth > 6:
        return None
    h = vn.getHigh()
    if h is not None:
        sym = h.getSymbol()
        if sym is not None and sym.getName():
            return sym.getName()
        nm = h.getName()
        if nm and nm.lower() not in ("unnamed", "unique", "null"):
            return nm
    if vn.isConstant():
        return "#0x%x" % (vn.getOffset() & 0xffffffff)
    if vn.isAddress():
        s = getSymbolAt(vn.getAddress())
        if s is not None:
            return s.getName()
    op = vn.getDef()
    if op is not None:
        opc = op.getOpcode()
        if opc == PcodeOp.LOAD:
            ptr = op.getInput(1)
            if ptr.isConstant():
                s = getSymbolAt(space.getAddress(ptr.getOffset() & 0xffffffff))
                if s is not None:
                    return s.getName()
            return vname(ptr, depth + 1)
        if opc in PASS_OPS or opc in (PcodeOp.INT_ADD, PcodeOp.INT_MULT,
                                      PcodeOp.INT_AND, PcodeOp.INT_RIGHT,
                                      PcodeOp.INT_SRIGHT, PcodeOp.INT_LEFT):
            return vname(op.getInput(0), depth + 1)
    return None

def read_axis(axis_off, count, elem):
    if not count:
        return []
    vals = []
    a = space.getAddress(CAL_FLASH + axis_off)
    for i in range(min(count, 24)):
        try:
            if elem == 2:
                v = mem.getShort(a.add(i * 2)) & 0xffff
            else:
                v = mem.getByte(a.add(i)) & 0xff
            vals.append(v)
        except:
            break
    return vals

# tables keyed by data offset
tables = {}   # off -> dict(elem,count,idx=set,dest=set,axis_off,axis_role,srcs)

decomp = DecompInterface()
decomp.openProgram(currentProgram)

callers = {}
for entryoff in targets:
    entry = space.getAddress(entryoff)
    for ref in refMgr.getReferencesTo(entry):
        if ref.getReferenceType().isCall():
            cf = fm.getFunctionContaining(ref.getFromAddress())
            if cf is not None:
                callers.setdefault(cf.getEntryPoint().getOffset(), cf)

print("scanning %d callers ..." % len(callers))
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
        name, cfg = targets[toff]
        # constant size args
        def carg(i):
            if op.getNumInputs() > i:
                v = op.getInput(i)
                return (v.getOffset() & 0xffffffff) if v.isConstant() else None
            return None
        a0, a1 = carg(1), carg(2)
        # index var name(s)
        idxs = []
        for ia in cfg["idx"]:
            if op.getNumInputs() > ia + 1:
                nm = vname(op.getInput(ia + 1))
                if nm:
                    idxs.append(nm)
        dest = vname(op.getOutput()) if op.getOutput() is not None else None
        # resolve ptr args
        resolved = []
        for (ai, role, lenkey) in cfg["ptrs"]:
            if op.getNumInputs() <= ai + 1:
                continue
            off = extract_off(op.getInput(ai + 1))
            if off is None or off >= CAL_SIZE:
                continue
            n = {"a0": a0, "a1": a1,
                 "prod01": (a0 * a1) if (a0 and a1) else None,
                 "fix256": 256}[lenkey]
            resolved.append([ai, role, off, n])
        # infer elem from spacing for 2d pair
        elem = 2
        if name == "lookup2d_interpolated_u16" and len(resolved) == 2:
            n = resolved[0][3]
            gap = abs(resolved[0][2] - resolved[1][2])
            if n and gap == n:
                elem = 1
            elif n and gap == 2 * n:
                elem = 2
        elif name == "lookup1d_interpolated_u8":
            elem = 1
        # find the data table + its axis offset
        data = [r for r in resolved if r[1] == "data"]
        axis = [r for r in resolved if r[1].startswith("axis")]
        axis_off = axis[0][2] if axis else None
        for (ai, role, off, n) in data:
            t = tables.get(off)
            if t is None:
                t = dict(elem=elem, count=n, idx=set(), dest=set(),
                         axis_off=axis_off, srcs=set(), kind=name)
                tables[off] = t
            t["elem"] = min(t["elem"], elem)
            if n:
                t["count"] = max(t["count"] or 0, n)
            if axis_off is not None:
                t["axis_off"] = axis_off
            for x in idxs:
                t["idx"].add(x)
            if dest:
                t["dest"].add(dest)
            t["srcs"].add(cf.getName())

decomp.dispose()

# ---- report ----------------------------------------------------------------
offs = sorted(tables.keys())
print("\n==== %d calibration data tables ====" % len(offs))
print("offset   elem cnt  index_var(s)            dest_var(s)            axis[0:6]")
rows = []
for off in offs:
    t = tables[off]
    ax = read_axis(t["axis_off"], t["count"], t["elem"]) if t["axis_off"] is not None else []
    idx = ",".join(sorted([x for x in t["idx"] if x]))[:22]
    dst = ",".join(sorted([x for x in t["dest"] if x]))[:22]
    axs = " ".join(str(v) for v in ax[:6])
    print("+0x%04x  u%d  %3s  %-22s %-22s [%s]" % (
        off, t["elem"] * 8, t["count"] or "?", idx or "-", dst or "-", axs))
    rows.append((off, t, ax, idx, dst))

# named-index subset = highest confidence to name now
print("\n---- tables with a NAMED index var (self-identifying) ----")
for (off, t, ax, idx, dst) in rows:
    if idx and not idx.startswith("DAT_") and not idx.startswith("#"):
        axs = " ".join(str(v) for v in ax[:8])
        print("  +0x%04x  idx=%-20s dest=%-20s axis=[%s]" % (off, idx, dst or "-", axs))

# CSV
try:
    tmp = os.path.join(os.environ.get("TEMP", "/tmp"), "cal_tables.csv")
    f = open(tmp, "w")
    f.write("offset,elem_bytes,count,kind,index_vars,dest_vars,axis_off,axis_values,sources\n")
    for (off, t, ax, idx, dst) in rows:
        f.write("0x%04x,%d,%s,%s,%s,%s,%s,%s,%s\n" % (
            off, t["elem"], t["count"] or "", t["kind"],
            "|".join(sorted(t["idx"])), "|".join(sorted(t["dest"])),
            ("0x%04x" % t["axis_off"]) if t["axis_off"] is not None else "",
            "|".join(str(v) for v in ax),
            "|".join(sorted(t["srcs"]))))
    f.close()
    print("\nCSV written: %s" % tmp)
except Exception as e:
    print("CSV write failed: %s" % e)

# ---- detect input quantity for axis naming --------------------------------
def qty_of(idx_set, axis_vals):
    s = " ".join(sorted(idx_set)).lower()
    if "coolant" in s:
        return "coolant"
    if "engine_speed" in s or "rpm" in s:
        return "rpm"
    if "load" in s:
        return "load"
    if "tps" in s or "throttle" in s or "pedal" in s or "0x3ff" in s:
        return "tps"
    if "setpoint" in s:
        return "idlesetpt"
    # strict RPM-breakpoint fallback: monotonic, plausible idle->redline range
    v = [x for x in axis_vals if x is not None]
    if len(v) >= 6 and all(v[i] <= v[i + 1] for i in range(len(v) - 1)):
        if 400 <= v[0] <= 1200 and 5000 <= v[-1] <= 9000:
            return "rpm"
    return None

# ---- report self-identifying axes & optionally apply -----------------------
proposed = []   # (axis_off, qty, table_off)
for (off, t, ax, idx, dst) in rows:
    if t["axis_off"] is None:
        continue
    q = qty_of(t["idx"], ax)
    if q:
        proposed.append((t["axis_off"], q, off))

# de-dup axis_off; require consistent qty
axis_qty = {}
conflict = set()
for (aoff, q, toff) in proposed:
    if aoff in axis_qty and axis_qty[aoff] != q:
        conflict.add(aoff)
    else:
        axis_qty[aoff] = q
for c in conflict:
    axis_qty.pop(c, None)

print("\n==== axis members to name by quantity (%d) ====" % len(axis_qty))
for aoff in sorted(axis_qty):
    print("  axis +0x%04x -> %s" % (aoff, axis_qty[aoff]))
if conflict:
    print("  (skipped %d axes with conflicting quantity)" % len(conflict))

if not APPLY:
    print("\n(dry-run) re-run with 'apply' and without -readOnly to rename axis members.")
else:
    dtm = currentProgram.getDataTypeManager()
    cal = dtm.getDataType(CategoryPath("/cal"), "Calibration")
    if cal is None:
        print("!! Calibration struct not found; run BuildCalStruct apply first")
    else:
        done = skip = 0
        for aoff in sorted(axis_qty):
            comp = cal.getComponentAt(aoff)
            if comp is None or comp.getOffset() != aoff:
                skip += 1
                continue
            cur = comp.getFieldName() or ""
            if not cur.startswith("axis"):   # don't clobber hand-named axes
                skip += 1
                continue
            try:
                comp.setFieldName("axis_%s_%04x" % (axis_qty[aoff], aoff))
                done += 1
            except Exception as e:
                print("  !! %04x: %s" % (aoff, e))
                skip += 1
        print("renamed %d axis members, skipped %d" % (done, skip))
        print("== DONE (review + save/commit in GUI) ==")
