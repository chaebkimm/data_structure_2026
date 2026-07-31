#include "graph_matrix.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

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

static bool add_permission_edges(Graph *graph)
{
    /*
     * 0 Gateway, 1 Web, 2 Admin, 3 Database, 4 Monitor, 5 Archive.
     * Archive is isolated, meaning it has no incident edges.
     */
    return
        graph_add_edge(graph, 0U, 1U) == GRAPH_OK &&
        graph_add_edge(graph, 0U, 2U) == GRAPH_OK &&
        graph_add_edge(graph, 1U, 3U) == GRAPH_OK &&
        graph_add_edge(graph, 2U, 3U) == GRAPH_OK &&
        graph_add_edge(graph, 3U, 4U) == GRAPH_OK &&
        graph_add_edge(graph, 4U, 1U) == GRAPH_OK;
}

static bool test_empty_boundaries_and_preservation(void)
{
    Graph graph;
    Graph before;
    GraphNeighbors neighbors;
    GraphNeighbors neighbors_before;
    bool has_edge = true;
    size_t degree = 73U;
    size_t row;
    size_t column;

    graph.vertex_count = 7U;
    graph.kind = GRAPH_UNDIRECTED;
    for (row = 0U; row < (size_t)GRAPH_MAX_VERTICES; ++row) {
        for (column = 0U;
             column < (size_t)GRAPH_MAX_VERTICES;
             ++column) {
            graph.adjacency[row][column] =
                (row + column) % 2U == 0U;
        }
    }
    before = graph;

    REQUIRE(
        graph_init(NULL, 3U, GRAPH_DIRECTED) ==
        GRAPH_ERR_INVALID_ARGUMENT
    );
    REQUIRE(
        graph_init(
            &graph,
            (size_t)GRAPH_MAX_VERTICES + 1U,
            GRAPH_DIRECTED
        ) == GRAPH_ERR_OUT_OF_RANGE
    );
    REQUIRE(graphs_equal(&graph, &before));
    REQUIRE(
        graph_init(&graph, 3U, (GraphKind)99) ==
        GRAPH_ERR_INVALID_ARGUMENT
    );
    REQUIRE(graphs_equal(&graph, &before));

    REQUIRE(graph_init(&graph, 0U, GRAPH_DIRECTED) == GRAPH_OK);
    REQUIRE(graph.vertex_count == 0U);
    REQUIRE(graph.kind == GRAPH_DIRECTED);
    REQUIRE(graph_validate(&graph) == GRAPH_OK);
    for (row = 0U; row < (size_t)GRAPH_MAX_VERTICES; ++row) {
        for (column = 0U;
             column < (size_t)GRAPH_MAX_VERTICES;
             ++column) {
            REQUIRE(!graph.adjacency[row][column]);
        }
    }

    REQUIRE(graph_init(&graph, 0U, GRAPH_UNDIRECTED) == GRAPH_OK);
    REQUIRE(graph_validate(&graph) == GRAPH_OK);
    REQUIRE(
        graph_init(
            &graph,
            (size_t)GRAPH_MAX_VERTICES,
            GRAPH_DIRECTED
        ) == GRAPH_OK
    );
    REQUIRE(
        graph.vertex_count == (size_t)GRAPH_MAX_VERTICES
    );
    REQUIRE(graph_validate(&graph) == GRAPH_OK);

    /* Restore an empty graph for the inactive-index preservation checks. */
    REQUIRE(graph_init(&graph, 0U, GRAPH_DIRECTED) == GRAPH_OK);

    neighbors.count = 8U;
    for (row = 0U; row < (size_t)GRAPH_MAX_VERTICES; ++row) {
        neighbors.vertices[row] = row + 20U;
    }
    neighbors_before = neighbors;

    REQUIRE(
        graph_has_edge(&graph, 0U, 0U, &has_edge) ==
        GRAPH_ERR_OUT_OF_RANGE
    );
    REQUIRE(has_edge);
    REQUIRE(
        graph_out_degree(&graph, 0U, &degree) ==
        GRAPH_ERR_OUT_OF_RANGE
    );
    REQUIRE(degree == 73U);
    REQUIRE(
        graph_out_neighbors(&graph, 0U, &neighbors) ==
        GRAPH_ERR_OUT_OF_RANGE
    );
    REQUIRE(neighbors_equal(&neighbors, &neighbors_before));
    REQUIRE(
        graph_has_edge(&graph, 0U, 0U, NULL) ==
        GRAPH_ERR_INVALID_ARGUMENT
    );
    REQUIRE(
        graph_out_degree(&graph, 0U, NULL) ==
        GRAPH_ERR_INVALID_ARGUMENT
    );
    REQUIRE(
        graph_in_degree(&graph, 0U, NULL) ==
        GRAPH_ERR_INVALID_ARGUMENT
    );
    REQUIRE(
        graph_out_neighbors(&graph, 0U, NULL) ==
        GRAPH_ERR_INVALID_ARGUMENT
    );
    return true;
}

static bool test_directed_edge_operations(void)
{
    Graph graph;
    Graph before;
    bool has_edge = false;

    REQUIRE(graph_init(&graph, 6U, GRAPH_DIRECTED) == GRAPH_OK);
    REQUIRE(add_permission_edges(&graph));
    REQUIRE(graph_validate(&graph) == GRAPH_OK);

    REQUIRE(
        graph_has_edge(&graph, 4U, 1U, &has_edge) == GRAPH_OK
    );
    REQUIRE(has_edge);
    REQUIRE(
        graph_has_edge(&graph, 1U, 4U, &has_edge) == GRAPH_OK
    );
    REQUIRE(!has_edge);

    before = graph;
    REQUIRE(
        graph_add_edge(&graph, 0U, 1U) ==
        GRAPH_ERR_EDGE_EXISTS
    );
    REQUIRE(graphs_equal(&graph, &before));

    REQUIRE(graph_remove_edge(&graph, 2U, 3U) == GRAPH_OK);
    REQUIRE(
        graph_has_edge(&graph, 2U, 3U, &has_edge) == GRAPH_OK
    );
    REQUIRE(!has_edge);
    before = graph;
    REQUIRE(
        graph_remove_edge(&graph, 2U, 3U) ==
        GRAPH_ERR_EDGE_ABSENT
    );
    REQUIRE(graphs_equal(&graph, &before));
    REQUIRE(graph_validate(&graph) == GRAPH_OK);
    return true;
}

static bool test_undirected_symmetry_duplicates_and_self_loops(void)
{
    Graph graph;
    Graph before;
    bool has_edge = false;

    REQUIRE(graph_init(&graph, 4U, GRAPH_UNDIRECTED) == GRAPH_OK);
    REQUIRE(graph_add_edge(&graph, 1U, 3U) == GRAPH_OK);
    REQUIRE(graph.adjacency[1][3]);
    REQUIRE(graph.adjacency[3][1]);
    REQUIRE(graph_validate(&graph) == GRAPH_OK);

    REQUIRE(
        graph_has_edge(&graph, 3U, 1U, &has_edge) == GRAPH_OK
    );
    REQUIRE(has_edge);
    before = graph;
    REQUIRE(
        graph_add_edge(&graph, 3U, 1U) ==
        GRAPH_ERR_EDGE_EXISTS
    );
    REQUIRE(graphs_equal(&graph, &before));

    REQUIRE(graph_remove_edge(&graph, 3U, 1U) == GRAPH_OK);
    REQUIRE(!graph.adjacency[1][3]);
    REQUIRE(!graph.adjacency[3][1]);
    before = graph;
    REQUIRE(
        graph_remove_edge(&graph, 1U, 3U) ==
        GRAPH_ERR_EDGE_ABSENT
    );
    REQUIRE(graphs_equal(&graph, &before));

    has_edge = true;
    REQUIRE(
        graph_add_edge(&graph, 2U, 2U) ==
        GRAPH_ERR_SELF_LOOP
    );
    REQUIRE(
        graph_remove_edge(&graph, 2U, 2U) ==
        GRAPH_ERR_SELF_LOOP
    );
    REQUIRE(
        graph_has_edge(&graph, 2U, 2U, &has_edge) ==
        GRAPH_ERR_SELF_LOOP
    );
    REQUIRE(has_edge);
    REQUIRE(graphs_equal(&graph, &before));
    return true;
}

static bool test_directed_and_undirected_degrees(void)
{
    Graph graph;
    const size_t expected_out[6] = { 2U, 1U, 1U, 1U, 1U, 0U };
    const size_t expected_in[6] = { 0U, 2U, 1U, 2U, 1U, 0U };
    size_t vertex;
    size_t degree;

    REQUIRE(graph_init(&graph, 6U, GRAPH_DIRECTED) == GRAPH_OK);
    REQUIRE(add_permission_edges(&graph));

    for (vertex = 0U; vertex < 6U; ++vertex) {
        REQUIRE(
            graph_out_degree(&graph, vertex, &degree) == GRAPH_OK
        );
        REQUIRE(degree == expected_out[vertex]);
        REQUIRE(
            graph_in_degree(&graph, vertex, &degree) == GRAPH_OK
        );
        REQUIRE(degree == expected_in[vertex]);
    }

    REQUIRE(graph_init(&graph, 4U, GRAPH_UNDIRECTED) == GRAPH_OK);
    REQUIRE(graph_add_edge(&graph, 0U, 1U) == GRAPH_OK);
    REQUIRE(graph_add_edge(&graph, 0U, 3U) == GRAPH_OK);
    REQUIRE(graph_add_edge(&graph, 1U, 2U) == GRAPH_OK);
    REQUIRE(graph_out_degree(&graph, 0U, &degree) == GRAPH_OK);
    REQUIRE(degree == 2U);
    REQUIRE(graph_in_degree(&graph, 0U, &degree) == GRAPH_OK);
    REQUIRE(degree == 2U);
    REQUIRE(graph_out_degree(&graph, 1U, &degree) == GRAPH_OK);
    REQUIRE(degree == 2U);
    return true;
}

static bool test_neighbors_are_ascending(void)
{
    Graph graph;
    GraphNeighbors neighbors;

    REQUIRE(graph_init(&graph, 6U, GRAPH_DIRECTED) == GRAPH_OK);
    REQUIRE(graph_add_edge(&graph, 0U, 4U) == GRAPH_OK);
    REQUIRE(graph_add_edge(&graph, 0U, 1U) == GRAPH_OK);
    REQUIRE(graph_add_edge(&graph, 0U, 3U) == GRAPH_OK);

    REQUIRE(
        graph_out_neighbors(&graph, 0U, &neighbors) == GRAPH_OK
    );
    REQUIRE(neighbors.count == 3U);
    REQUIRE(neighbors.vertices[0] == 1U);
    REQUIRE(neighbors.vertices[1] == 3U);
    REQUIRE(neighbors.vertices[2] == 4U);

    REQUIRE(
        graph_out_neighbors(&graph, 5U, &neighbors) == GRAPH_OK
    );
    REQUIRE(neighbors.count == 0U);
    return true;
}

static bool test_malformed_incident_state_is_rejected(void)
{
    Graph graph;
    Graph before;
    GraphNeighbors neighbors;
    GraphNeighbors neighbors_before;
    bool has_edge = true;
    size_t degree = 81U;
    size_t index;

    REQUIRE(graph_init(&graph, 4U, GRAPH_UNDIRECTED) == GRAPH_OK);
    graph.adjacency[1][2] = true;
    before = graph;

    neighbors.count = 9U;
    for (index = 0U;
         index < (size_t)GRAPH_MAX_VERTICES;
         ++index) {
        neighbors.vertices[index] = index + 30U;
    }
    neighbors_before = neighbors;

    REQUIRE(
        graph_has_edge(&graph, 1U, 2U, &has_edge) ==
        GRAPH_ERR_INVALID_GRAPH
    );
    REQUIRE(has_edge);
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
    REQUIRE(
        graph_out_degree(&graph, 1U, &degree) ==
        GRAPH_ERR_INVALID_GRAPH
    );
    REQUIRE(degree == 81U);
    REQUIRE(
        graph_in_degree(&graph, 2U, &degree) ==
        GRAPH_ERR_INVALID_GRAPH
    );
    REQUIRE(degree == 81U);
    REQUIRE(
        graph_out_neighbors(&graph, 1U, &neighbors) ==
        GRAPH_ERR_INVALID_GRAPH
    );
    REQUIRE(neighbors_equal(&neighbors, &neighbors_before));
    REQUIRE(graph_validate(&graph) == GRAPH_ERR_INVALID_GRAPH);

    REQUIRE(graph_init(&graph, 4U, GRAPH_DIRECTED) == GRAPH_OK);
    graph.adjacency[3][3] = true;
    degree = 81U;
    REQUIRE(
        graph_out_degree(&graph, 3U, &degree) ==
        GRAPH_ERR_INVALID_GRAPH
    );
    REQUIRE(degree == 81U);
    REQUIRE(graph_validate(&graph) == GRAPH_ERR_INVALID_GRAPH);
    return true;
}

static bool test_status_names(void)
{
    REQUIRE(strcmp(graph_status_name(GRAPH_OK), "ok") == 0);
    REQUIRE(
        strcmp(
            graph_status_name(GRAPH_ERR_INVALID_ARGUMENT),
            "invalid argument"
        ) == 0
    );
    REQUIRE(
        strcmp(
            graph_status_name(GRAPH_ERR_OUT_OF_RANGE),
            "vertex count or index out of range"
        ) == 0
    );
    REQUIRE(
        strcmp(
            graph_status_name(GRAPH_ERR_SELF_LOOP),
            "self-loops are not allowed"
        ) == 0
    );
    REQUIRE(
        strcmp(
            graph_status_name(GRAPH_ERR_EDGE_EXISTS),
            "edge already exists"
        ) == 0
    );
    REQUIRE(
        strcmp(
            graph_status_name(GRAPH_ERR_EDGE_ABSENT),
            "edge does not exist"
        ) == 0
    );
    REQUIRE(
        strcmp(
            graph_status_name(GRAPH_ERR_INVALID_GRAPH),
            "graph does not satisfy required representation rules"
        ) == 0
    );
    REQUIRE(
        strcmp(graph_status_name((GraphStatus)99), "unknown GraphStatus") ==
        0
    );
    return true;
}

int main(void)
{
    run_test(
        "empty graph, boundaries, and preservation",
        test_empty_boundaries_and_preservation
    );
    run_test(
        "directed edge operations",
        test_directed_edge_operations
    );
    run_test(
        "undirected symmetry, duplicates, and self-loops",
        test_undirected_symmetry_duplicates_and_self_loops
    );
    run_test(
        "directed and undirected degrees",
        test_directed_and_undirected_degrees
    );
    run_test(
        "neighbors are ascending",
        test_neighbors_are_ascending
    );
    run_test(
        "malformed incident state is rejected",
        test_malformed_incident_state_is_rejected
    );
    run_test("status names", test_status_names);

    (void)printf(
        "\n%u test(s), %u failure(s)\n",
        tests_run,
        tests_failed
    );
    return tests_failed == 0U ? 0 : 1;
}
