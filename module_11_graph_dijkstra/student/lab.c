#include "module_03_graph/student/lab.c"

int node_dist[10];

int heap[10];
int size;

int comp(int i, int j) {
    int node_x = heap[i];
    int node_y = heap[j];
    return node_dist[node_x] < node_dist[node_y];
}

int node_heap_pos[10];

void init_heap() {
    size = 0;
    for (int i = 0; i < 10; i++) {
        node_heap_pos[i] = -1;
    }
}

void swap(int i, int j) {
    int node_x = heap[i]; /* node_heap_pos[node_x] == i */
    int node_y = heap[j]; /* node_heap_pos[node_y] == j */
    heap[i] = node_y;
    heap[j] = node_x;
    node_heap_pos[node_x] = j;
    node_heap_pos[node_y] = i;
}

int heap_parent(int i) {return i == 0 ? -1 : (i - 1) / 2;}
int left(int i) {return 2 * i + 1 >= size? -1 : 2 * i + 1;}
int right(int i) {return 2 * i + 2 >= size? -1 : 2 * i + 2;}

void heapify_up(int i) {
    int p;
    while ((p = heap_parent(i)) != -1) {
        if (comp(p, i)) {break;}
        swap(p, i);
        i = p;
    }
}

void add_node(int node, int value) {
    node_dist[node] = value;
    int i = size++;
    node_heap_pos[node] = i;
    heap[i] = node;
    heapify_up(i);
}

int chief_child(int i) {
    if (right(i) == -1) return left(i);
    return comp(left(i), right(i)) ? left(i) : right(i);
}

void heapify_down(int i) {
    int child;
    while ((child = chief_child(i)) != -1) {
        if (comp(i, child)) {break;}
        swap (child, i);
        i = child;
    }
}

int remove_root() {
    int node = heap[0];
    swap(0, --size);
    heapify_down(0);
    return node;
}

void update_value(int node, int value) {
    node_dist[node] = value;
    int i = node_heap_pos[node];
    if (i == 0 || comp(heap_parent(i), i)) { heapify_down(i);}
    else {heapify_up(i);}
}

int edge_length[10][10]; /* positive value */
int found[10];

void init_dist(int start_node) {
    init_heap();
    for (int i = 0; i < 10; i++) {
        node_dist[i] = -1;
        found[i] = 0;
    }
    add_node(start_node, 0);
}

void min_dist(int start_node) {
    init_dist(start_node);
    while (size > 0) {
        int node = remove_root();
        found[node] = 1;
        for (int i = 0; i < nodes[node].adj_size; i++) {
            int adj = nodes[node].adj_list[i];
            int new_dist = node_dist[node] + edge_length[node][adj];
            if (node_dist[adj] == -1) {
                add_node(adj, new_dist);
            } else if (node_dist[adj] > new_dist) {
                update_value(adj, new_dist);
            }
        }
    }
}