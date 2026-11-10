# Module 09 Answer Key — Storing and Finding Data with a Hash Table

These answers describe the current [lab.c](../student/lab.c): ten `hnode`
records, fifteen bucket heads, and no external source dependency. Use the
PPTs for concepts; their smaller code examples have different capacities,
identifiers, input values, and brute-force loop order.

## Stage A — Find stored values before applying lookup

### A. Scan an array, then use a direct-address table

For the array `{2,5,6}`, searching in order for 5 compares 2, then 5,
and reports input position 1 after two comparisons. Searching for absent 3
compares all three values before reporting a miss.

The seven table entries are `{-1,-1,0,-1,-1,1,2}`. Thus `table[5]=1`
reports the original position of 5 and `table[3]=-1` reports absence. Values
select table indices; the entries contain input positions. This is direct
addressing. Negative values cannot directly index the array, and a few
very large values would require a table spanning a wastefully large range.
These limitations motivate the bounded table introduced afterward.

### B. Group keys, then compare complete keys

| Key | C remainder `% 15` | Selected place |
| ---: | ---: | ---: |
| 12 | 12 | 12 |
| 27 | 12 | 12 |
| -3 | -3 | 12 |
| -16 | -1 | 14 |
| 0 | 0 | 0 |

Keys 12, 27, and -3 select the same place. Putting each new record first
gives key order `-3 → 27 → 12`. A search for 42 selects this same place,
compares all three complete keys, and reaches the end without a match.
The separate data field supplies associated information only after a key
match. A shared place never proves equal keys.

### C. Reset references and the allocation counter together

Ten record slots can be exhausted while fourteen starting places remain
empty. An eleventh allocation reports -1 and leaves the existing state
unchanged. Clearing only starting references leaves the allocation counter
at ten and restores no capacity. Reset both the counter to zero and every
starting reference to -1 before reusing slots. Old node fields need not be
erased: no starting reference reaches them, and subsequent allocation
writes new fields. There is no free chain to rebuild.

### D. Introduce the pair application last

Only after lookup and storage are understood, apply them to two input
positions. Store earlier input values as keys and their input positions as
data. Search for the needed value before storing the current position.
The exact pair answers, descending-loop order, comparison counts, and
self-pair explanation appear in Stage D below.

## Stage B — Representation and signed hashing

| Quantity | Meaning |
| --- | --- |
| `NODES_CAPACITY` | 10 node slots |
| `TABLE_CAPACITY` | `10*3/2`, or 15 bucket heads |
| `NUMS_SIZE` | 10 input numbers |
| `hashtable[bucket]` | First node index, or -1 |
| `hnodes[node].key` | Value used for hashing and equality |
| `hnodes[node].data` | Associated data; an input position in two sum |
| `hnodes[node].next` | Next node index, or -1 |
| `hnodes_unused` | Next unused node index and allocation count |

Before manual table use, call `initialize()`: bucket heads are statically
zero at process start, which is not the empty marker. Initialization writes
-1 to all fifteen heads and sets the counter to 0. It does not clear the
node records, `nums`, or `answer`.

| Key | C remainder `% 15` | `hash_func(key)` |
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
| 12 | 12 | 12 |
| 27 | 12 | 12 |
| -3 | -3 | 12 |

The negative-remainder branch adds 15. A negative multiple of 15 already
has remainder 0. `hash_func` accepts all `int` keys, including the extremes,
because it does not negate the key. A collision gives only bucket equality;
`find` must still compare full keys.

Open addressing and Robin Hood hashing from the concept PPT are alternate
collision strategies. They do not describe this lab's separate chains.

## Stage C — Allocation, chains, and lookup

Start with `initialize()`, then execute the following inserts:

| Operation | `insert` return | Allocated node | Node `(key,data,next)` | Head 12 | Counter |
| --- | ---: | ---: | --- | ---: | ---: |
| `insert(12,120)` | 0 | 0 | `(12,120,-1)` | 0 | 1 |
| `insert(27,270)` | 0 | 1 | `(27,270,0)` | 1 | 2 |
| `insert(-3,-30)` | 0 | 2 | `(-3,-30,1)` | 2 | 3 |

The final chain is `2→1→0→-1`. It is newest first because each insertion
uses the old head as its new node's `next`. The other fourteen heads remain
-1. This does not move entries into neighboring buckets.

| Lookup | Visited node indices | Return | Retrieved data after a match |
| --- | --- | ---: | ---: |
| `find(-3)` | 2 | 2 | -30 |
| `find(27)` | 2,1 | 1 | 270 |
| `find(12)` | 2,1,0 | 0 | 120 |
| `find(42)` | 2,1,0 | -1 | No data access |
| `find(120)` | None; bucket 0 is empty | -1 | No data access |

Lookup compares keys, not data. A caller cannot search for the payload 120
and expect key 12 to match. `find` calculates its own bucket, so callers do
not pass bucket arguments to `insert` or `find`.

`insert(27,271)` returns 0, allocates node 3, sets its next to 2, and makes
head 12 equal 3. `find(27)` now returns node 3 with data 271. The older
key-27 node 1 remains allocated and linked. Duplicate insertion consumes
another slot; it does not update or reject the existing key.

`new_hnode(key,data,next)` returns an allocated index; `insert` returns a
status. The allocator does not publish a head or validate a next link.
Directly allocated, unlinked nodes also consume capacity. For insert-only
experiments, every allocated node is reachable from exactly one bucket.

## Stage C — Capacity and reset

For an independent fixture, initialize and insert keys `0,15,...,135`
with data `0,1,...,9`. All ten keys select bucket 0. The final head is 9,
the chain is `9→8→...→0→-1`, and the counter is 10. Every insert returns 0.
Fourteen other buckets are empty even though no node capacity remains.

A further `insert(150,10)` returns -1. The counter, all heads, and every
node field must match the saved snapshot. The allocator checks capacity
before changing the counter or writing a node; insertion publishes the
new head only after successful allocation. A failed direct `new_hnode`
call also preserves state.

`initialize()` now sets all heads to -1 and the counter to 0. All old
`key/data/next` fields remain unchanged, as do `nums` and `answer`. Old
node references no longer designate active entries. A second reset has
the same result. `insert(7,70)` then uses node 0, overwrites its three
fields, and returns 0. There is no free chain to reconstruct or recycle.
Initialization visits the bucket array, not the old linked chains.

## Stage D — Key/value roles in two sum

A result contains two input positions. With the supplied array, target 0
first succeeds at `i=5,j=4`, where `nums[4]=-1` and `nums[5]=1`.
Both methods return `{4,5}`. The ordering is `{j,i}`, with `j<i`.
A complete miss produces `{-1,-1}`. Ten values have 45 unordered pairs.
The largest distinct-position sum here is `16+8=24`, so target 100 misses.

`two_sum_bf` scans increasing `i`, then `j=i-1` down to 0. Before `i=5`,
it performs `0+1+2+3+4=10` pair comparisons. Its first comparison at
`i=5` succeeds, so target 0 takes 11 comparisons, not 15. Brute force
changes `answer` but does not initialize or otherwise change hash storage.

The operation `insert(nums[i],i)` uses the input value as key and its
position as associated data. For input index 1, those are key -8, data 1,
and bucket 7. `find(complement)` compares stored keys and returns a node
index; `hnodes[node].data` then retrieves the earlier input index.

At the start of iteration `i`, every stored position is less than `i`.
The function searches before inserting the current position, so a match
cannot reuse `i`. Inserting first could incorrectly pair the single value
1 at position 5 with itself for target 2. The actual first valid target-2
pair is `{3,7}`, containing -2 and 4.

| `i` | Current value | Complement for target 0 | Lookup bucket | Lookup result | Action |
| ---: | ---: | ---: | ---: | --- | --- |
| 0 | -16 | 16 | 1 | Empty | Insert key -16, data 0, in bucket 14 |
| 1 | -8 | 8 | 8 | Empty | Insert key -8, data 1, in bucket 7 |
| 2 | -4 | 4 | 4 | Empty | Insert key -4, data 2, in bucket 11 |
| 3 | -2 | 2 | 2 | Empty | Insert key -2, data 3, in bucket 13 |
| 4 | -1 | 1 | 1 | Empty | Insert key -1, data 4, in bucket 14 |
| 5 | 1 | -1 | 14 | Node 4 matches key -1 | Return `{4,5}` without inserting 5 |

The target-0 hash trace compares one stored key. The five empty searches
still do constant work. Five records remain allocated; counter 5 and
nonempty heads `7:1`, `11:2`, `13:3`, `14:4`. Bucket 14 links `4→0→-1`.

| Target | `two_sum_bf` | `two_sum_ht` |
| ---: | --- | --- |
| 0 | `{4,5}` | `{4,5}` |
| 2 | `{3,7}` | `{3,7}` |
| 3 | `{5,6}` | `{5,6}` |
| 100 | `{-1,-1}` | `{-1,-1}` |

After target 100, counter 10 and the nonempty chains are:
`1:9→5→-1`, `2:6→-1`, `4:7→-1`, `7:1→-1`, `8:8→-1`,
`11:2→-1`, `13:3→-1`, and `14:4→0→-1`.
The payload and node index coincide because fresh allocation followed the
input order. The bucket index generally differs from both. A later hash
call initializes first and allocates from node 0 again.

With `{1,1,5,0,0,0,0,0,0,0}` and target 6, both methods choose `{1,2}`.
Brute force tries `j=1` first at `i=2`, and key-1 lookup reaches the newest
key-1 node first. Exact answer agreement is appropriate for this source,
as well as asserting valid distinct indices and the requested sum. Restore
the original array afterward.

The failure result `{-1,-1}` does not distinguish a miss from insertion
failure. In the unchanged ten-number search, initialization supplies enough
slots for the run. Signed sums and differences must be representable as
`int`; the functions do not detect overflow.

## Stage E — Driver, tests, and costs

A driver includes `lab.c` once and defines `main`. Compile that driver
alone. No repository-root include path or Module 07 file is needed.
The required Make targets are `lab-compile`, `core`, and `student-tests`.
The student scaffold's smoke test is not a substitute for three original
assertion groups: hashing/chains; capacity/reset; and two sum.

A complete brute-force miss inspects `n(n-1)/2` pairs: 45 here. Head
insertion and allocation take constant work. Lookup may inspect all `k`
nodes in one chain. Reset costs `Θ(b)` for `b` bucket heads and does not
depend on the number of active nodes.

For distributed keys, expected chain length is about `n/b`, giving expected
`O(1+n/b)` lookup. Expected complete two-sum work is linear when `b=Θ(n)`
and node capacity is sufficient. All-colliding keys can make total search
quadratic. The actual source fixes ten nodes and fifteen buckets; it does
not grow. Generalized table storage is `Θ(b+p)` for `p` node slots.

Preserve initial predictions and explain corrections with exact state or
return values. Optional open addressing, Robin Hood hashing, tombstones,
dynamic allocation, growth, and individual deletion are not required lab
implementation or test tasks.
