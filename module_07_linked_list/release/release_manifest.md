# Module 7 Current Student Release

The required [student/lab.c](../student/lab.c) contains a ten-slot index-linked pool, list operations, and the linked queue application. The [Python packager](prepare_student_release.py) is the release implementation; the PowerShell wrapper delegates to it.

```sh
python3 module_07_linked_list/release/prepare_student_release.py
```

The default archive is `../dist/module_07_linked_list.zip`. Use `--output` for a new destination. Existing archives are never overwritten.

## Archive layout

The archive preserves student/code directories and includes canonical student Markdown, exact `student/lab.c`, Makefile, PowerShell helper, actual-lab core tests, student test template, test support, READMEs, and a file manifest.

Faculty answers, generated builds, pointer-list implementations, DSU, and the legacy unsafe autopsy are excluded. Students trace the supplied lab and add three original safe linked-list test groups.

## Facilitation notes

Stage A–E READMEs are optional checkpoints within one weekly lesson. They do not produce separate archives. Use the current lesson plan for timing.

## Verification before distribution

Run `make -C ../code core student-tests`. Verify ten-slot exhaustion and preservation, two-argument allocation, insertion writes, tail deletion, detachment/recycling/reuse, caller-managed first removal, and linked queue FIFO/endpoints, public-value returns and recycling, raw empty-index return, and failed-enqueue preservation. Extract a fresh archive and run the same tests there. Compare canonical source bytes and check local Markdown links. A second packaging attempt at the same output must preserve the existing archive and fail. Verify the PowerShell wrapper separately when available.

The linked queue is a linked-list example here; Module 8 imports it for tree and graph BFS. Array queue alternatives and BFS algorithms are Module 8 work. The optional pointer-list/DSU library remains under `../code/`; DSU is taught in Week 14.

The linked queue example is included in the same `student/lab.c`. Its caller checks bool enqueue status and queue emptiness. Public dequeue returns a value and recycles internally; raw node helpers expose indices and separate recycling. Initialize the unused pool and reset `head = tail = -1` for an independent run. Module 8 reuses these functions.
