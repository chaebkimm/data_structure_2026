#ifndef GRAPH_MATRIX_H
#define GRAPH_MATRIX_H

#include <stdbool.h>
#include <stddef.h>

#define GRAPH_MAX_VERTICES 16U

/*
 * A graph stores vertices (items) and edges (connections between items).
 * A directed edge has one direction. An undirected edge connects both ways.
 */
typedef enum {
    GRAPH_DIRECTED = 0,
    GRAPH_UNDIRECTED
} GraphKind;

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
 * A true cell at adjacency[from][to] records one directed connection.
 * vertex_count selects the active rows and columns.
 */
typedef struct {
    size_t vertex_count;
    GraphKind kind;
    bool adjacency[GRAPH_MAX_VERTICES][GRAPH_MAX_VERTICES];
} Graph;

typedef struct {
    size_t count;
    size_t vertices[GRAPH_MAX_VERTICES];
} GraphNeighbors;

GraphStatus graph_init(
    Graph *graph,
    size_t vertex_count,
    GraphKind kind
);

GraphStatus graph_validate(const Graph *graph);

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

GraphStatus graph_out_neighbors(
    const Graph *graph,
    size_t vertex,
    GraphNeighbors *out_neighbors
);

const char *graph_status_name(GraphStatus status);

#endif
