# Recon: list still-FUN_* functions with small bodies and a compact view of
# their decompiled behavior, to find obvious-purpose functions to name.
# Classifies the easy cases (getter/setter/clear of a NAMED global, single
# tail-call delegate). Read-only.
# @category Recon
from ghidra.app.decompiler import DecompInterface
from ghidra.util.task import ConsoleTaskMonitor
from ghidra.program.model.pcode import PcodeOp

fm = currentProgram.getFunctionManager()
space = currentProgram.getAddressFactory().getDefaultAddressSpace()
monitor = ConsoleTaskMonitor()
decomp = DecompInterface()
decomp.openProgram(currentProgram)

MAXBYTES = 48
PASS = (PcodeOp.CAST, PcodeOp.COPY, PcodeOp.INT_ZEXT, PcodeOp.INT_SEXT,
        PcodeOp.SUBPIECE, PcodeOp.MULTIEQUAL, PcodeOp.INDIRECT)

def sym_at(off):
    s = getSymbolAt(space.getAddress(off & 0xffffffff))
    if s is None:
        return None
    n = s.getName()
    if n.startswith("DAT_") or n.startswith("FUN_") or n.startswith("LAB_"):
        return None
    return n

def const_addr(vn, d=0):
    if vn is None or d > 6:
        return None
    if vn.isConstant():
        return vn.getOffset() & 0xffffffff
    op = vn.getDef()
    if op is not None and op.getOpcode() in PASS:
        return const_addr(op.getInput(0), d + 1)
    if op is not None and op.getOpcode() == PcodeOp.PTRSUB:
        a, b = op.getInput(0), op.getInput(1)
        if a.isConstant() and b.isConstant():
            return (a.getOffset() + b.getOffset()) & 0xffffffff
    return None

getters = []
setters = []
delegates = []
others = []

for f in fm.getFunctions(True):
    if not f.getName().startswith("FUN_"):
        continue
    if f.getBody().getNumAddresses() > MAXBYTES:
        continue
    res = decomp.decompileFunction(f, 30, monitor)
    if res is None or not res.decompileCompleted():
        continue
    hf = res.getHighFunction()
    if hf is None:
        continue
    stores = []
    loads = []
    calls = []
    ret = None
    ops = hf.getPcodeOps()
    while ops.hasNext():
        op = ops.next()
        oc = op.getOpcode()
        if oc == PcodeOp.STORE:
            stores.append(op)
        elif oc == PcodeOp.LOAD:
            loads.append(op)
        elif oc in (PcodeOp.CALL, PcodeOp.CALLIND):
            calls.append(op)
        elif oc == PcodeOp.RETURN and op.getNumInputs() > 1:
            ret = op.getInput(1)
    ea = f.getEntryPoint()
    # setter: exactly one store to a named global, no calls
    if len(stores) == 1 and len(calls) == 0:
        addr = const_addr(stores[0].getInput(1))
        nm = sym_at(addr) if addr else None
        if nm:
            val = stores[0].getInput(2)
            kind = "set"
            if val.isConstant():
                kind = "clear" if (val.getOffset() & 0xffffffff) == 0 else "set"
            setters.append((ea, "%s_%s" % (kind, nm), nm))
            continue
    # getter: no stores, no calls, returns a load of a named global
    if len(stores) == 0 and len(calls) == 0 and ret is not None:
        a2 = None
        op = ret.getDef()
        if op is not None and op.getOpcode() == PcodeOp.LOAD:
            a2 = const_addr(op.getInput(1))
        if a2 is None:
            a2 = const_addr(ret)
        nm = sym_at(a2) if a2 else None
        if nm:
            getters.append((ea, "get_%s" % nm, nm))
            continue
    # delegate: single tail call to a named function, nothing else
    if len(calls) == 1 and len(stores) == 0:
        t = calls[0].getInput(0)
        if t.isAddress():
            cf = fm.getFunctionContaining(t.getAddress())
            if cf is not None and not cf.getName().startswith("FUN_"):
                delegates.append((ea, cf.getName()))
                continue

def dump(title, lst):
    print("\n==== %s (%d) ====" % (title, len(lst)))
    for row in lst[:80]:
        print("  %s  %s" % (row[0], "  ".join(str(x) for x in row[1:])))

dump("GETTERS (get_<namedGlobal>)", getters)
dump("SETTERS/CLEAR (set/clear_<namedGlobal>)", setters)
dump("DELEGATES (single tail-call to named fn)", delegates)
print("\ntotals: getters=%d setters=%d delegates=%d" % (
    len(getters), len(setters), len(delegates)))
decomp.dispose()
