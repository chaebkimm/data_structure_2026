# Week 13 lab — Which link needs repair?

Predict each state before running the [demo](../code/demo.c). Mark each key with R or B for the color of its incoming link. Use B at the root. For black height, count black keyed nodes from the root down to any missing child.

1. **Red on the right.** Insert 10 and 20 into an empty tree. Draw the tree before and after repair. Identify which key becomes the root and which key gets the red link. Group the keys joined by the red left link. Label the group as a 2-node, 3-node, or 4-node and mark its child ranges.
2. **Two reds on the left.** Start again with 30, 20, 10. Pause just after attaching 10. Draw the state after a right rotation, after the flip, and after the final root recoloring. In the drawing just before the flip, circle the three keys of the 4-node. After root recoloring, draw the three separate groups. Which step changed the child indices?
3. **A subtree moves.** In the ascending run, pause just before inserting 50. Predict the flip and the rotation. Follow 30 through both operations. Record the keys visited when searching for 30 and 35 after insertion.
4. **A flip reaches the root.** Continue with 60 and 70. Identify both nodes where colors flip on insertion of 70. Record the black height and the longest binary path in edges before and after this insertion. Explain why these two measures can change independently here.
5. **Check and review.** Try 10, 30, 20 in a fresh tree. Predict the order of repairs and compare the final tree with 30, 20, 10. Use the input array in your copy of the demo. Add an original search or invariant assertion to your copy of the checks. For the ascending seven keys, compare the number of nodes visited for 70 in the ordinary BST and the LLRB. In your review memo, choose a structure for frequent membership queries and one for ordered output after repeated updates. State a cost or assumption for each choice.

Run these commands from the module directory.

```sh
make -C code demo
make -C code check
```

The demo labels each child L or R for its position and appends B or R to the key for its incoming color. For example, `L 20R` means the left child holds 20 and its incoming link is red. With a standalone C11 compiler, build `code/llrb.c` together with `code/demo.c` or `code/check.c`.

Submit the rotation and flip drawings, the black-height and search evidence, your original assertion and output, and the workload memo as one record. Include one prediction you verified or corrected.
