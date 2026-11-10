# Chapter 9. Storing and Finding Data with a Hash Table

Begin with array search and direct addressing, then build a hash table that
stores and finds keys despite collisions. Use two sum as an application
after the table operations are understood. The required lesson follows
[lab.c](lab.c): read the supplied functions, predict their state changes,
and test them with a separate driver. The source is self-contained: it owns ten hash nodes and fifteen bucket heads. It does
not import Module 07's linked-list pool.

This chapter uses the supplied lab's constants, names, signed input,
failure checks, and loop order throughout its examples and assertions.

## Thinking Logically

### How can we find a value in an array?

Start with an array containing `{2,5,6}` and ask where the value 5 occurs.
Read the entries in order and compare each complete value with 5. The match
at input position 1 supplies the answer. If we search for a value absent
from the array, every entry must be checked before reporting a miss.

This direct scan is a simple starting point. Repeated searches repeat the
comparisons. Could a small table remember where each value was found?

### What is a direct-address table?

When stored values can serve as array indices, put each value's original
input position at the table index equal to that value. For `{2,5,6}`, use
seven table positions numbered 0 through 6:

| Table index | 0 | 1 | 2 | 3 | 4 | 5 | 6 |
| --- | ---: | ---: | ---: | ---: | ---: | ---: | ---: |
| Stored input position | -1 | -1 | 0 | -1 | -1 | 1 | 2 |

Now looking for 5 reads `table[5] == 1`. Looking for 3 reads -1, the marker
for an absent value. The table stores input positions, while its indices
represent the values being searched. This is **direct addressing**.

### Why use a hash function instead of direct addressing?

A negative value cannot directly index the table. A very large value would
also require a large table even if only a few values were stored. The table
size would depend on the key range rather than the number of stored items.

A **hash function** maps each key into a fixed table-index range. Equal keys
always select the same position. We call a selected position a **bucket**.
Different keys can select the same bucket, so the bucket alone cannot prove
that a requested key is present. That event is a **collision**. We will keep
all candidates assigned to the bucket and compare their complete keys.

A **hash table** combines this bucket calculation with a representation for
storing keys and their associated data, plus operations to insert and find
them. The calculation selects candidates; complete-key comparison decides
whether the requested key is present.

### How do negative keys select a valid bucket?

`NODES_CAPACITY` is 10. `TABLE_CAPACITY = NODES_CAPACITY * 3 / 2` is 15.
The fifteen buckets are numbered 0 through 14. C can produce a negative
remainder for a negative dividend. `hash_func` adds `TABLE_CAPACITY` only
when the remainder is negative.

| Key | C remainder `% 15` | Bucket |
| --- | ---: | ---: |
| -16 | -1 | 14 |
| -8 | -8 | 7 |
| -4 | -4 | 11 |
| -2 | -2 | 13 |
| -1 | -1 | 14 |
| 1 | 1 | 1 |
| 2 | 2 | 2 |
| 4 | 4 | 4 |
| 8 | 8 | 8 |
| 16 | 1 | 1 |

-16 and -1 collide in bucket 14; 1 and 16 collide in bucket 1. Equality of
buckets does not imply equality of keys. A negative multiple of 15 already
has remainder 0 and needs no adjustment.

### Where do colliding keys go?

Each `struct hnode` stores `key`, `data`, and `next`. A bucket head in
`hashtable` selects a node in `hnodes`; `next` selects another node or ends
at -1. This collision rule is **separate chaining**. The nodes live in an
array but form linked chains through integer indices.

The bucket array and node array have different capacities and roles.
`hashtable[14]` is valid; `hnodes[14]` is not. A bucket stores a node index,
not the key or payload itself.

`initialize()` sets `hnodes_unused` to 0 and every bucket head to -1.
Call it before a standalone insertion or lookup experiment. Global bucket
heads initially contain zero by C static-storage rules, which is not the
empty marker.
`new_hnode(key,data,next)` takes the next unused slot, writes all three
fields, and returns its index. `hnodes_unused` is the number of allocated
slots and the next slot index while capacity remains. There is no free
list or individual deletion. `insert(k,d)` hashes the key, allocates a
node linked to the old head, and publishes the new head only on success.
It returns 0 on success and -1 on exhaustion; it does not return a node index.

After initialization, call `insert(12,120)`, `insert(27,270)`, and
`insert(-3,-30)`. All three keys select bucket 12:

```text
hashtable[12] = 2
node 2: key -3, data -30, next 1
node 1: key 27, data 270, next 0
node 0: key 12, data 120, next -1
hnodes_unused = 3
```

New nodes go at the front. `find(27)` visits node 2, then node 1, compares
`key`, and returns 1. The payload is `hnodes[1].data == 270`.
`find(42)` visits nodes 2, 1, and 0, then returns -1. Although 42 also hashes
to 12, no stored key is 42. `find(120)` must not match the payload 120.

Inserting `(27,999)` adds node 3 rather than updating node 1. Both nodes
remain in the chain; `find(27)` returns the newest match, node 3.

### What other collision rules can we use?

Open addressing stores entries in the table array itself and follows a
probing rule when a position is occupied. Robin Hood hashing can move an
entry aside for one that has traveled farther from its home bucket, reducing
variation in probe distances. These are alternative collision strategies.
The required source uses separate chains; it has no probing, Robin Hood
moves, deletion, or resizing. The older open-addressed library under `code/`
is optional enrichment with its own API and tests.

### Which two positions reach the target?

Now apply the table to a new task: find a pair of input positions. The table
operations are already familiar; two sum gives them a useful application.

Suppose we have ten numbers and want two different positions whose numbers
add to a target. Positions matter: equal values at different positions are
different choices. The supplied array is:

```c
int nums[NUMS_SIZE] = {-16, -8, -4, -2, -1, 1, 2, 4, 8, 16};
int answer[2] = {-1, -1};
```

For target 0, positions 4 and 5 contain -1 and 1. Both supplied functions
return `answer = {4, 5}`: earlier position `j` first, current position `i`
second. `{-1, -1}` means no pair was reported.

### How does checking every earlier position work?

`two_sum_bf` uses brute force: enumerate candidate pairs directly. Its outer
loop visits `i` from 0 through `NUMS_SIZE - 1`. Its inner loop visits `j`
from `i - 1` down to 0. At `i = 0` there are no earlier positions.
The condition `j < i` prevents reusing one position and avoids checking both
orders of the same pair.

For target 0, iterations 0 through 4 make `0+1+2+3+4 = 10` comparisons
without success. At `i = 5`, the first comparison uses `j = 4`:
`nums[5] + nums[4] == 0`. The function writes `{4,5}` and returns.
A complete miss writes -1 to both result positions after the loops.

### How do keys and payloads help two sum?

At input position `i`, the needed earlier number is `target - nums[i]`.
This is the **complement**. Store `nums[i]` as the node's key and `i` as
its data. Then `find(complement)` compares the needed number with stored
keys. On success, its returned node index selects `hnodes[node].data`,
the earlier input position `j`.

For example, the first inserted record has key -16, data 0, node index 0,
and bucket 14. These four numbers have different meanings. A search for
-16 returns the node index 0; the payload then identifies `nums[0]`.

### Why search before inserting the current position?

At the beginning of iteration `i`, all table records represent positions
less than `i`. Search for the complement before inserting the current key
and index. A match therefore satisfies `j < i`, so the current position
cannot pair with itself.

For target 0, `two_sum_ht` follows this sequence after its automatic reset:

| `i` | `nums[i]` | Complement | Search bucket | Result before insertion |
| ---: | ---: | ---: | ---: | --- |
| 0 | -16 | 16 | 1 | Empty; insert `(-16,0)` in bucket 14 |
| 1 | -8 | 8 | 8 | Empty; insert `(-8,1)` in bucket 7 |
| 2 | -4 | 4 | 4 | Empty; insert `(-4,2)` in bucket 11 |
| 3 | -2 | 2 | 2 | Empty; insert `(-2,3)` in bucket 13 |
| 4 | -1 | 1 | 1 | Empty; insert `(-1,4)` at the head of bucket 14 |
| 5 | 1 | -1 | 14 | Node 4 has key -1 and data 4; return `{4,5}` |

Position 5 is not inserted. Five allocated nodes remain available for
inspection and `hnodes_unused == 5`. Bucket 14 has chain `4 → 0 → -1`.

Both supplied algorithms visit outer positions in ascending order and
prefer the most recent matching earlier position. Brute force decrements
`j`; chain insertion prepends, so `find` encounters the newest matching
key first. With safe arithmetic and sufficient capacity, they return the
same first pair, even with duplicate values. Temporarily using
`{1,1,5,0,0,0,0,0,0,0}` and target 6 gives `{1,2}` in both methods.
Restore the original array after a custom test.

### How does reset make storage available again?

`initialize()` resets the allocation counter and all fifteen bucket heads.
It does not traverse old chains or clear node fields, `nums`, or `answer`.
Old node indices cease to identify active entries; later allocations
reuse slots from 0 and overwrite all three fields.

After ten successful insertions, `hnodes_unused == NODES_CAPACITY`.
The next `new_hnode` returns -1 without changing state. `insert` propagates
-1 and keeps the old bucket head. A table can exhaust its ten nodes while
many of its fifteen buckets are still empty. Reset the whole table before
reusing the slots; resetting only the counter would leave stale heads.

`two_sum_ht` begins every call with `initialize()`. A target-100 miss stores
all ten inputs and returns `{-1,-1}`. A following target-0 call starts again
at slot 0 and returns `{4,5}` without a manual reset. Its insertion-failure
branch also reports `{-1,-1}`, but the normal fixed ten-input run cannot
exhaust capacity before processing the input: it inserts at most ten nodes.

## Calculating Efficiency

### How many pairs does brute force inspect?

A complete miss checks `0+1+...+9 = 45` pairs. Target 0 checks 11 pairs:
10 before `i=5`, then one successful comparison with `j=4`.
For generalized input length `n`, the complete pair count is
`n(n-1)/2`, so worst-case time is `O(n^2)`. Extra space is `O(1)`.

### How much work does a selected chain require?

Hash calculation and head insertion each take constant work when a slot
is available. Searching a chain of `k` nodes can require `k` key comparisons;
including empty-chain overhead its cost is `O(1+k)`.
The target-0 hash trace compares just one key, at iteration 5. The other
five searches encounter empty buckets. This is an observed count for this
input, not a guarantee for all inputs.

For `n` entries and `b` buckets, adequate distribution gives expected lookup
cost `O(1+n/b)`. A generalized two-sum design has expected `O(n)` total work
when `b=Θ(n)`, distribution keeps expected chain lengths bounded, and node
capacity is sufficient. Long collision chains can produce `O(n^2)` total
search work. Holding fifteen buckets fixed while increasing input length
does not preserve an unconditional expected linear bound.

### What does initialization cost?

`initialize()` visits all bucket heads, but no node chains: `Θ(b)` time
for `b` buckets, regardless of the number of old nodes. Every hash two-sum
call includes this reset. The fixed source reserves fifteen bucket integers
and ten records with three integer fields. A generalized representation
uses `O(b+n)` table space and no dynamic allocation in this design.

## Glossary

| Term | Meaning in this lesson |
| --- | --- |
| Direct addressing | Use the value itself as a table index when its range permits |
| Key | Stored number used for hashing and equality |
| Payload | Associated `data`; an input position in two sum |
| Complement | Needed key `target - nums[i]` |
| Bucket | One chain-head position, numbered 0–14 |
| Node index | Position 0–9 in `hnodes` |
| Collision | Different keys select the same bucket |
| Separate chaining | Keep colliding records in a linked chain |
| Allocation counter | `hnodes_unused`; counts allocated slots |
| Exhaustion | All ten node slots have been allocated since reset |
| Expected cost | Work under stated distribution and load assumptions |
| Worst-case cost | Greatest work among the allowed inputs |

## Coding Plan

1. Relate direct addressing to hashed bucket selection.
2. Read the capacity constants and normalize signed remainders.
3. Trace `initialize` and `new_hnode` before using table operations.
4. Trace `insert` through allocation, failure check, and head publication.
5. Trace `find` through key comparisons and the -1 ending marker.
6. Trace `two_sum_bf` with descending `j` and result order `{j,i}`.
7. Trace `two_sum_ht` through complement lookup before insertion.
8. Assert chains, duplicate keys, exhaustion, reset, and repeated pair searches.

The implementation is supplied; students write a driver. Keep the supplied
`lab.c` unchanged. There are no required dynamic-allocation,
individual-deletion, or rehashing implementation tasks.

## C Code

The excerpts below reproduce the current lab's declarations and operations.

### Declare the node array and allocate a slot

```c
/* NODES_CAPACITY > 0 */
enum { NODES_CAPACITY = 10, TABLE_CAPACITY = NODES_CAPACITY * 3 / 2 };

struct hnode {
	int key;
	int data;
	int next;
};
struct hnode hnodes[NODES_CAPACITY];
int hnodes_unused = 0;

int new_hnode(int _key, int _data, int _next) {
	if (hnodes_unused >= NODES_CAPACITY) {
		return -1;
	}
	int i = hnodes_unused++;
	hnodes[i].key = _key;
	hnodes[i].data = _data;
	hnodes[i].next = _next;
	return i;
}
```

`new_hnode` returns a node index, while `insert` below returns a status.
The low-level allocator writes the supplied link; table insertion supplies
a valid old head. Use table operations for active bucket chains.

### Normalize the hash and initialize all bucket heads

```c
int hash_func(int key) {
	int hash = key % TABLE_CAPACITY;
	if (hash < 0) {
		hash += TABLE_CAPACITY;
	}
	return hash;
}

int hashtable[TABLE_CAPACITY];

void initialize(void) {
	hnodes_unused = 0;
	for (int i = 0; i < TABLE_CAPACITY; i++) {
		hashtable[i] = -1;
	}
}
```

### Insert by key and search by key

```c
int insert(int k, int d) {
	int hash = hash_func(k);
	int old_head = hashtable[hash];
	int node = new_hnode(k, d, old_head);
	if (node == -1) {
		return -1;
	}
	hashtable[hash] = node;
	return 0;
}

int find(int k) {
	int hash = hash_func(k);
	int node = hashtable[hash];
	while (node != -1) {
		if (hnodes[node].key == k) {
			return node;
		}
		node = hnodes[node].next;
	}
	return -1;
}
```

Check the -1 marker before indexing `hnodes`. `find` returns a node index,
so read its `data` separately when the associated payload is needed.

### Compare earlier positions directly

```c
enum { NUMS_SIZE = NODES_CAPACITY };

int nums[NUMS_SIZE] = {-16, -8, -4, -2, -1, 1, 2, 4, 8, 16};
int answer[2] = {-1, -1};

void two_sum_bf(int target) {
	for (int i = 0; i < NUMS_SIZE; i++) {
		for (int j = i - 1; j >= 0; j--) {
			if (nums[i] + nums[j] == target) {
				answer[0] = j;
				answer[1] = i;
				return;
			}
		}
	}
	answer[0] = answer[1] = -1;
}
```

### Find the complement before inserting the current position

```c
void two_sum_ht(int target) {
	initialize();
	for (int i = 0; i < NUMS_SIZE; i++) {
		int complement = target - nums[i];
		int node = find(complement);
		if (node != -1) {
			int j = hnodes[node].data;
			answer[0] = j;
			answer[1] = i;
			return;
		}
		if (insert(nums[i], i) == -1) {
			break;
		}
	}
	answer[0] = answer[1] = -1;
}
```

Choose experimental values so every evaluated sum `nums[i] + nums[j]` and
subtraction `target - nums[i]` fits in `int`; the code does not check signed
overflow. Hashing alone supports every `int` key, including negative values.
`lab.c` has no `main`. Include it once in a separate driver and compile only
the driver. See [lab.md](lab.md) for commands and submission requirements.
