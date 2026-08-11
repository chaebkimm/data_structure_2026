# Week 2 — Binary-Tree Foundations and BST Seed: Vocabulary and Questions

[All-week vocabulary and question bank](../Data_Structures_Course_2026_Student_Question_Bank.md)

Required scope: model a rooted binary tree in a fixed arena, translate among diagrams, indexes, and pointers, implement checked local queries and child assignment, distinguish local checks from whole-tree validation, and trace the supplied strict-BST validator. Traversal, recursion, dynamic node allocation, rotations, and balancing are deferred.

Sources: [Module 2 teaching-package overview](../module_02_binary_tree/README.md), [Module 2 full vocabulary reference](../module_02_binary_tree/student/vocabulary.md), and [Weeks 1–7 anticipated-question source](01_weeks_01_07_questions.md).

## Vocabulary students will learn

| Term | Working meaning |
|---|---|
| hierarchy | An arrangement in levels, with some items above other items. |
| node | One item in a tree. |
| tree | An empty structure or a rooted hierarchy with one parent for every other node, no cycle, and a route to every node. |
| binary tree | A tree in which each node has at most a left child and a right child. |
| root | The starting node, which has no parent. |
| parent | The node directly above another node. |
| child | The node directly below another node. |
| leaf | A node with no children. |
| ancestor | A node above another node on a path. |
| descendant | A node below another node on a path. |
| path | A sequence of nodes connected by links. |
| depth | The number of links from the root to a node. |
| height | The greatest number of downward links from a node to a leaf. |
| subtree | One node together with every node below it. |
| reachable | Able to be reached by following child links from the root. |
| cycle | A route that follows links and returns to an earlier node on that route. |
| representation | A chosen way to store or show information. |
| arena | A prepared storage area from which the program uses objects. |
| fixed arena | An arena whose size and location do not change during the activity. |
| index | A numbered array position; C starts at zero. |
| field | One named value inside a C `struct`. |
| key | A value used to identify or compare a node. |
| pointer | A value that stores a memory address. |
| `NULL` | A pointer value meaning “no object here.” |
| ownership | Responsibility for how long storage stays usable and when it is released. |
| invariant | A rule that must hold in every valid tree state. |
| local validation | Checking one node and its immediate relationships. |
| global validation | Checking the complete structure and all relationships. |
| structurally valid | Following every required rule for how tree nodes are connected. |
| malformed tree | A stored tree that breaks at least one structural rule. |
| shared child | One node referenced as a child by more than one parent. |
| orphan | An active non-root node that cannot be reached from the root. |
| binary search tree (BST) | A binary tree whose left-subtree keys are smaller and right-subtree keys are larger at every node. |
| strict BST ordering | BST ordering that rejects duplicate keys. |
| status code | A named result that reports success or a kind of failure. |
| graph | A more general relationship structure that may permit sharing or cycles. |

## Anticipated student questions

### Meaning and mental model

- What makes a collection of linked nodes a tree rather than merely a set of pointers?
- What is the difference among a root, parent, child, leaf, subtree, path, depth, and height?
- Can the same node be a leaf, a subtree root, and someone else’s child at the same time?
- Why does a binary tree limit child positions without requiring binary-search ordering?

### Representation and invariants

- How do a tree diagram, an arena index table, and `left`/`right` pointer fields describe the same state?
- Why must the root have no parent while every other active node has exactly one parent?
- Why must every arena node be reachable from the root in a completed valid tree?
- Which shared-node, cycle, out-of-arena, and orphan configurations violate the whole-tree invariant?

### Operations, C API, and ownership

- Who owns the node array passed to `tree_arena_init`, and how long must that storage remain alive?
- Why may `storage` and `keys` be `NULL` for an empty tree but not for a nonempty tree?
- What does `tree_assign_child` check locally, and why can it return `TREE_OK` for a structure that is globally invalid?
- Why must `tree_immediate_family` validate the entire structure before reporting one node’s parent?

### Tracing

- Given keys, a root index, and several child assignments, what pointers and index relationships result after each operation?
- How do I translate a pointer value back to the corresponding arena index without confusing an address with a key?
- What does a validation trace record when two parents point to the same child?
- How can a tree satisfy every local child-slot check yet still contain a cycle or unreachable node?

### Tests and debugging

- Which tests distinguish an empty tree, a singleton leaf, a one-child node, and a two-child node?
- How can a regression test expose a child pointer that accidentally points outside the arena?
- What test separates a direct self-link defect from a longer ancestor cycle?
- In the Tree Structure Autopsy, which address and parent-count evidence identifies the first broken invariant?

### Complexity

- Why can a local leaf or child-count query be constant time?
- Why does whole-structure validation need to examine more than the selected node?
- What work is required to find a node’s parent when nodes store only child pointers?
- How might adding parent pointers change operation costs, storage, and invariant complexity?

### Cybersecurity and interpretation

- How could an unchecked child index become an out-of-bounds pointer or memory-corruption defect?
- Why can shared ownership of one node lead to double cleanup later?
- How might an attacker-controlled insertion order preview poor BST performance even when ordering remains correct?
- Why should a hierarchy inferred from security records be validated rather than assumed to be a tree?

### Assignment and evidence

- Which local query and link operations must I implement for the Week 2 core?
- Am I expected to write recursion, general traversal, dynamic node allocation, rotations, or balancing this week?
- What three distinct student-authored tests would add structural evidence beyond the supplied cases?
- What should my corrected Cognitive Pause explain if my original diagram accidentally created a graph?

### Transfer and prerequisites

- Which Week 1 ideas about addresses, `NULL`, invariants, and failure preservation are reused here?
- Why will depth-first traversal require more than the local family queries implemented this week?
- Which tree restriction disappears when we generalize relationships to a graph in Week 3?
- How does the strict BST seed prepare us for later search and AVL balancing?

### Extension and deferred questions — optional or later

- Could the arena be resized safely, and which stored pointers would become invalid if it moved?
- How would individually allocated nodes change ownership and cleanup compared with the fixed arena?
- Can we write a traversal now, or is traversal intentionally deferred to Week 5?
- Are rotations and balancing part of Week 2 evidence or reserved for the later AVL unit?
