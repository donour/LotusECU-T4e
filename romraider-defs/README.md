## Introduction

To edit the "calrom.bin" files in RomRaider a definition file is required.

It's also possible to open the "decram.bin" file to show some learned data.

The T4e RomRaider definition is very complete and avalaible for free. For the
T6 definition please contact me.

## Usage

The "T4E90_defs.xml" file was created for a 2008 T4e ECU. It should also work
with 2006–2007 ECUs, but for best results, update your software to the latest
version.

Read the description of the tables:

![Description](../documentation/Usage/RomRaider2.png)

## Evora definition reviews

The [GT430 correction and verification notes](../disassembly/evora/C132E0278/analysis/GT430_ROMRAIDER_REVIEW.md)
and [NA091 correction ledger](../disassembly/evora/B13200091/DEFINITION_REVIEW.md)
record the reviewed fixes, evidence, unresolved binary checks and regeneration requirements.
The audit, reconciliation tool and tests use the Python 3.10+ standard library.
Run the regression checks from the repository root with:

```sh
python3 -m unittest discover -s romraider-defs/tests -v
```

## GT430 and NA091 whole definition map

The [whole-map comparison](../disassembly/evora/analysis/DEFINITION_MAP_COMPARISON.md)
covers every calibration and learned-data entry, subsystem behavior, and new verification candidates.
Generate a complete address-based CSV/JSON inventory without modifying definitions:

```sh
python3 romraider-defs/audit_definition_maps.py --output-dir /tmp/evora-definition-map-review
```

## Preserve reviewed metadata after a Ghidra export

Fresh exports can restore stale names, units or placeholder axes. Run the explicit
[metadata reconciliation command](reconcile_reviewed_metadata.py) after export,
using the checked-in reviewed XML as the canonical metadata source:

```sh
python3 romraider-defs/reconcile_reviewed_metadata.py /tmp/gt430-export.xml --rom-id T6-EVORA--F430-V000E --check
python3 romraider-defs/reconcile_reviewed_metadata.py /tmp/gt430-export.xml --rom-id T6-EVORA--F430-V000E --output /tmp/gt430-reviewed.xml
```

Select exactly one ROM id per invocation: `T6-EVORA--F430-V000E`, `T6-V00BU`, or
`T6-V00BU - Learned data` (quote the learned-data id in the shell). If an export
contains both NA images, reconcile each id in sequence using a new output path
for each step. Other ROMs and non-allowlisted entries remain byte-for-byte intact.

The command restores only explicitly allowlisted root-table metadata, including
reviewed nested axes, from the versioned definition. It rejects missing or
duplicate roots, changed root payload addresses, dimensions, widths, type or
endianness. Same-width signedness corrections are allowed. Axis restoration may
change an axis address or replace a placeholder; those are reviewed metadata
corrections, not inferred layout repairs. Update the allowlist only alongside a
reviewed definition change and its correction ledger.

`--check` writes nothing: exit status 0 means reviewed metadata matches, 1 means
it differs, and 2 indicates invalid input or an unsafe operation. `--output`
requires a new path separate from the input and every canonical definition;
existing files and symlink aliases cannot be overwritten. The command prints the
canonical file's SHA-256 so a run can be tied to its metadata version. Review the
output before adopting it. It does not validate calibration/firmware bytes or
prove that a patched executable matches a definition. In particular, the GT430
4 Nm/count torque-cap definitions still require the matching firmware patch.
