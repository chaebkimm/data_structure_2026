# Chapter 12. Finding the Path with the Smallest Cost

## Starting Question

> "If the path with the fewest edges and the path with the smallest total cost are different, which vertex's path should we check next?"

**Expected Answer:** Students should say that we must take out the waiting record with the smallest cost found so far, and record cheaper candidates that pass through that vertex.

## Why We Need This

Breadth-first search counts the number of edges. If each edge has a different cost, a path with three edges like `A-C-D-E` (cost 6) can be cheaper than a path with just one edge like `A-E` (cost 14). We need a process that updates the total sum of the cost instead of just counting the number of edges.

We take out the vertex with the smallest cost found so far. If there is a cheaper candidate path going through that vertex, we update the record. This checking step is called "relaxation." The records waiting to be processed are called the "frontier." This overall flow is called "Dijkstra's Algorithm."

In the week 10 practice, we only complete the core parts of relaxation and the frontier within the provided framework of a weighted graph, heap, and path reconstruction. We will not add a separate full practice project.

## Board Walkthrough

Let's look at the following directed edges in the written order:

```text
A->B 9   A->C 2   A->E 14
B->D 0   B->E 8
C->B 2   C->D 2
D->E 2

```

We write the heap records in the order of `Vertex/Cost`. `dist` is the currently cheapest cost, and `pred` is the vertex right before it. `INF` is a mark showing we haven't found a path yet. We change these values line by line.

```text
Take out A/0: B=9, C=2, E=14
Take out C/2: B=4, D=4
Take out B/4: D candidate 4 is the same, E=12
Take out D/4: E=6
Take out E/6: no outgoing edges
Take out B/9: old
Take out E/12: old
Take out E/14: old

```

This is the final state:

```text
dist       0, 4, 2, 4, 6, INF
pred       -, C, A, C, D, -
Confirmed  A, C, B, D, E

```

Ask these questions before showing the next line:

* When we take out `C/2`, what are the candidate costs for B and D?
* If D's candidate cost going through B is exactly the same as its current value, what record is kept?
* When we take out `B/9`, what value do we compare it with to decide that it is an old record?

## Common First Thoughts

* "Fewer edges mean the total cost is also smaller."
* "Every record taken out of the heap is the current minimum distance."
* "A candidate with the exact same cost still changes the previous vertex and the heap record."
* "Even if there are negative costs, we can just fix the smallest current value as it is."

## Neutral Questions

* What do the current heap records and the `dist` array each show?
* After calculating the candidate cost, which values and actions change?
* What decides whether we should look at the outgoing edges from the taken-out record?

## Vocabulary Rules

**Words we can use:** Weighted graph, breadth-first search, previous vertex, path reconstruction, priority queue, and min-heap.

**Names we will introduce in this chapter:** Starting point, temporary distance, relaxation, frontier, lazy duplication, old record, and Dijkstra's algorithm.

**Words we won't use yet:** Other procedures that solve negative edges, paths for all pairs of vertices, or the total connection cost from Chapter 16.

## Final Check

> "Even though B's cost dropped from 9 to 4, why do we leave `B/9` in there and still get the correct answer?"

**Minimum Expected Answer:** Students should mention the reason for adding a new record instead of finding and changing the old one, the comparison between the taken-out value and the current `dist`, and the action of skipping old records.