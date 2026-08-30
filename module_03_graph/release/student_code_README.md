# Module 3 Student Code

## Files you edit

- `starter/graph_matrix.c`
- `tests/test_student.c`

Do not edit the public header or supplied tests unless your instructor
authorizes it.

## Exact public work

```c
#define GRAPH_MAX_VERTICES 16

struct DirectedGraph {
    size_t vertex_count;
    int grid[GRAPH_MAX_VERTICES][GRAPH_MAX_VERTICES];
};

int graph_init(struct DirectedGraph *graph, size_t vertex_count);
int graph_add_edge(struct DirectedGraph *graph, size_t from, size_t to);
int graph_remove_edge(struct DirectedGraph *graph, size_t from, size_t to);
int graph_out_degree(
    const struct DirectedGraph *graph,
    size_t vertex,
    size_t *out_degree
);
```

These are the only four library functions. Each returns 1 on success and 0
on rejection. Initialization clears all 256 cells. Add and remove change one
directed cell and are idempotent. Addition rejects self-loops. Every rejected
mutation preserves the graph, and an out-degree failure preserves its output.

For direct lookup, first establish a valid initialized object and check both
IDs against `vertex_count`, then read `graph.grid[from][to]`. Do not invent
a query function.

The implemented graph is directed and unweighted. Undirected symmetry,
weights, edge lists, adjacency lists, and components are comparison topics,
not extra code.

## PowerShell

From the `code` directory:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target starter -StudentTests
```

Add `-Sanitize` when supported. The script searches for Clang, GCC, and then
Microsoft C. Use a Visual Studio Developer PowerShell for Microsoft C.

## GNU Make

From Git Bash, MSYS2, WSL, Linux, or macOS:

```sh
make starter-core
make starter-student-tests
```

The starter is intentionally incomplete. The test failures identify the four
required implementations still to complete.

## Matrix Autopsy

Preserve the prediction in `../student/matrix_autopsy.md`, then run:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target autopsy
```

or `make autopsy` in a POSIX-like shell. The standalone fixture is physically
in bounds and is expected to finish normally. Compare active versus inactive
state; do not rely on a crash.

The solution and instructor extension tests are deliberately absent from
this release.
