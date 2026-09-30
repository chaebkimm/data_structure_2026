# Stage B — Five-Minute Cognitive Pause

Use [`lab.c`](lab.c). Answer from your trace before checking the
[representation reveal](representation_reveal.md).

1. After `alphabet_init()` and `tree_connect()`, distinguish `size` from
   the number of reachable nodes. Trace the three visit orders and state
   the final values of `pre_data`, `in_data`, and `post_data`. Why are those
   three values not complete traversal sequences?
2. While processing `D`, list the active node calls. If height `h` counts
   edges, how many calls can a deepest path keep active? Where is `-1`
   checked before a child call?
3. For `123*+`, state the stack contents just before and just after `*`.
   Explain what an entry represents and why the first pop is the right
   child. Does `eq_tree()` calculate the expression?
4. Compare the outputs for `12+3*`, `12-3-`, and `123--`. Explain the
   different comparisons for left and right parentheses.
5. Why must `start_write_infix()` both reset `pos` and append `'\0'` when
   formatting a shorter expression? Which current input limit makes the
   ten-character output buffer sufficient?
