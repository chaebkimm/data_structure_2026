# Week 11 — Indexed-Heap Dijkstra and Practical 2

[All-week vocabulary and question bank](../Data_Structures_Course_2026_Student_Question_Bank.md)

## Required scope for the 14-week course

**Practical 2 is the sole Week 11 submission.** The supplied
[Module 11 lab](../module_11_graph_dijkstra/student/lab.c) is complete.
Students predict and trace its state, write an assertion driver, run supplied
checks, and compare BFS, linear minimum-selection Dijkstra, and indexed-heap
Dijkstra on the same positive weighted graph. The evidence and comparison
belong in that single artifact within the 180-minute contact block.

The current source uses ten fixed nodes, `int` distances with `-1` for
undiscovered nodes, a heap of node IDs, and an inverse position map. Each
pending node appears once; a shorter route edits its existing key. The
retained lazy-duplicate C library is an optional reference with a separate
API, not another required implementation or path-reconstruction assignment.

## Vocabulary students will learn

| Term | Working meaning |
|---|---|
| graph | Nodes and their stored connections. |
| node or vertex | One graph item, represented by an integer ID in this lab. |
| source | The node where one shortest-distance run begins. |
| directed edge or arc | A connection usable in its stored direction. |
| adjacency list | The neighbor IDs stored in one node's outgoing row. |
| weight | The positive `int` cost stored separately in `edge_length[u][v]`. |
| path cost | The sum of weights along a valid route. |
| breadth-first search (BFS) | Queue-based traversal that minimizes edge count. |
| Dijkstra's algorithm | Repeatedly finalize the smallest current unfinished cost and test outgoing edges. |
| positive weight | A cost strictly greater than zero, as required by the current lab contract. |
| tentative distance | The best source cost known so far, still able to improve before removal. |
| finalized distance | A removed minimum that cannot improve under the stated weight assumptions. |
| frontier | Discovered nodes still waiting to be processed. |
| Priority Queue | An ADT that removes the waiting item with the selected priority. |
| minimum heap | An array-based complete tree whose parent keys are no larger than child keys. |
| node ID | The identity stored in a heap cell; it is not that cell's position. |
| heap position | An index into the live prefix of `heap`. |
| live prefix | Positions `0` through `size-1`, the entries currently in the heap. |
| root | Position0, holding a node with a minimum current distance. |
| parent and child | Related heap positions returned by `heap_parent`, `left`, and `right`. |
| shared key | A node's distance read through `node_dist[heap[i]]`, rather than copied into a heap record. |
| inverse position map | `node_heap_pos`, which locates each live node's current heap position. |
| swap | Exchange two heap positions and update both moved IDs' map entries. |
| upward repair | Move a changed entry toward the root while required by key order. |
| downward repair | Move a changed entry toward the smaller existing child while required. |
| decrease-key | Lower the key of an entry already queued and repair its heap position. |
| strict relaxation | Accept a candidate only on first discovery or when it is strictly smaller. |
| candidate distance | Current node distance plus one listed outgoing edge weight. |
| sentinel | A reserved marker; `-1` means undiscovered/unreachable in this lab. |
| unreachable | Having no route from the source using the loaded directions. |
| caller precondition | A condition the calling driver must establish because the function does not check it. |
| overflow | Arithmetic outside `int`'s range; the lab requires callers to prevent it. |
| Practical 2 | The one integrated Week 11 trace, test, and comparison submission. |

### Optional reference vocabulary

| Term | Working meaning |
|---|---|
| lazy duplicate | Insert an improved copied snapshot rather than editing the queued entry. |
| stale snapshot | An old copied cost that differs from the node's current distance. |
| stable priority queue | Equal keys leave by a promised arrival rule; the current lab promises none. |
| predecessor | A stored prior node used to describe a route; absent from this lab. |
| path reconstruction | Build a route from stored predecessor state in the separate optional API. |
| dynamic frontier | Heap storage whose capacity grows at runtime in the optional implementation. |
| weight parser | Convert checked textual input to a number; the required lab has no parser. |
| `SIZE_MAX` infinity | The optional API's reserved unsigned sentinel, distinct from this lab's `-1`. |
| negative-edge algorithm | A different shortest-path method needed when Dijkstra's assumptions fail. |

## Anticipated student questions

### Meaning and mental model

- Why can BFS return A,E at cost 14 while a three-edge route costs6?
- What does a tentative distance mean before its node is removed?
- Why does choosing the smallest queued distance allow finalization under positive weights?
- What question does relaxation ask about one outgoing adjacency?
- What does `-1` mean before and after the run finishes?

### Representation and invariants

- Why do adjacency rows store only IDs while `edge_length` stores weights separately?
- Does assigning `edge_length[u][v]` create a connection without an adjacency entry?
- How do a node ID, heap position, and distance key differ after C is processed?
- What does `comp(i,j)` read before it compares two costs?
- Which inverse-map identity holds for every live heap position?
- Why must a swap update two map entries?
- Why can a removed node retain a nonnegative map value that no longer proves membership?
- Why is `[D,E,B]` a valid heap for keys `[4,14,5]` even though the keys are not sorted?

### Operations and source behavior

- Which arrays does `init_dist` reset, and which graph data does it retain?
- Why is the source explicitly inserted with distance0?
- Why does first discovery call `add_node`, while a later improvement calls `update_value`?
- How does `update_value` find the node and choose upward or downward repair?
- Why must downward repair keep the selected child position across its swap?
- Why is a singleton removal valid even though downward repair is called after `size` becomes0?
- Why is the heap helper called `heap_parent` rather than `parent` in this combined source?

### Canonical tracing

- After A, why are the distances B9,C2,E14 and the live heap `[C,B,E]`?
- After C, how do B9→5 and the insertion of D4 produce `[D,E,B]`?
- Why does D leave before B, and how does D improve E14→6?
- Why do B's candidate costs D6 and E13 cause no change?
- Which five nodes are removed, and why does F never enter the heap?
- How can the cost 6 route A,C,D,E be checked manually when the lab stores no predecessor array?

### Testing and debugging

- What focused regression distinguishes a node ID from its heap position?
- How can a driver check active heap order and inverse maps after every operation?
- What should tied-key tests assert when the source promises no stable removal order?
- Which fixtures exercise a left-only child, a singleton, and active-key changes in both directions?
- How can an independent linear shortest-distance reference check all final distances?
- Why should repeated runs and nonzero or isolated sources appear in the test evidence?

### Assumptions and interpretation

- Which ID, row-size, heap-capacity, and active-entry conditions must the caller establish?
- Why must every candidate addition fit in `int`, even when that candidate will be rejected as too large?
- Where is `found` written, and why does correctness rely on the positive-weight argument rather than a `found` guard?
- Why should negative weights or signed overflow not be executed as tests expecting rejection from this source?
- What does F's unreachable result say about the loaded model, and what does it not establish about real availability?

### Complexity and comparison

- Why is each reachable node inserted and removed at most once in the indexed strategy?
- Why do the canonical counts give five adds, five removals, two updates, and eight adjacency inspections?
- Why can generalized indexed-heap Dijkstra use `O(V + (V+E) log V)` work and `O(V)` heap-related state?
- How does the separate weight matrix contribute `O(V²)` storage?
- How do BFS, a linear minimum scan, and a heap differ in objective, selection work, and representation?
- Why should fixed ten-node storage be distinguished from a generalized asymptotic analysis?

### Assignment and transfer

- Which supplied functions must students trace rather than reimplement for Practical 2?
- Which driver, output, trace, same-graph comparison, and corrected explanation belong in the single submission?
- Why do the five teaching checkpoints not create five assignments or extra contact time?
- Which Week 10 heap and inverse-map ideas transfer to the changing distance keys?
- Which Priority Queue properties describe the ADT, and which depend on the indexed-heap implementation?
- How does Dijkstra's source-to-node objective differ from a minimum-spanning-tree objective in Week 14?

### Optional extension questions

- How would a lazy-duplicate frontier replace the inverse map and change pending storage?
- Which stale-snapshot check would the optional strategy need before inspecting outgoing arcs?
- What additional state and API would be needed to return predecessor paths from this lab?
- What validation and arithmetic checks would be needed before accepting untrusted graph input?

## Sources

- [14-week delivery guide](../Data_Structures_Course_2026_14_Week_Delivery_Guide.md)
- [Master spiral curriculum](../Data_Structures_Course_2026_Spiral_Curriculum.md)
- [Module 11 current source](../module_11_graph_dijkstra/student/lab.c)
- [Module 11 vocabulary reference](../module_11_graph_dijkstra/student/vocabulary.md)
- [Module 11 Practical 2 role](../module_11_graph_dijkstra/README.md)
