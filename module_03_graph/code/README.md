# Module 3 C Code: Graphs in a Fixed Matrix

A **graph** is a set of items and connections. An item is a **vertex**; a
connection is an **edge**. This lab stores a graph in an **adjacency matrix**,
a square table in which a true cell records an edge.

The graph owns one fixed 16 by 16 matrix inside its `Graph` object. It never
requests storage while the program is running. `vertex_count` selects the
active rows and columns.

## What students complete

The starter contains short tasks for:

1. initializing and clearing a graph;
2. adding and removing checked edges;
3. asking whether one edge exists;
4. counting outgoing and incoming edges; and
5. listing outgoing neighbors in ascending index order.

A **directed edge** has one direction, such as `0 -> 1`. An **undirected
edge** connects both ways, so the two mirror cells `[0][1]` and `[1][0]`
must match. A **neighbor** is a vertex reached by one outgoing edge.

The whole-matrix validator and status text are supplied. A **validator** is a
function that checks whether stated rules hold.

## Local checks and the full check

Ordinary edge operations inspect only the requested pair. A directed add,
remove, or query therefore takes constant time: its work does not grow with
the number of vertices. An undirected edge operation also checks the one
mirror cell, so it is constant time too.

Degree and neighbor operations scan one active row or column. Their work
grows in direct proportion to `V`, the active vertex count. This is written
as `O(V)`.

`graph_validate` checks the whole active matrix. It examines `V` rows by `V`
columns, written as `O(V^2)`. A defect unrelated to a local operation is
therefore found by the separate full validator, not by that local operation.

## Targets

- `starter`: the compiling student scaffold; core tests initially fail.
- `solution`: the instructor reference; core tests should pass.
- `-StudentTests`: three student-designed test placeholders.
- `-Extensions`: extra instructor checks.
- `autopsy`: a separate safe observation of a broken undirected matrix.

The default build target is `starter`. The solution and extension tests are
instructor materials and should not be included in a student release.

## PowerShell

Run these commands from this `code` directory:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target starter -StudentTests
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target solution
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target solution -Extensions
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target autopsy
```

`-ExecutionPolicy Bypass` applies only to this PowerShell process. It can be
useful when a computer blocks unsigned local scripts; it does not change the
user or machine policy.

The script searches for Clang, GCC, and then Microsoft C (`cl`). A
**compiler** is a program that translates C source into an executable
program. Microsoft C must run from a Visual Studio Developer PowerShell or
Command Prompt.

Add `-Sanitize` when the installed compiler supports sanitizers. A
**sanitizer** adds checks while a program runs and can report certain memory
mistakes.

## GNU Make

```sh
make starter-core
make starter-student-tests
make solution-core
make solution-extension
make autopsy
```

The Makefile uses POSIX shell commands, the command forms used by Unix-like
systems. It is intended for Git Bash, MSYS2, WSL, Linux, or macOS, not
ordinary Windows PowerShell. It defaults to `gcc`; override that choice with
a command such as `make CC=clang solution-core`.

## Manual GCC or Clang build

```sh
mkdir -p build
cc -std=c11 -Wall -Wextra -Wpedantic -Wconversion -Wshadow -g \
  -Iinclude solution/graph_matrix.c tests/test_core.c \
  -o build/solution_core

./build/solution_core
```

## Manual Microsoft C build

From a Visual Studio Developer PowerShell:

```powershell
New-Item -ItemType Directory -Force build | Out-Null
cl /nologo /std:c11 /W4 /Zi /Iinclude `
  solution\graph_matrix.c tests\test_core.c `
  /Fe:build\solution_core.exe

.\build\solution_core.exe
```

## Expected reference output

```text
PASS empty graph, boundaries, and preservation
PASS directed edge operations
PASS undirected symmetry, duplicates, and self-loops
PASS directed and undirected degrees
PASS neighbors are ascending
PASS malformed incident state is rejected
PASS status names

7 test(s), 0 failure(s)
```

All functions with an `out_` parameter change that output only after every
check succeeds. An edge operation that returns an error leaves the graph
unchanged.
