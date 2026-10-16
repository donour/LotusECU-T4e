#!/usr/bin/env python3
"""Inventory every NA091/GT430 calibration and learned-data definition.

This reads XML and exported symbols only. Address matches and review flags do
not establish firmware behavior or validate an original image. Nothing is
changed unless --output-dir is supplied, which writes review artifacts there.
"""

import argparse
import ast
import collections
import csv
from functools import lru_cache
import hashlib
import json
import math
import operator
from pathlib import Path
import re
import xml.etree.ElementTree as ET
from xml.parsers import expat


ROOT = Path(__file__).resolve().parents[1]
PROFILES = {
    "NA091": ("T6-V00BU_defs.xml", "B13200091/B13200091-symbols.csv"),
    "GT430": ("T6-EVORA--F430-V000E_defs.xml", "C132E0278/C132E0278_symbols.csv"),
}
STORAGE = {"uint8": (1, 0, 255), "int8": (1, -128, 127),
           "uint16": (2, 0, 65535), "int16": (2, -32768, 32767),
           "uint32": (4, 0, 4294967295), "int32": (4, -2147483648, 2147483647)}
OPS = {ast.Add: operator.add, ast.Sub: operator.sub,
       ast.Mult: operator.mul, ast.Div: operator.truediv}
SYMBOL_FIELDS = ["Name", "Location", "Type", "Data Type", "EOL Comment"]


def read_symbols(path):
    """Keep readable identities, reporting incomplete CSV records explicitly."""
    rows, issues = [], []
    with path.open(newline="", encoding="utf-8") as source:
        reader = csv.DictReader(source, strict=True)
        try:
            if reader.fieldnames != SYMBOL_FIELDS:
                raise ValueError(f"Unexpected symbol CSV header in {path}")
            for row in reader:
                if (not re.fullmatch(r"[0-9a-fA-F]{8}", row.get("Location") or "")
                        or not row.get("Name")
                        or not isinstance(row.get("Data Type"), str)):
                    issues.append({"end_line": reader.line_num,
                                   "issue": "invalid_identity_fields"})
                    continue
                if any(row.get(field) is None for field in SYMBOL_FIELDS):
                    issues.append({"end_line": reader.line_num, "issue": "short_record",
                                   "symbol": row["Name"]})
                if None in row:
                    issues.append({"end_line": reader.line_num,
                                   "issue": "extra_comment_columns", "symbol": row["Name"]})
                rows.append(row)
        except csv.Error as error:
            raise ValueError(f"Malformed CSV in {path} near line {reader.line_num}: {error}") from error
    return rows, issues


def root_table_lines(data):
    """Find XML source lines without depending on indentation or line endings."""
    parser = expat.ParserCreate()
    stack, lines = [], []

    def start(name, attributes):
        if name == "table" and stack == ["roms", "rom"]:
            lines.append(parser.CurrentLineNumber)
        stack.append(name)

    parser.StartElementHandler = start
    parser.EndElementHandler = lambda name: stack.pop()
    parser.Parse(data, True)
    return lines


@lru_cache(maxsize=None)
def expression_tree(expression):
    return ast.parse(expression, mode="eval").body


def evaluate(node, value):
    if isinstance(node, ast.Name) and node.id == "x":
        return value
    if isinstance(node, ast.Constant) and type(node.value) in (int, float):
        return node.value
    if isinstance(node, ast.BinOp) and type(node.op) in OPS:
        return OPS[type(node.op)](evaluate(node.left, value), evaluate(node.right, value))
    if isinstance(node, ast.UnaryOp) and isinstance(node.op, (ast.USub, ast.UAdd)):
        return (-1 if isinstance(node.op, ast.USub) else 1) * evaluate(node.operand, value)
    raise ValueError("Unsupported arithmetic expression")


@lru_cache(maxsize=None)
def check_scaling(expression, inverse, storage):
    if storage not in STORAGE:
        return {"status": "storage_unknown"}
    width, low, high = STORAGE[storage]
    samples = list(range(low, high + 1)) if width == 1 else sorted(
        {low, high, 0, 1, *[n for n in (127, 128, 255, 256, 32767, 32768, 65535)
                          if low <= n <= high]})
    try:
        forward, backward = expression_tree(expression), expression_tree(inverse)
    except (TypeError, SyntaxError) as error:
        return {"status": "not_evaluated", "reason": str(error)}
    displayed, errors, excluded = [], [], []
    for raw in samples:
        try:
            shown = evaluate(forward, raw)
            error = abs(evaluate(backward, shown) - raw)
            if not math.isfinite(shown) or not math.isfinite(error):
                raise ValueError("Non-finite scaling result")
        except (TypeError, ValueError, ZeroDivisionError, OverflowError) as error:
            excluded.append({"raw": raw, "reason": str(error)})
            continue
        displayed.append(shown)
        errors.append(error)
    if not displayed:
        return {"status": "not_evaluated", "excluded_samples": excluded}
    status = ("roundtrip_mismatch" if max(errors) >= 1e-6 else
              "partial_scaling_domain" if excluded else "roundtrip_ok")
    return {"status": status, "sample_count": len(samples), "exhaustive": width == 1,
            "excluded_samples": excluded,
            "display_min": min(displayed), "display_max": max(displayed),
            "max_raw_roundtrip_error": max(errors)}


def symbol_size(datatype):
    match = re.fullmatch(r"(.+)\[(\d+)\]", datatype)
    scalar, count = (match[1], int(match[2])) if match else (datatype, 1)
    match = re.match(r"^[ui](8|16|32)(?:_|$)", scalar)
    widths = {"bool": 1, "byte": 1, "char": 1, "undefined": 1,
              "undefined1": 1, "undefined2": 2, "undefined4": 4,
              "uint8_t": 1, "int8_t": 1, "uint16_t": 2, "int16_t": 2,
              "uint32_t": 4, "int32_t": 4, "ushort": 2, "short": 2,
              "uint": 4, "int": 4}
    width = int(match[1]) // 8 if match else widths.get(scalar)
    return None if width is None else count * width


def xml_size(element):
    if element.get("type") == "Switch":
        # Enum states sometimes use unpadded values; use the declared byte count.
        return int(element.get("sizey", "1"))
    storage = STORAGE.get(element.get("storagetype"))
    if storage is None:
        return None
    count = int(element.get("sizex", "1")) * int(element.get("sizey", "1"))
    return count * storage[0]


def declared_file_size(value):
    match = re.fullmatch(r"(\d+)(kb|b)", value or "", re.I)
    return int(match[1]) * (1024 if match[2].lower() == "kb" else 1) if match else None


def inspect_element(element, base, prefix, symbols, advertised_size):
    result = dict(element.attrib)
    result["flags"] = []
    flags = result["flags"]
    offset = element.get("storageaddress")
    result["byte_length"] = xml_size(element) if offset else None
    result["scalings"] = []
    for scaling in element.findall("scaling"):
        item = dict(scaling.attrib)
        item["check"] = (check_scaling(scaling.get("expression"), scaling.get("to_byte"),
                                       element.get("storagetype")) if offset else
                         {"status": "not_applicable_static_axis"})
        result["scalings"].append(item)
        if item["check"]["status"] not in ("roundtrip_ok", "not_applicable_static_axis"):
            flags.append(item["check"]["status"])
    if len(result["scalings"]) > 1:
        unique = {json.dumps(dict(s.attrib), sort_keys=True)
                  for s in element.findall("scaling")}
        flags.append("duplicate_identical_scaling" if len(unique) == 1 else "alternate_scalings")
    if offset:
        offset = int(offset, 16)
        address = base + offset
        result["ram_address"] = f"0x{address:08X}"
        matches = symbols.get(address, [])
        result["symbols_at_address"] = [{"name": row["Name"], "type": row["Data Type"]}
                                        for row in matches]
        named = [row for row in matches if row["Name"].startswith(prefix)]
        result["symbol_match"] = ("unique_named" if len(named) == 1 else "multiple_named"
                                  if named else "address_only" if matches else "unmatched")
        if result["symbol_match"] != "unique_named":
            flags.append("symbol_" + result["symbol_match"])
        known_sizes = [symbol_size(row["Data Type"]) for row in named]
        if result["byte_length"] is not None and any(
                size is not None and size != result["byte_length"] for size in known_sizes):
            flags.append("csv_byte_length_disagreement")
        if advertised_size is not None and result["byte_length"] is not None:
            if offset < 0 or offset + result["byte_length"] > advertised_size:
                flags.append("outside_advertised_file_size")
    else:
        result["labels"] = [cell.text for cell in element.findall("data")]
        size = int(element.get("sizex", element.get("sizey", "1")))
        if len(result["labels"]) != size:
            flags.append("static_axis_label_count")
        if any(s.get("units", "").lower() in ("v", "volt") for s in element.findall("scaling")):
            flags.append("static_voltage_axis_review")
    return result


def audit(profile):
    xml_name, csv_name = PROFILES[profile]
    xml_path = ROOT / "romraider-defs" / xml_name
    csv_path = ROOT / "disassembly/evora" / csv_name
    rows, csv_issues = read_symbols(csv_path)
    symbols = collections.defaultdict(list)
    for row in rows:
        symbols[int(row["Location"], 16)].append(row)
    raw = xml_path.read_bytes()
    lines = iter(root_table_lines(raw))
    result = {"profile": profile, "inputs": {}, "symbol_csv_issues": csv_issues, "roms": []}
    for path in (xml_path, csv_path):
        result["inputs"][str(path.relative_to(ROOT))] = hashlib.sha256(path.read_bytes()).hexdigest()
    for rom, prefix in zip(ET.fromstring(raw).findall("rom"), ("CAL_", "LEA_"), strict=True):
        base_row, = [row for row in rows if row["Name"] == prefix + "base"]
        base = int(base_row["Location"], 16)
        advertised_size = declared_file_size(rom.findtext("romid/filesize"))
        tables = []
        for element in rom.findall("table"):
            table = inspect_element(element, base, prefix, symbols, advertised_size)
            table["xml_line"] = next(lines)
            table["axes"] = [inspect_element(axis, base, prefix, symbols, advertised_size)
                             for axis in element.findall("table")]
            tables.append(table)
        names = collections.Counter(table["name"] for table in tables)
        addresses = collections.Counter(table["storageaddress"] for table in tables)
        for table in tables:
            if names[table["name"]] > 1:
                table["flags"].append("duplicate_table_name")
            if addresses[table["storageaddress"]] > 1:
                table["flags"].append("shared_table_start")
        objects = tables + [axis for table in tables for axis in table["axes"]]
        result["roms"].append({
            "xmlid": rom.findtext("romid/xmlid"), "kind": prefix.rstrip("_"),
            "ram_base": f"0x{base:08X}", "advertised_file_bytes": advertised_size,
            "table_count": len(tables), "axis_count": len(objects) - len(tables),
            "categories": dict(sorted(collections.Counter(t["category"] for t in tables).items())),
            "symbol_matches": dict(collections.Counter(t["symbol_match"] for t in tables)),
            "review_flags": dict(sorted(collections.Counter(
                flag for obj in objects for flag in obj["flags"]).items())),
            "tables": tables})
    return result


def write_outputs(directory, results):
    directory.mkdir(parents=True, exist_ok=True)
    (directory / "definition-map-inventory.json").write_text(
        json.dumps({"scope": "Exported XML/CSV only; review flags are not confirmed defects.",
                    "profiles": results}, indent=2, ensure_ascii=False) + "\n")
    fields = ["profile", "kind", "xmlid", "category", "name", "xml_line", "storageaddress",
              "ram_address", "type", "storagetype", "sizex", "sizey", "byte_length",
              "symbol_match", "symbols", "units", "expressions", "flags", "axis_flags"]
    with (directory / "definition-map-inventory.csv").open("w", newline="") as out:
        writer = csv.DictWriter(out, fieldnames=fields)
        writer.writeheader()
        for profile in results:
            for rom in profile["roms"]:
                for table in rom["tables"]:
                    row = {field: table.get(field, "") for field in fields}
                    row.update(profile=profile["profile"], kind=rom["kind"], xmlid=rom["xmlid"],
                               symbols=" | ".join(s["name"] for s in table["symbols_at_address"]),
                               units=" | ".join(s.get("units", "") for s in table["scalings"]),
                               expressions=" | ".join(s.get("expression", "") for s in table["scalings"]),
                               flags=" | ".join(table["flags"]),
                               axis_flags=" | ".join(sorted({f for a in table["axes"] for f in a["flags"]})))
                    writer.writerow(row)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--output-dir", type=Path)
    args = parser.parse_args()
    results = [audit(profile) for profile in PROFILES]
    summary = [{"profile": result["profile"], "inputs": result["inputs"],
                "symbol_csv_issues": result["symbol_csv_issues"],
                "roms": [{k: v for k, v in rom.items() if k != "tables"}
                         for rom in result["roms"]]} for result in results]
    print(json.dumps(summary, indent=2))
    if args.output_dir:
        write_outputs(args.output_dir, results)


if __name__ == "__main__":
    main()
