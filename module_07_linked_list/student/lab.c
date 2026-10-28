enum { CAPACITY = 10 };

struct Linked_Node {
  int data;
  int next;
};
struct Linked_Node lnodes[CAPACITY];

/* Unchecked: caller guarantees 0 <= prev, node < CAPACITY,
 * prev != node, prev is an allocated non-queue node,
 * and node is allocated, unreferenced, and isolated (lnodes[node].next == -1). */
void simple_link_lnode_to_prev(int prev, int node) {
	lnodes[node].next = lnodes[prev].next;
	lnodes[prev].next = node;
}

/* Unchecked: caller guarantees 0 <= prev < CAPACITY and prev is an
 * allocated non-queue node.
 * Returns the detached node index (or -1 if none); caller owns the returned node. */
int simple_delink_next_lnode_from_prev(int prev) {
	int node = lnodes[prev].next;
	if (node != -1) {
		lnodes[prev].next = lnodes[node].next;
		lnodes[node].next = -1;
	}
	return node;
}

int free_head = -1;

/* Initializes the free list on first use; does not reset an active pool. */
void init_lnodes_pool(void) {
	static int initialized = 0;
	if (initialized) { return; }
	initialized = 1;

	for (int i = 0; i < CAPACITY - 1; i++) {
		lnodes[i].next = i + 1;
	}
	lnodes[CAPACITY - 1].next = -1;
	free_head = 0;
}

int new_lnode(void) {
	init_lnodes_pool();
	if (free_head == -1) {
		return -1;
	}
	int node = free_head;
	free_head = lnodes[free_head].next;
	lnodes[node].next = -1;
	return node;
}

/* Unchecked: caller guarantees node == -1, or (0 <= node < CAPACITY and
 * node is allocated, unreferenced, and isolated (lnodes[node].next == -1)). */
void free_lnode(int node) {
	if (node == -1) {
		return;
	}
	lnodes[node].next = free_head;
	free_head = node;
}

int qhead = -1;
int qtail = -1;

int is_empty_queue(void) { return qhead == -1; }

/* Unchecked: caller guarantees node == -1, or (0 <= node < CAPACITY and
 * node is allocated, unreferenced, and isolated (lnodes[node].next == -1)). */
void enqueue_lnode(int node) {
	if (node == -1) {
		return;
	}
	if (is_empty_queue()) {
		qhead = qtail = node;
	} else {
		lnodes[qtail].next = node;
		qtail = node;
	}
}

/* Returns the detached node index (or -1 if none); caller owns the returned node. */
int dequeue_lnode(void) {
	if (is_empty_queue()) {
		return -1;
	}
	int oldest = qhead;
	qhead = lnodes[qhead].next;
	if (qhead == -1) {
		qtail = -1;
	}
	lnodes[oldest].next = -1;
	return oldest;
}
