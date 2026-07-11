# Print defined members of /cal/Calibration whose offset is in any requested range.
# Args: space-separated "<starthex>:<endhex>" ranges. No args => print all named (non-padding) members.
# Read-only. @category Labeling
from ghidra.program.model.data import CategoryPath

dtm = currentProgram.getDataTypeManager()
cal = dtm.getDataType(CategoryPath("/cal"), "Calibration")
if cal is None:
    print("!! /cal/Calibration not found")
else:
    ranges = []
    for a in getScriptArgs():
        s, e = a.split(":")
        ranges.append((int(s, 16), int(e, 16)))
    print("Calibration length = 0x%x, numComponents=%d" % (cal.getLength(), cal.getNumComponents()))
    for c in cal.getComponents():
        off = c.getOffset()
        nm = c.getFieldName()
        if nm is None:   # undefined/padding
            continue
        inrange = (not ranges) or any(s <= off < e for s, e in ranges)
        if inrange:
            print("  +0x%04x  %-28s %s[%d]" % (off, nm, c.getDataType().getName(), c.getLength()))
print("== DONE ==")
