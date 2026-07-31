# Student Code Package

You will complete exactly three concepts in
`starter/alert_priority_queue.c`:

1. check every live parent relationship with
   `alert_priority_queue_is_min_heap`;
2. insert a complete record and sift it upward, growing storage when needed;
   and
3. extract the minimum root, replace it with the final live record, and sift
   that record downward.

A **binary Heap** is a complete binary tree stored in an array. **Complete**
means that positions fill level by level from left to right. A **minimum
Heap** keeps each parent no later than either child under the complete record
comparison rule.

This package preserves Module 10 ordering:

1. smaller `priority` first;
2. for equal priorities, smaller `arrival_sequence` first; and
3. `alert_id` and physical position do not affect order.

For a live index `i`:

```text
parent, when i > 0: (i - 1) / 2
left child:          2 * i + 1
right child:         2 * i + 2
```

Never read a child position unless it is smaller than `size`. In particular,
a final parent can have a left child without a right child.

The unsorted Module 10 backend is replaced by Heap order while the capacity
sequence remains:

```text
0 -> 4 -> 8 -> 16 -> 32 -> 64
```

The only public API addition is `alert_priority_queue_is_min_heap`. On a
valid visible shape, it scans every non-root live record. It adds zero
comparator calls when empty and otherwise exactly `size - 1` to the shared
saturating comparison counter. It must finish the scan even after finding a
violation. Reset or snapshot the counter so checker/debug comparisons are
reported separately from the comparisons performed by insert or extract.

Edit only:

- `starter/alert_priority_queue.c`; and
- `tests/test_student.c`.

Run the public core tests from this directory:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1
```

Run your three tests:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -StudentTests
```

Run the isolated faulty program:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target autopsy
```

GNU Make users can run:

```sh
make starter-core
make starter-student-tests
make autopsy
```

The starter is intentionally incomplete. A failed first test run is
expected. Fix the earliest failed requirement without changing the public
header or supplied core tests.
