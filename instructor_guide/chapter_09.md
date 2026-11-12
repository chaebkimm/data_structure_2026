# Chapter 9. Storing and Finding Data by Key

## Starting Question

> "How can we find a stored value without comparing it with every array entry again?"

**Expected answer:** First remember each small nonnegative value's input
position at the table index equal to that value. When the range is too large
or includes negative values, use a hash function to select a bounded bucket.
Keep colliding keys in a chain and compare their complete keys.

## Required source and PPT references

Teach [Module 09's lab.c](../module_09_hash_table/student/lab.c). It is
self-contained, with ten `hnode` records and fifteen bucket heads. Students
trace supplied code and write a driver. There is no Module 07 dependency,
free list, individual deletion, or dynamic allocation.

Use [the concept PPT material](../module_09_hash_table/student/ppt_material.md)
for array search, direct addressing, hashing, collisions, and two sum, and
[the code PPT material](../module_09_hash_table/student/ppt_lab_material.md)
for key/data/next nodes, head insertion, and lookup. Its five-node,
seven-bucket example and positive input are smaller illustrations. For
required traces use current names `hnodes_unused`, `hashtable`, `nums`,
`answer`, capacities 10/15, and descending brute-force `j`. Open addressing
and Robin Hood hashing remain conceptual comparisons. Keep all lab and
PPT source files unchanged.

## Board walkthrough

Start with `{2,5,6}`. Searching for 5 scans 2, then 5, and returns input
position 1. Searching for absent 3 checks all three entries. Build a
seven-position direct-address table `{-1,-1,0,-1,-1,1,2}` so `table[5]`
returns 1 immediately. Explain why negative keys cannot be direct indices
and why a sparse large range would demand too much table space. Then
introduce bounded bucket selection, collisions, and separate chains.

Show `hashtable[15]` separately from `hnodes[10]`. Each record has
`key`, `data`, and `next`. Manual experiments begin with `initialize()`:
static zero heads are not empty markers. Initialization writes -1 to all
fifteen heads and resets `hnodes_unused` to zero. The counter is also the
next unused node index.

The hash function computes the remainder modulo 15, then adds 15 only
when negative. Thus -16 and -1 select 14, -8 selects 7, and 1 and 16
select 1. A collision is not equality. Chains retain all candidates and
`find` compares their full keys.

After initialization, insert `(12,120)`, `(27,270)`, and `(-3,-30)`.
All keys select bucket 12. The final chain is `2→1→0→-1`, with keys
`-3,27,12` and data `-30,270,120`. Each `insert` returns status 0;
`find(12)` returns node 0 after three key comparisons. Missing `find(42)`
visits all three nodes. `find(120)` does not search data. A fourth insert
`(27,271)` creates node 3, and `find(27)` returns that newest matching
node with data 271. The earlier equal key remains allocated.

After insertion and lookup are familiar, introduce two sum as a later
application. `two_sum_bf` visits `j=i-1,i-2,...,0` for each increasing `i`.
A complete miss checks 45 pairs; target 0 succeeds at `i=5,j=4` after 11
checks and returns `{4,5}`. Use complement lookup to replace the repeated
earlier-position scan.

Then trace `two_sum_ht(0)`. At `i=5`, value 1 needs complement -1. Bucket
14 points to node 4, with key -1 and data 4. The lookup returns node 4;
the caller retrieves earlier position 4 and writes `{4,5}`. No insertion
occurs for current index 5. Five records remain allocated, including
bucket-14 chain `4→0→-1`. This scan makes one stored-key comparison.

Trace target 100. All ten lookups miss; every input position is inserted,
`hnodes_unused=10`, and `answer={-1,-1}`. The next hash call initializes
at entry and allocates from node 0 again. Reset does not walk chains or
clear node fields, input values, or the previous answer. A manual eleventh
insertion returns -1 without changing heads, counter, or nodes.

## One 180-minute submission

Use [the lesson plan](../module_09_hash_table/instructor/lesson_plan.md)
for Stage A inquiry, Stage B representation and Cognitive Pause, Stage C
investigation, Stage D textbook calibration, and Stage E driver work.
Preserve predictions before revealing results; accept spatial or linear
traces with the same evidence requirements.

Require three original assertion groups: hashing/chains, capacity/reset,
and two sum. Include exact state, key/data distinction, duplicate-key
lookup, unchanged failed insertion, a hit, a miss, repeated calls, and
self-pair protection. For `{1,1,5,0,0,0,0,0,0,0}` with target 6, both
methods return `{1,2}`: descending `j` and newest-first key lookup choose
the same earlier duplicate. Assert valid indices and sum as well as exact
agreement. Restore the original input after custom fixtures.

A driver beside `lab.c` includes it once and defines `main`. Compile only
that driver; no imported source or repository-root include path is needed.
Run `make -C module_09_hash_table/code lab-compile core student-tests`.
See [the lab instructions](../module_09_hash_table/student/lab.md).

## Costs and limits

Allocation and head insertion take constant work. Key lookup may inspect
an entire chain. For `n` entries, `b` buckets, and adequate distribution,
expected lookup work is `O(1+n/b)`. Reset costs `Θ(b)` because it visits
heads only. With `b=Θ(n)` and enough node capacity, complete hash two sum
has expected `O(n)` work including reset; all-colliding keys can make
search quadratic. The actual source fixes ten nodes and fifteen buckets
and never grows.

All evaluated sums and complement subtractions must fit in `int`; the
source does not check signed overflow. Manually constructed next links
must form valid, acyclic chains. Tests should detect valid-operation
failures without executing invalid-index or corrupted-chain experiments.
The retained open-addressing library and tombstone autopsy are optional.

## Questions to use in class

- How does a scan find value 5 in `{2,5,6}`, and how does direct addressing avoid repeating it?
- Why do negative keys and a large sparse key range motivate a bounded hash table?
- Why does -8 select bucket 7 rather than array position -8?
- What differs between a bucket, node, input position, key, and associated data?
- Why does `find(120)` not retrieve key 12 with data 120?
- Why must the complement lookup happen before current-position insertion?
- Why do duplicate-key insertion and unique-key update differ?
- How can ten nodes be exhausted while fourteen buckets remain empty?
- What remains in node fields after reset, and which node is allocated next?
- Which distribution and capacity conditions support expected linear work?
