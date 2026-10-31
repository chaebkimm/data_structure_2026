#include <assert.h>
#include <stdio.h>
#include "lab.c"

int main(void)
{
    /* Smoke tests only. Add ONE focused original regression. Choose a
       question such as:
       1. Node IDs versus positions, both repair directions, and live maps.
       2. A cheaper multi-edge route, an unreachable node, and another source.
       3. Equal distances and repeated runs, without assuming stable ties.
       Keep at most ten live IDs; add each ID once until removed; remove
       only while nonempty. All graph weights must be positive and every
       candidate sum must fit in int. The supplied lab.c remains unchanged. */
    init_heap();
    add_node(8, 20);
    add_node(3, 7);
    update_value(8, 2);
    assert(remove_root() == 8);
    assert(remove_root() == 3 && size == 0);

    alphabet_nodes_init();
    nodes_size = 3;
    nodes[0].adj_list[0] = 1;
    nodes[0].adj_size = 1;
    edge_length[0][1] = 4;
    min_dist(0);
    assert(node_dist[0] == 0 && node_dist[1] == 4 && node_dist[2] == -1);
    assert(found[0] == 1 && found[1] == 1 && found[2] == 0);
    puts("Module 11 student smoke tests passed; add your original evidence.");
    return 0;
}
