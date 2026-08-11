# Week 13 — BST-to-AVL Synthesis: Vocabulary and Questions

[All-week vocabulary and question bank](../Data_Structures_Course_2026_Student_Question_Bank.md)

> **Required scope (14-week path; one submission):** This week formally introduces edge height, stored height, balance factor, and rotations; those ideas were not required in the compressed Week 8 BFS bridge. Students use the supplied complete BST baseline, implement left and right rotations, the LL/RR/LR/RL rebalance decisions, and recursive AVL insertion with validation and failure preservation. Full AVL deletion and package extensions remain optional.

Extension questions below are enrichment only and do not enlarge the required Week 13 artifact.

## Vocabulary students will learn

| Term | Working meaning |
|---|---|
| Algorithm | A defined sequence of steps for solving a problem. |
| Algorithmic-complexity denial of service | Valid attacker-chosen inputs make an operation much slower than intended. |
| Allocation | Storage reserved while a program runs. |
| Assertion | A test check that must evaluate as true. |
| AVL tree | A BST whose balance factor at every node is `-1`, `0`, or `1`. |
| Balance factor | Left-subtree height minus right-subtree height. |
| Binary Heap | A priority structure with parent-child order rather than global subtree search order. |
| Binary Search Tree (BST) | A binary tree with every left-subtree key smaller and every right-subtree key larger than the node key. |
| Binary tree | A branching structure with at most two children per node. |
| Cached or stored height | A node field containing that node's current computed edge height. |
| Child | A node directly below another node. |
| Comparison | One test that orders or matches two keys. |
| Complexity | How resource use grows as input size grows. |
| Denial of service | Preventing or delaying intended service. |
| Duplicate key | A key equal to one already stored; the strict policy rejects its insertion. |
| Edge height | Links on a longest downward route, with `height(NULL) = -1` and `height(leaf) = 0`. |
| Failure preservation | A rejected or failed insertion leaves root, links, size, keys, and ownership unchanged. |
| Global search-order invariant | Every key in an entire left subtree is smaller and every key in an entire right subtree is larger. |
| Inorder traversal | Visit the left subtree, current node, then right subtree. |
| Invariant | A rule that must hold for every valid tree state. |
| Key | The value used to order and find a record. |
| Leaf | A node with no children. |
| LL / RR case | A single-rotation imbalance caused by insertion into the outer side of a child subtree. |
| LR / RL case | A double-rotation imbalance caused by insertion into the inner side of a child subtree. |
| Memory corruption | An invalid memory read, write, or release. |
| Memory leak | Owned allocated storage that can no longer be reached and released. |
| Metadata | Values describing other data, such as a node's stored height. |
| Node | One stored record containing a key, height, and child links. |
| Ownership | Responsibility for releasing allocated storage. |
| Pointer | A C value that stores a memory address. |
| Postcondition | A rule guaranteed after a successful operation. |
| Precondition | A rule the caller must satisfy before an operation. |
| Range query | Retrieval of all keys within an ordered interval. |
| Rebalance | Repair an AVL imbalance after a mutation. |
| Recursion | An operation calls itself on a smaller part of the problem. |
| Regression test | A test checking that a repaired defect does not return. |
| Relink | Change a pointer so it refers to a different object. |
| Resource exhaustion | Use up memory, storage, processing time, or another finite resource. |
| Root | The first node of a tree or subtree. |
| Rotation | Local pointer relinking that changes shape while preserving inorder key order. |
| Sanitizer | A runtime checker for defects such as invalid memory access. |
| Skewed | Shaped mostly as one long branch. |
| Strict unique-key policy | Equal-key insertion is rejected. |
| Subtree | A node together with every node reachable below it. |
| Validator | A diagnostic operation checking ordering, height, balance, size, and ownership rules. |

### Optional-only vocabulary for extension questions

| Term | Working meaning |
|---|---|
| AVL deletion | Removal followed by height repair and any needed rebalancing back toward the root. |
| Parent pointer | A node link that points upward to its parent. |
| Red-black tree | A BST using color rules to maintain a looser logarithmic height bound. |

## Anticipated student questions

### Meaning and mental model

- What global ordering rule defines a strict binary search tree?
- Why can the same set of keys produce very different BST shapes?
- What does edge-height count, and why are `height(NULL) = -1` and `height(leaf) = 0` consistent?
- What does a node's left-minus-right balance factor reveal?
- How does an AVL tree repair local shape without changing sorted key order?

### Representation and invariants

- Which links, key, and cached-height fields belong to each AVL node?
- What ordering relationship must hold across every node's entire left and right subtrees?
- What exact relationship must hold between a node's cached height and its children's heights?
- Which balance-factor values are valid in an AVL tree?
- Why must the tree's `size` equal the number of uniquely owned reachable nodes?
- How does a Heap's parent-child priority invariant differ from an AVL tree's global search-order invariant?

### Operations, C API, and ownership

- Which complete BST baseline operations are supplied rather than rewritten in Week 13?
- What link changes must a left rotation make while preserving the middle subtree?
- In what bottom-up order must cached heights be refreshed after a rotation?
- How must recursive `avl_insert` handle a duplicate, full tree, or allocation failure?
- What storage does the `Tree` own, and what must destruction restore?

### Tracing

- Why does insertion order `30, 20, 10` require an LL repair, and which rotation resolves it?
- Why does `10, 20, 30` require an RR repair?
- Which two rotations resolve `30, 10, 20`, and why is it an LR case?
- Which two rotations resolve `10, 30, 20`, and why is it an RL case?
- How do inorder sequence, subtree ownership, and final stored heights compare before and after each repair?
- Why do ascending and descending 15-key streams produce height 14 in a plain BST but height 3 in the required AVL experiment?

### Testing and debugging

- Which focused test should isolate each of LL, RR, LR, and RL rotation behavior?
- How can a test verify duplicate rejection without relying only on the returned status?
- What evidence proves allocation failure leaves root, links, size, keys, and ownership unchanged?
- How can `tree_validate_avl` distinguish an ordering defect, stale height, excessive balance factor, size mismatch, or shared node?
- What sanitizer or allocation-count evidence can reveal a lost middle subtree after a faulty rotation?

### Complexity

- Why do BST and AVL search both take `O(h)` time for tree height `h`?
- How can an unbalanced BST make search and insertion `O(n)`?
- Why does the AVL balance invariant keep search and insertion at `O(log n)`?
- Why is a single rotation `O(1)` while full traversal, measurement, and destruction remain `O(n)`?

### Security and interpretation

- How can attacker-controlled insertion order create algorithmic-complexity denial of service in a plain BST?
- Why is degraded operation cost not the same as memory corruption?
- Why does AVL balancing not eliminate allocation failure, bounds, ownership, or input-validation risks?
- Why is using all available memory a different failure category from performing too many comparisons?

### Assignment and evidence

- What code, tests, four rotation traces, measurement table, and validation output belong in the single Week 13 submission?
- Why are edge-height and balance factor formally assessed here rather than in the compressed Week 8 tree-BFS bridge?
- Which three implementation clusters form the required AVL core?
- Why are AVL deletion, optional extension tests, and unsafe autopsy execution outside the Week 13 requirement?

### Transfer

- When would an AVL index be a better capstone choice than the Week 11 hash index?
- How does inorder DFS provide sorted evidence for the BST invariant?
- How do local AVL rotations differ from the global edge-selection decisions used by MST algorithms?
- Which failure-preservation and ownership rules carry over from linked lists and hash tables to AVL insertion?

### Extension questions

- What additional cases and repair steps would AVL deletion require?
- How could parent pointers change rotation code and ownership validation?
- How might a red-black tree trade a weaker balance rule for different update behavior?
- What experiment would compare hash-table and AVL lookup under ordinary and adversarial inputs?

## Sources

- [14-week delivery guide](../Data_Structures_Course_2026_14_Week_Delivery_Guide.md#weeks-1314--avl-mst-and-integration)
- [Master curriculum, Module 15](../Data_Structures_Course_2026_Spiral_Curriculum.md#module-15--tree-bst-to-avl-synthesis)
- [Module 15 package](../module_15_bst_avl/README.md)
- [Module 15 vocabulary reference](../module_15_bst_avl/student/vocabulary.md)
- [Consolidated Weeks 8–14 question bank](02_weeks_08_14_questions.md#week-13-bst-to-avl-synthesis-module-15)
