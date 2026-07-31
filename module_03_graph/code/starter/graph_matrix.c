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

    /*
     * TODO(core):
     * 1. Use nested loops to set every matrix cell to false. Clear all 16
     *    rows and columns, even when fewer vertices are active.
     * 2. Store vertex_count and kind in graph.
     * 3. Return GRAPH_OK.
     *
     * All checks happen above, so an error leaves graph unchanged.
     */
    (void)row;
    (void)column;
    return GRAPH_ERR_INVALID_GRAPH;
}

/*
 * Instructor-supplied whole-matrix validator. V is the active vertex count,
 * so examining V rows by V columns takes time proportional to V squared.
 */
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

        /*
         * TODO(core): Set the selected cell to true and return GRAPH_OK.
         * A directed edge changes one cell.
         */
        return GRAPH_ERR_INVALID_GRAPH;
    }

    reverse = graph->adjacency[to_vertex][from_vertex];
    if (forward != reverse) {
        return GRAPH_ERR_INVALID_GRAPH;
    }
    if (forward) {
        return GRAPH_ERR_EDGE_EXISTS;
    }

    /*
     * TODO(core): Set both mirror cells to true, then return GRAPH_OK.
     * Mirror cells reverse the two indexes: [a][b] and [b][a].
     */
    return GRAPH_ERR_INVALID_GRAPH;
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

        /*
         * TODO(core): Set the selected cell to false and return GRAPH_OK.
         */
        return GRAPH_ERR_INVALID_GRAPH;
    }

    reverse = graph->adjacency[to_vertex][from_vertex];
    if (forward != reverse) {
        return GRAPH_ERR_INVALID_GRAPH;
    }
    if (!forward) {
        return GRAPH_ERR_EDGE_ABSENT;
    }

    /*
     * TODO(core): Set both mirror cells to false, then return GRAPH_OK.
     */
    return GRAPH_ERR_INVALID_GRAPH;
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

    /*
     * TODO(core): Copy result to out_has_edge and return GRAPH_OK.
     * Write the output only after all checks pass.
     */
    (void)result;
    return GRAPH_ERR_INVALID_GRAPH;
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

    /*
     * TODO(core): Scan row vertex. Add one to result for every true cell.
     * After the scan, copy result to out_degree and return GRAPH_OK.
     */
    (void)result;
    (void)other;
    return GRAPH_ERR_INVALID_GRAPH;
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

    /*
     * TODO(core): Scan column vertex. Add one to result for every true
     * cell. Then copy result to out_degree and return GRAPH_OK.
     */
    (void)result;
    (void)other;
    return GRAPH_ERR_INVALID_GRAPH;
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

    /*
     * TODO(guided): Scan row vertex from index 0 upward. For each true cell,
     * store the index in result.vertices[result.count], then increase
     * result.count. Copy the completed result to out_neighbors and return
     * GRAPH_OK. Scanning upward produces ascending order.
     */
    (void)result;
    (void)other;
    return GRAPH_ERR_INVALID_GRAPH;
}

/*
 * Instructor-supplied status text.
 */
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
