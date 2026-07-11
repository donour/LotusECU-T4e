# WRITE: type + label the execute_shift per-gear-pair flash calibration tables.
# Guarded to the TCU domain file. Omit -readOnly to save. @category Labeling
from ghidra.program.model.data import (ArrayDataType, UnsignedCharDataType,
    PointerDataType)
from ghidra.program.model.symbol import SourceType

path = currentProgram.getDomainFile().getPathname()
if path != "/C132F0395.fullbin":
    print("REFUSING: wrong program %s" % path); raise SystemExit

space = currentProgram.getAddressFactory().getDefaultAddressSpace()
listing = currentProgram.getListing()
st = currentProgram.getSymbolTable()
def A(v): return space.getAddress(v)
BYTE = UnsignedCharDataType()
PTR = PointerDataType(None, 4)

PLATE = {
 0x8daf4: "CAL_shift_profile_index[from*7+to]: 0xff=invalid, else shift-profile index 0..0x12 "
          "(selects clutch pressure curve via CAL_shift_pressure_curve_ptr_a/b).",
 0x8db28: "CAL_shift_clutch_element[from*7+to]: clutch element id (0..7); execute_shift reads "
          "both [from][to] (on-coming) and [to][from] (off-going). 0xff=invalid.",
 0x8db5c: "CAL_shift_type[from*7+to]: 0/1/2 shift-type flag (execute_shift compares ==2).",
 0x8d9d0: "CAL_gear_clutch_bitmask[gear 0..10]: clutch element bitmask engaged in each gear.",
 0x8dbdc: "CAL_shift_pressure_curve_ptr_a[profile 0..18]: ptr to on-coming clutch pressure-vs-load "
          "curve (8-axis+8-data u8) in RAM cal shadow.",
 0x8dc28: "CAL_shift_pressure_curve_ptr_b[profile 0..18]: ptr to off-going clutch pressure-vs-load curve.",
}
DEFS = [
 (0x8daf4, ArrayDataType(BYTE, 49, 1), "CAL_shift_profile_index"),
 (0x8db28, ArrayDataType(BYTE, 49, 1), "CAL_shift_clutch_element"),
 (0x8db5c, ArrayDataType(BYTE, 49, 1), "CAL_shift_type"),
 (0x8d9d0, ArrayDataType(BYTE, 11, 1), "CAL_gear_clutch_bitmask"),
 (0x8dbdc, ArrayDataType(PTR, 19, 4), "CAL_shift_pressure_curve_ptr_a"),
 (0x8dc28, ArrayDataType(PTR, 19, 4), "CAL_shift_pressure_curve_ptr_b"),
]
for off, dt, nm in DEFS:
    a = A(off); ln = dt.getLength()
    listing.clearCodeUnits(a, a.add(ln - 1), False)
    d = listing.createData(a, dt)
    for s in st.getSymbols(a):
        if s.getSource() != SourceType.DEFAULT:
            s.delete()
    st.createLabel(a, nm, SourceType.USER_DEFINED)
    listing.setComment(a, 0x0003, PLATE[off])  # PLATE comment
    print("  defined %-32s @0x%06x  %s (%d B)" % (nm, off, dt.getName(), ln))
print("== DONE ok ==")
