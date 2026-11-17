#ifndef DIJKSTRA_FRONTIER_H
#define DIJKSTRA_FRONTIER_H

#include "weighted_graph.h"

#include <stdbool.h>
#include <stddef.h>

#define DIJKSTRA_FRONTIER_MAX_ENTRIES 241U

/*
 * The frontier is the pending work. A smaller distance leaves first. Equal
 * distances leave in insertion order; vertex does not break a tie.
 */
typedef struct {
    size_t vertex;
    size_t distance;
    size_t insertion_sequence;
} DijkstraFrontierEntry;

/*
 * data stores a binary minimum Heap. limit is selected by the caller and may
 * be zero through 241. Capacity grows 0, min(8, limit), then doubles through
 * 16, 32, 64, and 128 before a final step clipped to limit. Draining retains
 * the allocation and next_sequence; sequence numbers remain global for the
 * Frontier object's lifetime. Only destroy resets the sequence to zero.
 */
typedef struct {
    DijkstraFrontierEntry *data;
    size_t size;
    size_t capacity;
    size_t limit;
    size_t next_sequence;
    size_t comparison_count;
} DijkstraFrontier;

typedef enum {
    DIJKSTRA_FRONTIER_OK = 0,
    DIJKSTRA_FRONTIER_INVALID_ARGUMENT,
    DIJKSTRA_FRONTIER_OUT_OF_RANGE,
    DIJKSTRA_FRONTIER_FULL,
    DIJKSTRA_FRONTIER_EMPTY,
    DIJKSTRA_FRONTIER_ALLOCATION,
    DIJKSTRA_FRONTIER_SEQUENCE_EXHAUSTED,
    DIJKSTRA_FRONTIER_INVALID_STATE
} DijkstraFrontierStatus;

/*
 * Initializes an all-zero Frontier without allocating.
 */
DijkstraFrontierStatus dijkstra_frontier_init(
    DijkstraFrontier *frontier,
    size_t limit
);

/*
 * Checks constant-time ownership and counter relationships. Heap order is
 * checked separately.
 */
DijkstraFrontierStatus dijkstra_frontier_validate(
    const DijkstraFrontier *frontier
);

/*
 * Scans all live entries and writes whether Heap order and entry bounds
 * hold. This diagnostic does not change comparison_count. Failure preserves
 * the bool output.
 */
DijkstraFrontierStatus dijkstra_frontier_is_min_heap(
    const DijkstraFrontier *frontier,
    bool *out_is_min_heap
);

/*
 * Assigns insertion_sequence internally and sifts upward. distance must be
 * below SIZE_MAX. Every failure preserves all fields and allocated entries.
 */
DijkstraFrontierStatus dijkstra_frontier_push(
    DijkstraFrontier *frontier,
    size_t vertex,
    size_t distance
);

/*
 * Removes the stable minimum and repairs one downward path. Failure
 * preserves the output and Frontier.
 */
DijkstraFrontierStatus dijkstra_frontier_pop(
    DijkstraFrontier *frontier,
    DijkstraFrontierEntry *out_entry
);

void dijkstra_frontier_destroy(DijkstraFrontier *frontier);

const char *dijkstra_frontier_status_name(
    DijkstraFrontierStatus status
);

#ifdef DIJKSTRA_TESTING
/*
 * Fails one Frontier growth after exactly successful_allocations successful
 * growths. Zero fails the next attempted growth.
 */
void dijkstra_frontier_test_fail_allocation_after(
    size_t successful_allocations
);

size_t dijkstra_frontier_test_live_allocation_count(void);
#endif

#endif
