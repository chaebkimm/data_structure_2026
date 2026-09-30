# Stage C — Investigation Worksheet: Urgency-First Service

Name: ____________________________  
Date: ____________________________

Preserve Sections A through F before opening the textbook. Sections G
through I are later work. This linear version uses numbered prose instead
of spatial tables.

## Quick reference

Record `a` comes before record `b` when `a` has a smaller priority, or when
their priorities are equal and `a` has a smaller arrival sequence.

The backend is an unsorted dynamic array. Insertion appends. Peek and
extraction scan all live records. Extraction fills the removed position
with the last live record.

## Canonical alert fixture

Insert the following exact records in order:

1. alert 71, priority 3, receives sequence 0;
2. alert 88, priority 1, receives sequence 1;
3. alert 42, priority 2, receives sequence 2;
4. alert 17, priority 1, receives sequence 3;
5. alert 26, priority 4, receives sequence 4;
6. alert 9, priority 2, receives sequence 5; and
7. alert 63, priority 1, receives sequence 6.

After insertion: capacity 8, size 7, `next_sequence` 7. Write a record as
`ID/P/S`, meaning alert ID, priority, and arrival sequence.

## A. Apply the comparator

### A1. Compare pairs

For each exact pair, name the record that comes first and state why:

1. `88/1/1` versus `42/2/2`;
2. `88/1/1` versus `17/1/3`; and
3. `9/2/5` versus `42/2/2`.

Response: ___________________________________________________________

### A2. State complete logical service order

Write all seven alert IDs in logical service order without changing the
physical array.

Response: ___________________________________________________________

### A3. Exclude alert ID

Use one pair above to prove that numeric alert ID is not a tie-breaker.

Response: ___________________________________________________________

## B. Trace the unsorted backend

### B1. Preserve the insertion state

List indexes 0 through 7 after all insertions. Label index 7 inactive.

Response: ___________________________________________________________

### B2. Apply peek-min

Starting with `comparison_count == 0`, apply one peek. State the output,
comparison count, and every field or record that must remain logically
unchanged.

Response: ___________________________________________________________

### B3. Apply every extraction

Return to the post-insertion state with comparison count 0. Fill these
seven exact rows:

1. Extract 88; list remaining active physical IDs; comparisons added 6.
2. Extract 17; list remaining active physical IDs; comparisons added 5.
3. Extract 63; list remaining active physical IDs; comparisons added 4.
4. Extract 42; list remaining active physical IDs; comparisons added 3.
5. Extract 9; list remaining active physical IDs; comparisons added 2.
6. Extract 71; list remaining active physical IDs; comparisons added 1.
7. Extract 26; list remaining active physical IDs; comparisons added 0.

Total comparisons: __________________

### B4. Describe the drained state

After the final extraction, state `data`, capacity, size,
`next_sequence`, and the status of former physical values.

Response: ___________________________________________________________

## C. Check representation and contracts

### C1. Classify states

Classify each exact state and cite one invariant rule:

1. `data=NULL,size=0,capacity=0,next=0,comparisons=0`;
2. non-NULL data, `size=0,capacity=8,next=0`;
3. non-NULL data, `size=0,capacity=6,next=0`;
4. non-NULL data, `size=5,capacity=4,next=5`;
5. non-NULL data, `size=2,capacity=8,next=2`, live sequences 0 and 0; and
6. non-NULL data, `size=2,capacity=8,next=2`, live sequences 0 and 1.

Response: ___________________________________________________________

### C2. Preserve failed operations

State what remains unchanged after:

1. peek or extraction on an empty valid object;
2. growth allocation failure;
3. insertion when 64 live records already exist; and
4. insertion when sequence assignment cannot advance.

Response: ___________________________________________________________

### C3. Separate metric from logical state

Why may successful peek change `comparison_count` while still leaving the
Priority Queue's logical contents unchanged? What happens when the count
has reached `SIZE_MAX`?

Response: ___________________________________________________________

### C4. Respect storage lifetime

Explain why returned records are copied, why an output location must not
point inside the owned array, and why the owning struct must not be
shallow-copied.

Response: ___________________________________________________________

## D. Compare two array backends

### D1. Analyze the unsorted array

State comparator calls and time for:

1. insert without growth;
2. one insert that grows;
3. a long sequence of inserts;
4. peek-min with `n` records; and
5. extract-min with `n` records.

Response: ___________________________________________________________

### D2. Build a paper-only sorted array

Maintain records from worst to best so the minimum is at the removable
right end. Write the canonical physical ID order.

Response: ___________________________________________________________

Why is insertion `O(n)`? Why are peek-min and extract-min `O(1)`? Why would
minimum-at-index-0 extraction instead require shifting?

Response: ___________________________________________________________

### D3. Count two workloads

Insert-heavy exact workload: insert 32 records whose new record must cross
all earlier sorted records. The unsorted backend makes 0 priority
comparisons. The paper sorted backend makes
`0 + 1 + ... + 31 = 496` comparisons.

Removal-heavy exact workload: preload 32 records and reset the metric.
Extract all records.

```text
unsorted:
sorted with minimum at removable end:
```

### D4. Write a backend-selection memo

Choose one backend for many inserts followed by rare reports, and one for a
fixed batch followed by many removals. Justify from operations rather than
claiming one representation is always best.

Response: ___________________________________________________________

## E. Analyze policy hazards

### E1. Explain starvation

Give an arrival pattern in which priority-4 alert 26 waits indefinitely.
Why does stable tie behavior not solve this problem?

Response: ___________________________________________________________

### E2. Control mutable priority

Why does silently editing an active record break the ADT boundary even
though this unsorted backend scans again? Why will the same edit be more
dangerous for a future sorted or Heap backend?

Response: ___________________________________________________________

### E3. Preview two update strategies

**Decrease-key** explicitly lowers a stored priority and repairs the
backend. A **duplicate-entry strategy** inserts a new version and later
ignores the old stale entry. State one fact the duplicate strategy must
store so stale entries can be recognized.

Response: ___________________________________________________________

### E4. State the safe SOC interpretation

Explain why a course priority number and passing tests do not prove a real
alert is authentic, severe, timely, complete, or handled fairly.

Response: ___________________________________________________________

## F. Connect the spiral

### F1. Contrast Queue and Priority Queue

For the canonical arrivals, state the FIFO order and the Priority Queue
order. What public rule changed?

Response: ___________________________________________________________

### F2. Predict the Heap role

A later Heap backend will preserve the same public service rule. Which
current operation should become faster without changing client meaning?

Response: ___________________________________________________________

### F3. Preview weighted exploration

Why might an algorithm choosing the smallest known path cost need a
minimum-priority Queue instead of FIFO?

Response: ___________________________________________________________

## G. Design exactly three tests — later work

### G1. Mixed priorities and stable ties

Design one test in which IDs are not ordered like priorities or arrival.

### G2. Growth and swap-scrambled storage

Design one test that crosses capacities 4 and 8 and still extracts the
correct order after at least one swap-with-last.

### G3. Failure preservation

Design one test covering protected output on empty access and complete state
preservation at the 64-record full limit.

## H. Analyze a bounded autopsy — later work

### H1. Predict the correct selection

For `80/2/0, 91/1/1, 17/1/2, 44/3/3`, which ID should leave first?

### H2. Find the first divergence

A faulty scan replaces its candidate whenever a later priority is less than
**or equal to** the candidate priority. Which ID does it select?

### H3. Repair and retain

State the exact repair and one regression test that would prevent return of
the defect.

## I. Exit reflection — later work

### I1. Answer the macro-question

Answer in three sentences: service rule, backend cost, and one policy risk.

### I2. Correct an incomplete claim

Correct: “A Priority Queue always handles the most important real alert
fairly.”
