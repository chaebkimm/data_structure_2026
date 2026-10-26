# Module 10 Answer Key

Use [lab.c](../student/lab.c) and the current student evidence prompts.
The required code is supplied. These answers describe its integer Heap and
ten-device interval search.

## Complete tree and sentinels

Index 0 is the root. A non-root position i has parent `(i-1)/2`.
Its candidate children are `2*i+1` and `2*i+2`; children outside the live
prefix return `-1`. At size 6, index 2 has left child 5 and no right child.
`proper_parent(-1,-1)==-1`; a valid index wins against `-1` without
indexing the sentinel. `proper_parent` returns a position.

Min mode requires each parent value <= each child value; max mode reverses
the inequality. Neither rule sorts siblings or the full array. The flag
`is_min_heap` chooses a comparison rule and does not check order.

## Canonical insertion and removal

Start with `init_heap()` and add `7,3,5,1,9,4`:

| Added | Active prefix |
|---:|---|
| 7 | `[7]` |
| 3 | `[3,7]` |
| 5 | `[3,7,5]` |
| 1 | `[1,3,5,7]` |
| 9 | `[1,3,5,7,9]` |
| 4 | `[1,3,4,7,9,5]` |

The first removal saves 1, moves 5 from index 5 to index 0, and reduces size
to 5. Choose child 3 at index 1 over child 4 at index 2 and swap. Then stop
because children 7 and 9 can stay below 5. Result:
`[3,5,4,7,9]`. Complete drain returns `1,3,4,5,7,9`.

A singleton removal returns that value and leaves size 0. Its unconditional
`heapify_down(0)` stops without reading missing children. An empty initial
removal or eleventh insertion has no valid defined lab contract.

To change an existing min heap to max mode, set `is_min_heap=0` and call
`heapify()`. Rebuilding the original six-value min Heap produces `[9,7,5,1,3,4]`.
Bottom-up processing starts at `parent(size-1)`. A mode change alone leaves
old physical order intact.

## Interval trace

Use ID0 `[1,3],[7,10]`; ID1 `[2,5],[8,12]`;
IDs2–9 `[4,9]` each. All intervals are closed.

| Epoch change | Latest on | Earliest off | Overlap? | Next action |
|---|---:|---:|---|---|
| Initialized, all epochs 0 | 4 (a tied ID2–9) | 3 (ID0) | No | Advance ID0 |
| `epoch[0]=1` | 7 (ID0) | 5 (ID1) | No | Advance ID1 |
| `epoch[1]=1` | 8 (ID1) | 9 (a tied ID2–9) | Yes | Return 8 |

The full heaps store IDs, not endpoints. Reading a root ID must be followed
by its time accessor. Exact array order among tied times is not a service
policy; verify heap order, ID permutation, and both inverse-map identities.

For endpoint success change only ID1's second interval to `[9,12]`.
The answer is 9 because `9 <= 9`. For exhaustion use ID0 with only
`[1,3]` and IDs1–9 with `[4,9]`. Incrementing ID0 to its interval count
returns `-1` before another accessor call. Never inspect an exhausted ID's
current time. A fresh `all_on_time()` resets epochs and repeats the search.

## Three-target Cognitive Pause

Target 1 appends 1 at index 3, swaps with parent 1, then with parent 0.
The result is `[1,3,5,7]`. The caller checks `size<10` first.
Target 2 returns 1 and leaves `[3,5,4,7,9]`, as traced above; the full array
need not be sorted because only parent-child order is required.
Target 3 starts at bounds `(4,3)`, advances ID0, and reaches `(7,5)`.
Its changed epoch alters both endpoint keys. Repair positions come from
`_min_heap_pos[0]` and `_max_heap_pos[0]`, respectively.

## Why two heaps and two maps?

The max-on root supplies the latest chosen start. The min-off root supplies
the earliest chosen finish. Their comparison decides overlap in constant
time. After an epoch change, the ID remains in both heaps with new keys.
Both orders must be repaired. The same ID may occupy different positions,
so `_min_heap_pos` cannot locate it in the max heap. Every swap updates both
moved IDs in the selected inverse map.

`_reheapify` repairs up when the changed ID outranks its parent; otherwise
it repairs down. A root repairs down. This relies on only one changed key
and valid order before that change. Full reconstruction remains possible
but repeats more work.

## Correctness, tests, and costs

The latest on-time is the earliest possible common time. It works exactly
when it is no later than the earliest off-time. Otherwise the earliest-off
current interval cannot participate in a solution with any current or later
interval of the latest-on device. Advancing it cannot discard a solution.
If that ID has no later interval, no common time exists.

Required test evidence covers (1) integer min/max construction, insertion,
removal, duplicates, and one-child/singleton boundaries; (2) both heap/map
invariants and repair directions after epoch changes; (3) first-epoch
success, delayed success, endpoint equality, and exhaustion, with all ten
IDs populated. Additional scan checks are driver helpers, not lab APIs.

For generalized n, root read is O(1), repair is O(log n), bottom-up build is
O(n), and all-on search is O(n + A log n) for A advances. Input storage is
separate from O(n) auxiliary heaps/maps/epochs. The actual program reserves
fixed arrays for ten values/IDs and five intervals each. It does not grow,
allocate, return status enums, count comparisons, or guarantee stable ties.
