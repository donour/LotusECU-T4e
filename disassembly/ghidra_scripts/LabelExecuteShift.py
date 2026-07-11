# WRITE: name execute_shift's clutch-control state + add documenting plate comments.
# Guarded to the TCU domain file. Omit -readOnly to save. @category Labeling
from ghidra.program.model.symbol import SourceType
from ghidra.program.model.listing import CodeUnit

path = currentProgram.getDomainFile().getPathname()
if path != "/C132F0395.fullbin":
    print("REFUSING: wrong program %s" % path); raise SystemExit

space = currentProgram.getAddressFactory().getDefaultAddressSpace()
fm = currentProgram.getFunctionManager()
st = currentProgram.getSymbolTable()
listing = currentProgram.getListing()
def A(v): return space.getAddress(v)

NAMES = {
 # --- shift-state scalars ---
 0x40001b6a: "clutch_mask_target",        # CAL_gear_clutch_bitmask[to]
 0x40001bd4: "clutch_mask_current",       # working mask; == target => shift done
 0x40001c74: "shift_mode_word",
 0x40001ad9: "shift_profile_index",       # 0..0x12, 0xff=idle
 0x40001add: "clutch_elem_oncoming_id",
 0x40001adc: "clutch_elem_offgoing_id",
 0x40001488: "clutch_idx_oncoming",
 0x40001489: "clutch_idx_offgoing",
 0x40001ada: "shift_phase2_started",
 0x40001b83: "shift_torque_phase_hold",
 0x40001bf6: "shift_ramp_timer",
 0x400014ac: "shift_ramp_step",
 0x40001ad7: "slip_settle_timer",
 0x40001ad8: "shift_substage",
 0x40001bd2: "slip_threshold",
 0x400014ae: "pressure_setpoint_oncoming",
 0x400014af: "pressure_setpoint_offgoing",
 0x40001b70: "clutch_pressure_base_a",
 0x40001b71: "clutch_pressure_base_b",
 0x40001b72: "clutch_pressure_base_c",
 0x40001b73: "shift_end_load_dn_light",
 0x40001b74: "shift_end_load_dn_heavy",
 0x40001b75: "shift_end_load_up_light",
 0x40001b76: "shift_end_load_up_heavy",
 0x40001b78: "torque_phase_pressure",
 0x40001b7c: "torque_phase_pressure_pct",
 # --- per clutch-element arrays [0..5] (base = element 0) ---
 0x40001b64: "clutch_elem_action",        # 0=idle 1=on-coming 2=off-going
 0x40001bcc: "clutch_elem_ramp_phase",
 0x40001bc4: "clutch_elem_fill_delay",
 0x40001bbc: "clutch_elem_fill_delay_reload",
 0x40001bb4: "clutch_elem_step_count",
 0x4000638c: "clutch_elem_pressure_cmd",
 0x40006368: "clutch_elem_pressure_endpoint",
 0x40006398: "clutch_elem_prefill_pressure",
 0x40001ba8: "clutch_elem_ramp_step",
 0x40006328: "clutch_elem_pressure_accum",
 0x40006350: "clutch_elem_pressure_hold",
 0x40006374: "clutch_elem_pressure_delta",
 0x40006380: "clutch_elem_pressure_ref",
 0x400063b8: "clutch_elem_slip_error",
 0x400063d0: "clutch_elem_slip_ref",
}
COMMENTS = {
 0x7fdd0: ("Clutch-to-clutch shift controller (param_1=from gear, param_2=to). On "
   "shift_exec_init it loads per-gear-pair cal (CAL_shift_profile_index/clutch_element/"
   "type, CAL_gear_clutch_bitmask) + selects per-profile pressure curves via "
   "CAL_shift_pressure_curve_ptr_a/b and the 0x8d9xx-0x8dfxx pointer-table family. Each "
   "cycle it loops the 6 clutch elements computing per-element pressure commands into "
   "solenoid_SL_demand[]; engaged clutches accumulate in clutch_mask_current. RETURNS 1 "
   "when clutch_mask_current == clutch_mask_target (shift complete) else 0."),
 0x40001c74: ("shift_mode_word: bit0=upshift bit1=downshift; bit2=heavy/power-load "
   "bit3=light/coast-load; bit4=single-gear bit5=multi/skip. Low nibble 5=up-power "
   "9=up-coast 6=down-power 10=down-coast."),
 0x40001b64: "clutch_elem_action[0..5]: 0=inactive, 1=on-coming (engaging), 2=off-going (releasing).",
 0x40001b6a: "clutch_mask_target: target-gear clutch bitmask; shift done when clutch_mask_current matches.",
}

done = 0
for off, nm in sorted(NAMES.items()):
    a = A(off)
    f = fm.getFunctionAt(a)
    if f is not None:
        f.setName(nm, SourceType.USER_DEFINED)
    else:
        s = st.getPrimarySymbol(a)
        if s is not None:
            s.setName(nm, SourceType.USER_DEFINED)
        else:
            st.createLabel(a, nm, SourceType.USER_DEFINED)
    done += 1
for off, txt in COMMENTS.items():
    listing.setComment(A(off), CodeUnit.PLATE_COMMENT, txt)
print("named %d, commented %d" % (done, len(COMMENTS)))
print("== DONE ok ==")
