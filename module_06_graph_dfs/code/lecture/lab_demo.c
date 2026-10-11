/* Run from the repository root with -I., or use make lecture in code/. */
#include <stdio.h>
#include "module_06_graph_dfs/student/lab.c"

int main(void)
{
    alphabet_nodes_init();
    edges_init();
    init_edges_list(0);
    find_bcc(0);

    puts("vertex discovery parent low");
    for (int i = 0; i < nodes_size; ++i) {
        if (visit_num[i] != 0) {
            printf("%c %d %d %d\n", nodes[i].data,
                   visit_num[i], parent[i], back_num[i]);
        }
    }
    printf("edges_size = %d\n", edges_size);
    for (int i = 0; i < edges_size; ++i) {
        int u = edges[i].from;
        int v = edges[i].to;
        printf("%d: %c -> %c (%s)\n", i, nodes[u].data, nodes[v].data,
               parent[v] == u ? "tree" : "back");
    }
    printf("current_bcc = %d\n", current_bcc);
    for (int i = 0; i < current_bcc; ++i) {
        printf("bcc[%d]:", i);
        for (int j = 0; j < bcc_size[i]; ++j) {
            printf(" %d", bcc[i][j]);
        }
        putchar('\n');
    }
    printf("top = %d\n", top);
    return 0;
}
