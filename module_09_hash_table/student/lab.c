#ifndef MODULE_07_LINKED_LIST_SOURCE_IMPORTED
#define MODULE_07_LINKED_LIST_SOURCE_IMPORTED
#include "module_07_linked_list/student/lab.c"
#endif

int hashtable[10] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1};

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

int hash_func(int value) {
    int hash = value % 10;
    if (hash >= 0) {
        return hash;
    }
    else {
        return hash + 10;
    }
}

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

int nums[10] = {-16, -8, -4, -2, -1, 1, 2, 4, 8, 16};

int answer[2] = {-1, -1};

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
