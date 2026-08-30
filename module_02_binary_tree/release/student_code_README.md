# Module 2 Student Code

## Files you edit

- `starter/binary_tree.c`
- `tests/test_student.c`

Do not edit the public header or supplied tests unless your instructor
authorizes it.

## Exact model and work

```c
struct TreeNode {
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
};

struct TreeNode *tree_find(struct TreeNode *node, int target);
void tree_clear(struct TreeNode *node);
```

These are the only two library functions to complete. Nodes are local
variables with addresses stored in their child links. The caller keeps them
alive and constructs a finite, acyclic, unshared tree.

The canonical five-node fixture represents `(3 + 5) * 2`:

```text
          root:'*'
          /      \
     plus:'+'    two:2
       /   \
  three:3 five:5
```

Its current-node/left/right order is `'*', '+', 3, 5, 2`. Use character
constants such as `'*'` and `'+'` directly; they have type `int` and fit the
data field. The two child positions preserve operand order.

Search checks the current node, then the left subtree, then the right subtree,
returning the first matching address or `NULL`. It does not change the tree.
Clear resets all reachable data to zero and links to `NULL`; it does not
end local-object lifetimes or erase an incoming link outside the subtree.

Direct initialization, guarded attachment to a chosen side, and explicit
clear-then-detach removal belong in the examples and your three tests.
A right-only child is valid. Removing left never moves right into left.
The expression fixture happens to give each binary operator two operands,
but the same representation supports general valid binary trees with exactly
one child and with duplicate or non-expression data.

## PowerShell

From this `code` directory:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target starter -StudentTests
```

Add `-Sanitize` when supported. The execution-policy setting applies only
to the launched child process. The script searches for Clang, GCC, and then
Microsoft C; use a Visual Studio Developer PowerShell for Microsoft C.

## GNU Make

In Git Bash, MSYS2, WSL, Linux, or macOS:

```sh
make starter-core
make starter-student-tests
```

The Makefile defaults to GCC. Use `make CC=clang starter-core` for Clang.
The starter is intentionally incomplete, so initial test failures identify
the two functions still to implement.

## Isolated Tree Structure Autopsy

First preserve the prediction requested in `../student/tree_autopsy.md`.
Then run either:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target autopsy
```

or `make autopsy` in a POSIX-like shell. The standalone fixture supplies its
own clearance routine; it does not depend on your unfinished implementation.
All fixture variables remain alive. Its intentionally malformed expression
reuses one `shared_five` operand beneath both `plus` and `minus`. Compare its
observable state with the tree invariant rather than expecting a crash.

Instructor extension tests and the reference implementation are deliberately
absent from this student release.
