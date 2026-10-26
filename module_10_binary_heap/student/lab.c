int heap[10];
int size;
int is_min_heap;

void init_heap() {
    size = 0;
    is_min_heap = 1;
}
int parent(int i) {return i <= 0 ? -1 : (i - 1) / 2;}
int left(int i) {return 2 * i + 1 >= size ? -1 : 2 * i + 1;}
int right(int i) {return 2 * i + 2 >= size ? -1 : 2 * i + 2;}
int comp(int i, int j) {
    return is_min_heap ? heap[i] <= heap[j] : heap[i] >= heap[j];
}
int proper_parent(int i, int j) {
    if (i == -1 && j == -1) {
        return -1;
    } else if (i == -1 || j == -1) {
        return i == -1 ? j : i;
    }
    return comp(i, j) ? i : j;
}
void swap_data(int i, int j) {
    int old_i_val = heap[i];
    int old_j_val = heap[j];
    heap[i] = old_j_val;
    heap[j] = old_i_val;
}
void heapify_down(int i) {
    while (i != -1) {
        int child = proper_parent(left(i), right(i));
        if (proper_parent(i, child) == i) {break;}
        swap_data(i, child);
        i = child;
    }
}
void heapify() {
    for (int i = parent(size - 1); i >= 0; i--) {
        heapify_down(i);
    }
}
int remove_root() {
    int root = 0;
    int data = heap[root];
    heap[root] = heap[--size];
    heapify_down(root);
    return data;
}
void heapify_up(int i) {
    while (i > 0) {
        int p = parent(i);
        if (proper_parent(p, i) == p) {break;}
        swap_data(i, p);
        i = p;
    }
}
void add(int data) {
    int i = size++;
    heap[i] = data;
    heapify_up(i);
}
void update_value(int i, int data) {
    heap[i] = data;
    int pp = proper_parent(parent(i), i);
    if (i == 0 || parent(i) == pp) {
        heapify_down(i);
    } else {
        heapify_up(i);
    }
}

int toggle_info[10][10];
int interval_size[10];
int epoch[10];

int get_on_time(int id) {
    return toggle_info[id][epoch[id] * 2];
}

int get_off_time(int id) {
    return toggle_info[id][epoch[id] * 2 + 1];
}

int _comp_on_max(int id_x, int id_y) {
    int on_time_x = get_on_time(id_x);
    int on_time_y = get_on_time(id_y);
    return on_time_x >= on_time_y;
}

int _comp_off_min(int id_x, int id_y) {
    int off_time_x = get_off_time(id_x);
    int off_time_y = get_off_time(id_y);
    return off_time_x <= off_time_y;
}

struct Heap_Full {
    int array[10];
    int (*comp)(int x, int y); 
    void (*swap)(int i, int j);
} max_on_heap, min_off_heap;

int _proper_parent(struct Heap_Full *_heap, int i, int j) {
    if (i == -1 && j == -1) {return -1;}
    else if (i == -1) {return j;}
    else if (j == -1) {return i;}
    else {
        int *arr = _heap->array;
        return _heap->comp(arr[i], arr[j]) ? i : j;
    }
}

int _parent(int i) {return i == 0 ? -1 : (i - 1) / 2;}
int _left(int i) {return i >= 5 ? -1 : 2 * i + 1;}
int _right(int i) {return i >= 4 ? -1 : 2 * i + 2;}

int _max_heap_pos[10];
int _min_heap_pos[10];

void __swap__(int i, int j, int *_arr, int *_heap_pos) {
    int x = _arr[i]; /* _heap_pos[x] == i */
    int y = _arr[j]; /* _heap_pos[y] == j */
    _arr[i] = y;
    _arr[j] = x;
    _heap_pos[x] = j;
    _heap_pos[y] = i;
}
void _swap_max(int i, int j) {__swap__(i, j, max_on_heap.array, _max_heap_pos);}
void _swap_min(int i, int j) {__swap__(i, j, min_off_heap.array, _min_heap_pos);}

void _heapify_down(struct Heap_Full *_heap, int i) {
    int leaf_start = 5;
    while (i < leaf_start) {
        int child = _proper_parent(_heap, _left(i), _right(i));
        int pp = _proper_parent(_heap, i, child);
        if (pp == i) {break;}
        _heap->swap(i, child);
        i = child;        
    }
}

void _heapify(struct Heap_Full *_heap) {
    for (int i = 5; i >= 0; i--) {
        _heapify_down(_heap, i);
    }
}

void _init_heaps() {
    for (int i = 0; i < 10; i++) {
        epoch[i] = 0;
        max_on_heap.array[i] = i;
        _max_heap_pos[i] = i;
        min_off_heap.array[i] = i;
        _min_heap_pos[i] = i;
    }
    max_on_heap.comp = _comp_on_max;
    max_on_heap.swap = _swap_max;
    min_off_heap.comp = _comp_off_min;
    min_off_heap.swap = _swap_min;
    _heapify(&max_on_heap);
    _heapify(&min_off_heap);
}

int _get_root(struct Heap_Full *_heap) {
    return _heap->array[0];
}

void _heapify_up(struct Heap_Full *_heap, int i) {
    while (i > 0) {
        int pp = _proper_parent(_heap, _parent(i), i);
        if (pp == _parent(i)) {break;}
        _heap->swap(i, _parent(i));
        i = _parent(i);
    }
}

void _reheapify(struct Heap_Full *_heap, int i) {
    int pp = _proper_parent(_heap, _parent(i), i);
    if (i == 0 || pp == _parent(i)) {_heapify_down(_heap, i);}
    else {_heapify_up(_heap, i);}
}

int check_all_on() {
    int last_on_id = _get_root(&max_on_heap);
    int first_off_id = _get_root(&min_off_heap);
    return get_on_time(last_on_id) <= get_off_time(first_off_id);
}

int all_on_time() {
    _init_heaps();
    while (!check_all_on()) {
        int id = _get_root(&min_off_heap);
        if (++epoch[id] == interval_size[id]) {return -1;}
        _reheapify(&min_off_heap, _min_heap_pos[id]);
        _reheapify(&max_on_heap, _max_heap_pos[id]);
    }
    int last_on_id = _get_root(&max_on_heap);
    return get_on_time(last_on_id);
}
