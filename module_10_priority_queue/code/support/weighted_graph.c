#include "weighted_graph.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

enum {
    WEIGHTED_EDGE_INITIAL_CAPACITY = 4
};

#ifdef DIJKSTRA_TESTING
static bool graph_allocation_failure_armed = false;
static size_t graph_allocations_before_failure = 0U;
static size_t graph_live_row_count = 0U;

void weighted_graph_test_fail_allocation_after(
    size_t successful_allocations
)
{
    graph_allocation_failure_armed = true;
    graph_allocations_before_failure = successful_allocations;
}

size_t weighted_graph_test_live_row_count(void)
{
    return graph_live_row_count;
}
#endif

static void *weighted_row_allocate(size_t byte_count)
{
    void *candidate;

#ifdef DIJKSTRA_TESTING
    if (graph_allocation_failure_armed &&
        graph_allocations_before_failure == 0U) {
        graph_allocation_failure_armed = false;
        return NULL;
    }
#endif

    candidate = malloc(byte_count);

#ifdef DIJKSTRA_TESTING
    if (candidate != NULL) {
        graph_live_row_count += 1U;
        if (graph_allocation_failure_armed) {
            graph_allocations_before_failure -= 1U;
        }
    }
#endif

    return candidate;
}

static void weighted_row_release(void *pointer)
{
    if (pointer == NULL) {
        return;
    }

#ifdef DIJKSTRA_TESTING
    graph_live_row_count -= 1U;
#endif

    free(pointer);
}

static bool weighted_graph_kind_is_valid(WeightedGraphKind kind)
{
    return kind == WEIGHTED_GRAPH_DIRECTED ||
        kind == WEIGHTED_GRAPH_UNDIRECTED;
}

static bool weighted_row_capacity_is_valid(size_t capacity)
{
    return capacity == 0U ||
        capacity == (size_t)WEIGHTED_EDGE_INITIAL_CAPACITY ||
        capacity == 8U ||
        capacity == (size_t)WEIGHTED_GRAPH_MAX_VERTICES;
}

static bool weighted_graph_is_zero(const WeightedGraph *graph)
{
    size_t vertex;

    if (graph->vertex_count != 0U ||
        graph->kind != WEIGHTED_GRAPH_DIRECTED ||
        graph->arc_count != 0U) {
        return false;
    }

    for (vertex = 0U;
         vertex < (size_t)WEIGHTED_GRAPH_MAX_VERTICES;
         ++vertex) {
        if (graph->outgoing[vertex].data != NULL ||
            graph->outgoing[vertex].size != 0U ||
            graph->outgoing[vertex].capacity != 0U) {
            return false;
        }
    }
    return true;
}

static size_t weighted_row_lower_bound(
    const WeightedEdgeArray *row,
    size_t destination
)
{
    size_t index = 0U;

    while (index < row->size &&
           row->data[index].to < destination) {
        index += 1U;
    }
    return index;
}

static bool weighted_row_contains(
    const WeightedEdgeArray *row,
    size_t destination,
    size_t *out_index
)
{
    size_t index = weighted_row_lower_bound(row, destination);

    if (out_index != NULL) {
        *out_index = index;
    }
    return index < row->size &&
        row->data[index].to == destination;
}

static WeightedGraphStatus weighted_graph_check_pair(
    const WeightedGraph *graph,
    size_t from_vertex,
    size_t to_vertex
)
{
    WeightedGraphStatus status = weighted_graph_validate(graph);

    if (status != WEIGHTED_GRAPH_OK) {
        return status;
    }
    if (from_vertex >= graph->vertex_count ||
        to_vertex >= graph->vertex_count) {
        return WEIGHTED_GRAPH_OUT_OF_RANGE;
    }
    if (from_vertex == to_vertex) {
        return WEIGHTED_GRAPH_SELF_LOOP;
    }
    return WEIGHTED_GRAPH_OK;
}

typedef struct {
    WeightedEdge *data;
    size_t capacity;
    bool replaces_row;
} WeightedRowStage;

static WeightedGraphStatus weighted_row_stage_insert(
    const WeightedEdgeArray *row,
    WeightedRowStage *stage
)
{
    size_t new_capacity;
    WeightedEdge *candidate;

    stage->data = row->data;
    stage->capacity = row->capacity;
    stage->replaces_row = false;

    if (row->size < row->capacity) {
        return WEIGHTED_GRAPH_OK;
    }

    new_capacity = row->capacity == 0U
        ? (size_t)WEIGHTED_EDGE_INITIAL_CAPACITY
        : row->capacity * 2U;
    if (new_capacity >
        (size_t)WEIGHTED_GRAPH_MAX_VERTICES) {
        new_capacity =
            (size_t)WEIGHTED_GRAPH_MAX_VERTICES;
    }

    candidate = weighted_row_allocate(
        new_capacity * sizeof *candidate
    );
    if (candidate == NULL) {
        return WEIGHTED_GRAPH_ALLOCATION;
    }
    if (row->size > 0U) {
        memcpy(
            candidate,
            row->data,
            row->size * sizeof *candidate
        );
    }

    stage->data = candidate;
    stage->capacity = new_capacity;
    stage->replaces_row = true;
    return WEIGHTED_GRAPH_OK;
}

static void weighted_row_abandon_stage(WeightedRowStage *stage)
{
    if (stage->replaces_row) {
        weighted_row_release(stage->data);
        stage->data = NULL;
        stage->capacity = 0U;
        stage->replaces_row = false;
    }
}

static void weighted_row_insert_staged(
    WeightedRowStage *stage,
    size_t old_size,
    size_t insertion_index,
    size_t destination,
    size_t weight
)
{
    size_t move_count = old_size - insertion_index;

    if (move_count > 0U) {
        memmove(
            &stage->data[insertion_index + 1U],
            &stage->data[insertion_index],
            move_count * sizeof *stage->data
        );
    }
    stage->data[insertion_index].to = destination;
    stage->data[insertion_index].weight = weight;
}

static void weighted_row_commit_stage(
    WeightedEdgeArray *row,
    WeightedRowStage *stage
)
{
    WeightedEdge *old_data = row->data;

    if (stage->replaces_row) {
        row->data = stage->data;
        row->capacity = stage->capacity;
    }
    row->size += 1U;

    if (stage->replaces_row) {
        weighted_row_release(old_data);
    }
}

WeightedGraphStatus weighted_graph_init(
    WeightedGraph *graph,
    size_t vertex_count,
    WeightedGraphKind kind
)
{
    if (graph == NULL) {
        return WEIGHTED_GRAPH_INVALID_ARGUMENT;
    }
    if (vertex_count >
        (size_t)WEIGHTED_GRAPH_MAX_VERTICES) {
        return WEIGHTED_GRAPH_OUT_OF_RANGE;
    }
    if (!weighted_graph_kind_is_valid(kind)) {
        return WEIGHTED_GRAPH_INVALID_ARGUMENT;
    }
    if (!weighted_graph_is_zero(graph)) {
        return WEIGHTED_GRAPH_INVALID_GRAPH;
    }

    graph->vertex_count = vertex_count;
    graph->kind = kind;
    return WEIGHTED_GRAPH_OK;
}

WeightedGraphStatus weighted_graph_validate(
    const WeightedGraph *graph
)
{
    bool present[WEIGHTED_GRAPH_MAX_VERTICES]
        [WEIGHTED_GRAPH_MAX_VERTICES] = {{false}};
    size_t weights[WEIGHTED_GRAPH_MAX_VERTICES]
        [WEIGHTED_GRAPH_MAX_VERTICES] = {{0U}};
    size_t counted_arcs = 0U;
    size_t from_vertex;

    if (graph == NULL) {
        return WEIGHTED_GRAPH_INVALID_ARGUMENT;
    }
    if (graph->vertex_count >
            (size_t)WEIGHTED_GRAPH_MAX_VERTICES ||
        !weighted_graph_kind_is_valid(graph->kind) ||
        graph->arc_count >
            (size_t)WEIGHTED_GRAPH_MAX_ARCS) {
        return WEIGHTED_GRAPH_INVALID_GRAPH;
    }

    for (from_vertex = 0U;
         from_vertex <
             (size_t)WEIGHTED_GRAPH_MAX_VERTICES;
         ++from_vertex) {
        const WeightedEdgeArray *row =
            &graph->outgoing[from_vertex];
        size_t index;

        if (from_vertex >= graph->vertex_count) {
            if (row->data != NULL ||
                row->size != 0U ||
                row->capacity != 0U) {
                return WEIGHTED_GRAPH_INVALID_GRAPH;
            }
            continue;
        }

        if (row->size > row->capacity ||
            !weighted_row_capacity_is_valid(row->capacity) ||
            (row->capacity == 0U && row->data != NULL) ||
            (row->capacity > 0U && row->data == NULL)) {
            return WEIGHTED_GRAPH_INVALID_GRAPH;
        }

        for (index = 0U; index < row->size; ++index) {
            const WeightedEdge *edge = &row->data[index];

            if (edge->to >= graph->vertex_count ||
                edge->to == from_vertex ||
                edge->weight == SIZE_MAX ||
                (index > 0U &&
                    row->data[index - 1U].to >= edge->to)) {
                return WEIGHTED_GRAPH_INVALID_GRAPH;
            }
            present[from_vertex][edge->to] = true;
            weights[from_vertex][edge->to] = edge->weight;
        }
        counted_arcs += row->size;
    }

    if (counted_arcs != graph->arc_count ||
        counted_arcs >
            (size_t)WEIGHTED_GRAPH_MAX_ARCS) {
        return WEIGHTED_GRAPH_INVALID_GRAPH;
    }

    if (graph->kind == WEIGHTED_GRAPH_UNDIRECTED) {
        for (from_vertex = 0U;
             from_vertex < graph->vertex_count;
             ++from_vertex) {
            const WeightedEdgeArray *row =
                &graph->outgoing[from_vertex];
            size_t index;

            for (index = 0U; index < row->size; ++index) {
                size_t to_vertex = row->data[index].to;

                if (!present[to_vertex][from_vertex] ||
                    weights[from_vertex][to_vertex] !=
                        weights[to_vertex][from_vertex]) {
                    return WEIGHTED_GRAPH_INVALID_GRAPH;
                }
            }
        }
    }

    return WEIGHTED_GRAPH_OK;
}

WeightedGraphStatus weighted_graph_add_edge(
    WeightedGraph *graph,
    size_t from_vertex,
    size_t to_vertex,
    size_t weight
)
{
    WeightedGraphStatus status = weighted_graph_check_pair(
        graph,
        from_vertex,
        to_vertex
    );
    WeightedEdgeArray *forward_row;
    WeightedEdgeArray *reverse_row;
    WeightedRowStage forward_stage;
    WeightedRowStage reverse_stage;
    size_t forward_index;
    size_t reverse_index = 0U;

    if (status != WEIGHTED_GRAPH_OK) {
        return status;
    }
    if (weight == SIZE_MAX) {
        return WEIGHTED_GRAPH_WEIGHT_OUT_OF_RANGE;
    }

    forward_row = &graph->outgoing[from_vertex];
    if (weighted_row_contains(
            forward_row,
            to_vertex,
            &forward_index
        )) {
        return WEIGHTED_GRAPH_EDGE_EXISTS;
    }

    reverse_row = &graph->outgoing[to_vertex];
    if (graph->kind == WEIGHTED_GRAPH_UNDIRECTED &&
        weighted_row_contains(
            reverse_row,
            from_vertex,
            &reverse_index
        )) {
        return WEIGHTED_GRAPH_INVALID_GRAPH;
    }

    status = weighted_row_stage_insert(
        forward_row,
        &forward_stage
    );
    if (status != WEIGHTED_GRAPH_OK) {
        return status;
    }

    if (graph->kind == WEIGHTED_GRAPH_UNDIRECTED) {
        status = weighted_row_stage_insert(
            reverse_row,
            &reverse_stage
        );
        if (status != WEIGHTED_GRAPH_OK) {
            weighted_row_abandon_stage(&forward_stage);
            return status;
        }
    }

    weighted_row_insert_staged(
        &forward_stage,
        forward_row->size,
        forward_index,
        to_vertex,
        weight
    );
    if (graph->kind == WEIGHTED_GRAPH_UNDIRECTED) {
        weighted_row_insert_staged(
            &reverse_stage,
            reverse_row->size,
            reverse_index,
            from_vertex,
            weight
        );
    }

    weighted_row_commit_stage(forward_row, &forward_stage);
    if (graph->kind == WEIGHTED_GRAPH_UNDIRECTED) {
        weighted_row_commit_stage(reverse_row, &reverse_stage);
        graph->arc_count += 2U;
    } else {
        graph->arc_count += 1U;
    }
    return WEIGHTED_GRAPH_OK;
}

WeightedGraphStatus weighted_graph_add_edge_text(
    WeightedGraph *graph,
    size_t from_vertex,
    size_t to_vertex,
    const char *weight_text
)
{
    size_t weight;
    WeightedGraphStatus status;

    if (graph == NULL) {
        return WEIGHTED_GRAPH_INVALID_ARGUMENT;
    }
    status = weighted_graph_parse_weight(weight_text, &weight);
    if (status != WEIGHTED_GRAPH_OK) {
        return status;
    }
    return weighted_graph_add_edge(
        graph,
        from_vertex,
        to_vertex,
        weight
    );
}

WeightedGraphStatus weighted_graph_get_weight(
    const WeightedGraph *graph,
    size_t from_vertex,
    size_t to_vertex,
    size_t *out_weight
)
{
    WeightedGraphStatus status;
    const WeightedEdgeArray *row;
    size_t index;
    size_t candidate;

    if (out_weight == NULL) {
        return WEIGHTED_GRAPH_INVALID_ARGUMENT;
    }

    status = weighted_graph_check_pair(
        graph,
        from_vertex,
        to_vertex
    );
    if (status != WEIGHTED_GRAPH_OK) {
        return status;
    }

    row = &graph->outgoing[from_vertex];
    if (!weighted_row_contains(row, to_vertex, &index)) {
        return WEIGHTED_GRAPH_EDGE_ABSENT;
    }

    candidate = row->data[index].weight;
    *out_weight = candidate;
    return WEIGHTED_GRAPH_OK;
}

void weighted_graph_destroy(WeightedGraph *graph)
{
    size_t vertex;

    if (graph == NULL) {
        return;
    }

    for (vertex = 0U;
         vertex <
             (size_t)WEIGHTED_GRAPH_MAX_VERTICES;
         ++vertex) {
        weighted_row_release(graph->outgoing[vertex].data);
        graph->outgoing[vertex].data = NULL;
        graph->outgoing[vertex].size = 0U;
        graph->outgoing[vertex].capacity = 0U;
    }
    graph->vertex_count = 0U;
    graph->kind = WEIGHTED_GRAPH_DIRECTED;
    graph->arc_count = 0U;
}

const char *weighted_graph_status_name(WeightedGraphStatus status)
{
    switch (status) {
        case WEIGHTED_GRAPH_OK:
            return "ok";
        case WEIGHTED_GRAPH_INVALID_ARGUMENT:
            return "invalid argument";
        case WEIGHTED_GRAPH_OUT_OF_RANGE:
            return "vertex count or index out of range";
        case WEIGHTED_GRAPH_SELF_LOOP:
            return "self-loops are not allowed";
        case WEIGHTED_GRAPH_EDGE_EXISTS:
            return "edge already exists";
        case WEIGHTED_GRAPH_EDGE_ABSENT:
            return "edge does not exist";
        case WEIGHTED_GRAPH_NEGATIVE_WEIGHT:
            return "negative weight is not allowed";
        case WEIGHTED_GRAPH_INVALID_WEIGHT_TEXT:
            return "weight text is not a decimal integer";
        case WEIGHTED_GRAPH_WEIGHT_OUT_OF_RANGE:
            return "weight is outside the supported range";
        case WEIGHTED_GRAPH_INVALID_GRAPH:
            return "graph representation is invalid";
        case WEIGHTED_GRAPH_ALLOCATION:
            return "allocation failed";
        default:
            return "unknown WeightedGraphStatus";
    }
}
