"""Package the current index-based AVL lab and its Module 2 dependency."""
import argparse
import hashlib
import io
from pathlib import Path
from zipfile import ZIP_DEFLATED, ZipFile, ZipInfo


def release_map(module):
    sources = {
        path.relative_to(module).as_posix(): path
        for path in sorted((module / "student").glob("*.md"))
    }
    sources.update({
        path.relative_to(module).as_posix(): path
        for path in sorted((module / "release").glob("stage_*_README.md"))
    })
    sources.update({
        "README.md": module / "release/student_README.md",
        "student/lab.c": module / "student/lab.c",
        "module_02_binary_tree/student/lab.c":
            module.parent / "module_02_binary_tree/student/lab.c",
        "diagrams/bst_avl_models.md": module / "diagrams/bst_avl_models.md",
        "code/README.md": module / "release/student_code_README.md",
        "code/Makefile": module / "release/student_Makefile",
        "code/build.ps1": module / "release/student_build.ps1",
        "code/tests/test_lab_core.c": module / "code/tests/test_lab_core.c",
        "code/tests/test_lab_student.c": module / "code/tests/test_lab_student.c",
        "code/tests/compare_lab.c": module / "code/tests/compare_lab.c",
        "code/tests/lab_test_support.h": module / "code/tests/lab_test_support.h",
    })
    return sources


def package_bytes(sources):
    # Resolve every required source before creating an output file.
    files = {name: source.read_bytes() for name, source in sources.items()}
    files["MANIFEST.txt"] = (
        "Module 12 index-based AVL student release.\n"
        "SHA256  archive path (MANIFEST.txt is excluded from hashing)\n"
        + "".join(
            f"{hashlib.sha256(data).hexdigest()}  {name}\n"
            for name, data in sorted(files.items())
        )
    ).encode("utf-8")
    buffer = io.BytesIO()
    with ZipFile(buffer, "w", ZIP_DEFLATED) as archive:
        for name, data in sorted(files.items()):
            if name.startswith("/") or ".." in Path(name).parts:
                raise ValueError(f"Unsafe archive entry: {name}")
            info = ZipInfo(name, (2000, 1, 1, 0, 0, 0))
            info.compress_type = ZIP_DEFLATED
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
    parser.add_argument(
        "--output", type=Path,
        default=module / "dist/module_12_bst_avl.zip",
    )
    args = parser.parse_args()
    payload, count = package_bytes(release_map(module))
    args.output.parent.mkdir(parents=True, exist_ok=True)
    # Exclusive creation also protects the destination from concurrent runs.
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
