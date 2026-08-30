/*
 * INTENTIONALLY INVALID GHOST-CONNECTION TRAINING PROGRAM.
 *
 * Every access stays inside one fixed local matrix. The defect is changing
 * vertex_count without clearing rows and columns that become inactive.
 */

#include "graph_matrix.h"

#include <stdio.h>

static const char *yes_or_no(int condition)
{
    return condition ? "yes" : "no";
}

int main(void)
{
    struct DirectedGraph network;
    size_t row;
    size_t column;

    network.vertex_count = 4U;
    for (row = 0U; row < (size_t)GRAPH_MAX_VERTICES; row = row + 1U) {
        for (column = 0U;
             column < (size_t)GRAPH_MAX_VERTICES;
             column = column + 1U) {
            network.grid[row][column] = 0;
        }
    }
    network.grid[3][1] = 1;

    (void)printf(
        "before shrinking: vertex 3 -> 1 = %d\n",
        network.grid[3][1]
    );

    /* Intentional fault: row and column 3 are not cleared before shrinking. */
    network.vertex_count = 3U;
    (void)printf("after shrinking to 3 vertices:\n");
    (void)printf(
        "vertex 3 is inactive: %s\n",
        yes_or_no(3U >= network.vertex_count)
    );
    (void)printf(
        "inactive cell [3][1] is still %d\n",
        network.grid[3][1]
    );

    /* A second faulty count-only change makes the stale edge active again. */
    network.vertex_count = 4U;
    (void)printf("after growing back to 4 without clearing:\n");
    (void)printf(
        "ghost connection 3 -> 1 reappears: %s\n",
        yes_or_no(network.grid[3][1] == 1)
    );
    return 0;
}
