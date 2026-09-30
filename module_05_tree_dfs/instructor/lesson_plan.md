# Module 5 Lesson Plan

## Outcomes

Students will follow child indices in [the current lab](../student/lab.c),
trace the three recursive visit positions, build an expression tree from
postfix notation, and explain the formatter's parentheses and string
termination. They will distinguish allocated slots from reachable nodes,
and an assignment sequence from a global's final value.

Use the [textbook](../student/textbook.md) and
[chapter guide](../../instructor_guide/chapter_05.md). The core schedule is
160 minutes across two meetings, leaving 20 minutes within the 180-minute
weekly limit for transitions or additional practice.

## Meeting A — 80 minutes

1. **Predict the waiting work (10 minutes).** Ask the chapter guide's
   starting question without naming the traversal orders. Preserve each
   first explanation, then have pairs identify what a caller still needs
   after a child returns.
2. **Follow indices (15 minutes).** Trace `alphabet_init()` and
   `tree_connect()`. Draw `F [5]` above `A [0]` and `G [6]`; connect
   `A` to `B` and `C`, and `B` to `D` and `E`. Students distinguish ten
   initialized slots from seven reachable nodes. Ask what changed when
   the root became 5.
3. **Trace the visits (25 minutes).** One partner follows calls and returns;
   the other records assignments before, between, and after child calls.
   Switch roles at `B`. Compare complete sequences with final values
   `G G F`, then introduce preorder, inorder, and postorder.
4. **Construct from postfix (20 minutes).** Trace `123*+` using stack
   entries that are indices. Pause before each operator so students choose
   its right and left roots. Track `top` and `size` separately. Revisit
   operand order with `12-`; no arithmetic evaluation is required.
5. **Revise and explain (10 minutes).** Pairs revise one initial prediction
   and justify it with a source statement. Individually explain what a
   stack entry represents after processing `*`.

## Meeting B — 80 minutes

1. **Retrieve and compare (10 minutes).** Reconstruct the default tree and
   its infix text. Compare it with the tree for `12+3*`; students decide
   what information a bare inorder sequence loses.
2. **Derive the parentheses rules (20 minutes).** Use `12+3*`, `12-3-`,
   `123--`, and `123++`. Ask which grouping each unparenthesized expression
   describes. Locate the left `>` and right `>=` comparisons, and connect
   them to left associativity and preservation of tree grouping.
3. **Trace output state (15 minutes).** Follow `infix[pos++]` through an
   expression and its terminating byte. Format `123++`, then `12+`; track
   the reset and new terminator separately. Explain why recursive child
   calls continue at the current position.
4. **Predict, run, inspect (20 minutes).** Run `make lecture` from
   `module_05_tree_dfs/code` using the [lecture driver](../code/lecture/lab_demo.c).
   Before running, predict `G G F` and the four expression lines from the
   textbook. Use breakpoints or a written trace for the complete visit
   sequences: the lab's traversal does not print them. Discuss any mismatch
   by locating its first differing state.
5. **Bound the work and exit check (15 minutes).** Count each reachable
   node once and identify the longest active call path. Justify the current
   output bound of eight bytes including `'\0'`. Finish with the chapter
   guide's `123--` question, including final `pos == 8`.

## Checks for understanding

- Which indices are reached from `F`, and which are only initialized?
- After a recursive child returns, which visit assignment executes next?
- Why do the traversal globals finish as `G`, `G`, and `F`?
- What do `size`, `top`, and `top + 1` count during construction?
- How do the two postfix pops preserve left and right operand order?
- What grouping does `1-2-3` encode without parentheses?
- Why can `1+(2+3)` retain parentheses even if arithmetic could remove them?
- What byte ends a new output that is shorter than the previous output?
- Which assumptions must hold before calling the builder or writer?
- How does a taller tree change the number of simultaneously active calls?

## Scope and teaching boundaries

Use nonempty, well-formed postfix strings of at most five tokens, with
single-digit operands and binary `+ - * / %`. The lab assumes valid input
and does not check malformed expressions or output capacity. It stores
indices and digit characters; it does not calculate numeric results.

The [iterative pointer example](../code/lecture/iterative_traversals.c) is
an optional extension after the core work. The existing pointer-based
starter, tests, copy/evaluation autopsy, lab instructions, rubric, and
evidence template are a separate legacy exercise package. They are not
completion requirements for this lecture. Use the current inquiry
handouts for predictions and revisions; drawing quality or response mode
does not change the reasoning expected.
