"""Regression checks for canonical Chapter 7 web downloads and link rewriting."""
import json
import subprocess
import sys
import tempfile
import unittest
from pathlib import Path
from zipfile import ZipFile

from sync_web import web_reading


class WebSyncTests(unittest.TestCase):
    def test_only_relative_prose_links_change(self):
        source = (
            "[Lab](./lab.md#work) [Book](./part/../textbook.md) "
            "[Web](https://example.org/x) [Here](#anchor)\n"
            "```c\n[Keep](lab.md)\n```\n"
            "~~~text\n[Also keep](lab.md)\n~~~\n"
        )
        expected = (
            "[Lab](/chapter-7/student/lab.md#work) "
            "[Book](/chapter-7/student/textbook.md) "
            "[Web](https://example.org/x) [Here](#anchor)\n"
            "```c\n[Keep](lab.md)\n```\n"
            "~~~text\n[Also keep](lab.md)\n~~~\n"
        )
        self.assertEqual(web_reading(source, {
            "student/lab.md": b"", "student/textbook.md": b"",
        }), expected)

    def test_missing_or_nonstudent_targets_fail(self):
        for target in ("missing.md", "../instructor/answer_key.md"):
            with self.subTest(target=target), self.assertRaises(ValueError):
                web_reading(f"[Link]({target})", {})

    def test_full_sync_keeps_exact_sources_and_reproducible_archive(self):
        module = Path(__file__).resolve().parent.parent
        synchronizer = module / "release/sync_web.py"
        with tempfile.TemporaryDirectory(prefix="module-07-web-test-") as temporary:
            web_root = Path(temporary)
            (web_root / "package.json").write_text(json.dumps({"private": True}))
            command = [sys.executable, str(synchronizer),
                       "--web-root", str(web_root)]
            subprocess.run(command, check=True, capture_output=True, text=True)
            public = web_root / "public/chapter-7"
            archive_path = public / "sources.zip"
            first_archive = archive_path.read_bytes()
            with ZipFile(archive_path) as archive:
                names = archive.namelist()
                manifest = archive.read("MANIFEST.txt").decode().splitlines()[1:]
                self.assertEqual(set(names), set(manifest))
                for name in names:
                    self.assertEqual((public / name).read_bytes(), archive.read(name))
                for source in (module / "student").iterdir():
                    if source.suffix in (".md", ".c"):
                        self.assertEqual(archive.read("student/" + source.name),
                                         source.read_bytes())
            for language in ("en", "ko"):
                reading = (web_root / f"content/chapter-seven.{language}.md").read_text()
                self.assertIn("](/chapter-7/student/", reading)
                self.assertNotIn("](textbook", reading)
            subprocess.run(command, check=True, capture_output=True, text=True)
            self.assertEqual(archive_path.read_bytes(), first_archive)


if __name__ == "__main__":
    unittest.main()
