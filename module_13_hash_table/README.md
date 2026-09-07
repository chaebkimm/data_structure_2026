# Module 13 Teaching Package

## Sparse Indicator Index with a Hash Table

## 14-week delivery role - Week 11

This is the required Week 11 hash-table unit and produces **one submission**.
Follow the [14-week delivery guide](../Data_Structures_Course_2026_14_Week_Delivery_Guide.md).
The 180-minute path keeps bounded probing, lookup, insertion/update, and
removal as the student-written core. Transactional same-capacity compaction
and growth are supplied as a nearly complete scaffold: students finish the
maintenance decision and commit checkpoints, then test preservation rather
than writing the rebuild from scratch.

Students author exactly the three categories already named in
`code/tests/test_student.c`: collision/wraparound with exact probes;
tombstone-safe update, reuse, and duplicate prevention; and scaffolded
growth/compaction with one forced maintenance-allocation failure and state
preservation. Missing/key-zero behavior, additional allocation failures,
maximum-capacity, deep-validator, and long-churn suites are supplied. The complete
Stage E archive remains a resource package; its extra tests and autopsy do
not become another assignment.

This package is an associative-index bridge after Dijkstra and before the
final Linear -> Tree -> Graph spiral in **Data Structures Course 2026**. It
returns to array indexing and dynamic growth, then asks what changes when
keys are sparse, collisions are unavoidable, and a caller needs exact-key
lookup rather than sorted order.

## Beginner-first rule

Students are not expected to know map vocabulary, hash functions, collision
resolution, open addressing, linear probing, load factor, tombstones,
rehashing, or hash-flooding before this module. Every student-facing term and
symbol is explained in ordinary language when first needed. Assessment
rewards correct traces, explicit invariants, safe implementation, and
reproducible evidence, not memorized wording, arithmetic speed, or drawing
quality.

## Module question

> When indicator IDs are sparse and provide no search direction, how can we
> find a stored record without scanning every record -- and what can
> collisions make that promise cost?

## Core learning targets

Students will be able to:

1. distinguish key-to-value map behavior from one particular storage form;
2. explain why direct indexing is wasteful for a large sparse key universe;
3. calculate a home slot using the course teaching hash;
4. trace linear probing with collisions and wraparound;
5. distinguish `EMPTY`, `OCCUPIED`, and `DELETED` slot states;
6. preserve lookup reachability after deletion;
7. insert a new key and update an existing key without creating a duplicate;
8. bound every probe sequence by the table capacity;
9. decide when an insertion requires growth or same-capacity compaction;
10. rehash occupied entries transactionally and preserve the old table if
    allocation fails;
11. validate counts, unique keys, slot states, and probe reachability;
12. test ordinary, collision, wraparound, deletion, growth, full, malformed,
    and allocation-failure cases; and
13. state expected and worst-case costs without treating a teaching hash as
    a cryptographic or security guarantee.

A **map** associates each unique key with one value. This module maps a
`uint32_t` synthetic indicator key to an `int` value. A **hash function**
converts a key into a starting position. The deliberately transparent course
function is:

```text
home = key % capacity
```

It exists so every student can reproduce the exact traces. It is not a
production recommendation and is not a cryptographic hash.

## Fixed table contract

- Keys are `uint32_t`; values are `int`. Every `uint32_t` key, including 0
  and `UINT32_MAX`, is legal because slot state is stored separately.
- A table slot is exactly one of `HASH_SLOT_EMPTY`,
  `HASH_SLOT_OCCUPIED`, or `HASH_SLOT_DELETED`.
- Empty and deleted slots have key 0 and value 0. Occupied key 0 remains
  legal because state, not a key sentinel, marks activity.
- The canonical destroyed state has a null slot pointer, size 0, capacity 0,
  and tombstone count 0. `hash_table_init` accepts only that state and
  allocates eight empty slots.
- A positive capacity is exactly 8, 16, 32, or 64. Positive capacity owns
  one allocation containing that many slots.
- `size` counts occupied slots. `tombstones` counts deleted slots. Therefore
  `size + tombstones <= capacity`.
- Every occupied key is unique.
- The home slot is `key % capacity`. A probe examines home, then the next
  slot, wrapping from `capacity - 1` to 0.
- Every search examines at most `capacity` slots. It stops unsuccessfully at
  the first `EMPTY` slot or after `capacity` inspections. It does not stop at
  `DELETED`.
- A new insertion may remember the first deleted slot, but continues until
  it finds the key, an empty slot, or completes the bounded probe. This
  prevents a duplicate key after a tombstone.
- Updating an existing key changes only its value and operation metric. It
  does not change size, capacity, or tombstone count and does not trigger
  maintenance.
- Removing a present key clears its key/value fields, changes its state from
  `OCCUPIED` to `DELETED`, decreases size once, and increases tombstones
  once. Removing a missing key reports that result without changing logical
  table state.
- After searching for a distinct key, calculate proposed effective
  occupancy. If the selected insertion slot is empty, it is:

  ```text
  size + tombstones + 1
  ```

  Maintenance is required when this value exceeds three quarters of the
  current capacity. Reusing a deleted slot increments size and decrements
  tombstones, so effective occupancy does not increase and maintenance is
  not required for that reuse.
- When maintenance is required and `size + 1` still fits within three
  quarters of the current capacity, rehash into a fresh table of the same
  capacity. This is **compaction**: deleted slots disappear.
- Otherwise grow to the next capacity and rehash. A distinct insertion that
  would require growth beyond capacity 64 returns `HASH_TABLE_FULL` and
  preserves the table. Existing-key updates remain permitted.
- Rehashing copies only occupied key/value pairs. It never copies a deleted
  marker as a live record.
- Allocation and rehash are transactional: completely build a replacement
  allocation using bounded internal placements, then commit it. This does
  not call the full public validator during ordinary maintenance. Allocation
  failure preserves the old pointer, all records, every count, and caller
  outputs.
- Ordinary operations perform only constant-time active-shape checks. The
  explicit full validator performs the deeper uniqueness and reachability
  diagnosis.
- Public result structs are published only on `HASH_TABLE_OK`. A successful
  missing `get` reports `found == false`, value 0, and its actual probe count;
  a successful missing remove analogously reports `removed == false`, value
  0, and its probe count. Any non-`OK` status preserves the entire caller
  result struct.
- The full validator is an explicit diagnostic. It is not hidden inside the
  advertised expected cost of ordinary operations.
- Shallow copying a live table is prohibited because two structures would
  appear to own the same slot allocation.

## Canonical collision trace

At capacity 8, keys 10, 18, and 26 all have home slot 2:

```text
index       0  1  2   3   4   5  6  7
state       E  E  O   O   O   E  E  E
key               10  18  26
```

Removing key 18 produces a tombstone at index 3:

```text
index       0  1  2   3   4   5  6  7
state       E  E  O   D   O   E  E  E
key               10      26
```

Lookup for 26 must inspect indexes 2, 3, and 4. Lookup for missing key 34
must inspect 2, 3, 4, and 5 before the empty slot proves absence.

An update of key 26 must continue past the tombstone and update index 4. A
new key 34 may remember index 3, continue through index 5 to establish that
34 is not already present, and then reuse index 3.

## Canonical wraparound trace

At capacity 8, keys 7, 15, and 23 all have home slot 7:

```text
index       0   1   2  3  4  5  6  7
state       O   O   E  E  E  E  E  O
key         15  23                 7
```

The trace examines 7, then wraps to 0 and 1. Slot arithmetic must remain in
range at every step.

## Full-package TODO inventory

1. Complete the bounded probe helper and exact-key lookup, including
   wraparound, empty-stop, tombstone continuation, output-last behavior, and
   the capacity stop.
2. Complete insertion, update, and removal, including first-tombstone
   memory, duplicate prevention, exact count changes, and failure
   preservation.
3. Complete transactional maintenance: select same-capacity compaction or
   growth, allocate a fresh slot array, reinsert only occupied entries, and
   commit only after success.

In the 14-week path, students complete clusters 1 and 2. For cluster 3, the
instructor supplies allocation, reinsertion, rollback, and cleanup code;
students complete the bounded maintenance-choice and commit checkpoints and
verify them with the supplied preservation tests. Students author exactly
three bounded core test categories in `code/tests/test_student.c`; allocation,
maximum-capacity, full-validator, and churn coverage is supplied.

## Safe deletion autopsy

The isolated faulty program changes a removed occupied slot directly to
`EMPTY`. All memory accesses remain in bounds, but the early empty marker
makes a later colliding key appear absent. The ordinary autopsy target runs a
bounded logical demonstration; it is not linked into normal tests and does
not intentionally perform invalid memory access.

## Package map

```text
module_13_hash_table/
|-- README.md
|-- diagrams/
|   `-- hash_table_models.md
|-- instructor/
|   |-- answer_key.md
|   |-- lesson_plan.md
|   `-- technical_notes.md
|-- student/
|   |-- cognitive_pause.md
|   |-- evidence_template.md
|   |-- hash_table_autopsy.md
|   |-- inquiry_prompt.md
|   |-- inquiry_prompt_linear.md
|   |-- investigation_worksheet.md
|   |-- investigation_worksheet_linear.md
|   |-- lab.md
|   |-- representation_reveal.md
|   |-- rubric.md
|   |-- textbook.md
|   `-- vocabulary.md
|-- release/
|   |-- prepare_student_release.ps1
|   |-- release_manifest.md
|   |-- stage_a_README.md ... stage_e_README.md
|   |-- student_build.ps1
|   |-- student_code_README.md
|   `-- student_Makefile
|-- dist/
|   `-- module_13_stage_a_*.zip ... module_13_stage_e_*.zip
`-- code/
    |-- README.md
    |-- build.ps1
    |-- Makefile
    |-- include/hash_table.h
    |-- starter/hash_table.c
    |-- solution/hash_table.c
    |-- tests/
    |   |-- test_core.c
    |   |-- test_extension.c
    |   `-- test_student.c
    `-- autopsy/
        |-- README.md
        `-- faulty_delete_empty.c
```

The source package contains exactly 38 files before the five generated
archives: 26 Markdown files, 3 PowerShell files, 2 Makefiles, 6 C files, and
1 header.

## Recommended release order

1. Run the release preparation script only after all materials and tests
   pass.
2. Release Stage A before Meeting A. It withholds formal structure names,
   slot-state names, formulas, code, and completed reasoning.
3. Release Stage B after each student preserves the initial placement model.
4. Release Stage C after the exactly-three-target Cognitive Pause and
   instructor comparison.
5. Release Stage D only after the student preserves Sections A through F of
   Stage C.
6. Release Stage E after retrieval and Stage D calibration in Meeting B.
7. Keep instructor materials, solution code, and extension tests closed
   until revisions finish.

## Week 11 submission

Students submit:

- completed bounded probe/lookup/put/remove work in
  `code/starter/hash_table.c`;
- completed maintenance-choice and commit checkpoints in the supplied
  transactional rebuild scaffold;
- completed `code/tests/test_student.c` with three bounded core tests;
- saved warning-enabled core and student-test output;
- collision, wraparound, tombstone, compaction, and growth traces;
- supplied validator and failure-preservation suite output;
- the completed evidence record;
- a direct-array, AVL, and separate-chaining comparison; and
- a precise expected-cost and security-boundary explanation.

The allocation-failure, maximum-capacity, validator, long-churn, and autopsy
work remains supplied or optional and is not a second submission.

## Cost and security boundary

Let `n` be the number of live entries and `m` the capacity.

- Under an adequately distributed hash and controlled load, `get`, `put`,
  and `remove` have expected `O(1)` probe work.
- A collision cluster may force one requested-key probe to inspect `O(m)`
  slots. Because this implementation does not shrink and may retain
  tombstones, that bound does not always simplify to `O(n)`.
- Rehash scans `m` old slots and reinserts `n` live entries. It is expected
  `O(m)` under expected-constant internal placement, worst
  `O(m + n^2)`, and therefore bounded by `O(m^2)`. At a growth event,
  `m = Theta(n)`, so those bounds simplify to expected `O(n)` and worst
  `O(n^2)`. Rebuild uses fresh `O(m)` temporary space.
- Geometric growth spreads growth-rehash work across an insertion-only
  sequence, giving expected amortized `O(1)` there under the stated hashing
  assumptions. Mixed deletion/insertion churn may trigger repeated
  same-capacity compactions, so that stronger amortized claim does not cover
  every mixed sequence.
- The teaching validator may use `O(m^2)` work to check uniqueness and probe
  reachability. Its diagnostic work is separate from ordinary operations.

Attacker-chosen colliding keys can cause **hash-flood
algorithmic-complexity denial of service** when the added work materially
delays intended service. The locked fixture demonstrates the mechanism at a
safe bounded scale. Capacity growth alone does not fix chosen collisions.
The course hash does not authenticate records, hide keys, resist
cryptographic collision search, prove authorization, or establish overall
system security.

## Relationship to the course spiral

- **Revisits:** Module 1 contiguous storage and bounds, Module 4 failure
  preservation, growable-array maintenance from Modules 10–11, direct indexing
  in graph representations, exact lookup, invariants, and bounded loops.
- **Contrasts:** direct indexing uses key-sized address space; a linked list
  scans; separate chaining stores collision groups in linked nodes; an AVL
  tree supplies sorted order and worst-case logarithmic search; this table
  supplies expected constant-time exact lookup under stated assumptions.
- **Introduces:** hashing, collision resolution, open addressing, linear
  probing, tombstones, effective occupancy, compaction, transactional
  rehashing, and hash-flood analysis.
- **Forwards:** Module 14 retrieves linked nodes and introduces Union-Find;
  Module 15 provides the formal AVL comparison; Module 16 integrates the
  course structures in minimum-spanning-tree work.
