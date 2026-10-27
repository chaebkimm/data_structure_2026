# Data Structures Course Guide

This guide explains how to use the `student/textbook.md` file for each chapter during class. It does not replace the student textbook. Do not give the answers first. Instead, let the students explain why a new method is needed in their own words, and then give it a formal name.

## Standard Flow for a Chapter

1. Ask the **Starting Question** exactly as it is written.
2. Write down the student's first answer without fixing it.
3. In **Why We Need This**, check the exact point where the old method fails or gets stuck.
4. Reveal the state of the **Board Walkthrough** one step at a time. Ask them what the next state will be before showing it.
5. Summarize the new idea in easy words, and then introduce the formal name.
6. Check **Common First Thoughts** using neutral questions. Do not ask questions that already contain the answer.
7. Do not use any names in your explanations that are outside the **Vocabulary Rules**.
8. For the **Final Check**, listen to both the student's final result and their reason for it.

## Standards for Oral Explanations

Check if the student can explain all three of these parts in their own words:

1. The problem we need to solve and why the old method fails.
2. The easy new idea and its formal name.
3. How the state changes in a main example and why it happens that way.

## Relationship Between the 14-Week Course and the Chapters

| Class Week | Chapters | Teaching Rules |
| --- | --- | --- |
| 1–6 | Chapters 1–6 | Completed sequence; existing materials retained. |
| 7 | Chapter 7 | Acyclic index links, predecessor insertion/detachment, shared-pool reuse and stale-access rules; linked LIFO Stack and FIFO Queue applications in one lab following `student/lab.c`. |
| 8 | Chapter 8 | Retrieve Module 7's linked queue, compare linear/circular array queues, and use the same linked queue for tree BFS and graph/maze BFS with distances, shortest predecessors, and path recovery in one lab. |
| 9 | Chapter 9 | Hash Table: pooled collision chains, signed hashing, and two sum. |
| 10 | Chapter 10 | Fixed integer min/max Heap, bottom-up construction, and two indexed ID Heaps for common on-time; one lab-driver submission. |
| 11 | Chapter 11 | Indexed-Heap Dijkstra traces and tests in Practical 2. |
| 12 | Chapter 12 | Combined BST-to-AVL lesson; deletion optional. |
| 13 | Chapter 13 | Linear and first-match binary search, stable insertion/merge sorting, and consolidation through a workload-selection memo; one artifact. |
| 14 | DSU reference from Module 7 + Chapter 14 | Introduce DSU and Kruskal in one lab; Prim demonstration only. |

The 14 teaching packages and chapters are numbered consecutively from 1 to 14, matching the teaching weeks. Module 7 applies linked lists to a stack and a queue. Module 8 compares queue representations and reuses that linked queue for tree BFS and graph BFS.

The total class time for a single week must not go over 180 minutes. The board walkthroughs in these files are just one piece of the core explanation. Manage the time so it stays under 180 minutes by adding in your separate coding practice and test times.

## Chapter-by-Chapter Guide

| Chapter | Teaching guide |
|---:|---|
| 1 | [When the Array is Too Small, Move It](chapter_01.md) |
| 2 | [Making a Hierarchy with Addresses](chapter_02.md) |
| 3 | [Storing Relationships in Multiple Directions](chapter_03.md) |
| 4 | [Take Out the Last Added Value First](chapter_04.md) |
| 5 | [Depth-First Traversal and Expression Trees](chapter_05.md) |
| 6 | [How Not to Get Lost in a Graph](chapter_06.md) |
| 7 | [Linking Array Nodes and Reusing Slots](chapter_07.md) |
| 8 | [Queues, Tree BFS, and Graph BFS](chapter_08.md) |
| 9 | [Finding Large Numbers in a Small Table](chapter_09.md) |
| 10 | [Binary Heaps and Common On-Times](chapter_10.md) |
| 11 | [Finding the Path with the Smallest Cost](chapter_11.md) |
| 12 | [Fixing a Search Tree that Collapses to One Side](chapter_12.md) |
| 13 | [Searching, Sorting, and Consolidation](chapter_13.md) |
| 14 | [Connecting All Vertices at the Lowest Cost](chapter_14.md) |

The required scope of what to teach is decided by the [14-Week Delivery Guide](../Data_Structures_Course_2026_14_Week_Delivery_Guide.md). The order of the vocabulary terms follows the [Korean Textbook Style Guide](../TEXTBOOK_STYLE_GUIDE.md).
