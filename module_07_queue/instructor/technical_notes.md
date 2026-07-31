# Instructor Technical Notes — Module 7 Queue and Circular Buffer

## Source-of-truth contract

The production model is a Queue abstract data type backed by one owned
contiguous allocation. **Contiguous** means the event-code slots occupy one
unbroken memory region. Successful initialization chooses a capacity once;
enqueue and dequeue neither grow nor shrink it.

The public behavior is FIFO: first in, first out. Physical array order may
differ from logical Queue order after wrap-around.

The exact public maximum is:

```c
#define EVENT_QUEUE_MAX_CAPACITY 64U
```

The exact public field order and types are:

```c
typedef struct {
    int *data;
    size_t capacity;
    size_t head;
    size_t size;
} EventQueue;
```

`data` is the Queue-owned allocation. `capacity` counts available physical
slots. `head` is the physical index of the oldest event when `size` is
positive. `size` counts logically waiting events. There is no stored tail
field.

The exact public status order is:

```c
typedef enum {
    EVENT_QUEUE_OK = 0,
    EVENT_QUEUE_INVALID_ARGUMENT,
    EVENT_QUEUE_LIMIT,
    EVENT_QUEUE_FULL,
    EVENT_QUEUE_EMPTY,
    EVENT_QUEUE_ALLOCATION,
    EVENT_QUEUE_INVALID_STATE
} EventQueueStatus;
```

The exact public declarations are:

```c
EventQueueStatus event_queue_init(
    EventQueue *queue,
    size_t capacity
);

EventQueueStatus event_queue_validate(
    const EventQueue *queue
);

EventQueueStatus event_queue_enqueue(
    EventQueue *queue,
    int event_code
);

EventQueueStatus event_queue_dequeue(
    EventQueue *queue,
    int *out_event_code
);

EventQueueStatus event_queue_peek(
    const EventQueue *queue,
    int *out_event_code
);

void event_queue_destroy(EventQueue *queue);

const char *event_queue_status_name(EventQueueStatus status);

#ifdef EVENT_QUEUE_TESTING
void event_queue_test_fail_next_allocation(void);
#endif
```

Every `int` is a valid event code. The Queue does not reserve a sentinel
value and does not rank or interpret codes.

## Exact status-name behavior

`event_queue_status_name` returns:

| Status | Exact text |
|---|---|
| `EVENT_QUEUE_OK` | `ok` |
| `EVENT_QUEUE_INVALID_ARGUMENT` | `invalid argument` |
| `EVENT_QUEUE_LIMIT` | `requested Queue capacity exceeds maximum` |
| `EVENT_QUEUE_FULL` | `Queue is full` |
| `EVENT_QUEUE_EMPTY` | `Queue is empty` |
| `EVENT_QUEUE_ALLOCATION` | `allocation failed` |
| `EVENT_QUEUE_INVALID_STATE` | `Queue representation is invalid` |
| Unknown enum value | `unknown EventQueueStatus` |

Status categories must remain distinct:

- a missing required pointer is an invalid argument;
- an init request above 64 is a limit result;
- enqueue on a valid full Queue is full;
- dequeue or peek on a valid empty Queue is empty;
- failure of the one initialization allocation is allocation;
- contradictory visible fields are invalid state.

Do not rename the statuses to generic `QUEUE_*`, replace empty with
underflow, or combine full with limit. Course files and tests use the exact
namespaced contract above.

## Visible representation invariant

An **invariant** is a rule that must hold whenever a completed Queue is
offered to a public operation. The validator accepts exactly these visible
field relationships.

For every valid Queue:

```text
capacity <= EVENT_QUEUE_MAX_CAPACITY
size <= capacity
```

At capacity zero, the only valid state is:

```text
data == NULL
capacity == 0
head == 0
size == 0
```

At positive capacity:

```text
data != NULL
head < capacity, when size > 0
head == 0, when size == 0
```

The implementation may express the final two rules as:

```text
if size == 0: head must be 0
otherwise:    head must be less than capacity
```

An empty positive-capacity Queue therefore has one canonical metadata
state: non-NULL `data`, fixed positive `capacity`, `head == 0`, and
`size == 0`. Inactive array cells have no public value requirement.

The validator must not read through `data` to infer pointer origin. Standard
C cannot establish from an arbitrary non-NULL pointer that:

- it is still live;
- it points to an allocation of at least `capacity` integers;
- it is owned uniquely by this Queue; or
- any inactive element has been initialized.

Those are caller lifetime and ownership obligations. **Lifetime** is the
period during which allocated storage remains valid.

## Logical order and circular arithmetic

For a valid positive-capacity Queue, logical item `k` is stored at:

```text
physical_index(k) = (head + k) % capacity
```

where:

```text
0 <= k < size
```

The derived tail is:

```text
tail = (head + size) % capacity
```

Here **tail** means the candidate physical index where a successful enqueue
would write. It is not the newest event and is not a stored field.

The formulas require all of the following:

1. the Queue pointer is non-NULL;
2. the visible state is valid;
3. `capacity > 0`; and
4. for an actual enqueue write, `size < capacity`.

The full check must precede the remainder expression. A valid capacity-zero
Queue has `size == capacity == 0`, so enqueue returns
`EVENT_QUEUE_FULL` before evaluating `% 0`.

The bounded invariant also makes the additions representable:

```text
head <= 63
size <= 64
head + size <= 127
```

No `size_t` overflow is possible under the public maximum.

At positive capacity, derived `tail` can equal `head` in both states:

```text
empty: size == 0
full:  size == capacity
```

Therefore `head == tail` must never be used to distinguish empty from full.
The explicit `size` field is the discriminator.

## Initialization

Callers begin with:

```c
EventQueue queue = {0};
```

`event_queue_init` follows this exact decision order:

1. a NULL receiver returns `EVENT_QUEUE_INVALID_ARGUMENT`;
2. a receiver that is not the exact all-zero state returns
   `EVENT_QUEUE_INVALID_STATE`;
3. requested capacity above 64 returns `EVENT_QUEUE_LIMIT`;
4. requested capacity zero succeeds without allocation and leaves the exact
   zero state;
5. positive capacity requests exactly
   `capacity * sizeof *candidate` bytes;
6. allocation failure returns `EVENT_QUEUE_ALLOCATION` without changing any
   receiver byte; and
7. allocation success commits only `data` and `capacity`; zero `head` and
   zero `size` were already present.

The maximum of 64 makes the byte-count multiplication safe for `int`.

The implementation uses a local candidate pointer. It does not place the
allocation result into `queue->data` until success is known. A test-only
one-shot hook makes the next positive-capacity request return NULL.
Capacity-zero init performs no request and therefore must not consume that
hook.

Positive-capacity initialization allocates once. There is no `realloc`,
growth, shrink, or enqueue-time allocation.

The API accepts only an all-zero or previously destroyed receiver. It does
not replace a live positive-capacity Queue because doing so would lose the
only owned pointer. A capacity-zero initialized Queue is the exact all-zero
state, so the representation cannot distinguish it from a destroyed
receiver; a later init may initialize that zero receiver.

## Destruction and ownership

`event_queue_destroy(NULL)` is a no-op. For an initialized or already
destroyed Queue, destroy:

1. passes `data` to `free`;
2. stores `NULL` in `data`; and
3. stores zero in capacity, head, and size.

Repeated destroy is safe because `free(NULL)` is defined as a no-op.
Destroy is not a validator or repair operation. Passing arbitrary
uninitialized bytes or a contradictory/bogus pointer violates its
precondition.

Ordinary C structure assignment makes a **shallow copy**: it copies the
pointer but not the allocation. Two copied Queue structs would then claim
one array and could free it twice. Treat a live `EventQueue` as non-copyable
unless a future API defines a deep-copy operation.

The Queue owns `data`; callers must not free, replace, resize, or retain an
interior pointer to it. Enqueue copies an integer into owned storage.
Dequeue and peek copy an integer to caller storage.

The output for dequeue or peek must not point inside the Queue's allocation.
This is the documented **no-alias precondition**. **Aliasing** means two
access paths refer to the same storage. The implementation does not attempt
relational comparisons between unrelated C pointers to enforce it.

## Validator decision order

`event_queue_validate` follows these rules:

1. NULL Queue pointer → `EVENT_QUEUE_INVALID_ARGUMENT`;
2. capacity above 64 or size above capacity →
   `EVENT_QUEUE_INVALID_STATE`;
3. capacity zero → `EVENT_QUEUE_OK` only for the exact all-zero state;
4. positive capacity with NULL data → `EVENT_QUEUE_INVALID_STATE`;
5. positive capacity with zero size → `EVENT_QUEUE_OK` only if head is 0;
6. positive capacity with nonzero size → `EVENT_QUEUE_OK` only if head is
   below capacity.

Validation performs constant work. It does not scan elements and does not
change any Queue byte.

## Enqueue

`event_queue_enqueue` follows this exact order:

1. validate the Queue;
2. return the validation result if it is not `EVENT_QUEUE_OK`;
3. if `size == capacity`, return `EVENT_QUEUE_FULL`;
4. derive `tail = (head + size) % capacity`;
5. store `event_code` at `data[tail]`;
6. increment size; and
7. return `EVENT_QUEUE_OK`.

The full check protects capacity zero and implements the frozen
reject-newest retention policy. On full, the pointer, capacity, head, size,
and every physical slot remain unchanged.

The operation does not shift elements. The same data pointer and capacity
remain in place for the Queue's full live lifetime.

## Dequeue

`event_queue_dequeue` follows this exact order:

1. if `out_event_code == NULL`, return
   `EVENT_QUEUE_INVALID_ARGUMENT`;
2. validate the Queue and propagate any non-OK result;
3. if `size == 0`, return `EVENT_QUEUE_EMPTY`;
4. copy `data[head]` into a local result;
5. derive `new_size = size - 1`;
6. derive `new_head = 0` if `new_size == 0`, otherwise
   `(head + 1) % capacity`;
7. commit head and size;
8. copy the local result to the caller output; and
9. return `EVENT_QUEUE_OK`.

No failure can occur after the successful validation and empty check.
Calculating candidate fields and holding the result locally makes the
commit boundary explicit.

Dequeue does not clear the vacated physical slot. Once outside the `size`
logical positions beginning at `head`, its old bits are stale and have no
public Queue meaning.

When the final event is removed, head becomes 0 rather than the next
circular index. This normalization is part of the public invariant and is
tested.

## Peek

`event_queue_peek` is supplied. It:

1. rejects a NULL output;
2. validates the Queue;
3. returns `EVENT_QUEUE_EMPTY` if size is zero;
4. copies `data[head]` to a local result;
5. publishes that result; and
6. returns `EVENT_QUEUE_OK`.

Peek never changes the Queue. On every non-OK result, it also leaves caller
output unchanged.

## Failure atomicity

**Failure atomicity** means a reported failure appears not to have happened.
Require exact evidence for:

- invalid-argument init;
- live-receiver init;
- excessive-capacity init;
- forced positive-capacity allocation failure;
- invalid visible state;
- enqueue on full;
- dequeue and peek on empty; and
- dequeue and peek with NULL output.

For a failed operation on an allocated Queue, compare:

- `data` pointer identity;
- capacity;
- head;
- size; and
- every physical slot whose value was established before the call.

For dequeue and peek failure, also initialize an output to a recognizable
value and prove it remains unchanged. No integer can serve as an
out-of-band failure sentinel; the recognizable value is only pre-call test
state.

## Full-buffer retention policy

An **overflow attempt** is an enqueue request when a fixed-capacity Queue is
full. Representation safety and retention policy are related but distinct:
correct bounds checks prevent an invalid write, while policy says what the
system does with the new and waiting information.

This implementation freezes:

```text
reject newest
```

It returns `EVENT_QUEUE_FULL`, preserves every waiting event, and does not
write at the derived candidate index. The caller now has explicit evidence
that event ingestion did not succeed. This still does not guarantee that
the caller retries or retains the rejected event elsewhere.

Two alternatives are analyzed only:

- **discard oldest** would explicitly remove the longest-waiting event and
  accept the new one; it favors recency but loses earlier context;
- **backpressure** would make the producer slow, pause, or retry; it can
  preserve data only if the surrounding system implements and obeys that
  coordination.

Do not silently implement either alternative. Do not add blocking,
concurrency, a retry loop, file storage, or a second buffer to the core API.

## Canonical trace

The course fixture is distinct from the Stage B reveal and pause:

```text
capacity 4
enqueue 31, 8, 47, 19
dequeue -> 31
dequeue -> 8
enqueue 62
enqueue 5
enqueue 90 -> EVENT_QUEUE_FULL
drain -> 47, 19, 62, 5
```

Immediately before the rejected enqueue:

```text
physical slots: [62,5,47,19]
head = 2
size = 4
tail = 2
logical order: 47,19,62,5
```

After the final successful dequeue:

```text
head = 0
size = 0
tail = 0
```

The allocated cells may still contain `62,5,47,19`; those inactive values
are not logical Queue contents.

## Complexity and representation comparison

After validation, enqueue, dequeue, and peek each execute a fixed number of
field checks, arithmetic operations, and at most one payload read or write.
They are worst-case `O(1)` with respect to Queue size.

A naive contiguous Queue that always stores its oldest event at physical
slot 0 may shift each remaining event left after dequeue. With `n` waiting
events, that dequeue is `O(n)`.

The circular representation uses `O(capacity)` allocated storage and four
public metadata fields including the pointer. It offers:

- fixed memory use after initialization;
- no per-operation allocation;
- direct indexed slots;
- good spatial locality; and
- explicit full behavior.

A linked Queue uses separately stored nodes. With pointers to both the
oldest and newest nodes, enqueue and dequeue can also be `O(1)` and need no
shifting. Trade-offs include:

- one allocation or pool operation per accepted node unless nodes are
  preallocated;
- pointer and ownership rules per node;
- noncontiguous memory;
- no intrinsic fixed capacity unless policy adds one; and
- an empty-state rule coordinating both end pointers.

Module 7 compares these facts diagrammatically. It does not require a linked
implementation. Later breadth-first modules reuse the Queue behavior
contract; they do not change FIFO meaning.

## Starter assignment boundary

Keep responsibilities exact:

- supplied: public header;
- supplied: all-zero receiver check and one-allocation initializer;
- supplied: peek;
- supplied: destroy;
- supplied: status-name mapping;
- supplied under `EVENT_QUEUE_TESTING`: one-shot allocation-failure hook;
- TODO 1: `event_queue_validate`;
- TODO 2: `event_queue_enqueue`;
- TODO 3: `event_queue_dequeue`;
- student evidence: three tests in the exact categories below; and
- private verification: `solution/event_queue.c` and
  `tests/test_extension.c`.

Do not ask students to add a tail field, grow the array, implement a linked
Queue, change the payload type, or implement a retention alternative.

## Public core-test matrix

The public core suite must cover:

1. NULL initialization;
2. exact zero receiver and successful capacity-zero initialization;
3. positive initialization and visible validity;
4. rejection of positive live-receiver reinitialization without changing
   pointer, metadata, or established slots;
5. destroy reset, repeated destroy, and `destroy(NULL)`;
6. accepted capacities 1 and 64 and rejected capacity 65;
7. one-shot forced positive-capacity allocation failure with exact zero
   receiver preserved;
8. capacity-zero enqueue full and dequeue/peek empty, with no allocation and
   unchanged output;
9. capacity-one enqueue, peek, full rejection, dequeue, empty rejection, and
   head normalization;
10. ordinary FIFO ordering;
11. exact capacity-4 wrap trace using
    `31,8,47,19,62,5,90`;
12. full enqueue preserving pointer, capacity, head, size, and physical
    slots;
13. empty dequeue and peek preserving outputs, all fields, and all safely
    inspectable established physical slots;
14. repeated fill/drain/reuse cycles;
15. final-dequeue normalization to head 0;
16. invalid state for excessive capacity, size above capacity, missing data,
    nonzero capacity-zero fields, empty positive Queue with nonzero head, and
    nonempty Queue with head out of range;
17. operation propagation of invalid state without mutation, including
    safely inspectable established physical slots;
18. exact status strings and unknown fallback; and
19. data-pointer and capacity stability from successful positive init until
    destroy.

Tests must not require cleared inactive slots. When checking a failed call,
they may compare established physical values, including stale values, to
prove no write occurred.

## Private extension-test matrix

Private extension tests have these seven groups:

1. exact capacity-64 fill, partial drain, wrap refill, full rejection, and
   FIFO drain;
2. every valid physical head position;
3. proof that capacity-zero initialization does not consume the one-shot
   allocation-failure hook, followed by a failed and then successful
   positive init;
4. repeated capacity-one cycles;
5. deterministic differential testing against a small ordinary FIFO model
   across many enqueue/dequeue/peek operations, including pointer and
   capacity stability;
6. broad contradictory-state combinations with status/output/state
   preservation; and
7. error precedence and preservation: NULL init beats an excessive request,
   a live receiver's invalid state beats an excessive request, and NULL
   dequeue/peek output beats an invalid Queue; every safely inspectable
   established slot remains unchanged.

The differential model may shift its own small reference array. It is test
oracle code, not the required Queue implementation.

## Student-test categories

Require exactly three independently meaningful categories:

1. FIFO including capacity one;
2. wrap-around plus a repeated fill/drain cycle; and
3. both full and post-drain empty failure preservation in one test body.

The student's wrap values and operation sequence must differ from the
course canonical trace. Test 3 snapshots a full Queue, proves a rejected
enqueue preserves every field and established slot, drains it, then proves
an empty peek or dequeue preserves metadata, established stale slots, and
caller output. Both the full and empty boundaries are required, but one
empty operation is sufficient. Merely calling the same public test three
times does not satisfy the requirement.

## Safe neutral autopsy

The autopsy models:

```text
capacity = 3
head = 1
size = 2
physical state = [10 STALE,20 LIVE,30 LIVE]
logical order = 20,30
intended enqueue = 40
```

The faulty calculation produces raw candidate index 3. A harness guard
checks that index before any array access, refuses the enqueue, and leaves
the state unchanged. It does not print candidate 3. Its exact visible
evidence is rejection, unchanged size 2, and unchanged logical events
20,30. This is memory-safe and solution-independent.

The first wrong decision is calculating a linear raw index without reducing
it into the circular physical range. The guard is correct diagnostic
containment and must remain. Adding a fourth storage cell would change the
capacity contract and hide the defect; it is not a repair.

After learner prediction and diagnosis are preserved, the instructor may
state the exact repair:

```text
tail = (head + size) % capacity
```

The operation must still validate and reject full before evaluating the
expression. For this valid non-full state, repaired tail is 0. Enqueue 40
produces:

```text
physical [40,20,30]
head = 1
size = 3
tail = 1
logical order 20,30,40
```

A regression test should create a valid non-full Queue where
`head + size >= capacity`, enqueue one event, and verify the wrapped
physical index plus complete FIFO drain. Increasing a safety bound, removing
the guard, shifting elements, or allocating extra storage is not a repair.

## Modeling and security boundary

The Queue stores only instructor-created or student-created integer codes.
It does not read logs, packets, files, devices, environment variables,
sockets, or live services.

Passing tests establishes only the documented single-threaded in-memory
Queue behavior. It does not prove:

- complete event ingestion;
- delivery of a rejected event;
- log authenticity or integrity;
- durable retention across process failure;
- thread safety or lock correctness;
- privacy or access control;
- correct event interpretation;
- attack detection; or
- overall system security.

The Queue is not synchronized. Do not call it concurrently. Backpressure is
a surrounding-system policy concept here, not implemented blocking
behavior.

Silent event loss is security-relevant because missing evidence can distort
later analysis. An explicit `EVENT_QUEUE_FULL` is necessary evidence of a
failed enqueue, but it is not sufficient evidence of eventual retention.

## Instructor verification commands

From `module_07_queue/code` on Windows:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target solution
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target solution -Extensions
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target autopsy
```

GNU Make equivalents should build the solution core suite, solution
instrumentation when supported, but do not make a platform-specific
sanitizer a release requirement.

The exact GNU Make commands are:

```text
make solution-core
make solution-extension
make autopsy
```

The unfinished starter must compile and fail behavioral tests until its
three TODOs are completed.

## Instructor implementation audit

- [ ] `EVENT_QUEUE_MAX_CAPACITY` remains 64.
- [ ] Field order is `data`, `capacity`, `head`, `size`.
- [ ] Public status names, order, strings, and function declarations match
      exactly.
- [ ] Positive initialization performs exactly one allocation.
- [ ] Init never overwrites a live positive-capacity Queue.
- [ ] Capacity-zero init does not allocate or consume the test hook.
- [ ] Every init failure preserves the receiver.
- [ ] Validator accepts the exact zero state.
- [ ] Validator requires positive-capacity empty head 0.
- [ ] Validator does not scan or claim to prove pointer liveness.
- [ ] Enqueue checks full before remainder.
- [ ] Tail is derived and never stored.
- [ ] Full enqueue rejects newest and changes no Queue byte.
- [ ] Dequeue checks output before validation.
- [ ] Empty dequeue and peek preserve output.
- [ ] Final dequeue normalizes head to 0.
- [ ] Dequeue does not shift or require clearing a slot.
- [ ] Data pointer and capacity remain stable until destroy.
- [ ] Destroy resets every field and is repeatable.
- [ ] No live Queue is shallow-copied in examples.
- [ ] No output pointer aliases owned storage.
- [ ] Circular enqueue/dequeue/peek are described as `O(1)`.
- [ ] Shifting dequeue is correctly described as `O(n)`.
- [ ] Linked Queue is comparison only.
- [ ] Public, extension, and student test categories match this matrix.
- [ ] The autopsy guard prevents every invalid access.
- [ ] Extra storage and guard removal are rejected as repairs.
- [ ] No example uses live or sensitive security data.
- [ ] Claims remain within the single-threaded in-memory model.
