# Module 3 C Code

This lab stores one fixed directed, unweighted graph in the representation
shown by the textbook:

```c
#define GRAPH_MAX_VERTICES 16

struct DirectedGraph {
    size_t vertex_count;
    int grid[GRAPH_MAX_VERTICES][GRAPH_MAX_VERTICES];
};
```

The active vertex indexes are `0` through `vertex_count - 1`. A cell equal to
`1` records the directed edge from its row vertex to its column vertex; `0`
records no edge. Direction matters, so setting `grid[0][1]` does not change
`grid[1][0]`.

Valid completed graphs keep `vertex_count` at most 16, every diagonal cell at
`0`, and all inactive rows and columns at `0`. Longer cycles and multiple
edges arriving at one destination are valid. The four small public functions
make the textbook's direct operations independently testable; they do not
add dynamic storage or an undirected-graph mode.

## Core work

Complete the four TODO regions in `starter/graph_matrix.c`:

- `graph_init`: clear the entire 16-by-16 grid and store the active count;
- `graph_add_edge`: set one checked directed cell to `1`;
- `graph_remove_edge`: set one checked directed cell to `0`; and
- `graph_out_degree`: count cells equal to `1` across one active row.

Every function returns `1` on success and `0` on invalid input. Re-adding an
edge and re-removing an edge are successful idempotent assignments. Add
rejects a self-loop; remove permits equal indexes because writing `0` to a
diagonal cell is harmless. A rejected mutation leaves the graph unchanged,
and a rejected out-degree query leaves its output unchanged.

The canonical three-server example is:

```text
Web (0) -> App (1)
App (1) -> Database (2)
App (1) -> Web (0)
```

Before removal, App's row is `[1, 0, 1]` and its out-degree is 2. After
removing `1 -> 2`, the row is `[1, 0, 0]` and its out-degree is 1.

## Targets

- `starter-core`: compile the scaffold and run the required tests;
- `starter-student-tests`: run the three student-designed placeholders;
- `starter-extension`: run extra checks against the scaffold;
- `solution-core`: run the reference core tests;
- `solution-extension`: run boundary and sequence tests;
- `autopsy`: build and run the memory-safe ghost-connection observation; and
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
  -Iinclude solution/graph_matrix.c tests/test_core.c \
  -o build/solution_core

./build/solution_core
```

To add supported run-time checks:

```sh
cc -std=c11 -Wall -Wextra -Wpedantic -Wconversion -Wshadow -g \
  -fsanitize=address,undefined -fno-omit-frame-pointer \
  -Iinclude solution/graph_matrix.c tests/test_extension.c \
  -o build/solution_extension_sanitized

./build/solution_extension_sanitized
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
PASS initialization clears the full grid
PASS initialization rejection preserves graph
PASS canonical Web-App-Database trace
PASS direction is independent
PASS add rejections preserve graph
PASS idempotent add and remove
PASS out-degree and isolated vertex
PASS invalid metadata and output preservation

8 core test(s), 0 failure(s)
```

The extension suite reports five passing boundary and sequence tests.
