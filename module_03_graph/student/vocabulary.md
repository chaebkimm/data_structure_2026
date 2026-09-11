# Module 3 Word Reference — Open Only After the Pause

This reference contains the 30 required Module 3 terms. Read those numbered
entries after preserving the five-minute individual activity and completing
calibration. Leave the supplemental textbook terms at the end until Stage D,
after preserving the Stage C attempt. The lab explains function-specific C
details where they are used; those details are not extra vocabulary targets.

1. **graph** — A model of objects and their relationships.

2. **vertex** — One object in a graph, such as an SNS account. The plural is
   vertices.

3. **edge** — One direct relationship between two vertices. Here `u → v`
   means account `u` follows account `v`.

4. **directed graph** — A graph whose edges distinguish a source vertex from
   a destination vertex.

5. **undirected graph** — A graph whose edges do not distinguish a start from
   an end. This module compares the idea but implements a directed graph.

6. **source** — The vertex where a directed edge starts; the follower in the
   SNS model.

7. **destination** — The vertex where a directed edge ends; the followed
   account in the SNS model.

8. **degree** — The number of edges touching a vertex in an undirected graph.

9. **out-degree** — The number of directed edges leaving a vertex; in the
   matrix, count `1` cells across its row. This is the account's follow count.

10. **in-degree** — The number of directed edges entering a vertex; inspect
    its column. This is the account's follower count. The concept is required,
    but no in-degree function is required.

11. **path** — A sequence that follows edges without repeating a vertex.
    Directed paths respect arrows. A follow path does not automatically
    deliver the last account's posts to the first account's feed.

12. **cycle** — A route that returns to its starting vertex without repeating
    another vertex.

13. **self-loop** — An edge from a vertex to itself. The course implementation
    rejects adding one.

14. **weight** — A number attached to an edge, such as an interaction count.

15. **unweighted graph** — A graph that records edge existence without an
    edge weight. The course matrix is unweighted.

16. **edge list** — A representation that stores one endpoint pair per edge.

17. **adjacency list** — A representation that stores neighbors for each
    vertex; outgoing neighbors are the accounts that vertex follows here.

18. **adjacency matrix** — A grid whose row `u`, column `v` records whether
    the directed edge `u → v` exists.

19. **connected component** — A maximal group joined by routes in an
    undirected graph. Maximal means no further vertex can join the group
    while preserving connectivity. Directed connectivity is discussed in
    Stage D; computing components is not a lab operation.

20. **isolated vertex** — An active vertex with no incoming or outgoing edge.
    Nuri is isolated. Dae is not isolated before Sora unfollows Dae.

21. **symmetric matrix** — A matrix whose values mirror across the diagonal.
    An undirected adjacency matrix is symmetric; the implemented directed
    matrix need not be.

22. **row** — A horizontal line of matrix cells. A graph row records outgoing
    edges from its vertex.

23. **column** — A vertical line of matrix cells. A graph column records edges
    entering its vertex.

24. **grid cell** — One position selected by a row index and column index. The
    course stores only the integer `0` or `1` in each cell.

25. **diagonal** — Cells whose row and column indexes are equal. They remain
    `0` under the course no-self-loop rule.

26. **two-dimensional array** — An array of rows, written with two bracketed
    indexes in C.

27. **active vertex** — A vertex whose index is less than `vertex_count`.

28. **inactive row or column** — Physically reserved grid space involving an
    index that is not an active vertex. Every such cell must remain `0`.

29. **`size_t`** — An unsigned integer C type used for counts and indexes.
    Values can still exceed the active count or capacity and need checking.

30. **`GRAPH_MAX_VERTICES`** — The fixed name for this module’s capacity of 16
    vertices.

## Stage D supplement — Read after the Stage C attempt

Read these with either `textbook.md` or `textbook_korean.md` during Stage D.
They explain the SNS follower example without changing the 30 required terms
or adding C functions or student-authored tests.

- **maximal** — Cannot be expanded while preserving the required property.
  This does not mean the largest group in the graph.

- **weakly connected component** — A maximal group connected by paths when
  arrow directions are ignored. Accounts can belong to one weak component
  even when there is no directed path from one account to another.
- **strongly connected component** — A maximal group in which every account
  can reach every other account along directed paths. This need not mean
  every pair follows each other directly. A single account can be a component
  without a self-loop.
