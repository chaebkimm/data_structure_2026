# Instructor Technical Notes - Module 11

## Source of truth

The public header is authoritative for names, field order, statuses,
parameters, and limits. Module 11 preserves the Module 10 API and adds one
checker.

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

The additional operation is:

```c
AlertPriorityQueueStatus alert_priority_queue_is_min_heap(
    AlertPriorityQueue *queue,
    bool *out_is_min_heap
);
```

All other functions, statuses, readable status strings, capacity rules,
ownership rules, sequence behavior, and failure precedence remain as in
Module 10.

## Exact preserved statuses

```text
ALERT_PRIORITY_QUEUE_OK
ALERT_PRIORITY_QUEUE_INVALID_ARGUMENT
ALERT_PRIORITY_QUEUE_FULL
ALERT_PRIORITY_QUEUE_EMPTY
ALERT_PRIORITY_QUEUE_ALLOCATION
ALERT_PRIORITY_QUEUE_SEQUENCE_EXHAUSTED
ALERT_PRIORITY_QUEUE_INVALID_STATE
```

Readable strings remain:

| Status | String |
|---|---|
| `OK` | `"ok"` |
| `INVALID_ARGUMENT` | `"invalid argument"` |
| `FULL` | `"Priority Queue is full"` |
| `EMPTY` | `"Priority Queue is empty"` |
| `ALLOCATION` | `"allocation failed"` |
| `SEQUENCE_EXHAUSTED` | `"arrival sequence exhausted"` |
| `INVALID_STATE` | `"Priority Queue representation is invalid"` |
| unknown | `"unknown AlertPriorityQueueStatus"` |

## Stable comparator

Record `a` precedes `b` exactly when:

```text
a.priority < b.priority
or
a.priority == b.priority and
    a.arrival_sequence < b.arrival_sequence
```

Alert ID never participates. Every movement copies a complete
`AlertRecord`; separating fields would corrupt record identity and stable
tie behavior.

The comparator is strict. Arrival sequences are unique under valid API use,
so two live records do not compare equal as complete scheduling keys.

## Complete-tree array representation

Live records occupy the contiguous prefix:

```text
data[0] through data[size - 1]
```

For live index `i`:

```text
left(i) = 2*i + 1
right(i) = 2*i + 2
parent(i) = (i - 1)/2 for i > 0
```

A child exists only when its calculated index is below size.

Contiguous prefix storage automatically represents a complete binary tree:
all earlier positions exist before a later position. There are no child
pointers and no stored shape flags. A right child cannot exist without its
smaller-index left sibling.

At the teaching maximum, live indexes are 0 through 63. The largest
intermediate `2*i+1` evaluated by the extraction loop remains 127, safely
representable by `size_t`. Code still checks `left >= new_size` before
reading a child. It derives `right = left + 1` only after the bounded left
calculation and checks `right < new_size` before reading.

## Shape rules preserved from Module 10

The constant-time validator requires:

1. capacity exactly `0,4,8,16,32,64`;
2. size no greater than capacity;
3. capacity 0 in exact all-zero state;
4. positive capacity with non-NULL data;
5. allocated empty state with `next_sequence == 0`; and
6. nonempty state with nonzero `next_sequence >= size`.

It cannot prove pointer liveness, allocation extent, ownership, live record
initialization, unique sequences, or Heap order.

The complete shape follows from the live prefix and size. It is not an
additional pointer structure for the validator to traverse.

## Heap-order invariant

For every child index 1 through `size-1`:

```text
child must not precede data[(child - 1)/2]
```

This is a partial order. It guarantees root index 0 is minimum because every
record has a parent chain ending at the root, and no step in that chain
allows a lower-ranked child above a higher-ranked parent.

It does not guarantee:

- global array sorting;
- sibling order;
- lower values in an entire left subtree;
- higher values in an entire right subtree;
- fast arbitrary-ID search; or
- fast arbitrary deletion.

## Full checker contract

`alert_priority_queue_is_min_heap` follows this exact order:

1. reject NULL output with `INVALID_ARGUMENT`;
2. validate field shape;
3. preserve output and comparison counter on validation failure;
4. initialize a local Boolean result to true;
5. inspect every child index 1 through `size-1`;
6. add one saturating comparator call per child;
7. set the local result false when a child precedes its parent;
8. continue after every violation;
9. publish the Boolean last; and
10. return `OK`.

Success adds zero comparisons when `size` is 0; otherwise, it adds exactly
`size-1`, including when the Boolean result is false. Empty and singleton
valid states add zero and return true.

The checker intentionally separates status from order:

- malformed public field shape -> non-OK status, protected output/count;
- valid field shape but broken Heap order -> `OK`, output false, full
  comparison delta.

Continuing after a violation gives complete diagnostic coverage and makes
the count deterministic.

## Comparison counter

The same public `comparison_count` stores comparator calls from:

- insert parent tests;
- extraction sibling selection;
- extraction selected-child/candidate tests; and
- checker parent-child tests.

It saturates at `SIZE_MAX`.

To measure honestly:

1. record the count before the normal operation;
2. record it immediately after the operation;
3. call the checker;
4. record the checker delta separately.

Do not call the checker inside the timed or claimed normal operation.
Operation plus checker is an instrumented debug cycle with `O(n)` checker
work.

## Insertion and sift-up

Insertion preserves Module 10 precedence:

```text
validate
then full
then sequence exhausted
then growth allocation if needed
then mutation
```

Growth remains `0 -> 4 -> 8 -> 16 -> 32 -> 64` through a temporary
`realloc` result.

After all failure conditions are resolved:

1. build a local candidate with ID, priority, and `next_sequence`;
2. set hole index to current size;
3. while hole is nonroot, compare candidate with its parent;
4. if candidate does not precede parent, stop;
5. otherwise copy the parent record down into the hole;
6. move the hole to the parent index;
7. place candidate once at its final position;
8. increment size and next sequence; and
9. return success.

Moving parents down rather than swapping on every step reduces record
copies while producing the same logical trace. Count exactly one comparison
per parent test, including the final test that stops.

Appending first conceptually preserves complete shape. The implementation
does not publish size until repair finishes, so a partially filled new slot
is not yet live.

## Peek-min

After NULL-output, shape-validation, and empty checks, peek copies
`data[0]`. It makes zero record comparisons and changes no Queue field.
Output is committed only on success and must not alias the owned array.

## Extraction and sift-down

After NULL-output, shape-validation, and empty checks:

1. save `data[0]` as local result;
2. set `new_size = size - 1`;
3. when nonempty, save `data[new_size]` as local candidate;
4. start a hole at index 0;
5. calculate left child;
6. if left is outside `new_size`, stop;
7. select left initially;
8. if right exists, compare right with left and select the better child;
9. compare selected child with candidate;
10. if selected child does not precede candidate, stop;
11. copy selected child upward and move the hole down;
12. place candidate at the final hole;
13. publish `size = new_size`;
14. reset sequence only if size becomes zero;
15. publish output last; and
16. return success.

When both children exist, each level adds two comparisons: sibling choice,
then child versus candidate. A lone left child adds one. A leaf adds zero.

The implementation must choose the better child before comparing with the
candidate. Always choosing left can leave a better right child below a
worse root.

## Locked Stage A boundary

Stage A may use:

- synthetic alerts;
- letter labels `K,B,T,R,C,M,Q`;
- urgency numbers;
- arrival order;
- numbered spots;
- above/below language;
- handling, reading, moving, and checking in ordinary language.

It must not contain, in any case or code fence:

```text
heap
tree
root
parent
child
array
index
Priority Queue
PQ
insert
peek
extract
comparator
invariant
sift
O(
log
code
formula
```

Stage A contains no fenced block. Standard and linear forms have identical
labels, urgencies, relationships, questions, and scoring.

One valid later calibration arrangement for the Stage A arrivals is:

```text
B,R,Q,K,C,M,T
```

Do not reveal it before initial work is preserved.

## Stage B reveal fixture

Reveal insertions:

```text
50/4/0, 11/2/1, 80/3/2, 34/1/3, 62/2/4, 7/1/5
```

Final array:

```text
34/1/3, 11/2/1, 7/1/5, 50/4/0, 62/2/4, 80/3/2
```

Normal insertion comparison deltas:

```text
0,1,1,2,1,2
```

Extracting 34 uses candidate 80, selects child 7 over 11, and produces:

```text
7/1/5, 11/2/1, 80/3/2, 50/4/0, 62/2/4
```

## Locked Cognitive Pause

Starting state:

```text
81/1/1, 27/1/3, 12/2/2, 54/3/0, 68/4/4
capacity 8
size 5
next_sequence 5
comparison_count 0
```

Exactly three target headings:

1. map and check;
2. insert and repair upward; and
3. extract and repair downward.

Target 1:

```text
children(0) = 1,2
children(1) = 3,4
parent(4) = 1
checker status OK
checker output true
checker count 4
```

Target 2 inserts `35/1/5`:

```text
first index 5
parent tests 2,0
final IDs 81,27,35,54,68,12
normal comparisons 2
size 6
next_sequence 6
```

Target 3 extracts 81:

```text
candidate 68
choose 27 over 12
then lone left child 54
final IDs 27,54,12,68
normal comparisons 3
```

Checker calls are deliberately absent from Targets 2 and 3.

## Canonical Module 10 fixture

Insert:

```text
71/3/0, 88/1/1, 42/2/2, 17/1/3,
26/4/4, 9/2/5, 63/1/6
```

Exact arrays and insertion deltas:

```text
[71]                         +0
[88,71]                      +1
[88,71,42]                   +1
[88,17,42,71]                +2
[88,17,42,71,26]             +1
[88,17,42,71,26,9]           +1
[88,17,63,71,26,9,42]        +2
```

Normal build total: 8.

One checker of the final seven records adds 6. Checkers after every
insertion add:

```text
0+1+2+3+4+5+6 = 21
```

Combined instrumented build count: 29.

After reset, exact extraction states:

```text
88 -> [17,42,63,71,26,9]   +4
17 -> [63,42,9,71,26]      +2
63 -> [42,71,9,26]         +3
42 -> [9,71,26]            +2
9  -> [71,26]              +1
71 -> [26]                 +0
26 -> []                   +0
```

Normal drain total: 12. Checkers after current sizes
`6,5,4,3,2,1,0` add:

```text
5+4+3+2+1+0+0 = 15
```

Combined instrumented drain count: 27.

The stable public output matches Module 10:

```text
88,17,63,42,9,71,26
```

Module 10's unsorted drain used 21 comparisons.

## Complexity boundary

**Amortized** means a total cost is spread across many operations rather
than charged to only the operation that triggers growth.
**Geometric growth** means multiplying capacity by a fixed factor; this
course doubles it.

| Work | Required bound |
|---|---:|
| Heap peek-min | `O(1)` |
| Heap insertion excluding growth/checker | `O(log n)` |
| one growth insertion | `O(n)` allocation copying may occur |
| geometric insertion sequence | amortized `O(log n)` |
| Heap extract-min | `O(log n)` |
| full Heap-order checker | `O(n)` |
| arbitrary-ID search | `O(n)` |
| arbitrary-value deletion without location support | `O(n)` search plus repair |

`O(log n)` follows from complete-tree height, not from the values being
balanced like a BST.

## Structure contrasts

### Heap versus BST

- Heap: complete shape; parent-child comparator order; minimum at root;
  arbitrary search linear.
- BST: global left-lower/right-higher key order; shape may skew; minimum is
  leftmost; search cost depends on height.
- Heap equal priorities are valid and settled by unique sequence.
- The course strict BST rejects duplicate search keys.

### Heap versus sorted array

- Heap is a partial order.
- Sorted array is a total order.
- Sorted minimum-at-end insertion is `O(n)` and removal `O(1)`.
- Heap sift-up and extraction are `O(log n)`.
- One growth insertion may be `O(n)`; geometric insertion is amortized
  `O(log n)`.

### Heap versus Module 10 unsorted array

- Same ADT, comparator, types, capacity ladder, statuses, ownership, and
  stable output.
- Module 10 insert uses zero record comparisons and removal scans `O(n)`.
- Module 11 maintains path order with `O(log n)` sift-up and removes in
  `O(log n)`; a growth insertion may copy `O(n)` records.

### Binary Heap versus C dynamic-memory heap

The binary Heap is the course data structure. C's dynamic-memory heap is an
informal name for storage obtained through allocation functions. The binary
Heap's array may be allocated there, but it is not the same concept.

## Failure preservation

Preserve Module 10 precedence and atomicity:

- NULL output precedes Queue validation for checker, peek, and extraction;
- invalid shape precedes empty/full;
- full precedes sequence exhaustion;
- sequence exhaustion precedes growth;
- allocation failure preserves the old allocation;
- failed checker preserves output and comparison count;
- failed peek/extraction preserves output;
- all failures preserve all Queue fields and safely inspectable established
  slots.

Checker success with output false is not a status failure and legitimately
increments the comparison metric.

## Ownership and memory

`realloc` can move the entire array. Index relationships survive because
they are recalculated from positions; no node pointer is stored.

The Queue uniquely owns `data`. Do not shallow-copy a live Queue. Output
must not point anywhere inside the allocation. Destroy releases storage and
restores exact zero. Extracting the last record retains allocation and
capacity, resets sequence, and leaves inactive bits unspecified.

## Student and supplied test partition

Exactly three student functions match `test_student.c`:

1. multi-step sift-up, stable ties, exact trace, returned records, and
   separate operation/checker deltas;
2. priorities `5,41,17,55,70` producing correct
   `17,41,70,55`, plus a lone-left boundary and exact counts; and
3. at least two growth boundaries, checker after mutations, full-64 state,
   and complete rejected-insertion preservation.

Supplied core/private tests cover:

- NULL, exact zero, status strings, destroy;
- empty and singleton behavior;
- capacity ladder and allocation failure;
- ascending and descending inputs;
- stable duplicate priorities;
- canonical arrays and counts;
- checker true, false, continuation, saturation, and failure preservation;
- missing-right boundaries;
- full and sequence precedence;
- drain/reuse;
- deterministic randomized differential requests against an independent
  reference model; and
- broad invalid shapes.

## Safe wrong-child autopsy

Frozen priorities/records:

```text
5/5/0, 41/41/1, 17/17/2, 55/55/3, 70/70/4
```

After extracting 5, candidate 70 moves to root.

Correct:

```text
compare children 41 and 17
choose 17
compare 17 with candidate 70
final IDs 17,41,70,55
```

Faulty:

```text
always choose left 41
then lone left 55
final IDs 41,55,17,70
```

The first divergence is failure to compare right child 17 with left child
41. The faulty final root is outranked by child 17.

The program uses five fixed initialized records and checks every index
before access. It is memory-safe but violates Heap order. Repair child
selection; do not add storage or remove bounds.

## Integrity and security boundary

Treat the checker as an integrity control:

- it can detect direct Heap-order corruption;
- constant-time validation prevents a contradictory size from driving a
  scan;
- continuing after violation gives full pair coverage.

It cannot prove pointer provenance, allocation lifetime, ownership,
authenticity, scoring quality, delivery, durability, fairness, thread
safety, or security.

All data is synthetic. Do not read operational sources.

## Dijkstra capacity caveat

The 64-record cap bounds teaching work and tests. It is not a proof that a
general Dijkstra frontier fits.

Module 12 must do one of the following:

- prove an authorized fixture-specific upper bound no greater than 64;
- use a separately validated larger/configurable Heap; or
- propagate explicit insufficient-capacity failure and withhold a complete
  result claim.

Silently dropping pending graph work invalidates shortest-path correctness.

## Five release gates

1. **Gate A:** preserve informal urgency arrangement before formal terms.
2. **Gate B:** release reveal, then preserve exactly three pause targets
   before vocabulary and Stage C.
3. **Gate C:** preserve worksheet Sections A through F before Stage D.
4. **Gate D:** release 1,100-1,250-word textbook and exact-equivalent models;
   require labeled corrections before code.
5. **Gate E:** release student lab; require three TODOs, exactly three tests,
   traces, normal/checker deltas, autopsy, contrasts, and scope statement.

## Accessibility

- Standard and linear inquiry/worksheet forms contain identical facts and
  scoring.
- Every diagram has an exact linear equivalent.
- Permit drawing, tables, numbered prose, typing, dictation, tactile cards,
  or verbal description.
- Do not assess visual scanning speed, handwriting, drawing quality, or
  memorized jargon.
- Extended-time pause uses the same fixture and exactly three targets.
- Preserve first work and add labeled corrections.

## Instructor audit

- [ ] Stage A has no forbidden term or fenced block.
- [ ] Standard/linear IDs and prompts match.
- [ ] Pause has exactly three `## Target` headings.
- [ ] Locked pause arrays and counts are exact.
- [ ] Canonical build arrays total 8 normal comparisons.
- [ ] Canonical drain arrays total 12 normal comparisons.
- [ ] Checker adds zero when `n` is 0, otherwise exactly `n-1`, and
  continues after violation.
- [ ] Instrumented totals are 29 build and 27 drain.
- [ ] Peek reads root with zero comparisons.
- [ ] Better child is selected before candidate comparison.
- [ ] Lone-left case never reads a missing right child.
- [ ] Full, sequence, allocation, output, and state precedence match header.
- [ ] Three starter TODOs and student tests match code.
- [ ] Autopsy arrays are `17,41,70,55` and `41,55,17,70`.
- [ ] Heap/BST/sorted/unsorted/C-memory contrasts are explicit.
- [ ] Full checker cost is excluded from `O(log n)` operation claims.
- [ ] One growth insertion is allowed `O(n)` copying and geometric
  insertion is amortized `O(log n)`.
- [ ] Arbitrary Heap search is not called logarithmic.
- [ ] C ownership and no-alias rules remain.
- [ ] Security claims and 64-record Dijkstra caveat are bounded.
