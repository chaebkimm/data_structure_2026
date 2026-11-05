# Korean Textbook Style Guide

This document applies the same standards to the introductory textbook in `module_00` and the 14 teaching packages numbered 1–14. Module 9 covers Hash Table; Module 10 combines Priority Queue and Binary Heap.

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
| 01 | C variables, functions, arrays, loops, conditionals, data, data structures, workload, memory efficiency, and the basic meanings of `O(1)` and `O(n)` | Contiguous memory, lists, fixed-capacity ArrayLists, indexes, elements, size versus capacity, invariants, indexed access, linear search, and unchanged state after rejected operations |
| 02 | Fixed arrays, array-based lists, bounds checks, invariants | Character labels, `struct` and member access with `.`, binary trees stored by child indices in a fixed array, absent child `-1`, initialized slots versus reachable nodes, node/root/parent/child/sibling/ancestor/descendant/leaf/subtree relationships, paths, edge-count depth and height, no-sharing and no-cycle rules, recursion and its stopping case, left/right/current recursive reading, addition expression trees, iterative left-to-right construction of `1+2+3`, recursive evaluation, separate local state per active call, and `O(h + 1)` additional call storage |
| 03 | Fixed arrays, size versus capacity, indexes, structs, trees, paths, cycles, valid conditions, and recursion | Directed and undirected graphs, vertices, edges, in-degree and out-degree, fixed adjacency lists, two-dimensional edge arrays, isolated vertices, maximal connected components, recursive graph depth-first search, positive discovery numbers with zero as the unvisited marker, DFS parents, traversal-dependent tree and back edges, child/parent/ancestor/descendant neighbor cases, same-pass discovery and low-link values, caller-controlled resets, prefix versus postfix increment, chained assignment, short-circuit logical AND, and hand-worked cut vertices, bridges, blocks, and block-cut forests |
| 04 | Fixed arrays, character and integer values, indexes versus counts, active prefixes, bounds, loops, conditionals, simple function calls, and expression precedence | Stack and LIFO behavior, `push`, `peek`, `pop`, underflow, and the runtime call-stack comparison; global `int stack[10]` with forward growth, last active index `top`, empty `top == -1`, item count `top + 1`, pre-increment push and post-decrement pop; unchecked operations with separate full/empty predicates; direct two-Stack calculation before sequential conversion and evaluation (`1-2*3+4 -> 123*-4+ -> -1`) using the same global Stack; `eq`, `postfix`, null-terminated scans within eight-character buffers, local output position `pos`, `while (!is_empty())` before operator reads, `switch` precedence cases, `break` for a lower-precedence operator or a popped opening parenthesis, explicit `postfix[pos++] = '\0'` after the final drain; phase-entry `top` resets, right-before-left operand pops; `eq_paren` and `infix_to_postfix_parentheses()` using opening parentheses as barriers (`1+(2+3) -> 123++ -> 6`); explicit valid-input assumptions |
| 05 | Binary trees stored by array index, recursion and stopping cases, depth-first search, expression trees, fixed-capacity stacks, postfix notation, precedence, and left associativity | Preorder/inorder/postorder visit positions in recursive `tree_traversal`, visit sequences versus overwritten globals, postfix construction using a stack of subtree-root indices and right-before-left pops, inorder formatting with asymmetric precedence comparisons, `start_write_infix` resetting and terminating output, valid-input and capacity assumptions, and `O(h + 1)` active calls versus fixed reserved arrays |
| 06 | Module 3 undirected adjacency lists, discovery numbers, DFS parents, tree/back edges, low-link values, connected components, cut vertices, bridges and blocks; Module 4 integer stack; Module 5 recursive postorder processing | One record per reached undirected edge, symmetric edge-index lookup, pending-edge stack with exact-once pending/assigned and postorder parent-edge block invariants, inclusive block extraction by the parent after a child returns using low-link comparisons, same-order low-link and extraction passes, one-component/one-call scope, and explicit reset/capacity assumptions |
| 07 | Fixed arrays, indexes, structs, explicit links, Stack/LIFO behavior, and failure preservation | Acyclic singly linked lists in `struct Linked_Node lnodes[CAPACITY]`, saved first index, integer next links and -1, safe predecessor mutation, `simple_link_lnode_to_prev` / `simple_delink_next_lnode_from_prev`, isolated detached allocations, shared-pool ownership, first-only `init_lnodes_pool` with a persistent static guard, no-argument `new_lnode()` retaining data and setting next=-1, caller payload assignment, exhaustion unchanged, explicit recycling with isolation preconditions, missing/double return and stale access, caller-linked Stack/LIFO, raw node Queue/FIFO with qhead/qtail and isolated node-index returns, caller copy-data/recycle, defined -1 no-ops, valid payload -1, invariants versus preconditions, fixed relinking versus linear traversal costs |
| 08 | Indexed binary trees, graph cycles, reachability, DFS/Stack behavior, struct declarations/member access, two-dimensional array indexing, enum constants, prefix/postfix increment, switch/break, continue, and Module 7's FIFO rule | Linear array queue of struct point values; front as the first queued data index and rear as the last queued data index when nonempty; deriving front=0/rear=-1; conceptual circular space reuse; tree level order and depth tracking; duplicate pending-node DFS entries with processed checks on pop versus BFS discovery before enqueue; maze cells as implicit graph nodes; nondecreasing pending distances and equal-move-cost shortest paths; shared right/left/down/up iterator; distance as discovery state; parent-cell path recovery beyond the distance-only lab; nested initializer braces, whole-structure copying/passing/returning, and short-circuit logical OR. Course activities also cover resets, closed borders, in-bounds wall starts, and total linear writes versus peak pending work |
| 9 | Array indexes, signed remainder, linked-node pools, free-chain recycling, unchanged state after pool exhaustion, and dense graph vertex IDs | Two-sum and complements; signed hash normalization into ten buckets; collisions and separate chaining; bucket heads versus node positions; raw payload lookup versus stored nums-index lookup; prepend order and duplicate payloads; lookup before insertion; init_lnodes_pool versus init_hashtable; complete-chain recycling; expected chain length O(1+n/b), collision worst cases, and fixed-array limits |
| 10 | Fixed arrays and active prefixes, caller preconditions, FIFO queues, binary trees, levels and depth | Priority selection, complete binary tree shape, integer min/max Heap order, mode flag, sentinel-aware position selection, sift-up/down, bottom-up heapify, closed intervals, epochs, function pointers, two ID heaps, inverse position maps, direction-aware repair, earliest shared on-time and interval exhaustion |
| 11 | Weighted graphs, previous vertices and path reconstruction in graph BFS, priority queues, min-heaps | Non-negative cost condition, temporary distance, updating to cheaper paths, old candidates, Dijkstra's algorithm |
| 12 | Binary trees, depth/breadth-first search, comparison, caller preconditions, and exact lookup | BST ordering and supplied search/insertion baseline, edge height, stored height, balance factor, AVL rules, four cases of imbalance, and left/right rotations |
| 13 | ArrayList access and first-match search, array shifts, linked lists and queues, recursion, hashing, BST/AVL ordering, Heap priority, DFS/BFS, and Dijkstra's route objective | Linear versus first-match binary search, sorted-input precondition, half-open search interval, overflow-safe midpoint, stable insertion sort, stable merge sort with caller-owned disjoint scratch, equal-key order, cost of one lookup versus sorting for repeated lookups, and workload-based consolidation of representation and algorithm choices |
| 14 | Weighted graphs, old candidate handling in Dijkstra's, min-heaps, dense IDs, connected components, graph cycles, and Module 13's sorting/stability/comparison rules | Disjoint sets, parent arrays, representative roots, iterative two-pass find, path compression, union by size, logical edge IDs, supplied edge lists and comparator, minimum spanning trees and forests, Prim's and Kruskal's algorithms |

For terms not in the table, explain their meaning immediately the first time they appear. A glossary does not replace explanations in the main text.

### Consistent Terms Across Chapters

* In Korean textbooks and webpages, use lowercase `preorder`, `inorder`, and `postorder` for traversal names, and `prefix`, `infix`, and `postfix` for notation and operator-position names. Use these English terms directly instead of Korean translations or duplicate parenthetical names.
* Graph storage methods are written as `edge list`, `adjacency list`, and `adjacency matrix`.
* General data is `data`, C types are `data types`, and abstract data types are `abstract data types`.
* Graphs that do not distinguish direction are written as `undirected graphs`.
* Search names are written as `depth-first search` and `breadth-first search`.
* The starting node of trees and heaps is written as `root`. For DSU, it is written as `representative root` to distinguish the meaning.
* Analysis that divides costs over a long task flow is written as `amortized analysis` and `amortized cost`. The cost under the condition that keys spread evenly is distinguished as `expected cost`.

## 5. Basic Flow of a Chapter

Chapter 0 briefly introduces data, data structures, workload, memory efficiency, and the basic meanings of `O(1)` and `O(n)`. It first counts concrete work in a small example, then attaches the Big O names to the observed growth patterns. The base chapter flow uses the following five sections. Preserve an explicitly adopted chapter-specific structure, including the current Chapter 8 structure below:

1. `Thinking Logically`: Start from a familiar problem and guide the reader through the actions, blocking conditions, and solution ideas using a sequence of questions.
2. `Calculating Efficiency`: Count the workload and memory usage of major actions separately.
3. `Glossary`: Attach formal English and Korean names to the ideas the reader has already understood in the main text.
4. `Coding Plan`: Divide the implementation steps by action and briefly write the goal of each step.
5. `C Code`: Show examples that match the actual repository's types and functions in the same order as the plan.

Use the subtitles of the first two sections mostly as questions that open up thinking. If a short descriptive title clearly answers the immediate previous question (like `The simplest method`), you can use it. Do not force readers to memorize terms first. Even if a term will be used in a later section, do not bring it up early if it is not needed for the logical flow of the current section. If there are two related structures or algorithms in a single chapter, do not duplicate the chapter sections; handle them together within the same flow.

### Current Chapter 8 structure

Chapter 8, *Processing data in stored order*, follows the current Chapter 2 style in both language editions: `Thinking logically` → `Calculating efficiency` → `Glossary` → `Invariant` → `Coding plan` → `New C syntax explained` → `C code`. Use compact question-led prose, one glossary heading per term, and an `Invariant` section explaining the rules, benefits, broken cases, and preservation. Distinguish maintained invariants from caller preconditions. Give C constructs focused explanations before the code, then use eight spaces per nesting level and comments that explain the state changes in documentation excerpts. The Korean edition uses the matching Chapter 1 webpage labels: `논리적으로 생각해 보기` → `효율 계산해 보기` → `용어 정리` → `규칙` → `코딩 계획` → `새로운 C 문법 설명` → `C 코드`. Keep the webpage’s stable section IDs across languages.

Chapter 8 concept prose is dry and declarative: explain properties and operations without worked numeric traces, sample-node walkthroughs, or computed example results. Put concrete worked examples in interactive webpage visuals; retain intentional exercises and their numbers in worksheets and instructor material. Preserve source-code literals and the explanation of those constructs. Define `front` and `rear` through the first and last data currently stored in a nonempty queue, then state that the C variables hold their indices. An empty queue has neither first nor last data.

The user froze `module_08_graph_bfs/student/textbook_korean.md` on 2026-11-03. Preserve its bytes, including the approved wording and comments, unless the user explicitly requests a Korean revision; see `module_08_graph_bfs/AGENTS.md` for the approved hash. English and course materials follow that manuscript and the read-only PPT references. Its seven sections have 14/2/15/4/5/3/7 subsections. The efficiency section covers queue capacity and constant-time queue operations. The invariant section centers on nondecreasing pending distances. The only new C explanations are nested two-dimensional initializer braces, whole-structure copying/passing/returning, and short-circuit logical OR; the other C constructs are prior learning. Concrete traversal counts and supplementary exercises remain in the course materials.

This is adopted guidance for the current Chapter 8 editions; do not rewrite other chapters solely to impose it. The user-owned `lab.c` and PPT sources remain read-only.

## 6. Examples and Code

* Inside a single chapter, use the same values and names all the way to the end as much as possible.
* Tables, pictures, the main text, and the code must all show the exact same state.
* Code snippets must follow the exact formats and names actually used by the repository's headers and implementations.
* If a code block can fail, explain exactly what remains unchanged after the failure.
* Do not just end by saying pointers or memory rules are "dangerous." Show exactly in what order an address is lost or read incorrectly.

## 7. Explaining Workload

Count concrete work before introducing a Big O symbol. Chapter 0 introduces `O(1)` and `O(n)` through a small worked example so students can understand notation used by the AI Tutor. Later chapters reuse those symbols only after explaining the actual work performed by the operation. If a new growth class or analysis name is needed, explain it in plain, everyday words before giving it a formal name in that chapter.

## 8. Completion Checklist

* Every new concept has a clear reason why it is needed.
* Every term is explained either before it is used or in the exact sentence where it is used.
* Every sentence can be understood using only the knowledge provided up to the previous chapter.
* Every code snippet and number matches the actual contracts of the chapter.
* In each step of an example, the reader can predict the next state.
* If the meaning remains exactly the same even if a sentence is deleted, delete that sentence.
* If deleting a sentence breaks the cause-and-effect link, keep that sentence.
