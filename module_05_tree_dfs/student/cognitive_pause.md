# Stage B — Five-Minute Cognitive Pause

Use [`lab.c`](lab.c) before checking the [reveal](representation_reveal.md).

1. Distinguish `nodes_size` from reachable nodes. Why do the three visit
   globals finish as `G G F` rather than complete sequences?
2. Compare the recursive negative-index base case with the iterative
   negative-entry pop. What do progress steps 0, 1, and 2 remember?
3. Why must `progress` be reset before a second stack traversal? Why must
   `infix_pos` be reset before a second complete write?
4. Split preorder `ABDECFG` and inorder `DBEAFCG` at their root. Which tree
   do they describe? What makes this reconstruction unambiguous?
5. For `123*+`, what does the stack contain before and after `*`, and why
   is the first pop the right child? What is `top` after returning the root?
6. What does the current writer produce for `12+3*`? How would the slides'
   parentheses extension preserve grouping, and why does it need a new
   output-capacity analysis?
