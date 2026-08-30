# Stage B — How the Binary Tree Is Stored

Open this file only when the instructor releases the representation.

A representation is a chosen way to store information. The hierarchy needs
separate items and a way to reach the item at each side.

## 1. Name the stored pieces

A node is one object in the tree. A C `struct` groups named fields in one
object. Each node stores its data and two child addresses:

```c
struct TreeNode {
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
};
```

An address identifies a memory location. A pointer stores an address.
The `*` in each child-field declaration says that the field is a pointer.
`NULL` means that no node is linked at that position.

A general binary tree has distinct left and right positions. It may use
neither, either one, or both. The completed expression tree used here adds a
meaning rule: an operator uses both positions for its operands, while a number
uses neither. The generic node representation and functions do not enforce
that expression rule. A node has no field pointing upward to its parent. A
parent is still the node directly above a child in the hierarchy.

Label the fields:

- `data`: _________________________________________________________
- `left`: _________________________________________________________
- `right`: ________________________________________________________

## 2. Initialize local variables, then connect their addresses

Create a node as a regular local variable. Set its data and both links before
the program follows any link.

```c
struct TreeNode root;
root.data = '*';
root.left = NULL;
root.right = NULL;

struct TreeNode plus;
plus.data = '+';
plus.left = NULL;
plus.right = NULL;

if (root.left == NULL) {
    root.left = &plus;
}
```

The dot in `root.left` selects a field of a node variable. `&plus` is the
address of `plus`; assigning it creates a link, not a copy of the whole node.
The check avoids replacing an existing left link.

The field has type `int`. Character constants such as `'*'` and `'+'` have
integer type in C, so use the character literals instead of assuming numeric
character codes.

When `root.left` is not `NULL`, `root.left->data` reads the linked node's
data. The arrow `->` selects a field through a pointer.

## 3. Read the complete example

All five variables below are initialized and remain alive in the same block.
Together they represent `(3 + 5) * 2`.

| Local variable | Data | Left address | Right address |
|---|---:|---|---|
| `root` | `'*'` | `&plus` | `&two` |
| `plus` | `'+'` | `&three` | `&five` |
| `three` | `3` | `NULL` | `NULL` |
| `five` | `5` | `NULL` | `NULL` |
| `two` | `2` | `NULL` | `NULL` |

The root is the starting node chosen by the caller. A leaf has no children:
both of its links are `NULL`. The nodes need not be next to one another in
memory.

The left and right links preserve operand positions. They are not a sorting
rule. A search checks the current node, then its left subtree, then its right
subtree: `'*'`, `'+'`, `3`, `5`, `2` for this tree. A subtree contains one
node and all nodes below it. Recursion means that the search function calls
itself on a child subtree.

## 4. Keep positions distinct

A node with `left == NULL` and a nonnull right link is valid in the general
binary-tree representation. It would not be a completed binary operator in
this expression model. Removing the left child does not move the right child.
The sides describe relationships, not a packed sequence of occupied
positions.

How does this differ from shifting items after deletion in Module 1?

____________________________________________________________________

## 5. Separate local checks from caller responsibilities

An invariant is a rule every valid state follows. In a nonempty tree:

1. Every node is reachable from one chosen root.
2. Each non-root node has exactly one incoming child link. The same node
   cannot occupy both sides of one parent or be shared by two parents.
3. No downward route returns to an earlier node. Such a return is a cycle.
4. Each child address names an initialized object that is still alive.

A precondition is a condition the caller must ensure before an operation.
Checking that one side is empty does not prove the whole structure is a
valid tree. The caller attaches a fresh, unlinked node or a disjoint valid
subtree. The search and clearing functions do not detect arbitrary sharing
or cycles.

## 6. Distinguish clearing from ending a lifetime

A local node's lifetime lasts until the block that declared it finishes.
Keeping its address elsewhere does not extend that lifetime. Do not follow
a link after the linked object has stopped existing.

Clearing a subtree resets each node's data to zero and both links to
`NULL`. It does not end the lifetime of those node variables. Zero remains
an ordinary data value.

A node has no upward field, so clearing it cannot remove an outside parent's
link. To remove a child branch, clear the selected subtree and set that
parent's selected link to `NULL`. Leave the other side unchanged.

## 7. Prepare for the Cognitive Pause

Check that you can read the table and distinguish a node variable from its
address. Do not solve the pause targets until the instructor releases them.

One representation question:

____________________________________________________________________
