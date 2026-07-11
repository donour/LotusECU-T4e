# Apply names from a file. Arg: path to a text file with one "<loc> <name>" per line.
#   loc  = hex address (e.g. dc32 / 0065) OR an existing symbol name.
#   name = first whitespace token after loc; trailing "# comment" is stripped.
# Function at addr -> rename function; else primary data symbol -> rename; else label.
# Requires write access (omit -readOnly; GUI project closed / file checked out).
# @category Labeling
from ghidra.program.model.symbol import SourceType

space = currentProgram.getAddressFactory().getDefaultAddressSpace()
fm = currentProgram.getFunctionManager()
st = currentProgram.getSymbolTable()

def resolve(loc):
    try:
        return space.getAddress(int(loc, 16))
    except ValueError:
        for s in st.getSymbols(loc):
            return s.getAddress()
    return None

args = list(getScriptArgs())
if not args:
    print("!! no names-file argument");
else:
    path = args[0]
    ok = bad = 0
    for raw in open(path):
        line = raw.split("#", 1)[0].strip()
        if not line:
            continue
        parts = line.split(None, 1)
        if len(parts) < 2:
            continue
        loc, name = parts[0], parts[1].split()[0]
        addr = resolve(loc)
        if addr is None:
            print("  !! could not resolve %s" % loc); bad += 1; continue
        try:
            f = fm.getFunctionAt(addr)
            if f is not None:
                f.setName(name, SourceType.USER_DEFINED)
                print("  func  %s -> %s" % (addr, name)); ok += 1
            else:
                sym = st.getPrimarySymbol(addr)
                if sym is not None:
                    sym.setName(name, SourceType.USER_DEFINED)
                    print("  data  %s -> %s" % (addr, name)); ok += 1
                else:
                    createLabel(addr, name, True)
                    print("  label %s -> %s" % (addr, name)); ok += 1
        except Exception as e:
            print("  !! %s (%s) failed: %s" % (loc, name, e)); bad += 1
    print("== DONE ok=%d bad=%d ==" % (ok, bad))
