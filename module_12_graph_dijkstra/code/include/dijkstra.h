#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "dijkstra_frontier.h"
#include "weighted_graph.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define DIJKSTRA_NO_VERTEX ((size_t)WEIGHTED_GRAPH_MAX_VERTICES)
#define DIJKSTRA_INF SIZE_MAX
#define DIJKSTRA_NO_SEQUENCE SIZE_MAX
#define DIJKSTRA_MAX_POP_EVENTS DIJKSTRA_FRONTIER_MAX_ENTRIES

/*
 * A pop is stale when a better distance was recorded after this Heap entry
 * was inserted. snapshot_distance is the old value carried by that entry.
 */
typedef struct {
    size_t vertex;
    size_t snapshot_distance;
    size_t insertion_sequence;
    bool stale;
} DijkstraPopEvent;

/*
 * finalized means the shortest distance is proven. Arrays use all sixteen
 * slots so inactive slots can be checked for canonical sentinel values.
 */
typedef struct {
    size_t vertex_count;
    size_t arc_count;
    size_t source;
    size_t distance[WEIGHTED_GRAPH_MAX_VERTICES];
    size_t predecessor[WEIGHTED_GRAPH_MAX_VERTICES];
    bool finalized[WEIGHTED_GRAPH_MAX_VERTICES];
    size_t finalized_order[WEIGHTED_GRAPH_MAX_VERTICES];
    size_t finalized_count;
    DijkstraPopEvent pop_trace[DIJKSTRA_MAX_POP_EVENTS];
    size_t pop_count;
    size_t push_count;
    size_t stale_pop_count;
    size_t frontier_peak;
    size_t relaxation_attempt_count;
    size_t successful_relaxation_count;
    size_t heap_comparison_count;
} DijkstraResult;

typedef struct {
    size_t vertices[WEIGHTED_GRAPH_MAX_VERTICES];
    size_t count;
    size_t total_cost;
} DijkstraPath;

typedef enum {
    DIJKSTRA_OK = 0,
    DIJKSTRA_INVALID_ARGUMENT,
    DIJKSTRA_OUT_OF_RANGE,
    DIJKSTRA_INVALID_GRAPH,
    DIJKSTRA_ALLOCATION,
    DIJKSTRA_LIMIT,
    DIJKSTRA_COST_RANGE,
    DIJKSTRA_UNREACHABLE,
    DIJKSTRA_INVALID_RESULT
} DijkstraStatus;

/*
 * Computes all shortest path costs from source_vertex using lazy duplicate
 * Frontier entries. Only nonnegative weights below SIZE_MAX are valid.
 *
 * Before adding finite distance d and weight w, the implementation rejects
 * w > SIZE_MAX - d and also rejects a sum equal to reserved DIJKSTRA_INF.
 * Any failure preserves out_result. graph is never changed.
 */
DijkstraStatus dijkstra_shortest_paths(
    const WeightedGraph *graph,
    size_t source_vertex,
    DijkstraResult *out_result
);

/*
 * Checks all visible result relationships without reading a graph.
 */
DijkstraStatus dijkstra_result_validate(
    const DijkstraResult *result
);

/*
 * Reconstructs source through destination, including both endpoints.
 * Unreachable and malformed inputs preserve out_path.
 */
DijkstraStatus dijkstra_reconstruct_path(
    const DijkstraResult *result,
    size_t destination_vertex,
    DijkstraPath *out_path
);

const char *dijkstra_status_name(DijkstraStatus status);

#endif
