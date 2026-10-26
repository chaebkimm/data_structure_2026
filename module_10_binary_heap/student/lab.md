# Module 10 Lab — Binary Heaps and a Common On-Time

Use [lab.c](lab.c) as the source of truth. The functions are supplied.
Trace their state and write a separate test driver. The current lab uses
fixed arrays. The alert-record library in [code](../code/README.md) and the
scan baseline in `priority_queue_baseline/` are optional references.
Their allocation, stable arrival ties, status codes, and comparison counters
are not requirements of this lab.

## Build the supplied source

The file has no `main`. Use the module's current-lab targets:

```sh
make -C code lab-compile
make -C code core
make -C code student-tests
```

Record the commands and output. Add your original tests to the student driver
named by [code/README.md](../code/README.md). To write a standalone driver,
include `<assert.h>` and `"lab.c"`, then define `int main(void)`.
Compile that driver alone. Do not also compile `lab.c` separately when the
driver includes it. The supplied source may produce non-prototype warnings;
record those warnings without changing the source to conceal them.

## 1. Keep the next integer at the root

Start with `init_heap()`. It sets `size=0` and `is_min_heap=1`; it does not
clear the ten stored integers. Only `heap[0]` through `heap[size-1]` are live.
Call `add` for `7,3,5,1,9,4` in that order. Predict every array before running.

| Call | Live array after repair |
| --- | --- |
| `add(7)` | `[7]` |
| `add(3)` | `[3,7]` |
| `add(5)` | `[3,7,5]` |
| `add(1)` | `[1,3,5,7]` |
| `add(9)` | `[1,3,5,7,9]` |
| `add(4)` | `[1,3,4,7,9,5]` |

Explain the parent tests for `add(1)` and `add(4)`. Then call `remove_root()`.
It returns 1 and leaves `[3,5,4,7,9]`. Trace saving the root, decrementing
`size`, copying the former last value, choosing the better existing child,
and swapping downward. The live array is not globally sorted.

The helpers `parent`, `left`, and `right` return positions. A missing position
is `-1`. `proper_parent(i,j)` chooses the existing position whose value
belongs above the other; with two missing positions it returns `-1`.
`comp` uses `<=` for a minimum Heap and `>=` for a maximum Heap. Equal values
favor the first argument. No arrival sequence is stored and no stable
first-arrival guarantee is provided.

The caller must enforce `size<10` before `add` and `size>0` before
`remove_root`. These functions do not reject an invalid request. Do not run
an eleventh insertion or an empty removal to test rejection.

Test a singleton removal separately. It returns its value, sets `size=0`,
and still calls `heapify_down(0)`. Both child helpers return `-1`;
`proper_parent(0,-1)` returns 0 without reading a missing child, so repair
stops. A subsequent removal would be invalid.

## 2. Build bottom-up and change the ranking

Load `7,3,5,1,9,4` directly into the array and set `size=6` and
`is_min_heap=1`. Call `heapify()`. Its starting index is `parent(5)==2`.
Record the arrays after repairs from positions 2, 1, and 0. The result is
`[1,3,4,7,9,5]`.

Set `is_min_heap=0`, then call `heapify()` again. The result is
`[9,7,5,1,3,4]`. Changing the flag alone changes comparisons but does not
rearrange the array. Rebuild before asking for a root under the new rule.
Drain with guarded removals and check descending values. Also test an empty
and singleton `heapify()` and a parent with only a left child.

## 3. Find when all ten devices are on

Each ID from 0 through 9 has one to five closed intervals. A closed interval
includes both its on-time and its off-time. Store endpoint pairs in
`toggle_info[id]`, the interval count in `interval_size[id]`, and let
`epoch[id]` select the current pair. Load all ten IDs before calling the
algorithm. Use nonnegative times so return value `-1` denotes no answer.
Each interval has `on<=off`; an ID's intervals are listed in increasing,
non-overlapping order. Each prior off-time is strictly before the next
on-time. Input validation is the caller's responsibility.

Use this same fixture throughout the report:

| IDs | Intervals | `interval_size` |
| --- | --- | ---: |
| 0 | `[1,3]`, `[7,10]` | 2 |
| 1 | `[2,5]`, `[8,12]` | 2 |
| 2 through 9 | `[4,9]` | 1 |

The two `struct Heap_Full` arrays always contain all ten IDs. They contain
IDs, not copied times. `max_on_heap` ranks the selected on-times largest
first. `min_off_heap` ranks the selected off-times smallest first. Their
`comp` fields select comparison functions; their `swap` fields select swap
functions. A function pointer stores which function to call.

`_init_heaps()` resets all epochs to 0, installs both functions in each
Heap, initializes the IDs and position maps, and builds both Heaps.
It does not load intervals or reset `interval_size`.

At each step, let `L` be the largest current on-time and `R` the smallest
current off-time. These are the two roots' times. If `L<=R`, all current
intervals share `[L,R]`, and the earliest shared time is `L`.

| State | `L` | `R` | Action |
| --- | ---: | ---: | --- |
| epochs all 0 | 4 | 3 | advance ID 0 |
| `epoch[0]=1` | 7 | 5 | advance ID 1 |
| `epoch[0]=epoch[1]=1` | 8 | 9 | return 8 |

When `L>R`, the interval ending at `R` cannot reach the required start `L`.
Advance that ID's epoch. Update its position in both Heaps with `_reheapify`.
Do not remove the ID or shrink either ten-element Heap.

Record both complete ID arrays and both inverse maps after initialization
and after each successful advance. Verify for every ID `id`:

```text
max_on_heap.array[_max_heap_pos[id]] == id
min_off_heap.array[_min_heap_pos[id]] == id
```

Every swap must update the two IDs' map entries. `_reheapify` receives a
current array position, not an ID. It repairs downward at the root or when
the parent already outranks the changed value; otherwise it repairs upward.

## 4. Check boundaries and exhaustion

Write three original test groups:

1. Integer-Heap operations: exact arrays, both modes, ties, a lone left
   child, bottom-up construction, and guarded singleton removal.
2. Indexed repairs: change one ID's selected key, repair from its current
   map position, and assert Heap order plus both inverse maps. Exercise
   upward and downward repair using independent valid states.
3. Interval answers: immediate overlap, the two-advance fixture, equal
   endpoints, and exhaustion. Compare returned answers with a simple scan
   of all ten current intervals.

For equal endpoints, change ID 1's second interval to `[9,12]`; the answer
is 9. For exhaustion, use only ID 0's `[1,3]` interval while IDs 1 through 9
have `[4,9]`; the answer is `-1`. In the exhaustion path, `++epoch[id]`
reaches `interval_size[id]` before either repair. The selected epoch is then
out of range for a time read. Do not call `check_all_on`, time accessors, or
repairs on that terminal state. Load valid input and call `all_on_time()`
again; its initialization resets epochs and maps.

## Evidence to submit

Submit your driver, saved output, [worksheet](investigation_worksheet.md),
[evidence record](evidence_template.md), corrected
[Cognitive Pause](cognitive_pause.md), and [autopsy](binary_heap_autopsy.md).
Use the [rubric](rubric.md) to check completeness. Count one-path repair,
bottom-up construction, and complete verification separately. The supplied
`lab.c` remains unchanged.
