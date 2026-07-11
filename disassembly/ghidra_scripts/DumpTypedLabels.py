# Dump defined data with non-default names and non-undefined types.
# Output: addr<TAB>name<TAB>datatype<TAB>existingEOL
# @category Analysis
import re
import io
from ghidra.program.model.symbol import SourceType

out_path = getScriptArgs()[0] if len(getScriptArgs()) > 0 else "typed_labels.tsv"
listing = currentProgram.getListing()

AUTO_PREFIXES = ('DAT_','FUN_','LAB_','SUB_','UNK_','PTR_','SWITCH_','switchD','switchdataD',
                 'caseD_','s_','u_','EXT_','byte_','word_','dword_')

def is_undefined_type(dt):
    base = re.sub(r'[\[\*].*$', '', dt.getName().strip()).strip().lower()
    return base.startswith('undefined') or base == ''

def is_autoname(name):
    for p in AUTO_PREFIXES:
        if name.startswith(p):
            return True
    return False

count = 0
skipped = 0
addr = None
f = io.open(out_path, "w", encoding="utf-8")
it = listing.getDefinedData(True)
while it.hasNext():
    try:
        d = it.next()
        sym = d.getPrimarySymbol()
        if sym is None:
            continue
        if sym.getSource() == SourceType.DEFAULT:
            continue
        name = sym.getName()
        if is_autoname(name):
            continue
        dt = d.getDataType()
        if is_undefined_type(dt):
            continue
        addr = d.getAddress()
        eol = listing.getComment(0, addr)  # 0 == EOL_COMMENT
        eol = "" if eol is None else eol.replace("\t", " ").replace("\n", " ")
        f.write(u"%s\t%s\t%s\t%s\n" % (addr, name, dt.getName(), eol))
        count += 1
        if (count % 500) == 0:
            f.flush()
    except Exception as e:
        skipped += 1
        try:
            print("SKIP %s : %s" % (addr, e))
        except:
            pass
f.close()
print("WROTE %d labels to %s (skipped %d)" % (count, out_path, skipped))
