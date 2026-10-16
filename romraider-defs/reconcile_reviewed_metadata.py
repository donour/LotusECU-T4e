#!/usr/bin/env python3
"""Restore explicitly reviewed RomRaider metadata after a fresh Ghidra export.

The checked-in definitions are canonical. Only allowlisted root tables in an
exact ROM id are copied; all other exported bytes are preserved. This does not
validate firmware bytes, rebuild missing maps, or reconcile changed layouts.
"""

import argparse
from dataclasses import dataclass
import hashlib
from pathlib import Path
import sys
import xml.etree.ElementTree as ET
from xml.parsers import expat


DIRECTORY = Path(__file__).resolve().parent
# Addresses are file offsets, scoped to the exact XML ROM id. See
# disassembly/evora/analysis/DEFINITION_MAP_COMPARISON.md and the per-variant
# correction ledgers. The table bodies deliberately remain in canonical XML.
PROFILES = {
    "T6-EVORA--F430-V000E": (
        DIRECTORY / "T6-EVORA--F430-V000E_defs.xml",
        frozenset((0x0026, 0x004E, 0x005A, 0x0060, 0x0061, 0x010E, 0x014E,
                   0x0222, 0x0262, 0x0032, 0x02EE, 0x0302, 0x0352,
                   0x06C2, 0x074C, 0x07FC, 0x0CB6, 0x1846, 0x18EE,
                   0x195E, 0x19AE, 0x2776, 0x3626, 0x416E, 0x425E,
                   0x43A6, 0x4438, 0x45B0, 0x45BC, 0x45C8,
                   0x45D4, 0x45D5, 0x45DA, 0x45E4, 0x45F0, 0x4670,
                   0x4FC8, 0x4FE0, 0x5C6C))),
    "T6-V00BU": (
        DIRECTORY / "T6-V00BU_defs.xml",
        frozenset((0x005A, 0x0083, 0x0084, 0x0085, 0x01E8, 0x01EA,
                   0x0206, 0x0262, 0x452E, 0x4532, 0x4536, 0x45B0,
                   0x45BC, 0x45C8, 0x45D4, 0x45D5, 0x45DA, 0x45E4,
                   0x45E6, 0x45EF, 0x45F0))),
    "T6-V00BU - Learned data": (
        DIRECTORY / "T6-V00BU_defs.xml", frozenset((0x0576, 0x0986))),
}
WIDTHS = {"uint8": 1, "int8": 1, "uint16": 2, "int16": 2,
          "uint32": 4, "int32": 4}


class ReconciliationError(ValueError):
    """The export does not satisfy the bounded reconciliation contract."""


@dataclass(frozen=True)
class RootTable:
    element: ET.Element
    start: int
    end: int


@dataclass(frozen=True)
class Result:
    data: bytes
    changed: tuple
    canonical_sha256: str


def _tag_end(data, start):
    """Find the end of a UTF-8 XML tag, allowing '>' inside quoted attributes."""
    quote = None
    for position in range(start, len(data)):
        char = data[position]
        if quote is not None:
            if char == quote:
                quote = None
        elif char in (ord("'"), ord('"')):
            quote = char
        elif char == ord(">"):
            return position + 1
    raise ReconciliationError("Unterminated XML tag")


def _document(data):
    """Parse XML and retain exact byte spans of each ROM's root tables."""
    try:
        data.decode("utf-8")
        parser = expat.ParserCreate()
        stack, rom_spans, open_tables = [], [], []

        def start(name, attributes):
            if name == "rom" and stack == ["roms"]:
                rom_spans.append([])
            if name == "table" and stack == ["roms", "rom"]:
                first = parser.CurrentByteIndex
                opening_end = _tag_end(data, first)
                self_closing = data[first:opening_end].rstrip().endswith(b"/>")
                open_tables.append((first, opening_end if self_closing else None))
            stack.append(name)

        def end(name):
            if name == "table" and stack == ["roms", "rom", "table"]:
                first, self_closing_end = open_tables.pop()
                last = self_closing_end or _tag_end(data, parser.CurrentByteIndex)
                rom_spans[-1].append((first, last))
            stack.pop()

        def reject_doctype(*args):
            raise ReconciliationError("DOCTYPE declarations are unsupported")

        parser.StartElementHandler, parser.EndElementHandler = start, end
        parser.StartDoctypeDeclHandler = reject_doctype
        parser.Parse(data, True)
        root = ET.fromstring(data)
    except (UnicodeError, expat.ExpatError, ET.ParseError) as error:
        raise ReconciliationError(f"Invalid UTF-8 definition XML: {error}") from error
    if root.tag != "roms":
        raise ReconciliationError("Expected an unnamespaced <roms> document")
    roms = root.findall("rom")
    if len(roms) != len(rom_spans):
        raise ReconciliationError("Unsupported ROM structure")
    return list(zip(roms, rom_spans))


def _selected_tables(data, rom_id):
    matches = [(rom, spans) for rom, spans in _document(data)
               if rom.findtext("romid/xmlid") == rom_id]
    if len(matches) != 1:
        raise ReconciliationError(f"Expected exactly one ROM with xmlid {rom_id!r}")
    rom, spans = matches[0]
    if len(rom.findall("romid")) != 1 or len(rom.findall("romid/xmlid")) != 1:
        raise ReconciliationError("The selected ROM must have exactly one xmlid")
    tables = rom.findall("table")
    if len(tables) != len(spans):
        raise ReconciliationError("Unsupported root-table structure")
    indexed = {}
    for table, (start, end) in zip(tables, spans):
        try:
            address = int(table.attrib["storageaddress"], 16)
        except (KeyError, ValueError) as error:
            raise ReconciliationError("Root table has no valid storage address") from error
        if address < 0 or address in indexed:
            raise ReconciliationError(f"Duplicate or invalid root address 0x{address:X}")
        indexed[address] = RootTable(table, start, end)
    return indexed


def _geometry(table):
    try:
        shape = (int(table.get("sizex", "1")), int(table.get("sizey", "1")))
        width = WIDTHS[table.attrib["storagetype"]]
        address = int(table.attrib["storageaddress"], 16)
    except (KeyError, ValueError) as error:
        raise ReconciliationError("Unsupported payload width or dimensions") from error
    if min(shape) < 1:
        raise ReconciliationError("Payload dimensions must be positive")
    # Signedness is metadata; byte width, endianness, type and shape are layout.
    return address, shape, width, table.get("endian"), table.get("type")


def _metadata(table):
    return (table.tag, tuple(sorted(table.attrib.items())),
            (table.text or "").strip(), tuple(_metadata(child) for child in table))


def reconcile(data, rom_id):
    """Return repaired bytes or raise before changing anything on disk."""
    if rom_id not in PROFILES:
        raise ReconciliationError(f"Unknown reviewed ROM id: {rom_id!r}")
    canonical_path, allowed = PROFILES[rom_id]
    canonical = canonical_path.read_bytes()
    source = _selected_tables(canonical, rom_id)
    target = _selected_tables(data, rom_id)
    replacements = []
    for address in sorted(allowed):
        if address not in source or address not in target:
            raise ReconciliationError(f"Missing reviewed root table 0x{address:X}")
        expected, exported = source[address], target[address]
        if _geometry(expected.element) != _geometry(exported.element):
            raise ReconciliationError(f"Payload layout changed at 0x{address:X}")
        if _metadata(expected.element) != _metadata(exported.element):
            replacements.append((exported.start, exported.end, address,
                                 canonical[expected.start:expected.end]))
    output = data
    for start, end, address, replacement in sorted(replacements, reverse=True):
        output = output[:start] + replacement + output[end:]
    return Result(output, tuple(item[2] for item in replacements),
                  hashlib.sha256(canonical).hexdigest())


def _validate_output(exported, output):
    destination = output.resolve()
    canonical_paths = {path.resolve() for path, allowed in PROFILES.values()}
    if destination in canonical_paths:
        raise ReconciliationError("Output must not overwrite a canonical definition")
    if destination == exported.resolve():
        raise ReconciliationError("Output must be separate from the input export")
    # Exclusive creation below also prevents symlink/hardlink replacement races.
    if output.exists() or output.is_symlink():
        raise ReconciliationError("Output already exists; choose a new output path")


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("exported", type=Path, help="fresh exported XML (read only)")
    parser.add_argument("--rom-id", required=True, choices=tuple(PROFILES))
    mode = parser.add_mutually_exclusive_group(required=True)
    mode.add_argument("--check", action="store_true", help="report drift without writing")
    mode.add_argument("--output", type=Path, help="write to a new, separate XML file")
    args = parser.parse_args(argv)
    try:
        if args.output is not None:
            _validate_output(args.exported, args.output)
        result = reconcile(args.exported.read_bytes(), args.rom_id)
        if args.output is not None:
            with args.output.open("xb") as destination:
                destination.write(result.data)
    except (OSError, ReconciliationError) as error:
        print(f"Reconciliation failed: {error}", file=sys.stderr)
        return 2
    print(f"{args.rom_id}: {len(result.changed)} reviewed root table(s) differ")
    if result.changed:
        print("Offsets: " + ", ".join(f"0x{offset:04X}" for offset in result.changed))
    print(f"Canonical SHA-256: {result.canonical_sha256}")
    if args.output is not None:
        print(f"Wrote {args.output}")
    return int(args.check and bool(result.changed))


if __name__ == "__main__":
    raise SystemExit(main())
