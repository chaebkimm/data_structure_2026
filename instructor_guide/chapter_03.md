# Chapter 3. Storing Relationships in Multiple Directions

## Starting Question

> "How should we store relationships if multiple paths lead to a single item and paths loop back?"

**Expected Answer:** Students should explain that the items and the direct relationships between them must be stored separately.

## Why We Need This

A tree has one root, and every other node has exactly one parent. It also does not allow connections that loop back. If we put relationships with multiple incoming paths or paths going back to previous items into a tree, this rule breaks. We need a "graph" that separates the items from their direct connections.

## Board Walkthrough

First, write down the total number of vertices (points) as `6`. This makes sure that vertex 5, which has no edges (connections), is still kept.

```text
Vertices: 0, 1, 2, 3, 4, 5
Edges: 0→1, 0→2, 1→3, 2→3, 3→4, 4→1

```

An adjacency matrix is read as `[start][end]`. Change the necessary boxes to 1 in the same order as the edge list.

```text
[0][1] = 1, [0][2] = 1
[1][3] = 1, [2][3] = 1
[3][4] = 1, [4][1] = 1
Row 5 and Column 5 are all 0

```

Even if we have `0→1`, `[1][0]` is still 0. Only when showing an undirected edge `{2,4}` separately do we change both `[2][4]` and `[4][2]` to 1 at the same time.

Let's predict:

* Which box in the adjacency matrix shows the connection `4→1`?
* For an undirected edge `{2,4}`, if only `[2][4]` is 1, what else do we need to check?
* If we erase the total number of vertices and leave only the edge list, which vertex will we not know exists?

## Common First Thoughts

* "If there is `0→1`, there must also be `1→0`."
* "If we only have an edge list, vertices with no edges are still saved."
* "An undirected edge only needs one box filled in the matrix."
* "If adding one edge is successful, the entire matrix is correct."

## Neutral Questions

* How did we read `[row][column]` as the start and the end?
* How do we tell the difference between a vertex with no edges and a vertex that does not exist at all?
* After changing one box, which parts of the matrix have we not checked yet?

## Vocabulary Rules

**Words we can use:** Array, list, tree, path, cycle, and valid shape conditions.

**Names we will introduce in this chapter:** Graph, vertex, edge, neighbor, in-degree, out-degree, directed graph, undirected graph, isolated vertex, connected component, edge list, adjacency list, adjacency matrix, mirrored cell, and weighted graph.

**Words we won't use yet:** Depth-first search (DFS), breadth-first search (BFS), visit history, stack, queue, or shortest path.

## Final Check

> "To keep vertex 5 even though it does not appear in the edge list, what must we store separately and why?"

**Minimum Expected Answer:** Students should say that the total number of vertices (6) must be saved separately. Because an edge list only shows the two ends of an active connection, an isolated vertex like 5 will not show up there.