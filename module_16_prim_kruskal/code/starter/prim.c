#include "minimum_spanning_forest.h"

#include "prim_frontier.h"
#include "undirected_edge_list.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef struct {
    UndirectedEdgeList edges;
    MstAdjacencyIndex adjacency;
    PrimFrontier frontier;
    PrimResult result;
    bool in_tree[UNDIRECTED_EDGE_LIST_MAX_VERTICES];
    bool has_best[UNDIRECTED_EDGE_LIST_MAX_VERTICES];
    int64_t best_key[UNDIRECTED_EDGE_LIST_MAX_VERTICES];
    size_t best_parent[UNDIRECTED_EDGE_LIST_MAX_VERTICES];
    size_t best_edge[UNDIRECTED_EDGE_LIST_MAX_VERTICES];
    size_t selected_vertex_count;
} PrimWorkspace;

static MstStatus map_edge_status(UndirectedEdgeListStatus status)
{
    switch (status) {
        case UNDIRECTED_EDGE_LIST_OK:
            return MST_OK;
        case UNDIRECTED_EDGE_LIST_INVALID_ARGUMENT:
            return MST_INVALID_ARGUMENT;
        case UNDIRECTED_EDGE_LIST_OUT_OF_RANGE:
            return MST_OUT_OF_RANGE;
        case UNDIRECTED_EDGE_LIST_LIMIT:
            return MST_LIMIT;
        case UNDIRECTED_EDGE_LIST_INVALID_GRAPH:
        case UNDIRECTED_EDGE_LIST_INVALID_LIST:
        default:
            return MST_INVALID_GRAPH;
    }
}

static MstStatus map_frontier_status(PrimFrontierStatus status)
{
    switch (status) {
        case PRIM_FRONTIER_OK:
            return MST_OK;
        case PRIM_FRONTIER_INVALID_ARGUMENT:
            return MST_INVALID_ARGUMENT;
        case PRIM_FRONTIER_ALLOCATION:
            return MST_ALLOCATION;
        case PRIM_FRONTIER_OUT_OF_RANGE:
        case PRIM_FRONTIER_FULL:
        case PRIM_FRONTIER_SEQUENCE_EXHAUSTED:
            return MST_LIMIT;
        case PRIM_FRONTIER_EMPTY:
        case PRIM_FRONTIER_INVALID_STATE:
        default:
            return MST_INVALID_STATE;
    }
}

static MstStatus relax_from_vertex(
    PrimWorkspace *workspace,
    size_t vertex
)
{
    /*
     * TODO 2: Scan this vertex's indexed adjacency slice. Ignore self-loops
     * and neighbors already in the forest. On a strict key improvement,
     * push the lazy Heap snapshot before committing best key/parent/edge,
     * then update the required counters and peak.
     */
    (void)workspace;
    (void)vertex;
    return MST_INVALID_STATE;
}

static MstStatus process_all_components(PrimWorkspace *workspace)
{
    /*
     * TODO 1: Use one monotone cursor to restart at the smallest unvisited
     * vertex without rescanning earlier IDs. Pop the stable Heap, reject
     * stale tuples before checking in_tree, select each current edge, and
     * call relax_from_vertex after a vertex enters the forest.
     */
    (void)relax_from_vertex;
    (void)workspace;
    return MST_INVALID_STATE;
}

MstStatus prim_minimum_spanning_forest(
    const UndirectedIncidentGraph *graph,
    PrimResult *out_result
)
{
    PrimWorkspace workspace = {0};
    UndirectedEdgeListStatus edge_status;
    PrimFrontierStatus frontier_status;
    MstStatus status;
    int64_t total = INT64_C(0);
    size_t limit;

    if (graph == NULL || out_result == NULL) {
        return MST_INVALID_ARGUMENT;
    }

    edge_status = undirected_edge_list_build(graph, &workspace.edges);
    if (edge_status != UNDIRECTED_EDGE_LIST_OK) {
        return map_edge_status(edge_status);
    }
    status = mst_adjacency_index_build(
        graph,
        &workspace.edges,
        &workspace.adjacency
    );
    if (status != MST_OK) {
        return status;
    }

    workspace.result.forest.vertex_count = graph->vertex_count;
    workspace.result.forest.input_edge_count =
        graph->logical_edge_count;
    limit = graph->logical_edge_count + graph->vertex_count;
    frontier_status = prim_frontier_init(
        &workspace.frontier,
        limit
    );
    if (frontier_status != PRIM_FRONTIER_OK) {
        return map_frontier_status(frontier_status);
    }

    status = process_all_components(&workspace);
    if (status == MST_OK) {
        status = mst_forest_total_checked(
            workspace.result.forest.selected_edges,
            workspace.result.forest.selected_count,
            &total
        );
    }
    if (status == MST_OK) {
        workspace.result.forest.total_weight = total;
    }

    prim_frontier_destroy(&workspace.frontier);
    if (status != MST_OK) {
        return status;
    }

    *out_result = workspace.result;
    return MST_OK;
}
