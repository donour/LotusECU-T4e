# Read-only: dump the ATF/oil-temp sensor table + related cals by symbol name,
# to derive the temperature scale of oil_temp_raw / oil_temp_unknown. @category Analysis
import jarray
mem = currentProgram.getMemory()
st = currentProgram.getSymbolTable()
space = currentProgram.getAddressFactory().getDefaultAddressSpace()

def addr_of(name):
    for s in st.getGlobalSymbols(name):
        return s.getAddress()
    for s in st.getSymbols(name):
        return s.getAddress()
    return None

def dump(name, n):
    a = addr_of(name)
    if a is None:
        print("  !! not found: %s" % name); return
    buf = jarray.zeros(n, 'b')
    mem.getBytes(a, buf)
    vals = [x & 0xff for x in buf]
    print("-- %s @%s (%d bytes) --" % (name, a, n))
    print("   u8 : " + " ".join("%3d" % v for v in vals))

dump("CAL_sensor_oil_temp", 32)
dump("CAL_oil_temp_fallback", 1)
dump("CAL_shift_speed_1_2_manual_X_oil_temp", 8)
dump("CAL_shift_neutral_release_timer_from_drive_X_oil_temp", 8)
for nm in ["DAT_4000e439","DAT_4000e44c","DAT_4000e45e","DAT_4000e470","DAT_4000e482",
           "DAT_4000e494","DAT_4000e4d3","DAT_4000e4d4","DAT_40009026","DAT_4000e3e0"]:
    dump(nm, 1)
print("== DONE ==")
