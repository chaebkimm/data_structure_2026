# Chapter 10 Concept Slides — Heaps and Common On-Time

Use one numbered topic per slide or board scene. Ask for a prediction
before revealing each state. The [textbook](textbook.md),
[workbook](class_material.md), and [exact board states](../diagrams/binary_heap_models.md)
follow the same source and examples.

## 1. Can the next request stay ready?

Requests have urgency values `7,3,5,1,9,4`. Smaller values should leave
first. Compare rescanning an unsorted array with keeping the answer at one
known position. Attach the name Priority Queue to behavior under a ranking.
The source compares integers; it stores no stable arrival sequence.

## 2. How much order is enough?

Fill tree positions top to bottom and left to right. Attach the name
complete binary tree. Keep every parent no larger than its children.
Attach the name minimum Heap. Reveal `[1,3,4,7,9,5]`; ask why 5 may follow 9
in the array without breaking the rule. Contrast parent/child order with
sorted order and BST order.

## 3. How do positions replace pointers?

Show root 0, children 1/2, then 3/4 and 5. Derive parent `(i-1)/2`, left
`2*i+1`, right `2*i+2`. A child exists only below `size`. The helpers return
`-1` for a missing position. Distinguish ten reserved slots from live size.

## 4. Which path changes after insertion?

Reveal additions `7,3,5`, giving `[3,7,5]`. Add 1 at position 3; it swaps
with positions 1 and 0, giving `[1,3,5,7]`. Add 9, then 4, ending with
`[1,3,4,7,9,5]`. Attach the source name `heapify_up`.

## 5. Which child should replace the root?

Save root 1; move final value 5 to position 0; reduce size to 5. Choose
child 3 over 4. Reveal `[3,5,4,7,9]`. Attach `heapify_down`. Predict the
wrong-child violation. Explain the lone-left child and singleton stop.

## 6. Why start with the last parent?

Load `[7,3,5,1,9,4]` directly. Repair 2, then 1, then 0; reveal the same
minimum Heap. Attach bottom-up `heapify`. Change `is_min_heap=0` and
rebuild to `[9,7,5,1,3,4]`. The flag alone cannot rearrange values.

## 7. When are all devices on?

Show ID 0 `[1,3],[7,10]`, ID 1 `[2,5],[8,12]`, IDs 2–9 `[4,9]`.
Selected intervals share a time exactly when the latest start is no later
than the earliest end. Closed intervals include equal endpoints. A scan
can compute both bounds; two Heaps keep those bounds ready after updates.

## 8. Why keep the same IDs in two Heaps?

Store all ten IDs in each `Heap_Full.array`. Compare selected on-times
largest first in `max_on_heap`, and off-times smallest first in
`min_off_heap`. Explain function-pointer fields by naming the concrete
functions they select. Neither fixed-ten Heap uses the simple `size`.

## 9. Where did an ID move?

A key changes through `epoch[id]`, while swaps change its array position.
Show `array[pos[id]]==id` and both map writes during one swap. Distinguish
the positions passed to `_proper_parent` from IDs passed to its comparator.
`_reheapify` uses the current map position and chooses a repair direction.

## 10. Which interval can be discarded?

Reveal bounds `(4,3)`; advance ID 0. Reveal `(7,5)`; advance ID 1. Reveal
`(8,9)`; return 8. Repair the changed ID in both Heaps after each advance.
Explain why an interval ending before the latest start cannot contribute a
shared time, so discarding it preserves the first possible answer.

## 11. What happens at equality and exhaustion?

Change ID 1's second interval to `[9,12]`; answer 9 remains valid. For
exhaustion, ID 0 only `[1,3]`, others `[4,9]`; return `-1`. The final epoch
is outside its row's selected intervals. Do not read times until valid
reinitialization. All ten rows need one to five valid nonnegative closed
intervals in strictly separated chronological order.

## 12. Which work grows with the input?

Count path length before naming `O(log n)` repair. Root inspection is
`O(1)`, bottom-up construction `O(n)`, full order/map checking `O(n)`.
Generalized interval work is `O(n+r log n)` for `r` successful advances.
Then restate the actual fixed limits: ten integer slots, ten device IDs,
and five intervals per ID. The source has no dynamic growth or comparison
counter. Close with workbook evidence and one corrected explanation.
