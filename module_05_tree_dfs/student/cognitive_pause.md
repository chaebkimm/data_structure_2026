# Stage B — Five-Minute Cognitive Pause

Use [`lab.c`](lab.c) before checking the [reveal](representation_reveal.md).
Preserve this response; add corrections afterward.

1. Distinguish `nodes_size` from reachable nodes. Where are the three visit
   hooks? What would a complete recording preserve that one overwritten
   variable cannot? Does the current source perform a recording action?
2. Compare the recursive negative-index base case with the iterative
   negative-entry pop. What do progress steps 0, 1, and 2 remember?
3. Why must `progress` be reset before a second stack traversal? Which
   reset does `write_infix()` already perform before a complete write?
4. For `123*+`, what does the stack contain before and after `*`, and why
   is the first pop the right child? What is `top` after returning the root?
5. What does the current writer produce for `12+3*` and `123--`? Explain
   the left `<` and right `<=` comparisons and digits' precedence 3.
6. How many cells does `1+(2+(3+4))` need, including `'\0'`? Which arrays
   fit that case, and which assumptions remain unchecked?

Optional transfer: split preorder `ABDECFG` and inorder `DBEAFCG` at their
root. Which tree do they describe, and what makes reconstruction unambiguous?
