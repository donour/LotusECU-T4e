# Coverage/gap report for /cal/Calibration: classify every defined member as
#   READY   = analyst-named AND element is a unit typedef (scaling derivable for RomRaider)
#   NAMED   = analyst-named but raw uchar/ushort element (needs scaling/units)
#   AUTO    = still tbl_XXXX / axis_XXXX (not yet named)
# Prints counts + the NAMED-raw worklist (data tables first) + a sample of AUTO data tables.
# Read-only. @category Calibration
import re
from ghidra.program.model.data import CategoryPath

dtm = currentProgram.getDataTypeManager()
cal = dtm.getDataType(CategoryPath("/cal"), "Calibration")
AUTO = re.compile(r"^(tbl|axis)_[0-9a-f]{4}$")
AUTO2 = re.compile(r"^axis_[a-z_]+_[0-9a-f]{4}$")
RAW = ("uchar", "ushort", "byte", "undefined1", "undefined2", "char", "short")

def elem_name(dt):
    n = dt.getName()
    # array -> element
    m = re.match(r"^([A-Za-z0-9_/+\-]+)\[", n)
    return m.group(1) if m else n

ready=[]; named=[]; auto=[]
for c in cal.getComponents():
    nm = c.getFieldName()
    if not nm:
        continue
    en = elem_name(c.getDataType())
    is_auto = AUTO.match(nm) or AUTO2.match(nm)
    is_unit = ("_" in en and en[0] in "ui" and any(ch.isdigit() for ch in en)) or "/" in en
    # a real unit datatype makes it RomRaider-ready regardless of the (possibly auto) name
    if is_unit:
        ready.append((c.getOffset(), nm, en, c.getLength()))
    elif is_auto:
        auto.append((c.getOffset(), nm, en, c.getLength()))
    else:
        named.append((c.getOffset(), nm, en, c.getLength()))

print("==== Calibration coverage (%d named members) ====" % (len(ready)+len(named)+len(auto)))
print("  READY (named + unit typedef)   : %d" % len(ready))
print("  NAMED (named, raw type)        : %d  <- needs scaling/units" % len(named))
print("  AUTO  (tbl_/axis_, unnamed)    : %d" % len(auto))

def is_data(nm): return not (nm.endswith(("_X","_Y")) or "_X_" in nm or "_Y_" in nm or "axis" in nm)

print("\n---- NAMED-raw DATA tables (the scaling worklist) ----")
nd = [r for r in named if is_data(r[1])]
for off,nm,en,ln in sorted(nd):
    print("  +0x%04x  %-40s %s[%d]" % (off, nm, en, ln))
print("  (%d named-raw data tables; %d named-raw axes omitted)" % (len(nd), len(named)-len(nd)))

print("\n---- AUTO data tables still unnamed (sample) ----")
ad = [r for r in auto if r[1].startswith("tbl_")]
for off,nm,en,ln in sorted(ad)[:40]:
    print("  +0x%04x  %-14s %s[%d]" % (off, nm, en, ln))
print("  (%d unnamed tbl_ data tables, %d unnamed axes)" % (len(ad), len(auto)-len(ad)))
print("== DONE ==")
