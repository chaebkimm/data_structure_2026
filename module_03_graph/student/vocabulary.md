# Module 3 Word Reference — Open Only After the Pause

This reference contains the 30 required Module 3 terms. It is released after
the five-minute individual activity. The lab explains function-specific C
details where they are used; those details are not extra vocabulary targets.

1. **graph** — A model of objects and their relationships.

2. **vertex** — One object in a graph. The plural is vertices.

3. **edge** — One direct relationship between two vertices.

4. **directed graph** — A graph whose edges have a starting direction and an
   ending direction.

5. **undirected graph** — A graph whose edges do not distinguish a start from
   an end. This module compares the idea but implements a directed graph.

6. **source** — The vertex where a directed edge starts.

7. **destination** — The vertex where a directed edge ends.

8. **degree** — The number of edges touching a vertex in an undirected graph.

9. **out-degree** — The number of directed edges leaving a vertex; in the
   matrix, count `1` cells across its row.

10. **in-degree** — The number of directed edges entering a vertex; inspect
    its column. The concept is required, but no in-degree function is required.

11. **path** — A sequence that follows edges without repeating a vertex.

12. **cycle** — A route that returns to its starting vertex without repeating
    another vertex.

13. **self-loop** — An edge from a vertex to itself. The course implementation
    rejects adding one.

14. **weight** — A number attached to an edge, such as cost, delay, or
    distance.

15. **unweighted graph** — A graph that records edge existence without an
    edge weight. The course matrix is unweighted.

16. **edge list** — A representation that stores one endpoint pair per edge.

17. **adjacency list** — A representation that stores neighbors for each
    vertex.

18. **adjacency matrix** — A grid whose row `u`, column `v` records whether
    the directed edge `u → v` exists.

19. **connected component** — A maximal group joined by routes in an
    undirected graph. It is a comparison concept, not a directed lab operation.

20. **isolated vertex** — An active vertex with no incoming or outgoing edge.

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

29. **`size_t`** — A nonnegative whole-number C type used for counts and
    indexes.

30. **`GRAPH_MAX_VERTICES`** — The fixed name for this module’s capacity of 16
    vertices.
