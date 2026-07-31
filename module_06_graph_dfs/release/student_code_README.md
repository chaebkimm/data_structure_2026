# Student Code Package

You will complete three graph operations in `starter/graph_dfs.c`:

1. recursive depth-first search;
2. iterative depth-first search with a supplied vertex-ID Stack; and
3. connected-component counting for an undirected graph.

**Depth-first search (DFS)** follows one route deeply before returning to a
waiting choice. A **vertex identifier** is the number naming one graph item.
A **connected component** is one largest group in an undirected graph whose
vertices can reach one another.

Edit only:

- `starter/graph_dfs.c`; and
- `tests/test_student.c`.

Run the public core tests from this directory:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1
```

Run your three tests:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -StudentTests
```

Run the standalone self-loop test and bounded faulty program:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target self-loop
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target autopsy
```

GNU Make users can run:

```sh
make starter-core
make starter-student-tests
make self-loop
make autopsy
```

The starter is intentionally incomplete. A failed first test run is
expected. Fix the earliest failed requirement without changing public
headers, supplied support, or supplied tests.
