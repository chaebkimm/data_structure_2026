# Lab — Build a Fixed Directed Permission Matrix

## Purpose and scope

Build the chapter’s fixed directed, unweighted graph. The matrix uses integer
`0` and `1` cells; it has capacity for 16 vertices and never grows. An edge in
the invented model means “communication is permitted.” It does not prove that
communication occurred or that a service is exploitable.

This module implements only initialization, directed add, directed remove,
out-degree, and a guarded direct cell lookup in caller/test code. The textbook’s
other graph comparisons do not add hidden implementation requirements, and
formal graph exploration remains later work.

## Two 90-minute meetings

### Meeting 1 — Stages A–D: 90 minutes

- 0–15: Stage A inquiry
- 15–30: Stage B representation reveal
- 30–35: five-minute Cognitive Pause
- 35–43: calibration and Stage B vocabulary
- 43–75: Stage C investigation
- 75–90: Stage D textbook notes, questions, and exit check

### Meeting 2 — Stage E: 90 minutes

- 0–10: retrieve the representation and contracts
- 10–25: initialization and full-grid invariant
- 25–47: directed add and remove
- 47–60: out-degree and guarded direct lookup
- 60–74: exactly three student-authored tests
- 74–83: ghost-connection autopsy
- 83–90: build evidence and submission check

## Files

You receive:

- `code/include/graph_matrix.h`
- `code/starter/graph_matrix.c`
- `code/tests/test_core.c`
- `code/tests/test_student.c`
- `code/build.ps1`
- `code/Makefile`
- `code/autopsy/faulty_ghost_connection.c`

Edit only:

- `code/starter/graph_matrix.c`
- `code/tests/test_student.c`

Do not change the supplied header, core tests, or autopsy source unless the
instructor authorizes it.

## Public representation and functions

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

Each function returns `1` for success and `0` for rejection. A pointer refers
to an existing object; a null pointer refers to no object. `const` promises not
to change the graph through that pointer. An output pointer names where a
successful query stores its result.

The public representation is only the explicit struct and the four listed
functions. Conceptual comparisons do not add fields, result types, or modes.

## Completed-state rules

1. `vertex_count` is at most `GRAPH_MAX_VERTICES`.
2. Active vertex indexes are exactly `0` through `vertex_count - 1`.
3. Every `grid` entry is exactly `0` or `1`.
4. Every cell involving an inactive row or column is `0`.
5. Every diagonal cell is `0`; the course graph has no self-loop.

Cycles with more than one edge and several incoming edges to one destination
are valid. The vertex count does not change during ordinary graph operations.
No function requests or releases dynamic memory.

## Core checkpoints

Complete only the marked `TODO` regions.

### 1. `graph_init`

- Reject a null graph pointer or a count above 16.
- On success, store the count and set every cell in the full 16-by-16 grid to
  `0`, including inactive rows and columns.
- On rejection, leave an existing graph unchanged.

### 2. `graph_add_edge`

- Reject a null graph pointer or a stored count above capacity.
- Require two active indexes and reject `from == to`.
- On success, set only `grid[from][to]` to `1`.
- Adding an edge already present succeeds and leaves the same state.
- On rejection, preserve the complete graph.

Do not set the reverse cell unless the caller separately requests that
opposite directed edge.

### 3. `graph_remove_edge`

- Reject a null graph pointer or a stored count above capacity.
- Require two active indexes.
- On success, set only `grid[from][to]` to `0`.
- Removing an edge already absent succeeds and leaves the same state.
- A diagonal removal is allowed because storing `0` preserves the no-self-loop
  rule.
- On rejection, preserve the complete graph.

### 4. `graph_out_degree`

- Reject a null graph pointer, null output pointer, malformed stored count, or
  inactive vertex index.
- Count `1` cells across the selected active row.
- Store the count only after all checks succeed.
- On rejection, preserve the caller’s output.

### 5. Guarded direct lookup

In `test_student.c`, demonstrate reading `grid[from][to]` only after both
indexes have been shown active. The row is the source and the column is the
destination. This is direct caller code, not a fifth public function.

## Canonical operation trace

Use the textbook fixture consistently:

- 0: Web
- 1: App
- 2: Database
- add `0 → 1`, `1 → 2`, and `1 → 0`
- remove `1 → 2`

Before removal, App’s active row is `[1, 0, 1]`. After removal, it is
`[1, 0, 0]`, and App’s out-degree is 1. Use this trace to orient your work;
the supplied tests also require general boundary behavior.

## Exactly three student-authored tests

Add exactly three test cases to `test_student.c`. Give each a one-sentence
rationale. Do not copy a supplied test verbatim.

1. **Full initialization:** show that initialization clears both the active
   square and at least one physically stored inactive cell.
2. **Directed sequence:** exercise direction, idempotent add/remove, a guarded
   direct lookup, and an out-degree change in one coherent valid sequence.
3. **Rejected request:** use a self-loop or inactive endpoint and show that the
   graph or query output is preserved.

## Build and test

From the `code` directory in PowerShell:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target starter -StudentTests
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target autopsy
```

In Git Bash, MSYS2, WSL, Linux, or macOS:

```sh
make starter-core
make starter-student-tests
make autopsy
```

Save warning-enabled compiler output or approved CI evidence. Optional
extension tests are available only if the instructor separately releases the
tests and matching build support; they do not replace core work.

## Ghost-connection autopsy

Complete `matrix_autopsy.md`. Predict before running. The fixture stays within
the physical grid while exposing a stale `1` in an inactive row or column.
Separate the first broken invariant from the edge that appears only after the
vertex count later increases.

## Required submission

1. completed `code/starter/graph_matrix.c`;
2. exactly three passing tests in `code/tests/test_student.c`, each with a
   rationale;
3. supplied and student-test transcripts;
4. warning-enabled compiler or approved CI evidence;
5. completed `evidence_template.md`;
6. completed `matrix_autopsy.md`;
7. corrected Cognitive Pause; and
8. Stage C exit and structure-choice responses.
