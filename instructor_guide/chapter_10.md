# Chapter 10. Integer Heaps and a Shared On-Time

## Starting Question

> How can we keep the smallest or largest value ready, and use both choices
> to find when ten devices are all on?

Expected answer: arrange a complete binary tree in an array and preserve
parent-child order. One Heap supplies the latest start; another supplies
the earliest finish. The current intervals overlap when the latest start
is no later than the earliest finish.

## Why We Need This

A FIFO Queue chooses by arrival order. Selecting a numeric extreme needs a
different rule. A scan finds an extreme but repeats work on every selection.
A complete tree keeps an extreme at position 0 and repairs one affected path.
This is the Heap implementation of priority selection.

The required [lab.c](../module_10_binary_heap/student/lab.c) uses ten fixed
integer slots, not the optional alert-record library. `is_min_heap` chooses
min or max comparison. It is not a validation result. Equal values have no
stored arrival sequence. Functions do not reject full insertion or empty
removal; callers prevent those operations.

## Board Walkthrough

Add `7,3,5,1,9,4` in min mode. The final active prefix is
`[1,3,4,7,9,5]`. Removing the root returns 1 and leaves
`[3,5,4,7,9]`. Ask students to choose the better child before swapping and
to identify the remaining left-only child. Change to max mode, then call
`heapify()`; changing the flag alone does not restore order.

Load ID0 `[1,3],[7,10]`; ID1 `[2,5],[8,12]`;
IDs2–9 `[4,9]` each. Intervals include both endpoints. Initially the latest
on is 4 and the earliest off is 3. Advance ID0, giving 7 and 5. Advance
ID1, giving 8 and 9. Return 8.

Both full heaps store IDs. Accessors obtain the current endpoints through
`epoch[id]`. A function pointer stores the comparison operation chosen for
that Heap. Its swap operation updates an inverse map from ID to position.
After each epoch change, locate and repair that ID separately in both heaps.

## Neutral Questions

- Which positions are active, and when does a child return `-1`?
- Does `proper_parent` return an integer value or a position?
- Why can the min root be correct while the array is not sorted?
- What must happen after changing the min/max flag?
- Which ID prevents the current intervals from overlapping?
- Why are the two root values IDs rather than times?
- Which map belongs to each heap, and what changes during a swap?
- Why does a single epoch change require two repairs?
- When should `_reheapify` go up, and when should it go down?
- Why does equality of latest on and earliest off count as success?

## Vocabulary Boundary

Retrieve arrays, active prefix, fixed bounds, binary tree, parent, child,
root, and FIFO. Introduce priority selection, complete tree, min/max Heap,
comparison rule, bottom-up construction, repair up/down, closed interval,
epoch, function pointer, and inverse position map as needed. Explain the
new C callback declarations before tracing their calls.

Dynamic allocation and stable alert-record queues remain optional reference
material. Do not assess their ownership/status contracts in the current lab.
The ten-device source assumes 1–5 chronologically ordered disjoint valid
intervals per ID. Use nonnegative times. No input validator enforces this.

## Final Check

Students explain the parent-child invariant and both map identities, trace
one repair in each direction, justify the interval-advancement rule, and
state the return values for overlap, endpoint equality, and exhaustion.
For generalized n and A advances the search uses O(n + A log n) work and
O(n) auxiliary storage. The literal lab fixes ten IDs and at most five
intervals per ID. Use the
[180-minute plan](../module_10_binary_heap/instructor/lesson_plan.md)
and current [rubric](../module_10_binary_heap/student/rubric.md).
