# Module 09 Lesson Plan — Chained Hashing and Two Sum

## Source and learning goals

Teach [student/lab.c](../student/lab.c), a self-contained table with ten
`hnode` records and fifteen bucket heads. Students trace supplied code and
write an assertion driver. Use the concept and code PPT materials as
references; keep current lab names, capacities, and loop order in examples.
There is no Module 07 source dependency or shared free list.

Students should calculate signed hashes, distinguish keys from associated
data and indices, follow collision chains, explain allocation failure and
reset, and justify searching before storing in two sum. They should count
work before making conditional expected-cost claims.

## Prerequisite retrieval and PPT bridge

Retrieve array indexing, `%`, integer `next` links, and the `-1` marker.
Ask how a direct-address table could store positions for `{2,5,6}`. Then
introduce negative and large keys: hashing maps them to a bounded bucket,
and chains preserve distinct keys that collide. A bucket match still needs
a key equality test.

The PPT code's five nodes and seven buckets are smaller examples of this
same representation. Map `size→hnodes_unused`, `htable→hashtable`,
`arr→nums`, and `ans→answer`. The lab's inner brute-force loop descends
through earlier positions, unlike the PPT's ascending loop. Briefly discuss
open addressing and Robin Hood hashing from the concept PPT after students
can explain separate chaining; those alternatives are not coding tasks.

## Delivery within 180 minutes

| Minutes | Work | Evidence retained |
| --- | --- | --- |
| 0–15 | Stage A: find one value by scanning an array, then use its value as a direct table index | Initial lookup method and table contents |
| 15–35 | Stage B: limits of direct addressing, signed hashing, key/data/next nodes, fifteen heads | Three Cognitive Pause predictions |
| 35–65 | Stage C: trace `insert(12,120)`, `insert(27,270)`, `insert(-3,-30)` and key lookup | Heads, nodes, counter, and visited nodes |
| 65–85 | Trace duplicate keys, ten-node capacity, failed insertion, and reset | Before/after state and return-value explanation |
| 85–95 | Break and retrieval | Explain bucket index versus node index versus data |
| 95–120 | Stage D: apply familiar table operations to two sum; compare both methods at targets 0 and 100 | Input/value/key/data trace and ordered answers |
| 120–160 | Stage E: compile the supplied source through a driver; write three original test groups | Commands, assertions, compiler output |
| 160–175 | Correct predictions and explain expected/worst work; compare collision strategies | Visible corrections and cost assumptions |
| 175–180 | Submit one evidence package | Driver and evidence record |

Keep the release sequence A → B → C → D → E. Preserve each prediction
before revealing the corresponding result. Accept spatial or linear traces;
the linear worksheet has the same evidence burden.

## Board sequence

Start with the array `{2,5,6}` and ask where 5 occurs. A linear scan
compares 2, then 5, and returns input position 1. Looking for absent 3
requires all three comparisons. Ask whether a table could retain those
positions so another lookup need not repeat the scan.

Build the seven-position direct-address table
`{-1,-1,0,-1,-1,1,2}`. Read `table[5]=1` and `table[3]=-1`, then ask
how to handle a negative key or a very large sparse key range. Introduce a
repeatable mapping into fifteen buckets, signed normalization, and collision
chains. Complete insertion and key lookup before introducing a pair problem.

Show `hnodes[10]` separately from `hashtable[15]`. Explain that global
bucket heads initially contain zero, so manual experiments must begin with
`initialize()`. The function writes fifteen `-1` heads and sets
`hnodes_unused=0`. It does not clear old node fields.

Calculate `hash_func(12)=hash_func(27)=hash_func(-3)=12`. After inserting
`(12,120)`, `(27,270)`, and `(-3,-30)`, bucket 12 has head 2 and chain
`2→1→0→-1`. The corresponding keys are `-3,27,12`; associated data is
`-30,270,120`. Each `insert` returns 0, even though the allocated indices
are 0, 1, and 2. `hnodes_unused` becomes 3.

Trace `find(12)` through nodes `2,1,0` and `find(42)` through the same
three nodes to a miss. `find(120)` does not retrieve the node whose data
is 120. Insert `(27,271)`: node 3 becomes the head and `find(27)` returns
3 with data 271. The old node remains allocated; this is duplicate-key
insertion rather than a map update.

Once the table operations are understood, introduce two sum as an
application. First trace `two_sum_bf`: for each increasing `i`, visit
`j=i-1,i-2,...,0`. A complete ten-number miss checks 45 pairs. For target 0,
the first success is at `i=5,j=4`, so the count is `0+1+2+3+4+1=11` and
the answer is `{4,5}`. Positions are returned, not the values `{-1,1}`.
Then store each earlier number as a key and its input position as data.

| Expression | Meaning |
| --- | --- |
| `hash_func(nums[i])` | Bucket selected by the current key |
| `hashtable[bucket]` | First node index, or `-1` |
| `hnodes[node].key` in two sum | Earlier input value |
| `hnodes[node].data` in two sum | Earlier input index `j` |
| `hnodes[node].next` | Next node index, or `-1` |

For target 0, `i=5` has value 1 and needs key -1. Bucket 14 begins at node
4, whose key is -1 and data is 4. `find(-1)` returns node 4; `two_sum_ht`
then stores `{4,5}`. Earlier -16 is in the same bucket at node 0, but the
match stops the search before that node. Only five nodes have been used;
position 5 has not been inserted.

For target 100, all ten lookups miss and all ten input indices are stored.
Both methods report `{-1,-1}`. The hash version ends with
`hnodes_unused=10`. A later `two_sum_ht(0)` calls `initialize()` at entry
and starts allocation from node 0 again. No old links need traversal.
Initialization retains the previous `answer`; the pair-search function writes
its new result when it returns a match or completes a miss.

## Driver and test coaching

A driver beside `student/lab.c` includes `"lab.c"` and defines `main`.
Compile the driver alone from the repository root:

```sh
cc -std=c11 -Wall -Wextra -Wpedantic \
  module_09_hash_table/student/lab_driver.c -o /tmp/module09_lab_driver
/tmp/module09_lab_driver
```

The include is relative to the driver. There is no imported Module 07
source requiring a repository-root include path.

Require three original assertion groups:

1. Signed hashes, exact collision-chain state, key/data distinction,
   present/missing lookup, and duplicate-key behavior.
2. Ten successful allocations, unchanged state on the eleventh failed
   insertion, reset of all heads and the counter, retained old node fields,
   and successful reuse from node 0.
3. Both two-sum methods, ordered results, misses, repeated calls, duplicate
   values, and a fixture exposing reuse of the current index.

Both methods choose the greatest matching earlier `j` at their first
successful `i`: brute force descends through `j`, and chains prepend newer
entries. For `{1,1,5,0,0,0,0,0,0,0}` with target 6, both return `{1,2}`.
Assert exact agreement for this source, together with `0<=j<i<NUMS_SIZE`
and the target sum. Restore `nums` after custom tests.

Keep all evaluated sums and complement subtractions representable as
`int`. Low-level `new_hnode` does not validate its next-link argument;
manual edits must preserve valid, acyclic chains. Keep the user-owned lab
and all PPT sources unchanged.

## Feedback and assessment

Ask students to identify the two distinct checks: `find` compares a stored
key with the complement, then its caller reads the matching node's data as
an index. A student comparing data with the complement has confused the
search key with the associated result.

Require the invariant: at iteration entry, every table entry represents an
input position less than `i`. Lookup before insertion guarantees different
positions. Hash equality alone cannot establish value equality.

A lookup can traverse an entire chain. With `n` entries and `b` buckets,
adequate distribution gives expected `O(1+n/b)` lookup. With `b=Θ(n)` and
sufficient node capacity, expected complete two-sum work is `O(n)` including
`Θ(b)` initialization. All-colliding candidates can require `O(n²)` work.
The exact source fixes ten nodes and fifteen buckets and never grows.

The legacy open-addressing library and tombstone autopsy remain optional
comparisons, not substitutes for the source-based Stage E assignment.
