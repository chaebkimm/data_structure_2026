# Linked-List Autopsy — Recycle Before Detaching

Examine the index pool in [lab.c](lab.c). Use a paper trace first; the wrong
sequence below is not normal lab code. The old `code/autopsy` program
concerns a separate pointer-based library and is optional reference.

## 1. Predict the defect

The standalone list starts at 0:

```text
lnodes[0]={17,1}; lnodes[1]={23,2}; lnodes[2]={31,-1}
free_head=3; free chain 3→4→5→6→7→8→9→-1
```

A programmer attempts to remove index 1 in the wrong order:

```c
int victim = lnodes[0].next;
free_lnode(victim);                 /* wrong: still linked */
int removed = delete_next_lnode(0);
```

Predict whether the list still reaches 31 and whether an index is now
both active and free.

Prediction: _________________________________________________________

## 2. Locate the earliest broken rule

Record `lnodes[0].next`, `lnodes[1].next`, and `free_head` after each call.
Which caller precondition breaks first? How does recycling overwrite the
successor, causing deletion to follow the free chain instead of index 2?

Response: ___________________________________________________________

This is logical pool corruption. The array still exists: `free_lnode` does
not end the C lifetime of a slot. A memory sanitizer may report no error
because wrong accesses can stay within `lnodes[0..9]`.

## 3. Repair and verify

Reset to the valid starting state, then trace:

```c
int removed = delete_next_lnode(0);
if (removed != -1) {
    free_lnode(removed);
}
```

State both chains after each call. Why is the detached node's stale `next`
harmless while the caller holds it, but overwritten on recycling?

Response: ___________________________________________________________

## 4. Diagnose nearby errors

1. After correct recycling, what does a second `free_lnode(1)` do to
   `lnodes[1].next`? Does its range check prevent this?
2. In a separate list 0→2→-1, reverse the insertion writes for detached node 1. State the resulting self-link and lost successor.

3. A removed node is detached but never recycled. Can `new_lnode` find it? Distinguish this lost allocation from a free slot.
4. In a separate fresh pool, A owns 0(17) and B owns 1(23), both with next `-1`. A detaches and recycles 0. B prepends `new_lnode(8,1)`, which returns 0. An old A variable still equals 0. What does `lnodes[old_a].data` now read? On paper, show how assigning either data or next through `old_a` changes B. A range check passes; explain why it cannot establish ownership.
5. A linked Stack recycles its first node before saving its next. Which successor is lost when recycling overwrites that field? Give the safe save-data/save-next, update-first, recycle order.

Response: ___________________________________________________________

## 5. Regression evidence

Assert the repaired active/free chains and absence of repeated indices.
For reuse, assert the returned index, data, next field, and exact traversal order. Include two disjoint lists sharing the free chain, a safe LIFO drain, and no access through recycled caller indices.
Run the repaired version as a normal regression; use a bounded trace for
the wrong sequence.

- first broken precondition: _________________________________________
- exact repaired state: ______________________________________________
- test name and result: ______________________________________________
- why “it did not crash” is insufficient: ______________________________
