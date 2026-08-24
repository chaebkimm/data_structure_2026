# Chapter 16. Connecting All Vertices at the Lowest Cost

## Starting Question

> "Why is the result of gathering the cheapest paths from one starting point different from the result where the total cost of edges connecting all vertices is the smallest?"

**Expected Answer:** Students should say that finding the cheapest paths from a starting point and finding the smallest sum of edges to connect everything are two completely different goals.

## Why We Need This

Dijkstra's algorithm finds cheap paths from vertex A to each other vertex. The sum of those previous vertex edges (AB, AC, CD, CE) is 13. However, the sum of the edges AB, BC, CD, and CE, which also connects all vertices, is only 10. We need a separate rule for choosing edges to reduce the total connection cost.

The result of connecting all vertices without any loops (cycles) is called a "spanning tree." The one with the smallest sum of edges is called a "minimum spanning tree." The method of looking at all edges in order from cheapest to most expensive is called "Kruskal's algorithm." The method of growing the connection by picking the cheapest edge going outward from the currently connected group is called "Prim's algorithm."

In week 14, we code Kruskal's algorithm all the way to the end. For Prim's algorithm, we only complete limited decision points in the provided code. We put the comparison of the two results and the final integration check into a single submission.

## Board Walkthrough

We use the same edge list for both methods.

```text
ID0 AB4  ID1 AC4  ID2 BC1  ID3 BD5
ID4 CD2  ID5 CE3  ID6 DE3  ID7 AE10

```

Kruskal's evaluates all edges sorted by cost, then by smaller endpoint, larger endpoint, and finally edge ID.

```text
ID2 BC1  Picked   Sum 1
ID4 CD2  Picked   Sum 3
ID5 CE3  Picked   Sum 6
ID6 DE3  Skipped because it makes a cycle
ID0 AB4  Picked   Sum 10
ID1 AC4  Skipped because it makes a cycle
ID3 BD5  Skipped because it makes a cycle
ID7 AE10 Skipped because it makes a cycle

```

`key[v]` is the cost of the single cheapest edge going outward from the current connection to vertex `v`. `A/0` is written in the order of `Vertex/key`. In the provided Prim's code, we only follow these decision points:

```text
A/0: B=4/A, C=4/A, E=10/A
B/4: Pick ID0 AB, C=1/B, D=5/B
C/1: Pick ID2 BC, D=2/C, E=3/C
D/2: Pick ID4 CD, E's same cost 3 stays as is
E/3: Pick ID5 CE

```

Ask these questions before showing the next line:

* After picking ID2 and ID4, which group are the two endpoints of ID5 in?
* When looking at ID6, how do we check the representative roots (leaders) of its two endpoints?
* In Prim's, when D is picked, if E's new candidate cost is the exact same as the current `key`, what do we keep?

## Common First Thoughts

* "All paths from the starting point inside a minimum spanning tree are also the cheapest paths."
* "If an edge is the cheapest overall, we pick it regardless of whether it makes a cycle."
* "Prim's `key` is the total distance added up from the starting point."
* "Prim's and Kruskal's must always pick the exact same edge IDs."

## Neutral Questions

* Which two groups does the edge we are trying to pick right now connect?
* If we add this edge, what kind of path is created between the already selected edges?
* What values must be exactly the same in the two results, and what values can be different?

## Vocabulary Rules

**Words we can use:** Undirected weighted graph, min-heap, old record, edge list, logical edge ID, DSU (Disjoint Set Union), and representative root.

**Names we will introduce in this chapter:** Spanning tree, minimum spanning tree, minimum spanning forest, cut, crossing edge, Prim's algorithm, and Kruskal's algorithm.

**Words we won't use yet:** Full implementation of Prim's algorithm outside the provided code, cheapest paths for all pairs of vertices, or detailed methods for fault-tolerant design.

## Final Check

> "Which edges does Kruskal's pick and in what order, and why do we skip an edge when the representative roots of its two endpoints are the same?"

**Minimum Expected Answer:** Students should mention the sorting rules, checking groups using the DSU, preventing loops (cycles), and finding the lowest total cost of the selected edges.