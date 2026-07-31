# Student Textbook - Binary Heap

## 1. Same promise, new storage

A **synthetic alert** is an invented notice used for safe study. Module 10
built a stable minimum **Priority Queue**, a collection that reports or
removes the record ranked first.

A **record** groups values; a **field** is a named part. Write one
record as `ID/P/S`: alert ID, priority, and arrival sequence. A smaller
priority comes first. Equal priorities use the smaller sequence, so earlier
equal-priority arrivals leave first. This two-record rule is the
**comparator**. Alert ID never ranks a record. A **live** record currently
belongs to the collection.

A **backend** is the storage method behind public operations.
Module 10 used an unsorted array, appending quickly but scanning every live
record for the minimum. This module preserves the rule but changes the
backend.

## 2. A complete tree inside an array

A **binary tree** is a hierarchy whose nodes have at most two child
positions. A **complete binary tree** fills every level except possibly the
last; the last fills left to right without a gap.

An **array** is a numbered row. An **index** is one position beginning at 0.
The complete shape needs no stored child pointers. For index `i`:

```text
left child  = 2*i + 1
right child = 2*i + 2
parent      = (i - 1)/2, when i > 0
```

`*` means multiply. `/` means whole-number division here, so a remainder is
discarded. A child exists only when its calculated index is smaller than
`size`, the live-record count. Appending at index `size` preserves the
left-to-right shape. Square brackets select an array position, so `data[0]`
means the record at index 0.

## 3. Minimum Heap order

A **binary Heap** is a complete binary tree arranged for a priority rule.
This course uses a **minimum binary Heap**, or **min-Heap**.

Its **Heap-order invariant** says:

> No child comes before its parent under the complete comparator.

Every record has a route of parents to index 0, called the **root**.
Therefore the minimum is at index 0.

Heap order is a **partial order**. It constrains parent-child pairs, not
every pair. Siblings need not be ordered, and the array need not be sorted.
Left does not mean lower and right does not mean higher.

## 4. Insert and sift-up

`insert` adds one record. It first appends the record at index `size`,
preserving complete shape. If the new record comes before its parent,
exchange the complete records. A **swap** exchanges every field together.
Continue toward the root until the parent comes first or the record reaches
index 0.

This one-route repair is **sift-up**. Its route is `O(log n)`, read "order
log n," because adding one tree level roughly doubles available positions.
A growth insertion may be `O(n)` because storage growth may copy `n`
records. With **geometric growth** (doubling capacity), copying is
**amortized**, meaning its total cost is spread across many insertions;
insertion is amortized `O(log n)`.

## 5. Peek and extract

`peek-min` copies `data[0]`. It performs zero record comparisons and takes
`O(1)`, meaning fixed work independent of size.

`extract-min` saves the root and treats the final live record as a
**candidate**, a record whose final position is not decided. It reduces the
live size, then repairs downward.

When both children exist, first compare them and select the **better child**,
the one that comes first. Compare that child with the candidate. If the
child comes first, move it upward and continue. Otherwise place the
candidate. This is **sift-down**.

If only a left child exists, compare it with the candidate. A complete tree
cannot have a right child without a left child. Sift-down follows at most
one root-to-leaf route, so extraction is `O(log n)`.

## 6. Canonical trace

Insert the Module 10 alerts in the same order:

```text
71/3/0, 88/1/1, 42/2/2, 17/1/3,
26/4/4, 9/2/5, 63/1/6
```

After every sift-up, the active ID arrays are:

```text
[71]
[88,71]
[88,71,42]
[88,17,42,71]
[88,17,42,71,26]
[88,17,42,71,26,9]
[88,17,63,71,26,9,42]
```

Normal insertion comparison additions are `0,1,1,2,1,1,2`, totaling 8.
Peek reports 88 with zero comparisons.

After resetting the metric, extraction produces:

```text
88 -> [17,42,63,71,26,9]  adds 4
17 -> [63,42,9,71,26]     adds 2
63 -> [42,71,9,26]        adds 3
42 -> [9,71,26]           adds 2
9  -> [71,26]             adds 1
71 -> [26]                adds 0
26 -> []                  adds 0
```

The stable output is unchanged from Module 10:
`88,17,63,42,9,71,26`. Heap extraction uses 12 normal comparisons instead
of Module 10's 21.

## 7. Check, then measure honestly

An **invariant checker** is a debug function that tests required rules.
**Debug** work helps locate or explain defects.
`alert_priority_queue_is_min_heap` compares every nonroot record with its
parent. At size `n`, it adds zero comparisons when `n` is 0; otherwise, it
adds exactly `n-1`, even if it finds a violation early.

The same saturating `comparison_count` stores operation and checker calls.
This field is a **metric**, meaning a recorded measurement.
**Saturating** means it stays at `SIZE_MAX`, the largest `size_t` value,
instead of wrapping to zero. `size_t` is C's nonnegative whole-number type
for sizes and indexes. The expression `n-1` means one fewer than `n`.

Measure a normal operation before calling the checker. Then record the
checker addition separately. A debug run with a full check after every
change is **instrumented**, meaning extra checking is enabled. Its complete
cycle is `O(n)` because the checker scans all parent-child links. Do not use
that combined time to deny the **uninstrumented** operation's `O(log n)`
bound; uninstrumented means the separate checker is not enabled. `O(n)`
means work may grow in proportion to all `n` live records.

## 8. Do not confuse the structures

A **subtree** is one node together with all nodes below it. A **binary search
tree (BST)** keeps lower search keys in entire left subtrees and higher keys
in entire right subtrees. A Heap does not. A BST's minimum is found by
following left links; a min-Heap's minimum is at index 0. Finding an
arbitrary ID in a Heap may inspect all records, so it is `O(n)`.

A **sorted array** orders every record. With its minimum at a removable end,
peek and removal are `O(1)`, but insertion shifts records and is `O(n)`.
A Heap is not sorted. Sift-up and extraction are `O(log n)`; one growth
insertion may be `O(n)`, while insertion is amortized `O(log n)`.

C's **dynamic-memory heap** is storage used by `malloc` and `realloc`.
A binary Heap is a data structure. This binary Heap owns an array that may
come from dynamic memory, but the two meanings remain different.

## 9. Safety, integrity, and scope

Capacity grows `0,4,8,16,32,64`. Growth uses a temporary `realloc` result
because `realloc`, a C storage-resizing operation, may move storage or fail.
An **allocation** is a storage block obtained while a program runs.
**Ownership** is responsibility for releasing it exactly once. A pointer
stores a memory address. Failed operations preserve the Queue and
**caller** output; the caller is code requesting an operation. Do not
**shallow-copy** the owning struct: that would copy the pointer but not the
allocation. Output must not point inside its owned array.

**Integrity** means stored state still obeys required rules. The checker can
detect a child that outranks its parent. It cannot prove pointer lifetime,
alert authenticity, correct scoring, or real severity.

The 64-record maximum is a teaching boundary, not a general claim about
later algorithms. **Dijkstra's algorithm** is a later graph procedure that
chooses pending work by smallest known path cost. A later Dijkstra client
must report insufficient capacity or use a separately validated larger
design. It must not silently lose pending work.

**Key sentence:** complete shape gives short routes; Heap order keeps the
stable minimum at the root.
