# Stage B — Dijkstra with One Heap Entry per Waiting Node

Open this file after preserving Stage A. The source of truth is
[lab.c](lab.c), including the graph representation imported from Module 3.

## 1. Separate two goals

A **graph** stores items called **nodes** or **vertices**, connected by
**edges**. A **directed edge** works only from its stated start to its end.
**Breadth-first search (BFS)** uses a first-in, first-out Queue to minimize
edge count. It does not minimize unequal numeric costs.

A **weight** is a cost on an edge. A **path** follows stored edges, and its
cost is the sum of their weights. The **source** is the starting node.
The invented direct route A to E costs 14, while A to C to D to E costs 6.
Dijkstra's algorithm chooses by current total cost instead of hop count.

## 2. Match the source's arrays to their meanings

The source reserves space for ten nodes, with IDs 0 through 9.

| Source name | Meaning |
| --- | --- |
| `nodes[v].adj_list` and `adj_size` | IDs of outgoing neighbors and their count |
| `edge_length[u][v]` | Positive `int` cost of a listed edge from `u` to `v` |
| `node_dist[v]` | Best total cost known so far; `-1` means undiscovered |
| `found[v]` | 1 after the node has been removed and finalized; otherwise 0 |
| `heap[0..size-1]` | Node IDs currently waiting, arranged as a minimum heap |
| `node_heap_pos[v]` | The current heap position of a waiting node |

An **adjacency list** groups a node's outgoing neighbor IDs. The list
establishes which edges exist; a zero cell in `edge_length` does not create
an edge. `init_dist` resets the heap, distances, and `found`, then adds the
source at cost zero. It does not load or validate the graph or weights.

## 3. Distinguish an ID from a position

A node ID identifies a place. A heap position identifies a slot in the
waiting collection. They can have different numeric values.

```text
heap position:     0  1  2
heap node ID:      3  4  1
current distance:  4 14  5
```

Here D is node 3 at position 0. `comp(0,2)` compares `node_dist[3]` with
`node_dist[1]`; it does not compare `node_dist[0]` with `node_dist[2]`.
The **inverse position map** satisfies, for every live position `i`:

```text
node_heap_pos[heap[i]] == i
```

`swap(i,j)` exchanges two heap slots and repairs both map entries. Entries
for removed nodes are left stale by this source. The inverse-map promise
applies only to nodes still in the live heap, not to every discovered node.

## 4. Insert once, then change the existing priority

A **tentative distance** is a best cost that may still improve.
**Relaxation** tests a listed edge using:

```text
new_dist = node_dist[node] + edge_length[node][adj]
```

If `adj` is undiscovered, `add_node` sets its distance, appends its ID, and
repairs upward. If the candidate is strictly smaller than its known cost,
`update_value` changes its distance and repairs from its mapped heap slot.
An equal candidate does nothing. This is an **indexed heap**: the map lets
the algorithm locate a waiting node directly. It creates no duplicate
snapshots and needs no stale-snapshot test.

The smallest current distance is removed next. **Finalization** means that
this cost can no longer improve under the assumptions. With positive
weights, an unfinished extension cannot produce a cheaper route to an
already removed node. Thus `found` records finalization but is never read
by this loop; it is not a membership test.

## 5. Read the exact limits

The caller supplies valid IDs and adjacency counts, positive weights, and
candidate sums representable by `int`. The code has no input validator or
addition guard. It computes distances, not predecessor arrays or paths.
It supplies no status returns, allocation, or stable tie rule. Its strict
`<` comparator can move equal priorities during repairs.

The separate `code/include`, `code/starter`, and `code/solution` library
uses a different lazy-duplicate design. Its parser, unsigned sentinels,
path API, and stable frontier are optional reference material, not this
lab's behavior or required work.
