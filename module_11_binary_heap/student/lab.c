/* No full or empty checks: never enqueue into a full queue,
 * never dequeue from an empty queue. */
enum { CAPACITY = 5 };

int pq[CAPACITY];
int size;

void init_pqueue(void) { size = 0; }

/* The smaller value has higher priority, so this is a min-heap */
int compare(int x, int y) { return x < y; }

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

void enqueue(int data) {
	int pos = sift_up(size, data);
	pq[pos] = data;
	size++;
}

int dequeue(void) {
	int root = pq[0];
	int data = pq[--size];
	int pos = sift_down(0, data);
	pq[pos] = data;
	return root;
}

/* Positions after parent(size - 1) are leaves, already heaps. Going
 * backwards, both subtrees of i are heaps when sift_down(i, data) runs. */
void heapify(void) {
	for (int i = parent(size - 1); i >= 0; i--) {
		int data = pq[i];
		int pos = sift_down(i, data);
		pq[pos] = data;
	}
}

/* pq must already be a heap. Each root fills sorted from the front,
 * so the order is ascending. pq ends empty. */
void heap_sort(int sorted[]) {
	int old_size = size;
	for (int i = 0; i < old_size; i++) {
		sorted[i] = dequeue();
	}
}

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
