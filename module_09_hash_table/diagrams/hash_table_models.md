# Hash Table Models — Current Lab Source

These text diagrams describe [student/lab.c](../student/lab.c). They use
its ten node slots and fifteen bucket heads. Text labels provide the same
information as the spatial arrangement; color is unnecessary.

## Model 1 — Signed keys select fifteen buckets

```text
key             -16  -8  -4  -2  -1   1   2   4   8  16
C key % 15       -1  -8  -4  -2  -1   1   2   4   8   1
hash_func        14   7  11  13  14   1   2   4   8   1
```

A negative remainder receives 15. Buckets are numbered 0–14; node slots
are numbered 0–9. Different keys can share a bucket: -16 and -1 select
14, while 1 and 16 select 1. Equality must still compare full keys.

The concept PPT begins with direct addressing, where a suitable key is
itself an index. Hashing maps signed or large keys into a small table.
The PPT's open-addressing and Robin Hood alternatives choose other table
positions after collisions. This lab instead keeps a linked chain at the
selected bucket.

## Model 2 — Empty table after initialization

```text
initialize()

hashtable[0..14] = {-1, -1, ... , -1}
hnodes_unused   = 0
next allocation = node 0
```

Call initialization before manual lookup or insertion. Static zeroed heads
are not empty markers. The function does not clear `hnodes`, `nums`, or
`answer`. There is no free-node chain or imported pool.

## Model 3 — Keys, data, and head insertion

Starting after initialization, insert `(12,120)`, `(27,270)`, and `(-3,-30)`.
All three keys select bucket 12.

```text
hashtable[12] = 2
                 key   data   next
node 2           -3    -30      1
node 1           27    270      0
node 0           12    120     -1

chain: 2 --> 1 --> 0 --> -1
hnodes_unused = 3
all other bucket heads = -1
```

Each insertion allocates the next node, writes its key and data, sets next
to the old head, then publishes the new head. Each `insert` returns 0;
that status is distinct from the allocated indices 0, 1, and 2.
The counter is the next unused index and allocated count, not the number
of remaining slots. Seven node slots remain.

## Model 4 — Lookup compares keys

```text
find(27): bucket 12 --> node2 key -3 --> node1 key 27 MATCH
                                                   return 1
                                                   data = 270

find(42): bucket 12 --> node2(-3) --> node1(27) --> node0(12) --> -1
                                                                  MISS

find(120): bucket 0 --> -1  MISS
```

An absent key may collide with stored keys. `find` returns a node index or
-1, not the associated data. Check the return value before reading data.
The stored data 120 does not make `find(120)` match key 12.

## Model 5 — A duplicate key consumes another node

After the three-node fixture, `insert(27,271)` returns 0:

```text
hashtable[12] = 3
node 3: key 27, data 271, next 2
node 2: key -3, data -30, next 1
node 1: key 27, data 270, next 0
node 0: key 12, data 120, next -1

find(27) --> node 3 --> data 271
hnodes_unused = 4
```

The older key-27 entry is still linked. Insertion does not implement a
unique-key update. Newest matching keys occur first.

## Model 6 — Capacity failure and reset

Initialize, then insert keys `0,15,...,135`, with data `0,...,9`:

```text
bucket 0 --> node9 --> node8 --> ... --> node0 --> -1
all other fourteen heads = -1
hnodes_unused = 10

insert(150,10) --> -1
heads, counter, and all node fields stay unchanged

initialize()
all fifteen heads = -1
hnodes_unused = 0
old node fields remain, but no bucket points to them

insert(7,70) --> 0
bucket 7 --> node0 {key:7, data:70, next:-1}
hnodes_unused = 1
```

Reset visits the fifteen heads, without following active chains. It does
not reset `answer` or erase old records. Capacity can be exhausted while
most buckets are empty. There is no individual-node recycling operation.

## Model 7 — Two-sum keys and associated input indices

For the first input position, `nums[0]` is -16:

```text
insert(nums[0], 0)
       key     data
        |        |
       -16       0

hash_func(-16) = 14
hashtable[14] --> node0 {key:-16, data:0, next:-1}
```

The key is an input value. Its associated data is an input position.
The bucket index 14, node index 0, stored data 0, and key -16 have distinct
roles even when some integer values happen to coincide.

## Model 8 — Target 0 before and at the match

After processing input positions 0–4:

```text
bucket 7  --> node1 {key:-8, data:1, next:-1}
bucket 11 --> node2 {key:-4, data:2, next:-1}
bucket 13 --> node3 {key:-2, data:3, next:-1}
bucket 14 --> node4 {key:-1, data:4, next:0}
               --> node0 {key:-16, data:0, next:-1}
other heads = -1
hnodes_unused = 5

i=5, nums[i]=1, complement=0-1=-1
find(-1): bucket14 --> node4 key -1 MATCH
j = hnodes[4].data = 4
answer = {4,5}
return before inserting current input position 5
```

Only one stored-key comparison occurs in this target-0 hash trace. The
preceding complement buckets are empty. Brute force reaches the same pair
after 11 comparisons, trying `j=4` first at `i=5`.

## Model 9 — A complete miss and another call

After `two_sum_ht(100)`:

```text
bucket 1  --> node9(key16,data9) --> node5(key1,data5) --> -1
bucket 2  --> node6(key2,data6) --> -1
bucket 4  --> node7(key4,data7) --> -1
bucket 7  --> node1(key-8,data1) --> -1
bucket 8  --> node8(key8,data8) --> -1
bucket 11 --> node2(key-4,data2) --> -1
bucket 13 --> node3(key-2,data3) --> -1
bucket 14 --> node4(key-1,data4) --> node0(key-16,data0) --> -1
all other heads = -1
hnodes_unused = 10
answer = {-1,-1}
```

A subsequent `two_sum_ht(0)` calls `initialize()` before lookup and starts
allocation at node 0 again. No caller reset or free-chain reconstruction
is needed. All hash calls reserve the whole node array for their own run.

## Model 10 — Duplicate values choose the same earlier position

```text
nums = {1,1,5,0,0,0,0,0,0,0}, target = 6

at i=2:
brute force tries j=1 first: nums[1]+nums[2] = 1+5 = 6
hash lookup finds newest key 1: node1 has data 1
both answers = {1,2}
```

Brute force descends through `j`; prepended chains visit newer entries
first. Both stop at the same first `i` and greatest matching earlier `j`.
Search before insertion ensures `j<i` and prevents a self-pair.

## Model 11 — Count before generalizing

```text
brute-force miss: 0+1+...+9 = 45 pair comparisons
brute-force target 0: 0+1+2+3+4+1 = 11 pair comparisons
hash target 0: 1 stored-key comparison, plus constant work at empty buckets
reset: fifteen head assignments and one counter assignment; no node walk
```

A generalized chain can contain all entries. Expected short chains require
adequate key distribution and controlled entries per bucket. Expected
linear complete hash two sum also requires a bucket count proportional to
input size and sufficient node capacity. Worst-case total chain search can
be quadratic. The actual source fixes ten nodes and fifteen buckets.
