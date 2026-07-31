# Binary Heap Models and Exact Linear Equivalents

Every visual is followed by an exact linear text equivalent. No meaning
depends on color, drawing quality, or spatial position.

`ID/P/S` means alert ID, priority, and arrival sequence. Smaller priority
comes first. Equal priority uses smaller sequence. Alert ID does not rank a
record.

## Model 1 - Canonical Heap as array and tree

A **binary Heap** is a complete binary tree used for a priority rule. A
**complete binary tree** fills every level except possibly the last, which
fills left to right. An **array** is a numbered row. An **index** is one
position beginning at 0.

Canonical active array:

```text
index       0        1        2        3        4       5        6
record   88/1/1   17/1/3   63/1/6   71/3/0   26/4/4  9/2/5   42/2/2
```

The same records as a tree:

```text
                         0:88/1/1
                     /              \
             1:17/1/3                2:63/1/6
             /       \               /       \
      3:71/3/0    4:26/4/4     5:9/2/5    6:42/2/2
```

Exact linear equivalent:

1. Root index 0 stores `88/1/1`.
2. Index 0 has left child index 1, `17/1/3`.
3. Index 0 has right child index 2, `63/1/6`.
4. Index 1 has children index 3, `71/3/0`, and index 4, `26/4/4`.
5. Index 2 has children index 5, `9/2/5`, and index 6, `42/2/2`.
6. Indexes 3 through 6 have no live children.
7. Every level is full, so this seven-record shape is complete.

## Model 2 - Index formulas

For a live index named `i`:

```text
left child  = 2*i + 1
right child = 2*i + 2
parent      = (i - 1)/2, only when i > 0
```

`*` means multiplication. `/` means whole-number division, so any remainder
is discarded. A calculated child exists only when its index is smaller than
`size`, the live-record count.

Examples:

```text
i = 1:
left = 3
right = 4
parent = 0

i = 2:
left = 5
right = 6
parent = 0
```

Exact linear equivalent:

1. For index 1, `2*1+1` equals 3 and `2*1+2` equals 4.
2. Parent `(1-1)/2` equals 0.
3. For index 2, the child indexes are 5 and 6.
4. Parent `(2-1)/2` uses whole-number division; `1/2` becomes 0.
5. No parent formula is applied to root index 0.
6. Appending at index `size` preserves left-to-right completeness.

## Model 3 - Heap order is partial

The **Heap-order invariant** requires that no child come before its parent
under priority then sequence. An **invariant** is a rule true in every valid
completed state.

Required canonical comparisons:

```text
88 before 17       88 before 63
17 before 71       17 before 26
63 before 9        63 before 42
```

Not required:

```text
17 compared with sibling 63
71 compared with 9
every earlier index compared with every later index
```

Exact linear equivalent:

1. Each of the six nonroot records is checked against one parent.
2. Alert 88 precedes both priority-1 children because sequence 1 is earlier.
3. Alert 17 precedes its priority-3 and priority-4 children.
4. Alert 63 precedes its priority-2 children.
5. Record 9 should be serviced before record 71, even though 9 is at later
   physical index 5.
6. The Heap is valid but not globally sorted.
7. This is a **partial order**, meaning only required relationships are
   ordered.

## Model 4 - Canonical sift-up build

**Sift-up** repairs one route from an appended record toward root index 0.
A normal-operation comparison is a comparator call made by the requested
operation before a separate checker.

```text
add 71: [71]                         +0
add 88: [88,71]                      +1
add 42: [88,71,42]                   +1
add 17: [88,17,42,71]                +2
add 26: [88,17,42,71,26]             +1
add 9:  [88,17,42,71,26,9]           +1
add 63: [88,17,63,71,26,9,42]        +2
```

Exact linear equivalent:

1. Alert 71 starts at root and needs no comparison.
2. Alert 88 starts at index 1, precedes parent 71, and moves to index 0.
3. Alert 42 starts at index 2 and stays below 88.
4. Alert 17 starts at index 3, moves above 71, then stays below earlier
   equal-priority 88.
5. Alert 26 stays below 17.
6. Alert 9 ties parent 42 on priority but has later sequence, so it stays.
7. Alert 63 starts at index 6, moves above 42, then stays below earlier
   equal-priority 88.
8. Normal insertion comparisons total
   `0+1+1+2+1+1+2`, which equals 8.

## Model 5 - Canonical sift-down drain

**Sift-down** repairs one route from the root toward a leaf. A **candidate**
is the former final record whose new position is being found. When two
children exist, the **better child** is the one that comes first under the
comparator.

```text
output 88: [17,42,63,71,26,9]   +4
output 17: [63,42,9,71,26]      +2
output 63: [42,71,9,26]         +3
output 42: [9,71,26]            +2
output 9:  [71,26]              +1
output 71: [26]                 +0
output 26: []                   +0
```

Exact linear equivalent:

1. Removing 88 makes 42 the candidate. Child 17 is better than child 63
   and moves to root. At the next position, candidate 42 already precedes
   children 71 and 26. Four comparisons occur.
2. Removing 17 makes 9 the candidate. Child 63 is better than child 42 and
   moves to root. Two comparisons occur.
3. Removing 63 makes 26 the candidate. Child 42 is better than child 9 and
   moves up. At the next position only left child 71 exists and precedes
   26. Three comparisons occur.
4. Removing 42 makes 26 the candidate. Child 9 moves to root. Two
   comparisons occur.
5. Removing 9 makes 26 the candidate. Lone child 71 moves to root. One
   comparison occurs.
6. Removing 71 leaves one record and makes no record comparison.
7. Removing 26 drains the Heap and makes no record comparison.
8. Stable output is `88,17,63,42,9,71,26`.
9. Normal drain comparisons total 12.

## Model 6 - Locked Cognitive Pause states

Starting state:

```text
[81/1/1, 27/1/3, 12/2/2, 54/3/0, 68/4/4]
```

Tree relationships:

```text
81 has children 27 and 12
27 has children 54 and 68
```

Target 2 result:

```text
insert 35/1/5
[81,27,35,54,68,12]
normal comparisons +2
```

Target 3 result:

```text
extract 81
[27,54,12,68]
normal comparisons +3
```

Exact linear equivalent:

1. The starting size is 5, so the checker compares indexes 1 through 4 and
   adds four comparisons.
2. The starting state passes because no child precedes its parent.
3. New record 35 begins at index 5.
4. It precedes parent 12 and moves to index 2.
5. It does not precede root 81 because 81 has earlier equal-priority
   sequence 1. Insertion adds two comparisons.
6. For extraction, final record 68 becomes candidate at root.
7. Children 27 and 12 are compared; 27 is selected.
8. Record 27 precedes candidate 68 and moves to root.
9. At the next position, left child 54 exists and no right child exists.
10. Record 54 precedes candidate 68 and moves up.
11. Extraction adds three comparisons and finishes
    `[27,54,12,68]`.

## Model 7 - Checker instrumentation

An **invariant checker** is a debug function that checks every required
parent-child relationship. **Instrumentation** is extra checking or
measurement added for study.

```text
canonical build:
normal operation comparisons       8
checks after sizes 1 through 7    21
combined instrumented count       29

canonical drain:
normal operation comparisons      12
checks after sizes 6 through 0    15
combined instrumented count       27
```

Exact linear equivalent:

1. A successful checker adds zero comparisons when `n` is 0; otherwise, it
   adds exactly `n-1`.
2. Post-insertion checks add `0+1+2+3+4+5+6`, which equals 21.
3. Normal build work is 8, so the combined instrumented value is 29.
4. Post-extraction checks add `5+4+3+2+1+0+0`, which equals 15.
5. Normal drain work is 12, so the combined instrumented value is 27.
6. The checker continues after a violation so every direct relationship is
   inspected.
7. Operation and checker deltas must be reported separately.

## Model 8 - Cost and structure contrasts

Let `n` mean live-record count. `O(1)` means fixed work. `O(log n)` means
work grows with the short height of a complete tree. `O(n)` means work may
grow with all live records. **Amortized** means a total cost is spread
across many operations. **Geometric growth** means multiplying capacity,
here doubling it.

| Structure or work | Insert | Minimum report | Minimum removal | Arbitrary ID search |
|---|---:|---:|---:|---:|
| Module 10 unsorted array | amortized `O(1)` | `O(n)` | `O(n)` | `O(n)` |
| Module 11 min-Heap, no growth | `O(log n)` | `O(1)` | `O(log n)` | `O(n)` |
| one Heap growth insertion | `O(n)` copying may occur | not applicable | not applicable | not applicable |
| Heap insertion sequence | amortized `O(log n)` | not applicable | not applicable | not applicable |
| sorted array, minimum at end | `O(n)` | `O(1)` | `O(1)` | depends on search key |
| full Heap checker | not an insert | not a report | not a removal | `O(n)` check |

Exact linear equivalent:

1. The unsorted backend spends little comparison work on insertion and
   scans for minimum service.
2. Sift-up and extraction follow `O(log n)` paths.
3. One growth insertion may copy `n` records and be `O(n)`.
4. Geometric capacity growth, which doubles capacity here, spreads copying
   across many insertions, so
   insertion is amortized `O(log n)`.
5. The sorted array spends shifting work to maintain total order.
6. A Heap does not support fast arbitrary ID search merely because minimum
   access is fast.
7. A full checker is separate debug work.

## Model 9 - Heap, BST, sorted sequence, and C memory

```text
binary Heap:
complete shape + parent-child priority order

binary search tree:
entire left subtree lower + entire right subtree higher

sorted sequence:
every record kept in total order

C dynamic-memory heap:
storage used by malloc and realloc
```

Exact linear equivalent:

1. A Heap root is the minimum, but left and right do not divide all lower
   and higher values.
2. A **binary search tree (BST)** uses global left/right search-key order.
3. A sorted sequence orders every pair consistently.
4. C's **dynamic-memory heap** is an allocation source, not this tree
   structure.
5. This binary Heap may own an array obtained from C dynamic memory.
6. The similar word does not make the concepts identical.

## Model 10 - Safe wrong-child autopsy

Before extraction:

```text
[5/5/0, 41/41/1, 17/17/2, 55/55/3, 70/70/4]
```

After removing 5, candidate 70 reaches root.

```text
correct chooses right child 17:
[17,41,70,55]

faulty always chooses left child 41:
[41,55,17,70]
```

Exact linear equivalent:

1. At root, left child is 41 at priority 41.
2. Right child is 17 at priority 17.
3. The correct repair compares them and chooses 17.
4. Candidate 70 has priority 70, so 17 moves upward.
5. The correct final IDs are `17,41,70,55`.
6. The faulty repair chooses left child 41 without comparing the better
   right child.
7. Its final IDs are `41,55,17,70`.
8. Faulty root 41 is outranked by child 17, so Heap order is broken.
9. Every fixture index remains in bounds; memory safety alone does not
   establish logical correctness.

## Model 11 - Integrity and the teaching cap

**Integrity** means stored state still follows required rules.

```text
checker can support:
child does not outrank parent

checker cannot prove:
pointer still live
alert authentic
priority accurate
work durably retained
real system secure
```

Exact linear equivalent:

1. The checker detects a direct Heap-order violation.
2. Constant-time shape validation runs before record scanning.
3. The checker cannot prove allocation lifetime or unique ownership.
4. It cannot judge a real alert or security outcome.
5. Capacity 64 is a bounded teaching choice.
6. A later Dijkstra client must report insufficient capacity or use a
   separately validated larger design.
7. Silently dropping pending work invalidates a claimed complete result.
