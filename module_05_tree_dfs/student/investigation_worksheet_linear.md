# Stage C — Investigation Worksheet: Linear Format

Use [`lab.c`](lab.c), the [textbook](textbook.md), and
[`ppt_material.md`](ppt_material.md). Preserve predictions before tracing or
running the [lecture demo](../code/lecture/lab_demo.c). The current lab uses
single-digit operands and binary `+ - * / %`, with nonempty valid postfix
text of at most seven tokens and no spaces. The stack traversal and writer
are single-run operations. Parentheses and repeated-run resets are
extensions to reason about, not implemented behavior.

Keep a separate numbered record with a prediction, trace, and explanation
for each task. These tasks match the standard worksheet.

1. **Follow and visit the alphabet tree.** Run `alphabet_init()` and `tree_connect()` on paper. Record the root index
   and character, `nodes_size`, reachable count, and unreachable characters.
   Explain `-1` links and why connecting a child does not move it. Trace each
   complete assignment sequence and final value of `pre_data`, `in_data`,
   and `post_data`. Do the globals save those sequences?

2. **Explain saved recursive work.** While processing `D`, list the active real-node calls and each caller's
   remaining work. Give the height in edges and maximum active real-node calls.
   Locate the negative-index base case. What happens in `tree_traversal(-1)`?
   How many empty-child calls does a leaf make? Distinguish real-node calls
   from the extra empty-child frame.

3. **Replace calls with a stack.** Trace `tree_traversal_with_stack(5)` through the first visit to `E`.
   For each step, record the top index, old progress, visit, updated progress,
   and stack from bottom to top. Include the `-1` entries. Explain how steps
   0, 1, and 2 resume preorder, inorder, and postorder work. What is the final
   progress of every reached node? Why would a second run fail to terminate,
   and what reset would support repeated runs?

4. **Reconstruct from traversal orders.** The slides give preorder `ABDECFG` and inorder `DBEAFCG`. Find the root,
   split the inorder sequence, count the two subtrees, and select their
   preorder segments. Repeat until the tree is complete; verify postorder
   `DEBFGCA`. Why must labels be distinct? Why is this `A`-rooted tree different
   from the supplied alphabet tree? Is this reconstruction implemented in
   `lab.c`?

5. **Build from postfix.** Prepare `postfix` as `123*+` before calling `build_tree_from_postfix()`.
   For each token, record its index, left and right links, stack, and
   `nodes_size`. Digits have two `-1` links. State the returned root, `top`
   after the final pop, and peak stack usage. Use `12-` to justify popping
   right before left. Does construction calculate a value? What happens to
   the alphabet nodes? Why must the initially empty `postfix` be prepared?

6. **Write inorder and preserve grouping.** For `123*+`, `12+3*`, `123--`, `12-3-`, `123++`, and `123/%`, record
   both the current writer's output and the infix expression required to
   preserve the tree. Use a fresh run for each current output. Which outputs
   lose grouping? Derive the slides' left `>` and right `>=` parentheses rules.
   When extending `_write_infix()`, where do opening and closing parentheses
   go? What does Chapter 4's `prec()` return for digits, and why must digits
   be excluded from these comparisons?

7. **Start, finish, and repeat.** Trace one `write_infix()` call for `123*+`. Record characters, terminator
   index, and final `infix_pos`. Does this wrapper reset its position? Predict
   what a second call would do. Explain the reset needed for repeated writing
   and why recursive child calls must share the advancing position. Predict
   the lecture output before running `make lecture` from
   `module_05_tree_dfs/code` (or `./build.ps1 -Target lecture` in PowerShell).
   Explain why its visit lines do not show complete traversal orders.

8. **State assumptions, capacities, and costs.** State the valid-tree and expression-tree assumptions and whether the
   builder or writer validates input or bounds. How many tokens fit in
   `postfix[8]`? Does the current output fit `infix[10]`? For the parentheses
   extension, count all characters in `1+(2+(3+4))`, including its terminator.
   How many entries would iterative traversal of a ten-node chain need when
   it also pushes absent children? Explain time and space for both traversals,
   construction, and writing using reachable nodes, tokens, and height.
   Distinguish used stack entries from reserved capacity and progress storage.
