# Chapter 6. Graph DFS, Edge Lists, and Biconnected Components

We will reuse Chapter 3's undirected adjacency lists and discovery numbers. We will give each reached edge an index, then use Chapter 4's stack to collect edges into blocks when a recursive branch finishes.

The implementation for this chapter is [lab.c](lab.c). It includes the earlier graph and stack labs. The checked matrix-based implementation under `code/starter` and `code/solution` is a separate legacy exercise.

## Thinking Logically

### Which vertices can one search reach?

Chapter 3 stores each undirected connection in both endpoint lists. Following every connection recursively would return to a vertex already entered. A discovery number prevents another call: zero means unvisited, and a positive number records the first entry.

Use the graph built by `alphabet_nodes_init()` and `edges_init()` throughout this chapter. The labels A–J have indices 0–9. The stored undirected pairs are:

```text
A-B, B-C, B-D, B-E, B-F, D-E, D-F, E-F, G-H
I and J are isolated.
```

Neighbors are read in their stored insertion order. They are not sorted by this lab.

| Vertex | Index | Stored neighbors |
| --- | ---: | --- |
| A | 0 | B |
| B | 1 | A, C, D, E, F |
| C | 2 | B |
| D | 3 | B, E, F |
| E | 4 | B, D, F |
| F | 5 | B, D, E |
| G | 6 | H |
| H | 7 | G |
| I | 8 | none |
| J | 9 | none |

Starting at A enters A, B, C, D, E, F. G, H, I, and J remain unvisited. The whole graph has four connected components, but the Module 6 wrappers explore only the selected starting component. They do not perform Chapter 3's all-vertex sweep.

### How do we record each undirected edge once?

Each undirected edge appears twice in the neighbor lists. We need one record for the connection, so both endpoint orders must refer to the same edge index.

When the neighbor is unvisited, record the current-to-neighbor edge, assign the neighbor's parent, and recurse. This is a tree edge: it creates a new DFS child. When the neighbor is the parent, skip the reverse entry of the same tree edge.

For another visited neighbor, compare discovery numbers. A smaller number identifies an ancestor in this simple undirected DFS. Record the current-to-ancestor connection as a back edge. A larger number is the reverse entry of an already recorded connection and is skipped. An equal number represents a self-loop and is ignored by this lab.

These rules assume a simple undirected graph with symmetric adjacency lists. Discovery-number comparisons alone do not classify edges in a directed graph. Parallel edges would also require different handling: skipping by parent vertex could discard a separate edge.

`init_edges_list(0)` produces the following records. The directions describe DFS processing; the input edges remain undirected.

| Edge index | `from → to` | Kind |
| ---: | --- | --- |
| 0 | A → B | tree |
| 1 | B → C | tree |
| 2 | B → D | tree |
| 3 | D → E | tree |
| 4 | E → B | back |
| 5 | E → F | tree |
| 6 | F → B | back |
| 7 | F → D | back |

For example, `edge_index[1][4]` and `edge_index[4][1]` both contain 4. The disconnected edge G–H is not indexed; its entries remain -1. Only `edges[0]` through `edges[edges_size - 1]` are active.

### How far back can a finished branch reconnect?

A branch may contain a connection to an earlier ancestor. Chapter 3's `save_back_num()` summarizes that possibility. On entry, it gives a vertex the same discovery and back number. After a child returns, it keeps the smaller child back number. For a visited non-parent neighbor, it keeps the smaller neighbor discovery number.

The result, called a low-link value here, is the earliest discovery number reachable by descending through tree edges and then using at most one back edge. It also includes the vertex's own discovery number.

After starting at A, the values are:

| Vertex | `visit_num` | `parent` | `back_num` |
| --- | ---: | --- | ---: |
| A | 1 | -1 | 1 |
| B | 2 | A (0) | 2 |
| C | 3 | B (1) | 3 |
| D | 4 | B (1) | 2 |
| E | 5 | D (3) | 2 |
| F | 6 | E (4) | 2 |

F connects back to B and D. Its minimum is B's discovery number, 2. That value returns through E and D. C has only its parent edge, so its value remains 3.

### When can we close a group of edges?

We now want groups whose vertices cannot be separated by deleting one vertex inside a group. Such a group is a biconnected component, or block. This lab groups edges. A bridge, an edge whose removal disconnects its endpoints, forms a one-edge block. An isolated vertex has no edge and creates no row in this lab's result.

Push a tree edge's index before entering its child. Push a back edge's index when scanning it from descendant to ancestor. The stack holds edges that have not yet been assigned to a block. Recursion still controls vertex traversal; the explicit stack stores edge indices.

When a non-root child `node` finishes, compare `back_num[node]` with `visit_num[parent[node]]`.

- If the child's value is smaller, its branch reconnects above its parent. Leave the pending edges on the stack.
- If the child's value is equal or larger, the branch cannot reconnect above its parent. Pop through the parent-to-child tree edge, inclusive. Those popped edges form one block.

Equality closes a block. A back edge to the parent connects within that block, but does not reconnect above the parent. A bridge uses the stricter condition `back_num[child] > visit_num[parent]`.

The root returns from its own postorder processing. Each of its children can close a block, since no discovery number is smaller than the root's number. Root articulation status is a different question: the root is a cut vertex only if it has at least two DFS children. The lab does not output cut vertices or bridges separately.

### What happens to the stack in the example?

The stack is listed bottom to top. A block row preserves pop order.

| Event | Pending edge indices | Emitted row |
| --- | --- | --- |
| Enter B through A–B | `0` | none |
| Enter C through B–C | `0, 1` | none |
| Finish C: `3 >= 2` | `0` | `bcc[0] = [1]` |
| Enter D, then E | `0, 2, 3` | none |
| Scan E → B | `0, 2, 3, 4` | none |
| Enter F | `0, 2, 3, 4, 5` | none |
| Scan F → B, then F → D | `0, 2, 3, 4, 5, 6, 7` | none |
| Finish F: `2 < 5` | unchanged | none |
| Finish E: `2 < 4` | unchanged | none |
| Finish D: `2 >= 2` | `0` | `bcc[1] = [7, 6, 5, 4, 3, 2]` |
| Finish B: `2 >= 1` | empty | `bcc[2] = [0]` |
| Finish root A | empty | none |

The rows represent B–C, the six edges among B/D/E/F, and A–B. The middle block shares B with both one-edge blocks. Connected components partition vertices; these blocks partition reached edges and may share a cut vertex.

### Why does the lab run DFS more than once?

Edge indexing must finish before the stack can store valid edge indices. Low-link values must also be available before block extraction begins.

Call `init_edges_list(root)` first. It resets discovery state, edge count, and the active part of `edge_index`, then indexes the root's reachable edges. Next call `find_bcc(root)` with the same root and unchanged adjacency lists.

`find_bcc()` runs `save_back_num(root)` after a discovery reset, resets `top`, resets discovery state again, and runs `_find_bcc(root)`. The second pass reproduces the first pass's discovery numbers because the root and neighbor order are unchanged. It uses the saved `back_num`; `_find_bcc()` does not recompute those values.

The comment `/* called once */` matters. `find_bcc()` does not reset `current_bcc`, `bcc`, or `bcc_size`. A fresh program starts them at zero. Repeated runs or a whole-graph extension require explicit result management. Calling `init_edges_list()` for another component also rebuilds the edge indices, so old rows cannot be interpreted using the new edge list.

## Calculating Efficiency

### How much neighbor work is repeated?

The reached A–F component has six vertices and eight undirected edges. Each pass enters six vertices and examines sixteen neighbor entries. Edge indexing, low-link computation, and extraction each traverse those lists once.

Let `R` be the number of reached vertices and `E_R` the number of edges in that component. Each traversal takes `O(R + E_R)` time. Every indexed edge is pushed once and popped once during extraction, adding `O(E_R)` work.

### What does initialization add?

The resets loop over all active vertices, including unreachable ones. `init_edges_list()` also sets every active cell of `edge_index` to -1. For `V` active vertices that is `V × V` assignments: 100 in the supplied ten-vertex graph. The complete indexing-and-extraction pipeline therefore takes `O(V² + E_R)` time when generalized beyond the fixed arrays. The square term comes from initializing the lookup table, not from scanning adjacency lists.

### How much storage do the passes use?

The explicit stack holds seven edges at its peak in this example. Recursive calls hold at most five vertices at once: A, B, D, E, F. In a generalized implementation, active recursive calls need `O(R)` storage and pending edges need `O(E_R)` storage.

The actual lab reserves fixed arrays: ten vertices, ten edge records, a ten-entry stack, `edge_index[10][10]`, and `bcc[10][45]`. The 45 columns do not enlarge `edges[10]` or `stack[10]`. The full sample graph has nine undirected edges, so even indexing every component would fit ten edge records. The code provides no bounds checks or allocation/status interface. Larger inputs need redesigned capacities and checks before these raw operations can be used.

## Glossary

- **Discovery number:** A positive first-entry number in `visit_num`; zero means unvisited.
- **DFS parent:** The vertex that first enters a child through a tree edge; roots use -1 after `init_visit()`.
- **Tree edge:** An edge used to discover an unvisited vertex.
- **Back edge:** In this simple undirected DFS, a non-parent edge from a descendant to an ancestor.
- **Low-link value:** `back_num`, the earliest discovery number reachable by tree descent followed by at most one back edge, including the current vertex itself.
- **Connected component:** A maximal group of vertices joined by undirected paths.
- **Biconnected component (block):** An edge group with no separating vertex within the group; this lab also emits bridges as one-edge blocks.
- **Cut vertex (articulation point):** A vertex whose deletion increases the number of connected components.
- **Bridge:** An edge whose deletion increases the number of connected components.
- **Postorder processing:** Work done after the current vertex's neighbor loop finishes.

## Coding Plan

1. **Prepare the graph.** Call `alphabet_nodes_init()` and `edges_init()` once in a fresh program. Choose root 0.
2. **Reset discovery state.** Set `visit_time` and active discovery entries to zero and parents to -1.
3. **Index edges.** Record tree edges before recursion and back edges toward ancestors. Store the same index for both endpoint orders.
4. **Save low-link values.** Reset discovery state and use the included `save_back_num()` with the chosen root.
5. **Extract blocks.** Clear the shared stack, reset discovery state, and traverse in the same order. Push edge indices and pop a block at each qualifying child return.
6. **Read active results.** Use rows below `current_bcc`, entries below `bcc_size[row]`, and the indexed `edges` records. Keep all input and capacity assumptions explicit.

Steps 4 and 5 are coordinated by `find_bcc()`. They are recursive DFS passes with an edge stack, not iterative vertex DFS.

## C Code

### Which earlier code does the lab include?

The graph globals and `save_back_num()` come from Chapter 3. The integer stack and unchecked `push()`/`pop()` come from Chapter 4. Compile from the repository root with `-I.` so the included paths resolve.

```c
#include "module_03_graph/student/lab.c"
#include "module_04_stack/student/lab.c"
```

### How does one edge receive one index?

The two endpoint orders share one index. The helper does not check capacity or reject duplicate insertion. Its callers enforce the one-record traversal rule.

```c
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
```

The comments inside `GraphEdge` describe the orientations produced by this traversal. A discovery-number inequality alone is not a general tree-edge test.

### How are discovery state and edges prepared?

The parent test precedes the ancestor test. It prevents the reverse entry of a tree edge from becoming a back edge. The source retains the comment spelling `ancester`.

```c
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
```

### How are pending edges assigned to blocks?

The root check uses short-circuit `||`: a root returns before indexing `visit_num[parent[node]]` with -1. For a qualifying child, `do ... while` pops at least once and includes `parent_edge` in the output. Valid indexing and traversal order ensure that edge is still on the stack.

```c
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
```

### How do we run the supplied example?

The lab has no `main()`. Use the [lecture driver](../code/lecture/lab_demo.c), which includes the unchanged lab and prints discovery, low-link, edge, and block tables:

```sh
cd module_06_graph_dfs/code
make lecture
```

In a fresh program the essential sequence is:

```c
alphabet_nodes_init();
edges_init();
init_edges_list(0);
find_bcc(0);
```

The expected active sizes are `edges_size == 8`, `current_bcc == 3`, and `bcc_size` beginning with `1, 6, 1`. The final stack is empty with `top == -1`. The exact rows are `[1]`, `[7, 6, 5, 4, 3, 2]`, and `[0]`.

Self-loops are ignored, parallel edges are unsupported, and invalid roots or exceeded capacities are not checked. The lab mutates globals directly and does not promise unchanged output after failure. A whole-graph block extractor, repeatable wrapper, and checked API are subsequent extensions.
