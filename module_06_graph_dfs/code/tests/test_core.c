#include "graph_dfs.h"
#include "vertex_stack.h"

#include <stdbool.h>
#include <stdio.h>

#define CHECK(condition)                                                   \
    do {                                                                   \
        if (!(condition)) {                                                \
            fprintf(stderr, "  check failed at line %d: %s\n",            \
                __LINE__, #condition);                                     \
            return false;                                                  \
        }                                                                  \
    } while (false)

typedef bool (*TestFunction)(void);

static bool make_service_graph(Graph *graph, GraphKind kind)
{
    return graph_init(graph, 6U, kind) == GRAPH_OK &&
        graph_add_edge(graph, 0U, 1U) == GRAPH_OK &&
        graph_add_edge(graph, 0U, 2U) == GRAPH_OK &&
        graph_add_edge(graph, 1U, 3U) == GRAPH_OK &&
        graph_add_edge(graph, 2U, 3U) == GRAPH_OK &&
        graph_add_edge(graph, 3U, 4U) == GRAPH_OK &&
        graph_add_edge(graph, 4U, 1U) == GRAPH_OK;
}

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

static bool order_matches(
    const GraphDfsOrder *order,
    const size_t *vertices,
    size_t count
)
{
    size_t index;

    if (order->count != count) {
        return false;
    }

    for (index = 0U; index < count; ++index) {
        if (order->vertices[index] != vertices[index]) {
            return false;
        }
    }
    return true;
}

static void mark_order(GraphDfsOrder *order)
{
    size_t index;

    order->count = 91U;
    for (index = 0U;
         index < (size_t)GRAPH_MAX_VERTICES;
         ++index) {
        order->vertices[index] = 100U + index;
    }
}

static bool order_is_marked(const GraphDfsOrder *order)
{
    size_t index;

    if (order->count != 91U) {
        return false;
    }

    for (index = 0U;
         index < (size_t)GRAPH_MAX_VERTICES;
         ++index) {
        if (order->vertices[index] != 100U + index) {
            return false;
        }
    }
    return true;
}

static bool test_recursive_directed_cycle(void)
{
    Graph graph;
    Graph before;
    GraphDfsOrder order;
    const size_t from_zero[] = {0U, 1U, 3U, 4U, 2U};
    const size_t from_two[] = {2U, 3U, 4U, 1U};
    const size_t from_five[] = {5U};

    CHECK(make_service_graph(&graph, GRAPH_DIRECTED));
    CHECK(graph_validate(&graph) == GRAPH_OK);
    before = graph;

    CHECK(
        graph_dfs_recursive(&graph, 0U, &order) == GRAPH_DFS_OK
    );
    CHECK(order_matches(&order, from_zero, 5U));

    CHECK(
        graph_dfs_recursive(&graph, 2U, &order) == GRAPH_DFS_OK
    );
    CHECK(order_matches(&order, from_two, 4U));

    CHECK(
        graph_dfs_recursive(&graph, 5U, &order) == GRAPH_DFS_OK
    );
    CHECK(order_matches(&order, from_five, 1U));
    CHECK(graphs_equal(&graph, &before));
    return true;
}

static bool test_iterative_directed_cycle_and_limits(void)
{
    Graph graph;
    Graph before;
    GraphDfsOrder order;
    const size_t from_zero[] = {0U, 1U, 3U, 4U, 2U};
    const size_t from_two[] = {2U, 3U, 4U, 1U};
    const size_t from_five[] = {5U};

    CHECK(make_service_graph(&graph, GRAPH_DIRECTED));
    before = graph;

    CHECK(
        graph_dfs_iterative(&graph, 0U, 2U, &order) == GRAPH_DFS_OK
    );
    CHECK(order_matches(&order, from_zero, 5U));

    CHECK(
        graph_dfs_iterative(&graph, 2U, 2U, &order) == GRAPH_DFS_OK
    );
    CHECK(order_matches(&order, from_two, 4U));

    CHECK(
        graph_dfs_iterative(&graph, 5U, 1U, &order) == GRAPH_DFS_OK
    );
    CHECK(order_matches(&order, from_five, 1U));

    mark_order(&order);
    CHECK(
        graph_dfs_iterative(&graph, 0U, 1U, &order) ==
        GRAPH_DFS_LIMIT
    );
    CHECK(order_is_marked(&order));

    mark_order(&order);
    CHECK(
        graph_dfs_iterative(&graph, 5U, 0U, &order) ==
        GRAPH_DFS_LIMIT
    );
    CHECK(order_is_marked(&order));
    CHECK(graphs_equal(&graph, &before));
    return true;
}

static bool test_undirected_orders_can_differ(void)
{
    Graph graph;
    GraphDfsOrder recursive_order;
    GraphDfsOrder iterative_order;
    const size_t recursive_expected[] = {0U, 1U, 3U, 2U, 4U};
    const size_t iterative_expected[] = {0U, 1U, 3U, 4U, 2U};

    CHECK(make_service_graph(&graph, GRAPH_UNDIRECTED));
    CHECK(graph_validate(&graph) == GRAPH_OK);

    CHECK(
        graph_dfs_recursive(&graph, 0U, &recursive_order) ==
        GRAPH_DFS_OK
    );
    CHECK(order_matches(
        &recursive_order,
        recursive_expected,
        5U
    ));

    CHECK(
        graph_dfs_iterative(&graph, 0U, 3U, &iterative_order) ==
        GRAPH_DFS_OK
    );
    CHECK(order_matches(
        &iterative_order,
        iterative_expected,
        5U
    ));
    CHECK(
        recursive_order.vertices[3] !=
        iterative_order.vertices[3]
    );
    return true;
}

static bool test_component_counts(void)
{
    Graph graph;
    size_t count = 77U;

    CHECK(make_service_graph(&graph, GRAPH_UNDIRECTED));
    CHECK(
        graph_count_connected_components(&graph, &count) ==
        GRAPH_DFS_OK
    );
    CHECK(count == 2U);

    CHECK(graph_init(&graph, 0U, GRAPH_UNDIRECTED) == GRAPH_OK);
    CHECK(
        graph_count_connected_components(&graph, &count) ==
        GRAPH_DFS_OK
    );
    CHECK(count == 0U);

    CHECK(graph_init(&graph, 1U, GRAPH_UNDIRECTED) == GRAPH_OK);
    CHECK(
        graph_count_connected_components(&graph, &count) ==
        GRAPH_DFS_OK
    );
    CHECK(count == 1U);

    CHECK(graph_init(&graph, 4U, GRAPH_UNDIRECTED) == GRAPH_OK);
    CHECK(
        graph_count_connected_components(&graph, &count) ==
        GRAPH_DFS_OK
    );
    CHECK(count == 4U);

    CHECK(graph_init(&graph, 1U, GRAPH_DIRECTED) == GRAPH_OK);
    count = 77U;
    CHECK(
        graph_count_connected_components(&graph, &count) ==
        GRAPH_DFS_REQUIRES_UNDIRECTED
    );
    CHECK(count == 77U);
    return true;
}

static bool test_empty_single_and_invalid_requests(void)
{
    Graph graph;
    GraphDfsOrder order;
    const size_t single[] = {0U};
    size_t count = 44U;

    CHECK(graph_init(&graph, 0U, GRAPH_DIRECTED) == GRAPH_OK);
    mark_order(&order);
    CHECK(
        graph_dfs_recursive(&graph, 0U, &order) ==
        GRAPH_DFS_OUT_OF_RANGE
    );
    CHECK(order_is_marked(&order));

    CHECK(graph_init(&graph, 1U, GRAPH_DIRECTED) == GRAPH_OK);
    CHECK(
        graph_dfs_recursive(&graph, 0U, &order) == GRAPH_DFS_OK
    );
    CHECK(order_matches(&order, single, 1U));
    CHECK(
        graph_dfs_iterative(&graph, 0U, 1U, &order) == GRAPH_DFS_OK
    );
    CHECK(order_matches(&order, single, 1U));

    mark_order(&order);
    CHECK(
        graph_dfs_recursive(NULL, 0U, &order) ==
        GRAPH_DFS_INVALID_ARGUMENT
    );
    CHECK(order_is_marked(&order));
    CHECK(
        graph_dfs_recursive(&graph, 0U, NULL) ==
        GRAPH_DFS_INVALID_ARGUMENT
    );
    CHECK(
        graph_dfs_iterative(&graph, 0U, 1U, NULL) ==
        GRAPH_DFS_INVALID_ARGUMENT
    );
    CHECK(
        graph_count_connected_components(&graph, NULL) ==
        GRAPH_DFS_INVALID_ARGUMENT
    );
    CHECK(count == 44U);
    return true;
}

static bool test_invalid_graphs_preserve_outputs(void)
{
    Graph graph;
    GraphDfsOrder order;
    size_t count = 63U;

    CHECK(graph_init(&graph, 3U, GRAPH_DIRECTED) == GRAPH_OK);
    graph.adjacency[1][1] = true;
    mark_order(&order);
    CHECK(
        graph_dfs_recursive(&graph, 0U, &order) ==
        GRAPH_DFS_INVALID_GRAPH
    );
    CHECK(order_is_marked(&order));
    CHECK(
        graph_dfs_iterative(&graph, 0U, 3U, &order) ==
        GRAPH_DFS_INVALID_GRAPH
    );
    CHECK(order_is_marked(&order));

    CHECK(graph_init(&graph, 3U, GRAPH_UNDIRECTED) == GRAPH_OK);
    graph.adjacency[0][2] = true;
    CHECK(
        graph_count_connected_components(&graph, &count) ==
        GRAPH_DFS_INVALID_GRAPH
    );
    CHECK(count == 63U);

    CHECK(graph_init(&graph, 3U, GRAPH_DIRECTED) == GRAPH_OK);
    graph.vertex_count = (size_t)GRAPH_MAX_VERTICES + 1U;
    CHECK(
        graph_dfs_recursive(&graph, 0U, &order) ==
        GRAPH_DFS_INVALID_GRAPH
    );
    CHECK(order_is_marked(&order));

    graph.vertex_count = 3U;
    graph.kind = (GraphKind)99;
    CHECK(
        graph_dfs_recursive(&graph, 0U, &order) ==
        GRAPH_DFS_INVALID_GRAPH
    );
    CHECK(order_is_marked(&order));
    return true;
}

static bool test_iterative_requested_limit_and_allocation(void)
{
    Graph graph;
    GraphDfsOrder order;

    CHECK(make_service_graph(&graph, GRAPH_DIRECTED));

    mark_order(&order);
    CHECK(
        graph_dfs_iterative(
            &graph,
            0U,
            (size_t)VERTEX_STACK_MAX_LIMIT + 1U,
            &order
        ) == GRAPH_DFS_LIMIT
    );
    CHECK(order_is_marked(&order));

    mark_order(&order);
    vertex_stack_test_fail_next_allocation();
    CHECK(
        graph_dfs_iterative(&graph, 0U, 2U, &order) ==
        GRAPH_DFS_ALLOCATION
    );
    CHECK(order_is_marked(&order));
    return true;
}

static int run_test(TestFunction function, const char *name)
{
    bool passed = function();

    printf("%s: %s\n", name, passed ? "PASS" : "FAIL");
    return passed ? 0 : 1;
}

int main(void)
{
    int failures = 0;

    failures += run_test(
        test_recursive_directed_cycle,
        "recursive directed cycle and isolated vertex"
    );
    failures += run_test(
        test_iterative_directed_cycle_and_limits,
        "iterative directed cycle and limits"
    );
    failures += run_test(
        test_undirected_orders_can_differ,
        "two valid undirected DFS orders"
    );
    failures += run_test(test_component_counts, "component counts");
    failures += run_test(
        test_empty_single_and_invalid_requests,
        "empty, single, and invalid requests"
    );
    failures += run_test(
        test_invalid_graphs_preserve_outputs,
        "invalid graph output preservation"
    );
    failures += run_test(
        test_iterative_requested_limit_and_allocation,
        "iterative requested limit and allocation"
    );

    if (failures != 0) {
        printf("%d core test group(s) failed.\n", failures);
        return 1;
    }

    puts("All core test groups passed.");
    return 0;
}
