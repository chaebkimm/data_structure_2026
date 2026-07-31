# Stage C - Investigation Worksheet: A Minimum at the Root

Name: ____________________________
Date: ____________________________

Preserve Sections A through F before opening Stage D. Sections G through I
are later testing, autopsy, and synthesis work.

## Quick reference

Record `a` comes before record `b` when `a` has smaller priority, or when
priorities tie and `a` has smaller arrival sequence.

For live index `i`:

```text
left = 2*i + 1
right = 2*i + 2
parent = (i - 1)/2 when i > 0
```

A calculated child exists only if its index is below `size`. Min-Heap order
requires that no child come before its parent.

**Dijkstra's algorithm** is a later graph method that selects pending work
by smallest known path cost.

## Canonical Module 10 arrivals

Insert the same records in the same order. The Queue assigns each sequence.

| Insertion | Alert ID | Priority | Sequence |
|---:|---:|---:|---:|
| 1 | 71 | 3 | 0 |
| 2 | 88 | 1 | 1 |
| 3 | 42 | 2 | 2 |
| 4 | 17 | 1 | 3 |
| 5 | 26 | 4 | 4 |
| 6 | 9 | 2 | 5 |
| 7 | 63 | 1 | 6 |

Write a record as `ID/P/S`.

## A. Build and map the complete shape

### A1. Trace every insertion

Complete the normal-operation trace. Do not call the checker.

| Added record | First index | Parent indexes tested | Comparisons added | Final active ID array |
|---|---:|---|---:|---|
| `71/3/0` | | | | |
| `88/1/1` | | | | |
| `42/2/2` | | | | |
| `17/1/3` | | | | |
| `26/4/4` | | | | |
| `9/2/5` | | | | |
| `63/1/6` | | | | |

Final normal-operation comparisons: ________________________________

### A2. Draw or describe the final tree

Give every index, full record, parent, left child, and right child. Mark a
missing child only when its calculated index is not below size.

____________________________________________________________________

____________________________________________________________________

### A3. Explain complete shape

Why does appending at index `size` fill the final level from left to right?
Why are child pointers unnecessary?

____________________________________________________________________

## B. Check Heap order without claiming sorted order

### B1. Check every direct relationship

Complete the table for the final seven-record state.

| Child index | Parent index | Parent record | Child record | Passes? |
|---:|---:|---|---|:---:|
| 1 | | | | |
| 2 | | | | |
| 3 | | | | |
| 4 | | | | |
| 5 | | | | |
| 6 | | | | |

### B2. Apply the checker

Starting with `comparison_count == 0`, call
`alert_priority_queue_is_min_heap`.

```text
status:
bool output:
comparisons added:
```

Why must the checker continue after finding one violation in a deliberately
corrupted test state?

____________________________________________________________________

### B3. Disprove global sorting

Name two canonical records whose physical index order differs from logical
service order. Why can the Heap still be valid?

____________________________________________________________________

### B4. Separate shape from Heap order

Classify:

1. valid field shape but one child precedes its parent;
2. size greater than capacity; and
3. a right child imagined without the earlier left position.

Which case returns `OK` with checker output `false`, and which cases fail
shape validation before record scanning?

____________________________________________________________________

## C. Peek and extract

### C1. Peek at the root

Starting from the final canonical Heap with a reset metric, apply
`peek-min`.

```text
output:
normal-operation comparisons:
fields and records changed:
```

### C2. Drain with sift-down

Return to the final canonical Heap and reset the metric. Complete the trace.
At each level, count one sibling comparison only when both children exist,
then one comparison between the selected child and the candidate.

| Extraction | Output ID | Moved candidate ID | Final active ID array | Comparisons added |
|---:|---:|---:|---|---:|
| 1 | | | | |
| 2 | | | | |
| 3 | | | | |
| 4 | | | | |
| 5 | | | | |
| 6 | | | | |
| 7 | | | | |

Complete output order: _____________________________________________

Final normal-operation comparisons: ________________________________

### C3. Handle a lone left child

Identify every canonical extraction step that reaches a position with a
left child but no right child. What comparison is made? Why is the absent
right position never read?

____________________________________________________________________

### C4. Describe the drained state

State `data`, capacity, size, `next_sequence`, comparison count, and the
status of former physical values.

____________________________________________________________________

## D. Separate checking cost from operation cost

### D1. Count the canonical debug checks

If the checker is called after every insertion, it adds:

```text
0 + 1 + 2 + 3 + 4 + 5 + 6 = __________________
```

Record:

```text
normal insertion comparisons:
checker comparisons:
combined instrumented count:
```

If the checker is called after every extraction, its current sizes are
6, 5, 4, 3, 2, 1, and 0. Record:

```text
normal extraction comparisons:
checker comparisons:
combined instrumented count:
```

### D2. Complete the cost table

Let `n` mean live-record count. `O(1)` means fixed work, `O(log n)` means
work grows with the short tree height, and `O(n)` means work may grow with
all live records. **Amortized** means a total cost is spread across many
operations. **Geometric growth** means multiplying capacity, here doubling
it.

| Work | Time | Reason |
|---|---:|---|
| Heap `peek-min` | | |
| Heap insertion without growth | | |
| one insertion that grows storage | | |
| insertions across geometric growth | | |
| Heap `extract-min` | | |
| full `is_min_heap` checker | | |
| find an arbitrary alert ID in a Heap | | |

Why does enabling the full checker after every mutation make the complete
debug cycle `O(n)` even though one repair is `O(log n)`?

____________________________________________________________________

### D3. Compare Module 10

For the same canonical build and drain, compare:

```text
Module 10 unsorted insertion comparisons:
Module 11 Heap insertion comparisons:
Module 10 unsorted drain comparisons:
Module 11 Heap drain comparisons:
```

Which workload moved more comparison work into insertion, and what removal
benefit did it buy?

____________________________________________________________________

## E. Contrast four structures and one memory term

### E1. Heap versus BST

Why do Heap left and right children not mean lower and higher entire
subtrees? Where is the minimum in each structure?

____________________________________________________________________

### E2. Heap versus sorted sequence

Why is the canonical Heap not globally sorted? Compare insertion and
minimum removal costs.

____________________________________________________________________

### E3. Heap versus Module 10 unsorted array

Which public behavior remains identical? Which physical rule and operation
costs change?

____________________________________________________________________

### E4. Binary Heap versus C dynamic-memory heap

Explain why these names describe different ideas even though this binary
Heap's `data` allocation may come from C dynamic memory.

____________________________________________________________________

## F. Contracts, integrity, and scope

### F1. Preserve failures

State what remains unchanged after:

1. checker with NULL output or malformed field shape;
2. empty peek or extraction;
3. failed growth;
4. insertion at 64 live records; and
5. sequence exhaustion.

____________________________________________________________________

### F2. Preserve whole records and ownership

Why must a swap move ID, priority, and sequence together? Why must output
not point inside `data`, and why must a live owning struct not be
shallow-copied?

____________________________________________________________________

### F3. Frame the checker as an integrity control

What silent order defect can the checker detect? What can it not prove
about pointer lifetime, alert authenticity, score quality, or real danger?

____________________________________________________________________

### F4. State the 64-record teaching boundary

Why must a later Dijkstra implementation not claim general correctness if
its required pending work can exceed this teaching cap? State one honest
response to insufficient capacity.

____________________________________________________________________

## G. Design exactly three tests - later work

### G1. Sift-up, stable ties, and separate deltas

Require more than one upward move, use stable ties with nonordering IDs,
verify the exact physical trace, and report normal-operation and checker
deltas separately.

### G2. Better child and missing right

Start from priorities `5,41,17,55,70`. Extract the root and prove the result
is `17,41,70,55`, not a left-first result. Also test a repair step with only
a left child and verify exact comparisons.

### G3. Growth, checker, full preservation

Cross at least two growth boundaries, check Heap order after each mutation,
fill 64 live slots, and prove the rejected next insertion preserves every
field and live record.

## H. Analyze the bounded wrong-child autopsy - later work

Start from:

```text
5/5/0, 41/41/1, 17/17/2, 55/55/3, 70/70/4
```

After removing 5, candidate 70 moves toward the root. A faulty repair
always chooses the left child when both children exist.

1. Which child should the correct repair choose first?
2. Give the correct and faulty final active ID arrays.
3. Identify the first divergence and exact repair.
4. Explain why the bounded program is memory-safe but logically wrong.

## I. Exit synthesis - later work

### I1. Answer the macro-question

In three sentences, state the shape rule, the order rule, and the operation
cost improvement.

### I2. Correct two false claims

Correct:

> A Heap is a sorted BST, and checking it after every change is free.

____________________________________________________________________
