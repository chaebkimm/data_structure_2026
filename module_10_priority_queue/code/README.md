# Module 10 C Package

This package implements a stable minimum-priority Queue of small synthetic
alert records. A **minimum-priority Queue** returns the record with the
smallest priority number. **Stable** means that records tied on priority leave
in their arrival order.

## Public record and Queue

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

The Queue owns one unsorted dynamic array. Insertion appends at `data[size]`
and assigns `next_sequence`; callers do not choose sequence numbers. The
stable comparison rule is:

1. smaller `priority` first;
2. for equal priorities, smaller `arrival_sequence` first; and
3. `alert_id` does not affect order.

An extraction scans for that record, copies it to the output, and fills its
physical slot with the final live record. Therefore physical array order is
not the abstract Queue order.

## Representation and growth

Start with `AlertPriorityQueue queue = {0};`, then call
`alert_priority_queue_init(&queue)`. The all-zero state is valid and performs
no allocation.

Capacity grows only through:

```text
0 -> 4 -> 8 -> 16 -> 32 -> 64
```

The constant-time validator rejects every other positive capacity. Capacity
is retained after extraction, including after the Queue is drained. A drain
resets `next_sequence` to zero because no older live tie remains.

At 64 live records, insertion returns `ALERT_PRIORITY_QUEUE_FULL`. If a
nonfull, nonempty Queue has exhausted `SIZE_MAX` sequence values, insertion
returns `ALERT_PRIORITY_QUEUE_SEQUENCE_EXHAUSTED`. Full takes precedence over
sequence exhaustion.

The Queue owns its allocation. Do not shallow-copy a live Queue and do not
edit its public fields or records outside controlled tests.

## Failure and output promises

Every failed operation preserves all Queue fields and allocated slots.
`peek_min` and `extract_min` change their output only on success; their output
must be separate caller-owned storage, not a location inside `queue.data`.
A null output is rejected before Queue validation. Other operations validate
before reporting empty, full, sequence exhaustion, or allocation failure.

Growth uses a temporary `realloc` result. A failed growth therefore cannot
erase the owned pointer. Destroy releases storage and restores every field to
zero/NULL.

## Diagnostic comparison count

`comparison_count` counts calls to the complete record comparator:

- insert performs zero record comparisons;
- peek or extract on `n` records performs exactly `n - 1`; and
- validation, reset, initialization, and destruction perform none.

The counter saturates at `SIZE_MAX`; it never wraps to zero. Reset changes
only this diagnostic counter. The counter is instrumentation for experiments,
not extra work required by the Priority Queue abstraction.

For the seven-record canonical fixture, one peek performs six comparisons.
After resetting the counter, extracting all seven performs
`6 + 5 + 4 + 3 + 2 + 1 + 0 = 21` comparisons.

## Student-controlled work

`starter/alert_priority_queue.c` contains exactly three numbered tasks:

1. stable comparator and minimum-index scan;
2. failure-safe insertion and geometric growth; and
3. stable swap-with-last extraction.

`tests/test_student.c` contains exactly three additional test tasks. The
instructor supplies initialization, validation, peek, reset, destruction,
status names, core tests, extension tests, and the isolated safe autopsy.

## Cost

Let `n` be the number of live records.

- Insertion is amortized `O(1)`: occasional growth copies existing records.
- Peek-min is `O(n)` because the unsorted array must be scanned.
- Extract-min is `O(n)` for the scan and `O(1)` for swap-with-last removal.
- Validation, counter reset, and field updates are `O(1)`.
- Owned storage is `O(n)` and never exceeds 64 records.

## Build commands

From this `code` directory on Windows:

```powershell
# Starter scaffold: compiles, then tests fail until all TODOs are complete.
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1

# Instructor reference and private extension tests.
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target solution
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target solution -Extensions

# Student-authored tests and isolated autopsy.
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target starter -StudentTests
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target autopsy
```

The script selects Clang, GCC, or Microsoft C from `PATH`. `-Sanitize` adds
runtime memory checks where the selected compiler supports them.

With GNU Make:

```sh
make starter-core
make starter-student-tests
make solution-core
make solution-extension
make autopsy
```

The Makefile is intended for Git Bash, MSYS2, WSL, Linux, or macOS.
