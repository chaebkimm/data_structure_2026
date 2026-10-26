# Module 09 Lesson Plan — Chained Hashing and Two Sum

## Source and learning goals

The required lesson follows [student/lab.c](../student/lab.c). It includes
Module 07's [node-pool implementation](../../module_07_linked_list/student/lab.c).
Students trace supplied operations and write a separate assertion driver.
There are no required hash-table implementation TODOs.

By the end, students should calculate a bucket for positive and negative
integers, follow a collision chain, distinguish bucket/node/input indices,
explain pool exhaustion and recycling, and justify searching before storing
in two sum. They should compare concrete work before making conditional
expected-cost claims.

## Prerequisite retrieval

Retrieve array positions, `%`, integer `next` links, `-1`, `free_head`, and
`new_lnode(data,next)` from Module 07. Module 08 supplied practice following
indices while preserving the meaning of stored data. The hash table needs
those ideas, not dynamic allocation or a new queue lesson.

Inspect the actual imported names: `lnodes`, `init_lnodes_pool`, and
`new_lnode`. Earlier material may use different names. Do not substitute
those names in code examples.

## Delivery within 180 minutes

| Minutes | Work | Evidence retained |
| --- | --- | --- |
| 0–15 | Stage A: find two different positions whose values reach a target; count the nested-loop comparisons | Initial method and stopping rule |
| 15–35 | Stage B: reveal ten bucket heads and Module 07's linked-node pool; normalize negative remainders | Three Cognitive Pause predictions |
| 35–65 | Stage C: hand-trace insertion and lookup with `12,22,-8`; test duplicate payloads | Bucket heads, nodes, free chain, visited nodes |
| 65–85 | Trace pool exhaustion, unchanged failed insertion, and whole-table recycling | Before/after state and ownership explanation |
| 85–95 | Break and short retrieval | Explain bucket index versus node index |
| 95–120 | Stage D: compare `two_sum_bf` and `two_sum_ht`; trace target 0 and a miss at 100 | Input-index/value/node table and answers |
| 120–160 | Stage E: build the supplied source through a separate driver; complete three original test groups | Commands, assertions, compiler output |
| 160–175 | Compare evidence; correct pause answers and explain expected/worst work | Visible corrections and cost conditions |
| 175–180 | Submit the single Week 9 evidence package | Driver and evidence record |

Keep the release sequence A → B → C → D → E. Preserve each initial response
before giving the corresponding explanation. Accept linear or spatial
traces. The linear worksheet has the same questions and evidence burden.

## Board sequence

Begin with the two-sum problem. For the supplied ten values, the nested loop
tries only earlier indices `j<i`. A miss makes 45 comparisons. Ask how a
new value could find a needed earlier value without scanning all earlier
positions every time.

Show ten bucket heads, all `-1`, and a separate ten-node pool. Calculate
`hash_func(12)=2`, `hash_func(22)=2`, and `hash_func(-8)=2`. Save those
payloads in that order after a fresh `init_lnodes_pool()` and empty bucket heads.
The final bucket 2 head is node 2. Its chain is `2→1→0→-1`, with data
`-8,22,12`. Insertion puts a node at the front; it does not seek an empty
neighboring bucket.

Trace `find_data(2,12)` through nodes `2,1,0`. Trace absent 32 through the
same three nodes and then `-1`. Save another 22. Node 3 becomes the head;
`find_data(2,22)` now returns 3. This routine allows repeated payloads.
It does not implement a unique-key update contract.

Then separate the three meanings of an index:

| Expression | Meaning |
| --- | --- |
| `hash_func(nums[i])` | Bucket selected by the input value |
| `hashtable[bucket]` | First linked-node index, or `-1` |
| `lnodes[node].data` in two sum | Earlier input index `j` |
| `nums[j]` | Earlier input value to compare with the complement |

For target 0, the first successful outer iteration is `i=5`, value 1.
The complement is -1. Bucket 9 selects node 4, whose payload is input index
4. `nums[4] == -1`, so `answer` becomes `{5,4}`. Index 5 has not been
saved. The five earlier nodes remain allocated after this early return.

For target 100, all ten iterations miss. Both implementations report
`{-1,-1}`. The hash version has saved all ten input indices and the pool
has no free nodes. No pair of supplied values reaches 100. A later
call to `two_sum_ht` begins by recycling the old bucket chains.

## Driver and test coaching

Call `init_lnodes_pool()` before the first hash-table use in a process. Static
`free_head` begins at -1. Empty bucket heads alone do not initialize the
pool. Do not call `init_lnodes_pool()` while bucket chains still own nodes.
After a run, use `init_hashtable()` to return bucket-owned chains to the
existing pool. A list or linked queue using Module 07's pool must not claim the same nodes.

A driver beside `student/lab.c` can include `"lab.c"` and define
`int main(void)`. Compile the driver alone from the repository root:

```sh
cc -std=c11 -Wall -Wextra -Wpedantic -I. \
  module_09_hash_table/student/lab_driver.c -o /tmp/module09_lab_driver
/tmp/module09_lab_driver
```

The root include path is necessary because Module 09 includes Module 07 by
its repository-relative path. Do not compile either included `.c` file as a
second translation unit.

Require exactly three original test groups:

1. Signed hashing, collision chains, present/missing lookup, and duplicate
   payload behavior.
2. Pool lifecycle, eleventh-allocation failure with unchanged state,
   recycling, and repeated reset.
3. Two-sum comparison with brute force, including a hit, a miss, repeated
   calls, and a case that would expose reuse of the current index.

For modified arrays with duplicate values, both algorithms must agree on
whether a pair exists. They may choose different valid earlier indices:
`two_sum_bf` searches `j` upward; the chain searches most recent insertions
first. Check distinct in-range indices and the requested sum. Restore the
supplied `nums` after a test changes it.

Keep all tested additions and complement subtractions representable as C
`int`. The source does not guard signed overflow. Low-level hash helpers
also require a bucket in 0–9 and valid, disjoint, acyclic chains.

## Feedback and assessment

Assess the meaning of each stored number before its spelling. A student
who compares `lnodes[node].data` directly with the complement has confused
an input index with an input value. Ask the student to identify the extra
`nums[j]` lookup in the supplied code.

Require the search-before-save invariant: at the start of iteration `i`,
every table entry represents an input position smaller than `i`. A match
therefore uses two different positions. Bucket agreement only narrows the
candidates; equality still decides a match.

Do not claim unconditional constant lookup or linear two sum. For `n`
items, `b` buckets, and adequate distribution, lookup examines expected
`O(1+n/b)` nodes. With a bounded load and sufficient pool capacity, the
hash approach has expected `O(n)` work including initialization when
`b=O(n)`. All-colliding values can require quadratic total search work.
The actual program fixes both bucket and pool size at ten.

The older `code/include`, `starter`, `solution`, and tombstone autopsy form
an optional open-addressing reference. They are not the Stage E assignment
and must not replace current-source traces with resizing or deletion tasks.
