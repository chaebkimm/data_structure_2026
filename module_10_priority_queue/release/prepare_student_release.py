"""Package Chapter 10's self-contained priority-queue meeting-time lesson."""
import argparse
import hashlib
import io
from pathlib import Path, PurePosixPath
from zipfile import ZIP_DEFLATED, ZipFile, ZipInfo

STUDENT_FILES = (
    "lab.c", "ppt_material.md", "ppt_lab_material.md",
    "textbook.md", "textbook_korean.md", "vocabulary.md", "lab.md",
    "inquiry_prompt.md", "inquiry_prompt_linear.md", "representation_reveal.md",
    "cognitive_pause.md", "investigation_worksheet.md",
    "investigation_worksheet_linear.md", "evidence_template.md", "rubric.md",
    "priority_queue_autopsy.md",
)
CODE_FILES = (
    "test_lab.c", "test_lab_student.c", "compare_lab.c", "survey_fixtures.h",
)


def release_map(module):
    sources = {f"student/{name}": module / "student" / name for name in STUDENT_FILES}
    sources.update({f"code/tests/{name}": module / "code/tests" / name for name in CODE_FILES})
    sources.update({
        f"release/stage_{stage}_README.md": module / "release" / f"stage_{stage}_README.md"
        for stage in "abcde"
    })
    sources.update({
        "README.md": module / "release/student_README.md",
        "code/README.md": module / "release/student_code_README.md",
        "code/Makefile": module / "release/student_Makefile",
        "code/build.ps1": module / "release/student_build.ps1",
        "diagrams/priority_queue_models.md": module / "diagrams/priority_queue_models.md",
    })
    return sources


def package_bytes(sources):
    # Validate all entry names and read all inputs before creating a destination.
    files = {}
    for name, source in sources.items():
        if (not name or name.startswith("/") or "\\" in name or ":" in name
                or any(part in {"", ".", ".."} for part in name.split("/"))
                or PurePosixPath(name).is_absolute() or name == "MANIFEST.txt"):
            raise ValueError(f"Unsafe or reserved archive entry: {name}")
        files[name] = source.read_bytes()
    files["MANIFEST.txt"] = (
        "Chapter 10 priority queue and meeting-time student release.\n"
        "SHA256  archive path (MANIFEST.txt is excluded from hashing)\n"
        + "".join(f"{hashlib.sha256(data).hexdigest()}  {name}\n"
                  for name, data in sorted(files.items()))
    ).encode("utf-8")
    buffer = io.BytesIO()
    with ZipFile(buffer, "w", ZIP_DEFLATED) as archive:
        for name, data in sorted(files.items()):
            info = ZipInfo(name, (2000, 1, 1, 0, 0, 0))
            info.compress_type = ZIP_DEFLATED
            info.create_system = 3
            info.external_attr = 0o100644 << 16
            archive.writestr(info, data)
    payload = buffer.getvalue()
    with ZipFile(io.BytesIO(payload)) as archive:
        if set(archive.namelist()) != set(files):
            raise ValueError("Archive inventory mismatch")
        for name, data in files.items():
            if archive.read(name) != data:
                raise ValueError(f"Archive content mismatch: {name}")
    return payload, len(files)


def main():
    module = Path(__file__).resolve().parent.parent
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--output", type=Path,
                        default=module / "dist/module_10_priority_queue.zip")
    args = parser.parse_args()
    payload, count = package_bytes(release_map(module))
    args.output.parent.mkdir(parents=True, exist_ok=True)
    # Exclusive creation preserves any existing destination, including races.
    with args.output.open("xb") as output:
        try:
            output.write(payload)
        except BaseException:
            args.output.unlink(missing_ok=True)
            raise
    print(f"{args.output.resolve()}: {count} entries; "
          f"SHA256 {hashlib.sha256(payload).hexdigest()}")


if __name__ == "__main__":
    main()
