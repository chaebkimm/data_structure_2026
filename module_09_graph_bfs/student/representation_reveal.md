# Stage B — Formal Name and Stored Graph-Search State

Open this file only after preserving the Stage A inquiry.

## 1. Name the task

A **graph** stores items called vertices and direct relationships called
edges. A **source** is the selected starting vertex. A **hop** follows one
edge.

**Breadth-first search (BFS)** processes vertices in nondecreasing hop
count from the source: smaller counts before larger counts. An
**unweighted graph** treats every edge as one hop.

The **distance** of a reachable vertex is the minimum number of hops from
the source. **Unreachable** means no route following the stored directions
leads from the source to that vertex.

## 2. Separate discovered from processed

A **Boolean value** is either `true` or `false`. A `discovered` array stores
one Boolean per vertex.

An **ID** is an identifying number. In `discovered[v]`, the letter `v`
stands for one vertex ID and square brackets select that ID's array
position. The symbol `==` asks whether two values are equal.

In this module:

> `discovered[v] == true` means vertex `v` was successfully placed in
> waiting work earlier.

A vertex is **processed** when it is removed from waiting work and recorded
in visit order. A discovered vertex may still be waiting, so discovered and
processed do not mean the same thing.

A **Queue** removes the earliest-added item first. `enqueue` adds at the
back. `dequeue` removes from the front. **FIFO** abbreviates “first in,
first out.” The **frontier** is the Queue of discovered vertices that have
not yet been processed.

List every Queue in this module from front to back.

## 3. Store distance and predecessor

The `distance` array stores one hop count per vertex. The source distance is
0.

A **predecessor** is the previous vertex on the route fixed at first
discovery. Here `u` is the current vertex and `v` is its neighbor. If edge
`u -> v` first discovers `v`, then:

```text
distance[v] = distance[u] + 1
predecessor[v] = u
```

The source has no predecessor. An unreachable vertex has no distance and no
predecessor. The C package uses the named value 16 for both “no distance”
and “no predecessor.” Sixteen is a **sentinel**, a stored value chosen to
mean a special case. It is safe here because valid vertex IDs are 0 through
15 and every possible minimum distance is at most 15.

The discovered field distinguishes the two uses:

```text
source:      discovered true,  distance 0,  predecessor 16
unreachable: discovered false, distance 16, predecessor 16
```

## 4. Mark after successful enqueue

Use this exact state-change order:

```text
validate the request and graph
enqueue the source
if that succeeds:
    mark the source discovered
    set its distance to 0

while the Queue is not empty:
    dequeue vertex u
    record u in visit order
    inspect u's outgoing neighbors from lower ID to higher ID
    for each neighbor v that is not discovered:
        enqueue v
        if that succeeds:
            mark v discovered
            set distance[v] to distance[u] + 1
            set predecessor[v] to u
```

Do not wait until dequeue to mark a vertex. Two routes could add the same
pending vertex. Do not mark before a possibly failing enqueue. That would
claim that work was arranged when it was not.

## 5. Trace the reveal graph

Outgoing-neighbor lists:

```text
0:[1,2]
1:[3]
2:[3,4]
3:[0]
4:[]
```

An **outgoing neighbor** is the destination of an edge leaving the current
vertex. The notation `0:[1,2]` means edges `0 -> 1` and `0 -> 2` exist.
Brackets contain the neighbor IDs in ascending order.

| Completed processing | Queue, front to back | Newly discovered | Visit order |
|---|---|---|---|
| none | `[0]` | 0 at distance 0 | empty |
| 0 | `[1,2]` | 1 and 2 at distance 1, predecessor 0 | `0` |
| 1 | `[2,3]` | 3 at distance 2, predecessor 1 | `0,1` |
| 2 | `[3,4]` | skip 3; add 4 at distance 2, predecessor 2 | `0,1,2` |
| 3 | `[4]` | skip 0 | `0,1,2,3` |
| 4 | `[]` | none | `0,1,2,3,4` |

The empty brackets `[]` mean no vertex waits.

At `2 -> 3`, vertex 3 is discovered even though it has not yet been
processed. At `3 -> 0`, the source is already discovered. Neither edge
adds work or changes stored state.

## 6. Why the distances are minimum

Three facts work together:

1. every edge contributes exactly one hop;
2. FIFO removal processes smaller distances before larger distances; and
3. first discovery is permanent.

Let `d` stand for the current vertex's distance. When a distance-`d` vertex
first reaches an unseen neighbor, the new route has `d + 1` hops. A route
with fewer hops cannot appear later because all smaller-distance vertices
were already ahead in the Queue.

FIFO alone does not solve a graph with unequal edge costs. Weighted paths
wait for a later module.

## 7. Reconstruct one path

A **path** is a route that does not repeat a vertex. To **reconstruct** a
path means to build it from stored predecessors.
Begin at the destination and follow predecessors backward:

```text
destination 4
predecessor[4] = 2
predecessor[2] = 0
```

The backward sequence is `4,2,0`. Reverse it:

```text
0,2,4
```

This path has two hops, equal to `distance[4]`. A **path certificate** is
checkable evidence: its endpoints are correct, each consecutive edge
exists, and its hop count equals the stored distance.

## 8. Preview two graph representations

An **adjacency matrix** is a square table. Cell `[u][v]` states whether
edge `u -> v` exists. Matrix BFS scans every possible destination in row
`u`. A **representation** is the form used to store a structure in memory.

An **adjacency list** stores only existing outgoing neighbors for each
vertex. This module uses an array of dynamic neighbor arrays, not linked
nodes. **Dynamic** means storage may be obtained while the program runs.
An **allocation** is a block of storage obtained while a program runs.
**Validation** means checking that stored fields satisfy their required
rules. The supplied support owns allocation, sorted insertion, validation,
and cleanup.

Both representations inspect neighbors in ascending ID order, so their
named BFS results match.

## 9. Prepare for the Cognitive Pause

Be ready to:

1. trace Queue, discovery, distance, predecessor, and visit order;
2. explain why a pending vertex must already count as discovered; and
3. reconstruct one path and report one unreachable vertex.

Keep `vocabulary.md` closed until all three pause responses are preserved.
