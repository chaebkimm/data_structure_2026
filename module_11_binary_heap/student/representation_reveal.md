# Stage B - Formal Name and Stored Form

Open this file only after preserving the Stage A inquiry.

## 1. Preserve the public promise

An **abstract data type (ADT)** states public behavior without requiring one
storage method. Module 10 built a stable minimum **Priority Queue ADT**.

A **record** groups named values called **fields**. Write an alert record as
`ID/P/S`: alert ID, priority, and arrival sequence. A smaller priority comes
first. When priorities tie, the smaller sequence comes first. A
**comparator** is that exact two-record rule. Alert ID never ranks a record.

A **backend** is one storage method used to provide the ADT. Module 10 used
an unsorted-array backend and scanned every live record to find the minimum.
**Live** means currently stored in the Queue. Module 11 preserves the same
public answer but changes the backend.

## 2. Make one compact tree shape

A **binary tree** is a hierarchy in which each node has at most two child
positions. A **node** is one stored item. The one top node is the **root**.
A **parent** is directly above a **child**.

A **complete binary tree** fills every level except possibly the final
level; the final level fills from left to right without a gap. A **level**
groups nodes the same number of links below the root.

This shape fits directly in an array. An **array** is a numbered row, and an
**index** is one position beginning at 0. Relationships are **implicit**,
meaning calculated instead of stored as pointers. A **pointer** is a value
holding a memory address.

For a live index `i`:

```text
left child  = 2*i + 1
right child = 2*i + 2
parent      = (i - 1)/2, only when i > 0
```

`*` means multiplication. `/` means whole-number division here, so any
remainder is discarded. A calculated child exists only when its index is
smaller than `size`, the live-record count.

## 3. Name the ordering rule

A **binary Heap** is a complete binary tree stored to support a priority
rule. This module uses a **minimum binary Heap**, shortened to **min-Heap**.

Its **Heap-order invariant** is a rule true at every direct relationship:

> No child may come before its parent under the complete comparator.

Therefore, no record can outrank every record above it, and the minimum is
at root index 0.

This is a **partial order**: only required parent-child relationships are
ordered. Siblings need not be ordered, and the whole array is not sorted.

## 4. Add by repairing upward

To `insert` is to add a record. First append the new record at index `size`.
**Append** means place at the end. This keeps the shape complete.

If the new record precedes its parent, exchange the two records. A **swap**
exchanges complete records. Continue toward the root. This repair is
**sift-up**.

Reveal insertions:

```text
50/4/0, 11/2/1, 80/3/2, 34/1/3, 62/2/4, 7/1/5
```

The resulting array is:

```text
34/1/3, 11/2/1, 7/1/5, 50/4/0, 62/2/4, 80/3/2
```

The ID 34 remains before ID 7 because their priority ties and sequence 3 is
earlier than sequence 5. IDs do not settle the tie.

## 5. Remove by repairing downward

`peek-min` copies index 0 without removing or comparing records.
`extract-min` removes and reports index 0.

Extraction saves the root, moves the final live record to a **candidate**,
meaning a record whose final position is undecided, and reduces the live
size. It then:

1. identifies the better existing child under the comparator;
2. compares that child with the candidate;
3. moves the child upward if it precedes the candidate; and
4. continues down that one route.

This repair is **sift-down**. If only a left child exists, compare that child
with the candidate. A right child cannot exist alone in a complete shape.

Extracting 34 from the reveal array moves 80 into the opening. Between
children 11 and 7, record 7 is better. The repaired active array is:

```text
7/1/5, 11/2/1, 80/3/2, 50/4/0, 62/2/4
```

## 6. Check every direct relationship

`alert_priority_queue_is_min_heap` is an **invariant checker**, meaning a
debug function that checks every live child against its parent. **Debug**
work helps locate or explain defects. For size `n`, it performs zero
comparisons when `n` is 0; otherwise, it performs exactly `n - 1`, even
after finding a violation. The symbol `n` means the current live-record
count.

The shared `comparison_count` **saturates** at `SIZE_MAX`: it stays at the
largest `size_t` value instead of wrapping to zero. `size_t` is C's
nonnegative whole-number type for sizes and indexes.

A **mutation** is an operation that changes the structure. During debugging,
call the checker after a successful mutation. That **instrumented run**
includes the checker's linear work. A **normal-operation count** records
only insert, peek, or extraction before calling the checker. Report these
two amounts separately. A full checker after every operation would make the
measured debug cycle linear even though one Heap repair follows only one
short route.

## 7. Separate four different ideas

- A **Heap** has complete shape and parent-child priority order. It is not
  globally sorted.
- A **binary search tree (BST)** places lower search keys in entire left
  subtrees and higher keys in entire right subtrees. A **subtree** is one
  node and all nodes below it. A Heap does not.
- A **sorted sequence** orders every record. A Heap orders only required
  parent-child pairs.
- C's **dynamic-memory heap** is the storage area from which `malloc` and
  `realloc` obtain allocations. An **allocation** is a storage block
  obtained while a program runs. A binary Heap is a data structure. One
  binary Heap may own an array obtained from dynamic memory, but the two
  meanings are not the same.

## 8. Prepare for the Cognitive Pause

Be ready to:

1. map one array to a complete tree and run the checker;
2. append and sift one new record upward; and
3. extract the root, choose the better child, and handle a missing right
   child.

Keep the vocabulary file closed until all three targets are preserved.
