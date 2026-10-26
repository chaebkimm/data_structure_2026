# Chapter 11 — Minimum-Cost Routes with an Indexed Heap

This chapter explains the supplied [lab.c](lab.c). The code is complete;
the required work is to predict states, trace operations, and test the
actual source. Keep the initial inquiry and investigation predictions
before reading the worked trace.

## Why BFS and least cost can disagree

Breadth-first search processes a graph in edge-count layers. It finds the
fewest connections from a source. When edges have different costs, counting
connections does not add their weights.

```text
A -> E                 1 edge,  cost 14
A -> C -> D -> E        3 edges, cost 2 + 2 + 2 = 6
```

Both statements can be correct: the first route uses fewer edges and the
second costs less. A path is a sequence following stored edges; its cost
is the sum of their weights. In this lesson the numbers are invented
minutes, so the sum models consecutive work. A cheap modeled route does
not establish authorization, trust, safety, or real-world availability.

## Store the current best cost

`node_dist[v]` stores the best source-to-node cost discovered so far.
Before discovery it is `-1`, a reserved marker called a sentinel. A source
has cost zero because its source-only route uses no edges.

`init_dist(start_node)` calls `init_heap`, fills all ten distances with
`-1`, clears `found`, and calls `add_node(start_node,0)`. The graph and its
weights are supplied separately by the caller.

The waiting costs are tentative: another route may lower them. When the
algorithm removes the waiting node with the smallest total cost, that cost
becomes final. `found[node]=1` records this event. The loop never reads
`found`; it is useful observed state, not the queue membership mechanism.

## Three arrays answer different questions

The graph imported from Module 3 has `nodes[10]`. Each node stores neighbor
IDs in `adj_list` and a count in `adj_size`. Module 11 stores a listed
edge's positive cost separately in `edge_length[u][v]`.

The adjacency list tells the algorithm which edges exist. The cost matrix
tells it what a listed edge costs. An unused zero matrix cell does not
create an edge. The canonical fixture is directed; do not call Module 3's
`edges_init()` to load it, because that helper creates a different,
undirected graph.

The minimum heap stores IDs rather than copied distances:

```text
heap position i:          0  1  2
heap[i], a node ID:       3  4  1
node_dist[heap[i]]:       4 14  5
```

Here D is node 3 at position 0, while B is node 1 at position 2. `comp(i,j)`
first reads the IDs in the two slots and then compares their distances.
The heap property requires each parent's cost to be no greater than each
existing child's cost. It does not sort the entire array.

## Find a waiting node directly

`node_heap_pos[v]` locates the slot containing waiting node `v`. For every
live heap slot `i`:

```text
node_heap_pos[heap[i]] == i
```

This is an inverse-map invariant: applying the ID lookup and then the
position lookup returns the starting slot. `swap(i,j)` exchanges the IDs
and updates both positions together. A map update is part of a heap swap,
not optional work after the complete algorithm.

Only positions `0` through `size-1` are live. The actual `remove_root`
leaves the removed ID's map entry pointing at an inactive slot. Therefore
`node_heap_pos[v] != -1` is not a reliable membership test after removals.
Check the inverse map only for live entries. Never call `update_value` for
an absent node.

## Repair locally after a change

`heap_parent`, `left`, and `right` return heap positions. `-1` means a
missing relative. `heap_parent` has a distinct name because the imported
graph source already uses `parent` for a different array.

`heapify_up` compares a node with its parent and moves it upward until the
local order holds or it reaches the root. `chief_child` chooses the child
with the smaller current distance. `heapify_down` saves that chosen
position before swapping, then follows it downward. Choosing the child
again after a swap could follow a different branch.

`add_node(node,value)` sets the node's distance, appends its ID, records
its position, and repairs upward. The caller must have room and must not
already have that node in the live heap.

`remove_root()` saves `heap[0]`, swaps slots 0 and `--size`, repairs downward,
and returns the saved ID. It needs a nonempty heap. After singleton
removal the heap is empty; both child helpers return `-1`, so the repair
performs no comparisons or swaps.

`update_value(node,value)` uses the map to locate the node. It repairs
downward at the root or when the parent already has a smaller cost;
otherwise it repairs upward. In Dijkstra, this function receives only
strict decreases. A separate valid-heap test can exercise increases too.

The comparator uses strict `<`. Equal priorities may swap upward or
downward; the smaller child selector chooses the right child on an equal
comparison. The source promises neither arrival-order stability nor
node-ID tie ordering. Equal costs still satisfy the heap property.

## Relax one outgoing edge

To relax an edge is to ask whether that edge supplies a better route:

```text
new_dist = node_dist[node] + edge_length[node][adj]
```

There are three cases:

1. `node_dist[adj] == -1`: this is its first discovery. Insert the node.
2. `node_dist[adj] > new_dist`: improve its cost and repair its existing slot.
3. Otherwise: leave the known cost and heap unchanged.

The second case changes an existing priority; it does not insert a second
copy. Equal candidates cause no distance update. This differs from a
lazy-duplicate queue that keeps separate old and new cost snapshots.

## Work the canonical fixture

Use A=0, B=1, C=2, D=3, E=4, F=5. Load each adjacency list in the listed
order:

```text
A -> B 9, C 2, E 14
B -> D 1, E 8
C -> B 3, D 2
D -> E 2
E -> no outgoing edges
F -> no outgoing edges
```

The next table records state after each removed node's outgoing edges have
been processed. Heap columns contain IDs, not distances.

| Event | `node_dist` A through F | Live heap |
| --- | --- | --- |
| initialized | `[0,-1,-1,-1,-1,-1]` | `[A]` |
| process A | `[0,9,2,-1,14,-1]` | `[C,B,E]` |
| process C | `[0,5,2,4,14,-1]` | `[D,E,B]` |
| process D | `[0,5,2,4,6,-1]` | `[B,E]` |
| process B | `[0,5,2,4,6,-1]` | `[E]` |
| process E | `[0,5,2,4,6,-1]` | `[]` |

C improves B from 9 to 5 in place, and D improves E from 14 to 6 in place.
B later offers D a cost of 6 and E a cost of 13; neither is smaller.
Finalization order is A, C, D, B, E. F remains undiscovered and `found[F]`
remains zero.

There are five insertions including the source, five removals, two
`update_value` calls, eight outgoing-edge inspections, and a peak heap size
of three. These are source-derived counts, not counters returned by the
lab. Count six successful edge changes: four first discoveries and two
improvements. The source insertion is separate from those edge changes.

The route A,C,D,E manually certifies E's cost 6. The program itself stores
no predecessor and returns no path, so the route is not a reconstructed
program output.

## Why a removed node is final

Suppose node `u` has the smallest waiting distance. Any alternative route
that still passes through unfinished work must reach a waiting node at a
cost at least as large as `u`'s current cost. Following positive edges
cannot reduce that cost. Such a route cannot later improve `u`.

Thus every discovered node is inserted once and removed once. An already
removed node cannot satisfy the strict-improvement branch. This explains
why the source can leave `found` unread and removed positions stale under
its valid-input assumptions. It would be unsafe to reuse this reasoning
for arbitrary priority updates or negative weights.

## State what the C source assumes

The arrays support IDs 0–9 and at most ten neighbors per stored list.
The caller must load valid neighbor IDs, use positive weights for every
listed edge, call removals only on nonempty heaps, and keep all candidate
sums within `int`. The source validates none of these conditions and has
no signed-overflow guard. Do not execute overflow or out-of-bounds cases
to demonstrate rejection that the API does not provide.

Dijkstra's mathematical method also works with zero weights, but the
supplied lab explicitly states a positive-weight contract. Negative costs
are outside both that contract and this finalization argument.

## Analyze the representation actually used

For a generalized graph with `V` vertices and `E` stored directed edges,
there are at most `V` insertions and removals and at most `E` priority
improvements. Each heap repair follows one path of length `O(log V)`.
The usual bound is `O((V+E) log V)` time with `O(V)` auxiliary heap, map,
distance, and finalization storage. Full invariant checking is separate
`O(V)` work and is not part of a single repair's cost.

The graph input includes an `O(V^2)` cost matrix as well as adjacency
lists. Do not call the whole representation `O(V+E)` storage while ignoring
that matrix. The actual code fixes every relevant node array at ten,
so asymptotic claims describe a scalable version of the same design.

## Connect to the course

BFS uses FIFO ordering; a linear minimum-priority queue scans for its next
node; this indexed heap repairs a tree-shaped array. Dijkstra supplies the
same least-cost rule to either priority-queue implementation. Compare
returned distances on the same fixture before comparing operations.

Practical 2 is the sole Week 11 submission. It contains the trace, actual-
source tests, one focused original regression, assumptions, and the supplied
BFS/linear-priority-queue/heap comparison. The optional lazy-duplicate
library in `code/include`, `code/starter`, and `code/solution` illustrates a
different design; its parser, path API, dynamic allocation, and stable
snapshot rules are not added implementation tasks for this lab.
