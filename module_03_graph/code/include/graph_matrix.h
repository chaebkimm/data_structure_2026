#ifndef GRAPH_MATRIX_H
#define GRAPH_MATRIX_H

#include <stddef.h>

#define GRAPH_MAX_VERTICES 16

/*
 * A directed, unweighted graph stored in a fixed adjacency matrix.
 * Active vertex indexes are 0 through vertex_count - 1. A grid entry of 1
 * records one directed edge; 0 records no edge. Active diagonal entries and
 * every inactive row and column are kept at 0 by valid callers.
 *
 * Edge and degree operations check the pointer, vertex_count, and requested
 * indexes described below. They assume unrelated grid invariants already
 * hold; they do not scan and validate the entire matrix. Removal may clear
 * its selected cell even when that cell is a nonzero diagonal defect.
 */
struct DirectedGraph {
    size_t vertex_count;
    int grid[GRAPH_MAX_VERTICES][GRAPH_MAX_VERTICES];
};

/*
 * Initializes vertex_count active vertices and clears the entire fixed grid.
 * Returns 1 on success. A null graph or a count above the fixed limit returns
 * 0 and leaves every supplied graph byte unchanged.
 */
int graph_init(struct DirectedGraph *graph, size_t vertex_count);

/*
 * Records the directed edge from -> to. Both indexes must be active and must
 * differ. Re-adding an existing edge succeeds without further change.
 * Invalid input returns 0 and leaves the graph unchanged.
 */
int graph_add_edge(
    struct DirectedGraph *graph,
    size_t from,
    size_t to
);

/*
 * Clears the directed edge from -> to. Both indexes must be active. Removing
 * an absent edge, including an already-clear diagonal cell, succeeds.
 * Invalid input returns 0 and leaves the graph unchanged.
 */
int graph_remove_edge(
    struct DirectedGraph *graph,
    size_t from,
    size_t to
);

/*
 * Counts entries equal to 1 across the active part of vertex's row. Returns
 * 1 and writes the count on success. Invalid input returns 0 and leaves the
 * output unchanged.
 */
int graph_out_degree(
    const struct DirectedGraph *graph,
    size_t vertex,
    size_t *out_degree
);

#endif
