# Module 7 C Package

This package implements a fixed-capacity circular Queue of synthetic integer
event codes. A Queue follows first-in, first-out (FIFO): the oldest queued
event is the first event removed.

## Representation

`EventQueue` owns one array allocated during initialization:

```c
typedef struct {
    int *data;
    size_t capacity;
    size_t head;
    size_t size;
} EventQueue;
```

Capacity never changes after successful initialization. `head` identifies the
oldest event when the Queue is nonempty. `size` distinguishes an empty Queue
from a full Queue.

For positive capacity, the next insertion index is derived:

```c
tail = (head + size) % capacity;
```

Do not evaluate this expression when capacity is zero. A full Queue rejects
the newest event with `EVENT_QUEUE_FULL`; it does not silently discard an
older event.

After the last event is dequeued, `head` returns to zero. This gives every
empty Queue one simple state.

## Supplied and student-controlled code

The instructor supplies:

- `include/event_queue.h`, the public representation and promises;
- initialization, fixed allocation, peek, destruction, and status names in
  the starter;
- `tests/test_core.c`, the visible required behavior;
- `tests/test_extension.c`, instructor-only stress tests; and
- the isolated bounded autopsy.

Students edit only:

- the three TODO bodies in `starter/event_queue.c`: validate, enqueue, and
  dequeue; and
- the three TODO test bodies in `tests/test_student.c`.

`solution/event_queue.c` is the instructor reference.

## Ownership and failures

Call `event_queue_init` only with an all-zero Queue variable or one previously
reset by `event_queue_destroy`. Capacity may be zero and may not exceed 64.
Positive capacity makes one exact allocation. There is no later growth or
shrinking.

Initialization failure leaves every Queue field unchanged. Enqueue,
dequeue, and peek validate before accessing storage. Every failure preserves
the Queue and its slots. Dequeue and peek also preserve their output on
failure.

The Queue owns its integer array. Do not shallow-copy a live Queue. A shallow
copy duplicates the owning pointer without duplicating the allocation.

## Build commands

From this `code` directory on Windows:

```powershell
# Expected to compile but fail until the three starter TODOs are completed.
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1

# Instructor reference.
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target solution
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target solution -Extensions

# Student-designed tests and isolated autopsy.
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target starter -StudentTests
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target autopsy
```

The script searches for Clang, GCC, and Microsoft `cl`. Add `-Sanitize` when
the selected compiler supports memory and undefined-behavior sanitizers.

With GNU Make:

```sh
make starter-core
make solution-core
make solution-extension
make starter-student-tests
make autopsy
```

## Test-only allocation control

Core and extension builds define `EVENT_QUEUE_TESTING`. This exposes
`event_queue_test_fail_next_allocation()`, which makes the next
positive-capacity initialization allocation fail once. Student tests do not
use this instructor test-only control.

## Cost

Initialization uses `O(capacity)` storage. Enqueue, dequeue, peek, validation,
and every index update take `O(1)` time: their work does not grow with the
number of queued events. No operation shifts the remaining events.
