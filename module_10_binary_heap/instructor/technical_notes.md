# Module 10 Technical Notes

[student/lab.c](../student/lab.c) is authoritative for the required lesson.
The separately built alert-record Heap and unsorted baseline are optional
references. Their allocation, ownership, status, stable-tie, and counter
contracts do not describe this source.

## Integer representation and comparison

`heap[10]` is fixed storage. `size` counts the active prefix.
`init_heap()` resets `size=0` and selects min mode; it does not zero storage.
`is_min_heap` is a flag. Nonzero selects `<=`; zero selects `>=`.
The non-strict comparator returns true when the first position can remain
above the second. `proper_parent(i,j)` returns the winning position and
handles `-1` before calling `comp`, so missing children are never indexed.
When valid values tie, the first position wins the local comparison.
This is not a stable arrival-order guarantee.

`parent(0)` and negative arguments return `-1`. A child's formula is
accepted only if its result is less than `size`. Call `left` and `right`
with valid nonnegative positions in normal traces. These helpers do not
constitute general argument validation.

## Local and whole-array repairs

`heapify_up(i)` swaps toward the root until its parent can stay above it.
`heapify_down(i)` selects the better existing child before comparing it
with the current position. It may stop with a non-sorted array because only
ancestor-to-descendant order is required.

`heapify()` starts at `parent(size-1)` and repairs internal nodes backward.
For zero or one value the initial index is `-1`, so the loop makes no calls.
Changing `is_min_heap` on a populated array requires `heapify()` before
relying on root order or performing ordinary add/remove operations.

`add` writes at old `size`, increments the count, and repairs upward.
`remove_root` saves `heap[0]`, decrements `size`, copies the last active value
to position 0, and calls downward repair. With a singleton the copy is a
self-copy. At size zero both children return `-1`; `proper_parent(0,-1)`
returns 0 without calling `comp`, so repair stops safely. The initial
removal still requires a nonempty heap. Empty removal is invalid.

Caller preconditions are `0 <= size <= 10`, `size < 10` for add, and
`size > 0` for remove. There is no rejection status, growth, allocation,
invariant checker, or built-in comparison counter. Use a test helper for
whole-heap checks; separate its scan from the repair's work.

## Current intervals and ID heaps

`toggle_info[id][2*epoch[id]]` and the following element are the current
on/off endpoints. `interval_size[id]` counts intervals, not endpoint cells.
The input must contain all IDs 0–9, with 1–5 intervals each. Use nonnegative
integer endpoints, on <= off, chronological disjoint intervals per ID
(previous off < next on), and closed intervals. The source validates none
of these assumptions. Increasing endpoints is needed for the advancement
argument; `-1` is reserved for no solution.

`max_on_heap.array` and `min_off_heap.array` each contain every ID exactly
once. Their capacities and live sizes are always ten. Their comparator
fields are function pointers: `_comp_on_max` places the greatest current
on-time at the root, and `_comp_off_min` places the smallest off-time there.
The swap fields call a heap-specific wrapper that also maintains its map.
`_proper_parent` takes positions and passes the stored IDs to the comparator.

The fixed helpers differ from the variable-size helpers. `_left(4)==9`,
`_right(4)==-1`, and positions 5–9 are leaves. `_heapify` starts at 5;
`_heapify_down` immediately ignores that leaf. Do not rewrite the source
as if its first loop index were 4 or its heap had a mutable size.

## Inverse maps and priority changes

The paired invariants are:

```text
max_on_heap.array[_max_heap_pos[id]] == id
min_off_heap.array[_min_heap_pos[id]] == id
```

`__swap__` exchanges two IDs and updates both moved IDs' positions in the
selected map. Swapping only array cells leaves order potentially correct
but makes the next lookup repair the wrong ID.

After an epoch change, all priorities except one remain unchanged.
`_reheapify(heap,i)` compares the changed entry with its parent. A root or
an entry that can stay below its parent repairs downward. A parent-order
violation repairs upward. One direction suffices when only that entry's
key changed and the heap was valid beforehand. A changed epoch updates
both its on and off keys, so both heaps must be repaired, using each heap's
own map. Off-times move later and commonly repair down in the min heap;
on-times move later and commonly repair up in the max heap.

## Search correctness and failure state

Let `L=max(current on)` and `R=min(current off)`. The chosen intervals have
a common closed point precisely when `L <= R`. The earliest point is L.
When `L > R`, the ID whose current off-time equals R cannot overlap the
currently latest start or any future start for that device. Advancing that
expired interval is necessary. Equal off-times may choose either tied ID;
retesting advances any other expired intervals as needed.

`all_on_time()` begins with `_init_heaps()`, resetting all epochs to zero,
installing callbacks, filling both ID arrays/maps, and heapifying both.
On a failed overlap it increments the earliest-off ID's epoch. If that
value reaches its interval count it returns `-1` before reading another
endpoint or repairing. The epoch is now exhausted and the heaps need not
reflect valid current keys. Do not call time accessors or continue checking
that state. A fresh `all_on_time()` restarts initialization.

## Work and storage

For generalized n, inspecting a root takes constant work, each up/down
repair follows at most a logarithmic-height path, and bottom-up heapify
is O(n): most positions lie close to leaves and move only a few levels.
Repeated insertion can instead take O(n log n). An invariant scan is O(n)
and is a separate testing action.

For n devices and A epoch advances, initialize both heaps in O(n), then
perform O(A log n) repair work and constant-time endpoint tests per step:
O(n + A log n) time and O(n) auxiliary ID/map/epoch storage, excluding
input intervals. The literal lab fixes n=10 and at most five intervals per
ID. Each ID has at most four successful advances, so there are at most 40
successful advances followed by success or one exhaustion attempt. All
arrays have fixed reserved storage; no heap allocation occurs.
