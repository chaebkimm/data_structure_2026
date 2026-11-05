/* Run the unchanged lecture source through valid callers only. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../student/lab.c"

#define CHECK(condition) do { \
    if (!(condition)) { \
        fprintf(stderr, "FAIL at line %d: %s\n", __LINE__, #condition); \
        exit(EXIT_FAILURE); \
    } \
} while (0)

static int same_point(struct point a, struct point b) {
    return a.y == b.y && a.x == b.x;
}

static int adjacent(struct point a, struct point b) {
    return abs(a.y - b.y) + abs(a.x - b.x) == 1;
}

/* Repeated relaxation supplies an oracle without the lab's queue/iterator. */
static void expected_distances(struct point start, int expected[N][N]) {
    for (int y = 0; y < N; ++y) {
        for (int x = 0; x < N; ++x) {
            expected[y][x] = INF;
        }
    }
    if (maze[start.y][start.x] == 0) { return; }
    expected[start.y][start.x] = 0;
    for (int pass = 0; pass < N * N; ++pass) {
        for (int y = 1; y < N - 1; ++y) {
            for (int x = 1; x < N - 1; ++x) {
                if (maze[y][x] == 0) { continue; }
                int nearest = expected[y][x];
                if (expected[y - 1][x] + 1 < nearest) {
                    nearest = expected[y - 1][x] + 1;
                }
                if (expected[y + 1][x] + 1 < nearest) {
                    nearest = expected[y + 1][x] + 1;
                }
                if (expected[y][x - 1] + 1 < nearest) {
                    nearest = expected[y][x - 1] + 1;
                }
                if (expected[y][x + 1] + 1 < nearest) {
                    nearest = expected[y][x + 1] + 1;
                }
                expected[y][x] = nearest;
            }
        }
    }
}

/* Linear storage retains the insertion order after the queue is drained. */
static int verify_search(struct point start) {
    int expected[N][N];
    int before[N][N];
    int seen[N][N] = {{0}};
    memcpy(before, maze, sizeof before);
    expected_distances(start, expected);
    bfs(start);
    CHECK(memcmp(before, maze, sizeof before) == 0);
    int reached = 0;
    for (int y = 0; y < N; ++y) {
        for (int x = 0; x < N; ++x) {
            CHECK(distance[y][x] == expected[y][x]);
            if (expected[y][x] != INF) { ++reached; }
        }
    }
    CHECK(is_empty_queue());
    CHECK(front == reached);
    CHECK(rear == reached - 1);
    CHECK(reached <= (N - 2) * (N - 2));
    for (int i = 0; i < reached; ++i) {
        struct point p = queue[i];
        CHECK(p.y > 0 && p.y < N - 1 && p.x > 0 && p.x < N - 1);
        CHECK(maze[p.y][p.x] != 0);
        CHECK(seen[p.y][p.x] == 0);
        seen[p.y][p.x] = 1;
        CHECK(expected[p.y][p.x] != INF);
        if (i == 0) {
            CHECK(same_point(p, start));
        } else {
            CHECK(get_distance(queue[i - 1]) <= get_distance(p));
        }
    }
    return reached;
}

static void test_iterator_and_queue(void) {
    const struct point neighbors[] = {{2, 3}, {2, 1}, {3, 2}, {1, 2}};
    init_iter((struct point){2, 2});
    for (int i = 0; i < 4; ++i) {
        CHECK(has_next_iter());
        CHECK(same_point(next_iter(), neighbors[i]));
    }
    CHECK(!has_next_iter());
    init_iter((struct point){1, 1});
    CHECK(same_point(next_iter(), (struct point){1, 2}));

    init_queue();
    CHECK(front == 0 && rear == -1 && is_empty_queue());
    for (int i = 0; i < N * N; ++i) {
        enqueue((struct point){i / N, i % N});
    }
    CHECK(rear == N * N - 1);
    for (int i = 0; i < N * N; ++i) {
        CHECK(!is_empty_queue());
        CHECK(same_point(dequeue(), (struct point){i / N, i % N}));
    }
    CHECK(is_empty_queue() && front == N * N && rear == N * N - 1);
    init_queue();
    CHECK(front == 0 && rear == -1 && is_empty_queue());
}

static void test_canonical_trace(void) {
    const struct point order[] = {
        {1, 1}, {2, 1}, {2, 2}, {3, 1},
        {2, 3}, {3, 2}, {3, 3}, {1, 3}
    };
    const int expected[N][N] = {
        {INF, INF, INF, INF, INF},
        {INF,   0, INF,   4, INF},
        {INF,   1,   2,   3, INF},
        {INF,   2,   3,   4, INF},
        {INF, INF, INF, INF, INF}
    };
    CHECK(verify_search((struct point){1, 1}) == 8);
    CHECK(memcmp(distance, expected, sizeof expected) == 0);
    for (int i = 0; i < 8; ++i) { CHECK(same_point(queue[i], order[i])); }

    /* First earlier adjacent vertex is the discoverer in this FIFO order. */
    int arrivals[N * N] = {0};
    for (int i = 1; i < 8; ++i) {
        int parent = -1;
        for (int j = 0; j < i; ++j) {
            if (adjacent(queue[j], queue[i]) &&
                get_distance(queue[j]) + 1 == get_distance(queue[i])) {
                parent = j;
                break;
            }
        }
        CHECK(parent >= 0);
        ++arrivals[parent];
    }
    int pending = 1;
    int peak = pending;
    for (int i = 0; i < 8; ++i) {
        pending += arrivals[i] - 1;
        if (pending > peak) { peak = pending; }
    }
    CHECK(pending == 0 && peak == 3);
    CHECK(verify_search((struct point){3, 3}) == 8);
    CHECK(get_distance((struct point){1, 1}) == 4);
    CHECK(verify_search((struct point){0, 0}) == 0);
    CHECK(verify_search((struct point){1, 2}) == 0);
    maze[2][1] = 0;
    CHECK(verify_search((struct point){1, 1}) == 1);
    CHECK(get_distance((struct point){3, 3}) == INF);
    maze[2][1] = 1;
    CHECK(verify_search((struct point){1, 1}) == 8);
}

static void test_all_bordered_mazes(void) {
    int original[N][N];
    memcpy(original, maze, sizeof original);
    /* All 512 wall/passage arrangements of the nine interior cells. */
    for (unsigned mask = 0; mask < (1U << 9); ++mask) {
        unsigned bit = 0;
        for (int y = 1; y < N - 1; ++y) {
            for (int x = 1; x < N - 1; ++x) {
                maze[y][x] = (int)((mask >> bit) & 1U);
                ++bit;
            }
        }
        for (int y = 0; y < N; ++y) {
            for (int x = 0; x < N; ++x) {
                (void)verify_search((struct point){y, x});
            }
        }
    }
    memcpy(maze, original, sizeof original);
    CHECK(verify_search((struct point){1, 1}) == 8);
}

int main(void) {
    test_iterator_and_queue();
    test_canonical_trace();
    test_all_bordered_mazes();
    puts("PASS: array queue, iterator, maze distances, resets, and 12800 bordered-maze searches");
    return EXIT_SUCCESS;
}
