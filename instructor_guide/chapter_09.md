# Chapter 9. Finding the Path with the Fewest Edges

## Starting Question

> "To find the path with the fewest edges in a graph, what do we need to remember for each vertex?"

**Expected Answer:** If students say we need to remember whether it was put in the queue, how many moves it took from the starting point, and which vertex it came from, write it down.

## Why We Need This

In a tree, there is only one path to a node. In a graph, multiple paths can meet at one vertex and go back to a vertex we already passed. If we just copy the level-by-level traversal of a tree, we will put the same vertex in many times.

To process the closest vertices first, we need a queue. We also need a record so we do not put the same vertex in again. To make the path later, we must also keep track of where it first came from.

## Board Walkthrough

The starting vertex of the graph in the text is 0.

```text
0:[1,2]  1:[3,4]  2:[4,5]  3:[6]
4:[6]    5:[4]    6:[1]    7:[]

```

We attach `(distance, previous vertex)` to the newly discovered vertex. Cover the next lines and ask first:

* Prediction 1: After processing 0, what two values will be recorded for 1 and 2?
* Prediction 2: When 2 meets 4, how will the queue and 4's record change?
* Prediction 3: If we follow 6's previous vertices backward, what numbers will come out?

| Processed Vertex | Queue | Newly Fixed Record |
| --- | --- | --- |
| Before start | `0` | `0:(0, 16)` |
| 0 | `1, 2` | `1:(1, 0)`, `2:(1, 0)` |
| 1 | `2, 3, 4` | `3:(2, 1)`, `4:(2, 1)` |
| 2 | `3, 4, 5` | `5:(2, 2)` |
| 3 | `4, 5, 6` | `6:(3, 3)` |
| 4 | `5, 6` | None |
| 5 | `6` | None |
| 6 | Empty | None |

Since 4, which we met from 2, is already discovered, we do not put it in again. Reversing `6 ← 3 ← 1 ← 0` becomes `0 → 1 → 3 → 6`. The search finishes normally with 7 in an undiscovered state.

## Common First Thoughts

* "We can mark it as discovered when we take it out of the queue." But while it is waiting, another edge could put the same vertex in again.
* "If we meet 4 later, we can just change the distance and previous vertex." But when we count every edge as one move, we fix the first discovery record and do not change it.
* "If we can't reach 7, the whole search fails." But a vertex that cannot be reached just stays in the normal result as undiscovered.
* "Even if each edge has a different cost, the same queue can find the cheapest path." But a regular queue does not compare the sizes of those costs.

## Neutral Questions

* The moment vertex 2 meets 4, what records do we need to check?
* What is left in vertex 7's discovery status, distance, and previous vertex, respectively?
* How can we make the order from 0 to 6 by only looking at the previous vertex array?
* How can we compare the results of searching the same graph using two different storage methods?

## Vocabulary Rules

**Words we can use:** Graph, vertex, edge, loop (cycle), starting vertex, reachability, discovery and processing, queue, and breadth-first search for trees.

**Names we will introduce in this chapter:** One hop, unweighted graph, graph breadth-first search, `discovered`, `distance`, `predecessor`, first discovered distance, and path reconstruction.

**Words we won't use yet:** We won't use the names for the procedure in a later chapter that compares different costs for each edge to fix the cheapest path. We also won't name the next data structure that picks what to take out first using a separate rule.

## Final Check

> "Can you explain why vertex 6's distance is fixed at 3, and the process of making `0 → 1 → 3 → 6` using the previous vertex records?"

**Minimum Expected Answer:** Students should mention that the queue processes smaller distances first, the first discovery record is not changed, and we reverse `6 ← 3 ← 1 ← 0`.