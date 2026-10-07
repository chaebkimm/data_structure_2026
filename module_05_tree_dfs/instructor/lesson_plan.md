# Module 5 Lesson Plan

## Outcomes and materials

Use the [lab](../student/lab.c), [slides](../student/ppt_material.md),
[textbook](../student/textbook.md), and
[chapter guide](../../instructor_guide/chapter_05.md). Students trace
recursive and explicit-stack DFS, reconstruct a tree from orders, build
from postfix, and distinguish bare inorder output from grouping preservation.
The schedule totals 160 minutes across two meetings, leaving 20 minutes
within the 180-minute weekly limit.

## Meeting A — 80 minutes

1. **Follow indices (15 minutes).** Preserve initial predictions; initialize
   the alphabet tree, locate root 5, and distinguish ten slots from seven
   reachable nodes. Changing links does not move nodes.
2. **Trace recursion (20 minutes).** Record the three visit sequences and
   final globals. Follow a leaf's two empty-child calls and locate the
   negative-index base case. Introduce the three traversal names.
3. **Resume with a stack (30 minutes).** Trace progress steps 0, 1, and 2
   through `D` and `E`, including sentinel pushes/pops. Compare visit
   sequences with recursion. Explain why a second run needs fresh progress;
   do not run the unchanged infinite-loop case.
4. **Reconstruct (15 minutes).** Split preorder `ABDECFG` and inorder
   `DBEAFCG` at `A`; count subtree sizes and repeat. Verify `DEBFGCA`.
   Distinguish this tree from the supplied alphabet tree and explain the
   distinct-label assumption.

## Meeting B — 80 minutes

1. **Build from postfix (20 minutes).** Prepare `123*+`; trace indices,
   right-before-left pops, node count, and the final root pop. Compare with
   Chapter 4's value stack and note that the shared array replaces old nodes.
2. **Write and compare grouping (20 minutes).** Trace the current bare
   inorder writer for `123*+`, `12+3*`, and `123--`. Derive the slides'
   parentheses extension using left `>` and right `>=`, excluding digits
   whose `prec()` value is 0. Locate where parentheses would be added.
3. **Trace state and capacity (15 minutes).** Track `infix_pos` and the
   terminator. Identify its missing reset and the progress reset required
   for reuse. Count twelve bytes for `1+(2+(3+4))` and eleven stack entries
   for a ten-node chain with a sentinel; propose capacity fixes.
4. **Predict, run, inspect (15 minutes).** Predict both visit lines and the
   conversion/build/write output, then run `make lecture`. Use written
   traces or breakpoints for full orders; the driver reports final globals.
5. **Count and revise (10 minutes).** Explain linear work and height-based
   path storage, with separate progress storage. Revise one prediction
   using a source statement. Finish by distinguishing the current output
   `1-2-3` for `123--` from the extension's `1-(2-3)`.

## Scope and evidence

Current input is nonempty valid postfix, at most seven tokens, with single
digits and binary `+ - * / %`, no spaces. The writer and stack traversal
are single-run operations. Parentheses and repeatability are extensions;
input/bounds validation is not supplied. Both worksheet formats require
the same predictions, traces, and explanations.

The pointer-based starter, tests, autopsy, lab instructions, rubric, and
evidence template are a separate legacy package. The pointer iterative
sample is optional; the array-based progress traversal is core material.
