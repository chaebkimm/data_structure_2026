# Chapter 9. Storing and Finding Data by Key

Each item in an array has an assigned number, so we can find data by that number. Giving those numbers meaning and using them as keys lets us easily find the data we want by its meaning.

## Thinking logically

### How do we find a value in memory?

A simple method is to read all the data one item at a time from the beginning and check whether each item is the value we want. If the value is present, we can find where it is; if it is absent, we can determine that it is not there.

### How can we find it more easily?

Create a table with a slot for every possible value and record where each stored value is located. Then use the value as the table’s index and check only the slot for the value you want. If the value is present, we can find where it is; if it is absent, we can determine that it is not there.

### What if the range of values is wide?

If the range of values exceeds the table’s capacity, we can perform an appropriate calculation on the value to obtain an index that fits the table. Since the index and the value are now different, we must also record the value in the table to tell whether the information belongs to the value we want.

### What if different values have the same index?

Store values with the same index in a list in that table entry. A linked list is suitable because the list’s size is difficult to know in advance. To find a value, we only need to check the list at its index.

### What other solutions are there?

When storing a value, if the slot at its index is occupied, we can follow a predetermined rule to move to another empty slot. To find a value, start at the slot for its index and follow the same rule. If a slot is empty, we know the value is absent.

### How can we find two numbers whose sum equals the target?

Let us find two numbers stored in memory whose sum equals a target value. The simplest approach is brute force: check every possibility. Adding each number to every other number checks all possible pairs. Since addition gives the same result regardless of order, we only need to add each number to those we have already seen.

### Which number should we look for at each step?

To reach the target when added to the current number, the number we need is the target minus the current number. Instead of adding the current number to each number we have already seen, we only need to check whether this needed value is among them.

### How can we use a table to find the number?

Store the numbers we have already seen in a table. Read the numbers one at a time, look up the target minus the current number in the table, and add the current number to the table if no match is found. Checking only the corresponding table entry for each number makes the search faster.

## Calculating Efficiency

### How much time does searching one item at a time take?

When the value we want is stored, we find it after reading about half of all the data on average. When it is absent, we always have to check every item. Therefore, the time needed to search grows in proportion to the number of items.

### What does searching with a table cost?

A table with a slot for every possible value lets us check just the slot for that value, so lookup takes a fixed amount of time regardless of the number of stored items. However, the wider the range of values, the more memory is needed, regardless of how many items are actually stored.

### What happens when many values have the same index?

Calculating an index from each value allows a table with smaller capacity, but different values can receive the same index. If the table has enough capacity and indices are distributed evenly, few values share an index, so lookup still takes nearly a fixed amount of time regardless of the number of stored items. As more values share an index, more data must be checked. In the worst case, when all values receive the same index, the time cost is the same as reading the data one item at a time.

### What does finding two numbers whose sum equals the target cost?

Brute force adds each number to all numbers already seen, so the time grows in proportion to the square of the number of inputs. It needs almost no additional memory. With a table, if indices are distributed evenly, we check only the table entry for each number’s partner, so the time grows in proportion to the number of inputs. This requires memory for a table with capacity proportional to the number of inputs.

## Glossary

### Key

A value used to find data.

### Direct-address table

A table with a slot for every possible value, using each value itself as its index.

### Hashing

Applying a calculation to any given data to obtain a result within a fixed range.

### Hash function

A function that calculates a result within a fixed range from data.

### Hash value

The result of applying a hash function to data.

### Hash table

A table that uses hash values as indices to store and find data.

### Bucket

A cell in a hash table, also called a slot.

### Collision

Different values receiving the same index.

### Chaining

A way to resolve collisions by keeping the values in a linked list stored in the table.

### Open addressing

A way to resolve collisions by following a predetermined rule to move to another empty slot. Checking slots along the way is called probing.

### Brute force

Checking every possible case.

## Invariant

### What rules must a hash function used in a hash table follow?

A hash function used in a hash table returns an index that fits that table. It also always returns the same result for the same data.

### What do these rules guarantee?

A hash value is an index that fits the table, so its corresponding slot always exists. The same data always has the same hash value, so stored data can be found again using that hash value.

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
