# Module 11 C Package

This package replaces Module 10's unsorted-array backend with a binary
minimum Heap while preserving the public Priority Queue record, object,
statuses, and operation signatures.

A **binary Heap** is a complete binary tree stored in one array. Complete
means every level is filled from left to right before a new level begins. It
is unrelated to the dynamically allocated memory that C programmers also
call “the heap.”

## Complete-tree indexes

For a live array index `i`:

```text
parent = (i - 1) / 2       when i > 0
left   = 2*i + 1
right  = 2*i + 2
```

The root is index zero. The stable comparison rule remains:

1. smaller `priority` first;
2. for equal priorities, smaller `arrival_sequence` first; and
3. `alert_id` does not affect order.

Heap order requires that no child precede its parent. It does not require the
whole array to be sorted.

## Representation and compatibility

`AlertRecord`, `AlertPriorityQueue`, all Module 10 statuses, the capacity
ladder `0, 4, 8, 16, 32, 64`, and all existing function signatures are
unchanged. Module 11 adds:

```c
AlertPriorityQueueStatus alert_priority_queue_is_min_heap(
    AlertPriorityQueue *queue,
    bool *out_is_min_heap
);
```

The constant-time validator checks field shape but deliberately does not scan
Heap order. The full checker examines every child-parent pair (`size - 1` for
a nonempty Heap and zero for an empty Heap), continues after finding a
violation, and returns `OK` plus `true` or `false`.
Malformed field shape returns `INVALID_STATE` without changing output or the
counter.

Callers must not edit live records or public fields. During development,
tests call the full checker after every successful mutation.

## Insert, peek, and extraction

Insertion appends at the next complete-tree position, then sifts the new
record upward while it precedes its parent.

Peek returns the root directly.

Extraction saves the root and repairs one downward path. At each level it:

1. chooses the better existing child;
2. compares that child with the final-record candidate; and
3. moves the child upward only when it precedes the candidate.

The code explicitly handles a parent with a left child but no right child.
Draining retains allocation/capacity and resets `next_sequence` to zero.

## Failures

Module 10 precedence and preservation remain:

1. reject a null output before Queue validation;
2. reject invalid field shape before empty or full;
3. report full before sequence exhaustion; and
4. report allocation failure only when growth is attempted.

Every failure preserves all fields, live and stale slots, prior output, and
the diagnostic counter. Growth uses a temporary `realloc` result.

## Comparison instrumentation

`comparison_count` counts stable record-comparator calls and saturates at
`SIZE_MAX`.

- Insert counts one comparison per parent test.
- Peek counts zero.
- Extract counts a sibling comparison when both children exist, then one
  selected-child/candidate comparison.
- `is_min_heap` adds zero comparisons when empty; otherwise it adds exactly
  `size - 1`.

The checker is debug instrumentation. Record the normal-operation delta
before calling it, then record the checker delta separately. Including a
full checker after every operation makes observed debug work `O(n)` and must
not be used to claim the normal Heap bound.

## Cost

- Peek is `O(1)`.
- Sift-up and sift-down are `O(log n)`.
- A growth insertion can take `O(n)` because reallocation may copy records;
  geometric growth makes that copying cost amortized.
- The full invariant checker is `O(n)`.
- Storage is `O(n)` and capped at 64 records.

## Student-controlled work

The starter contains exactly three numbered tasks:

1. full minimum-Heap checker;
2. insertion and sift-up; and
3. extraction and sift-down.

The student test file contains exactly three additional test categories.
Initialization, constant-time validation, stable comparison, peek, reset,
destruction, status names, core tests, extension tests, and the safe autopsy
are supplied.

## Build commands

From this `code` directory on Windows:

```powershell
# Starter scaffold: compiles, then tests fail until completed.
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1

# Instructor reference and extension tests.
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
runtime checks where the selected compiler supports them.

With GNU Make:

```sh
make starter-core
make starter-student-tests
make solution-core
make solution-extension
make autopsy
```

The Makefile is intended for Git Bash, MSYS2, WSL, Linux, or macOS.
