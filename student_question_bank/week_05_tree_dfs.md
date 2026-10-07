# Week 5 — Tree DFS and Expression Trees: Vocabulary and Questions

[All-week question bank](../Data_Structures_Course_2026_Student_Question_Bank.md)

Use the current [lab](../module_05_tree_dfs/student/lab.c),
[textbook](../module_05_tree_dfs/student/textbook.md),
[vocabulary](../module_05_tree_dfs/student/vocabulary.md), and
[lecture demo](../module_05_tree_dfs/code/lecture/lab_demo.c). Core topics
include recursive and stack-based traversal, conceptual reconstruction,
postfix construction, and bare inorder writing. Parentheses and repeated
runs are extensions to the current single-run code.

## Vocabulary

Node index, child link, root, leaf, reachable node, `nodes_size`, visit,
assignment trace, DFS, preorder, inorder, postorder, call frame, base case,
explicit stack, `top`, progress, sentinel, height, reconstruction, postfix,
expression tree, infix, precedence, left associativity, `infix_pos`, null
terminator, wrapper, capacity, and input assumption. See the linked
vocabulary for working definitions.

## Representation and recursive visits

- Why are child links integers while node data is a character?
- Why is root 5 `F`, and why is `nodes_size` 10 when seven nodes are reachable?
- Does changing a child index move a node?
- How do the three visit positions produce their complete orders?
- Why do the globals retain `G G F` rather than whole sequences?
- Where is a negative index checked, and why does `tree_traversal(-1)` return safely?
- How many empty-child calls does a leaf make?
- Which calls are waiting while `D` is active, and what must they resume?
- How many real-node frames and extra empty-child frames can be active?
- What assumptions exclude cycles, shared children, and invalid positive indices?

## Explicit traversal and reconstruction

- Why must an explicit traversal remember both node index and progress?
- What do steps 0, 1, and 2 do, and why advance before pushing a child?
- Why must the helper read the stack top again after a child finishes?
- What happens when the top is `-1`?
- Why does a second unchanged stack traversal fail to terminate?
- What reset makes another run possible?
- How many stack entries does a ten-node chain need with its sentinel?
- How does progress storage differ from used path storage?
- How do `ABDECFG` and `DBEAFCG` reconstruct the slides' tree?
- Why must subtree sizes determine the preorder segments?
- Why do distinct labels matter, and why is preorder alone insufficient?
- Which examples have root `A` and which have root `F`?
- Is reconstruction implemented in the current lab?

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

## Inorder output and extensions

- What does the current writer output for `123*+`, `12+3*`, and `123--`?
- Which outputs lose grouping, and why does bare inorder lose information?
- What parentheses would preserve each tree?
- Why does the slides' extension use `>` on the left and `>=` on the right?
- How does left associativity distinguish `1-2-3` from `1-(2-3)`?
- Why might the extension retain `1+(2+3)` without simplifying it?
- What does Chapter 4's `prec()` return for digits, and why exclude digit children?
- Where should opening and closing parentheses surround each child call?
- Why can the alphabet tree be traversed but not passed to the writer?

## State, capacity, and efficiency

- Does `write_infix()` reset `infix_pos`, and what would another call do?
- Why must child calls share the advancing position?
- Why does final `infix_pos` include the null terminator?
- Which reset permits a shorter output to replace a previous expression?
- How many tokens fit `postfix[8]`, and why does bare output fit `infix[10]`?
- Why does grouped `1234+++` exceed the existing output buffer?
- Why are traversal and writing linear in reachable nodes, and building linear in tokens?
- Why is used path/call storage `O(h + 1)` despite separate progress storage?
- How do fixed reserved arrays differ from used space and generalized bounds?
- Why can reconstruction by inorder scans take quadratic time, and how does a map help?
- How can breakpoints show full orders that the demo's final visit lines do not?

Use nonempty valid postfix of up to seven single-character tokens, digits
and binary `+ - * / %`, with no spaces. Keep current behavior separate from
extension proposals and from the legacy pointer-based exercise's contracts.
