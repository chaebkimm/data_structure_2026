"""Package the Module 7 indexed linked-list lab and linked queue example."""
import argparse
from pathlib import Path
from zipfile import ZIP_DEFLATED, ZipFile


def main():
    module = Path(__file__).resolve().parent.parent
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--output", type=Path,
                        default=module / "dist/module_07_linked_list.zip")
    args = parser.parse_args()

    # Keep exact copies of canonical student material and one lab source.
    sources = {path.relative_to(module).as_posix(): path
               for path in sorted((module / "student").glob("*.md"))}
    sources["student/lab.c"] = module / "student/lab.c"
    sources.update({
        "README.md": module / "release/student_README.md",
        "code/README.md": module / "release/student_code_README.md",
        "code/Makefile": module / "release/student_Makefile",
        "code/build.ps1": module / "release/student_build.ps1",
        "code/tests/lab_test_support.h": module / "code/tests/lab_test_support.h",
        "code/tests/test_lab_core.c": module / "code/tests/test_lab_core.c",
        "code/tests/test_lab_student.c": module / "code/tests/test_lab_student.c",
    })
    files = {name: source.read_bytes() for name, source in sources.items()}
    files["MANIFEST.txt"] = (
        "Module 7 linked-list and linked queue example student release.\n"
        + "\n".join(sorted([*files, "MANIFEST.txt"])) + "\n"
    ).encode()

    args.output.parent.mkdir(parents=True, exist_ok=True)
    with ZipFile(args.output, "x", ZIP_DEFLATED) as archive:
        for name, data in sorted(files.items()):
            archive.writestr(name, data)
    print(args.output.resolve())


if __name__ == "__main__":
    main()
