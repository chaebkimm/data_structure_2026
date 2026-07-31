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

static void record_successful_push(PrimWorkspace *workspace)
{
    workspace->result.push_count += 1U;
    workspace->result.key_improvement_count += 1U;
    if (workspace->frontier.size >
        workspace->result.frontier_peak) {
        workspace->result.frontier_peak =
            workspace->frontier.size;
    }
}

static MstStatus relax_from_vertex(
    PrimWorkspace *workspace,
    size_t vertex
)
{
    size_t position;

    for (position = workspace->adjacency.offsets[vertex];
         position < workspace->adjacency.offsets[vertex + 1U];
         ++position) {
        size_t edge_id = workspace->adjacency.edge_ids[position];
        const UndirectedEdge *edge = &workspace->edges.edges[edge_id];
        size_t neighbor;
        PrimFrontierStatus frontier_status;

        workspace->result.incident_scan_count += 1U;
        if (edge->u == edge->v) {
            continue;
        }
        neighbor = edge->u == vertex ? edge->v : edge->u;
        if (workspace->in_tree[neighbor]) {
            continue;
        }

        workspace->result.eligible_crossing_count += 1U;
        if (workspace->has_best[neighbor] &&
            edge->weight >= workspace->best_key[neighbor]) {
            continue;
        }

        frontier_status = prim_frontier_push(
            &workspace->frontier,
            neighbor,
            edge->weight,
            vertex,
            edge_id
        );
        if (frontier_status != PRIM_FRONTIER_OK) {
            return map_frontier_status(frontier_status);
        }

        workspace->has_best[neighbor] = true;
        workspace->best_key[neighbor] = edge->weight;
        workspace->best_parent[neighbor] = vertex;
        workspace->best_edge[neighbor] = edge_id;
        record_successful_push(workspace);
    }

    return MST_OK;
}

static MstStatus process_all_components(PrimWorkspace *workspace)
{
    size_t vertex_count = workspace->result.forest.vertex_count;
    size_t next_root = 0U;

    while (workspace->selected_vertex_count < vertex_count) {
        size_t root;
        PrimFrontierStatus frontier_status;

        while (next_root < vertex_count &&
            workspace->in_tree[next_root]) {
            next_root += 1U;
        }
        root = next_root;
        if (root == vertex_count || workspace->frontier.size != 0U) {
            return MST_INVALID_STATE;
        }
        next_root += 1U;

        frontier_status = prim_frontier_push(
            &workspace->frontier,
            root,
            INT64_C(0),
            PRIM_FRONTIER_NO_VERTEX,
            PRIM_FRONTIER_NO_EDGE
        );
        if (frontier_status != PRIM_FRONTIER_OK) {
            return map_frontier_status(frontier_status);
        }
        workspace->has_best[root] = true;
        workspace->best_key[root] = INT64_C(0);
        workspace->best_parent[root] = MST_NO_VERTEX;
        workspace->best_edge[root] = MST_NO_EDGE;
        workspace->result.forest.component_count += 1U;
        workspace->result.push_count += 1U;
        if (workspace->frontier.size >
            workspace->result.frontier_peak) {
            workspace->result.frontier_peak =
                workspace->frontier.size;
        }

        while (workspace->frontier.size > 0U) {
            PrimFrontierEntry entry;
            MstStatus status;

            frontier_status = prim_frontier_pop(
                &workspace->frontier,
                &entry
            );
            if (frontier_status != PRIM_FRONTIER_OK) {
                return map_frontier_status(frontier_status);
            }
            workspace->result.pop_count += 1U;

            if (!workspace->has_best[entry.vertex] ||
                entry.key != workspace->best_key[entry.vertex] ||
                entry.parent != workspace->best_parent[entry.vertex] ||
                entry.edge_id != workspace->best_edge[entry.vertex]) {
                workspace->result.stale_pop_count += 1U;
                continue;
            }
            if (workspace->in_tree[entry.vertex]) {
                workspace->result.already_in_tree_pop_count += 1U;
                continue;
            }

            if (entry.edge_id != MST_NO_EDGE) {
                size_t selected =
                    workspace->result.forest.selected_count;

                if (selected >= (size_t)MST_MAX_SELECTED_EDGES ||
                    entry.edge_id >= workspace->edges.size) {
                    return MST_INVALID_STATE;
                }
                workspace->result.forest.selected_edges[selected] =
                    workspace->edges.edges[entry.edge_id];
                workspace->result.forest.selected_count += 1U;
            } else if (entry.parent != MST_NO_VERTEX) {
                return MST_INVALID_STATE;
            }

            workspace->in_tree[entry.vertex] = true;
            workspace->selected_vertex_count += 1U;
            status = relax_from_vertex(workspace, entry.vertex);
            if (status != MST_OK) {
                return status;
            }
        }
    }

    return MST_OK;
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
