# Chapter 9. Finding a Pair with a Hash Table

Current pool contract: `new_lnode()` takes no arguments, returns an isolated index with retained data, and initializes the pool only on first use. `save_data` checks the index, writes data/next, then publishes the bucket head. Later `init_lnodes_pool()` calls are no-ops; `init_hashtable()` recycles owned bucket chains.


The required lesson follows [lab.c](lab.c). It reuses the ten-node pool in
[Module 07's lab.c](../../module_07_linked_list/student/lab.c). Read the
supplied functions, predict their state changes, and test them with a driver.
The older dynamic table under `code/` is an optional comparison.

## Thinking Logically

### Which two numbers reach the target?

Suppose we have ten numbers and want two different positions whose numbers
add to a target. We need the positions because equal numbers at different
positions are different choices.

The supplied example uses the same array throughout this chapter:

```c
int nums[10] = {-16, -8, -4, -2, -1, 1, 2, 4, 8, 16};
int answer[2] = {-1, -1};
```

For target 0, positions 5 and 4 contain 1 and -1. Their sum is 0. The result
`answer = {5, 4}` reports positions, not the numbers themselves. The result
`{-1, -1}` reports that the function did not find a pair. In the hash-table
version, this result can also follow an exhausted node pool.

### How does checking every earlier position work?

We can take one position and compare its number with every earlier number.
The function `two_sum_bf` does exactly this. The suffix `bf` means brute
force: enumerate the candidate pairs directly.

The outer loop visits `i` from 0 through 9. The inner loop visits `j` from 0
through `i - 1`. The condition `j < i` prevents using one position twice. It
also avoids checking both orders of the same pair.

For target 0, the first successful outer position is 5. The inner loop
compares 1 with -16, -8, -4, -2, and finally -1. The function writes 5 and 4
into `answer` and returns. If no pair succeeds, it writes -1 to both result
positions after the loops.

### Can we search for one needed number instead?

When the current number is 1 and the target is 0, the needed earlier number
is -1. Subtracting the current number from the target gives that needed
number. We call the needed number the **complement**.

If earlier numbers are grouped by a repeatable calculation, we can search
only the selected group. The group must retain every earlier candidate
assigned to it. A calculation can send different numbers to the same group.
We must therefore compare complete numbers inside the group.

A **hash function** selects a group from a number. The selected group is a
**bucket**. A **hash table** combines the bucket calculation with a rule for
storing and searching the candidates in that bucket.

### How do negative numbers select a valid bucket?

The table has ten bucket positions, numbered 0 through 9. The expression
`value % 10` gives a remainder. In C, a negative value can have a negative
remainder. An array position cannot be negative.

The supplied `hash_func` adds 10 only when the remainder is negative. This
puts every result between 0 and 9.

| Number | C remainder `% 10` | `hash_func` result |
| --- | ---: | ---: |
| -16 | -6 | 4 |
| -8 | -8 | 2 |
| -4 | -4 | 6 |
| -2 | -2 | 8 |
| -1 | -1 | 9 |
| 1 | 1 | 1 |
| 2 | 2 | 2 |
| 4 | 4 | 4 |
| 8 | 8 | 8 |
| 16 | 6 | 6 |

Different numbers can select the same bucket. For example, -16 and 4 both
select bucket 4. This event is a **collision**. A shared bucket does not mean
the numbers are equal.

### Where do colliding candidates go?

Module 07 already supplied linked records with integer `next` positions.
The table uses those records to keep one linked chain per bucket. This
collision rule is called **separate chaining**.

The array `hashtable[10]` holds chain-head positions. A value of -1 means
that the bucket has no chain. A nonnegative value selects a record in
`lnodes[10]`. That record's `next` selects another record or ends at -1.
Bucket positions and node positions belong to different arrays.

Before the first allocation, call `init_lnodes_pool()`. It creates the free
chain `0 → 1 → ... → 9 → -1` and sets `free_head` to 0. The initial
`hashtable` heads are already -1. A call to `init_hashtable()` alone does
not initialize the free pool. Before `init_lnodes_pool()`, `free_head` is -1 and
`new_lnode` reports exhaustion.

For a small storage experiment, start with the fresh pool and save 12, 22,
and -8 into bucket 2, in that order. Each call puts the new node before the
old head:

```text
hashtable[2] = 2
node 2: data -8, next 1
node 1: data 22, next 0
node 0: data 12, next -1
free_head = 3
```

The function `save_data` returns the allocated node position. Its second
argument is the payload to store. Its first argument must already be a
valid bucket position. The function does not calculate a hash or check
that the bucket is in range. It does not search for duplicates or update
an existing entry. Saving 22 again adds another node.

### What does a chain search compare?

We must distinguish a stored number from a stored position. The function
`find_data(hash, data)` compares its second argument with each node's
`data` field. In the storage experiment, searching bucket 2 for 22 visits
node 2, then node 1, and returns 1. Searching that chain for 32 visits all
three nodes and returns -1.

The two-sum application uses the same nodes differently. It stores an
array position `i` as the payload. The bucket is selected by `nums[i]`.
To compare a candidate number, the application reads the stored position
`j`, then compares `nums[j]` with the complement.

For example, the first stored candidate has payload 0 because -16 is at
`nums[0]`. Its bucket is 4 because `hash_func(-16)` is 4. Calling
`find_data(4, -16)` would compare -16 with the stored position 0. It would
not perform the number comparison the application needs. For this reason,
`two_sum_ht` walks the chain itself.

### Why search before saving the current position?

At the beginning of iteration `i`, the table contains only positions less
than `i`. The function searches for `target - nums[i]` before saving `i`.
Every successful candidate therefore satisfies `j < i`. The function cannot
pair the current position with itself.

With a fresh pool, target 0 follows this sequence:

| `i` | `nums[i]` | Complement | Search bucket | Result before insertion |
| ---: | ---: | ---: | ---: | --- |
| 0 | -16 | 16 | 6 | Empty; save payload 0 in bucket 4 |
| 1 | -8 | 8 | 8 | Empty; save payload 1 in bucket 2 |
| 2 | -4 | 4 | 4 | Payload 0 gives -16; save payload 2 in bucket 6 |
| 3 | -2 | 2 | 2 | Payload 1 gives -8; save payload 3 in bucket 8 |
| 4 | -1 | 1 | 1 | Empty; save payload 4 in bucket 9 |
| 5 | 1 | -1 | 9 | Payload 4 gives -1; return `answer = {5, 4}` |

Iteration 5 does not save its current position. The successful early return
leaves five nodes in the table. The caller can inspect them or call
`init_hashtable()` to recycle them.

The two functions can return different valid pairs when several pairs
exist. Brute force visits earlier positions from oldest to newest. A chain
visits stored candidates from newest to oldest because insertion prepends.
Do not require identical result positions for every modified input. Require
two distinct valid positions with the requested sum.

For example, temporarily use `nums = {1,1,5,0,0,0,0,0,0,0}` and target 6.
Both functions first succeed at `i = 2`, where the number is 5. Brute force
chooses the older position 0, returning `{2,0}`. The chain chooses the newer
position 1, returning `{2,1}`. Both pairs add to 6. Restore the supplied
array after the experiment.

### How can another call reuse the node pool?

The table and pool are global. Nodes used by one call must become available
before another call can use them. `two_sum_ht` begins by calling
`init_hashtable()`.

For each nonempty bucket, `init_hashtable` passes its head to
`free_lnode_chunk`. That function follows the chain to its tail. It connects
the tail to the existing free chain and makes the supplied head the new
`free_head`. Then `init_hashtable` sets that bucket head to -1.

Recycling changes links. It does not clear old payloads. A recycled node is
available because it belongs to the free chain, not because its data is 0.
The next allocation overwrites its payload and `next`.

Every active chain must be valid, acyclic, and disjoint from the free chain
and the other active chains. Do not recycle one chain twice. The helper
`free_lnode_chunk` does not clear a bucket head itself. Resetting the pool
with `init_lnodes_pool()` while buckets still point into it would make those
nodes both available and active. Clear the table before deliberately
reinitializing an otherwise unused pool.

If `new_lnode` finds `free_head == -1`, it returns -1 without changing the
pool. `save_data` then returns -1 without changing the bucket head. In
`two_sum_ht`, this failure breaks the loop and produces `{-1, -1}`. The
result does not distinguish exhaustion from a completed unsuccessful
search. Give the table exclusive use of all ten nodes for a complete run
on the ten supplied numbers.

## Calculating Efficiency

### How many pairs does brute force inspect?

A complete unsuccessful run compares 0 earlier candidates at position 0,
then 1, then 2, through 9. The sum is 45 comparisons. Target 0 succeeds at
position 5 after `0 + 1 + 2 + 3 + 4 + 5 = 15` comparisons.

If the same method were generalized to `n` numbers, the complete count
would be `n(n - 1) / 2`. Doubling the input makes the dominant pair count
about four times as large. We describe this growth as `O(n^2)` time. The
function uses a fixed number of local variables, so its extra space is
`O(1)`.

### How much work does a selected chain require?

Hashing a number takes one remainder and a possible addition. Prepending an
available node changes a fixed number of fields. Both require `O(1)` work.
A search in a chain with `k` candidates can compare all `k` candidates. Its
worst-case cost is `O(k)`.

For the target-0 trace, chain searches compare only three candidate numbers:
-16 at iteration 2, -8 at iteration 3, and -1 at iteration 5. Empty buckets
compare no candidates. This count is evidence for this input, not a bound
for every input.

If `n` records spread across `b` buckets, expected chain length is about
`n / b`. With suitable distribution, expected search work is `O(1 + n/b)`.
When a generalized design increases `b` along with `n`, chain lengths can
stay bounded and the complete two-sum scan has expected `O(n)` work. This
source keeps exactly ten buckets and ten nodes. It does not grow either
array. Holding ten buckets fixed while increasing the input does not
justify an unconditional expected linear-time claim.

If many candidates collide, the successive searches can inspect a growing
chain. A generalized two-sum run can then take `O(n^2)` time. The remainder
function alone gives no guarantee that inputs spread evenly.

### What does clearing the table cost?

Clearing visits all ten bucket positions and follows every active node once
while finding chain tails. With `b` buckets and `s` active nodes, this work
is `O(b + s)`. Clearing is separate from the per-candidate hash calculation
and prepend costs. Each `two_sum_ht` call includes clearing at entry.

The exact program reserves ten bucket integers and ten linked records. It
uses no dynamic allocation. In a generalized design with `b` buckets and
room for `n` nodes, table storage is `O(b + n)`. The array `nums` and result
array are separate from the table representation.

## Glossary

We can now attach names to the operations already traced.

| Term | Meaning in this lesson |
| --- | --- |
| Two-sum | Find distinct positions whose numbers add to a target |
| Brute force | Enumerate every earlier candidate pair |
| Complement | The number `target - nums[i]` needed by the current position |
| Hash function | Repeatable calculation selecting bucket 0–9 |
| Bucket | One chain-head position in `hashtable` |
| Collision | Different numbers select the same bucket |
| Separate chaining | Keep colliding candidates in that bucket's linked chain |
| Payload | The integer stored in a node's `data` field |
| Free chain | Nodes currently available, beginning at `free_head` |
| Pool exhaustion | No available node; `free_head == -1` |
| Expected cost | Work estimated under stated input-distribution assumptions |
| Worst-case cost | Greatest work among the inputs allowed by the assumptions |

## Coding Plan

Use the source to explain each action before testing it.

1. Initialize the unused node pool once with `init_lnodes_pool()`.
2. Trace `hash_func` on negative and positive numbers.
3. Trace `save_data` through allocation, next-link assignment, and head update.
4. Trace `find_data` through payload comparisons and the -1 stopping marker.
5. Trace `free_lnode_chunk` and `init_hashtable` through chain recycling.
6. Trace `two_sum_bf` in `i` then `j` order.
7. Trace `two_sum_ht` through complement lookup before current-index storage.
8. Write a driver that asserts results, chains, reset behavior, and exhaustion.

The implementation is supplied. There are no required rehashing,
dynamic-allocation, or individual-deletion implementation tasks.

## C Code

The excerpts below use the exact names and operations from `lab.c`.

### Normalize the bucket calculation

We need a nonnegative bucket for signed numbers. The supplied calculation
normalizes only negative remainders.

```c
int hash_func(int value) {
    int hash = value % 10;
    if (hash >= 0) {
        return hash;
    }
    else {
        return hash + 10;
    }
}
```

### Allocate before publishing the new head

The bucket head must keep its old value when allocation fails. The supplied
function updates the head only after `new_lnode` succeeds.

```c
int save_data(int hash, int data) {
    int node = new_lnode();
    if (node == -1) {
        return -1;
    }
    lnodes[node].data = data;
    lnodes[node].next = hashtable[hash];
    hashtable[hash] = node;
    return node;
}
```

The caller must pass `0 <= hash && hash < 10`. Every linked node position
must be between 0 and 9, with -1 used only as an ending marker.

### Search stored payloads

A chain ends when its current position is -1. Check that marker before
indexing `lnodes`.

```c
int find_data(int hash, int data) {
    int node = hashtable[hash];
    while (node != -1) {
        if (lnodes[node].data == data) {
            return node;
        }
        node = lnodes[node].next;
    }
    return -1;
}
```

### Recycle a complete chain

A valid chain can become the beginning of the free chain. The caller then
clears the old bucket head.

```c
void free_lnode_chunk(int head) {
    if (head == -1) {
        return;
    }
    int tail = head;
    while (lnodes[tail].next != -1) {
        tail = lnodes[tail].next;
    }
    lnodes[tail].next = free_head;
    free_head = head;
}

void init_hashtable() {
    for (int i = 0; i < 10; i++) {
        if (hashtable[i] != -1) {
            free_lnode_chunk(hashtable[i]);
            hashtable[i] = -1;
        }
    }
}
```

### Compare earlier positions directly

The nested loops inspect each unordered pair once and publish the first
successful pair in their iteration order.

```c
void two_sum_bf(int target) {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < i; j++) {
            if (nums[i] + nums[j] == target) {
                answer[0] = i;
                answer[1] = j;
                return;
            }
        }
    }
    answer[0] = answer[1] = -1;
}
```

### Find the complement before storing the current position

The table stores earlier positions. The comparison reads the number at each
stored position.

```c
void two_sum_ht(int target) {
    init_hashtable();
    for (int i = 0; i < 10; i++) {
        int j_num = target - nums[i];
        int j_node = hashtable[hash_func(j_num)];
        while (j_node != -1) {
            int j = lnodes[j_node].data;
            if (nums[j] == j_num) {
                answer[0] = i;
                answer[1] = j;
                return;
            }
            j_node = lnodes[j_node].next;
        }
        int i_node = save_data(hash_func(nums[i]), i);
        if (i_node == -1) {
            break;
        }
    }
    answer[0] = answer[1] = -1;
}
```

The supplied numbers and targets 0 and 100 keep all arithmetic within
`int`. For other experiments, choose inputs so every evaluated
`nums[i] + nums[j]` and `target - nums[i]` is representable as `int`.
The functions do not check signed overflow.

`lab.c` has no `main`. Include it once in a separate driver and compile the
driver with the repository root on the include path. See [lab.md](lab.md)
for the exact command and submission requirements.
