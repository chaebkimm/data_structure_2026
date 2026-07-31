#include "undirected_edge_list.h"

#include <stdbool.h>
#include <stdlib.h>

static bool incident_record_is_zero(
    const UndirectedIncidentRecord *record
)
{
    return record->from == 0U &&
        record->to == 0U &&
        record->weight == INT64_C(0) &&
        record->edge_id == 0U;
}

static bool edge_record_is_zero(const UndirectedEdge *edge)
{
    return edge->u == 0U &&
        edge->v == 0U &&
        edge->weight == INT64_C(0) &&
        edge->edge_id == 0U;
}

UndirectedEdgeListStatus undirected_incident_graph_validate(
    const UndirectedIncidentGraph *graph
)
{
    size_t occurrence_count[UNDIRECTED_EDGE_LIST_MAX_LOGICAL_EDGES] = {0U};
    size_t first_index[UNDIRECTED_EDGE_LIST_MAX_LOGICAL_EDGES];
    size_t second_index[UNDIRECTED_EDGE_LIST_MAX_LOGICAL_EDGES];
    size_t index;

    if (graph == NULL) {
        return UNDIRECTED_EDGE_LIST_INVALID_ARGUMENT;
    }
    if (graph->vertex_count >
            (size_t)UNDIRECTED_EDGE_LIST_MAX_VERTICES ||
        graph->logical_edge_count >
            (size_t)UNDIRECTED_EDGE_LIST_MAX_LOGICAL_EDGES ||
        graph->incident_count >
            (size_t)UNDIRECTED_EDGE_LIST_MAX_INCIDENT_RECORDS) {
        return UNDIRECTED_EDGE_LIST_LIMIT;
    }
    if (graph->incident_count != graph->logical_edge_count * 2U) {
        return UNDIRECTED_EDGE_LIST_INVALID_GRAPH;
    }

    for (index = 0U;
         index < (size_t)UNDIRECTED_EDGE_LIST_MAX_LOGICAL_EDGES;
         ++index) {
        first_index[index] =
            (size_t)UNDIRECTED_EDGE_LIST_MAX_INCIDENT_RECORDS;
        second_index[index] =
            (size_t)UNDIRECTED_EDGE_LIST_MAX_INCIDENT_RECORDS;
    }

    for (index = 0U; index < graph->incident_count; ++index) {
        const UndirectedIncidentRecord *record = &graph->incidents[index];
        size_t edge_id = record->edge_id;

        if (record->from >= graph->vertex_count ||
            record->to >= graph->vertex_count) {
            return UNDIRECTED_EDGE_LIST_OUT_OF_RANGE;
        }
        if (edge_id >= graph->logical_edge_count) {
            return UNDIRECTED_EDGE_LIST_INVALID_GRAPH;
        }

        if (occurrence_count[edge_id] == 0U) {
            first_index[edge_id] = index;
        } else if (occurrence_count[edge_id] == 1U) {
            second_index[edge_id] = index;
        } else {
            return UNDIRECTED_EDGE_LIST_INVALID_GRAPH;
        }
        occurrence_count[edge_id] += 1U;
    }

    for (index = graph->incident_count;
         index < (size_t)UNDIRECTED_EDGE_LIST_MAX_INCIDENT_RECORDS;
         ++index) {
        if (!incident_record_is_zero(&graph->incidents[index])) {
            return UNDIRECTED_EDGE_LIST_INVALID_GRAPH;
        }
    }

    for (index = 0U; index < graph->logical_edge_count; ++index) {
        const UndirectedIncidentRecord *first;
        const UndirectedIncidentRecord *second;

        if (occurrence_count[index] != 2U) {
            return UNDIRECTED_EDGE_LIST_INVALID_GRAPH;
        }

        first = &graph->incidents[first_index[index]];
        second = &graph->incidents[second_index[index]];
        if (first->from != second->to ||
            first->to != second->from ||
            first->weight != second->weight) {
            return UNDIRECTED_EDGE_LIST_INVALID_GRAPH;
        }
    }

    return UNDIRECTED_EDGE_LIST_OK;
}

UndirectedEdgeListStatus undirected_edge_list_build(
    const UndirectedIncidentGraph *graph,
    UndirectedEdgeList *out_list
)
{
    UndirectedEdgeList candidate = {0};
    UndirectedEdgeListStatus status;
    bool seen_id[UNDIRECTED_EDGE_LIST_MAX_LOGICAL_EDGES] = {false};
    size_t record_index;

    if (out_list == NULL) {
        return UNDIRECTED_EDGE_LIST_INVALID_ARGUMENT;
    }

    status = undirected_incident_graph_validate(graph);
    if (status != UNDIRECTED_EDGE_LIST_OK) {
        return status;
    }

    candidate.size = graph->logical_edge_count;
    for (record_index = 0U;
         record_index < graph->incident_count;
         ++record_index) {
        const UndirectedIncidentRecord *record =
            &graph->incidents[record_index];
        size_t edge_id = record->edge_id;

        if (!seen_id[edge_id]) {
            UndirectedEdge *edge = &candidate.edges[edge_id];

            if (record->from <= record->to) {
                edge->u = record->from;
                edge->v = record->to;
            } else {
                edge->u = record->to;
                edge->v = record->from;
            }
            edge->weight = record->weight;
            edge->edge_id = edge_id;
            seen_id[edge_id] = true;
        }
    }

    *out_list = candidate;
    return UNDIRECTED_EDGE_LIST_OK;
}

UndirectedEdgeListStatus undirected_edge_list_validate(
    const UndirectedEdgeList *list
)
{
    bool seen_id[UNDIRECTED_EDGE_LIST_MAX_LOGICAL_EDGES] = {false};
    size_t index;

    if (list == NULL) {
        return UNDIRECTED_EDGE_LIST_INVALID_ARGUMENT;
    }
    if (list->size >
        (size_t)UNDIRECTED_EDGE_LIST_MAX_LOGICAL_EDGES) {
        return UNDIRECTED_EDGE_LIST_LIMIT;
    }

    for (index = 0U; index < list->size; ++index) {
        const UndirectedEdge *edge = &list->edges[index];

        if (edge->u > edge->v ||
            edge->u >= (size_t)UNDIRECTED_EDGE_LIST_MAX_VERTICES ||
            edge->v >= (size_t)UNDIRECTED_EDGE_LIST_MAX_VERTICES) {
            return UNDIRECTED_EDGE_LIST_INVALID_LIST;
        }
        if (edge->edge_id >= list->size || seen_id[edge->edge_id]) {
            return UNDIRECTED_EDGE_LIST_INVALID_LIST;
        }
        seen_id[edge->edge_id] = true;
    }

    for (index = list->size;
         index < (size_t)UNDIRECTED_EDGE_LIST_MAX_LOGICAL_EDGES;
         ++index) {
        if (!edge_record_is_zero(&list->edges[index])) {
            return UNDIRECTED_EDGE_LIST_INVALID_LIST;
        }
    }

    return UNDIRECTED_EDGE_LIST_OK;
}

int undirected_edge_compare(const void *left, const void *right)
{
    const UndirectedEdge *left_edge = (const UndirectedEdge *)left;
    const UndirectedEdge *right_edge = (const UndirectedEdge *)right;

    if (left_edge->weight < right_edge->weight) {
        return -1;
    }
    if (left_edge->weight > right_edge->weight) {
        return 1;
    }
    if (left_edge->u < right_edge->u) {
        return -1;
    }
    if (left_edge->u > right_edge->u) {
        return 1;
    }
    if (left_edge->v < right_edge->v) {
        return -1;
    }
    if (left_edge->v > right_edge->v) {
        return 1;
    }
    if (left_edge->edge_id < right_edge->edge_id) {
        return -1;
    }
    if (left_edge->edge_id > right_edge->edge_id) {
        return 1;
    }
    return 0;
}

UndirectedEdgeListStatus undirected_edge_list_sort(
    UndirectedEdgeList *list
)
{
    UndirectedEdgeListStatus status =
        undirected_edge_list_validate(list);

    if (status != UNDIRECTED_EDGE_LIST_OK) {
        return status;
    }

    qsort(
        list->edges,
        list->size,
        sizeof list->edges[0],
        undirected_edge_compare
    );
    return UNDIRECTED_EDGE_LIST_OK;
}

const char *undirected_edge_list_status_name(
    UndirectedEdgeListStatus status
)
{
    switch (status) {
        case UNDIRECTED_EDGE_LIST_OK:
            return "UNDIRECTED_EDGE_LIST_OK";
        case UNDIRECTED_EDGE_LIST_INVALID_ARGUMENT:
            return "UNDIRECTED_EDGE_LIST_INVALID_ARGUMENT";
        case UNDIRECTED_EDGE_LIST_OUT_OF_RANGE:
            return "UNDIRECTED_EDGE_LIST_OUT_OF_RANGE";
        case UNDIRECTED_EDGE_LIST_LIMIT:
            return "UNDIRECTED_EDGE_LIST_LIMIT";
        case UNDIRECTED_EDGE_LIST_INVALID_GRAPH:
            return "UNDIRECTED_EDGE_LIST_INVALID_GRAPH";
        case UNDIRECTED_EDGE_LIST_INVALID_LIST:
            return "UNDIRECTED_EDGE_LIST_INVALID_LIST";
        default:
            return "UNDIRECTED_EDGE_LIST_UNKNOWN_STATUS";
    }
}
