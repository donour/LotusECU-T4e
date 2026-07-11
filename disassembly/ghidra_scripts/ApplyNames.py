# Apply names from script args: space-separated <locator> <name> pairs.
#   locator = hex address (e.g. a72e2c / 40009120) OR an existing symbol name.
#   target  = function at that addr -> rename function;
#             else primary data symbol -> rename; else create a label.
# Avoid '=' in args (the launcher swallows key=value forms).
# Requires write access (omit -readOnly; GUI project must be closed).
# @category Labeling
from ghidra.program.model.symbol import SourceType
from ghidra.program.model.data import (CategoryPath, ArrayDataType,
    UnsignedCharDataType, UnsignedShortDataType)

space = currentProgram.getAddressFactory().getDefaultAddressSpace()
fm = currentProgram.getFunctionManager()
st = currentProgram.getSymbolTable()
dtm = currentProgram.getDataTypeManager()

def cal_member(spec, name):
    # spec = "calarr:<offhex>:<count>:<elembytes>" -> named array member in /cal/Calibration
    _, offh, cnt, eb = spec.split(":")
    off, cnt, eb = int(offh, 16), int(cnt), int(eb)
    cal = dtm.getDataType(CategoryPath("/cal"), "Calibration")
    if cal is None:
        print("  !! /cal/Calibration not found"); return
    elem = UnsignedShortDataType() if eb == 2 else UnsignedCharDataType()
    dt = elem if cnt == 1 else ArrayDataType(elem, cnt, eb)
    try:
        cal.replaceAtOffset(off, dt, cnt * eb, name, "")
        print("  calmem +0x%04x[%d] -> %s" % (off, cnt, name))
    except Exception as e:
        print("  !! calmem +0x%04x (%s): %s" % (off, name, e))

def resolve(loc):
    try:
        return space.getAddress(int(loc, 16))
    except ValueError:
        for s in st.getSymbols(loc):
            return s.getAddress()
    return None

args = list(getScriptArgs())
print("got %d args" % len(args))
i = 0
while i + 1 < len(args):
    loc, name = args[i], args[i + 1]
    i += 2
    if loc.startswith("calarr:"):
        cal_member(loc, name)
        continue
    # "fn:<loc>" forces naming the function CONTAINING the address
    contain = False
    if loc.startswith("fn:"):
        contain = True
        loc = loc[3:]
    addr = resolve(loc)
    if addr is None:
        print("  !! could not resolve %s" % loc)
        continue
    f = fm.getFunctionContaining(addr) if contain else fm.getFunctionAt(addr)
    try:
        if f is not None:
            f.setName(name, SourceType.USER_DEFINED)
            print("  func  %s -> %s" % (f.getEntryPoint(), name))
        else:
            sym = st.getPrimarySymbol(addr)
            if sym is not None:
                sym.setName(name, SourceType.USER_DEFINED)
                print("  data  %s -> %s" % (addr, name))
            else:
                createLabel(addr, name, True)
                print("  label %s -> %s" % (addr, name))
    except Exception as e:
        print("  !! %s (%s) failed: %s" % (loc, name, e))
print("== DONE ==")
