# Module 13 Instructor Technical Notes

## 1. Scope and dependency boundary

This module teaches an exact-key map implemented by open addressing with
linear probing. Core scope includes:

- `uint32_t` key to `int` value;
- capacities 8, 16, 32, and 64;
- explicit empty, occupied, and deleted states;
- bounded probe routes with wraparound;
- insert-or-update, get, and remove;
- same-capacity compaction and geometric growth;
- transactional rehash and allocation-failure preservation;
- full diagnostic validation; and
- qualified expected, worst-case, and security claims.

Do not add string ownership, generic `void *` values, custom user hash
callbacks, concurrency, iteration-order promises, cryptographic hash design,
Robin Hood probing, cuckoo hashing, or incremental rehashing to the core.
Separate chaining is a comparison and extension, not a second required
implementation.

The transparent remainder function is intentional. Students can reproduce
all exact routes before reasoning about hash quality. Do not present it as a
production recommendation.

## 2. Public API and statuses

The locked public structures are in `code/include/hash_table.h`:

```c
HashTableStatus hash_table_init(HashTable *table);
HashTableStatus hash_table_validate(const HashTable *table);
HashTableStatus hash_table_put(
    HashTable *table,
    uint32_t key,
    int value,
    HashTablePutResult *out_result
);
HashTableStatus hash_table_get(
    const HashTable *table,
    uint32_t key,
    HashTableGetResult *out_result
);
HashTableStatus hash_table_remove(
    HashTable *table,
    uint32_t key,
    HashTableRemoveResult *out_result
);
void hash_table_destroy(HashTable *table);
```

Status meanings:

- `HASH_TABLE_OK`: completed operation, including get/remove miss and put
  update;
- `HASH_TABLE_INVALID_ARGUMENT`: required pointer is null;
- `HASH_TABLE_ALLOCATION`: an attempted table allocation failed;
- `HASH_TABLE_FULL`: a new distinct key would cross the maintained bound at
  capacity 64 with no tombstones to compact; and
- `HASH_TABLE_INVALID_STATE`: active shape, slot state, probe result, or
  internal placement contradicts the contract.

Error precedence is locked.

For put/get/remove:

1. null table or result -> invalid argument;
2. failed constant-time active-shape check -> invalid state;
3. invalid state encountered along the requested probe -> invalid state;
4. successful match/miss logic;
5. for distinct put only, maintenance allocation or full decision.

Thus an existing-key update at the maximum live boundary succeeds. It does
not require allocation or more occupancy.

All result structs are local until success. Non-`OK` preserves the complete
caller result. Successful misses publish false, value 0, and the exact probe
count. Never describe a miss as an error status.

## 3. Representation and ownership

The canonical destroyed state is:

```text
slots NULL, size 0, tombstones 0, capacity 0
```

`hash_table_validate` accepts it. `hash_table_init` requires it, allocates
eight zeroed slots, and commits pointer/capacity only after allocation
success. Put/get/remove require an active state, so they reject all zero.

Positive capacity owns one `HashSlot[capacity]` allocation and is exactly 8,
16, 32, or 64. A live table must not be shallow-copied. Destroy accepts null,
releases the slot allocation for a contract-valid active table, and resets
all fields. Repeated destroy of the all-zero state is safe.

Every inactive slot is canonical:

```text
EMPTY:   key 0, value 0
DELETED: key 0, value 0
```

Key 0 remains legal because state, not a sentinel key, identifies activity.
Occupied values may be any `int`, including 0.

## 4. Occupancy invariant

The exact nonempty-state limit is:

```text
limit(capacity) = (capacity / 4) * 3
```

Therefore limits are:

| Capacity | Nonempty-state limit |
|---:|---:|
| 8 | 6 |
| 16 | 12 |
| 32 | 24 |
| 64 | 48 |

Every valid active table satisfies:

```text
size + tombstones <= limit(capacity)
```

This integer formulation avoids floating point. Because supported capacities
are divisible by four and tiny, the arithmetic is exact and cannot overflow.

For a selected deleted insertion target, the transition is
`size+1,tombstones-1`, so the sum is unchanged. For a selected empty target,
the proposed sum is `size+tombstones+1`. Only the latter can request
maintenance.

## 5. Constant-time shape check versus full validator

Ordinary operations use `has_valid_active_shape`, which checks only:

- nonnull slots;
- supported capacity;
- size at most capacity;
- tombstones at most remaining capacity; and
- nonempty-state count at most the three-quarter limit.

This is `O(1)`. It does not scan slot states, count exact entries, detect a
duplicate outside the route, or prove reachability.

The explicit `hash_table_validate` accepts canonical all zero or performs a
full diagnosis:

1. shape and maintained occupancy;
2. valid state tag at every index;
3. zero inactive key/value fields;
4. exact occupied and deleted counts;
5. pairwise duplicate-key rejection; and
6. for each occupied key, a bounded home-to-index path with no earlier empty.

The pairwise duplicate scan and per-key reachability scan make the teaching
validator `O(m^2)` worst case. Do not call it inside ordinary operations or
rehash, and do not advertise it as part of expected `O(1)` lookup.

## 6. Probe helper

`probe_for_key` returns:

```text
valid
found
found_index
insertion_index
probe_count
```

Initialize `insertion_index` and the local first-deleted marker to
`SIZE_MAX`. For each step less than capacity:

```text
index = (home + step) % capacity
```

Count the inspected slot before interpreting it.

- matching occupied -> found and return;
- first deleted -> remember and continue;
- empty -> missing; insertion index is first deleted if present, otherwise
  this empty index; return;
- occupied different -> continue;
- unknown state -> invalid and return.

After capacity inspections, insertion index is the first deleted marker or
`SIZE_MAX`. Under the full valid invariant there is normally an empty slot,
but the bound and invalid-state path keep the helper safe under shallowly
plausible input.

Probe count includes a terminating empty slot. It counts only the requested
key's search in the caller-visible table. It excludes internal rehash work
and the requested entry's internal replacement-table placement.

## 7. Put commit logic

The public put performs shallow checks and one probe, then calls
`commit_put`.

On found:

- update the existing slot's value;
- report inserted false and original probe count;
- preserve size, tombstones, capacity, key, state, and allocation.

On missing, require an insertion index. If the target is deleted, decrement
tombstones and use it. If target is empty and proposed effective occupancy is
within the limit, use it directly.

For an empty target beyond the limit:

- tombstones positive -> rebuild at the same capacity;
- no tombstones and capacity below 64 -> double capacity;
- no tombstones and capacity 64 -> full.

This selection works because a valid table with tombstones has live size
strictly below the nonempty limit, so same-capacity compaction creates room
for the requested entry.

The result is published only after direct mutation or successful rebuild.
Allocation/full/internal errors preserve it.

## 8. Remove commit logic

The public remove shallow-checks and probes, then `commit_remove` prepares a
local result.

Miss:

```text
removed false, value 0, actual probe count, no mutation
```

Hit:

1. save the old value in the local result;
2. write key 0 and value 0;
3. write `HASH_SLOT_DELETED`;
4. decrement size;
5. increment tombstones; and
6. publish the result.

Do not collapse an entirely drained active table automatically. Keeping its
allocation is permitted. Later insertion can reuse a deleted slot or compact
when an empty-target insertion crosses the effective-occupancy bound.

## 9. Transactional rebuild

`rebuild_with_entry` receives either the same supported capacity or double
capacity plus the requested new record. The order is:

1. allocate a zeroed replacement;
2. scan old indexes from 0 upward;
3. raw-insert every occupied entry using replacement capacity;
4. skip empty and deleted entries;
5. raw-insert the requested entry;
6. if any placement fails, release only replacement and return invalid state;
7. save old pointer;
8. commit replacement pointer, `size+1`, tombstones 0, and new capacity; and
9. release old pointer.

`raw_insert` is capacity-bounded and only needs empty handling because the
replacement begins empty and source keys are unique under the precondition.
No fallible step follows the public-table commit.

Do not insert the requested key into the old table before allocation. Do not
use `realloc`: compaction may retain capacity, and transactional rebuilding
requires both old and replacement states until complete. Do not invoke the
quadratic public validator during rebuild; it is a separate diagnostic, not
part of internal placement.

## 10. Canonical measurements

Collision fixture at capacity 8:

| Operation | Route | Result |
|---|---|---|
| put 10/100 | 2 | inserted true, probes 1 |
| put 18/180 | 2,3 | inserted true, probes 2 |
| put 26/260 | 2,3,4 | inserted true, probes 3 |
| get 26 | 2,3,4 | found true, value 260, probes 3 |
| get 34 | 2,3,4,5 | found false, value 0, probes 4 |
| remove 18 | 2,3 | removed true, value 180, probes 2 |
| get 26 after | 2,3,4 | found true, value 260, probes 3 |
| update 26/999 | 2,3,4 | inserted false, probes 3 |
| put 34/340 | 2,3,4,5 | inserted true at 3, probes 4 |

Wrap fixture: keys 7, 15, 23 finish at 7, 0, 1 with probe counts 1, 2, 3.
Missing 31 follows `7,0,1,2`, false/value0/probes4.

Growth fixture: direct keys 0 through 5 occupy capacity 8. Put key 6
initially examines empty 6 once, triggers growth, and reports probes 1. The
result is capacity 16, size 7, tombstones 0.

Compaction fixture: direct keys 0 through 5, then remove 0 through 3. Size 2,
tombstones 4. Put key 6 examines empty 6 once, compacts at capacity 8, and
finishes with keys 4, 5, 6 at their direct homes, size 3, tombstones 0.

Maximum fixture: 48 direct keys at capacity 64. Put new key 48 reports full
and preserves result/table. Updating key 47 succeeds. Removing key 0 creates
a deleted slot. Put key 48 selects its empty home, so the tombstone causes a
same-capacity compaction; key 48 finishes at index 48, size is 48, and
tombstones is 0.

## 11. Cost analysis

Let `m` be capacity and `n` live size. This implementation does not shrink,
so current `m` need not be proportional to live `n` after deletions. The
maintained bound applies to `n + tombstones`, not to `n` alone.

- adequately distributed ordinary get/put/remove: expected `O(1)` requested-
  key probes;
- collision-cluster requested-key probing: worst `O(m)`; this does not always
  simplify to `O(n)` in the no-shrink implementation;
- raw placement during rebuild: expected `O(1)`, worst `O(m)`;
- complete rebuild scans `m` and reinserts `n`: expected `O(m)`, worst
  `O(m + n^2)`, and therefore bounded `O(m^2)`;
- at a growth event `m = Theta(n)`: rebuild expected `O(n)`, worst `O(n^2)`;
- public teaching validator: `O(m^2)` worst case;
- owned table space: `O(m)`;
- rebuild temporary peak: old plus new arrays, still `O(m)`.

Be careful with the phrase amortized. Geometric growth spreads expected
growth-rebuild work across an insertion-only sequence, so that sequence has
expected amortized `O(1)` insertion under suitable distribution.
Same-capacity compaction still scans `m`; alternating deletion and insertion
can trigger it repeatedly. Chosen collisions can also defeat constant
placement. Do not state unconditional amortized `O(1)` for arbitrary mixed
operation sequences.

## 12. Representation comparisons

Direct indexing has a stronger worst-case lookup bound but allocates from the
key universe. It remains correct and preferable for dense bounded IDs.

AVL retains whole-key order, logarithmic worst-case lookup, sorted traversal,
range queries, predecessor/successor, and individually allocated nodes. It
has pointer/rotation overhead and different locality.

Separate chaining keeps a bucket array whose entries identify linked or
dynamic collision collections. It avoids open-addressing tombstones and can
exceed one entry per bucket-array position, but introduces per-chain
traversal and often additional allocations/ownership.

The course open-addressed table owns one compact slot allocation, offers no
stable physical or sorted order, and requires rehash after capacity change.

## 13. Security framing

The threat mechanism is:

- the attacker can choose accepted keys;
- the table uses a predictable function;
- many chosen keys share a home or cluster;
- operations perform linear rather than expected constant work; and
- repeated work may delay intended service.

Call it hash-flood algorithmic-complexity denial of service only when the
work can materially delay or deny service. The classroom fixture is a safe
bounded mechanism demonstration.

Growth controls occupancy but does not guarantee distribution. A keyed or
otherwise collision-resistant production strategy may be one mitigation,
but “use a cryptographic hash” is not a complete design answer and is outside
core implementation.

The table does not prove indicator authenticity, authorization,
completeness, freshness, confidentiality, durable retention, thread safety,
or overall system security. A valid representation can contain false values.

## 14. Autopsy boundary

The isolated defect writes empty instead of deleted when removing key 18
from the `10,18,26` cluster. The first wrong line is the state assignment.
The first observable divergence is get 26:

```text
correct: 2,3,4 -> found true, value260, probes3
faulty:  2,3   -> found false, value0, probes2
```

All accesses remain in range. Classify this as a logical invariant failure,
not memory corruption. The autopsy must never be linked into normal tests.

## 15. Private-test priorities

Prioritize:

1. key 0 and `UINT32_MAX`;
2. matching key before empty, and empty-stop metrics;
3. first deleted remembered across wraparound;
4. full-capacity bounded helper behavior on shallowly plausible fixtures;
5. update beyond deleted without duplicate;
6. canonical inactive key/value zeros after remove;
7. exact compaction/growth selection and excluded internal probes;
8. initialization and replacement allocation failures with pointer/result
   preservation and live-allocation baseline;
9. full at capacity 64 plus existing-key update and deleted-slot reuse;
10. validator count, unknown-state, duplicate, unreachable, inactive-field,
    and malformed-capacity cases; and
11. repeated destroy and null destroy.

Restore malformed fixtures before cleanup when necessary. Never release the
same allocation through two shallow-copied owners.
