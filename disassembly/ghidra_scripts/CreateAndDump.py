# Create functions at the given addresses (if missing) and dump their
# decompilation. Used to crack open pointer-called functions (e.g. the
# ignition timing calc reached via a function pointer).
# Args: hex addresses to create+decompile.
# Requires write access (omit -readOnly; GUI project closed).
# @category Analysis
from ghidra.app.cmd.function import CreateFunctionCmd
from ghidra.app.decompiler import DecompInterface
from ghidra.util.task import ConsoleTaskMonitor

space = currentProgram.getAddressFactory().getDefaultAddressSpace()
fm = currentProgram.getFunctionManager()
listing = currentProgram.getListing()
monitor = ConsoleTaskMonitor()
dec = DecompInterface()
dec.openProgram(currentProgram)

for a in getScriptArgs():
    addr = space.getAddress(int(a, 16))
    f = fm.getFunctionContaining(addr)
    if f is None:
        if listing.getInstructionAt(addr) is None:
            disassemble(addr)
        CreateFunctionCmd(addr).applyTo(currentProgram, monitor)
        f = fm.getFunctionContaining(addr)
    print("\n==================== %s ====================" % a)
    if f is None:
        print("  could not create function")
        continue
    print("Function %s @ %s bytes=%d" % (f.getName(), f.getEntryPoint(),
          f.getBody().getNumAddresses()))
    res = dec.decompileFunction(f, 60, monitor)
    if res is not None and res.decompileCompleted():
        print(res.getDecompiledFunction().getC())
    else:
        print("  decompile failed")
dec.dispose()
