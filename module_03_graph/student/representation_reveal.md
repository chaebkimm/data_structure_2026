# Stage B — Formal Names and the Directed Matrix

Open this file only after preserving Stage A.

## 1. Name the model

A **graph** models objects and their direct relationships. One object is a
**vertex**; one direct relationship is an **edge**. A **directed edge** has a
source and a destination. The ordered pair `(u, v)` means `u → v`; reversing
the pair names a different possible edge.

The chapter’s canonical directed graph is:

- vertex 0: Web
- vertex 1: App
- vertex 2: Database
- edge set `{(0, 1), (1, 2), (1, 0)}`

This model may contain cycles longer than one edge or several edges entering
one destination. Those relationships are why it is not restricted like a
tree.

## 2. Translate it to a matrix

An **adjacency matrix** uses one row and one column for every possible vertex
pair. Row `from`, column `to` answers “Does `from → to` exist?” The course
stores the answer as the integer `1` for yes and `0` for no.

| From \ To | 0 | 1 | 2 |
|---:|---:|---:|---:|
| 0 | 0 | 1 | 0 |
| 1 | 1 | 0 | 1 |
| 2 | 0 | 0 | 0 |

Row 1 is `[1, 0, 1]`, so App has two outgoing edges. Column 1 shows edges
entering App. A row and its matching column answer different questions.

## 3. Distinguish active size from capacity

The physical matrix reserves 16 rows and 16 columns. `vertex_count` says how
many indexes are currently active. With a count of 3, only indexes 0, 1, and 2
name vertices. Index 3 is physically inside the array but is not an active
vertex.

```c
#define GRAPH_MAX_VERTICES 16

struct DirectedGraph {
    size_t vertex_count;
    int grid[GRAPH_MAX_VERTICES][GRAPH_MAX_VERTICES];
};
```

This is fixed storage: the grid never grows and no dynamic memory is used.
`grid[from][to]` is the stored directed fact. The representation has only the
two fields shown above.

## 4. State the completed-state invariant

Every valid completed course graph satisfies all these rules:

1. `vertex_count <= GRAPH_MAX_VERTICES`.
2. Active vertex indexes are `0` through `vertex_count - 1`.
3. Every grid entry is exactly `0` or `1`.
4. Every row or column position involving an inactive index is `0`.
5. Every diagonal cell is `0` under the course no-self-loop policy.

Initialization therefore clears the complete 16-by-16 grid, not only the
active square. A rejected operation changes neither metadata nor cells.

## 5. Preview the four operations

- Initialization validates the count, stores it, and clears the full grid.
- Adding a valid non-self edge sets one cell to `1`.
- Removing a valid edge sets one cell to `0`.
- Out-degree counts `1` cells across one active row.

Adding an edge already present and removing an edge already absent are
idempotent: repeating either operation leaves the same valid state. A guarded
direct lookup reads one cell after checking both active indexes.

## 6. Keep comparisons conceptual

An **undirected** relationship can be represented by two opposite directed
connections; its matrix is symmetric. A **weighted** graph stores more than
existence. An **edge list** stores endpoint pairs, while an **adjacency list**
stores neighbors by vertex. These comparisons explain design choices, but
this module implements only the fixed directed, unweighted integer matrix.

## 7. Prepare for individual thinking

Do not open `vocabulary.md` until the five-minute Cognitive Pause has been
completed and preserved.

One representation question:

____________________________________________________________________
