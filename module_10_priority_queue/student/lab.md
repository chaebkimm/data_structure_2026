# Stage E — C Lab: Stable Alert Priority Queue

## Purpose

Implement the unsorted dynamic-array backend described in the textbook.
The lab has exactly three implementation TODO concepts. Initialization,
peek, metric reset, destruction, status text, public tests, and a safe
autopsy are supplied.

All alerts are synthetic. Do not connect this program to live logs, alert
feeds, files, or networks.

## Public behavior

Smaller numeric priority leaves first. Equal-priority records leave in
arrival order. The Queue, not the caller, assigns arrival sequence.

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

The capacity sequence is 0, 4, 8, 16, 32, 64. A drained Queue retains its
allocation and capacity but resets `next_sequence` to 0.

## Status results

Read each named result before coding:

1. `ALERT_PRIORITY_QUEUE_OK` — the request succeeded.
2. `ALERT_PRIORITY_QUEUE_INVALID_ARGUMENT` — a required pointer is NULL.
3. `ALERT_PRIORITY_QUEUE_FULL` — 64 live records already exist.
4. `ALERT_PRIORITY_QUEUE_EMPTY` — no record can be reported or removed.
5. `ALERT_PRIORITY_QUEUE_ALLOCATION` — growth storage could not be obtained.
6. `ALERT_PRIORITY_QUEUE_SEQUENCE_EXHAUSTED` — the next sequence cannot
   advance safely.
7. `ALERT_PRIORITY_QUEUE_INVALID_STATE` — visible fields break a shape
   rule, including an initialization receiver that is not all zero.

Every failed operation preserves protected Queue state and caller output.

## Files and build

Edit only:

```text
code/starter/alert_priority_queue.c
code/tests/test_student.c
```

Do not edit the public header or supplied tests. From `code/`, use the
provided build script or equivalent Make targets:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -StudentTests
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target autopsy
```

Use warning-enabled compilation. Run the smallest relevant test after each
change. Preserve command and output evidence.

## TODO 1 — Comparator and minimum scan

Implement the stable comparator:

```text
a before b =
    a.priority < b.priority
    OR
    priorities equal AND a.arrival_sequence < b.arrival_sequence
```

Do not subtract priorities and do not compare alert IDs.

Then implement the minimum-index scan:

1. begin with live index 0 as the candidate;
2. compare each later live record once;
3. increment `comparison_count` once per comparator call;
4. keep the count at `SIZE_MAX` if it is already saturated; and
5. replace the candidate only when the later record comes before it.

A successful scan of size `n` adds exactly `n - 1` comparisons. A
single-record scan adds zero.

Checkpoint: trace the reveal fixture before running tests.

## TODO 2 — Insert and growth

Implement this order:

1. reject a NULL Queue;
2. validate its constant-time visible shape;
3. report full at 64 live records;
4. report sequence exhaustion before changing anything;
5. grow when `size == capacity`;
6. use a temporary allocation result and commit it only after success;
7. write `{alert_id, priority, next_sequence}` at index `size`;
8. increment size and sequence only after the write; and
9. return success.

Growth is 0 → 4 → 8 → 16 → 32 → 64. Insert performs zero record
comparisons. Allocation failure preserves every field and allocated slot.

Checkpoint: test the first insertion, fourth-to-fifth growth, and 64-record
boundary.

## TODO 3 — Extract with swap-last

Implement this order:

1. reject a NULL Queue or output;
2. validate visible shape;
3. report empty without changing output;
4. find the stable minimum using TODO 1;
5. copy that record to a local result;
6. move the final live record into the selected position when needed;
7. decrease size;
8. reset `next_sequence` to 0 if size became 0;
9. write the local result to caller output last; and
10. return success.

The output must not point anywhere inside the Queue's owned allocation.
That no-alias rule is a caller precondition; portable C cannot reliably
prove where every pointer originated.

Checkpoint: extract all canonical records and compare the exact physical
states in Stage C.

## Supplied-function boundaries

`alert_priority_queue_validate` checks field relationships in constant
time. Capacity must be exactly 0, 4, 8, 16, 32, or 64; another positive
capacity is invalid. Capacity 0 requires the complete all-zero state.
Validation cannot prove pointer liveness, allocation extent, record
contents, or unique ownership.

Successful `peek_min` scans and therefore changes only
`comparison_count`; it does not change records, size, capacity, sequence,
or storage identity. `alert_priority_queue_reset_comparisons` resets only
the metric. The metric saturates rather than wrapping.

`alert_priority_queue_destroy` releases storage and restores the all-zero
state. Do not shallow-copy a live owning struct.

## Exactly three student-authored test categories

Write exactly three numbered test functions:

1. **Mixed priorities and stable ties:** use IDs whose numeric order differs
   from both priority and arrival; assert complete output records.
2. **Growth and swap-scrambled storage:** cross capacities 4 and 8, perform
   extraction, insert again, and verify logical order despite changed
   physical order.
3. **Failure preservation:** prove protected output after empty access and
   complete state preservation at the 64-record full limit.

Before each test, write one sentence naming the claim. Three renamings of
the canonical fixture do not satisfy the requirement.

## Required workload evidence

Reset the comparison metric before each workload:

```text
insert-heavy: 32 append insertions
removal-heavy: preload 32 records, then extract all 32
```

The unsorted insertions make zero record comparisons. The removals make
`31 + 30 + ... + 0 = 496`. Compare on paper with a sorted array whose
minimum is at the removable right end: the chosen insert-heavy case can
require 496 comparisons and shifts, while its 32 removals need zero
record comparisons.

Explain which workload favors each backend.

## Safe autopsy and policy explanation

Complete `priority_queue_autopsy.md`. Predict before running the bounded
faulty program. It contains no deliberate invalid memory access.

Also explain:

- one starvation scenario;
- why clients cannot mutate active priority fields directly;
- how decrease-key differs from inserting a newer duplicate and ignoring a
  stale older entry; and
- why course ordering is not a real severity or fairness guarantee.

## Submission

Submit:

- completed three starter TODO concepts;
- exactly three student-authored test categories;
- warning-clean build and test output;
- canonical trace and comparison totals;
- completed evidence template;
- completed safe autopsy;
- sorted-versus-unsorted backend memo;
- starvation and mutable-priority explanation; and
- corrected Cognitive Pause.
