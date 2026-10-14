# Student Code Package

Start with the current array-based classroom implementation in
[`../student/lab.c`](../student/lab.c) and its bundled
[lab slides](../student/ppt_lab_material.md). Run the lecture demo and direct lab
checks from this `code/` directory:

```sh
make
make lab-tests
```

`make lecture` also runs the demo. With PowerShell and a supported C compiler:

```powershell
.\build.ps1
.\build.ps1 -Target lab-tests
```

The demo runs recursive traversal, the explicit stack, postfix conversion,
tree construction, and infix writing. The traversal visit points are comments,
so the demo reports completion and the final per-node progress values:

```text
Recursive traversal complete (visit comments).
Stack progress (A-G): 3 3 3 3 3 3 3
123*-4+ -> 1-2*3+4
Root: 6; nodes: 7; top: -1
1234+++ -> 1+(2+(3+4))
12+3* -> (1+2)*3
831-/ -> 8/(3-1)
```

The public checks cover the supplied tree, repeated traversal after resetting
`progress`, postfix operand order, and precedence-aware infix formatting.
The classroom arrays assume valid single-digit expressions within their
capacities. Reset `progress` before each stack traversal; `write_infix()` resets
its output position for each call.

Keep the extracted directory structure. The lab includes the bundled Chapter 2
and Chapter 4 files using their repository-root paths. The Makefile adds the
archive root with `-I..`; the PowerShell script resolves the same root from its
own location. Compile the demo or test source only: each includes `lab.c`.

The optional pointer-based comparison remains in `starter/tree_dfs.c` and
[`../student/lab.md`](../student/lab.md). Its three TODO operations and public
tests use a 100-node pool, single digits, `+`, and `*`:

```sh
make starter-core
make starter-student-tests
make autopsy
```

Those starter tests fail until the TODOs are complete. Their PowerShell
equivalents are `-Target starter`, `-Target starter -StudentTests`, and
`-Target autopsy`. The autopsy deliberately dereferences `NULL` when its
copy pool is full; use it as the assigned debugging example.
