# Instructor Lesson Plan - Module 11 Binary Heap

## 14-week delivery override - Week 9 main lab (140 of 180 minutes)

Run this block after the 40-minute Module 10 contract/baseline block. Module
11 provides the combined week's only submission. The longer two-meeting plan
below remains an optional resource. See the
[14-week delivery guide](../../Data_Structures_Course_2026_14_Week_Delivery_Guide.md).

| Combined-week minutes | Required live work |
|---:|---|
| 40-52 | Map the complete tree to an array and derive parent/child indexes. |
| 52-65 | Distinguish Heap order from sorted/BST order and trace sift-up/down. |
| 65-75 | Run the exactly-three-target pause and calibrate both traces. |
| 75-85 | Reuse the Module 10 contract and introduce the Heap checker. |
| 85-105 | Implement and test the invariant checker. |
| 105-125 | Implement and test insertion with sift-up. |
| 125-147 | Implement and test extraction with sift-down, including a left-only child. |
| 147-160 | Run three test categories, including stable ties, against the supplied reference baseline. |
| 160-170 | Compare measured Heap work with the Module 10 scan baseline. |
| 170-177 | Correct one sift trace and the combined evidence without erasing first work. |
| 177-180 | Verify one combined checklist and submit once for Week 9. |

The required submission contains Heap code, three focused tests, sift traces,
and the backend comparison. Treat the extended randomized differential run,
the bounded autopsy, and the rest of the full-package evidence as optional
after the core passes; do not create a separate Module 10 assignment.

## Module question

> Can a compact array avoid scanning every alert while still returning the
> highest-priority item quickly?

Plan for approximately three contact hours across two meetings, with
additional lab time as scheduled. Preserve the five gates and locked
fixtures even when timing changes.

## Five-gate control

| Gate | Release | Evidence required before next gate |
|---|---|---|
| A | Informal inquiry only | Preserved service, layered arrangement, repair, and complete-check reasoning |
| B | Formal reveal and pause | Responses under exactly three Target headings |
| C | One investigation form | Preserved Sections A through F |
| D | Textbook and models | Labeled corrections and one correct up/down trace |
| E | Student lab | Three TODOs, exactly three tests, output, metrics, autopsy, contrasts, and scope |

Instructor key, solution, and private tests remain closed.

## Before class

1. Scan both Stage A files case-insensitively for every forbidden word and
   verify they contain no fenced block.
2. Confirm standard/linear parity for `K,B,T,R,C,M,Q`, urgencies, spot
   relationships, questions, and scoring.
3. Confirm the pause has exactly three `## Target` headings.
4. Run solution core, extension, and bounded autopsy targets.
5. Confirm canonical totals: build 8, drain 12, checker sums 21 and 15,
   instrumented totals 29 and 27.
6. Confirm autopsy correct `17,41,70,55` and faulty `41,55,17,70`.
7. Prepare optional alert cards and numbered position cards. They support
   access but are not required.
8. Accept drawing, tables, numbered prose, typing, dictation, tactile
   modeling, and verbal response.
9. Use synthetic values only.

## Meeting A - Model and reason

### 1. Gate A retrieval without formal leakage - 8 minutes

Release one inquiry form. Do not say or display any forbidden formal term.
Use only alert, label, urgency, arrival, spot, above, below, move, check,
handle, next, and ordinary number language.

Students retrieve:

```text
K3, B1, T2, R1, C4, M2, Q1
```

Required service order is not revealed.

### 2. Read and compare work plans - 12 minutes

Students determine urgency-then-arrival service and describe the repeated
work of rereading all waiting alerts.

Observe:

- Does label accidentally rank an alert?
- Are B, R, and Q kept in arrival order?
- Does a student seek total ordering when only the next answer is needed?
- Can the student distinguish short repair from a complete check?

### 3. Invent the seven-spot arrangement - 15 minutes

The inquiry gives relationships:

```text
spot 0 above 1 and 2
spot 1 above 3 and 4
spot 2 above 5 and 6
```

Students place cards and state a nearby-pair promise. Do not correct toward
the formal structure yet. Require the first attempt to remain visible.

### 4. Pair comparison and repair - 8 minutes

Partners compare one local promise, one new-arrival route, and one
top-removal route. They name a stop condition and a complete checking idea.

Gate A closes when Sections A through F are preserved, not when they are
correct.

### 5. Gate B formal reveal - 22 minutes

Release `representation_reveal.md`. Define terms in vocabulary order:

1. preserved Priority Queue ADT and stable comparator;
2. binary tree and complete binary tree;
3. array/index implicit relationships;
4. Binary Heap and min-Heap;
5. Heap-order invariant and partial order;
6. append, sift-up, peek-min, extract-min, better child, sift-down;
7. invariant checker and instrumentation; and
8. Heap/BST/sorted/C-memory distinctions.

Use reveal insertions:

```text
50/4/0,11/2/1,80/3/2,34/1/3,62/2/4,7/1/5
```

Trace all parent calculations. Emphasize that 34 remains before smaller ID 7
because sequence 3 is earlier than 5.

Extract 34, choose child 7 over 11, and finish:

```text
7,11,80,50,62
```

### 6. Exactly-three-target Cognitive Pause - 5 minutes

Read the definitions and locked start aloud:

```text
81/1/1,27/1/3,12/2/2,54/3/0,68/4/4
capacity 8, size 5, next_sequence 5, comparison_count 0
```

The only Target headings are:

1. map and check;
2. insert and repair upward; and
3. extract and repair downward.

Vocabulary, notes, slides, classmates, and coding tools remain closed.
Extended time uses the identical state and targets.

### 7. Pause calibration - 12 minutes

Display:

```text
Target 1:
children(0)=1,2; children(1)=3,4; parent(4)=1
checker OK, true, count4

Target 2:
35 starts5, tests2 then0
81,27,35,54,68,12
normal count2

Target 3:
output81, candidate68
choose27, then lone-left54
27,54,12,68
normal count3
```

Students label corrections:

```text
mapping
order
upward
child choice
missing right
measurement
```

### 8. Gate C canonical build - 25 minutes

Release one worksheet. Students reuse Module 10 arrivals:

```text
71/3/0,88/1/1,42/2/2,17/1/3,26/4/4,9/2/5,63/1/6
```

Complete only the first insertion row. Students finish all arrays, parent
tests, and normal comparison deltas.

Hint ladder:

1. append at old size;
2. calculate parent;
3. compare priority;
4. on tie compare sequence;
5. move the whole record;
6. stop after a nonpreceding result.

### 9. Exit ticket - 5 minutes

Prompt:

> Why can root be minimum even though the array is not sorted?

Expected: every record has a chain of parents to root and no child outranks
its parent.

## Between meetings

Students preserve worksheet Sections A through F:

- build/map;
- checker/order;
- peek/drain;
- normal versus instrumented cost;
- four structure contrasts; and
- contracts, integrity, and cap.

Release Stage D only afterward. Corrections are added beside earlier work.

## Meeting B - Implement and verify

### 1. Gate D textbook/model calibration - 12 minutes

Retrieve without code:

1. formulas for parent and two children;
2. the child-exists boundary;
3. stable Heap order;
4. better-child choice;
5. checker delta at size `n`; and
6. why the Heap is neither BST nor sorted.

Then open the 1,100-1,250-word textbook and exact-equivalent models.

Gate D closes when each student can trace one upward and one downward step
and label normal versus checker work.

### 2. Gate E public contract - 15 minutes

Students locate the unchanged fields, statuses, and functions plus:

```text
alert_priority_queue_is_min_heap
```

Establish:

```text
checker: NULL output -> shape validation -> all child pairs -> output
insert: validation -> full -> sequence -> growth -> upward repair
extract: NULL output -> validation -> empty -> downward repair -> output
```

Review ownership, no-alias output, saturation, and complete-record moves.

### 3. TODO 1 checker - 22 minutes

Students implement:

1. local true result;
2. child loop 1 through size-1;
3. parent formula;
4. one counted stable comparison per child;
5. false on violation without early exit; and
6. output last.

Test empty, singleton, valid pause state, one violation, multiple violations,
counter saturation, NULL output, and malformed shape.

Ask students to state why valid shape plus false order is `OK`, not
`INVALID_STATE`.

### 4. TODO 2 insertion - 28 minutes

Students preserve Module 10 error and growth logic, then:

1. create local candidate;
2. begin hole at size;
3. compare with parent;
4. move parent down if outranked;
5. place candidate once; and
6. commit size and sequence.

Checkpoint:

```text
canonical final IDs 88,17,63,71,26,9,42
normal comparison total 8
```

The supplied allocation hook covers first and later growth failure. Student
tests do not call the private hook.

### 5. TODO 3 extraction - 28 minutes

Students:

1. save root and final candidate;
2. use new size for every boundary;
3. stop when left is absent;
4. compare siblings only when right exists;
5. select the better child;
6. compare selected child with candidate;
7. move selected child upward when needed;
8. place candidate;
9. reset sequence only after drain; and
10. publish output last.

Checkpoint:

```text
outputs 88,17,63,42,9,71,26
normal total 12
```

Stop at extraction of 63 and extraction of 9 to retrieve lone-left handling.

### 6. Instrumented checking - 12 minutes

For each mutation:

1. snapshot count;
2. call operation;
3. record normal delta;
4. call checker;
5. record checker delta.

Canonical expected:

```text
build 8 + 21 = 29
drain 12 + 15 = 27
```

State explicitly: the debug cycle is linear; a sift route is logarithmic.
One growth insertion may be linear because records are copied. With
geometric growth (doubling capacity), copying is amortized, meaning spread across many
insertions, so insertion is amortized logarithmic.

### 7. Exactly three student tests - 22 minutes

Require the template's exact categories:

1. multi-step sift-up, stable ties, exact arrays/outputs, separate deltas;
2. priorities `5,41,17,55,70` producing `17,41,70,55`, plus lone-left
   boundary and exact counts;
3. at least two growth boundaries, checks after mutations, fill 64, and
   complete preservation on rejected insertion.

Supplied private tests own randomized differential coverage.

### 8. Bounded wrong-child autopsy - 12 minutes

Students predict first.

```text
before 5,41,17,55,70
candidate 70
correct 17,41,70,55
faulty 41,55,17,70
```

First divergence: the faulty code chooses left child 41 without comparing
right child 17. The repair is better-existing-child selection followed by
child/candidate comparison.

The fixed five-record program checks every boundary. Do not call the logical
defect a memory error.

### 9. Contrast, integrity, and forward boundary - 10 minutes

Close with:

- Heap partial order versus BST global search order;
- Heap versus sorted and unsorted arrays;
- binary Heap versus C dynamic-memory heap;
- checker as an integrity control, not a security proof; and
- capacity 64 as a teaching bound, not a general Dijkstra guarantee.

## Formative misconceptions

Intervene if a student:

- uses alert ID in ordering;
- moves priority without ID and sequence;
- assumes left child must precede right child;
- claims all array positions are sorted;
- applies BST lower-left/higher-right rules;
- calls complete shape the same as BST balance;
- uses child formulas without checking against size;
- evaluates or reads a missing right child;
- always chooses left during sift-down;
- compares candidate with left before selecting the better sibling;
- forgets the final stopping comparison;
- increments the metric for arithmetic rather than comparator calls;
- lets the metric wrap;
- stops the checker at its first violation;
- treats checker false as a status failure;
- includes checker work in the normal `O(log n)` claim;
- claims every individual insertion is `O(log n)` despite possible growth
  copying;
- claims arbitrary Heap search is logarithmic;
- writes directly through the only pointer returned by `realloc`;
- publishes size before repair;
- updates output before success;
- shallow-copies the owner;
- confuses the binary Heap with C allocation memory;
- treats passing Heap order as proof of alert truth; or
- assumes capacity 64 proves general Dijkstra completion.

## Extension prompts

Use only after core correctness:

- Why can bottom-up Heap construction be linear even though repeated
  insertion is `O(n log n)`?
- What extra mapping could support faster decrease-key by alert identity?
- Why must a mutable priority trigger repair?
- How would a maximum Heap reverse only the comparator?
- What production capacity or allocation policy would Module 12 need?

Do not replace core work with extensions.

## Submission check

Students submit:

- exactly three implementation TODOs;
- exactly three student tests;
- warning-clean or instructor-CI output;
- locked pause and canonical traces;
- normal totals 8 and 12;
- checker totals 21 and 15;
- instrumented totals 29 and 27;
- bounded autopsy and regression;
- structure/memory contrasts;
- ownership and failure evidence;
- integrity/security limits;
- 64-record Dijkstra response; and
- corrected preserved artifacts.
