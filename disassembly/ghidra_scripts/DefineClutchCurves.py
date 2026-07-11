# WRITE: type + label the 12 clutch pressure-vs-load curves (RAM shadow) referenced
# by CAL_shift_pressure_curve_ptr_a/b. Each = load_axis[8] (base) + pressure[8] (base+8).
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

# role -> list of (base_addr, tag)  ; base = axis, base+8 = pressure data
CURVES = {
 "oncoming": [(0x4000cd82,"1_2"),(0x4000cda2,"2_3"),(0x4000cdc2,"3_4"),
              (0x4000cde2,"4_5"),(0x4000ce02,"5_6"),(0x4000ce22,"default")],
 "offgoing": [(0x4000cd72,"1_2"),(0x4000cd92,"2_3"),(0x4000cdb2,"3_4"),
              (0x4000cdd2,"4_5"),(0x4000cdf2,"5_6"),(0x4000ce12,"default")],
}

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

n = 0
for role in ("oncoming", "offgoing"):
    for base, tag in CURVES[role]:
        stem = "CAL_clutch_press_%s_%s" % (role, tag)
        put(base, ARR8, stem + "_axis",
            "%s clutch pressure vs input_shaft_load. axis[8]=load breakpoints; "
            "pressure[8] at +8 (255=full). Used for shift-profile %s." % (role, tag))
        put(base + 8, ARR8, stem)
        print("  %-34s @0x%06x (axis 0x%06x)" % (stem, base + 8, base))
        n += 2
print("defined %d symbols" % n)
print("== DONE ok ==")
