# Module 5 lesson plan: Visiting nodes in a tree

## Outcomes and materials

Use the revised [textbook](../student/textbook.md), the
[lab](../student/lab.c), and the
[chapter guide](../../instructor_guide/chapter_05.md). Begin with the
textbook's `F`-rooted alphabet tree, then use `12+34-*` to connect postfix
construction with grouping-preserving infix writing. The schedule totals
160 minutes across two meetings, leaving 20 minutes within the 180-minute
weekly limit.

- **Thinking logically:** predict visit orders, explain saved work, and build and read an expression tree.
- **Calculating efficiency** and **Glossary:** distinguish reserved storage, used path space, and reachable nodes; name the ideas after tracing them.
- **Invariant:** state the rules, explain their benefit and failures, and show how each operation preserves them.
- **Coding plan**, **New C syntax explained**, and **C code:** connect each plan to its source, including progress increments, `switch`, shared output position, and termination.

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

1. **Build from postfix (20 minutes).** Prepare `12+34-*`; trace indices,
   right-before-left pops, node count, and the final root pop. Root 6 joins
   `1+2` on its left and `3-4` on its right. Compare with Chapter 4's value
   stack and note that construction replaces old nodes.
2. **Write with grouping (25 minutes).** Trace the implemented writer for
   `12+34-*`: bare inorder gives `1+2*3-4`, but the writer gives
   `(1+2)*(3-4)`. Compare each child with its parent using `prec2()`:
   left `<`, right `<=`. Use `832--` to explain `8-(3-2)` and right-side
   equality. Digits get precedence 3. Locate parentheses around child
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
   using a source statement. Explain why `832--` writes `8-(3-2)` while
   `83-2-` writes `8-3-2`.

## Supplement and scope

Use the remaining 20 minutes for the textbook's optional reconstruction.
Preorder `F A B D E C G` and inorder `D B E A C F G` identify root `F`.
Split inorder into `D B E A C` and `G`, take the five-node preorder segment
`A B D E C` for the left subtree, and repeat. Verify postorder
`D E B C A G F`; distinct labels make the splits unique. No reconstruction
function is supplied in `lab.c`.

The existing worksheets retain `123*+` for construction and the separate
`A`-rooted reconstruction from the [concept slides](../student/ppt_material.md).
Use these as additional practice, with the corresponding
answers in the answer key. The [lab slides](../student/ppt_lab_material.md)
cover the same four core algorithms; the textbook supplies this plan's
main examples and section names.

Current input is nonempty valid postfix, at most seven tokens, with single
digits and binary `+ - * / %`, no spaces. The writer includes parentheses
and resets its cursor. Only the explicit traversal needs a progress reset
for reuse; input and bounds validation remain extensions. Both worksheet
formats require the same predictions, traces, and explanations.

The pointer-based starter, its tests, and autopsy form an optional legacy
comparison. The lab instructions, rubric, and evidence template distinguish
its contracts from the classroom core. The pointer iterative sample is
optional; the array-based progress traversal is core material.
