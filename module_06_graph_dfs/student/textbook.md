# Chapter 6. Graph DFS, Edge Lists, and Biconnected Components

Chapter 3 stores neighbors in adjacency lists and finds connected vertices. This chapter introduces edge lists and adjacency matrices, records connections, and groups the edges according to how the graph holds together. We reuse Chapter 3's adjacency lists and discovery numbers, Chapter 4's stack, and Chapter 5's preorder and postorder processing.

## Thinking Logically

### How do we store and explore the graph?

A connection has two endpoints. In Chapter 3, we stored each vertex's neighbors in an adjacency list. Here we introduce two more representations: an edge list collects the connections themselves, and an adjacency matrix lets us check a specified pair of vertices. Compare the familiar adjacency list with these two new ways to organize the same graph.

| Representation | What it remembers | What it makes easy |
| --- | --- | --- |
| adjacency list — review from Chapter 3 | Each vertex's neighbors | Following connections from the current vertex |
| edge list — new in this chapter | One pair of endpoints per undirected edge | Examining the edges as individual records |
| adjacency matrix — new in this chapter | Whether each pair of vertices is directly joined | Checking one specified pair |

Following every connection without remembering earlier visits would return to vertices already explored. Give each vertex a positive visit number when first entering it. A vertex that already has a number needs no new exploration.

The slide diagram shows the completed DFS. The numbers 1–7 written at its vertices are their visit numbers. We use those completed numbers to identify vertices while explaining a replay. For example, vertex 3 means the vertex that received visit number 3. During exploration, an unreached vertex has no visit number yet.

Using this completed numbering, the ten undirected edges are:

```text
1–2, 1–3, 2–3, 2–7, 3–4, 3–6, 3–7, 4–5, 4–6, 5–6
```

Replay the same traversal from the vertex that receives visit number 1. The table describes the fixed neighbor order using the completed diagram's numbers in ascending order. Assign each visit number only when first entering its vertex.

| Vertex identified by completed visit number | Neighbor order for this replay |
| --- | --- |
| 1 | 2, 3 |
| 2 | 1, 3, 7 |
| 3 | 1, 2, 4, 6, 7 |
| 4 | 3, 5, 6 |
| 5 | 4, 6 |
| 6 | 3, 4, 5 |
| 7 | 2, 3 |

All seven vertices are reached. The graph has one connected component. The partially numbered slide shows this process in progress: after assigning visit numbers 1 and 2, the remaining circles are still blank. The next first entry assigns visit number 3.

### How do we distinguish the neighbors?

The current vertex may meet a new vertex or a vertex already reached. Treating every neighbor as a new child would repeat exploration. Use the discovery number and DFS parent to decide what work remains.

When a neighbor has not been reached, the current vertex becomes its parent. Continue exploration through that child. The edge that first discovers the child is a **tree edge**. When the child sees its parent, skip the reverse entry of that same connection.

For another reached neighbor, compare discovery numbers. A smaller number identifies an ancestor. The connection from the descendant toward that ancestor is a **back edge**. A larger number identifies a descendant that has already processed the connection, so skip the reverse entry.

When the current vertex receives visit number 3, ancestors 1 and 2 have already been reached. The vertices later numbered 4, 6, and 7 are still unreached. Exploring the child that receives number 4 later reaches the vertex that receives number 6. That changes the latter neighbor's case before vertex 3 examines its entry.

| Neighbor of vertex at visit 3 | Case when its entry is examined | Action |
| --- | --- | --- |
| 1 | Earlier ancestor, not the parent | Process back edge 3 → 1 without exploring 1 again |
| 2 | DFS parent | Skip the reverse tree edge |
| 4 | Unreached child, identified by its eventual visit number | Set its parent to vertex 3 and explore it |
| 6 | Already reached descendant | Skip the connection already processed as 6 → 3 |
| 7 | Unreached child, identified by its eventual visit number | Set its parent to vertex 3 and explore it |

The graph is simple and undirected: each edge joins two distinct vertices, and each pair has at most one edge. These ancestor/descendant relationships let us process each undirected connection from one endpoint only.

#### When do we perform each task?

A vertex's exploration pauses while a child is explored. We need work before the pause and work after the child's branch finishes. Chapter 5's visit positions describe these times.

| Time | Work |
| --- | --- |
| preorder: first entering a vertex | Assign its discovery number; when calculating low-links, begin its summary with that number |
| Before continuing through a tree-edge child | Record the child's parent; record or stack the edge when the current task needs it |
| When examining a back edge toward an ancestor | Process the edge without another recursive exploration |
| After a child finishes | Receive its completed low-link summary; when grouping edges, decide whether that child's tree edge closes a block |
| postorder: after all neighbors finish | Finish the current branch and return to its parent |

The current vertex receives visit number 3 on entry. It handles 3 → 1, skips its parent 2, and explores the child that receives visit number 4. When that child returns, vertex 3 checks the finished branch before continuing to its next neighbor. It then skips the already reached 6 and explores the child that receives visit number 7. Only after all five neighbor entries finish does vertex 3 return to its own parent. A graph has no fixed left/right child positions, so there is no single inorder position as in a binary tree.

### How do we record each edge and find it again?

Each undirected edge appears twice in the neighbor lists. In the completed numbering, vertex 3 lists 6 and vertex 6 lists 3. Recording both entries would duplicate the same connection. An edge list needs one record per connection.

Record a tree edge before entering its child. Record a back edge when examining it from descendant to ancestor. Skip the parent and already processed descendant entries. Following the specified DFS gives these ten records.

| Undirected edge | Recording direction | Kind |
| --- | --- | --- |
| 1–2 | 1 → 2 | tree |
| 2–3 | 2 → 3 | tree |
| 1–3 | 3 → 1 | back |
| 3–4 | 3 → 4 | tree |
| 4–5 | 4 → 5 | tree |
| 5–6 | 5 → 6 | tree |
| 3–6 | 6 → 3 | back |
| 4–6 | 6 → 4 | back |
| 3–7 | 3 → 7 | tree |
| 2–7 | 7 → 2 | back |

The arrows show the recording direction. The connections remain undirected.

A later exploration needs the record describing a connection. Searching every record would repeat work. Keep a table that associates each endpoint pair with its edge record. Vertex pair 3–6 and vertex pair 6–3 both find the same 3–6 record in the completed numbering. The table is symmetric.

An adjacency matrix answers whether two vertices are directly joined by an edge. This edge-record lookup answers which record describes the connection. Vertex pair 1–4 has no edge and therefore no record. If only part of a larger graph were explored, an unreached edge would also have no record in that exploration.

### How far back can a finished branch reconnect?

A descendant may connect to an earlier ancestor. For each vertex, remember the earliest discovery number reachable by going down tree edges and then using at most one back edge. Include the vertex's own number as a candidate. This summary is its **low-link value**.

Start with the current vertex's discovery number. After a child finishes, keep the smaller of the current summary and the child's summary. A back edge toward an ancestor also supplies that ancestor's discovery number.

The specified exploration gives these values.

| Vertex's visit number | Parent's visit number | Low-link value |
| --- | --- | --- |
| 1 | none | 1 |
| 2 | 1 | 1 |
| 3 | 2 | 1 |
| 4 | 3 | 3 |
| 5 | 4 | 3 |
| 6 | 5 | 3 |
| 7 | 3 | 2 |

At visit 6, back edges reach the ancestors numbered 3 and 4. The smaller number is 3, so the low-link value becomes 3. That value returns through vertices 5 and 4.

At visit 7, a back edge reaches ancestor 2, giving low-link value 2. Vertex 3 itself connects back to ancestor 1. That earliest value returns through vertex 2.

### When can we close a group of edges?

Being connected does not guarantee that a graph stays connected after one vertex is removed. Removing the vertex with visit number 3 separates vertices 1/2/7 from vertices 4/5/6. We want the largest groups whose remaining vertices stay connected after any one vertex inside the group is removed.

Within vertices 3/4/5/6, any two vertices have two paths that share only their endpoints. For vertices 3 and 6, use 3–6 and 3–4–6. The vertices between the endpoints do not overlap. Such paths are **internally vertex-disjoint**. For a group with at least three vertices, this property for every pair expresses resistance to losing one vertex. A maximal group with that property is a **biconnected component (BCC)**, or **block**.

The graph has two blocks. One contains the five edges among vertices 3/4/5/6. The other contains the five edges among vertices 1/2/3/7. They share the vertex with visit number 3, but share no edge. That vertex is a cut vertex. A single edge and its endpoints can also form a block in other graphs. An isolated vertex has no edge to group.

Place a tree edge on a stack before continuing through its child. Place a back edge on the stack when examining it from descendant to ancestor. The stack holds edges awaiting assignment to a block. Recursive exploration remembers unfinished vertex work; this edge stack remembers unfinished grouping work.

When a child's branch finishes, compare its low-link value with its parent's discovery number.

- A smaller value means the branch reconnects above the parent. Leave its edges pending.
- An equal or larger value means the branch cannot reconnect above the parent. Remove edges from the top through the parent-to-child tree edge, including that edge. These edges form one block.

When this boundary closes, blocks separated farther down have already been removed. The remaining portion at the top of the stack belongs to the incoming edge's BCC. The branch cannot reconnect to an ancestor visited before the parent, so this BCC cannot extend below that boundary. Removing from the top through the parent-to-child edge therefore yields exactly one complete block.

Equality closes a block. Vertex 4's branch reconnects to parent 3 through 6 → 3, but cannot bypass that parent. Its low-link value 3 equals the parent's visit number 3. Remove the pending edges through 3–4.

The root has no parent, so there is no incoming edge to close at the root itself. Each root child can close a block because no discovery number is earlier than the root's number. The root, visited first, has one DFS child: vertex 2. That child closes the other block. The root is not a cut vertex.

### What happens to the stack in the example?

Show each undirected edge by its vertex pair. List the stack from bottom to top and each completed block in removal order.

| Event | Pending edges | Completed block |
| --- | --- | --- |
| Enter visits 2, then 3 | 1–2, 2–3 | none |
| Examine 3 → 1 | 1–2, 2–3, 1–3 | none |
| Enter visits 4, 5, then 6 | 1–2, 2–3, 1–3, 3–4, 4–5, 5–6 | none |
| Examine 6 → 3, then 6 → 4 | 1–2, 2–3, 1–3, 3–4, 4–5, 5–6, 3–6, 4–6 | none |
| Return from visit 6 to visit 5: low-link 3 is smaller than parent visit 5 | 1–2, 2–3, 1–3, 3–4, 4–5, 5–6, 3–6, 4–6 | none |
| Return from visit 5 to visit 4: low-link 3 is smaller than parent visit 4 | 1–2, 2–3, 1–3, 3–4, 4–5, 5–6, 3–6, 4–6 | none |
| Return from visit 4 to visit 3: low-link 3 equals parent visit 3 | 1–2, 2–3, 1–3 | 4–6, 3–6, 5–6, 4–5, 3–4 |
| At visit 3, skip already reached 6 | 1–2, 2–3, 1–3 | none |
| Enter visit 7; examine 7 → 2 | 1–2, 2–3, 1–3, 3–7, 2–7 | none |
| Return from visit 7 to visit 3: low-link 2 is smaller than parent visit 3 | 1–2, 2–3, 1–3, 3–7, 2–7 | none |
| Return from visit 3 to visit 2: low-link 1 is smaller than parent visit 2 | 1–2, 2–3, 1–3, 3–7, 2–7 | none |
| Return from visit 2 to visit 1: low-link 1 equals parent visit 1 | empty | 2–7, 3–7, 1–3, 2–3, 1–2 |
| At visit 1, skip already reached 3; finish the root | empty | none |

Each completed block has five edges. The ten edges appear exactly once across the two blocks. Their common vertex at visit 3 joins the groups. Connected components partition vertices; blocks partition edges and may share a cut vertex.

#### What is the edge-stack invariant?

An empty final stack alone does not show that grouping was correct. An edge could have been lost or assigned twice. We need a rule that stays true as the stack changes. Such a rule is an **invariant**.

After each push or completed pop-and-store step, every edge handled so far appears exactly once: either pending on the stack or assigned to output. The two collections do not overlap. During block removal, assigned edges include the row still being filled. An edge counts as handled when its tree-edge or ancestor-back-edge case is processed. Merely seeing its reverse neighbor entry does not handle a new edge.

The counts therefore satisfy **handled edges = pending edges + assigned edges**. Counts alone are insufficient: the edge identities must also match, with no missing or repeated edge. The stack keeps the handling order from bottom to top, with already assigned edges removed.

**Initialization.** Before grouping starts, no edge has been handled. Both collections are empty, so the rule holds.

**Maintenance.** A new tree edge enters the stack before its child is explored. A new back edge enters when read toward an ancestor. Each adds one handled edge and one pending edge. Parent and processed-descendant entries add nothing. A pop-and-store step moves one edge from pending to assigned. The total and the identities remain unchanged.

The child's incoming tree edge stays pending until its parent closes that boundary. After the child returns, the remaining edges from that branch form a suffix starting at the boundary edge. Blocks inside the branch may already have been removed. The suffix therefore contains the branch's still-unassigned edges, not every edge explored below the child. If the child's low-link is smaller than the parent's visit number, keep the suffix pending. Otherwise, remove the suffix through its boundary, including that edge, to form one block. Including the boundary prevents it from leaking into a later block.

**Termination.** After the starting component finishes, every reached edge has been handled. The stack is empty and every reached edge has been assigned exactly once. The low-link boundary rule establishes which edges form each block; the accounting invariant establishes that none is lost or duplicated. The recursive call stack separately remembers unfinished vertex scans.

In the example, eight handled edges initially give eight pending and zero assigned. After the first pop, eight equals seven pending plus one assigned to the forming row. After the first block closes, eight equals three pending plus five assigned. At the end, ten equals zero pending plus ten assigned. These statements assume the input and all storage capacities satisfy the lab's preconditions.

#### What remains on the stack at postorder?

Accounting shows that no handled edge is lost. We also need to explain why the remaining edges can wait together. Check the current vertex at postorder, after all its neighbors and child-boundary decisions finish, just before its call returns. Its parent has not yet made the boundary decision for this call.

For a non-root vertex, include its incoming parent edge with the edges handled in its DFS branch. **Every one of these edges has been processed: it is either assigned to a completed block or still pending on the stack. Among these branch edges, only edges in the same eventual block as the incoming parent edge remain pending.** They occupy the suffix from that parent edge through the top of the stack.

Why? A child's branch that cannot reconnect above the current vertex has already been removed as a block. A child's branch that can reconnect above it stays pending. That reconnection creates a cycle through the current vertex's incoming edge, so the remaining child edges belong with that edge. A back edge from the current vertex to an ancestor also creates such a cycle. If none of these edges remains, the incoming edge waits by itself.

This claim concerns the branch's suffix. Older edges below the incoming edge may belong to other blocks. The suffix also need not contain the whole eventual block: some of its edges may be older entries below the boundary or may be handled later from an ancestor's unfinished scan.

At visit 4's postorder, its branch's pending suffix is 3–4, 4–5, 5–6, 3–6, 4–6. All five edges belong to the block containing its parent edge 3–4. Older entries 1–2, 2–3, 1–3 remain below that suffix and belong to the other block. The call then returns to visit 3, which compares the finished child's low-link and removes the suffix through 3–4.

At visit 3's postorder, the right-hand block has already been assigned. Its remaining suffix begins at parent edge 2–3 and contains 2–3, 1–3, 3–7, 2–7. These four edges share the eventual block with the older edge 1–2 below the suffix. The parent at visit 2 keeps them pending because the branch reconnects above it.

The root has no incoming parent edge. By the root's postorder, each child has already triggered its boundary removal, so the edge stack is empty. An isolated root also finishes with an empty stack.

### What must be ready before grouping edges?

The stack must distinguish every reached edge. The block-boundary decision also needs a completed low-link summary for every reached vertex.

Our method first records the edges, then calculates the low-link summaries, then groups the edges using those saved summaries. Each exploration starts at the same vertex, receives visit number 1 there, and follows the same fixed neighbor order described by the completed diagram. This keeps discovery numbers and parent relationships consistent, so a saved summary still describes the branch being grouped.

The three passes perform different work at the same times: discovery on entry, edge work before child exploration or at an ancestor connection, and branch decisions after a child returns. Grouping checks each finished child before examining the parent's next neighbor.

## Calculating Efficiency

### How much neighbor work is repeated?

The example has seven vertices and ten undirected edges. Each pass enters seven vertices and examines twenty neighbor entries. The entries fall into six child cases, six parent cases, four ancestor cases, and four descendant cases.

Edge recording, low-link computation, and grouping each explore those lists once. Together, the three passes make twenty-one vertex entries and sixty neighbor inspections. Grouping also places ten edges on the stack and removes those ten edges.

Let R be the number of reached vertices and E_R the number of edges in that component. Each exploration takes O(R + E_R) time. Each recorded edge enters and leaves the stack once, adding O(E_R) work.

### What does preparing the lookup add?

Discovery-state preparation covers all vertices. Preparing a pair lookup considers every ordered vertex pair. For seven vertices, that is seven rows and seven columns: 49 cells.

For V vertices, the table has V × V cells. The complete method therefore takes O(V² + E_R) time when generalized beyond the fixed example. The square term comes from preparing the pair lookup, not from examining neighbor lists.

### How much storage do the explorations use?

The stack holds eight pending edges at its peak. At most six recursive vertex explorations are active together, for visits 1, 2, 3, 4, 5, 6. The completed blocks hold five edges each.

In general, active recursive work needs O(R) storage and pending edges need O(E_R) storage. The pair lookup needs O(V²) cells. Edge records and completed blocks together need O(E_R) entries because each reached edge belongs to one block. Reserving space for every possible pair differs from counting only the records and stack entries actually used.

## Glossary

- **Visit number (discovery number):** A positive number recording when a vertex is first reached. The slide identifies vertices using these numbers from the completed DFS.
- **DFS parent:** The vertex that first discovers a child through a tree edge; a root has no parent.
- **Tree edge:** An edge used to discover an unreached vertex.
- **Back edge:** In this simple undirected DFS, a non-parent edge from a descendant to an ancestor.
- **preorder processing:** Work on first entering a vertex.
- **postorder processing:** Work after the current vertex's neighbor exploration finishes.
- **Low-link value:** The earliest discovery number reachable by tree descent followed by at most one back edge, including the current vertex itself.
- **Connected component:** A maximal group of vertices joined by undirected paths.
- **Edge list:** A collection of endpoint records, with one record per undirected edge.
- **Adjacency list:** Each vertex's collection of neighbors.
- **Adjacency matrix:** A table recording whether each vertex pair is directly joined by an edge.
- **Edge-record lookup:** A symmetric table associating an endpoint pair with its edge record.
- **Internally vertex-disjoint paths:** Paths whose only shared vertices are their two endpoints.
- **Biconnected component (block):** A maximal group with no separating vertex within the group; a single edge can also form a block.
- **Cut vertex (articulation point):** A vertex whose deletion increases the number of connected components.
- **Pending-edge stack:** Edges encountered but not yet assigned to a block.
- **Invariant:** A rule that remains true at specified steps. Here, each handled edge is pending or assigned exactly once after a push or a pop-and-store step.

## Coding Plan

1. **Prepare representations.** Keep the vertices and their neighbor lists. Prepare endpoint records and a symmetric table for finding those records.
2. **Classify neighbors and choose timing.** Discover a vertex on entry. Continue through unreached children and distinguish parent, ancestor, and descendant relationships. Complete branch work after all neighbors finish.
3. **Record reached edges.** Record tree edges before entering children and back edges when examining ancestors. Associate both endpoint orders with one record.
4. **Save low-link summaries.** Explore from the chosen starting vertex and retain each branch's earliest reconnection number.
5. **Group pending edges.** Start with an empty edge stack and fresh discovery state. Explore in the same order, keeping the saved summaries. After each child returns, remove a block through that child's tree edge if its branch cannot reconnect above the current parent.
6. **Check the invariant and read the result.** Account for each handled edge after a push or a pop-and-store step. Identify every completed block by its endpoint pairs and check that each reached edge appears once.

#### What should we be able to explain for the midterm?

1. Explain how the three graph representations store, add, and delete vertices and edges. Use the completed diagram to identify the endpoints of a hypothetical edge 1–7. Adding or deleting it changes both endpoint neighbor lists and both symmetric matrix cells. Deleting the vertex at visit 7 removes its incident edges 2–7 and 3–7 and all references to it. A new vertex needs a neighbor collection and a matrix row and column. Keep lookups consistent if records move. A later DFS assigns visit numbers afresh after graph changes.
2. Define a block using paths with no shared internal vertices. Explain the two five-edge blocks, their shared vertex at visit 3, the low-link boundary comparison, and the inclusive stack removal.
3. Review Chapter 5's tree reconstruction from preorder and inorder with distinct labels. Take the first preorder label as the root, split inorder at that label, and use the two subtree sizes to split the remaining preorder sequence. Repeat for each subtree.

#### Complete and submit the mini-quiz

Identify the five neighbors' cases at visit 3, explain the low-link value at visit 6, and mark the two block boundaries. Complete the Chapter 5 preorder/inorder reconstruction review, then submit your mini-quiz answers.

## C Code

### Which earlier code does the lab include?

The graph globals and `save_back_num()` come from Chapter 3. The integer stack and unchecked `push()`/`pop()` come from Chapter 4. Compile from the repository root with `-I.` so the included paths resolve.

```c
#include "module_03_graph/student/lab.c"
#include "module_04_stack/student/lab.c"
```

The [lab slides](ppt_lab_material.md) first follow one call in preorder → neighbor loop → postorder order. Before studying edge records, read `init_visit()` as a separate traversal-preparation step. It resets `visit_time`, `visit_num`, and `parent`. `init_edges_list()` reuses that preparation, then clears the edge count, fills the active lookup with -1, and starts recording.

### How does the source represent the example?

The numbers 1–7 in the conceptual diagram are completed DFS visit numbers. The supplied
initializers in `lab.c` build a separate A–J graph. The source selects
those vertices with integer indices 0–9 in `nodes`.
`alphabet_nodes_init()` initializes
the labels and empty neighbor lists; `edges_init()` appends the supplied
nine undirected edges to both endpoint lists. Read neighbors in their
stored insertion order. Call those initializers in that order once.

The supplied alphabet graph has edges A–B, B–C, B–D, B–E, B–F, D–E,
D–F, E–F, and G–H. I and J are isolated. Starting at A reaches A–F;
G/H/I/J remain unvisited. The graph has four connected components.
The A–F neighbor lists are A: B; B: A, C, D, E, F; C: B;
D: B, E, F; E: B, D, F; F: B, D, E.

The included graph source supplies these names for discovery and low-link values:

| Concept | Source storage | Meaning |
| --- | --- | --- |
| Vertex and neighbors | `nodes[i].data`, `nodes[i].adj_list`, `nodes[i].adj_size` | Label, neighbor indices, and active neighbor count |
| Discovery number | `visit_num[i]`, with counter `visit_time` | Zero means unvisited; positive numbers record first entry |
| DFS parent | `parent[i]` | A vertex index; `init_visit()` gives roots -1 |
| Low-link value | `back_num[i]` | Saved earliest reconnection number |

The lab assumes a valid root, valid symmetric adjacency lists, and a
simple undirected input. Its discovery-number comparisons do not classify
directed edges. Parallel edges need a different parent-edge rule, because
skipping by parent vertex could discard another edge between the same
vertices. The source's self-loop branch does nothing.

### How does one edge receive one index?

The two endpoint orders share one index. The helper does not check capacity or reject duplicate insertion. Its callers enforce the one-record traversal rule.

```c
struct GraphEdge {
    int from, to;
    /* tree edge: visit_num[from] < visit_num[to] */
    /* back edge: visit_num[from] > visit_num[to] */
};

struct GraphEdge edges[45];
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

The source stores edge indices in the integer stack. For the root-A run,
these indices describe the separate alphabet example:

| Edge index | Undirected edge | Stored `from → to` |
| ---: | --- | --- |
| 0 | A–B | A → B |
| 1 | B–C | B → C |
| 2 | B–D | B → D |
| 3 | D–E | D → E |
| 4 | B–E | E → B |
| 5 | E–F | E → F |
| 6 | B–F | F → B |
| 7 | D–F | F → D |

The lookup example B–E becomes
`edge_index[1][4] == edge_index[4][1] == 4`. The wrapper initializes the
active lookup cells to -1 before indexing. In the root-A run, G–H is
unreached, so `edge_index[6][7] == -1`; A–C has no edge, so
`edge_index[0][2] == -1` as well. Static `{0}` initialization cannot mark
a missing record because 0 is a valid edge index. Active records occupy
`edges[0]` through `edges[edges_size - 1]`.

### How do we reset and classify neighbors?

The parent test precedes the ancestor test. It prevents the reverse entry of a tree edge from becoming a back edge. The source retains the comment spelling `ancester`. The template only marks the places for edge actions; it does not add records, compute low-link values, or emit blocks.

```c
void init_visit() {
    visit_time = 0;

    for (int i = 0; i < nodes_size; i++) {
        visit_num[i] = 0;
        parent[i] = -1;
    }
}

void _edge_iteration_(int node) {
    visit_num[node] = ++visit_time;
    for (int i = 0; i < nodes[node].adj_size; i++) {
        int adj = nodes[node].adj_list[i];
        if (visit_num[adj] == 0) {
            /* tree edge */
            parent[adj] = node;
            _edge_iteration_(adj);
        }
        else if (adj == parent[node]) {
            /* tree edge to parent node (processed) */
        }
        else if (visit_num[adj] < visit_num[node]) {
            /* back edge to ancester */
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
```

`visit_num[node] = ++visit_time` increments the shared counter before assigning the new discovery number. `init_visit()` must run before using the template for a fresh traversal. No wrapper for `_edge_iteration_()` is provided.

### How do we add actions to the edge template?

The indexing helper adds one record in each of the two forward-processing cases. The wrapper establishes the active lookup table's -1 marker before recursion.

```c
void _init_edges_list(int node) {
    visit_num[node] = ++visit_time;
    for (int i = 0; i < nodes[node].adj_size; i++) {
        int adj = nodes[node].adj_list[i];
        if (visit_num[adj] == 0) {
            /* tree edge */
            add_edge(node, adj);
            parent[adj] = node;
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

### Where do the saved low-link values come from?

Before extracting blocks, the lab calls the included Chapter 3 function. It initializes each reached vertex's value on entry and propagates smaller values after a child returns.

The review slide abbreviates this array as `back`. The included C source names it `back_num`.

```c
void save_back_num(int i) {
	back_num[i] = visit_num[i] = ++visit_time;
	for (int j = 0; j < nodes[i].adj_size; j++) {
		int adj = nodes[i].adj_list[j];
		if (visit_num[adj] == 0) {
			parent[adj] = i;
			save_back_num(adj);
			if (back_num[i] > back_num[adj]) {
				back_num[i] = back_num[adj];
			}
		} else if (adj != parent[i]) {
			if (back_num[i] > visit_num[adj]) {
				back_num[i] = visit_num[adj];
			}
		}
	}
}
```

The chained assignment gives `back_num[i]` and `visit_num[i]` the same incremented number. This function also compares a visited descendant's number, but that larger number cannot lower the current value. The parent edge is excluded. Only reached vertices get new `back_num` values.

### How are pending edges assigned to blocks?

A parent must decide whether its finished child's edges form a block. The source makes this decision immediately after `_find_bcc(adj)` returns. It compares the child's saved `back_num[adj]` with the current parent's `visit_num[node]`.

If the child's value is smaller, `continue` leaves the edges pending and advances to the next neighbor. It does not end the current vertex's exploration. Otherwise, `close_bcc(tree_edge)` removes edges through that child's tree edge, including the boundary edge. Equality therefore closes a block.

`close_bcc()` opens the next result row with `current_bcc++`. Its `do ... while` pops at least once. The variable `edge` is declared before `do` so the condition can read it. The helper stops only after storing `boundary_edge`, then saves the row's length in `bcc_size[cur]`.

Each reached edge is pushed once. The stack contains exactly the encountered edges not yet assigned to a row. Valid indexing and unchanged traversal order ensure that `tree_edge` is still present when its child finishes. A root checks each finished child by the same comparison. There is no incoming root edge and no separate root-parent array access.

```c
int bcc[9][45];
int bcc_size[9] = {0};
int current_bcc = 0;

void close_bcc(int boundary_edge) {
    int cur = current_bcc++;
    int pos = 0;

    int edge;
    do {
        edge = pop();
        bcc[cur][pos++] = edge;
    } while (edge != boundary_edge);

    bcc_size[cur] = pos;
}

void _find_bcc(int node) {
    visit_num[node] = ++visit_time;
    for (int i = 0; i < nodes[node].adj_size; i++) {
        int adj = nodes[node].adj_list[i];
        if (visit_num[adj] == 0) {
            /* tree edge add to stack and proceed */
            int tree_edge = edge_index[node][adj];
            push(tree_edge);
            parent[adj] = node;
            _find_bcc(adj);
            if (back_num[adj] < visit_num[node]) {
                continue;
            }
            close_bcc(tree_edge);
        }
        else if (adj == parent[node]) {
            /* tree edge to parent node (processed) */
        }
        else if (visit_num[adj] < visit_num[node]) {
            /* back edge to ancester add to stack */
            int back_edge = edge_index[node][adj];
            push(back_edge);
        }
        else if (visit_num[adj] > visit_num[node]) {
            /* back edge to descendant (processed) */
        }
        else {
            /* edge connecting node to itself */
        }
    }
}

/* called once */
void find_bcc(int start_node) {
    init_visit();
    save_back_num(start_node);
    top = -1;
    init_visit();
    _find_bcc(start_node);
}
```

#### Where does the invariant hold in the C code?

Check the accounting invariant after each `push()` or complete pop-and-store pair. In `close_bcc()`, the first `pos` cells of `bcc[cur]` belong to the forming row. Each `edge = pop()` temporarily holds one removed edge in the local variable; `bcc[cur][pos++] = edge` finishes the transfer. While another loop iteration is needed, `boundary_edge` remains in the pending stack. Popping and storing it ends the loop.

`current_bcc` increases when the row opens. `bcc_size[cur]` is written only after the row is complete. During this helper, use `pos` for the forming length; a row count alone does not mean every row is complete. Read completed output rows through their saved sizes after the helper returns. This invariant does not add bounds checks to the source's unchecked stack operations.

The stronger postorder invariant applies at the end of `_find_bcc(node)`'s neighbor loop, before that function returns. For a non-root, its incoming edge is `edge_index[parent[node]][node]`. That edge and the pending entries above it share one eventual BCC. The caller then tests `back_num[adj] < visit_num[node]` and either keeps or closes the returned child's suffix. A root has `parent[node] == -1`; do not use that value as an array index to look for an incoming edge.

### How do the passes share and reset state?

Call `init_edges_list(start_node)` before `find_bcc(start_node)` with the
same starting vertex and unchanged adjacency lists. The indexing wrapper
clears discovery state, sets `edges_size` to zero, initializes the active
`edge_index` table, and records only the starting component's edges.
Neither wrapper performs an all-vertex sweep.

`find_bcc()` calls `init_visit()`, then `save_back_num(start_node)`. It
sets `top = -1`, calls `init_visit()` again, and enters
`_find_bcc(start_node)`. `init_visit()` clears `visit_time` and
`visit_num`, and sets parents to -1. It preserves `back_num`. Extraction
reads those saved values without recomputing them. The same root and
neighbor order reproduce the discovery numbers used in the saved values.

The `/* called once */` comment describes the supplied use.
`find_bcc()` does not clear `current_bcc`, `bcc`, or `bcc_size`. A fresh
process initializes these globals to zero; another call appends rows
unless the caller manages the result state. Reindexing a different
component also overwrites edge records and changes the meaning of old
row indices. A whole-graph extension needs consistent edge identities
and explicit result management.

### What storage and checks does the source provide?

The supplied alphabet example uses seven pending stack entries and five
active recursive calls at peak. The slide example uses eight
pending entries and six active calls. The declared arrays reserve their
full capacities:

| Storage | Fixed capacity |
| --- | --- |
| `nodes[10]`, each with `adj_list[10]` | Ten vertices and ten neighbor positions per vertex |
| `edges[45]` | Forty-five edge records |
| `stack[10]` | Ten pending edge indices |
| `edge_index[10][10]` | One lookup cell per ordered vertex pair |
| `bcc[9][45]`, `bcc_size[9]` | Nine block rows, up to 45 entries per row, and nine row sizes |

Ten vertices have at most 45 distinct unordered pairs, so `edges[45]` can
record all edges of a simple undirected graph on those vertices. An edge
block needs at least one tree edge, and ten vertices have at most nine
tree edges across their connected components. The nine result rows cover
that bound. These capacities do not enlarge `stack[10]`: the pending-edge
peak must still fit ten entries. The alphabet and slide examples use
seven and eight entries respectively. Capacity also does not make the
wrappers whole-graph algorithms. Every node, neighbor, edge, stack,
block-row, and block-column write must fit its storage.

`add_edge()` and the stack operations are unchecked. `push()` does not
call `is_full()`, and `pop()` does not call `is_empty()`. Invalid roots or
exceeded capacities are not rejected through a status interface. The lab
changes globals directly and provides no unchanged-output failure
guarantee. Larger inputs need redesigned capacities and checks.

### How do we run the two examples?

The lab has no `main()`. The [alphabet lecture driver](../code/lecture/lab_demo.c)
uses the supplied initializers and prints discovery, low-link, edge, and
block tables for the A–J graph:

```sh
cd module_06_graph_dfs/code
make lecture
```

For the alphabet example, the essential sequence in a fresh program is:

```c
alphabet_nodes_init();
edges_init();
init_edges_list(0);
find_bcc(0);
```

The expected active sizes are `edges_size == 8`, `current_bcc == 3`, and `bcc_size` beginning with `1, 6, 1`. The final stack is empty with `top == -1`. The exact rows are `[1]`, `[7, 6, 5, 4, 3, 2]`, and `[0]`.

After extraction completes, read only rows below `current_bcc` and entries below `bcc_size[row]`.
Resolve those entries through the current `edges` list. In this run,
`visit_num` for A–F is 1/2/3/4/5/6, `parent` is -1/0/1/1/3/4, and
`back_num` is 1/2/3/2/2/2. G/H/I/J remain unvisited. These are the source
values for the separate alphabet example. Its three edge blocks are
B–C, the six edges among B/D/E/F, and A–B.

The [slide driver](../code/lecture/ppt_demo.c) initializes seven vertices
at internal indices 0–6, with `data` characters A–G, and the ten slide
connections. It uses the unchanged DFS and block functions without
calling the alphabet graph initializers. The displayed diagram numbers
come from `visit_num`; the `data` characters are separate source data.
From the repository root, compile it with
`cc -std=c11 -I. module_06_graph_dfs/code/lecture/ppt_demo.c -o /tmp/ppt_demo`,
then run `/tmp/ppt_demo`.

The driver's vertex table separates storage indices from visit numbers.
Its printed columns are `vertex_index visit_number parent_index low`:

| `vertex_index` | `visit_number` | `parent_index` | `low` |
| --- | --- | --- | --- |
| 0 | 1 | -1 | 1 |
| 1 | 2 | 0 | 1 |
| 2 | 3 | 1 | 1 |
| 3 | 4 | 2 | 3 |
| 4 | 5 | 3 | 3 |
| 5 | 6 | 4 | 3 |
| 6 | 7 | 2 | 2 |

For internal indices 0–6, `parent` is -1/0/1/2/3/4/2 and `back_num`
is 1/1/1/3/3/3/2. Printed edge and block endpoints use
`visit_num[edges[i].from]` and `visit_num[edges[i].to]`, so the output
pairs match the completed diagram's visit numbers. `parent_index`
continues to identify the parent by its storage index.

Edge indices 0–9 follow the ten recording directions in Thinking
Logically, in that order. `edges_size == 10` and `current_bcc == 2`.
The two raw rows are `[7, 6, 5, 4, 3]` and `[9, 8, 2, 1, 0]`, with
`bcc_size` 5/5 and `top == -1`. The driver also prints each row's resolved
visit-number endpoint pairs, matching the conceptual stack table.
With `nodes_size == 7`,
lookup initialization writes 49 cells; the alphabet setup uses 100 cells.

The midterm insertion/deletion questions concern the representations.
`lab.c` supplies sample initialization and DFS passes; it does not provide
a general vertex/edge deletion interface.
