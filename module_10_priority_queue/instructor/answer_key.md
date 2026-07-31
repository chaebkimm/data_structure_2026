# Instructor Answer Key - Module 10

This key gives required meanings and exact canonical results. Student wording
may differ. Preserve initial responses and require labeled corrections;
do not reward memorized wording over a correct rule, trace, or test.

`ID/P/S` means alert ID, priority, and arrival sequence.

## Five-gate evidence map

| Gate | Evidence required before release of the next stage |
|---|---|
| A | Preserved first attempt for urgency order, equal-urgency rule, waiting risk, score change, and full-storage response |
| B | Preserved responses under exactly three Cognitive Pause target headings |
| C | Preserved worksheet Sections A through F, including trace, contracts, backend costs, policy risks, and spiral links |
| D | Labeled corrections using the textbook/models and one correct spoken, drawn, or written operation trace |
| E | Three code TODOs, exactly three original test categories, test output, counts, memo, autopsy, fairness explanation, and corrected prior work |

No drawing style, speed, or exact prose is part of these gates.

## Stage A - Initial inquiry

### A. Separate label from urgency

#### A1. Read arrival

- First arrival: K.
- Last arrival: C.

#### A2. Read urgency

B and R have the smallest urgency number, 1.

#### A3. Ignore the identifier

The letter is only an identifier. The stated service rule uses urgency, not
alphabetical order. For example, K arrived before B, but B has the smaller
urgency number.

### B. Apply a repeatable rule

#### B1. Service order

Using arrival to settle equal urgency:

```text
B, R, T, K, C
```

#### B2. Equal urgency

Handle B before R because B arrived earlier. At Stage A, another clearly
stated and repeatable tie rule is useful inquiry evidence, but students must
later correct it to earlier-arrival order for this module's contract.

#### B3. Arrival-only contrast

FIFO order is:

```text
K, B, T, R, C
```

The answers differ at the first serviced record: FIFO chooses K; the
urgency-first rule chooses B.

### C. New arrivals and waiting

#### C1. A more urgent arrival

M with urgency 1 is handled before waiting K with urgency 3. The rule ranks
the smaller urgency number first even though M arrived later.

#### C2. A long wait

Yes. C has urgency 4. If lower-numbered alerts keep arriving before C is
selected, C can wait indefinitely. That is a fairness risk.

### D. Changing a waiting score

#### D1. Silent change

T may move earlier. With arrival settling the new urgency-1 tie, the order
would become:

```text
B, T, R, K, C
```

The program must revisit any choice based on the old score.

#### D2. Required evidence

Accept an explicit controlled-update answer such as:

- who or what authorized the change;
- the old and new score;
- the update time;
- a version or generation number; or
- a defined operation that repairs the stored ordering.

A silent field edit is not sufficient.

### E. Meet a storage boundary

#### E1. State the policy

Any one explicit policy with its trade-off is acceptable at inquiry:

- refuse the new alert and report failure;
- deliberately remove a named existing class of alert; or
- require the source to slow or retry.

The Module 10 implementation freezes refusal at 64 live records. Refusal
does not prove the caller retained or retried the rejected alert.

#### E2. Preserve failure

If insertion is refused, all waiting alerts, their values, arrival facts,
service meaning, storage metadata, and diagnostic count remain unchanged.
The caller receives an explicit failure result.

### F. Initial synthesis

A strong initial answer:

> A stated urgency rule replaces pure arrival order, with a repeatable rule
> for equal urgency. The structure must spend work either while adding or
> while finding the next alert. Low-ranked alerts may wait too long, and a
> storage boundary needs an explicit failure policy.

Useful open questions include how ties are recorded, where search work
occurs, what happens on full storage, and how a waiting score may change.

## Stage B - Cognitive Pause

Starting state:

```text
index 0: 54/3/0
index 1: 81/1/1
index 2: 12/2/2
index 3: 27/1/3
index 4: 68/4/4
capacity 8
size 5
next_sequence 5
comparison_count 0
```

### Target 1 - Select without removing

`peek-min` reports:

```text
81/1/1
```

Alert 27 also has priority 1, but sequence 3 is later than sequence 1, so it
does not replace 81. Five records require four comparisons.

Final state:

```text
data identity unchanged
active records unchanged
size 5
capacity 8
next_sequence 5
comparison_count 4
```

Only the copied output and diagnostic count change.

### Target 2 - Extract, swap, and insert

`extract-min` reports `81/1/1` and adds four comparisons. The last live
record fills index 1:

```text
54/3/0, 68/4/4, 12/2/2, 27/1/3
```

Insert alert 35 with priority 1. It receives sequence 5 and appends:

```text
index 0: 54/3/0
index 1: 68/4/4
index 2: 12/2/2
index 3: 27/1/3
index 4: 35/1/5
```

Final metadata:

```text
size 5
capacity 8
next_sequence 6
comparison_count 4
```

The next logical alert is 27, because its priority ties 35's priority and
sequence 3 is earlier than 5.

### Target 3 - Separate ties from policy

Stable behavior orders records only within one priority. It does not move
priority-4 alert 68 ahead of a continuing stream of priority-1 records.
Alert 68 can therefore starve.

A silent edit to alert 54 bypasses the public contract, erases update
evidence, and may break a future sorted or Heap backend's stored order.

Accept one explicit surrounding policy, such as controlled aging, a
maximum-wait escalation, an authorized decrease-key operation, or a
versioned duplicate entry whose older version can be identified as stale.

## Stage C - Investigation

### A. Apply the comparator

#### A1. Compare pairs

1. `88/1/1` precedes `42/2/2`: priority 1 is smaller than 2.
2. `88/1/1` precedes `17/1/3`: priorities tie and sequence 1 is earlier
   than 3.
3. `42/2/2` precedes `9/2/5`: priorities tie and sequence 2 is earlier
   than 5.

#### A2. Complete logical service order

```text
88, 17, 63, 42, 9, 71, 26
```

#### A3. Exclude alert ID

Alert 42 precedes alert 9 even though 9 is the smaller numeric ID. Equal
priority is settled by sequence 2 before sequence 5, not by ID.

### B. Trace the unsorted backend

#### B1. Insertion state

```text
index 0: 71/3/0
index 1: 88/1/1
index 2: 42/2/2
index 3: 17/1/3
index 4: 26/4/4
index 5: 9/2/5
index 6: 63/1/6
index 7: inactive
```

The first insertion grows capacity from 0 to 4. The fifth grows it from 4
to 8. Insertion makes zero record comparisons.

#### B2. Peek-min

Output:

```text
88/1/1
```

Seven live records require six comparisons. Final facts:

```text
same data identity
same seven active records and physical positions
size 7
capacity 8
next_sequence 7
comparison_count 6
```

#### B3. Every extraction

Starting again with `comparison_count == 0`:

| Extracted ID | Remaining active physical IDs | Comparisons added | Running total |
|---:|---|---:|---:|
| 88 | `71,63,42,17,26,9` | 6 | 6 |
| 17 | `71,63,42,9,26` | 5 | 11 |
| 63 | `71,26,42,9` | 4 | 15 |
| 42 | `71,26,9` | 3 | 18 |
| 9 | `71,26` | 2 | 20 |
| 71 | `26` | 1 | 21 |
| 26 | empty | 0 | 21 |

The complete extracted ID order is:

```text
88,17,63,42,9,71,26
```

#### B4. Drained state

```text
data: same owned non-NULL allocation
capacity: 8
size: 0
next_sequence: 0
comparison_count: 21
```

All former physical records are inactive. Their old bits need not be
cleared and have no logical Queue meaning.

### C. Check representation and contracts

#### C1. Classify states

Assume omitted `comparison_count` is zero.

1. `data=NULL,size=0,capacity=0,next=0`: valid exact-zero state.
2. Non-NULL data, `size=0,capacity=8,next=0`: valid allocated-empty state.
3. Non-NULL data, `size=5,capacity=4,next=5`: invalid because size exceeds
   capacity.
4. Non-NULL data, `size=2,capacity=8,next=2`, live sequences 0 and 0:
   invalid because live sequences must be unique. Important: the
   constant-time validator cannot detect this record-level violation.
5. Non-NULL data, `size=2,capacity=8,next=2`, live sequences 0 and 1:
   valid, assuming ownership, allocation extent, and other rules hold.

Also reject every capacity other than:

```text
0, 4, 8, 16, 32, 64
```

#### C2. Preserve failed operations

1. Empty peek/extraction: all five fields, allocation identity, established
   slots, and caller output remain unchanged.
2. Growth allocation failure: the old pointer remains owned; capacity,
   size, next sequence, count, and every established slot remain unchanged.
3. Full insertion: all 64 records and all five fields remain unchanged;
   result is `ALERT_PRIORITY_QUEUE_FULL`.
4. Sequence exhaustion: every field and slot remains unchanged; result is
   `ALERT_PRIORITY_QUEUE_SEQUENCE_EXHAUSTED`.

If a Queue is both full and sequence-exhausted, `FULL` takes precedence.
Invalid visible state takes precedence over both.

#### C3. Metric versus logical state

Peek applies the comparator but does not add, remove, or reorder a logical
record. It therefore changes the diagnostic count while preserving the
logical collection. At `SIZE_MAX`, the count stays at `SIZE_MAX`; it never
wraps to zero.

#### C4. Storage lifetime

Peek and extraction return copied records so the caller does not receive
ownership of an interior array location. An output inside `data` would
alias owned storage and could be overwritten during extraction. A shallow
copy of the owning Queue duplicates the pointer but not the allocation,
creating conflicting owners and double-release risk.

### D. Compare two array backends

#### D1. Unsorted-array costs

| Operation | Comparator calls | Time |
|---|---:|---:|
| insert without growth | 0 | `O(1)` |
| one insert that grows | 0 | `O(n)` because copying may occur |
| long sequence of inserts | 0 | amortized `O(1)` per insert |
| peek-min with `n` records | `n - 1` | `O(n)` |
| extract-min with `n` records | `n - 1` | `O(n)` |

Swap-last work after the extraction scan is `O(1)`.

#### D2. Paper-only sorted array

Worst to best, with the minimum at the removable right end:

```text
26, 71, 9, 42, 63, 17, 88
```

Full records:

```text
26/4/4, 71/3/0, 9/2/5, 42/2/2, 63/1/6, 17/1/3, 88/1/1
```

Insertion is `O(n)` because records may shift to open the ordered position.
Peek-min reads the last live position in `O(1)`. Extract-min reduces size
at that end in `O(1)`. If minimum were at index 0, extraction would shift
all survivors and be `O(n)`.

#### D3. Two workloads

Insert-heavy:

```text
unsorted: 0 record comparisons
paper sorted: 0 + 1 + ... + 31 = 496 comparisons
```

Removal-heavy after preload and reset:

```text
unsorted: 31 + 30 + ... + 0 = 496 comparisons
sorted with minimum at removable end: 0 record comparisons
```

#### D4. Backend-selection memo

Model response:

> For many insertions followed by rare minimum reports, choose the unsorted
> array because ordinary insertion appends with zero record comparisons and
> geometric growth gives amortized constant insertion. For a fixed prepared
> batch followed by many removals, a sorted worst-to-best array can justify
> its construction cost because the minimum stays at the removable end.
> Neither backend is universally faster; the operation mixture decides.

### E. Analyze policy hazards

#### E1. Starvation

After priority-4 alert 26 arrives, continually insert at least one
priority-1 alert before the waiting priority-1 group becomes empty. Every
new priority-1 alert still ranks ahead of priority 4, so 26 can wait
indefinitely. Stable ties order priority-1 alerts among themselves; they do
not move 26 across priority levels.

#### E2. Mutable priority

Editing an active record through `data` bypasses validation, update
authorization, and the abstraction boundary. The current unsorted backend
rescans, but that accident does not make the edit supported. A sorted array
or Heap relies on stored positional rules, so an unannounced edit can leave
the record in a position inconsistent with those rules.

#### E3. Update strategies

A duplicate-entry strategy may store:

- one stable alert identity plus a version or generation; or
- one identity plus the client's current best priority.

When an entry leaves, the client compares it with current state and ignores
an older version. Decrease-key instead needs a defined operation and a
backend repair.

#### E4. Safe SOC interpretation

The score and implementation are a synthetic scheduling model. Neither the
number nor passing tests proves authenticity, severity, timeliness,
completeness, correct classification, fair staffing, or successful real
handling.

### F. Connect the spiral

#### F1. Queue versus Priority Queue

FIFO:

```text
71, 88, 42, 17, 26, 9, 63
```

Priority Queue:

```text
88, 17, 63, 42, 9, 71, 26
```

FIFO selects the oldest waiting item. The Priority Queue selects the
smallest priority, then the earliest sequence.

#### F2. Heap role

A minimum Heap will preserve the same comparator and outputs while avoiding
a full scan. Peek-min should become `O(1)` and extract-min should become
`O(log n)` instead of `O(n)`. `log n` describes the height of the compact
binary Heap and is formally introduced in Module 11.

#### F3. Weighted exploration

FIFO is appropriate when every step has equal cost, as in BFS. When path
costs differ, the next work item may need to be the vertex with the smallest
currently known total cost, which is a minimum-priority decision.

### G. Exactly three student tests

The student's values and operation sequences must be original. These are
models, not values students must copy.

#### G1. Mixed priorities and stable ties

Insert:

```text
900/2, 100/1, 50/2, 700/1
```

Assigned sequences are 0 through 3. Expected extraction IDs:

```text
100, 700, 900, 50
```

This proves IDs do not rank records and both priority ties remain stable.

#### G2. Growth and swap-scrambled storage

Insert at least five original records so successful growth crosses:

```text
capacity 4 -> capacity 8
```

Extract a minimum that is not in the last physical slot, snapshot the
fill-from-last state, insert another record, then drain and compare every
output with a small independent comparator-based model.

#### G3. Failure preservation

First call empty peek or extraction with a recognizable output record and
prove output plus Queue state remain unchanged. Then fill the Queue to 64,
snapshot all five fields and all 64 live slots, attempt one more insertion,
and prove `FULL` plus exact preservation.

The student test build does not expose the allocation-failure hook. Forced
growth failure is covered by the supplied core and instructor tests.

Merely repeating a supplied test or using three names for one claim does
not satisfy the three categories.

### H. Bounded autopsy

#### H1. Correct selection

For:

```text
80/2/0, 91/1/1, 17/1/2, 44/3/3
```

the correct first ID is 91.

#### H2. First divergence

The faulty `less than or equal priority` scan selects ID 17. Its first
wrong decision occurs when it replaces `91/1/1` with `17/1/2` merely
because both priorities are 1.

Correct scan table:

| Compared index | Candidate before | Replace? | Candidate after | Reason |
|---:|---:|:---:|---:|---|
| 1 | 0 | yes | 1 | priority 1 is smaller than 2 |
| 2 | 1 | no | 1 | priority ties; sequence 1 is earlier than 2 |
| 3 | 1 | no | 1 | priority 3 is larger than 1 |

The faulty assumption is that a later equal-priority record should replace
the earlier one. The contract instead requires smaller arrival sequence.
Choosing the smallest alert ID would also be wrong because ID is not a
comparison field.

#### H3. Repair and regression

Repair:

```text
later precedes candidate only when:
later priority is smaller
or priorities tie and later sequence is smaller
```

Regression: insert two or more same-priority records with misleading IDs,
then assert extraction follows increasing assigned sequence.

Exact example:

```text
insert IDs 700, 4, 300, all at priority 1
assigned sequences 0, 1, 2
expected extraction IDs 700, 4, 300
faulty first selection 300
```

All four fixture positions and all loop indexes are bounded. That fact
makes the autopsy memory-safe; it does not make the faulty service decision
correct. Even the repaired course comparator does not prove that a real
alert's assigned score is accurate or fair.

### I. Exit reflection

#### I1. Three-sentence macro answer

> A stable minimum Priority Queue selects the smaller priority and uses
> earlier arrival sequence for a tie. This unsorted-array backend inserts
> in amortized `O(1)` time but scans in `O(n)` time for peek or extraction.
> Stable ties do not prevent starvation, and a course score is not proof of
> real severity.

#### I2. Correct the incomplete claim

> A Priority Queue follows its programmed comparator; it does not establish
> real-world importance or fairness. This implementation is stable only
> among equal-priority records, and lower-ranked records can starve.

## Stage E - Lab implementation key

### TODO 1 - comparator and minimum-index scan

Required behavior:

```text
candidate index = 0
for each live index 1 through size - 1:
    increment comparison_count unless already SIZE_MAX
    replace candidate only if:
        later priority is smaller
        or priorities tie and later sequence is smaller
return candidate index
```

The helper is called only for a valid nonempty Queue. It must make exactly
`size - 1` comparator calls and must not use alert ID.

### TODO 2 - insertion and growth

Required decision order:

```text
validate
if size == 64: FULL
if next_sequence == SIZE_MAX: SEQUENCE_EXHAUSTED
if size == capacity:
    candidate capacity = 4 when zero, otherwise twice capacity
    realloc through a temporary pointer
    on NULL: ALLOCATION with complete preservation
    commit pointer and capacity
append ID, priority, current next_sequence
increase size
increase next_sequence
OK
```

The accepted capacity ladder is exact:

```text
0, 4, 8, 16, 32, 64
```

No record comparison occurs during insertion.

### TODO 3 - extract-min

Required behavior:

```text
reject NULL output
validate
reject empty
scan minimum
save selected record
replace selected slot from final live slot when positions differ
decrease size
if now empty: next_sequence = 0
publish saved output
OK
```

Retain allocation, capacity, comparison count, and inactive physical bits.

### Canonical lab checkpoints

After canonical insertion:

```text
status: ok
capacity: 8
size: 7
next_sequence: 7
comparison_count: 0
```

One peek:

```text
record: 88/1/1
comparisons: 6
logical records unchanged
```

After comparison reset and complete drain:

```text
order: 88,17,63,42,9,71,26
comparisons: 21
data identity retained
capacity: 8
size: 0
next_sequence: 0
```

Required failure evidence:

```text
empty output preserved
growth-failure state and slots preserved
full state and slots preserved
sequence-exhausted state and slots preserved
invalid state precedes empty/full
NULL output precedes Queue validation
full precedes sequence exhaustion
```

### Operation-count experiment

For a 32-record insert-heavy worst-position sorted workload:

```text
unsorted insert comparisons: 0
paper sorted insert comparisons: 496
```

For a preloaded 32-record complete drain:

```text
unsorted extract comparisons: 496
paper sorted extract comparisons: 0
```

Do not count array copying as a record-comparator call. Report it separately
through time complexity.

## Priority Queue Autopsy conclusion

Expected prediction and observation:

```text
correct selected ID: 91
faulty selected ID: 17
first divergence: later equal-priority sequence replaces earlier sequence
smallest repair: use strict priority-then-sequence comparator
regression: equal priority extracts in increasing arrival sequence
```

The bounded program is memory-safe. The defect is a service-rule violation,
not an out-of-bounds write or allocation failure.

## Final gate decision

Open revision or completion only when the evidence supports all of these:

- comparator uses no hidden ID rule;
- capacity and ownership rules hold;
- failure paths are atomic;
- comparison counts are exact before saturation;
- canonical and original tests both pass;
- physical and logical order are distinguished;
- sorted-array analysis uses minimum at the removable end;
- starvation is distinguished from stable ties;
- mutable priority is treated as a controlled operation or policy; and
- security claims remain limited to the synthetic scheduling model.
