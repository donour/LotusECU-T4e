# WRITE: apply U660E friction-element identification (verified from apply table +
# CAL_shift_clutch_element + DAT_0008dfe9). Fixes swapped on/off-going names and
# documents the element<->bit<->solenoid mapping. @category Labeling
from ghidra.program.model.symbol import SourceType
from ghidra.program.model.listing import CodeUnit

path = currentProgram.getDomainFile().getPathname()
if path != "/C132F0395.fullbin":
    print("REFUSING: wrong program %s" % path); raise SystemExit

space = currentProgram.getAddressFactory().getDefaultAddressSpace()
st = currentProgram.getSymbolTable()
fm = currentProgram.getFunctionManager()
listing = currentProgram.getListing()
def A(v): return space.getAddress(v)

# 1) fix swapped on/off-going element-id names ([from][to] = off-going)
def rename(off, nm):
    a = A(off); s = st.getPrimarySymbol(a)
    if s is not None: s.setName(nm, SourceType.USER_DEFINED)
    else: st.createLabel(a, nm, SourceType.USER_DEFINED)
# use temp names to avoid a transient duplicate-name collision during the swap
rename(0x40001add, "clutch_elem_offgoing_id_tmp")
rename(0x40001adc, "clutch_elem_oncoming_id")
rename(0x40001add, "clutch_elem_offgoing_id")

# 2) plate comments
CM = CodeUnit.PLATE_COMMENT
EOL = CodeUnit.EOL_COMMENT
listing.setComment(A(0x8d9d0), CM,
 "CAL_gear_clutch_bitmask[gear 0..10]: U660E friction-element apply mask. "
 "bit4=C1(input/fwd clutch) bit3=C2(direct) bit2=B1(2-6 brake) bit1=C3(underdrive); "
 "bit0/bit5 unused in fwd gears (B2 reverse brake handled separately). "
 "1=C1 2=C1+B1 3=C1+C3 4=C1+C2 5=C2+C3 6=C2+B1 ; R(gear10)=C3(+B2).")
listing.setComment(A(0x8dfe9), CM,
 "element-id -> solenoid map (10-byte stride; byte0 = index into solenoid_SL_demand[]). "
 "Verified physical mapping: SL1=C1, SL2=C2, SL3=B1, SL4=C3 (each element has 2 ids = "
 "apply/release profiles). SLT=line pressure, SLU=lock-up (TCC).")
listing.setComment(A(0x8db28), CM,
 "CAL_shift_clutch_element[from*7+to] = OFF-GOING element id released leaving `from` "
 "(constant per from-gear); [to*7+from] = on-coming element id. Ids route to solenoids "
 "via DAT_0008dfe9. 0xff=no element / invalid.")
listing.setComment(A(0x7fdd0), CM,
 "U660E 6-speed automatic (Aisin) clutch-to-clutch shift controller (param_1=from gear, "
 "param_2=to; torque converter w/ lock-up). On shift_exec_init loads per-gear-pair cal "
 "(CAL_shift_profile_index/clutch_element/type, CAL_gear_clutch_bitmask) + per-profile "
 "pressure curves (CAL_shift_pressure_curve_ptr_a/b, 0x8d9xx-0x8dfxx family). Each cycle "
 "loops the friction elements computing on-coming/off-going pressures into "
 "solenoid_SL_demand[] (SL1=C1, SL2=C2, SL3=B1, SL4=C3; SLT=line, SLU=lock-up). Engaged "
 "elements accumulate in clutch_mask_current; RETURNS 1 when clutch_mask_current == "
 "clutch_mask_target (shift complete) else 0.")

# 3) EOL notes on the four clutch solenoids
for nm, elem in [("solenoid_SL1_demand","C1 (input/fwd clutch)"),
                 ("solenoid_SL2_demand","C2 (direct clutch)"),
                 ("solenoid_SL3_demand","B1 (2-6 brake)"),
                 ("solenoid_SL4_demand","C3 (underdrive clutch)")]:
    syms = st.getGlobalSymbols(nm)
    if syms:
        listing.setComment(syms[0].getAddress(), EOL, "U660E %s apply-pressure demand" % elem)
print("== DONE ok ==")
