# Export the whole program as C using Ghidra's CppExporter (same as GUI
# "Export As C/C++"). Arg: output .c path (a sibling .h is also written).
# Run read-only; export does not modify the program.
# @category Export
from ghidra.app.util.exporter import CppExporter
from ghidra.app.util import OptionException
from ghidra.util.task import ConsoleTaskMonitor
from java.io import File

out = File(getScriptArgs()[0])
exp = CppExporter()
# Ensure the C body (decompiled functions) is emitted, C-style comments,
# and type definitions, matching the existing hc08_firmware.c.
try:
    opts = exp.getOptions(None)
    for o in opts:
        n = o.getName().lower()
        if "create c file" in n or "c file" in n:
            o.setValue(True)
        elif "header" in n:
            o.setValue(False)   # self-contained .c (typedefs inline), matches original
        elif "type definition" in n or "emit data type" in n:
            o.setValue(True)
        elif "cpp style" in n or "c++ style" in n:
            o.setValue(True)    # // comments, matches original
    exp.setOptions(opts)
except Exception as e:
    print("  (option setup skipped: %s)" % e)

ok = exp.export(out, currentProgram, None, ConsoleTaskMonitor())
print("export ok=%s -> %s" % (ok, out.getAbsolutePath()))
