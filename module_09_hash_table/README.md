# Module 09 — Storing and Finding Data with a Hash Table

The required Chapter 9 lesson follows [student/lab.c](student/lab.c).
The source is self-contained: ten hash nodes, fifteen bucket heads, and two
ways to find different input positions whose values sum to a target. Teach
array search and direct addressing first, then hash functions, collision
chains, and table operations. Introduce two sum after students can insert
and find keys. Students trace the supplied functions and write an assertion driver. There
are no required implementation TODOs.

## PPT references and current source

Use [the concept material](student/ppt_material.md) for the sequence from
array search and direct addressing to hashing, collisions, and two sum.
Use [the code material](student/ppt_lab_material.md) for key/data/next nodes,
head insertion, key lookup, and lookup before insertion. The accompanying
[prompt slides](student/ppt.md) and [code prompts](student/ppt_lab.md) support
retrieval during class. All PPT files remain user-maintained references.

The PPT code illustrates five nodes, seven buckets, a positive-only array,
and names such as `size`, `htable`, `arr`, and `ans`. The current lab uses
`NODES_CAPACITY=10`, `TABLE_CAPACITY=15`, `hnodes_unused`, `hashtable`,
`nums`, and `answer`. Its brute-force inner loop visits earlier indices in
**descending** order, and its hash version checks insertion failure. Use
current lab parameters and control flow for all required traces and tests.
Direct addressing, open addressing, and Robin Hood hashing are conceptual
comparisons; this implementation uses separate chaining.

## Teach the current source

| Material | Purpose |
| --- | --- |
| [Textbook](student/textbook.md) · [Korean](student/textbook_korean.md) | Move from array search and direct addressing to hashing; apply it to two sum |
| [Representation reveal](student/representation_reveal.md) · [Vocabulary](student/vocabulary.md) | Distinguish keys, data, buckets, and node indices |
| [Investigation](student/investigation_worksheet.md) · [Linear version](student/investigation_worksheet_linear.md) | Preserve predictions and exact traces |
| [Lab](student/lab.md) | Build a driver around the actual source |
| [Evidence record](student/evidence_template.md) · [Rubric](student/rubric.md) | One Chapter 9 submission |
| [Models](diagrams/hash_table_models.md) | Text diagrams of chains, reset, and two sum |
| [Lesson plan](instructor/lesson_plan.md) · [Chapter guide](../instructor_guide/chapter_09.md) | Deliver the lesson in 180 minutes |
| [Release manifest](release/release_manifest.md) | Package the self-contained lesson |

## Source contract

- Call `initialize()` before manual table operations. Static bucket heads
  start at zero; that is not the empty marker. Initialization writes `-1`
  to all fifteen heads and resets `hnodes_unused` to zero.
- `struct hnode` contains `key`, `data`, and `next`. `hnodes[10]` stores the
  nodes. `hnodes_unused` is the next unused index, also the allocated count.
- `new_hnode(key,data,next)` returns a node index or `-1` when all ten slots
  have been allocated. It does not publish a bucket head.
- `hash_func(key)` normalizes `key % TABLE_CAPACITY` into 0–14. Keys 12,
  27, and -3 all select bucket 12.
- `insert(k,d)` prepends a node to the selected chain and returns **0** on
  success, **-1** on exhaustion. A failed insertion leaves state unchanged.
  Duplicate keys allocate another node; they do not update an old node.
- `find(k)` compares `hnodes[node].key` and returns the newest matching
  node index, or `-1`. Retrieve its associated data only after checking the
  returned index.
- `initialize()` discards all active chains by resetting heads and the
  allocation counter. It does not traverse chains, clear node fields, or
  change `nums` or `answer`. The next allocation uses node 0 again.
- `two_sum_bf(target)` visits increasing `i`, then `j=i-1` down to zero.
  It stores `{j,i}` in `answer`, or `{-1,-1}` on a miss.
- `two_sum_ht(target)` initializes at entry, looks up the complement key,
  reads the earlier input index from the returned node's `data`, and stores
  `{j,i}`. Only after a lookup miss does it insert `(nums[i],i)`.

With the supplied array, targets 0, 2, and 3 return `{4,5}`, `{3,7}`, and
`{5,6}` in both methods. Target 100 returns `{-1,-1}`. Both methods choose
the most recent matching earlier position, including on duplicate input
values. Keep all tested sums and complement subtractions representable as
C `int`; the supplied functions do not check signed overflow.

## Build and evidence

From the repository root:

```sh
make -C module_09_hash_table/code lab-compile core student-tests
```

The core tests include the actual source. Students extend
`code/tests/test_lab_student.c` with three original groups: hashing and
chains; capacity and reset; and two sum with misses, duplicates, repeated
calls, and distinct indices. See [the lab](student/lab.md) for a standalone
driver command. Compile a driver that includes `lab.c` once; do not also
compile `lab.c` as another translation unit. No Module 07 include or shared
node pool is needed.

## Costs and scope

Initialization visits fifteen heads: generalized cost `Θ(b)` for `b`
buckets. Allocation and head insertion take constant work. Lookup visits
one chain; under adequate distribution its expected cost is `O(1+n/b)`
for `n` entries. With `b=Θ(n)` and enough node capacity, complete hash-based
two sum has expected `O(n)` work including initialization, and worst
`O(n²)` work when chains grow. A brute-force miss checks 45 pairs here;
target 0 succeeds after 11 pair comparisons. The hash target-0 trace makes
one stored-key comparison. These are observations for the supplied input.
The actual arrays reserve ten nodes and fifteen heads and never grow.

The older open-addressed map in `code/include`, `starter`, and `solution`
is an optional comparison. Its probing, tombstones, dynamic allocations,
growth, validator, and deletion autopsy are not required lab operations.
See [code/README.md](code/README.md) for its named build targets.
