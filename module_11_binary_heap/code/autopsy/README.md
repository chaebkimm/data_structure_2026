# Safe Wrong-Child Autopsy

`faulty_sift_down.c` is a standalone bounded program. It does not include or
link the student Priority Queue, allocates no memory, and checks every child
index before access.

The initial minimum Heap stores these priorities:

```text
[5, 41, 17, 55, 70]
```

The program removes `5` and uses `70` as the downward-repair candidate. Its
intentional defect always chooses the left child instead of comparing both
existing children.

Before running it:

1. draw the array as a complete binary tree;
2. predict the faulty array;
3. predict the correct array; and
4. identify the first decision at which they differ.

The bounded faulty result is `[41, 55, 17, 70]`. The correct repair chooses
the better right child first and produces `[17, 41, 70, 55]`.

Explain which parent-child relationship proves the faulty result is not a
minimum Heap and propose one regression test. Do not replace these synthetic
records with production alerts, logs, hostnames, or identifiers.
