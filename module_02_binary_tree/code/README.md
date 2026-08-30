# Module 2 C Code

This lab uses local binary-tree node objects. Each object stores one integer
and two downward links, named `left` and `right`. Numeric operands are stored
as integer values. Operators use C character constants such as `'+'` and
`'*'`, which also have integer values.

```c
struct TreeNode three = { 3, NULL, NULL };
struct TreeNode five = { 5, NULL, NULL };
struct TreeNode plus = { '+', &three, &five };
struct TreeNode two = { 2, NULL, NULL };
struct TreeNode root = { '*', &plus, &two };
```

These five objects represent `(3 + 5) * 2`. Their preorder search order is
`'*'`, `'+'`, `3`, `5`, `2`: current node, entire left subtree, then entire
right subtree. This expression uses two children for each binary operator and
none for each numeric operand. The underlying general binary-tree structure
also permits a node with only one child.

The caller must keep every linked node alive, use an empty selected side,
and attach only a fresh node or disjoint subtree. A normal tree has no cycle
and no shared child. The library does not enforce these structural rules.

## Core work

Complete the two TODOs in `starter/binary_tree.c`:

- `tree_find`: check the current node, then the entire left subtree, then
  the right subtree; return the first matching address or `NULL`;
- `tree_clear`: recursively reset every reachable node's data to `0` and
  both child links to `NULL`.

Direct initialization, guarded left/right attachment, and explicit child
removal are also core operations. They do not need wrapper functions.

```c
tree_clear(root.left);
root.left = NULL;
```

Clearance does not end a node object's lifetime and cannot detach a link in
an outside parent. Cleared local variables may still be inspected and
reinitialized. The right child remains the right child when the left branch
is removed.

`0` is an ordinary data value. A cleared node with data `0` can still match
`tree_find`; only a `NULL` link means there is no node to visit.

The core fixture is the five-node expression tree for `(3 + 5) * 2`. Data does
not follow a binary-search ordering rule, so the library treats operator
character constants and numeric operands as ordinary integer data.

## Targets

- `starter-core`: compile the scaffold and run the required tests;
- `starter-student-tests`: run the three student-designed placeholders;
- `starter-extension`: run extra checks against the starter;
- `solution-core`: run the reference core tests;
- `solution-extension`: run boundary and deeper-fixture tests;
- `autopsy`: build and run a memory-safe shared-child observation; and
- `clean`: remove generated executables.

The default Make target is the starter core. Its tests intentionally fail
until the TODOs are implemented.

## PowerShell

Run from this `code` directory:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target starter -StudentTests
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target solution
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target solution -Extensions
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target solution -Extensions -Sanitize
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target autopsy
```

`-ExecutionPolicy Bypass` applies only to this PowerShell process. The script
searches for Clang, GCC, and then Microsoft C (`cl`). Microsoft C needs a
Visual Studio Developer PowerShell or Command Prompt.

`-Sanitize` enables supported run-time memory checks. Test recursive functions
only with finite, acyclic, unshared fixtures; do not pass an actual cycle to
the library to see whether it stops.

## GNU Make

```sh
make starter-core
make starter-student-tests
make solution-core
make solution-extension
make autopsy
```

The Makefile is intended for Git Bash, MSYS2, WSL, Linux, or macOS. It
defaults to `gcc`; override it with `make CC=clang solution-core` when needed.

## Manual GCC or Clang build

```sh
mkdir -p build
cc -std=c11 -Wall -Wextra -Wpedantic -Wconversion -Wshadow -g \
  -Iinclude solution/binary_tree.c tests/test_core.c \
  -o build/solution_core

./build/solution_core
```

To check recursive operations with Clang or GCC:

```sh
cc -std=c11 -Wall -Wextra -Wpedantic -Wconversion -Wshadow -g \
  -fsanitize=address,undefined -fno-omit-frame-pointer \
  -Iinclude solution/binary_tree.c tests/test_extension.c \
  -o build/solution_extension_sanitized

./build/solution_extension_sanitized
```

## Manual Microsoft C build

From a Visual Studio Developer PowerShell:

```powershell
New-Item -ItemType Directory -Force build | Out-Null
cl /nologo /std:c11 /W4 /Zi /Iinclude `
  solution\binary_tree.c tests\test_core.c `
  /Fe:build\solution_core.exe

.\build\solution_core.exe
```

## Expected reference output

```text
PASS expression initialization and occupied-side guard
PASS canonical expression preorder search preserves nodes
PASS preorder duplicates and generic unsorted values
PASS right-only child, null, and missing search
PASS zero is ordinary data
PASS clear expression branch and explicit detachment
PASS whole expression clear keeps objects live
PASS reinitialize and reuse cleared nodes

8 core test(s), 0 failure(s)
```

The extension suite reports five passing boundary and deeper-fixture tests.
