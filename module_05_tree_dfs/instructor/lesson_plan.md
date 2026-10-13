# Module 5 Lesson Plan

## Outcomes and materials

Use the [lab](../student/lab.c), [lab slides](../student/ppt_lab_material.md),
[textbook](../student/textbook.md), and
[chapter guide](../../instructor_guide/chapter_05.md). Follow the lab slides'
sequence: recursive DFS, explicit-stack DFS, postfix tree construction,
and precedence-aware inorder writing. The schedule totals 160 minutes
across two meetings, leaving 20 minutes within the 180-minute weekly limit.

## Meeting A — 80 minutes

1. **Follow indices (15 minutes).** Preserve initial predictions; initialize
   the alphabet tree, locate root 5, and distinguish ten slots from seven
   reachable nodes. Changing links does not move nodes.
2. **Trace recursion (25 minutes).** Record the three visit orders at the
   comment positions. They identify where data processing belongs; the lab
   does not record or print those visits. Follow a leaf's two empty-child
   calls and locate the negative-index base case. Introduce the three
   traversal names.
3. **Resume with a stack (30 minutes).** Trace progress steps 0, 1, and 2
   through `D` and `E`, including sentinel pushes/pops. Compare potential
   visit orders with recursion. Follow the wrapper's
   `tree_traversal_proceed(peek())` call and explain why progress advances
   before pushing a child. A second run needs fresh progress; trace its
   missing step-3 case on paper rather than running it.
4. **Connect saved work (10 minutes).** Explain which parent operations wait
   while a child is top. Count the four real-node entries and one sentinel
   in the example's longest path, and distinguish path storage from progress.

## Meeting B — 80 minutes

1. **Build from postfix (20 minutes).** Prepare `123*+`; trace indices,
   right-before-left pops, node count, and the final root pop. Compare with
   Chapter 4's value stack and note that construction replaces old nodes.
2. **Write with grouping (25 minutes).** Trace the implemented writer for
   `123*+`, `12+3*`, and `123--`. Compare each child with its parent using
   `prec2()`: left `<`, right `<=`. Digits get precedence 3, above every
   supported operator. Locate opening and closing parentheses around child
   calls and connect those positions to preorder, inorder, and postorder.
3. **Trace state and capacity (15 minutes).** Track `write_char()`,
   `infix_pos = 0`, and the terminator. Write another expression and explain
   why a shorter result replaces the old text. Count twelve bytes for
   `1+(2+(3+4))`, which fits `infix[20]`; contrast the eleven stack entries
   needed by a ten-node chain with an absent-child sentinel.
4. **Predict, run, inspect (10 minutes).** Predict conversion/build/write
   results, then run `make lecture`. Use written traces or breakpoints at
   the visit comments to recover full traversal orders.
5. **Count and revise (10 minutes).** Explain linear work and height-based
   path storage, with separate progress storage. Revise one prediction
   using a source statement. Explain why `123--` writes `1-(2-3)` while
   `12-3-` writes `1-2-3`.

## Supplement and scope

The [concept slides](../student/ppt_material.md) also give reconstruction
from preorder `ABDECFG` and inorder `DBEAFCG`: split at `A`, count subtree
sizes, repeat, and verify postorder `DEBFGCA`. Use the remaining 20 minutes
if needed. This `A`-rooted tree differs from the supplied `F`-rooted tree;
distinct labels make the splits unique. No reconstruction function is
supplied in `lab.c`.

Current input is nonempty valid postfix, at most seven tokens, with single
digits and binary `+ - * / %`, no spaces. The writer includes parentheses
and resets its cursor. Only the explicit traversal needs a progress reset
for reuse; input and bounds validation remain extensions. Both worksheet
formats require the same predictions, traces, and explanations.

The pointer-based starter, its tests, and autopsy form an optional legacy
comparison. The lab instructions, rubric, and evidence template distinguish
its contracts from the classroom core. The pointer iterative sample is
optional; the array-based progress traversal is core material.
