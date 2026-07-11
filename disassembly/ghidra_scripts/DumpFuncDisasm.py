# Dump instruction listing (with raw bytes) + decompiler output for function
# addresses passed as hex script args. Read-only.
# @category Analysis
from ghidra.app.decompiler import DecompInterface
from ghidra.util.task import ConsoleTaskMonitor

args = getScriptArgs()
dec = DecompInterface()
dec.openProgram(currentProgram)
listing = currentProgram.getListing()
space = currentProgram.getAddressFactory().getDefaultAddressSpace()
monitor = ConsoleTaskMonitor()

def resolve(a):
    try:
        return space.getAddress(int(a.replace("0x", ""), 16))
    except ValueError:
        for s in currentProgram.getSymbolTable().getSymbols(a):
            return s.getAddress()
    return None

for a in args:
    addr = resolve(a)
    if addr is None:
        print("\n==================== %s ====================" % a)
        print("  (could not resolve)")
        continue
    f = getFunctionContaining(addr)
    print("\n==================== %s ====================" % a)
    if f is None:
        print("  (no function at this address)")
        continue
    print("Function %s @ %s  bytes=%d" % (
        f.getName(), f.getEntryPoint(), f.getBody().getNumAddresses()))
    it = listing.getInstructions(f.getBody(), True)
    while it.hasNext():
        ins = it.next()
        hx = "".join("%02x" % (x & 0xff) for x in ins.getBytes())
        print("  %s  %-12s  %-32s [%s]" % (
            ins.getAddress(), hx, ins.toString(), ins.getFlowType()))
    res = dec.decompileFunction(f, 30, monitor)
    if res is not None and res.decompileCompleted():
        print("  --- decompiled ---")
        print(res.getDecompiledFunction().getC())
    else:
        print("  --- decompile failed ---")

dec.dispose()
