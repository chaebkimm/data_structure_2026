"""Package Module 13 searching, sorting, and consolidation without faculty answers."""
import argparse
from pathlib import Path
from zipfile import ZIP_DEFLATED, ZipFile


def main():
    module = Path(__file__).resolve().parent.parent
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--output", type=Path,
                        default=module / "dist/module_13_search_sort_consolidation.zip")
    args = parser.parse_args()
    sources = {path.relative_to(module).as_posix(): path
               for path in sorted((module / "student").glob("*")) if path.is_file()}
    sources.update({
        "README.md": module / "release/student_README.md",
        "code/README.md": module / "code/README.md",
        "code/Makefile": module / "code/Makefile",
        "code/build.ps1": module / "code/build.ps1",
        "code/tests/test_lab_core.c": module / "code/tests/test_lab_core.c",
        "code/tests/test_lab_student.c": module / "code/tests/test_lab_student.c",
    })
    files = {name: path.read_bytes() for name, path in sources.items()}
    files["MANIFEST.txt"] = ("Module 13 searching, sorting, and consolidation.\n"
                             + "\n".join(sorted([*files, "MANIFEST.txt"])) + "\n").encode()
    args.output.parent.mkdir(parents=True, exist_ok=True)
    with ZipFile(args.output, "x", ZIP_DEFLATED) as archive:
        for name, data in sorted(files.items()): archive.writestr(name, data)
    print(args.output.resolve())


if __name__ == "__main__":
    main()
