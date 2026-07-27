# Syllabus - Data Structure

* **Week 1 (Linear): Asymptotic Foundations & Contiguous Memory**
* **Topics:** Static Arrays, Strings, Singly Linked Lists. Stacks (LIFO) and Queues (FIFO) implemented with basic arrays.

* **Week 2 (Algorithmic): Brute Force & State Management**
* **Topics:** Linear Search vs. basic Binary Search (on pre-sorted arrays). $O(N^2)$ Sorting (Bubble, Insertion, Selection). Introduction to Recursion and the Call Stack.

* **Week 3 (Hierarchical): Unconstrained Trees**
* **Topics:** Base cases. Basic Binary Trees and tree terminology (Root, Leaf, Height). Depth-First Traversals (Pre/In/Post-order) using naive recursion.

* **Week 4 (Associative): The Mapping Problem (Intro to Dictionaries)**
* **Topics:** The concept of Key-Value mapping. **Direct Address Tables** (using array indices as keys).

* **Week 5 (Networked): Basic Graphs & State Spaces**
* **Topics:** Graph terminology (Vertices, Edges, Directed/Undirected). Adjacency Lists vs. Matrices. Unweighted Breadth-First Search (BFS) and Depth-First Search (DFS). 

* **Week 6 (Linear): Dynamic Memory & Advanced Pointers**
* **Topics:** Overcoming static limits: Dynamic Arrays (resizing strategies, amortized $O(1)$ analysis). Overcoming one-way traversal: Doubly Linked Lists (DLLs), Circular Queues, Deques.

* **Week 7 (Exam): Midterm**

* **Week 8 (Algorithmic): Divide & Conquer**
* **Topics:** Advanced recursion (Recurrence relations, Master Theorem basics). Overcoming $O(N^2)$ sorting limits: Merge Sort, Quick Sort.

* **Week 9 (Hierarchical): Ordered Trees & Priority**
* **Topics:** Overcoming naive linear search: Binary Search Trees (BST property, Insertion, Deletion). Array-backed trees: Min/Max Heaps, Heapify, Priority Queues.

* **Week 10 (Associative): Hash Tables & Collision Resolution**
* **Topics:** Overcoming the memory waste of Week 4: Hash Functions and Modulo arithmetic. Collision resolution (Separate Chaining, Linear/Quadratic Probing). Load Factor and dynamic resizing.

* **Week 11 (Networked): Weighted Graphs & Shortest Paths**
* **Topics:** Adding edge weights. Edge Relaxation and Greedy algorithms. Dijkstra’s Algorithm.

* **Week 12 (Hierarchical Synthesis): Self-Balancing Trees**
* **Topics:** The worst-case $O(N)$ degradation problem of standard BSTs. AVL Trees (Balance factors, Tree Rotations LL/RR/LR/RL). 

* **Week 13 (Networked Synthesis): Sets & Minimum Spanning Trees**
* **Topics:** Disjoint Sets (Union-Find). Global vs. Local graph optimization. Prim’s Algorithm (Synthesizes Graphs + Heaps) and Kruskal’s Algorithm (Synthesizes Graphs + Sorting + Union-Find).

* **Week 14 (Capstone Synthesis & System Architecture)**
* **Topics:** Directed Acyclic Graphs (DAGs), Topological Sort, and Advanced Caching.
* **Capstone 1 (Networked):** "Write a program that takes an unstructured list of college course prerequisites, detects cycle errors, and outputs a valid 4-year graduation schedule." *(Synthesizes DAGs, Traversals, and Hash Maps to map course strings to nodes).*
* **Capstone 2 (Linear + Associative):** "Design an LRU Cache." *(Synthesizes Week 6 Doubly Linked Lists + Week 10 Hash Maps).*

* **Week 15 (Exam): Final**


