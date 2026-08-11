# Week 8 — BFS from Trees to Graphs: Vocabulary and Questions

[All-week vocabulary and question bank](../Data_Structures_Course_2026_Student_Question_Bank.md)

## Required scope for the 14-week course

Module 8 is a short bridge: students trace a Queue of tree nodes through a
left-first level-order visit, explain why Queue order produces nondecreasing
depth, and read and run a supplied level-order scaffold. They do not implement
or submit the full Module 8 lab. Module 9 is the main lab: students implement
graph BFS discovery, distance, predecessor, and path reconstruction and test
cycles, unreachable vertices, and both graph representations. The tree trace
and Graph BFS evidence form **one combined Week 8 artifact**, with one rubric
and one due date.

## Vocabulary students will learn

| Term | Working meaning |
|---|---|
| traversal | A planned procedure for visiting stored items. |
| breadth-first search (BFS) | A method that processes smaller depths or hop counts before larger ones. |
| level order | Tree BFS order, grouping nodes by equal depth. |
| root | The top node from which tree depth is measured. |
| depth | The number of child links from the root to a tree node. |
| level | All tree nodes at the same depth. |
| nondecreasing depth | An order in which the reported depth never becomes smaller. |
| Queue | A waiting collection that removes the earliest-added item first. |
| first in, first out (FIFO) | The Queue rule that preserves waiting arrival order. |
| frontier | Discovered nodes or vertices still waiting to be processed. |
| work record | One queued tree-node pointer paired with its depth. |
| left-first level order | Enqueuing the left child before the right child when both exist. |
| width | The number of tree nodes at one level. |
| maximum width (`w`) | The greatest number of nodes found at any one tree level. |
| graph | A set of vertices and the direct relationships stored between them. |
| vertex | One item in a graph. |
| edge | One direct relationship between two vertices. |
| source | The selected vertex where graph search begins. |
| hop | Following one graph edge. |
| unweighted graph | A graph in which every followed edge contributes one hop. |
| minimum-hop path | A valid source-to-destination path using the fewest edges. |
| discovered | Reached and successfully added to the waiting Queue for the first time. |
| enqueue-time marking | Recording discovery immediately after a successful enqueue. |
| processed | Removed from the Queue and recorded in visit order. |
| discovered array | One stored yes-or-no value per vertex indicating whether it has already entered the frontier. |
| distance | The minimum number of hops from the source to a discovered vertex. |
| predecessor | The previous vertex on the route fixed at first discovery. |
| sentinel | A value reserved to represent a special case rather than an ordinary vertex or distance. |
| sentinel 16 | The course marker for “no distance” or “no predecessor,” unambiguous because active IDs are 0–15. |
| unreachable | Having no directed route from the selected source. |
| path reconstruction | Building a forward path by following predecessors backward and reversing the sequence. |
| path certificate | A returned path whose endpoints, edges, and hop count can be checked independently. |
| visit order | The order in which vertices are dequeued and recorded. |
| deterministic neighbor order | A stated inspection order that makes repeated runs choose the same valid path. |
| adjacency matrix | A square table whose cell records whether one possible edge exists. |
| adjacency list | One stored collection of outgoing neighbors for every vertex. |
| representation equivalence | Different graph storage methods producing the same public BFS results under the same ordering rule. |
| candidate result | Temporary output built separately before a function is known to have succeeded. |
| commit | Publish a completed candidate into caller-owned output. |
| failure preservation | A failed operation leaves the caller's old protected output unchanged. |
| auxiliary space | Temporary working storage separate from the input and returned result. |
| `O(n)` | Tree-traversal work proportional to the number of nodes. |
| `O(w)` | Tree-BFS frontier space proportional to maximum width. |
| `O(V²)` | Matrix-BFS work that can grow like the vertex count multiplied by itself. |
| `O(V + E)` | Adjacency-list BFS work proportional to vertices plus stored edges. |
| combined artifact | The single Week 8 submission containing the brief tree trace and the main Graph BFS evidence. |

### Optional vocabulary for extension questions

These terms belong to the optional Module 8 deep dive or additional Graph BFS
generalization, not the required Week 8 implementation.

| Term | Working meaning |
|---|---|
| tree-BFS implementation | Student-written code for level-order tree traversal; Week 8 uses supplied code instead. |
| shallowest-value search | A tree BFS that returns a matching node at the smallest depth. |
| left-first tie | Choosing the left-discovered match first when equal-depth matches exist. |
| BFS forest | Repeated BFS trees used to cover every component of a disconnected graph. |
| proof obligation | A specific fact that must be justified for an algorithm or ordering rule to be trusted. |

## Anticipated student questions

### Meaning and mental model

- What does breadth-first search mean in ordinary language?
- What is a frontier, and why does BFS manage it with a Queue?
- Why does a FIFO Queue visit a tree in nondecreasing depth?
- What changes when the tree-level-order idea is transferred to a graph?
- What does a minimum-hop path minimize, and what does it ignore?

### Representation and invariants

- What information belongs in each supplied tree-BFS work record?
- Which tree properties let level-order traversal omit a discovered array?
- Why does graph BFS need discovered state even when tree BFS does not?
- What do the `distance` and `predecessor` arrays mean for a discovered vertex?
- When must a graph vertex become discovered, and what invariant does that timing preserve?
- Which result fields use the sentinel value 16, and why is 16 unambiguous in this course graph?

### Operations, C API, and ownership

- Which parts of the supplied Module 8 level-order scaffold are students expected to read and run rather than implement?
- Does `tree_level_order` own or modify the caller's tree nodes?
- What must `graph_bfs_matrix` and `graph_bfs_list` preserve when they return an error?
- What must `graph_bfs_reconstruct_path` include in a successful path, including the source-only case?
- Who owns the graph, Queue storage, BFS result, and reconstructed path at each API boundary?

### Tracing

- Given a binary tree, what are the Queue contents before and after each left-first level-order step?
- How can a tree trace demonstrate that depths never decrease in dequeue order?
- On a graph with two routes to the same vertex, which route fixes its predecessor?
- How do Queue, discovery, distance, predecessor, and visit order change during one complete graph-BFS trace?
- What happens in the trace when an outgoing edge points to an already discovered vertex?
- How does ascending neighbor-ID order determine one reproducible minimum-hop path when several exist?

### Testing and debugging

- Which test shows that enqueue-time marking prevents duplicate pending work on converging routes?
- Which tests distinguish an empty graph, a singleton source path, a cycle, and a disconnected destination?
- How would a matrix/list equivalence test reveal a representation-specific BFS defect?
- What symptom would appear if a vertex were marked discovered only when dequeued?
- How can a test verify that an unreachable or malformed path request leaves the caller's prior output unchanged?

### Complexity

- Why is the supplied tree-level-order trace `O(n)` time and `O(w)` auxiliary space?
- Why does matrix-based graph BFS take `O(V^2)` time even on a sparse graph?
- Why does adjacency-list graph BFS take `O(V + E)` time when each vertex and edge is processed in bounded ways?
- How can the Queue's peak size differ between a narrow tree and a wide graph without changing BFS correctness?

### Security and interpretation

- Why does graph reachability not prove that access is authorized?
- Why does a small hop count not establish likelihood, exploitability, trust, or real-world risk?
- How could invalid vertex IDs or unchecked Queue limits become reliability or security problems in C?

### Assignment and evidence

- What belongs in the single combined Week 8 submission?
- Why is there no separate Module 8 programming submission in the 14-week course?
- Which evidence demonstrates correct distance, predecessor, path reconstruction, cycles, unreachable vertices, and representation equivalence?
- How should the brief tree trace and the main graph-BFS code be connected in the synthesis explanation?

### Transfer

- How does Queue-controlled tree level order prepare you to reason about graph BFS?
- When would DFS answer a reachability question without providing the minimum-hop certificate that BFS provides?
- How will graph-BFS predecessor paths prepare you for Dijkstra's weighted paths?
- Why is a dense Boolean discovered array preferable to a hash table when vertex IDs already occupy `0` through `V - 1`?

### Extension questions

- How would you implement `tree_level_order` from the supplied scaffold while preserving output on every failure?
- How would a shallowest-value tree search resolve equal-depth ties?
- How could a full BFS forest cover all disconnected graph components after the source component finishes?
- What additional proof obligations arise if outgoing neighbors are not stored in deterministic order?

## Sources

- [14-week delivery guide](../Data_Structures_Course_2026_14_Week_Delivery_Guide.md)
- [Master spiral curriculum](../Data_Structures_Course_2026_Spiral_Curriculum.md)
- [Original Weeks 8–14 question bank](02_weeks_08_14_questions.md)
- [Module 8 bridge role](../module_08_tree_bfs/README.md)
- [Module 8 vocabulary reference](../module_08_tree_bfs/student/vocabulary.md)
- [Module 9 main-lab role](../module_09_graph_bfs/README.md)
- [Module 9 vocabulary reference](../module_09_graph_bfs/student/vocabulary.md)
