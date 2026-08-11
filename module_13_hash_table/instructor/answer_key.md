# Module 13 Instructor Answer Key

Accept equivalent linear, visual, tactile, typed, dictated, or verbal
evidence. Require exact values where the prompt locks them.

## Stage A key

### A. Avoid an enormous mostly empty row

Direct indexing uses positions 10, 18, and 26. It is not large for this tiny
sample, but a row covering all `uint32_t` keys would reserve billions of
positions even when almost all are unused.

```text
10 / 8 = 1 remainder 2
18 / 8 = 2 remainder 2
26 / 8 = 3 remainder 2
```

All start at spot 2, so a rule is needed to keep three different records
without overwrite or ambiguity.

### B. Use a repeatable next-spot rule

The final 10/18/26 row is:

```text
0 unused, 1 unused, 2 key10, 3 key18, 4 key26,
5 unused, 6 unused, 7 unused
```

Routes are 10: `2`; 18: `2,3`; 26: `2,3,4`.

The fresh wrap state is:

```text
index7 key7, index0 key15, index1 key23
all other positions unused
```

Routes are `7`; `7,0`; `7,0,1`.

Looking for 26 inspects `2,3,4`. Looking for missing 34 inspects
`2,3,4,5`. Spot 5 has never been used, so the fixed placement rule could not
have put key 34 farther along the route.

### C. Remove without breaking later searches

Spot 3 needs the crossed-out marker. Search for 26 then follows
`2,3,4`. Making 3 look never used would stop the search at 3.

For new key 34, remember 3 but inspect through 5. Reaching never-used spot 5
proves key 34 is absent; then 3 may be reused. For existing key 26, continue
through 3 and update the value at 4. Placing a second 26 at 3 would violate
one-key/one-value behavior and make later update/removal ambiguous.

### D. Cost and scope

Many chosen same-start IDs create a long run of inspections. A lookup or
placement can approach the number of stored records instead of a fixed small
amount. Quick placement does not prove indicator truth, authorization,
completeness, or system security.

Strong synthesis: use a repeatable starting calculation plus bounded
next-position search; distinguish never-used from removed so a valid route is
not cut.

## Cognitive Pause key

### Target 1

- `get(26)`: indexes `2,3,4`; found true; value 260; probe count 3.
- `get(34)`: indexes `2,3,4,5`; found false; value 0; probe count 4.
- The first stops on a matching occupied key. The second stops on empty 5.

### Target 2

- `remove(18)`: indexes `2,3`; removed true; value 180; probes 2. Index 3
  becomes deleted with key/value zero. Size 2, tombstones 1.
- `get(26)`: indexes `2,3,4`; found true; value 260; probes 3.
- `put(26,999)`: indexes `2,3,4`; inserted false; probes 3. Key 26 remains
  only at index 4 with value 999. Final size 2, tombstones 1.

### Target 3

- Capacity 8, size 2, tombstones 4, with an empty selected target: proposed
  effective occupancy `2+4+1=7`, above limit 6. Live after insertion is 3,
  so compact at capacity 8.
- Capacity 8, size 6, tombstones 0: proposal 7 is above 6 and no deleted
  states can be cleared, so grow to 16.
- Expected `O(1)` assumes adequate distribution and controlled occupancy.
  Chosen colliding keys can create a linear cluster. The remainder function
  organizes keys; it does not authenticate them and is not cryptographic.

## Investigation worksheet key

### A. Map and direct indexing

The key is 18 and the value is -4. A later put of `(18,70)` updates the one
existing entry. With only 20 live entries, a direct array covering more than
four billion positions has space tied to the universe rather than live data.

Homes at capacity 8:

```text
10 % 8 = 2; 18 % 8 = 2; 26 % 8 = 2
7 % 8 = 7; 15 % 8 = 7; 23 % 8 = 7
```

### B. Collision and wraparound

| Put | Route | Final | Inserted | Probes |
|---|---|---:|:---:|---:|
| `(10,100)` | 2 | 2 | true | 1 |
| `(18,180)` | 2,3 | 3 | true | 2 |
| `(26,260)` | 2,3,4 | 4 | true | 3 |

Final states are `E,E,O10,O18,O26,E,E,E`.

Wrap routes/finals are key 7: `7`/7; key 15: `7,0`/0; key 23:
`7,0,1`/1. Modulo by capacity keeps indexes 0 through 7, and the step loop
ends after eight attempts.

| Get | Route | Found | Value | Probes | Stop |
|---|---|:---:|---:|---:|---|
| 26 | 2,3,4 | true | 260 | 3 | matching occupied |
| 34 | 2,3,4,5 | false | 0 | 4 | empty 5 |

### C. Routes and unique keys

Removing 18 returns removed true, value 180, probes 2. Index 3 becomes
deleted with key/value zero; size 2, tombstones 1. Get 26 still returns found
true, value 260, probes 3 over `2,3,4`.

Putting `(26,999)` follows `2,3,4`, returns inserted false/probes 3, and
updates index 4. Size 2 and tombstones 1 remain. It must not commit at index 3
before checking for an existing key.

From the deleted state, putting `(34,340)` follows `2,3,4,5`, returns
inserted true/probes 4, and commits at remembered index 3. Final size 3,
tombstones 0.

### D. Maintenance and transaction

Assuming the selected insertion target is empty:

| Capacity | Size | Tombstones | Calculations | Action |
|---:|---:|---:|---|---|
| 8 | 2 | 3 | proposal 6; live 3 | none |
| 8 | 2 | 4 | proposal 7; live 3 | compact at 8 |
| 8 | 6 | 0 | proposal 7; live 7 | grow to 16 |
| 64 | 48 | 0 | proposal 49; live 49 | full |

An existing-key update is found before the new-key maintenance decision and
does not change occupancy.

For D2, put key 8 first inspects empty index 0, so public probe count is 1.
Compaction scans old indexes: key 10 goes to index 2; key 26 also has home 2
and goes to index 3. The requested key 8 goes to index 0. Final states:

```text
index0 O key8 value80
index1 E
index2 O key10 value100
index3 O key26 value260
indexes4 through7 E
size3, tombstones0, capacity8
```

Internal placements do not add to the public probe count.

At capacity 16: key 10 home/final 10; key 18 home/final 2; key 26 home 10
and final 11. Allocation failure preserves the old pointer identity,
capacity, size, tombstones, every slot byte/key/value/state, live-allocation
ownership, and caller result.

### E. Validation and errors

1. The stated valid count case is valid when the exact slot counts agree and
   probe routes are preserved; counts satisfy `3+1<=6`.
2. Capacity 12 is invalid.
3. Duplicate occupied key 26 is invalid.
4. Key 26 after empty on its home route is invalid/unreachable.
5. The canonical all-zero state is valid for `hash_table_validate`.

Error results:

1. valid table plus null get result: `HASH_TABLE_INVALID_ARGUMENT`; no result
   exists to change.
2. put on destroyed state: `HASH_TABLE_INVALID_STATE`; result unchanged.
3. missing get on active valid state: `HASH_TABLE_OK`; result becomes found
   false, value 0, actual probe count.
4. failed growth: `HASH_TABLE_ALLOCATION`; table and result unchanged.

A shallow copy duplicates the owner pointer, risking double release and
conflicting mutation. Transactional replacement keeps one valid owner until
the replacement is complete. Destroy releases the allocation and restores
`{NULL,0,0,0}` in pointer, size, tombstones, capacity order.

### F. Cost, selection, and security

Let `n` be live entries and `m` capacity. Requested-key probing is expected
`O(1)` with adequately distributed keys and the occupancy bound; worst case
is `O(m)`. It does not always simplify to `O(n)` because the table does not
shrink and may retain tombstones. Rehash scans `m` old slots and reinserts
`n`: expected `O(m)`, worst `O(m+n^2)`, hence bounded `O(m^2)`. At growth,
`m = Theta(n)`, giving expected `O(n)` and worst `O(n^2)`. Geometric growth
supports conditional expected amortized `O(1)` for an insertion-only growth
sequence. Repeated deletion/insertion compaction is not covered by that
stronger claim.

Good selection examples:

- direct array: dense bounded vertex IDs;
- open addressing: many exact unordered lookups with suitable distribution;
- AVL: ordered traversal, predecessor/successor, or range query plus
  logarithmic worst-case lookup;
- separate chaining: stable bucket references or a design accepting per-node
  allocation and avoiding open-addressed deletion markers.

Hash flooding means chosen collisions force unexpectedly long work and may
delay service. The bounded fixture demonstrates the mechanism, not actual
exhaustion or compromise. The hash/validator do not prove authenticity,
authorization, completeness, cryptographic collision resistance,
availability, or overall security.

### G. Exactly three tests

Credit categories only when assertions distinguish the claim:

1. both canonical collision families, physical indexes, exact successful and
   missing results/probes, validation, cleanup;
2. middle deletion, later-key lookup, beyond-tombstone update without
   duplicate, new-key reuse, exact counts;
3. seventh-key growth, four-removal compaction, forced maintenance allocation
   failure, exact pointer/slots/counts/result/live-allocation preservation,
   then destroy.

### H. Autopsy

The first wrong state is `slot->state = HASH_SLOT_EMPTY`. The next get 26
exposes it: faulty route `2,3`, found false, value 0, probes 2. Correct state
is deleted; route `2,3,4`, found true, value 260, probes 3. The smallest
regression inserts three same-home keys, removes the middle one, and retrieves
the last.

### I. Synthesis

Strong response: empty proves no insertion passed the point since rehash;
deleted preserves the possibility that a colliding key lies later. Select a
hash table for expected fast exact unordered lookup under adequate
distribution; select AVL when ordered/range work or logarithmic worst-case
lookup matters. A valid completion is “when keys distribute adequately and
occupancy is controlled; when many keys collide.”

## Evidence-template exact values

- initial capacity after successful init: 8;
- destroyed state: slots null, size 0, tombstones 0, capacity 0;
- canonical collision put probes: 1, 2, 3;
- get 26: true, 260, 3; get 34: false, 0, 4;
- wrap indexes: 7, 0, 1; probes 1, 2, 3;
- remove 18: true, 180, 2; index 3 deleted/0/0;
- update 26 after deletion: inserted false, probes 3;
- insert 34 after deletion: inserted true, probes 4, index 3;
- growth threshold at capacity 8: six nonempty states; seventh empty-target
  insertion grows or compacts;
- maximum capacity live boundary without tombstones: 48;
- all internal maintenance probes excluded from public result metrics.

## Rubric interpretation

Do not deduct for using the linear forms, correct prose instead of a spatial
drawing, instructor-CI evidence when local sanitizers are unavailable, or
different local variable names.

Do not award affected implementation-safety credit until unbounded probing,
delete-to-empty, duplicate creation, failed-operation mutation, premature
replacement commit, hidden test failure, or double ownership is repaired.
