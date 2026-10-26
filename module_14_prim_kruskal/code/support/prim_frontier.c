#include "prim_frontier.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

enum {
    PRIM_FRONTIER_INITIAL_CAPACITY = 8
};

#ifdef MST_TESTING
static bool fail_next_growth = false;
static size_t live_allocation_count = 0U;

void prim_frontier_test_fail_next_growth(void)
{
    fail_next_growth = true;
}

size_t prim_frontier_test_live_allocation_count(void)
{
    return live_allocation_count;
}
#endif

static void *frontier_reallocate(void *old_pointer, size_t new_bytes)
{
#ifdef MST_TESTING
    if (fail_next_growth) {
        fail_next_growth = false;
        return NULL;
    }
#endif

    return realloc(old_pointer, new_bytes);
}

static bool is_supported_capacity(size_t capacity, size_t limit)
{
    if (capacity == 0U) {
        return true;
    }
    if (capacity == limit) {
        return capacity <= (size_t)PRIM_FRONTIER_MAX_ENTRIES;
    }
    return capacity < limit &&
        (capacity == 8U ||
         capacity == 16U ||
         capacity == 32U ||
         capacity == 64U ||
         capacity == 128U);
}

static bool entry_precedes(
    const PrimFrontierEntry *left,
    const PrimFrontierEntry *right
)
{
    if (left->key != right->key) {
        return left->key < right->key;
    }
    return left->insertion_sequence < right->insertion_sequence;
}

static bool sentinel_pair_is_valid(size_t parent, size_t edge_id)
{
    if (parent == PRIM_FRONTIER_NO_VERTEX ||
        edge_id == PRIM_FRONTIER_NO_EDGE) {
        return parent == PRIM_FRONTIER_NO_VERTEX &&
            edge_id == PRIM_FRONTIER_NO_EDGE;
    }
    return parent < (size_t)UNDIRECTED_EDGE_LIST_MAX_VERTICES &&
        edge_id < (size_t)UNDIRECTED_EDGE_LIST_MAX_LOGICAL_EDGES;
}

PrimFrontierStatus prim_frontier_init(
    PrimFrontier *frontier,
    size_t limit
)
{
    if (frontier == NULL) {
        return PRIM_FRONTIER_INVALID_ARGUMENT;
    }
    if (limit > (size_t)PRIM_FRONTIER_MAX_ENTRIES) {
        return PRIM_FRONTIER_OUT_OF_RANGE;
    }
    if (frontier->data != NULL ||
        frontier->size != 0U ||
        frontier->capacity != 0U ||
        frontier->limit != 0U ||
        frontier->next_sequence != 0U) {
        return PRIM_FRONTIER_INVALID_STATE;
    }

    frontier->limit = limit;
    return PRIM_FRONTIER_OK;
}

PrimFrontierStatus prim_frontier_validate(
    const PrimFrontier *frontier
)
{
    if (frontier == NULL) {
        return PRIM_FRONTIER_INVALID_ARGUMENT;
    }
    if (frontier->limit > (size_t)PRIM_FRONTIER_MAX_ENTRIES ||
        !is_supported_capacity(frontier->capacity, frontier->limit) ||
        frontier->size > frontier->capacity ||
        frontier->capacity > frontier->limit) {
        return PRIM_FRONTIER_INVALID_STATE;
    }
    if (frontier->capacity == 0U) {
        if (frontier->data != NULL ||
            frontier->size != 0U ||
            frontier->next_sequence != 0U) {
            return PRIM_FRONTIER_INVALID_STATE;
        }
    } else if (frontier->data == NULL ||
        frontier->next_sequence == 0U) {
        return PRIM_FRONTIER_INVALID_STATE;
    }
    if (frontier->size > 0U &&
        (frontier->next_sequence == 0U ||
         frontier->next_sequence < frontier->size)) {
        return PRIM_FRONTIER_INVALID_STATE;
    }

    return PRIM_FRONTIER_OK;
}

PrimFrontierStatus prim_frontier_is_min_heap(
    const PrimFrontier *frontier,
    bool *out_is_min_heap
)
{
    PrimFrontierStatus status;
    bool result = true;
    size_t child;

    if (out_is_min_heap == NULL) {
        return PRIM_FRONTIER_INVALID_ARGUMENT;
    }

    status = prim_frontier_validate(frontier);
    if (status != PRIM_FRONTIER_OK) {
        return status;
    }

    for (child = 1U; child < frontier->size; ++child) {
        size_t parent = (child - 1U) / 2U;

        if (entry_precedes(
                &frontier->data[child],
                &frontier->data[parent]
            )) {
            result = false;
        }
    }
    for (child = 0U; child < frontier->size; ++child) {
        const PrimFrontierEntry *entry = &frontier->data[child];
        size_t other;

        if (entry->vertex >=
                (size_t)UNDIRECTED_EDGE_LIST_MAX_VERTICES ||
            !sentinel_pair_is_valid(entry->parent, entry->edge_id) ||
            entry->insertion_sequence >= frontier->next_sequence) {
            return PRIM_FRONTIER_INVALID_STATE;
        }
        for (other = child + 1U;
             other < frontier->size;
             ++other) {
            if (entry->insertion_sequence ==
                frontier->data[other].insertion_sequence) {
                return PRIM_FRONTIER_INVALID_STATE;
            }
        }
    }

    *out_is_min_heap = result;
    return PRIM_FRONTIER_OK;
}

PrimFrontierStatus prim_frontier_push(
    PrimFrontier *frontier,
    size_t vertex,
    int64_t key,
    size_t parent,
    size_t edge_id
)
{
    PrimFrontierStatus status = prim_frontier_validate(frontier);
    PrimFrontierEntry candidate;
    size_t index;

    if (status != PRIM_FRONTIER_OK) {
        return status;
    }
    if (vertex >= (size_t)UNDIRECTED_EDGE_LIST_MAX_VERTICES ||
        !sentinel_pair_is_valid(parent, edge_id)) {
        return PRIM_FRONTIER_OUT_OF_RANGE;
    }
    if (frontier->size == frontier->limit) {
        return PRIM_FRONTIER_FULL;
    }
    if (frontier->next_sequence == SIZE_MAX) {
        return PRIM_FRONTIER_SEQUENCE_EXHAUSTED;
    }

    if (frontier->size == frontier->capacity) {
        size_t new_capacity;
        PrimFrontierEntry *grown;
        bool first_allocation = frontier->data == NULL;

        if (frontier->capacity == 0U) {
            new_capacity = frontier->limit <
                    (size_t)PRIM_FRONTIER_INITIAL_CAPACITY
                ? frontier->limit
                : (size_t)PRIM_FRONTIER_INITIAL_CAPACITY;
        } else if (frontier->capacity > frontier->limit / 2U) {
            new_capacity = frontier->limit;
        } else {
            new_capacity = frontier->capacity * 2U;
        }

        grown = frontier_reallocate(
            frontier->data,
            new_capacity * sizeof *frontier->data
        );
        if (grown == NULL) {
            return PRIM_FRONTIER_ALLOCATION;
        }

        frontier->data = grown;
        frontier->capacity = new_capacity;
#ifdef MST_TESTING
        if (first_allocation) {
            live_allocation_count += 1U;
        }
#else
        (void)first_allocation;
#endif
    }

    candidate.vertex = vertex;
    candidate.key = key;
    candidate.parent = parent;
    candidate.edge_id = edge_id;
    candidate.insertion_sequence = frontier->next_sequence;
    index = frontier->size;

    while (index > 0U) {
        size_t parent_index = (index - 1U) / 2U;

        if (!entry_precedes(
                &candidate,
                &frontier->data[parent_index]
            )) {
            break;
        }

        frontier->data[index] = frontier->data[parent_index];
        index = parent_index;
    }

    frontier->data[index] = candidate;
    frontier->size += 1U;
    frontier->next_sequence += 1U;
    return PRIM_FRONTIER_OK;
}

PrimFrontierStatus prim_frontier_pop(
    PrimFrontier *frontier,
    PrimFrontierEntry *out_entry
)
{
    PrimFrontierStatus status;
    PrimFrontierEntry result;
    PrimFrontierEntry candidate;
    size_t new_size;
    size_t hole = 0U;

    if (out_entry == NULL) {
        return PRIM_FRONTIER_INVALID_ARGUMENT;
    }

    status = prim_frontier_validate(frontier);
    if (status != PRIM_FRONTIER_OK) {
        return status;
    }
    if (frontier->size == 0U) {
        return PRIM_FRONTIER_EMPTY;
    }

    result = frontier->data[0];
    new_size = frontier->size - 1U;
    if (new_size > 0U) {
        candidate = frontier->data[new_size];

        for (;;) {
            size_t left = hole * 2U + 1U;
            size_t right;
            size_t selected;

            if (left >= new_size) {
                break;
            }
            selected = left;
            right = left + 1U;
            if (right < new_size &&
                entry_precedes(
                    &frontier->data[right],
                    &frontier->data[left]
                )) {
                selected = right;
            }
            if (!entry_precedes(
                    &frontier->data[selected],
                    &candidate
                )) {
                break;
            }

            frontier->data[hole] = frontier->data[selected];
            hole = selected;
        }
        frontier->data[hole] = candidate;
    }

    frontier->size = new_size;
    *out_entry = result;
    return PRIM_FRONTIER_OK;
}

void prim_frontier_destroy(PrimFrontier *frontier)
{
    if (frontier == NULL) {
        return;
    }

#ifdef MST_TESTING
    if (frontier->data != NULL && live_allocation_count > 0U) {
        live_allocation_count -= 1U;
    }
#endif
    free(frontier->data);
    frontier->data = NULL;
    frontier->size = 0U;
    frontier->capacity = 0U;
    frontier->limit = 0U;
    frontier->next_sequence = 0U;
}

const char *prim_frontier_status_name(PrimFrontierStatus status)
{
    switch (status) {
        case PRIM_FRONTIER_OK:
            return "PRIM_FRONTIER_OK";
        case PRIM_FRONTIER_INVALID_ARGUMENT:
            return "PRIM_FRONTIER_INVALID_ARGUMENT";
        case PRIM_FRONTIER_OUT_OF_RANGE:
            return "PRIM_FRONTIER_OUT_OF_RANGE";
        case PRIM_FRONTIER_FULL:
            return "PRIM_FRONTIER_FULL";
        case PRIM_FRONTIER_EMPTY:
            return "PRIM_FRONTIER_EMPTY";
        case PRIM_FRONTIER_ALLOCATION:
            return "PRIM_FRONTIER_ALLOCATION";
        case PRIM_FRONTIER_SEQUENCE_EXHAUSTED:
            return "PRIM_FRONTIER_SEQUENCE_EXHAUSTED";
        case PRIM_FRONTIER_INVALID_STATE:
            return "PRIM_FRONTIER_INVALID_STATE";
        default:
            return "PRIM_FRONTIER_UNKNOWN_STATUS";
    }
}
