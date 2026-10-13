# Chapter 5. Depth-First Traversal and Expression Trees

## Starting question

> After a child finishes, how does its parent know which work to do next?

A recursive call frame remembers the paused position. The explicit stack
version remembers the node index and its next progress step. Preserve
first predictions before introducing traversal names.

## Board walkthrough

Use the [lab](../module_05_tree_dfs/student/lab.c),
[textbook](../module_05_tree_dfs/student/textbook.md), and
[lab slides](../module_05_tree_dfs/student/ppt_lab_material.md).
Follow the lab slides' four topics in order.

1. Initialize and connect Chapter 2's alphabet tree. Root 5 contains `F`;
   its children are `A [0]` and `G [6]`. `A` has `B [1], C [2]`, and `B`
   has `D [3], E [4]`. `nodes_size` is 10, but only seven are reachable.
2. Trace preorder `FABDECG`, inorder `DBEACFG`, and postorder `DEBCAGF`
   at the three visit comment positions. The source does not record or
   print those symbols; add a recording action to observe them at runtime.
   Each leaf makes two calls on `-1`, which return at the base case.
3. Replace recursive frames with stack indices and progress. Step 0 marks
   preorder and pushes left, step 1 marks inorder and pushes right, and
   step 2 marks postorder and pops. Progress advances before a child is
   pushed. The wrapper passes `peek()` to `tree_traversal_proceed(int i)`.
   Include sentinel pushes and immediate pops in the trace. A second run
   requires resetting progress from 3 to 0.
4. Prepare `postfix` as `123*+`, then trace `build_tree_from_postfix()`:
   `[0] → [0,1] → [0,1,2] → [0,3] → [4]`. Each operator pops right then
   left. The final pop returns root 4, leaving `top == -1` and
   `nodes_size == 5`. Construction records nodes without calculating.
5. Trace the implemented infix writer for `123*+`, `12+3*`, and `123--`:
   `1+2*3`, `(1+2)*3`, and `1-(2-3)`. Compare with bare inorder to see
   why grouping matters. The left comparison is child `<` parent precedence;
   the right comparison is child `<=` parent. `prec2()` returns 3 for digits
   and delegates operators to Chapter 4's `prec()`, whose maximum is 2.
6. Follow `write_char()` and the parentheses around each child call.
   `write_infix()` resets `infix_pos` before the helper and appends `'\0'`
   afterward. For `1+2*3`, final `infix_pos` is 6. A repeated write begins
   at index 0; child calls share the advancing position. Count grouped
   `1+(2+(3+4))`: twelve bytes with its terminator fit `infix[20]`.

The companion [concept slides](../module_05_tree_dfs/student/ppt_material.md)
also reconstruct a separate tree from preorder `ABDECFG` and inorder
`DBEAFCG`. Root `A` splits inorder into `DBE` and `FCG`; their sizes
select preorder `BDE` and `CFG`. Repeat to obtain `B` with `D, E` and
`C` with `F, G`. Verify postorder `DEBFGCA`; require distinct labels.
Use this as supplemental transfer. No reconstruction function is supplied
in `lab.c`.

## Common first thoughts and neutral questions

- “Ten initialized nodes means ten visits.” Which nodes are reachable?
- “The comments save the orders.” What action executes at each comment?
- “A stack index alone replaces a recursive frame.” Where is the next step kept?
- “Resetting the stack restarts traversal.” What progress remains after a run?
- “All traversal orders describe the same example.” Which root does each example use?
- “The first pop is the left child.” What tree would that build for `12-`?
- “Bare inorder preserves meaning.” Which grouping does bare `1-2-3` describe?
- “Both precedence helpers treat digits alike.” What do `prec()` and `prec2()` return?
- “Every equal-precedence child needs parentheses.” Which side already groups first?
- “Every traversal wrapper resets its state.” Which reset is in the writer, and which is absent from stack traversal?
- “Seven tokens need only eight output bytes.” How many parentheses does `1234+++` produce?

## Scope and evidence

Use [both inquiry formats](../module_05_tree_dfs/student/inquiry_prompt.md)
and [both worksheet formats](../module_05_tree_dfs/student/investigation_worksheet.md)
for equivalent reasoning. The [lesson plan](../module_05_tree_dfs/instructor/lesson_plan.md)
allocates 160 minutes within the 180-minute week. Use
[the answer key](../module_05_tree_dfs/instructor/answer_key.md) for traces.

The lab implements parentheses and the writer's cursor reset. Stack
traversal requires a caller-supplied progress reset before reuse. Valid
nonempty postfix contains up to seven tokens in `postfix[8]`: single
digits and binary `+ - * / %`, no spaces. The builder and writer do not
validate input or bounds. Current grouped output needs at most twelve
bytes and fits `infix[20]`. A ten-node path plus its sentinel needs eleven
stack entries, exceeding `stack[10]`; the supplied example fits.

Run `make lecture` from `module_05_tree_dfs/code`, then `make lab-tests`.
Predict completion, progress, and conversion/build/write output before
running; trace or debug for complete visit orders. Both traversals and
writing take linear reachable-node time; construction is linear in tokens.
Used path/call storage is `O(h + 1)`, with separate per-node progress
storage.

The pointer-based copy/print/evaluate starter, its tests, and autopsy
remain a separate assignment. Graph visited state comes later.

## Final check

> For `123--`, what does the current writer emit, why is the right subtree
> parenthesized, and what happens if the same tree is written twice?

It emits `1-(2-3)` because the right child has equal precedence to its
parent and must remain grouped before the outer subtraction. Each write
starts at position 0 and ends at position 8 including the terminator.
No writer reset or parentheses extension is needed for this repeated output.
