enum {CAPACITY = 10};
int queue[CAPACITY];
int size = 0;

int (*comp)(int i, int j);
void swap(int i, int j) {
    int old_i_val = queue[i];
    int old_j_val = queue[j];
    queue[i] = old_j_val;
    queue[j] = old_i_val;
}
int left(int id) {return id * 2 + 1;}
int right(int id) {return id * 2 + 2;}
int parent(int id) {return id == 0 ? -1 : (id - 1) / 2;}

void sift_down(int id) {
    while (left(id) < size) {
        int child = left(id);
        if (right(id) < size && comp(right(id), left(id))) {
            child = right(id);
        }
        if (comp(id, child)) { break; }
        swap(id, child);
        id = child;
    }
}

void sift_up(int id) {
    while (id > 0) {
        int p = parent(id);
        if (comp(p, id)) { break; }
        swap(id, p);
        id = p;
    }
}

int is_empty_queue(void) { return size == 0; }

void init_queue(int (*compare)(int, int)) {
    comp = compare; 
	size = 0;
}

void enqueue_heap(int data) {
    queue[size++] = data;
    sift_up(size - 1);
}

int dequeue_heap(void) {
    if (is_empty_queue()) { return -1; }
    int temp = queue[0];
    queue[0] = queue[--size];
    sift_down(0);
    return temp;
}

void (*enqueue)(int);
int (*dequeue)(void);

void init_queue_heap(int (*compare)(int, int)) {
    init_queue(compare);
    enqueue = enqueue_heap;
    dequeue = dequeue_heap;
}

enum {LSIZE = CAPACITY, EPOCH_SIZE = 5};

struct Light {
    int on_time;
    int off_time;
    int epoch;
};

struct Light lights[LSIZE];

int toggle_info[LSIZE][EPOCH_SIZE * 2];

void init_lights() {
    for (int i = 0; i < LSIZE; i++) {
        lights[i].on_time = toggle_info[i][0];
        lights[i].off_time = toggle_info[i][1];
        lights[i].epoch = 0;
    }
}

int greater_on_time(int id_x, int id_y) {
    return lights[id_x].on_time >= lights[id_y].on_time;
}

int lesser_heap_off_time(int heap_id_x, int heap_id_y) {
    int id_x = queue[heap_id_x];
    int id_y = queue[heap_id_y];
    return lights[id_x].off_time <= lights[id_y].off_time;
}

int last_on_id = -1;
int first_off_id = -1;

void init_on_off() {
    init_queue_heap(lesser_heap_off_time);
    last_on_id = 0;
    for (int i = 0; i < LSIZE; i++) {
        if (greater_on_time(i, last_on_id)) {last_on_id = i;}
        enqueue(i);
    }
    first_off_id = dequeue();
}

int next_epoch(int id) {
    int ep = ++lights[id].epoch;
    if (ep >= EPOCH_SIZE) {return -1;}
    lights[id].on_time = toggle_info[id][ep * 2];
    lights[id].off_time = toggle_info[id][ep * 2 + 1];  
    return 0;
}

void update_on_off(int id) {
    if (greater_on_time(id, last_on_id)) {last_on_id = id;}
    enqueue(id);
    first_off_id = dequeue();
}

int check_all_on() {
    return lights[last_on_id].on_time <= lights[first_off_id].off_time;
}

int all_on_time() {
    init_lights();
    init_on_off();
    while (!check_all_on()) {
        if (next_epoch(first_off_id) == -1) {return -1;}
        update_on_off(first_off_id);
    }
    return lights[last_on_id].on_time;
}

