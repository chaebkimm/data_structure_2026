# Stage C — Investigation Worksheet: Linear Accessible Format

Name: ____________________________  
Date: ____________________________

Open this file after completing and preserving the Cognitive Pause.

Sections A through F are the required core. Preserve them before opening
Stage D. Sections G through I are extension work for the announced
independent-work window. This version states storage positions in numbered
sentences. It has the same facts and questions as the standard worksheet.

## Quick reference

A **Queue** is an abstract data type (ADT), a collection described by its
operations and rules. It uses **first-in, first-out (FIFO)** order: the
earliest-added item is removed first. FIFO preserves arrival order; it does
not sort event codes by number.

- `enqueue` adds at the back.
- `peek` reports the front item without removing it.
- `dequeue` removes and reports the front item.

This Queue uses a **circular buffer**, a fixed array whose beginning is
reused after its physical end. `capacity` is the number of array positions,
`head` is the physical index of the front item, and `size` is the number of
current logical items. **Logical order** is FIFO order. A **physical index**
is an actual array position. Tail is the next insertion index; it is
calculated, not stored.

When `capacity > 0`:

```text
tail = (head + size) % capacity
physical index of logical item k = (head + k) % capacity
```

The `%` operator gives a division remainder. It makes an index wrap from the
physical end to index 0. Never evaluate either expression when capacity is
zero. A `LIVE` value belongs to the Queue, a `STALE` value remains after its
item was removed, and `UNUSED` means no event has yet been stored there.

## A. Identify the service rule

Events arrive as 31, then 8, then 47, then 19.

**A1.** Write the required removal order.

____________________________________________________________________

**A2.** Why would removing `8` first violate the FIFO rule?

____________________________________________________________________

**A3.** Name the operation that adds an event, the operation that only
reports the oldest event, and the operation that removes it.

____________________________________________________________________

**A4.** A Stack uses last-in, first-out (LIFO) order, so its newest item
leaves first. What removal order would a Stack produce, and why is it wrong
for this collector?

____________________________________________________________________

## B. Trace the capacity-four Queue

A **trace** is a step-by-step record of changing state. Complete every
blank. For each step, state all four physical positions and label each
`LIVE`, `STALE`, or `UNUSED`. Write logical items from front to back.

1. Initialize: indexes 0, 1, 2, and 3 are `UNUSED`; `head` is 0; `size` is
   0; tail is 0; logical order is empty; result is `EVENT_QUEUE_OK`.
2. After `enqueue(31)`: physical positions __________________________;
   `head` _____; `size` _____; tail _____; logical order ____________;
   result ____________________.
3. After `enqueue(8)`: physical positions ___________________________;
   `head` _____; `size` _____; tail _____; logical order ____________;
   result ____________________.
4. After `enqueue(47)`: physical positions __________________________;
   `head` _____; `size` _____; tail _____; logical order ____________;
   result ____________________.
5. After `enqueue(19)`: physical positions __________________________;
   `head` _____; `size` _____; tail _____; logical order ____________;
   result ____________________.
6. After `dequeue`: physical positions ______________________________;
   `head` _____; `size` _____; tail _____; logical order ____________;
   reported result ____________________.
7. After another `dequeue`: physical positions ______________________;
   `head` _____; `size` _____; tail _____; logical order ____________;
   reported result ____________________.
8. After `enqueue(62)`: physical positions __________________________;
   `head` _____; `size` _____; tail _____; logical order ____________;
   result ____________________.
9. After `enqueue(5)`: physical positions ___________________________;
   `head` _____; `size` _____; tail _____; logical order ____________;
   result ____________________.
10. After attempted `enqueue(90)`: physical positions _______________;
    `head` _____; `size` _____; tail _____; logical order ____________;
    result ____________________.
11. After the next `dequeue`: physical positions ____________________;
    `head` _____; `size` _____; tail _____; logical order ____________;
    reported result ____________________.
12. After the next `dequeue`: physical positions ____________________;
    `head` _____; `size` _____; tail _____; logical order ____________;
    reported result ____________________.
13. After the next `dequeue`: physical positions ____________________;
    `head` _____; `size` _____; tail _____; logical order ____________;
    reported result ____________________.
14. After the final `dequeue`: physical positions ___________________;
    `head` _____; `size` _____; tail _____; logical order ____________;
    reported result ____________________.

**B1.** Immediately after `enqueue(5)`, write the complete physical row and
the complete logical order.

____________________________________________________________________

**B2.** Why can logical order differ from left-to-right physical order?

____________________________________________________________________

**B3.** What must remain unchanged when `enqueue(90)` reports that the Queue
is full?

____________________________________________________________________

**B4.** After the final successful `dequeue`, what values must `head` and
`size` have? Why may old numbers still remain in physical storage?

____________________________________________________________________

## C. Check the representation

An **invariant** is a rule true in every valid completed state. A
**pointer** stores a memory address. `NULL` is a pointer value meaning
“points to no object.” Assume address `A` points to an allocated array, a
storage block obtained while the program runs, with the stated capacity.

Classify each independent state as valid or invalid and give the reason.

1. `data` is `NULL`; `capacity` is 0; `head` is 0; `size` is 0.
2. `data` is `NULL`; `capacity` is 3; `head` is 0; `size` is 0.
3. `data` is address `A`; `capacity` is 3; `head` is 0; `size` is 0.
4. `data` is address `A`; `capacity` is 3; `head` is 2; `size` is 0.
5. `data` is address `A`; `capacity` is 3; `head` is 2; `size` is 3.
6. `data` is address `A`; `capacity` is 65; `head` is 0; `size` is 0.

**C1.** Complete the invariant.

```text
size <= __________________ <= 64
capacity == 0 requires _____________________________________________
capacity > 0 requires ______________________________________________
size == 0 requires _________________________________________________
logical item k is stored at _________________________________________
```

**C2.** Why must code test capacity before using `% capacity`?

____________________________________________________________________

**C3.** With capacity 1, what are `head` and tail when the Queue is empty?
What are they when it is full? Which field distinguishes the states?

____________________________________________________________________

**C4.** Why is tail derived instead of stored as a fifth field?

____________________________________________________________________

## D. Apply the public contracts

A **function** is a named block of instructions that performs one task. A
**contract** states what a function accepts, changes, reports, and
preserves. A **status code** is a named result. The **caller** is the code
requesting a function. An **output location** is storage supplied by the
caller so a function can write a result. A **header file** lists public C
types and functions.

The statuses, in header-file order, are:

1. `EVENT_QUEUE_OK`;
2. `EVENT_QUEUE_INVALID_ARGUMENT`;
3. `EVENT_QUEUE_LIMIT`;
4. `EVENT_QUEUE_FULL`;
5. `EVENT_QUEUE_EMPTY`;
6. `EVENT_QUEUE_ALLOCATION`; and
7. `EVENT_QUEUE_INVALID_STATE`.

Match each independent request to its status and state/output promise.

1. Initialize capacity 4 in a Queue variable whose four fields are zero.
2. Initialize capacity 65 in a Queue variable whose four fields are zero.
3. Initialize an already initialized positive-capacity Queue.
4. `enqueue` into a full valid Queue.
5. `peek` at an empty valid Queue; output began as `-7`.
6. `dequeue` from an empty valid Queue; output began as `-7`.
7. `dequeue` with a `NULL` output pointer.
8. Validate a Queue with `size > capacity`.

For each numbered request, record:

```text
status:
required preservation:
```

**D1.** Which three student functions are incomplete in the starter file?

____________________________________________________________________

**D2.** Why must `dequeue` save the result before changing `head`?

____________________________________________________________________

**D3.** Why must an output location for `peek` or `dequeue` be separate from
the Queue's owned array?

____________________________________________________________________

**D4.** A positive-capacity Queue obtains one fixed allocation, a requested
storage block. **Initialization** prepares a Queue for use. **Destruction**
releases its storage. **Ownership** means responsibility for that release.
State the caller's responsibilities for initialization, copying, and
destruction.

____________________________________________________________________

## E. Choose an explicit full-Queue policy

A **retention policy** states which information is kept. Compare:

1. **reject newest** — refuse the attempted addition and preserve the Queue;
2. **discard oldest** — remove the longest-waiting event to make room; and
3. **backpressure** — ask the source to slow or stop.

**E1.** Which policy does the course Queue implement, and what exact promise
does it make?

____________________________________________________________________

**E2.** Give one situation in which each of the three policies could be a
deliberate choice.

____________________________________________________________________

**E3.** Why must a real security-event system never lose events silently?

____________________________________________________________________

## F. Compare three representations

A **shifting array Queue** moves remaining items toward index 0 after a
removal. A **linked Queue** stores separately allocated nodes; each node
holds an item and a link to another node. **Time complexity** describes how
work grows. `O(1)` means a fixed amount of work; `O(n)` means work may grow
with the number `n` of items.

For each representation, record enqueue cost, dequeue cost, and its main
cost or risk:

1. shifting array Queue;
2. fixed circular Queue; and
3. linked Queue with front and back pointers.

**F1.** Why does this circular Queue avoid shifting after removal?

____________________________________________________________________

**F2.** Which representation uses one fixed allocation? Which commonly
allocates one node per item?

____________________________________________________________________

**F3.** An **algorithm** is a precise step-by-step method. Breadth-first
search (BFS) is a later algorithm that explores shallower levels before
deeper levels. Why could FIFO storage support that order? Do not write the
BFS algorithm.

____________________________________________________________________

## G. Design three tests — extension

A **test** runs a case and checks an expected result. A **regression test**
is kept so a repaired defect does not return. Design tests in this required
order.

**G1.** FIFO, including capacity 1: state operations, expected statuses,
reported values, and final state.

____________________________________________________________________

**G2.** Wrap-around plus repeated fill/drain: state operations and the exact
logical order after each refill.

____________________________________________________________________

**G3.** Full/empty failure preservation: first prove that enqueue on a full
Queue preserves every field and all established slots. Then drain the Queue
and prove that empty peek or dequeue preserves every field, all stale slots,
and the prior output value.

____________________________________________________________________

## H. Investigate policy and stale storage — extension

**H1.** Starting from the full Queue reached in Section B, predict its
logical order after a hypothetical discard-oldest policy accepts event 90.
Clearly label this as a policy experiment, not course behavior.

____________________________________________________________________

**H2.** Does clearing a removed physical slot change FIFO behavior? Give one
benefit and one cost of clearing.

____________________________________________________________________

**H3.** An **autopsy** is a careful study of a supplied defect. In the Queue
Autopsy, record the earliest broken rule, the visible message, the smallest
repair idea, and one regression test. Do not use only the final symptom as
the cause.

____________________________________________________________________

## I. Exit reflection — extension

**I1.** In two sentences, answer the macro-question: How can a
security-event collector process events in arrival order without shifting
all remaining events after every removal?

____________________________________________________________________

**I2.** Name one idea that repeats from ArrayList or Stack and one Queue idea
that is new.

____________________________________________________________________

**I3.** Preserve one initial claim, then write a labeled correction supported
by a trace, invariant, test, or program observation.

____________________________________________________________________
