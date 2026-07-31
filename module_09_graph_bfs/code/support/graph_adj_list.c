#include "graph_adj_list.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

enum {
    GRAPH_NEIGHBOR_INITIAL_CAPACITY = 4
};

#ifdef GRAPH_BFS_TESTING
static bool allocation_failure_armed = false;
static size_t successful_allocations_before_failure = 0U;
static size_t live_array_count = 0U;

void graph_adj_list_test_fail_allocation_after(
    size_t successful_allocations
)
{
    allocation_failure_armed = true;
    successful_allocations_before_failure = successful_allocations;
}

size_t graph_adj_list_test_live_array_count(void)
{
    return live_array_count;
}
#endif

static void *neighbor_array_allocate(size_t byte_count)
{
    void *candidate;

#ifdef GRAPH_BFS_TESTING
    if (allocation_failure_armed &&
        successful_allocations_before_failure == 0U) {
        allocation_failure_armed = false;
        return NULL;
    }
#endif

    candidate = malloc(byte_count);

#ifdef GRAPH_BFS_TESTING
    if (candidate != NULL) {
        live_array_count += 1U;
        if (allocation_failure_armed) {
            successful_allocations_before_failure -= 1U;
        }
    }
#endif

    return candidate;
}

static void neighbor_array_release(void *pointer)
{
    if (pointer == NULL) {
        return;
    }

#ifdef GRAPH_BFS_TESTING
    live_array_count -= 1U;
#endif

    free(pointer);
}

static bool graph_kind_is_valid(GraphKind kind)
{
    return kind == GRAPH_DIRECTED || kind == GRAPH_UNDIRECTED;
}

static bool neighbor_capacity_is_valid(size_t capacity)
{
    return capacity == 0U ||
        capacity == (size_t)GRAPH_NEIGHBOR_INITIAL_CAPACITY ||
        capacity == 8U ||
        capacity == (size_t)GRAPH_MAX_VERTICES;
}

static bool graph_adj_list_is_zero(const GraphAdjList *graph)
{
    size_t vertex;

    if (graph->vertex_count != 0U || graph->kind != GRAPH_DIRECTED) {
        return false;
    }

    for (vertex = 0U;
         vertex < (size_t)GRAPH_MAX_VERTICES;
         ++vertex) {
        if (graph->neighbors[vertex].data != NULL ||
            graph->neighbors[vertex].size != 0U ||
            graph->neighbors[vertex].capacity != 0U) {
            return false;
        }
    }
    return true;
}

static GraphAdjListStatus check_pair(
    const GraphAdjList *graph,
    size_t from_vertex,
    size_t to_vertex
)
{
    GraphAdjListStatus status = graph_adj_list_validate(graph);

    if (status != GRAPH_ADJ_LIST_OK) {
        return status;
    }
    if (from_vertex >= graph->vertex_count ||
        to_vertex >= graph->vertex_count) {
        return GRAPH_ADJ_LIST_OUT_OF_RANGE;
    }
    if (from_vertex == to_vertex) {
        return GRAPH_ADJ_LIST_SELF_LOOP;
    }
    return GRAPH_ADJ_LIST_OK;
}

static size_t lower_bound_index(
    const GraphNeighborArray *row,
    size_t target
)
{
    size_t index = 0U;

    while (index < row->size && row->data[index] < target) {
        index += 1U;
    }
    return index;
}

static bool row_contains(
    const GraphNeighborArray *row,
    size_t target,
    size_t *out_index
)
{
    size_t index = lower_bound_index(row, target);

    if (out_index != NULL) {
        *out_index = index;
    }
    return index < row->size && row->data[index] == target;
}

typedef struct {
    size_t *data;
    size_t capacity;
    bool replaces_row;
} NeighborRowStage;

static GraphAdjListStatus stage_row_for_insert(
    const GraphNeighborArray *row,
    NeighborRowStage *stage
)
{
    size_t new_capacity;
    size_t *candidate;

    stage->data = row->data;
    stage->capacity = row->capacity;
    stage->replaces_row = false;

    if (row->size < row->capacity) {
        return GRAPH_ADJ_LIST_OK;
    }

    new_capacity = row->capacity == 0U
        ? (size_t)GRAPH_NEIGHBOR_INITIAL_CAPACITY
        : row->capacity * 2U;
    if (new_capacity > (size_t)GRAPH_MAX_VERTICES) {
        new_capacity = (size_t)GRAPH_MAX_VERTICES;
    }

    candidate = neighbor_array_allocate(
        new_capacity * sizeof *candidate
    );
    if (candidate == NULL) {
        return GRAPH_ADJ_LIST_ALLOCATION;
    }
    if (row->size > 0U) {
        memcpy(candidate, row->data, row->size * sizeof *candidate);
    }

    stage->data = candidate;
    stage->capacity = new_capacity;
    stage->replaces_row = true;
    return GRAPH_ADJ_LIST_OK;
}

static void abandon_stage(NeighborRowStage *stage)
{
    if (stage->replaces_row) {
        neighbor_array_release(stage->data);
        stage->data = NULL;
        stage->capacity = 0U;
        stage->replaces_row = false;
    }
}

static void insert_into_stage(
    NeighborRowStage *stage,
    size_t old_size,
    size_t insertion_index,
    size_t value
)
{
    size_t values_to_move = old_size - insertion_index;

    if (values_to_move > 0U) {
        memmove(
            &stage->data[insertion_index + 1U],
            &stage->data[insertion_index],
            values_to_move * sizeof *stage->data
        );
    }
    stage->data[insertion_index] = value;
}

static void commit_stage(
    GraphNeighborArray *row,
    NeighborRowStage *stage
)
{
    size_t *old_data = row->data;

    if (stage->replaces_row) {
        row->data = stage->data;
        row->capacity = stage->capacity;
    }
    row->size += 1U;

    if (stage->replaces_row) {
        neighbor_array_release(old_data);
    }
}

static void remove_at(GraphNeighborArray *row, size_t index)
{
    size_t values_to_move = row->size - index - 1U;

    if (values_to_move > 0U) {
        memmove(
            &row->data[index],
            &row->data[index + 1U],
            values_to_move * sizeof *row->data
        );
    }
    row->size -= 1U;
}

GraphAdjListStatus graph_adj_list_init(
    GraphAdjList *graph,
    size_t vertex_count,
    GraphKind kind
)
{
    if (graph == NULL) {
        return GRAPH_ADJ_LIST_INVALID_ARGUMENT;
    }
    if (vertex_count > (size_t)GRAPH_MAX_VERTICES) {
        return GRAPH_ADJ_LIST_OUT_OF_RANGE;
    }
    if (!graph_kind_is_valid(kind)) {
        return GRAPH_ADJ_LIST_INVALID_ARGUMENT;
    }
    if (!graph_adj_list_is_zero(graph)) {
        return GRAPH_ADJ_LIST_INVALID_GRAPH;
    }

    graph->vertex_count = vertex_count;
    graph->kind = kind;
    return GRAPH_ADJ_LIST_OK;
}

GraphAdjListStatus graph_adj_list_validate(
    const GraphAdjList *graph
)
{
    uint32_t masks[GRAPH_MAX_VERTICES] = {0U};
    size_t from_vertex;

    if (graph == NULL) {
        return GRAPH_ADJ_LIST_INVALID_ARGUMENT;
    }
    if (graph->vertex_count > (size_t)GRAPH_MAX_VERTICES ||
        !graph_kind_is_valid(graph->kind)) {
        return GRAPH_ADJ_LIST_INVALID_GRAPH;
    }

    for (from_vertex = 0U;
         from_vertex < (size_t)GRAPH_MAX_VERTICES;
         ++from_vertex) {
        const GraphNeighborArray *row =
            &graph->neighbors[from_vertex];
        size_t index;

        if (from_vertex >= graph->vertex_count) {
            if (row->data != NULL ||
                row->size != 0U ||
                row->capacity != 0U) {
                return GRAPH_ADJ_LIST_INVALID_GRAPH;
            }
            continue;
        }

        if (row->size > row->capacity ||
            !neighbor_capacity_is_valid(row->capacity) ||
            (row->capacity == 0U && row->data != NULL) ||
            (row->capacity > 0U && row->data == NULL)) {
            return GRAPH_ADJ_LIST_INVALID_GRAPH;
        }

        for (index = 0U; index < row->size; ++index) {
            size_t neighbor = row->data[index];

            if (neighbor >= graph->vertex_count ||
                neighbor == from_vertex ||
                (index > 0U &&
                    row->data[index - 1U] >= neighbor)) {
                return GRAPH_ADJ_LIST_INVALID_GRAPH;
            }
            masks[from_vertex] |=
                (uint32_t)1U << (unsigned int)neighbor;
        }
    }

    if (graph->kind == GRAPH_UNDIRECTED) {
        for (from_vertex = 0U;
             from_vertex < graph->vertex_count;
             ++from_vertex) {
            const GraphNeighborArray *row =
                &graph->neighbors[from_vertex];
            size_t index;

            for (index = 0U; index < row->size; ++index) {
                size_t neighbor = row->data[index];
                uint32_t reverse_bit =
                    (uint32_t)1U << (unsigned int)from_vertex;

                if ((masks[neighbor] & reverse_bit) == 0U) {
                    return GRAPH_ADJ_LIST_INVALID_GRAPH;
                }
            }
        }
    }

    return GRAPH_ADJ_LIST_OK;
}

GraphAdjListStatus graph_adj_list_add_edge(
    GraphAdjList *graph,
    size_t from_vertex,
    size_t to_vertex
)
{
    GraphAdjListStatus status = check_pair(
        graph,
        from_vertex,
        to_vertex
    );
    GraphNeighborArray *forward_row;
    GraphNeighborArray *reverse_row;
    NeighborRowStage forward_stage;
    NeighborRowStage reverse_stage;
    size_t forward_index;
    size_t reverse_index = 0U;

    if (status != GRAPH_ADJ_LIST_OK) {
        return status;
    }

    forward_row = &graph->neighbors[from_vertex];
    if (row_contains(forward_row, to_vertex, &forward_index)) {
        return GRAPH_ADJ_LIST_EDGE_EXISTS;
    }

    reverse_row = &graph->neighbors[to_vertex];
    if (graph->kind == GRAPH_UNDIRECTED) {
        if (row_contains(reverse_row, from_vertex, &reverse_index)) {
            return GRAPH_ADJ_LIST_INVALID_GRAPH;
        }
    }

    status = stage_row_for_insert(forward_row, &forward_stage);
    if (status != GRAPH_ADJ_LIST_OK) {
        return status;
    }

    if (graph->kind == GRAPH_UNDIRECTED) {
        status = stage_row_for_insert(reverse_row, &reverse_stage);
        if (status != GRAPH_ADJ_LIST_OK) {
            abandon_stage(&forward_stage);
            return status;
        }
    }

    insert_into_stage(
        &forward_stage,
        forward_row->size,
        forward_index,
        to_vertex
    );
    if (graph->kind == GRAPH_UNDIRECTED) {
        insert_into_stage(
            &reverse_stage,
            reverse_row->size,
            reverse_index,
            from_vertex
        );
    }

    commit_stage(forward_row, &forward_stage);
    if (graph->kind == GRAPH_UNDIRECTED) {
        commit_stage(reverse_row, &reverse_stage);
    }
    return GRAPH_ADJ_LIST_OK;
}

GraphAdjListStatus graph_adj_list_remove_edge(
    GraphAdjList *graph,
    size_t from_vertex,
    size_t to_vertex
)
{
    GraphAdjListStatus status = check_pair(
        graph,
        from_vertex,
        to_vertex
    );
    GraphNeighborArray *forward_row;
    GraphNeighborArray *reverse_row;
    size_t forward_index;
    size_t reverse_index = 0U;

    if (status != GRAPH_ADJ_LIST_OK) {
        return status;
    }

    forward_row = &graph->neighbors[from_vertex];
    if (!row_contains(forward_row, to_vertex, &forward_index)) {
        return GRAPH_ADJ_LIST_EDGE_ABSENT;
    }

    reverse_row = &graph->neighbors[to_vertex];
    if (graph->kind == GRAPH_UNDIRECTED &&
        !row_contains(reverse_row, from_vertex, &reverse_index)) {
        return GRAPH_ADJ_LIST_INVALID_GRAPH;
    }

    remove_at(forward_row, forward_index);
    if (graph->kind == GRAPH_UNDIRECTED) {
        remove_at(reverse_row, reverse_index);
    }
    return GRAPH_ADJ_LIST_OK;
}

GraphAdjListStatus graph_adj_list_has_edge(
    const GraphAdjList *graph,
    size_t from_vertex,
    size_t to_vertex,
    bool *out_has_edge
)
{
    GraphAdjListStatus status;
    bool candidate;

    if (out_has_edge == NULL) {
        return GRAPH_ADJ_LIST_INVALID_ARGUMENT;
    }

    status = check_pair(graph, from_vertex, to_vertex);
    if (status != GRAPH_ADJ_LIST_OK) {
        return status;
    }

    candidate = row_contains(
        &graph->neighbors[from_vertex],
        to_vertex,
        NULL
    );
    *out_has_edge = candidate;
    return GRAPH_ADJ_LIST_OK;
}

GraphAdjListStatus graph_adj_list_out_neighbors(
    const GraphAdjList *graph,
    size_t vertex,
    GraphNeighbors *out_neighbors
)
{
    GraphAdjListStatus status;
    GraphNeighbors candidate = {0U, {0U}};
    size_t index;

    if (out_neighbors == NULL) {
        return GRAPH_ADJ_LIST_INVALID_ARGUMENT;
    }

    status = graph_adj_list_validate(graph);
    if (status != GRAPH_ADJ_LIST_OK) {
        return status;
    }
    if (vertex >= graph->vertex_count) {
        return GRAPH_ADJ_LIST_OUT_OF_RANGE;
    }

    candidate.count = graph->neighbors[vertex].size;
    for (index = 0U; index < candidate.count; ++index) {
        candidate.vertices[index] =
            graph->neighbors[vertex].data[index];
    }
    *out_neighbors = candidate;
    return GRAPH_ADJ_LIST_OK;
}

void graph_adj_list_destroy(GraphAdjList *graph)
{
    size_t vertex;

    if (graph == NULL) {
        return;
    }

    for (vertex = 0U;
         vertex < (size_t)GRAPH_MAX_VERTICES;
         ++vertex) {
        neighbor_array_release(graph->neighbors[vertex].data);
        graph->neighbors[vertex].data = NULL;
        graph->neighbors[vertex].size = 0U;
        graph->neighbors[vertex].capacity = 0U;
    }
    graph->vertex_count = 0U;
    graph->kind = GRAPH_DIRECTED;
}

const char *graph_adj_list_status_name(GraphAdjListStatus status)
{
    switch (status) {
        case GRAPH_ADJ_LIST_OK:
            return "ok";
        case GRAPH_ADJ_LIST_INVALID_ARGUMENT:
            return "invalid argument";
        case GRAPH_ADJ_LIST_OUT_OF_RANGE:
            return "vertex count or index out of range";
        case GRAPH_ADJ_LIST_SELF_LOOP:
            return "self-loops are not allowed";
        case GRAPH_ADJ_LIST_EDGE_EXISTS:
            return "edge already exists";
        case GRAPH_ADJ_LIST_EDGE_ABSENT:
            return "edge does not exist";
        case GRAPH_ADJ_LIST_INVALID_GRAPH:
            return "graph does not satisfy adjacency-list representation rules";
        case GRAPH_ADJ_LIST_ALLOCATION:
            return "allocation failed";
        default:
            return "unknown GraphAdjListStatus";
    }
}
