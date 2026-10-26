# Module 12 Code — Execute the Supplied AVL Lab

## Which implementation is required?

[`../student/lab.c`](../student/lab.c) is the complete teaching source.
It includes Module 2's `nodes[10]` with character labels and integer child
links, and adds `height[10]`. No node allocation or `main` is supplied.
Each driver includes the lab exactly once through
`tests/lab_test_support.h`; compile the driver alone.

The current lab accepts equal labels on distinct IDs. A new equal label
branches left, but rotations may leave equals on either side. Validate a
nondecreasing inorder sequence, not strict unique-key ordering. Missing
links have height `-1`; leaves have height `0`.

## How do we build from the repository?

From the repository root with GCC or Clang:

```sh
make -C module_12_bst_avl/code lab-compile core student-tests comparison
```

The standalone archive uses `make -C code` from its extraction root.

`make -C module_12_bst_avl/code` defaults to current-lab core and student
tests. The targets mean:

| Target | Work |
| --- | --- |
| `lab-compile` | Compile the actual lab into an object without linking |
| `core` | Run supplied rotation, transfer, duplicate, boundary, and measurement tests |
| `student-tests` | Run three smoke groups to extend with original evidence |
| `comparison` | Print and assert the seven-label BST-versus-AVL table |

The default `LAB_DIR=../student` and `TREE_ROOT=../..` are relative to
`code/`. `TREE_ROOT` is the directory containing
`module_02_binary_tree/student/lab.c`. The standalone student archive uses
`TREE_ROOT=..` because the dependency is bundled at its extraction root.
`BUILD_DIR` and `CC` may also be overridden.

A direct build from `module_12_bst_avl/code` is:

```sh
cc -std=c11 -Wall -Wextra -Wpedantic -Wconversion -Wshadow -g \
  -I../student -I../.. tests/test_lab_core.c -o /tmp/module12_core
/tmp/module12_core
```

Replace the test source and output name for the other drivers. Do not add
`student/lab.c` or Module 2's `lab.c` as another linked translation unit;
both are already included.

## How do we run PowerShell builds?

From `module_12_bst_avl/code`:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 -StudentTests
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 -Comparison
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 -CompileOnly
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 -Sanitize
```

The default target is `lab`. `-CompileOnly` builds the selected driver
executable without running it. Clang/GCC use AddressSanitizer and
UndefinedBehaviorSanitizer with `-Sanitize`; MSVC uses AddressSanitizer.
Sanitized executables use `build-sanitize/` separately from `build/`.

For Make sanitizer builds, choose a separate output directory:

```sh
make -C module_12_bst_avl/code core student-tests comparison \
  CC=clang BUILD_DIR=build-sanitize \
  CFLAGS='-std=c11 -Wall -Wextra -Wpedantic -Wconversion -Wshadow -g -fsanitize=address,undefined -fno-omit-frame-pointer'
```

Do not define `NDEBUG`: these drivers use active assertions.
Keep warning output. The included Module 2 source currently produces
warnings for older no-argument declarations, an `int`-to-`char` assignment,
and an unused `data_read` local under Clang's strict flags. These are
inherited warnings; the current AVL source has no uninitialized-root
warning. The build does not suppress or promote warnings to errors.

## What do the drivers add?

`lab_test_support.h` provides a fresh-build reset, guarded fresh-ID
insertion, an ordinary BST baseline, a visited-record search counter, and
an independent representation validator. None is exported by `lab.c`.
The validator tracks IDs before following children, rejects cycles/shared
children, compares the full inserted-ID set, checks sorted inorder, derives
actual height from links, and compares each stored height and balance.

It runs in `O(n)` time for a generalized `n`-node tree. Baseline validation
skips AVL height/balance checks because the unbalanced baseline does not
maintain those heights. Diagnostic work is excluded from algorithm counts.

Core checks include all four three-key cases; LL/RR/LR/RL transfers with
nonempty middle subtrees; equal values on distinct IDs; empty, singleton,
and ten-slot builds; the exact comparison table; and all 5,040 permutations
of seven labels, checking invariants after each insertion.

With A=0 through G=6, the fixture orders are `ABCDEFG`, `GFEDCBA`, and
`DBFACEG`. Plain BST heights are `6,6,2`; listed deepest present/missing
searches visit `7,7,3` records. All AVL builds have root D at ID 3, height
2, and three visited records for the corresponding probes. See the
[lab](../student/lab.md) for the exact present/missing labels.

## Which files are optional references?

The directories `include`, `starter`, `solution`, `support`, and `autopsy`,
and the older `test_core.c`, `test_extension.c`, and `test_student.c` retain
the separate 64-node pointer API. It uses unique integer keys, allocation
and status codes, strict validators, and iterative destruction. Those
contracts do not describe the required indexed lab.

Existing named builds are preserved:

```sh
make -C module_12_bst_avl/code solution-core solution-extension
make -C module_12_bst_avl/code starter-compile
make -C module_12_bst_avl/code autopsy
make -C module_12_bst_avl/code autopsy-unsafe
```

`starter-*` tests intentionally fail until the optional TODOs are complete.
`autopsy` runs only the safe pointer-library inspection branch.
`autopsy-unsafe` compiles the isolated leak demonstration with sanitizers
and never runs it automatically. PowerShell retains `-Target solution`,
`-Target starter`, `-Extensions`, and `-Target autopsy`; the unsafe variant
requires `-Target autopsy -UnsafeAutopsy -Sanitize`.
