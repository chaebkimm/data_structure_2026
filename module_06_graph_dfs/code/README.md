# Module 6 C Package

## Current array-based classroom lab

The current [lab](../student/lab.c), [textbook](../student/textbook.md),
[concept slides](../student/ppt_material.md),
[lab slides](../student/ppt_lab_material.md), and
[class material](../student/class_material.md) use the Module 3 adjacency
lists and Module 4 integer stack. Read `_edge_iteration_()` as the
template; `_init_edges_list()` records edges, and `_find_bcc()` stacks their
indices and collects blocks.

The lab has no `main()`. From this directory, run its supplied
[lecture driver](lecture/lab_demo.c) with GNU Make and a C11 compiler:

```sh
make lecture
```

Plain `make` runs the same original driver. To check the array lab, run:

```sh
make lab-tests
```

The nine checks cover both supplied graphs, isolate/self-loop scope,
strict/equal boundary comparisons, root branches, nine result rows,
ten pending stack entries, and more than ten records with a smaller
pending peak.

The driver initializes the graph with `alphabet_nodes_init()` and
`edges_init()`, then calls `init_edges_list(0)` and `find_bcc(0)` in a fresh
process. Expect discovery A/B/C/D/E/F = 1/2/3/4/5/6, low-link values
1/2/3/2/2/2, eight indexed edges, three rows `[1]`, `[7,6,5,4,3,2]`,
`[0]`, and `top == -1`. This is the original A–J source example.

The updated concept slides, textbook, class activities, and website use
the seven-vertex graph numbered by DFS visits 1–7 as their main worked example. Run the additional
[slide driver](lecture/ppt_demo.c) with `make lecture-ppt`. It prepares
the slide graph without changing `lab.c` or its dependencies. With the slide traversal order, expect visit numbers 1–7, low-link values
1/1/1/3/3/3/2, ten edge records, and two five-entry rows
`[7,6,5,4,3]` and `[9,8,2,1,0]`. The slide driver prints edge endpoints from computed visit numbers; its array indices appear separately in the C table. Both drivers finish with an empty stack.
Use the class material and [models](../diagrams/dfs_models.md) for the
intermediate endpoint-pair trace.

`add_edge()` records a connection already present in the graph; it does
not insert a neighbor. `init_edges_list()` resets discovery/parents,
sets `edges_size` to zero, fills the active `edge_index` region with -1,
then calls its recursive helper. `find_bcc()` assumes prepared edge indices and
does not reset `current_bcc`. The array lab is an unchecked one-call
teaching example with fixed capacity; see its
[technical notes](../instructor/technical_notes.md) for the contract.
Indexing, low-link calculation, and extraction are three DFS passes.
The latter two use the same start and neighbor order, with `back_num`
preserved across the discovery reset before extraction. Immediately after
a child returns, a strict `back_num[adj] < visit_num[node]` keeps its
edges pending; otherwise `close_bcc(tree_edge)` pops through that edge.

The lab now reserves 45 records in `edges`, nine 45-entry rows in `bcc`,
and nine row lengths in `bcc_size`. The reused Module 4 stack still has
ten entries. Input must fit every capacity, including the peak pending
count; neither the wrappers nor raw stack operations enforce these limits.

## Legacy checked matrix-DFS exercise

The remainder describes the separate matrix starter/support package. Its
headers, status codes, tests, and failure promises apply to that package.
See [the module teaching path](../README.md) for current classroom work.

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
