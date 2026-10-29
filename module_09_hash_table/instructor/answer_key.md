# Module 09 Instructor Answer Key — Chaining and Two Sum

Current pool contract: `new_lnode()` takes no arguments, returns an isolated index with retained data, and initializes the pool only on first use. `save_data` checks the index, writes data/next, then publishes the bucket head. Later `init_lnodes_pool()` calls are no-ops; `init_hashtable()` recycles owned bucket chains.


Accept equivalent spatial or linear traces, typed or verbal evidence, and
correct explanations in the student's own words. Lock exact numbers only
when a fixture fixes initialization and operation order. The source is
[student/lab.c](../student/lab.c), including Module 07's node pool.

## Inquiry and representation

The task asks for two different input positions, not two distinct numeric
values. Equal values at different positions can form a pair. The supplied
brute-force loop scans each new index `i` against earlier `j<i`. A full miss
checks 45 pairs for ten inputs. The answer stores indices.

Keeping earlier values in groups selected by a repeatable calculation can
reduce candidate searches. Different values can select one group, so group
agreement cannot replace exact equality. In this source, each bucket head
points to a linked chain. Collisions add nodes to that chain.

## Signed hashing

| Value | `value % 10` | `hash_func(value)` |
| ---: | ---: | ---: |
| -16 | -6 | 4 |
| -8 | -8 | 2 |
| -4 | -4 | 6 |
| -2 | -2 | 8 |
| -1 | -1 | 9 |
| 0 | 0 | 0 |
| 1 | 1 | 1 |
| 2 | 2 | 2 |
| 4 | 4 | 4 |
| 8 | 8 | 8 |
| 10 | 0 | 0 |
| 12 | 2 | 2 |
| 22 | 2 | 2 |
| 16 | 6 | 6 |
| 20 | 0 | 0 |
| -10 | 0 | 0 |

Only negative remainders receive +10. Every returned bucket is 0–9.
A negative multiple of ten already returns zero. `save_data` and
`find_data` do not check or normalize the supplied bucket argument.

## Collision and duplicate fixture

With empty bucket heads and freshly initialized pool, run:

```c
int a = save_data(hash_func(12), 12);
int b = save_data(hash_func(22), 22);
int c = save_data(hash_func(-8), -8);
```

| Step | Return | Bucket 2 chain, shown as node(data) | `free_head` |
| --- | ---: | --- | ---: |
| Save 12 | 0 | `0(12)→-1` | 1 |
| Save 22 | 1 | `1(22)→0(12)→-1` | 2 |
| Save -8 | 2 | `2(-8)→1(22)→0(12)→-1` | 3 |

Every other bucket stays -1. Node links are `0.next=-1`, `1.next=0`, and
`2.next=1`. The free chain is `3→4→5→6→7→8→9→-1`.

| Find | Visited nodes | Return |
| --- | --- | ---: |
| `find_data(2,-8)` | 2 | 2 |
| `find_data(2,22)` | 2, 1 | 1 |
| `find_data(2,12)` | 2, 1, 0 | 0 |
| `find_data(2,32)` | 2, 1, 0 | -1 |
| `find_data(1,12)` | none | -1 |

Saving another 22 returns node 3 and produces
`3(22)→2(-8)→1(22)→0(12)→-1`. The next find of 22 returns 3.
No unique-key rule, update operation, neighboring-bucket probe, or
caller-visible probe-count result is supplied.

## Pool lifecycle

Before explicit initialization, `free_head=-1`. Static zeroed node records
do not form a valid initialized free chain. `init_lnodes_pool()` creates
`0→1→…→9→-1` and sets `free_head=0` only on the first call. It does not assign data; later calls are no-ops. Empty bucket heads
must accompany a fresh pool setup. Never reinitialize a pool while active
bucket chains still reference its nodes.

A successful save removes one free node and prepends it. An exhausted save
returns -1 before changing any node, bucket head, or `free_head`. Ten
entries in one bucket exhaust the same shared pool as ten entries spread
across buckets. Empty buckets do not imply available nodes.

Resetting the three-save fixture returns
`2→1→0→3→4→5→6→7→8→9→-1` to the free chain. All bucket heads become
-1. Node data are unchanged. A second reset has no effect. `nums` and
`answer` are unchanged by `init_hashtable()`.

`free_lnode_chunk` walks to the chain's tail before splicing the old free
chain after it. The chain must be valid, disjoint from the free chain and
other active chains, and acyclic. Calling it directly does not detach a
bucket. `init_hashtable` handles the bucket clearing as part of the reset.
The lesson should not run malformed-cycle or double-recycle demonstrations.

## Two-sum index meanings

For input index 1, `nums[1]=-8`, so `hash_func(nums[1])=2`, while the saved
payload is 1. The bucket is 2, the physical node depends on allocation
history, and the payload is an input index. Lookup recovers `j` and then
reads `nums[j]` to compare the earlier input value with the complement.

Consequently, neither `lnodes[node].data == j_num` nor
`find_data(hash_func(j_num),j_num)` implements this search. Those compare
the input index against the desired value. The same low-level helper can
store raw values in an earlier exercise; its caller defines the meaning of
`data`.

At iteration entry, all entries represent earlier positions `j<i`.
Searching before saving the current index ensures a match uses different
positions. Two equal values at different positions remain legal.

## Fixed-input results

Use the supplied `nums={-16,-8,-4,-2,-1,1,2,4,8,16}`.

| Target | `answer` from both algorithms | Matching values |
| ---: | --- | --- |
| -24 | `{1,0}` | -8 + -16 |
| -20 | `{2,0}` | -4 + -16 |
| 0 | `{5,4}` | 1 + -1 |
| 2 | `{7,3}` | 4 + -2 |
| 3 | `{6,5}` | 2 + 1 |
| 7 | `{8,4}` | 8 + -1 |
| 10 | `{8,6}` | 8 + 2 |
| 24 | `{9,8}` | 16 + 8 |
| 32 | `{-1,-1}` | No pair |
| 100 | `{-1,-1}` | No pair |

For target 0 after fresh initialization:

| `i` | `nums[i]` | Complement | Searched bucket | Result, then save |
| ---: | ---: | ---: | ---: | --- |
| 0 | -16 | 16 | 6 | empty; save index 0 in bucket 4 |
| 1 | -8 | 8 | 8 | empty; save index 1 in bucket 2 |
| 2 | -4 | 4 | 4 | node 0 represents -16; save index 2 in bucket 6 |
| 3 | -2 | 2 | 2 | node 1 represents -8; save index 3 in bucket 8 |
| 4 | -1 | 1 | 1 | empty; save index 4 in bucket 9 |
| 5 | 1 | -1 | 9 | node 4 stores `j=4`; `nums[4]=-1`; return |

The returned pair is `{5,4}`. Index 5 is not saved. There are five active
nodes, bucket heads `2:1,4:0,6:2,8:3,9:4`, and `free_head=5`.
The early return does not recycle those nodes.

For fresh target 100, all ten positions are saved and `free_head=-1`.

| Bucket | Physical-node chain | Input values in that chain |
| ---: | --- | --- |
| 0 | -1 | none |
| 1 | `5→-1` | 1 |
| 2 | `6→1→-1` | 2, -8 |
| 3 | -1 | none |
| 4 | `7→0→-1` | 4, -16 |
| 5 | -1 | none |
| 6 | `9→2→-1` | 16, -4 |
| 7 | -1 | none |
| 8 | `8→3→-1` | 8, -2 |
| 9 | `4→-1` | -1 |

Node and payload indices coincide only because a fresh pool allocated
0 through 9 in order. Reset visits buckets in increasing order, producing
free chain `4→8→3→9→2→7→0→6→1→5→-1`. A following target-0 call saves
input indices 0–4 in nodes 4, 8, 3, 9, 2, respectively. Its successful
lookup uses node 2 containing input index 4, and still returns `{5,4}`.

## Brute-force comparison and duplicate inputs

The algorithms agree on pair existence when arithmetic and capacity
preconditions hold. They need not choose identical earlier positions on
all modified inputs. Brute force scans `j` upward. Prepending puts the
most recently stored matching position first in the hash chain.

For example, use `nums={1,1,5,0,0,0,0,0,0,0}` and target 6.
At `i=2`, brute force returns `{2,0}`; hash two sum returns `{2,1}`.
Both represent 5+1 using different valid positions. The changed-array
fixture should not remain installed after the test.

Good assertions check `0<=j<i<10`, `nums[i]+nums[j]==target`, and agreement
on whether no pair exists. For the locked fixed-input targets, exact answer
indices can also be required. Copy one algorithm's global `answer` before
calling the other, which overwrites it.

## Safe autopsy reasoning

A comparison against node data alone confuses an input index with its
value. At target 0 and `i=5`, the correct comparison reads `nums[4]`
and matches -1. Comparing the stored index 4 with -1 instead misses that
pair. This is the first control-flow divergence for that fixture.

Saving before searching lets a current position appear among earlier
candidates. With target 2, index 5 could then match its own value 1 and
incorrectly return `{5,5}`. The correct first pair is `{7,3}`, using 4 and
-2. Explain this counterfactual on paper or in an isolated
bounded experiment; do not change the supplied lab source.

The old delete-to-empty program diagnoses open-addressing tombstones. It
is optional and does not test this chained implementation.

## Work and limits

The actual arrays have ten positions. For generalized analysis, use `n`
input values, `b` buckets, `p` pool nodes, and `r` currently active nodes.

- One save removes a free head and prepends a node: constant work.
- A lookup visits its selected chain: up to every stored entry in that
  bucket. Expected work is `O(1+n/b)` under adequate distribution.
- Returning a chain walks to its tail. Reset visits all `b` heads and all
  `r` returned nodes: `Θ(b+r)`.
- Brute-force two sum can test `n(n-1)/2` pairs.
- With `b=Θ(n)`, bounded load, enough nodes, and adequate distribution,
  hash two sum has expected `O(n)` work including reset of an `O(n)`
  prior table. Chosen collisions can make the candidate walks quadratic.
- Holding `b=10` while increasing `n` does not establish expected linear
  two sum. The fixed ten-node pool cannot store an arbitrary larger input.
- The hash structure reserves `Θ(b+p)` storage. It uses no heap allocation
  or resizing. Returning pool nodes does not invoke C `free`.

All tested additions and complement subtractions must fit in `int`. The
source does not check signed overflow, bucket bounds, chain cycles, shared
ownership, or invalid stored indices. It checks only the documented empty
free-chain allocation case. Tests should obey other preconditions.

## Three test groups and grading

Require exactly three student-authored groups:

1. Hashing/chains: signed bucket calculations, collisions, exact returned
   nodes, present/missing searches, and duplicate payload behavior.
2. Pool lifecycle: ten saves, unchanged eleventh failure, complete
   recycling, repeated reset, and successful reuse.
3. Two sum: fixed hits and misses, target-2 distinct-position protection,
   repeated calls, and comparison with brute force. A duplicate-input
   extension checks validity rather than identical earlier indices.

Award evidence credit for commands, exact states, assertions, and corrected
predictions. Deduct affected reasoning credit for conflating a bucket with
a node, comparing input indices with values, reinitializing live storage,
accepting self-pairs, or making unconditional performance claims. Do not
require dynamic allocation, public validators, tombstone deletion, growth,
or implementation TODOs from the optional older library.
