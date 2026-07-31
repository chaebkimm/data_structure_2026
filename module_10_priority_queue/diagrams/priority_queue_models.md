# Priority Queue Models and Exact Linear Equivalents

These models accompany Stage D. Every visual has an exact linear text
equivalent. No meaning depends on color, drawing quality, or spatial
position.

An **alert ID** is an identifying whole-number label. It does not rank an
alert. A record groups related values; a field is one named value in a
record. `ID/P/S` means the record fields alert ID, priority, and arrival
sequence. A **priority** is the course number used for service order;
smaller numbers leave first. An **arrival sequence** is a whole number
assigned by the Queue at successful insertion. Smaller sequences mean
earlier insertion.

A physical position is an actual array index. Logical service order is the
output order promised by the public rule, even when physical positions
differ.

## Model 1 - FIFO order versus Priority Queue order

A **Queue** uses **first in, first out (FIFO)**: the oldest waiting item
leaves first. A **Priority Queue** selects a waiting item using a stated
ranking rule. This module uses a **minimum** rule, so the smaller priority
leaves first.

Arrivals:

```text
first                                                   last
  |                                                       |
  v                                                       v
71/3/0 -> 88/1/1 -> 42/2/2 -> 17/1/3 -> 26/4/4 -> 9/2/5 -> 63/1/6
```

Two service rules:

```text
FIFO:
71 -> 88 -> 42 -> 17 -> 26 -> 9 -> 63

minimum Priority Queue:
88 -> 17 -> 63 -> 42 -> 9 -> 71 -> 26
```

Exact linear equivalent:

1. Alert 71 arrives first and receives sequence 0.
2. Alert 88 arrives second and receives sequence 1.
3. Alert 42 receives sequence 2.
4. Alert 17 receives sequence 3.
5. Alert 26 receives sequence 4.
6. Alert 9 receives sequence 5.
7. Alert 63 arrives last and receives sequence 6.
8. FIFO outputs IDs `71,88,42,17,26,9,63`.
9. The minimum Priority Queue outputs IDs
   `88,17,63,42,9,71,26`.
10. The service rules differ even though the arrivals are identical.

## Model 2 - The complete comparison rule

A **comparator** is the exact repeatable rule that decides which of two
records comes first. **Stable tie behavior** means equal-priority records
leave in arrival order.

```text
Compare record a with record b.
             |
             v
   Is a.priority smaller?
       /             \
     yes              no
      |                |
 a comes first         v
              Are priorities equal?
                  /          \
                yes           no
                 |             |
                 v        b comes first
       Is a.sequence smaller?
             /          \
           yes           no
            |             |
       a comes first  b comes first
```

Exact linear equivalent:

1. First compare priorities.
2. If `a` has the smaller priority, `a` comes first.
3. If `b` has the smaller priority, `b` comes first.
4. If priorities tie, compare arrival sequences.
5. The record with the smaller sequence comes first.
6. Alert IDs are never compared.

Exact canonical examples:

```text
88/1/1 before 42/2/2 because 1 < 2
88/1/1 before 17/1/3 because priority ties and 1 < 3
42/2/2 before 9/2/5 because priority ties and 2 < 5
```

The symbol `<` means "is smaller than."

## Model 3 - Unsorted dynamic-array storage after growth

An **array** is a numbered row of same-type values. An **index** is one
position number, beginning at 0. A **dynamic array** uses an allocation
that may be replaced by a larger allocation while the program runs. An
**allocation** is storage obtained while the program is running.

The storage **backend** is the physical method used to provide the public
Priority Queue behavior. This backend is **unsorted**, meaning physical
positions are not maintained in service order.

Capacity grows in this exact sequence:

```text
0 -> 4 -> 8 -> 16 -> 32 -> 64
```

**Capacity** is the number of allocated record positions. **Size** is the
number of currently used, or **live**, positions.

After four insertions:

```text
capacity 4, size 4

index       0        1        2        3
         +--------+--------+--------+--------+
record   | 71/3/0 | 88/1/1 | 42/2/2 | 17/1/3 |
         +--------+--------+--------+--------+
```

The fifth insertion requires growth from capacity 4 to capacity 8. After
all seven canonical insertions:

```text
data ----> +--------+--------+--------+--------+
           | 71/3/0 | 88/1/1 | 42/2/2 | 17/1/3 |
           +--------+--------+--------+--------+
index           0        1        2        3

           +--------+-------+--------+----------+
           | 26/4/4 | 9/2/5 | 63/1/6 | inactive |
           +--------+-------+--------+----------+
index           4       5        6         7

size = 7
capacity = 8
next_sequence = 7
comparison_count = 0
```

`data` is a **pointer**, meaning a value that stores a memory address. The
Queue owns the allocation. **Ownership** is responsibility for releasing
that allocation exactly once.

Exact linear equivalent:

1. Capacity starts at 0.
2. Inserting alert 71 obtains capacity 4 and writes `71/3/0` at index 0.
3. Alerts 88, 42, and 17 append at indexes 1, 2, and 3.
4. Inserting alert 26 grows capacity from 4 to 8.
5. Alert 26 appends at index 4.
6. Alerts 9 and 63 append at indexes 5 and 6.
7. Index 7 is inactive, meaning it is allocated but not logically used.
8. The seven live records remain in insertion order only because no
   extraction has happened yet.
9. `next_sequence` is 7 because the next successful insertion would
   receive sequence 7.
10. Insertion makes no record comparisons, so the count remains 0.

## Model 4 - One seven-record peek scan

A **scan** examines live positions one at a time. A **candidate minimum** is
the best record found so far. `peek-min` reports that record without
removing it.

```text
start candidate: index 0, 71/3/0

step  challenger   decision                         candidate after step
 1    88/1/1       smaller priority                 88/1/1
 2    42/2/2       larger priority                  88/1/1
 3    17/1/3       same priority, later sequence    88/1/1
 4    26/4/4       larger priority                  88/1/1
 5    9/2/5        larger priority                  88/1/1
 6    63/1/6       same priority, later sequence    88/1/1
```

Exact linear equivalent:

1. Begin with index 0, record `71/3/0`, as the candidate.
2. Compare index 1 with the candidate. Record `88/1/1` becomes candidate.
3. Compare index 2 with `88/1/1`; keep 88.
4. Compare index 3 with `88/1/1`; keep earlier sequence 1 instead of 3.
5. Compare index 4 with `88/1/1`; keep 88.
6. Compare index 5 with `88/1/1`; keep 88.
7. Compare index 6 with `88/1/1`; keep earlier sequence 1 instead of 6.
8. Report `88/1/1`.
9. Seven live records produce six record comparisons.
10. The records, physical positions, size, capacity, and next sequence do
    not change.
11. `comparison_count` changes from 0 to 6.

A **saturating count** stays at its largest value instead of wrapping to
zero. Here the largest `size_t` value is named `SIZE_MAX`. If the count is
already `SIZE_MAX`, later scans still compare records but the stored count
remains `SIZE_MAX`.

## Model 5 - Swap-last extraction trace

`extract-min` removes and reports the minimum. After scanning, the last
live record fills the removed physical position. The student material calls
this **swap-last removal**. The operation does not keep the array sorted.

Starting active records:

```text
[71/3/0, 88/1/1, 42/2/2, 17/1/3, 26/4/4, 9/2/5, 63/1/6]
```

Exact active arrays after every extraction:

```text
extract 88:
[71/3/0, 63/1/6, 42/2/2, 17/1/3, 26/4/4, 9/2/5]

extract 17:
[71/3/0, 63/1/6, 42/2/2, 9/2/5, 26/4/4]

extract 63:
[71/3/0, 26/4/4, 42/2/2, 9/2/5]

extract 42:
[71/3/0, 26/4/4, 9/2/5]

extract 9:
[71/3/0, 26/4/4]

extract 71:
[26/4/4]

extract 26:
[]
```

Exact linear equivalent:

1. Scan seven records, report 88, copy final record 63 into 88's old index,
   and reduce size to 6. Add 6 comparisons.
2. Scan six records, report 17, copy final record 9 into 17's old index,
   and reduce size to 5. Add 5 comparisons.
3. Scan five records, report 63, copy final record 26 into 63's old index,
   and reduce size to 4. Add 4 comparisons.
4. Scan four records, report 42, copy final record 9 into 42's old index,
   and reduce size to 3. Add 3 comparisons.
5. Scan three records, report 9, and reduce size to 2. Add 2 comparisons.
6. Scan two records, report 71, copy final record 26 into 71's old index,
   and reduce size to 1. Add 1 comparison.
7. Scan one record, report 26, and reduce size to 0. Add 0 comparisons.
8. The output order is `88,17,63,42,9,71,26`.
9. Total comparisons are `6+5+4+3+2+1+0`, which equals 21.
10. Capacity remains 8 and the allocation remains owned.
11. `next_sequence` resets to 0 when the final live record leaves.
12. Positions that are no longer live are inactive; their old bits have no
    logical record meaning.

## Model 6 - Physical order versus logical service order

**Physical order** is the record arrangement at actual indexes. **Logical
service order** is the promised output sequence defined above.
**ADT** means abstract data type: the public behavior without requiring one
physical storage method.

After the first extraction:

```text
physical indexes:
0:71/3/0, 1:63/1/6, 2:42/2/2,
3:17/1/3, 4:26/4/4, 5:9/2/5

logical service:
17 -> 63 -> 42 -> 9 -> 71 -> 26
```

Exact linear equivalent:

1. Alert 63 is physically before alert 17 after swap-last removal.
2. Both have priority 1.
3. Alert 17 has earlier sequence 3; alert 63 has later sequence 6.
4. The comparator therefore selects alert 17 first.
5. Physical position is not a tie-breaker.
6. Alert ID is not a tie-breaker.

## Model 7 - Paper-only sorted array

A **sorted array** maintains records in a defined order during insertion.
This alternative is studied on paper and is not implemented.

Place records from worst to best so the minimum is at the removable right
end:

```text
worst                                                     best/minimum
  |                                                            |
  v                                                            v
+--------+--------+-------+--------+--------+--------+--------+
| 26/4/4 | 71/3/0 | 9/2/5 | 42/2/2 | 63/1/6 | 17/1/3 | 88/1/1 |
+--------+--------+-------+--------+--------+--------+--------+
 index 0    index 1  index 2  index 3  index 4  index 5  index 6
```

Exact linear equivalent:

1. Worst-to-best IDs are `26,71,9,42,63,17,88`.
2. Priority 4 is worse than priority 3.
3. Priority 3 is worse than priority 2.
4. Among priority-2 records, later sequence 5 is worse than earlier
   sequence 2, so 9 is left of 42.
5. Among priority-1 records, worst-to-best sequence order is 6, 3, 1, so
   the IDs are 63, 17, 88.
6. The minimum record 88 is at the final live index.
7. Peek-min reads that final index.
8. Extract-min reduces size and needs no shift.
9. Insertion may shift existing records to open the correct position.

## Model 8 - Operation-cost comparison

**Time complexity** describes how work grows as input size grows. Let `n`
mean the live-record count. `O(1)`, read "order one," means work is bounded
by a fixed amount independent of `n`. `O(n)`, read "order n," means work may
grow in proportion to `n`.

**Amortized `O(1)`** means average constant work across a sequence that
includes occasional growth.

| Operation | Unsorted course backend | Paper sorted backend |
|---|---:|---:|
| insert without growth | `O(1)`, 0 record comparisons | `O(n)` |
| long insertion sequence | amortized `O(1)` each | `O(n)` each |
| peek-min | `O(n)`, `n-1` comparisons | `O(1)` |
| extract-min | `O(n)`, `n-1` comparisons | `O(1)` |

Exact linear equivalent:

1. The unsorted backend appends ordinary insertions.
2. A growth insertion may copy records, but geometric growth makes a long
   insertion sequence amortized constant per insertion.
3. The unsorted backend scans all live records for peek and extraction.
4. The paper sorted backend spends work maintaining order during insertion.
5. Its minimum remains at the removable end, so peek and extraction use
   fixed work.
6. No backend is fastest for every operation mixture.

Exact 32-record comparison workloads:

```text
insert-heavy:
unsorted 0
paper sorted 0+1+...+31 = 496

removal-heavy after preload and metric reset:
unsorted 31+30+...+0 = 496
paper sorted 0
```

## Model 9 - Failure preservation and commit

**Failure preservation** means a failed operation leaves protected prior
state and output unchanged. A **commit** is the point at which a successful
candidate becomes the official Queue state.

Suppose four records fill capacity 4 and a fifth insertion needs capacity
8:

```text
before:
data A -> [r0][r1][r2][r3]
size 4, capacity 4, next_sequence 4

request larger storage
          |
      +---+---+
      |       |
   failure  success
      |       |
      v       v
 keep A,   commit data B and capacity 8,
 all four  then append the new record
 records
```

`r0` through `r3` mean the four established records. `A` and `B` are names
for memory addresses, not stored fields. A successful request may return
the same address or a different address.

Exact linear equivalent:

1. Validate the Queue before changing it.
2. Check the 64-record full limit.
3. Check whether the arrival sequence can advance.
4. If growth is required, request capacity 8 through a temporary pointer.
5. If the request fails, preserve the old data address, all five fields,
   and all established slots.
6. If it succeeds, commit the returned address and capacity.
7. Append the new record only after successful growth.
8. A failed insertion does not consume an arrival sequence.
9. Empty peek or extraction preserves the caller's output record.
10. Full and sequence-exhausted insertion preserve the complete Queue.

The valid capacities are exactly:

```text
0, 4, 8, 16, 32, 64
```

A constant-time **validator** checks field relationships without scanning
records. It rejects another positive capacity, a size above capacity, a
missing positive-capacity data pointer, and contradictory empty or sequence
fields. It cannot prove that a pointer still identifies usable allocated
storage, that ownership is unique, or that live sequences are unique.

## Model 10 - Stability is not starvation prevention

**Starvation** means an item waits indefinitely because other items keep
ranking ahead of it.

```text
waiting: 26/4/4

time 1: priority-1 alert arrives -> it ranks before 26
time 2: priority-1 alert arrives -> it ranks before 26
time 3: priority-1 alert arrives -> it ranks before 26
...
```

Exact linear equivalent:

1. Alert 26 has priority 4.
2. Every priority-1 record ranks before alert 26.
3. If lower-numbered records keep arriving, alert 26 may never be selected.
4. Stable behavior orders records that have equal priority.
5. Stable behavior does not move priority 4 ahead of priority 1.
6. A client needs a separate fairness policy if indefinite waiting is not
   acceptable.

One possible policy is **aging**, meaning an explicit rule that improves a
record's effective priority as waiting time grows. Aging is not implemented
in this module.

## Model 11 - Controlled priority changes

A **mutable priority** is a priority allowed to change while its record
waits. Clients must not silently edit a live record through the owned array.

Two later strategies:

```text
decrease-key:
old record -> defined update -> repair backend position

duplicate-entry:
old version remains
new version is inserted
later removal checks version
old version is recognized as stale and ignored
```

**Decrease-key** is a defined operation that lowers a stored priority and
repairs the backend. A **duplicate entry** is a new version inserted instead
of editing the old one. A **stale entry** is an older version that no longer
represents current information.

Exact linear equivalent:

1. A silent priority edit bypasses the Priority Queue contract.
2. A defined decrease-key operation changes priority and repairs the
   backend.
3. A duplicate strategy inserts a new version.
4. The client stores an identity plus version, generation, or current best
   value.
5. When an older version leaves, the client recognizes it as stale.
6. Module 10 implements neither update strategy; they are previews.

## Model 12 - Linear to tree to graph spiral

```text
Module 7 Queue
oldest waiting item
        |
        v
Module 10 Priority Queue
smallest priority, then earliest sequence
        |
        v
Module 11 binary Heap backend
same Priority Queue service rule with faster minimum removal
        |
        v
Module 12 Dijkstra
smallest currently known path cost controls exploration
```

A **binary Heap** is a compact tree-shaped arrangement stored in an array;
Module 11 defines its rules. A graph models objects and the connections
between them. An edge is one modeled connection. **Dijkstra's algorithm**
is a later graph procedure for minimum-cost paths when every edge cost
satisfies the procedure's required rules.

Exact linear equivalent:

1. Module 7 FIFO selects the oldest waiting item.
2. Module 10 changes the public selection rule to priority then sequence.
3. Module 10's unsorted array scans to find that record.
4. Module 11 changes the backend while preserving the public comparator.
5. Module 12 uses a minimum-priority decision to choose weighted graph work.
6. A faster backend must not change which logical record ranks first.

## Model 13 - Safe interpretation boundary

```text
course priority number
        |
        v
defined in-memory service order

course priority number
        X
does not prove authenticity, severity, exploitability, or fair handling
```

The `X` means "does not establish."

Exact linear equivalent:

1. The exercise uses synthetic, meaning invented, alert records.
2. The priority number controls only the course comparator.
3. Passing tests supports only the documented in-memory behavior.
4. It does not prove that a real alert is authentic.
5. It does not prove real severity, completeness, timeliness, compromise,
   or exploitability, meaning whether a weakness can actually be used.
6. It does not prove that a failed insertion was retried or retained.
7. It does not prove fair staffing or overall system security.
