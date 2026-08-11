# Week 5 — Tree DFS with Recursive Core: Vocabulary and Questions

[All-week vocabulary and question bank](../Data_Structures_Course_2026_Student_Question_Bank.md)

Required scope: trace and implement recursive preorder, inorder, and postorder traversal, reason about active calls and `O(h)` space, trace strict-BST search, and destroy an owned tree in postorder. A complete explicit-Stack tree traversal is an optional extension.

Sources: [Module 5 teaching-package overview](../module_05_tree_dfs/README.md), [Module 5 full vocabulary reference](../module_05_tree_dfs/student/vocabulary.md), and [Weeks 1–7 anticipated-question source](01_weeks_01_07_questions.md).

## Vocabulary students will learn

| Term | Working meaning |
|---|---|
| algorithm | A precise, repeatable set of steps. |
| visit | Perform the current task at one reached node. |
| visit order | The sequence in which nodes receive the visit task. |
| tree traversal | An algorithm that visits tree nodes in a stated order. |
| subtree | One node together with every node below it. |
| depth-first search (DFS) | A method that explores one subtree deeply before returning to unfinished choices. |
| backtrack | Return to an earlier unfinished choice. |
| preorder | Visit the node, then its left subtree, then its right subtree. |
| inorder | Visit the left subtree, then the node, then its right subtree. |
| postorder | Visit the left subtree, then its right subtree, then the node. |
| recursion | A function calling itself directly or through other functions. |
| recursive call | A function call made as part of recursion. |
| base case | An input that stops further recursive calls. |
| `NULL` subtree | A missing subtree; the traversal base case that visits nothing. |
| active call | A function call that has started but has not returned. |
| return | Finish one call and continue the caller’s saved work. |
| caller | The function or program part that requested another function call. |
| call frame | Saved state for one active call, including where execution must resume. |
| runtime call stack | Bookkeeping commonly used by C to manage active function calls. |
| Stack ADT | A collection defined by last-in, first-out access. |
| tree height (`h`) | The greatest number of downward links from a node to a leaf. |
| node count (`n`) | The number of nodes in the tree being analyzed. |
| auxiliary space | Extra working storage used by an algorithm. |
| `O(n)` time | Work that may grow in proportion to the number of tree nodes. |
| `O(h)` space | Extra storage that may grow with the tree’s height. |
| output parameter | Caller-provided storage in which a function writes a result. |
| bounded output | A result limited to a stated maximum number of stored visits. |
| failure atomicity | A failed operation leaves the previous valid output or structure unchanged. |
| dynamic allocation | Obtaining storage while the program runs. |
| ownership | Responsibility for eventually releasing allocated storage. |
| postorder destruction | Release each node only after its children have been released. |
| `tree_node_release` | The supplied operation that releases one node after its children are handled. |
| `tree_destroy_postorder` | The operation that releases a whole tree child-before-parent and resets its root. |
| dangling pointer | An address that refers to storage already released. |
| binary search tree (BST) | A binary tree whose entire left subtree has smaller keys and right subtree has larger keys at every node. |
| strict ordering | An ordering rule that rejects duplicate keys. |
| BST search | Choose left or right from key comparisons until the key is found or a `NULL` subtree is reached. |
| cycle | A route that returns to an already reached node. |
| shared child | A node reached through more than one parent link. |
| visited set | Stored marks showing which nodes have already been reached; valid tree DFS does not need one. |

## Anticipated student questions

### Meaning and mental model

- What makes a traversal depth-first rather than breadth-first?
- How does recursion remember the node, next child, and return location for each unfinished branch?
- What is the difference among preorder, inorder, and postorder?
- Why is `NULL` a stopping case rather than a node that should be recorded?

### Representation and invariants

- What assumptions about cycles, shared children, and ownership do the recursive traversal functions make?
- Why can a `TreeOrder` hold at most `TREE_DFS_MAX_NODES` visits?
- What is the relationship between tree height and the number of simultaneously active recursive calls?
- Why does strict BST ordering apply to entire subtrees rather than only immediate children?

### Operations, C API, and ownership

- Which recursive traversals must I implement in the required Week 5 core?
- Why must `out_order` remain unchanged if traversal encounters a limit or invalid argument?
- What is the difference between `tree_node_release` and `tree_destroy_postorder`?
- Why must `tree_destroy_postorder` receive a pointer to the root pointer and set the caller’s root to `NULL`?

### Tracing

- For one asymmetric tree, what visit sequences result from preorder, inorder, and postorder?
- What active call frames exist immediately before and after returning from a leaf?
- How does a recursive preorder trace correspond to push/pop-like behavior on the runtime call stack?
- What branch decisions does `tree_bst_search` make for a present key and for a missing key?

### Tests and debugging

- Which tests distinguish an empty tree, singleton tree, left chain, right chain, and branching tree?
- How can a test prove that traversal records both each node’s key and its `flagged` value?
- In the Tree DFS Autopsy, what missing or misplaced base case causes the first incorrect recursive action?
- How can the live-node-count test seam reveal a leak after an insertion allocation failure or incomplete destruction?

### Complexity

- Why does a complete traversal take `O(n)` time regardless of visit order?
- Why is recursive traversal’s extra space `O(h)` rather than always `O(n)`?
- How do balanced and completely skewed shapes change `h` and BST-search time?
- Why can a very deep but valid tree still exhaust the C runtime call stack?

### Cybersecurity and interpretation

- How could a cycle or shared child turn trusted tree-recursion code into nontermination or double-free behavior?
- Why must tree shape and ownership be validated at a trust boundary before destructive traversal?
- How can adversarial key order make an unbalanced BST a performance risk?
- What does a `flagged` field demonstrate, and what security conclusion can it not establish by itself?

### Assignment and evidence

- Is recursive preorder alone required, or are recursive preorder, inorder, postorder, and postorder cleanup all core evidence?
- Is a complete explicit-Stack tree traversal required in the 14-week path?
- What must my three student-authored tests add beyond the supplied traversal cases?
- What should the tree-to-graph transfer explanation identify about assumptions that will no longer hold in Week 6?

### Transfer and prerequisites

- Which Week 2 vocabulary and strict BST rule must I understand before tracing these functions?
- How is the implicit runtime call stack related to, but different from, the Week 4 Stack ADT?
- Why will graph DFS need visited state even if tree DFS does not?
- How will inorder traversal and BST search reappear in the later AVL unit?

### Extension questions — optional

- How can an explicit Stack reproduce left-first preorder without recursion?
- Why would an iterative preorder implementation push the right child before the left child?
- What should happen if the explicit Stack’s configured limit is too small for the pending frontier?
- Is `tree_preorder_iterative` optional enrichment or required Week 5 evidence in the 14-week course?
