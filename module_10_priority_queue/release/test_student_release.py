"""Validate the distributable, including an independent extracted build."""
import hashlib
import io
from pathlib import Path
import re
import shutil
import subprocess
import sys
import tempfile
import unittest
from zipfile import ZipFile

import prepare_student_release as release

MODULE = Path(__file__).resolve().parent.parent


class StudentReleaseTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.sources = release.release_map(MODULE)
        cls.payload, cls.count = release.package_bytes(cls.sources)

    def test_deterministic_inventory_and_manifest(self):
        self.assertEqual(self.payload, release.package_bytes(self.sources)[0])
        with ZipFile(io.BytesIO(self.payload)) as archive:
            names = archive.namelist()
            self.assertEqual(len(names), 31)
            self.assertEqual(len(names), self.count)
            self.assertEqual(set(names), set(self.sources) | {"MANIFEST.txt"})
            for name, source in self.sources.items():
                self.assertEqual(archive.read(name), source.read_bytes(), name)
            records = archive.read("MANIFEST.txt").decode().splitlines()[2:]
            self.assertEqual(len(records), len(self.sources))
            for record in records:
                digest, name = record.split("  ", 1)
                self.assertEqual(hashlib.sha256(archive.read(name)).hexdigest(), digest)
            self.assertTrue(all(not name.startswith(("legacy/", "instructor/", "module_03_"))
                                and not name.endswith((".zip", ".exe", ".o")) for name in names))
            self.assertIn("student/textbook_korean.md", names)
            self.assertTrue(all(info.date_time == (2000, 1, 1, 0, 0, 0)
                                for info in archive.infolist()))

    def test_repository_release_template_parity(self):
        for name, template in (("Makefile", "student_Makefile"),
                               ("build.ps1", "student_build.ps1"),
                               ("README.md", "student_code_README.md")):
            self.assertEqual((MODULE / "code" / name).read_bytes(),
                             (MODULE / "release" / template).read_bytes())

    def test_unsafe_and_reserved_names(self):
        source = MODULE / "student/textbook.md"
        for name in ("../escape", "/absolute", "C:/absolute", "a\\b", "a/../b",
                     "a//b", "./file", "", "MANIFEST.txt"):
            with self.subTest(name=name), self.assertRaises(ValueError):
                release.package_bytes({name: source})

    def test_exclusive_destination_and_identity(self):
        with tempfile.TemporaryDirectory(prefix="chapter10-release-") as folder:
            dest = Path(folder) / "student.zip"
            command = [sys.executable, str(MODULE / "release/prepare_student_release.py"),
                       "--output", str(dest)]
            subprocess.run(command, check=True, capture_output=True, text=True)
            self.assertEqual(dest.read_bytes(), self.payload)
            result = subprocess.run(command, capture_output=True, text=True)
            self.assertNotEqual(result.returncode, 0)
            self.assertEqual(dest.read_bytes(), self.payload)

    def test_extracted_links_and_standalone_build(self):
        self.assertIsNotNone(shutil.which("make"), "make is required for release verification")
        self.assertIsNotNone(shutil.which("cc"), "a C compiler is required for release verification")
        with tempfile.TemporaryDirectory(prefix="chapter10-extracted-") as folder:
            root = Path(folder)
            with ZipFile(io.BytesIO(self.payload)) as archive:
                archive.extractall(root)
            for path in root.rglob("*.md"):
                for target in re.findall(r"\[[^\]\n]+\]\(([^)\s]+)\)", path.read_text()):
                    if target.startswith(("https:", "http:", "mailto:", "#")):
                        continue
                    target_path = target.split("#", 1)[0]
                    self.assertTrue((path.parent / target_path).exists(), f"{path}: {target}")
            command = ["make", "-C", str(root / "code"),
                       "CFLAGS=-std=c11 -Wall -Wextra -Wpedantic -Wconversion -Wshadow -Werror -g",
                       "lab-compile", "core", "student-tests", "comparison"]
            result = subprocess.run(command, capture_output=True, text=True)
            self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
            self.assertIn("10000 independent reference schedules passed", result.stdout)
            self.assertIn("student smoke passed", result.stdout)
            self.assertIn("1000 generated comparisons passed", result.stdout)
            # The exact excerpts in both language editions are usable together.
            for language in ("textbook.md", "textbook_korean.md"):
                blocks = re.findall(r"^```c\n(.*?)^```", (root / "student" / language).read_text(),
                                    re.MULTILINE | re.DOTALL)
                self.assertEqual(len(blocks), 3)
                source = root / "excerpt_driver.c"
                source.write_text("\n".join(blocks) +
                                  '\n#include <assert.h>\nint main(void) { assert(survey() == 12); return 0; }\n')
                executable = root / "excerpt_driver"
                result = subprocess.run(["cc", "-std=c11", "-Wall", "-Wextra", "-Wpedantic",
                                         "-Wconversion", "-Wshadow", "-Werror", str(source),
                                         "-o", str(executable)], capture_output=True, text=True)
                self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
                subprocess.run([str(executable)], check=True, capture_output=True)


if __name__ == "__main__":
    unittest.main()
