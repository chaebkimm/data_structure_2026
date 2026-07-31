# Keeping Arrival Order Without Shifting

## Essential question

> How can a security-event collector process events in arrival order without
> shifting all remaining events after every removal?

## 1. The service promise

A **program** is a group of instructions a computer can run. Its **state**
is the information it currently remembers. A **security event** is a stored
report about something a system noticed. Our integer event codes are
synthetic, meaning invented for safe practice.

Suppose codes arrive as `31, 8, 47, 19`. If the promise is arrival order,
the removal order must also be `31, 8, 47, 19`. The code values identify
events; they do not state importance. Removing 8 first would sort by number
and break the promise.

## 2. The Queue rule

A **data structure** is a planned way to organize information. An
**abstract data type (ADT)** describes a collection through its operations
and rules without requiring one storage method.

A **Queue ADT** uses **first-in, first-out (FIFO)** order: the item added
earliest is removed first.

- The **front** is the oldest item.
- The **back** is the newest item.
- `enqueue` adds one item at the back.
- `peek` reports the front item without removing it.
- `dequeue` removes and reports the front item.

An empty Queue has no items. **Underflow** is an attempted `peek` or
`dequeue` on an empty Queue. A full Queue has reached its capacity, its
fixed item limit. **Overflow** means an attempted addition cannot fit under
the chosen rule.

Module 4's Stack used **last-in, first-out (LIFO)** order: its newest item
left first. For the same arrivals, a Stack would remove `19, 47, 8, 31`.
A Queue and Stack organize access; neither rule sorts numeric values.

## 3. One circular representation

An **array** is a numbered row of same-type values. An index is one numbered
position, beginning at 0 in C. A **buffer** is bounded temporary storage. A
**circular buffer** reuses array positions at the beginning after reaching
the physical end. Memory does not bend into a circle; an index calculation
wraps.

The course type is:

```c
typedef struct {
    int *data;
    size_t capacity;
    size_t head;
    size_t size;
} EventQueue;
```

A **struct** is a C type grouping named values called fields. `int` stores a
whole number. A **pointer** stores a memory address; `int *data` points to
the event array. `size_t` is a nonnegative whole-number type for counts and
indexes.

- `capacity` is the fixed number of physical positions.
- `head` is the physical index of the front when the Queue is nonempty.
- `size` counts current logical items.
- Tail is the next physical insertion index. It is derived, or calculated,
  rather than stored as another field.

A **physical position** is one array index. **Logical order** is FIFO order.
The two orders can differ after wrap-around.

## 4. Derive every live position

The `%` operator gives the remainder after whole-number division. For
example, `6 % 4` is 2. For a valid Queue with positive capacity:

```text
tail = (head + size) % capacity
physical index of logical item k = (head + k) % capacity
```

Offset `k` counts items after the front, so `k == 0` means the front. Never
evaluate these expressions when capacity is zero, because division by zero
has no valid result.

A `LIVE` value currently belongs to the Queue. A `STALE` value remains in a
slot after its logical item was removed. `UNUSED` means no event has yet
been stored there. The implementation need not erase removed values:
`head`, `size`, and the mapping decide what is live.

## 5. Trace capacity four

A **trace** is a step-by-step record of changing state. Each physical row
lists indexes 0 through 3.

| Completed request | Physical row | `head` | `size` | tail | Logical order or result |
|---|---|---:|---:|---:|---|
| initialize | `UNUSED, UNUSED, UNUSED, UNUSED` | 0 | 0 | 0 | empty |
| enqueue 31, 8, 47, 19 | `31 LIVE, 8 LIVE, 47 LIVE, 19 LIVE` | 0 | 4 | 0 | `31, 8, 47, 19` |
| dequeue | `31 STALE, 8 LIVE, 47 LIVE, 19 LIVE` | 1 | 3 | 0 | reports 31 |
| dequeue | `31 STALE, 8 STALE, 47 LIVE, 19 LIVE` | 2 | 2 | 0 | reports 8 |
| enqueue 62 | `62 LIVE, 8 STALE, 47 LIVE, 19 LIVE` | 2 | 3 | 1 | `47, 19, 62` |
| enqueue 5 | `62 LIVE, 5 LIVE, 47 LIVE, 19 LIVE` | 2 | 4 | 2 | `47, 19, 62, 5` |
| attempt enqueue 90 | unchanged | 2 | 4 | 2 | `EVENT_QUEUE_FULL` |

The physical row is now `[62, 5, 47, 19]`, but FIFO order is
`47, 19, 62, 5`. The full Queue rejects event 90 and preserves every field
and slot.

Four successful dequeues report `47`, then `19`, then `62`, then `5`.
Removing the last item returns the empty state to its required form:
`head == 0` and `size == 0`. Old numbers may remain physically stale.

## 6. The invariant

`NULL` means that a pointer points to no object. An **invariant** is a rule
true in every valid completed state:

1. `size <= capacity <= EVENT_QUEUE_MAX_CAPACITY`, and the maximum is 64.
2. If `capacity == 0`, then `data == NULL`, `head == 0`, and `size == 0`.
3. If `capacity > 0`, then `data != NULL` and `head < capacity`.
4. If `size == 0`, then `head == 0`.
5. Logical item `k` is at `(head + k) % capacity`.
6. Tail is derived; it is not stored.

A capacity-zero Queue is valid and empty. Its enqueue reports
`EVENT_QUEUE_FULL`; its peek and dequeue report `EVENT_QUEUE_EMPTY`.

When a Queue is empty, `head` and derived tail can both be 0. When it is
full, head and tail can also be equal. `size` distinguishes the states.
This remains true at capacity 1.

## 7. The public contract

A **function** is a named block of instructions performing one task. An
**API**, or application programming interface, is the set of functions
other program parts may call. A **contract** states what a function accepts,
changes, reports, and preserves.

```c
EventQueueStatus event_queue_init(EventQueue *queue, size_t capacity);
EventQueueStatus event_queue_validate(const EventQueue *queue);
EventQueueStatus event_queue_enqueue(EventQueue *queue, int event_code);
EventQueueStatus event_queue_dequeue(EventQueue *queue, int *out_event_code);
EventQueueStatus event_queue_peek(const EventQueue *queue, int *out_event_code);
void event_queue_destroy(EventQueue *queue);
const char *event_queue_status_name(EventQueueStatus status);
```

A **status code** is a named result:

- `EVENT_QUEUE_OK`: success;
- `EVENT_QUEUE_INVALID_ARGUMENT`: a required Queue or output is invalid;
- `EVENT_QUEUE_LIMIT`: requested capacity is above 64;
- `EVENT_QUEUE_FULL`: a valid Queue cannot accept another item;
- `EVENT_QUEUE_EMPTY`: a valid Queue has no item to report;
- `EVENT_QUEUE_ALLOCATION`: storage could not be obtained; and
- `EVENT_QUEUE_INVALID_STATE`: visible fields break the invariant.

The **caller** is the program part requesting a function. An **output
location** is caller-provided storage where a function writes a result.
Peek and dequeue change the output only on success. That output must not
point inside the Queue's own array.

`event_queue_validate` checks visible field relationships but cannot prove
from a pointer value alone that storage is still usable, large enough, or
belongs only to this Queue. Students complete `validate`, `enqueue`, and
`dequeue`.
Initialization, peek, destruction, and status text are supplied.

**Failure preservation** means a failed operation leaves the prior state
unchanged. Full enqueue preserves all fields and slots. Empty peek or
dequeue preserves both Queue and output. Enqueue writes the item before
increasing size. Dequeue saves the result before changing head and size,
then writes the output last.

## 8. Storage lifetime

An **allocation** is a storage block obtained while a program runs.
**Ownership** means responsibility for releasing it.

The caller begins with a Queue variable whose fields are all zero, or with
one that was destroyed. Capacity 0 succeeds without allocation. Positive
capacity from 1 through 64 obtains exactly one allocation, and the Queue
never grows. A request above 64, a failed allocation, or an attempt to
initialize an already initialized Queue leaves the Queue variable unchanged.

`event_queue_destroy` releases storage and resets every field. A `NULL`
pointer does nothing; every other argument must be initialized or already
destroyed. Do not make a **shallow copy** of a positive-capacity Queue: it
duplicates the fields and owning pointer, not the allocation.

## 9. Costs and alternatives

**Time complexity** describes how work grows: `O(1)` means fixed work; `O(n)` means work may grow with `n` items.

| Representation | Enqueue | Dequeue | Trade-off |
|---|---:|---:|---|
| shifting array Queue | `O(1)` when space remains | `O(n)` | removal moves remaining items |
| fixed circular Queue | `O(1)` | `O(1)` | fixed capacity may become full |
| linked Queue with front/back pointers | `O(1)` | `O(1)` | one node allocation and link per item |

A linked Queue stores separately allocated **nodes**, objects containing an
item and a pointer to another node. It can grow until another boundary
fails, but pointer and allocation rules add risk. Releasing all linked nodes
takes `O(n)` work; releasing this one-allocation circular Queue takes
`O(1)`.

Full storage needs a **retention policy**, a rule stating which information
is kept. **Reject newest** preserves the current Queue. **Discard oldest**
sacrifices the longest-waiting event. **Backpressure** asks the source to slow or stop.
Different systems may choose differently, but silent event loss is never an
acceptable hidden behavior.

## 10. Forward link

An **algorithm** is a precise step-by-step method. **Breadth-first search
(BFS)** is a later algorithm that explores shallower levels before deeper
levels. A FIFO Queue can keep found work in the order it was found. The
procedure and trace wait for a later module.

**Key sentence:** a circular Queue preserves FIFO order with `head`, `size`,
and wrapped indexes, so successful removal needs no shifting.
