#include "minimum_spanning_forest.h"

#include "dsu.h"
#include "undirected_edge_list.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

static MstStatus map_edge_list_status(UndirectedEdgeListStatus status)
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

static bool edge_is_zero(const UndirectedEdge *edge)
{
    return edge->u == 0U &&
        edge->v == 0U &&
        edge->weight == INT64_C(0) &&
        edge->edge_id == 0U;
}

static bool edges_equal(
    const UndirectedEdge *left,
    const UndirectedEdge *right
)
{
    return left->u == right->u &&
        left->v == right->v &&
        left->weight == right->weight &&
        left->edge_id == right->edge_id;
}

static bool ascii_space(char value)
{
    return value == ' ' || value == '\t' || value == '\n' ||
        value == '\r' || value == '\f' || value == '\v';
}

MstStatus mst_graph_init(
    UndirectedIncidentGraph *graph,
    size_t vertex_count
)
{
    UndirectedIncidentGraph candidate = {0};

    if (graph == NULL) {
        return MST_INVALID_ARGUMENT;
    }
    if (vertex_count >
        (size_t)UNDIRECTED_EDGE_LIST_MAX_VERTICES) {
        return MST_OUT_OF_RANGE;
    }

    candidate.vertex_count = vertex_count;
    *graph = candidate;
    return MST_OK;
}

MstStatus mst_graph_add_edge(
    UndirectedIncidentGraph *graph,
    size_t u,
    size_t v,
    int64_t weight
)
{
    UndirectedEdgeListStatus graph_status;
    size_t edge_id;
    size_t first_index;

    if (graph == NULL) {
        return MST_INVALID_ARGUMENT;
    }

    graph_status = undirected_incident_graph_validate(graph);
    if (graph_status != UNDIRECTED_EDGE_LIST_OK) {
        return map_edge_list_status(graph_status);
    }
    if (u >= graph->vertex_count || v >= graph->vertex_count) {
        return MST_OUT_OF_RANGE;
    }
    if (graph->logical_edge_count ==
        (size_t)UNDIRECTED_EDGE_LIST_MAX_LOGICAL_EDGES) {
        return MST_LIMIT;
    }

    edge_id = graph->logical_edge_count;
    first_index = graph->incident_count;
    graph->incidents[first_index] = (UndirectedIncidentRecord){
        u, v, weight, edge_id
    };
    graph->incidents[first_index + 1U] = (UndirectedIncidentRecord){
        v, u, weight, edge_id
    };
    graph->logical_edge_count += 1U;
    graph->incident_count += 2U;
    return MST_OK;
}

MstStatus mst_graph_validate(const UndirectedIncidentGraph *graph)
{
    return map_edge_list_status(
        undirected_incident_graph_validate(graph)
    );
}

MstStatus mst_parse_weight(
    const char *text,
    int64_t *out_weight
)
{
    const char *cursor;
    bool negative = false;
    bool saw_digit = false;
    uint64_t magnitude = UINT64_C(0);
    uint64_t limit;
    int64_t parsed;

    if (text == NULL || out_weight == NULL) {
        return MST_INVALID_ARGUMENT;
    }

    cursor = text;
    while (ascii_space(*cursor)) {
        cursor += 1;
    }
    if (*cursor == '+' || *cursor == '-') {
        negative = *cursor == '-';
        cursor += 1;
    }

    limit = negative
        ? (uint64_t)INT64_MAX + UINT64_C(1)
        : (uint64_t)INT64_MAX;
    while (*cursor >= '0' && *cursor <= '9') {
        uint64_t digit = (uint64_t)(unsigned int)(*cursor - '0');

        saw_digit = true;
        if (magnitude > (limit - digit) / UINT64_C(10)) {
            return MST_WEIGHT_OUT_OF_RANGE;
        }
        magnitude = magnitude * UINT64_C(10) + digit;
        cursor += 1;
    }
    if (!saw_digit) {
        return MST_INVALID_WEIGHT_TEXT;
    }
    while (ascii_space(*cursor)) {
        cursor += 1;
    }
    if (*cursor != '\0') {
        return MST_INVALID_WEIGHT_TEXT;
    }

    if (negative && magnitude ==
        (uint64_t)INT64_MAX + UINT64_C(1)) {
        parsed = INT64_MIN;
    } else if (negative) {
        parsed = -(int64_t)magnitude;
    } else {
        parsed = (int64_t)magnitude;
    }

    *out_weight = parsed;
    return MST_OK;
}

MstStatus mst_adjacency_index_build(
    const UndirectedIncidentGraph *graph,
    const UndirectedEdgeList *edge_list,
    MstAdjacencyIndex *out_index
)
{
    MstAdjacencyIndex candidate = {0};
    UndirectedEdgeList canonical;
    size_t degree[UNDIRECTED_EDGE_LIST_MAX_VERTICES] = {0U};
    size_t cursor[UNDIRECTED_EDGE_LIST_MAX_VERTICES] = {0U};
    UndirectedEdgeListStatus edge_status;
    size_t index;

    if (out_index == NULL || graph == NULL || edge_list == NULL) {
        return MST_INVALID_ARGUMENT;
    }

    edge_status = undirected_edge_list_build(graph, &canonical);
    if (edge_status != UNDIRECTED_EDGE_LIST_OK) {
        return map_edge_list_status(edge_status);
    }
    edge_status = undirected_edge_list_validate(edge_list);
    if (edge_status != UNDIRECTED_EDGE_LIST_OK) {
        return map_edge_list_status(edge_status);
    }
    if (edge_list->size != canonical.size) {
        return MST_INVALID_GRAPH;
    }

    for (index = 0U; index < edge_list->size; ++index) {
        const UndirectedEdge *edge = &edge_list->edges[index];

        if (!edges_equal(edge, &canonical.edges[edge->edge_id])) {
            return MST_INVALID_GRAPH;
        }
    }

    for (index = 0U; index < canonical.size; ++index) {
        const UndirectedEdge *edge = &canonical.edges[index];

        degree[edge->u] += 1U;
        degree[edge->v] += 1U;
    }

    candidate.offsets[0] = 0U;
    for (index = 0U;
         index < (size_t)UNDIRECTED_EDGE_LIST_MAX_VERTICES;
         ++index) {
        candidate.offsets[index + 1U] =
            candidate.offsets[index] + degree[index];
        cursor[index] = candidate.offsets[index];
    }
    candidate.incident_count = candidate.offsets[
        UNDIRECTED_EDGE_LIST_MAX_VERTICES
    ];
    if (candidate.incident_count != graph->incident_count ||
        candidate.incident_count >
            (size_t)UNDIRECTED_EDGE_LIST_MAX_INCIDENT_RECORDS) {
        return MST_INVALID_GRAPH;
    }

    for (index = 0U; index < canonical.size; ++index) {
        const UndirectedEdge *edge = &canonical.edges[index];

        candidate.edge_ids[cursor[edge->u]] = edge->edge_id;
        cursor[edge->u] += 1U;
        candidate.edge_ids[cursor[edge->v]] = edge->edge_id;
        cursor[edge->v] += 1U;
    }

    *out_index = candidate;
    return MST_OK;
}

MstStatus mst_forest_total_checked(
    const UndirectedEdge *edges,
    size_t edge_count,
    int64_t *out_total
)
{
    uint64_t positive[MST_MAX_SELECTED_EDGES] = {UINT64_C(0)};
    uint64_t negative[MST_MAX_SELECTED_EDGES] = {UINT64_C(0)};
    size_t positive_count = 0U;
    size_t negative_count = 0U;
    size_t negative_index = 0U;
    size_t index;
    uint64_t sum = UINT64_C(0);
    uint64_t negative_limit =
        (uint64_t)INT64_MAX + UINT64_C(1);
    int64_t result;

    if (edges == NULL || out_total == NULL) {
        return MST_INVALID_ARGUMENT;
    }
    if (edge_count > (size_t)MST_MAX_SELECTED_EDGES) {
        return MST_LIMIT;
    }

    for (index = 0U; index < edge_count; ++index) {
        int64_t weight = edges[index].weight;

        if (weight >= INT64_C(0)) {
            positive[positive_count] = (uint64_t)weight;
            positive_count += 1U;
        } else {
            negative[negative_count] =
                (uint64_t)(-(weight + INT64_C(1))) + UINT64_C(1);
            negative_count += 1U;
        }
    }

    for (index = 0U; index < positive_count; ++index) {
        while (negative_index < negative_count &&
            positive[index] != UINT64_C(0)) {
            uint64_t amount = positive[index] < negative[negative_index]
                ? positive[index]
                : negative[negative_index];

            positive[index] -= amount;
            negative[negative_index] -= amount;
            if (negative[negative_index] == UINT64_C(0)) {
                negative_index += 1U;
            }
        }
    }

    for (index = 0U; index < positive_count; ++index) {
        if (positive[index] >
            (uint64_t)INT64_MAX - sum) {
            return MST_TOTAL_OUT_OF_RANGE;
        }
        sum += positive[index];
    }
    if (sum != UINT64_C(0)) {
        result = (int64_t)sum;
        *out_total = result;
        return MST_OK;
    }

    for (index = 0U; index < negative_count; ++index) {
        if (negative[index] > negative_limit - sum) {
            return MST_TOTAL_OUT_OF_RANGE;
        }
        sum += negative[index];
    }
    if (sum == negative_limit) {
        result = INT64_MIN;
    } else {
        result = -(int64_t)sum;
    }

    *out_total = result;
    return MST_OK;
}

static MstStatus initialize_dsu(Dsu *sets, size_t vertex_count)
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

static bool forest_path_maximum(
    const size_t degree[UNDIRECTED_EDGE_LIST_MAX_VERTICES],
    const size_t
        neighbor[UNDIRECTED_EDGE_LIST_MAX_VERTICES]
                [MST_MAX_SELECTED_EDGES],
    const int64_t
        neighbor_weight[UNDIRECTED_EDGE_LIST_MAX_VERTICES]
                       [MST_MAX_SELECTED_EDGES],
    size_t start,
    size_t target,
    int64_t *out_maximum
)
{
    bool visited[UNDIRECTED_EDGE_LIST_MAX_VERTICES] = {false};
    bool has_maximum[UNDIRECTED_EDGE_LIST_MAX_VERTICES] = {false};
    int64_t maximum[UNDIRECTED_EDGE_LIST_MAX_VERTICES] = {INT64_C(0)};
    size_t queue[UNDIRECTED_EDGE_LIST_MAX_VERTICES];
    size_t head = 0U;
    size_t tail = 0U;

    visited[start] = true;
    queue[tail] = start;
    tail += 1U;

    while (head < tail) {
        size_t current = queue[head];
        size_t slot;

        head += 1U;
        for (slot = 0U; slot < degree[current]; ++slot) {
            size_t next = neighbor[current][slot];
            int64_t edge_weight = neighbor_weight[current][slot];

            if (visited[next]) {
                continue;
            }
            visited[next] = true;
            has_maximum[next] = true;
            if (!has_maximum[current] ||
                edge_weight > maximum[current]) {
                maximum[next] = edge_weight;
            } else {
                maximum[next] = maximum[current];
            }
            if (next == target) {
                *out_maximum = maximum[next];
                return true;
            }
            queue[tail] = next;
            tail += 1U;
        }
    }

    return false;
}

MstStatus mst_forest_validate(
    const UndirectedIncidentGraph *graph,
    const MstForest *forest
)
{
    UndirectedEdgeList canonical;
    bool selected_id[UNDIRECTED_EDGE_LIST_MAX_LOGICAL_EDGES] = {false};
    size_t degree[UNDIRECTED_EDGE_LIST_MAX_VERTICES] = {0U};
    size_t
        neighbor[UNDIRECTED_EDGE_LIST_MAX_VERTICES]
                [MST_MAX_SELECTED_EDGES];
    int64_t
        neighbor_weight[UNDIRECTED_EDGE_LIST_MAX_VERTICES]
                       [MST_MAX_SELECTED_EDGES];
    Dsu input_sets;
    Dsu forest_sets;
    size_t input_to_forest[UNDIRECTED_EDGE_LIST_MAX_VERTICES];
    size_t forest_to_input[UNDIRECTED_EDGE_LIST_MAX_VERTICES];
    UndirectedEdgeListStatus edge_status;
    MstStatus status;
    int64_t total = INT64_C(0);
    size_t index;

    if (graph == NULL || forest == NULL) {
        return MST_INVALID_ARGUMENT;
    }

    edge_status = undirected_edge_list_build(graph, &canonical);
    if (edge_status != UNDIRECTED_EDGE_LIST_OK) {
        return map_edge_list_status(edge_status);
    }
    if (forest->vertex_count != graph->vertex_count ||
        forest->input_edge_count != graph->logical_edge_count ||
        forest->selected_count > (size_t)MST_MAX_SELECTED_EDGES ||
        forest->component_count > graph->vertex_count) {
        return MST_INVALID_RESULT;
    }
    if ((graph->vertex_count == 0U &&
            forest->component_count != 0U) ||
        (graph->vertex_count > 0U &&
            forest->component_count == 0U)) {
        return MST_INVALID_RESULT;
    }
    if (forest->selected_count !=
        graph->vertex_count - forest->component_count) {
        return MST_INVALID_RESULT;
    }

    for (index = forest->selected_count;
         index < (size_t)MST_MAX_SELECTED_EDGES;
         ++index) {
        if (!edge_is_zero(&forest->selected_edges[index])) {
            return MST_INVALID_RESULT;
        }
    }

    status = initialize_dsu(&input_sets, graph->vertex_count);
    if (status != MST_OK) {
        return status;
    }
    status = initialize_dsu(&forest_sets, graph->vertex_count);
    if (status != MST_OK) {
        return status;
    }

    for (index = 0U; index < canonical.size; ++index) {
        const UndirectedEdge *edge = &canonical.edges[index];

        if (edge->u != edge->v) {
            bool merged = false;

            if (dsu_union(
                    &input_sets,
                    edge->u,
                    edge->v,
                    &merged
                ) != DSU_OK) {
                return MST_INVALID_STATE;
            }
        }
    }

    for (index = 0U; index < forest->selected_count; ++index) {
        const UndirectedEdge *edge = &forest->selected_edges[index];
        bool merged = false;

        if (edge->edge_id >= canonical.size ||
            selected_id[edge->edge_id] ||
            !edges_equal(edge, &canonical.edges[edge->edge_id]) ||
            edge->u == edge->v) {
            return MST_INVALID_RESULT;
        }
        if (degree[edge->u] >= (size_t)MST_MAX_SELECTED_EDGES ||
            degree[edge->v] >= (size_t)MST_MAX_SELECTED_EDGES) {
            return MST_INVALID_RESULT;
        }
        if (dsu_union(
                &forest_sets,
                edge->u,
                edge->v,
                &merged
            ) != DSU_OK || !merged) {
            return MST_INVALID_RESULT;
        }

        selected_id[edge->edge_id] = true;
        neighbor[edge->u][degree[edge->u]] = edge->v;
        neighbor_weight[edge->u][degree[edge->u]] = edge->weight;
        degree[edge->u] += 1U;
        neighbor[edge->v][degree[edge->v]] = edge->u;
        neighbor_weight[edge->v][degree[edge->v]] = edge->weight;
        degree[edge->v] += 1U;
    }

    if (input_sets.component_count != forest->component_count ||
        forest_sets.component_count != forest->component_count) {
        return MST_INVALID_RESULT;
    }

    for (index = 0U;
         index < (size_t)UNDIRECTED_EDGE_LIST_MAX_VERTICES;
         ++index) {
        input_to_forest[index] = MST_NO_VERTEX;
        forest_to_input[index] = MST_NO_VERTEX;
    }
    for (index = 0U; index < graph->vertex_count; ++index) {
        size_t input_root = DSU_NO_ELEMENT;
        size_t forest_root = DSU_NO_ELEMENT;

        if (dsu_find(&input_sets, index, &input_root) != DSU_OK ||
            dsu_find(&forest_sets, index, &forest_root) != DSU_OK) {
            return MST_INVALID_STATE;
        }
        if (input_to_forest[input_root] == MST_NO_VERTEX) {
            input_to_forest[input_root] = forest_root;
        } else if (input_to_forest[input_root] != forest_root) {
            return MST_INVALID_RESULT;
        }
        if (forest_to_input[forest_root] == MST_NO_VERTEX) {
            forest_to_input[forest_root] = input_root;
        } else if (forest_to_input[forest_root] != input_root) {
            return MST_INVALID_RESULT;
        }
    }

    status = mst_forest_total_checked(
        forest->selected_edges,
        forest->selected_count,
        &total
    );
    if (status != MST_OK) {
        return status;
    }
    if (total != forest->total_weight) {
        return MST_INVALID_RESULT;
    }

    for (index = 0U; index < canonical.size; ++index) {
        const UndirectedEdge *edge = &canonical.edges[index];
        int64_t maximum = INT64_C(0);

        if (selected_id[edge->edge_id] || edge->u == edge->v) {
            continue;
        }
        if (!forest_path_maximum(
                degree,
                neighbor,
                neighbor_weight,
                edge->u,
                edge->v,
                &maximum
            )) {
            return MST_INVALID_RESULT;
        }
        if (edge->weight < maximum) {
            return MST_NOT_MINIMUM;
        }
    }

    return MST_OK;
}

const char *mst_status_name(MstStatus status)
{
    switch (status) {
        case MST_OK:
            return "MST_OK";
        case MST_INVALID_ARGUMENT:
            return "MST_INVALID_ARGUMENT";
        case MST_OUT_OF_RANGE:
            return "MST_OUT_OF_RANGE";
        case MST_LIMIT:
            return "MST_LIMIT";
        case MST_INVALID_GRAPH:
            return "MST_INVALID_GRAPH";
        case MST_INVALID_WEIGHT_TEXT:
            return "MST_INVALID_WEIGHT_TEXT";
        case MST_WEIGHT_OUT_OF_RANGE:
            return "MST_WEIGHT_OUT_OF_RANGE";
        case MST_ALLOCATION:
            return "MST_ALLOCATION";
        case MST_TOTAL_OUT_OF_RANGE:
            return "MST_TOTAL_OUT_OF_RANGE";
        case MST_INVALID_RESULT:
            return "MST_INVALID_RESULT";
        case MST_NOT_MINIMUM:
            return "MST_NOT_MINIMUM";
        case MST_INVALID_STATE:
            return "MST_INVALID_STATE";
        default:
            return "MST_UNKNOWN_STATUS";
    }
}
