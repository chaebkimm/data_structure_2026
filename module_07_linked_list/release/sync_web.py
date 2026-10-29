"""Synchronize Chapter 7 web reading and downloads from the canonical module.

Run from any directory. The default destination is the repository's sibling
student-textbook-web checkout. Only generated chapter files are written.
"""
import argparse
import posixpath
import re
import subprocess
import sys
import tempfile
from pathlib import Path, PurePosixPath
from urllib.parse import unquote, urlsplit, urlunsplit
from zipfile import ZipFile


MARKDOWN_LINK = re.compile(r"(!?\[[^\]\n]*\]\()([^\s)]+)(\))")


def web_reading(source, members):
    """Rewrite relative prose links, preserving code and external destinations."""
    fence = None
    result = []

    def replace_link(match):
        target = match.group(2)
        parts = urlsplit(target)
        if parts.scheme or parts.netloc or target.startswith(("/", "#")):
            return match.group(0)
        # The canonical textbooks live in student/. Never publish a link to a
        # sibling faculty or source file that is absent from the student archive.
        member = posixpath.normpath(posixpath.join("student", unquote(parts.path)))
        if not member.startswith("student/") or member not in members:
            raise ValueError(f"Textbook link has no packaged student target: {target}")
        destination = urlunsplit(("", "", "/chapter-7/" + member,
                                  parts.query, parts.fragment))
        return match.group(1) + destination + match.group(3)

    for line in source.splitlines(keepends=True):
        marker = re.match(r"^\s*(`{3,}|~{3,})", line)
        if marker:
            token = marker.group(1)
            if fence is None:
                fence = token
            elif token[0] == fence[0] and len(token) >= len(fence):
                fence = None
            result.append(line)
        elif fence is None:
            result.append(MARKDOWN_LINK.sub(replace_link, line))
        else:
            result.append(line)
    return "".join(result)


def main():
    module = Path(__file__).resolve().parent.parent
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--web-root", type=Path,
                        default=module.parent / "student-textbook-web",
                        help="Absolute web checkout path (default: repository sibling)")
    args = parser.parse_args()
    if not args.web_root.is_absolute():
        parser.error("--web-root must be an absolute path")
    web_root = args.web_root.resolve()
    if not (web_root / "package.json").is_file():
        parser.error(f"Not a web checkout (missing package.json): {web_root}")

    with tempfile.TemporaryDirectory(prefix="module-07-web-") as temporary:
        archive_path = Path(temporary) / "sources.zip"
        subprocess.run([sys.executable,
                        str(module / "release/prepare_student_release.py"),
                        "--output", str(archive_path)],
                       check=True, capture_output=True, text=True)
        archive_bytes = archive_path.read_bytes()
        with ZipFile(archive_path) as archive:
            members = {}
            for info in archive.infolist():
                member = PurePosixPath(info.filename)
                if (info.is_dir() or member.is_absolute()
                        or ".." in member.parts or "\\" in info.filename
                        or info.filename in members):
                    raise ValueError(f"Invalid student archive member: {info.filename}")
                members[info.filename] = archive.read(info)
            manifest = members["MANIFEST.txt"].decode("utf-8").splitlines()[1:]
            if set(manifest) != set(members) or len(manifest) != len(members):
                raise ValueError("Student archive manifest does not match its members")

        # Derive all output before writing, so broken links fail without a
        # partially synchronized chapter. Source downloads remain exact bytes.
        readings = {
            "en": web_reading(members["student/textbook.md"].decode("utf-8"), members),
            "ko": web_reading(members["student/textbook_korean.md"].decode("utf-8"), members),
        }
        destination = web_root / "public/chapter-7"
        destination.mkdir(parents=True, exist_ok=True)
        for name, data in sorted(members.items()):
            path = destination.joinpath(*PurePosixPath(name).parts)
            path.parent.mkdir(parents=True, exist_ok=True)
            path.write_bytes(data)
        (destination / "sources.zip").write_bytes(archive_bytes)
        (web_root / "content").mkdir(parents=True, exist_ok=True)
        for language, reading in readings.items():
            (web_root / f"content/chapter-seven.{language}.md").write_bytes(
                reading.encode("utf-8"))
    print(f"Synchronized Chapter 7: {len(members)} source files, sources.zip, "
          f"and 2 textbook readings in {web_root}")


if __name__ == "__main__":
    main()
