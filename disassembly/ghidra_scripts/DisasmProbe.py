# Probe: disassemble undefined regions (in-memory) and report whether they are valid VLE code.
# For each hex address arg, run DisassembleCommand, then walk instructions from that addr and
# report count, end, any calls, and references to CALBASE_addr (0x40003340) / cal offset imm.
# Run with -readOnly to probe without persisting (disassembly stays in the throwaway transaction).
# @category Analysis
from ghidra.app.cmd.disassemble import DisassembleCommand
from ghidra.util.task import ConsoleTaskMonitor

space = currentProgram.getAddressFactory().getDefaultAddressSpace()
listing = currentProgram.getListing()
mon = ConsoleTaskMonitor()

for a in getScriptArgs():
    start = space.getAddress(int(a, 16))
    cmd = DisassembleCommand(start, None, True)
    cmd.applyTo(currentProgram, mon)
    n = 0
    calls = 0
    cal_imm = 0
    bad = 0
    ins = listing.getInstructionAt(start)
    last = start
    addr = start
    while ins is not None and n < 4000:
        n += 1
        last = ins.getAddress()
        ft = ins.getFlowType()
        if ft is not None and ft.isCall():
            calls += 1
        txt = ins.toString()
        if "0x50d8" in txt or "0x50d0" in txt or "20752" in txt:
            cal_imm += 1
        nxt = ins.getAddress().add(ins.getLength())
        ins2 = listing.getInstructionAt(nxt)
        if ins2 is None:
            # stop at first gap / terminator
            if ft is not None and (ft.isTerminal()):
                break
            # gap that isn't a terminator => likely end or undecodable
            break
        ins = ins2
    print("probe %s : %d instrs, end~%s, calls=%d, cal0x50d8_refs=%d" % (
        start, n, last, calls, cal_imm))
print("== DONE ==")
