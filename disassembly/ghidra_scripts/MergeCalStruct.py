# Merge newly-exposed calibration tables into the EXISTING `Calibration` struct
# WITHOUT clobbering hand-named members.
#
# BuildCalStruct.py rebuilds the struct from scratch (generic tbl_/axis_ names),
# so re-running it after code-recovery would wipe every analyst-assigned member
# name/type. This script instead:
#   - scans every lookup call site (same offset/elem/size recovery as BuildCalStruct),
#   - reads the current `Calibration` struct and classifies each member as
#       HAND  (analyst-named -> preserved verbatim: name, datatype, comment) or
#       AUTO  (matches tbl_XXXX / axis_[qty_]XXXX -> may be refreshed),
#   - keeps all HAND members, keeps/refreshes AUTO members, and ADDS members for
#     newly-discovered offsets that don't collide with a HAND member's extent,
#   - enriches each table with index var / dest var / flash axis breakpoints
#     (like IdentifyCalTables) and writes a worklist CSV of ONLY the NEW members.
#
# Dry-run by default (prints summary + writes %TEMP%\cal_new_members.csv).
# Pass "apply" (and DROP -readOnly) to rewrite the merged struct, re-place the
# instances at 0x20000 / 0x4002e000, and retype CALBASE_addr.
#
# Usage (review):
#   analyzeHeadless <proj> "Lotus ECU" -process emira -readOnly -noanalysis \
#       -scriptPath <dir> -postScript MergeCalStruct.py
# Apply:
#       ... -postScript MergeCalStruct.py apply        (omit -readOnly)
#
# @category Calibration
import os, re
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
mem = currentProgram.getMemory()
space = currentProgram.getAddressFactory().getDefaultAddressSpace()
dtm = currentProgram.getDataTypeManager()
monitor = ConsoleTaskMonitor()

# auto-generated member-name patterns (safe to refresh/replace); anything else
# is treated as hand-named and preserved.
AUTO_RE = re.compile(r"^(tbl|axis)_[0-9a-f]{4}$")
AUTO_AXIS_RE = re.compile(
    r"^axis_(rpm|coolant|load|tps|idlesetpt|airflow|demand|manifold_temp|time)_[0-9a-f]{4}$")
def is_auto(nm):
    return bool(nm) and (AUTO_RE.match(nm) is not None or AUTO_AXIS_RE.match(nm) is not None)

calbase_off = None
for s in st.getSymbols("CALBASE_addr"):
    calbase_off = s.getAddress().getOffset()
    break
print("CALBASE_addr @ %s" % ("%x" % calbase_off if calbase_off is not None else "??"))

# ---- per-lookup arg config -------------------------------------------------
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
            print("  target %s @ %s" % (name, func.getEntryPoint()))
if not targets:
    print("!! no lookup functions found -- nothing to do")

# Self-axis 1-D interpolated lookups: a SINGLE pointer to a [axis[count]][data[count]]
# block (axis breakpoints then data). Signature (count, index, table). These were
# invisible to the lookup2d/3d scan. Keyed by ENTRY ADDRESS (the helpers are still FUN_*).
SELFAXIS = {
    0x00a4a0cc: 1,   # byte  axis+data
    0x00a4a148: 2,   # short axis+data
    0x00a4a1e0: 1,   # signed-byte axis+data
}
self_targets = {}
for off, elem in SELFAXIS.items():
    if fm.getFunctionAt(space.getAddress(off)) is not None:
        self_targets[off] = elem
        print("  self-axis target FUN @ %x (elem=%d)" % (off, elem))

# ---- p-code helpers --------------------------------------------------------
PASS_OPS = (PcodeOp.CAST, PcodeOp.COPY, PcodeOp.INT_ZEXT, PcodeOp.INT_SEXT,
            PcodeOp.SUBPIECE, PcodeOp.MULTIEQUAL, PcodeOp.INDIRECT)

def classify_base(vn, depth=0):
    if vn is None or depth > 8:
        return "?"
    if vn.isConstant():
        v = vn.getOffset() & 0xffffffff
        return "CAL" if v in (CAL_RAM, CAL_FLASH) else "C:%x" % v
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
            return ((acc + c) & 0xffffffff, classify_base(other))
    if opc in PASS_OPS:
        return extract_off(op.getInput(0), depth + 1, acc)
    return None

def const_arg(vn):
    if vn is None:
        return None
    if vn.isConstant():
        return vn.getOffset() & 0xffffffff
    op = vn.getDef()
    if op is not None and op.getOpcode() in PASS_OPS:
        return const_arg(op.getInput(0))
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
    if axis_off is None or not count:
        return []
    vals = []
    a = space.getAddress(CAL_FLASH + axis_off)
    for i in range(min(count, 24)):
        try:
            v = (mem.getShort(a.add(i * 2)) & 0xffff) if elem == 2 else (mem.getByte(a.add(i)) & 0xff)
            vals.append(v)
        except:
            break
    return vals

# ---- scan all call sites ---------------------------------------------------
# proposals: off -> dict(len,elem,role,kind,srcs,counts)
# enrich:    off -> dict(idx=set,dest=set,axis_off,from_data,srcs)
proposals = {}
enrich = {}
unresolved = []
stats = {"calls": 0, "args": 0, "cal": 0, "other": 0}

decomp = DecompInterface()
decomp.openProgram(currentProgram)

callers = {}
for entryoff in list(targets) + list(self_targets):
    entry = space.getAddress(entryoff)
    for ref in refMgr.getReferencesTo(entry):
        if ref.getReferenceType().isCall():
            cf = fm.getFunctionContaining(ref.getFromAddress())
            if cf is not None:
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
        # --- self-axis 1-D lookups: single [axis][data] block ------------------
        if toff in self_targets:
            elem = self_targets[toff]
            cnt = const_arg(op.getInput(1)) if op.getNumInputs() > 1 else None
            got = extract_off(op.getInput(3)) if op.getNumInputs() > 3 else None
            if cnt is None or got is None:
                continue
            base_off, kind = got
            if base_off >= CAL_SIZE or kind != "CAL":
                continue
            ix = vname(op.getInput(2)) if op.getNumInputs() > 2 else None
            dst = vname(op.getOutput()) if op.getOutput() is not None else None
            data_off = base_off + cnt * elem            # data follows the axis
            for (moff, mrole, m_axis) in ((base_off, "axis", None),
                                          (data_off, "data", base_off)):
                p = proposals.get(moff)
                if p is None:
                    proposals[moff] = dict(len=cnt * elem, elem=elem, role=mrole,
                                           kind=kind, srcs=set([cf.getName()]),
                                           counts=set([cnt]))
                else:
                    p["len"] = max(p["len"], cnt * elem)
                    p["elem"] = min(p["elem"], elem)
                    p["srcs"].add(cf.getName())
                    p["counts"].add(cnt)
                en = enrich.setdefault(moff, dict(idx=set(), dest=set(), axis_off=None, srcs=set()))
                en["srcs"].add(cf.getName())
                if mrole == "data":
                    if ix:
                        en["idx"].add(ix)
                    if dst:
                        en["dest"].add(dst)
                    en["axis_off"] = m_axis
            stats["calls"] += 1
            stats["cal"] += 1
            continue
        if toff not in targets:
            continue
        name, cfg = targets[toff]
        stats["calls"] += 1
        callsite = op.getSeqnum().getTarget()
        a0 = const_arg(op.getInput(1)) if op.getNumInputs() > 1 else None
        a1 = const_arg(op.getInput(2)) if op.getNumInputs() > 2 else None
        # index var name(s) + dest var
        idxs = []
        for ia in cfg["idx"]:
            if op.getNumInputs() > ia + 1:
                nm = vname(op.getInput(ia + 1))
                if nm:
                    idxs.append(nm)
        dest = vname(op.getOutput()) if op.getOutput() is not None else None
        # resolve base-relative pointer args
        resolved = []   # [argidx, role, off, kind, count, elem]
        for (idx, role, lenkey) in cfg["ptrs"]:
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
            n = {"a0": a0, "a1": a1,
                 "prod01": (a0 * a1) if (a0 and a1) else None,
                 "fix256": 256}[lenkey]
            resolved.append([idx, role, off, kind, n, 2])
        # u8 vs u16 for a 1-D lookup2d pair via pointer spacing
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
        elif name == "lookup1d_interpolated_u8":
            for r in resolved:
                r[5] = 1
        # axis offset for enrichment (the data table's axis)
        axis_entry = next((r for r in resolved if r[1].startswith("axis")), None)
        axis_off = axis_entry[2] if axis_entry else None
        # emit sizing proposals
        for (idx, role, off, kind, n, elem) in resolved:
            e = elem if elem else 2
            blen = (n * e) if n else e
            p = proposals.get(off)
            simple_role = "axis" if role.startswith("axis") else "data"
            if p is None:
                proposals[off] = dict(len=blen, elem=e, role=simple_role, kind=kind,
                                      srcs=set([cf.getName()]), counts=set([n]))
            else:
                p["len"] = max(p["len"], blen)
                p["elem"] = min(p["elem"], e)
                p["srcs"].add(cf.getName())
                p["counts"].add(n)
                if simple_role not in p["role"]:
                    p["role"] = p["role"] + "+" + simple_role
            # enrichment
            en = enrich.get(off)
            if en is None:
                en = dict(idx=set(), dest=set(), axis_off=None, srcs=set())
                enrich[off] = en
            en["srcs"].add(cf.getName())
            if simple_role == "data":
                for x in idxs:
                    en["idx"].add(x)
                if dest:
                    en["dest"].add(dest)
                if axis_off is not None:
                    en["axis_off"] = axis_off

decomp.dispose()

# propagate index-quantity to axis offsets (axis inherits the data table's index)
for off, p in proposals.items():
    if p["role"].startswith("axis"):
        # find a data table that referenced this axis
        for doff, en in enrich.items():
            if en.get("axis_off") == off and en["idx"]:
                enrich[off]["idx"] |= en["idx"]

# ---- snapshot the existing struct -----------------------------------------
cat = CategoryPath("/cal")
existing = dtm.getDataType(cat, "Calibration")
hand = {}   # off -> (dt, length, name, comment)
auto = {}   # off -> (dt, length, name, comment)
if existing is not None:
    for comp in existing.getDefinedComponents():
        nm = comp.getFieldName()
        if not nm:
            continue
        rec = (comp.getDataType(), comp.getLength(), nm, comp.getComment())
        if is_auto(nm):
            auto[comp.getOffset()] = rec
        else:
            hand[comp.getOffset()] = rec
    print("\nexisting Calibration: %d hand-named, %d auto members" % (len(hand), len(auto)))
else:
    print("\n!! no existing Calibration struct -- merge will behave like a fresh build")

hand_ranges = sorted((o, o + r[1]) for o, r in hand.items())
def shadowed_by_hand(off):
    for (s, e) in hand_ranges:
        if s <= off < e:
            return s
        if s > off:
            break
    return None

# ---- compute the final merged member set ----------------------------------
# final: off -> dict(elem,count_len,name,comment,dt(optional),kind)
final = {}
# 1) hand members preserved verbatim
for off, (dt, ln, nm, cm) in hand.items():
    final[off] = dict(dt=dt, len=ln, name=nm, comment=cm, kind="hand")
# 2) proposals -> auto-refresh or new
new_offs = []
shadowed = []
for off in sorted(proposals.keys()):
    if off in hand:
        continue
    hs = shadowed_by_hand(off)
    if hs is not None:
        shadowed.append((off, hs))
        continue
    p = proposals[off]
    nm = "%s_%04x" % ("axis" if p["role"].startswith("axis") else "tbl", off)
    if off in auto:
        # refresh size with the larger of existing/new; keep auto name
        ex_dt, ex_len, ex_nm, ex_cm = auto[off]
        final[off] = dict(elem=p["elem"], len=max(p["len"], ex_len),
                          name=ex_nm if is_auto(ex_nm) else nm,
                          comment=None, kind="auto")
    else:
        final[off] = dict(elem=p["elem"], len=p["len"], name=nm,
                          comment="from %s" % (",".join(sorted(p["srcs"]))[:80]),
                          kind="new")
        new_offs.append(off)
# 3) keep existing auto members that have no current proposal (don't shrink)
for off, (dt, ln, nm, cm) in auto.items():
    if off in final:
        continue
    if shadowed_by_hand(off) is not None:
        continue
    final[off] = dict(dt=dt, len=ln, name=nm, comment=cm, kind="auto-kept")

# ---- cap non-hand members at the gap to the next member -------------------
offs = sorted(final.keys())
capped = 0
for i, off in enumerate(offs):
    m = final[off]
    if m["kind"] == "hand":
        continue
    nxt = offs[i + 1] if i + 1 < len(offs) else CAL_SIZE
    gap = nxt - off
    if m["len"] > gap:
        m["raw"] = m["len"]
        m["len"] = gap
        capped += 1

# ---- report ----------------------------------------------------------------
by_kind = {}
for off in offs:
    by_kind[final[off]["kind"]] = by_kind.get(final[off]["kind"], 0) + 1
print("\n==== merge summary ====")
print("  total members : %d" % len(offs))
for k in ("hand", "auto", "auto-kept", "new"):
    print("    %-10s : %d" % (k, by_kind.get(k, 0)))
print("  capped-to-gap : %d" % capped)
print("  shadowed by hand member (skipped): %d" % len(shadowed))
for (off, hs) in shadowed[:20]:
    print("    +0x%04x inside hand member @ +0x%04x" % (off, hs))
print("  unresolved arg ptrs: %d" % len(unresolved))

print("\n==== NEW members to name (%d) ====" % len(new_offs))
print("  offset   elem cnt  index_var(s)          dest_var(s)           axis[0:8]")
for off in new_offs:
    p = proposals[off]
    en = enrich.get(off, {})
    cnt = max([c for c in p["counts"] if c] or [0])
    ax = read_axis(en.get("axis_off"), cnt, p["elem"]) if p["role"] == "data" else []
    idx = ",".join(sorted([x for x in en.get("idx", []) if x]))[:20]
    dst = ",".join(sorted([x for x in en.get("dest", []) if x]))[:20]
    axs = " ".join(str(v) for v in ax[:8])
    print("  +0x%04x  u%d  %3s  %-20s %-20s [%s]" % (
        off, p["elem"] * 8, cnt or "?", idx or "-", dst or "-", axs))

# ---- worklist CSV (NEW members only) --------------------------------------
try:
    tmp = os.path.join(os.environ.get("TEMP", "/tmp"), "cal_new_members.csv")
    f = open(tmp, "w")
    f.write("offset,role,elem_bytes,count,index_vars,dest_vars,axis_off,axis_values,sources\n")
    for off in new_offs:
        p = proposals[off]
        en = enrich.get(off, {})
        cnt = max([c for c in p["counts"] if c] or [0])
        ax = read_axis(en.get("axis_off"), cnt, p["elem"]) if p["role"] == "data" else []
        f.write("0x%04x,%s,%d,%s,%s,%s,%s,%s,%s\n" % (
            off, p["role"], p["elem"], cnt or "",
            "|".join(sorted([x for x in en.get("idx", []) if x])),
            "|".join(sorted([x for x in en.get("dest", []) if x])),
            ("0x%04x" % en["axis_off"]) if en.get("axis_off") is not None else "",
            "|".join(str(v) for v in ax),
            "|".join(sorted(p["srcs"]))))
    f.close()
    print("\nworklist CSV written: %s" % tmp)
except Exception as e:
    print("CSV write failed: %s" % e)

# ---- apply -----------------------------------------------------------------
if not APPLY:
    print("\n(dry-run) re-run with 'apply' (and without -readOnly) to write the merged struct.")
else:
    print("\n==== APPLYING (merge) ====")
    cal = StructureDataType(cat, "Calibration", CAL_SIZE)
    skipped = 0
    for off in offs:
        m = final[off]
        if m.get("dt") is not None:
            dt = m["dt"]
        else:
            elem = UnsignedShortDataType() if m["elem"] == 2 else UnsignedCharDataType()
            cnt = max(1, m["len"] // m["elem"])
            dt = ArrayDataType(elem, cnt, m["elem"])
        try:
            cal.replaceAtOffset(off, dt, m["len"], m["name"], m.get("comment"))
        except Exception as e:
            skipped += 1
            print("  overlap/skip +0x%04x (%s): %s" % (off, m["name"], e))
    if existing is not None:
        dtm.remove(existing, monitor)
    cal = dtm.addDataType(cal, None)
    print("  Calibration struct rebuilt: %d members (%d new), %d skipped" % (
        len(offs) - skipped, len(new_offs), skipped))

    for tag, a in (("flash", CAL_FLASH), ("ram", CAL_RAM)):
        addr = space.getAddress(a)
        try:
            clearListing(addr, addr.add(CAL_SIZE - 1))
            createData(addr, cal)
            createLabel(addr, "CAL_%s" % tag, True)
            print("  placed Calibration @ %s (%s)" % (addr, tag))
        except Exception as e:
            print("  could not place @ %s (%s): %s" % (addr, tag, e))

    if calbase_off is not None:
        ca = space.getAddress(calbase_off)
        try:
            clearListing(ca, ca.add(3))
            createData(ca, PointerDataType(cal))
            print("  retyped CALBASE_addr @ %s -> Calibration*" % ca)
        except Exception as e:
            print("  could not retype CALBASE_addr: %s" % e)
    print("==== DONE (review decompilation, then save/commit in GUI) ====")
