# Read-only: dump the automatic shift-point calibration cluster + compute rpm thresholds.
# @category Analysis
import jarray
mem = currentProgram.getMemory()
space = currentProgram.getAddressFactory().getDefaultAddressSpace()
def A(v): return space.getAddress(v)
def rd(off, n):
    b = jarray.zeros(n, 'b'); mem.getBytes(A(off), b)
    return [x & 0xff for x in b]
def u16le(off):  # these cals are stored big-endian on PPC; show both
    b = rd(off, 2); return (b[0] << 8) | b[1]

def row(off, n, label):
    b = rd(off, n)
    print("  %-28s @0x%08x: %s" % (label, off, " ".join("%3d" % x for x in b)))

print("== per-gear base shift speeds (build funcs; x25 -> rpm-ish) ==")
row(0x4000d35b, 4, "base_up_manual g2-5 (d35b)")
row(0x4000d360, 5, "base_up_auto  g1-5 (d360)")
print("  d35f(up max)=%d  d365(auto max)=%d  d359(dn offset)=%d  d307(offset)=%d" % (
    rd(0x4000d35f,1)[0], rd(0x4000d365,1)[0], rd(0x4000d359,1)[0], rd(0x4000d307,1)[0]))

print("\n== throttle-axis breakpoints (8pt) ==")
row(0x4000d76e, 8, "up_manual  thr-axis (d76e)")
row(0x4000d77e, 8, "up_auto    thr-axis (d77e)")
row(0x4000d78e, 8, "dn_manual  thr-axis (d78e)")
row(0x4000d79e, 8, "dn_auto    thr-axis (d79e)")
print("\n== curve blend weights (8pt, 0..255) ==")
row(0x4000d776, 8, "up_manual  blend (d776)")
row(0x4000d786, 8, "up_auto    blend (d786)")
row(0x4000d796, 8, "dn_manual  blend (d796)")
row(0x4000d7a6, 8, "dn_auto    blend (d7a6)")

print("\n== per-gear upshift rev-limit offset (lookup 6, gear) ==")
row(0x4000c022, 6, "gear axis (c022)")
row(0x4000c028, 6, "revlimit offset x5 (c028)")

print("\n== gear ratios (u16 BE) + speed const ==")
print("  CAL_gear_ratio_1..6 = %s" % " ".join(str(u16le(0x40009094+2*i)) for i in range(6)))
print("  DAT_40008f7c (speed/tire const) = %d (u16=%d)" % (rd(0x40008f7c,1)[0], u16le(0x40008f7c)))
print("  DAT_40009158 (kickdown) = %d" % rd(0x40009158,1)[0])
print("== DONE ==")
