"""Package Module 8 queues, tree BFS, and maze graph BFS with dependencies."""
import argparse
from pathlib import Path
from zipfile import ZIP_DEFLATED, ZipFile


def main():
    module = Path(__file__).resolve().parent.parent
    repository = module.parent
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--output", type=Path,
                        default=module / "dist/module_08_graph_bfs.zip")
    args = parser.parse_args()
    current_names = (
        "textbook.md", "textbook_korean.md", "class_material.md",
        "ppt_material.md", "ppt_lab_material.md", "lab.md",
        "evidence_template.md", "rubric.md", "vocabulary.md",
        "queue.c", "tree_bfs.c", "lab.c", "lab_driver.c",
    )
    sources = {"module_08_graph_bfs/student/" + name:
               module / "student" / name for name in current_names}
    sources.update({
        "README.md": module / "release/student_README.md",
        "module_08_graph_bfs/README.md": module / "README.md",
        "module_08_graph_bfs/code/README.md": module / "release/student_code_README.md",
        "module_08_graph_bfs/code/Makefile": module / "release/student_Makefile",
        "module_08_graph_bfs/code/build.ps1": module / "release/student_build.ps1",
        "module_02_binary_tree/student/lab.c": repository / "module_02_binary_tree/student/lab.c",
        "module_07_linked_list/student/lab.c": repository / "module_07_linked_list/student/lab.c",
    })
    files = {name: source.read_bytes() for name, source in sources.items()}
    # Only the student guide is shipped as the module landing page; it has no instructor links.
    files["module_08_graph_bfs/README.md"] = files["README.md"]
    files["MANIFEST.txt"] = (
        "Module 8 queues, tree BFS, and graph BFS student release.\n"
        + "\n".join(sorted([*files, "MANIFEST.txt"])) + "\n"
    ).encode()
    args.output.parent.mkdir(parents=True, exist_ok=True)
    with ZipFile(args.output, "x", ZIP_DEFLATED) as archive:
        for name, data in sorted(files.items()):
            archive.writestr(name, data)
    print(args.output.resolve())


if __name__ == "__main__":
    main()
