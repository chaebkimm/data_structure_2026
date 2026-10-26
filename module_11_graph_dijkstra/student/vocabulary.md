# Module 11 — Vocabulary for the Current Lab

Open after preserving the Cognitive Pause. Definitions describe
[lab.c](lab.c) unless explicitly labeled as a mathematical generalization.

| Term | Working meaning |
| --- | --- |
| graph | Nodes connected by stored edges. |
| node or vertex | One graph item, identified here by an integer ID from 0 to 9. |
| directed edge | A connection usable only in its stored direction. |
| adjacency list | A node's stored outgoing neighbor IDs and their count. |
| source | The node where a shortest-cost run begins. |
| path | A sequence of nodes that follows stored edges. |
| weight | A listed edge's cost; the lab requires a positive `int`. |
| path cost | The sum of the weights on a path. |
| BFS | Breadth-first search: FIFO processing that minimizes edge count. |
| Dijkstra's algorithm | Repeatedly finalize the waiting node with the smallest current cost and relax its outgoing edges. |
| tentative distance | The best cost found so far for a waiting node; it can still improve. |
| finalized distance | A removed node's cost, proven unable to improve under the valid-weight assumptions. |
| `node_dist[v]` | The source-to-node cost currently known for node ID `v`. |
| sentinel | A reserved marker rather than an ordinary cost. |
| `-1` distance | No source-to-node route has been discovered. |
| unreachable | No stored directed route exists from the source; its distance remains `-1` at termination. |
| `found[v]` | A record that node `v` was removed and finalized; the loop writes but never reads it. |
| frontier | The nodes discovered and still waiting to be processed. |
| Priority Queue ADT | Operations that retain pending items and remove a minimum-ranked item, independent of storage. |
| minimum heap | An array with a tree relationship: each parent's key is no greater than its children's keys. |
| live prefix | Heap positions 0 through `size-1`; other slots are inactive. |
| node ID | The identity of a graph node; not the slot where it currently waits. |
| heap position | An index into the live heap array. |
| key or priority | The cost used to rank a waiting node; read through `node_dist[heap[i]]`. |
| indexed heap | A heap with a map locating an item directly from its ID. |
| inverse position map | `node_heap_pos`, satisfying `node_heap_pos[heap[i]] == i` for every live slot. |
| invariant | A relationship that must hold at the stated observation points. |
| stale removed position | A removed node's map value left at an inactive slot; not a membership guarantee. |
| upward repair | Follow a node's parent path to restore heap order. |
| downward repair | Follow the smaller child's path to restore heap order. |
| relaxation | Check whether one outgoing edge supplies a better distance. |
| candidate distance | `node_dist[node] + edge_length[node][adj]`. |
| strict improvement | A candidate smaller than the known distance; equality does not update it. |
| decrease-key | Lower an already waiting item's priority and restore its position. |
| stable tie order | Equal priorities leave in arrival order; this lab does not promise it. |
| precondition | A requirement the caller must satisfy before an operation. |
| overflow | A mathematical value beyond the C type's range; the lab does not guard `int` addition. |
| regression test | A focused check designed to expose a specific plausible defect. |
| independent reference | A separately implemented way to check expected shortest costs. |
| auxiliary storage | Working state beyond the graph input, including heap, map, distance, and `found`. |
| asymptotic complexity | How work or storage would grow if the fixed arrays were generalized. |
| implementation | The particular code and storage used to perform ADT operations. |
| Practical 2 | The sole integrated Week 11 evidence and programming artifact. |

Dijkstra's mathematical method permits nonnegative weights, including zero.
The current lab declares the narrower positive-weight precondition and
checks no inputs. It stores no predecessor and returns no path.

## Optional reference vocabulary

The separate library in `code/include`, `code/starter`, and `code/solution`
uses **lazy duplicates**: improved vertex-and-cost snapshots are inserted
while older snapshots remain. A **stale snapshot** has a saved cost that
no longer matches the current distance. That library uses an unsigned
`size_t` range, a `SIZE_MAX` infinity sentinel, status returns, a parser,
predecessors, reconstructed paths, and stable snapshot ties. These terms
describe that optional library, not guarantees or required tasks of the
indexed `student/lab.c`.
