# Module 7 Current Student Release

The required [student/lab.c](../student/lab.c) contains a ten-slot index-linked pool, list operations, and the linked queue application. The [Python packager](prepare_student_release.py) is the release implementation; the PowerShell wrapper delegates to it.

```sh
python3 module_07_linked_list/release/prepare_student_release.py
```

The default archive is `../dist/module_07_linked_list.zip`. Use `--output` for a new destination. Existing archives are never overwritten.

## Archive layout

The archive preserves student/code directories and includes canonical student Markdown, exact `student/lab.c`, Makefile, PowerShell helper, actual-lab core tests, student test template, test support, READMEs, and a file manifest.

Faculty answers, generated builds, pointer-list implementations, DSU, and the legacy unsafe autopsy are excluded. Students trace the supplied lab and add three original safe linked-list test groups covering shared storage and linked stack/queue applications. The stack is caller-side use of the supplied primitives. The concept slides `student/ppt_material.md`, retrieval questions
`student/ppt.md`, and code-oriented `student/ppt_lab_material.md` are all
packaged. Short slide names such as `arr`, `CAP`, and `new_node` map to
the canonical lab names explained in the textbooks.

## Facilitation notes

Stage A–E READMEs are optional checkpoints within one weekly lesson. They do not produce separate archives. Use the current lesson plan for timing.

## Verification before distribution

Run `make -C ../code core student-tests`. Verify ten-slot exhaustion and preservation, zero-argument allocation and caller payload writes, one-time
initialization, insertion writes, tail deletion, isolated detachment,
recycling/reuse, caller-managed first removal, and linked queue FIFO/endpoints,
index returns with separate recycling, raw empty-index return, and exhausted
allocation preservation. Execute the textbook's caller-side Stack example and trace shared-pool reuse as additional material checks. Extract a fresh archive and run the same tests there. Compare canonical source bytes and check local Markdown links. A second packaging attempt at the same output must preserve the existing archive and fail. Verify the PowerShell wrapper separately when available.

The linked queue is a linked-list example here; Module 8 imports it for tree and graph BFS. Array queue alternatives and BFS algorithms are Module 8 work. The optional pointer-list/DSU library remains under `../code/`; DSU is taught in Week 14.

The linked queue accepts and returns node indices through
`enqueue_lnode(index)`/`dequeue_lnode()`. Use `qhead`/`qtail` and preserve
`lnodes[qtail].next == -1` when nonempty. Recycle dequeued allocations after
reading their values. Initialization happens once and cannot reset ownership;
each independent test must return all allocations. Module 8 supplies its own
value adapters around this unchanged source.

## Website source synchronization

After editing canonical student materials, run:

```sh
python3 module_07_linked_list/release/sync_web.py
```

The synchronizer creates a fresh temporary archive through the same packager,
copies its exact members and `sources.zip` to the web checkout's
`public/chapter-7/`, and derives both `content/chapter-seven.*.md` readings.
Only relative prose links are rewritten to packaged `/chapter-7/student/`
URLs; source downloads and code blocks retain canonical bytes. Fixed archive
metadata makes repeated synchronization reproducible. To target a different
web checkout, pass its absolute path with `--web-root`.

Run `python3 module_07_linked_list/release/test_sync_web.py` to check link
normalization, code-fence preservation, invalid destination rejection, exact
source downloads, and repeated archive byte equality in a temporary web root.
