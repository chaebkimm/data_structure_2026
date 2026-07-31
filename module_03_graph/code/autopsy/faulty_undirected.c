/*
 * INTENTIONALLY INVALID UNDIRECTED-GRAPH TRAINING PROGRAM.
 *
 * Every access stays inside a fixed local matrix. The defect is logical:
 * one direction of an undirected connection is true while its mirror is
 * false.
 */

#include "graph_matrix.h"

#include <stdio.h>

static const char *yes_or_no(bool value)
{
    return value ? "yes" : "no";
}

int main(void)
{
    Graph graph;
    size_t row;
    size_t column;

    graph.vertex_count = 3U;
    graph.kind = GRAPH_UNDIRECTED;
    for (row = 0U; row < (size_t)GRAPH_MAX_VERTICES; ++row) {
        for (column = 0U;
             column < (size_t)GRAPH_MAX_VERTICES;
             ++column) {
            graph.adjacency[row][column] = false;
        }
    }

    /*
     * Vertex 0 is Gateway and vertex 1 is Web. This intentionally records
     * only Gateway -> Web even though the graph claims to be undirected.
     */
    graph.adjacency[0][1] = true;

    (void)printf(
        "Gateway reports Web as connected: %s\n",
        yes_or_no(graph.adjacency[0][1])
    );
    (void)printf(
        "Web reports Gateway as connected: %s\n",
        yes_or_no(graph.adjacency[1][0])
    );
    (void)printf(
        "mirror cells agree: %s\n",
        yes_or_no(
            graph.adjacency[0][1] == graph.adjacency[1][0]
        )
    );
    return 0;
}
