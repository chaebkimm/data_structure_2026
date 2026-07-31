#include "graph_dfs.h"
#include "vertex_stack.h"

#include <stdbool.h>

static GraphDfsStatus validate_graph(const Graph *graph)
{
    GraphStatus status = graph_validate(graph);

    if (status == GRAPH_OK) {
        return GRAPH_DFS_OK;
    }
    if (status == GRAPH_ERR_INVALID_ARGUMENT) {
        return GRAPH_DFS_INVALID_ARGUMENT;
    }
    return GRAPH_DFS_INVALID_GRAPH;
}

static GraphDfsStatus check_traversal_request(
    const Graph *graph,
    size_t start_vertex,
    const GraphDfsOrder *out_order
)
{
    GraphDfsStatus status;

    if (out_order == NULL) {
        return GRAPH_DFS_INVALID_ARGUMENT;
    }

    status = validate_graph(graph);
    if (status != GRAPH_DFS_OK) {
        return status;
    }

    if (start_vertex >= graph->vertex_count) {
        return GRAPH_DFS_OUT_OF_RANGE;
    }

    return GRAPH_DFS_OK;
}

static GraphDfsStatus check_component_request(
    const Graph *graph,
    const size_t *out_component_count
)
{
    GraphDfsStatus status;

    if (out_component_count == NULL) {
        return GRAPH_DFS_INVALID_ARGUMENT;
    }

    status = validate_graph(graph);
    if (status != GRAPH_DFS_OK) {
        return status;
    }

    if (graph->kind != GRAPH_UNDIRECTED) {
        return GRAPH_DFS_REQUIRES_UNDIRECTED;
    }

    return GRAPH_DFS_OK;
}

static GraphDfsStatus map_stack_failure(VertexStackStatus status)
{
    if (status == VERTEX_STACK_LIMIT) {
        return GRAPH_DFS_LIMIT;
    }
    if (status == VERTEX_STACK_ALLOCATION) {
        return GRAPH_DFS_ALLOCATION;
    }
    return GRAPH_DFS_INVALID_ARGUMENT;
}

/*
 * TODO 1: Mark vertex, record it, and recursively enter each unseen outgoing
 * neighbor in ascending index order.
 */
static void recursive_visit(
    const Graph *graph,
    size_t vertex,
    bool seen[GRAPH_MAX_VERTICES],
    GraphDfsOrder *order
)
{
    (void)graph;
    (void)vertex;
    (void)seen;
    (void)order;
}

GraphDfsStatus graph_dfs_recursive(
    const Graph *graph,
    size_t start_vertex,
    GraphDfsOrder *out_order
)
{
    GraphDfsOrder candidate = {{0U}, 0U};
    bool seen[GRAPH_MAX_VERTICES] = {false};
    GraphDfsStatus status = check_traversal_request(
        graph,
        start_vertex,
        out_order
    );

    if (status != GRAPH_DFS_OK) {
        return status;
    }

    recursive_visit(graph, start_vertex, seen, &candidate);
    *out_order = candidate;
    return GRAPH_DFS_OK;
}

GraphDfsStatus graph_dfs_iterative(
    const Graph *graph,
    size_t start_vertex,
    size_t stack_limit,
    GraphDfsOrder *out_order
)
{
    VertexStack stack;
    VertexStackStatus stack_status;
    GraphDfsStatus status = check_traversal_request(
        graph,
        start_vertex,
        out_order
    );

    if (status != GRAPH_DFS_OK) {
        return status;
    }

    stack_status = vertex_stack_init(&stack, stack_limit);
    if (stack_status != VERTEX_STACK_OK) {
        return map_stack_failure(stack_status);
    }

    /*
     * TODO 2: Use the supplied Stack to perform iterative DFS. Mark a vertex
     * only after its push succeeds, record on pop, and scan neighbors from
     * the greatest active index down to zero. Build a local result and copy
     * it to out_order only after complete success.
     */
    vertex_stack_destroy(&stack);
    return GRAPH_DFS_INVALID_ARGUMENT;
}

GraphDfsStatus graph_count_connected_components(
    const Graph *graph,
    size_t *out_component_count
)
{
    GraphDfsStatus status = check_component_request(
        graph,
        out_component_count
    );

    if (status != GRAPH_DFS_OK) {
        return status;
    }

    /*
     * TODO 3: Scan possible roots in ascending order. Each unseen root starts
     * one new component. Reuse recursive_visit with one shared seen array.
     * Change out_component_count only after the whole count succeeds.
     */
    return GRAPH_DFS_INVALID_ARGUMENT;
}

const char *graph_dfs_status_name(GraphDfsStatus status)
{
    switch (status) {
        case GRAPH_DFS_OK:
            return "ok";
        case GRAPH_DFS_INVALID_ARGUMENT:
            return "invalid argument";
        case GRAPH_DFS_OUT_OF_RANGE:
            return "start vertex out of range";
        case GRAPH_DFS_INVALID_GRAPH:
            return "graph does not satisfy required representation rules";
        case GRAPH_DFS_REQUIRES_UNDIRECTED:
            return "operation requires an undirected graph";
        case GRAPH_DFS_LIMIT:
            return "vertex Stack limit reached or requested limit too large";
        case GRAPH_DFS_ALLOCATION:
            return "allocation failed";
        default:
            return "unknown GraphDfsStatus";
    }
}
