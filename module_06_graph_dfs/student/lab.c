#include "module_03_graph/student/lab.c"
#include "module_04_stack/student/lab.c"

struct GraphEdge {
    int from, to; 
    /* tree edge: visit_num[from] < visit_num[to] */
    /* back edge: visit_num[from] > visit_num[to] */
};

struct GraphEdge edges[10];
int edges_size = 0;

int edge_index[10][10] = {0};

void add_edge(int u, int v) {
    int index = edges_size++;
    edges[index].from = u;
    edges[index].to = v;
    edge_index[u][v] = index;
    edge_index[v][u] = index;
}

void init_visit() {
    visit_time = 0;

    for (int i = 0; i < nodes_size; i++) {
        visit_num[i] = 0;
        parent[i] = -1;
    }
}

void _init_edges_list(int node) {
    visit_num[node] = ++visit_time;
    for (int i = 0; i < nodes[node].adj_size; i++) {
        int adj = nodes[node].adj_list[i];
        if (visit_num[adj] == 0) {
            /* tree edge */
            parent[adj] = node;
            add_edge(node, adj);
            _init_edges_list(adj);
        }
        else if (adj == parent[node]) {
            /* tree edge to parent node (processed) */
        }
        else if (visit_num[adj] < visit_num[node]) {
            /* back edge to ancester */
            add_edge(node, adj);
        }
        else if (visit_num[adj] > visit_num[node]) {
            /* back edge to descendant (processed) */
        }
        else {
            /* edge connecting node to itself */
        }
    }
    /* postorder processing */
}

void init_edges_list(int start_node) {
    init_visit();
    edges_size = 0;
    for (int i = 0; i < nodes_size; i++) {
        for (int j = 0; j < nodes_size; j++) {
            edge_index[i][j] = -1;
        }
    }
    _init_edges_list(start_node);
}

int bcc[10][45];
int bcc_size[10] = {0};
int current_bcc = 0;

void _find_bcc(int node) {
    visit_num[node] = ++visit_time;
    for (int i = 0; i < nodes[node].adj_size; i++) {
        int adj = nodes[node].adj_list[i];
        if (visit_num[adj] == 0) {
            /* tree edge add to stack and proceed */
            push(edge_index[node][adj]);
            parent[adj] = node;
            _find_bcc(adj);
        }
        else if (adj == parent[node]) {
            /* tree edge to parent node (processed) */
        }
        else if (visit_num[adj] < visit_num[node]) {
            /* back edge to ancester add to stack */
            push(edge_index[node][adj]);
        }
        else if (visit_num[adj] > visit_num[node]) {
            /* back edge to descendant (processed) */
        }
        else {
            /* edge connecting node to itself */
        }
    }
    /* postorder processing */
    if (parent[node] == -1 || back_num[node] < visit_num[parent[node]]) {
        return;
    } 
    int parent_edge = edge_index[parent[node]][node];
    int cur = current_bcc++;
    int pos = 0;

    int edge;
    do {
        edge = pop();
        bcc[cur][pos++] = edge;
    } while (edge != parent_edge);
    bcc_size[cur] = pos;
}

/* called once */
void find_bcc(int root) {
    init_visit();
    save_back_num(root);
    top = -1;
    init_visit();
    _find_bcc(root);
}