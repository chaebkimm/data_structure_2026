"""Package the current Module 8 array-queue and maze BFS lesson."""
import argparse
from pathlib import Path
from zipfile import ZIP_DEFLATED, ZipFile


def main():
    module = Path(__file__).resolve().parent.parent
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--output", type=Path,
                        default=module / "dist/module_08_graph_bfs.zip")
    args = parser.parse_args()
    current_names = (
        "textbook.md", "textbook_korean.md", "class_material.md",
        "ppt.md", "ppt_lab.md", "ppt_material.md", "ppt_lab_material.md", "lab.md",
        "evidence_template.md", "rubric.md", "vocabulary.md",
        "cognitive_pause.md", "lab.c",
    )
    sources = {"module_08_graph_bfs/student/" + name:
               module / "student" / name for name in current_names}
    sources.update({
        "README.md": module / "release/student_README.md",
        "module_08_graph_bfs/README.md": module / "release/student_README.md",
        "module_08_graph_bfs/code/README.md": module / "release/student_code_README.md",
        "module_08_graph_bfs/code/Makefile": module / "release/student_Makefile",
        "module_08_graph_bfs/code/build.ps1": module / "release/student_build.ps1",
        "module_08_graph_bfs/code/tests/test_lecture.c": module / "code/tests/test_lecture.c",
    })
    files = {name: source.read_bytes() for name, source in sources.items()}
    files["MANIFEST.txt"] = (
        "Module 8 array queues, tree level order, and maze BFS student release.\n"
        + "\n".join(sorted([*files, "MANIFEST.txt"])) + "\n"
    ).encode()
    args.output.parent.mkdir(parents=True, exist_ok=True)
    with ZipFile(args.output, "x", ZIP_DEFLATED) as archive:
        for name, data in sorted(files.items()):
            archive.writestr(name, data)
    print(args.output.resolve())


if __name__ == "__main__":
    main()
