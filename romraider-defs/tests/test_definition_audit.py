"""Check audit domain handling, CSV diagnostics and XML source navigation."""

import importlib.util
from pathlib import Path
import tempfile
import unittest


SPEC = importlib.util.spec_from_file_location(
    "definition_audit", Path(__file__).resolve().parents[1] / "audit_definition_maps.py")
audit = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(audit)


class DefinitionAuditTests(unittest.TestCase):
    def test_roundtrip_domain_and_wrong_inverse_are_distinguished(self):
        result = audit.check_scaling("(x-128)/4", "x*4+128", "uint8")
        self.assertEqual(result["status"], "roundtrip_ok")
        self.assertEqual((result["display_min"], result["display_max"]), (-32, 31.75))
        self.assertEqual(result["sample_count"], 256)
        self.assertTrue(result["exhaustive"])
        self.assertEqual(audit.check_scaling("x/4", "x*5", "uint8")["status"],
                         "roundtrip_mismatch")

    def test_zero_in_reciprocal_does_not_discard_valid_samples(self):
        result = audit.check_scaling("15000000/x", "15000000/x", "uint16")
        self.assertEqual(result["status"], "partial_scaling_domain")
        self.assertFalse(result["exhaustive"])
        self.assertEqual([sample["raw"] for sample in result["excluded_samples"]], [0])
        self.assertLess(result["max_raw_roundtrip_error"], 1e-6)

    def test_non_arithmetic_expressions_are_never_executed(self):
        result = audit.check_scaling("__import__('os').getcwd()", "x", "uint8")
        self.assertEqual(result["status"], "not_evaluated")
        self.assertTrue(all(sample["reason"] == "Unsupported arithmetic expression"
                            for sample in result["excluded_samples"]))

    def read_csv(self, content):
        with tempfile.TemporaryDirectory() as directory:
            path = Path(directory) / "symbols.csv"
            path.write_text(content)
            return audit.read_symbols(path)

    def test_csv_reports_short_extra_and_invalid_identity_records(self):
        header = ','.join(audit.SYMBOL_FIELDS) + '\n'
        content = (header + 'CAL_a,40000000,Data Label,uint8_t\n'
                   + 'CAL_b,40000001,Data Label,uint8_t,comment,extra\n'
                   + 'CAL_c,123,Data Label,uint8_t,comment\n'
                   + 'function_a,00040000,Function,,\n')
        rows, issues = self.read_csv(content)
        self.assertEqual([row["Name"] for row in rows], ["CAL_a", "CAL_b", "function_a"])
        self.assertEqual([issue["issue"] for issue in issues],
                         ["short_record", "extra_comment_columns", "invalid_identity_fields"])
        self.assertEqual([issue["end_line"] for issue in issues], [2, 3, 4])

    def test_csv_rejects_wrong_header_and_broken_quoting(self):
        for content in ('Name,Address\n',
                        ','.join(audit.SYMBOL_FIELDS) + '\nCAL_a,40000000,Data,uint8_t,"unterminated'):
            with self.subTest(content=content), self.assertRaises(ValueError):
                self.read_csv(content)

    def test_root_source_lines_ignore_indentation_and_nested_axes(self):
        data = (b'<roms>\r\n<rom><romid/>\r\n<table>\r\n'
                b'<table/>\r\n</table><table/>\r\n</rom>\r\n'
                b'<rom><table/></rom></roms>')
        self.assertEqual(audit.root_table_lines(data), [3, 5, 7])


if __name__ == "__main__":
    unittest.main()
