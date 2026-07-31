# Stage E - C Lab: Stable Minimum Binary Heap

## Purpose

Replace Module 10's unsorted backend with a minimum binary Heap while
preserving the Priority Queue service rule and public operations. The lab
has exactly three implementation TODO concepts: checker, upward repair, and
downward repair.

All alerts are synthetic. Do not connect this program to live logs, feeds,
files, accounts, devices, or networks.

## Preserved public contract

Smaller `size_t` priority comes first. Equal priorities use smaller assigned
arrival sequence. Alert ID never ranks a record.

```c
typedef struct {
    int alert_id;
    size_t priority;
    size_t arrival_sequence;
} AlertRecord;

typedef struct {
    AlertRecord *data;
    size_t size;
    size_t capacity;
    size_t next_sequence;
    size_t comparison_count;
} AlertPriorityQueue;
```

The status order and existing Module 10 functions remain unchanged. Module
11 adds:

```c
AlertPriorityQueueStatus alert_priority_queue_is_min_heap(
    AlertPriorityQueue *queue,
    bool *out_is_min_heap
);
```

Capacity is exactly `0,4,8,16,32,64`. A drained Queue keeps its allocation
and capacity, resets `next_sequence` to 0, and retains the comparison count.

## Heap contract

For live index `i`:

```text
left = 2*i + 1
right = 2*i + 2
parent = (i - 1)/2 when i > 0
```

The live indexes 0 through `size-1` form a complete binary tree. No child
may come before its parent under priority-then-sequence comparison.

`comparison_count` includes:

- one call for every parent test during sift-up;
- one sibling comparison when sift-down has two children;
- one selected-child/candidate comparison at each sift-down level; and
- zero calls when `size` is 0, otherwise exactly `size-1` calls during a
  successful checker call.

The count saturates at `SIZE_MAX`.

## Files and build

Edit only:

```text
code/starter/alert_priority_queue.c
code/tests/test_student.c
```

Use the supplied warning-enabled build:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -StudentTests
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target autopsy
```

GNU Make users may run:

```text
make starter-core
make starter-student-tests
make autopsy
```

Preserve command and output evidence. Run the smallest relevant test after
each change.

## TODO 1 - Full min-Heap checker

Implement `alert_priority_queue_is_min_heap`:

1. reject a NULL output before Queue validation;
2. validate constant-time field shape;
3. begin with local result `true`;
4. for every child index 1 through `size-1`, calculate
   `(child-1)/2`;
5. count one complete record comparison;
6. set the local result false if the child comes before its parent;
7. continue checking all remaining children after a violation;
8. publish the Boolean output last; and
9. return `OK`.

A valid shape produces success plus `true` or `false`. A malformed shape is
a status failure and preserves output and comparison count. A successful
size-`n` check adds zero comparisons when `n` is 0; otherwise, it adds
exactly `n-1`.

Checkpoint: the locked five-record pause state returns true and adds four.

## TODO 2 - Insert with sift-up

Implement this order:

1. validate;
2. reject full before sequence exhaustion;
3. grow safely through the exact capacity ladder when needed;
4. prepare `{alert_id, priority, next_sequence}` locally;
5. begin at index `size`;
6. while nonroot, compare the candidate with its parent;
7. if the candidate comes first, move the parent down and continue upward;
8. otherwise stop;
9. place the complete candidate;
10. commit size and sequence; and
11. return success.

Use a temporary `realloc` result. Every failure preserves all fields and
established slots. Move complete records; never separate ID, priority, and
sequence.

Checkpoint: canonical insertion arrays end at:

```text
88,17,63,71,26,9,42
```

Normal insertion comparisons total 8.

## TODO 3 - Extract with sift-down

Implement this order:

1. reject NULL output before validation;
2. validate and reject empty;
3. save the root as local output;
4. reduce the candidate size by one;
5. if records remain, save the final live record as the candidate;
6. at each position, stop if no left child exists;
7. when a right child exists, compare the two children and select the one
   that comes first;
8. compare the selected child with the candidate;
9. move the child upward only when it comes first;
10. place the candidate at the final hole;
11. commit size and reset sequence only on complete drain;
12. publish output last; and
13. return success.

Never calculate or read a right-child record unless `right < new_size`.

Checkpoint: after metric reset, canonical outputs are:

```text
88,17,63,42,9,71,26
```

Normal extraction comparisons total 12.

## Checker instrumentation rule

During debugging, call the checker after each successful mutation. Record
two deltas:

```text
normal delta = count after operation - count before operation
checker delta = count after checker - count before checker
```

For the canonical lifecycle:

```text
build normal: 8
checks after each insertion: 21
build instrumented combined: 29

drain normal: 12
checks after each extraction: 15
drain instrumented combined: 27
```

The debug cycle is `O(n)` because the full checker is `O(n)`. A sift-up or
sift-down route is `O(log n)`. One insertion that grows storage may be
`O(n)` because records may be copied. With geometric capacity growth
(doubling here),
copying is **amortized**, meaning its total cost is spread across many
insertions; insertion is amortized `O(log n)`.

## Exactly three student-authored test categories

Write exactly three numbered test functions. State the claim before its
assertions.

1. **Sift-up, stable ties, and separate deltas:** require more than one
   upward move, use stable ties with nonordering IDs, assert the exact
   physical trace and returned records, and separate normal-operation from
   the checker's zero-if-empty, otherwise `size-1`, comparisons.
2. **Better child and missing right:** start from priorities
   `5,41,17,55,70`, extract the root, and prove the result is
   `17,41,70,55`, not a left-first result. Also test a repair position with
   a lone left child and verify exact comparisons.
3. **Growth, checker, and full preservation:** cross at least two growth
   boundaries, check Heap order after each mutation, fill all 64 slots, and
   prove a rejected insertion preserves every field and all live records.

Empty and singleton behavior, capacity boundaries, allocation failure,
saturation, malformed shape, ascending/descending input, and randomized
differential behavior are covered by supplied core/private tests. Three
renamed copies of one supplied fixture earn credit once.

## Safe autopsy

Complete `binary_heap_autopsy.md` before and after running the bounded
`faulty_sift_down.c`. Predict first. The defect chooses the left child
without comparing a better right child. All records and indexes remain
inside fixed bounds; the failure is logical, not an invalid memory access.

## Integrity and security scope

Call the checker after each mutation in debug/test work. A false result can
reveal silent Heap-order corruption that might misprioritize alerts.
Constant-time field validation must occur before record scanning so a
contradictory size cannot cause an out-of-range read.

The checker does not prove:

- pointer lifetime or unique ownership;
- alert authenticity or completeness;
- priority accuracy;
- fair staffing or absence of starvation;
- durable retention;
- thread safety; or
- overall system security.

## The 64-record boundary

The maximum of 64 keeps this teaching lab bounded. It is not a general
capacity proof for Dijkstra. A later client must either:

- prove its authorized input cannot need more pending records;
- use a separately tested larger or configurable Heap; or
- return an explicit insufficient-capacity failure without claiming a
  complete shortest-path result.

Never silently discard pending work.

## Submission

Submit:

- all three TODOs;
- exactly three student-test categories;
- core and student-test output;
- canonical build and drain traces;
- normal and checker comparison deltas;
- completed evidence record;
- completed safe autopsy;
- Heap/BST/sorted/C-memory contrast;
- 64-record boundary explanation; and
- corrected Cognitive Pause.
