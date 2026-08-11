#ifndef MINIMUM_SPANNING_FOREST_H
#define MINIMUM_SPANNING_FOREST_H

#include "prim_frontier.h"
#include "undirected_edge_list.h"

#include <stddef.h>
#include <stdint.h>

#define MST_MAX_SELECTED_EDGES \
    (UNDIRECTED_EDGE_LIST_MAX_VERTICES - 1U)
#define MST_NO_VERTEX \
    ((size_t)UNDIRECTED_EDGE_LIST_MAX_VERTICES)
#define MST_NO_EDGE \
    ((size_t)UNDIRECTED_EDGE_LIST_MAX_LOGICAL_EDGES)

typedef enum {
    MST_OK = 0,
    MST_INVALID_ARGUMENT,
    MST_OUT_OF_RANGE,
    MST_LIMIT,
    MST_INVALID_GRAPH,
    MST_INVALID_WEIGHT_TEXT,
    MST_WEIGHT_OUT_OF_RANGE,
    MST_ALLOCATION,
    MST_TOTAL_OUT_OF_RANGE,
    MST_INVALID_RESULT,
    MST_NOT_MINIMUM,
    MST_INVALID_STATE
} MstStatus;

typedef struct {
    size_t vertex_count;
    size_t input_edge_count;
    UndirectedEdge selected_edges[MST_MAX_SELECTED_EDGES];
    size_t selected_count;
    size_t component_count;
    int64_t total_weight;
} MstForest;

typedef struct {
    MstForest forest;
    size_t push_count;
    size_t pop_count;
    size_t stale_pop_count;
    size_t already_in_tree_pop_count;
    size_t frontier_peak;
    size_t incident_scan_count;
    size_t eligible_crossing_count;
    size_t key_improvement_count;
} PrimResult;

typedef struct {
    MstForest forest;
    size_t examined_edge_count;
    size_t cycle_skip_count;
    size_t self_loop_skip_count;
} KruskalResult;

/*
 * offsets[v] through offsets[v + 1] indexes edge_ids adjacent to v.
 * Each slice is ordered by logical edge ID. A self-loop occurs twice.
 */
typedef struct {
    size_t offsets[UNDIRECTED_EDGE_LIST_MAX_VERTICES + 1U];
    size_t edge_ids[UNDIRECTED_EDGE_LIST_MAX_INCIDENT_RECORDS];
    size_t incident_count;
} MstAdjacencyIndex;

/* Inline graph construction. Parallel edges and self-loops are accepted. */
MstStatus mst_graph_init(
    UndirectedIncidentGraph *graph,
    size_t vertex_count
);
MstStatus mst_graph_add_edge(
    UndirectedIncidentGraph *graph,
    size_t u,
    size_t v,
    int64_t weight
);
MstStatus mst_graph_validate(
    const UndirectedIncidentGraph *graph
);

/*
 * Parses one signed decimal int64_t. Surrounding ASCII whitespace and one
 * leading sign are accepted. Failure preserves out_weight.
 */
MstStatus mst_parse_weight(
    const char *text,
    int64_t *out_weight
);

/*
 * Builds an O(V + E) indexed adjacency view. out_index changes only on
 * success and must not overlap either input object.
 */
MstStatus mst_adjacency_index_build(
    const UndirectedIncidentGraph *graph,
    const UndirectedEdgeList *edge_list,
    MstAdjacencyIndex *out_index
);

/*
 * Computes the mathematical sum independent of edge order. It supports
 * cancellation beyond an overflowing prefix and changes output only when
 * the final total fits int64_t.
 */
MstStatus mst_forest_total_checked(
    const UndirectedEdge *edges,
    size_t edge_count,
    int64_t *out_total
);

MstStatus prim_minimum_spanning_forest(
    const UndirectedIncidentGraph *graph,
    PrimResult *out_result
);
MstStatus kruskal_minimum_spanning_forest(
    const UndirectedIncidentGraph *graph,
    KruskalResult *out_result
);

/*
 * Validates structure, input-edge membership, component coverage, checked
 * total, and minimum cost. This O(V + E + EV) diagnostic is not hidden in
 * either algorithm's normal operation; its minimum-cost phase is O(EV).
 */
MstStatus mst_forest_validate(
    const UndirectedIncidentGraph *graph,
    const MstForest *forest
);

const char *mst_status_name(MstStatus status);

#endif
