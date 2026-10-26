"""Create the five Module 09 lab-based student archives, including Module 07."""
import argparse
import hashlib
import io
from pathlib import Path
import re
from zipfile import ZIP_DEFLATED, ZipFile, ZipInfo

MODULE = Path(__file__).resolve().parent.parent
REPOSITORY = MODULE.parent
PREFIX = MODULE.name


def stage(readme, paths):
    entries = {"README.md": MODULE / "release" / readme}
    entries.update({f"{PREFIX}/{name}": MODULE / name for name in paths})
    return entries


def release_maps():
    stages = {
        "module_09_stage_a_initial_inquiry.zip": stage("stage_a_README.md", [
            "student/inquiry_prompt.md", "student/inquiry_prompt_linear.md"]),
        "module_09_stage_b_representation_pause.zip": stage("stage_b_README.md", [
            "student/representation_reveal.md", "student/cognitive_pause.md",
            "student/vocabulary.md"]),
        "module_09_stage_c_investigation.zip": stage("stage_c_README.md", [
            "student/investigation_worksheet.md",
            "student/investigation_worksheet_linear.md"]),
        "module_09_stage_d_textbook_models.zip": stage("stage_d_README.md", [
            "student/textbook.md", "diagrams/hash_table_models.md"]),
        "module_09_stage_e_lab.zip": stage("stage_e_README.md", [
            "student/lab.c", "student/lab.md", "student/evidence_template.md",
            "student/rubric.md", "student/hash_table_autopsy.md",
            "code/tests/test_lab_core.c", "code/tests/test_lab_student.c"]),
    }
    stages["module_09_stage_e_lab.zip"].update({
        f"{PREFIX}/code/README.md": MODULE / "release/student_code_README.md",
        f"{PREFIX}/code/Makefile": MODULE / "release/student_Makefile",
        f"{PREFIX}/code/build.ps1": MODULE / "release/student_build.ps1",
        "module_07_linked_list/student/lab.c":
            REPOSITORY / "module_07_linked_list/student/lab.c",
    })
    return stages


def archive_bytes(entries):
    output = io.BytesIO()
    with ZipFile(output, "w", ZIP_DEFLATED) as archive:
        for name, source in sorted(entries.items()):
            if name.startswith("/") or ".." in Path(name).parts:
                raise ValueError(f"Unsafe archive path: {name}")
            info = ZipInfo(name, date_time=(2000, 1, 1, 0, 0, 0))
            info.compress_type = ZIP_DEFLATED
            info.external_attr = 0o100644 << 16
            archive.writestr(info, source.read_bytes())
    result = output.getvalue()
    with ZipFile(io.BytesIO(result)) as archive:
        if set(archive.namelist()) != set(entries):
            raise ValueError("Archive inventory mismatch")
        for name, source in entries.items():
            if archive.read(name) != source.read_bytes():
                raise ValueError(f"Archive content mismatch: {name}")
    return result


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--output-dir", type=Path, default=MODULE / "dist")
    args = parser.parse_args()
    maps = release_maps()
    # Stage A preserves reasoning before the formal representation is named.
    for source in maps["module_09_stage_a_initial_inquiry.zip"].values():
        text = source.read_text(encoding="utf-8")
        if re.search(r"\b(hash|hashtable|tombstone|rehash|malloc|calloc)\b", text, re.I):
            raise ValueError(f"Formal implementation term in Stage A: {source}")
        if re.search(r"^```(?:c|cpp|python|sh|powershell)\b", text, re.M | re.I):
            raise ValueError(f"Implementation code in Stage A: {source}")
    # Read and verify all sources before creating any output.
    payloads = {name: archive_bytes(entries) for name, entries in maps.items()}
    for name in payloads:
        if (args.output_dir / name).exists():
            raise FileExistsError(f"Refusing to overwrite: {args.output_dir / name}")
    args.output_dir.mkdir(parents=True, exist_ok=True)
    created = []
    try:
        for name, payload in payloads.items():
            destination = args.output_dir / name
            # Exclusive creation also protects against a file appearing after preflight.
            with destination.open("xb") as output:
                created.append(destination)
                output.write(payload)
    except BaseException:
        for destination in created:
            destination.unlink(missing_ok=True)
        raise
    for name, payload in payloads.items():
        print(f"{name}: {len(maps[name])} entries; SHA256 {hashlib.sha256(payload).hexdigest()}")


if __name__ == "__main__":
    main()
