# Label OBD-II Mode 01 PID handlers from the obd_ii_handlers_mode01 table.
# Each entry: pid@0, handler@8, handler2@0xc (struct stride 0x14, 59 entries).
# The table IS the pid->handler mapping, so naming each handler after its pid
# is a fact, not a guess.  Matches the existing obd_ii_handler_mode01_0xNN
# convention.  Creates functions at handler targets that aren't defined yet.
#
# Dry-run by default; pass "apply" (and drop -readOnly) to write.
# @category Labeling
from ghidra.program.model.symbol import SourceType
from ghidra.app.cmd.function import CreateFunctionCmd

APPLY = "apply" in [a.lower() for a in getScriptArgs()]
STRIDE, N = 0x14, 59
NAME1 = "obd_ii_handler_mode01_0x%02X"
NAME2 = "obd_ii_handler2_mode01_0x%02X"

st = currentProgram.getSymbolTable()
fm = currentProgram.getFunctionManager()
mem = currentProgram.getMemory()
space = currentProgram.getAddressFactory().getDefaultAddressSpace()

sym = None
for s in st.getSymbols("obd_ii_handlers_mode01"):
    sym = s
    break
if sym is None:
    print("!! obd_ii_handlers_mode01 not found")
else:
    base = sym.getAddress()
    plan = []   # (target_off, newname, existing_name, needs_create)
    for i in range(N):
        a = base.add(i * STRIDE)
        pid = mem.getByte(a) & 0xff
        for (foff, tmpl) in ((0x8, NAME1), (0xc, NAME2)):
            tgt = mem.getInt(a.add(foff)) & 0xffffffff
            if tgt == 0:
                continue
            ta = space.getAddress(tgt)
            f = fm.getFunctionAt(ta)
            newname = tmpl % pid
            plan.append((tgt, newname, f.getName() if f else None, f is None))

    print("== OBD mode01 handler labels (%d) ==" % len(plan))
    rename = create = skip = 0
    for (tgt, newname, cur, needs_create) in plan:
        tag = ""
        if needs_create:
            tag = "CREATE+NAME"
            create += 1
        elif cur == newname:
            tag = "ok(same)"
            skip += 1
        else:
            tag = "RENAME from %s" % cur
            rename += 1
        print("  %08x  %-30s  %s" % (tgt, newname, tag))
    print("\nplan: %d rename, %d create+name, %d already-correct" % (
        rename, create, skip))

    if not APPLY:
        print("\n(dry-run) re-run with 'apply' and without -readOnly to write.")
    else:
        done = 0
        for (tgt, newname, cur, needs_create) in plan:
            ta = space.getAddress(tgt)
            f = fm.getFunctionAt(ta)
            if f is None:
                cmd = CreateFunctionCmd(ta)
                if not cmd.applyTo(currentProgram, monitor):
                    print("  !! could not create function @ %08x" % tgt)
                    continue
                f = fm.getFunctionAt(ta)
                if f is None:
                    print("  !! still no function @ %08x" % tgt)
                    continue
            try:
                f.setName(newname, SourceType.USER_DEFINED)
                done += 1
            except Exception as e:
                print("  !! rename %08x failed: %s" % (tgt, e))
        print("applied %d names" % done)
        print("== DONE (review + save/commit in GUI) ==")
