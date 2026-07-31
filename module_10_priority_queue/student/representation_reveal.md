# Stage B — Formal Name and Stored Form

Open this file only after preserving the Stage A inquiry.

## 1. Name the service rule

A **data structure** is a planned way to organize information. An
**abstract data type (ADT)** describes public behavior without requiring
one storage method.

A **Priority Queue ADT** reports or removes the item that ranks first under
a stated rule. This module uses a **minimum-priority Queue**: a smaller
numeric priority leaves before a larger one.

- `insert` adds one record.
- `peek-min` reports the next record without removing it.
- `extract-min` removes and reports the next record.

Module 7's Queue used first-in, first-out order. This collection uses
priority first and arrival only to settle equal priorities.

## 2. Make equal priorities deterministic

A **record** groups related values. Each course alert record has three
**fields**, or named parts:

```c
typedef struct {
    int alert_id;
    size_t priority;
    size_t arrival_sequence;
} AlertRecord;
```

The alert ID identifies a synthetic alert; it does not rank it. The
Priority Queue assigns `arrival_sequence` automatically. The first
successful insertion receives 0, the next receives 1, and so on.

A **comparator** is a repeatable rule for deciding which of two records
comes first. Record `a` comes before record `b` exactly when:

```text
a.priority is smaller
or
priorities are equal and a.arrival_sequence is smaller
```

This produces **deterministic** behavior: the same completed state gives the
same answer. It also gives **stable tie behavior**: equal-priority alerts
leave in arrival order. Never use alert ID as a hidden tie-breaker.

## 3. Use one unsorted dynamic array

An **array** is a numbered row of same-type values. A **dynamic array** owns
an allocation that may be replaced by a larger allocation while the program
runs. An **unsorted array** does not keep records in service order.

A **backend** is the storage method used to provide an ADT's behavior. This
module's backend stores:

```text
data              owned record array
size              number of live records
capacity          number of allocated record positions
next_sequence     sequence for the next successful insertion
comparison_count  number of record comparisons, capped at SIZE_MAX
```

`SIZE_MAX` is the largest value representable by `size_t`. A capped or
**saturating** count stays at `SIZE_MAX` instead of wrapping to zero.

Insertion appends at `data[size]`. Capacity grows 0 → 4 → 8 → 16 → 32 → 64.
The course limit is 64 live records.

## 4. Scan for the minimum

A **scan** inspects positions one by one. Begin with index 0 as the
candidate, meaning the best record found so far. Compare each later live
record with that candidate. Replace the candidate only when the later
record comes before it under the exact comparator.

A scan of `n` records makes `n - 1` comparisons. Here `n` means the current
number of live records. Peek scans but changes no logical record.

Extract scans, saves the selected record, replaces its position with the
last live record, and decreases size. This **swap-with-last removal** keeps
removal after the scan constant in size. Physical order may change; the
stored sequences still preserve equal-priority service order.

## 5. Trace a four-alert example

Records arrive in this order:

```text
id50 p2 s0
id11 p1 s1
id80 p1 s2
id34 p3 s3
```

Here `p` means priority and `s` means arrival sequence. The array remains in
insertion order. A four-record scan makes three comparisons and selects
id11. id80 has the same priority but arrived later.

After extracting id11, id34 moves into its physical position:

```text
id50 p2 s0, id34 p3 s3, id80 p1 s2
```

The next scan still selects id80. Complete service order is:

```text
id11, id80, id50, id34
```

## 6. State the representation rules

An **invariant** is a rule true in every valid completed state:

1. Capacity is exactly 0, 4, 8, 16, 32, or 64, and `size <= capacity`.
2. Capacity 0 has `data == NULL`, size 0, sequence 0, and comparison count
   0.
3. Positive capacity has non-NULL owned storage.
4. Live records occupy indexes 0 through `size - 1`.
5. Live sequences are unique and smaller than `next_sequence`.
6. An empty Priority Queue has `next_sequence == 0`.
7. Physical record order need not be sorted.
8. `comparison_count` never wraps after reaching `SIZE_MAX`.

When extraction removes the final record, capacity and allocation remain,
but size and `next_sequence` become 0. Destruction releases the allocation
and resets every field.

## 7. Prepare for the Cognitive Pause

Be ready to:

1. select a minimum using priority and sequence;
2. trace extract-min followed by insertion; and
3. separate stable ties from fairness and changing-priority policy.
