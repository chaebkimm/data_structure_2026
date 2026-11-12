# Module 12 — AVL Insertion with Node Indices

This package follows the complete supplied [student/lab.c](student/lab.c).
It reuses Module 2's ten `TreeNode` slots, stores child links as integer
indices, and keeps current edge heights in `height[10]`. A driver supplies
`main`, initializes fresh nodes, and keeps the root returned by `_add`.

The required work is to predict, trace, compare, and test this source.
There are no required implementation TODOs. Submit one Week 12 artifact
using [student/lab.md](student/lab.md) and the
[evidence record](student/evidence_template.md).

## Opening order

Stage A–E are checkpoints within one 180-minute lesson. This archive
contains the complete material; the instructor controls when to open it.

1. [Stage A](release/stage_a_README.md): preserve an initial arrangement
   model before reading formal names or supplied code.
2. [Stage B](release/stage_b_README.md): reveal the representation and
   preserve the three-target Cognitive Pause.
3. [Stage C](release/stage_c_README.md): trace insertion, rotations, and
   stored heights using either worksheet format.
4. [Stage D](release/stage_d_README.md): compare preserved work with the
   textbook and exact models.
5. [Stage E](release/stage_e_README.md): execute tests and assemble evidence.

## Build

With GNU Make, run from the extracted archive root:

```sh
make -C code lab-compile core student-tests comparison
```

The [code guide](code/README.md) also provides direct compiler and
PowerShell commands. Each test driver includes the supplied source exactly
once. Do not link a separately compiled copy of either included `lab.c`.

## Representation and calling contract

- Node IDs are `0..9`; a missing child or empty root is `-1`.
- Data are `char` values. Heights use `height(-1)=-1`, `height(leaf)=0`.
- Initialize a fresh node's `left` and `right` to `-1` before insertion.
- Insert each node ID only once; maintain `root = _add(root, new_node)`.
- Begin with an empty tree or a valid AVL tree whose cached heights agree
  with its links. Respect the ten-slot capacity before calling.
- Equal values are accepted. They descend left on insertion, but rotation
  may put an equal value on either side; inorder data remain nondecreasing.

The lab does not check invalid indices, full capacity, repeated node IDs,
or malformed input. It has no allocation or rejection-status API. The
baseline BST, comparison counter, and independent validators belong to the
test drivers rather than the lab.

The optional pointer-based API remains in the instructor's repository and
is excluded from this student archive. Its 64-node limit, allocation
contracts, duplicate rejection, and implementation TODOs do not define
this lesson.
