#include "minimum_spanning_forest.h"

#include "dsu.h"
#include "undirected_edge_list.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

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

static MstStatus initialize_sets(Dsu *sets, size_t vertex_count)
{
    size_t vertex;

    if (dsu_init(sets) != DSU_OK) {
        return MST_INVALID_STATE;
    }
    for (vertex = 0U; vertex < vertex_count; ++vertex) {
        size_t created = DSU_NO_ELEMENT;

        if (dsu_make_set(sets, &created) != DSU_OK ||
            created != vertex) {
            return MST_INVALID_STATE;
        }
    }
    return MST_OK;
}

static MstStatus select_sorted_edges(
    const UndirectedEdgeList *sorted,
    Dsu *sets,
    KruskalResult *candidate
)
{
    size_t index;

    for (index = 0U; index < sorted->size; ++index) {
        const UndirectedEdge *edge = &sorted->edges[index];
        size_t left_root = DSU_NO_ELEMENT;
        size_t right_root = DSU_NO_ELEMENT;
        bool merged = false;

        candidate->examined_edge_count += 1U;
        if (edge->u == edge->v) {
            candidate->self_loop_skip_count += 1U;
            continue;
        }
        if (dsu_find(sets, edge->u, &left_root) != DSU_OK ||
            dsu_find(sets, edge->v, &right_root) != DSU_OK) {
            return MST_INVALID_STATE;
        }
        if (left_root == right_root) {
            candidate->cycle_skip_count += 1U;
            continue;
        }
        if (candidate->forest.selected_count >=
            (size_t)MST_MAX_SELECTED_EDGES) {
            return MST_INVALID_STATE;
        }

        candidate->forest.selected_edges[
            candidate->forest.selected_count
        ] = *edge;
        candidate->forest.selected_count += 1U;
        if (dsu_union(
                sets,
                edge->u,
                edge->v,
                &merged
            ) != DSU_OK || !merged) {
            return MST_INVALID_STATE;
        }
    }

    candidate->forest.component_count = sets->component_count;
    return MST_OK;
}

MstStatus kruskal_minimum_spanning_forest(
    const UndirectedIncidentGraph *graph,
    KruskalResult *out_result
)
{
    KruskalResult candidate = {0};
    UndirectedEdgeList sorted;
    UndirectedEdgeListStatus edge_status;
    Dsu sets;
    MstStatus status;
    int64_t total = INT64_C(0);

    if (graph == NULL || out_result == NULL) {
        return MST_INVALID_ARGUMENT;
    }

    edge_status = undirected_edge_list_build(graph, &sorted);
    if (edge_status != UNDIRECTED_EDGE_LIST_OK) {
        return map_edge_status(edge_status);
    }
    edge_status = undirected_edge_list_sort(&sorted);
    if (edge_status != UNDIRECTED_EDGE_LIST_OK) {
        return map_edge_status(edge_status);
    }

    candidate.forest.vertex_count = graph->vertex_count;
    candidate.forest.input_edge_count = graph->logical_edge_count;
    status = initialize_sets(&sets, graph->vertex_count);
    if (status != MST_OK) {
        return status;
    }
    status = select_sorted_edges(&sorted, &sets, &candidate);
    if (status != MST_OK) {
        return status;
    }
    status = mst_forest_total_checked(
        candidate.forest.selected_edges,
        candidate.forest.selected_count,
        &total
    );
    if (status != MST_OK) {
        return status;
    }

    candidate.forest.total_weight = total;
    *out_result = candidate;
    return MST_OK;
}
