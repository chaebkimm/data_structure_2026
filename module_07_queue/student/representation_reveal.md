# Stage B — Formal Name and Stored Form

Open this file only after preserving the Stage A inquiry.

## 1. Name the access rule

A **data structure** is a planned way to organize information. An **abstract
data type (ADT)** describes a collection through its allowed operations and
rules, without requiring one storage method.

A **Queue ADT** removes items in **first-in, first-out (FIFO)** order: the
item added earliest is the first item removed. FIFO means arrival order, not
numeric sorting.

- The **front** is the oldest item.
- The **back** is the newest item.
- `enqueue` adds one item at the back.
- `peek` reports the front item without removing it.
- `dequeue` removes and reports the front item.

An **empty Queue** has no items. **Underflow** means attempting `peek` or
`dequeue` while empty. A **full Queue** has reached its stated capacity.
**Overflow** means an attempted addition cannot fit under the current rule.

Module 4's Stack used **last-in, first-out (LIFO)** order, so the newest item
left first.

| Collection | Item removed next |
|---|---|
| Queue, FIFO | oldest item |
| Stack, LIFO | newest item |

Linear equivalent: a Queue removes the earliest arrival; a Stack removes
the most recent arrival.

## 2. Store the Queue in a circular buffer

A **buffer** is bounded storage that temporarily holds items. An **array**
is a numbered row of same-type values. A **circular buffer** uses an array
and reuses positions at the beginning after reaching the physical end.
Nothing in memory bends into a circle; the index calculation wraps.

A **physical position** is one actual array index. **Logical order** is the
FIFO order in which current items belong to the Queue. After wrap-around,
logical order may cross the physical end and continue at index 0.

The stored state is:

```c
typedef struct {
    int *data;
    size_t capacity;
    size_t head;
    size_t size;
} EventQueue;
```

A **struct** is a C type grouping named values called **fields**. `int`
stores a whole number. A **pointer** stores a memory address; `int *data`
points to the event-code array. `size_t` is a nonnegative whole-number type
used for counts and indexes.

- `capacity` is the fixed number of physical positions.
- `head` is the physical index of the front item when the Queue is nonempty.
- `size` is the number of logical items.
- `tail` is the next physical insertion index. It is derived, meaning
  calculated from stored fields rather than stored as another field.

Tail is not the newest item's position.

## 3. Calculate positions safely

The `%` operator gives the **remainder** after whole-number division. For
example, `5 % 3` is 2. Using remainder to return from the physical end to
index 0 is **wrap-around**.

For a valid Queue whose capacity is greater than zero:

```text
tail = (head + size) % capacity
```

An **offset** counts logical steps after the front. For offset `k`, where
offset 0 means the front:

```text
physical index = (head + k) % capacity
```

Never use either expression when capacity is zero because division by zero
has no valid result.

A **stale value** remains in a physical position after its logical item was
removed. Stale values are not Queue items. `head`, `size`, and the mapping
above decide which positions are live.

## 4. Trace a separate capacity-three example

A **trace** is a step-by-step record of changing state. This example is
different from the Cognitive Pause. `UNUSED` means the
position has not stored an event in this trace. `STALE` means the displayed
value remains physically present but is not a logical item.

| Completed request | Physical 0 | Physical 1 | Physical 2 | `head` | `size` | Derived `tail` | Logical order |
|---|---:|---:|---:|---:|---:|---:|---|
| initialize | UNUSED | UNUSED | UNUSED | 0 | 0 | 0 | empty |
| `enqueue(71)` | 71 | UNUSED | UNUSED | 0 | 1 | 1 | `71` |
| `enqueue(24)` | 71 | 24 | UNUSED | 0 | 2 | 2 | `71, 24` |
| `dequeue` → 71 | 71 STALE | 24 | UNUSED | 1 | 1 | 2 | `24` |
| `enqueue(83)` | 71 STALE | 24 | 83 | 1 | 2 | 0 | `24, 83` |
| `enqueue(36)` | 36 | 24 | 83 | 1 | 3 | 1 | `24, 83, 36` |

Exact linear equivalent:

1. Initialization has no logical item; `head`, `size`, and tail are 0.
2. Enqueuing 71 stores it at index 0.
3. Enqueuing 24 stores it at index 1; logical order is 71 then 24.
4. Dequeue reports 71. Its old physical value becomes stale. `head` becomes
   1, `size` becomes 1, and logical order is only 24.
5. Enqueuing 83 uses index 2. The next insertion position wraps to 0.
6. Enqueuing 36 uses index 0. The physical row becomes 36, 24, 83, while
   logical order is 24, 83, 36.

The final Queue is full. Its `head` and derived tail are both 1. That does
not mean it is empty: `size == capacity == 3` proves it is full.

## 5. State the valid-storage rules

`NULL` is the pointer value meaning “points to no object.” An **invariant**
is a rule true in every valid completed state. The course Queue satisfies:

1. `size <= capacity <= 64`.
2. If `capacity == 0`, then `data == NULL`, `head == 0`, and `size == 0`.
3. If `capacity > 0`, then `data != NULL` and `head < capacity`.
4. If `size == 0`, then `head == 0`.
5. Current logical item `k` is at `(head + k) % capacity`.
6. The next insertion position is derived; no tail field is stored.

A positive capacity owns one fixed allocation, a block of storage requested
while the program runs. **Ownership** means responsibility for releasing
that storage. The Queue does not grow after initialization.

A **policy** is a chosen rule for what happens. The course full policy
rejects the newest attempted event and leaves the entire prior Queue
unchanged.

## 6. Prepare for the Cognitive Pause

Be ready to:

1. derive tail and logical order from a wrapped physical state;
2. apply one enqueue and one dequeue without shifting; and
3. distinguish full from empty using `size`.

Do not solve the pause example before timing begins.
