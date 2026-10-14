# Stage E — Lab

Use `student/lab.c` with `student/ppt_lab_material.md` and
`student/ppt_material.md`, also supplied in Stage D. From `code/`, run `make`
for the current lecture demo and `make lab-tests` for the direct checks.
PowerShell users can run `.\build.ps1` and `.\build.ps1 -Target lab-tests`
from the same directory. Record traversal timing, stack progress, postfix child
order, and precedence-aware infix output in the evidence record.

Keep all directories together: the Chapter 2 tree and Chapter 4 stack sources
are bundled at the paths included by `student/lab.c`. See `code/README.md` for
expected output, state resets, and capacity assumptions.

Slide links in the student material resolve to the bundled `student/` files.
Textbook links refer to files from Stage D; open those files from the Stage D
directory, whose archive location differs from the original `student/` layout.

The pointer-based copy, print, and evaluate assignment in `student/lab.md`,
`code/starter/tree_dfs.c`, and its copy-failure autopsy are optional comparisons.
