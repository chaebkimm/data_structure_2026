# Instructor Answer Key — Module 2

Keep this file instructor-only. Students preserve an initial attempt before
calibration and an autopsy prediction before observation. Both textbooks
teach the same four-function array-index model used throughout this key.

## Macro-question synthesis

The hierarchy records operator grouping. A node stores a character and
left/right child indices; the evaluator obtains each child's value before
applying the operator. Construction consumes multiplication terms before
combining them with addition, so `1+2*3` becomes `1+(2*3)` and returns `7`.
Parent-child relationships follow stored indices, not array adjacency.

## Stage A — Initial inquiry

### A. Reconstruct the hierarchy

```text
             '+'
            /   \
          '1'   '*'
                / \
              '2' '3'
```

The starting item is `'+'`; items with nothing below them are `'1'`, `'2'`,
and `'3'`. The route to `'3'` is `'+' -> '*' -> '3'`. Multiplication lies
below addition because its result is an input to that addition. Accept
side-labeled tables or linear descriptions instead of a drawing.

### B. Preserve the hierarchy

1. Making the existing `'2'` item also appear below `'1'` introduces two
   routes to one object. It is shared rather than an unshared tree node.
2. Linking `'3'` back to `'+'` creates the cycle
   `'+' -> '*' -> '3' -> '+'`; following that route can continue forever.
3. Removing the left branch does not move the right branch. A right-only
   node can belong to a general binary tree, but the remaining `'+'` lacks
   one operand and no longer represents a completed expression.
4. Suitable rules include one root, one incoming link per other node, no
   cycles, and at most one item at each named side.

Do not require representation or technical vocabulary before the reveal.

### C. Calculate from relationships

Multiplication returns `6`; addition then returns `7` and finishes last.
Grouping the same input as `(1+2)*3` instead gives `9`, with `'*'` at the
top and the `'+'` group on its left. The different answer comes from a
different hierarchy. Parentheses in this explanation express grouping;
the program's input grammar does not accept them.

### D. Storage brainstorm

Each object needs its character and a way to identify each child, with a
special indication for an empty position. Related objects need not occupy
neighboring storage. Equal stored characters do not make two objects the
same object. Accept any reasoned initial proposal and preserve unresolved
questions for later comparison.

## Stage B — Representation and Cognitive Pause

### Canonical table

For `1+2*3`, `root == 1`, `size == 5`, and `pos == 5`:

| Index | `data` | `left` | `right` |
|---:|---|---:|---:|
| 0 | `'1'` | -1 | -1 |
| 1 | `'+'` | 0 | 3 |
| 2 | `'2'` | -1 | -1 |
| 3 | `'*'` | 2 | 4 |
| 4 | `'3'` | -1 | -1 |

### Target 1 — Indices and characters

`root` is index `1`. `nodes[root].left` is index `0`.
`nodes[nodes[root].left].data` is character `'1'`. Zero selects the first
array slot. The link value `-1` means no child and must not be dereferenced.
The integer index, the character, and an evaluated number are distinct
kinds of information even when their printed forms look similar.

### Target 2 — A term boundary

Starting fresh, the first `term()` inside `terms()` reserves only `'1'` at index `0`. It
returns `0` with `size == 1`, `pos == 1`, and `eq[pos] == '+'`. The test
for `*` examines the next character without consuming it.

When this call is the first step inside `terms()`, its caller keeps root
`0`, consumes `+`, and requests a complete next term. That next `term()`
call builds `2*3`. The caller finally puts both terms below the plus node.
Do not suggest calling `terms()` separately at the `+` after a standalone
`term()` call; `terms()` begins by expecting a digit at the start of a term.

### Target 3 — Returned results and unchanged data

Call-entry indices are `1, 0, 3, 2, 4`. Completed calls return:

| Index | Stored character | Returned value |
|---:|---|---:|
| 0 | `'1'` | 1 |
| 2 | `'2'` | 2 |
| 4 | `'3'` | 3 |
| 3 | `'*'` | 6 |
| 1 | `'+'` | 7 |

A digit is the base case and returns its character minus `'0'`. Each
operator needs both returned operand values before combining them.
Indices `1` and `3` retain `'+'` and `'*'`; all child links and shared
parser state also remain unchanged. Arithmetic answers live in call-local
values and return values, not in overwritten operator fields.

## Stage C — Investigation

Use a fresh starting state for every independent operation.

### D. Translate among representations

```text
[3] '+'
|-- left: [1] '*'
|   |-- left: [0] '2'
|   `-- right: [2] '3'
`-- right: [5] '*'
    |-- left: [4] '4'
    `-- right: [6] '5'
```

| Index | `data` | `left` | `right` |
|---:|---|---:|---:|
| 0 | `'2'` | -1 | -1 |
| 1 | `'*'` | 0 | 2 |
| 2 | `'3'` | -1 | -1 |
| 3 | `'+'` | 1 | 5 |
| 4 | `'4'` | -1 | -1 |
| 5 | `'*'` | 4 | 6 |
| 6 | `'5'` | -1 | -1 |

The four assignments are `nodes[3].left = 1`, `nodes[3].right = 5`,
`nodes[1].right = 2`, and `nodes[5].left = 4`.

| Expression | Meaning and value |
|---|---|
| `root` | index `3`, selecting the whole-expression root |
| `nodes[root].data` | character `'+'` |
| `nodes[root].left` | index `1`, selecting its left subtree |
| `nodes[nodes[root].left].data` | character `'*'` at index `1` |
| `-1` in a child field | no child in that position |

### E. Positions

The data path to index `4` is `'+' -> '*' -> '4'`, using indices `3, 5, 4`.
Its depth is `2`. Leaf indices are `0, 2, 4, 6`. The height of index `1`
is `1`; the root's height is `2`. The subtree at index `1` contains
indices `1, 0, 2`. Count links rather than nodes; a leaf has height zero.
A parent or ancestor remains a relationship without being a stored field.

### F. Invariants

The root has zero incoming child links. Every other tree node has exactly
one. Each present child index is in `[0, size)`, and absence is `-1`.

- `nodes[0].left = 3` creates the route `3 -> 1 -> 0 -> 3`, a cycle.
- `nodes[5].left = 2` makes index `2` a child of both indices `1` and `5`
  while removing the only route to index `4` from the root.
- Joining disjoint subtrees under a fresh parent adds one incoming link to
  each subtree root. No existing descendant can already reach the fresh
  parent, so no cycle is introduced.
- An empty field establishes only that the selected side is unused. It
  cannot prove that a candidate child is unshared or cannot reach a parent.
- A right-only general binary-tree node is possible. A completed `'+'` or
  `'*'` expression needs both operands and therefore both child links.

The proposed defects stay on paper. The required functions assume valid
input and completed trees rather than detecting arbitrary malformed links.

### G. Node reservation and shared state

After `int a = new_node('0');`, `a == 0`, `size == 1`, and the new fields
are character `'0'`, left `-1`, right `-1`. Character `'0'` is data; integer
`0` is its evaluated value; index `0` is its storage position.

After `int b = new_node('7');`, `b == 1` and `size == 2`. Both new child
fields are `-1`; neither node is attached to the other. Each reservation
initializes both fields because unused or previously reused storage does
not establish the required no-child marker.

A fresh build resets `size` to reserve from the beginning and `pos` to
read from the beginning of its new valid `eq`. Reusing array slots changes
which logical tree they describe, so saved old root indices cannot retain
the earlier tree. The global storage itself remains alive.

A 19-character input plus its `\0` occupies all 20 character slots. One
node per input character needs at most 19 of the 20 node slots. Capacity
suffices under the fresh-state and valid-input assumptions.

### H. Two parsing levels

For `2*3+4*5`, a standalone first `term()` returns root `1`, `size == 3`,
`pos == 3`, and unread `+`. Node `1` links left to `0` and right to `2`.

Starting fresh again, the complete `terms()` trace is:

| Checkpoint | Root information | `size` | `pos` | Next unread |
|---|---|---:|---:|---|
| after first `term()` | current root `1` | 3 | 3 | `+` |
| after reserving `+` | current root `1`; new operator `3` | 4 | 4 | `4` |
| after next `term()` | current root `1`; next-term root `5` | 7 | 7 | `\0` |
| after linking and return | whole root `3`, children `1` and `5` | 7 | 7 | `\0` |

The right operand of addition must be a complete term to include `4*5`.
Reading only `'4'` would leave the multiplication outside that operand.
`eq[pos]` peeks without advancing; `eq[pos++]` consumes at the old position
and advances once. `term()` leaves `+` for the caller's addition loop.
A successful complete `terms()` call leaves `\0` unread.

### I. Recursive evaluation

Call-entry indices: `3, 1, 0, 2, 5, 4, 6`.

| Return order | Index | Returned value |
|---:|---:|---:|
| 1 | 0 | 2 |
| 2 | 2 | 3 |
| 3 | 1 | 6 |
| 4 | 4 | 4 |
| 5 | 6 | 5 |
| 6 | 5 | 20 |
| 7 | 3 | 26 |

Digits return `data - '0'`; C guarantees consecutive digit character
codes. Each operator combines the numeric results of both child calls.
The final answer is `26`. Operator indices `1`, `3`, and `5` still contain
`'*'`, `'+'`, and `'*'`.

Snapshot the used nodes' data and both child fields, `size`, `pos`, and
`eq`; evaluate twice; assert both answers and compare the snapshots.
Compare struct fields explicitly rather than depending on padding bytes.
Nonmutation means the second evaluation can reuse the completed tree.

### J. Association and cost

For `2*3*4`, final root `3` stores the second `*`, with left index `1`
(the first `*`) and right index `4` (digit `'4'`). Node `1` has children
`0` and `2`. This shape expresses `(2*3)*4`.

For `1+2+3`, root `3` stores the second `+`, with left `1` and right `4`.
Node `1` has children `0` and `2`. The same old-root/new-parent pattern
expresses `(1+2)+3`. These examples return the same values under the other
association; inspect child indices to establish construction order.

| Operation | Time | Reason |
|---|---:|---|
| reserve and initialize one node | `O(1)` | three field writes and one counter update |
| assign one child link | `O(1)` | one known field write |
| construct the whole expression | `O(n)` | consume each character and reserve each node once |
| evaluate the whole tree | `O(n)` | compute each node's result once |

The fixed array reserves `20 * sizeof(struct TreeNode)` bytes; its `n`
used nodes represent the expression. Exact struct size may include padding.
The two parser levels use constant additional call space. Evaluation uses
`O(h + 1)` call-stack space, including the root frame. A long operator
chain can form a skewed tree; balanced height is not guaranteed.

### K. Transfer

`8+2*0` returns `8`, and the zero digit still has a real node index.
Character `'0'` is an ordinary operand, index `0` is a valid slot, and
only the link value `-1` denotes absence.

A reusable subexpression referenced by two operations is an example of a
shared relationship that may need a directed acyclic graph. It relaxes the
tree's single-parent rule. A model that also allows returning routes needs
cycle-aware processing. Students explain the distinction without
implementing a graph validator or a new API.

### L. Exit anchors

A child link is an integer index; `-1` means absent. `size` counts used
nodes and identifies the next available slot. `pos` identifies the next
unread character. `term()` stops before `+` or `\0`; `terms()` combines
complete terms with addition. The digit base case converts and returns a
number, and evaluation preserves node data. Students implement
`new_node`, `term`, `terms`, and `eval_tree`.

## Exact implementation boundary

```c
struct TreeNode {
    char data;
    int left;
    int right;
};

int new_node(char data);
int term(void);
int terms(void);
int eval_tree(int node);
```

The shared definitions are `nodes[20]`, `size = 0`,
`eq[20] = "1+2*3"`, and `pos = 0`. All four function bodies are core
student work. Independent fixtures reset both counters and copy a valid
bounded string. No extra initialization API, malformed-input handling,
overflow check, or arbitrary-tree validation is required.

Valid input alternates single digits and `+` or `*`, starts and ends with
a digit, uses no spaces or parentheses, has at most 19 characters, and
keeps every intermediate and final answer in `int` range. Empty input and
`eval_tree(-1)` are outside the contract.

## Tree Structure Autopsy — worked instructor answers

### Starting defect and prediction

The standalone `code/autopsy/faulty_precedence.c` treats every next
operator as a parent of the expression already built and the next digit.
For `1+2*3`, this produces `(1+2)*3`:

| Index | `data` | Faulty `left` | Faulty `right` |
|---:|---|---:|---:|
| 0 | `'1'` | -1 | -1 |
| 1 | `'+'` | 0 | 2 |
| 2 | `'2'` | -1 | -1 |
| 3 | `'*'` | 1 | 4 |
| 4 | `'3'` | -1 | -1 |

The faulty root is `3`. Its plus child returns `3`, and its digit child
returns `3`, so multiplication returns `9`. All five slots are initialized;
each non-root has one incoming link, there is no cycle, and every operator
has two children. The expression's precedence is wrong even though the
tree invariants hold.

The reference grouping has root `1`, whose children are `0` and `3`;
node `3` has children `2` and `4`. It returns `7`. Node character order
is the same in both arrays; the links determine the grouping.

The fixture's expected output is:

```text
faulty:  1+2*3 = 9 (root '*')
correct: 1+2*3 = 7 (root '+')
Precedence fault demonstrated.
```

### Repair and regression evidence

The defect is in construction, not evaluation. Reserving a `+` node and
consuming just its next digit fails to build a complete multiplication
term. Use `term()` to group every multiplication sequence, then have
`terms()` attach complete terms under plus nodes. The standalone autopsy
uses a directly initialized correct tree for comparison; it does not need
to ship the reference parser implementation.

A regression test can build `1+2*3` from fresh state and assert root `1`,
root character `'+'`, children `0` and `3`, multiplication children `2`
and `4`, `size == 5`, `pos == 5`, and result `7`. A repeated-operator
case should inspect links as well as the answer to establish left
association. The proposal may support the construction slot among the
three authored tests; a fourth coded test is not required.

Compiler warnings and sanitizers need not report this failure because all
accesses and arithmetic are valid. They supplement expected-value and
structural assertions; their silence cannot establish semantic correctness.

## Assessment alignment

| Criterion | Points |
|---|---:|
| Representation and invariants | 20 |
| Node creation | 15 |
| Expression construction | 20 |
| Recursive evaluation | 20 |
| Operation efficiency | 10 |
| Tests and tool evidence | 10 |
| Autopsy and forward transfer | 5 |
| Total | 100 |

The three authored-test slots cover creation, construction with precedence
and association, and evaluation with nonmutation, in that order. Require
distinct claims and rationales. Accept equivalent linear descriptions,
verbal explanations, and approved tool evidence. Do not penalize an initial
misconception that is preserved and meaningfully corrected.
