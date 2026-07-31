# Stage C — Investigation Worksheet: Graph Breadth-First Search

Name: ____________________________  
Date: ____________________________

Complete and preserve Sections A through F before opening Stage D.
Sections G through I are later testing, failure-investigation, and synthesis
work.

## Quick reference

A **source** is the starting vertex. A **hop** follows one edge.
**Breadth-first search (BFS)** processes vertices in nondecreasing hop
count. A **Queue** removes the earliest-added item first. The **frontier**
is the Queue of discovered vertices still waiting.

A vertex is **discovered** immediately after its first successful enqueue.
It is **processed** when dequeued and recorded. `distance[v]` stores the
minimum hop count to vertex ID `v`. `predecessor[v]` stores the prior vertex
on the route fixed at first discovery.

Valid IDs are 0 through 15. Sentinel 16 means no distance or no
predecessor. A **sentinel** is a stored value representing a special case.
List Queues front to back and inspect outgoing neighbors in ascending ID
order.

## Canonical graph

**Canonical** means the shared course example used for later checks.

| ID | Synthetic label | Ascending outgoing neighbors |
|---:|---|---|
| 0 | Gateway | 1, 2 |
| 1 | Web | 3, 4 |
| 2 | Admin | 4, 5 |
| 3 | Database | 6 |
| 4 | LogCollector | 6 |
| 5 | VPN | 4 |
| 6 | Monitor | 1 |
| 7 | Archive | none |

Exact edges:

```text
0 -> 1   0 -> 2   1 -> 3   1 -> 4   2 -> 4
2 -> 5   3 -> 6   4 -> 6   5 -> 4   6 -> 1
```

This is a synthetic directed, unweighted graph. **Directed** means each
edge works only in its stated direction. **Unweighted** means every edge
contributes one hop.

## A. Apply the discovery invariant

An **invariant** is a rule that remains true at each completed loop step:

> Every queued vertex is discovered but not processed; every processed
> vertex is discovered; and no vertex is enqueued more than once.

### A1. Initialize source 0

After the source enqueue succeeds, state:

```text
Queue:
discovered vertices:
distance[0]:
predecessor[0]:
visit order:
```

Why must discovery follow, rather than precede, successful enqueue?

____________________________________________________________________

### A2. Process vertex 0

State the complete Queue, newly discovered vertices, their distances and
predecessors, and visit order.

____________________________________________________________________

### A3. Process vertex 1

State the same facts after processing vertex 1.

____________________________________________________________________

### A4. Distinguish four meanings

Explain each phrase in one sentence:

```text
discovered:
processed:
frontier:
first discovery is permanent:
```

## B. Complete the canonical trace

### B1. Queue after every processed vertex

```text
initial:
after 0:
after 1:
after 2:
after 3:
after 4:
after 5:
after 6:
```

### B2. Final result

```text
vertex_count:
source:
visit_count:
visit_order:
discovered[0..7]:
distance[0..7]:
predecessor[0..7]:
```

The notation `[0..7]` means array positions 0 through 7, inclusive.

### B3. Explain four skipped edges

Complete the table.

| Edge | Destination state when checked | Required action | Fields changed |
|---|---|---|---|
| `2 -> 4` | | | |
| `4 -> 6` | | | |
| `5 -> 4` | | | |
| `6 -> 1` | | | |

Why must a pending destination already count as discovered?

____________________________________________________________________

## C. Explain minimum hops and reconstruct paths

### C1. Justify first discovery

Explain how these three facts work together:

1. every edge adds one hop;
2. the Queue removes the earliest-added item; and
3. first discovery is permanent.

____________________________________________________________________

____________________________________________________________________

Why is FIFO alone not a guarantee for unequal edge costs?

____________________________________________________________________

### C2. Reconstruct the path to 6

State:

```text
backward predecessor sequence:
forward path:
hop count:
distance[6]:
```

A **path certificate** is checkable evidence. Verify the source,
destination, every consecutive edge, and hop count.

____________________________________________________________________

### C3. Explain an equal-hop alternative

Give a different minimum-hop path from 0 to 6. Why does the stored
predecessor route remain correct?

____________________________________________________________________

### C4. Handle source and unreachable destinations

State the path and hop count from 0 to 0.

____________________________________________________________________

State the path-operation result for destination 7 and what happens to the
caller's previous path output.

____________________________________________________________________

Why can predecessor 16 alone not distinguish the source from an
unreachable vertex?

____________________________________________________________________

## D. Reason about disconnected graphs

### D1. Interpret canonical vertex 7

Does the one-source BFS call succeed or fail when 7 remains undiscovered?
Explain.

____________________________________________________________________

### D2. Trace an undirected forest on paper

An **undirected edge** connects both ways. A **connected component** is one
separate group whose vertices have undirected routes to one another.
The braces in `{0,1}` name one undirected edge. **Isolated** means having no
edge. A **root** is the first vertex of one forest tree.

Use vertices 0 through 6 and edges:

```text
{0,1}  {1,2}  {3,4}  {4,5}
```

Vertex 6 is isolated. Scan possible roots from 0 through 6. Keep one shared
discovered array.

```text
complete forest order, with | between trees:
root IDs:
component sets:
component count:
```

Why must the discovered array remain shared across roots?

____________________________________________________________________

### D3. Use precise directed language

**Weak connection** ignores edge direction. **Strong connection** requires
directed routes both ways between every pair in a group.

Why must the trees from a directed outer scan not automatically be called
weakly or strongly connected components?

____________________________________________________________________

## E. Apply the public contract

A **contract** states accepted inputs, output, changes, and preserved state.
A **caller** is code asking a function to run. An **output parameter** is
caller-provided storage where a function writes a result.

```c
GraphBfsStatus graph_bfs_matrix(
    const Graph *graph,
    size_t source_vertex,
    size_t queue_limit,
    GraphBfsResult *out_result);

GraphBfsStatus graph_bfs_list(
    const GraphAdjList *graph,
    size_t source_vertex,
    size_t queue_limit,
    GraphBfsResult *out_result);

GraphBfsStatus graph_bfs_reconstruct_path(
    const GraphBfsResult *result,
    size_t destination_vertex,
    GraphBfsPath *out_path);
```

`const` means a function may inspect the graph through that pointer but may
not change it. `size_t` is C's nonnegative type for sizes and indexes. A
**status code** is a named result that reports success or one failure kind.
**Malformed** means stored fields break their required rules.

### E1. Match cases to statuses

Use:

```text
GRAPH_BFS_OK
GRAPH_BFS_INVALID_ARGUMENT
GRAPH_BFS_OUT_OF_RANGE
GRAPH_BFS_INVALID_GRAPH
GRAPH_BFS_LIMIT
GRAPH_BFS_UNREACHABLE
GRAPH_BFS_INVALID_RESULT
```

```text
missing required output:
malformed graph:
inactive source:
requested Queue limit 17:
Queue becomes full at selected limit:
path destination is undiscovered:
stored result breaks its rules:
```

### E2. Explain candidate and commit

A **candidate** is a temporary possible output. To **commit** means to copy
it to the caller after required work succeeds.

Why must every failure preserve the caller's complete previous result or
path?

____________________________________________________________________

How would a sentinel-filled output help test preservation?

____________________________________________________________________

### E3. State the result-validator boundary

Which relationships can `graph_bfs_result_validate` check without reading
a graph?

____________________________________________________________________

Why can it not prove that each predecessor edge existed?

____________________________________________________________________

### E4. Analyze Queue limits

Find the canonical maximum pending count.

____________________________________________________________________

State the result at limit 3.

____________________________________________________________________

At limit 2, identify the current vertex, already waiting vertices,
successful new enqueue, and failed enqueue. What happens to caller output?

____________________________________________________________________

### E5. Explain ownership

**Ownership** is responsibility for releasing storage. Which structure owns
dynamic neighbor-row allocations? **Inline** Queue storage is an array
stored directly inside the Queue object. Which Queue storage is inline? What
cleanup does each require?

____________________________________________________________________

## F. Compare graph representations and costs

A **representation** is the form used to store a structure.
An **adjacency matrix** stores one Boolean cell for every possible from/to
pair. An **adjacency list** stores existing outgoing neighbors for each
vertex. This module's list is an array of dynamic neighbor arrays, not
linked nodes.

A **dynamic array** uses adjacent memory slots from an allocation obtained
while a program runs.

```c
typedef struct {
    size_t *data;
    size_t size;
    size_t capacity;
} GraphNeighborArray;
```

### F1. Compare vertex 2

Which matrix cells are scanned for vertex 2? Which are true?

____________________________________________________________________

Which list entries are live for vertex 2? Explain `data`, `size`, and
`capacity`.

____________________________________________________________________

### F2. Complete the cost comparison

Let `V` mean active vertex count and `E` mean edge count. `O(x)`, read
“order x,” describes how a bound grows with `x`. `V²` means `V` multiplied
by `V`. **Auxiliary space** is temporary working storage separate from the
graph and returned output.

| Quantity | Matrix | Adjacency list |
|---|---:|---:|
| Representation storage | | |
| Public BFS time | | |
| BFS auxiliary space | | |

### F3. Separate construction from traversal

A **valid-state precondition** is a required assumption that the Queue
already obeys its representation rules.

Why is matrix-to-list conversion not part of the list BFS traversal cost?
What is its cost if it scans every matrix cell?

____________________________________________________________________

The explicit full Queue validator scans live Queue IDs. **Constant-time**
means the work bound does not grow with Queue size. Why do enqueue and
dequeue use constant-time checks under a valid-state precondition instead
of calling that full validator every time?

____________________________________________________________________

### F4. State the safe interpretation

List four real-world claims that a minimum-hop result does not prove.

____________________________________________________________________

Why must this exercise use only synthetic, approved data?

____________________________________________________________________

## G. Design exactly three tests — later work

An **assertion** is a test check expected to be true. **Sparse** means
having few stored edges compared with the possible edge count.

### G1. Cyclic and converging routes

Design one graph and exact assertions proving each reached vertex appears
once and first distances/predecessors are permanent.

____________________________________________________________________

### G2. Reachable and unreachable path behavior

Design one reachable path-certificate check and one unreachable-output
preservation check.

____________________________________________________________________

### G3. Matrix/list equivalence on disconnected input

Represent one sparse disconnected graph both ways. State every named result
field that must match.

____________________________________________________________________

## H. Analyze a bounded autopsy — later work

An **autopsy** is a careful investigation of a supplied failure.

Use this separate graph:

```text
0:[1,2]  1:[3,4]  2:[3,4]  3:[0]  4:[]
```

### H1. Predict the correct state

With enqueue-time discovery, state the Queue after processing 2, complete
visit order, and predecessors of 3 and 4.

____________________________________________________________________

### H2. Predict delayed discovery

If discovery waits until dequeue, what duplicate records can enter after
processing 2? Which predecessor fields could be overwritten?

____________________________________________________________________

### H3. Separate safety from correctness

Why can fixed bounds and checked indexes coexist with wrong graph-search
state? State the smallest repair without deleting a safety check.

____________________________________________________________________

### H4. Change neighbor order

If both representations inspect higher IDs first, which results may change?
Which results must remain the same?

____________________________________________________________________

## I. Complete Spiral 3 synthesis — later work

### I1. Interpret pending work

State what one pending item means in:

1. a Module 7 event Queue;
2. Module 8 tree BFS; and
3. Module 9 graph BFS.

____________________________________________________________________

### I2. State the graph addition

What state does graph BFS need that a valid tree did not need? Why?

____________________________________________________________________

### I3. Correct an incomplete claim

Correct:

> FIFO always finds a shortest path.

____________________________________________________________________

### I4. Exit reflection

My strongest evidence for the minimum-hop claim is:

____________________________________________________________________

One labeled correction to my Stage A reasoning is:

____________________________________________________________________
