#include "dijkstra.h"
#include "dijkstra_frontier.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

enum {
    DIJKSTRA_FRONTIER_INITIAL_CAPACITY = 8
};

#ifdef DIJKSTRA_TESTING
static bool frontier_allocation_failure_armed = false;
static size_t frontier_allocations_before_failure = 0U;
static size_t frontier_live_allocation_count = 0U;

void dijkstra_frontier_test_fail_allocation_after(
    size_t successful_allocations
)
{
    frontier_allocation_failure_armed = true;
    frontier_allocations_before_failure =
        successful_allocations;
}

size_t dijkstra_frontier_test_live_allocation_count(void)
{
    return frontier_live_allocation_count;
}
#endif

static void *dijkstra_frontier_reallocate(
    void *old_pointer,
    size_t byte_count
)
{
#ifdef DIJKSTRA_TESTING
    bool was_empty = old_pointer == NULL;
#endif
    void *candidate;

#ifdef DIJKSTRA_TESTING
    if (frontier_allocation_failure_armed &&
        frontier_allocations_before_failure == 0U) {
        frontier_allocation_failure_armed = false;
        return NULL;
    }
#endif

    candidate = realloc(old_pointer, byte_count);

#ifdef DIJKSTRA_TESTING
    if (candidate != NULL) {
        if (was_empty) {
            frontier_live_allocation_count += 1U;
        }
        if (frontier_allocation_failure_armed) {
            frontier_allocations_before_failure -= 1U;
        }
    }
#endif

    return candidate;
}

static void dijkstra_frontier_release(void *pointer)
{
    if (pointer == NULL) {
        return;
    }

#ifdef DIJKSTRA_TESTING
    frontier_live_allocation_count -= 1U;
#endif

    free(pointer);
}

static bool dijkstra_frontier_is_zero(
    const DijkstraFrontier *frontier
)
{
    return frontier->data == NULL &&
        frontier->size == 0U &&
        frontier->capacity == 0U &&
        frontier->limit == 0U &&
        frontier->next_sequence == 0U &&
        frontier->comparison_count == 0U;
}

static bool dijkstra_frontier_capacity_is_valid(
    const DijkstraFrontier *frontier
)
{
    size_t capacity = frontier->capacity;

    if (capacity == 0U) {
        return true;
    }
    if (capacity == frontier->limit &&
        frontier->limit > 0U) {
        return true;
    }
    return capacity < frontier->limit &&
        (capacity == 8U ||
         capacity == 16U ||
         capacity == 32U ||
         capacity == 64U ||
         capacity == 128U);
}

static bool dijkstra_frontier_entry_precedes(
    const DijkstraFrontierEntry *left,
    const DijkstraFrontierEntry *right
)
{
    if (left->distance != right->distance) {
        return left->distance < right->distance;
    }
    return left->insertion_sequence <
        right->insertion_sequence;
}

static void dijkstra_frontier_count_comparison(
    DijkstraFrontier *frontier
)
{
    if (frontier->comparison_count < SIZE_MAX) {
        frontier->comparison_count += 1U;
    }
}

static size_t dijkstra_frontier_next_capacity(
    const DijkstraFrontier *frontier
)
{
    size_t candidate;

    if (frontier->capacity == 0U) {
        candidate =
            (size_t)DIJKSTRA_FRONTIER_INITIAL_CAPACITY;
    } else {
        candidate = frontier->capacity * 2U;
    }
    if (candidate > frontier->limit) {
        candidate = frontier->limit;
    }
    return candidate;
}

DijkstraFrontierStatus dijkstra_frontier_init(
    DijkstraFrontier *frontier,
    size_t limit
)
{
    if (frontier == NULL) {
        return DIJKSTRA_FRONTIER_INVALID_ARGUMENT;
    }
    if (limit >
        (size_t)DIJKSTRA_FRONTIER_MAX_ENTRIES) {
        return DIJKSTRA_FRONTIER_OUT_OF_RANGE;
    }
    if (!dijkstra_frontier_is_zero(frontier)) {
        return DIJKSTRA_FRONTIER_INVALID_STATE;
    }

    frontier->limit = limit;
    return DIJKSTRA_FRONTIER_OK;
}

DijkstraFrontierStatus dijkstra_frontier_validate(
    const DijkstraFrontier *frontier
)
{
    if (frontier == NULL) {
        return DIJKSTRA_FRONTIER_INVALID_ARGUMENT;
    }
    if (frontier->limit >
            (size_t)DIJKSTRA_FRONTIER_MAX_ENTRIES ||
        !dijkstra_frontier_capacity_is_valid(frontier) ||
        frontier->size > frontier->capacity ||
        frontier->capacity > frontier->limit) {
        return DIJKSTRA_FRONTIER_INVALID_STATE;
    }

    if (frontier->capacity == 0U) {
        return frontier->data == NULL &&
            frontier->size == 0U &&
            frontier->next_sequence == 0U &&
            frontier->comparison_count == 0U
            ? DIJKSTRA_FRONTIER_OK
            : DIJKSTRA_FRONTIER_INVALID_STATE;
    }

    if (frontier->data == NULL) {
        return DIJKSTRA_FRONTIER_INVALID_STATE;
    }
    if (frontier->size == 0U) {
        return frontier->next_sequence != 0U
            ? DIJKSTRA_FRONTIER_OK
            : DIJKSTRA_FRONTIER_INVALID_STATE;
    }
    if (frontier->next_sequence == 0U ||
        frontier->next_sequence < frontier->size) {
        return DIJKSTRA_FRONTIER_INVALID_STATE;
    }

    return DIJKSTRA_FRONTIER_OK;
}

DijkstraFrontierStatus dijkstra_frontier_is_min_heap(
    const DijkstraFrontier *frontier,
    bool *out_is_min_heap
)
{
    DijkstraFrontierStatus status;
    bool candidate = true;
    size_t index;

    if (out_is_min_heap == NULL) {
        return DIJKSTRA_FRONTIER_INVALID_ARGUMENT;
    }

    status = dijkstra_frontier_validate(frontier);
    if (status != DIJKSTRA_FRONTIER_OK) {
        return status;
    }

    for (index = 0U; index < frontier->size; ++index) {
        const DijkstraFrontierEntry *entry =
            &frontier->data[index];
        size_t other;

        if (entry->vertex >=
                (size_t)WEIGHTED_GRAPH_MAX_VERTICES ||
            entry->distance == SIZE_MAX ||
            entry->insertion_sequence >=
                frontier->next_sequence) {
            candidate = false;
        }
        if (index > 0U) {
            size_t parent = (index - 1U) / 2U;

            if (dijkstra_frontier_entry_precedes(
                    entry,
                    &frontier->data[parent]
                )) {
                candidate = false;
            }
        }
        for (other = 0U; other < index; ++other) {
            if (frontier->data[other].insertion_sequence ==
                entry->insertion_sequence) {
                candidate = false;
            }
        }
    }

    *out_is_min_heap = candidate;
    return DIJKSTRA_FRONTIER_OK;
}

DijkstraFrontierStatus dijkstra_frontier_push(
    DijkstraFrontier *frontier,
    size_t vertex,
    size_t distance
)
{
    DijkstraFrontierStatus status =
        dijkstra_frontier_validate(frontier);
    DijkstraFrontierEntry candidate;
    size_t index;

    if (status != DIJKSTRA_FRONTIER_OK) {
        return status;
    }
    if (vertex >=
            (size_t)WEIGHTED_GRAPH_MAX_VERTICES ||
        distance == SIZE_MAX) {
        return DIJKSTRA_FRONTIER_OUT_OF_RANGE;
    }
    if (frontier->size == frontier->limit) {
        return DIJKSTRA_FRONTIER_FULL;
    }
    if (frontier->next_sequence == SIZE_MAX) {
        return DIJKSTRA_FRONTIER_SEQUENCE_EXHAUSTED;
    }

    if (frontier->size == frontier->capacity) {
        size_t new_capacity =
            dijkstra_frontier_next_capacity(frontier);
        DijkstraFrontierEntry *grown =
            dijkstra_frontier_reallocate(
                frontier->data,
                new_capacity * sizeof *grown
            );

        if (grown == NULL) {
            return DIJKSTRA_FRONTIER_ALLOCATION;
        }
        frontier->data = grown;
        frontier->capacity = new_capacity;
    }

    candidate.vertex = vertex;
    candidate.distance = distance;
    candidate.insertion_sequence =
        frontier->next_sequence;
    index = frontier->size;

    while (index > 0U) {
        size_t parent = (index - 1U) / 2U;

        dijkstra_frontier_count_comparison(frontier);
        if (!dijkstra_frontier_entry_precedes(
                &candidate,
                &frontier->data[parent]
            )) {
            break;
        }
        frontier->data[index] = frontier->data[parent];
        index = parent;
    }

    frontier->data[index] = candidate;
    frontier->size += 1U;
    frontier->next_sequence += 1U;
    return DIJKSTRA_FRONTIER_OK;
}

DijkstraFrontierStatus dijkstra_frontier_pop(
    DijkstraFrontier *frontier,
    DijkstraFrontierEntry *out_entry
)
{
    DijkstraFrontierStatus status;
    DijkstraFrontierEntry result;
    DijkstraFrontierEntry candidate;
    size_t new_size;
    size_t hole = 0U;

    if (out_entry == NULL) {
        return DIJKSTRA_FRONTIER_INVALID_ARGUMENT;
    }

    status = dijkstra_frontier_validate(frontier);
    if (status != DIJKSTRA_FRONTIER_OK) {
        return status;
    }
    if (frontier->size == 0U) {
        return DIJKSTRA_FRONTIER_EMPTY;
    }

    result = frontier->data[0];
    new_size = frontier->size - 1U;

    if (new_size > 0U) {
        candidate = frontier->data[new_size];

        for (;;) {
            size_t left = hole * 2U + 1U;
            size_t selected;
            size_t right;

            if (left >= new_size) {
                break;
            }

            selected = left;
            right = left + 1U;
            if (right < new_size) {
                dijkstra_frontier_count_comparison(frontier);
                if (dijkstra_frontier_entry_precedes(
                        &frontier->data[right],
                        &frontier->data[left]
                    )) {
                    selected = right;
                }
            }

            dijkstra_frontier_count_comparison(frontier);
            if (!dijkstra_frontier_entry_precedes(
                    &frontier->data[selected],
                    &candidate
                )) {
                break;
            }
            frontier->data[hole] =
                frontier->data[selected];
            hole = selected;
        }

        frontier->data[hole] = candidate;
    }

    frontier->size = new_size;
    *out_entry = result;
    return DIJKSTRA_FRONTIER_OK;
}

void dijkstra_frontier_destroy(DijkstraFrontier *frontier)
{
    if (frontier == NULL) {
        return;
    }

    dijkstra_frontier_release(frontier->data);
    frontier->data = NULL;
    frontier->size = 0U;
    frontier->capacity = 0U;
    frontier->limit = 0U;
    frontier->next_sequence = 0U;
    frontier->comparison_count = 0U;
}

const char *dijkstra_frontier_status_name(
    DijkstraFrontierStatus status
)
{
    switch (status) {
        case DIJKSTRA_FRONTIER_OK:
            return "ok";
        case DIJKSTRA_FRONTIER_INVALID_ARGUMENT:
            return "invalid argument";
        case DIJKSTRA_FRONTIER_OUT_OF_RANGE:
            return "Frontier limit or entry is out of range";
        case DIJKSTRA_FRONTIER_FULL:
            return "Frontier is full";
        case DIJKSTRA_FRONTIER_EMPTY:
            return "Frontier is empty";
        case DIJKSTRA_FRONTIER_ALLOCATION:
            return "allocation failed";
        case DIJKSTRA_FRONTIER_SEQUENCE_EXHAUSTED:
            return "insertion sequence exhausted";
        case DIJKSTRA_FRONTIER_INVALID_STATE:
            return "Frontier representation is invalid";
        default:
            return "unknown DijkstraFrontierStatus";
    }
}

static bool dijkstra_result_inactive_slots_are_canonical(
    const DijkstraResult *result
)
{
    size_t vertex;
    size_t event_index;

    for (vertex = result->vertex_count;
         vertex <
             (size_t)WEIGHTED_GRAPH_MAX_VERTICES;
         ++vertex) {
        if (result->distance[vertex] != DIJKSTRA_INF ||
            result->predecessor[vertex] !=
                DIJKSTRA_NO_VERTEX ||
            result->finalized[vertex]) {
            return false;
        }
    }
    for (vertex = result->finalized_count;
         vertex <
             (size_t)WEIGHTED_GRAPH_MAX_VERTICES;
         ++vertex) {
        if (result->finalized_order[vertex] !=
            DIJKSTRA_NO_VERTEX) {
            return false;
        }
    }
    for (event_index = result->pop_count;
         event_index <
             (size_t)DIJKSTRA_MAX_POP_EVENTS;
         ++event_index) {
        const DijkstraPopEvent *event =
            &result->pop_trace[event_index];

        if (event->vertex != DIJKSTRA_NO_VERTEX ||
            event->snapshot_distance != DIJKSTRA_INF ||
            event->insertion_sequence !=
                DIJKSTRA_NO_SEQUENCE ||
            event->stale) {
            return false;
        }
    }
    return true;
}

DijkstraStatus dijkstra_result_validate(
    const DijkstraResult *result
)
{
    bool seen_finalized[WEIGHTED_GRAPH_MAX_VERTICES] =
        {false};
    bool seen_sequence[DIJKSTRA_MAX_POP_EVENTS] = {false};
    size_t finalization_rank[
        WEIGHTED_GRAPH_MAX_VERTICES];
    size_t current_event_count = 0U;
    size_t counted_stale = 0U;
    size_t vertex;
    size_t index;

    if (result == NULL) {
        return DIJKSTRA_INVALID_ARGUMENT;
    }
    if (result->vertex_count == 0U ||
        result->vertex_count >
            (size_t)WEIGHTED_GRAPH_MAX_VERTICES ||
        result->arc_count >
            (size_t)WEIGHTED_GRAPH_MAX_ARCS ||
        result->source >= result->vertex_count ||
        result->push_count == 0U ||
        result->push_count > result->arc_count + 1U ||
        result->push_count >
            (size_t)DIJKSTRA_MAX_POP_EVENTS ||
        result->pop_count != result->push_count ||
        result->successful_relaxation_count + 1U !=
            result->push_count ||
        result->successful_relaxation_count >
            result->relaxation_attempt_count ||
        result->relaxation_attempt_count >
            result->arc_count ||
        result->finalized_count == 0U ||
        result->finalized_count >
            result->vertex_count ||
        result->stale_pop_count +
                result->finalized_count !=
            result->pop_count ||
        result->frontier_peak == 0U ||
        result->frontier_peak > result->push_count) {
        return DIJKSTRA_INVALID_RESULT;
    }

    for (vertex = 0U;
         vertex <
             (size_t)WEIGHTED_GRAPH_MAX_VERTICES;
         ++vertex) {
        finalization_rank[vertex] =
            DIJKSTRA_NO_VERTEX;
    }

    for (index = 0U;
         index < result->finalized_count;
         ++index) {
        size_t finalized_vertex =
            result->finalized_order[index];

        if (finalized_vertex >= result->vertex_count ||
            seen_finalized[finalized_vertex] ||
            !result->finalized[finalized_vertex] ||
            result->distance[finalized_vertex] ==
                DIJKSTRA_INF ||
            (index == 0U &&
                finalized_vertex != result->source) ||
            (index > 0U &&
                result->distance[
                    result->finalized_order[index - 1U]
                ] >
                result->distance[finalized_vertex])) {
            return DIJKSTRA_INVALID_RESULT;
        }
        seen_finalized[finalized_vertex] = true;
        finalization_rank[finalized_vertex] = index;
    }

    for (vertex = 0U;
         vertex < result->vertex_count;
         ++vertex) {
        if (result->finalized[vertex] !=
            seen_finalized[vertex]) {
            return DIJKSTRA_INVALID_RESULT;
        }

        if (vertex == result->source) {
            if (result->distance[vertex] != 0U ||
                result->predecessor[vertex] !=
                    DIJKSTRA_NO_VERTEX ||
                !result->finalized[vertex]) {
                return DIJKSTRA_INVALID_RESULT;
            }
        } else if (result->distance[vertex] ==
                   DIJKSTRA_INF) {
            if (result->predecessor[vertex] !=
                    DIJKSTRA_NO_VERTEX ||
                result->finalized[vertex]) {
                return DIJKSTRA_INVALID_RESULT;
            }
        } else {
            size_t predecessor =
                result->predecessor[vertex];

            if (!result->finalized[vertex] ||
                predecessor >= result->vertex_count ||
                predecessor == vertex ||
                !result->finalized[predecessor] ||
                finalization_rank[predecessor] >=
                    finalization_rank[vertex]) {
                return DIJKSTRA_INVALID_RESULT;
            }
        }
    }

    for (index = 0U; index < result->pop_count; ++index) {
        const DijkstraPopEvent *event =
            &result->pop_trace[index];
        bool expected_stale;

        if (event->vertex >= result->vertex_count ||
            event->snapshot_distance == DIJKSTRA_INF ||
            event->insertion_sequence >=
                result->push_count ||
            seen_sequence[event->insertion_sequence]) {
            return DIJKSTRA_INVALID_RESULT;
        }
        if (index > 0U) {
            const DijkstraPopEvent *previous =
                &result->pop_trace[index - 1U];

            if (previous->snapshot_distance >
                    event->snapshot_distance ||
                (previous->snapshot_distance ==
                    event->snapshot_distance &&
                 previous->insertion_sequence >=
                    event->insertion_sequence)) {
                return DIJKSTRA_INVALID_RESULT;
            }
        }
        seen_sequence[event->insertion_sequence] = true;

        expected_stale =
            event->snapshot_distance !=
                result->distance[event->vertex];
        if (event->stale != expected_stale) {
            return DIJKSTRA_INVALID_RESULT;
        }

        if (event->stale) {
            counted_stale += 1U;
        } else {
            if (current_event_count >=
                    result->finalized_count ||
                event->vertex !=
                    result->finalized_order[
                        current_event_count
                    ]) {
                return DIJKSTRA_INVALID_RESULT;
            }
            current_event_count += 1U;
        }
    }

    if (counted_stale != result->stale_pop_count ||
        current_event_count != result->finalized_count ||
        !dijkstra_result_inactive_slots_are_canonical(
            result
        )) {
        return DIJKSTRA_INVALID_RESULT;
    }

    return DIJKSTRA_OK;
}

const char *dijkstra_status_name(DijkstraStatus status)
{
    switch (status) {
        case DIJKSTRA_OK:
            return "ok";
        case DIJKSTRA_INVALID_ARGUMENT:
            return "invalid argument";
        case DIJKSTRA_OUT_OF_RANGE:
            return "source or destination is out of range";
        case DIJKSTRA_INVALID_GRAPH:
            return "weighted graph is invalid";
        case DIJKSTRA_ALLOCATION:
            return "allocation failed";
        case DIJKSTRA_LIMIT:
            return "Frontier limit was exhausted";
        case DIJKSTRA_COST_RANGE:
            return "path cost reaches or exceeds reserved infinity";
        case DIJKSTRA_UNREACHABLE:
            return "destination is unreachable";
        case DIJKSTRA_INVALID_RESULT:
            return "Dijkstra result is invalid";
        default:
            return "unknown DijkstraStatus";
    }
}
