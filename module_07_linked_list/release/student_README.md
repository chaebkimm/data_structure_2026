# Module 7 — Linked Lists

Read the [English textbook](student/textbook.md) or
[Korean textbook](student/textbook_korean.md). Use the
[class workbook](student/class_material.md) and
[concept slides](student/ppt_material.md), [question outline](student/ppt.md),
and [lab slides](student/ppt_lab_material.md) with the supplied source.

Complete the [lab](student/lab.md) and check the [rubric](student/rubric.md).
The supplied [student/lab.c](student/lab.c) is complete. Trace it and add
three original safe test groups in `code/tests/test_lab_student.c`.

From the extracted root, run:

```sh
make -C code lab-compile
make -C code core
make -C code student-tests
```

PowerShell users can run `./code/build.ps1` and
`./code/build.ps1 -StudentTests`. Add `-Sanitize` where supported.

The tests include `student/lab.c` directly. No repository checkout or faculty
source is needed. The pointer-list and DSU reference library is optional
and is not included in this release.

Follow the slides through acyclic chains, safe insertion/deletion, shared-pool
reuse, a linked stack, and a linked queue. Keep live lists disjoint in the pool.
After recycling a slot, its former owner must stop accessing it. The linked
stack uses a caller-owned `first` and the existing node primitives; there is
no supplied stack API. Insert at the first position, guard empty removal,
save the value and successor, then recycle. Compare output 31,23,17 from a
stack with 17,23,31 from a queue after the same input sequence. Include both
within the three original test groups and the single lab artifact.

The linked queue example in `student/lab.c` accepts and returns **node
indices**. Call `new_lnode()`, check for `-1`, write the payload, then pass
the isolated node to `enqueue_lnode(index)`. `dequeue_lnode()` returns an
isolated allocation (or `-1` when empty); read its payload before returning
it with `free_lnode(index)`. Neither queue operation recycles a node.
`qhead == qtail == -1` represents an empty queue, and the tail's next is
`-1` whenever the queue is nonempty. A stored payload of `-1` is valid.

`init_lnodes_pool()` initializes once, including on first allocation.
Later calls preserve pool ownership, free order, links, and data. They do
not reset a test fixture. Recycle every detached allocation and drain every
list or queue between independent runs. `free_lnode(-1)` is a no-op;
other calls require a valid, allocated, isolated, unreferenced node. Invalid
indices, live-node recycling, double recycling, and stale writes are caller
errors, not rejected operations. Module 8 adds value adapters around these
same node operations for BFS.
