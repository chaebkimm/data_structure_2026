#ifndef GRAPH_ADJ_LIST_H
#define GRAPH_ADJ_LIST_H

#include "graph_matrix.h"

#include <stdbool.h>
#include <stddef.h>

/*
 * One dynamic array stores the ascending outgoing neighbors of one vertex.
 * size counts live entries; capacity counts allocated size_t slots.
 */
typedef struct {
    size_t *data;
    size_t size;
    size_t capacity;
} GraphNeighborArray;

/*
 * This adjacency list owns every non-NULL neighbor-array allocation.
 * Rows at indexes vertex_count through 15 remain canonical empty rows.
 */
typedef struct {
    size_t vertex_count;
    GraphKind kind;
    GraphNeighborArray neighbors[GRAPH_MAX_VERTICES];
} GraphAdjList;

typedef enum {
    GRAPH_ADJ_LIST_OK = 0,
    GRAPH_ADJ_LIST_INVALID_ARGUMENT,
    GRAPH_ADJ_LIST_OUT_OF_RANGE,
    GRAPH_ADJ_LIST_SELF_LOOP,
    GRAPH_ADJ_LIST_EDGE_EXISTS,
    GRAPH_ADJ_LIST_EDGE_ABSENT,
    GRAPH_ADJ_LIST_INVALID_GRAPH,
    GRAPH_ADJ_LIST_ALLOCATION
} GraphAdjListStatus;

/*
 * Initializes an all-zero or previously destroyed object. No neighbor
 * storage is requested until an edge needs it. Failure preserves graph.
 */
GraphAdjListStatus graph_adj_list_init(
    GraphAdjList *graph,
    size_t vertex_count,
    GraphKind kind
);

/*
 * Checks visible ownership fields, sorted unique active neighbors, inactive
 * empty rows, and reciprocal storage for an undirected graph.
 */
GraphAdjListStatus graph_adj_list_validate(
    const GraphAdjList *graph
);

/*
 * Edge mutations preserve the complete graph on every failure. An
 * undirected add stages both possible growth allocations before committing.
 */
GraphAdjListStatus graph_adj_list_add_edge(
    GraphAdjList *graph,
    size_t from_vertex,
    size_t to_vertex
);

GraphAdjListStatus graph_adj_list_remove_edge(
    GraphAdjList *graph,
    size_t from_vertex,
    size_t to_vertex
);

GraphAdjListStatus graph_adj_list_has_edge(
    const GraphAdjList *graph,
    size_t from_vertex,
    size_t to_vertex,
    bool *out_has_edge
);

GraphAdjListStatus graph_adj_list_out_neighbors(
    const GraphAdjList *graph,
    size_t vertex,
    GraphNeighbors *out_neighbors
);

/*
 * Releases all owned rows and restores the all-zero directed empty state.
 * Passing NULL is a no-op. Every other input must be initialized or already
 * destroyed.
 */
void graph_adj_list_destroy(GraphAdjList *graph);

const char *graph_adj_list_status_name(GraphAdjListStatus status);

#ifdef GRAPH_BFS_TESTING
/*
 * Fails one allocation after exactly successful_allocations successful
 * allocation attempts. Zero therefore fails the next attempt.
 */
void graph_adj_list_test_fail_allocation_after(
    size_t successful_allocations
);

size_t graph_adj_list_test_live_array_count(void);
#endif

#endif
