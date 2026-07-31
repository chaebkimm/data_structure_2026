#include "graph_matrix.h"

#include <stdbool.h>
#include <stdio.h>

typedef bool (*TestFunction)(void);

static unsigned int tests_run = 0U;
static unsigned int tests_failed = 0U;

#define REQUIRE(condition)                                                   \
    do {                                                                     \
        if (!(condition)) {                                                  \
            (void)printf(                                                    \
                "  requirement failed at line %d: %s\n",                    \
                __LINE__,                                                    \
                #condition                                                   \
            );                                                               \
            return false;                                                    \
        }                                                                    \
    } while (false)

static bool graphs_equal(const Graph *left, const Graph *right)
{
    size_t row;
    size_t column;

    if (left->vertex_count != right->vertex_count ||
        left->kind != right->kind) {
        return false;
    }

    for (row = 0U; row < (size_t)GRAPH_MAX_VERTICES; ++row) {
        for (column = 0U;
             column < (size_t)GRAPH_MAX_VERTICES;
             ++column) {
            if (left->adjacency[row][column] !=
                right->adjacency[row][column]) {
                return false;
            }
        }
    }

    return true;
}

static bool neighbors_equal(
    const GraphNeighbors *left,
    const GraphNeighbors *right
)
{
    size_t index;

    if (left->count != right->count) {
        return false;
    }
    for (index = 0U;
         index < (size_t)GRAPH_MAX_VERTICES;
         ++index) {
        if (left->vertices[index] != right->vertices[index]) {
            return false;
        }
    }
    return true;
}

static void run_test(const char *name, TestFunction test)
{
    bool passed;

    tests_run += 1U;
    passed = test();
    if (passed) {
        (void)printf("PASS %s\n", name);
    } else {
        tests_failed += 1U;
        (void)printf("FAIL %s\n", name);
    }
}

static bool test_all_sixteen_vertices(void)
{
    Graph graph;
    GraphNeighbors neighbors;
    size_t vertex;
    size_t degree;

    REQUIRE(
        graph_init(
            &graph,
            (size_t)GRAPH_MAX_VERTICES,
            GRAPH_UNDIRECTED
        ) == GRAPH_OK
    );

    for (vertex = 1U;
         vertex < (size_t)GRAPH_MAX_VERTICES;
         ++vertex) {
        REQUIRE(graph_add_edge(&graph, 0U, vertex) == GRAPH_OK);
    }

    REQUIRE(graph_validate(&graph) == GRAPH_OK);
    REQUIRE(graph_out_degree(&graph, 0U, &degree) == GRAPH_OK);
    REQUIRE(degree == (size_t)GRAPH_MAX_VERTICES - 1U);
    REQUIRE(
        graph_out_neighbors(&graph, 0U, &neighbors) == GRAPH_OK
    );
    REQUIRE(neighbors.count == (size_t)GRAPH_MAX_VERTICES - 1U);
    for (vertex = 1U;
         vertex < (size_t)GRAPH_MAX_VERTICES;
         ++vertex) {
        REQUIRE(neighbors.vertices[vertex - 1U] == vertex);
    }

    REQUIRE(
        graph_init(
            &graph,
            (size_t)GRAPH_MAX_VERTICES,
            GRAPH_DIRECTED
        ) == GRAPH_OK
    );
    for (vertex = 1U;
         vertex < (size_t)GRAPH_MAX_VERTICES;
         ++vertex) {
        REQUIRE(graph_add_edge(&graph, 0U, vertex) == GRAPH_OK);
    }
    REQUIRE(graph_validate(&graph) == GRAPH_OK);
    REQUIRE(graph_out_degree(&graph, 0U, &degree) == GRAPH_OK);
    REQUIRE(degree == (size_t)GRAPH_MAX_VERTICES - 1U);
    return true;
}

static bool test_directed_permission_cycle_is_valid(void)
{
    Graph graph;
    bool has_edge = false;

    REQUIRE(graph_init(&graph, 6U, GRAPH_DIRECTED) == GRAPH_OK);
    REQUIRE(graph_add_edge(&graph, 0U, 1U) == GRAPH_OK);
    REQUIRE(graph_add_edge(&graph, 0U, 2U) == GRAPH_OK);
    REQUIRE(graph_add_edge(&graph, 1U, 3U) == GRAPH_OK);
    REQUIRE(graph_add_edge(&graph, 2U, 3U) == GRAPH_OK);
    REQUIRE(graph_add_edge(&graph, 3U, 4U) == GRAPH_OK);
    REQUIRE(graph_add_edge(&graph, 4U, 1U) == GRAPH_OK);

    /*
     * 1 -> 3 -> 4 -> 1 is a directed cycle: a route that returns to its
     * starting vertex. Cycles are allowed in this graph representation.
     */
    REQUIRE(graph_validate(&graph) == GRAPH_OK);
    REQUIRE(
        graph_has_edge(&graph, 4U, 1U, &has_edge) == GRAPH_OK
    );
    REQUIRE(has_edge);
    return true;
}

static bool test_local_operations_ignore_unrelated_defects(void)
{
    Graph graph;
    GraphNeighbors neighbors;
    bool has_edge = false;
    size_t degree;

    REQUIRE(graph_init(&graph, 10U, GRAPH_UNDIRECTED) == GRAPH_OK);
    graph.adjacency[7][8] = true;
    graph.adjacency[8][7] = false;

    REQUIRE(graph_add_edge(&graph, 0U, 1U) == GRAPH_OK);
    REQUIRE(
        graph_has_edge(&graph, 0U, 1U, &has_edge) == GRAPH_OK
    );
    REQUIRE(has_edge);
    REQUIRE(graph_out_degree(&graph, 0U, &degree) == GRAPH_OK);
    REQUIRE(degree == 1U);
    REQUIRE(
        graph_out_neighbors(&graph, 0U, &neighbors) == GRAPH_OK
    );
    REQUIRE(neighbors.count == 1U);
    REQUIRE(neighbors.vertices[0] == 1U);
    REQUIRE(graph_remove_edge(&graph, 0U, 1U) == GRAPH_OK);
    REQUIRE(graph_validate(&graph) == GRAPH_ERR_INVALID_GRAPH);

    has_edge = false;
    REQUIRE(
        graph_has_edge(&graph, 7U, 8U, &has_edge) ==
        GRAPH_ERR_INVALID_GRAPH
    );
    REQUIRE(!has_edge);

    REQUIRE(graph_init(&graph, 10U, GRAPH_DIRECTED) == GRAPH_OK);
    graph.adjacency[9][9] = true;
    REQUIRE(graph_add_edge(&graph, 0U, 1U) == GRAPH_OK);
    REQUIRE(graph_out_degree(&graph, 0U, &degree) == GRAPH_OK);
    REQUIRE(degree == 1U);
    REQUIRE(graph_validate(&graph) == GRAPH_ERR_INVALID_GRAPH);
    return true;
}

static bool test_full_validator_cases(void)
{
    Graph graph;

    REQUIRE(graph_init(&graph, 0U, GRAPH_UNDIRECTED) == GRAPH_OK);
    REQUIRE(graph_validate(&graph) == GRAPH_OK);

    REQUIRE(graph_init(&graph, 3U, GRAPH_DIRECTED) == GRAPH_OK);
    graph.adjacency[GRAPH_MAX_VERTICES - 1U]
                   [GRAPH_MAX_VERTICES - 1U] = true;
    REQUIRE(graph_validate(&graph) == GRAPH_OK);
    REQUIRE(graph_add_edge(&graph, 0U, 1U) == GRAPH_OK);
    graph.adjacency[1][2] = true;
    REQUIRE(graph_validate(&graph) == GRAPH_OK);
    graph.adjacency[2][2] = true;
    REQUIRE(graph_validate(&graph) == GRAPH_ERR_INVALID_GRAPH);

    REQUIRE(graph_init(&graph, 3U, GRAPH_UNDIRECTED) == GRAPH_OK);
    graph.adjacency[0][2] = true;
    REQUIRE(graph_validate(&graph) == GRAPH_ERR_INVALID_GRAPH);
    graph.adjacency[2][0] = true;
    REQUIRE(graph_validate(&graph) == GRAPH_OK);

    graph.vertex_count = (size_t)GRAPH_MAX_VERTICES + 1U;
    REQUIRE(graph_validate(&graph) == GRAPH_ERR_INVALID_GRAPH);
    graph.vertex_count = 3U;
    graph.kind = (GraphKind)99;
    REQUIRE(graph_validate(&graph) == GRAPH_ERR_INVALID_GRAPH);
    REQUIRE(
        graph_validate(NULL) == GRAPH_ERR_INVALID_ARGUMENT
    );
    return true;
}

static bool test_every_output_type_is_preserved_on_failure(void)
{
    Graph graph;
    Graph before;
    GraphNeighbors neighbors;
    GraphNeighbors neighbors_before;
    bool has_edge = true;
    size_t degree = 91U;
    size_t index;

    REQUIRE(graph_init(&graph, 4U, GRAPH_UNDIRECTED) == GRAPH_OK);
    neighbors.count = 11U;
    for (index = 0U;
         index < (size_t)GRAPH_MAX_VERTICES;
         ++index) {
        neighbors.vertices[index] = index + 40U;
    }
    neighbors_before = neighbors;

    REQUIRE(
        graph_has_edge(&graph, 0U, 4U, &has_edge) ==
        GRAPH_ERR_OUT_OF_RANGE
    );
    REQUIRE(has_edge);
    REQUIRE(
        graph_in_degree(&graph, 4U, &degree) ==
        GRAPH_ERR_OUT_OF_RANGE
    );
    REQUIRE(degree == 91U);
    REQUIRE(
        graph_out_neighbors(&graph, 4U, &neighbors) ==
        GRAPH_ERR_OUT_OF_RANGE
    );
    REQUIRE(neighbors_equal(&neighbors, &neighbors_before));

    graph.adjacency[1][2] = true;
    before = graph;
    REQUIRE(
        graph_has_edge(&graph, 1U, 2U, &has_edge) ==
        GRAPH_ERR_INVALID_GRAPH
    );
    REQUIRE(has_edge);
    REQUIRE(
        graph_out_degree(&graph, 1U, &degree) ==
        GRAPH_ERR_INVALID_GRAPH
    );
    REQUIRE(degree == 91U);
    REQUIRE(
        graph_out_neighbors(&graph, 2U, &neighbors) ==
        GRAPH_ERR_INVALID_GRAPH
    );
    REQUIRE(neighbors_equal(&neighbors, &neighbors_before));
    REQUIRE(
        graph_add_edge(&graph, 1U, 2U) ==
        GRAPH_ERR_INVALID_GRAPH
    );
    REQUIRE(graphs_equal(&graph, &before));
    REQUIRE(
        graph_remove_edge(&graph, 1U, 2U) ==
        GRAPH_ERR_INVALID_GRAPH
    );
    REQUIRE(graphs_equal(&graph, &before));
    return true;
}

int main(void)
{
    run_test(
        "all sixteen vertices",
        test_all_sixteen_vertices
    );
    run_test(
        "directed permission cycle is valid",
        test_directed_permission_cycle_is_valid
    );
    run_test(
        "local operations ignore unrelated defects",
        test_local_operations_ignore_unrelated_defects
    );
    run_test(
        "full validator cases",
        test_full_validator_cases
    );
    run_test(
        "every output type is preserved on failure",
        test_every_output_type_is_preserved_on_failure
    );

    (void)printf(
        "\n%u extension test(s), %u failure(s)\n",
        tests_run,
        tests_failed
    );
    return tests_failed == 0U ? 0 : 1;
}
