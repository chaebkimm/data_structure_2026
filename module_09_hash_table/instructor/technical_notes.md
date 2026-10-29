# Module 09 Technical Notes — Current `lab.c`

Current pool contract: `new_lnode()` takes no arguments, returns an isolated index with retained data, and initializes the pool only on first use. `save_data` checks the index, writes data/next, then publishes the bucket head. Later `init_lnodes_pool()` calls are no-ops; `init_hashtable()` recycles owned bucket chains.


## Source boundary

The required source is [student/lab.c](../student/lab.c), including
[Module 07's lab.c](../../module_07_linked_list/student/lab.c). No `main`
is supplied. The lesson uses signed `int` values, ten bucket heads, and ten
pool nodes. The retained open-addressing library under `code/` is optional
and has a different contract. Do not import its result structs, tombstones,
allocation hooks, growth thresholds, or unique-key rules into this lesson.

## State and initialization

`hashtable[10]` holds linked-node indices. A bucket value of -1 means its
chain is empty. `lnodes[10]` holds `{data,next}` records. An active `next`
is another node index or -1. `free_head` identifies the first free node.
It initially equals -1, so the pool must be initialized explicitly.

`init_lnodes_pool()` links `0→1→…→9→-1` and sets `free_head=0` only on its first call. It does not assign data or clear bucket heads; a persistent static guard makes later calls no-ops. `new_lnode()` also calls that initializer. Reuse capacity by recycling table chains, not by reinitializing the pool.
The linked queue taught as a Module 07 list example and reused in Module 08 shares this pool. It must not use
the same nodes concurrently without explicit disjoint ownership.

On valid state, every pool node is owned by exactly one active chain or the
free chain. All chains are acyclic and disjoint. A deliberately detached
node may be temporarily caller-owned during a low-level experiment.
These conditions are caller preconditions; the functions do not validate
them.

## Normalized signed remainder

`hash_func(value)` calculates `value % 10`, then adds 10 only when the
remainder is negative. C signed remainder can be negative. The result is
always in 0–9, including for `INT_MIN` because division is by positive 10.

| Value | C remainder | Returned bucket |
| ---: | ---: | ---: |
| -16 | -6 | 4 |
| -8 | -8 | 2 |
| -1 | -1 | 9 |
| 0 | 0 | 0 |
| 2 | 2 | 2 |
| 16 | 6 | 6 |

Do not use `abs(value)%10`: `abs(INT_MIN)` is not representable as an `int`.
Bucket selection is not equality. For example, -8 and 2 share bucket 2.

## Save and find contracts

`save_data(hash,data)` requires `hash` in 0–9. It calls
`new_lnode()`, checks its returned index, then writes `data` and `next=hashtable[hash]`. On success, that node becomes the new
bucket head and its index is returned. It does not calculate `hash`, check
for an existing payload, update an existing record, or validate bucket
bounds. The caller chooses what the payload means.

When the pool is exhausted, `new_lnode` returns -1 before mutation.
`save_data` then returns -1 and preserves bucket heads, node records, and
`free_head`. A full pool can coexist with empty buckets. Ten is the total
number of stored nodes, not a per-bucket capacity.

`find_data(hash,data)` requires a valid bucket and chain. It traverses
that chain until payload equality or `-1`. It returns the first matching
node index, not the payload or a Boolean. It never modifies the table and
has no explicit traversal counter; termination depends on acyclicity.
Duplicate payloads are legal, and the newest matching payload is found first.

With fresh pool state, saves 12, 22, -8 into bucket 2 allocate nodes 0, 1,
2. The chain is `2(-8)→1(22)→0(12)→-1`, and `free_head=3`.
`find_data(2,12)` returns 0 after three comparisons. Missing 32 visits all
three nodes. Saving 22 again allocates node 3; the next find of 22 returns 3.

## Recycling a chain and resetting the table

`free_lnode_chunk(head)` does nothing for -1. Otherwise it follows `next`
to the tail, attaches the old free chain after that tail, and makes `head`
the new free head. It preserves data fields and links within the returned
chunk. It does not clear any bucket head. Calling it directly on a
bucket-owned chain requires the caller to detach that bucket immediately
and before allocating or traversing again. Do not recycle a chain twice.

`init_hashtable()` processes buckets 0 through 9 in order. Each nonempty
chain is recycled and its bucket is set to -1. Existing free nodes remain
available. A second reset of an empty table changes nothing. The recycled
order need not be numerical order. It depends on bucket order and chain
order. Reset does not change `nums` or `answer`.

For a fresh collision chain `2→1→0` and free chain `3→…→9`, resetting
produces empty buckets and free chain `2→1→0→3→…→9→-1`.

## Brute-force two sum

`two_sum_bf(target)` scans outer index `i` from 0 through 9. Inner index
`j` scans 0 through `i-1`. A hit stores input indices `{i,j}` and returns.
A miss writes both answers as -1. The loop never pairs a position with
itself, and it considers each unordered pair once. A full miss evaluates
`0+1+…+9=45` sums.

The function does not use or reset the hash table. Calling it after
`two_sum_ht` leaves hash chains exactly as they were.

## Hash-based two sum

`two_sum_ht(target)` first calls `init_hashtable()`. For each `i`:

1. Compute `j_num=target-nums[i]`.
2. Select bucket `hash_func(j_num)`.
3. Read each candidate node's payload as earlier input index `j`.
4. Compare `nums[j]` with `j_num`.
5. On a match, write `{i,j}` and return.
6. After an unsuccessful search, save input index `i` in bucket
   `hash_func(nums[i])`.
7. If saving returns -1, stop and write `{-1,-1}`.

The insertion call hashes an input value but stores its input index.
Consequently, `find_data(hash_func(j_num),j_num)` is not a substitute for
the explicit loop: that helper would compare an input index with a value.

At iteration entry, the table contains only previously processed input
positions `j<i`. Searching before saving preserves distinct positions.
A collision only selects candidates; the `nums[j] == j_num` comparison
establishes the exact value match. Two equal values at two different input
positions are a valid pair when their sum is the target.

On a hit, the function returns before saving the current position or
recycling prior nodes. On a complete miss, all ten input indices remain
stored. The next call recycles them first. No-match and pool-exhaustion
failure share the same `{-1,-1}` answer; there is no distinct error status.
With a valid initialized pool owned only by this table, ten nodes suffice
for the ten-element input. Exhaustion before the last insertion signals a
violated capacity/ownership assumption in this fixed workload.

`answer` is global and overwritten on every normal hit or miss. Neither
algorithm returns the answer as its C return value; both have return type
`void`.

## Exact fixed-input checkpoints

The supplied input is `{-16,-8,-4,-2,-1,1,2,4,8,16}`.

| Target | Both algorithms' answer on this input | Values |
| ---: | --- | --- |
| -24 | `{1,0}` | -8 and -16 |
| -20 | `{2,0}` | -4 and -16 |
| 0 | `{5,4}` | 1 and -1 |
| 2 | `{7,3}` | 4 and -2 |
| 3 | `{6,5}` | 2 and 1 |
| 7 | `{8,4}` | 8 and -1 |
| 10 | `{8,6}` | 8 and 2 |
| 24 | `{9,8}` | 16 and 8 |
| 32 | `{-1,-1}` | No two distinct positions |
| 100 | `{-1,-1}` | No pair |

On fresh target 0, nodes 0–4 hold input indices 0–4 and `free_head=5`.
The five nonempty buckets are `2:1`, `4:0`, `6:2`, `8:3`, and `9:4`.
At `i=5`, complement -1 selects bucket 9; node 4 contains input index 4.

On fresh target 100, the final bucket chains are:

```text
bucket 0: -1
bucket 1: 5 → -1
bucket 2: 6 → 1 → -1
bucket 3: -1
bucket 4: 7 → 0 → -1
bucket 5: -1
bucket 6: 9 → 2 → -1
bucket 7: -1
bucket 8: 8 → 3 → -1
bucket 9: 4 → -1
free_head: -1
```

In this fresh trace, each node happens to have the same number as its
payload input index. That is an allocation coincidence. After recycling,
the numbers can differ. Resetting this full table yields free chain
`4→8→3→9→2→7→0→6→1→5→-1`. A following target-0 run allocates nodes
4, 8, 3, 9, 2 for input indices 0, 1, 2, 3, 4 and still answers `{5,4}`.

For a duplicate-input fixture, brute force examines earlier `j` in ascending
order while the chain examines recent matching entries first. The first
matching outer `i` is the same under valid conditions, but the returned
`j` may differ. Grade pair validity and existence, not identical arrays for
all possible fixtures.

## Arithmetic and input assumptions

All array accesses require the documented bounds. All active stored input
indices in two sum must be 0–9. All computed additions in `two_sum_bf` and
subtractions in `two_sum_ht` must be representable as C `int`. Signed
overflow is undefined behavior; the implementation supplies no overflow
checks. Use bounded test values and targets. The supplied fixed values and
the listed targets meet these conditions.

Do not run malformed cycles, invalid bucket indices, or double recycling
to demonstrate a defect. Predict such consequences on paper. Use valid
bounded counterexamples for payload/value confusion or self-pairing.

## Work and storage

The literal program has fixed limits of ten. Use generalized variables only
when explaining how the same design would scale: `n` input items, `b`
buckets, `p` available pool nodes, `k` nodes in one chain, and `r` nodes
currently stored in the table. Assume enough pool nodes for the workload.

| Operation | Work |
| --- | --- |
| `hash_func` | One remainder and conditional adjustment: `O(1)` |
| `save_data` | One free-chain removal and one prepend: `O(1)` |
| `find_data` | Up to `k` comparisons: `O(k+1)` including empty-chain work |
| `free_lnode_chunk` | Walk one chain to its tail: `O(k+1)` |
| `init_hashtable` | Visit `b` heads and `r` active nodes: `Θ(b+r)` |
| `init_lnodes_pool` | Initialize all `p` pool nodes: `Θ(p)` |
| `two_sum_bf` | Up to `n(n-1)/2` sums: `O(n²)` |
| `two_sum_ht` | Reset plus `n` saves and candidate walks; worst `O(b+r+n²)` |

Under adequately distributed values, average chain length is `α=n/b`.
Lookup has expected `O(1+α)` work. With `b=Θ(n)`, a bounded load, sufficient
pool capacity, and ordinary constant-time integer operations, hash two sum
has expected `O(n)` work including reset when the prior table has `O(n)`
entries. Keeping only ten buckets while increasing `n` does not justify
that linear claim. If all values collide, the candidate walks can total
`0+1+…+(n-1)` comparisons.

Reserved storage is `Θ(b+p+n)` including input; the hash structure itself
reserves `Θ(b+p)`, independent of how many nodes are active. The actual
source has fixed arrays and uses no `malloc` or `free`. Recycling changes
ownership inside the pool; it does not return heap memory. No resizing or
amortized growth analysis is required.

## Build and verification

A separate driver includes the actual `lab.c` and defines `main`. From the
repository root, compile with `-I.` so its Module 07 include resolves:

```sh
cc -std=c11 -Wall -Wextra -Wpedantic -I. \
  module_09_hash_table/student/lab_driver.c -o /tmp/module09_lab_driver
/tmp/module09_lab_driver
```

Compile the driver once. Do not separately link either included source.
Use assertions for exact bucket/node state, returned node indices,
unchanged failed insertion, recovered pool ownership, valid answer indices,
and repeated calls. Sanitizers may supplement these valid-state tests when
available. They do not establish logical correctness.

The three student-authored groups are hashing/chains, pool lifecycle, and
two-sum comparison. Supplied checks can cover a wider range of targets.
The optional open-addressing autopsy is about a different representation;
it cannot serve as current-source test evidence.
