# Week 2 — Array-Indexed Trees: Vocabulary and Questions

[All-week vocabulary and question bank](../Data_Structures_Course_2026_Student_Question_Bank.md)

Classroom scope follows Chapter 2: connect character nodes by integer child
indices in `nodes[10]`, first as an alphabet tree and then as the addition tree
for `1+2+3`. Use `capacity` and `nodes_size` to distinguish reserved and
initialized slots. Trace `alphabet_init`, `tree_connect`, `tree_recursion`,
`eq_plus_init`, `eq_plus_connect`, and `eval`. The alphabet root is index `5`
(`F`); the addition root is index `3` (the second `+`), and evaluation returns
`6`. An absent child is `-1`; index `0` is valid. The addition code assumes
valid single digits alternating with `+` and does not parse multiplication.

The separate parser-lab extension below keeps the existing four-function
assignment and its questions. Its storage, function names, and input contract
are distinct from the classroom snippets.

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
| `char` | The C type used to store one letter, digit, or operator character. |
| `struct` | A C type grouping named members into one object. |
| member | A named value accessed with the dot after selecting a node. |
| left association | Grouping equal operators from left to right. |
| invariant | A rule every valid state must satisfy. |
| recursion | A function calling itself, with separate parameter and local values in each call. |
| base case | A stopping case requiring no further recursive call. |
| evaluation | Returning the integer answer represented by a subtree. |
| `capacity` | The number of reserved node slots, ten in the classroom array. |
| `nodes_size` | The number of initialized, in-use slots, not the number reachable from one root. |
| sibling | Another child of the same parent. |
| ancestor | A node earlier on the path from the root. |
| descendant | A node reached by following child links downward. |
| postorder | Reading the left subtree, then the right subtree, then the current node. |
| postfix increment | `i++` supplies the old value of `i`, then increases it by one. |

## Classroom questions

### Tree structure and root access

- How do child links give a hierarchy to nodes stored side by side in an array?
- Why does every non-root node have one parent, and why must following parents lead to the same root?
- Why does a binary-tree node have two child-link fields even when it has fewer than two children?
- How do we reach the whole tree from its root, and why must we skip child links equal to `-1`?

### Array storage and the alphabet tree

- What do `data`, `left`, and `right` store, and why is index `0` different from child marker `-1`?
- How does `tree_connect()` make `F` the root without moving the old subtree rooted at `A`?
- Why does `nodes_size` remain `10` even though only seven nodes are reachable from `F`?
- Why is the read order `D E B C A G F`, and why does assigning `data_read` not print those letters?

### Building the addition tree

- How does an operator become a parent whose operands can be numbers or whole subtrees?
- Why do the two `+` characters in `1+2+3` need separate nodes with links initially set to `-1`?
- How do `i`, `op`, `num`, and `root` change through both iterations of `eq_plus_connect()`?
- Why does the final root index `3` represent `(1+2)+3`, with the first `+` on its left and digit `'3'` on its right?

### Recursive evaluation and valid trees

- How do a node index, its stored digit character, and the integer returned by `eval` differ?
- Why does a digit return immediately, while a `+` waits for its left and right subtree answers?
- How do separate `i`, `l`, and `r` values in each active call let `eval(3)` return `6` without changing the tree?
- Why does the range guard in `tree_recursion` stop at `-1` but fail to detect cycles, and what valid-tree assumptions does `eval` require?

### Work and memory

- Why do the ten reserved array slots, initialized slots, and nodes reachable from one root describe different quantities?
- Why does one node initialization or one child-link assignment take constant work, while building `n` nodes takes `O(n)` time?
- Why do traversal and evaluation take `O(r)` time for `r` reachable nodes rather than all reserved array slots?
- Why does the path `F → A → B → D` have height `3`, four node calls, and briefly a fifth stopping call, giving `O(h + 1)` additional call storage?

## Separate parser-lab extension

These questions belong to the four-function lab in `code/`, after the
classroom lesson. Implement `new_node`, `term`, `terms`, and `eval_tree` to
build and evaluate `1+2*3`. This lab uses `nodes[20]`, `size`, `eq[20]`, and
`pos`. It assumes valid, nonempty input: single digits alternate with `+` or
`*`, with no spaces or parentheses, at most 19 characters, and all results
fitting in `int`. Construction preserves multiplication precedence and left
association. Each independent build resets `size` and `pos`; evaluation does
not change the tree. See the [lab](../module_02_binary_tree/student/lab.md) for
its unchanged implementation and evidence requirements.

### Additional parser vocabulary

| Term | Working meaning |
|---|---|
| `size` | The count of used nodes and the next unused node index. |
| `eq` | The array containing the expression string. |
| `pos` | The index of the next unread character in eq. |
| `'\0'` | The character terminating the expression string. |
| consume | Read a character and advance the input position. |
| term | One digit followed by zero or more multiplication-and-digit pairs. |
| precedence | The priority that groups multiplication before addition here. |

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
