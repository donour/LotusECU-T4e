# WRITE: label the MPC5534 INTC software-vector infrastructure in C132F0395.
#  1) define + name the default/spurious ISR at 0x40b00 (b . spin trap)
#  2) type the vector table at 0x8f800 as a pointer array + label INTC_vector_table
#  3) rename intc_init and the 25 unnamed active ISRs (by verified peripheral+vector)
# Guarded to the TCU domain file. Omit -readOnly to save. @category Labeling
from ghidra.app.cmd.disassemble import DisassembleCommand
from ghidra.app.cmd.function import CreateFunctionCmd
from ghidra.program.model.data import PointerDataType, ArrayDataType
from ghidra.util.task import ConsoleTaskMonitor
import jarray

path = currentProgram.getDomainFile().getPathname()
if path != "/C132F0395.fullbin":
    print("REFUSING: wrong program %s" % path); raise SystemExit

space = currentProgram.getAddressFactory().getDefaultAddressSpace()
fm = currentProgram.getFunctionManager()
listing = currentProgram.getListing()
mem = currentProgram.getMemory()
st = currentProgram.getSymbolTable()
mon = ConsoleTaskMonitor()
from ghidra.program.model.symbol import SourceType
def A(v): return space.getAddress(v)

# ---- 1) default ISR at 0x40b00 ----
DEF = 0x40b00
if fm.getFunctionAt(A(DEF)) is None:
    DisassembleCommand(A(DEF), None, True).applyTo(currentProgram, mon)
    if listing.getInstructionAt(A(DEF)) is not None:
        CreateFunctionCmd(A(DEF)).applyTo(currentProgram, mon)
f = fm.getFunctionAt(A(DEF))
if f is not None:
    f.setName("intc_default_isr", SourceType.USER_DEFINED)
    f.setComment("Default/spurious INTC vector target: `b .` spin trap. "
                 "Filled into all unused entries of INTC_vector_table.")
    print("  default ISR @0x%06x -> %s" % (DEF, f.getName()))
else:
    print("  WARN: could not create function at 0x%06x" % DEF)

# ---- 2) vector table @0x8f800 ----
BASE = 0x8f800
def rdw(off):
    b = jarray.zeros(4, 'b'); mem.getBytes(A(off), b)
    return ((b[0]&0xff)<<24)|((b[1]&0xff)<<16)|((b[2]&0xff)<<8)|(b[3]&0xff)
# extent: consecutive words that are DEFAULT or a plausible flash-code pointer
n = 0
while True:
    v = rdw(BASE + n*4)
    if v == DEF or (0x40100 <= v <= 0x88430 and (v & 1) == 0):
        n += 1
    else:
        break
    if n > 512:
        break
ptr = PointerDataType(None, 4)
arr = ArrayDataType(ptr, n, 4)
listing.clearCodeUnits(A(BASE), A(BASE + n*4 - 1), False)
listing.createData(A(BASE), arr)
# label
for s in st.getSymbols(A(BASE)):
    if s.getSource() != SourceType.DEFAULT:
        s.delete()
st.createLabel(A(BASE), "INTC_vector_table", SourceType.USER_DEFINED)
listing.setComment(A(BASE), 0x0003,  # PLATE
    "MPC5534 INTC software-vector table (base written to INTC_IACKR 0xfff48010 by "
    "intc_init). Index = interrupt vector number; %d entries. Unused vectors point "
    "to intc_default_isr." % n)
print("  INTC_vector_table @0x%06x : %d pointers (0x%x bytes)" % (BASE, n, n*4))

# ---- 3) renames ----
RENAMES = {
    0x40b1c: "intc_init",
    0x40b58: "swint_isr_vec004",
    0x47970: "emios_isr_vec051", 0x47bf8: "emios_isr_vec052",
    0x47908: "emios_isr_vec056", 0x478a4: "emios_isr_vec057",
    0x44a24: "etpu_a_isr_vec068", 0x44a28: "etpu_a_isr_vec079",
    0x44acc: "etpu_a_isr_vec080", 0x44b70: "etpu_a_isr_vec086",
    0x44b88: "etpu_a_isr_vec087", 0x44ba0: "etpu_a_isr_vec088",
    0x44bb8: "etpu_a_isr_vec089", 0x44bd0: "etpu_a_isr_vec090",
    0x44be8: "etpu_a_isr_vec091", 0x44c00: "etpu_a_isr_vec092",
    0x44c44: "etpu_a_isr_vec093", 0x44c90: "etpu_a_isr_vec094",
    0x44cdc: "etpu_a_isr_vec095", 0x44d28: "etpu_a_isr_vec096",
    0x44d74: "etpu_a_isr_vec097",
    0x56a8c: "esci_a_isr_vec146",
    0x55e60: "flexcan_a_isr_vec152", 0x55e78: "flexcan_a_isr_vec153",
    0x53108: "flexcan_a_rx_isr_vec158", 0x5380c: "flexcan_a_rx_isr_vec161",
}
done = skip = 0
for off, nm in sorted(RENAMES.items()):
    fn = fm.getFunctionAt(A(off))
    if fn is None:
        print("  MISS 0x%06x (no function)" % off); continue
    cur = fn.getName()
    if not cur.startswith("FUN_"):
        print("  SKIP 0x%06x already named %s" % (off, cur)); skip += 1; continue
    fn.setName(nm, SourceType.USER_DEFINED)
    done += 1
print("  renamed %d, skipped %d" % (done, skip))
print("== DONE ok ==")
