# Student Code Package

You will complete exactly three concepts in `starter/dijkstra.c`:

1. parse one textual route cost, rejecting negative or out-of-range input
   before conversion to `size_t`;
2. run Dijkstra using guarded addition, strict relaxation, lazy duplicate
   frontier entries, and stale-pop skipping; and
3. reconstruct a bounded path from predecessor records.

The supplied `weighted_graph` support owns a simple directed adjacency list.
It permits zero-cost arcs, rejects self-loops and duplicate arcs, and keeps
each outgoing row in ascending destination order.

The supplied `dijkstra_frontier` is a dynamically growing stable minimum
Heap. It compares:

1. smaller tentative cost first; and
2. for equal costs, the earlier push sequence first.

The frontier does not use Module 11's 64-record cap. One run sets its limit
to:

```text
arc_count + 1
```

The `+ 1` reserves the source snapshot. A simple directed graph with at most
16 vertices has at most 240 arcs, so the limit is at most 241.

## Required arithmetic rule

`INF` equals `SIZE_MAX` and is reserved. For a current finite distance and
one nonnegative cost:

1. reject when addition would exceed `SIZE_MAX`;
2. add only after the subtraction guard succeeds;
3. reject when the candidate equals `INF`; and
4. return `DIJKSTRA_COST_RANGE` without changing caller output.

Relax only when:

```text
candidate < current distance
```

Equality does not replace a predecessor.

## Canonical evidence

Use these directed routes:

```text
A->B 9, A->C 2, A->E 14,
B->D 0, B->E 8,
C->B 2, C->D 2,
D->E 2,
F unreachable
```

Required result:

```text
cost A to E            6
path                   A,C,D,E
pushes                 8
pops                   8
stale pops             3
peak frontier size     4
Heap comparisons       17
```

Edit only:

- `starter/dijkstra.c`; and
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

Run the isolated faulty program:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target autopsy
```

GNU Make users can run:

```sh
make starter-core
make starter-student-tests
make autopsy
```

The starter is intentionally incomplete. A failed first test run is
expected. Fix the earliest failed requirement without changing public
headers, supplied support, or supplied core tests.
