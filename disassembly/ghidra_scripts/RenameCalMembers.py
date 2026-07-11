# Rename existing /cal/Calibration members in place (setFieldName only -- never
# changes datatypes or sizes). Args: space-separated "<offhex>:<name>" pairs.
# (Colon, not '=', because '=' is a delimiter in the .bat arg layer.)
# Only renames a component whose START offset matches exactly; reports anything
# that doesn't exist or whose offset is mid-member (so a typo can't clobber a
# neighbour). Saves. @category Labeling
from ghidra.program.model.data import CategoryPath

dtm = currentProgram.getDataTypeManager()
cal = dtm.getDataType(CategoryPath("/cal"), "Calibration")
done = skip = 0
if cal is None:
    print("!! /cal/Calibration not found")
else:
    for a in getScriptArgs():
        if ":" not in a:
            print("  SKIP malformed arg (no ':'): %r" % a)
            skip += 1
            continue
        offs, name = a.split(":", 1)
        off = int(offs, 16)
        comp = cal.getComponentAt(off)
        if comp is None or comp.getOffset() != off:
            print("  SKIP +0x%04x=%s (no component starts here; got %s)" % (
                off, name, None if comp is None else "+0x%04x" % comp.getOffset()))
            skip += 1
            continue
        old = comp.getFieldName()
        try:
            comp.setFieldName(name)
            print("  +0x%04x  %-30s -> %s  (%s[%d])" % (
                off, old, name, comp.getDataType().getName(), comp.getLength()))
            done += 1
        except Exception as e:
            print("  FAIL +0x%04x=%s: %s" % (off, name, e))
            skip += 1
print("\nrenamed %d, skipped %d" % (done, skip))
print("== DONE ==")
