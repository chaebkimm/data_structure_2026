# Student Textbook — Priority Queue

## Essential question

> If urgent alerts should be processed before routine alerts, what replaces
> arrival order, and what does that choice cost?

## 1. The service problem

A **security alert** is a stored notice that a system may need attention.
Our alerts are **synthetic**, meaning invented for safe study. An alert ID
identifies a record; it does not measure urgency.

Module 7's Queue used **first-in, first-out (FIFO)** order: the earliest
arrival left first. A **priority** is a number used to rank service. Here a
smaller priority leaves first; it is not proof of real danger.

## 2. The public behavior

A **data structure** organizes information. An **abstract data type (ADT)**
states public operations and rules without choosing storage.

A **Priority Queue ADT** reports or removes the item ranked first. This
course uses a **minimum-priority Queue**, so the smallest priority is first.

- `insert` adds one alert.
- `peek-min` reports the first alert without removing it.
- `extract-min` removes and reports the first alert.

A **tie** occurs when priorities are equal. **Stable tie behavior** means
tied alerts leave in arrival order. The Priority Queue assigns an
**arrival sequence**, an increasing number, at each successful insertion.

A **comparator** decides which of two records comes first. Below, `a` and
`b` name records, and a dot selects one field:

```text
a comes before b when
a.priority < b.priority
or priorities tie and a.arrival_sequence < b.arrival_sequence
```

The symbol `<` means “is smaller than.” Alert ID is never compared.

## 3. One array backend

A **record** groups named values called **fields**:

```c
typedef struct {
    int alert_id;
    size_t priority;
    size_t arrival_sequence;
} AlertRecord;
```

`int` is a C whole-number type. `size_t` is C's nonnegative type for sizes,
indexes, and sequences.

A **backend** is one storage method used to provide ADT behavior. This
module uses an **unsorted dynamic array**. An array is a numbered row. An
**allocation** is a storage block obtained while a program runs; a dynamic
array may replace it with a larger one. Unsorted means physical order, the
actual index order, may differ from logical service order, the promised
removal order.

The object stores:

```text
data, size, capacity, next_sequence, comparison_count
```

`data` points to the owned record array. A **pointer** stores a memory
address. `size` counts live records. `capacity` counts allocated positions.
`next_sequence` is assigned to the next successful insertion.
`comparison_count` records comparator calls.

Initialization creates all-zero state. Valid capacities are exactly 0, 4,
8, 16, 32, and 64; growth follows that order.

## 4. Insert and scan

Insertion appends at physical index `size`. An **index** is a numbered array
position beginning at 0. Growth happens before the write. The record
receives `next_sequence`; then size and sequence advance. A failed growth or
exhausted sequence leaves the earlier object unchanged.

To peek or extract, scan indexes 0 through `size - 1`. A **scan** inspects
positions one at a time. Start with index 0 as the **candidate minimum**,
the best record found so far. Replace it only when a later record comes
before it under the complete comparator.

With current size `n`, a scan makes `n - 1` comparisons. The count
**saturates** at `SIZE_MAX`: it stays at that largest
`size_t` value instead of wrapping to zero.

Extraction copies the selected record, moves the last live record into its
position, and decreases size. This is **swap-with-last removal**. Physical
order may change, but stored sequences still settle ties correctly.

## 5. Canonical trace

The canonical, or shared course, insertions are:

```text
71/p3/s0, 88/p1/s1, 42/p2/s2, 17/p1/s3,
26/p4/s4, 9/p2/s5, 63/p1/s6
```

`p` labels priority and `s` labels arrival sequence. Capacity is 8, size is
7, and `next_sequence` is 7.

Logical service order is:

```text
88, 17, 63, 42, 9, 71, 26
```

The first extraction replaces 88 with the last record, 63:

```text
71, 63, 42, 17, 26, 9
```

The next scan selects 17 because sequence 3 precedes 6. Seven extractions
use `6 + 5 + 4 + 3 + 2 + 1 + 0 = 21` comparisons.

After the final extraction, size and `next_sequence` reset to 0. Capacity
and the allocation remain for reuse. Former array positions are inactive,
not logical alerts.

## 6. Valid state and failures

An **invariant** is a rule true in every valid completed state:

1. Capacity is exactly 0, 4, 8, 16, 32, or 64, and size does not exceed it.
2. Capacity 0 has every field zero or `NULL`; `NULL` means “points to no
   object.”
3. Positive capacity has non-NULL owned storage.
4. Live records occupy indexes below size.
5. Live sequences are unique and below `next_sequence`.
6. Empty state has `next_sequence == 0`.
7. Physical order need not be sorted.

`alert_priority_queue_validate` is a constant-time shape check.
**Constant-time** means its work does not grow with size. It checks fields,
not every record. A pointer value alone cannot prove that an allocation is
live, large enough, uniquely owned, or filled with valid records.

**Failure preservation** means a failed call leaves protected state and
output unchanged. A **caller** is code requesting the operation. Empty
access does not overwrite its output. Other failures do not change logical
contents.

Records are returned by copy. An output address must not point inside the
owned array. Do not shallow-copy the owning struct: copying its fields
would create two apparent owners of one allocation.

## 7. Costs and backend choice

**Time complexity** describes how work grows. `O(1)`, read “order one,”
means bounded work. `O(n)` means work may grow with `n` live records.
**Amortized `O(1)`** means average constant work across many insertions,
including occasional array growth.

| Unsorted-array operation | Cost |
|---|---:|
| insert | amortized `O(1)` |
| peek-min | `O(n)` |
| extract-min | `O(n)` |

A paper-only **sorted array** can store worst records first and the minimum
at the removable right end. Insertion then finds a position and shifts
records, so it is `O(n)`. Peek and extraction are `O(1)`. If the minimum
were at index 0, extraction would shift remaining records and become
`O(n)`.

For 32 chosen sorted insertions that each cross earlier records,
`0 + 1 + ... + 31 = 496` comparisons. Unsorted append uses zero. Extracting
32 unsorted records uses 496; right-end sorted removal uses zero. A
**workload** is a chosen operation mixture.

## 8. Policy hazards

**Starvation** means an item waits indefinitely because other items keep
ranking ahead. Stable ties do not help a priority-4 alert when priority-1
alerts never stop arriving. Fairness requires a separate policy, such as
aging a waiting score or reserving service time.

A **mutable priority** may change while a record waits. Clients must not
edit owned records directly. A future ordered backend could silently
lose its ordering rule.

**Decrease-key** explicitly lowers one priority and repairs the backend. It
is not implemented. Another strategy inserts a newer copy. The old
**stale entry** must be recognized using an ID plus an increasing update
number or current-best record.

## 9. Forward and safe interpretation

A **binary Heap** is an array-backed tree with a minimum at a known
position. It preserves the Priority Queue rule with less scanning.
Dijkstra's algorithm, a path-finding procedure, ranks unfinished graph work
by smallest known cost instead of FIFO.

This lab models one in-memory operation at a time. It does not
prove that real alerts are authentic, complete, timely, severe, durable, or
fairly handled. It must not process live operational alerts.

**Key sentence:** priority and arrival sequence define service order;
backend choice determines its cost.
