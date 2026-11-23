# Module 11 — Reveal the Heap Representation

Use this guide to check the positions and movements in your
[investigation worksheet](investigation_worksheet.md) against [lab.c](lab.c).

## Which positions belong to the tree?

The five slots in `pq` have the following parent–child relationships when
all are live. The numbers in the diagram are array indices.

```text
        0
      /   \
     1     2
    / \
   3   4
```

`size` counts the live entries, starting at index 0. At size 3, only
positions 0, 1, and 2 belong to the tree. At size 4, position 1 has only
a left child. `init_pqueue()` resets the live count to zero.

For a live non-root index `i`, `parent(i)` gives `(i - 1) / 2`.
`left(i)` and `right(i)` compute candidate indices. `priority_child(i)`
returns the right index only if it exists and its value is strictly
smaller than the left child's value. Otherwise it returns the left index.
When both children are absent, `c < size` in `sift_down` stops the read.

## What travels along the path?

In `enqueue(3)` on `[5, 6, 9]`, `sift_up` starts at index 3. It copies
6 from index 1 to 3 and 5 from index 0 to 1. It returns 0. The caller
writes 3 there and increases the size. The array is now `[3, 5, 9, 6]`.

In the first removal from `[1, 3, 9, 6, 5]`, `dequeue` saves 1, takes
5 from the last slot, and reduces the live size to 4. The smaller child,
3, moves into the root. At index 1, the only child is 6. Since 6 does
not outrank 5, the sift returns 1. Writing 5 there gives `[3, 5, 9, 6]`.

## Why does draining the heap sort it?

`heapify()` works from the last parent toward the root for inputs with at
least two values. Once the heap is built, each `dequeue()` returns the
smallest remaining integer. `heap_sort(sorted)` writes those return values
from left to right. The count of live entries falls as the output grows.
