# Module 5 Release Manifest

Run `prepare_student_release.ps1` to create five staged archives in `dist/`.
The script checks every source first and refuses to overwrite existing archives.

1. Stage A: inquiry prompts.
2. Stage B: representation reveal, pause, and vocabulary.
3. Stage C: investigation worksheets for the current array-based lab.
4. Stage D: English and Korean textbooks, both slide Markdown files, and DFS models.
5. Stage E: current `student/lab.c`, both slide Markdown files, executable lecture demo, direct lab checks,
   bundled Chapter 2 tree and Chapter 4 stack dependencies, and evidence files.
   The pointer-based starter, public tests, and copy autopsy remain optional comparisons.

The student Markdown links retain filenames from the original `student/`
directory. Early-stage links to textbooks and slides resolve in Stage D;
links to `lab.c` refer to Stage E's `student/lab.c`. Each stage README explains
where these later materials appear. This preserves the staged reveal without
duplicating the executable source in the early archives.

The Stage E archive preserves these include paths at the archive root:

```text
student/lab.c
student/ppt_lab_material.md
student/ppt_material.md
module_02_binary_tree/student/lab.c
module_04_stack/student/lab.c
code/lecture/lab_demo.c
code/tests/test_lab.c
```

Before release, run `make lecture lab-tests solution-core solution-extension`
in the repository's `code/` directory. Extract Stage E into an empty directory,
then run `make lecture lab-tests` in its `code/` directory. Confirm the archives
contain no `instructor/`, `solution/`, or reference answer sources. The extracted
Makefile uses `-I..` so the included Chapter 2 and Chapter 4 files resolve without
the original repository.
