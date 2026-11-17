enum {SIZE = 10};
int heap[SIZE];

int (*comp_val)(int, int);

int comp(int i, int j) {
    return comp_val(heap[i], heap[j]);
}

void swap(int i, int j) {
    int old_i_val = heap[i];
    int old_j_val = heap[j];
    heap[i] = old_j_val;
    heap[j] = old_i_val;
}
int left(int id) {return id * 2 + 1;}
int right(int id) {return id * 2 + 2;}

void sift_down(int id) {
    while (left(id) < SIZE) {
        int child = left(id);
        if (right(id) < SIZE && comp(right(id), left(id))) {
            child = right(id);
        }
        if (comp(id, child)) { break; }
        swap(id, child);
        id = child;
    }
}

struct Light {
    int on_time;
    int off_time;
    int epoch;
};

struct Light lights[SIZE];

enum {EPOCH_SIZE = 5};

int toggle_info[SIZE][EPOCH_SIZE * 2];

void init_lights() {
    for (int i = 0; i < SIZE; i++) {
        lights[i].on_time = toggle_info[i][0];
        lights[i].off_time = toggle_info[i][1];
        lights[i].epoch = 0;
    }
}

int greater_on_time(int id_x, int id_y) {
    return lights[id_x].on_time >= lights[id_y].on_time;
}

int lesser_off_time(int id_x, int id_y) {
    return lights[id_x].off_time <= lights[id_y].off_time;
}

int last_on_id = -1;
int first_off_id = -1;

void init_on_off() {
    last_on_id = 0;
    comp_val = lesser_off_time;
    for (int i = 0; i < SIZE; i++) {
        if (greater_on_time(i, last_on_id)) {last_on_id = i;}
        heap[i] = i;
    }
    for (int i = SIZE / 2 - 1; i >= 0; i--) {
        sift_down(i);
    }
    first_off_id = heap[0];
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
    sift_down(0);
    first_off_id = heap[0];
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