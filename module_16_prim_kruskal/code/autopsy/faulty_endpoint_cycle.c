#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

typedef struct {
    size_t u;
    size_t v;
    int weight;
} TinyEdge;

static size_t find_root(const size_t parent[3], size_t vertex)
{
    size_t current = vertex;

    while (parent[current] != current) {
        current = parent[current];
    }
    return current;
}

static void merge_roots(size_t parent[3], size_t left, size_t right)
{
    size_t left_root = find_root(parent, left);
    size_t right_root = find_root(parent, right);

    if (left_root != right_root) {
        parent[right_root] = left_root;
    }
}

int main(void)
{
    static const TinyEdge edges[3] = {
        {0U, 1U, 1},
        {1U, 2U, 2},
        {0U, 2U, 3}
    };
    size_t faulty_selected = 0U;
    int faulty_total = 0;
    size_t correct_parent[3] = {0U, 1U, 2U};
    size_t correct_selected = 0U;
    int correct_total = 0;
    size_t index;

    for (index = 0U; index < 3U; ++index) {
        /*
         * Fault: different endpoint numbers do not prove that the endpoints
         * remain in different connected groups.
         */
        if (edges[index].u != edges[index].v) {
            faulty_selected += 1U;
            faulty_total += edges[index].weight;
        }
    }

    for (index = 0U; index < 3U; ++index) {
        size_t left_root = find_root(correct_parent, edges[index].u);
        size_t right_root = find_root(correct_parent, edges[index].v);

        if (left_root != right_root) {
            correct_selected += 1U;
            correct_total += edges[index].weight;
            merge_roots(
                correct_parent,
                edges[index].u,
                edges[index].v
            );
        }
    }

    (void)printf(
        "Faulty raw-endpoint rule: %zu edges, total %d, cycle: yes\n",
        faulty_selected,
        faulty_total
    );
    (void)printf(
        "Correct representative rule: %zu edges, total %d, cycle: no\n",
        correct_selected,
        correct_total
    );

    return faulty_selected == 3U &&
            faulty_total == 6 &&
            correct_selected == 2U &&
            correct_total == 3
        ? 0
        : 1;
}
