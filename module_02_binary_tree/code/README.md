# Module 2 C Code

This lab builds a small binary tree without requesting memory from the
operating system.

An **arena** is a fixed array of `TreeNode` objects supplied by the caller.
“Caller” means the part of the program that invokes a function. The arena
holds at most 32 active nodes, never grows, and is never passed to `free`.

## What students complete

The starter has four short tasks:

1. decide whether one node is a leaf;
2. count one node's children;
3. place a checked child address into an empty left or right position; and
4. report one node's parent and children.

The whole-tree and binary-search-tree validators are supplied. A
**validator** is a function that checks whether stated rules are satisfied.
In a **binary search tree (BST)**, every key in a node's left subtree is
lower and every key in its right subtree is higher. A **subtree** is one node
together with all the nodes below it.
Students use these functions but do not write a **traversal**—a procedure that
systematically visits nodes—in this module.

## Targets

- `starter`: the compiling scaffold; core tests initially fail.
- `solution`: the instructor reference; core tests should pass.
- `-StudentTests`: the three student-designed test placeholders.
- `-Extensions`: extra instructor checks for maximum size and boundary keys.
- `autopsy`: a separate, memory-safe link observation exercise.

The default build target is `starter`.

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

`-ExecutionPolicy Bypass` applies only to this one PowerShell process. It is
useful on a computer that blocks unsigned local scripts, and it does not
change the user or machine policy.

The script searches for Clang, GCC, and then Microsoft C (`cl`). Microsoft C
must be run from a Visual Studio Developer PowerShell or Command Prompt. A
**compiler** is the program that translates C source into an executable
program.

Add `-Sanitize` when the installed compiler supports sanitizers. A
**sanitizer** adds run-time checks that can report certain memory mistakes.

## GNU Make

```sh
make starter-core
make starter-student-tests
make solution-core
make solution-extension
make autopsy
```

The Makefile uses POSIX shell commands—the command forms used by Unix-like
systems. It is intended for Git Bash, MSYS2, WSL, Linux, or macOS—not ordinary
Windows PowerShell. It defaults to `gcc`; use an override such as
`make CC=clang solution-core` when needed.

## Manual GCC or Clang build

```sh
mkdir -p build
cc -std=c11 -Wall -Wextra -Wpedantic -Wconversion -Wshadow -g \
  -Iinclude solution/tree_arena.c tests/test_core.c \
  -o build/solution_core

./build/solution_core
```

## Manual Microsoft C build

From a Visual Studio Developer PowerShell:

```powershell
New-Item -ItemType Directory -Force build | Out-Null
cl /nologo /std:c11 /W4 /Zi /Iinclude `
  solution\tree_arena.c tests\test_core.c `
  /Fe:build\solution_core.exe

.\build\solution_core.exe
```

## Expected reference output

```text
PASS empty and single-node initialization
PASS initialization errors preserve state
PASS checked outputs stay unchanged on error
PASS local assignment checks and preservation
PASS node queries and immediate family
PASS global validator rejects shared child
PASS global validator rejects cycle
PASS BST uses whole-subtree limits

8 test(s), 0 failure(s)
```

## Storage rule

A `TreeArena` stores addresses into its caller-owned `TreeNode` array. That
array must still exist whenever the arena is used. Do not return an arena that
points to a local array belonging to a function that has already returned.

All checked-output functions change their output only when they return
`TREE_OK`. `tree_assign_child` makes no change when it returns an error.
