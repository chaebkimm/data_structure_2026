# Module 10 — Five-Minute Cognitive Pause

Read the starting states with the instructor. Then use no notes or coding
tools for the three targets. Preserve the initial response when correcting.
A minimum Heap keeps each parent no larger than its children. A child
position exists only below `size`; `-1` is a missing position.

## Target 1 — Map and repair upward

Start with `heap=[3,7,5]`, `size=3`, `is_min_heap=1`. Predict `add(1)`.
Give the initial insertion position, every tested parent position, each
swap, and the final live array. State the capacity condition the caller
must check before this call.

Response: ________________________________________________________

## Target 2 — Choose the better child

Start independently with `heap=[1,3,4,7,9,5]`, `size=6`, `is_min_heap=1`.
Predict `remove_root()`. Give the return value, replacement value, new
size, each selected child, and the final live array. Explain why this
array need not be globally sorted. Then explain how removing a singleton
reaches size 0 without reading a missing child.

Response: ________________________________________________________

## Target 3 — Advance an interval in two Heaps

ID 0 has `[1,3],[7,10]`; ID 1 has `[2,5],[8,12]`; IDs 2 through 9 have
`[4,9]`. All epochs start at 0. Intervals include their endpoints.
State the latest start and earliest end, the ID advanced first, and the
next pair of bounds. Explain why both Heaps require repair even though
only one epoch changes. State how the ID's current position is found in
each Heap.

Response: ________________________________________________________

## Correct using evidence

Label corrections `position`, `order`, `child choice`, `missing child`,
`epoch`, or `inverse map`. Identify the exact code or observed state that
changed your answer. The source stores no arrival sequence or operation
comparison counter; do not invent those fields in a trace.

Correction: ______________________________________________________
