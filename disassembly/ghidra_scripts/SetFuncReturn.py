# Set a function's return type. Args: "<funcname|addrhex>:<typename>"
#   typename = a builtin (void/short/ushort/char/uchar/int/uint) or a named typedef.
# Fixes decompiler-misinferred returns (e.g. a void-typed leaf that really returns r3).
# Saves. @category Labeling
from ghidra.program.model.symbol import SourceType
from ghidra.program.model.data import (CategoryPath, VoidDataType, ShortDataType,
    UnsignedShortDataType, CharDataType, UnsignedCharDataType, IntegerDataType, UnsignedIntegerDataType)

fm = currentProgram.getFunctionManager()
st = currentProgram.getSymbolTable()
dtm = currentProgram.getDataTypeManager()
space = currentProgram.getAddressFactory().getDefaultAddressSpace()
BUILTIN = {'void': VoidDataType(), 'short': ShortDataType(), 'ushort': UnsignedShortDataType(),
           'char': CharDataType(), 'uchar': UnsignedCharDataType(), 'int': IntegerDataType(),
           'uint': UnsignedIntegerDataType()}

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
    nm, tn = arg.split(":", 1)
    f = find_func(nm)
    dt = find_type(tn)
    if f is None:
        print("  SKIP %s (no function)" % nm); skip += 1; continue
    if dt is None:
        print("  SKIP %s (no type %s)" % (nm, tn)); skip += 1; continue
    old = f.getReturnType().getName()
    f.setReturnType(dt, SourceType.USER_DEFINED)
    print("  %-28s return %s -> %s" % (f.getName(), old, tn))
    done += 1
print("\nset %d, skipped %d" % (done, skip))
print("== DONE ==")
