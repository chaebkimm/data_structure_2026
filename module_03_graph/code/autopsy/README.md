# One-Sided Matrix Autopsy

An **autopsy** is a careful examination of a supplied defect.
`faulty_undirected.c` is separate from the normal passing tests. A **test**
runs one case and checks its result. The file uses a **fixed matrix**, meaning
a table that does not grow, and accesses only positions inside that table.

A **graph** is a collection of objects and connections. An **undirected
graph** uses connections that work both ways. An **adjacency matrix** is a
square table that records graph connections. A
**cell** is one table position. An **index** is a numbered position. A
**mirror cell** reverses two indexes: `[a][b]` is the mirror of `[b][a]`.
An undirected connection has no one-way direction, so those two cells must
agree. A matrix is **asymmetric** when a pair of mirror cells disagrees.

Before running the program:

1. Draw or state its three **active** rows and columns—the rows and columns
   included in this small example.
2. Predict each printed `yes` or `no`.
3. Mark the exact pair of cells that violates the undirected rule.

From the `code` directory, which is the parent of this directory, run:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target autopsy
```

Afterward, explain:

- why the two one-way reports contradict the graph's declared kind;
- why one logical undirected edge needs two matching cells;
- how changing only one of those cells creates the defect; and
- why `graph_validate`, the rule-checking function, must compare mirror
  cells.

Do not repair the program until the prediction and printed result have both
been recorded.
