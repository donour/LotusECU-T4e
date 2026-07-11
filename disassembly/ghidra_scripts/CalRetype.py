# Set the datatype of /cal/Calibration members to a named unit typedef, preserving
# the field name and array element-count. Args: "<offhex>:<typedefname>:<base>"
#   base in {u8,u16,u32} only used to CREATE the typedef (in /units) if missing.
# Only acts on a component whose START offset matches exactly. Saves. @category Labeling
from ghidra.program.model.data import (CategoryPath, TypedefDataType, ArrayDataType,
    UnsignedCharDataType, UnsignedShortDataType, UnsignedIntegerDataType)

dtm = currentProgram.getDataTypeManager()
cal = dtm.getDataType(CategoryPath("/cal"), "Calibration")
BASE = {'u8': UnsignedCharDataType(), 'u16': UnsignedShortDataType(), 'u32': UnsignedIntegerDataType()}
CAT = CategoryPath("/units")

def find_type(name):
    out = []
    dtm.findDataTypes(name, out)
    return out[0] if out else None

done = skip = 0
if cal is None:
    print("!! /cal/Calibration not found")
else:
    for a in getScriptArgs():
        parts = a.split(":")
        offs, tname, base = parts[0], parts[1], parts[2]
        # optional 4th = explicit element count (for raw field_ axes not sized as arrays);
        # optional 5th = new field name.
        ecount = int(parts[3]) if len(parts) > 3 and parts[3] else 0
        newname = parts[4] if len(parts) > 4 and parts[4] else None
        # first token may be a hex offset OR an existing field name
        try:
            off = int(offs, 16); comp = cal.getComponentAt(off)
        except ValueError:
            comp = next((c for c in cal.getComponents() if c.getFieldName() == offs), None)
            off = comp.getOffset() if comp else -1
        if comp is None or comp.getOffset() != off:
            print("  SKIP %s=%s (no component)" % (offs, tname)); skip += 1; continue
        dt = find_type(tname)
        if dt is None:
            dt = dtm.addDataType(TypedefDataType(CAT, tname, BASE[base]), None)
            print("  created typedef %s = %s" % (tname, base))
        cnt = ecount if ecount else comp.getLength() // dt.getLength()
        newdt = ArrayDataType(dt, cnt, dt.getLength()) if cnt > 1 else dt
        name = newname if newname else comp.getFieldName()
        try:
            cal.replaceAtOffset(off, newdt, newdt.getLength(), name, comp.getComment())
            print("  +0x%04x %-28s -> %s[%d]" % (off, name, tname, cnt)); done += 1
        except Exception as e:
            print("  FAIL +0x%04x: %s" % (off, e)); skip += 1
print("\nretyped %d, skipped %d" % (done, skip))
print("== DONE ==")
