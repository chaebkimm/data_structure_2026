# Chapter 11. Binary Heaps

In a priority queue stored in sorted order, the next value is easy to take out. Putting a new value at the front can move every value already waiting. We will use a tree to keep the next value ready while moving only the values along a single path. Then we will turn a tree of unsorted values into a heap and use it to sort integers.

## Thinking logically

### How much order does a priority queue need?

Sorting orders every pair of values, but we only need the highest-priority value at the root. Give each parent at least as much priority as either child. Following parents from any value to the root can only maintain or raise the priority. The root therefore has the highest priority, and siblings may be in either order.

### Where does the next leaf go?

Fill one level before starting the next, and fill each level from left to right. Once the root has two children, the next leaf goes under the left child, on its left.

### How does a value find its place on the way up?

Start with an open position and hold the new value separately. If the parent has lower priority than the new value, copy the parent down into the opening. Its old position is now open. Continue until we reach the root or a parent with equal or higher priority. Put the new value into the last opening.

### Which child should move up when a value goes down?

Choose the child with higher priority, because a child that moves up becomes its sibling's parent. If it has higher priority than the value we are holding, copy the child up and continue from its old position. A child with the same priority can stay where it is. With only a left child, compare that child. At a leaf the search is over. Put the held value into the last opening.

### How do we put a new value into the heap?

Open the position where the next leaf goes, and from there let the new value find its place on the way up. Only parents on the path from that leaf to the root can move, each by one level. The new leaf keeps the tree complete, and the heap now holds one more value.

### Which value fills the position left by the root?

Taking out the root leaves its position open. Moving a child up only pushes the opening down, where it could land in the middle of a level. Instead, remove the last leaf, which keeps the tree complete, and let its value find its place on the way down from the root. Only children on the path from the root can move, each by one level, and the heap now holds one fewer value.

### How can we turn a given tree into a heap?

A tree with only one value is already a heap. We can start from the root and grow the heap one value at a time, letting each value find its place on the way up. Or we can start from the leaves, which are one-value heaps, and merge heaps toward the root, letting each parent's value find its place on the way down.

### Why does the merge work?

Going backward, we reach each value only after every value below it, so its two subtrees are already heaps. That is the same situation as taking out the root: only the value on top may be out of place. Moving it down copies up the child with higher priority, which has at least as much priority as everything in both subtrees, and the value keeps going down until it fits. Going forward instead would send values down into subtrees that are not heaps yet, and the result may not be a heap.

### How does taking out the root sort the values?

Start with a heap, built as above. Each time we take out the root, we get the highest-priority value still waiting, and the rest settle back into a heap. Taking out the root until the heap is empty therefore gives every value in priority order. Collect them in the order they come out, and they are sorted.

### Where do we store the tree in an array?

Number the positions in the order we fill them: the root is at 0, its children at 1 and 2, and the next level at 3 through 6.

### Where does each level start and end?

Level d starts at 2ᵈ − 1, because the levels above it hold 1 + 2 + … + 2ᵈ⁻¹ = 2ᵈ − 1 values. A full level d ends at 2ᵈ⁺¹ − 2, just before level d + 1 starts.

### Where are the children of a value?

A value at position i on level d has i − (2ᵈ − 1) values before it on its level. Each of those has two children on the next level, which starts at 2ᵈ⁺¹ − 1, so the children of i are at 2ᵈ⁺¹ − 1 + 2(i − 2ᵈ + 1) = 2i + 1 and 2i + 2.

### Where is the parent of a value?

Going the other way, a child at position c has its parent at (c − 1) / 2, rounded down: both 2i + 1 and 2i + 2 give back i.

## Calculating efficiency

### How much work is putting in or taking out one value?

Either operation moves values along one path between a leaf and the root, so it moves at most one value per level. Every level but the last is full, and each level has twice the positions of the one above, so n values fit in ⌊log₂ n⌋ + 1 levels. Going up compares one parent per level, and going down compares the two children and then the higher one with the held value, so the work grows only like log₂ n.

### How much work is building the whole heap from the root?

Growing the heap one value at a time can send each new value all the way to the root, if it has the highest priority so far. Most values sit in the bottom levels, so the total work can grow like n log₂ n.

### How much work is building the whole heap from the leaves?

Merging from the leaves sends each value down at most as far as the levels below its starting position. A leaf has no downward step of its own, though its value can move up when a parent sifts down. At most half the starting positions allow a first step down, a quarter allow a second, an eighth allow a third, and so on. Those steps add up to fewer than n for a nonempty heap, so building by merging grows only like n.

### How much work is sorting with the heap?

Building the heap by merging takes fewer than n downward steps for a nonempty heap. Each of the n take-outs can then move a value down at most ⌊log₂ n⌋ levels. During the first half of the take-outs the heap still holds at least n/2 values. In the worst case, a constant fraction of those take-outs follow paths nearly as long as the height of the heap, so the total work grows like n log₂ n.

### How much storage is needed?

The heap needs one array with a position for every value it may hold, plus a count of the values; it cannot hold more values than the array has positions. No pointers are stored, because parents and children are found by arithmetic on positions. Putting in, taking out and building the heap each need only a few extra variables, such as the held value and the open position. Sorting as described collects the values in a second array, so it needs n more positions. Each take-out frees the last position, so the sorted values could go there instead, but with a min-heap they would end up in descending order.

## Glossary

### Complete binary tree

A binary tree whose levels fill from top to bottom and from left to right. Only the last level may be partly filled.

### Binary heap

A complete binary tree in which each parent has at least as much priority as either child.

### Min-heap

A heap in which smaller values have higher priority. The root of a nonempty min-heap holds a smallest value.

### Max-heap

A heap in which larger values have higher priority. The root of a nonempty max-heap holds a largest value.

### Opening

A position free to be overwritten, because its value has been copied elsewhere or it holds no value yet. The held value ends up in the last opening.

### Sift-up

To find a place for a value by moving lower-priority parents down one level each.

### Sift-down

To find a place for a value by moving higher-priority children up one level each.

### Heapify

To turn a given tree into a heap by sifting down each value that has a child, from the last one back to the root.

### Heap sort

To sort by taking out the root of a heap until the heap is empty. In this chapter's code, `heap_sort` expects the heap to be built already.

## Invariant

### Which positions are always in use?

Between operations, the values occupy positions 0 through `size - 1` with no gaps, and `size` counts them. During a sift one position is an opening and the held value is outside the array, but by the time the operation returns, the opening is filled and the rule holds again. Positions from `size` on are not part of the heap, even if they still hold old values.

### Why does one path suffice to restore heap order?

Before each operation the tree is a heap, and the operation copies values only along the path of the opening, so every parent–child pair off that path is unchanged. A value copied down lands above values that were already below it, and a value copied up has at least as much priority as everything below it, so the copies themselves break nothing. In both directions the only pair that can be out of order is the held value and its neighbor at the opening, and the sift stops when that pair is in order.

### What is already true when we sift down during a build?

When the build reaches position `i`, every position after `i` is the top of a heap: its subtree already follows the parent–child rule. At the start this holds because everything after the last value with a child is a leaf. Since the children of `i` come after `i`, both subtrees of `i` are heaps when it is sifted down.

## Coding plan

### What data does the priority queue need?

Reserve `pq[CAPACITY]` for the integers and keep their count in `size`. Initialize the count to zero. Let `compare(x, y)` return true when `x < y`. Equal values have equal priority. Nothing checks for a full or empty queue, so never put a value into a full queue or take one out of an empty queue.

### How do we move lower-priority ancestors to sift up a value?

Start with the opening at the given position and the value held aside. While the opening is not the root and its parent has lower priority than the held value, copy the parent down into the opening, and the parent's old position becomes the opening. Return the last opening, and let the caller put the held value there.

### How do we move higher-priority descendants to sift down a value?

Start with the opening at the given position and the value held aside. While the opening has a child and the chosen child has higher priority than the held value, copy that child up into the opening, and the child's old position becomes the opening. Return the last opening, and let the caller put the held value there. The next subsection shows how to choose the child.

### How do we choose an existing child?

A child exists only if its position is less than the count. If the right child exists and has higher priority than the left, choose the right; otherwise choose the left if it exists, so equal priorities pick the left. If there are no children, let the caller know to stop.

### What should we do to put a value in?

Sift the new value up from the first unused position, whose number equals the count. Put the value into the opening that comes back, and add one to the count.

### What should we do to take a value out?

Save the root's value. Subtract one from the count, which removes the last leaf, and hold its value aside. Sift the held value down from the root, put it into the opening that comes back, and return the saved value.

### Where should we begin building a heap?

Begin at the parent of the last value. It is the last value with a child, because any later position would have its children past the last value. From there, go back one position at a time to the root. At each position, hold its value aside, sift it down from that position, and put it into the opening that comes back.

### How many times should the sorting loop run?

Start with a built heap. Run the loop once per value, but save the count first: each take-out subtracts one from it, and comparing against the shrinking count would stop about halfway. Each time through, take a value out and store it in the next position of the second array, from the front, so the values end up in priority order.

## New C syntax explained

### How does integer division give the parent index?

If `i` is a child of `p`, its index is `p * 2 + 1` or `p * 2 + 2`. Subtract one and divide by two. C discards the fractional part, which rounds a nonnegative number down, so both give `p`. The root has no parent, so `sift_up` checks for the root before using the result.

```c
int parent(int i) { return (i - 1) / 2; }
```

### When is it safe to read a candidate child?

In `c != -1 && compare(pq[c], data)`, C checks the left side first and evaluates the right side only if the left side is true, so `pq[c]` is never read as `pq[-1]`. Likewise, `r < size && compare(pq[r], pq[l])` reads the two child values only after checking that the right child exists, and then the left child exists too.

### Which position does a pre-decrement read?

The expression `--size` first reduces `size`, then gives the new value as the index. The new `size` is the old last position, so the statement reads the former last value. Positions 0 through `size - 1` remain in the heap.

```c
int data = pq[--size];
```

## C code

### Priority queue implementation

#### Store the values and compare their priorities

```c
/* No full or empty checks: never enqueue into a full queue,
 * never dequeue from an empty queue. */
enum { CAPACITY = 5 };

int pq[CAPACITY];
int size;

void init_pqueue(void) { size = 0; }

/* The smaller value has higher priority, so this is a min-heap */
int compare(int x, int y) { return x < y; }
```

#### Find the parent and move lower-priority parents down

```c
/* Positions go level by level from 0, so the children of i are 2i + 1
 * and 2i + 2, and (i - 1) / 2 rounds down to i's parent from either. */
int parent(int i) { return (i - 1) / 2; }

/* Moves lower-priority parents down a level each and returns the
 * position where data belongs. The caller stores data there. */
int sift_up(int i, int data) {
	int p = parent(i);
	while (i > 0 && compare(data, pq[p])) {
		pq[i] = pq[p];
		i = p;
		p = parent(i);
	}
	return i;
}
```

#### Choose the higher-priority child

```c
int left(int i) { return i * 2 + 1; }
int right(int i) { return i * 2 + 2; }

/* Returns the existing child with higher priority, or -1 if i has
 * no children. Ties go to the left child. */
int priority_child(int i) {
	int l = left(i);
	int r = right(i);
	int child = -1;
	if (r < size && compare(pq[r], pq[l])) {
		child = r;
	} else if (l < size) {
		child = l;
	}
	return child;
}
```

#### Move higher-priority children up

```c
/* Moves higher-priority children up a level each and returns the
 * position where data belongs. The caller stores data there. */
int sift_down(int i, int data) {
	int c = priority_child(i);
	while (c != -1 && compare(pq[c], data)) {
		pq[i] = pq[c];
		i = c;
		c = priority_child(i);
	}
	return i;
}
```

#### Put a value into the heap

```c
void enqueue(int data) {
	int pos = sift_up(size, data);
	pq[pos] = data;
	size++;
}
```

#### Take the root out of the heap

```c
int dequeue(void) {
	int root = pq[0];
	int data = pq[--size];
	int pos = sift_down(0, data);
	pq[pos] = data;
	return root;
}
```

### Heap construction and sorting

#### Build the heap from the last parent

```c
/* Positions after parent(size - 1) are leaves, already heaps. Going
 * backwards, both subtrees of i are heaps when sift_down(i, data) runs. */
void heapify(void) {
	for (int i = parent(size - 1); i >= 0; i--) {
		int data = pq[i];
		int pos = sift_down(i, data);
		pq[pos] = data;
	}
}
```

#### Write the roots into the output array

```c
/* pq must already be a heap. Each root fills sorted from the front,
 * so the order is ascending. pq ends empty. */
void heap_sort(int sorted[]) {
	int old_size = size;
	for (int i = 0; i < old_size; i++) {
		sorted[i] = dequeue();
	}
}
```

#### Build, insert, and sort five values

```c
int main(void) {
	pq[0] = 9;
	pq[1] = 6;
	pq[2] = 5;
	size = 3;
	heapify(); /* pq is now 5 6 9: 9 moved down 1 level */

	enqueue(3); /* pq is now 3 5 9 6: 3 moved up 2 levels */
	enqueue(1); /* pq is now 1 3 9 6 5: 1 moved up 2 levels */

	int sorted[CAPACITY];
	/* Heap sort: empty the heap into sorted */
	heap_sort(sorted); /* sorted is now 1 3 5 6 9, and pq is empty */

	return 0;
}
```
