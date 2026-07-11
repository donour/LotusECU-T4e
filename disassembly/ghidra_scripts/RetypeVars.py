# Assign a unit typedef to a global data variable (does NOT rename it).
# Args: "<addrhex>:<typedefname>:<base>[:<count>]"
#   base in {u8,u16,u32,s8,s16,s32} -- only used to CREATE the typedef if it
#   doesn't already exist (in /units). count>1 makes it an array.
# Resolves the typedef by name across all categories; clears existing data at
# the address and applies the type. Saves. @category Labeling
from ghidra.program.model.data import TypedefDataType, CategoryPath, ArrayDataType
from ghidra.program.model.data import (UnsignedCharDataType, UnsignedShortDataType,
    UnsignedIntegerDataType, CharDataType, ShortDataType, IntegerDataType)

dtm = currentProgram.getDataTypeManager()
listing = currentProgram.getListing()
space = currentProgram.getAddressFactory().getDefaultAddressSpace()
BASE = {'u8': UnsignedCharDataType(), 'u16': UnsignedShortDataType(),
        'u32': UnsignedIntegerDataType(), 's8': CharDataType(),
        's16': ShortDataType(), 's32': IntegerDataType()}
CAT = CategoryPath("/units")

def find_type(name):
    out = []
    dtm.findDataTypes(name, out)
    return out[0] if out else None

done = fail = 0
for a in getScriptArgs():
    parts = a.split(":")
    addrs, tname, base = parts[0], parts[1], parts[2]
    count = int(parts[3]) if len(parts) > 3 else 1
    addr = space.getAddress(int(addrs, 16))
    dt = find_type(tname)
    if dt is None:
        dt = dtm.addDataType(TypedefDataType(CAT, tname, BASE[base]), None)
        print("  created typedef %s = %s" % (tname, base))
    applied = ArrayDataType(dt, count, dt.getLength()) if count > 1 else dt
    ln = applied.getLength()
    try:
        listing.clearCodeUnits(addr, addr.add(ln - 1), False)
        d = listing.createData(addr, applied)
        print("  +%-9s -> %s  (%d B)" % (addrs, applied.getName(), ln))
        done += 1
    except Exception as e:
        print("  FAIL +%s=%s: %s" % (addrs, tname, e))
        fail += 1
print("\nretyped %d, failed %d" % (done, fail))
print("== DONE ==")
