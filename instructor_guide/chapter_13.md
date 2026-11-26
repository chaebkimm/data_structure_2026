# Chapter 13. Left-Leaning Red–Black Trees and Review

> Inserting 10 through 70 in order gave us a chain. How can we change insertion and keep the same binary search?

Use the [English chapter](../module_13_llrb/student/textbook.md) or [한국어 교재](../module_13_llrb/student/textbook_korean.md), then run the [guided lab](../module_13_llrb/student/lab.md). Sketch one key per binary node. Mark its incoming link R or B. Show the 2–3–4 representation using 10, 20, 30 in ascending order. After 10, circle one key (2-node). After 20, circle the two keys joined by a red left link (3-node). Pause after attaching 30 and before flipping at 20. Both red links now belong inside the circle (4-node). A 2–3–4 tree may keep that group. The supplied bottom-up LLRB splits it before insertion finishes. [Sedgewick’s LLRB paper](https://sedgewick.io/wp-content/themes/sedgewick/papers/2008LLRB.pdf)

| Contact activity | Minutes |
|---|---:|
| Retrieve the skewed BST and read incoming link colors | 20 |
| Draw left and right rotations, subtree transfer, and color flips | 55 |
| Trace the supplied C insertion on ascending and descending keys | 30 |
| Check ordering, red links, black height, and lookup paths | 15 |
| Course review, workload choices, corrections, and one submission | 60 |
| **Total** | **180** |

## Board walkthrough and answers

Count black keyed nodes from the root to a missing child, including the black root and excluding the missing child. Edge height counts links to the deepest keyed node. Ask students to draw the next state before revealing a row.

| Insert into the ascending sequence | Repairs on return, in order | Root after insertion | Black height | Edge height |
|---:|---|---:|---:|---:|
| 10 | Color the first root black | 10B | 1 | 0 |
| 20 | Rotate left at 10 | 20B | 1 | 1 |
| 30 | Flip at 20, then color the root black | 20B | 2 | 1 |
| 40 | Rotate left at 30 | 20B | 2 | 2 |
| 50 | Flip at 40, then rotate left at 20 | 40B | 2 | 2 |
| 60 | Rotate left at 50 | 40B | 2 | 2 |
| 70 | Flip at 60, flip at 40, then color the root black | 40B | 3 | 2 |

- After 20, the missing right child of 20 and the missing children under 10 have different binary depths. Each path has one black key. Joining the red pair yields the 3-node `[10 | 20]`. Its child ranges are below 10, between 10 and 20, and above 20.
- For 30, 20, 10 in a fresh tree, inserting 10 rotates right at 30, placing red children 10 and 30 below 20B. This is the same 4-node `[10 | 20 | 30]` that appeared in the ascending run. Flip to 20R with black children and color the root black. A flip keeps the child indices. For the transfer exercise 10, 30, 20, first rotate left at 10, then right at 30, then flip at 20 and blacken the root. Both inputs end at 20B above 10B and 30B.
- At 50 in the ascending run, follow the link to 30. After the left rotation it belongs to the right of 20. Lookups for 30 and 35 visit 40, 20, 30. Only 30 succeeds. A drawing that loses this subtree can still have the correct root.
- At 70 the second flip reaches the root. Black height grows from two to three. Edge height stays two. Searching for 70 now visits three nodes in the LLRB and seven in the ascending ordinary BST.

## Final hour and assessment

Use 20 minutes to retrieve array/list updates, hash lookup, heap priority, and BFS/weighted-route objectives. Use 20 minutes to select a structure for exact membership and for ordered output under repeated updates. Allow 20 minutes for corrections and submission.

Accept one artifact. Check that both rotations keep BST order, the new subtree root inherits the old incoming color, and the student saves the returned root. Require a black root, left-leaning red links, no consecutive reds, and equal black counts to every missing child after each completed insertion. Check one original assertion, the two search paths, and a workload choice with evidence. Hash lookup can fit exact membership under suitable distribution. An LLRB supports logarithmic updates and sorted traversal. A sorted array is reasonable for a rarely changed snapshot when the memo accounts for its preparation cost.

[Module overview](../module_13_llrb/README.md) · [Week 13 question bank](../student_question_bank/week_13_llrb.md)
