#ifndef GRAPH_MATRIX_H
#define GRAPH_MATRIX_H

#include <stdbool.h>
#include <stddef.h>

#define GRAPH_MAX_VERTICES 16U

/*
 * A graph stores vertices (items) and edges (connections between items).
 * A directed edge has one direction, such as 2 -> 5. An undirected edge
 * connects both ways, such as 2 -- 5. An enum is a C type limited to named
 * choices; GraphKind names the two supported choices.
 */
typedef enum {
    GRAPH_DIRECTED = 0,
    GRAPH_UNDIRECTED
} GraphKind;

/*
 * GraphStatus reports success or the reason an operation failed.
 */
typedef enum {
    GRAPH_OK = 0,
    GRAPH_ERR_INVALID_ARGUMENT,
    GRAPH_ERR_OUT_OF_RANGE,
    GRAPH_ERR_SELF_LOOP,
    GRAPH_ERR_EDGE_EXISTS,
    GRAPH_ERR_EDGE_ABSENT,
    GRAPH_ERR_INVALID_GRAPH
} GraphStatus;

/*
 * An adjacency matrix is a square table. A true value at [from][to] records
 * an edge from one vertex index to another. An index is a numbered position.
 *
 * The matrix has fixed storage for 16 vertices. vertex_count says how many
 * rows and columns are currently active.
 */
typedef struct {
    size_t vertex_count;
    GraphKind kind;
    bool adjacency[GRAPH_MAX_VERTICES][GRAPH_MAX_VERTICES];
} Graph;

/*
 * A neighbor is a vertex reached by one outgoing edge. count says how many
 * entries at the start of vertices contain results.
 */
typedef struct {
    size_t count;
    size_t vertices[GRAPH_MAX_VERTICES];
} GraphNeighbors;

/*
 * Initializes a graph with indexes 0 through vertex_count - 1. An empty
 * graph has zero vertices and is valid. Success clears the entire 16 by 16
 * matrix, including inactive positions. Failure leaves graph unchanged.
 */
GraphStatus graph_init(
    Graph *graph,
    size_t vertex_count,
    GraphKind kind
);

/*
 * Validates the whole active matrix. A validator is a function that checks
 * whether stated rules hold. Self-loops are forbidden, so every active
 * diagonal entry [v][v] must be false. An undirected matrix must also be
 * symmetric: [a][b] must equal [b][a].
 *
 * This full check examines V by V entries, where V is vertex_count.
 */
GraphStatus graph_validate(const Graph *graph);

/*
 * Checked edge operations. from_vertex and to_vertex must be different
 * active indexes. Undirected operations update or inspect both matching
 * matrix cells. These functions check only the selected pair, not the whole
 * matrix.
 */
GraphStatus graph_add_edge(
    Graph *graph,
    size_t from_vertex,
    size_t to_vertex
);

GraphStatus graph_remove_edge(
    Graph *graph,
    size_t from_vertex,
    size_t to_vertex
);

GraphStatus graph_has_edge(
    const Graph *graph,
    size_t from_vertex,
    size_t to_vertex,
    bool *out_has_edge
);

/*
 * "Incident" means touching the selected vertex. A degree is a count of
 * incident edges. Out-degree counts edges leaving a vertex; in-degree
 * counts edges entering it. Each function checks only matrix cells incident
 * to the selected vertex and then scans one row or column. An output is
 * changed only when GRAPH_OK is returned.
 */
GraphStatus graph_out_degree(
    const Graph *graph,
    size_t vertex,
    size_t *out_degree
);

GraphStatus graph_in_degree(
    const Graph *graph,
    size_t vertex,
    size_t *out_degree
);

/*
 * Reports outgoing neighbors in ascending index order. The result object is
 * changed only when GRAPH_OK is returned.
 */
GraphStatus graph_out_neighbors(
    const Graph *graph,
    size_t vertex,
    GraphNeighbors *out_neighbors
);

const char *graph_status_name(GraphStatus status);

#endif
