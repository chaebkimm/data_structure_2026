# Module 8 C Code — Queues, Tree BFS, and Graph BFS


The required lecture source is [student/lab.c](../student/lab.c). It stores coordinates directly in a linear array queue and computes distances in the 5×5 maze. The source has no `main`; [tests/test_lecture.c](tests/test_lecture.c) includes it and supplies the executable checks. Compile the test file only.

Run `make lecture` or `make core` (the default). On Windows use `powershell -File ./build.ps1 -Target lecture`; `-Target lab` is an alias. The checks cover FIFO boundaries, the right/left/down/up iterator, the exact maze distance map and processing order, independent searches, wall starts, an isolated start, and all 512 bordered 3×3-interior maze layouts from all 25 in-bounds starts. This last check compares 12,800 searches against an independent relaxation oracle. `make student-tests` runs the same harness; students may add their own valid-case checks there.

For start `{1,1}` (fields `y,x`), eight passages are reached and `{3,3}` has distance 4. The queue ends with `front=8`, `rear=7`. Calling `bfs` again resets the queue and every distance. The unchanged source requires an in-bounds start and an intact wall border; in-bounds wall starts leave all distances `INF`. Its queue operations are unchecked. The 25-slot linear queue is sufficient because each passage is enqueued at most once per run. Tree level order and circular queues are conceptual comparisons in the chapter; the executable uses neither a linked queue nor circular storage.

The remaining sections describe optional checked-graph reference targets. Select `starter-core` or `-Target starter` for that scaffold; `solution-core`, `solution-extension`, and `solution-student-tests` run its supplied reference. These targets do not define the current lecture lab.

> Optional checked-graph reference. This file describes the separate matrix/list API, not the current maze `student/lab.c`. Use the [maze textbook](../student/textbook.md), [class workbook](../student/class_material.md), and [lab](../student/lab.md) for Week 8.

This package performs breadth-first search (BFS) on small synthetic graphs.
BFS processes vertices in nondecreasing hop distance from one source. A hop
means following one edge.

The package deliberately provides two graph representations:

- the fixed adjacency matrix reused from Module 3; and
- an array of dynamic outgoing-neighbor arrays.

Both inspect outgoing neighbors in ascending vertex order. Equivalent
graphs therefore produce the same visit order, discovered state, distances,
and predecessors.

## What students complete

`starter/graph_bfs.c` contains exactly three numbered tasks:

1. matrix BFS;
2. predecessor-path reconstruction; and
3. adjacency-list BFS.

The student test file contains exactly three additional test tasks. Students
do not edit graph allocation, adjacency-list growth, validation, or the
typed Queue.

## Discovery contract

A vertex becomes **discovered** when its first Queue insertion succeeds.
Its distance and predecessor are fixed at that moment. Recording happens
later, when the vertex is removed from the Queue.

Marking on insertion prevents two incoming routes from placing the same
vertex in the frontier twice. A successful result uses:

```text
source distance             0
source predecessor          16 (GRAPH_BFS_NO_VERTEX)
unreachable distance        16 (GRAPH_BFS_NO_DISTANCE)
unreachable predecessor     16
unused/inactive slots       explicit 16 sentinels
```

Sixteen is safe as a sentinel because active vertex IDs and possible
minimum-hop distances are 0 through 15.

Every `graph_bfs_*` operation with an output parameter changes that output
only on `GRAPH_BFS_OK`. An unreachable path therefore leaves the old path
intact. Traversal never changes either input graph.

## Supplied adjacency list

Each `GraphNeighborArray` owns a dynamic `size_t` array. Its live neighbors
are strictly ascending and unique. Capacity grows through 0, 4, 8, and 16.
The representation forbids self-loops and matches the matrix graph's
directed/undirected policy.

Undirected insertion stages both possible new arrays before changing either
row. An allocation failure therefore preserves the complete graph. Destroy
releases every row and restores the all-zero state.

The complete validator uses one fixed 16-entry scratch table to check
undirected reciprocal edges in `O(V+E)` time. It can check stored field
relationships, but it cannot prove that an arbitrary non-NULL address is
still usable, has enough storage, or has only one owner.

## Supplied vertex Queue

`VertexQueue` is an allocation-free circular Queue: after the final array
slot, storage use wraps to the first slot. Its caller-selected limit may be
0 through 16. Enqueue and dequeue use constant-time field checks; enqueue
checks its new ID, and dequeue checks the current head ID. The full public
validator additionally scans every currently queued entry, including
entries after a wrap. Public Queue operations require an object that
already satisfies that full validator. A dequeue output location must be
separate from the Queue's inline data array so reporting a removed ID cannot
overwrite pending work.

A valid source with limit zero fails. A limit above 16 also fails. The
canonical graph needs limit 3; limit 2 fails while vertex 1 tries to enqueue
vertex 4.

## Path result

`graph_bfs_reconstruct_path` returns source through destination, including
both endpoints. The source-to-source path contains one vertex. A destination
outside the active range is an error; an active but undiscovered destination
is explicitly unreachable.

The supplied result validator checks bounded predecessor chains, order
uniqueness, sentinel use, nondecreasing distance, and agreement between
order and discovered state. It cannot prove that a predecessor edge existed
without receiving the original graph.

## Cost

Let `V` be active vertices and `E` be edges.

- Matrix validation and BFS are `O(V^2)`.
- Adjacency-list validation and BFS are `O(V+E)`.
- BFS uses `O(V)` auxiliary Queue and state space.
- Path validation and reconstruction are `O(V)`.

For an undirected adjacency list, each logical edge is stored twice; this
constant factor does not change `O(V+E)`.

Graph construction cost is separate from traversal cost.

## Build targets

From this directory on Windows:

```powershell
# Starter scaffold: compiles, then expected tests fail until completed.
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 -Target starter

# Instructor reference and private boundaries.
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target solution
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target solution -Extensions

# Student-authored tests and isolated autopsy.
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target starter -StudentTests
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target autopsy
```

The script selects Clang, GCC, or Microsoft C from `PATH`. `-Sanitize` adds
runtime checks where the chosen compiler supports them.

With GNU Make:

```sh
make starter-core
make starter-student-tests
make solution-core
make solution-extension
make autopsy
```

The Makefile is intended for Git Bash, MSYS2, WSL, Linux, or macOS.

The optional complete BFS forest remains a conceptual exercise. No forest
API or build target is part of this package.
