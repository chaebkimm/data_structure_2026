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

static int graphs_equal(
    const struct DirectedGraph *left,
    const struct DirectedGraph *right
)
{
    size_t row;
    size_t column;

    if (left->vertex_count != right->vertex_count) {
        return 0;
    }
    for (row = 0U; row < (size_t)GRAPH_MAX_VERTICES; row = row + 1U) {
        for (column = 0U;
             column < (size_t)GRAPH_MAX_VERTICES;
             column = column + 1U) {
            if (left->grid[row][column] != right->grid[row][column]) {
                return 0;
            }
        }
    }
    return 1;
}

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

static void fill_pattern(struct DirectedGraph *graph, size_t vertex_count)
{
    size_t row;
    size_t column;

    graph->vertex_count = vertex_count;
    for (row = 0U; row < (size_t)GRAPH_MAX_VERTICES; row = row + 1U) {
        for (column = 0U;
             column < (size_t)GRAPH_MAX_VERTICES;
             column = column + 1U) {
            graph->grid[row][column] =
                (row + column) % 2U == 0U ? 7 : -3;
        }
    }
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

static int test_initialization_clears_full_grid(void)
{
    struct DirectedGraph graph;

    fill_pattern(&graph, 9U);
    REQUIRE(graph_init(&graph, 3U) == 1);
    REQUIRE(graph.vertex_count == 3U);
    REQUIRE(grid_is_all_zero(&graph));
    REQUIRE(graph.grid[3][0] == 0);
    REQUIRE(
        graph.grid[GRAPH_MAX_VERTICES - 1]
                  [GRAPH_MAX_VERTICES - 1] == 0
    );
    return 1;
}

static int test_initialization_rejection_preserves_graph(void)
{
    struct DirectedGraph graph;
    struct DirectedGraph before;

    fill_pattern(&graph, 4U);
    before = graph;

    REQUIRE(graph_init(NULL, 3U) == 0);
    REQUIRE(
        graph_init(
            &graph,
            (size_t)GRAPH_MAX_VERTICES + 1U
        ) == 0
    );
    REQUIRE(graphs_equal(&graph, &before));
    return 1;
}

static int test_canonical_web_app_database_trace(void)
{
    struct DirectedGraph network;
    size_t degree = 99U;

    REQUIRE(graph_init(&network, 3U) == 1);
    REQUIRE(graph_add_edge(&network, 0U, 1U) == 1);
    REQUIRE(graph_add_edge(&network, 1U, 2U) == 1);
    REQUIRE(graph_add_edge(&network, 1U, 0U) == 1);

    REQUIRE(network.grid[0][0] == 0);
    REQUIRE(network.grid[0][1] == 1);
    REQUIRE(network.grid[0][2] == 0);
    REQUIRE(network.grid[1][0] == 1);
    REQUIRE(network.grid[1][1] == 0);
    REQUIRE(network.grid[1][2] == 1);
    REQUIRE(network.grid[2][0] == 0);
    REQUIRE(network.grid[2][1] == 0);
    REQUIRE(network.grid[2][2] == 0);
    REQUIRE(graph_out_degree(&network, 1U, &degree) == 1);
    REQUIRE(degree == 2U);

    REQUIRE(graph_remove_edge(&network, 1U, 2U) == 1);
    REQUIRE(network.grid[1][0] == 1);
    REQUIRE(network.grid[1][1] == 0);
    REQUIRE(network.grid[1][2] == 0);
    REQUIRE(graph_out_degree(&network, 1U, &degree) == 1);
    REQUIRE(degree == 1U);
    return 1;
}

static int test_direction_is_independent(void)
{
    struct DirectedGraph graph;

    REQUIRE(graph_init(&graph, 3U) == 1);
    REQUIRE(graph_add_edge(&graph, 0U, 1U) == 1);
    REQUIRE(graph.grid[0][1] == 1);
    REQUIRE(graph.grid[1][0] == 0);

    REQUIRE(graph_add_edge(&graph, 1U, 0U) == 1);
    REQUIRE(graph.grid[0][1] == 1);
    REQUIRE(graph.grid[1][0] == 1);

    REQUIRE(graph_remove_edge(&graph, 0U, 1U) == 1);
    REQUIRE(graph.grid[0][1] == 0);
    REQUIRE(graph.grid[1][0] == 1);
    return 1;
}

static int test_add_rejections_preserve_graph(void)
{
    struct DirectedGraph graph;
    struct DirectedGraph before;

    REQUIRE(graph_init(&graph, 3U) == 1);
    REQUIRE(graph_add_edge(&graph, 0U, 1U) == 1);
    before = graph;

    REQUIRE(graph_add_edge(NULL, 0U, 1U) == 0);
    REQUIRE(graph_add_edge(&graph, 3U, 1U) == 0);
    REQUIRE(graph_add_edge(&graph, 1U, 3U) == 0);
    REQUIRE(graph_add_edge(&graph, 2U, 2U) == 0);
    REQUIRE(graphs_equal(&graph, &before));

    graph.vertex_count = (size_t)GRAPH_MAX_VERTICES + 1U;
    before = graph;
    REQUIRE(graph_add_edge(&graph, 0U, 1U) == 0);
    REQUIRE(graphs_equal(&graph, &before));
    return 1;
}

static int test_idempotent_add_and_remove(void)
{
    struct DirectedGraph graph;
    struct DirectedGraph after_add;

    REQUIRE(graph_init(&graph, 3U) == 1);
    REQUIRE(graph_add_edge(&graph, 0U, 2U) == 1);
    after_add = graph;
    REQUIRE(graph_add_edge(&graph, 0U, 2U) == 1);
    REQUIRE(graphs_equal(&graph, &after_add));

    REQUIRE(graph_remove_edge(&graph, 0U, 2U) == 1);
    REQUIRE(graph.grid[0][2] == 0);
    REQUIRE(graph_remove_edge(&graph, 0U, 2U) == 1);
    REQUIRE(graph.grid[0][2] == 0);

    graph.grid[1][1] = 1;
    REQUIRE(graph_remove_edge(&graph, 1U, 1U) == 1);
    REQUIRE(graph.grid[1][1] == 0);
    return 1;
}

static int test_out_degree_and_isolated_vertex(void)
{
    struct DirectedGraph graph;
    size_t degree = 99U;

    REQUIRE(graph_init(&graph, 5U) == 1);
    REQUIRE(graph_add_edge(&graph, 0U, 4U) == 1);
    REQUIRE(graph_add_edge(&graph, 0U, 2U) == 1);
    REQUIRE(graph_add_edge(&graph, 0U, 1U) == 1);
    REQUIRE(graph_add_edge(&graph, 2U, 1U) == 1);

    REQUIRE(graph_out_degree(&graph, 0U, &degree) == 1);
    REQUIRE(degree == 3U);
    REQUIRE(graph_out_degree(&graph, 1U, &degree) == 1);
    REQUIRE(degree == 0U);
    REQUIRE(graph_out_degree(&graph, 2U, &degree) == 1);
    REQUIRE(degree == 1U);
    REQUIRE(graph_out_degree(&graph, 4U, &degree) == 1);
    REQUIRE(degree == 0U);
    return 1;
}

static int test_invalid_metadata_and_output_preservation(void)
{
    struct DirectedGraph graph;
    struct DirectedGraph before;
    size_t degree = 73U;

    REQUIRE(graph_init(&graph, 3U) == 1);
    REQUIRE(graph_add_edge(&graph, 0U, 1U) == 1);
    before = graph;

    REQUIRE(graph_remove_edge(NULL, 0U, 1U) == 0);
    REQUIRE(graph_remove_edge(&graph, 3U, 1U) == 0);
    REQUIRE(graph_remove_edge(&graph, 1U, 3U) == 0);
    REQUIRE(graphs_equal(&graph, &before));

    REQUIRE(graph_out_degree(NULL, 0U, &degree) == 0);
    REQUIRE(degree == 73U);
    REQUIRE(graph_out_degree(&graph, 0U, NULL) == 0);
    REQUIRE(graph_out_degree(&graph, 3U, &degree) == 0);
    REQUIRE(degree == 73U);

    graph.vertex_count = (size_t)GRAPH_MAX_VERTICES + 1U;
    before = graph;
    REQUIRE(graph_remove_edge(&graph, 0U, 1U) == 0);
    REQUIRE(graphs_equal(&graph, &before));
    REQUIRE(graph_out_degree(&graph, 0U, &degree) == 0);
    REQUIRE(degree == 73U);
    return 1;
}

int main(void)
{
    run_test(
        "initialization clears the full grid",
        test_initialization_clears_full_grid
    );
    run_test(
        "initialization rejection preserves graph",
        test_initialization_rejection_preserves_graph
    );
    run_test(
        "canonical Web-App-Database trace",
        test_canonical_web_app_database_trace
    );
    run_test("direction is independent", test_direction_is_independent);
    run_test(
        "add rejections preserve graph",
        test_add_rejections_preserve_graph
    );
    run_test(
        "idempotent add and remove",
        test_idempotent_add_and_remove
    );
    run_test(
        "out-degree and isolated vertex",
        test_out_degree_and_isolated_vertex
    );
    run_test(
        "invalid metadata and output preservation",
        test_invalid_metadata_and_output_preservation
    );

    (void)printf(
        "\n%d core test(s), %d failure(s)\n",
        tests_run,
        tests_failed
    );
    return tests_failed == 0 ? 0 : 1;
}
