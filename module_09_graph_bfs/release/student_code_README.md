# Student Code Package

You will complete three operations in `starter/graph_bfs.c`:

1. breadth-first search over an adjacency matrix;
2. minimum-hop path reconstruction from a completed BFS result; and
3. the same BFS steps over sorted adjacency lists.

**Breadth-first search (BFS)** processes smaller hop distances before larger
ones. A **hop** follows one edge. A vertex becomes **discovered** when its
first successful enqueue places it in waiting work. A **predecessor** is the
previous vertex on the first-discovered route.

Edit only:

- `starter/graph_bfs.c`; and
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
headers, supplied representations, Queue support, or core tests.
