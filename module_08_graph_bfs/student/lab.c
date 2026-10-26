#include <assert.h>
#include "queue.c"

int maze[7][7] = {
    {0, 0, 0, 0, 0, 0, 0},
    {0, 1, 0, 1, 1, 1, 0},
    {0, 1, 1, 1, 0, 1, 0},
    {0, 1, 0, 1, 1, 1, 0},
    {0, 1, 0, 1, 0, 1, 0},
    {0, 1, 1, 1, 1, 1, 0},
    {0, 0, 0, 0, 0, 0, 0}
};

struct point {
    int x;
    int y;
};

int is_wall(struct point p) {
    return maze[p.y][p.x] == 0;
}

struct maze_node {
    int index;
    int distance;
    struct point prev[4];
    int prev_size;
};

struct maze_node info[7][7];
struct point points[50];

void init_info() {
    int pos = 0;
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 7; j++) {
            info[i][j].index = pos;
            info[i][j].distance = 25;
            info[i][j].prev_size = 0;
            points[pos].y = i;
            points[pos].x = j;
            pos++;
        }
    }
}

int get_index(struct point p) {return info[p.y][p.x].index;}

int get_distance(struct point p) {return info[p.y][p.x].distance;}
void set_distance(struct point p, int dist) {info[p.y][p.x].distance = dist;}

void add_prev(struct point p, struct point from) {
    int pos = info[p.y][p.x].prev_size++;
    info[p.y][p.x].prev[pos] = from;
}

struct point cur_point;
int state;

void init_iter(struct point p) {
    cur_point = p;
    state = 0;
}

int has_next() {return state < 4;}

struct point next_iter() {
    struct point p = cur_point;
    switch (state) {
        case 0: p.x += 1; break;
        case 1: p.x -= 1; break;
        case 2: p.y += 1; break;
        case 3: p.y -= 1; break;
    }
    ++state;
    return p;
}

void bfs(struct point start) {
    set_distance(start, 0);
    bool added = enqueue(get_index(start));
    assert(added);
    (void)added;

    while (!is_empty_queue()) {
        int cell_id = dequeue(); /* Returns the ID and recycles its queue node. */
        struct point cur = points[cell_id];
        int cur_distance = get_distance(cur);
        init_iter(cur);
        while (has_next()) {
            struct point neighbor = next_iter();
            if (is_wall(neighbor)) {continue;}
            int neighbor_distance = get_distance(neighbor);
            if (neighbor_distance <= cur_distance) {continue;}
            else if (neighbor_distance == cur_distance + 1) {
                add_prev(neighbor, cur);
            }
            else {
                set_distance(neighbor, cur_distance + 1);
                add_prev(neighbor, cur);
                added = enqueue(get_index(neighbor));
                assert(added);
            }
        }
    }
}
