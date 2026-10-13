# Stage C — Investigation Worksheet: Linear Format

Use [`lab.c`](lab.c), the [textbook](textbook.md), and
[the lab slides](ppt_lab_material.md). Preserve predictions before tracing
or running the [lecture demo](../code/lecture/lab_demo.c). Use single-digit
operands and binary `+ - * / %`, with nonempty valid postfix of at most
seven tokens and no spaces. Traversal visit comments are recording hooks;
they do not print or save values. Stack traversal requires fresh progress.
The current writer implements grouping parentheses and resets its cursor.

Keep a separate numbered record with a prediction, trace, and explanation
for each task. These tasks match the standard worksheet.

1. **Follow and visit the alphabet tree.** Run `alphabet_init()` and `tree_connect()` on paper. Record the root index and character, `nodes_size`, reachable count, and unreachable characters. Explain `-1` links and why connecting a child does not move it. Trace the symbol sequence for each visit hook. Does the source itself preserve those sequences? Compare appending to a trace with overwriting one value.

2. **Explain saved recursive work.** While processing `D`, list the active real-node calls and each caller's remaining work. Give the height in edges and maximum active real-node calls. Locate the negative-index base case. What happens in `tree_traversal(-1)`? How many empty-child calls does a leaf make? Distinguish real-node calls from the extra empty-child frame.

3. **Replace calls with a stack.** Trace `tree_traversal_with_stack(5)` through the first preorder hook at `E`. For each step, record the node index passed to `tree_traversal_proceed(peek())`, old progress, updated progress, hook, and stack from bottom to top. Include `-1` entries. Explain how steps 0, 1, and 2 resume preorder, inorder, and postorder work. What is every reached node's final progress? On paper, explain why stale progress does not select any case on another traversal, and give the caller reset needed first.

4. **Build from postfix.** Prepare `postfix` as `123*+` before calling `build_tree_from_postfix()`. For each token, record its index, data, left and right links, stack, and `nodes_size`. Digits have two `-1` links. State the returned root, `top` after the final pop, and peak stack usage. Use `12-` to justify popping right before left. Does construction calculate a value? What happens to the alphabet nodes? Why must the initially empty `postfix` be prepared?

5. **Write inorder and preserve grouping.** For `123*+`, `12+3*`, `123--`, `12-3-`, `123++`, and `123/%`, draw the tree and predict the current writer's exact output. Compare with a bare inorder recording. Which trees need parentheses? Explain the left child `<` and right child `<=` precedence comparisons. Where do opening and closing parentheses go around each recursive child call? Compare `prec()` and `prec2()` for digits, and explain precedence 3. This task reconstructs expressions; it does not evaluate their arithmetic.

6. **Start, finish, and repeat.** Trace one `write_infix()` call for `123*+`. Record characters, terminator index, and final `infix_pos`. Then write the tree for `12+3*` in the same process. Where does that complete write start? Why must recursive child calls share the cursor? Contrast the writer's reset with the stack traversal's progress precondition. Predict the lecture output before running `make lecture` from `module_05_tree_dfs/code` (or `./build.ps1 -Target lecture` in PowerShell). What can its progress report show without a symbol-recording action at the visit comments?

7. **State assumptions, capacities, and costs.** State valid-tree and expression-tree assumptions and whether the builder or writer validates grammar or bounds. How many tokens fit in `postfix[8]`? Count all characters in `1+(2+(3+4))`, including its terminator, and compare with `infix[20]`. What does `write_infix(-1)` produce? Why does that guard not validate an operator's missing children? How many entries would iterative traversal of a ten-node chain need including an absent child? Explain time and space for traversal, construction, and writing using reachable nodes, tokens, and height. Distinguish used stack entries from reserved capacity and progress storage.

8. **Optional transfer: reconstruct from traversal orders.** The general slides give preorder `ABDECFG` and inorder `DBEAFCG`. Find the root, split inorder, count the two subtrees, and select their preorder segments. Repeat until the tree is complete; verify postorder `DEBFGCA`. Why must labels be distinct? Why is this `A`-rooted tree different from the supplied alphabet tree? Is this reconstruction implemented in `lab.c`?
