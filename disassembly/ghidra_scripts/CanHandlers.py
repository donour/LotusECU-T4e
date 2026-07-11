# Find CAN message handler functions by the documented CAN-ID constants.
# Scans each function's scalar operands for known IDs; reports candidates with
# how many distinct IDs they touch (a single-ID function is a strong handler
# candidate; many-ID functions are dispatchers/tx schedulers). Read-only.
# @category Recon
fm = currentProgram.getFunctionManager()
listing = currentProgram.getListing()

# documented vehicle/diag CAN IDs -> short description (from CLAUDE.md)
IDS = {
    0x7DF: "diag_func_req", 0x7E0: "diag_phys_req", 0x7E8: "diag_resp",
    0x730: "diag_730", 0x7FF: "diag_7ff",
    0x102: "torque_to_abs", 0x114: "tach_pedal", 0x400: "cluster",
    0x085: "sas_steer", 0x0D2: "ips_req", 0x303: "yaw_lataccel",
    0x0A2: "wheel_spd_front", 0x0A4: "wheel_spd_rear", 0x0A8: "abs_esp_status",
}
# IDs that are common small integers -> only trust with corroboration
COMMON = set([0x102, 0x114, 0x400, 0x85, 0xD2, 0xA2, 0xA4, 0xA8])

# per function: which IDs appear (and operand count)
hits = {}   # entryoff -> {id: count}
for f in fm.getFunctions(True):
    body = f.getBody()
    it = listing.getInstructions(body, True)
    found = {}
    while it.hasNext():
        ins = it.next()
        for i in range(ins.getNumOperands()):
            for obj in ins.getOpObjects(i):
                try:
                    v = obj.getValue() & 0xffffffff
                except:
                    continue
                if v in IDS:
                    found[v] = found.get(v, 0) + 1
    if found:
        hits[f] = found

# rank: single distinctive ID = strong handler candidate
strong = []
disp = []
weak = []
for f, found in hits.items():
    ids = list(found.keys())
    distinctive = [i for i in ids if i not in COMMON]
    if len(ids) == 1 and ids[0] not in COMMON:
        strong.append((f, ids))
    elif len(ids) >= 3:
        disp.append((f, ids))
    elif distinctive:
        strong.append((f, ids))
    else:
        weak.append((f, ids))

def fmt(ids):
    return ", ".join("0x%X(%s)" % (i, IDS[i]) for i in sorted(ids))

print("==== STRONG single/distinctive-ID handler candidates (%d) ====" % len(strong))
for (f, ids) in sorted(strong, key=lambda x: x[0].getEntryPoint().getOffset()):
    print("  %s  %-26s  ids: %s" % (f.getEntryPoint(), f.getName(), fmt(ids)))
print("\n==== DISPATCHER/multi-ID candidates (%d) ====" % len(disp))
for (f, ids) in sorted(disp, key=lambda x: x[0].getEntryPoint().getOffset()):
    print("  %s  %-26s  ids: %s" % (f.getEntryPoint(), f.getName(), fmt(ids)))
print("\n==== weak (common-ID only) (%d) ====" % len(weak))
for (f, ids) in sorted(weak, key=lambda x: x[0].getEntryPoint().getOffset())[:40]:
    print("  %s  %-26s  ids: %s" % (f.getEntryPoint(), f.getName(), fmt(ids)))
