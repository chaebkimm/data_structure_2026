enum { CAP = 12 };
int arr[CAP] = {1, 3, 5, 7, 9, 11};
int front = 0, rear = 5;

int linear_search(int target) {
    for (int i = front; i <= rear; i++) {
        if (arr[i] == target) { return i; }
    }
    return -1;
}

int binary_search(int target) {
    int low = front;
    int high = rear;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (target == arr[mid]) {
            return mid;
        } else if (target < arr[mid]) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    return -1;
}

struct Tree_Node {
    int data;
    int left;
    int right;
};

struct Tree_Node nodes[CAP];
int nodes_size = 0;

int new_node(int val, int l, int r) {
    if (nodes_size == CAP) { return -1; }
    int i = nodes_size++;
    nodes[i].data = val;
    nodes[i].left = l;
    nodes[i].right = r;
    return i;
}

int convert_bst(int low, int high) {
    if (low > high) { return -1; }
    int mid = (low + high) / 2;
    int l = convert_bst(low, mid - 1);
    int r = convert_bst(mid + 1, high);
    return new_node(arr[mid], l, r);
}

int bst_search(int i, int val) {
    while (i != -1) {
        if (val == nodes[i].data) { 
            return i; 
        } else if (val < nodes[i].data) {
            i = nodes[i].left;
        } else {
            i = nodes[i].right;
        }
    }
    return -1;
}

int bst_add(int i, int val) {
    if (i == -1) { 
        return new_node(val, -1, -1); 
    }
    int p = -1;
    do {
        if (val == nodes[i].data) { 
            return i; 
        }
        p = i;
        if (val < nodes[i].data) {
            i = nodes[i].left;
        } else {
            i = nodes[i].right;
        }
    } while (i != -1);
    int node = new_node(val, -1, -1);
    if (val < nodes[p].data) {
        nodes[p].left = node;
    } else {
        nodes[p].right = node;
    }
    return node;
}
