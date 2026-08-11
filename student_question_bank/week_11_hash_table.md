# Week 11 — Hash Table: Vocabulary and Questions

[All-week vocabulary and question bank](../Data_Structures_Course_2026_Student_Question_Bank.md)

> **Required scope (14-week path; one submission):** Students implement capacity-bounded probing, exact lookup, insert/update, deletion, and tombstone reuse. They complete and test the maintenance-choice and commit checkpoints in an instructor-supplied transactional growth/compaction scaffold; they do not build every rebuild mechanism from scratch. Required student-authored tests cover collision and wraparound, tombstone-safe mutation and duplicate prevention, and scaffolded growth/compaction with one forced maintenance-allocation failure and state preservation. Additional capacity-policy, adversarial, deep-validator, and long-churn work is supplied or optional.

Extension questions below are enrichment only and do not enlarge the required Week 11 artifact.

## Vocabulary students will learn

| Term | Working meaning |
|---|---|
| Algorithmic-complexity denial of service | Valid attacker-chosen inputs force an operation to do far more work than intended. |
| Allocation | Storage reserved while the program runs. |
| Amortized cost | The total cost of occasional expensive operations spread across a sequence of operations. |
| AVL tree | An ordered, height-balanced search tree used here as a comparison for hash-table lookup. |
| Bucket | A possible starting location selected by the hash function; in this table, one array slot. |
| Capacity | The number of slots in the allocated table array. |
| Collision | Two different keys receive the same home slot. |
| Compaction | Rebuilding at the same capacity to remove tombstones. |
| Cryptographic hash | A hash designed for cryptographic properties; the course hash is not one. |
| Deleted slot | A formerly occupied slot that cannot terminate a probe through its cluster. |
| Dense internal graph ID | A validated consecutive identifier suitable for safe graph-array indexing. |
| Direct indexing | Using the key itself as an array index. |
| Effective occupancy | Live entries plus tombstones, including a proposed new entry when maintenance is considered. |
| Empty slot | A never-used-since-rehash slot that may end an unsuccessful lookup. |
| Exact lookup | Retrieving a value only when the requested key matches exactly. |
| Expected cost | Average behavior under stated distribution and load assumptions, not a per-operation guarantee. |
| Failure preservation | A failed operation leaves the earlier valid table and caller outputs unchanged. |
| Hash function | A repeatable computation mapping a key to a starting slot. |
| Hash flooding | Supplying many colliding keys to make table operations expensive. |
| Hash table | A key-to-value structure using a hash function and a collision rule. |
| Home slot | The first slot selected for a key. |
| Insert-or-update | Add a missing key or replace the value of an existing key without duplicating it. |
| Invariant | A rule that holds in every valid completed table state. |
| Key | The value used to identify and retrieve an entry. |
| Linear probing | After a collision, inspect consecutive slots and wrap at the array boundary. |
| Live entry | An occupied key/value pair currently stored in the table. |
| Load factor | Live-entry count divided by capacity. |
| Map | An abstract data type associating each unique key with one value. |
| Occupied slot | A slot currently holding one live key/value pair. |
| Open addressing | Storing all entries in the main slot array and resolving collisions by probing. |
| Probe | One inspection of a candidate slot. |
| Probe bound | The rule that one operation inspects no more than `capacity` slots. |
| Probe cluster | Occupied and deleted slots connected without an empty slot between them. |
| Rehash | Place every occupied entry into a fresh slot array using the new array's capacity. |
| Separate chaining | Resolve collisions with a collection, often a linked list, at each bucket. |
| Shallow copy | Copy an owning pointer without copying its allocation, creating conflicting apparent owners. |
| Slot | One position in the table's array. |
| Sparse key space | A key universe in which most possible values are absent. |
| Status | A named outcome returned by an operation. |
| Tombstone | The marker stored in a deleted slot so later colliding keys remain reachable. |
| Tombstone count | The number of deleted-slot markers currently in the table. |
| Transactional rebuild | Prepare a replacement table completely and commit it only after every fallible step succeeds. |
| `uint32_t` | C's unsigned integer type with exactly 32 bits. |
| Validator | A diagnostic operation that checks representation rules. |
| Value | Information associated with a key. |
| Worst-case cost | The greatest work allowed by the input and operation contract. |
| Wraparound | Continuing a probe at slot 0 after the final slot. |

### Optional-only vocabulary for extension questions

| Term | Working meaning |
|---|---|
| Keyed hash | A hash computation influenced by a secret key so outsiders cannot easily predict collision patterns. |
| Mixed-operation churn | A long sequence interleaving insertions, updates, removals, and rebuilds. |
| Resize thrashing | Repeated growth and shrinking caused by thresholds that are too close together. |
| Shrink policy | Rules deciding when a table may safely reduce its capacity. |

## Anticipated student questions

### Meaning and mental model

- What service does a key-to-value map provide independently of its storage representation?
- Why is direct array indexing wasteful when legal external keys are sparse and very large?
- What does a hash function contribute to lookup, and what does it not guarantee?
- What is a collision, and why can a correct hash table never assume collisions will not occur?
- How does linear probing search for another usable slot after a collision?

### Representation and invariants

- Why must each slot distinguish `EMPTY`, `OCCUPIED`, and `DELETED` states?
- How can key 0 remain legal when inactive slots contain zeroed key and value fields?
- What relationships must hold among `size`, `tombstones`, and `capacity`?
- Why must every occupied key be unique and reachable from its home slot without crossing an `EMPTY` slot?
- Which capacities are legal, and what does the canonical destroyed state look like?
- Why must every probe loop inspect at most `capacity` slots?

### Operations, C API, and ownership

- What is the difference between inserting a new key and updating an existing key in `hash_table_put`?
- Why must insertion remember the first tombstone but continue probing before committing there?
- How does `hash_table_remove` preserve the lookup reachability of later colliding keys?
- What table state and result output must be preserved if allocation or maintenance fails?
- Why is shallow copying a live `HashTable` prohibited, and what storage does `hash_table_destroy` release?

### Tracing

- At capacity 8, how do keys 10, 18, and 26 occupy their collision cluster?
- After removing key 18, which indexes must lookup for key 26 inspect, and which state appears at each?
- Which indexes must a missing-key lookup for 34 inspect before absence is established?
- Why must an update of key 26 continue past the tombstone instead of inserting a duplicate there?
- How can a new key 34 reuse the tombstone only after the search proves that 34 is not already present?
- How do keys with home slot 7 demonstrate wraparound from the last slot to index 0?

### Testing and debugging

- What exact-probe test covers both a collision cluster and wraparound?
- What test sequence proves tombstone-safe update, tombstone reuse, and duplicate prevention?
- How can a test force growth or same-capacity compaction and verify the selected maintenance action?
- What evidence proves that a forced maintenance-allocation failure preserves the old pointer, records, counts, and caller output?
- How would the full validator detect an unreachable occupied key, duplicate key, invalid state, or inconsistent count?

### Complexity

- Under which distribution and load assumptions do `get`, `put`, and `remove` have expected `O(1)` probe work?
- Why can one lookup require `O(m)` probes in a table of capacity `m`?
- What work and temporary space does a transactional rebuild require?
- Why does expected amortized `O(1)` growth not automatically describe arbitrary deletion/insertion churn with repeated compaction?

### Security and interpretation

- How can attacker-chosen colliding keys cause algorithmic-complexity denial of service?
- Why does increasing capacity alone not defeat deliberately chosen collisions under the teaching hash?
- Why is `key % capacity` neither a cryptographic hash nor an authentication mechanism?
- What validation must occur before an external label mapped by the table becomes a dense graph ID used for indexing?

### Assignment and evidence

- Which probing, lookup, insertion/update, removal, and scaffold checkpoints belong in the single Week 11 submission?
- What three student-authored test categories are required in the bounded Week 11 artifact?
- Which maximum-capacity, long-churn, deep-validator, and additional allocation-failure work is supplied or optional rather than a second assignment?
- What traces and tool output demonstrate collision, wraparound, tombstone, growth, compaction, and failure preservation?

### Transfer

- When is a hash table preferable to an AVL tree for exact lookup?
- When do ordered iteration, range queries, or worst-case lookup requirements favor an AVL tree instead?
- How can the hash table bridge sparse external identifiers to dense internal graph IDs?
- How do transactional rehashing and ArrayList growth share a commit-after-success principle?

### Extension questions

- How would separate chaining change collision storage, ownership, and worst-case traversal?
- What capacity policy could shrink a table without causing resize thrashing?
- How could a keyed production hash reduce predictable collision attacks?
- What proof or test strategy could strengthen confidence in long mixed-operation churn?

## Sources

- [14-week delivery guide](../Data_Structures_Course_2026_14_Week_Delivery_Guide.md#week-11--hash-table-within-180-minutes)
- [Master curriculum, Module 13](../Data_Structures_Course_2026_Spiral_Curriculum.md#module-13--supporting-adt-hash-table)
- [Module 13 package](../module_13_hash_table/README.md)
- [Module 13 vocabulary reference](../module_13_hash_table/student/vocabulary.md)
- [Consolidated Weeks 8–14 question bank](02_weeks_08_14_questions.md#week-11-hash-table-module-13)
