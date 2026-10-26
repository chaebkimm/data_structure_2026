#include <assert.h>
#include <stdio.h>
#include "lab.c"

/* Supplied comparison only: the teaching lab remains unchanged. */
struct LinearCounts {
    int selection_rounds;
    int slot_inspections;
    int selected_nodes;
    int adjacency_inspections;
    int strict_improvements;
};

static void load_fixture(void)
{
    const int arcs[][3] = {
        {0, 1, 9}, {0, 2, 2}, {0, 4, 14},
        {1, 3, 1}, {1, 4, 8},
        {2, 1, 3}, {2, 3, 2}, {3, 4, 2}
    };
    alphabet_nodes_init();
    nodes_size = 6;
    for (int u = 0; u < 10; ++u) {
        for (int v = 0; v < 10; ++v) {
            edge_length[u][v] = 0;
        }
    }
    for (int i = 0; i < 8; ++i) {
        int u = arcs[i][0];
        int v = arcs[i][1];
        nodes[u].adj_list[nodes[u].adj_size++] = v;
        edge_length[u][v] = arcs[i][2];
    }
}

/* BFS minimizes hops. route_cost records the cost of its first-discovery
   tree, so it must not be interpreted as a minimum weighted distance. */
static void bfs_reference(int source, int hops[10], int route_cost[10],
                          int *pops, int *adjacency_inspections)
{
    int queue[10];
    int front = 0;
    int end = 0;
    for (int id = 0; id < 10; ++id) {
        hops[id] = -1;
        route_cost[id] = -1;
    }
    hops[source] = 0;
    route_cost[source] = 0;
    queue[end++] = source;
    while (front < end) {
        int u = queue[front++];
        ++*pops;
        for (int i = 0; i < nodes[u].adj_size; ++i) {
            int v = nodes[u].adj_list[i];
            ++*adjacency_inspections;
            if (hops[v] == -1) {
                hops[v] = hops[u] + 1;
                route_cost[v] = route_cost[u] + edge_length[u][v];
                assert(end < 10);
                queue[end++] = v;
            }
        }
    }
}

/* Independent linear minimum selection: local distances and done flags,
   no heap or heap helpers. A slot inspection is one visited vertex slot
   during selection, including the final round that finds no pending node. */
static struct LinearCounts linear_dijkstra(int source, int distance[10])
{
    struct LinearCounts counts = {0};
    int done[10] = {0};
    for (int id = 0; id < 10; ++id) {
        distance[id] = -1;
    }
    distance[source] = 0;
    for (;;) {
        int selected = -1;
        ++counts.selection_rounds;
        for (int id = 0; id < nodes_size; ++id) {
            ++counts.slot_inspections;
            if (!done[id] && distance[id] != -1 &&
                (selected == -1 || distance[id] < distance[selected])) {
                selected = id;
            }
        }
        if (selected == -1) {
            break;
        }
        done[selected] = 1;
        ++counts.selected_nodes;
        for (int i = 0; i < nodes[selected].adj_size; ++i) {
            int v = nodes[selected].adj_list[i];
            int candidate = distance[selected] + edge_length[selected][v];
            ++counts.adjacency_inspections;
            if (distance[v] == -1 || candidate < distance[v]) {
                distance[v] = candidate;
                ++counts.strict_improvements;
            }
        }
    }
    return counts;
}

static void print_vector(const char *label, const int values[10])
{
    printf("%s[", label);
    for (int id = 0; id < nodes_size; ++id) {
        printf("%s%d", id == 0 ? "" : ", ", values[id]);
    }
    puts("]");
}

int main(void)
{
    const int expected_hops[] = {0, 1, 1, 2, 1, -1};
    const int expected_costs[] = {0, 5, 2, 4, 6, -1};
    int hops[10];
    int bfs_route_cost[10];
    int linear_distance[10];
    int bfs_pops = 0;
    int bfs_adjacency_inspections = 0;

    load_fixture();
    bfs_reference(0, hops, bfs_route_cost, &bfs_pops,
                  &bfs_adjacency_inspections);
    struct LinearCounts linear = linear_dijkstra(0, linear_distance);
    min_dist(0);
    for (int id = 0; id < nodes_size; ++id) {
        assert(hops[id] == expected_hops[id]);
        assert(linear_distance[id] == expected_costs[id]);
        assert(node_dist[id] == linear_distance[id]);
    }
    assert(bfs_route_cost[3] == 10 && bfs_route_cost[4] == 14);
    assert(bfs_pops == 5 && bfs_adjacency_inspections == 8);
    assert(linear.selection_rounds == 6 && linear.slot_inspections == 36);
    assert(linear.selected_nodes == 5 && linear.adjacency_inspections == 8);
    assert(linear.strict_improvements == 6);
    assert(size == 0);

    puts("Canonical directed graph, source A; vector order A B C D E F.");
    print_vector("BFS minimum hops:            ", hops);
    print_vector("BFS-selected route costs:    ", bfs_route_cost);
    print_vector("Linear Dijkstra costs:       ", linear_distance);
    print_vector("Indexed-heap Dijkstra costs: ", node_dist);
    printf("Measured BFS: %d queue pops, %d adjacency inspections.\n",
           bfs_pops, bfs_adjacency_inspections);
    printf("Measured linear selection: %d rounds, %d slot inspections "
           "(includes final no-candidate scan), %d selected nodes.\n",
           linear.selection_rounds, linear.slot_inspections,
           linear.selected_nodes);
    printf("Measured linear relaxation: %d adjacency inspections, "
           "%d strict improvements.\n", linear.adjacency_inspections,
           linear.strict_improvements);
    puts("Manual indexed-heap trace: 5 add_node calls, 5 remove_root calls, "
         "2 update_value calls; peak live size 3.");
    puts("lab.c exports no operation counters; both weighted results agree.");
    return 0;
}
