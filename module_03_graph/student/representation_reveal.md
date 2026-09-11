# Stage B — Formal Names and the Follower Matrix

Open this file only after preserving Stage A.

## 1. Name the model

A **graph** models objects and their direct relationships. One object is a
**vertex**; one direct relationship is an **edge**. A **directed edge** has a
source and a destination. The ordered pair `(u, v)` means `u → v`; reversing
the pair names a different possible edge.

In this SNS graph, a vertex is an account. The source is the follower and the
destination is the account being followed. The chapter’s canonical graph is:

- vertex 0: Mina
- vertex 1: Joon
- vertex 2: Sora
- vertex 3: Dae
- vertex 4: Hana
- vertex 5: Leo
- vertex 6: Nuri
- edge set `{(0, 1), (1, 2), (2, 0), (2, 3), (4, 5), (5, 4)}`

This model may contain cycles longer than one edge or several edges entering
one destination. Those relationships are why it is not restricted like a
tree. Following an arrow reads a follow relationship; it does not describe a
post being delivered to a feed.

## 2. Translate it to a matrix

An **adjacency matrix** uses one row and one column for every possible vertex
pair. Row `from`, column `to` answers “Does `from → to` exist?” The course
stores the answer as the integer `1` for yes and `0` for no.

| Follower \ Followed | 0 | 1 | 2 | 3 | 4 | 5 | 6 |
|---:|---:|---:|---:|---:|---:|---:|---:|
| 0 Mina | 0 | 1 | 0 | 0 | 0 | 0 | 0 |
| 1 Joon | 0 | 0 | 1 | 0 | 0 | 0 | 0 |
| 2 Sora | 1 | 0 | 0 | 1 | 0 | 0 | 0 |
| 3 Dae | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
| 4 Hana | 0 | 0 | 0 | 0 | 0 | 1 | 0 |
| 5 Leo | 0 | 0 | 0 | 0 | 1 | 0 | 0 |
| 6 Nuri | 0 | 0 | 0 | 0 | 0 | 0 | 0 |

Row 2 is `[1, 0, 0, 1, 0, 0, 0]`, so Sora follows two accounts: her
**out-degree** is 2. Column 2 has one `1`, so Sora has one follower: her
**in-degree** is 1. A row and its matching column answer different questions.

Mina follows Joon, but Joon does not directly follow Mina. Thus `grid[0][1]`
is `1` while `grid[1][0]` is `0`. Hana and Leo follow each other through two
separately stored edges. Nuri has no incoming or outgoing edges and is an
**isolated vertex**. Dae has no outgoing edges but is not isolated because
Sora follows Dae.

## 3. Distinguish active size from capacity

The physical matrix reserves 16 rows and 16 columns. `vertex_count` says how
many indexes are currently active. With a count of 7, indexes 0 through 6
name vertices. Nuri is active even though Nuri's row and column are all zero.
Index 7 is physically inside the array but is not an active vertex.

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

An **undirected** relationship can be recorded in the two mirror cells of a
matrix; such a matrix is symmetric. Two accounts following each other in our
directed graph still represent two separate follows. A **weighted** graph
attaches a number to an edge, such as an interaction count. An **edge list**
stores endpoint pairs, while an **adjacency list** stores neighbors by vertex.
These comparisons explain design choices, but this module implements only
the fixed directed, unweighted integer matrix.

## 7. Prepare for individual thinking

Do not open `vocabulary.md` until the five-minute Cognitive Pause has been
completed and preserved and the class has completed calibration. Then read
only its 30 numbered core entries; the supplement belongs to Stage D after
the Stage C attempt.

One representation question:

____________________________________________________________________
