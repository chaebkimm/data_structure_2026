# Module 09 Diagram and Linear-Text Models

These models follow [student/lab.c](../student/lab.c). Each visual includes
a linear equivalent with the same positions, values, and routes.

## Model 1 — Signed numbers select ten buckets

We need a valid array position for every signed number. The hash calculation
normalizes a negative remainder before selecting a bucket.

```text
value       -16  -8  -4  -2  -1   1   2   4   8  16
value % 10   -6  -8  -4  -2  -1   1   2   4   8   6
hash_func     4   2   6   8   9   1   2   4   8   6
```

Linear equivalent: the ten numbers select buckets 4, 2, 6, 8, 9, 1, 2, 4,
8, and 6. A negative remainder receives 10. Every result is between 0 and 9.
For example, -16 and 4 collide at bucket 4. Numbers -4 and 16 collide at
bucket 6.

## Model 2 — Bucket heads and pool nodes are different positions

A bucket selects the first linked node. It does not store the candidate
number itself.

```text
hashtable bucket:   0   1   2   3   4   5   6   7   8   9
head:             -1  -1   2  -1  -1  -1  -1  -1  -1  -1
                          |
                          v
node position 2       node position 1       node position 0
{data:-8,next:1}  -->  {data:22,next:0}  -->  {data:12,next:-1}

free_head = 3 --> 4 --> 5 --> 6 --> 7 --> 8 --> 9 --> -1
```

Linear equivalent: initialize an otherwise unused pool, then call
`save_data(2, 12)`, `save_data(2, 22)`, and `save_data(2, -8)`. The calls
return nodes 0, 1, and 2. Bucket 2's head is 2. Its node route is 2, 1, 0.
The payload route is -8, 22, 12. All other bucket heads are -1. Nodes 3–9
remain available.

## Model 3 — Search compares payloads

A shared bucket can contain unequal payloads. Search must compare the
complete payload at each node.

```text
find_data(2, 22): 2(data -8) --> 1(data 22 FOUND)        returns 1
find_data(2, 32): 2(data -8) --> 1(data 22) --> 0(data 12) --> -1
                                                           returns -1
```

Linear equivalent: the successful search compares two nodes and returns
node position 1. The unsuccessful search compares all three nodes and
stops at the ending link. An empty bucket requires no node comparison.

## Model 4 — Duplicate payloads remain separate nodes

The storage helper adds one node whenever allocation succeeds. It does
not implement update-on-duplicate behavior.

```text
before save_data(2, 22): head 2 --> 1 --> 0 --> -1; free_head 3

after:
head 3(data22) --> 2(data-8) --> 1(data22) --> 0(data12) --> -1
free_head 4 --> 5 --> 6 --> 7 --> 8 --> 9 --> -1
```

Linear equivalent: a second payload 22 is stored in new node 3. The old
payload 22 remains in node 1. `find_data(2, 22)` now returns 3 because it
searches newest-first. Allocation failure instead returns -1 and leaves
the old state unchanged.

## Model 5 — Two-sum stores array positions

The application needs the earlier position as its answer. It hashes the
number but stores its position in the node.

```text
nums position:  0    1   2   3   4  5  6  7  8   9
nums number:  -16  -8  -4  -2  -1  1  2  4  8  16

save_data(hash_func(nums[0]), 0)
             bucket 4        payload 0
                                  |
                                  v
                           nums[0] is -16
```

Linear equivalent: bucket 4 stores a node whose payload is position 0.
The candidate number is obtained by reading `nums[0]`. `find_data(4, -16)`
would compare -16 against payload 0 and report no match. The application's
chain walk compares `nums[j]` against the complement instead.

## Model 6 — Target 0 succeeds before inserting position 5

Earlier positions must be available without allowing the current position
to match itself. The application searches before inserting.

```text
fresh pool; after processing i = 0,1,2,3,4:

bucket 2 --> node1(data1) --> -1       nums[1] = -8
bucket 4 --> node0(data0) --> -1       nums[0] = -16
bucket 6 --> node2(data2) --> -1       nums[2] = -4
bucket 8 --> node3(data3) --> -1       nums[3] = -2
bucket 9 --> node4(data4) --> -1       nums[4] = -1
free_head 5 --> 6 --> 7 --> 8 --> 9 --> -1

i = 5; nums[5] = 1; complement = -1; hash_func(-1) = 9
bucket 9 --> node4 --> j=4 --> nums[4]=-1 --> answer={5,4}; return
```

Linear equivalent: bucket heads are 2→1, 4→0, 6→2, 8→3, and 9→4.
All other buckets are empty. Each active node's next is -1. Iteration 5
finds the complement in bucket 9 and does not allocate a node for position
5. Five nodes remain active after the return.

## Model 7 — Reset returns chains to the shared pool

A completed call can leave active candidates. The next call must recycle
them before allocating more nodes.

```text
Model 6 before reset:
free chain 5 --> 6 --> 7 --> 8 --> 9 --> -1

init_hashtable visits buckets in order:
bucket 2 returns node1
bucket 4 returns node0
bucket 6 returns node2
bucket 8 returns node3
bucket 9 returns node4

after reset:
all ten bucket heads = -1
free_head 4 --> 3 --> 2 --> 0 --> 1 --> 5 --> 6 --> 7 --> 8 --> 9 --> -1
```

Linear equivalent: each returned singleton becomes the front of the
current free chain. All ten nodes become available. Their payloads remain
unchanged until reused. Node reuse order differs from the original
0-through-9 order. `init_hashtable` preserves the available pool; it does
not call `init_lnodes_pool`.

For a longer active chain, `free_lnode_chunk` finds its final node, links
that node to the old `free_head`, and moves `free_head` to the supplied
head. The caller clears the old bucket head. Active and free chains must
never share a node.

## Model 8 — A complete miss uses all ten nodes

When no pair exists, every current position is saved after its failed
complement search. Use a fresh pool for the node identities below.

```text
two_sum_ht(100):
bucket 1 --> node5(data5) --> -1
bucket 2 --> node6(data6) --> node1(data1) --> -1
bucket 4 --> node7(data7) --> node0(data0) --> -1
bucket 6 --> node9(data9) --> node2(data2) --> -1
bucket 8 --> node8(data8) --> node3(data3) --> -1
bucket 9 --> node4(data4) --> -1
free_head = -1; answer = {-1, -1}
```

Linear equivalent: bucket 1 contains position 5; bucket 2 contains 6 then
1; bucket 4 contains 7 then 0; bucket 6 contains 9 then 2; bucket 8 contains
8 then 3; bucket 9 contains 4. Buckets 0, 3, 5, and 7 are empty. There are
ten active nodes and no free node. A later reset can recycle all ten.

## Model 9 — Work follows candidate counts

The two algorithms differ in which earlier positions they inspect. Their
cost claims must keep the input assumptions visible.

```text
target 0, brute force: 0+1+2+3+4+5 = 15 pair comparisons
complete brute-force miss: 0+1+2+3+4+5+6+7+8+9 = 45

target 0, hash chains: compare nums[0], nums[1], nums[4] = 3 comparisons
hash preparation and clearing are separate work

generalized n records, b buckets:
  expected lookup: O(1+n/b), with suitable distribution
  one chain of k records: O(k)
  clear all chains: O(b+s), s active nodes
```

Linear equivalent: target 0 succeeds at outer position 5. Brute force
checks fifteen pairs; the hash version checks three candidate numbers.
Those counts describe this input. A generalized design can achieve expected
linear total two-sum work when it keeps chain lengths bounded. All-colliding
candidates can require quadratic total work. The supplied arrays stay at
ten buckets and ten nodes.
