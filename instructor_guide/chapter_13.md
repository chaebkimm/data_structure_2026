# Chapter 13. AVL Rotations and Review

**Planning summary — 2026-11-10.** Use the
[Module 13 overview](../module_13_search_sort_consolidation/README.md) and
[14-week delivery guide](../Data_Structures_Course_2026_14_Week_Delivery_Guide.md).
The existing [AVL textbook](../module_12_bst_avl/student/textbook.md),
[AVL lab guide](../module_12_bst_avl/student/lab.md), and
[AVL investigation](../module_12_bst_avl/student/investigation_worksheet.md)
remain in Module 12 and await alignment to Week 13. The existing
[Module 13 textbook](../module_13_search_sort_consolidation/student/textbook.md),
[Korean edition](../module_13_search_sort_consolidation/student/textbook_korean.md),
[workbook](../module_13_search_sort_consolidation/student/class_material.md),
[lab guide](../module_13_search_sort_consolidation/student/lab.md),
[detailed lesson plan](../module_13_search_sort_consolidation/instructor/lesson_plan.md),
and [Week 13 questions](../student_question_bank/week_13_search_sort_consolidation.md)
also await alignment. Neither old complete weekly assignment is required.
Student materials and sources are unchanged.

## Starting question and goals

> How can we shorten last week's skewed tree without losing its ordering
> rule, and when is that structure the right choice?

Students compute height and balance, recognize four repair cases, preserve
inorder and transferred subtrees, trace supplied AVL insertion, and justify
structure choices using evidence from the course.

## Teaching outline

1. Retrieve the Week 12 chain. Establish empty height `-1`, leaf height `0`,
   left-minus-right balance, and the AVL range `[-1,1]`.
2. Trace LL with C,B,A and RR with A,B,C, then LR with C,A,B and RL with A,C,B.
   Preserve nondecreasing inorder and every reachable node. Include a repair
   with a nonempty middle subtree rather than only three-node cases.
3. Trace the supplied indexed AVL source still stored in Module 12. Its
   rotation helpers rewire links; `_add` refreshes lower heights before the
   new root and returns a possibly changed subtree root. Retain that return.
   LR/RL helpers perform direct rewiring in this source, rather than calling
   two single-rotation helpers.
4. Check links, independent heights, balance, and BST/AVL comparison evidence.
   Respect valid detached IDs and the ten-slot capacity. Equal labels on
   fresh IDs descend left at insertion; rotation can place equals on either
   side while preserving nondecreasing inorder.
5. Stop new AVL instruction at minute 120. Use the final 60 minutes for course
   review, the workload-selection memo, corrections, and submission.

## Time and assessment outline

| Required contact activity | Minutes |
|---|---:|
| Retrieve the skewed-tree problem; establish height and balance | 20 |
| LL/RR followed by LR/RL rotations, preserving ordering and middle subtrees | 55 |
| Guided AVL insertion: returned roots and bottom-up height updates | 30 |
| Rotation and insertion checks | 15 |
| Course review, workload selection, corrections, and submission | 60 |
| **Total** | **180** |

One submission contains four rotation traces, insertion/link/height/balance
checks, comparison evidence, a review memo, and a corrected prediction.
No from-scratch AVL implementation or AVL deletion is required.

## Review and Module 14 bridge

Use earlier artifacts to compare arrays/lists, hash versus BST/AVL lookup,
Heap priority, DFS/BFS frontier control, and minimum-hop versus weighted routes.
Do not require new implementations of those structures. The memo states
query/update frequency, ordering needs, preparation work, and relevant costs.

Briefly explain the cost of preparing and updating a sorted snapshot.
Insertion-sort and merge-sort instruction and implementation are optional.
Module 14 supplies edge sorting and its comparator and explains increasing
weight order and ties there, without assuming a sorting lesson. DSU and MST
selection remain new learning in Week 14.

## Final check

> Which ordering and balance rules make AVL lookup predictable, and when
> would an array, linked list, hash table, Heap, or graph traversal fit better?

Require a stated workload and evidence for the choice. Distinguish local
rotation correctness from broader input validation and system guarantees.
