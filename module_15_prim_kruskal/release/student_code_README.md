# Module 15 Student Code

This directory is a self-contained bounded C lab. You do not need files or
compiled programs from another module.

A **logical edge** is one undirected connection. An **incident record** is
one stored view of that connection from one endpoint, so a logical edge has
two incident records. A **frontier** stores pending Prim candidates. A
**Disjoint-Set Union (DSU)** stores which vertices are already joined while
Kruskal scans edges.

## Your files

Complete only the marked clusters in:

- `starter/prim.c`
- `starter/kruskal.c`
- `tests/test_student.c`

Do not change the **public headers**, the `.h` files that declare the shared
types and operations, merely to make a test pass. The supplied support files
implement the tested graph preparation, signed minimum Heap, DSU,
less-than/greater-than edge comparison, result validation, and checked total.
A **binary minimum Heap** is a tree-shaped array in which the smallest
pending key is at the first position.

## Build

From this `code` directory, use one compiler and its matching build method.

PowerShell:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -StudentTests
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target autopsy
```

A **sanitizer** is a compiler check that helps detect invalid memory or
arithmetic behavior while a program runs. Add `-Sanitize` to a normal or
autopsy command when the selected compiler supports sanitizers.

GNU Make:

```text
make starter-core
make starter-student-tests
make autopsy
```

The visible core tests are a **specification**, a statement of required
behavior, not a complete private test suite. Add all three requested
student-test categories.

## Public limits

```text
maximum vertices             16
maximum logical edges       120
maximum incident records    240
maximum selected edges       15
maximum Prim pushes         136
weight and total type       int64_t
```

Vertex IDs are dense: a five-vertex graph uses IDs 0 through 4. Invalid
endpoints must be rejected before any array access. `int64_t` is C's signed
64-bit whole-number type.

## Shared graph and result support

Important public operations include:

- `mst_graph_init`
- `mst_graph_add_edge`
- `mst_parse_weight`
- `mst_graph_validate`
- `mst_adjacency_index_build`
- `mst_forest_total_checked`
- `mst_forest_validate`

`mst_parse_weight` converts text into a signed 64-bit value. An output is
published only after complete success.

The validator checks that selected edge IDs belong to the input, do not
repeat, form no cycle, span every input component, contain exactly `V - c`
edges, and reproduce the stored total.

## Prim

`prim_minimum_spanning_forest` uses a lazy minimum Heap. **Lazy** means a
better candidate is pushed without removing the older record. When an older
record later leaves the Heap, a stale-key check discards it.

For a disconnected input, use one forward-only cursor, an index that never
moves backward, to restart at the smallest vertex not yet in the forest. A
self-loop never reaches a different vertex. Parallel edges remain separate
candidates. Each indexed adjacency slice visits edge IDs in ascending order,
only a strictly smaller key replaces the current proposal, and equal
frontier keys leave in stable insertion order.

The supplied frontier operations are:

- `prim_frontier_init`
- `prim_frontier_validate`
- `prim_frontier_is_min_heap`
- `prim_frontier_push`
- `prim_frontier_pop`
- `prim_frontier_destroy`

Every initialized frontier must be destroyed on every return path that
follows successful allocation.

## Kruskal

`kruskal_minimum_spanning_forest` builds and sorts a local edge list, creates
one DSU set for each vertex, and scans all logical edges.

The comparator uses less-than and greater-than tests. It never returns a
subtracted weight because signed subtraction can overflow. An edge is
accepted only when DSU reports that its endpoint **representatives** were
different. A representative is the root ID naming one joined component; a
**component** is a group of mutually connected vertices.

Sorting a local copy keeps the input graph unchanged.

The initial ordinary-language inquiry can stop once every site is reached.
The C implementation instead processes every logical edge so the result
keeps a complete acceptance/rejection decision ledger.

## Mathematical total

Negative weights are valid. Use the supplied order-independent total helper,
which permits positive and negative selections to cancel. A final
mathematical total that fits `int64_t` is accepted even when one selection
order would have an overflowing prefix. A final total outside the range
must preserve the caller's result object.

## Required tests

In addition to the canonical connected graph, cover:

1. singleton and disconnected graphs;
2. equal-weight alternatives, parallel edges, self-loops, and negative
   weights; and
3. invalid endpoints, a total beyond 32-bit range, fitting cancellation, a
   final total outside `int64_t`, and output preservation.

Prim and Kruskal must agree on minimum total weight. They are not required to
select or publish edges in identical order.

## Safe cycle autopsy

The isolated autopsy is memory-safe and deterministic. It shows why
comparing raw endpoint IDs is not a cycle test. It is never linked into a
normal test target.
