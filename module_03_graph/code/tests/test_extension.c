#include "graph_matrix.h"

#include <stdio.h>

static int tests_run = 0;
static int tests_failed = 0;

#define REQUIRE(condition)                                                   \
    do {                                                                     \
        if (!(condition)) {                                                  \
            (void)fprintf(                                                   \
                stderr,                                                      \
                "  requirement failed at %s:%d: %s\n",                     \
                __FILE__,                                                    \
                __LINE__,                                                    \
                #condition                                                   \
            );                                                               \
            return 0;                                                        \
        }                                                                    \
    } while (0)

static int grid_is_all_zero(const struct DirectedGraph *graph)
{
    size_t row;
    size_t column;

    for (row = 0U; row < (size_t)GRAPH_MAX_VERTICES; row = row + 1U) {
        for (column = 0U;
             column < (size_t)GRAPH_MAX_VERTICES;
             column = column + 1U) {
            if (graph->grid[row][column] != 0) {
                return 0;
            }
        }
    }
    return 1;
}

static void run_test(const char *name, int (*test)(void))
{
    int passed;

    tests_run = tests_run + 1;
    passed = test();
    if (passed) {
        (void)printf("PASS %s\n", name);
    } else {
        tests_failed = tests_failed + 1;
        (void)printf("FAIL %s\n", name);
    }
}

static int test_zero_vertex_graph(void)
{
    struct DirectedGraph graph;
    size_t degree = 41U;

    REQUIRE(graph_init(&graph, 0U) == 1);
    REQUIRE(graph.vertex_count == 0U);
    REQUIRE(grid_is_all_zero(&graph));
    REQUIRE(graph_add_edge(&graph, 0U, 0U) == 0);
    REQUIRE(graph_remove_edge(&graph, 0U, 0U) == 0);
    REQUIRE(graph_out_degree(&graph, 0U, &degree) == 0);
    REQUIRE(degree == 41U);
    REQUIRE(grid_is_all_zero(&graph));
    return 1;
}

static int test_single_vertex_diagonal_behavior(void)
{
    struct DirectedGraph graph;
    size_t degree = 41U;

    REQUIRE(graph_init(&graph, 1U) == 1);
    REQUIRE(graph_add_edge(&graph, 0U, 0U) == 0);
    REQUIRE(graph.grid[0][0] == 0);
    REQUIRE(graph_remove_edge(&graph, 0U, 0U) == 1);
    REQUIRE(graph.grid[0][0] == 0);
    REQUIRE(graph_out_degree(&graph, 0U, &degree) == 1);
    REQUIRE(degree == 0U);
    return 1;
}

static int test_full_capacity_dense_directed_graph(void)
{
    struct DirectedGraph graph;
    size_t row;
    size_t column;
    size_t degree;

    REQUIRE(
        graph_init(&graph, (size_t)GRAPH_MAX_VERTICES) == 1
    );
    for (row = 0U; row < graph.vertex_count; row = row + 1U) {
        for (column = 0U;
             column < graph.vertex_count;
             column = column + 1U) {
            if (row != column) {
                REQUIRE(graph_add_edge(&graph, row, column) == 1);
            }
        }
    }

    for (row = 0U; row < graph.vertex_count; row = row + 1U) {
        REQUIRE(graph.grid[row][row] == 0);
        REQUIRE(graph_out_degree(&graph, row, &degree) == 1);
        REQUIRE(
            degree == (size_t)GRAPH_MAX_VERTICES - 1U
        );
    }
    return 1;
}

static int test_directed_cycle_and_shared_destination(void)
{
    struct DirectedGraph graph;
    size_t degree;

    REQUIRE(graph_init(&graph, 5U) == 1);
    REQUIRE(graph_add_edge(&graph, 0U, 1U) == 1);
    REQUIRE(graph_add_edge(&graph, 1U, 2U) == 1);
    REQUIRE(graph_add_edge(&graph, 2U, 0U) == 1);
    REQUIRE(graph_add_edge(&graph, 3U, 1U) == 1);

    REQUIRE(graph.grid[0][1] == 1);
    REQUIRE(graph.grid[1][2] == 1);
    REQUIRE(graph.grid[2][0] == 1);
    REQUIRE(graph.grid[3][1] == 1);
    REQUIRE(graph.grid[1][0] == 0);
    REQUIRE(graph_out_degree(&graph, 0U, &degree) == 1);
    REQUIRE(degree == 1U);
    REQUIRE(graph_out_degree(&graph, 3U, &degree) == 1);
    REQUIRE(degree == 1U);
    REQUIRE(graph_out_degree(&graph, 4U, &degree) == 1);
    REQUIRE(degree == 0U);
    return 1;
}

static int test_reinitialize_smaller_clears_inactive_storage(void)
{
    struct DirectedGraph graph;

    REQUIRE(
        graph_init(&graph, (size_t)GRAPH_MAX_VERTICES) == 1
    );
    REQUIRE(
        graph_add_edge(
            &graph,
            (size_t)GRAPH_MAX_VERTICES - 1U,
            0U
        ) == 1
    );
    REQUIRE(
        graph_add_edge(
            &graph,
            0U,
            (size_t)GRAPH_MAX_VERTICES - 1U
        ) == 1
    );

    REQUIRE(graph_init(&graph, 3U) == 1);
    REQUIRE(graph.vertex_count == 3U);
    REQUIRE(grid_is_all_zero(&graph));
    return 1;
}

int main(void)
{
    run_test("zero-vertex graph", test_zero_vertex_graph);
    run_test(
        "single-vertex diagonal behavior",
        test_single_vertex_diagonal_behavior
    );
    run_test(
        "full-capacity dense directed graph",
        test_full_capacity_dense_directed_graph
    );
    run_test(
        "directed cycle and shared destination",
        test_directed_cycle_and_shared_destination
    );
    run_test(
        "reinitialize smaller clears inactive storage",
        test_reinitialize_smaller_clears_inactive_storage
    );

    (void)printf(
        "\n%d extension test(s), %d failure(s)\n",
        tests_run,
        tests_failed
    );
    return tests_failed == 0 ? 0 : 1;
}
