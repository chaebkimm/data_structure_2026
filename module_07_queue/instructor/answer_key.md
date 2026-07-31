# Instructor Answer Key — Module 7 Queue and Circular Buffer

## Macro-Question synthesis

> How can a security-event collector process events in arrival order without
> shifting all remaining events after every removal?

Use a Queue whose logical rule is first in, first out. Store the events in a
fixed-capacity circular array. Keep the physical index of the oldest event
in `head` and the current count in `size`; for a valid positive-capacity
Queue, derive the next write index as
`(head + size) % capacity`. Dequeue advances `head` rather than shifting
events. Checked full and empty results preserve state and output. This
course implementation rejects the newest attempted event when full and
reports `EVENT_QUEUE_FULL` rather than silently overwriting data.

The full synthesis is not expected in Stage A. Accept a plain-language
initial model that preserves arrival order, reuses earlier numbered slots,
and identifies an unresolved full-storage choice.

## Stage A inquiry

The standard and linear formats contain the same facts and questions.

### A. Preserve the arrival promise

The first event handled is K. The next is B.

Choosing B because it is alphabetically first would break the promise
because K arrived before it. The letters identify events; alphabetical
position is not priority.

### B. Use fixed numbered slots

After handling K and then B:

- event T remains waiting;
- it remains physically in slot 2; and
- slots 0 and 1 may be reused.

Slot 3 is also available, but it is unused rather than reused. Do not require
students to shift T to slot 0.

### C. Continue after the physical end

One arrival-preserving placement is:

```text
R -> slot 3
C -> slot 0
M -> slot 1
```

The physical row is then:

```text
slot 0: C
slot 1: M
slot 2: T
slot 3: R
```

The logical arrival order remains:

```text
T,R,C,M
```

After physical slot 3, continue at slot 0. A sufficient plain-language
answer says the collector must remember where the oldest waiting event is
and how many events are currently waiting. It also has a fixed total number
of slots. Do not require `head`, `size`, or a formula before Stage B.

### D. Decide what happens when every slot is occupied

Accept these policy consequences:

1. Refuse the new event: event Q is not accepted and may be lost unless the
   caller retains or retries it; all older waiting events remain.
2. Discard the longest-waiting event: the oldest current event is lost, and
   event Q is retained. In the completed Stage A state, T is the oldest.
3. Ask the source to slow or stop: event Q is delayed; loss is avoided only
   if the source and surrounding system honor the request or retain it
   elsewhere.

Silently choosing is unsafe because a caller could believe ingestion
succeeded even though evidence was rejected or discarded. Missing events
can hide chronology or distort later analysis.

At Stage A, accept any explicitly stated policy with a coherent trade-off.
During calibration, freeze **reject newest** for the course implementation:
return a full result and preserve the existing Queue.

### E. Compare an earlier access rule

No. Module 4's newest-leaves-first Stack rule would remove T before B and K
if all three were waiting. It reverses the required arrival order.

Newest-first and earliest-arrival-first differ whenever at least two items
are waiting and were added at different times. With zero or one waiting
item, they produce the same next result.

### F. Macro-Question

An acceptable initial answer identifies all of these ideas without
requiring formal vocabulary:

- handle the longest-waiting event first;
- remember the physical location of that event;
- remember how many events are waiting;
- reuse freed early slots after the physical end; and
- report an explicit full-storage decision.

The final “one question” response is open. Productive examples include:

- “How do we know whether the collector is empty or full?”
- “How is the next reusable position calculated?”
- “What exact result reports that the new event was refused?”
- “Who owns and releases the storage?”

## Stage B representation reveal

The complete capacity-three reveal is:

| Completed request | Physical 0 | Physical 1 | Physical 2 | `head` | `size` | `tail` | Logical order |
|---|---:|---:|---:|---:|---:|---:|---|
| initialize | UNUSED | UNUSED | UNUSED | 0 | 0 | 0 | empty |
| enqueue 71 | 71 LIVE | UNUSED | UNUSED | 0 | 1 | 1 | `71` |
| enqueue 24 | 71 LIVE | 24 LIVE | UNUSED | 0 | 2 | 2 | `71,24` |
| dequeue → 71 | 71 STALE | 24 LIVE | UNUSED | 1 | 1 | 2 | `24` |
| enqueue 83 | 71 STALE | 24 LIVE | 83 LIVE | 1 | 2 | 0 | `24,83` |
| enqueue 36 | 36 LIVE | 24 LIVE | 83 LIVE | 1 | 3 | 1 | `24,83,36` |

In the final row, `tail == head == 1`, but `size == capacity == 3`, so the
Queue is full. The reveal does not answer the pause because its capacity,
values, and sequence differ.

## Stage B Cognitive Pause

Keep the vocabulary file closed and give no hint or correctness check until
all three target responses are preserved.

### Target 1 — Derive the wrapped state

Starting state:

```text
physical [18,77,UNUSED,42,9]
capacity = 5
head = 3
size = 4
```

Calculation:

```text
tail = (3 + 4) % 5 = 7 % 5 = 2
```

The next successful write uses physical index 2. Logical order begins at
index 3 and continues through 4, 0, and 1:

```text
42,9,18,77
```

### Target 2 — Add once, then remove once

Enqueue 55 writes at index 2:

```text
physical [18,77,55,42,9]
head = 3
size = 5
tail = 3
logical 42,9,18,77,55
```

Dequeue reports 42. The final state is:

```text
physical 0: 18 LIVE
physical 1: 77 LIVE
physical 2: 55 LIVE
physical 3: 42 STALE
physical 4: 9 LIVE
head = 4
size = 4
tail = (4 + 4) % 5 = 3
logical order = 9,18,77,55
```

No event shifts.

### Target 3 — Preserve a full Queue

Start again from the base state and apply only enqueue 55. The resulting
full state is:

```text
physical [18,77,55,42,9]
head = 3
size = 5
tail = 3
logical order = 42,9,18,77,55
```

Attempted enqueue 66 returns `EVENT_QUEUE_FULL`. Every field and all five
physical values remain unchanged.

`head == tail` alone is ambiguous. Use:

```text
size == 0         -> empty
size == capacity  -> full
```

### Compare after time is called

Accept a labeled correction that preserves the initial work and cites a
specific calculation, indexed trace, or invariant. A complete final
sentence could be:

> The indexed trace strengthened my thinking because it showed that logical
> order starts at head and crosses from index 4 to index 0.

Do not grade wording or drawing quality.

## Stage C investigation

### A. Identify the service rule

#### A1. Required removal order

```text
31,8,47,19
```

#### A2. Why 8 cannot leave first

Event 31 arrived before event 8. Removing 8 first would use numeric value or
another priority rule, not FIFO arrival order.

#### A3. Operation names

- `enqueue` adds an event;
- `peek` reports the oldest event without removing it; and
- `dequeue` removes and reports the oldest event.

#### A4. Stack comparison

A Stack would remove:

```text
19,47,8,31
```

That is LIFO, newest first. It is wrong for a collector promising earliest
arrival first.

### B. Trace the capacity-four Queue

`LIVE` means part of the Queue. `STALE` means a known physical value remains
but is not logical content. `UNUSED` means the trace has not yet stored a
value there.

| Completed request | Physical indexes `0,1,2,3` | `head` | `size` | `tail` | Logical order | Result |
|---|---|---:|---:|---:|---|---|
| initialize | `UNUSED,UNUSED,UNUSED,UNUSED` | 0 | 0 | 0 | empty | `EVENT_QUEUE_OK` |
| enqueue 31 | `31 LIVE,UNUSED,UNUSED,UNUSED` | 0 | 1 | 1 | `31` | `EVENT_QUEUE_OK` |
| enqueue 8 | `31 LIVE,8 LIVE,UNUSED,UNUSED` | 0 | 2 | 2 | `31,8` | `EVENT_QUEUE_OK` |
| enqueue 47 | `31 LIVE,8 LIVE,47 LIVE,UNUSED` | 0 | 3 | 3 | `31,8,47` | `EVENT_QUEUE_OK` |
| enqueue 19 | `31 LIVE,8 LIVE,47 LIVE,19 LIVE` | 0 | 4 | 0 | `31,8,47,19` | `EVENT_QUEUE_OK` |
| dequeue | `31 STALE,8 LIVE,47 LIVE,19 LIVE` | 1 | 3 | 0 | `8,47,19` | `EVENT_QUEUE_OK`, reports 31 |
| dequeue | `31 STALE,8 STALE,47 LIVE,19 LIVE` | 2 | 2 | 0 | `47,19` | `EVENT_QUEUE_OK`, reports 8 |
| enqueue 62 | `62 LIVE,8 STALE,47 LIVE,19 LIVE` | 2 | 3 | 1 | `47,19,62` | `EVENT_QUEUE_OK` |
| enqueue 5 | `62 LIVE,5 LIVE,47 LIVE,19 LIVE` | 2 | 4 | 2 | `47,19,62,5` | `EVENT_QUEUE_OK` |
| attempt enqueue 90 | unchanged | 2 | 4 | 2 | `47,19,62,5` | `EVENT_QUEUE_FULL` |
| dequeue | `62 LIVE,5 LIVE,47 STALE,19 LIVE` | 3 | 3 | 2 | `19,62,5` | `EVENT_QUEUE_OK`, reports 47 |
| dequeue | `62 LIVE,5 LIVE,47 STALE,19 STALE` | 0 | 2 | 2 | `62,5` | `EVENT_QUEUE_OK`, reports 19 |
| dequeue | `62 STALE,5 LIVE,47 STALE,19 STALE` | 1 | 1 | 2 | `5` | `EVENT_QUEUE_OK`, reports 62 |
| dequeue | `62 STALE,5 STALE,47 STALE,19 STALE` | 0 | 0 | 0 | empty | `EVENT_QUEUE_OK`, reports 5 |

#### B1. State after enqueue 5

```text
physical [62,5,47,19]
head = 2
size = 4
tail = 2
logical order = 47,19,62,5
```

#### B2. Logical versus physical order

Logical order begins at `head`, follows `size` positions, and wraps from
physical index 3 to index 0. A left-to-right physical reading always starts
at index 0, so the two orders differ after wrap-around.

#### B3. Failed enqueue 90

Required unchanged state includes:

- the owned `data` pointer;
- capacity 4;
- head 2;
- size 4;
- all four physical values `62,5,47,19`; and
- logical order `47,19,62,5`.

The result is `EVENT_QUEUE_FULL`.

#### B4. Final successful dequeue

`head == 0` and `size == 0`. Old numbers may remain because dequeue changes
metadata instead of clearing or shifting physical cells. With size 0, none
of those stale values is logical Queue content.

### C. Check the representation

The completed validity table is:

| `data` | `capacity` | `head` | `size` | Valid? | Reason |
|---|---:|---:|---:|---|---|
| `NULL` | 0 | 0 | 0 | yes | exact capacity-zero state |
| `NULL` | 3 | 0 | 0 | no | positive capacity requires non-NULL data |
| address A | 3 | 0 | 0 | yes | valid positive-capacity empty state |
| address A | 3 | 2 | 0 | no | empty state requires head 0 |
| address A | 3 | 2 | 3 | yes | full, and head is in range |
| address A | 65 | 0 | 0 | no | capacity exceeds public maximum 64 |

The exercise assumes address A identifies suitable live storage. The actual
validator cannot prove that ownership or extent.

#### C1. Complete the invariant

```text
size <= capacity <= 64
capacity == 0 requires data == NULL, head == 0, and size == 0
capacity > 0 requires data != NULL and a head in range
size == 0 requires head == 0
logical item k is stored at (head + k) % capacity
```

For the logical mapping, also require a valid positive-capacity Queue and
`0 <= k < size`.

#### C2. Capacity guard

`% capacity` is a remainder operation. A zero right operand is division by
zero and has no defined valid C result. Validate and use a full/empty branch
before any circular expression.

#### C3. Capacity one

At capacity one:

```text
empty: head = 0, tail = 0, size = 0
full:  head = 0, tail = 0, size = 1
```

`size` distinguishes them. For the full state, `size == capacity`.

#### C4. Why tail is derived

Head, size, and capacity already determine tail. A stored fifth field would
repeat information and create contradictory possible states if one
operation updated the fields inconsistently.

### D. Apply the public contracts

The completed contract table is:

| Request | Status | Required preservation |
|---|---|---|
| initialize capacity 4 from all-zero receiver | `EVENT_QUEUE_OK` | commits owned allocation, capacity 4, head 0, size 0 |
| initialize capacity 65 from all-zero receiver | `EVENT_QUEUE_LIMIT` | exact all-zero receiver unchanged |
| initialize an already live Queue | `EVENT_QUEUE_INVALID_STATE` | pointer, fields, and established slots unchanged |
| enqueue into full valid Queue | `EVENT_QUEUE_FULL` | pointer, all fields, all physical slots unchanged |
| peek empty; output began `-7` | `EVENT_QUEUE_EMPTY` | Queue unchanged; output remains `-7` |
| dequeue empty; output began `-7` | `EVENT_QUEUE_EMPTY` | Queue unchanged; output remains `-7` |
| dequeue with NULL output | `EVENT_QUEUE_INVALID_ARGUMENT` | Queue unchanged; no output write |
| validate size above capacity | `EVENT_QUEUE_INVALID_STATE` | receiver unchanged |

#### D1. Three incomplete student functions

```text
event_queue_validate
event_queue_enqueue
event_queue_dequeue
```

Peek, init, destroy, status names, and the test hook are supplied.

#### D2. Save the dequeue result

The event at the old head is the result. Saving it before changing metadata
makes that value independent of the new head and lets the implementation
publish caller output only on the successful path.

#### D3. Separate output location

If output pointed inside the Queue's allocation, publishing a result would
also write owned Queue storage. That alias could modify a live or stale slot
and violate the documented ownership/operation model. The caller must use a
separate integer.

#### D4. Lifecycle and ownership

The caller:

1. starts with an all-zero or previously destroyed receiver;
2. initializes it once while positive-capacity storage is live;
3. does not copy the live struct by value or free/replace its `data`;
4. provides separate output storage; and
5. calls destroy exactly once when use ends; repeated destroy of the reset
   zero state is safe.

A shallow struct copy would make two structs claim the same allocation and
risk double-free.

### E. Choose an explicit full-Queue policy

#### E1. Course policy

The course Queue rejects the newest attempted event. It returns
`EVENT_QUEUE_FULL` and leaves the complete prior Queue unchanged. It neither
silently overwrites the oldest event nor blocks the caller.

#### E2. Deliberate policy examples

Accept other well-justified examples. Calibrated examples:

- reject newest when older audit chronology must remain intact and the
  producer can retry or escalate the rejected event;
- discard oldest for an explicitly documented recent-status display where
  newest information is more useful than history; and
- backpressure when a cooperating producer can safely pause or retain data
  until capacity returns.

Representation safety alone does not prove that any policy is operationally
correct.

#### E3. Why silent loss is unsafe

Silent loss can create invisible gaps in evidence, hide a sequence of
events, weaken detection or later reconstruction, and mislead callers into
believing ingestion succeeded. A real system must expose and monitor the
chosen retention behavior.

### F. Compare three representations

The completed cost table is:

| Representation | Enqueue | Dequeue | Main cost or risk |
|---|---:|---:|---|
| shifting array Queue | `O(1)` when the next end slot is available | `O(n)` | removal shifts up to the remaining `n` items; fixed capacity |
| fixed circular Queue | `O(1)` | `O(1)` | wrap arithmetic and explicit full policy; one fixed allocation |
| linked Queue with front/back pointers | `O(1)` | `O(1)` | per-node allocation/ownership and pointer correctness; no intrinsic bound |

These costs assume the stated representation and a linked Queue that keeps
both end pointers.

#### F1. Why no shifting

Dequeue advances `head` to change the logical front. Logical-to-physical
mapping finds later events without moving their stored integers.

#### F2. Allocation comparison

The course circular Queue obtains one fixed allocation at initialization. A
typical linked Queue allocates one node per accepted item unless it uses a
separate preallocated node pool.

#### F3. FIFO and later breadth-first work

If shallower work is discovered and enqueued before deeper work, FIFO
removes those earlier shallower discoveries first. This is only a transfer
hypothesis here; no BFS algorithm is required in Module 7.

### G. Design three tests — extension

Many tests are valid if they state exact operations, statuses, outputs, and
cleanup. The following are calibrated examples, not mandatory literal
values.

#### G1. FIFO including capacity one

Capacity one:

1. init 1 → OK;
2. enqueue 44 → OK;
3. peek → OK and 44, Queue unchanged;
4. enqueue 12 → FULL, slot 0 remains 44;
5. dequeue → OK and 44, head 0, size 0;
6. dequeue with output 777 → EMPTY, output remains 777; and
7. destroy → exact zero state.

#### G2. Wrap-around and repeated cycle

Capacity three:

1. enqueue 14,27,35;
2. dequeue 14, then 27;
3. enqueue 48, then 59;
4. require physical `[48,59,35]`, head 2, logical `35,48,59`;
5. drain exactly `35,48,59` and require normalized empty;
6. enqueue 70,81 and require logical `70,81`; and
7. drain `70,81` and destroy.

#### G3. Full/empty preservation

Capacity two:

1. enqueue 4 and 9;
2. snapshot pointer, capacity, head, size, and both slots;
3. enqueue 13 → FULL and compare the entire snapshot;
4. drain 4 and 9;
5. snapshot normalized empty metadata and the established stale slots 4 and
   9, then set output to 777;
6. dequeue → EMPTY, output still 777, metadata and both stale slots
   unchanged; and
7. destroy.

Both the full failure and a post-drain empty failure are required in the
single third student-test body. The empty operation may be peek or dequeue;
the example selects dequeue.

### H. Investigate policy and stale storage — extension

#### H1. Hypothetical discard-oldest

Labeling this explicitly as non-course policy, discarding oldest 47 and
accepting 90 gives logical order:

```text
19,62,5,90
```

The course Queue instead rejects 90 and keeps `47,19,62,5`.

#### H2. Clearing a removed slot

Clearing does not change FIFO behavior because head and size determine
logical membership. A possible benefit is reducing residual sensitive data
or making a debugger display easier to interpret. Costs include an extra
write and the risk of teaching that a sentinel value determines membership.
The course integer codes are synthetic and dequeue does not clear.

#### H3. Queue Autopsy

The earliest broken rule is the calculation of the candidate insertion
index as a linear sum without bringing it back into the capacity-three
range. The visible rejection line is:

```text
enqueue 40 accepted: no
```

The smallest repair is the positive-capacity circular tail calculation
after full validation/checking. A regression test should create
`capacity=3, head=1, size=2`, enqueue 40, require a write at slot 0, and
drain `20,30,40`.

### I. Exit reflection — extension

#### I1. Macro-Question

Example:

> Keep the oldest event's physical index and the logical item count, then
> derive positions with wrap-around. Dequeue advances the head and enqueue
> uses the derived tail, so events do not shift and FIFO order remains
> intact.

#### I2. Repeated and new ideas

Example:

> The Queue repeats ArrayList ownership, capacity, checked state, and
> failure-preserving API habits. Circular logical-to-physical mapping and a
> derived tail are new.

Contrasting FIFO with the earlier Stack LIFO rule is also acceptable.

#### I3. Preserved correction

Accept any honest preserved claim plus a labeled correction supported by
specific evidence. Example:

```text
Initial: head equal to tail means empty.
Correction: head equal to derived tail can mean empty or full; the
capacity-three reveal shows a full state with head 1, tail 1, and size 3.
```

## Canonical API reference

### Status and result rules

| Situation | Exact result |
|---|---|
| NULL required pointer | `EVENT_QUEUE_INVALID_ARGUMENT` |
| receiver is not exact zero at init | `EVENT_QUEUE_INVALID_STATE` |
| requested init capacity above 64 | `EVENT_QUEUE_LIMIT` |
| next positive init allocation forced/fails | `EVENT_QUEUE_ALLOCATION` |
| valid enqueue with `size == capacity` | `EVENT_QUEUE_FULL` |
| valid dequeue/peek with `size == 0` | `EVENT_QUEUE_EMPTY` |
| contradictory completed fields | `EVENT_QUEUE_INVALID_STATE` |
| completed success | `EVENT_QUEUE_OK` |

Init checks receiver zero state before requested limit. Dequeue and peek
check their required output pointer before validating the Queue.

### Positive-capacity formulas

After validation and only when capacity is positive:

```text
tail = (head + size) % capacity
physical(k) = (head + k) % capacity, 0 <= k < size
```

For enqueue, also prove non-full before using tail for a write.

### Boundary behavior

| Boundary | Behavior |
|---|---|
| capacity 0 | exact zero state; enqueue FULL; dequeue/peek EMPTY; no remainder |
| capacity 1 empty | head 0, size 0, tail 0 |
| capacity 1 full | head 0, size 1, tail 0 |
| capacity 64 | valid and allocated once |
| requested capacity 65 | LIMIT; receiver unchanged |
| final dequeue | output succeeds; head 0 and size 0; stale cell permitted |
| full enqueue | reject newest; complete Queue unchanged |
| empty dequeue/peek | output unchanged |
| destroy | free once and reset all fields; NULL/repeated zero destroy safe |

## Lab and test guidance

The starter's exact incomplete functions are validator, enqueue, and
dequeue. A correct submission does not add a tail field, growth path,
alternative payload, linked nodes, or policy switch.

The public core run should end with:

```text
8 core test(s), 0 failure(s)
```

The eight public test groups are:

1. zero initialization, reinitialization, and destroy;
2. capacity limit and allocation failure;
3. zero and capacity one;
4. FIFO and peek preservation;
5. exact wrap-around and full preservation;
6. repeated fill and drain cycles;
7. invalid arguments and states; and
8. status names.

The private extension run covers maximum wrap-around, every valid head
position, capacity-zero hook preservation, many capacity-one cycles,
deterministic differential behavior, broad invalid states, and error
precedence with preservation. The precedence group proves NULL init beats an
excessive request, live-receiver invalid state beats an excessive request,
and NULL dequeue/peek output beats an invalid Queue while safely inspectable
established slots remain unchanged.

The completed student run must report all three:

```text
student FIFO/capacity-one test: PASS
student wrap-around/repeated-cycle test: PASS
student full/empty failure-preservation test: PASS
All student-authored tests passed.
```

## Evidence-record reference

Evidence should identify commands and observed results rather than state
only “it works.” A complete record includes:

1. FIFO in ordinary language and the exact Queue/Stack contrast;
2. invariant and positive-capacity formula guard;
3. the course capacity-four physical and logical states;
4. core-test output;
5. three student-test names, operations, and expected claims;
6. one failure-preservation snapshot;
7. allocation/ownership lifecycle;
8. reject-newest policy and one trade-off;
9. circular-array versus linked-Queue cost comparison;
10. autopsy prediction, first wrong decision, repair, and regression;
11. correction to one earlier claim; and
12. safe-meaning statement.

An acceptable safe-meaning statement is:

> These tests support the checked single-threaded in-memory FIFO contract
> for synthetic integer codes. They do not prove real log completeness,
> authenticity, durable retention, thread safety, attack detection, or
> system security.

## Autopsy reference

The exact unmodified program output is:

```text
before: 20,30
enqueue 40 accepted: no
size after attempt: 2
after: 20,30
```

The initial Queue has physical state
`[10 STALE,20 LIVE,30 LIVE]`, capacity 3, head 1, size 2, and logical order
20,30. Space exists at physical index 0. The faulty calculation produces raw
index 3, and the safety guard rejects it before access. The program does not
print index 3. No undefined behavior occurs and state remains unchanged.

The first wrong decision is:

```c
insertion_index = queue->head + queue->size;
```

After learner diagnosis is preserved, the answer key may give:

```c
insertion_index =
    (queue->head + queue->size) % (size_t)TRAINING_CAPACITY;
```

Its required preconditions are a valid non-full state and positive
capacity. Keep the bounds guard. Do not allocate an extra slot.

The repaired result is:

```text
accepted: yes
physical [40,20,30]
head = 1
size = 3
logical order 20,30,40
```

The guard was containment, not the defect. Removing the guard, increasing
storage, shifting items, or merely accepting 40 without preserving FIFO is
not a repair.

### Complete Queue Autopsy worksheet reference

#### 1. Predict before running

Exact prediction:

```text
before: 20,30
enqueue 40 accepted: no
size after attempt: 2
after: 20,30
```

A correct enqueue should use physical index 0. Its complete logical order
would be `20,30,40`.

#### 2. Observe the bounded program

The four copied program lines must match the prediction above exactly. If a
student predicted acceptance, preserve that prediction and add a labeled
observation that the supplied program instead prints `no`, keeps size 2,
and keeps logical values 20,30.

#### 3. Locate the first wrong decision

```text
candidate index calculated by the program: 3
capacity: 3
bounds-check decision: reject because 3 is not below 3
returned result: false, printed as no
```

The earliest incorrect decision is using the raw linear sum
`head + size` as the physical insertion index. The Queue is not full because
`size == 2`, `capacity == 3`, and physical index 0 is not logically occupied.

#### 4. Separate safety from correctness

The guard keeps memory access inside the three-element array, so the program
is memory-bounded. It still violates the Queue contract because a valid
non-full state rejects an event that should fit. Deleting only the guard
would attempt to write `data[3]`, outside legal indexes 0, 1, and 2; that
would create undefined behavior rather than circular reuse.

#### 5. State a repair

After validating a positive capacity and proving the Queue is not full,
reduce the sum into the physical index range:

```text
(head + size) % capacity
```

Repaired state:

```text
physical index 0: 40 LIVE
physical index 1: 20 LIVE
physical index 2: 30 LIVE
head: 1
size: 3
next insertion index: 1
logical order: 20,30,40
```

The next insertion index is a derived candidate only; because the repaired
Queue is full, another enqueue must return full without writing there.

#### 6. Design regression tests

Exact first regression:

1. use capacity 3, physical `[10 STALE,20 LIVE,30 LIVE]`, head 1, size 2;
2. enqueue 40;
3. require success, physical `[40,20,30]`, head 1, size 3, tail 1, and
   logical `20,30,40`; and
4. dequeue exactly `20,30,40`, ending at normalized head 0 and size 0.

One acceptable repeated-cycle regression:

1. initialize capacity 3;
2. enqueue `1,2,3`, dequeue 1 and 2, enqueue 4 and 5, then drain
   `3,4,5`;
3. enqueue `6,7,8`, dequeue 6 and 7;
4. require head 2, size 1, and event 8 at index 2;
5. enqueue 9 and 10;
6. require physical `[9,10,8]`, head 2, size 3, logical `8,9,10`; and
7. drain `8,9,10`, ending at normalized empty state.

All successful enqueues return `EVENT_QUEUE_OK`; each full state has
`size == 3`. The data pointer and capacity remain stable.

#### 7. Autopsy conclusion

```text
prediction: event 40 is refused; size and logical order remain unchanged
observation: exact four output lines match the bounded refusal
first broken rule: raw head + size is used as a physical index
smallest repair idea: reduce the validated positive-capacity sum by capacity
required precondition: valid, positive-capacity, non-full Queue
regression test: a wrapped free slot accepts and FIFO drain is 20,30,40
```

### Complete evidence-template reference

#### 1. Queue model

- Queue/FIFO: the earliest-added current item is the earliest removed.
- Front/back/operations: front is oldest; back is newest; enqueue adds at
  back; peek reports front without removal; dequeue removes/reports front.
- Physical/logical: physical storage is indexed array placement; logical
  order is the FIFO sequence beginning at head.
- Not numeric sorting: the course sequence removes 31 before 8 because 31
  arrived first.

#### 2. Capacity-four trace

```text
physical indexes 0,1,2,3: 62,5,47,19
head: 2
size: 4
derived tail: 2
logical order: 47,19,62,5
enqueue 90 status: EVENT_QUEUE_FULL
preserved: pointer, capacity 4, head 2, size 4, and all four slots
drain: 47,19,62,5
final head: 0
final size: 0
observed stale values may remain 62,5,47,19
```

#### 3. Invariant and formulas

Use the complete C1 invariant above. The formulas are
`(head + size) % capacity` and `(head + k) % capacity`. Capacity must be
positive before remainder. Size 0 means empty; size equal to capacity means
full.

#### 4. Contract and failure evidence

Any exact successful case plus one exact failed case is acceptable. A
calibrated failure is the full enqueue of 90: status FULL, all fields and
slots unchanged. Empty peek/dequeue preserves output because every integer
may be legitimate data and output is committed only on success.

#### 5. Student-authored tests

Use the G1–G3 references above, while allowing any nonduplicate values and
sequences satisfying the live template. The third code test must contain
both the full enqueue snapshot and, after draining, one empty peek or
dequeue preservation check with caller output and established stale slots
unchanged.

#### 6. Tool evidence

Require the learner's actual compiler/version and exact command. The
reference solution should report eight core groups with zero failures, all
three student tests passing after completion, no compiler warnings, and no
sanitizer finding when a supported sanitizer is used. If tooling is
unavailable, record the exact instructor-approved equivalent run rather
than inventing output.

#### 7. Ownership and lifecycle

Start all-zero; positive init makes one fixed allocation at capacity 1–64;
capacity 0 stays zero; no Queue operation grows it; destroy frees and resets
all fields. A shallow copy duplicates the owning pointer and risks two frees
of one allocation.

#### 8. Policy and representation

The course uses reject-newest and reports FULL. Discard-oldest loses prior
context; backpressure asks a cooperating source to wait. Silent loss hides
missing evidence. A shifting array has `O(n)` dequeue, this circular array
has `O(1)` enqueue/dequeue with one fixed allocation, and a linked Queue can
have `O(1)` operations with per-node pointer/allocation obligations.

#### 9. Queue Autopsy

Use the complete seven-part reference immediately above.

#### 10. Transfer and correction

Queue removes oldest; Stack removes newest. FIFO can preserve the order in
which later breadth-first work is discovered, supporting shallower-before-
deeper scheduling. Accept any preserved initial claim and evidence-backed
labeled correction; do not require the sample wording in I3.
