# Apply EOL comments from a TSV file: addr<TAB>comment
# Only sets the EOL comment when the address currently has none (non-destructive).
# @category Analysis
import io
from ghidra.program.model.listing import CodeUnit

args = getScriptArgs()
path = args[0]
overwrite = (len(args) > 1 and args[1].lower() == "overwrite")

listing = currentProgram.getListing()
af = currentProgram.getAddressFactory()

applied = 0
skipped_existing = 0
bad = 0
f = io.open(path, "r", encoding="utf-8")
for line in f:
    line = line.rstrip(u"\r\n")
    if not line:
        continue
    parts = line.split(u"\t")
    if len(parts) < 2:
        continue
    hexa, comment = parts[0], parts[1]
    try:
        addr = af.getAddress(hexa)
    except:
        addr = None
    if addr is None:
        bad += 1
        continue
    cur = listing.getComment(CodeUnit.EOL_COMMENT, addr)
    if cur is not None and cur.strip() and not overwrite:
        skipped_existing += 1
        continue
    listing.setComment(addr, CodeUnit.EOL_COMMENT, comment)
    applied += 1
f.close()
print("APPLIED %d EOL comments (skipped %d existing, %d bad addrs)" % (applied, skipped_existing, bad))
