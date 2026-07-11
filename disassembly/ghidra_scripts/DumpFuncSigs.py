# Dump normalized per-function signatures for cross-program function matching.
# For the current program, writes a TSV file in the output directory named after
# the sanitized domain-file pathname. Columns:
#   addr  name  numInstr  numBytes  isThunk  sigHash
# The signature normalizes away addresses/immediates but preserves mnemonics and
# register operands, so byte-identical-but-differently-addressed HAL/library
# functions across firmwares hash to the same value.
# Arg: output directory (created if needed).
# @category Analysis
import hashlib, os

fm = currentProgram.getFunctionManager()
listing = currentProgram.getListing()

args = list(getScriptArgs())
outdir = args[0]
try:
    os.makedirs(outdir)
except Exception:
    pass

dfpath = currentProgram.getDomainFile().getPathname()
safe = dfpath.strip("/").replace("/", "_")
outpath = os.path.join(outdir, safe + ".sigs")


def op_rep(instr):
    parts = [instr.getMnemonicString()]
    for i in range(instr.getNumOperands()):
        rep = []
        for o in instr.getOpObjects(i):
            cls = o.getClass().getSimpleName()
            if cls == "Register":
                rep.append(o.getName())
            elif cls == "Scalar":
                rep.append("S")
            elif cls.endswith("Address"):
                rep.append("A")
            else:
                rep.append("?")
        parts.append(",".join(rep))
    return "|".join(parts)


f = open(outpath, "w")
count = 0
for func in fm.getFunctions(True):
    ep = func.getEntryPoint()
    body = func.getBody()
    toks = []
    for instr in listing.getInstructions(body, True):
        toks.append(op_rep(instr))
    ni = len(toks)
    if ni == 0:
        continue
    sig = ";".join(toks)
    h = hashlib.md5(sig).hexdigest()
    nb = body.getNumAddresses()
    isth = "T" if func.isThunk() else "."
    f.write("%s\t%s\t%d\t%d\t%s\t%s\n" % (ep, func.getName(), ni, nb, isth, h))
    count += 1
f.close()
print("DUMPSIG wrote %d functions to %s" % (count, outpath))
