#include <assert.h>
#include <stdio.h>
#include "queue.c"

/* Observe Module 8 value adapters around Module 7 node operations. */
static int inserted, removed_count, pending, peak_pending;
static int scheduled[49], payload_order[49];

static void check_pool_restored(void) {
    int seen[10] = {0};
    int count = 0;
    assert(is_empty_queue() && qhead == -1 && qtail == -1);
    for (int slot = free_head; slot != -1; slot = lnodes[slot].next) {
        assert(slot >= 0 && slot < 10 && !seen[slot]);
        seen[slot] = 1;
        ++count;
    }
    assert(count == 10);
}

static void reset_linked_run(void) {
    init_lnodes_pool(); /* One-time initialization; the previous run recycled all slots. */
    assert(is_empty_queue() && qhead == -1 && qtail == -1);
    inserted = removed_count = pending = peak_pending = 0;
    for (int i = 0; i < 49; ++i) scheduled[i] = 0;
}

static void check_live_free_partition(void) {
    int free_count = 0, live_count = 0, seen[10] = {0};
    for (int node = qhead; node != -1; node = lnodes[node].next) {
        assert(node >= 0 && node < 10 && !seen[node]);
        seen[node] = 1;
        ++live_count;
    }
    for (int node = free_head; node != -1; node = lnodes[node].next) {
        assert(node >= 0 && node < 10 && !seen[node]);
        seen[node] = 1;
        ++free_count;
    }
    assert(live_count == pending && free_count + live_count == 10);
}

static bool observe_enqueue(int payload) {
    assert(payload >= 0 && payload < 49 && !scheduled[payload]);
    bool added = enqueue(payload);
    if (!added) return false;
    scheduled[payload] = 1;
    payload_order[inserted++] = payload;
    ++pending;
    if (pending > peak_pending) peak_pending = pending;
    assert(pending <= 10);
    check_live_free_partition();
    return true;
}

static int observe_dequeue(void) {
    assert(!is_empty_queue());
    int value = dequeue();
    assert(value == payload_order[removed_count]);
    ++removed_count;
    --pending;
    check_live_free_partition(); /* The public operation already recycled. */
    return value;
}

#define enqueue observe_enqueue
#define dequeue observe_dequeue
#include "lab.c"
#include "tree_bfs.c"
#undef enqueue
#undef dequeue

static int same_point(struct point a, struct point b) {
    return a.x == b.x && a.y == b.y;
}

static void run_search(struct point start) {
    assert(start.x >= 1 && start.x <= 5);
    assert(start.y >= 1 && start.y <= 5);
    assert(!is_wall(start));
    init_info();
    reset_linked_run();
    bfs(start);
}

static int path_count(struct point p) {
    if (get_distance(p) == 25) return 0;
    if (get_distance(p) == 0) return 1;
    int count = 0;
    for (int i = 0; i < info[p.y][p.x].prev_size; ++i)
        count += path_count(info[p.y][p.x].prev[i]);
    return count;
}

static void check_result(struct point start) {
    const int dx[4] = {1, -1, 0, 0};
    const int dy[4] = {0, 0, 1, -1};
    int reached = 0;
    assert(inserted == 20 && removed_count == 20 && pending == 0);
    assert(peak_pending <= 6);
    check_pool_restored();
    for (int y = 0; y < 7; ++y) {
        for (int x = 0; x < 7; ++x) {
            struct point p = {x, y};
            struct maze_node *node = &info[y][x];
            assert(node->index == 7*y+x);
            assert(same_point(points[node->index], p));
            if (is_wall(p)) {
                assert(node->distance == 25 && node->prev_size == 0);
                continue;
            }
            ++reached;
            assert(node->distance >= 0 && node->distance <= 19);
            if (same_point(p, start)) {
                assert(node->distance == 0 && node->prev_size == 0);
                continue;
            }
            assert(node->prev_size >= 1 && node->prev_size <= 4);
            int expected = 0;
            for (int k = 0; k < 4; ++k) {
                struct point q = {x+dx[k], y+dy[k]};
                if (is_wall(q)) continue;
                assert(node->distance <= get_distance(q)+1);
                if (get_distance(q) == node->distance-1) {
                    int matches = 0;
                    ++expected;
                    for (int i = 0; i < node->prev_size; ++i)
                        matches += same_point(node->prev[i], q);
                    assert(matches == 1);
                }
            }
            assert(node->prev_size == expected);
        }
    }
    assert(reached == 20);
}

static void check_canonical(void) {
    const int expected[7][7] = {
        {25,25,25,25,25,25,25},
        {25, 0,25, 4, 5, 6,25},
        {25, 1, 2, 3,25, 7,25},
        {25, 2,25, 4, 5, 6,25},
        {25, 3,25, 5,25, 7,25},
        {25, 4, 5, 6, 7, 8,25},
        {25,25,25,25,25,25,25}
    };
    for (int y = 0; y < 7; ++y)
        for (int x = 0; x < 7; ++x)
            assert(info[y][x].distance == expected[y][x]);
    assert(info[5][3].prev_size == 2);
    assert(same_point(info[5][3].prev[0], (struct point){3,4}));
    assert(same_point(info[5][3].prev[1], (struct point){2,5}));
    assert(info[5][5].prev_size == 2);
    assert(same_point(info[5][5].prev[0], (struct point){5,4}));
    assert(same_point(info[5][5].prev[1], (struct point){4,5}));
    assert(path_count((struct point){5,5}) == 3);
    assert(peak_pending == 4);
    assert(path_count((struct point){1,1}) == 1);
    assert(path_count((struct point){0,0}) == 0);
}

static void check_queues(void) {
    init_lnodes_pool();
    qhead = qtail = -1;
    assert(dequeue_lnode() == -1); /* The raw helper reports empty. */
    bool added = enqueue(17);
    assert(added);
    added = enqueue(23);
    assert(added);
    assert(qhead == 0 && qtail == 1 && lnodes[qhead].next == qtail);
    int value = dequeue();
    assert(value == 17 && qhead == qtail && qhead == 1 && free_head == 0);
    value = dequeue();
    assert(value == 23 && is_empty_queue());
    check_pool_restored();

    /* A payload of -1 is a value, not an empty-queue status. */
    added = enqueue(-1);
    assert(added && !is_empty_queue());
    value = dequeue();
    assert(value == -1 && is_empty_queue());
    check_pool_restored();

    for (int i = 0; i < 10; ++i) {
        added = enqueue(i);
        assert(added);
    }
    struct Linked_Node saved[10];
    for (int i = 0; i < 10; ++i) saved[i] = lnodes[i];
    int saved_head = qhead, saved_tail = qtail;
    added = enqueue(99);
    assert(!added && free_head == -1 && qhead == saved_head && qtail == saved_tail);
    for (int i = 0; i < 10; ++i)
        assert(saved[i].data == lnodes[i].data && saved[i].next == lnodes[i].next);
    for (int i = 0; i < 10; ++i) {
        value = dequeue();
        assert(value == i);
    }
    check_pool_restored();

    front = 0; rear = -1;
    assert(is_empty_linear());
    for (int i = 0; i < 25; ++i) { assert(!is_full_linear()); enqueue_linear(i); }
    assert(is_full_linear());
    for (int i = 0; i < 25; ++i) {
        assert(!is_empty_linear());
        value = dequeue_linear();
        assert(value == i);
    }
    assert(is_empty_linear() && is_full_linear());

    front = 0; rear = -1;
    assert(is_empty_circular());
    for (int i = 0; i < 24; ++i) { assert(!is_full_circular()); enqueue_circular(i); }
    assert(is_full_circular());
    value = dequeue_circular(); assert(value == 0);
    value = dequeue_circular(); assert(value == 1);
    enqueue_circular(24); enqueue_circular(25);
    assert(rear == 0 && is_full_circular());
    for (int i = 2; i < 26; ++i) {
        assert(!is_empty_circular());
        value = dequeue_circular(); assert(value == i);
    }
    assert(is_empty_circular());
}

static void check_tree(void) {
    int order[10];
    const int expected[7] = {5,0,6,1,2,3,4};
    alphabet_init();
    int root = tree_connect();
    reset_linked_run();
    assert(tree_bfs(root, order) == 7);
    for (int i = 0; i < 7; ++i) assert(order[i] == expected[i]);
    assert(inserted == 7 && removed_count == 7 && peak_pending == 3);
    check_pool_restored();
    reset_linked_run();
    assert(tree_bfs(-1, order) == 0 && inserted == 0);
    check_pool_restored();
    reset_linked_run();
    assert(tree_bfs(3, order) == 1 && order[0] == 3);
    assert(inserted == 1 && removed_count == 1 && peak_pending == 1);
    check_pool_restored();
}

int main(void) {
    check_queues();
    check_tree();
    /* Group 1: mapping and initialization, including previously used data. */
    info[2][2].distance = 3;
    info[2][2].prev_size = 2;
    init_info();
    for (int y = 0; y < 7; ++y) {
        for (int x = 0; x < 7; ++x) {
            assert(info[y][x].index == 7*y+x);
            assert(same_point(points[7*y+x], (struct point){x,y}));
            assert(info[y][x].distance == 25);
            assert(info[y][x].prev_size == 0);
        }
    }
    /* Group 2: exact distances, all predecessors, ordered ties, three paths. */
    run_search((struct point){1,1});
    check_result((struct point){1,1});
    check_canonical();
    /* Group 3: independent starts cannot retain queue or predecessor state. */
    for (int y = 1; y <= 5; ++y) {
        for (int x = 1; x <= 5; ++x) {
            if (maze[y][x] == 0) continue;
            struct point start = {x,y};
            run_search(start);
            check_result(start);
        }
    }
    run_search((struct point){1,1});
    check_result((struct point){1,1});
    check_canonical();
    /* A passage can be unreachable even though its coordinate is valid. */
    maze[2][1] = 0; /* Isolate the still-valid starting passage. */
    run_search((struct point){1,1});
    assert(inserted == 1 && removed_count == 1 && peak_pending == 1);
    check_pool_restored();
    assert(get_distance((struct point){5,5}) == 25);
    assert(info[5][5].prev_size == 0 && path_count((struct point){5,5}) == 0);
    maze[2][1] = 1;
    run_search((struct point){1,1});
    check_result((struct point){1,1});
    check_canonical();
    /* Reuse is governed by peak pending work, not total discoveries.
     * Extension fixture: all 25 interior passages, every possible start. */
    int saved_maze[7][7];
    for (int y = 0; y < 7; ++y)
        for (int x = 0; x < 7; ++x) {
            saved_maze[y][x] = maze[y][x];
            maze[y][x] = x > 0 && x < 6 && y > 0 && y < 6;
        }
    int largest_open_peak = 0;
    for (int sy = 1; sy <= 5; ++sy)
        for (int sx = 1; sx <= 5; ++sx) {
            run_search((struct point){sx,sy});
            assert(inserted == 25 && removed_count == 25 && pending == 0);
            if (peak_pending > largest_open_peak) largest_open_peak = peak_pending;
            check_pool_restored();
            for (int y = 1; y <= 5; ++y)
                for (int x = 1; x <= 5; ++x) {
                    int dx = x > sx ? x-sx : sx-x;
                    int dy = y > sy ? y-sy : sy-y;
                    assert(info[y][x].distance == dx + dy);
                }
        }
    assert(largest_open_peak == 10);
    for (int y = 0; y < 7; ++y)
        for (int x = 0; x < 7; ++x) maze[y][x] = saved_maze[y][x];
    run_search((struct point){1,1});
    check_result((struct point){1,1});
    check_canonical();
    puts("PASS: linked queues, tree BFS, mapping, canonical maze, and independent searches");
    return 0;
}
