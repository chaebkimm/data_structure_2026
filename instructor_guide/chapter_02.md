# Chapter 2. Organizing Data in a Hierarchy

## Revised textbook teaching sequence

The [English textbook](../module_02_binary_tree/student/textbook.md) and
[Korean textbook](../module_02_binary_tree/student/textbook_korean.md)
follow the classroom source [lab.c](../module_02_binary_tree/student/lab.c).
They use `nodes[10]`, `capacity`, and `nodes_size`, first for letters and
then for the addition expression `1+2+3`.

Start with the revised question order:

1. What makes a hierarchy a tree? Each node stores data and child links.
   There is one root with no parent. Every other node has one parent,
   and following parents from any node leads to that root.
2. How can array positions record that hierarchy? A binary tree permits
   at most two children, stored as `left` and `right` indices. `-1` means
   absence. The number of present children can be zero, one, or two.
3. How can we access and extend it? Start at the root and follow present
   children. To attach a node, store its index in the parent's child member.
   To introduce a new root, attach the old root beneath the new parent,
   then save the new root's index.
4. How does an expression fit this model? A binary operator is a parent;
   its operands are children. An operand can itself be a whole expression.
   Digits are leaves with both links `-1`.
5. How do we build and then evaluate `1+2+3`? First record `(1+2)+3`
   through links. Then obtain child values before returning each sum.

## Textbook board examples

For the alphabet demonstration, initialize ten letters and absent links.
Connect `F(A(B(D,E),C),G)`. F at index 5 is the root; H, I, and J remain
initialized but unconnected. `nodes_size` is 10, while only seven nodes
are reachable. The left/right/current read order is `D E B C A G F`.
`tree_recursion` reads a character but does not print or return it.

For addition, prepare five separate nodes. The two `+` characters occupy
different indices. Build left to right:

| Step | New root | Left child | Right child | Expression represented |
|---|---:|---:|---:|---|
| First digit | 0 | -1 | -1 | `1` |
| First operator | 1 | 0 | 2 | `1+2` |
| Second operator | 3 | 1 | 4 | `(1+2)+3` |

The final index table is:

| Index | `data` | `left` | `right` |
|---:|---|---:|---:|
| 0 | `'1'` | -1 | -1 |
| 1 | `'+'` | 0 | 2 |
| 2 | `'2'` | -1 | -1 |
| 3 | `'+'` | 1 | 4 |
| 4 | `'3'` | -1 | -1 |

`eval(3)` waits for `eval(1)` to return 3, then obtains 3 from `eval(4)`
and returns 6. Each call has separate local `i`, `l`, and `r`. Stored
characters and links remain unchanged. The digit case stops before reading
its absent children; an operator requires two valid children. `eval` has
no range check and assumes only digit leaves and plus operators.

## Textbook checks and costs

Ask students to distinguish an array index, a stored character, and a
returned answer. Changing a root does not move data. One root accesses
one connected tree; initialized entries can remain outside it. A range
check cannot stop a cycle of valid indices or prevent shared children.

A node needs one character and two integers, plus any padding. Ten node
slots remain reserved in both demonstrations. Initialization and building
take `O(n)` for `n` slots; reading or evaluation takes `O(r)` for `r`
reachable nodes. The alphabet path F–A–B–D has three links and four nodes.
The guarded reader can briefly add a stopping call with index -1, so
extra call storage is `O(h + 1)`. Array storage is counted separately.

Check that students can explain why the second plus is root 3, why it
owns the entire first addition on its left, and why the answer 6 is returned
separately from the root index. Use **New C Syntax Explained** and **C Code**
for reading support; subsection **Ask GPT** is available on the webpage.

The remaining guide describes the existing staged application lab. It
adds `+`/`*` precedence, 20-slot arrays, node reservation, and shared `pos`.
Keep its four-function contract distinct from the six classroom functions
and seven code snippets above.

## Application-lab starting question

> How can a tree record which operation happens first, and how can the same
> function calculate the answer for every subtree?

**Expected answer:** For `1+2*3`, addition is the root. Its left child stores
`'1'`; its right child stores `'*'`, with children `'2'` and `'3'`. The
multiplication subtree supplies `6` before addition returns `7`. Every
child member stores an integer index into `nodes`, with `-1` for absence.
Index `0` identifies a real node.

## Application-lab connection to Chapter 1

Chapter 1 introduces a fixed array and index-based organization. Chapter 2
uses a fixed array to store nodes, while each node's left and right indices
record a hierarchy. Related nodes need not be adjacent, and array order
does not determine the root.

The separate application lab extends the textbook's child-index model
to multiplication precedence. It uses its own storage, parser state, and
four-function interface:

```c
struct TreeNode {
    char data; /* A stored digit character, '+', or '*'. */
    int left;  /* Child index, or -1 for no child. */
    int right;
};

struct TreeNode nodes[20];
int size = 0;
char eq[20] = "1+2*3";
int pos = 0;

int new_node(char data);
int term(void);
int terms(void);
int eval_tree(int node);
```

All four function bodies are required student implementations. Number
leaves store characters `'0'` through `'9'`; the evaluator converts those
characters into integer results. This chapter uses no dynamic allocation.

The accepted input is a nonempty expression alternating single digits and
`+` or `*`, starting and ending with a digit, with no spaces or parentheses,
and at most 19 characters. Assume every intermediate and final answer
fits in `int`. No malformed-input handling or overflow detection is
required.

## Board Walkthrough

Use `1+2*3` throughout the Stage B reveal:

```text
[1] '+'
|-- left: [0] '1'
`-- right: [3] '*'
    |-- left: [2] '2'
    `-- right: [4] '3'
```

| Index | `data` | `left` | `right` |
|---:|---|---:|---:|
| 0 | `'1'` | -1 | -1 |
| 1 | `'+'` | 0 | 3 |
| 2 | `'2'` | -1 | -1 |
| 3 | `'*'` | 2 | 4 |
| 4 | `'3'` | -1 | -1 |

Explain `nodes[root].right` as selecting the root node and then reading
its right member. Explain `nodes[nodes[root].right].data` as following the
stored index to another node and reading that node's character.

Ask students to predict:

- the root index, root character, and final integer answer separately;
- why child index `0` is valid while `-1` must not be dereferenced;
- the `pos` and root returned by the first `term()` inside `terms()`;
- which complete group supplies the addition's right operand; and
- whether the operator characters change during evaluation.

Stage C transfers the same reasoning to `2*3+4*5`, with root `3` for
`'+'`, multiplication roots `1` and `5`, digit indices `0, 2, 4, 6`, and
answer `26`. Use the module's investigation and answer key for the full
trace.

## From Text to a Tree

`size` counts used nodes and identifies the next available slot.
`new_node` writes a character, initializes both children to `-1`, advances
`size`, and returns the old index. It reserves a node without attaching it.

`pos` identifies the next unread character. `eq[pos]` examines that
character without advancing. `eq[pos++]` uses the old position and then
advances once.

`term()` starts from one digit. Each following `*` becomes a fresh parent:
the old root goes on its left, the next digit goes on its right, and its
index becomes the new root. It leaves `+` or `\0` unread.

`terms()` first calls `term()`, then repeats the corresponding pattern for
`+`. Its right operand comes from another complete `term()` call. Building
multiplication terms before joining them with addition preserves precedence.
Repeated operators at the same level group from left to right because each
new operator adopts the existing subtree on its left.

For the canonical input, the first term returns root `0`, `size == 1`,
and `pos == 1`. The enclosing `terms()` reserves plus index `1` and
calls `term()` again. That call builds `2*3` with root `3`, `size == 5`,
and `pos == 5`. The plus node receives children `0` and `3`, and the
whole-expression root is `1`. It is neither the first nor the last
reserved slot.

Before each independent expression run, set `size = 0`, set `pos = 0`,
and copy a valid bounded string into `eq`. A reset helper is not a fifth
required function. Array slots have program-long storage duration, but
reusing them means old root indices no longer retain the earlier tree.

## Recursion and Returned Values

Record call-entry indices `1, 0, 3, 2, 4` separately from completed-return
indices `0, 2, 4, 3, 1`. Their returned values are `1, 2, 3, 6, 7`.

The base case is a digit leaf: return its character minus `'0'`. C's digit
character codes are consecutive, so the conversion requires no assumed
ASCII code. The base case returns without following its absent children.

An operator evaluates the left child and then the right child in two
separate statements. Each call has its own local results. The plus call
keeps its left value `1` while the multiplication call computes `6`; then
addition returns `7`.

Evaluation does not overwrite `data` with an arithmetic result. The root
still stores `'+'`, its right child still stores `'*'`, and the indices,
`size`, `pos`, and `eq` remain unchanged. A second evaluation gives the
same answer from the same tree. Formal comparisons among traversal orders
and explicit-stack traversal remain later work.

## Core Invariant and Caller Duties

A valid nonempty tree has one root. Every other node appears in exactly
one child position. No child-link route returns to a node already on that
route. A node cannot be shared by two parents or occupy both sides of one
parent. Every present child index refers to an initialized slot below
`size`.

The builder preserves these rules by joining disjoint subtrees under a
fresh parent. An empty child member alone does not establish that an
arbitrary proposed attachment is valid. Discuss sharing and cycles through
paper traces; the four functions are not graph validators.

A general binary-tree node can have zero, one, or two children. A completed
expression for this grammar requires two operands at each operator and
none at each digit. `eval_tree(-1)` and operators with missing children
are outside the evaluator's contract.

## Common First Thoughts

- “Zero means no node.” Index `0` selects the first node; `-1` marks an
  absent child. Character `'0'` is an ordinary operand.
- “The first or last array element must be the root.” Stored links and the
  returned root index determine the hierarchy.
- “A digit character is already its numeric value.” The evaluator subtracts
  `'0'` to convert the stored character.
- “`return size++` returns the next free index.” It returns the old value,
  identifying the node just reserved, while advancing the counter.
- “A completed term is always the whole expression.” A `+` may remain unread
  for the enclosing `terms()` call.
- “The addition's next digit is its entire right operand.” That operand
  can be a whole multiplication term.
- “The right arithmetic answer proves left association.” These operators
  can produce equal answers under different groupings; inspect child links.
- “Every recursive call shares the same answer variables.” Local child
  results belong to each call; parser position is the shared global state.
- “Evaluation stores the answer in the operator node.” It returns the
  answer and preserves the stored characters and links.
- “A valid tree must encode the intended expression.” Structural validity
  does not by itself establish the right precedence.

## Vocabulary Boundaries

**Revisit with support:** C variables, functions, arrays, indices, loops,
conditions, bounds, and invariants from Chapter 1. Previous exposure does
not guarantee that a student can read every symbol; pause at the unfamiliar
line and use the chapter's syntax section or the lab's reading guide.

**Reinforce from the textbook:** hierarchy, binary tree, expression tree, node, root,
parent, child, sibling, ancestor, descendant, leaf, subtree, path, depth,
height, `struct`, member access with `.`, digit-character conversion,
index links and `-1`, left association, recursion, and a base case.

**Add in the application lab:** precedence, parsing, and shared `pos`.

**Deferred:** multi-digit, parenthesized, or unary parsing; other operators;
malformed-input validation; dynamic node allocation; upward-link APIs;
binary-search ordering; balancing; arbitrary-graph validation; and detailed
traversal-order comparisons. The lab does not require a separate parser
wrapper, reset function, or success/status type.

## Operation Summary

| Operation | Main idea | Work |
|---|---|---|
| `new_node` | Initialize the next array slot and return its index | `O(1)` |
| Assign a child link | Write one known integer member | `O(1)` |
| `term` | Build one digit and its multiplication pairs | `O(k)` for a term of `k` characters |
| `terms` | Join complete multiplication terms with addition | `O(n)` for the full expression |
| `eval_tree` | Get both child results, then apply the operator | `O(n)` for the full tree |

The array reserves 20 node slots, of which `n` are used after a fresh
complete parse. A node's representation includes a character, two integers,
and any implementation padding. Parsing uses loops and a constant number
of call levels. Evaluation uses `O(h + 1)` temporary call-stack space,
where `h` counts links on the longest downward route. Repeated operators
can make that tree skewed.

The runnable lecture example is
[expression_tree.c](../module_02_binary_tree/code/lecture/expression_tree.c).
See the module's code README for build commands and separate starter,
reference, and student-authored test workflows.

## Teaching Sequence and Assessment

Use the module's two 90-minute meetings and five release gates:

1. A: initial inquiry before representation, vocabulary, or code.
2. B: representation and vocabulary, then a five-minute Cognitive Pause on
   indices, a term boundary, and evaluation without mutation.
3. C: structural, construction, and evaluation investigation.
4. D: both bilingual textbooks and the shared diagram/text models after
   the Stage C attempt is preserved.
5. E: the four-function lab, tests, rubric, evidence, and autopsy.

Both Stage D textbooks retain **New C Syntax Explained** and **C Code**.
Use the relevant syntax or classroom example for the student's current
difficulty. On the Chapter 2 webpage, **Ask GPT** at the end of a subsection
allows questions about its content and code. The downloaded chapters
remain available for reading without GPT.

Ask students to check any explanation against the code, explain one line,
predict its state change, and then return to the relevant lab checkpoint.
This reading support adds no submission or rubric points. Use the
[lab's file and test guidance](../module_02_binary_tree/student/lab.md) for
the supplied header, shared declarations, and test helpers surrounding the
four functions in this lab package.

Preserve initial attempts and labeled corrections. Hold back solutions,
instructor extension tests, and worked autopsy answers from student
releases. The standalone `faulty_precedence.c` autopsy requires a saved
prediction before execution; it demonstrates a semantic grouping fault
using valid array accesses and a structurally valid tree. The private
answer key supplies its exact output and repair.

The three authored tests cover creation, construction with precedence and
left association, and evaluation with unchanged members/shared state. The
100-point rubric assigns 20 to representation/invariants, 15 to creation,
20 to construction, 20 to evaluation, 10 to efficiency, 10 to tests/tool
evidence, and 5 to autopsy/transfer. Do not add API requirements or a
fourth student-authored test for the autopsy.

## Application-lab final check

> Why is the root of `1+2*3` a plus node at index `1`?

**Minimum answer:** `terms()` reserves the plus after its first digit term,
then builds `2*3` as the complete right term. The plus node joins root
indices `0` and `3` and becomes the whole-expression root.

> What do the first `term()` call and the complete `terms()` call leave unread?

**Minimum answer:** In this input the first term leaves `+` at position `1`.
The complete expression call leaves `\0` at position `5`.

> What changes when `eval_tree(root)` returns `7`?

**Minimum answer:** The caller receives integer `7`. The tree's characters,
child indices, and shared parsing state remain unchanged.

> Why can a valid tree return the wrong result for the intended input?

**Minimum answer:** Its links may represent the wrong operator grouping.
A correct evaluator computes the expression represented by those links.
