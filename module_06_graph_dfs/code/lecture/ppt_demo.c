/* Compile from the repository root with -std=c11 -I. */
#include <stdio.h>
#include "module_06_graph_dfs/student/lab.c"

static void slide_graph_init(void)
{
    const int pairs[10][2] = {
        {0, 1}, {0, 2}, {1, 2}, {1, 6}, {2, 3},
        {2, 5}, {2, 6}, {3, 4}, {3, 5}, {4, 5}
    };
    nodes_size = 7;
    for (int i = 0; i < nodes_size; ++i) {
        nodes[i].data = (char)('A' + i);
        nodes[i].adj_size = 0;
    }
    for (int i = 0; i < 10; ++i) {
        int u = pairs[i][0], v = pairs[i][1];
        nodes[u].adj_list[nodes[u].adj_size++] = v;
        nodes[v].adj_list[nodes[v].adj_size++] = u;
    }
}

int main(void)
{
    slide_graph_init();
    init_edges_list(0);
    find_bcc(0);

    puts("vertex_index visit_number parent_index low");
    for (int i = 0; i < nodes_size; ++i) {
        printf("%d %d %d %d\n", i,
               visit_num[i], parent[i], back_num[i]);
    }
    printf("edges_size = %d\n", edges_size);
    for (int i = 0; i < edges_size; ++i) {
        int u = edges[i].from, v = edges[i].to;
        printf("%d: visit %d -> visit %d (%s)\n", i, visit_num[u], visit_num[v],
               parent[v] == u ? "tree" : "back");
    }
    printf("current_bcc = %d\n", current_bcc);
    for (int i = 0; i < current_bcc; ++i) {
        printf("bcc[%d]:", i);
        for (int j = 0; j < bcc_size[i]; ++j) {
            printf(" %d", bcc[i][j]);
        }
        putchar('\n');
        printf("block[%d] visits:", i);
        for (int j = 0; j < bcc_size[i]; ++j) {
            int edge = bcc[i][j];
            int u = visit_num[edges[edge].from];
            int v = visit_num[edges[edge].to];
            printf(" %d-%d", u < v ? u : v, u < v ? v : u);
        }
        putchar('\n');
    }
    printf("top = %d\n", top);
    return 0;
}
