#include "graph_matrix.h"

static int graph_metadata_is_valid(const struct DirectedGraph *graph)
{
    return graph != NULL &&
        graph->vertex_count <= (size_t)GRAPH_MAX_VERTICES;
}

int graph_init(struct DirectedGraph *graph, size_t vertex_count)
{
    size_t row;
    size_t column;

    if (graph == NULL ||
        vertex_count > (size_t)GRAPH_MAX_VERTICES) {
        return 0;
    }

    /*
     * TODO(core): Use nested loops to set every cell in the full fixed grid
     * to 0. Then store vertex_count and return 1. Do not clear only the
     * active square: inactive rows and columns must also start clean.
     */
    (void)row;
    (void)column;
    return 0;
}

int graph_add_edge(
    struct DirectedGraph *graph,
    size_t from,
    size_t to
)
{
    if (!graph_metadata_is_valid(graph) ||
        from >= graph->vertex_count ||
        to >= graph->vertex_count ||
        from == to) {
        return 0;
    }

    /*
     * TODO(core): Set grid[from][to] to 1 and return 1. This is one
     * directed edge, so do not change the reverse cell.
     */
    return 0;
}

int graph_remove_edge(
    struct DirectedGraph *graph,
    size_t from,
    size_t to
)
{
    if (!graph_metadata_is_valid(graph) ||
        from >= graph->vertex_count ||
        to >= graph->vertex_count) {
        return 0;
    }

    /*
     * TODO(core): Set grid[from][to] to 0 and return 1. Clearing an already
     * empty cell still succeeds. The two indexes may be equal here because
     * clearing a diagonal cell is a harmless repair or no-op.
     */
    return 0;
}

int graph_out_degree(
    const struct DirectedGraph *graph,
    size_t vertex,
    size_t *out_degree
)
{
    size_t result = 0U;
    size_t column;

    if (out_degree == NULL ||
        !graph_metadata_is_valid(graph) ||
        vertex >= graph->vertex_count) {
        return 0;
    }

    /*
     * TODO(core): Scan the active columns in vertex's row. Add one to result
     * for every cell equal to 1. After the scan, write result to out_degree
     * and return 1. Do not change the output before all checks succeed.
     */
    (void)result;
    (void)column;
    return 0;
}
