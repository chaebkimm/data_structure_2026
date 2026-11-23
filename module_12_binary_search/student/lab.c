int arr[6] = {1, 3, 5, 7, 9, 11};
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

int bst[7];

int parent(int i) { return (i - 1) / 2; }
int left(int i) { return 2 * i + 1; }
int right(int i) { return 2 * i + 2; }

struct interval {
    int lo;
    int hi;
    int root;
};

void convert_to_bst(void) {
    struct interval stack[15];
    int top = 0;

    stack[top].root = 0;
    stack[top].lo = front;
    stack[top].hi = rear;

    while (top >= 0) {
        struct interval i = stack[top--];
        int mid = (i.lo + i.hi) / 2;
        bst[i.root] = arr[mid];
        struct interval l = i;
        l.root = left(i.root);
        l.hi = mid - 1;
        if (l.lo <= l.hi) {
            stack[++top] = l;
        }
        struct interval r = i;
        r.root = right(i.root);
        r.lo = mid + 1;
        if (r.lo <= r.hi) {
            stack[++top] = r;
        }
    }
}