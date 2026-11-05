# Module 2 Tree Models — Stage D

Read after the Stage C investigation and exit ticket. The first models
follow both current Chapter 2 textbooks and the classroom `student/lab.c`.
The final section retains the separate precedence application-lab models.
Every diagram includes a text equivalent.

## How do child indices record a hierarchy?

A node stores data and links to its children. In one tree, the root has
no parent and every other node has one. Following parents from any node
leads to that root; the relationships form one connected hierarchy.

The classroom representation is:

```c
struct TreeNode {
    char data;
    int left;
    int right;
};
struct TreeNode nodes[10];
int capacity = 10;
int nodes_size = 0;
```

Text equivalent: ten array slots are reserved. Each node stores a
character and at most two child indices, named left and right. A child
index of -1 means no child; index 0 names a real array element. No parent
member is stored. Changing links or the root index does not move nodes.

## Which initialized letters belong to the alphabet tree?

`alphabet_init` writes A through J and sets every link to -1.
`tree_connect` then creates these relationships:

```text
                 [5] F
                 /   \
             [0] A   [6] G
             /   \
         [1] B   [2] C
         /   \
     [3] D   [4] E

Unconnected initialized entries: [7] H, [8] I, [9] J
```

Text equivalent: F is the root at index 5. Its children are A and G.
A's children are B and C. B's children are D and E. The other connected
nodes are leaves. H, I, and J remain outside this tree.

| Index | `data` | `left` | `right` |
|---:|---|---:|---:|
| 0 | `'A'` | 1 | 2 |
| 1 | `'B'` | 3 | 4 |
| 2 | `'C'` | -1 | -1 |
| 3 | `'D'` | -1 | -1 |
| 4 | `'E'` | -1 | -1 |
| 5 | `'F'` | 0 | 6 |
| 6 | `'G'` | -1 | -1 |
| 7 | `'H'` | -1 | -1 |
| 8 | `'I'` | -1 | -1 |
| 9 | `'J'` | -1 | -1 |

The returned root is 5 and `nodes_size` is 10. Starting at F reaches
seven nodes. `tree_recursion` calls left, then right, then reads the current
character. The read order is `D E B C A G F`. A call with index -1 stops
at the range guard. Reading `data_read` does not print a character.

## How does an operand become a subtree?

A binary operator combines two operands. Each operand may be a digit or
another expression. Represent the operator as the parent and the operands
as its left and right children. Digits have no children.

Prepare five nodes for `1+2+3`, with all links initially -1. The first
digit is root 0. Connect the first plus to digits 1 and 2, then make that
whole expression the left operand of the second plus:

```text
                  [3] '+' (second)
                  /     \
        [1] '+' (first) [4] '3'
            /     \
        [0] '1' [2] '2'
```

Text equivalent: the second plus, index 3, is the root. Its left child
is the first plus, index 1, and its right child is digit 3 at index 4.
The first plus has digit 1 at index 0 and digit 2 at index 2 as children.
The links represent `(1+2)+3`.

| Construction step | `i` after increments | `op` | `num` | Current root |
|---|---:|---:|---:|---:|
| `int root = i++;` | 1 | — | — | 0 |
| First loop iteration | 3 | 1 | 2 | 1 |
| Second loop iteration | 5 | 3 | 4 | 3 |

The old root becomes the new operator's left child; the next digit becomes
its right child. Update root after those links. At every step, the current
root accesses everything connected so far. Construction records grouping;
it does not calculate the answer.

| Index | `data` | `left` | `right` |
|---:|---|---:|---:|
| 0 | `'1'` | -1 | -1 |
| 1 | `'+'` | 0 | 2 |
| 2 | `'2'` | -1 | -1 |
| 3 | `'+'` | 1 | 4 |
| 4 | `'3'` | -1 | -1 |

`nodes_size` is now 5. The same ten-slot array has been reused; old alphabet
roots no longer describe the earlier tree. `eq_plus_init` resets the five
active nodes before `eq_plus_connect` links them.

## How do child answers return to the waiting operator?

Evaluate only the completed addition tree with its returned root:

```text
eval(3): second '+' waits for two results
  eval(1): first '+' waits for two results
    eval(0): '1' returns 1
    eval(2): '2' returns 2
  first '+' returns 3
  eval(4): '3' returns 3
second '+' returns 6
```

Text equivalent: the digit cases subtract `'0'` and return immediately.
The first plus returns 3 to the waiting root call. The root receives its
right value 3 and returns 6. Each call has separate local state; the node
characters and links remain unchanged. `eval` assumes a valid addition
tree and has no check for an invalid index or another operator.

## How much work and call storage are needed?

The alphabet path F–A–B–D has three links, so its height is 3. Four node
calls can be active along it. The reader can add one brief stopping call
for D's absent child. Count reserved node storage separately from calls.

| Action | Work | Extra call storage |
|---|---:|---:|
| Initialize one node or assign one child link | `O(1)` | `O(1)` |
| Initialize or connect `n` nodes | `O(n)` | `O(1)` |
| Read or evaluate `r` reachable nodes in a valid tree | `O(r)` | `O(h + 1)` |

Text equivalent: ten slots remain reserved even when only five are in use.
Traversal visits nodes reached from the root, not every initialized slot.
A single-root tree has height 0 and still needs a root call. Cycles and
shared children violate the tree rules; range checks do not detect them.

## Application-lab models: adding multiplication precedence

The remaining models describe the existing staged lab, which extends the
textbook with `+`/`*` precedence. It uses `nodes[20]`, `size`, shared `pos`,
and `new_node`, `term`, `terms`, and `eval_tree`. Those names and capacities
belong to a separate program from the classroom examples above.

### 1. Characters and indices

```c
struct TreeNode {
    char data; /* A digit or operator character. */
    int left;  /* Child index or -1. */
    int right; /* Child index or -1. */
};
```

```text
nodes[index]
+-------------------------+
| data: digit, '+', or '*' |
| left: child index or -1  |
| right: child index or -1 |
+-------------------------+
```

Text equivalent: one node stores a character and two independent child
indices. All nodes live in `nodes[20]`; no parent member is stored. `size`
counts occupied slots. Index 0 is valid, and -1 means an absent child.

### 2. The application-lab expression: 1+2*3

```text
                 [1] '+'
                 /     \
             left       right
              /           \
          [0] '1'        [3] '*'
                         /     \
                     [2] '2' [4] '3'
```

Text equivalent: the root is index 1, whose character is `'+'`. It has left
child 0 and right child 3. The multiplication at 3 has left child 2 and right
child 4. Indices 0, 2, and 4 are digit leaves. Multiplication occurs below
addition, so it produces a value before the addition combines its operands.

| Index | `data` | `left` | `right` |
|---|---|---:|---:|
| 0 | `'1'` | -1 | -1 |
| 1 | `'+'` | 0 | 3 |
| 2 | `'2'` | -1 | -1 |
| 3 | `'*'` | 2 | 4 |
| 4 | `'3'` | -1 | -1 |

`root == 1`, `size == 5`, and `pos == 5`. Array order follows character
consumption; child links supply the hierarchy. A root need not be the first
or last array position.

### 3. Read nested member expressions

| Expression | Meaning and canonical value |
|---|---|
| `root` | Root index, 1 |
| `nodes[root]` | The node stored at index 1 |
| `nodes[root].data` | Its character, `'+'` |
| `nodes[root].left` | Left child index, 0 |
| `nodes[nodes[root].right].data` | Right child's character, `'*'` |
| `nodes[0].left` | -1, meaning the digit has no left child |

Text equivalent: brackets select an array element and dots select members.
Follow a child link by using its nonnegative index to select another node.
Never use the absence marker -1 as an array index.

### 4. Build a term, then a sum

```text
input: 1 + 2 * 3 \0
index: 0 1 2 3 4  5

first term: return root 0; size 1; pos 1 (next '+')
reserve '+': index 1; size 2; pos 2
next term: create 2, '*', 3 at indices 2, 3, 4
           return root 3; size 5; pos 5 (next '\0')
join sum: nodes[1].left = 0; nodes[1].right = 3
return whole root 1
```

Text equivalent: `term()` consumes a digit and all following multiplication
pairs. `terms()` consumes each addition and asks `term()` for a complete
operand. Both functions share `pos`, so multiplication stays inside the
addition's right subtree. Checking a next character does not consume it.

### 5. Equal operators associate left to right

For `2*3*4`:

```text
                [3] '*'
                /     \
           [1] '*'   [4] '4'
           /     \
       [0] '2' [2] '3'
```

Text equivalent: the second multiplication, at index 3, becomes the root.
Its left child is the previous multiplication at index 1, and its right
child is the new digit at index 4. The links encode `(2*3)*4`. Parentheses
explain grouping and are not input to this parser. Repeated additions use
the same root-update pattern.

### 6. Evaluate children before their operator

For `1+2*3`:

```text
eval_tree(1): '+' waits for two results
  eval_tree(0): '1' returns 1
  eval_tree(3): '*' waits for two results
    eval_tree(2): '2' returns 2
    eval_tree(4): '3' returns 3
  multiplication returns 6
addition returns 7
```

Text equivalent: calls enter indices 1, 0, 3, 2, 4. Calls complete with values
1, 2, 3, 6, 7. Each call keeps its own local results. Every node member and
shared variable remains unchanged; the root still stores `'+'`.

### 7. General trees and completed expressions

```text
leaf             left-only          right-only
  A                  A                  A
 / \                / \                / \
-1 -1              B  -1             -1   B
```

Text equivalent: all three shapes can be valid general binary trees. In this
module's completed expressions, digits are leaves and operators have both
children. A missing left child never causes a right child to change sides.
Fresh parent nodes connect disjoint subtrees, preserving one incoming link
per non-root node and preventing cycles.

### 8. Stage C transfer model: 2*3+4*5

```text
                   [3] '+'
                   /     \
              [1] '*'   [5] '*'
              /   \       /   \
          [0] '2' [2] '3' [4] '4' [6] '5'
```

Text equivalent: root 3 has children 1 and 5. Multiplication node 1 has
children 0 and 2. Multiplication node 5 has children 4 and 6. The four digits
are leaves. The left term returns 6, the right term returns 20, and the whole
expression returns 26.

The root's depth is 0 and height is 2. Both multiplication nodes have depth
1 and height 1. All leaves have depth 2 and height 0. Parent and ancestor
relationships can be read from root-to-node paths without storing upward
links.

### 9. Shared storage across independent builds

```text
reset size and pos to 0
copy a valid expression into eq
build with terms; save its returned root
evaluate this tree

next independent build reuses the same array slots
```

Text equivalent: the global array exists for the whole program. Resetting
its used-count and the input position begins a new logical tree. Reused
slots can change what an old index denotes, so use the root of the current
build. Creation initializes both children even in reused slots.

### 10. Count the work and storage

Let `n` be the number of expression characters/nodes and `h` the longest
root-to-leaf path measured in links.

| Operation | Time | Extra call storage |
|---|---:|---:|
| Reserve and initialize one node | `O(1)` | `O(1)` |
| Assign one child link | `O(1)` | `O(1)` |
| Build a whole expression | `O(n)` | `O(1)` |
| Evaluate a whole expression | `O(n)` | `O(h + 1)` |

Text equivalent: creation and linking touch fixed numbers of members.
Parsing consumes every character once and uses loops plus two parser levels.
Evaluation visits each node once, and its longest active call chain follows
the tree's depth. The literal array always reserves 20 nodes; `n` slots are
occupied. If capacity scales with input length, stored nodes require `O(n)`
space. These costs describe the algorithm even though this exercise bounds
input to 19 characters and assumes all results fit in `int`.
