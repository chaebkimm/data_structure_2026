#include "graph_matrix.h"

static bool graph_kind_is_valid(GraphKind kind)
{
    return kind == GRAPH_DIRECTED || kind == GRAPH_UNDIRECTED;
}

/*
 * A container check verifies only the Graph object's count and kind. It does
 * not scan the matrix.
 */
static GraphStatus graph_check_container(const Graph *graph)
{
    if (graph == NULL) {
        return GRAPH_ERR_INVALID_ARGUMENT;
    }

    if (graph->vertex_count > (size_t)GRAPH_MAX_VERTICES ||
        !graph_kind_is_valid(graph->kind)) {
        return GRAPH_ERR_INVALID_GRAPH;
    }

    return GRAPH_OK;
}

static GraphStatus graph_check_vertex(
    const Graph *graph,
    size_t vertex
)
{
    GraphStatus status;

    status = graph_check_container(graph);
    if (status != GRAPH_OK) {
        return status;
    }

    if (vertex >= graph->vertex_count) {
        return GRAPH_ERR_OUT_OF_RANGE;
    }

    return GRAPH_OK;
}

static GraphStatus graph_check_pair(
    const Graph *graph,
    size_t from_vertex,
    size_t to_vertex
)
{
    GraphStatus status;

    status = graph_check_container(graph);
    if (status != GRAPH_OK) {
        return status;
    }

    if (from_vertex >= graph->vertex_count ||
        to_vertex >= graph->vertex_count) {
        return GRAPH_ERR_OUT_OF_RANGE;
    }

    if (from_vertex == to_vertex) {
        return GRAPH_ERR_SELF_LOOP;
    }

    return GRAPH_OK;
}

/*
 * "Incident" means touching the selected vertex. This local check does not
 * reject a defect elsewhere in the matrix.
 */
static GraphStatus graph_check_incident(
    const Graph *graph,
    size_t vertex
)
{
    GraphStatus status;
    size_t other;

    status = graph_check_vertex(graph, vertex);
    if (status != GRAPH_OK) {
        return status;
    }

    if (graph->adjacency[vertex][vertex]) {
        return GRAPH_ERR_INVALID_GRAPH;
    }

    if (graph->kind == GRAPH_UNDIRECTED) {
        for (other = 0U; other < graph->vertex_count; ++other) {
            if (graph->adjacency[vertex][other] !=
                graph->adjacency[other][vertex]) {
                return GRAPH_ERR_INVALID_GRAPH;
            }
        }
    }

    return GRAPH_OK;
}

GraphStatus graph_init(
    Graph *graph,
    size_t vertex_count,
    GraphKind kind
)
{
    size_t row;
    size_t column;

    if (graph == NULL) {
        return GRAPH_ERR_INVALID_ARGUMENT;
    }

    if (vertex_count > (size_t)GRAPH_MAX_VERTICES) {
        return GRAPH_ERR_OUT_OF_RANGE;
    }

    if (!graph_kind_is_valid(kind)) {
        return GRAPH_ERR_INVALID_ARGUMENT;
    }

    for (row = 0U; row < (size_t)GRAPH_MAX_VERTICES; ++row) {
        for (column = 0U;
             column < (size_t)GRAPH_MAX_VERTICES;
             ++column) {
            graph->adjacency[row][column] = false;
        }
    }

    graph->vertex_count = vertex_count;
    graph->kind = kind;
    return GRAPH_OK;
}

GraphStatus graph_validate(const Graph *graph)
{
    GraphStatus status;
    size_t from_vertex;
    size_t to_vertex;

    status = graph_check_container(graph);
    if (status != GRAPH_OK) {
        return status;
    }

    for (from_vertex = 0U;
         from_vertex < graph->vertex_count;
         ++from_vertex) {
        for (to_vertex = 0U;
             to_vertex < graph->vertex_count;
             ++to_vertex) {
            if (from_vertex == to_vertex &&
                graph->adjacency[from_vertex][to_vertex]) {
                return GRAPH_ERR_INVALID_GRAPH;
            }

            if (graph->kind == GRAPH_UNDIRECTED &&
                graph->adjacency[from_vertex][to_vertex] !=
                    graph->adjacency[to_vertex][from_vertex]) {
                return GRAPH_ERR_INVALID_GRAPH;
            }
        }
    }

    return GRAPH_OK;
}

GraphStatus graph_add_edge(
    Graph *graph,
    size_t from_vertex,
    size_t to_vertex
)
{
    GraphStatus status;
    bool forward;
    bool reverse;

    status = graph_check_pair(graph, from_vertex, to_vertex);
    if (status != GRAPH_OK) {
        return status;
    }

    forward = graph->adjacency[from_vertex][to_vertex];
    if (graph->kind == GRAPH_DIRECTED) {
        if (forward) {
            return GRAPH_ERR_EDGE_EXISTS;
        }

        graph->adjacency[from_vertex][to_vertex] = true;
        return GRAPH_OK;
    }

    reverse = graph->adjacency[to_vertex][from_vertex];
    if (forward != reverse) {
        return GRAPH_ERR_INVALID_GRAPH;
    }
    if (forward) {
        return GRAPH_ERR_EDGE_EXISTS;
    }

    graph->adjacency[from_vertex][to_vertex] = true;
    graph->adjacency[to_vertex][from_vertex] = true;
    return GRAPH_OK;
}

GraphStatus graph_remove_edge(
    Graph *graph,
    size_t from_vertex,
    size_t to_vertex
)
{
    GraphStatus status;
    bool forward;
    bool reverse;

    status = graph_check_pair(graph, from_vertex, to_vertex);
    if (status != GRAPH_OK) {
        return status;
    }

    forward = graph->adjacency[from_vertex][to_vertex];
    if (graph->kind == GRAPH_DIRECTED) {
        if (!forward) {
            return GRAPH_ERR_EDGE_ABSENT;
        }

        graph->adjacency[from_vertex][to_vertex] = false;
        return GRAPH_OK;
    }

    reverse = graph->adjacency[to_vertex][from_vertex];
    if (forward != reverse) {
        return GRAPH_ERR_INVALID_GRAPH;
    }
    if (!forward) {
        return GRAPH_ERR_EDGE_ABSENT;
    }

    graph->adjacency[from_vertex][to_vertex] = false;
    graph->adjacency[to_vertex][from_vertex] = false;
    return GRAPH_OK;
}

GraphStatus graph_has_edge(
    const Graph *graph,
    size_t from_vertex,
    size_t to_vertex,
    bool *out_has_edge
)
{
    GraphStatus status;
    bool result;

    if (out_has_edge == NULL) {
        return GRAPH_ERR_INVALID_ARGUMENT;
    }

    status = graph_check_pair(graph, from_vertex, to_vertex);
    if (status != GRAPH_OK) {
        return status;
    }

    result = graph->adjacency[from_vertex][to_vertex];
    if (graph->kind == GRAPH_UNDIRECTED &&
        result != graph->adjacency[to_vertex][from_vertex]) {
        return GRAPH_ERR_INVALID_GRAPH;
    }

    *out_has_edge = result;
    return GRAPH_OK;
}

GraphStatus graph_out_degree(
    const Graph *graph,
    size_t vertex,
    size_t *out_degree
)
{
    GraphStatus status;
    size_t result = 0U;
    size_t other;

    if (out_degree == NULL) {
        return GRAPH_ERR_INVALID_ARGUMENT;
    }

    status = graph_check_incident(graph, vertex);
    if (status != GRAPH_OK) {
        return status;
    }

    for (other = 0U; other < graph->vertex_count; ++other) {
        if (graph->adjacency[vertex][other]) {
            result += 1U;
        }
    }

    *out_degree = result;
    return GRAPH_OK;
}

GraphStatus graph_in_degree(
    const Graph *graph,
    size_t vertex,
    size_t *out_degree
)
{
    GraphStatus status;
    size_t result = 0U;
    size_t other;

    if (out_degree == NULL) {
        return GRAPH_ERR_INVALID_ARGUMENT;
    }

    status = graph_check_incident(graph, vertex);
    if (status != GRAPH_OK) {
        return status;
    }

    for (other = 0U; other < graph->vertex_count; ++other) {
        if (graph->adjacency[other][vertex]) {
            result += 1U;
        }
    }

    *out_degree = result;
    return GRAPH_OK;
}

GraphStatus graph_out_neighbors(
    const Graph *graph,
    size_t vertex,
    GraphNeighbors *out_neighbors
)
{
    GraphStatus status;
    GraphNeighbors result = { 0U, { 0U } };
    size_t other;

    if (out_neighbors == NULL) {
        return GRAPH_ERR_INVALID_ARGUMENT;
    }

    status = graph_check_incident(graph, vertex);
    if (status != GRAPH_OK) {
        return status;
    }

    for (other = 0U; other < graph->vertex_count; ++other) {
        if (graph->adjacency[vertex][other]) {
            result.vertices[result.count] = other;
            result.count += 1U;
        }
    }

    *out_neighbors = result;
    return GRAPH_OK;
}

const char *graph_status_name(GraphStatus status)
{
    switch (status) {
        case GRAPH_OK:
            return "ok";
        case GRAPH_ERR_INVALID_ARGUMENT:
            return "invalid argument";
        case GRAPH_ERR_OUT_OF_RANGE:
            return "vertex count or index out of range";
        case GRAPH_ERR_SELF_LOOP:
            return "self-loops are not allowed";
        case GRAPH_ERR_EDGE_EXISTS:
            return "edge already exists";
        case GRAPH_ERR_EDGE_ABSENT:
            return "edge does not exist";
        case GRAPH_ERR_INVALID_GRAPH:
            return "graph does not satisfy required representation rules";
        default:
            return "unknown GraphStatus";
    }
}
