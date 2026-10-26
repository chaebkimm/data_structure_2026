#ifndef GRAPH_BFS_H
#define GRAPH_BFS_H

#include "graph_adj_list.h"
#include "graph_matrix.h"

#include <stdbool.h>
#include <stddef.h>

/*
 * Sixteen is outside the valid vertex range and above every possible
 * minimum-hop distance in this bounded graph.
 */
#define GRAPH_BFS_NO_VERTEX ((size_t)GRAPH_MAX_VERTICES)
#define GRAPH_BFS_NO_DISTANCE ((size_t)GRAPH_MAX_VERTICES)

typedef struct {
    size_t vertex_count;
    size_t source;
    size_t visit_order[GRAPH_MAX_VERTICES];
    size_t visit_count;
    bool discovered[GRAPH_MAX_VERTICES];
    size_t distance[GRAPH_MAX_VERTICES];
    size_t predecessor[GRAPH_MAX_VERTICES];
} GraphBfsResult;

typedef struct {
    size_t vertices[GRAPH_MAX_VERTICES];
    size_t count;
} GraphBfsPath;

typedef enum {
    GRAPH_BFS_OK = 0,
    GRAPH_BFS_INVALID_ARGUMENT,
    GRAPH_BFS_OUT_OF_RANGE,
    GRAPH_BFS_INVALID_GRAPH,
    GRAPH_BFS_LIMIT,
    GRAPH_BFS_UNREACHABLE,
    GRAPH_BFS_INVALID_RESULT
} GraphBfsStatus;

/*
 * Both traversals validate the complete graph, follow outgoing edges, and
 * inspect possible neighbors in ascending vertex order. A vertex becomes
 * discovered only after its enqueue succeeds. visit_order records dequeue
 * order. queue_limit may be zero through 16.
 *
 * Every failure preserves out_result. Neither operation changes its graph.
 */
GraphBfsStatus graph_bfs_matrix(
    const Graph *graph,
    size_t source_vertex,
    size_t queue_limit,
    GraphBfsResult *out_result
);

GraphBfsStatus graph_bfs_list(
    const GraphAdjList *graph,
    size_t source_vertex,
    size_t queue_limit,
    GraphBfsResult *out_result
);

/*
 * Reconstructs source through destination, including both endpoints. The
 * one-vertex source path has zero hops. Unreachable and malformed results
 * preserve out_path.
 */
GraphBfsStatus graph_bfs_reconstruct_path(
    const GraphBfsResult *result,
    size_t destination_vertex,
    GraphBfsPath *out_path
);

/*
 * Checks all visible result relationships without reading a graph. It can
 * verify a bounded predecessor certificate, but cannot prove that each
 * predecessor edge existed in the original graph.
 */
GraphBfsStatus graph_bfs_result_validate(
    const GraphBfsResult *result
);

const char *graph_bfs_status_name(GraphBfsStatus status);

#endif
