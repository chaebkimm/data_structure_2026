# Instructor Lesson Plan - Module 10 Priority Queue

## Module question

> If urgent alerts should be processed before routine alerts, what replaces
> arrival order, and what does that choice cost?

Plan for approximately three contact hours across two meetings, with
additional lab time where the course schedule provides it. Times are
adjustable. The five gates, exact fixtures, and evidence conditions are
not.

## Five-gate control

| Gate | Release | Required preserved evidence | Still withheld |
|---|---|---|---|
| A | Initial inquiry only | Urgency order, tie proposal, waiting risk, score-change reasoning, and full-storage policy | Formal names, operation names, sequences, backend, formulas, code, answers |
| B | Representation reveal and Cognitive Pause | Responses under exactly three target headings | Vocabulary during the timed pause, investigation, textbook, code |
| C | One investigation worksheet | Sections A through F attempted and preserved | Textbook, models, lab, solution |
| D | Beginner textbook and models | Labeled corrections and one correct operation trace | Lab until calibration; instructor and solution files |
| E | Student lab package | Three TODOs, exactly three test categories, output, counts, memo, autopsy, policy explanation | Instructor key, solution, private extensions |

If a student is absent, use the same gate evidence asynchronously. Do not
combine stages into one packet merely to recover time.

## Before class

1. Verify the public header, reference solution, core tests, private
   extensions, and bounded autopsy.
2. Confirm that capacity validation accepts exactly
   `0,4,8,16,32,64`.
3. Confirm the canonical extraction order:

   ```text
   88,17,63,42,9,71,26
   ```

4. Confirm the exact swap-last states and comparison totals in the answer
   key.
5. Run release packaging only after source verification. Confirm a second
   packaging attempt refuses to overwrite archives.
6. Keep `instructor/`, `code/solution/`, and
   `code/tests/test_extension.c` private.
7. Prepare standard and linear forms together. They must use identical
   records, priorities, sequences, operation order, questions, and scoring.
8. Prepare optional record cards labeled `ID/P/S` and numbered index cards
   0 through 7. Cards support modeling; they are not required.
9. Confirm that drawing, indexed tables, numbered prose, typing, dictation,
   and tactile or verbal models are accepted.
10. Use only synthetic alert values. Do not connect the activity to live
    logs, feeds, files, networks, accounts, or services.

## Meeting A - Model and reason

### 1. Retrieval in ordinary language - 8 minutes

Before Gate A, avoid Priority Queue, comparator, sequence, dynamic array,
backend, complexity notation, and operation names.

Ask:

- In Module 7, which waiting event left first?
- What information did `size` and `capacity` describe in an ArrayList?
- What had to remain unchanged when growth failed?
- Could an identifier safely double as an urgency score?
- What policy did a fixed storage boundary require?

Accept everyday descriptions such as "oldest waiting," "used spaces,"
"available spaces," and "the request did not happen."

### 2. Gate A - Initial inquiry - 15 minutes

Release exactly one Stage A form.

Fixture:

```text
arrival: K, B, T, R, C
urgency: 3, 1, 2, 1, 4
```

Students:

1. separate arrival, label, and urgency;
2. invent a repeatable equal-urgency rule;
3. contrast urgency order with arrival-only order;
4. reason about a newly arriving urgency-1 alert;
5. identify indefinite waiting;
6. reason about a silently changed score; and
7. choose and explain one full-storage policy.

Observe without supplying the formal answer:

- Does alphabetical order enter the rule?
- Does the student state which numeric direction means more urgent?
- Is the tie rule repeatable?
- Can the student distinguish waiting fairness from storage safety?
- Does a failed insertion preserve earlier facts?
- Does a score change trigger reconsideration?

Gate A closes only when the first response is preserved. Accuracy is not
the release condition.

### 3. Pair comparison - 5 minutes

Partners identify:

1. one shared service rule;
2. one different tie proposal; and
3. one unresolved policy question.

A partner may read, describe, or transcribe without replacing the author's
reasoning.

### 4. Gate B - Formal reveal - 18 minutes

Release `representation_reveal.md`. Define each new term at first use:

- data structure;
- abstract data type;
- Priority Queue;
- minimum priority;
- insert, peek-min, and extract-min;
- record and field;
- comparator;
- deterministic and stable;
- arrival sequence;
- dynamic array and backend;
- scan and candidate;
- size and capacity;
- invariant; and
- saturating count.

Use the reveal fixture:

```text
50/2/0, 11/1/1, 80/1/2, 34/3/3
```

Build the service rule in this order:

1. compare priority;
2. on equal priority, compare sequence;
3. exclude alert ID;
4. scan from index 0 through the later live indexes;
5. extract 11;
6. fill its slot from final record 34; and
7. rescan to show that 80 still leaves before 50.

Ask why the physical move cannot change the stable tie promise.

### 5. Exactly-three-target Cognitive Pause - 5 minutes

Read the starting definitions and state aloud. Students then use no notes,
slides, vocabulary file, classmates, or coding tools.

Starting state:

```text
54/3/0, 81/1/1, 12/2/2, 27/1/3, 68/4/4
capacity 8, size 5, next_sequence 5, comparison_count 0
```

The three and only three target headings are:

1. select without removing;
2. extract, swap, and insert; and
3. separate ties from policy.

Approved extended time uses the same fixture and targets. Responses may be
drawn, typed, dictated, modeled with cards, or given as numbered sentences.

Gate B closes only when responses under all three headings are preserved.

### 6. Cognitive Pause calibration - 10 minutes

Display and explain:

```text
Target 1:
peek 81/1/1
4 comparisons
logical contents unchanged

Target 2:
extract 81
physical 54/3/0,68/4/4,12/2/2,27/1/3
insert 35/1/5
final size 5, capacity 8, next_sequence 6, count 4
next logical record 27/1/3

Target 3:
stable ties do not prevent priority-4 starvation
silent field mutation bypasses the ADT
an explicit client policy or update operation is required
```

Students preserve the original and add corrections labeled:

```text
comparison
swap-last
sequence
policy
```

An incorrect first response is useful evidence when it is meaningfully
corrected.

### 7. Gate C - Canonical comparator and storage - 22 minutes

Release one Stage C worksheet.

Canonical insertions:

```text
71/3/0, 88/1/1, 42/2/2, 17/1/3,
26/4/4, 9/2/5, 63/1/6
```

Complete only the first comparison as entry support. Students then:

1. settle all pair comparisons;
2. state logical service order;
3. prove alert ID is excluded;
4. draw or list capacity-8 physical storage;
5. trace a seven-record peek and its six comparisons;
6. begin the swap-last extraction table; and
7. distinguish live from inactive positions.

Use this hint ladder:

1. point to priority;
2. if priority ties, point to sequence;
3. ignore ID;
4. locate the current candidate;
5. locate the final live record;
6. reduce size before deciding which positions remain live.

Do not reveal the full extraction table while students are constructing it.

### 8. Contract checkpoint - 12 minutes

Use five proposed states from Section C.

Require the distinction:

- the full invariant says live sequences are unique; and
- the constant-time validator cannot prove record-level uniqueness.

Add capacity examples 6 and 12. Both are invalid even with a plausible
pointer and size because valid capacity is exactly:

```text
0,4,8,16,32,64
```

Ask students to name protected facts for empty, full, sequence-exhausted,
and allocation failures.

### 9. Exit ticket - 5 minutes

Prompt:

> Why can a physically unsorted array still provide stable service, and
> where does it pay for that choice?

Expected causal answer: every selection rescans with priority then sequence,
so physical order need not be sorted; peek and extraction cost linear scan
work.

## Between meetings

Students complete and preserve Stage C Sections A through F.

Required Gate C evidence:

- comparator pairs and logical order;
- complete swap-last trace;
- valid/invalid state reasoning;
- failure preservation;
- unsorted and paper-sorted operation costs;
- 32-record workload counts;
- backend-selection memo;
- starvation and mutable-priority reasoning; and
- Queue-to-Heap-to-weighted-exploration links.

Release Stage D only after that attempt is preserved. Ask students to add
corrections beside earlier work instead of erasing it.

## Meeting B - Implement and verify

### 1. Gate D retrieval and model calibration - 12 minutes

Before code, ask:

1. Which field ranks first?
2. Which field settles a tie?
3. How many comparisons does a size-7 scan make?
4. What fills the removed physical slot?
5. What changes on successful peek?
6. What remains after complete drain?

Then permit the concise textbook and model file.

Use Model 5 to calibrate the exact active arrays:

```text
after 88: 71,63,42,17,26,9
after 17: 71,63,42,9,26
after 63: 71,26,42,9
after 42: 71,26,9
after 9:  71,26
after 71: 26
after 26: empty
```

Gate D closes after each student preserves corrections and can trace at
least one comparison plus one swap-last step in an accessible format.

### 2. Gate E - Read the public contract - 15 minutes

Release the student lab package.

Students locate, without editing:

```text
AlertRecord
AlertPriorityQueue
AlertPriorityQueueStatus
ALERT_PRIORITY_QUEUE_MAX_CAPACITY
```

Have them point to the five Queue fields and seven statuses. Establish
precedence:

```text
peek/extract: NULL output -> validate -> empty
insert: validate -> full -> sequence exhausted -> possible growth
```

Review the no-alias precondition: output cannot point inside `data`.
Review shallow-copy risk: copying the struct duplicates an owning pointer,
not the allocation.

### 3. TODO 1 - Comparator and scan - 22 minutes

Students edit only the numbered comparator/minimum-scan TODO.

Small checks:

1. smaller priority wins;
2. equal priority uses smaller sequence;
3. alert ID is never read by the comparator;
4. candidate starts at index 0;
5. each later live record is compared once;
6. count increments once per comparator call;
7. count stays at `SIZE_MAX` after saturation; and
8. candidate changes only when the challenger strictly precedes it.

Test a singleton, two equal-priority records, and the reveal fixture before
the canonical seven records.

Intervene if a student writes subtraction-based comparison. Unsigned
subtraction can wrap and does not express the two-field rule clearly.

### 4. TODO 2 - Insert and growth - 28 minutes

Students implement in contract order:

1. validate;
2. check the 64-record full boundary;
3. check sequence exhaustion;
4. derive capacity 4 or double the current capacity;
5. use a temporary `realloc` result;
6. commit pointer and capacity only on allocation success;
7. append ID, priority, and current sequence;
8. increment size and sequence; and
9. return success.

Test:

```text
first insertion: capacity 0 -> 4
fifth insertion: capacity 4 -> 8
insertion with spare capacity: pointer and capacity stable
64 live records: FULL and exact preservation
```

The supplied core/instructor suite forces actual growth allocation failure.
The student build does not expose that test hook. Students explain the
temporary-pointer contract and cite supplied evidence.

### 5. TODO 3 - Extract-min - 22 minutes

Students:

1. reject NULL output;
2. validate;
3. reject empty with output unchanged;
4. call the stable scan;
5. copy the result locally;
6. fill the selected position from the final live position when different;
7. reduce size;
8. reset sequence only when size becomes zero;
9. publish output last; and
10. preserve allocation, capacity, and comparison count.

Test the canonical fixture after resetting comparisons. Require:

```text
output 88,17,63,42,9,71,26
total comparisons 21
drained capacity 8
drained next_sequence 0
drained comparison_count 21
```

Do not require clearing inactive slots.

### 6. Exactly three student tests - 20 minutes

Students state each claim before writing assertions.

1. **Mixed priorities and stable ties.** IDs must not reveal priority or
   arrival order; assert complete output records.
2. **Growth and swap-scrambled storage.** Cross capacity 4 to 8, extract a
   nonfinal minimum, insert again, and prove logical order.
3. **Empty and full failure preservation.** Protect a recognizable output
   on empty access, fill to 64, snapshot all fields and live slots, reject
   the 65th insertion, and prove exact preservation.

The one-shot allocation hook is instructor/core-only. Do not require
student code to call it.

### 7. Workload and backend comparison - 12 minutes

Reset the metric before each workload.

Students report:

```text
32 unsorted append insertions: 0 record comparisons
32 worst-position paper-sorted insertions: 496 comparisons
32 unsorted extractions after preload: 496 comparisons
32 paper-sorted right-end extractions: 0 comparisons
```

Separate record comparisons from allocation copying and shifting.

Memo targets:

- many inserts with rare reports: unsorted append backend; and
- fixed prepared batch with many removals: sorted minimum-at-end backend.

Accept another choice only if its operation assumptions and costs are
stated consistently.

### 8. Bounded Priority Queue Autopsy - 12 minutes

Students predict before running.

Frozen fixture:

```text
80/2/0, 91/1/1, 17/1/2, 44/3/3
```

The correct scan keeps 91 when it reaches later equal-priority 17. The
faulty `later.priority <= candidate.priority` rule replaces 91 with 17.

Focus on the first divergence:

```text
candidate 91/1/1
challenger 17/1/2
faulty decision: replace
correct decision: keep earlier sequence 1
```

The repair must state both comparator fields. Merely changing `<=` to `<`
is incomplete documentation even if it happens to keep the first physical
equal-priority record in this backend.

Require a regression test with at least three same-priority alerts whose
IDs do not follow arrival order.

### 9. Policy and spiral synthesis - 10 minutes

Ask students to separate four claims:

1. stable ties preserve arrival order within one priority;
2. starvation can still occur across priorities;
3. mutable priority needs a controlled update or versioned duplicate
   strategy; and
4. a course score does not establish real severity or fairness.

Close the spiral:

```text
Module 7: FIFO controls pending work
Module 10: priority then sequence controls pending work
Module 11: a Heap keeps the same rule with a faster backend
Module 12: minimum known path cost controls weighted exploration
```

## Formative checkpoints

Intervene if a student:

- treats a smaller alert ID as more urgent;
- reverses the smaller-priority convention;
- uses physical position as the stable tie rule;
- uses `<=` on priority alone;
- assigns caller-provided arrival sequences;
- increments sequence on a failed insertion;
- assigns `SIZE_MAX` and then wraps sequence;
- lets the comparison counter wrap;
- counts insertion or field checks as record-comparator calls;
- scans inactive slots;
- writes `realloc` directly into the only owned pointer;
- accepts capacity 1, 2, 6, 12, or another off-ladder value;
- allocates before checking full or sequence exhaustion;
- changes output before an empty or invalid result;
- resets comparison count while draining;
- fails to reset `next_sequence` after the final extraction;
- clears inactive slots and then treats clearing as required correctness;
- shallow-copies a live owner;
- passes an output inside the owned array;
- claims constant-time validation proves unique sequences or pointer
  liveness;
- claims sorted minimum-at-index-0 extraction is `O(1)`;
- calls stable ties a starvation solution;
- silently mutates an active priority;
- implements a Heap or decrease-key instead of the three TODOs; or
- treats a synthetic priority score as proof of real severity.

## Extension prompts

Use only after core correctness:

- What workload balance would justify moving comparison work from removal
  to insertion?
- How could an aging policy change the comparator, and what new evidence
  would it require?
- Why can sequence reset safely occur only after size becomes zero?
- How would a version field identify a stale duplicate?
- Which minimum operations should a Heap accelerate while preserving the
  same outputs?
- Why does a complete validator need linear record scanning, and why is it
  intentionally outside the public constant-time validator?

Do not replace core implementation or tests with extension work.

## Submission check

Students submit:

- completed comparator/scan, insertion, and extraction TODOs;
- exactly three student-authored test categories;
- warning-clean core and student-test output or approved instructor-CI
  evidence;
- canonical capacity-8 state and complete swap-last trace;
- exact peek count 6 and drain count 21;
- 32-record comparison totals `0/496` and `496/0`;
- sorted-versus-unsorted backend memo;
- empty and full preservation evidence;
- supplied/core allocation-failure evidence;
- completed bounded autopsy and regression design;
- starvation and mutable-priority explanation;
- safe SOC interpretation;
- completed evidence record; and
- corrected, preserved Stage A through Stage D artifacts.

Gate E completion is based on this evidence, not on code alone.
