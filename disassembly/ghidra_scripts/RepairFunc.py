# Repair a function split into fragments: remove the truncated function + body fragments, then
# re-disassemble from the true start and re-create one function. Args: <start_hex> <name> [frag_hex...]
# Saves. @category Analysis
from ghidra.app.cmd.disassemble import DisassembleCommand
from ghidra.app.cmd.function import CreateFunctionCmd
from ghidra.util.task import ConsoleTaskMonitor
from ghidra.program.model.symbol import SourceType

space = currentProgram.getAddressFactory().getDefaultAddressSpace()
fm = currentProgram.getFunctionManager()
mon = ConsoleTaskMonitor()
def A(v): return space.getAddress(int(v, 16))

args = getScriptArgs()
start, end, name, frags = args[0], args[1], args[2], args[3:]

# remove the truncated function + any body-fragment functions
for v in [start] + list(frags):
    f = fm.getFunctionAt(A(v))
    if f is not None:
        print("remove fn %s @ %s (%d B)" % (f.getName(), f.getEntryPoint(), f.getBody().getNumAddresses()))
        fm.removeFunction(A(v))

# clear the (possibly misaligned) code units across the whole range, then re-disassemble cleanly
currentProgram.getListing().clearCodeUnits(A(start), A(end), False)
DisassembleCommand(A(start), None, True).applyTo(currentProgram, mon)
# recreate one function spanning the whole body
CreateFunctionCmd(A(start)).applyTo(currentProgram, mon)
f = fm.getFunctionAt(A(start))
if f is not None:
    f.setName(name, SourceType.USER_DEFINED)
    print("RESULT: %s @ %s  bytes=%d" % (f.getName(), f.getEntryPoint(), f.getBody().getNumAddresses()))
else:
    print("RESULT: FAILED to create function at %s" % start)
print("== DONE ==")
