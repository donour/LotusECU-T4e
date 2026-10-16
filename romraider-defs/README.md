## Introduction

To edit the "calrom.bin" files in RomRaider a definition file is required.

It's also possible to open the "decram.bin" file to show some learned data.

The T4e RomRaider definition is very complete and avalaible for free. For the
T6 definition please contact me.

## Regenerating Evora definitions

This exporter/source follow-up depends on the corrected GT430 and NA091 XML in
[PR #6](https://github.com/donour/LotusECU-T4e/pull/6). Merge or apply that
change first, and keep those reviewed XML files with this exporter revision.
The guard deliberately rejects the older GT430 definition.

The Evora CSV snapshots and C annotations now agree for the cold-start axis and
adjacent idle data, startup TPS retention factor, signed pressure offsets,
biased cylinder trim, injector-deadtime IAT axis, shiftlight gear/spacing
families, GT STFT learning thresholds, and raw GT idle output/while-moving
counts. CSV quoting and base signatures are also corrected. Other inherited annotations still need reconciliation; a CSV
snapshot does not update an already-open Ghidra database automatically.

For exact ROM ids `T6-EVORA--F430-V000E` and `T6-V00BU`, the existing
[`ExportRomRaiderDefs.java`](ghidra_scripts/ExportRomRaiderDefs.java) now loads the
checked-in XML before generating output. It preserves an explicit address list
of corrected metadata, including the two existing GT patched torque caps and
their warnings. It restores axes, scales, names and descriptions by ROM identity
and payload offset, rather than by table name. Obsolete standalone GT shiftlight
axis views are removed only after validating their shape and nested replacement.
The duplicate identical datatype registration is removed; alternative units stay.

Regeneration aborts before replacing the output if a protected ROM/table is
missing or duplicated, a ROM signature differs, or a payload's address, byte
width, dimensions, type or byte order has changed. Same-width signedness fixes
and reviewed axis restoration are allowed. The output is serialized to a
sibling temporary file and atomically replaces the destination only after the
loaded XML is checked for concurrent changes. No partial output replaces the
existing definition on validation failure. Unknown profiles retain their normal
export behavior.

Keep the versioned definition in `romraider-defs`, one level above
`ghidra_scripts`, and align the corresponding Ghidra CAL/LEA primary labels, defined data types and base
signature comments before export. A missing-root error identifies the required
ROM/offset; do not remove the guard to bypass it. The historical generic symbols
at GT RAM `4000883C/E`, for example, must be named and typed for the new STFT
entries to be generated. The existing `ImportSymbolsFromCSV` utility expects a
rename CSV with `new_name`; these five-column symbol snapshots are not its
input format and require a deliberate database annotation update.

The protection trusts the versioned XML metadata. It does not validate original
firmware bytes, infer a new layout, reconcile the remaining ambiguous names, or
prove that a patched executable matches the 4 Nm/count torque-cap definitions.
Keep the matching reviewed XML and script revisions together.

## Usage

The "T4E90_defs.xml" file was created for a 2008 T4e ECU. It should also work
with 2006–2007 ECUs, but for best results, update your software to the latest
version.

Read the description of the tables:

![Description](../documentation/Usage/RomRaider2.png)

