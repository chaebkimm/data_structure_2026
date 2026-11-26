enum { CAPACITY = 12 };
int arr[CAPACITY] = {1, 3, 5, 7, 9, 11};
int front = 0, rear = 5;

int linear_search(int target) {
    for (int i = front; i <= rear; i++) {
        if (arr[i] == target) {
            return i;
        }
    }
    return -1;
}

int binary_search(int target) {
    int lo = front;
    int hi = rear;
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        if (arr[mid] == target) {
            return mid;
        } else if (arr[mid] < target) {
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }
    return -1;
}

struct Tree_Node {
    int data;
    int left;
    int right;
};

struct Tree_Node nodes[CAPACITY];
int nodes_size = 0;

int new_node(int d, int l, int r) {
    if (nodes_size == CAPACITY) {return -1;}
    int i = nodes_size++;
    nodes[i].data = d;
    nodes[i].left = l;
    nodes[i].right = r;
    return i;
}

int arr_to_bst(int lo, int hi) {
    if (lo > hi) { 
        return -1;
    }
    int mid = (lo + hi) / 2;
    int left_child = arr_to_bst(lo, mid - 1);
    int right_child = arr_to_bst(mid + 1, hi);
    return new_node(arr[mid], left_child, right_child);
}

int bst_search(int root, int value) {
    int i = root;
    while (i != -1) {
        if (value == nodes[i].data) { return i; }
        else if (value < nodes[i].data) {
            i = nodes[i].left;
        } else {
            i = nodes[i].right;
        }
    }
    return -1;
}

int bst_add(int root, int value) {
    if (root == -1) { return new_node(value, -1, -1); }
    int p = -1;
    int i = root;
    do {
        if (value == nodes[i].data) { return root; }
        p = i;
        if (value < nodes[i].data) {
            i = nodes[i].left;
        } else {
            i = nodes[i].right;
        }
    } while (i != -1);
    if (value < nodes[p].data) {
        nodes[p].left = new_node(value, -1, -1);
    } else {
        nodes[p].right = new_node(value, -1, -1);
    }
    return root;
}
