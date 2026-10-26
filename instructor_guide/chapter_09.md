# Chapter 9. Finding Earlier Values with a Hash Table

## Starting Question

> "Which two different positions contain values that add up to the target, and how can we avoid searching every earlier position again?"

**Expected answer:** Keep earlier values in small groups selected by a
repeatable calculation. Search only the group that could contain the needed
value. Compare the actual value before accepting a match.

## Required source and scope

Teach [Module 09's lab.c](../module_09_hash_table/student/lab.c), which
includes [Module 07's linked-node pool](../module_07_linked_list/student/lab.c).
Students trace the supplied code and write a separate test driver. They do
not implement a dynamic map, deletion, tombstones, resizing, or rehashing.
The older open-addressing library remains an optional comparison.

Retrieve integer `next` links, -1, `free_head`, and `new_lnode` from Module
07. Module 08 practiced preserving the meaning of array indices. Here,
bucket indices, linked-node indices, and input indices have different roles.

## Board walkthrough

First count the brute-force pairs. `two_sum_bf` visits each `i` from 0
through 9 and each earlier `j<i`. A complete miss tests 45 pairs. The
answer contains input indices, not the input values.

Next show `hashtable[10]`, initially all -1, and the separate pool
`lnodes[10]`. Call `init_lnodes_pool()` before first use. The bucket heads do
not initialize the pool. Do not reinitialize the pool while bucket chains
still own nodes.

The hash function takes the remainder on division by 10 and adds 10 only
when that remainder is negative. Thus -16 selects 4, -8 selects 2, and 2
also selects 2. A shared bucket is a collision. The stored nodes form a
linked chain, called separate chaining. They do not spill into neighboring
bucket heads.

After a fresh initialization, save payloads 12, 22, and -8 into bucket 2.
The final chain is `2(-8)→1(22)→0(12)→-1`. A find for 12 compares three
payloads and returns node index 0. A missing 32 reaches -1. Saving another
22 creates another node; `find_data` returns the newest match. The helper
does not enforce unique keys or perform updates.

Then trace `two_sum_ht(0)` with the supplied `nums`. At `i=5`, value 1
needs complement -1. Bucket 9 points to node 4, whose payload is input
index 4. The equality test is `nums[4] == -1`, so the answer is `{5,4}`.
Only earlier positions are stored because lookup precedes insertion.

Trace target 100. No pair of supplied values reaches 100. Both algorithms
report `{-1,-1}`. The hash version leaves all ten input indices stored and
`free_head=-1`. Its next call runs `init_hashtable()` to recycle the old
chains. Reset clears bucket heads and reconnects nodes to the free chain;
it does not call C `free` and does not reset `answer`.

## One 180-minute submission

Use the [lesson plan](../module_09_hash_table/instructor/lesson_plan.md) for
Stage A inquiry, Stage B representation and three-target Cognitive Pause,
Stage C investigation, Stage D textbook calibration, and Stage E driver
work. Preserve predictions before revealing answers.

Require exactly three original test groups: hashing and chains; pool
lifecycle and exhaustion; two-sum comparison with brute force. Evidence
includes a hit, a miss, repeated calls, and distinct-index protection.
Check exact chain state and unchanged failed insertion. For duplicate input
values, accept different valid earlier indices because brute force scans
oldest first while prepended chains scan newest first.

A driver beside `lab.c` includes it once and defines `main`. From the
repository root, compile with `-I.` for the Module 07 include. The current
Make targets are `make -C module_09_hash_table/code lab-compile`, `core`,
and `student-tests`. See the [lab instructions](../module_09_hash_table/student/lab.md).

## Cost and limits

Count visited nodes before naming the cost. Saving one node is constant
work. Finding a payload walks its selected chain. With `n` entries, `b`
buckets, and adequately distributed values, lookup has expected
`O(1+n/b)` work. Hash two sum is expected `O(n)` with bounded load,
`b=Θ(n)`, sufficient pool capacity, and linear reset work. All-colliding
values can make total search work quadratic. The actual program fixes the
input, bucket array, and pool at ten; it does not grow.

`init_hashtable` visits all bucket heads and all returned nodes. Valid
chains must be disjoint and acyclic. Bucket helpers require indices 0–9.
Test sums and complement subtractions must fit in `int`. The code checks
pool exhaustion, but does not validate these other preconditions.

## Questions to use in class

- Why does -8 select bucket 2 rather than array position -8?
- What differs between a bucket index, a node index, and a stored input index?
- Why is `find_data(bucket,complement)` unsuitable when payloads are input indices?
- Why must the complement search occur before saving the current index?
- What remains stored after an early successful return?
- How can the pool be full while some buckets are empty?
- Which distribution and capacity conditions support the expected linear claim?
