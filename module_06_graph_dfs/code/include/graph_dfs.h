#ifndef GRAPH_DFS_H
#define GRAPH_DFS_H

#include "graph_matrix.h"

#include <stddef.h>

/*
 * The first count entries contain the vertices reached by one traversal,
 * in visit order. Every reached vertex appears exactly once.
 */
typedef struct {
    size_t vertices[GRAPH_MAX_VERTICES];
    size_t count;
} GraphDfsOrder;

/* A status is a named result returned by a DFS operation. */
typedef enum {
    GRAPH_DFS_OK = 0,
    GRAPH_DFS_INVALID_ARGUMENT,
    GRAPH_DFS_OUT_OF_RANGE,
    GRAPH_DFS_INVALID_GRAPH,
    GRAPH_DFS_REQUIRES_UNDIRECTED,
    GRAPH_DFS_LIMIT,
    GRAPH_DFS_ALLOCATION
} GraphDfsStatus;

/*
 * Follows outgoing edges from start_vertex. The recursive version records a
 * vertex when its call begins and checks outgoing neighbors in ascending
 * index order. A vertex already seen is not entered again.
 *
 * Both directed and undirected graphs are accepted. The entire active stored
 * graph is validated before traversal. On every failure, out_order is
 * unchanged.
 */
GraphDfsStatus graph_dfs_recursive(
    const Graph *graph,
    size_t start_vertex,
    GraphDfsOrder *out_order
);

/*
 * Performs DFS with the supplied vertex-ID Stack. A vertex is marked seen
 * only after it is pushed successfully, so no vertex is pushed more than
 * once. A popped vertex is recorded, then its outgoing neighbors are checked
 * in descending index order. This makes a lower-index neighbor the next pop
 * when no other route marks pending work first.
 *
 * stack_limit may be zero and may not exceed GRAPH_MAX_VERTICES. On every
 * failure, out_order is unchanged.
 */
GraphDfsStatus graph_dfs_iterative(
    const Graph *graph,
    size_t start_vertex,
    size_t stack_limit,
    GraphDfsOrder *out_order
);

/*
 * Counts connected components in an undirected graph. An isolated vertex is
 * one component, and an empty undirected graph has zero components. Directed
 * graphs return GRAPH_DFS_REQUIRES_UNDIRECTED. The output changes only on
 * success.
 */
GraphDfsStatus graph_count_connected_components(
    const Graph *graph,
    size_t *out_component_count
);

const char *graph_dfs_status_name(GraphDfsStatus status);

#endif
