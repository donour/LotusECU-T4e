# Create enum_throttle_actuator_state in the C132E0278 program and retype the
# throttle_actuator_state global, so the decompiler renders the ETB status byte
# symbolically (e.g. `throttle_actuator_state == TSL_SHUTDOWN`).
#
# throttle_actuator_state is the HC08 ETB-monitor status byte: it is written
# ONLY from the HC08 message (hc08_parse_buf[2]) and drives DTCs P1104/P2104/
# P2105. Values 0..10 mirror the HC08 `throttle_status_level_t` exactly, so the
# member names are reused to make the cross-processor link explicit.
#
# Resolves the global by name (must already be named). 1-byte enum.
#
# Usage (dry-run review):
#   analyzeHeadless <projloc> "Lotus ECU" -process C132E0278.fullbin -readOnly \
#       -noanalysis -scriptPath <dir> -postScript ApplyThrottleActuatorEnum.py
# Apply (writes DB -- omit -readOnly; GUI closed / file checked out):
#       ... -postScript ApplyThrottleActuatorEnum.py apply
#
# @category Labeling
from ghidra.program.model.data import EnumDataType, CategoryPath, DataTypeConflictHandler

args = [a.lower() for a in getScriptArgs()]
APPLY = "apply" in args

p = currentProgram
print("PROGRAM name=%s path=%s" % (p.getName(), p.getDomainFile().getPathname()))

dtm = p.getDataTypeManager()
st = p.getSymbolTable()
cat = CategoryPath("/")

ENUM = "enum_throttle_actuator_state"
GLOBAL = "throttle_actuator_state"
MEMBERS = [
    ("TSL_INIT", 0), ("TSL_MODE_1", 1), ("TSL_MODE_2", 2), ("TSL_MODE_3", 3),
    ("TSL_MONITOR_4", 4), ("TSL_MONITOR_5", 5), ("TSL_MONITOR_6", 6),
    ("TSL_REARM", 7), ("TSL_RUN", 8), ("TSL_FAULT", 9), ("TSL_SHUTDOWN", 10),
]

e = EnumDataType(cat, ENUM, 1)   # 1-byte enum
for (m, v) in MEMBERS:
    e.add(m, v)
print("enum %s: %d members" % (ENUM, len(MEMBERS)))

addr = None
for s in st.getSymbols(GLOBAL):
    addr = s.getAddress()
    break
if addr is None:
    print("!! global %s not found -- name it first" % GLOBAL)
else:
    print("global %s @ %s -> %s" % (GLOBAL, addr, ENUM))

if not APPLY:
    print("(dry-run) re-run with 'apply' (and without -readOnly) to write the DB.")
elif addr is not None:
    dt = dtm.addDataType(e, DataTypeConflictHandler.REPLACE_HANDLER)
    print("  + datatype /%s" % ENUM)
    try:
        clearListing(addr, addr)
        createData(addr, dt)
        print("  retyped %s @ %s -> %s" % (GLOBAL, addr, ENUM))
        print("==== DONE retyped=1 ====")
    except Exception as ex:
        print("  !! retype failed: %s" % ex)
