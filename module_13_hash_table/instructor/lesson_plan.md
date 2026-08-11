# Module 13 Instructor Lesson Plan - Sparse Indicator Hash Table

## 14-week delivery override - Week 11 (180 minutes)

This is the authoritative Week 11 sequence; see the
[14-week delivery guide](../../Data_Structures_Course_2026_14_Week_Delivery_Guide.md).
It produces one hash-table submission. Prepare a bounded scaffold that leaves
probe/lookup/put/remove for students while supplying most transactional
rehash allocation, reinsertion, rollback, and cleanup code.

| Required contact activity | Minutes |
|---|---:|
| Retrieve dense indexing and launch the sparse-key inquiry | 10 |
| Derive and trace bounded collision/wraparound probing | 15 |
| Diagnose deletion and establish tombstone behavior | 12 |
| Reveal map, load, compaction, growth, and transaction terms | 18 |
| Cognitive Pause and calibration | 10 |
| Complete the canonical trace and exit check | 15 |
| Retrieve contracts and read the supplied maintenance scaffold | 10 |
| Implement bounded probe and exact-key lookup | 20 |
| Implement put/update/remove and count preservation | 25 |
| Complete maintenance-choice and commit checkpoints | 15 |
| Author three bounded core tests | 15 |
| Run supplied extended allocation/max/validator suites and inspect the autopsy | 10 |
| Record cost/scope evidence and submit the one artifact | 5 |
| **Total** | **180** |

Beyond the one bounded forced failure in the third student test, additional
allocation-failure injection, maximum-capacity cases, deep-validator cases,
long churn, and the complete autopsy are supplied tests or optional resource
work. They must not be converted into a separate lab or extra homework. The
full-package sequence below is retained only for instructors who have time
outside the 14-week required path.

## Purpose

Students move from dense direct indexing to a sparse key-to-value index. They
construct collision and deletion rules before formal names, then implement
bounded probing, exact map mutation, and transactional maintenance in C.

Plan for exactly three contact hours across two portions of the Week 11
block. Preserve the five release gates and exact fixtures within that cap.

## Locked outcomes

By the end, each student must be able to:

1. distinguish map behavior, direct indexing, and hash-table representation;
2. trace `10,18,26` collisions and `7,15,23` wraparound exactly;
3. preserve lookup through deletion and prevent duplicate keys after a
   tombstone;
4. bound a probe by capacity and report exact inspected-slot counts;
5. select direct insertion, tombstone reuse, same-capacity compaction,
   doubling, or full;
6. explain transactional rehash and allocation-failure preservation;
7. implement probe/lookup/put/remove, finish the bounded transactional
   scaffold checkpoints, and author exactly three core test categories;
8. compare direct array, open addressing, AVL, and separate chaining; and
9. qualify expected cost and hash-flood security claims.

## Five-gate control

| Gate | Release | Evidence required before next gate |
|---|---|---|
| A | Informal inquiry only | Preserved sparse placement, same-start, wrap, removal, and scope reasoning |
| B | Representation reveal and pause | Responses under exactly three Target headings |
| C | One investigation form | Preserved Sections A through F |
| D | Textbook and exact-equivalent models | Labeled corrections plus one correct tombstone/maintenance trace |
| E | Bounded Week 11 lab | Core operations, scaffold checkpoints, three core tests, supplied-suite output, evidence, costs, and scope |

Instructor key, solution, and private tests remain closed.

## Preparation

1. Confirm Stage A standard/linear parity for keys, spot numbers, questions,
   and 40 points.
2. Confirm Stage A does not reveal hash table, hash function, collision, open
   addressing, linear probing, tombstone, load factor, rehash, complexity, or
   code.
3. Confirm the Cognitive Pause has exactly three `## Target` headings.
4. Run solution core, extension, sanitizer where supported, and autopsy
   targets.
5. Lock the canonical probe results:

   ```text
   10/18/26 puts: 1,2,3
   get26: true/260/3
   get34: false/0/4
   remove18: true/180/2
   get26 after: true/260/3
   update26: inserted false/probes3
   put34: inserted true/probes4/index3
   wrap 7/15/23: indexes7,0,1 and probes1,2,3
   ```

6. Confirm growth after six direct capacity-8 entries and compaction after
   the locked two-live/four-deleted state.
7. Confirm initialization and rebuild allocation failures preserve state and
   live-allocation counts.
8. Prepare optional eight index cards, three-state cards, and synthetic
   key/value cards. Manipulatives are optional, not required.
9. Accept drawing, tables, numbered prose, typing, dictation, tactile models,
   and verbal evidence.

## Optional full-package resource sequence - Meeting A

### 1. Retrieval from dense indexing - 8 minutes

Without formal hash vocabulary, retrieve a Module 9/12 idea: a graph with
dense vertex IDs can use `visited[id]` or `distance[id]` directly.

Ask:

> What changes if the accepted ID might be any unsigned 32-bit number but
> only twenty IDs are present?

Do not imply direct indexing is wrong. It is representation-sensitive.

### 2. Gate A sparse-row inquiry - 10 minutes

Release one Stage A form. Students preserve answers about direct positions
10, 18, and 26 and storage tied to a huge universe.

Then reveal only the ordinary-language rule: divide by eight and use the
remainder as starting spot. Do not name the formal computation.

Observe whether students:

- overwrite one record;
- assume different IDs cannot share a start;
- propose an unrepeatable free-spot choice; or
- identify that a second rule is needed.

### 3. Invent the next-spot rule - 15 minutes

Students place 10, 18, 26 and then fresh keys 7, 15, 23. Require every
inspected position, not only final positions.

Prompt for a stop bound:

> If every spot has some earlier history, how many spots may this eight-spot
> search inspect before it must stop?

Preserve the first conjecture. The target is eight, even when an ordinary
example stops sooner.

### 4. Removal conjecture - 10 minutes

Remove 18 from the middle of `10,18,26`. Partners choose never-used appearance
or a crossed-out marker, then trace a search for 26.

Do not name the formal states yet. Ask what evidence a never-used position
supplies and what history would be lost by pretending the position had never
been used.

### 5. Gate B formal reveal - 20 minutes

Release `representation_reveal.md`. Define in this order:

1. map, key, value, insert, update, get, remove;
2. hash table, hash function, home slot, bucket;
3. collision, open addressing, linear probing, wraparound;
4. empty, occupied, deleted/tombstone;
5. load factor and effective occupancy;
6. compaction, growth, rehash, transaction; and
7. expected versus worst cost and non-cryptographic scope.

Trace the canonical cluster and removal. Demonstrate why put must remember a
deleted slot but continue looking for an existing key.

### 6. Exactly-three-target Cognitive Pause - 5 minutes

Read the starting rules aloud. Notes, slides, classmates, vocabulary, and
coding tools remain closed. Extended time uses the same exact targets.

The only Target headings are:

1. present and missing lookup;
2. delete, continue, and update once; and
3. select maintenance and limit the promise.

### 7. Pause calibration - 12 minutes

Display exact evidence:

```text
T1 get26 2,3,4 -> true/260/3
T1 get34 2,3,4,5 -> false/0/4
T2 remove18 2,3 -> D at3, size2, tomb1
T2 get26 and update26 both 2,3,4
T3 2 live + 4 D -> compact8; 6 live + 0 D -> grow16
```

Students label corrections `stop`, `tombstone`, `unique key`,
`maintenance`, `cost`, or `scope`.

### 8. Gate C start and exit ticket - 10 minutes

Release one investigation form. Complete only the first home calculation.
Students begin Sections A and B.

Exit prompt:

> Why can empty stop a search while deleted cannot?

Expected: empty proves no placement passed it since rehash; deleted preserves
the possibility that a colliding key lies later.

## Optional full-package resource sequence - Between meetings

Students preserve worksheet Sections A through F. Release Stage D only
afterward. Corrections are added beside earlier responses.

Require standard/linear parity, not spatial drawing. The exact compaction
fixture uses an empty selected target; deleted-target reuse does not increase
effective occupancy.

## Optional full-package resource sequence - Meeting B

### 1. Gate D textbook/model calibration - 10 minutes

Retrieve without code:

1. three slot states and stop meanings;
2. capacity-bounded index formula;
3. first-deleted memory plus continued duplicate search;
4. capacity-8 nonempty-state limit 6;
5. compaction versus growth; and
6. public probes versus internal maintenance work.

Open the textbook and exact-equivalent diagrams. Gate D closes after one
correct delete/update trace and one maintenance selection.

### 2. Gate E public contract - 10 minutes

Students locate:

```text
HashSlotState, HashSlot, HashTable
HashTablePutResult, HashTableGetResult, HashTableRemoveResult
hash_table_init, validate, put, get, remove, destroy
```

Establish precedence:

```text
null argument -> constant-time active shape -> bounded probe -> operation
```

A successful miss changes its result to false/value0/probes. A non-`OK`
status preserves the entire result.

### 3. TODO 1 bounded probe helper - 20 minutes

Students implement one capacity-bounded loop. Pause after these cases:

- matching occupied at home;
- occupied different then empty;
- deleted before matching key;
- deleted before empty;
- wrap from 7 to 0; and
- capacity attempts with no empty.

Require exact count increment at inspection, not on movement or arithmetic.
Unknown state returns an invalid probe result.

### 4. TODO 2 mutation helpers - 25 minutes

Implement update first, then direct insert/deleted reuse, maintenance
selection, and removal.

Ask after each branch:

- Does size change?
- Does tombstones change?
- Can allocation still fail?
- Has output been published too early?

Checkpoint the canonical deletion/update/reuse sequence. Do not permit
immediate insertion at the first deleted slot before duplicate search.

### 5. TODO 3 transactional rebuild - 20 minutes

Students allocate a fresh array, raw-insert occupied old records in index
order, add the requested entry, then commit and release old storage.

Test initialization allocation failure first, then replacement failure. The
old pointer, fields, slots, result, and live-allocation count must match the
snapshot after a failed rebuild.

State explicitly: do not use `realloc`, do not copy deleted markers, and do
not call the full validator inside maintenance.

### 6. Exactly three student tests - 15 minutes

Require the locked categories:

1. collision plus wraparound and exact probes;
2. tombstone reachability, update, reuse, and no duplicate; and
3. growth, compaction, forced maintenance-allocation failure, exact
   table/result/ownership preservation, and destroy.

Students state one claim before assertions. The third student test uses the
published testing hook for replacement-allocation failure. Supplied tests own
initialization failure, capacity-64/full, key-boundary, and deliberately
malformed-state breadth.

### 7. Bounded delete-to-empty autopsy - 8 minutes

Students predict first. Run only the documented safe target.

```text
correct get26: 2,3,4 -> true/260/3
faulty get26:  2,3   -> false/0/2
```

The state assignment is the first divergence. All accesses remain in range;
the defect is logical, not memory corruption.

### 8. Cost, selection, and scope - 7 minutes

Close with:

- conditional expected constant probes versus worst `O(m)` routes in capacity
  `m`;
- rebuild scan/reinsertion cost: expected `O(m)`, worst `O(m+n^2)`, and why
  no-shrink compaction does not always reduce to live-entry `n`;
- direct array for dense keys;
- AVL for ordered/range work and logarithmic worst-case lookup;
- separate chaining's per-bucket collections; and
- transparent teaching hash/validator as neither cryptography nor
  authentication.

## Common misconceptions and responses

### “Different keys should always get different homes.”

A smaller array cannot give every possible `uint32_t` key a unique position.
Retrieve the pigeonhole idea in ordinary language and require a collision
rule.

### “Deleted is just empty.”

Trace get 26 after removing 18. Empty changes the stopping evidence; deleted
preserves the route.

### “Use the first tombstone immediately.”

Ask where an existing same key could be. Trace update 26 past deleted index 3.

### “Key zero can mean empty.”

State is separate. Core tests store key 0 with a nonzero or negative value.

### “Modulo wraparound can probe forever.”

Modulo keeps indexes in range; the independent `step < capacity` bound ends
the search.

### “Always double when the threshold is crossed.”

If deleted states caused effective occupancy, same-capacity compaction
recovers them without more long-term storage.

### “Rehash means copy the array.”

Capacity changes home indexes, and tombstones must disappear. Reinsert
occupied entries.

### “Publish the result before allocation.”

A later failure would violate output preservation. Prepare locally and
publish after commit.

### “Validation makes every operation safe and constant.”

The full validator is a separate, potentially quadratic diagnostic. Ordinary
operations use shallow shape checks plus the bounded requested route.

### “Hash tables are always O(1).”

Require the words expected, distribution assumption, occupancy bound, and
linear worst-case collision route.

### “Hash means cryptographic.”

The course remainder function organizes storage. It supplies none of the
authentication or cryptographic claims associated with other uses of hashes.

## Accessibility and equivalent evidence

- Offer standard and linear inquiry/investigation forms with identical
  values, questions, and points.
- Read slot states as words, not color. Never rely on color alone.
- Permit `E/O/D`, full words, tables, numbered lists, tactile cards, typing,
  dictation, or verbal tracing.
- Caption demonstrations and provide commands and output as text.
- Grade route, state, invariant, and evidence rather than drawing quality,
  handwriting, arithmetic speed, or public speaking.
- Use the hint ladder: state the home; label current state; identify legal
  stop; apply one next step; check capacity bound.

## Safety controls

- Use only synthetic indicator IDs and values.
- Keep intentionally faulty code isolated from ordinary targets.
- Bound every probe and internal placement by capacity.
- Use warning-enabled builds and sanitizers where supported.
- Preserve allocation/result state on failures.
- Never create two owning shallow copies for malformed tests.
- Restore a malformed fixture before destruction if its pointer/shape was
  deliberately changed.
- Do not describe a logical miss as proof of compromise or data falsity.

## Assessment checkpoints

- Stage A: serious preserved reasoning and later correction, not initial
  correctness.
- Pause: exactly three target responses.
- Stage C: exact traces, maintenance decisions, invariant/cost/scope.
- Week 11: one artifact containing core operations, bounded maintenance
  scaffold checkpoints, three original core tests, supplied-suite output,
  traces, cost, scope, and synthesis.
- Allocation/max/validator stress work and the complete autopsy remain
  supplied or optional; they are not additional submissions.
- Revision: one feedback-driven repair is permitted under the course policy.

## Forward bridge

Module 14 retrieves linked-node ownership and contrasts separate chaining
while building Union-Find. Module 15 contrasts expected hash lookup with AVL
ordered lookup and logarithmic worst-case search. Module 16 uses structure
selection and bounded failure reasoning during MST integration.
