# Module 13 Hash-Table C Package

This package implements a bounded map from every `uint32_t` key, including
zero and `UINT32_MAX`, to one `int` value. It uses an owned dynamic array,
`key % capacity`, and linear probing. Active capacities are 8, 16, 32, and
64. At most 48 mappings are live because effective occupancy is capped at
three quarters of capacity.

## Slot and operation contracts

Each slot is `EMPTY`, `OCCUPIED`, or `DELETED`. Empty and deleted slots have
canonical zero key/value fields; an occupied slot may legally contain key
zero. Lookup stops at a matching key or the first `EMPTY`, never at
`DELETED`, and every probe walk is bounded by the capacity.

`hash_table_put` updates an existing mapping without adding a duplicate.
For a distinct key it remembers the first tombstone but continues searching
for an existing key. It reuses that tombstone after the miss is proven.
When insertion into an empty slot would exceed the three-quarter effective
occupancy bound, the table transactionally:

- compacts at the same capacity if tombstones exist;
- doubles when no tombstones exist and capacity is below 64; or
- returns `HASH_TABLE_FULL` at capacity 64.

The replacement allocation is filled completely, including the requested
new entry, before the public table is changed. Allocation failure preserves
the old allocation, every field and slot, and the result output.

`hash_table_remove` writes a canonical tombstone so later colliding keys
remain reachable. A missing get/remove is successful and reports a false
flag plus value zero. Results change only when the operation returns
`HASH_TABLE_OK`.

## Probe counts and validation

Each result reports the number of slots examined for the requested key.
Misses count the terminating `EMPTY`. A put that triggers maintenance
reports its initial old-table search only; moving old entries and placing the
new entry in the replacement are internal rehash work and are excluded.

Normal operations perform constant-time public-field shape checks and then
one bounded probe walk. `hash_table_validate` is a separate full diagnostic.
It scans state/count consistency and canonical inactive slots, rejects an
unsupported capacity or excess effective occupancy, detects duplicate keys,
and proves each occupied slot is reachable from its home index without
crossing `EMPTY`. With capacity `C`, ordinary expected work is constant only
under the stated distribution and load assumptions; worst-case probing is
`O(C)`. For `n` live mappings in capacity `C`, a rebuild scans all `C` old
slots and reinserts the live mappings: expected `O(C)`, but worst-case
`O(C + n^2)`, which is at most `O(C^2)`. During no-tombstone growth,
`C = Theta(n)`, so those bounds simplify to expected `O(n)` and worst-case
`O(n^2)`. Expected amortized `O(1)` insertion is therefore conditional, not
unconditional. The full diagnostic is `O(C^2)`.

## Student-controlled work

The starter compiles with exactly three task clusters:

1. the complete capacity-bounded probe helper and exact counter;
2. insertion/update/removal mutations and result commitment; and
3. transactional same-capacity compaction or doubling.

Core tests lock collisions `10/18/26`, wrapping `7/15/23`, tombstone
reachability and reuse, duplicate prevention, growth, compaction, allocation
failure, maximum-capacity behavior, key boundaries, and destruction.
Extensions add deterministic differential churn and deliberate diagnostic
corruption. `test_student.c` contains three student-authored test prompts.

Under `HASH_TABLE_TESTING`, one hook fails the next attempted table
allocation and another reports currently live table allocations.

## Build commands

From this directory, the completed solution is the default:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 -Extensions
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 -Sanitize
```

The starter can be compiled without running intentionally failing core tests:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target starter -CompileOnly
```

The three student tests intentionally fail until completed:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target starter -StudentTests
```

The safe standalone autopsy is:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target autopsy
```

GNU Make targets include `solution-core`, `solution-extension`,
`starter-compile`, `starter-student-tests`, and `autopsy`.
