# Instructor Answer Key - Module 11

Student wording may differ. Require the exact rule, state, or evidence rather
than memorized prose. Preserve first attempts and label corrections.

## Stage A - Informal inquiry

### A. Service promise

Required handling order:

```text
B, R, Q, T, M, K, C
```

B, R, and Q share urgency 1 and keep arrival order. T and M share urgency 2
and keep arrival order. Alphabetical order is excluded; for example, C is
alphabetically early but has urgency 4 and leaves last.

### B. Repeated work

The scan-style plan reads seven alerts for the first decision, then reads
the remaining six, then five, and so on. A strong alternative proposal says
one known spot can hold the next alert while only selected nearby
relationships are maintained; it need not fully order every waiting alert.

### C. One valid layered arrangement

Many first arrangements are useful inquiry evidence. One later-calibrated
valid arrangement is:

```text
spots 0 through 6: B,R,Q,K,C,M,T
```

Immediate relationships:

```text
B above R and Q
R above K and C
Q above M and T
```

Every upper alert is handled no later than either immediately lower alert
under urgency then arrival. This local promise prevents a later alert from
outranking spot 0 through an unchecked chain. Sequence order keeps B before
R before Q.

### D. Repair

A newly arrived, more urgent alert begins at the next open spot and may
trade places along the immediate route above it. It stops when no upper
alert is outranked or when it reaches spot 0.

If B leaves the calibrated seven-alert arrangement, moving final alert T to
spot 0 and repairing yields:

```text
R,T,Q,K,C,M
```

First choose R over Q because R arrived earlier at urgency 1. R moves to
spot 0. Candidate T at spot 1 already belongs before K and C, so repair
stops.

### E. Silent mistake

A lower alert that should precede the alert above it breaks the local
promise, so a chain no longer proves spot 0 is next. A full check inspects
each of the six immediate relationships. Report that complete-check work
separately from the short change route.

### F. Initial synthesis

Model answer:

> A compact layered arrangement can keep the next alert at one known spot
> if every immediate upper/lower pair follows urgency then arrival. A new or
> moved alert repairs only one short route. A separate complete check can
> detect a silent broken relationship, but that checking has its own cost.

## Stage B - Reveal fixture

Reveal insertions:

```text
50/4/0, 11/2/1, 80/3/2, 34/1/3, 62/2/4, 7/1/5
```

Arrays:

```text
[50]                         +0
[11,50]                      +1
[11,50,80]                   +1
[34,11,80,50]                +2
[34,11,80,50,62]             +1
[34,11,7,50,62,80]           +2
```

Total normal insertion comparisons: 7.

Final tree:

```text
root 34
children of 34: 11,7
children of 11: 50,62
left child of 7: 80
right child of 7: missing
```

Extracting 34:

```text
candidate 80
compare children 11 and 7; choose 7
compare 7 with 80; move 7
final IDs 7,11,80,50,62
normal comparisons 2
```

Alert 34 precedes alert 7 because equal priority uses earlier sequence 3
before 5, not smaller ID.

## Stage B - Cognitive Pause

Starting IDs:

```text
81,27,12,54,68
```

### Target 1 - Map and check

```text
children of index 0: 1 and 2
children of index 1: 3 and 4
parent of index 4: 1
```

Every pair passes:

```text
81 before 27 by earlier equal-priority sequence
81 before 12 by smaller priority
27 before 54 and 68 by smaller priority
```

Checker:

```text
status OK
output true
comparisons 4
```

### Target 2 - Insert and repair upward

`35/1/5` begins at index 5.

```text
compare with parent index 2, record 12/2/2: 35 precedes; move 12 down
compare with parent index 0, record 81/1/1: 81 is earlier; stop
```

Final:

```text
81/1/1,27/1/3,35/1/5,54/3/0,68/4/4,12/2/2
size 6
capacity 8
next_sequence 6
normal comparisons 2
```

### Target 3 - Extract and repair downward

Output is `81/1/1`. Candidate is `68/4/4`, with new size 4.

```text
compare children 27 and 12; choose 27                    +1
compare 27 with candidate 68; move 27                    +1
at index 1, lone left child 54 exists
compare 54 with candidate 68; move 54                    +1
```

Final:

```text
27/1/3,54/3/0,12/2/2,68/4/4
normal comparisons 3
```

No right record is read at index 1 because its calculated index 4 is not
below new size 4.

## Stage C - Investigation

### A. Build and map

#### A1. Exact insertion trace

| Added | First index | Parents tested | Comparisons | Final IDs |
|---|---:|---|---:|---|
| `71/3/0` | 0 | none | 0 | `71` |
| `88/1/1` | 1 | 0 | 1 | `88,71` |
| `42/2/2` | 2 | 0 | 1 | `88,71,42` |
| `17/1/3` | 3 | 1,0 | 2 | `88,17,42,71` |
| `26/4/4` | 4 | 1 | 1 | `88,17,42,71,26` |
| `9/2/5` | 5 | 2 | 1 | `88,17,42,71,26,9` |
| `63/1/6` | 6 | 2,0 | 2 | `88,17,63,71,26,9,42` |

Total: 8.

#### A2. Final map

```text
index 0 88/1/1: children 1 and 2
index 1 17/1/3: parent 0, children 3 and 4
index 2 63/1/6: parent 0, children 5 and 6
index 3 71/3/0: parent 1, no children
index 4 26/4/4: parent 1, no children
index 5 9/2/5: parent 2, no children
index 6 42/2/2: parent 2, no children
```

Appending at each old size fills the next left-to-right position. Formulas
derive relationships, so no child pointer is stored.

### B. Check without claiming sorting

#### B1. Direct pairs

| Child | Parent | Parent record | Child record | Result |
|---:|---:|---|---|---|
| 1 | 0 | `88/1/1` | `17/1/3` | pass |
| 2 | 0 | `88/1/1` | `63/1/6` | pass |
| 3 | 1 | `17/1/3` | `71/3/0` | pass |
| 4 | 1 | `17/1/3` | `26/4/4` | pass |
| 5 | 2 | `63/1/6` | `9/2/5` | pass |
| 6 | 2 | `63/1/6` | `42/2/2` | pass |

#### B2. Checker

From metric zero:

```text
status OK
output true
comparisons 6
```

It continues after a violation to check all direct pairs, provide complete
diagnostic coverage, and preserve the exact rule: zero comparisons when
`n` is 0, otherwise `n-1`.

#### B3. Not sorted

Record 71 at index 3 physically precedes record 9 at index 5, but priority 2
record 9 leaves before priority 3 record 71. This is valid because those
records are not a required parent-child pair.

#### B4. Shape versus order

1. Valid fields with one bad pair: checker returns `OK`, writes false, and
   scans all pairs.
2. Size greater than capacity: validation returns `INVALID_STATE`; output
   and counter are preserved.
3. A right-without-left gap cannot be represented by the required contiguous
   live prefix. If right index is below size, the smaller left index is also
   live. Any external drawing claiming otherwise is not this representation.

### C. Peek and extract

#### C1. Peek

```text
output 88/1/1
normal comparisons 0
Queue fields and records unchanged
```

#### C2. Drain

| Step | Output | Candidate | Final IDs | Delta |
|---:|---:|---:|---|---:|
| 1 | 88 | 42 | `17,42,63,71,26,9` | 4 |
| 2 | 17 | 9 | `63,42,9,71,26` | 2 |
| 3 | 63 | 26 | `42,71,9,26` | 3 |
| 4 | 42 | 26 | `9,71,26` | 2 |
| 5 | 9 | 26 | `71,26` | 1 |
| 6 | 71 | 26 | `26` | 0 |
| 7 | 26 | none needed | empty | 0 |

Output:

```text
88,17,63,42,9,71,26
```

Normal total: 12.

#### C3. Lone-left cases

- Extracting 63 reaches index 1 with lone left child 71.
- Extracting 9 reaches root with lone left child 71.

Each lone-left level makes one child/candidate comparison and reads no right
record because `right >= new_size`.

#### C4. Drained state

```text
data same non-NULL owned allocation
capacity 8
size 0
next_sequence 0
comparison_count 12
former values inactive
```

### D. Measurement and costs

#### D1. Instrumentation totals

Build:

```text
normal 8
checker 0+1+2+3+4+5+6 = 21
combined 29
```

Drain:

```text
normal 12
checker 5+4+3+2+1+0+0 = 15
combined 27
```

#### D2. Costs

**Amortized** means a total cost is spread across many operations.
**Geometric growth** means multiplying capacity, here doubling it.

| Work | Time | Reason |
|---|---:|---|
| peek-min | `O(1)` | root copy |
| insert without growth | `O(log n)` | one upward route |
| one growth insertion | `O(n)` may occur | allocation copying |
| geometric insertion sequence | amortized `O(log n)` | copying cost spread across many insertions |
| extract-min | `O(log n)` | one downward route |
| full checker | `O(n)` | all nonroot records |
| arbitrary ID search | `O(n)` | no ID search order |

Checker after every mutation makes the combined debug cycle `O(n)`.

#### D3. Module 10 comparison

```text
Module 10 insertion: 0
Module 11 insertion: 8
Module 10 drain: 21
Module 11 drain: 12
```

The Heap spends comparisons maintaining paths during insertion and reduces
minimum-removal comparisons.

### E. Contrasts

#### E1. Heap versus BST

Heap left/right positions are shape positions, not global lower/higher key
regions. Heap minimum is root. BST minimum is leftmost. Arbitrary Heap
search is linear; BST search follows ordering and depends on height.

#### E2. Heap versus sorted sequence

The Heap orders parent-child pairs only. A sorted minimum-at-end array uses
linear insertion and constant minimum removal. Heap sift-up and extraction
are logarithmic; one growth insertion may be linear, while a geometric
insertion sequence is amortized logarithmic.

#### E3. Heap versus Module 10

Public comparator, outputs, fields, statuses, growth, and ownership remain.
Physical invariant and costs change from scan-at-service to path repair.

#### E4. Binary Heap versus C memory

The binary Heap is a data structure. C dynamic-memory heap is an allocation
source. The structure may own an array allocated from that source.

### F. Contracts and scope

#### F1. Failure preservation

Every status failure preserves all Queue fields and safely established
slots. Checker failure also preserves Boolean output and count. Empty
peek/extraction preserves record output. Full, sequence exhaustion, and
allocation failure consume no sequence and publish no mutation.

#### F2. Records and ownership

Move all three record fields together. Output inside data violates the
no-alias precondition. Shallow-copying duplicates the owned pointer and can
cause double release.

#### F3. Integrity

The checker detects a child outranking its parent. It cannot prove pointer
lifetime, ownership, authentic alerts, correct scoring, real severity, or
overall security.

#### F4. Cap

If Dijkstra may need more than 64 pending records, either prove a smaller
authorized bound, use a separately tested larger/configurable Heap, or
return explicit insufficient-capacity failure and withhold a complete
result.

### G. Exactly three tests

Required categories match the student test template:

1. multi-step sift-up, stable ties, exact state, returned records, and
   separate normal/checker deltas;
2. priorities `5,41,17,55,70` giving `17,41,70,55`, plus a lone-left case;
3. two growth boundaries, checker after mutations, full 64, and exact
   preservation.

### H. Autopsy

Frozen:

```text
5/5/0,41/41/1,17/17/2,55/55/3,70/70/4
```

Correct:

```text
output 5
candidate 70
choose right child 17 over left 41
final IDs 17,41,70,55
```

Faulty:

```text
choose left 41 automatically
then move lone left 55
final IDs 41,55,17,70
```

First divergence is failing to compare siblings 41 and 17. Repair selects
the better existing child first. All five positions are bounded, so the
defect is logical rather than an invalid access.

### I. Synthesis

Model:

> A complete binary tree stored in an array gives logarithmic-height repair
> routes. Min-Heap order keeps the stable minimum at root without globally
> sorting records. Sifting and extraction are `O(log n)`; one growth insert
> may be `O(n)`, insertion is amortized `O(log n)`, peek is `O(1)`, and the
> separate full checker is `O(n)`.

Correction:

> A Heap is neither a sorted sequence nor a BST. Checking after every
> mutation adds linear debug work and is not free.

## Stage E implementation key

### TODO 1 - checker

```text
reject NULL output
validate
result = true
for child 1 through size-1:
    parent = (child-1)/2
    add one saturating comparison
    if child precedes parent: result = false
publish result
OK
```

Do not stop early.

### TODO 2 - insertion

Preserve validation/full/sequence/growth precedence. Hold a local candidate,
move each outranked parent down, place candidate once, then commit size and
sequence.

### TODO 3 - extraction

Save root and final candidate. At each level:

```text
if no left: stop
selected = left
if right exists:
    compare right with left
    selected = better child
compare selected with candidate
if candidate already comes first: stop
move selected upward
```

Place candidate, commit size/sequence, publish output last.

## Canonical lab checkpoints

```text
build IDs 88,17,63,71,26,9,42
build normal 8
one final checker delta 6
peek 88, delta 0
drain 88,17,63,42,9,71,26
drain normal 12
instrumented build 29
instrumented drain 27
drained capacity 8, size 0, next 0
```

## Final gate decision

Require:

- exact formulas and bounded child checks;
- complete comparator and whole-record movement;
- checker true/false/status distinction;
- normal/checker measurement separation;
- canonical and original tests;
- wrong-child autopsy repair;
- structure contrasts;
- ownership/failure evidence; and
- bounded integrity/security/Dijkstra claims.
