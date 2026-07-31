#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

enum {
    VERTEX_COUNT = 3,
    CALL_BUDGET = 8
};

/*
 * This standalone program contains one intentional traversal defect. Its
 * call budget makes the behavior observable without allowing uncontrolled
 * recursion.
 */
static bool faulty_visit(
    const bool adjacency[VERTEX_COUNT][VERTEX_COUNT],
    size_t vertex,
    bool seen[VERTEX_COUNT],
    size_t *calls_left
)
{
    size_t neighbor;

    if (*calls_left == 0U) {
        return false;
    }

    *calls_left -= 1U;
    printf("enter %zu\n", vertex);

    for (neighbor = 0U; neighbor < (size_t)VERTEX_COUNT; ++neighbor) {
        if (adjacency[vertex][neighbor] && !seen[neighbor]) {
            if (!faulty_visit(
                    adjacency,
                    neighbor,
                    seen,
                    calls_left
                )) {
                return false;
            }
        }
    }

    seen[vertex] = true;
    return true;
}

int main(void)
{
    bool adjacency[VERTEX_COUNT][VERTEX_COUNT] = {{false}};
    bool seen[VERTEX_COUNT] = {false};
    size_t calls_left = (size_t)CALL_BUDGET;
    bool completed;

    adjacency[0][1] = true;
    adjacency[1][2] = true;
    adjacency[2][0] = true;

    completed = faulty_visit(adjacency, 0U, seen, &calls_left);
    if (!completed) {
        puts("STOP: safety budget exhausted before DFS finished.");
    } else {
        puts("DFS finished.");
    }

    return 0;
}
