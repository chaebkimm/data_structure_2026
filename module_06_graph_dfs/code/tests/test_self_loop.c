#include "graph_dfs.h"

#include <stdbool.h>
#include <stdio.h>

#define CHECK(condition)                                                   \
    do {                                                                   \
        if (!(condition)) {                                                \
            fprintf(stderr, "check failed at line %d: %s\n",              \
                __LINE__, #condition);                                     \
            return 1;                                                      \
        }                                                                  \
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

static void mark_order(GraphDfsOrder *order)
{
    size_t index;

    order->count = 51U;
    for (index = 0U;
         index < (size_t)GRAPH_MAX_VERTICES;
         ++index) {
        order->vertices[index] = 200U + index;
    }
}

static bool order_is_marked(const GraphDfsOrder *order)
{
    size_t index;

    if (order->count != 51U) {
        return false;
    }
    for (index = 0U;
         index < (size_t)GRAPH_MAX_VERTICES;
         ++index) {
        if (order->vertices[index] != 200U + index) {
            return false;
        }
    }
    return true;
}

int main(void)
{
    Graph graph;
    Graph before;
    GraphDfsOrder order;

    CHECK(graph_init(&graph, 3U, GRAPH_UNDIRECTED) == GRAPH_OK);
    CHECK(graph_add_edge(&graph, 0U, 1U) == GRAPH_OK);
    before = graph;

    CHECK(
        graph_add_edge(&graph, 1U, 1U) == GRAPH_ERR_SELF_LOOP
    );
    CHECK(graphs_equal(&graph, &before));
    CHECK(graph_validate(&graph) == GRAPH_OK);

    /*
     * Direct matrix writes bypass graph_add_edge. Full validation still
     * prevents DFS from accepting the malformed simple graph.
     */
    graph.adjacency[1][1] = true;
    CHECK(graph_validate(&graph) == GRAPH_ERR_INVALID_GRAPH);

    mark_order(&order);
    CHECK(
        graph_dfs_recursive(&graph, 0U, &order) ==
        GRAPH_DFS_INVALID_GRAPH
    );
    CHECK(order_is_marked(&order));

    mark_order(&order);
    CHECK(
        graph_dfs_iterative(&graph, 0U, 3U, &order) ==
        GRAPH_DFS_INVALID_GRAPH
    );
    CHECK(order_is_marked(&order));

    puts("Self-loop rejection and malformed-input checks passed.");
    return 0;
}
