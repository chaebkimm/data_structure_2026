# Module 12 Current Student Release

The required release follows the exact updated
[student/lab.c](../student/lab.c), which reuses Module 2's indexed node array.
It replaces the old five-archive pointer-library distribution. Stage A–E
remain opening-order checkpoints within one 180-minute Week 12 lesson.
The complete archive does not enforce withholding; the instructor controls
which files students open at each checkpoint.

## Create the archive

From the module directory, use Python 3:

```sh
python3 release/prepare_student_release.py
```

The default output is `dist/module_12_bst_avl.zip`. For verification or a
new release, choose an unused destination:

```sh
python3 release/prepare_student_release.py --output /path/to/new/release.zip
```

The PowerShell wrapper accepts `-OutputPath` for the same option. Existing
archives are never overwritten. The generator checks required source files
rather than enforcing an obsolete fixed inventory count.

## Included materials

- The student README and generated `MANIFEST.txt` with SHA-256 hashes.
- Every current `student/*.md`, the exact `student/lab.c`, Stage A–E notes,
  and `diagrams/bst_avl_models.md`.
- The exact dependency `module_02_binary_tree/student/lab.c` at the archive
  root, preserving the lab's original include unchanged.
- Student-only `code/README.md`, `code/Makefile`, and `code/build.ps1`.
- `code/tests/test_lab_core.c`, `test_lab_student.c`, `compare_lab.c`, and
  `lab_test_support.h`.

The released Makefile supplies the student-folder and archive-root include
paths, so extraction requires no original repository checkout. It compiles
the source or one driver at a time, never a second compiled copy of an
included `lab.c`.

Instructor keys, the optional pointer-based headers/starter/solution/support
API, old library tests, allocation autopsy, release tooling, binaries, and
build directories are excluded. The current lab is complete and included
in full; students contribute traces, independent tests, and evidence.

## Required source contract

There are ten slots with character data, integer node IDs and links, `-1`
for missing links, and a separate `height[10]`. Missing height is `-1`,
leaf height is `0`. Callers initialize fresh child links, respect capacity,
insert each ID once, and save the returned root. Duplicate characters are
accepted; inorder order remains nondecreasing after rotations.

No `Tree` ownership type, allocation-failure API, strict duplicate rejection,
64-node capacity, full validator, search counter, or deletion operation is
exported by the required source. Independent validation, baseline insertion,
and measured search are test-driver support.

## Teaching checkpoints

1. Stage A: preserve an initial record arrangement before formal names.
2. Stage B: reveal indexed links/heights and preserve the Cognitive Pause.
3. Stage C: trace link repairs and bottom-up height updates.
4. Stage D: compare textbook/model evidence with preserved predictions.
5. Stage E: execute tests and submit one Week 12 evidence artifact.

## Verify before delivery

Build `lab-compile`, `core`, `student-tests`, and `comparison` in both the
repository and a fresh extraction. Run core/student tests under sanitizers
where supported. Confirm four canonical rotations, nonempty middle-subtree
preservation, exact cached heights, nondecreasing inorder data, duplicate
values, a ten-node tree, and seven-key baseline/AVL measurements.

The packager reads source bytes before output creation, rejects unsafe
archive paths, sets deterministic metadata, and checks every ZIP entry's
bytes and the complete inventory in memory. Check local document links and
verify that a repeated destination is refused without changing the archive.
The optional pointer-library checks remain a separate repository activity.
