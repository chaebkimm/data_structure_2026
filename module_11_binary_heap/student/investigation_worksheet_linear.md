# Stage C - Investigation Worksheet: A Minimum at the Root

Name: ____________________________
Date: ____________________________

Preserve Sections A through F before opening Stage D. Sections G through I
are later testing, autopsy, and synthesis work. This linear version contains
the same records, operations, questions, and scoring as the standard form.

## Quick reference

Record `a` comes before record `b` when `a` has smaller priority, or when
priorities tie and `a` has smaller arrival sequence.

For live index `i`, left child is `2*i+1`, right child is `2*i+2`, and the
parent index of nonroot index `i` is `(i-1)/2`. A child exists only if its
index is below `size`. No child may come before its parent.

**Dijkstra's algorithm** is a later graph method that selects pending work
by smallest known path cost.

## Canonical Module 10 arrivals

Insert these exact records in order:

1. `71/3/0`;
2. `88/1/1`;
3. `42/2/2`;
4. `17/1/3`;
5. `26/4/4`;
6. `9/2/5`; and
7. `63/1/6`.

`ID/P/S` means alert ID, priority, and sequence.

## A. Build and map the complete shape

### A1. Trace every insertion

For each of the seven records, state:

1. its first index;
2. every parent index tested;
3. comparisons added; and
4. the complete final active ID array for that insertion.

Do not call the checker.

Response: ___________________________________________________________

Final normal-operation comparisons: ________________________________

### A2. Draw or describe the final tree

For every index 0 through 6, give the full record, parent when present,
left child when present, and right child when present. A calculated child
is missing when its index is not below size.

Response: ___________________________________________________________

### A3. Explain complete shape

Why does appending at index `size` fill the final level from left to right?
Why are child pointers unnecessary?

Response: ___________________________________________________________

## B. Check Heap order without claiming sorted order

### B1. Check every direct relationship

For each child index 1 through 6, state:

1. parent index;
2. parent record;
3. child record; and
4. whether the pair passes.

Response: ___________________________________________________________

### B2. Apply the checker

Starting with `comparison_count == 0`, call
`alert_priority_queue_is_min_heap`. State status, Boolean output, and
comparisons added.

Response: ___________________________________________________________

Why must the checker continue after finding one violation in a deliberately
corrupted test state?

Response: ___________________________________________________________

### B3. Disprove global sorting

Name two canonical records whose physical index order differs from logical
service order. Why can the Heap still be valid?

Response: ___________________________________________________________

### B4. Separate shape from Heap order

Classify these exact cases:

1. valid field shape but one child precedes its parent;
2. size greater than capacity; and
3. a right child imagined without the earlier left position.

Which returns `OK` with checker output `false`, and which fail shape
validation before record scanning?

Response: ___________________________________________________________

## C. Peek and extract

### C1. Peek at the root

Starting from the final canonical Heap with a reset metric, apply
`peek-min`. State output, normal-operation comparisons, and every field or
record changed.

Response: ___________________________________________________________

### C2. Drain with sift-down

Return to the final canonical Heap and reset the metric. For each of seven
extractions, state:

1. output ID;
2. moved candidate ID;
3. complete final active ID array; and
4. comparisons added.

Count one sibling comparison only when both children exist, then one
selected-child/candidate comparison.

Response: ___________________________________________________________

Complete output order: _____________________________________________

Final normal-operation comparisons: ________________________________

### C3. Handle a lone left child

Identify every canonical extraction step that reaches a position with a
left child but no right child. What comparison is made? Why is the absent
right position never read?

Response: ___________________________________________________________

### C4. Describe the drained state

State data, capacity, size, `next_sequence`, comparison count, and the
status of former physical values.

Response: ___________________________________________________________

## D. Separate checking cost from operation cost

### D1. Count the canonical debug checks

After every insertion, checker comparisons are:

```text
0 + 1 + 2 + 3 + 4 + 5 + 6
```

State normal insertion comparisons, checker comparisons, and combined
instrumented count.

Response: ___________________________________________________________

After every extraction, checker sizes are 6, 5, 4, 3, 2, 1, and 0. State
normal extraction comparisons, checker comparisons, and combined
instrumented count.

Response: ___________________________________________________________

### D2. Complete the cost table

Let `n` mean live-record count. `O(1)` means fixed work, `O(log n)` means
work grows with the short tree height, and `O(n)` means work may grow with
all live records. **Amortized** means a total cost is spread across many
operations. **Geometric growth** means multiplying capacity, here doubling
it.

For each item, state time and reason:

1. Heap `peek-min`;
2. Heap insertion without growth;
3. one insertion that grows storage;
4. insertions across geometric growth;
5. Heap `extract-min`;
6. full `is_min_heap` checker; and
7. find an arbitrary alert ID in a Heap.

Response: ___________________________________________________________

Why does a checker after every mutation make the complete debug cycle
`O(n)` even though one repair is `O(log n)`?

Response: ___________________________________________________________

### D3. Compare Module 10

State:

1. Module 10 unsorted insertion comparisons;
2. Module 11 Heap insertion comparisons;
3. Module 10 unsorted drain comparisons; and
4. Module 11 Heap drain comparisons.

Which workload moved comparison work into insertion, and what removal
benefit did it buy?

Response: ___________________________________________________________

## E. Contrast four structures and one memory term

### E1. Heap versus BST

Why do Heap left and right children not mean lower and higher entire
subtrees? Where is the minimum in each structure?

Response: ___________________________________________________________

### E2. Heap versus sorted sequence

Why is the canonical Heap not globally sorted? Compare insertion and
minimum removal costs.

Response: ___________________________________________________________

### E3. Heap versus Module 10 unsorted array

Which public behavior remains identical? Which physical rule and operation
costs change?

Response: ___________________________________________________________

### E4. Binary Heap versus C dynamic-memory heap

Explain why these names describe different ideas even though this binary
Heap's `data` allocation may come from C dynamic memory.

Response: ___________________________________________________________

## F. Contracts, integrity, and scope

### F1. Preserve failures

State what remains unchanged after:

1. checker with NULL output or malformed field shape;
2. empty peek or extraction;
3. failed growth;
4. insertion at 64 live records; and
5. sequence exhaustion.

Response: ___________________________________________________________

### F2. Preserve whole records and ownership

Why must a swap move ID, priority, and sequence together? Why must output
not point inside `data`, and why must a live owning struct not be
shallow-copied?

Response: ___________________________________________________________

### F3. Frame the checker as an integrity control

What silent order defect can the checker detect? What can it not prove
about pointer lifetime, alert authenticity, score quality, or real danger?

Response: ___________________________________________________________

### F4. State the 64-record teaching boundary

Why must a later Dijkstra implementation not claim general correctness if
its required pending work can exceed this teaching cap? State one honest
response to insufficient capacity.

Response: ___________________________________________________________

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

Cross at least two growth boundaries, check Heap order after every mutation,
fill 64 live slots, and prove the rejected next insertion preserves every
field and live record.

## H. Analyze the bounded wrong-child autopsy - later work

Start from:

```text
5/5/0, 41/41/1, 17/17/2, 55/55/3, 70/70/4
```

After removing 5, candidate 70 moves toward the root. A faulty repair
always chooses the left child when both children exist.

State the correct first child, correct and faulty final active ID arrays,
first divergence, exact repair, and why the bounded program is memory-safe
but logically wrong.

Response: ___________________________________________________________

## I. Exit synthesis - later work

### I1. Answer the macro-question

In three sentences, state the shape rule, order rule, and operation cost
improvement.

### I2. Correct two false claims

Correct:

> A Heap is a sorted BST, and checking it after every change is free.

Response: ___________________________________________________________
