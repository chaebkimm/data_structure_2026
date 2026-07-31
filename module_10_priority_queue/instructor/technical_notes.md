# Instructor Technical Notes - Module 10

## Source of truth

The public header is authoritative for spelling, field order, status order,
parameters, and limits. These notes explain the required behavior; they do
not expand the public API.

```c
#define ALERT_PRIORITY_QUEUE_MAX_CAPACITY 64U

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

`size_t` is a C whole-number type used for sizes and array positions. It
cannot represent a negative number. The course comparator uses `size_t`
for both `priority` and `arrival_sequence`.

The five Queue fields mean:

- `data`: the address of the owned record array;
- `size`: the number of live records;
- `capacity`: the number of allocated record positions;
- `next_sequence`: the sequence assigned by the next successful insertion;
  and
- `comparison_count`: a diagnostic count of record-comparator calls.

A **diagnostic** is information collected to study the implementation.
`comparison_count` is observable state, but it is not part of the logical
collection of waiting alerts.

The public operations are:

```c
AlertPriorityQueueStatus alert_priority_queue_init(
    AlertPriorityQueue *queue
);

AlertPriorityQueueStatus alert_priority_queue_validate(
    const AlertPriorityQueue *queue
);

AlertPriorityQueueStatus alert_priority_queue_insert(
    AlertPriorityQueue *queue,
    int alert_id,
    size_t priority
);

AlertPriorityQueueStatus alert_priority_queue_peek_min(
    AlertPriorityQueue *queue,
    AlertRecord *out_record
);

AlertPriorityQueueStatus alert_priority_queue_extract_min(
    AlertPriorityQueue *queue,
    AlertRecord *out_record
);

AlertPriorityQueueStatus alert_priority_queue_reset_comparisons(
    AlertPriorityQueue *queue
);

void alert_priority_queue_destroy(AlertPriorityQueue *queue);

const char *alert_priority_queue_status_name(
    AlertPriorityQueueStatus status
);
```

Under `ALERT_PRIORITY_QUEUE_TESTING`, the header also declares the
instructor test hook:

```c
void alert_priority_queue_test_fail_next_growth(void);
```

The hook makes the next attempted growth allocation fail once. It is test
instrumentation, not a production operation or a student TODO.

## Exact status contract

The status enumeration has this exact order:

```text
ALERT_PRIORITY_QUEUE_OK
ALERT_PRIORITY_QUEUE_INVALID_ARGUMENT
ALERT_PRIORITY_QUEUE_FULL
ALERT_PRIORITY_QUEUE_EMPTY
ALERT_PRIORITY_QUEUE_ALLOCATION
ALERT_PRIORITY_QUEUE_SEQUENCE_EXHAUSTED
ALERT_PRIORITY_QUEUE_INVALID_STATE
```

The exact readable names are:

| Status | `alert_priority_queue_status_name` result |
|---|---|
| `ALERT_PRIORITY_QUEUE_OK` | `"ok"` |
| `ALERT_PRIORITY_QUEUE_INVALID_ARGUMENT` | `"invalid argument"` |
| `ALERT_PRIORITY_QUEUE_FULL` | `"Priority Queue is full"` |
| `ALERT_PRIORITY_QUEUE_EMPTY` | `"Priority Queue is empty"` |
| `ALERT_PRIORITY_QUEUE_ALLOCATION` | `"allocation failed"` |
| `ALERT_PRIORITY_QUEUE_SEQUENCE_EXHAUSTED` | `"arrival sequence exhausted"` |
| `ALERT_PRIORITY_QUEUE_INVALID_STATE` | `"Priority Queue representation is invalid"` |
| any unknown value | `"unknown AlertPriorityQueueStatus"` |

`FULL` means 64 live records already occupy the course maximum.
`SEQUENCE_EXHAUSTED` is different: storage may remain, but the next arrival
number cannot be assigned and advanced without wrapping.

## ADT service rule

An **abstract data type (ADT)** defines public behavior independently of
one storage method. This ADT is a stable minimum Priority Queue.

Record `a` precedes record `b` exactly when:

```text
a.priority < b.priority
or
a.priority == b.priority and
    a.arrival_sequence < b.arrival_sequence
```

The word **minimum** refers to the smaller numeric priority. It does not
mean a smaller alert ID. The alert ID never participates in comparison.

The word **stable** means equal-priority records leave in their insertion
order. Stability is obtained by assigning increasing arrival sequences and
using sequence as the second comparison field. Do not rely on the current
physical array order to settle a tie: swap-last extraction changes that
order.

This comparator is strict. A later equal-priority record does not replace
an earlier equal-priority candidate. Code such as
`later.priority <= candidate.priority` is incorrect because it discards the
sequence rule and reverses equal-priority service.

## Representation invariant

An **invariant** is a rule that is true in every valid completed state. The
full representation invariant is:

1. `capacity` is exactly `0`, `4`, `8`, `16`, `32`, or `64`.
2. `size <= capacity`.
3. Capacity 0 requires the exact all-zero state:
   `data == NULL`, `size == 0`, `next_sequence == 0`, and
   `comparison_count == 0`.
4. Positive capacity requires non-NULL owned storage for at least
   `capacity` records.
5. Live records occupy indexes 0 through `size - 1`.
6. Inactive positions have no public record value.
7. Positive-capacity empty state requires `next_sequence == 0`.
8. A nonempty state requires `next_sequence != 0` and
   `next_sequence >= size`.
9. Every live arrival sequence is unique and smaller than
   `next_sequence`.
10. Physical record order need not be sorted.
11. `comparison_count` never wraps after reaching `SIZE_MAX`.
12. The Queue uniquely owns `data`.

`SIZE_MAX` is the largest value representable by `size_t`.

The API itself produces only these capacity transitions:

```text
0 -> 4 -> 8 -> 16 -> 32 -> 64
```

The exact all-zero state is both an accepted receiver for initialization
and the state restored by destruction.

An allocated empty state is also valid:

```text
data != NULL
size == 0
capacity in {4,8,16,32,64}
next_sequence == 0
comparison_count may retain a prior diagnostic value
```

Extraction retains the allocation and capacity. Destruction releases the
allocation.

## Constant-time validator boundary

`alert_priority_queue_validate` performs a constant amount of work. It
checks only relationships that can be established from the five public
fields:

1. reject a NULL Queue pointer;
2. reject a capacity outside `0,4,8,16,32,64`;
3. reject `size > capacity`;
4. for capacity 0, accept only the exact all-zero state;
5. for positive capacity, reject `data == NULL`;
6. for positive-capacity empty state, require `next_sequence == 0`; and
7. for nonempty state, require `next_sequence != 0` and
   `next_sequence >= size`.

Validation is `O(1)`, read "order one," because it does not scan records.
It therefore cannot prove:

- that `data` points to live storage;
- that the allocation contains `capacity` records;
- that ownership is unique;
- that live slots were initialized;
- that live sequences are unique or smaller than `next_sequence`;
- that a client did not edit a record through the public pointer; or
- that the comparison count reached its value through valid operations.

Those are ownership, lifetime, and API-use obligations. A duplicate live
sequence violates the full invariant even if the constant-time shape
validator cannot detect it. Make students state this distinction rather
than claiming that one validator proves all correctness.

## Initialization and destruction

Callers begin with:

```c
AlertPriorityQueue queue = {0};
```

Initialization:

1. rejects a NULL receiver with `INVALID_ARGUMENT`;
2. rejects any nonzero receiver with `INVALID_STATE`;
3. performs no allocation; and
4. leaves the accepted exact-zero receiver unchanged.

Initialization is still a useful explicit contract check. It does not
replace or reset a live Queue, because doing so could lose the only owned
pointer.

Destruction:

1. does nothing for a NULL pointer;
2. releases `data`;
3. resets every field to zero; and
4. is safe to repeat on an initialized or already destroyed Queue.

Destroy is not a validator or repair operation. Passing arbitrary
uninitialized bytes or a bogus pointer violates its precondition.

Ordinary C structure assignment makes a **shallow copy**: it copies the
pointer without copying the allocation. Two copied Queue structs would
then appear to own the same storage and could release it twice. Treat a live
`AlertPriorityQueue` as non-copyable.

## Sequence assignment and exhaustion

The first successful insertion receives sequence 0. Each later successful
insertion receives the current `next_sequence`, then advances that field by
one.

Insertion rejects when `next_sequence == SIZE_MAX`. The implementation does
not assign `SIZE_MAX`, because advancing after that assignment would wrap
to zero. Thus the greatest assigned sequence is `SIZE_MAX - 1`.

Sequence exhaustion is checked before an allocation attempt. It leaves the
pointer, metadata, live records, inactive established values, and
comparison counter unchanged.

Removing some but not all records does not renumber the survivors. When
the final record is extracted, no old live sequence remains, so
`next_sequence` resets to 0. A later insertion begins a new empty-to-live
episode at sequence 0 without colliding with a waiting record.

If both conditions are present, full capacity takes precedence over
sequence exhaustion:

```text
validate -> full -> sequence exhausted -> possible growth
```

## Geometric growth and insertion

**Geometric growth** multiplies capacity instead of adding one position at
a time. Insertion follows this order:

1. validate the Queue;
2. if size is 64, report `FULL`;
3. if `next_sequence == SIZE_MAX`, report `SEQUENCE_EXHAUSTED`;
4. if `size == capacity`, choose 4 for the first allocation or double the
   positive capacity;
5. request the new allocation through a temporary pointer;
6. on allocation failure, report `ALLOCATION` without committing anything;
7. on success, commit the possibly changed `data` pointer and capacity;
8. append `{alert_id, priority, next_sequence}` at `data[size]`;
9. increment size and `next_sequence`; and
10. report success.

Insertion makes zero record comparisons. Without growth it is `O(1)`.
One growth insertion is `O(n)` because the allocator may copy `n` live
records. Across a long sequence of geometric-growth insertions, the
average cost per insertion is amortized `O(1)`. **Amortized** means an
occasional expensive growth is distributed across many inexpensive
insertions.

`realloc` may move the allocation. Clients must not keep an interior
pointer to a Queue record across insertion. On a failed `realloc`, the old
allocation remains owned by the Queue. The implementation commits through
a temporary pointer so a failed request cannot lose the old address.

The test hook is consumed only when growth is actually attempted. An
insertion with spare capacity does not call the allocation wrapper.

## Minimum scan and saturating comparison count

For a nonempty Queue:

```text
candidate = index 0
for index = 1 through size - 1:
    add one comparison, unless the count is already SIZE_MAX
    if data[index] strictly precedes data[candidate]:
        candidate = index
```

A scan of `n` records makes exactly `n - 1` comparator calls. A one-record
scan makes zero calls.

The counter is **saturating**:

```text
if comparison_count < SIZE_MAX:
    comparison_count += 1
```

Once it reaches `SIZE_MAX`, later comparator calls still occur but the
stored metric remains `SIZE_MAX`. Saturation prevents an overflow from
making a very large count appear small. It also means the field is no
longer an exact lifetime total after saturation.

The comparator count increases only on successful nonempty peek and
extraction scans, and only once per examined challenger record. Insertion,
validation, initialization, reset, and status naming make zero record
comparisons. A successful reset separately assigns zero to the field.

`alert_priority_queue_reset_comparisons` validates the Queue and then sets
only the metric to zero. It preserves allocation identity, capacity, size,
sequence state, and every record.

## Peek-min

Peek-min follows this exact order:

1. reject a NULL output before inspecting the Queue;
2. validate the Queue and propagate any failure;
3. report `EMPTY` if size is zero;
4. scan all live records with the complete comparator;
5. copy the selected record to a local result;
6. publish the copied result; and
7. report success.

A successful peek of seven records adds six comparisons. It changes no
logical record, size, capacity, data pointer, or sequence state. It does
change the diagnostic comparison counter.

The output must not point inside the Queue allocation. This **no-alias
precondition** means caller output cannot be another access path to owned
record storage. The function does not attempt to detect aliasing.

## Extract-min and swap-last removal

Extraction uses the same output, validation, empty, and scan order as peek.
After the scan:

1. save the selected record locally;
2. let `final_index = size - 1`;
3. if the selected position differs from `final_index`, copy the final live
   record into the selected position;
4. set size to `final_index`;
5. if size is now zero, reset `next_sequence` to 0;
6. publish the saved record; and
7. report success.

This is called **swap-last removal** in the student material, although the
implementation needs only one replacement copy. It does not preserve
physical array order. It does preserve logical service order because every
later scan uses the stored priority and arrival sequence.

The vacated final slot is not cleared. Once outside indexes 0 through
`size - 1`, its prior bits are inactive and have no public record value.
The allocation and capacity remain unchanged after draining.

The output uses a copy. The same no-alias precondition as peek applies.

## Failure preservation and precedence

**Failure preservation** means a reported failure appears not to have
changed the caller's protected state.

For peek and extraction, a NULL output takes precedence over Queue
validation. Otherwise, invalid Queue state takes precedence over empty
state.

For insertion, the order is:

```text
invalid argument or state
then full
then sequence exhausted
then allocation failure, but only when growth is required
```

On every failure:

- every Queue field is unchanged;
- the allocation identity is unchanged;
- every safely inspectable established slot is unchanged; and
- a non-NULL output record is unchanged.

Peek and extraction do not begin a scan before all failure conditions have
been resolved, so failed access does not increment `comparison_count`.
Reset comparison failure also leaves the counter unchanged.

Tests should snapshot all five fields, pointer identity, all established
physical slots, and recognizable output values. Inactive slots need not
have been initialized merely to make a comparison.

## Authoritative Stage A fixture

Stage A uses labels and urgency numbers, not formal Priority Queue
vocabulary:

```text
arrival:  K, B, T, R, C
urgency:  3, 1, 2, 1, 4
```

With arrival settling equal urgency, the service order is:

```text
B, R, T, K, C
```

FIFO order would be:

```text
K, B, T, R, C
```

Keep formal operation names, comparator language, sequence fields, backend
details, formulas, code, and exact answers closed until the initial model
is preserved.

## Authoritative Stage B and Cognitive Pause fixtures

Stage B reveal fixture:

```text
50/2/0, 11/1/1, 80/1/2, 34/3/3
```

Here `ID/P/S` means alert ID, priority, and arrival sequence. Correct
service order is:

```text
11, 80, 50, 34
```

After extracting 11, the active physical array is:

```text
50/2/0, 34/3/3, 80/1/2
```

The Cognitive Pause always returns to:

```text
54/3/0, 81/1/1, 12/2/2, 27/1/3, 68/4/4
capacity 8, size 5, next_sequence 5, comparison_count 0
```

The three and only three target headings are:

1. select without removing;
2. extract, swap, and insert; and
3. separate ties from policy.

Target 1 reports 81 and four comparisons. Target 2 extracts 81, moves 68
into index 1, appends `35/1/5`, and leaves 27 as the next logical record.
Target 3 distinguishes stable equal-priority order from starvation and
controlled priority updates.

## Canonical seven-alert fixture

Insert, in exact order:

```text
71/3/0
88/1/1
42/2/2
17/1/3
26/4/4
9/2/5
63/1/6
```

After insertion:

```text
capacity = 8
size = 7
next_sequence = 7
comparison_count = 0
index 7 is inactive
```

Logical extraction order:

```text
88, 17, 63, 42, 9, 71, 26
```

One peek at size 7 reports `88/1/1` and adds six comparisons.

Starting again with comparison count 0, the exact active physical IDs after
each swap-last extraction are:

```text
extract 88: [71,63,42,17,26,9]  add 6 comparisons
extract 17: [71,63,42,9,26]     add 5 comparisons
extract 63: [71,26,42,9]        add 4 comparisons
extract 42: [71,26,9]           add 3 comparisons
extract 9:  [71,26]             add 2 comparisons
extract 71: [26]                add 1 comparison
extract 26: []                  add 0 comparisons
```

The drain adds:

```text
6 + 5 + 4 + 3 + 2 + 1 + 0 = 21
```

After the final extraction:

```text
data is the same owned non-NULL allocation
capacity = 8
size = 0
next_sequence = 0
comparison_count = 21
all former physical records are inactive
```

Do not grade inactive slot values as logical contents.

## Paper-only sorted-array backend

The alternative backend is analyzed but not implemented. Maintain records
from worst to best, with the minimum at the removable right end:

```text
26/4/4, 71/3/0, 9/2/5, 42/2/2, 63/1/6, 17/1/3, 88/1/1
```

This order deliberately reverses ties at the physical level so the earlier
arrival is farther right and leaves first.

For this design:

- insertion is `O(n)` because records may shift to open the correct
  position;
- peek-min is `O(1)` because the rightmost live record is the minimum; and
- extract-min is `O(1)` because reducing size removes the rightmost record.

If the minimum were stored at index 0, peek would remain `O(1)` but
extraction would be `O(n)` because every survivor would shift left.

The course's unsorted backend has:

| Operation | Record comparisons | Time |
|---|---:|---:|
| insert without growth | 0 | `O(1)` |
| one growth insertion | 0 | `O(n)` copying may occur |
| long insertion sequence | 0 | amortized `O(1)` each |
| peek-min at size `n` | `n - 1` | `O(n)` |
| extract-min at size `n` | `n - 1` | `O(n)` |

For 32 worst-position insertions, the paper sorted array uses:

```text
0 + 1 + ... + 31 = 496 comparisons
```

The unsorted backend uses zero record comparisons for those insertions.

For draining 32 preloaded records after resetting the metric:

```text
unsorted: 31 + 30 + ... + 0 = 496 comparisons
sorted minimum-at-end: 0 comparisons
```

Construction cost and service cost must not be blended silently. Backend
selection follows the workload: many inserts with rare reports favors the
unsorted array; a prepared batch with many minimum removals may justify the
sorted array.

## Fairness and mutable-priority boundaries

Stable ties do not guarantee global fairness. A priority-4 alert can wait
indefinitely if priority-1, priority-2, or priority-3 alerts keep arriving
before the higher-numbered record is selected. This is **starvation**.

Possible surrounding policies include:

- **aging**, which explicitly improves a waiting record's effective
  priority over time;
- a reserved service share for long-waiting records; or
- a documented maximum-wait escalation.

None is implemented by this module. Do not imply one from stability.

Clients must not silently edit the priority or sequence of a live record
through `data`. Such editing bypasses the ADT contract and may invalidate
the meaning of earlier decisions. This unsorted backend happens to rescan,
but a future sorted array or Heap could retain a physically incorrect
order.

Two later strategies are previewed only:

- **decrease-key** changes a stored priority through a defined operation
  and repairs the backend; and
- a **duplicate-entry strategy** inserts a new version and ignores an older
  stale version when removed.

A duplicate strategy needs an identity plus version, generation, or current
best-value record so stale entries can be recognized. Module 10 does not
add either operation to the API.

## Starter assignment and test partition

Student responsibility is exactly three implementation TODOs:

1. apply the comparator and scan for the minimum record index;
2. insert, including geometric growth and checked commit; and
3. extract-min with swap-last removal.

Supplied code owns:

- initialization;
- constant-time validation;
- peek-min;
- comparison reset;
- destruction;
- status naming;
- saturating comparison support as scaffolded for the TODO; and
- the one-shot growth-failure hook under the testing macro.

Students also author exactly three test categories:

1. mixed priorities and stable ties, with IDs that do not reveal the
   expected order;
2. growth from capacity 4 to 8, followed by swap-last extraction,
   reinsertion, and correct logical service; and
3. protected output on empty access plus complete state and slot
   preservation for insertion at the 64-record full limit.

The allocation-failure hook is not exposed in the student test build.
Forced allocation failure remains supplied core and instructor evidence.

The public core suite should cover:

1. NULL and exact-zero initialization;
2. rejection of a nonzero receiver without mutation;
3. exact status strings and unknown fallback;
4. valid capacities `0,4,8,16,32,64` and rejection of every other capacity;
5. size, pointer, empty-sequence, and nonempty-sequence shape violations;
6. constant-time validation's stated inability to detect duplicate live
   sequences;
7. first insertion and exact capacity ladder growth;
8. zero comparator calls during insert;
9. stable mixed-priority peek and extraction;
10. exact `n - 1` scan counts and saturation;
11. canonical seven-alert extraction order and swap-last states;
12. comparison reset preserving every nonmetric fact;
13. empty access preserving output and state;
14. full insertion preserving fields and slots;
15. sequence exhaustion preserving fields and slots;
16. forced first-growth and later-growth allocation failure;
17. no-growth insertion not consuming the failure hook;
18. output-before-validation error precedence;
19. invalid-state-before-empty precedence;
20. full-before-sequence-exhaustion precedence;
21. retained allocation, capacity, and metric after draining;
22. sequence reset and valid reuse after draining; and
23. destroy reset, repeated destroy, and `destroy(NULL)`.

Private extension tests should add broad boundary and differential coverage,
not new public behavior. Useful groups include:

1. every valid capacity shape and representative nearby invalid values;
2. capacity-64 fill and complete stable drain;
3. sequence values near `SIZE_MAX`;
4. comparison counts near `SIZE_MAX`;
5. deterministic differential testing against a small reference model;
6. repeated drain-and-reuse episodes;
7. all error-precedence intersections; and
8. exact state, slot, and output snapshots across every failure path.

The unfinished starter must compile but fail behavioral tests until all
three TODOs are completed.

## Safe stable-tie autopsy

The isolated autopsy uses:

```text
80/2/0, 91/1/1, 17/1/2, 44/3/3
```

Correct selection is alert 91. Alert 17 has the same priority but arrived
later.

The faulty bounded scan replaces its candidate whenever a later priority
is less than or equal to the current priority. It therefore changes from
91 to 17 when it reaches the second priority-1 record.

The first broken decision is:

```text
replace 91/1/1 with 17/1/2 merely because 1 <= 1
```

The exact repair is to use the complete strict comparator:

```text
smaller priority
or
equal priority and smaller arrival sequence
```

The harness uses only four fixed records and indexes 0 through 3. It
contains no invalid pointer, unbounded loop, or out-of-range access.
Memory safety does not make the result logically correct.

A regression test must include at least three equal-priority records whose
IDs do not encode arrival order, then assert that the earlier sequence is
selected first.

## Modeling and security boundary

All alert records are instructor-created or student-created synthetic
values. The module does not read logs, packets, files, devices, environment
variables, sockets, accounts, or live services.

A smaller course priority number is a scheduling input, not proof that an
alert is:

- authentic;
- severe;
- timely;
- complete;
- correctly classified;
- authorized for disclosure;
- handled within a real service objective; or
- part of an actual compromise.

Passing tests establishes only the documented single-threaded in-memory
ADT behavior. It does not prove durable retention, thread safety, fair
staffing, score quality, delivery after a failed insert, or overall system
security.

`FULL`, `ALLOCATION`, and `SEQUENCE_EXHAUSTED` provide explicit failure
evidence. The caller still needs a surrounding policy for retry,
backpressure, durable recording, or escalation. This module implements none
of those policies.

## Deferred topics

Keep these outside the core implementation:

- a binary Heap backend;
- sorted-array implementation;
- decrease-key;
- duplicate stale-entry processing;
- arbitrary deletion;
- priority aging;
- concurrency and locking;
- generic `void *` records;
- shrinking capacity;
- durable storage; and
- live SOC integration.

They may be discussed as bounded previews. They must not replace the core
stable minimum Queue.

## Five release gates

The five gates are instructional controls, not optional suggestions.

1. **Gate A - initial inquiry.** Release only a Stage A prompt. Preserve the
   student's urgency-order, tie, waiting, and boundary reasoning before any
   formal name or answer is shown.
2. **Gate B - representation and pause.** Release the formal reveal. Keep
   vocabulary closed during the exactly-three-target Cognitive Pause.
   Preserve all three responses before calibration and Stage C.
3. **Gate C - investigation.** Release one worksheet form. Preserve
   Sections A through F, including the canonical trace, contracts, costs,
   policy risks, and spiral links, before Stage D.
4. **Gate D - textbook and models.** Release the beginner textbook and
   models only after the investigation attempt. Require labeled corrections
   and one verbal or written API trace before Stage E.
5. **Gate E - lab and evidence.** Release only the student code package.
   Completion requires the three TODOs, exactly three student-test
   categories, saved test output, autopsy correction, operation counts,
   backend memo, fairness explanation, and corrected earlier artifacts.

Instructor files, solution code, and private extension tests remain closed
through all student gates.

## Accessibility requirements

- Standard and linear versions must contain identical records, priorities,
  sequences, operation order, questions, and scoring.
- Every spatial model must have an exact numbered or linear text
  equivalent.
- Do not assess drawing quality, handwriting speed, visual scanning speed,
  or memorized jargon.
- Permit drawing, indexed tables, numbered prose, typing, dictation, and
  tactile or verbal modeling.
- Read starting definitions and exact record triples aloud when requested.
- Approved extended time uses the same three Cognitive Pause targets and
  fixture.
- Corrections are added beside preserved initial work; they do not replace
  the evidence of learning.

## Instructor implementation audit

- [ ] Header names, field order, status order, and strings match exactly.
- [ ] Priority and sequence use `size_t`; alert ID never ranks a record.
- [ ] Smaller priority wins; earlier sequence settles equal priority.
- [ ] Capacity is accepted only at `0,4,8,16,32,64`.
- [ ] Exact zero includes comparison count zero.
- [ ] Allocated empty state requires next sequence zero.
- [ ] Nonempty shape requires nonzero next sequence at least equal to size.
- [ ] Constant-time validation does not claim to prove record uniqueness,
      pointer liveness, allocation extent, ownership, or mutation history.
- [ ] Init accepts only exact zero and performs no allocation.
- [ ] Growth uses a temporary `realloc` result and never exceeds 64.
- [ ] Insert checks full before sequence exhaustion and sequence before
      allocation.
- [ ] Insert performs zero record comparisons.
- [ ] Scan applies the complete strict comparator exactly `n - 1` times.
- [ ] Comparison count saturates at `SIZE_MAX`.
- [ ] Peek changes only output and the diagnostic counter.
- [ ] Extract uses exact swap-last states and resets sequence only when
      empty.
- [ ] Drain retains allocation, capacity, and comparison count.
- [ ] Every failure preserves all Queue fields, established slots, and
      applicable output.
- [ ] NULL output precedes validation for peek and extraction.
- [ ] Output never aliases the owned array.
- [ ] Live owning structs are never shallow-copied in examples.
- [ ] Sorted paper order is
      `26,71,9,42,63,17,88`, worst to best.
- [ ] Canonical peek costs 6 comparisons; canonical drain costs 21.
- [ ] The three TODOs and three student-test categories remain exact.
- [ ] The autopsy is bounded and identifies the first equal-priority
      divergence.
- [ ] Five release gates are enforced.
- [ ] Every student-facing model defines jargon and has an exact linear
      equivalent.
- [ ] No example uses live or sensitive security data.
- [ ] Claims remain within the single-threaded in-memory scheduling model.
