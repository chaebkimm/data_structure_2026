# Stage C - Hash-Table Investigation

Name: ____________________________  
Date: ____________________________

Preserve Sections A through F before opening the textbook or code. Add
labeled corrections after comparison. Use `E`, `O`, and `D` for empty,
occupied, and deleted when space is limited.

Unless a prompt says otherwise, capacity is 8 and `home = key % 8`.

## A. Separate map behavior from direct indexing - 10 points

### A1. Identify key and value - 3 points

For the record `key 18 -> value -4`, identify the key and value. State what
must happen if a later `put` supplies key 18 with value 70.

____________________________________________________________________

### A2. Explain sparse direct-index cost - 3 points

A `uint32_t` key can be greater than four billion. Explain why allocating
one `int` position for every possible key is a poor fit when only 20 records
are live.

____________________________________________________________________

### A3. Calculate homes - 4 points

Complete the capacity-8 calculations.

| Key | Remainder expression | Home | Same home as |
|---:|---|---:|---|
| 10 |  |  |  |
| 18 |  |  |  |
| 26 |  |  |  |
| 7 |  |  |  |
| 15 |  |  |  |
| 23 |  |  |  |

## B. Trace collision and wraparound - 15 points

### B1. Build the canonical collision cluster - 6 points

Insert `(10,100)`, `(18,180)`, and `(26,260)` in that order. For each put,
record its inspected indexes, final index, `inserted`, and `probe_count`.

| Put | Inspected indexes | Final index | `inserted` | `probe_count` |
|---|---|---:|:---:|---:|
| `(10,100)` |  |  |  |  |
| `(18,180)` |  |  |  |  |
| `(26,260)` |  |  |  |  |

Draw or list all eight final slot states and occupied records.

____________________________________________________________________

### B2. Wrap safely - 5 points

Start with a fresh table. Insert `(7,70)`, `(15,150)`, and `(23,230)`.
Show every inspected index and the final array. Explain how the operation
keeps every array access in range.

____________________________________________________________________

____________________________________________________________________

### B3. Stop a missing search - 4 points

Return to B1. Complete both `HashTableGetResult` values.

| Get | Inspected indexes | `found` | `value` | `probe_count` | Stop reason |
|---|---|:---:|---:|---:|---|
| key 26 |  |  |  |  |  |
| key 34 |  |  |  |  |  |

## C. Preserve routes and unique keys - 15 points

### C1. Remove with a tombstone - 5 points

From the B1 table, apply `remove(18)`. Record the complete remove result,
index 3's new state, size, and tombstone count. Then trace `get(26)`.

____________________________________________________________________

____________________________________________________________________

### C2. Update beyond a tombstone - 5 points

From C1's state, apply `put(26,999)`. Record every inspected index and the
complete put result. State the final value and location of key 26, size,
tombstone count, and why no second key 26 may be created.

____________________________________________________________________

### C3. Reuse only after proving absence - 5 points

Return to C1's state before C2, then apply `put(34,340)`. Trace through the
first empty slot even though a deleted slot appears earlier. State where 34
is committed and the final size and tombstone count.

____________________________________________________________________

## D. Compact or grow transactionally - 15 points

At capacity 8, three quarters is 6. Maintenance is required before a new
distinct key when `size + tombstones + 1 > 6`.

### D1. Select the maintenance action - 5 points

For each state, assume the distinct-key search selects an `EMPTY` insertion
slot. Choose `none`, `compact at 8`, `grow to 16`, or `full`. Show both the
effective-occupancy calculation and the live-after-insert calculation.

| Capacity | Size | Tombstones | Proposed distinct put | Action |
|---:|---:|---:|---|---|
| 8 | 2 | 3 | one key |  |
| 8 | 2 | 4 | one key |  |
| 8 | 6 | 0 | one key |  |
| 64 | 48 | 0 | one key |  |

Why may an update of an already-present key proceed in the final row?

____________________________________________________________________

### D2. Trace same-capacity compaction - 5 points

Use this exact capacity-8 state:

```text
index 0 E
index 1 E
index 2 O key10 value100
index 3 D
index 4 O key26 value260
index 5 D
index 6 D
index 7 D
size 2, tombstones 4
```

Apply `put(8,80)`. Show the pre-maintenance requested-key search, explain why
capacity remains 8, reinsert the two occupied entries in old-index order,
then place key 8. List the final eight slots, size, tombstones, and put probe
count. Internal maintenance placements do not add to that count.

____________________________________________________________________

____________________________________________________________________

### D3. Rehash on growth and preserve failure - 5 points

Suppose occupied keys 10, 18, and 26 are rehashed from capacity 8 to 16 in
that old-slot order. Calculate each new home and final index.

| Key | New home | Final index |
|---:|---:|---:|
| 10 |  |  |
| 18 |  |  |
| 26 |  |  |

List every old-table fact that must remain unchanged if replacement
allocation fails before commit.

____________________________________________________________________

## E. Validate state and preserve errors - 15 points

### E1. Check representation rules - 5 points

For each condition, state whether it is valid and name the rule involved.

1. Capacity 8, size 3, tombstones 1, exactly three reachable occupied slots
   and one canonical deleted slot: __________________________________
2. Capacity 12 with a nonnull allocation: __________
3. Two occupied slots both contain key 26: __________
4. Key 26 sits after an empty slot on its probe route: __________
5. Canonical all-zero destroyed state: __________

### E2. Apply status and output rules - 5 points

The API uses this precedence: null table/result is
`HASH_TABLE_INVALID_ARGUMENT`; malformed or destroyed state passed to
`put`, `get`, or `remove` is `HASH_TABLE_INVALID_STATE`; allocation and full
are considered only for a new key after searching for an existing key.

For each call, state the status and whether the caller's result struct may
change.

1. `get(valid_table, 26, NULL)`: _________________________________
2. `put(destroyed_table, 1, 2, valid_result)`: ___________________
3. missing `get` on a valid table: _______________________________
4. failed growth allocation: ____________________________________

### E3. Explain ownership and cleanup - 5 points

Explain why a live `HashTable` may not be shallow-copied, why replacement
must be committed only after successful rehash, and what exact state destroy
restores.

____________________________________________________________________

____________________________________________________________________

## F. Analyze cost, selection, and security - 10 points

### F1. State operation costs with assumptions - 4 points

Let `n` be live entries and `m` capacity. State expected and worst
requested-key probe work for get, put, and remove. State expected and worst
total rehash work, including the old-array scan and `n` internal insertions.
Explain why expected `O(1)` is conditional and why worst probe `O(m)` does
not always simplify to `O(n)` in this no-shrink implementation.

____________________________________________________________________

### F2. Select among four representations - 3 points

Give one workload that favors each: direct-index array, open-addressed hash
table, AVL tree, and separate chaining. Include sorted traversal or range
queries in your comparison.

____________________________________________________________________

### F3. Limit the security claim - 3 points

Explain hash-flood algorithmic-complexity denial of service at the level
demonstrated here. State two things the course remainder function and passing
validator do not prove.

____________________________________________________________________

## G. Design exactly three tests - later work - 9 points

### G1. Collision, wraparound, and bounded probes - 3 points

Design one test using both canonical key families. Require exact slots,
results, probe counts, and no out-of-range access.

____________________________________________________________________

### G2. Tombstone, update, and reuse - 3 points

Design one test proving lookup through a deletion, update beyond the first
tombstone, reuse for a missing key, and exact size/tombstone counts.

____________________________________________________________________

### G3. Maintenance and preservation - 3 points

Design one test covering same-capacity compaction, growth, forced maintenance
allocation failure, complete table/result/ownership preservation, and
destruction.

____________________________________________________________________

## H. Complete the bounded autopsy - later work - 6 points

### H1. Find the first wrong state - 2 points

In the faulty deletion, identify the assignment that changes index 3 to the
wrong state and the first later operation that exposes the defect.

____________________________________________________________________

### H2. Repair and verify - 2 points

State the correct slot state and the exact `get(26)` route/result after the
repair.

____________________________________________________________________

### H3. Add a regression - 2 points

Describe a smallest test that fails for delete-to-empty and passes for a
tombstone.

____________________________________________________________________

## I. Synthesize - later work - 5 points

### I1. Connect invariant to operation - 2 points

Explain how the distinction between empty and deleted lets lookup stop early
without losing colliding keys.

____________________________________________________________________

### I2. Select and qualify - 2 points

Choose hash table or AVL for exact unordered lookup, then identify one
requirement or threat that could reverse or qualify the choice.

____________________________________________________________________

### I3. Exit synthesis - 1 point

Complete: “A hash table can avoid an ordinary full scan when __________,
but it can still require linear work when __________.”

____________________________________________________________________
