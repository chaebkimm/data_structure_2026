# Chapter 10 Lab Slides — Trace the Supplied Source

Use the [lab](lab.md) for the full assignment. The source is [lab.c](lab.c).
Keep one state per scene and distinguish IDs, positions, and values.

## 1. Which source are we executing?

Build the current-lab targets described in [code/README.md](../code/README.md).
The supplied lab has no `main`. A driver includes the lab once and supplies
`int main(void)`. Do not link another compiled copy of the included source.
Record compiler warnings and leave the source unchanged.

## 2. What does initialization reset?

`init_heap()` sets size 0 and minimum mode; stored integer slots remain.
Load the six values using guarded additions. Show the live prefix after
each call. Capacity is ten, and add/remove do not check their preconditions.

## 3. What does `proper_parent` return?

Evaluate two valid positions, one missing position, and two missing
positions. Show that it returns a position, not a value. Equal values
favor the first argument. Trace the two upward swaps caused by `add(1)`.

## 4. Why does singleton removal stop safely?

Drain a valid singleton once. Show `--size` reaching zero, the same slot's
value copied to root, both children missing, and `proper_parent(0,-1)==0`.
The source stops without a missing-child read. Another removal is invalid.

## 5. How do we test bottom-up building?

Load `[7,3,5,1,9,4]` and trace positions 2, 1, 0. Check Heap order after
the full build. Change to maximum mode and rebuild before reading its root.
Write independent assertions for exact values and monotone drain order.

## 6. Which fields hold interval input?

Load endpoint pairs into `toggle_info[10][10]` and counts into
`interval_size[10]`. `_init_heaps()` resets epochs and both ID/map arrays;
it does not load or validate the input. Show the two endpoint lookups
using `2*epoch` and `2*epoch+1`.

## 7. Which arguments are positions and which are IDs?

Read `_proper_parent`: it accepts positions, fetches stored IDs, then calls
the selected comparator with those IDs. Read `__swap__`: swap array IDs and
update both inverse-map entries. Assert `array[pos[id]]==id` for all IDs.

## 8. What changes after one epoch advance?

Use the shared fixture. Initially bounds are `(4,3)`. Advance ID 0, then
repair its minimum-off position and maximum-on position using separate
maps. Bounds become `(7,5)`. Repeat for ID 1; bounds become `(8,9)`.
Call `all_on_time()` on valid loaded input and assert answer 8.

## 9. Which boundary is a valid test?

Assert immediate overlap, equality at 9, and exhaustion returning `-1`.
Do not read times after exhaustion; the epoch now equals its interval
count. A new `all_on_time()` call initializes epochs/maps for another valid
input. Do not run empty removals or full insertions as rejection tests.

## 10. What evidence should a test print?

Submit three original test groups: integer operations, indexed repairs,
and interval answers. Check exact arrays where specified, every Heap-order
relationship, both inverse maps, and an independently computed answer.
Attach the commands and results to the [evidence record](evidence_template.md).
Explain one-path work, bottom-up work, and diagnostic scans separately.
