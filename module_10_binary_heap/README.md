# Module 10 — Binary Heaps and Common On-Times

The required Week 10 lesson follows [`student/lab.c`](student/lab.c).
The supplied source first stores up to ten integers in a min/max heap.
It then keeps ten interval schedules in two heaps to find their earliest
common on-time. Students predict states, trace the supplied operations,
and write an assertion driver. The lab has no required implementation TODOs.

## Teaching materials

| Material | Purpose |
| --- | --- |
| [English textbook](student/textbook.md) · [Korean textbook](student/textbook_korean.md) | Explain the integer heap, then the interval application |
| [Class workbook](student/class_material.md) · [Concept slides](student/ppt_material.md) · [Lab slides](student/ppt_lab_material.md) | Organize prediction, discussion, and execution |
| [Investigation](student/investigation_worksheet.md) · [Linear version](student/investigation_worksheet_linear.md) | Record arrays, bounds, epochs, and position maps |
| [Representation reveal](student/representation_reveal.md) · [Vocabulary](student/vocabulary.md) | Connect each name to the current source |
| [Lab](student/lab.md) · [Evidence](student/evidence_template.md) · [Rubric](student/rubric.md) | Build one Week 10 submission |
| [Models](diagrams/binary_heap_models.md) | Show array/tree positions and interval overlap |
| [Lesson plan](instructor/lesson_plan.md) · [Chapter guide](../instructor_guide/chapter_10.md) | Deliver the lesson in 180 minutes |
| [Release manifest](release/release_manifest.md) | Package the current lab and student materials |

## Integer heap contract

`heap[10]` reserves ten integers. Only positions `0` through `size - 1`
are live. `init_heap()` sets `size = 0` and `is_min_heap = 1`; it does not
clear the array. With `is_min_heap == 1`, parents have values no greater
than their children. Set the flag to 0 for the reverse order. Changing the
flag alone does not rearrange values; call `heapify()` before using the new
root or making further heap operations.

`parent`, `left`, and `right` return positions. `-1` means a missing
relative. `comp(i,j)` compares values at positions, and
`proper_parent(i,j)` selects the position that should be above the other.
It handles missing positions before accessing the array. Equal values
favor the first argument. This local rule does not promise arrival-order
stability.

`add(data)` appends and repairs upward. `remove_root()` saves the root,
moves the last live value to position 0, reduces `size`, repairs downward,
and returns the saved value. Callers require `size < 10` before adding and
`size > 0` before removing. These functions do not reject overflow or empty
removal. Bottom-up `heapify()` repairs an already populated live prefix.
The global integer `is_min_heap` is a mode flag, not an invariant checker.

## Interval application contract

Load all ten IDs, 0–9, before calling `all_on_time()`. Each ID has one to
five closed intervals stored as alternating on/off times in
`toggle_info[id]`; `interval_size[id]` counts intervals. Use nonnegative
integer times, `on <= off`, and chronologically ordered, disjoint intervals
with `off[k] < on[k+1]`. The supplied source does not validate these inputs.

`epoch[id]` selects the current interval. `max_on_heap.array` stores the
ten IDs ranked by current on-time, largest first. `min_off_heap.array`
stores the same IDs ranked by current off-time, smallest first. These are
two fixed, full heaps, separate from the ordinary integer heap and its size.
Their comparator and swap function pointers select the appropriate behavior.
The inverse maps satisfy:

```text
max_on_heap.array[_max_heap_pos[id]] == id
min_off_heap.array[_min_heap_pos[id]] == id
```

Every swap updates its map. After an epoch changes, `_reheapify` repairs
that ID in both heaps using each heap's own position map. Equal time keys
do not establish an arrival-order or ID-order contract.

The roots give the latest selected on-time and earliest selected off-time.
Their intervals overlap when `max(on) <= min(off)`. Equality counts because
the intervals are closed. If they do not overlap, the algorithm advances
an ID with the earliest off-time. Exhausting that ID returns `-1`;
otherwise it repairs both heaps and tries again. A success returns the
earliest common on-time. Every call resets epochs and rebuilds both heaps.
After an exhausted return, an epoch equals its interval count; do not read
that interval or reuse the heaps without reinitializing.

The shared fixture has ID 0 intervals `[1,3],[7,10]`, ID 1 intervals
`[2,5],[8,12]`, and IDs 2–9 interval `[4,9]`. The bounds progress from
`(4,3)` to `(7,5)` to `(8,9)`, so the result is 8.

## Build, evidence, and costs

From the repository root:

```sh
make -C module_10_binary_heap/code lab-compile core student-tests
```

Tests include the actual `student/lab.c`. Extend
`code/tests/test_lab_student.c` with three original groups: integer heap
order and boundaries; dual-heap order and inverse positions; and interval
results including closed endpoints, exhaustion, and repeated calls.
Submit the driver, output, state traces, and corrected explanation as one
artifact. See [the lab](student/lab.md) for direct compiler commands.

For a generalized heap with `n` values, root inspection is `O(1)`, upward
or downward repair is `O(log n)`, and bottom-up construction is `O(n)`.
For `n` schedules and `a` successful interval advances, two-heap work is
`O(n + a log n)` with `O(n)` heap/map/epoch storage, in addition to interval
input. The actual arrays fix `n = 10` and at most five intervals per ID.
The textbook distinguishes these fixed bounds from the scalable analysis.

## Optional alert-queue reference

The `code/include`, `code/starter`, `code/solution`, old alert tests, and
[`priority_queue_baseline/`](priority_queue_baseline/README.md) retain the
separate alert Priority Queue library. Its dynamic growth, 64-record limit,
arrival-sequence ties, status values, ownership rules, comparison counter,
and `alert_priority_queue_is_min_heap` checker describe that optional API.
They are not requirements or guarantees of `student/lab.c`.
Its named reference targets remain available in [code/README.md](code/README.md).

Week 11 reuses the minimum-heap selection idea with ten pending node IDs,
current distances, and an inverse position map for in-place priority updates. Week 12 contrasts heap parent/child order with search-tree
ordering. Neither application changes this lab's fixed-array contract.
