# READ-ONLY scan for the "void-returns-r3" decompiler miss: a function typed
# void/undefined whose tail is a call to a NON-void function, with no r3 overwrite
# afterward -> the callee's r3 return passes straight through (implicit return the
# decompiler dropped). Confirmation column `retUsed` = at least one caller reads r3
# right after the call. Reports candidates sorted by caller count. @category Analysis

fm = currentProgram.getFunctionManager()
listing = currentProgram.getListing()
ref = currentProgram.getReferenceManager()

def voidish(dt):
    n = dt.getName()
    return n == 'void' or n.startswith('undefined')

def reg_named(obj, name):
    try:
        return obj.getName() == name
    except:
        return False

def callers_use_r3(f):
    for r in ref.getReferencesTo(f.getEntryPoint()):
        if not r.getReferenceType().isCall():
            continue
        site = listing.getInstructionAt(r.getFromAddress())
        if site is None:
            continue
        nxt = site.getNext()
        for _ in range(2):
            if nxt is None:
                break
            if any(reg_named(o, 'r3') for o in nxt.getInputObjects()):
                return True
            if any(reg_named(o, 'r3') for o in nxt.getResultObjects()):
                break  # r3 reassigned before use
            nxt = nxt.getNext()
    return False

cands = []
for f in fm.getFunctions(True):
    if f.isThunk() or f.isExternal():
        continue
    if not voidish(f.getReturnType()):
        continue
    instrs = list(listing.getInstructions(f.getBody(), True))
    if not instrs:
        continue
    last_idx = -1
    for i, ins in enumerate(instrs):
        if ins.getFlowType().isCall():
            last_idx = i
    if last_idx < 0:
        continue
    trailing = len(instrs) - last_idx - 1
    if trailing > 6:                       # last call not in tail position
        continue
    call = instrs[last_idx]
    callee = None
    for fl in call.getFlows():
        callee = fm.getFunctionAt(fl)
        if callee:
            break
    if callee is None or voidish(callee.getReturnType()):
        continue                            # callee returns nothing -> no pass-through
    if any(reg_named(o, 'r3') for ins in instrs[last_idx + 1:] for o in ins.getResultObjects()):
        continue                            # r3 overwritten after the call
    ncallers = len(list(f.getCallingFunctions(monitor)))
    cands.append((ncallers, callers_use_r3(f), f.getName(), str(f.getEntryPoint()),
                  callee.getName(), callee.getReturnType().getName()))

cands.sort(reverse=True)
print("=== void-returns-r3 candidates: %d ===" % len(cands))
print("callers retUsed  function @addr -> tail callee : callee_ret")
for nc, used, nm, addr, cn, crt in cands:
    print("  %3d   %-5s  %-26s @%s -> %-24s : %s" % (nc, used, nm, addr, cn, crt))
print("== DONE ==")
