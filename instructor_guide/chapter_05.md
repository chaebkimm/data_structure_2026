# Chapter 5. Depth-First Traversal and Expression Trees

## Starting question

> After a child finishes, how does its parent know which work to do next?

A recursive call frame remembers the paused position. The explicit stack
version remembers the node index and its next progress step. Preserve
first predictions before introducing traversal names.

## Board walkthrough

Use the [lab](../module_05_tree_dfs/student/lab.c),
[textbook](../module_05_tree_dfs/student/textbook.md), and
[slides](../module_05_tree_dfs/student/ppt_material.md).

1. Initialize and connect Chapter 2's alphabet tree. Root 5 contains `F`;
   its children are `A [0]` and `G [6]`. `A` has `B [1], C [2]`, and `B`
   has `D [3], E [4]`. `nodes_size` is 10, but only seven are reachable.
2. Trace preorder `FABDECG`, inorder `DBEACFG`, and postorder `DEBCAGF`.
   The globals finish as `G G F`; they do not save complete sequences.
   Each leaf makes two calls on `-1`, which return at the base case.
3. Replace recursive frames with stack indices and progress. Step 0 visits
   preorder and pushes left, step 1 visits inorder and pushes right, and
   step 2 visits postorder and pops. Progress advances before a child is
   pushed. Include sentinel pushes and immediate pops in the trace.
   A second run requires resetting progress from 3 to 0.
4. Reconstruct the slides' separate tree from preorder `ABDECFG` and inorder
   `DBEAFCG`. Root `A` splits inorder into `DBE` and `FCG`; their sizes
   select preorder `BDE` and `CFG`. Repeat to obtain `B` with `D, E` and
   `C` with `F, G`. Verify postorder `DEBFGCA`; require distinct labels.
5. Prepare `postfix` as `123*+`, then trace `build_tree_from_postfix()`:
   `[0] → [0,1] → [0,1,2] → [0,3] → [4]`. Each operator pops right then
   left. The final pop returns root 4, leaving `top == -1` and
   `nodes_size == 5`. Construction records nodes without calculating.
6. Trace bare inorder output for `123*+`, `12+3*`, and `123--`: `1+2*3`,
   `1+2*3`, and `1-2-3`. The latter two lose grouping. Derive the slides'
   extension: parenthesize operator children using parent `>` left
   precedence and parent `>=` right precedence. Digits have `prec() == 0`
   in Chapter 4; exclude them with `is_digit()`.
7. Trace `write_infix()` once from position zero. It calls `_write_infix()`
   and terminates without resetting. For `1+2*3`, final `infix_pos` is 6.
   Reuse needs a reset in the wrapper, never in child calls. Added
   parentheses also require output-capacity analysis.

## Common first thoughts and neutral questions

- “Ten initialized nodes means ten visits.” Which nodes are reachable?
- “The globals save the orders.” What remains after the last assignment?
- “A stack index alone replaces a recursive frame.” Where is the next step kept?
- “Resetting the stack restarts traversal.” What progress remains after a run?
- “All traversal orders describe the same example.” Which root does each example use?
- “The first pop is the left child.” What tree would that build for `12-`?
- “Inorder preserves meaning.” Which grouping does bare `1-2-3` describe?
- “Digits have precedence 3.” What does the included `prec()` actually return?
- “Writing again replaces the string.” Does the wrapper reset `infix_pos`?
- “The extension fits the old buffer.” Count `1+(2+(3+4))` plus its terminator.

## Scope and evidence

Use [both inquiry formats](../module_05_tree_dfs/student/inquiry_prompt.md)
and [both worksheet formats](../module_05_tree_dfs/student/investigation_worksheet.md)
for equivalent reasoning. The [lesson plan](../module_05_tree_dfs/instructor/lesson_plan.md)
allocates 160 minutes within the 180-minute week. Use
[the answer key](../module_05_tree_dfs/instructor/answer_key.md) for traces.

The lab's current stack traversal and writer are single-run operations.
Reconstruction is conceptual; parentheses and repeated-run resets are
extensions. Valid nonempty postfix contains up to seven tokens in
`postfix[8]`: single digits and binary `+ - * / %`, no spaces. The builder
and writer do not validate input or bounds. Added grouping can require
twelve output bytes; a ten-node path plus its sentinel needs eleven stack
entries. The supplied demonstration fits the current arrays.

Run `make lecture` from `module_05_tree_dfs/code`. Predict the final visit
lines and conversion/build/write output before running; trace or debug
for complete assignment orders. Both traversals and writing take linear
reachable-node time; construction is linear in tokens. Used path/call
storage is `O(h + 1)`, with separate per-node progress storage.

The pointer-based copy/print/evaluate starter, tests, and autopsy remain a
separate assignment. Graph visited state comes later.

## Final check

> For `123--`, what does the current writer emit, what grouping is needed,
> and which changes would support the grouped output repeatedly?

The current writer emits `1-2-3`, ending at `infix_pos == 6` on a fresh run.
The tree requires `1-(2-3)` because the right child has equal precedence.
Add parentheses around that child, provide sufficient output capacity,
and reset the position before each complete write. Its grouped output
would end at position 8 including the terminator.
