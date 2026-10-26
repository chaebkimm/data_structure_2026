# Chapter 11. Minimum Costs with an Indexed Heap

## Starting Question

> BFS finds a route with the fewest edges. Which unfinished node should we
> choose when the goal is the smallest total cost?

Expected answer: choose the node with the smallest current cost, then test
whether its outgoing edges improve other costs. Positive edge costs make
that chosen minimum final.

## Why We Need This

A direct A→E edge can cost 14 while A→C→D→E costs6. BFS optimizes edge count;
Dijkstra optimizes the sum of weights. The required
[lab.c](../module_11_graph_dijkstra/student/lab.c) reuses Module 03 adjacency
lists and Module 10 heap ideas. The graph rows store neighbor IDs, a separate
matrix stores edge lengths, and a minimum heap stores one pending copy of
each discovered node. Its key is read from `node_dist`.

All functions are supplied. Students trace and test the actual source, then
compare it with BFS and an instructor-supplied linear minimum-selection
reference. Their driver, trace, comparison, and corrections form the one
Week 11 Practical 2 submission. No new parser, path reconstruction, or separate
standalone Dijkstra implementation is required.

## Board Walkthrough

Use these directed edges in this adjacency order:

```text
A->B9  A->C2  A->E14
B->D1  B->E8
C->B3  C->D2
D->E2
E and F have no outgoing edges
```

Initialize the imported nodes, set `nodes_size=6`, and install both adjacency
IDs and matching weights. Do not also call Module 03's different `edges_init`.
Only listed adjacency entries are traversed; a matrix cell does not itself
create an edge.

| After processing | Distances A..F | Live heap IDs |
|---|---|---|
| initialize | `0,-1,-1,-1,-1,-1` | `[A]` |
| A | `0,9,2,-1,14,-1` | `[C,B,E]` |
| C | `0,5,2,4,14,-1` | `[D,E,B]` |
| D | `0,5,2,4,6,-1` | `[B,E]` |
| B | `0,5,2,4,6,-1` | `[E]` |
| E | `0,5,2,4,6,-1` | `[]` |

The removal/finalization order is A,C,D,B,E. B9→5 and E14→6 are in-place
updates, not duplicate insertions. B's proposals D6 and E13 change nothing.
F stays `-1`; source A remains0. The manually checked A,C,D,E route costs6,
but the current lab stores no predecessors or returned path.

After C, position 0 holds D, numeric ID 3, and its key is4. Position1 holds
E/key 14; position 2 holds B/key 5. Require the live inverse identity
`node_heap_pos[heap[i]]==i`. The heap array need not be globally sorted.
`comp` and `swap` receive positions; `update_value` receives a node ID.
`heap_parent` avoids a name conflict with Module 03's `parent[10]` array.

## Neutral Questions

- Why can A,E be the BFS answer while its cost 14 exceeds6?
- What does `-1` mean, and which function initializes every distance?
- Why does improving B change its one queued entry rather than add another?
- Which map entries must a swap update?
- Why is the selected child cached before a downward swap?
- Does `found` prevent a later update, or does the positive-weight proof do that?
- After removal, can a nonnegative map value still refer to an absent node?
- What does the strict `<` comparator promise about equal-key removal order?

## Source Boundaries

The source fixes ten node slots and assumes valid IDs, bounded rows, positive
`int` weights, and candidate sums that fit in `int`. It does not validate
those conditions or check overflow. Callers prevent duplicate/full insertion,
empty removal, and updates to removed nodes.

`found` is written on removal and never checked. A removed minimum cannot
improve under the stated assumptions, so the code never uses its stale map.
Only live map entries are authoritative; removal does not reset its map to
`-1`. Equal keys may swap, and no arrival-order guarantee exists.

The optional library under `code/include`, `starter`, `solution`, and `support`
uses a different lazy-duplicate strategy, parser, stable snapshots, sentinels,
and predecessor/path API. Those features are not guarantees of this lab.

## Vocabulary and Final Check

Retrieve BFS, adjacency lists, arrays, active prefixes, parent/child order,
and inverse maps. Introduce path cost, tentative/finalized distance, strict
relaxation, indexed minimum heap, shared key, and decrease-key when needed.
No stale-snapshot mechanism is required in this implementation.

Students explain why finalization is safe, trace a key decrease and both
map updates, test a nonzero or isolated source, and state caller assumptions.
For generalized V and E, the indexed run uses `O(V + (V+E) log V)` work and
`O(V)` heap-related state; the matrix separately reserves `O(V²)` storage.
The literal source bounds remain ten nodes. Use the
[180-minute plan](../module_11_graph_dijkstra/instructor/lesson_plan.md)
and current [rubric](../module_11_graph_dijkstra/student/rubric.md).
