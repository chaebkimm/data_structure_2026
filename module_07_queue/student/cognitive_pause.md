# Stage B — Five-Minute Cognitive Pause

Read the starting definitions with the instructor before timing begins.
Then use no notes, slides, classmates, vocabulary file, or coding tools for
five minutes. You may draw, type, dictate, or answer in numbered sentences.

An approved extended-time version, or one completed at another approved
time, uses the same state and three targets. Speed, handwriting, and drawing
quality are not assessed. Preserve your first response when correction
begins.

## Starting definitions

A **Queue** removes items in **first-in, first-out (FIFO)** order: the
earliest addition leaves first. `enqueue` adds one event. `dequeue` removes
and reports the oldest event.

An **array** is a numbered row of same-type values. The **capacity** is the
fixed number of physical array positions. `head` is the physical index of
the oldest event. `size` counts current logical events. **Logical order** is
their FIFO order, even when it differs from left-to-right physical order.

When capacity is greater than zero, the next insertion position is:

```text
tail = (head + size) % capacity
```

The `%` operator gives the remainder after whole-number division. It lets an
index **wrap around**, meaning continue at index 0 after the physical end.
Tail is the next insertion position, not the newest event.

`UNUSED` labels a physical position with no event from this trace. `STALE`
labels a physically present value that is no longer a logical Queue item.

## Starting state

Capacity is 5.

| Physical index | 0 | 1 | 2 | 3 | 4 |
|---:|---:|---:|---:|---:|---:|
| Stored value | 18 | 77 | UNUSED | 42 | 9 |

`head == 3` and `size == 4`.

Exact linear equivalent: index 0 stores 18; index 1 stores 77; index 2 is
unused; index 3 stores 42; index 4 stores 9. The oldest event is at index 3,
and four logical events are present.

## Target 1 — Derive the wrapped state

Using only the starting state:

1. calculate the derived tail;
2. state the physical index that the next successful addition would use;
   and
3. write all current events in logical FIFO order.

Response:

____________________________________________________________________

____________________________________________________________________

## Target 2 — Add once, then remove once

Return to the starting state. Apply `enqueue(55)`, then one `dequeue`.

State:

1. the event code reported by `dequeue`;
2. every physical position, labeling any stale value;
3. the final `head`, `size`, and derived tail; and
4. the final logical order.

Response:

____________________________________________________________________

____________________________________________________________________

## Target 3 — Preserve a full Queue

Return to the starting state. Apply only `enqueue(55)`. The Queue is now
full. Next, attempt `enqueue(66)`.

State:

1. the result of the second addition;
2. the unchanged physical state, `head`, `size`, tail, and logical order;
   and
3. why `head == tail` cannot by itself distinguish this full Queue from an
   empty Queue.

Response:

____________________________________________________________________

____________________________________________________________________

## Compare after time is called

**Calibration** means comparing an initial answer with an accurate answer.
When the instructor releases that answer:

1. preserve your initial response;
2. check reasoning that remains correct;
3. label each correction `tail`, `logical order`, `operation`, or
   `full versus empty`; and
4. finish the sentence below.

Correction:

____________________________________________________________________

The evidence that changed or strengthened my thinking was:

____________________________________________________________________
