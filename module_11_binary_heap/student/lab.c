enum {CAPACITY = 10};
int queue[CAPACITY];
int size = 0;

int is_empty_queue(void) { return size == 0; }

int (*comp)(int x, int y);

int comp_q(int i, int j) {
    return comp(queue[i], queue[j]);
}

void swap(int i, int j) {
    int old_i_val = queue[i];
    int old_j_val = queue[j];
    queue[i] = old_j_val;
    queue[j] = old_i_val;
}

void sift_down(int id) {
    while (id * 2 + 1 < size) {
        int l = id * 2 + 1;
        int r = id * 2 + 2;
        int child = l;
        if (r < size && comp_q(r, l)) {
            child = r;
        }
        if (!comp_q(child, id)) { break; }
        swap(id, child);
        id = child;
    }
}

void sift_up(int id) {
    while (id > 0) {
        int p = (id - 1) / 2;
        if (!comp_q(id, p)) { break; }
        swap(p, id);
        id = p;
    }
}

void enqueue(int data) {
    queue[size++] = data;
    sift_up(size - 1);
}

int dequeue(void) {
    if (is_empty_queue()) { return -1; }
    int most = queue[0];
    queue[0] = queue[--size];
    sift_down(0);
    return most;
}

void init_queue(int (*compare)(int, int)) {
    comp = compare;
    size = 0;
}

void heapify(void) {
    for (int i = size / 2 - 1; i >= 0; i--) {
        sift_down(i);
    }
}

int sorted[CAPACITY];
int pos = 0;

void heap_sort(void) {
    heapify();
    pos = 0;
    while (!is_empty_queue()) {
        sorted[pos++] = dequeue();
    }
}