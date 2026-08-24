# Korean Textbook Style Guide

This document applies the same standards to the introductory textbook in `module_00` and the student textbooks from `module_01` to `module_16`.

## 1. Audience

The readers have learned C variables, functions, arrays, loops, and conditionals, but they are meeting data structures for the first time. Even if they have seen structs and pointers, we do not assume they are fluent in them. Each chapter assumes the reader only knows what was explained in the previous chapters. Do not explain the current chapter using terms from later chapters.

## 2. Sentences

Use a "hardboiled" writing style—short, cool precision. Do not add dramatic metaphors or threats.

* Write explanations and descriptions in short, firm, declarative sentences.
* Write questions directed at the reader as natural, direct questions. Keep question-style titles short, like "Why gather data?" or "What about memory efficiency?".
* When asking for a cause, ask directly like "Why do we...?" instead of "What is the reason that we...?".
* Do not use titles that only state a role, like "First Question", "Problem to Solve", "Checking", or "Review Question". Write titles so readers know the exact problem or core point just by reading them.
* Put only one judgment or action in a single sentence.
* Remove decorations, exaggerations, and repeating the same words.
* When shortening text, keep the sentences that connect cause and effect.
* Avoid vague words like "this", "that", or "the relevant item". Use the actual names.
* Instead of using expressions that create fear, write the exact conditions and results of a failure.
* Put the English name in parentheses after the Korean word only once, the very first time it is introduced. Keep code names exactly as they are in the original code.

## 3. Order of Introducing New Concepts

Do not throw out a new name first. Follow this exact order:

Do not start a new section right away with terms, code names, math formulas, tables, or code blocks. First, state the problem or goal that follows the previous content in one or more sentences using plain, everyday words. Do not create motivation only from programming situations the reader has never experienced; start from familiar situations if needed.

1. Show the problem to solve right now.
2. Show exactly where the already-learned method gets stuck.
3. State the necessary properties for the new method.
4. Explain the new idea in everyday language.
5. Give it a formal name.
6. Walk through a small example by hand.
7. Keep the exact same example through the code and cost explanations.

## 4. Vocabulary Rules

| Chapter | Core concepts already learned that can be used | Core concepts to be introduced for the first time here |
| --- | --- | --- |
| 01 | C variables, functions, arrays, loops, conditionals | Data structures, contiguous memory, lists, ArrayLists, dynamic arrays, indexes, elements, invariants, addresses, pointers, `NULL`, allocated space, safe expansion, and average work over many additions |
| 02 | Array-based lists, addresses, ownership, valid conditions | Hierarchy, binary tree, node, root, parent, child, ancestor, leaf, path, depth, height, subtree, fixed node space, reachability and cycles, partial link check vs overall check, strict binary search tree rules |
| 03 | Arrays, lists, trees, valid conditions | Graphs, vertices, edges, neighbors, degrees, paths, cycles, direction and weight, edge list, adjacency list, adjacency matrix, connected components of undirected graphs |
| 04 | Array-based lists and expansion, valid conditions, ownership, keeping state after failure, amount of work | Stack behavioral rules, taking out the last added value first, `push`, `pop`, `peek`, bracket checking. (Running function call storage space and depth-first search are mentioned by name only as a preview) |
| 05 | Binary trees, stacks | Depth-first search, recursive calls and stopping conditions, state remembered by running calls, preorder, inorder, and postorder traversals, call space `O(h)`, postorder deletion of separately allocated nodes |
| 06 | Directed/undirected graphs, cycles, adjacency matrices/lists, connected components, stacks, recursive calls and depth-first search | Starting vertex and reachability, visit history, differences between discovery, waiting, and processing, the order of marking after successfully pushing to the stack, counting connected components |
| 07 | Array-based lists, stack behavioral rules, ownership and keeping state after failure | Queue behavioral rules, taking out the first added value first, circular arrays, storing `head` and `size` vs calculating `tail`, physical position and logical order, policy when full |
| 08 | Binary tree depth and height, traversals, queues, depth-first search | Queue containing node-and-depth pairs, breadth-first search visiting level by level from the left. (Finding the shallowest match is optional content) |
| 09 | Graph cycles, storage methods, starting vertex, reachability, discovery and processing, queues, tree breadth-first search | Graph breadth-first search, path with the fewest edges, marking unvisited vertices, fixing the first discovered distance and previous vertex, path reconstruction |
| 10 | Array list expansion, ownership, keeping state after failure, average cost, queue logical order | Priority queue behavioral rules, rules for comparing priority then arrival order, keeping arrival order for ties, scanning the entire unsorted array and its cost |
| 11 | Priority queues with stable tie rules, array expansion, binary search trees, tree levels and depth | Complete binary tree shape, min-heap rules, moving up (bubble up) and moving down (bubble down) |
| 12 | Weighted graphs, previous vertices and path reconstruction in graph BFS, priority queues, min-heaps | Non-negative cost condition, temporary distance, updating to cheaper paths, old candidates, Dijkstra's algorithm |
| 13 | Array position calculation and keeping state after failure, remainder operation in circular arrays, gapless vertex numbers | Key and value mapping, hash functions, collisions, linear probing, empty slots, in-use slots, deleted marks, rebuilding (rehashing) |
| 14 | Node addresses and ownership, arrays and gapless numbers, connected components and cycles in undirected graphs, previewing connected nodes | Singly linked lists, preserving the next link, disjoint sets, representative roots, path compression, union by size |
| 15 | Binary search trees, height counted by edges, depth/breadth-first search | Height stored and updated in nodes, balance difference, AVL rules, four cases of imbalance and left/right rotations |
| 16 | Weighted graphs, old candidate handling in Dijkstra's, min-heaps, disjoint sets, edge lists and edge IDs | Minimum cost to connect all vertices, spanning trees, minimum spanning trees, forests, Prim's and Kruskal's algorithms |

For terms not in the table, explain their meaning immediately the first time they appear. A glossary does not replace explanations in the main text.

### Consistent Terms Across Chapters

* Graph storage methods are written as `edge list`, `adjacency list`, and `adjacency matrix`.
* General data is `data`, C types are `data types`, and abstract data types are `abstract data types`.
* Graphs that do not distinguish direction are written as `undirected graphs`.
* Search names are written as `depth-first search` and `breadth-first search`.
* The starting node of trees and heaps is written as `root`. For DSU, it is written as `representative root` to distinguish the meaning.
* Analysis that divides costs over a long task flow is written as `amortized analysis` and `amortized cost`. The cost under the condition that keys spread evenly is distinguished as `expected cost`.

## 5. Basic Flow of a Chapter

Chapter 0 briefly introduces data, data structures, workload, and memory efficiency. Chapters 1 to 16 keep the following five sections in the exact same order:

1. `Thinking Logically`: Start from a familiar problem and guide the reader through the actions, blocking conditions, and solution ideas using a sequence of questions.
2. `Calculating Efficiency`: Count the workload and memory usage of major actions separately.
3. `Glossary`: Attach formal English and Korean names to the ideas the reader has already understood in the main text.
4. `Coding Plan`: Divide the implementation steps by action and briefly write the goal of each step.
5. `C Code`: Show examples that match the actual repository's types and functions in the same order as the plan.

Use the subtitles of the first two sections mostly as questions that open up thinking. If a short descriptive title clearly answers the immediate previous question (like `The simplest method`), you can use it. Do not force readers to memorize terms first. Even if a term will be used in a later section, do not bring it up early if it is not needed for the logical flow of the current section. If there are two related structures or algorithms in a single chapter, do not duplicate the five sections; handle them together within the same flow.

## 6. Examples and Code

* Inside a single chapter, use the same values and names all the way to the end as much as possible.
* Tables, pictures, the main text, and the code must all show the exact same state.
* Code snippets must follow the exact formats and names actually used by the repository's headers and implementations.
* If a code block can fail, explain exactly what remains unchanged after the failure.
* Do not just end by saying pointers or memory rules are "dangerous." Show exactly in what order an address is lost or read incorrectly.

## 7. Explaining Workload

Count the actual work before using symbols. Use `O(1)` and `O(n)` only after explaining their meanings in Chapter 1. If a new analysis name is needed, explain it in plain, everyday words first in that specific chapter.

## 8. Completion Checklist

* Every new concept has a clear reason why it is needed.
* Every term is explained either before it is used or in the exact sentence where it is used.
* Every sentence can be understood using only the knowledge provided up to the previous chapter.
* Every code snippet and number matches the actual contracts of the chapter.
* In each step of an example, the reader can predict the next state.
* If the meaning remains exactly the same even if a sentence is deleted, delete that sentence.
* If deleting a sentence breaks the cause-and-effect link, keep that sentence.
