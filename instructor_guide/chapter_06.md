# Chapter 6. How Not to Get Lost in a Graph

## Starting Question

> "In a graph with loops (cycles), what do we need to remember to follow one path to the end without working on the same vertex twice?"

**Expected Answer:** If students say we need to record the vertices we put into the stack, write it down. We will check the exact time to mark them during the walkthrough.

## Why We Need This

In a tree, there is only one path to a node. In a graph, multiple paths can meet at one vertex and go back to a vertex we already passed. If we just copy the depth-first idea from trees, we might put the same vertex into the stack many times.

We must follow one path to the end, but we shouldn't put a vertex into the stack again if it is already there. So, we record whether each vertex has been discovered or not.

## Board Walkthrough

We use the directed graph from the main text.

```text
0 → 1   0 → 2   1 → 3
2 → 3   3 → 4   4 → 1
5 is not connected to any vertex.

```

Write the stack from bottom to top. Cover the next lines and ask first:

* Prediction 1: After processing 0, what will be left in the stack and in what order?
* Prediction 2: When checking `4 → 1` from 4, what record should we look at?
* Prediction 3: Will 5 be in the result after the stack becomes empty?

| Processed Vertex | Stack | Result |
| --- | --- | --- |
| Before start | `0` | Empty |
| 0 | `2, 1` | `0` |
| 1 | `2, 3` | `0, 1` |
| 3 | `2, 4` | `0, 1, 3` |
| 4 | `2` | `0, 1, 3, 4` |
| 2 | Empty | `0, 1, 3, 4, 2` |

We mark a vertex right after we successfully put it into the stack. A vertex waiting to be taken out is also an already discovered vertex. In the activity of counting connected components in an undirected graph, we start a new search from a vertex that is not marked yet.

## Common First Thoughts

* "We can mark it when we take it out of the stack." But even before taking it out, another edge might meet the same vertex.
* "It's safe to mark it before putting it in." But if putting it in fails, a vertex that isn't actually waiting gets marked.
* "We started at 0, so we saw the whole graph." But 5, which cannot be reached from 0, is not included in a single search.
* "Recursive calls are also what we need to code this time." But the coding focus of this chapter is the repeating (iterative) method using a stack.

## Neutral Questions

* How do the steps of the stack change if we change the time we mark the vertex?
* What state is left at the exact moment putting a vertex into the stack fails?
* How should we choose the starting points for the search to see the whole graph, including vertex 5?

## Vocabulary Rules

**Words we can use:** Directed graph, undirected graph, vertex, edge, loop (cycle), adjacency matrix, adjacency list, connected component, stack, and depth-first search for trees.

**Names we will introduce in this chapter:** Starting vertex, reachability, visit history, discovery, waiting, processing, graph depth-first search using a stack, and counting connected components. We only cover the recursive call method in extended learning.

**Words we won't use yet:** We won't name the next data structure that takes out the first added item first, nor the next search method that looks at the closest vertices first. We also won't talk about the path with the fewest edges yet.

## Final Check

> "Can you explain why we must mark a vertex right after putting it into the stack, and also why 5 is missing from the result when we start at 0?"

**Minimum Expected Answer:** Students should mention that a waiting vertex is already discovered, we don't mark it before a successful insert, and vertex 5 cannot be reached from vertex 0.