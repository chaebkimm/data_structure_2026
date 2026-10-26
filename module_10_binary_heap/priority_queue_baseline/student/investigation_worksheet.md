# Stage C — Investigation Worksheet: Urgency-First Service

Name: ____________________________  
Date: ____________________________

Preserve Sections A through F before opening the textbook. Sections G
through I are later work.

## Quick reference

Record `a` comes before record `b` when `a` has a smaller priority, or when
their priorities are equal and `a` has a smaller arrival sequence.

The backend is an unsorted dynamic array. Insertion appends. Peek and
extraction scan all live records. Extraction fills the removed position
with the last live record.

## Canonical alert fixture

Insert these records in the displayed order. The Priority Queue assigns the
sequences.

| Insertion | Alert ID | Priority | Assigned sequence |
|---:|---:|---:|---:|
| 1 | 71 | 3 | 0 |
| 2 | 88 | 1 | 1 |
| 3 | 42 | 2 | 2 |
| 4 | 17 | 1 | 3 |
| 5 | 26 | 4 | 4 |
| 6 | 9 | 2 | 5 |
| 7 | 63 | 1 | 6 |

After insertion: capacity 8, size 7, `next_sequence` 7. Write a record as
`ID/P/S`, meaning alert ID, priority, and arrival sequence.

## A. Apply the comparator

### A1. Compare pairs

For each pair, circle the record that comes first and state why:

```text
88/1/1 versus 42/2/2
88/1/1 versus 17/1/3
9/2/5 versus 42/2/2
```

Reasoning: __________________________________________________________

### A2. State complete logical service order

Write all seven alert IDs in logical service order without changing the
physical array.

____________________________________________________________________

### A3. Exclude alert ID

Use one pair above to prove that numeric alert ID is not a tie-breaker.

____________________________________________________________________

## B. Trace the unsorted backend

### B1. Preserve the insertion state

Write indexes 0 through 7 after all insertions. Label index 7 inactive.

____________________________________________________________________

### B2. Apply peek-min

Starting with `comparison_count == 0`, apply one peek. State the output,
comparison count, and every field or record that must remain logically
unchanged.

____________________________________________________________________

### B3. Apply every extraction

Return to the post-insertion state with comparison count 0. Complete the
swap-with-last trace.

| Extracted ID | Remaining active physical IDs | Comparisons added |
|---:|---|---:|
| 88 | | 6 |
| 17 | | 5 |
| 63 | | 4 |
| 42 | | 3 |
| 9 | | 2 |
| 71 | | 1 |
| 26 | | 0 |

Total comparisons: __________________

### B4. Describe the drained state

After the final extraction, state `data`, capacity, size,
`next_sequence`, and the status of former physical values.

____________________________________________________________________

## C. Check representation and contracts

### C1. Classify states

Mark each state valid or invalid and cite one invariant rule.

| State | Valid or invalid? | Reason |
|---|---|---|
| `data=NULL,size=0,capacity=0,next=0,comparisons=0` | | |
| non-NULL data, `size=0,capacity=8,next=0` | | |
| non-NULL data, `size=0,capacity=6,next=0` | | |
| non-NULL data, `size=5,capacity=4,next=5` | | |
| non-NULL data, `size=2,capacity=8,next=2`, live sequences 0 and 0 | | |
| non-NULL data, `size=2,capacity=8,next=2`, live sequences 0 and 1 | | |

### C2. Preserve failed operations

State what remains unchanged after:

1. peek or extraction on an empty valid object;
2. growth allocation failure;
3. insertion when 64 live records already exist; and
4. insertion when sequence assignment cannot advance.

____________________________________________________________________

### C3. Separate metric from logical state

Why may successful peek change `comparison_count` while still leaving the
Priority Queue's logical contents unchanged? What happens when the count
has reached `SIZE_MAX`?

____________________________________________________________________

### C4. Respect storage lifetime

Explain why returned records are copied, why an output location must not
point inside the owned array, and why the owning struct must not be
shallow-copied.

____________________________________________________________________

## D. Compare two array backends

### D1. Analyze the unsorted array

Complete:

| Operation | Comparator calls | Time |
|---|---:|---:|
| insert without growth | | |
| one insert that grows | | |
| long sequence of inserts | | |
| peek-min with `n` records | | |
| extract-min with `n` records | | |

### D2. Build a paper-only sorted array

Maintain records from worst to best so the minimum is at the removable
right end. Write the canonical physical ID order.

____________________________________________________________________

Why is insertion `O(n)`? Why are peek-min and extract-min `O(1)`? Why would
minimum-at-index-0 extraction instead require shifting?

____________________________________________________________________

### D3. Count two workloads

For the insert-heavy workload, insert 32 records whose new record must cross
all earlier sorted records. The unsorted backend performs 0 priority
comparisons. The paper sorted backend performs:

```text
0 + 1 + ... + 31 = 496 comparisons
```

For the removal-heavy workload, preload 32 records and reset the metric.
Extract all records. State both comparison totals.

```text
unsorted:
sorted with minimum at removable end:
```

### D4. Write a backend-selection memo

Choose one backend for many inserts followed by rare reports, and one for a
fixed batch followed by many removals. Justify from operations rather than
claiming one representation is always best.

____________________________________________________________________

## E. Analyze policy hazards

### E1. Explain starvation

Give an arrival pattern in which priority-4 alert 26 waits indefinitely.
Why does stable tie behavior not solve this problem?

____________________________________________________________________

### E2. Control mutable priority

Why does silently editing an active record break the ADT boundary even
though this unsorted backend scans again? Why will the same edit be more
dangerous for a future sorted or Heap backend?

____________________________________________________________________

### E3. Preview two update strategies

**Decrease-key** explicitly lowers a stored priority and repairs the
backend. A **duplicate-entry strategy** inserts a new version and later
ignores the old stale entry. State one fact the duplicate strategy must
store so stale entries can be recognized.

____________________________________________________________________

### E4. State the safe SOC interpretation

Explain why a course priority number and passing tests do not prove a real
alert is authentic, severe, timely, complete, or handled fairly.

____________________________________________________________________

## F. Connect the spiral

### F1. Contrast Queue and Priority Queue

For the canonical arrivals, state the FIFO order and the Priority Queue
order. What public rule changed?

____________________________________________________________________

### F2. Predict the Heap role

A later Heap backend will preserve the same public service rule. Which
current operation should become faster without changing client meaning?

____________________________________________________________________

### F3. Preview weighted exploration

Why might an algorithm choosing the smallest known path cost need a
minimum-priority Queue instead of FIFO?

____________________________________________________________________

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
