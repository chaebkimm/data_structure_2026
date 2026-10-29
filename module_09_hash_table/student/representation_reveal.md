# Stage B — Representation Reveal: Buckets and Linked Chains

Current pool contract: `new_lnode()` takes no arguments, returns an isolated index with retained data, and initializes the pool only on first use. `save_data` checks the index, writes data/next, then publishes the bucket head. Later `init_lnodes_pool()` calls are no-ops; `init_hashtable()` recycles owned bucket chains.


Preserve the initial inquiry before opening this explanation. The required
representation is the one in [lab.c](lab.c). It uses the node pool supplied
by Module 07.

## 1. Select a group before searching

A full scan compares a requested number with every stored number. We can
reduce the candidates by putting numbers into groups. The calculation must
send equal numbers to the same group every time.

A **hash function** selects a **bucket**, one group of possible matches.
The supplied `hash_func` begins with `value % 10`. If the remainder is
negative, it adds 10. The result is always a bucket position from 0 to 9.

| Value | Remainder | Bucket |
| --- | ---: | ---: |
| -16 | -6 | 4 |
| -1 | -1 | 9 |
| 12 | 2 | 2 |
| 22 | 2 | 2 |
| -8 | -8 | 2 |

Different numbers can select the same bucket. This is a **collision**.
The bucket calculation narrows the search. It does not prove equality.

## 2. Preserve every colliding candidate

A bucket must retain several candidates when their calculations agree.
The supplied representation keeps a linked chain at each bucket. This is
**separate chaining**.

`hashtable[10]` stores the first node position for each chain. A head of -1
means an empty bucket. Otherwise the head selects `lnodes[head]`. Each node
has integer fields `data` and `next`. The final node has `next == -1`.
A bucket position and a node position select different arrays.

A fresh storage experiment saves 12, 22, and -8 into bucket 2. The newest
node becomes the head:

```text
hashtable[2] = 2
lnodes[2] = {data: -8, next: 1}
lnodes[1] = {data: 22, next: 0}
lnodes[0] = {data: 12, next: -1}
free_head = 3
```

All other bucket heads are -1. This state assumes the unused pool was
initialized with `init_lnodes_pool()` before the three calls.

## 3. Separate bucket selection from the stored payload

We must know what each node's integer means. The integer in `data` is its
**payload**. `save_data(hash, data)` takes an already calculated bucket
and a payload. It calls `new_lnode()`, checks its returned index, then writes `data` and `next=hashtable[hash]`, then publishes
the returned node as the new head.

The caller must pass a bucket from 0 to 9. The function has no bucket-range
check. It neither prevents duplicate payloads nor updates an old payload.
A return of -1 means no node was available. On that failure, the bucket
head and node pool are unchanged.

`find_data(hash, data)` compares payloads along one chain. In the state
above, `find_data(2, 22)` visits nodes 2 and 1, then returns 1.
`find_data(2, 32)` visits 2, 1, and 0, then returns -1. An empty bucket
returns -1 without visiting a node.

## 4. Use earlier positions to solve two-sum

Two different positions must supply numbers whose sum equals a target.
The supplied array is:

```text
position:  0    1   2   3   4  5  6  7  8   9
number:  -16  -8  -4  -2  -1  1  2  4  8  16
```

`two_sum_bf` checks each current position `i` against earlier positions
`j` in ascending order, with `j < i`.

`two_sum_ht` stores earlier positions as payloads. It selects their buckets
using their numbers. At position `i`, the needed number is the
**complement**, `target - nums[i]`.

The function searches the complement's bucket before saving `i`. For each
node it reads `j = lnodes[j_node].data`, then checks `nums[j] == j_num`.
`find_data` cannot replace this walk: its comparison checks the stored
position itself, not `nums[j]`.

For target 0, positions 0 through 4 are saved first. Their buckets are
4, 2, 6, 8, and 9. At position 5, the current number is 1 and the
complement is -1. Bucket 9 stores position 4, whose number is -1. The
function returns `answer = {5, 4}` without inserting position 5.

Lookup before insertion guarantees that any match uses an earlier position.
Prepending makes each chain newest-first. Brute force checks earlier
positions oldest-first. Both methods may report different valid pairs when
the input has several solutions.

## 5. Initialize once and recycle between runs

The available nodes must be prepared before the first hash-table run.
`init_lnodes_pool()` makes the ten-node free chain. Initial bucket heads are
already -1. `init_hashtable()` does not create that free chain.

`two_sum_ht` calls `init_hashtable()` at entry. It recycles each active
bucket chain with `free_lnode_chunk`, then clears that bucket's head.
The recycling helper follows the chain to its tail, connects the tail to
the old free chain, and makes the chain head the new `free_head`.

Old payload fields are not erased. Reachability from the bucket heads or
from `free_head` determines whether a node is active or available. A
successful early return leaves active chains for the next reset. A
complete unsuccessful run with an exclusive ten-node pool stores all ten
positions, so `free_head` becomes -1. Resetting makes those nodes reusable.

Keep active chains valid and acyclic. Keep them disjoint from each other
and from the free chain. Repeated `init_lnodes_pool()` calls are no-ops and cannot reset active bucket
chains. The table shares Module 07's pool, so independent list and queue
experiments must release their nodes before the table uses the pool.

If saving fails, `two_sum_ht` stops and sets both answers to -1. The same
result represents an unsuccessful complete search. It does not separately
report pool exhaustion.

## 6. State the cost with its assumptions

A complete brute-force run on ten numbers checks 45 pairs. A chain search
checks only its selected candidates, but all candidates might collide.
With `n` records spread across `b` buckets, expected search work is
`O(1 + n/b)`. A chain of `k` records requires at most `k` comparisons.

A generalized design with a suitably distributed hash and enough buckets
can complete two-sum in expected `O(n)` time. Chosen collisions can make the
work `O(n^2)`. This exact source has fixed arrays of ten buckets and ten
nodes and does not resize them. Increasing input size while keeping ten
buckets does not give an unconditional linear-time guarantee.

Clearing visits `b` bucket heads and `s` active nodes, for `O(b + s)` work.
Prepending an available node takes `O(1)`. The source uses no `malloc` or
`free`; recycling returns records to the fixed pool. It supplies no unique
key-update operation or individual hash-entry removal operation.

The remainder calculation is a teaching hash. It is not a cryptographic
hash or an authenticity check. The optional open-addressed library under
`code/` uses a different representation and is outside the required lab.
