# Chapter 5. Visiting nodes in a tree

## Starting question

> After a child finishes, how does its parent know which work to do next?

A recursive call frame remembers the paused position. The explicit stack
version remembers the node index and its next progress step. Preserve
first predictions before introducing traversal names.

## Thinking logically: board walkthrough

Use the revised [textbook](../module_05_tree_dfs/student/textbook.md)
and the [lab](../module_05_tree_dfs/student/lab.c). Follow the textbook's
questions from traversal through expression construction and writing.
Introduce its **Glossary** terms after students explain the examples.

1. Initialize and connect Chapter 2's alphabet tree. Root 5 contains `F`;
   its children are `A [0]` and `G [6]`. `A` has `B [1], C [2]`, and `B`
   has `D [3], E [4]`. `nodes_size` is 10, but only seven are reachable.
2. Trace preorder `F A B D E C G`, inorder `D B E A C F G`, and postorder `D E B C A G F`
   at the three visit comment positions. The source does not record or
   print those symbols; use written traces or debugger observations.
   Each leaf makes two calls on `-1`, which return at the base case.
3. Replace recursive frames with stack indices and progress. Step 0 marks
   preorder and pushes left, step 1 marks inorder and pushes right, and
   step 2 marks postorder and pops. Progress advances before a child is
   pushed. The wrapper passes `peek()` to `tree_traversal_proceed(int i)`.
   Include sentinel pushes and immediate pops in the trace. A second run
   requires resetting progress from 3 to 0.
4. Prepare the textbook's `postfix`, `12+34-*`, then trace construction:
   `[0] → [0,1] → [2] → [2,3] → [2,3,4] → [2,5] → [6]`. Each operator
   pops right then left. The final pop returns root 6, leaving `top == -1`
   and `nodes_size == 7`. Its left subtree is `1+2`; its right is `3-4`.
   Construction records these connections without calculating a value.
5. Compare bare inorder `1+2*3-4` with the writer's `(1+2)*(3-4)`.
   Both children need grouping before the root's multiplication. The left
   comparison is child `<` parent precedence; the right is child `<=`
   parent. Use `832--` to explain `8-(3-2)`: the right child has equal
   precedence. `prec2()` returns 3 for digits and delegates operators to
   Chapter 4's `prec()`, whose maximum is 2.
6. Follow `write_char()` and the parentheses around each child call.
   `write_infix()` resets `infix_pos` before the helper and appends `'\0'`
   afterward. For `(1+2)*(3-4)`, final `infix_pos` is 12. A repeated write begins
   at index 0; child calls share the advancing position. Count grouped
   `1+(2+(3+4))`: twelve bytes with its terminator fit `infix[20]`.

For optional reconstruction, reuse preorder `F A B D E C G` and inorder
`D B E A C F G`. Root `F` splits inorder into `D B E A C` and `G`.
The left subtree has five nodes, selecting preorder `A B D E C`; split
again at `A`, then `B`. Verify postorder `D E B C A G F` and explain why
distinct labels matter. No reconstruction function is supplied in `lab.c`.

The existing worksheets retain `123*+` for construction and the separate
`A`-rooted reconstruction (`ABDECFG`, `DBEAFCG`) from the companion
[concept slides](../module_05_tree_dfs/student/ppt_material.md). Treat them as additional
practice; the answer key covers both sets. The
[lab slides](../module_05_tree_dfs/student/ppt_lab_material.md) cover the
same core algorithms.

## Common first thoughts and neutral questions

- “Ten initialized nodes means ten visits.” Which nodes are reachable?
- “The comments save the orders.” What action executes at each comment?
- “A stack index alone replaces a recursive frame.” Where is the next step kept?
- “Resetting the stack restarts traversal.” What progress remains after a run?
- “All traversal orders describe the same example.” Which root does each example use?
- “The first pop is the left child.” What tree would that build for `12-`?
- “Bare inorder preserves meaning.” Does `1+2*3-4` multiply the two subtrees in our expression tree?
- “Both precedence helpers treat digits alike.” What do `prec()` and `prec2()` return?
- “Every equal-precedence child needs parentheses.” Which side already groups first?
- “Every traversal wrapper resets its state.” Which reset is in the writer, and which is absent from stack traversal?
- “Seven tokens need only eight output bytes.” How many parentheses does `1234+++` produce?

## Calculating efficiency and invariant

Use the textbook's four efficiency topics to distinguish fixed array
storage, used traversal memory, constant work per created node, and linear
work over a complete tree. Both traversals and writing take linear
reachable-node time; construction is linear in tokens. Used path/call
storage is `O(h + 1)`, with separate per-node progress storage.

Then use the four **Invariant** questions: state the rules, their benefit,
what breaks when they fail, and how to preserve them. Focus on valid child
links, saved traversal progress, complete subtrees on the postfix stack,
and the written prefix before the shared output position.

## Coding plan, syntax, and evidence

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

Connect **Coding plan** to **New C syntax explained** and **C code**:
locate early `return`, one-time `{0}` initialization, `progress[i]++`,
the `switch` cases, and the shared `infix_pos++`. Distinguish resetting the
writer cursor on each complete call from initializing global progress once.

Run `make lecture` from `module_05_tree_dfs/code`, then `make lab-tests`.
Predict completion, progress, and conversion/build/write output before
running; trace or debug for complete visit orders. The existing driver
starts with Chapter 4's converted expression `123*-4+`, so its expected
output is listed separately in the answer key.

The pointer-based copy/print/evaluate starter, its tests, and autopsy
remain a separate assignment. Graph visited state comes later.

## Final check

> For `832--`, what does the current writer emit, why is the right subtree
> parenthesized, and what happens if the same tree is written twice?

It emits `8-(3-2)` because the right child has equal precedence to its
parent and must remain grouped before the outer subtraction. Each write
starts at position 0 and ends at position 8 including the terminator.
No writer reset or parentheses extension is needed for this repeated output.
