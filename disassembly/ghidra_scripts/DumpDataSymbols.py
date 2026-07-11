# Dump every data symbol (RAM + flash) with its address, name, defined-datatype
# and length. Useful for type inference: shows which globals are already typed
# (e.g. u16_rspeed_*) and which are still undefined/raw.
# Arg: output TSV path. Columns: addr  name  type  length  source
# @category Analysis
listing = currentProgram.getListing()
st = currentProgram.getSymbolTable()
fm = currentProgram.getFunctionManager()

args = list(getScriptArgs())
outpath = args[0]
f = open(outpath, "w")
count = 0
for sym in st.getAllSymbols(True):
    addr = sym.getAddress()
    if addr is None or not addr.isMemoryAddress():
        continue
    off = addr.getOffset()
    # data regions: flash 0..0x100000 and RAM 0x40000000..0x40010000
    in_flash = off < 0x100000
    in_ram = 0x40000000 <= off < 0x40010000
    if not (in_flash or in_ram):
        continue
    if fm.getFunctionAt(addr) is not None:
        continue
    stype = str(sym.getSymbolType())
    if stype not in ("Label",):
        continue
    d = listing.getDataAt(addr)
    if d is not None and d.isDefined():
        dt = d.getDataType()
        tname = dt.getName()
        tlen = dt.getLength()
    else:
        tname = "-"
        tlen = 0
    f.write("%s\t%s\t%s\t%d\t%s\n" % (addr, sym.getName(), tname, tlen,
                                      sym.getSource()))
    count += 1
f.close()
print("DUMPDATA wrote %d data symbols to %s" % (count, outpath))
