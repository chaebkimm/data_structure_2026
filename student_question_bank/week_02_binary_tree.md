# Week 2 — Expression-Tree Model, Binary-Tree Links, and Recursive Clearance: Vocabulary and Questions

[All-week vocabulary and question bank](../Data_Structures_Course_2026_Student_Question_Bank.md)

Required scope: represent `(3 + 5) * 2` with live local node variables, distinguish a completed binary expression from the generic binary-tree representation, use distinct left/right links, search recursively, and clear a selected subtree without releasing storage. Only `tree_find` and `tree_clear` are library functions. Initialization, guarded attachment, and detachment through the parent's chosen child link are direct operations; no parent pointer is stored in a node. Callers prevent cycles and shared children. Character constants such as `'*'` and `'+'` are simplified integer labels, not an expression-evaluation interface.

Sources: [Module 2 teaching-package overview](../module_02_binary_tree/README.md), [Module 2 vocabulary](../module_02_binary_tree/student/vocabulary.md), and [Weeks 1–7 question view](01_weeks_01_07_questions.md).

## Vocabulary students will learn

| Term | Working meaning |
|---|---|
| hierarchy | An arrangement with items at different levels. |
| tree | A hierarchy with one root and one incoming child link for every other node. |
| binary tree | A tree with at most two children per node, distinguished as left and right. |
| expression tree | A tree in which operators connect to their operands; this chapter uses one as a structural example. |
| node | One object containing data and child links. |
| root | The top node of a nonempty tree. |
| parent | The node directly above another node; this relationship needs no stored parent field. |
| child | A node directly below another node. |
| left link | The address of the left child, or `NULL`. |
| right link | The address of the right child, or `NULL`, independent of the left link. |
| ancestor | A node earlier on the path from the root to a selected node. |
| descendant | A node reached by following one or more child links downward. |
| leaf | A node whose left and right links are both `NULL`. |
| subtree | One node and all of its descendants. |
| path | A sequence of nodes connected by child links. |
| depth | The number of links from the root to a node. |
| height | The greatest number of downward links from a node to a leaf. |
| address | The location of a live object in memory. |
| pointer | A value that stores an address or a null pointer value. |
| `struct` | A C type that groups named fields into one object. |
| `&` | The operator that obtains a variable's address. |
| `NULL` | A null pointer value used to represent no child or no match. |
| `.` and `->` | Field access through a struct variable or a pointer to one. |
| lifetime | The period during which a node variable exists and may be used. |
| invariant | A rule that every valid completed tree state must satisfy. |
| cycle | A child-link route that returns to a node already on that route. |
| shared child | One node appearing in more than one child position. |
| recursion | A function calling itself on a smaller part of the problem. |
| base case | A stopping condition that needs no further recursive call. |
| cascading clearance | Resetting all nodes in a selected subtree without releasing their storage. |

## Anticipated student questions

### Meaning and mental model

- How does `(3 + 5) * 2` become a root operation, a sub-expression, and operand leaves?
- How do root, parent, child, ancestor, descendant, and subtree differ?
- Why is a node with only a right child still a valid binary-tree node?
- How do a generic binary tree's zero/one/two-child possibilities differ from a completed binary expression?

### Representation and invariants

- How do a diagram and the data, left, and right fields describe the same state?
- Why are left and right operand positions not interchangeable for every operator?
- Why must every non-root node appear in exactly one child position?
- Which no-cycle and no-sharing rules are caller responsibilities rather than automatic checks?

### Direct operations and C

- Which fields must be initialized before a local node is linked into a tree?
- Why can the C character constants `'*'` and `'+'` be stored in an `int` data field in this simplified model?
- What does `&plus` provide, and how does `root.left` differ from `node->left`?
- What must remain unchanged when the chosen child position is already occupied?

### Recursive tracing

- What stopping cases does tree_find need?
- Why does the canonical search order begin `'*', '+', 3, 5, 2`?
- Which node address is returned when several nodes store the target value?
- What unfinished work remains after the search enters the left subtree?

### Clearing and lifetime

- What happens to the data and links of every node reached by tree_clear?
- Why does clearing root.left not automatically set root.left to NULL?
- Why does a cleared node remain a live object, and why is data zero not an empty-node marker?
- Why must every linked local node variable stay alive while the tree uses its address?

### Tests and debugging

- Which cases distinguish no children, a left-only child, and a right-only child?
- How can a snapshot test prove that an occupied-side attachment made no change?
- How can a test prove that clearing the `'+'` branch preserves the right operand `2` and its position?
- Why should cycle mistakes be analyzed with diagrams rather than passed to these recursive functions?

### Complexity

- Why do initialization and a guarded child-link assignment take constant work?
- Why can an unsuccessful search inspect every node?
- Why does clearing a subtree with k nodes require work proportional to k?
- Why can recursive search and clearance use temporary call-stack space proportional to height?

### Safety and interpretation

- How can a child link back to an ancestor prevent a recursive operation from finishing?
- In the shared-child autopsy, why does clearing one branch unexpectedly change the other branch's data?
- Why is the shared child's pointer still live after clearance rather than a pointer to released storage?
- What information can be lost if an occupied child link is overwritten without checking it?

### Assignment and evidence

- What must I implement in tree_find and tree_clear?
- How should my three student-authored tests demonstrate expression construction, searching, and clearance?
- What warning-enabled and diagnostic evidence belongs in the submission?
- What should my corrected Cognitive Pause explain about links, search order, and node lifetime?

### Transfer and deferred questions

- Which Chapter 1 ideas about fixed storage, checking before mutation, and invariants are reused?
- How will Module 3 change the no-sharing and no-cycle restrictions?
- When will Module 5 formalize and compare traversal orders and introduce binary-search ordering?
- Why are allocation, parent links, root-comparison helpers, rotations, and balancing outside this lab?
