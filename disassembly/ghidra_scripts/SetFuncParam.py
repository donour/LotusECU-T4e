# Set a function parameter's datatype. Args: "<funcname|addr>:<idx>:<typename>[:ptr]"
#   idx = 0-based parameter index; typename = builtin or named typedef;
#   trailing ":ptr" makes the param a pointer-to-typedef (for out-pointer getters).
# Saves. @category Labeling
from ghidra.program.model.symbol import SourceType
from ghidra.program.model.listing import ParameterImpl
from ghidra.program.model.listing.Function import FunctionUpdateType
from ghidra.program.model.data import (ShortDataType, UnsignedShortDataType, CharDataType,
    UnsignedCharDataType, IntegerDataType, UnsignedIntegerDataType, Undefined4DataType)

fm = currentProgram.getFunctionManager()
st = currentProgram.getSymbolTable()
dtm = currentProgram.getDataTypeManager()
space = currentProgram.getAddressFactory().getDefaultAddressSpace()
BUILTIN = {'short': ShortDataType(), 'ushort': UnsignedShortDataType(), 'char': CharDataType(),
           'uchar': UnsignedCharDataType(), 'int': IntegerDataType(), 'uint': UnsignedIntegerDataType()}

def find_type(name):
    if name in BUILTIN:
        return BUILTIN[name]
    out = []
    dtm.findDataTypes(name, out)
    return out[0] if out else None

def find_func(nm):
    for s in st.getGlobalSymbols(nm):
        f = fm.getFunctionAt(s.getAddress())
        if f:
            return f
    try:
        return fm.getFunctionAt(space.getAddress(int(nm, 16)))
    except ValueError:
        return None

done = skip = 0
for arg in getScriptArgs():
    parts = arg.split(":")
    nm, idx, tn = parts[0], int(parts[1]), parts[2]
    asptr = len(parts) > 3 and parts[3] == 'ptr'
    f = find_func(nm)
    dt = find_type(tn)
    if f is None or dt is None:
        print("  SKIP %s (func=%s type=%s)" % (nm, f is not None, dt is not None)); skip += 1; continue
    if asptr:
        dt = dtm.getPointer(dt)
    params = list(f.getParameters())
    while len(params) <= idx:
        params.append(ParameterImpl("param_%d" % (len(params) + 1), Undefined4DataType(), currentProgram))
    old = params[idx].getDataType().getName()
    nm2 = params[idx].getName() or ("param_%d" % (idx + 1))
    params[idx] = ParameterImpl(nm2, dt, currentProgram)
    f.updateFunction(None, None, params, FunctionUpdateType.DYNAMIC_STORAGE_FORMAL_PARAMS,
                     True, SourceType.USER_DEFINED)
    print("  %-26s arg%d  %s -> %s" % (f.getName(), idx, old, dt.getName()))
    done += 1
print("\nset %d, skipped %d" % (done, skip))
print("== DONE ==")
