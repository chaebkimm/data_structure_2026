# Stage B — Five-Minute Cognitive Pause

Read the starting definitions and graph with the instructor before timing
begins. Then use no notes, slides, classmates, vocabulary file, or coding
tools for five minutes.

You may draw, type, dictate, or answer in numbered sentences. An approved
extended-time or asynchronous version uses the same graph and exactly the
same three sections. Speed, handwriting, and drawing quality are not
assessed. Preserve your first response when correction begins.

## Starting definitions

**Breadth-first search (BFS)** processes vertices in nondecreasing hop
count from one **source**, or starting vertex. A **hop** follows one edge.

A vertex is **discovered** after it is successfully added to the Queue.
A **Queue** removes the earliest-added waiting item first. The
**frontier** is the Queue of discovered vertices still waiting to be
processed. List it from front to back.

The **distance** of a discovered vertex is its minimum hop count from the
source. Its **predecessor** is the previous vertex on the route fixed at
first discovery. The source has distance 0 and no predecessor.
**Unreachable** means no directed route leads from the source.

Inspect outgoing neighbors from lower vertex ID to higher vertex ID.

## Pause graph

```text
0:[1,3]
1:[2,4]
2:[0]
3:[2,5]
4:[5]
5:[]
6:[]
```

Exact linear edges:

```text
1. 0 -> 1
2. 0 -> 3
3. 1 -> 2
4. 1 -> 4
5. 2 -> 0
6. 3 -> 2
7. 3 -> 5
8. 4 -> 5
9. Vertex 5 has no outgoing edge.
10. Vertex 6 has no entering or leaving edge.
```

Begin at source 0. Enqueue and then mark the source. Dequeue and record one
vertex at a time. Enqueue an unseen neighbor and mark it immediately after
that enqueue succeeds.

## Target 1 — Trace Queue and state

State:

1. the initial Queue;
2. the complete Queue immediately after processing 0;
3. the complete Queue immediately after processing 1;
4. the complete Queue immediately after processing 3; and
5. the final visit order, distances, and predecessors for vertices 0
   through 6.

Response:

____________________________________________________________________

____________________________________________________________________

## Target 2 — Stop duplicate waiting work

When vertex 3 checks edge `3 -> 2`, state:

1. whether vertex 2 is discovered;
2. where vertex 2 is at that moment;
3. the required action for the edge; and
4. what duplicate work could occur if discovery waited until dequeue.

Response:

____________________________________________________________________

____________________________________________________________________

## Target 3 — Reconstruct and report

State:

1. the predecessor chain from vertex 5 backward to source 0;
2. the forward path from 0 to 5;
3. its hop count; and
4. the correct result for vertex 6.

Response:

____________________________________________________________________

____________________________________________________________________

## Compare after time is called

When the instructor releases the expert model:

1. preserve your initial response;
2. check reasoning that remains correct;
3. label each correction `Queue`, `discovery`, `distance`,
   `predecessor`, `path`, or `unreachable`; and
4. finish the sentence below.

Correction:

____________________________________________________________________

The evidence that changed or strengthened my thinking was:

____________________________________________________________________
