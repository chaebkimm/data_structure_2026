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