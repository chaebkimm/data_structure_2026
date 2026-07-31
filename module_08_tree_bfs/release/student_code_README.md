# Student Code Package

You will complete three tree operations in `starter/tree_bfs.c`:

1. left-first level-order traversal;
2. shallowest-value search; and
3. edge-height calculation through breadth-first traversal.

A **traversal** is a planned procedure for visiting nodes. **Breadth-first
search (BFS)** visits every nearer node before any deeper node. The supplied
typed Queue stores a node pointer and its depth in each pending work record.

Edit only:

- `starter/tree_bfs.c`; and
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
expected. Fix the earliest failed requirement without changing the public
headers, supplied Queue, tree support, or core tests.
