# Student Textbook — Graph Breadth-First Search

## Essential question

> Which system is reachable in the fewest communication hops when
> relationships may branch, merge, and cycle?

## 1. The problem

A **graph** stores items called vertices and direct relationships called
edges. A **source** is the selected starting vertex. A **hop** follows one
edge. In an **unweighted graph**, every edge contributes one hop.

Graphs can merge or cycle, so copying tree traversal can schedule the same
work repeatedly.

**Breadth-first search (BFS)** processes vertices in nondecreasing hop
count, meaning the count never gets smaller as work proceeds. It answers
minimum-hop questions on an unweighted graph.

## 2. The four pieces of state

A **Queue** removes the earliest-added item first. This is **FIFO**, meaning
first in, first out. The **frontier** is the Queue of reached vertices still
waiting to be processed.

A vertex is **discovered** after its first successful enqueue. It is
**processed** after dequeue, when its ID enters visit order. A discovered
vertex can still be pending.

Three arrays and one output sequence record the search:

An **ID** is an identifying number. In `discovered[v]`, the letter `v`
stands for one vertex ID and square brackets select that array position.

- `discovered[v]` says whether vertex `v` was successfully enqueued;
- `distance[v]` stores its minimum hop count from the source;
- `predecessor[v]` stores the previous vertex on the first fixed route; and
- `visit_order` stores dequeue order.

The package supports IDs 0 through 15. It uses sentinel 16 for no distance
or no predecessor. A **sentinel** is a stored value chosen to mean a special
case.

```text
source:      discovered true,  distance 0,  predecessor 16
unreachable: discovered false, distance 16, predecessor 16
```

## 3. The exact procedure

Inspect outgoing neighbors from lower ID to higher ID. In the procedure,
`u` means the current vertex and `v` means one neighbor. To **validate**
means to check that stored fields obey their rules.

```text
validate the request and graph
prepare a temporary result filled with sentinels

enqueue the source
after success, discover it at distance 0

while dequeue succeeds:
    remove vertex u
    append u to visit order

    for each outgoing neighbor v in ascending order:
        if v is not discovered:
            enqueue v
            after success:
                discover v
                distance[v] = distance[u] + 1
                predecessor[v] = u

publish the temporary result
```

Mark after successful enqueue. Marking earlier records failed work; marking
only at dequeue permits duplicate pending work.

## 4. Canonical example

**Canonical** means the shared course example used for later checks.
The notation `0:[1,2]` means edges `0 -> 1` and `0 -> 2` exist. Brackets
list outgoing neighbor IDs.

```text
0:[1,2]  1:[3,4]  2:[4,5]  3:[6]
4:[6]    5:[4]    6:[1]    7:[]
```

Queue states are front to back:

```text
initial [0]
after 0 [1,2]
after 1 [2,3,4]
after 2 [3,4,5]
after 3 [4,5,6]
after 4 [5,6]
after 5 [6]
after 6 []
```

The result is:

```text
visit order  0,1,2,3,4,5,6
discovered   T,T,T,T,T,T,T,F
distance     0,1,1,2,2,2,3,16
predecessor  16,0,0,1,1,2,3,16
```

`T` means true and `F` means false. Vertex 7 is unreachable from source 0.

The rule skips `2 -> 4`, `4 -> 6`, `5 -> 4`, and `6 -> 1` because each
destination is already discovered. Stored state is not overwritten.

## 5. Why the hop counts are minimum

The guarantee uses three facts together:

1. each edge adds exactly one hop;
2. FIFO processes smaller distances before larger distances; and
3. first discovery is permanent.

Let `d` stand for the current distance. Suppose a distance-`d` vertex first
reaches unseen neighbor `v`. The new
route has `d + 1` hops. A shorter route cannot appear later because every
smaller-distance vertex was already ahead in the Queue.

FIFO alone does not solve unequal edge costs. Weighted shortest paths need
a different rule later in the course.

## 6. Reconstruct a path

A **path** is a route that does not repeat a vertex. To **reconstruct**
means to build a forward path from predecessor records.
Start at the destination and follow backward:

```text
6 <- 3 <- 1 <- 0
```

Reverse the sequence:

```text
0 -> 1 -> 3 -> 6
```

The path has three hops, equal to `distance[6]`. A **path certificate** is
checkable evidence: confirm both endpoints, every consecutive graph edge,
and the hop count.

Other three-hop paths to 6 exist. Ascending neighbor order selects one
**deterministic** route, meaning the same input and rule choose it again; it
does not make that route unique.

A path from source 0 to itself is `[0]` and has zero hops. A request for
unreachable vertex 7 reports unreachable and leaves the program's previous
output path unchanged.

## 7. Disconnected graphs

A one-source search may finish while other vertices remain undiscovered.
That is a successful result, not a traversal error.

A **BFS forest** repeats the search from each still-undiscovered vertex
while keeping one shared discovered array.
For an undirected graph, each resulting tree identifies one **connected
component**, or separate group whose vertices have undirected routes to one
another.

For directed graphs, call the result a traversal forest. “Weak” connection
ignores edge directions; “strong” connection requires directed routes both
ways. The forest alone proves neither. Forest code is not required here.

## 8. Matrix and adjacency-list storage

An **adjacency matrix** is a square table. Cell `[u][v]` says whether edge
`u -> v` exists. Processing one matrix vertex scans all `V` possible
destinations. `V` means vertices currently in the graph.

An **adjacency list** stores only existing outgoing neighbors. This package
uses one dynamic array per source vertex. A **dynamic array** uses adjacent
memory slots in an **allocation**, a storage block obtained while a program
runs.

Each neighbor row stores:

```text
data      address of its owned destination storage
size      currently stored destination count
capacity  allocated destination slots
```

**Ownership** is responsibility for releasing storage. Supplied operations
handle growth, ordered insertion, checking, and cleanup. Students do
not implement that memory management.

Let `E` mean edge count. `O(x)`, read “order x,” means growth is bounded in
proportion to `x`.

| Question | Matrix | Adjacency list |
|---|---:|---:|
| Representation storage | `O(V²)` | `O(V+E)` |
| Public BFS time | `O(V²)` | `O(V+E)` |
| BFS auxiliary space | `O(V)` | `O(V)` |

The raised 2 in `V²` means `V` multiplied by `V`. **Auxiliary space** is
temporary working storage separate from the graph and returned result.

Construction is separate from traversal. Converting a matrix by scanning
all its cells costs `O(V²)` even if later list searches cost `O(V+E)`.
Queue enqueue and dequeue remain `O(1)`, meaning constant time, under a
**valid-state precondition**, a required assumption that Queue rules
already hold. They do not run a full Queue scan each time.

## 9. Contracts and safe interpretation

A **contract** states accepted inputs, results, changes, and preserved
state. A **caller** is code asking a function to run. Both BFS operations
validate the complete graph and build a temporary **candidate**, or
possible result. They **commit** it to caller output only
after full success. Path reconstruction follows the same rule.

**Malformed** means breaking stored rules. Test empty, cyclic, converging,
disconnected, unreachable, malformed, and Queue-limit cases. All named
matrix and sorted-list result values must match.

The synthetic communication graph is only a model. Minimum modeled hops
does not prove real communication, permission to act, the presence or
usability of a flaw, an actual takeover, its chance, or its danger. Do not
use this lab to scan a live system.
