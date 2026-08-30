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

    for (row = 0U; row < (size_t)GRAPH_MAX_VERTICES; row = row + 1U) {
        for (column = 0U;
             column < (size_t)GRAPH_MAX_VERTICES;
             column = column + 1U) {
            graph->grid[row][column] = 0;
        }
    }
    graph->vertex_count = vertex_count;
    return 1;
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

    graph->grid[from][to] = 1;
    return 1;
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

    graph->grid[from][to] = 0;
    return 1;
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

    for (column = 0U;
         column < graph->vertex_count;
         column = column + 1U) {
        if (graph->grid[vertex][column] == 1) {
            result = result + 1U;
        }
    }

    *out_degree = result;
    return 1;
}
