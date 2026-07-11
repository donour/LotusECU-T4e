# WRITE: type + label the two unreferenced neighbor clutch pressure curves that
# bracket the CAL_shift_pressure_curve_ptr_a/b curve block. Same structure as the
# referenced ones: load_axis[8] (base) + pressure[8] (base+8).
# Guarded to the TCU domain file. Omit -readOnly to save. @category Labeling
from ghidra.program.model.data import ArrayDataType, UnsignedCharDataType
from ghidra.program.model.symbol import SourceType

path = currentProgram.getDomainFile().getPathname()
if path != "/C132F0395.fullbin":
    print("REFUSING: wrong program %s" % path); raise SystemExit

space = currentProgram.getAddressFactory().getDefaultAddressSpace()
listing = currentProgram.getListing()
st = currentProgram.getSymbolTable()
def A(v): return space.getAddress(v)
BYTE = UnsignedCharDataType()
ARR8 = ArrayDataType(BYTE, 8, 1)

def put(addr, dt, name, comment=None):
    a = A(addr); ln = dt.getLength()
    listing.clearCodeUnits(a, a.add(ln - 1), False)
    listing.createData(a, dt)
    for s in st.getSymbols(a):
        if s.getSource() != SourceType.DEFAULT:
            s.delete()
    st.createLabel(a, name, SourceType.USER_DEFINED)
    if comment:
        listing.setComment(a, 0x0003, comment)  # PLATE

CURVES = [
 (0x4000cd62, "CAL_clutch_press_curve_cd62",
  "UNREFERENCED clutch pressure-vs-input_shaft_load curve (no pointer in CAL_shift_"
  "pressure_curve_ptr_a/b, no code/flash/RAM pointer anywhere in this image). Same axis "
  "family; sits one 16B slot BEFORE the referenced curve block (0x4000cd72). pressure[8]"
  "=all 0 (no-apply). Address parity = on-coming group. Likely a reserved/disabled slot."),
 (0x4000ce32, "CAL_clutch_press_curve_ce32",
  "UNREFERENCED clutch pressure-vs-input_shaft_load curve (no pointer anywhere in this "
  "image). Same axis family; sits one 16B slot AFTER the referenced block (right after "
  "CAL_clutch_press_oncoming_default @0x4000ce22). pressure[8]=flat 115. Address parity "
  "= off-going group. Likely a reserved/disabled slot."),
]
for base, stem, comment in CURVES:
    put(base, ARR8, stem + "_axis", comment)
    put(base + 8, ARR8, stem)
    print("  %-30s @0x%08x (axis 0x%08x)" % (stem, base + 8, base))
print("== DONE ok ==")
