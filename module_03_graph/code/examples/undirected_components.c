#include <stdio.h>

#define MAX_VERTICES 16
#define MAX_EDGES 120
#define MAX_BLOCKS (MAX_EDGES + MAX_VERTICES)
#define MAX_MEMBERS (2 * MAX_EDGES + MAX_VERTICES)

typedef struct {
    int to, edge, next;
} Neighbor;

int vertex_count, edge_count, entry_count;
int head[MAX_VERTICES], edge_u[MAX_EDGES], edge_v[MAX_EDGES];
Neighbor neighbor[2 * MAX_EDGES];
const char *name[MAX_VERTICES];

int dfn[MAX_VERTICES], low[MAX_VERTICES], component[MAX_VERTICES];
int cut[MAX_VERTICES], clock_value, component_count;
int pending[MAX_EDGES], pending_count;
int block_count, member_count, block_edge_count;
int block_vertex[MAX_MEMBERS], block_edge[MAX_EDGES];
int block_vertex_start[MAX_BLOCKS + 1], block_edge_start[MAX_BLOCKS + 1];
int in_block[MAX_VERTICES];

int initialize(int count, const char *labels[]) {
    if (count < 0 || count > MAX_VERTICES) return 0;
    vertex_count = count;
    edge_count = entry_count = 0;
    for (int u = 0; u < count; ++u) {
        head[u] = -1;
        name[u] = labels[u];
    }
    return 1;
}

/* Keep each account's neighbors in ascending account-ID order. */
void insert_neighbor(int from, int to, int edge) {
    int *link = &head[from];
    while (*link != -1 && neighbor[*link].to < to)
        link = &neighbor[*link].next;
    neighbor[entry_count] = (Neighbor){to, edge, *link};
    *link = entry_count++;
}

/* One undirected edge receives two neighbor entries with one shared ID. */
int add_edge(int u, int v) {
    if (u < 0 || v < 0 || u >= vertex_count || v >= vertex_count || u == v)
        return 0;
    for (int p = head[u]; p != -1; p = neighbor[p].next)
        if (neighbor[p].to == v) return 0;
    if (edge_count == MAX_EDGES) return 0;
    int edge = edge_count++;
    edge_u[edge] = u;
    edge_v[edge] = v;
    insert_neighbor(u, v, edge);
    insert_neighbor(v, u, edge);
    return 1;
}

void add_block_vertex(int u) {
    if (in_block[u] == block_count) return;
    in_block[u] = block_count;
    block_vertex[member_count++] = u;
}

/* The next block begins immediately after this block's entries. */
void close_block(void) {
    ++block_count;
    block_vertex_start[block_count] = member_count;
    block_edge_start[block_count] = block_edge_count;
}

/* Read pending edges backward through the edge that opened this block. */
void finish_block(int opening_edge) {
    int edge;
    do {
        edge = pending[--pending_count];
        block_edge[block_edge_count++] = edge;
        add_block_vertex(edge_u[edge]);
        add_block_vertex(edge_v[edge]);
    } while (edge != opening_edge);
    close_block();
}

void explore(int u, int parent_edge) {
    dfn[u] = low[u] = ++clock_value;
    component[u] = component_count;
    int children = 0;

    for (int p = head[u]; p != -1; p = neighbor[p].next) {
        int v = neighbor[p].to;
        int edge = neighbor[p].edge;
        if (edge == parent_edge) continue;

        if (dfn[v] == 0) {
            ++children;
            pending[pending_count++] = edge;
            explore(v, edge);
            if (low[v] < low[u]) low[u] = low[v];

            if (low[v] >= dfn[u]) {
                if (parent_edge != -1) cut[u] = 1;
                finish_block(edge);
            }
        } else if (dfn[v] < dfn[u]) {
            /* Record this earlier connection once, from its later end. */
            pending[pending_count++] = edge;
            if (dfn[v] < low[u]) low[u] = dfn[v];
        }
    }
    if (parent_edge == -1 && children > 1) cut[u] = 1;
}

void analyze(void) {
    clock_value = component_count = pending_count = block_count = 0;
    member_count = block_edge_count = 0;
    block_vertex_start[0] = block_edge_start[0] = 0;
    for (int u = 0; u < vertex_count; ++u) {
        dfn[u] = low[u] = component[u] = cut[u] = 0;
        in_block[u] = -1;
    }

    for (int u = 0; u < vertex_count; ++u) {
        if (dfn[u] != 0) continue;
        ++component_count;
        explore(u, -1);
        /* Convention: an isolated account is a singleton block. */
        if (head[u] == -1) {
            add_block_vertex(u);
            close_block();
        }
    }
}

void print_results(void) {
    printf("Connected components: %d\n", component_count);
    puts("Account  component  dfn  low  cut");
    for (int u = 0; u < vertex_count; ++u)
        printf("%-7s  %9d  %3d  %3d  %s\n", name[u], component[u],
               dfn[u], low[u], cut[u] ? "yes" : "no");

    puts("\nBlocks (vertices; edges):");
    for (int block = 0; block < block_count; ++block) {
        printf("B%d:", block + 1);
        for (int i = block_vertex_start[block]; i < block_vertex_start[block + 1]; ++i)
            printf(" %s", name[block_vertex[i]]);
        printf(" ;");
        for (int i = block_edge_start[block]; i < block_edge_start[block + 1]; ++i) {
            int edge = block_edge[i];
            printf(" %s--%s", name[edge_u[edge]], name[edge_v[edge]]);
        }
        if (block_edge_start[block] == block_edge_start[block + 1]) printf(" (no edges)");
        putchar('\n');
    }

    puts("\nBlock-cut forest (block -- cut account):");
    for (int block = 0; block < block_count; ++block) {
        int links = 0;
        for (int i = block_vertex_start[block]; i < block_vertex_start[block + 1]; ++i) {
            int u = block_vertex[i];
            if (!cut[u]) continue;
            printf("B%d -- %s\n", block + 1, name[u]);
            ++links;
        }
        if (links == 0) printf("B%d (standalone block node)\n", block + 1);
    }
}

int main(void) {
    const char *labels[] = {"Mina", "Joon", "Sora", "Dae", "Hana", "Leo", "Nuri", "Yuna"};
    const int edges[][2] = {{0, 1}, {0, 2}, {0, 3}, {0, 6}, {0, 7},
                            {1, 2}, {1, 3}, {2, 3}, {4, 5}};
    if (!initialize(8, labels)) return 1;
    for (unsigned int i = 0; i < sizeof edges / sizeof edges[0]; ++i) {
        if (!add_edge(edges[i][0], edges[i][1])) {
            fputs("Invalid edge.\n", stderr);
            return 1;
        }
    }
    analyze();
    print_results();
    return 0;
}
