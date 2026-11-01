enum { NUMS_SIZE = 10 };

int nums[NUMS_SIZE] = {-16, -8, -4, -2, -1, 1, 2, 4, 8, 16};
int answer[2] = {-1, -1};

void two_sum_bf(int target) {
	for (int i = 0; i < NUMS_SIZE; i++) {
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

enum { CAPACITY = NUMS_SIZE, HASHTABLE_SIZE = 15 };

struct hnode {
	int key;
	int value;
	int next;
};
struct hnode hnodes[CAPACITY];
int hnodes_unused = 0;

int hashtable[HASHTABLE_SIZE];

void initialize(void) {
	hnodes_unused = 0;
	for (int i = 0; i < HASHTABLE_SIZE; i++) {
		hashtable[i] = -1;
	}
}

int hash_func(int key) {
	int hash = key % HASHTABLE_SIZE;
	if (hash < 0) {
		hash += HASHTABLE_SIZE;
	}
	return hash;
}

int new_hnode(int _key, int _value, int _next) {
	if (hnodes_unused >= CAPACITY) {
		return -1;
	}
	int i = hnodes_unused++;
	hnodes[i].key = _key;
	hnodes[i].value = _value;
	hnodes[i].next = _next;
	return i;
}

int save_data(int k, int v) {
	int hash = hash_func(k);
	int old_head = hashtable[hash];
	int node = new_hnode(k, v, old_head);
	if (node == -1) {
		return -1;
	}
	hashtable[hash] = node;
	return 0;
}

int find_data(int k) {
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

void two_sum_ht(int target) {
	initialize();
	for (int i = 0; i < NUMS_SIZE; i++) {
		int j_num = target - nums[i];
		int j_node = find_data(j_num);
		if (j_node != -1) {
			int j = hnodes[j_node].value;
			answer[0] = i;
			answer[1] = j;
			return;
		}
		if (save_data(nums[i], i) == -1) {
			break;
		}
	}
	answer[0] = answer[1] = -1;
}