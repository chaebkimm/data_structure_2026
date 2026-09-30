# Stage E - C Lab: Sparse Indicator Hash Table

## Purpose

Complete a bounded open-addressed hash table for `uint32_t` keys and `int`
values. Preserve exact-key map behavior across collisions, wraparound,
deletion, compaction, growth, allocation failure, and the maximum-capacity
boundary.

The supplied scaffold owns initialization, result types, shallow active-
shape checks, full diagnostic validation, allocation wrappers, bounded raw
placement support, public operation wrappers, cleanup, status names, and
allocation test hooks. Your work is limited to exactly three TODO clusters,
including the transactional replacement logic.

## Locked public contract

The public types and declarations are in `code/include/hash_table.h`.

```c
typedef struct {
    HashSlot *slots;
    size_t size;
    size_t tombstones;
    size_t capacity;
} HashTable;
```

Active capacity is 8, 16, 32, or 64. Home is `key % capacity`. Key 0 is
legal. Slots are empty, occupied, or deleted. Inactive empty/deleted slots
have key 0 and value 0.

`hash_table_init` accepts only the all-zero state and allocates capacity 8.
The all-zero state is valid for the diagnostic validator but is not active;
put, get, and remove reject it as `HASH_TABLE_INVALID_STATE`.

Public result types are:

```c
typedef struct { bool inserted; size_t probe_count; } HashTablePutResult;
typedef struct { bool found; int value; size_t probe_count; } HashTableGetResult;
typedef struct { bool removed; int value; size_t probe_count; } HashTableRemoveResult;
```

A successful miss has a false Boolean, value 0, and the number of inspected
slots. A non-`OK` status preserves the complete caller result. Null table or
result is `HASH_TABLE_INVALID_ARGUMENT` before any state check.

## Files and build

Edit only:

```text
code/starter/hash_table.c
code/tests/test_student.c
```

From the `code/` directory, use the supplied warning-enabled build:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target starter
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target starter -StudentTests
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target autopsy
```

GNU Make users may run:

```text
make starter-core
make starter-student-tests
make autopsy
```

Preserve commands and output. Run the smallest relevant test after each
change. Do not edit the public header to make a failing implementation appear
correct.

## TODO 1 - Capacity-bounded probe walk

Complete `probe_for_key`.

1. Calculate home as `key % table->capacity`.
2. Begin with no remembered deleted index.
3. For `step` from 0 while `step < capacity`, calculate
   `(home + step) % capacity`.
4. Count exactly one probe for every inspected slot.
5. If an occupied slot contains the requested key, return found and its
   index.
6. If the first deleted slot appears, remember its index and continue.
7. At an empty slot, return missing and choose the remembered deleted index,
   or the empty index if no deleted slot was seen.
8. Reject an unknown state through the helper's invalid result.
9. After a full-capacity walk, return missing and the remembered deleted
   index, if any.

Never return at a deleted slot. Never probe beyond capacity. The helper does
not mutate the table.

Checkpoints:

```text
10,18,26 puts: probe counts 1,2,3
get26: found true, value260, probes3
get34: found false, value0, probes4
7,15,23 puts: probe counts 1,2,3 and final indexes 7,0,1
```

## TODO 2 - Commit insert, update, and removal mutations

Complete `commit_put` and `commit_remove`. The public operations have already
performed shallow active-shape checks and the TODO 1 search. These helpers
must interpret that probe result without searching a second time.

For `commit_put`:

1. Prepare `{inserted=false, probe->probe_count}` locally.
2. If the key was found, update only that slot's value, publish the result,
   and return `OK`.
3. Reject a missing insertion index as invalid state.
4. If the selected target is deleted, reuse it: decrement tombstones, write
   the new key/value/occupied state, and increment size.
5. If the target is empty and effective occupancy remains within three
   quarters, write it directly and increment size.
6. If an empty-target insertion would cross the boundary, request
   same-capacity rebuild when tombstones exist, doubling when no tombstones
   exist and capacity is below 64, or report full at 64.
7. Set inserted true and publish the result only after direct insertion or a
   successful transactional rebuild.

For `commit_remove`:

1. Prepare removed, value, and probe count locally. A miss uses removed false
   and value 0.
2. On a hit, clear key and value, write `HASH_SLOT_DELETED`, decrease size,
   and increase tombstones.
3. Publish the complete result last and return `OK`.

Checkpoints:

```text
update key26 beyond a tombstone -> inserted false, probes3, one live key26
insert key34 through that route -> inserted true, probes4, tombstone reused
remove key18 -> removed true, value180, probes2, index3 DELETED
get key26 after removal -> found true, value260, probes3
```

## TODO 3 - Build and commit transactional maintenance

Complete `rebuild_with_entry`. TODO 2 selects either the existing capacity
for compaction or double capacity for growth.

1. Allocate a zeroed replacement array of `new_capacity`.
2. On allocation failure, return `HASH_TABLE_ALLOCATION` without changing
   the old table.
3. Scan old indexes in increasing order.
4. Use the supplied bounded raw placement for each occupied key/value pair.
   Skip empty and deleted slots.
5. Place the requested new key/value into the replacement.
6. If any internal placement fails, release only the replacement and return
   invalid state.
7. Save the old pointer, then commit replacement pointer, incremented size,
   zero tombstones, and new capacity.
8. Release the old allocation only after commit.

Do not call the full public validator inside maintenance; that would add a
separate quadratic diagnostic to the rebuild. Internal placements and the
requested key's final replacement-table placement do not add to the
caller-visible probe count.

Checkpoints:

```text
six direct keys at capacity8, then a seventh distinct key -> capacity16
capacity8 size2 tombstones4, empty-home put -> capacity8, tombstones0
capacity64 size48 tombstones0, distinct empty-home put -> HASH_TABLE_FULL
capacity64 existing-key update -> HASH_TABLE_OK, inserted false
replacement allocation failure -> old pointer/table/result unchanged
```

## Exactly three student-authored test categories

Write exactly three numbered test functions. State each claim before its
assertions.

1. **Collision, wraparound, and exact probes:** build both `10,18,26` and
   `7,15,23`, assert physical indexes, present/missing results, exact probe
   counts, validation, and cleanup.
2. **Tombstone reachability, update, and reuse:** remove 18, find 26 through
   the tombstone, update 26 without duplication, insert 34 into the first
   deleted position only after proving absence, and assert exact
   size/tombstone changes.
3. **Maintenance and failure preservation:** trigger growth at the seventh
   direct key, separately trigger same-capacity compaction after four
   removals, then force a maintenance allocation failure and prove pointer,
   slots, counts, caller result, and live-allocation ownership are unchanged;
   destroy every initialized table.

Initialization allocation failure, malformed states, unknown slot states,
inactive-field canonicalization, key `UINT32_MAX`, capacity-64 full/update,
and additional full-probe states are covered by supplied core or private
tests. Renaming a supplied test does not make it original.

## Validation rule

Use `hash_table_validate` at checkpoints in debug/test work. It performs a
full diagnostic scan for exact counts, canonical inactive slots, unique keys,
and probe reachability. Ordinary operations perform only constant-time active
shape checks. Do not include the validator's possible quadratic work in an
expected constant-time operation claim.

## Safe autopsy

Complete `student/hash_table_autopsy.md` before and after the bounded
`faulty_delete_empty.c` demonstration. Predict first. The defect marks the
removed middle slot empty; get 26 stops there and falsely reports missing.
This is a logical invariant failure, not an out-of-bounds access or a use-
after-free.

## Cost and security scope

- Let `n` be live entries and `m` capacity. Expected requested-key probe work
  is `O(1)` only with suitable key distribution and controlled occupancy.
- One requested-key route may inspect `O(m)` slots. Because this table does
  not shrink and may retain tombstones, that is not always `O(n)`.
- Rehash scans `m` old slots and reinserts `n` entries: expected `O(m)`,
  worst `O(m + n^2)`, bounded `O(m^2)`, with temporary `O(m)` space. At a
  growth event `m = Theta(n)` (capacity and live count differ only by
  constant factors), this is expected `O(n)` and worst `O(n^2)`.
- Geometric growth supports expected amortized `O(1)` for an insertion-only
  growth sequence under the same assumptions. Repeated deletion/insertion
  compaction is outside that stronger claim.

The course remainder function is transparent and non-cryptographic. Chosen
colliding keys demonstrate a hash-flood mechanism but do not by themselves
prove denial of service, memory corruption, or resource exhaustion. Passing
validation does not authenticate keys or values.

## Submission

Submit:

- exactly three completed TODO clusters;
- exactly three student test categories;
- warning-clean core and student-test output;
- collision, wrap, deletion, compaction, and growth evidence;
- full and failure-preservation evidence;
- completed evidence record and safe autopsy;
- direct-array, AVL, and separate-chaining comparison;
- precise `n`/`m`, expected/worst/rebuild/amortized cost statements; and
- corrected preserved Cognitive Pause and investigation artifacts.
