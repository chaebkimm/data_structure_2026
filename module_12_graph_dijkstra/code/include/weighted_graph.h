#ifndef WEIGHTED_GRAPH_H
#define WEIGHTED_GRAPH_H

#include <stddef.h>

#define WEIGHTED_GRAPH_MAX_VERTICES 16U
#define WEIGHTED_GRAPH_MAX_ARCS 240U

/*
 * A directed edge has one stored direction. An undirected edge is stored
 * twice, once in each direction, so it contributes two stored arcs.
 */
typedef enum {
    WEIGHTED_GRAPH_DIRECTED = 0,
    WEIGHTED_GRAPH_UNDIRECTED
} WeightedGraphKind;

typedef struct {
    size_t to;
    size_t weight;
} WeightedEdge;

/*
 * One dynamic array stores the outgoing edges of one vertex. Live edges are
 * sorted by destination vertex and occupy data[0] through data[size - 1].
 */
typedef struct {
    WeightedEdge *data;
    size_t size;
    size_t capacity;
} WeightedEdgeArray;

/*
 * This graph owns every non-NULL row allocation. arc_count counts stored
 * directed arcs; an undirected connection therefore adds two.
 */
typedef struct {
    size_t vertex_count;
    WeightedGraphKind kind;
    size_t arc_count;
    WeightedEdgeArray outgoing[WEIGHTED_GRAPH_MAX_VERTICES];
} WeightedGraph;

typedef enum {
    WEIGHTED_GRAPH_OK = 0,
    WEIGHTED_GRAPH_INVALID_ARGUMENT,
    WEIGHTED_GRAPH_OUT_OF_RANGE,
    WEIGHTED_GRAPH_SELF_LOOP,
    WEIGHTED_GRAPH_EDGE_EXISTS,
    WEIGHTED_GRAPH_EDGE_ABSENT,
    WEIGHTED_GRAPH_NEGATIVE_WEIGHT,
    WEIGHTED_GRAPH_INVALID_WEIGHT_TEXT,
    WEIGHTED_GRAPH_WEIGHT_OUT_OF_RANGE,
    WEIGHTED_GRAPH_INVALID_GRAPH,
    WEIGHTED_GRAPH_ALLOCATION
} WeightedGraphStatus;

/*
 * Initializes an all-zero or previously destroyed object. Zero through
 * sixteen vertices are accepted. No row allocation happens here.
 */
WeightedGraphStatus weighted_graph_init(
    WeightedGraph *graph,
    size_t vertex_count,
    WeightedGraphKind kind
);

/*
 * Checks the complete owned representation: capacity shapes, sorted unique
 * destinations, weights below SIZE_MAX, arc_count, inactive rows, and
 * matching reverse arcs in an undirected graph.
 */
WeightedGraphStatus weighted_graph_validate(
    const WeightedGraph *graph
);

/*
 * Parses one nonnegative decimal size_t value. Surrounding ASCII whitespace
 * and one leading plus are accepted. Negative, malformed, overflowing, and
 * SIZE_MAX values are rejected. Failure preserves out_weight.
 */
WeightedGraphStatus weighted_graph_parse_weight(
    const char *text,
    size_t *out_weight
);

/*
 * Adds one simple edge. Self-loops and parallel edges are forbidden.
 * Undirected insertion stages both possible allocations before changing
 * either row. Every failure preserves the complete graph.
 */
WeightedGraphStatus weighted_graph_add_edge(
    WeightedGraph *graph,
    size_t from_vertex,
    size_t to_vertex,
    size_t weight
);

/*
 * Parses weight_text and then applies the same atomic edge insertion.
 */
WeightedGraphStatus weighted_graph_add_edge_text(
    WeightedGraph *graph,
    size_t from_vertex,
    size_t to_vertex,
    const char *weight_text
);

/*
 * Reports an existing stored arc's weight. Failure preserves out_weight.
 */
WeightedGraphStatus weighted_graph_get_weight(
    const WeightedGraph *graph,
    size_t from_vertex,
    size_t to_vertex,
    size_t *out_weight
);

/*
 * Releases every owned row and restores the all-zero directed state.
 * Passing NULL is a no-op.
 */
void weighted_graph_destroy(WeightedGraph *graph);

const char *weighted_graph_status_name(WeightedGraphStatus status);

#ifdef DIJKSTRA_TESTING
/*
 * Fails one graph-row allocation after exactly successful_allocations
 * successful attempts. Zero fails the next graph-row allocation.
 */
void weighted_graph_test_fail_allocation_after(
    size_t successful_allocations
);

size_t weighted_graph_test_live_row_count(void);
#endif

#endif
