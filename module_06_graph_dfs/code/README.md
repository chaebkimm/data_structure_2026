# Module 6 C Package

This package explores a bounded graph with depth-first search (DFS). DFS
follows one pending route deeply before returning to other unfinished work.
Unlike the Module 5 tree, a graph can contain a cycle or two routes to the
same vertex, so each implementation keeps separate seen state.

## Reused graph contract

`graph_matrix.h` and `support/graph_matrix.c` preserve the Module 3 API:

- at most 16 active vertices;
- a fixed adjacency matrix;
- directed and undirected graphs;
- no self-loops; and
- no duplicate edge insertion.

Every DFS public function first validates the entire active stored graph.
Inactive matrix cells are not active vertices.

## Supplied and student-controlled code

The instructor supplies:

- `include/graph_matrix.h` and `support/graph_matrix.c`;
- `include/graph_dfs.h`, which states the DFS promises;
- `include/vertex_stack.h` and `support/vertex_stack.c`, a tested Stack of
  vertex IDs;
- validation and status scaffolding in `starter/graph_dfs.c`;
- `tests/test_core.c`, the visible required behavior;
- `tests/test_extension.c`, instructor-only boundary tests;
- `tests/test_self_loop.c`, the separate malformed-input check; and
- the isolated bounded autopsy program.

Students edit only:

- the three numbered TODO areas in `starter/graph_dfs.c`; and
- the three TODO test bodies in `tests/test_student.c`.

The implementation TODOs are recursive DFS, iterative DFS, and undirected
component counting. `solution/graph_dfs.c` is the instructor reference.

## Deterministic visit rules

Recursive DFS marks and records a vertex, then checks outgoing neighbors in
ascending index order.

Iterative DFS marks a vertex only after a successful push, records it when
it is popped, and checks outgoing neighbors in descending index order. Thus,
the lowest-index newly pushed neighbor is on top. A cross-link can still make
the two correct implementations report different orders.

Every reached vertex appears exactly once in the first `count` positions of
a `GraphDfsOrder`. For a directed graph, DFS follows outgoing edges.

Connected-component counting accepts only an undirected graph. Directed
graphs use reachability from a named starting vertex instead.

## Failure behavior

DFS never changes its input graph. A result output changes only on
`GRAPH_DFS_OK`. This includes invalid graphs, inactive starts, Stack-limit
failures, allocation failures, and attempts to count components in a
directed graph.

The recursive functions need no dynamic allocation. The iterative function
uses the supplied growable Stack. The Stack grows lazily through capacities
4, 8, and 16, clipped to the caller's limit.

## Build commands

From this `code` directory on Windows:

```powershell
# Expected to compile but fail tests until the three starter TODOs are done.
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1

# Instructor reference checks.
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target solution
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target solution -Extensions

# Student-authored tests, separate self-loop check, and bounded autopsy.
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target starter -StudentTests
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target self-loop
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target autopsy
```

The script chooses Clang, GCC, or Microsoft `cl` from `PATH`. With GNU Make:

```sh
make starter-core
make solution-core
make solution-extension
make starter-student-tests
make self-loop
make autopsy
```

`make starter-self-loop` links the same check to the starter validation
scaffolding. `make solution-self-loop` is the instructor reference target.

Warning checks use C11 plus common high-value warnings. `-Sanitize` adds
memory and undefined-behavior checks where the selected compiler supports
them.

## Test-only control

Core and extension builds define `GRAPH_DFS_TESTING`. That definition exposes
`vertex_stack_test_fail_next_allocation()`, which makes the next vertex-Stack
allocation fail once. It makes the rare allocation-failure path repeatable
and is absent from normal builds.

## Cost

Let `V` be the active vertex count. Full validation and adjacency-matrix DFS
each take at most a constant times `V * V` checks, so the public operations
are `O(V^2)`. Recursive calls, seen state, result storage, and the explicit
Stack each use `O(V)` additional space. An adjacency-list DFS can instead
take `O(V + E)`, where `E` is the edge count.
