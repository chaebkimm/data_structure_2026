# Module 2 Expression-Tree Models — Stage D

Read after the Stage C investigation and exit ticket. These models accompany
both Chapter 2 textbooks. Every diagram includes a text equivalent.

## 1. Characters and indices

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
indices. All nodes live in `nodes[20]`; no parent field is stored. `size`
counts occupied slots. Index 0 is valid, and -1 means an absent child.

## 2. The canonical expression: 1+2*3

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

## 3. Read nested field expressions

| Expression | Meaning and canonical value |
|---|---|
| `root` | Root index, 1 |
| `nodes[root]` | The node stored at index 1 |
| `nodes[root].data` | Its character, `'+'` |
| `nodes[root].left` | Left child index, 0 |
| `nodes[nodes[root].right].data` | Right child's character, `'*'` |
| `nodes[0].left` | -1, meaning the digit has no left child |

Text equivalent: brackets select an array element and dots select fields.
Follow a child link by using its nonnegative index to select another node.
Never use the absence marker -1 as an array index.

## 4. Build a term, then a sum

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

## 5. Equal operators associate left to right

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

## 6. Evaluate children before their operator

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
1, 2, 3, 6, 7. Each call keeps its own local results. Every node field and
shared variable remains unchanged; the root still stores `'+'`.

## 7. General trees and completed expressions

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

## 8. Stage C transfer model: 2*3+4*5

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

## 9. Shared storage across independent builds

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

## 10. Count the work and storage

Let `n` be the number of expression characters/nodes and `h` the longest
root-to-leaf path measured in links.

| Operation | Time | Extra call storage |
|---|---:|---:|
| Reserve and initialize one node | `O(1)` | `O(1)` |
| Assign one child link | `O(1)` | `O(1)` |
| Build a whole expression | `O(n)` | `O(1)` |
| Evaluate a whole expression | `O(n)` | `O(h + 1)` |

Text equivalent: creation and linking touch fixed numbers of fields.
Parsing consumes every character once and uses loops plus two parser levels.
Evaluation visits each node once, and its longest active call chain follows
the tree's depth. The literal array always reserves 20 nodes; `n` slots are
occupied. If capacity scales with input length, stored nodes require `O(n)`
space. These costs describe the algorithm even though this exercise bounds
input to 19 characters and assumes all results fit in `int`.
