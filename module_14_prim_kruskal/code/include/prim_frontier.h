#ifndef PRIM_FRONTIER_H
#define PRIM_FRONTIER_H

#include "undirected_edge_list.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define PRIM_FRONTIER_MAX_ENTRIES 136U
#define PRIM_FRONTIER_NO_VERTEX \
    ((size_t)UNDIRECTED_EDGE_LIST_MAX_VERTICES)
#define PRIM_FRONTIER_NO_EDGE \
    ((size_t)UNDIRECTED_EDGE_LIST_MAX_LOGICAL_EDGES)

/*
 * A smaller signed key leaves first. Equal keys leave in insertion order.
 * vertex, parent, and edge_id do not break a Heap tie.
 */
typedef struct {
    size_t vertex;
    int64_t key;
    size_t parent;
    size_t edge_id;
    size_t insertion_sequence;
} PrimFrontierEntry;

/*
 * data owns a dynamic binary minimum Heap. Draining retains allocation and
 * the global insertion sequence. Only destroy resets the sequence.
 */
typedef struct {
    PrimFrontierEntry *data;
    size_t size;
    size_t capacity;
    size_t limit;
    size_t next_sequence;
} PrimFrontier;

typedef enum {
    PRIM_FRONTIER_OK = 0,
    PRIM_FRONTIER_INVALID_ARGUMENT,
    PRIM_FRONTIER_OUT_OF_RANGE,
    PRIM_FRONTIER_FULL,
    PRIM_FRONTIER_EMPTY,
    PRIM_FRONTIER_ALLOCATION,
    PRIM_FRONTIER_SEQUENCE_EXHAUSTED,
    PRIM_FRONTIER_INVALID_STATE
} PrimFrontierStatus;

PrimFrontierStatus prim_frontier_init(
    PrimFrontier *frontier,
    size_t limit
);
PrimFrontierStatus prim_frontier_validate(
    const PrimFrontier *frontier
);
PrimFrontierStatus prim_frontier_is_min_heap(
    const PrimFrontier *frontier,
    bool *out_is_min_heap
);
PrimFrontierStatus prim_frontier_push(
    PrimFrontier *frontier,
    size_t vertex,
    int64_t key,
    size_t parent,
    size_t edge_id
);
PrimFrontierStatus prim_frontier_pop(
    PrimFrontier *frontier,
    PrimFrontierEntry *out_entry
);
void prim_frontier_destroy(PrimFrontier *frontier);
const char *prim_frontier_status_name(PrimFrontierStatus status);

#ifdef MST_TESTING
void prim_frontier_test_fail_next_growth(void);
size_t prim_frontier_test_live_allocation_count(void);
#endif

#endif
