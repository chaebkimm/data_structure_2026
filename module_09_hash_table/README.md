# Module 09 — Hash Tables and Two Sum

Current pool contract: `new_lnode()` takes no arguments, returns an isolated index with retained data, and initializes the pool only on first use. `save_data` checks the index, writes data/next, then publishes the bucket head. Later `init_lnodes_pool()` calls are no-ops; `init_hashtable()` recycles owned bucket chains.


The required Week 9 lesson follows [student/lab.c](student/lab.c). It uses
ten bucket heads and the ten-node pool included from
[Module 07](../module_07_linked_list/student/lab.c). Collisions form linked
chains. Students trace the supplied functions and write a test driver;
there are no required implementation TODOs in the supplied lab.

The hash table uses the node-pool interface directly: `struct Linked_Node`,
`init_lnodes_pool()`, and `new_lnode()` followed by caller data/next assignments. Module 8's local queue adapters
`enqueue(value)` and `dequeue()` belong to FIFO use; hash chains retain and
recycle their own nodes rather than passing them through those wrappers.

## Teach the current source

| Material | Purpose |
| --- | --- |
| [Textbook](student/textbook.md) | Move from checking every pair to looking for a complement |
| [Representation reveal](student/representation_reveal.md) · [Vocabulary](student/vocabulary.md) | Explain buckets, chains, node indices, and stored data |
| [Investigation](student/investigation_worksheet.md) · [Linear version](student/investigation_worksheet_linear.md) | Preserve predictions and exact traces |
| [Lab](student/lab.md) | Build a driver around the actual source |
| [Evidence record](student/evidence_template.md) · [Rubric](student/rubric.md) | One Week 9 submission |
| [Models](diagrams/hash_table_models.md) | Bucket, node-pool, and two-sum diagrams with text equivalents |
| [Lesson plan](instructor/lesson_plan.md) · [Chapter guide](../instructor_guide/chapter_09.md) | Deliver the lesson in 180 minutes |
| [Release manifest](release/release_manifest.md) | Package the lesson with its Module 07 dependency |

## Source contract

- `hashtable[10]` contains node indices, initially `-1`. A bucket head is
  not a stored number. `-1` ends a chain.
- Call `init_lnodes_pool()` before the first allocation. The pool and hash table
  must have exclusive, consistent ownership of their nodes during a lab run.
- `hash_func(value)` normalizes `value % 10` to 0–9, including negative
  values. For example, 12, 22, and -8 all select bucket 2.
- `save_data(hash, data)` prepends a node and returns its pool index. It
  returns `-1` without changing the bucket when the pool is exhausted.
  Callers provide a bucket in 0–9. Duplicate data is allowed.
- `find_data(hash, data)` follows that bucket's chain and compares stored
  `data`. It returns the first matching node index, or `-1`.
- `free_lnode_chunk(head)` joins an entire valid chain to the free chain.
  `init_hashtable()` applies it to each nonempty bucket and clears the heads.
  These functions recycle pool slots; they do not call C `free()`.
- `two_sum_bf(target)` checks pairs in increasing `i`, then increasing
  `j < i`. It writes indices to `answer`, or `{-1,-1}` on a miss.
- `two_sum_ht(target)` resets the table, searches for `target - nums[i]`
  among earlier indices, then stores `i` under `hash_func(nums[i])`.
  The search compares `nums[j]`, because node data is an index in this use.
  Lookup before insertion prevents using the current index twice.
- Both algorithms use exactly ten numbers. Signed sums and differences
  must be representable as `int`. The supplied fixture satisfies this
  condition for the targets used in the lesson.
- A successful early return leaves chains allocated. The next
  `init_hashtable()` recycles them. Repeated `init_lnodes_pool()` calls do not reset live
  bucket chains or mix another user of the shared pool into the experiment.

For `nums = {-16,-8,-4,-2,-1,1,2,4,8,16}`, target 0 returns `[5,4]`.
Target 32 returns `[-1,-1]` after the hash version stores all ten indices.
With duplicate input values, the two implementations may return different
valid earlier indices; compare pair validity and existence, not exact pairs.

## Build and evidence

From the repository root:

```sh
make -C module_09_hash_table/code lab-compile core student-tests
```

The core tests include the actual `student/lab.c`. The student test file is
`code/tests/test_lab_student.c`; its initial smoke test is a starting point.
Write three original test groups: hashing and chains; pool exhaustion and
recycling; and two sum, including misses, repeated runs, and distinct indices.
Submit the driver, compiler/run output, traces, and corrected reasoning as
one artifact. See [the lab](student/lab.md) for direct compiler commands.

The include in `lab.c` is relative to the repository root. A driver needs
that root on its include path (`-I.` when compiling from the root). Compile
only the driver when it includes `lab.c`; do not separately compile either
included lab source.

## Costs and scope

Prepending is constant work once the bucket is known. A lookup traverses
one chain. With `n` stored items and `b` buckets, adequate distribution gives
expected `O(1 + n/b)` lookup; one chain can still contain all `n` items.
For a scalable version with controlled load, hash-based two sum has expected
`O(n)` work and worst `O(n²)` work. Brute force has worst `O(n²)` work.
The actual teaching arrays fix both bucket count and pool capacity at ten.
Resetting visits `b` heads and `r` live nodes, costing `Θ(b + r)`.

The older open-addressed map in `code/include`, `starter`, and `solution`
is an optional reference. Its probing, tombstones, dynamic allocations,
growth, validator, and deletion autopsy do not describe this lab and are
not Week 9 requirements. Its named build targets remain available in
[code/README.md](code/README.md).
