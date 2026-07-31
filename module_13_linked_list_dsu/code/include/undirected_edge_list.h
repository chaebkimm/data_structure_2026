#ifndef UNDIRECTED_EDGE_LIST_H
#define UNDIRECTED_EDGE_LIST_H

#include <stddef.h>
#include <stdint.h>

#define UNDIRECTED_EDGE_LIST_MAX_VERTICES 16U
#define UNDIRECTED_EDGE_LIST_MAX_LOGICAL_EDGES 120U
#define UNDIRECTED_EDGE_LIST_MAX_INCIDENT_RECORDS 240U

/*
 * Each logical undirected edge owns exactly two incident records. Ordinary
 * edges use reciprocal directions. A self-loop uses two identical records.
 * Parallel edges remain separate because they have different edge IDs.
 */
typedef struct {
    size_t from;
    size_t to;
    int64_t weight;
    size_t edge_id;
} UndirectedIncidentRecord;

typedef struct {
    size_t vertex_count;
    size_t logical_edge_count;
    size_t incident_count;
    UndirectedIncidentRecord
        incidents[UNDIRECTED_EDGE_LIST_MAX_INCIDENT_RECORDS];
} UndirectedIncidentGraph;

/*
 * Builder output uses canonical endpoints u <= v and one record per logical
 * edge ID. Sorting changes only the order of the active records.
 */
typedef struct {
    size_t u;
    size_t v;
    int64_t weight;
    size_t edge_id;
} UndirectedEdge;

typedef struct {
    UndirectedEdge edges[UNDIRECTED_EDGE_LIST_MAX_LOGICAL_EDGES];
    size_t size;
} UndirectedEdgeList;

typedef enum {
    UNDIRECTED_EDGE_LIST_OK = 0,
    UNDIRECTED_EDGE_LIST_INVALID_ARGUMENT,
    UNDIRECTED_EDGE_LIST_OUT_OF_RANGE,
    UNDIRECTED_EDGE_LIST_LIMIT,
    UNDIRECTED_EDGE_LIST_INVALID_GRAPH,
    UNDIRECTED_EDGE_LIST_INVALID_LIST
} UndirectedEdgeListStatus;

UndirectedEdgeListStatus undirected_incident_graph_validate(
    const UndirectedIncidentGraph *graph
);

/*
 * Validates the incident graph, builds a local list in dense edge-ID order,
 * and commits out_list only on success. graph and out_list must not overlap.
 */
UndirectedEdgeListStatus undirected_edge_list_build(
    const UndirectedIncidentGraph *graph,
    UndirectedEdgeList *out_list
);

UndirectedEdgeListStatus undirected_edge_list_validate(
    const UndirectedEdgeList *list
);

/*
 * Uses qsort after validation. Invalid input is not changed.
 */
UndirectedEdgeListStatus undirected_edge_list_sort(
    UndirectedEdgeList *list
);

/*
 * Public qsort comparator. It compares relationally by weight, u, v, and
 * edge ID. It never subtracts numeric fields.
 */
int undirected_edge_compare(const void *left, const void *right);

const char *undirected_edge_list_status_name(
    UndirectedEdgeListStatus status
);

#endif
