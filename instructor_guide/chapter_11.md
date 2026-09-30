# Chapter 11. Priority Queues with a Binary Heap

## Starting Question

> "To process urgent alerts first, but keep arrival order for alerts with the same urgency, what rule do we need? How can we follow that rule without scanning every alert?"

**Expected Answer:** First compare priority. If priorities match, compare successful insertion order. Then keep the first record in a fixed position and repair only the path affected by insertion or removal. Picking the smaller priority number first is the rule for this chapter.

## Why We Need This

A normal queue takes out the first arrived value first. It cannot move an urgent alert ahead of earlier alerts. Comparing only priority leaves the order of equally urgent alerts undecided.

We need a behavioral rule for inserting, inspecting, and removing records. Compare priority first. For a tie, compare successful insertion order, called arrival order. This is a stable minimum priority queue. `insert` adds a record, `peek-min` inspects the first record, and `extract-min` removes it. The rule does not prescribe a storage layout.

An unsorted array can follow this rule by checking every record before choosing the first one. Adding a record is easy, but each removal repeats the full search. Students first read the supplied array baseline and count its comparisons. They do not implement a separate baseline assignment.

To avoid the repeated scan, keep the first record at array position 0. Fill the array level by level without gaps. This is a complete binary tree. Require every parent to come before its children under the same priority-then-arrival comparison. This is a min-heap. After adding or removing one record, only one path can need repair.

In week 10, the priority-queue contract, the supplied unsorted-array baseline, and the student-written binary heap form one unit. Students submit their heap code and comparison results once. Retrieve array growth and failure preservation from the hash-table scaffold in Chapter 10; do not require another growth implementation from scratch.

## Board Walkthrough

### Establish the priority-queue contract with the supplied baseline

Use the unsorted array exactly as supplied. Write each record as `ID/P/S`. `P` is priority and `S` is successful insertion order. Compare `P` first, then `S`.

```text
71/3/0, 88/1/1, 42/2/2, 17/1/3,
26/4/4, 9/2/5, 63/1/6
```

Scan the array from the left and underline the current first candidate.

* Among the seven alerts, which one will be announced first?
* After taking out 88 and moving 63 to its empty spot, which alert is next?
* When taking out all seven records, how many new comparisons will we make?

| State Looked At | First Candidate |
| --- | --- |
| Start | `71/3/0` |
| After comparing with 88 | `88/1/1` |
| After comparing with 42, 17, 26, 9, 63 | `88/1/1` |

The first `peek-min` makes 6 comparisons. After removing 88, the physical ID array is `[71,63,42,17,26,9]`. The next alert is 17. Its priority ties with 63, but its arrival order 3 precedes 6. Array position does not decide the tie.

Reset the comparison count to 0. Extracting all seven records makes 21 new comparisons:

```text
6 + 5 + 4 + 3 + 2 + 1 + 0 = 21
```

Including the initial `peek-min` gives 27 comparisons. Keep the counter boundary explicit when comparing implementations.

### Keep the same contract with a binary heap

Insert the same records in the same arrival order. Reveal the ID array one line at a time:

```text
[71]
[88,71]
[88,71,42]
[88,17,42,71]
[88,17,42,71,26]
[88,17,42,71,26,9]
[88,17,63,71,26,9,42]
```

Empty that heap:

```text
88 -> [17,42,63,71,26,9]
17 -> [63,42,9,71,26]
63 -> [42,71,9,26]
42 -> [9,71,26]
9  -> [71,26]
71 -> [26]
26 -> []
```

Ask these questions before showing the next state:

* When we add 17 to `[88,71,42]`, which path's relationships do we check?
* If we take out 88 and move 42 to position 0, which child do we compare with first?
* If we check the heap rule for all 7 records, how many parent-child comparisons do we make?
* Why do the baseline and heap remove the records in the same order despite their different arrays?

## Common First Thoughts

* "Smaller priority numbers are always more urgent." The direction is a program rule.
* "For equal priorities, choose the leftmost array record." Arrival order decides the tie, independently of position.
* "An unsorted array cannot follow a priority rule." A full scan can find the first record under that rule.
* "Taking out one item takes one comparison." The baseline compares its candidate with `n - 1` other records.
* "The entire heap array is sorted in processing order." The invariant only orders each parent before its children.
* "An insertion requires fixing every branch." Only the new record's ancestor path can need repair.
* "Moving down always moves the left child up." Compare both children and choose the one that comes first.
* Students may count full heap validation as part of one insertion or removal. Keep these measurements separate.

## Neutral Questions

* Which record fields decide priority, and in what order?
* How do the positions and arrival orders of 63 and 17 differ?
* How does the baseline scan count change with the number of remaining records?
* Which parent-child relationship could have become invalid in this operation?
* Which child comes first under the same comparison rule?
* Where did you count repair comparisons, and where did you count validation comparisons?
* How does the balance of insertions, inspections, and extractions affect your choice of storage?

## Vocabulary Rules

**Words we can use:** Array-based list, size and capacity, array growth and failure preservation from Chapter 10, queue arrival order, array position, parent, child, and root.

**Names we will introduce in this chapter:** Priority queue behavioral rule, priority, arrival order, stable tie-breaking, comparison rule, minimum priority queue, `insert`, `peek-min`, `extract-min`, unsorted-array baseline, complete binary tree, min-heap, move up (bubble up), and move down (bubble down).

**Words we won't use yet:** The path-cost procedure in Chapter 12 or other heap shapes. Establish the contract before introducing the heap representation.

## Final Check

> "Why do 88, 17, and 63 leave in that order in both implementations? How does the heap avoid the baseline's full scan?"

**Minimum Expected Answer:** Priority 1 comes first; arrival orders 1, 3, and 6 decide the tie. The baseline scans the remaining records, making `6+5+4+3+2+1+0 = 21` comparisons for seven extractions. The heap keeps the first record at the root through the complete shape and parent-child rule. Only one affected path needs repair after insertion or removal.
