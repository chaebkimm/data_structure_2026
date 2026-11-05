# Chapter 3. Connecting data in a graph

We will connect items with edges that work in both directions. Then we will follow those connections to find groups and record how a branch can reach an earlier vertex.

## Thinking logically

### What does connected data look like?

We use nodes to represent items and edges to connect them. We call this structure a graph; a node in a graph is also called a vertex. In an undirected graph, each edge works in either direction.

Vertices joined directly by an edge are neighbors. Following successive edges gives a path. In our graph without self-loops or repeated edges, a cycle goes through at least three vertices and returns to its start without repeating another vertex. Unlike the tree in Chapter 2, a graph can contain cycles and separate groups.

### How do array positions become a graph?

We use indices of other nodes in the array as neighbor links. A tree node had two child links. Here, each node stores a list of neighbor indices, called an adjacency list.

The node array has room for ten nodes, and `nodes_size` records how many are in use. Each node also has room for ten neighbor indices. Its `adj_size` records how many of those entries are in use. An empty list has size 0; a stored neighbor index of 0 refers to the first node.

### How do we connect two vertices?

Add each vertex's index to the other's neighbor list. For endpoints `u` and `v`, append `v` to `u`'s list and `u` to `v`'s list, increasing each list's size by one. Both entries are needed because the edge works both ways.

Initialize the neighbor lists as empty before adding edges. We use a graph with no edge from a vertex to itself and no repeated edge. Each endpoint must be an active node, and both neighbor lists must have room.

### How do we visit connected vertices?

Starting at one vertex, we follow its neighbors and repeat this for each newly discovered vertex. A cycle could otherwise make us revisit the same vertices indefinitely, so we give each vertex a positive visit number before checking its neighbors. A visit number of 0 means it has not been discovered.

For each neighbor, check its visit number. If it is 0, explore that neighbor recursively. When the call returns, continue the current vertex's list. Skip neighbors that already have a number.

Finishing a new neighbor's search before continuing the current vertex's list is depth-first search (DFS). It reaches every vertex connected to the starting vertex. Vertices with no path from that start remain unvisited. An index tells us where a vertex is stored; a visit number tells us when it was discovered.

### How do we find every connected group?

A connected component is a whole group joined by paths, with no path to a vertex outside that group.

Scan the active nodes. Whenever an unvisited vertex is found, increase the group number and start a search from it. Give every vertex reached by that search the same group number. Continue the scan until all active nodes have a label. A vertex with no neighbors forms a component by itself.

### Which edges belong to the search tree?

An edge that first discovers a new vertex is a tree edge. The current vertex becomes the new vertex's parent in the DFS tree. Earlier vertices on its parent chain are ancestors; vertices below it are descendants.

In this undirected DFS, an edge to an already discovered ancestor other than the parent is a back edge. When the ancestor later examines the same edge, it sees an already discovered descendant. These roles belong to the search; a different start or neighbor order can change them.

### How early can a branch reach back?

A back number is the smallest discovery number reachable by going down zero or more tree edges and then taking at most one back edge to an ancestor. Keeping the current vertex's own number is allowed.

Start `back[i]` at `visit_num[i]`. Then handle each neighbor:

| Neighbor | How to update the back number |
|---|---|
| New child | Recurse first; after it returns, use its back number if smaller. |
| Parent | Skip it: this is the edge used to arrive, seen in reverse. |
| Already discovered ancestor, other than the parent | Use its visit number if smaller. |
| Already discovered descendant | Its larger visit number cannot lower the current value. |

The completed value records how early this branch can reach without retracing its arrival edge. It is a discovery number, not an array index. A vertex that this search never reaches keeps its initial visit and back numbers of 0.

## Calculating efficiency

### Memory efficiency for storing

A node stores one `char`, ten neighbor indices, and one neighbor count. The node array reserves all ten slots even when only some are in use. Each undirected edge uses two neighbor entries; unused positions remain reserved.

### Memory efficiency for iterating over items

Visit numbers, group labels, back numbers, and parents use separate arrays with one entry per reserved node. Each recursive call also keeps its own temporary state while a child's call runs. The number of simultaneous calls equals the number of vertices on the current DFS path, which can include every vertex in a component.

### Efficiency of creating or adding one item

Initializing one node's character and neighbor count takes constant time. Adding one edge also takes constant time when both neighbor lists have room: append two indices and increase two counts. This assumes valid endpoints and no repeated edges; the append operation does not search for duplicates.

### Efficiency of iterating over items

Each search does work proportional to the number of reached vertices plus their stored neighbor entries. Every reached vertex is discovered once, and each undirected edge is examined from both ends. Finding all components also scans every active node, including isolated vertices.

## Glossary

### Vertex (node)

One item in a graph. Our node stores a character, neighbor indices, and their used count.

### Edge

A direct connection between two vertices.

### Undirected graph

A graph whose edges can be followed in either direction.

### Neighbor

A vertex directly connected to another by an edge.

### Adjacency list

The list of neighbors stored for one vertex; our lists hold array indices.

### Path

A sequence of vertices connected by successive edges.

### Cycle

A route through at least three vertices that returns to its start without repeating another vertex, in our graph without self-loops or repeated edges.

### Connected component

A whole group joined by paths, with no path to a vertex outside the group.

### Isolated vertex

A vertex with no neighbors; it forms a component by itself.

### Depth-first search (DFS)

A search that finishes exploring a newly discovered neighbor before continuing the current vertex's list.

### Visit number

A positive discovery number. Zero marks a vertex that has not been discovered in the current search.

### Tree edge

An edge that first discovers a new vertex, making it a child in the DFS tree.

### Back edge

A non-tree edge connecting a vertex to an ancestor in this undirected DFS.

### Back number

The smallest visit number reachable by descending tree edges and then taking at most one back edge to an ancestor, including the option of staying at the current vertex.

## Invariant

### What are the invariants (the golden rules) in this data structure?

- `nodes_size` and each `adj_size` stay between 0 and 10. Only positions before the corresponding size are in use.
- Every stored neighbor index is between 0 and `nodes_size - 1`.
- Each undirected edge appears once in each endpoint's list. There are no self-loops or repeated edges.
- During a search, each vertex receives a visit number before its neighbors are explored. Recurse only into an unvisited neighbor.
- In the back-number search, the root has parent `-1`, and a new child's parent is set before its recursive call.

### What is the benefit of the invariants?

Valid sizes and indices let us read exactly the stored neighbors. Recording visits before recursion lets us explore each reachable vertex once, even around cycles. Parent links let us distinguish the reverse of an arrival edge from another route to an ancestor.

### What happens if an invariant is broken?

An invalid size or index can access unused slots or memory outside an array. A missing reverse entry makes an edge work in only one direction. Missing visit records can cause endless recursion, and an incorrect parent can give the wrong back number.

### How do we keep the invariants intact?

Initialize neighbor counts before adding edges, and append both endpoints only when the indices and available space are valid. Start each independent search with clear visit records. Set a child's parent before exploring it, and wait for its call to return before using its completed back number.

## Coding plan

### Designing a node

Keep `data`, `adj_list`, and `adj_size` in `struct GraphNode`; store ten such nodes in a shared array. Use `nodes_size` for the number of active nodes and `adj_size` for one node's number of neighbors.

### Preparing the graph

1. Set the number of active nodes, within the array's capacity.
2. Initialize their data and set every neighbor count to 0.
3. For each edge, append each endpoint to the other's list.

### Recording discovery order

In `save_visit_num`, give the current vertex the next positive number. Read each neighbor index and recurse only when its visit number is 0.

### Labeling connected components

In `mark_group`, record both a visit number and `current_group`. In `mark_all_groups`, scan all active nodes. Whenever an unvisited node is found, increase the group number and start `mark_group`.

### Recording back numbers

In `save_back`, assign the current vertex's visit number and use it as the initial back number. Set a new child's parent before recursion, then compare its completed back number after it returns. For an already visited neighbor other than the parent, compare its visit number instead.

### Preparing independent searches

Before each independent search, clear `visit_num` and reset `visit_time` to 0. Before labeling components, also clear `group` and reset `current_group` to 0. Before computing back numbers, clear `back` and set every `parent` entry to `-1`.

After this preparation, start a single-component search at a valid vertex index, or call `mark_all_groups()` to cover the whole graph. `save_back` assigns its own visit numbers; it does not need a preceding discovery pass. Old visit numbers would make any new pass skip vertices.

## New C syntax explained

### An array inside a `struct`

`int adj_list[10];` reserves ten neighbor indices inside each node. `nodes[i].adj_list[j]` selects node `i`, then position `j` in that node's neighbor list. The stored value is another node's index.

### Initializing arrays with braces

`int visit_num[10] = {0};` sets every element to 0: the first is explicit, and the remaining elements are zero-initialized. This happens at initialization, not before every search.

### Prefix and postfix increment

`++visit_time` increases the counter before supplying its value, so the first discovery receives 1. `nodes[u].adj_size++` supplies the old size as the next free position, then increases the size.

### `else if` and `&&`

An `else if` is checked only when the preceding `if` condition was false. In `adj != parent[i] && back[i] > visit_num[adj]`, both conditions must hold: the neighbor is not the parent, and its visit number is smaller than the current back number.

## C code

The functions below initialize nodes, add individual edges, and search the resulting graph. The search names follow [ppt_day_c_code.md](ppt_day_c_code.md); the separate [lab.c](lab.c) calls `back` and `save_back` by the names `back_num` and `save_back_num`.

### Node storage

```c
struct GraphNode {
        char data; // A stored letter, not a visit number.
        int adj_list[10]; // Neighbor indices, not neighbor characters.
        int adj_size; // Number of neighbor entries in use.
};
struct GraphNode nodes[10];
int nodes_size = 0; // Active nodes, including any isolated vertices.
```

### Initializing nodes

```c
void graph_init(int size) {
        // Requires a size from 0 through 10. Initialize before adding edges.
        nodes_size = size;
        for (int i = 0; i < nodes_size; i++) {
                nodes[i].data = 0; // No character label assigned yet.
                // An empty list has size zero; zero is still a valid node index.
                nodes[i].adj_size = 0;
        }
}
```

### Connecting two vertices

```c
void add_edge(int u, int v) {
        // Requires distinct active endpoints, a new edge, and room in both lists.
        // Save each next free position before increasing its used size.
        int u_adj_end = nodes[u].adj_size++;
        int v_adj_end = nodes[v].adj_size++;
        // Store both directions of this one undirected edge.
        nodes[u].adj_list[u_adj_end] = v;
        nodes[v].adj_list[v_adj_end] = u;
}
```

### Recording discovery order

```c
int visit_num[10] = {0};
int visit_time = 0;

void save_visit_num(int i) {
        // Requires a valid, unvisited starting vertex. Mark before following edges.
        visit_num[i] = ++visit_time;
        for (int j = 0; j < nodes[i].adj_size; j++) {
                int adj = nodes[i].adj_list[j]; // A neighbor's index.
                if (visit_num[adj] == 0) {
                        // Finish this neighbor's whole search before continuing j.
                        save_visit_num(adj);
                }
        }
}
```

### Labeling one connected component

```c
int group[10] = {0};
int current_group = 0;

void mark_group(int i) {
        visit_num[i] = ++visit_time;
        group[i] = current_group; // Every vertex in this search gets the same label.
        for (int j = 0; j < nodes[i].adj_size; j++) {
                int adj = nodes[i].adj_list[j];
                if (visit_num[adj] == 0) {
                        mark_group(adj);
                }
        }
}
```

### Finding all connected components

```c
void mark_all_groups() {
        // Requires clear visit records and current_group set to zero.
        for (int i = 0; i < nodes_size; i++) {
                if (visit_num[i] == 0) {
                        // An isolated vertex also starts a new group.
                        current_group++;
                        mark_group(i);
                }
        }
}
```

### Recording back numbers

```c
int back[10] = {0};
int parent[10]; // Set every entry to -1 before starting this search.

void save_back(int i) {
        // This pass assigns its own discovery numbers.
        visit_num[i] = ++visit_time;
        back[i] = visit_num[i];
        for (int j = 0; j < nodes[i].adj_size; j++) {
                int adj = nodes[i].adj_list[j];
                if (visit_num[adj] == 0) {
                        parent[adj] = i; // Record the arrival edge before recursion.
                        save_back(adj);
                        // A child's back number is complete only after it returns.
                        if (back[i] > back[adj]) {
                                back[i] = back[adj];
                        }
                }
                else if (adj != parent[i]
                        && back[i] > visit_num[adj]) {
                        // Skip the parent; compare a visited neighbor's visit number.
                        // A descendant's larger visit number cannot lower back[i].
                        back[i] = visit_num[adj];
                }
        }
}
```
