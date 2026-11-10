# Module 09 Technical Notes — Current Chained Hash Table

## Authoritative source and PPT bridge

The required implementation is [student/lab.c](../student/lab.c). It is
self-contained and uses fixed arrays; it imports no other chapter's source.
The PPTs supply the conceptual sequence and smaller code examples. Their
five nodes, seven buckets, positive input, and names `size/htable/arr/ans`
are replaced in the current source by ten nodes, fifteen buckets, signed
input, and `hnodes_unused/hashtable/nums/answer`. Brute force now searches
earlier positions in descending order. The hash version checks failure of
`insert`. Preserve lab and PPT files as read-only references.

## Representation and initialization

```c
enum { NODES_CAPACITY = 10, TABLE_CAPACITY = NODES_CAPACITY * 3 / 2 };
struct hnode {
    int key;
    int data;
    int next;
};
struct hnode hnodes[NODES_CAPACITY];
int hnodes_unused = 0;
int hashtable[TABLE_CAPACITY];
```

`TABLE_CAPACITY` evaluates to 15. The fifteen bucket positions and ten node
positions index different arrays. `key` is the value used for hashing and
equality. `data` is associated information; two sum stores an input index
there. `next` is another node index or -1. Heads have the same node-index
meaning. A chain's nodes all have keys hashing to its bucket.

Static storage initializes the arrays to zero, which does **not** represent
an empty table. Call `initialize()` before manual insertion or lookup.
`two_sum_ht` makes that call itself. Initialization resets
`hnodes_unused=0` and assigns -1 to every bucket. It leaves node fields,
`nums`, and `answer` unchanged. Old node indices are invalid as active
references after reset, even though their fields are still readable. The
next allocation starts at node 0 and overwrites all three fields.

The name `hnodes_unused` denotes the first unused index, not the number of
remaining slots. After `r` allocations it is `r`; remaining capacity is
`NODES_CAPACITY-r`. There is no free list, individual deletion, chain
recycling, heap allocation, or growth.

## Allocation and insertion

`new_hnode(_key,_data,_next)` checks capacity before incrementing the
counter. On success it writes all fields and returns the allocated node
index. On exhaustion it returns -1 without changing state. It does not
link the new node into a bucket or validate `_next`. In ordinary table use,
`insert` supplies a valid previous head. A direct helper experiment may
allocate a node not reachable from a bucket; that still consumes capacity.

`insert(k,d)` hashes the key, remembers the old head, and allocates a node
whose `next` is that head. Only after successful allocation does it publish
the new head. It returns 0 on success and -1 on exhaustion. Do not confuse
its success code with the node index returned by `new_hnode` or `find`.
Failed insertion preserves heads, node fields, counter, `nums`, and
`answer`. A full node array can coexist with fourteen empty buckets.

The operation never searches for an existing key. Repeated equal keys
allocate separate nodes. Newest-first lookup retrieves the data belonging
to the most recently inserted equal key; earlier nodes remain allocated.

## Signed hashing and lookup

`hash_func(key)` computes `key % 15` and adds 15 only when the remainder is
negative. This produces 0–14 even for `INT_MIN`; it never negates the key.
A negative multiple of 15 already has remainder zero and needs no change.

| Key | C remainder `% 15` | Bucket |
| ---: | ---: | ---: |
| -16 | -1 | 14 |
| -8 | -8 | 7 |
| -4 | -4 | 11 |
| -2 | -2 | 13 |
| -1 | -1 | 14 |
| 0 | 0 | 0 |
| 1 | 1 | 1 |
| 2 | 2 | 2 |
| 4 | 4 | 4 |
| 8 | 8 | 8 |
| 16 | 1 | 1 |

`find(k)` calculates its own bucket and compares full `key` fields while
following `next`. It returns the first equal node index or -1. It does
not search data fields or every bucket. Check for -1 before indexing the
returned node. An absent key can collide with stored keys and still miss.

After initialization, insert `(12,120)`, `(27,270)`, and `(-3,-30)`.
All keys hash to 12; the chain is `2(-3,-30)→1(27,270)→0(12,120)→-1`
and `hnodes_unused=3`. `find(12)` visits 2,1,0 and returns 0;
`find(42)` visits the same nodes and returns -1. `find(120)` does not find
key 12 merely because its associated data is 120. Inserting `(27,271)`
uses node 3 and makes `find(27)` return 3, data 271.

## Two-sum behavior

`NUMS_SIZE=NODES_CAPACITY=10`; the supplied input is
`{-16,-8,-4,-2,-1,1,2,4,8,16}`. Both methods return `{j,i}` with
`0<=j<i<NUMS_SIZE`. On a miss they write `{-1,-1}`.

`two_sum_bf` increases `i` and decreases `j` from `i-1` to zero. It stops
at the first successful `i` and chooses the greatest matching earlier `j`.
It changes `answer` but not the hash storage.

`two_sum_ht` calls `initialize()` on every invocation. At each `i`, it:

1. Calculates `complement=target-nums[i]`.
2. Calls `find(complement)`, which compares keys.
3. On a match, reads `j=hnodes[node].data`, writes `{j,i}`, and returns.
4. On a miss, inserts key `nums[i]` with data `i`.
5. Breaks if insertion fails, then writes `{-1,-1}`.

All entries at iteration entry represent positions less than `i`. Search
before insertion prevents a self-pair. For equal keys, the most recent
position occurs first in the chain. Consequently both methods choose the
same first ordered pair for representable arithmetic and sufficient
capacity, including duplicate inputs. The current ten-element search has
enough capacity because initialization reserves all ten slots for the run.

| Target | Both methods return | Values |
| ---: | --- | --- |
| 0 | `{4,5}` | -1 and 1 |
| 2 | `{3,7}` | -2 and 4 |
| 3 | `{5,6}` | 1 and 2 |
| 100 | `{-1,-1}` | No pair |

For the duplicate fixture `{1,1,5,0,0,0,0,0,0,0}`, target 6 returns `{1,2}`
in both methods. With just one 5 and other values 20, target 10 misses;
with two 5s it returns `{0,1}`. Restore the original `nums` after tests.

A successful target-0 call leaves five nodes allocated. Its nonempty heads
are `7:1`, `11:2`, `13:3`, `14:4`; bucket 14 has chain `4→0→-1`.
A target-100 miss leaves ten allocated nodes and heads
`1:9`, `2:6`, `4:7`, `7:1`, `8:8`, `11:2`, `13:3`, `14:4`.
Node 9 links to 5 in bucket 1, and node 4 links to 0 in bucket 14.
The next hash call resets the counter and heads before its first lookup.
`initialize()` itself does not reset a previous answer.

The failure result does not distinguish exhaustion from an ordinary miss.
Capacity failure is relevant to manual insertion tests; it is unreachable
in the unchanged ten-number run before all candidates have been processed.

## Work and limits

| Operation | Generalized work |
| --- | --- |
| `hash_func`, `new_hnode`, `insert` | `Θ(1)` |
| `find` on a chain of length `k` | Worst `Θ(k+1)` including an empty chain |
| `initialize` on `b` buckets | `Θ(b)`; no active-node traversal |
| Brute-force miss on `n` numbers | `n(n-1)/2` pair checks; `Θ(n²)` |
| Hash two sum | Expected `O(b+n(1+n/b))` under adequate distribution; worst `O(b+n²)` |

A brute-force miss here checks 45 pairs. Target 0 checks 11 pairs because
its first comparison at `i=5` succeeds. The hash target-0 scan makes one
stored-key comparison: all preceding complement buckets are empty, then
node 4 matches -1. Empty lookups still perform constant work. These counts
are fixture-specific, not worst-case guarantees.

For a scalable version with `b=Θ(n)` and enough nodes, initialization and
expected search together cost `O(n)`. Keeping fifteen buckets fixed while
increasing input size does not ensure expected linear work. All-colliding
keys can produce quadratic total traversal. Generalized storage is
`Θ(b+p)` for `p` available nodes; this source reserves fifteen heads and
ten records and never grows.

Every evaluated sum and complement subtraction must fit in C `int`.
The source does not check signed overflow or validate manually corrupted
chains. Helpers assume valid linked indices and acyclic chains. Do not
execute invalid-index or corrupted-chain demonstrations.

## Optional comparisons

The PPT direct-address example stores positions directly under small
nonnegative values. Hashing permits signed and large keys with a bounded
bucket array, at the cost of collisions. The concept PPT also introduces
open addressing and Robin Hood displacement. They do not describe the
lab's linked chains.

The retained `code/include`, `starter`, and `solution` library uses open
addressing, tombstones, and growth. Its tests and delete-to-empty autopsy
are optional enrichment. Required evidence must exercise the actual
`student/lab.c` through a separate driver, leaving lab and PPTs unchanged.
