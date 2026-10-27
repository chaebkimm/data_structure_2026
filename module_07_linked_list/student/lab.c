struct Linked_Node {
	int data;
	int next;
};

struct Linked_Node lnodes[10];

void link_lnode(int prev, int node) {
	lnodes[node].next = lnodes[prev].next;
	lnodes[prev].next = node;
}

int delete_next_lnode(int prev) {
	int node = lnodes[prev].next;
	if (node != -1) {
		lnodes[prev].next = lnodes[node].next;
	}
	return node;
}

int free_head = -1;

void init_lnodes_pool(void) {
	for (int i = 0; i < 9; i++) {
		lnodes[i].data = 0;
		lnodes[i].next = i + 1;
	}
	lnodes[9].data = 0;
	lnodes[9].next = -1;
	free_head = 0;
}

int new_lnode(int data_value, int next_value) {
	if (free_head == -1) {
		return -1;
	}
	int node = free_head;
	free_head = lnodes[free_head].next;
	lnodes[node].data = data_value;
	lnodes[node].next = next_value;
	return node;
}

void free_lnode(int node) {
	if (node < 0 || node >= 10) {
		return;
	}
	lnodes[node].next = free_head;
	free_head = node;
}

int head = -1;
int tail = -1;

int is_empty_queue(void) { return head == -1; }

void enqueue_lnode(int node) {
  if (node == -1) {
    return;
  }
	if (is_empty_queue()) {
		head = tail = node;
	} else {
		lnodes[tail].next = node;
		tail = node;
	}
}

int dequeue_lnode(void) {
	if (is_empty_queue()) {
		return -1;
	}
	int oldest = head;
	if (head == tail) {
		head = tail = -1;
	} else {
		head = lnodes[head].next;
	}
	return oldest;
}