# Stage E — Lab: Implement and Test a Fixed Circular Queue

## Goal

Complete three functions so a fixed-capacity Queue preserves FIFO arrival
order without shifting items. Then write three focused tests and record
reproducible evidence.

A **compiler** translates C source into a runnable program. A **test** runs a
case and checks an expected result. **Reproducible evidence** gives enough
detail for another person to repeat the check. A `TODO` label marks an
unfinished section that the student must complete.

## 1. Work only in the student files

Read:

- `code/include/event_queue.h` — public type, statuses, and contracts;
- `code/README.md` — package and build guide;
- `code/starter/event_queue.c` — supplied code plus three `TODO` sections;
  and
- `code/tests/test_student.c` — three student-test `TODO` sections.

Edit only:

1. `event_queue_validate`;
2. `event_queue_enqueue`;
3. `event_queue_dequeue`; and
4. the three `TODO` test sections in `test_student.c`.

Initialization, allocation, `peek`, destruction, and status-name text are
supplied. Do not edit the public type, grow the array, add a tail field, or
shift items.

## 2. Keep the representation contract visible

```c
typedef struct {
    int *data;
    size_t capacity;
    size_t head;
    size_t size;
} EventQueue;
```

The maximum capacity is `EVENT_QUEUE_MAX_CAPACITY`, which is 64. A
positive-capacity Queue owns exactly one fixed allocation. A capacity-zero
Queue is the all-zero state.

For `capacity > 0`:

```text
tail = (head + size) % capacity
physical index of logical item k = (head + k) % capacity
```

Never evaluate `% capacity` when capacity is zero. A removed slot may retain
a stale value. `head` and `size`, not old slot contents, determine the live
items.

## 3. TODO 1 — validate

**Validation** means checking whether visible fields follow the invariant.
Return:

- `EVENT_QUEUE_INVALID_ARGUMENT` for a `NULL` Queue pointer;
- `EVENT_QUEUE_INVALID_STATE` when a visible rule is broken; or
- `EVENT_QUEUE_OK` when the visible rules hold.

Check the rules in a safe order:

1. `capacity <= 64` and `size <= capacity`;
2. capacity zero requires `data == NULL`, `head == 0`, and `size == 0`;
3. positive capacity requires `data != NULL`;
4. an empty positive-capacity Queue requires `head == 0`; and
5. a nonempty Queue requires `head < capacity`.

The function must not change the Queue. It cannot prove from field values
alone that a non-NULL pointer is live, large enough, or uniquely owned.

## 4. TODO 2 — enqueue

Implement this contract:

1. validate before accessing storage;
2. return the validation status if validation fails;
3. if `size == capacity`, return `EVENT_QUEUE_FULL`;
4. otherwise derive tail, store the event there, and increase `size` last;
5. return `EVENT_QUEUE_OK`.

A full failure must preserve the pointer, fields, and every physical slot.
The course policy rejects the newest attempted event. It never discards an
older event silently.

## 5. TODO 3 — dequeue

An **output location** is caller-provided storage for a result. Implement
this contract:

1. reject a `NULL` output with `EVENT_QUEUE_INVALID_ARGUMENT`;
2. validate before reading storage;
3. return `EVENT_QUEUE_EMPTY` before reading if `size == 0`;
4. save the front value;
5. calculate the new size and head;
6. if the removal makes the Queue empty, put it into its one required form
   by setting head to 0;
7. otherwise advance head circularly;
8. store the new field values, write the output last, and return
   `EVENT_QUEUE_OK`.

The output must not point inside the Queue's allocation. Every failed
dequeue preserves both the Queue and the caller's previous output value.

## 6. Use the capacity-four checkpoint

Run this exact sequence:

```text
enqueue 31, 8, 47, 19
dequeue twice
enqueue 62, 5
attempt enqueue 90
dequeue until empty
```

Required checkpoints:

- the first two outputs are 31 and 8;
- before attempting 90, physical storage is `[62, 5, 47, 19]`,
  `head == 2`, `size == 4`, tail is 2, and logical order is
  `47, 19, 62, 5`;
- event 90 is rejected with `EVENT_QUEUE_FULL`, with all state unchanged;
- draining reports `47, 19, 62, 5`; and
- the final empty state has `head == 0` and `size == 0`.

## 7. Write the three student tests in order

Complete the existing functions; do not replace their category or order.
Every successful initialization must be matched by destruction on every
return path.

### Test 1: FIFO, including capacity 1

Show that the earliest event leaves first. Include a capacity-one Queue that
becomes full, drains, returns to the required empty form, and can be reused.

### Test 2: wrap-around plus repeated fill/drain

Force insertion to reuse index 0 after the physical end. Then perform
another fill/drain cycle so the test checks repeated use, not one lucky
state.

### Test 3: full/empty failure preservation

Use one Queue and prove both boundaries in this one test function:

1. Fill the Queue with known events. Record the `data` pointer, `capacity`,
   `head`, and `size` as separate test values. Copy all established slot
   integers into a separate plain integer array.
2. Attempt one more enqueue. Check `EVENT_QUEUE_FULL`, then prove every
   field and established slot is unchanged.
3. Drain the Queue completely. Its former values are now stale physical
   values.
4. Give the output a known prior value. Again record each field separately
   and copy the stale slot integers.
5. Attempt `peek` or `dequeue`. Check `EVENT_QUEUE_EMPTY`, then prove every
   field, stale slot, and the prior output value is unchanged.

Do not copy the positive-capacity `EventQueue` struct. The recorded pointer
and numbers are observations for comparison, not a second Queue owner.

For each test, write one sentence naming the claim that would fail if the
implementation were wrong.

## 8. Build and run

From the `module_07_queue/code` directory in PowerShell:

```powershell
# Supplied core tests; expected to fail before the TODOs are complete.
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1

# Your three tests.
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target starter -StudentTests

# Optional memory and undefined-behavior checks when supported.
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target starter -Sanitize

# Isolated, bounds-guarded autopsy.
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target autopsy
```

With GNU Make, the matching commands are:

```text
make starter-core
make starter-student-tests
make autopsy
```

A **compiler warning** points out code that may be mistaken. Keep the
warning-enabled flags already supplied. A **sanitizer** is a tool that can
detect some invalid memory or arithmetic behavior while a program runs.
Record the compiler, command, result, and any warning or sanitizer output.

## 9. Evidence checklist

- [ ] All supplied core tests pass.
- [ ] The three student tests pass and state distinct claims.
- [ ] Capacity 0 and capacity 1 are handled without division by zero.
- [ ] The capacity-four physical and logical states are exact.
- [ ] Full and empty failures preserve required state and output.
- [ ] Removing the final item sets `head` to 0 as the required empty form.
- [ ] No operation shifts items or changes capacity.
- [ ] Every owned allocation is destroyed once; no live Queue is
      shallow-copied.
- [ ] The Queue Autopsy records prediction, observation, first broken rule,
      repair idea, and regression test.

## 10. Cost and scope

Validation, enqueue, dequeue, and peek each use `O(1)` time, meaning fixed
work independent of Queue size. Initialization uses `O(capacity)` storage.
The examples use synthetic integer codes. Passing these tests demonstrates
the stated data-structure contract; it does not prove that a real monitoring
system has enough capacity or the right retention policy.
