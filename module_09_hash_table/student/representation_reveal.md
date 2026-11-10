# Stage B — Representation Reveal: Keys, Buckets, and Linked Chains

Preserve the Stage A inquiry before opening this explanation. The required
representation is the one in [lab.c](lab.c). It owns its node array and has
no source dependency on Module 07.

## 1. Select a group before searching

A direct-address table can use a small nonnegative key as an index. Sparse,
large, or negative keys make that representation inconvenient. A **hash
function** maps a key into a bounded group, called a **bucket**. Equal keys
must select the same bucket every time.

The supplied constants are `NODES_CAPACITY = 10` and
`TABLE_CAPACITY = NODES_CAPACITY * 3 / 2`, giving 15 buckets. `hash_func`
calculates `key % TABLE_CAPACITY` and adds `TABLE_CAPACITY` only when the
remainder is negative. Returned buckets are 0 through 14.

| Key | C remainder `% 15` | Bucket |
| --- | ---: | ---: |
| -16 | -1 | 14 |
| -1 | -1 | 14 |
| 12 | 12 | 12 |
| 27 | 12 | 12 |
| -3 | -3 | 12 |

Different keys can select the same bucket. This is a **collision**. A
bucket narrows the search; only a comparison of complete keys proves a match.

## 2. Preserve every colliding candidate

`hashtable[TABLE_CAPACITY]` stores one chain-head node index per bucket.
A head of -1 means an empty bucket. A nonnegative head selects a record in
`hnodes[NODES_CAPACITY]`. Each `struct hnode` has `key`, `data`, and `next`.
The final node has `next == -1`. Bucket indices and node indices select
different arrays, with different capacities.

Call `initialize()` before using `insert` or `find`. Then run:

```c
insert(12, 120);
insert(27, 270);
insert(-3, -30);
```

All three keys select bucket 12. Each insertion puts a new node first:

```text
hashtable[12] = 2
hnodes[2] = {key: -3, data: -30, next: 1}
hnodes[1] = {key: 27, data: 270, next: 0}
hnodes[0] = {key: 12, data: 120, next: -1}
hnodes_unused = 3
```

All other bucket heads are -1. This collision rule is **separate chaining**.
It does not search neighboring buckets for an empty slot.

## 3. Separate a key from its payload

The `key` selects the bucket and is compared during lookup. The `data` is
an associated **payload**. `insert(k, d)` computes the bucket, calls
`new_hnode(k, d, old_head)`, checks allocation, and publishes the new head.
It returns 0 on success or -1 when all ten records are allocated. On failure,
the node array, allocation counter, and bucket heads remain unchanged.

`find(k)` computes the bucket and compares `hnodes[node].key == k` while
following `next`. It returns the first matching **node index**, or -1.
In the state above, `find(27)` visits nodes 2 and 1, returning 1. The payload
is then `hnodes[1].data`, or 270. `find(42)` visits nodes 2, 1, and 0, then
returns -1. Matching the bucket alone is insufficient.

`insert(27, 271)` creates node 3 with next 2. It does not update node 1.
Now `find(27)` returns 3 and its payload is 271. Duplicate keys remain in
the chain; the newest matching key is found first.

## 4. Use earlier positions to solve two-sum

The supplied input is:

```text
position:  0    1   2   3   4  5  6  7  8   9
number:  -16  -8  -4  -2  -1  1  2  4  8  16
```

`two_sum_bf` visits current positions `i` in ascending order. For each `i`,
it visits `j` from `i - 1` down to 0. Every examined pair satisfies `j < i`.
It writes the answer in the order `{j, i}`.

`two_sum_ht` starts with `initialize()`. Before processing position `i`,
the table contains only earlier positions: each key is `nums[j]` and its
payload is `j`. It calculates `complement = target - nums[i]` and calls
`find(complement)`. If a node is found, its `data` supplies the earlier
position. Otherwise, `insert(nums[i], i)` stores the current candidate.

For target 0, positions 0 through 4 are saved in buckets 14, 7, 11, 13,
and 14. At `i = 5`, the current value is 1 and complement is -1. Bucket 14
starts at node 4, whose key is -1 and data is 4. The function returns
`answer = {4, 5}` without inserting position 5.

Searching before insertion prevents a self-pair. Both descending brute-force
search and prepended chains choose the newest earlier matching position.
For `{1,1,5,0,0,0,0,0,0,0}` and target 6, both return `{1,2}`. Equal values
at different positions remain legitimate candidates.

## 5. Reset the table and reuse its records

`hnodes_unused` identifies the next unused array slot. `new_hnode` takes
that slot and increments the counter. It returns -1 at capacity without
mutating state. There is no free list, individual deletion, or chain recycling.

`initialize()` sets `hnodes_unused` to 0 and all 15 bucket heads to -1.
It does not erase node fields, change `nums`, or reset `answer`. Old nodes
are no longer reachable through the heads and can be overwritten by later
allocations. Call it before the first table operation; static zeroed heads
are not the required -1 initialization.

A successful two-sum return leaves earlier nodes in the table. A miss on
target 100 stores all ten positions. Every `two_sum_ht` call resets the
previous table at entry, so 100 followed by 0 works without a manual reset.
A failed insertion ends the scan with `{-1,-1}`. With the supplied capacity
and ten inputs, a fresh run has enough slots for every insertion.

## 6. State the cost and compare other representations

A complete brute-force miss checks 45 pairs. A chain of `k` nodes requires
at most `k` key comparisons. Hashing, allocating a slot, and prepending take
constant work. Reset visits all `b` bucket heads, for `O(b)` work; it does
not walk the old nodes. Storage is `O(b + n)` for `b` heads and `n` node slots.

With suitably distributed keys, expected lookup work is `O(1 + n/b)`.
A scalable design with bounded load and `b = Θ(n)` can perform two-sum in
expected `O(n)` time including reset. All-colliding keys can cause `O(n^2)`
total search work. This exact source fixes 10 nodes and 15 buckets and never
resizes them. Its remainder function is a teaching hash, not a password hash.

An alternative is **open addressing**, which places entries directly
in table slots and probes for another slot after a collision. **Robin Hood
hashing** can give a slot to the entry that has traveled farther along its
probe sequence. These explain alternative collision rules; the required
lab implements separate chaining. The older library under `code/` is an
optional open-addressing comparison.
