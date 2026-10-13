# Week 5 — Tree DFS and Expression Trees: Vocabulary and Questions

[All-week question bank](../Data_Structures_Course_2026_Student_Question_Bank.md)

Use the current [lab](../module_05_tree_dfs/student/lab.c),
[lab slides](../module_05_tree_dfs/student/ppt_lab_material.md),
[textbook](../module_05_tree_dfs/student/textbook.md),
[vocabulary](../module_05_tree_dfs/student/vocabulary.md), and
[lecture demo](../module_05_tree_dfs/code/lecture/lab_demo.c). Follow recursive
traversal, explicit-stack traversal, postfix construction, and
precedence-aware inorder writing. The companion concept slides also cover
reconstruction. The writer resets its cursor; stack traversal still needs
fresh progress before a repeated run.

## Vocabulary

Node index, child link, root, leaf, reachable node, `nodes_size`, visit,
visit position, DFS, preorder, inorder, postorder, call frame, base case,
explicit stack, `top`, progress, sentinel, height, postfix, expression tree,
infix, precedence, `prec2()`, left associativity, `write_char()`, `infix_pos`,
null terminator, wrapper, capacity, input assumption, and reconstruction.
See the linked vocabulary for working definitions.

## Representation and recursive visits

- Why are child links integers while node data is a character?
- Why is root 5 `F`, and why is `nodes_size` 10 when seven nodes are reachable?
- Does changing a child index move a node?
- How do the three visit positions produce their complete orders?
- Which data-processing actions could be added at the preorder, inorder, and postorder comments?
- Does the current lab record or print visit data at those comments?
- How does recording only the last visited character differ from retaining a complete sequence?
- Where is a negative index checked, and why does `tree_traversal(-1)` return safely?
- How many empty-child calls does a leaf make?
- Which calls are waiting while `D` is active, and what must they resume?
- How many real-node frames and extra empty-child frames can be active?
- What assumptions exclude cycles, shared children, and invalid positive indices?

## Explicit traversal

- Why must an explicit traversal remember both node index and progress?
- What do steps 0, 1, and 2 do, and why advance before pushing a child?
- How does `int step = progress[i]++;` distinguish the old step from the saved next step?
- Why does the wrapper pass `peek()` to `tree_traversal_proceed(int i)` on every iteration?
- What happens when the top is `-1`, and why must it be checked before indexing progress?
- What are the final progress values for reached and unconnected nodes?
- Why does a second unchanged traversal have no terminating step-3 case?
- What reset makes another run possible, and does resetting `top` reset progress?
- How many stack entries does a ten-node chain need with its sentinel?
- How does progress storage differ from used path storage?

## Postfix construction

- Why must the initially empty `postfix` be prepared before building?
- What does Chapter 4's default expression convert to?
- Why does token index become node index in `build_tree_from_postfix()`?
- What does each stack entry represent after every token of `123*+`?
- Why is the first pop the right child, and what would reversal do to `12-`?
- What are the returned root, `nodes_size`, and `top` after the final pop?
- Why are digits stored as characters, and does construction calculate values?
- What happens to the earlier alphabet tree?
- Why need two roots per operator and exactly one before returning?
- Does the builder validate malformed input, empty input, or capacity?

## Precedence-aware inorder output

- What does the current writer output for `123*+`, `12+3*`, and `123--`?
- How would omitting parentheses lose grouping in the latter two examples?
- Why does the implemented writer use child `<` parent on the left and child `<=` parent on the right?
- How does left associativity distinguish `1-2-3` from `1-(2-3)`?
- Why does the writer retain `1+(2+3)` without simplifying it?
- How do `prec()` and `prec2()` differ for digits, and why does precedence 3 avoid digit parentheses?
- Where do opening and closing parentheses surround each child call?
- How do the writer's preorder, inorder, and postorder comment positions relate to its actions?
- What does `write_char()` do to the shared cursor?
- Why can the alphabet tree be traversed but not passed to the writer?
- How does `write_infix(-1)` produce an empty string, and why does that not validate malformed operator nodes?

## State, capacity, and efficiency

- How does `write_infix()` reset `infix_pos` before each complete output?
- Why must child calls share the advancing position?
- Why does final `infix_pos` include the null terminator?
- How can a shorter output replace a longer previous expression?
- Which wrapper supports repeated calls itself, and which requires a caller reset?
- How many tokens fit `postfix[8]`?
- Why does grouped `1234+++` fit the current `infix[20]` buffer?
- Why can a valid seven-token binary expression require at most twelve output bytes including its terminator?
- Why are traversal and writing linear in reachable nodes, and building linear in tokens?
- Why is used path/call storage `O(h + 1)` despite separate progress storage?
- How do fixed reserved arrays differ from used space and generalized bounds?
- What do the demo's completion and progress lines show, and how can breakpoints recover visit orders?

## Supplemental reconstruction

The companion [concept slides](../module_05_tree_dfs/student/ppt_material.md)
use an `A`-rooted tree for this activity.

- How do `ABDECFG` and `DBEAFCG` reconstruct that tree?
- Why must subtree sizes determine the preorder segments?
- Why do distinct labels matter, and why is preorder alone insufficient?
- Which examples have root `A` and which have root `F`?
- Is reconstruction implemented in the current lab?
- Why can reconstruction by inorder scans take quadratic time, and how does a map help?

Use nonempty valid postfix of up to seven single-character tokens, digits
and binary `+ - * / %`, with no spaces. Keep implemented parentheses and
writer resets separate from proposed validation/progress-reset extensions
and the legacy pointer-based exercise's contracts.
