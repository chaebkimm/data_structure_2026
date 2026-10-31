# Module 10 Instructor Lesson Plan — Integer Heaps and Shared On-Time

The required source is [student/lab.c](../student/lab.c). Its functions are
supplied. Students trace the functions and write a driver and three focused
test groups. The alert-record library and
[linear baseline](../priority_queue_baseline/README.md) are optional references.
Use one Week 10 submission.

## 180-minute sequence

| Minutes | Activity and evidence |
|---:|---|
| 0–15 | Retrieve FIFO, then choose the smallest or largest integer. Contrast a scan with keeping an extreme at index 0. |
| 15–35 | Map the complete tree, active prefix, parent/child formulas, and `-1` missing-position sentinel. |
| 35–55 | Trace `comp`, `proper_parent`, swaps, `heapify_up`, and `add`. Preserve the first prediction. |
| 55–75 | Trace `remove_root`, both-child choice, left-only child, and singleton removal. |
| 75–90 | Change `is_min_heap`, explain why order is stale, and run bottom-up `heapify`. |
| 90–100 | Complete the three-target [pause](../student/cognitive_pause.md) and label corrections. |
| 100–120 | Introduce ten devices, closed on/off intervals, epochs, and the overlap test. |
| 120–140 | Trace the two ID heaps, comparator/swap function pointers, and inverse position maps. |
| 140–160 | Trace `_reheapify` in both directions and `all_on_time`, including exhaustion. |
| 160–175 | Run tests, verify state and map invariants, and explain generalized work and fixed storage. |
| 175–180 | Submit one evidence record and one corrected explanation. |

## Before class

Run the current lab checks from [code/README.md](../code/README.md). Prepare
integer cards and ten ID cards. Use valid input only: `0 <= size <= 10`, no
empty root removal, no insertion into ten live positions, and all ten IDs
with one through five ordered valid intervals each. The code does not
validate those conditions. Define endpoints as inclusive and use
nonnegative times so `-1` remains an unambiguous failure result.

Do not assign allocation, dynamic growth, alert arrival sequences, statuses,
or a comparison counter. No such fields appear in the current lab. A test
helper may scan parent-child pairs, but it is not a supplied lab API.

## Board example: integer heap

Use arrivals `7,3,5,1,9,4`. After each `add`, preserve the active prefix:

```text
[7]
[3,7]
[3,7,5]
[1,3,5,7]
[1,3,5,7,9]
[1,3,4,7,9,5]
```

First removal returns 1 and leaves `[3,5,4,7,9]`. Complete draining returns
`1,3,4,5,7,9`. Ask why neither sibling order nor the entire array must be
sorted. Set max mode only in a separate experiment or rebuild before the
next operation. Changing the flag changes the comparison rule immediately;
it does not move stored integers.

## Board example: ten simultaneous devices

Load these intervals before calling `all_on_time`:

| ID | Closed intervals |
|---:|---|
| 0 | `[1,3]`, `[7,10]` |
| 1 | `[2,5]`, `[8,12]` |
| 2–9 | `[4,9]` each |

Initially `max(on)=4` and `min(off)=3`, so the current choices do not overlap.
Advance ID 0: `max(on)=7`, `min(off)=5`. Advance ID 1:
`max(on)=8`, `min(off)=9`. The earliest common time is 8. Trace both repairs
following each single epoch change. Require `array[pos[id]] == id` in each
heap after every swap.

Ask students to explain why a device ending at the earliest off-time must
advance when that time is before the latest on-time. Future intervals of
other devices cannot rescue that expired interval. Equality is success:
closed intervals sharing one endpoint overlap.

## Common misconceptions

- `is_min_heap` is a mode flag, not a checker result.
- `proper_parent` returns a position, not a value.
- The basic comparator receives positions. The full-heap comparator receives IDs.
- A root ID must be passed to `get_on_time` or `get_off_time` to obtain a time.
- Equal values do not acquire an arrival sequence or guaranteed FIFO policy.
- Advancing one epoch changes that ID's priority in both heaps.
- Each heap needs its own map because their physical orders differ.
- `_init_heaps` resets all epochs; every `all_on_time` call restarts the search.
- Exhaustion increments an epoch to its count and returns before another time read.
  The exhausted state is not a valid continuation; start again through `all_on_time`.

## Submission and calibration

Use the current [rubric](../student/rubric.md). Require a driver, output,
three original test groups, integer and interval traces, map checks, caller
preconditions, cost reasoning, and a labeled correction. Students need not
change supplied `lab.c`. Accept tables, diagrams, prose, typed or spoken
explanations with equivalent evidence. The optional reference library has a
separate API and does not enlarge the required artifact.
