# Student Code Package

You will complete four tree operations in `starter/tree_dfs.c`:

1. recursive preorder traversal;
2. iterative preorder traversal with a supplied Stack;
3. binary-search-tree search; and
4. postorder destruction.

A **traversal** visits every node in a stated order. **Recursive** code solves
a tree by calling the same function on smaller child trees. **Iterative** code
uses repetition, such as a `while` loop, instead of recursive calls.

Edit only:

- `starter/tree_dfs.c`; and
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

The starter is intentionally incomplete. A failed first test run is expected.
Fix the earliest failed requirement without changing the public headers or
the supplied core tests.
