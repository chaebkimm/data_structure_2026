# Week 2 — Array-Index Expression Trees: Vocabulary and Questions

[All-week vocabulary and question bank](../Data_Structures_Course_2026_Student_Question_Bank.md)

Required scope: use Chapter 2's character nodes and integer child indices to
build and evaluate `1+2*3`. Implement all four functions: `new_node`, `term`,
`terms`, and `eval_tree`. Shared storage is `nodes[20]`, `size`, `eq[20]`, and
`pos`. Absent children use -1; index 0 is valid. Input is assumed valid and
nonempty: single digits alternate with `+` or `*`, no spaces or parentheses,
at most 19 characters, and all intermediate and final results fit in `int`.
Preserve multiplication precedence and left association. Evaluation returns
values without changing the tree. Each independent build resets size and pos.

Sources: [Module 2 teaching-package overview](../module_02_binary_tree/README.md),
[English Chapter 2](../module_02_binary_tree/student/textbook.md),
[Korean Chapter 2](../module_02_binary_tree/student/textbook_korean.md),
[Module 2 vocabulary](../module_02_binary_tree/student/vocabulary.md), and
[Weeks 1–7 question view](01_weeks_01_07_questions.md).

## Vocabulary students will learn

| Term | Working meaning |
|---|---|
| hierarchy | An arrangement with items at different levels. |
| tree | A connected hierarchy with one root, one parent per other node, and no cycle. |
| binary tree | A tree with at most two children per node, distinguished as left and right. |
| expression tree | Operators connected to operand subtrees, with digit leaves in this chapter. |
| node | One object containing a character and two child indices. |
| root | The node giving access to the whole tree, represented here by an index. |
| parent | The node directly above another node; no upward member is required. |
| child | A node directly below another node. |
| leaf | A node whose two child indices are both -1. |
| subtree | One node and all of its descendants. |
| path | A sequence of nodes connected by child links. |
| depth | The number of links from the root to a node. |
| height | The greatest number of downward links to a leaf. |
| index | An integer identifying a position in an array; zero is a valid node position. |
| `-1` | The absent-child marker, never an array index to access. |
| `char` | The C type used to store one digit or operator character. |
| `size` | The count of used nodes and the next unused node index. |
| `eq` | The array containing the expression string. |
| `pos` | The index of the next unread character in eq. |
| `'\0'` | The character terminating the expression string. |
| `struct` | A C type grouping named members into one object. |
| member | A named value accessed with the dot after selecting a node. |
| consume | Read a character and advance the input position. |
| term | One digit followed by zero or more multiplication-and-digit pairs. |
| precedence | The priority that groups multiplication before addition here. |
| left association | Grouping equal operators from left to right. |
| invariant | A rule every valid state must satisfy. |
| recursion | A function calling itself on a smaller part of the problem. |
| base case | A stopping case requiring no further recursive call. |
| evaluation | Returning the integer answer represented by a subtree. |

## Anticipated student questions

### Meaning and mental model

- How does `1+2*3` become an addition root with a multiplication subtree?
- How do root, parent, child, ancestor, descendant, and subtree differ?
- Why can a general binary tree have a right child without a left child?
- Why does a completed operator node in this expression model require two children?

### Representation and invariants

- How do the expression string, node-array table, and hierarchy describe the same expression?
- Why is node index 0 valid while child index -1 means no child?
- Why must each non-root node occur in exactly one child position, with no downward cycles?
- How does attaching disjoint subtrees under a fresh operator preserve the tree rules?

### Node creation and C

- What does `new_node` store, initialize, increment, and return?
- How do a stored digit character, a node index, and an integer answer differ?
- How do I read `nodes[nodes[root].right].data` one step at a time?
- Why does returning the old value of `size` identify the new node correctly?

### Parsing and precedence

- What does `term()` consume, and why does it leave the next `'+'` unread?
- Why does `terms()` call `term()` for a whole operand instead of reading one digit?
- How do `eq[pos]` and `eq[pos++]` differ when tracing the next unread character?
- Why do repeated equal operators make each new operator the parent of the previous subtree?

### Recursive evaluation

- What is the digit-leaf base case, and why does subtracting `'0'` produce its integer value?
- What unfinished work waits while `eval_tree` evaluates a child subtree?
- Why do the canonical completed calls return 1, 2, 3, 6, and 7?
- Why do the operator characters and parser state remain unchanged after evaluation?

### Tests and debugging

- Which test shows that a digit-only expression can return root index 0?
- How can checking links reveal an association error that an answer-only test misses?
- How can member snapshots and a second evaluation establish nonmutation?
- Why must every independent test build reset both size and pos and copy a valid expression?

### Complexity

- Why do reserving a node and assigning one child link each take constant work?
- Why does the two-level parser take time proportional to the number of characters?
- Why does evaluation visit every expression-tree node once?
- How do the fixed 20-node array, its occupied slots, and the evaluator's call-stack depth differ?

### Input contract and autopsy

- Why do valid inputs use single digits, no spaces or parentheses, at most 19 characters, and int-sized results?
- Why does treating every operator alike turn `1+2*3` into a tree whose answer is 9?
- Why can the faulty tree satisfy the general tree rules and pass memory diagnostics while expressing the wrong grouping?
- Why should the precedence defect be repaired in construction rather than by ignoring the tree during evaluation?

### Assignment and evidence

- What must I implement in `new_node`, `term`, `terms`, and `eval_tree`?
- What new evidence should my creation, construction, and evaluation tests provide?
- What warning-enabled and diagnostic evidence belongs in the submission?
- What should my corrected Cognitive Pause explain about indices, term boundaries, and returned values?

### Transfer and deferred questions

- Which Chapter 1 ideas about fixed storage and occupied slots apply to the nodes array?
- How will a later graph model change the no-sharing and no-cycle restrictions?
- How can later traversal topics describe the child-before-parent completion order used by evaluation?
- Why are malformed-input validation, extra public functions, rotations, and balancing outside this lab?
