# Chapter 2. Organizing Data in a Hierarchy

## Thinking Logically

### What does hierarchical data look like?

Think about a mathematical expression like `(3 + 5) * 2`. You don't just read it in a single straight line from left to right; you calculate the `(3 + 5)` group first, and then multiply that result by `2`. The `*` operation relies on the result of the `+` operation below it. This data branches out into levels of priority, forming a structure much like a family tree, called an expression tree.

### What should each item remember?

Each item (we call it a node) needs to store its own actual data (such as a math operator or a number) and the exact locations of the items sitting directly beneath it. To keep things simple, each node only looks downward at its own pieces; it has no idea what larger equation is sitting above it.

### Simple example

A general binary-tree node has two specific child positions, left and right.
It may use neither position, either one, or both. The completed binary
expression tree in this chapter follows an additional expression rule: an
operator such as `+` or `*` uses both positions for its two operands, while a
number uses neither. The tree functions remain general binary-tree functions;
they do not enforce this expression-specific rule or calculate the result.

### How do we add a new item?

For a binary operator, attach each number or sub-expression to its
corresponding operand position. Left and right must stay distinct because
operand order matters for operators such as subtraction and division.

### How do we describe an item's position?

You trace the path from the final, outermost operation at the very top down to the specific item. Counting the steps on that downward route tells you exactly how deeply buried that part of the expression is.

### How do we find a specific piece of data?

You start at the very top. If it isn't what you are looking for, you search the entire left side of the equation. If you still don't find it, you search the entire right side. You keep repeating this left-then-right checking process until you find a match.

### What happens when we throw away a branch?

Because a node only looks down, it cannot unhook itself from the operation above it. You must ask the parent to clear the selected child's sub-expression, then set that left or right link to `NULL`. Clearing resets the nodes' data and links. It does not release their storage or end their lifetimes.

## Calculating Efficiency

### How much memory does one item use?

Every item takes up a fixed, predictable amount of room: space for its data (a number or symbol), plus space for a left and right pointer. Even a plain number at the bottom reserves the space for those two pointers. Also, when searching or calculating deeply through the expression, the computer uses a little bit of temporary memory to keep track of its place. This temporary memory grows based on how deep the branches go.

### How fast is creating or adding one item?

Setting up a new empty item is instantly fast. Hooking it up to an empty left or right spot is also instantly fast because you are just updating one single location, regardless of how massive the entire equation is.

### How fast is finding a value?

Because the data isn't sorted in a clever sequence, the computer might have to open every single node in the worst-case scenario. The time it takes grows steadily in proportion to the total number of items you have stored in the tree.

### How fast is throwing away a whole branch?

Unhooking a single sub-expression from its parent is instantly fast. However, going through and wiping out all the nodes sitting below it takes time. The amount of work grows in proportion to how many items are being thrown away.

## Glossary

### Node

One object that stores data and links to related nodes.

### Tree

A hierarchy in which a node may have children.

### Binary Tree

A hierarchy in which every node has at most two children, specifically distinguished as left and right.

### Expression Tree

A tree that represents an expression. In this chapter's completed examples,
an operator node has two operand children and a number node is a leaf.

### Root

The top node (usually the final operation to be evaluated in an expression).

### Parent

A parent is directly above another node.

### Child

The node directly below it is its child.

### Sibling

A different node with the same parent.

### Ancestor

An ancestor is a node earlier on the path from the root to another node. Ancestors still exist even though our nodes do not store upward links.

### Descendant

A descendant is found below a node by following one or more child links.

### Leaf

A node with no children. Both its `left` and `right` links are `NULL`.

### Subtree

One node together with all of its descendants (a standalone sub-expression).

### Path

A sequence of nodes connected by child links.

### Depth

The number of child links on the path from the root to a node. The root has depth zero.

### Height

The greatest number of child links on a downward path from a node to a leaf. A leaf has height zero.

### Cycle

A path of links that returns to a node already on that path. A valid tree has no cycles.

### Recursion

A technique in which a function calls itself on a smaller part of the same problem. A tree function can process one node and then call itself on each child subtree.

### Cascading Clearance

Recursively resetting every node's data and child links in a subtree. Detachment from its outside parent is a separate caller step.

## Invariant

### What is the invariant (the golden rule) in this data structure?

- The Root Rule: A nonempty tree has exactly one root at the very top.

- The Single-Parent Rule: Every node below the root appears in exactly one child position. Two parent nodes cannot share the exact same child node, and one parent cannot use the exact same node as both its left and right child.

- The Acyclicity Rule (No Loops): A node cannot be placed inside itself, and you can never create an endless loop where following child links downward leads you back to where you started.

### What happens if an invariant is broken?

- If the Root Rule breaks: Two disconnected starting nodes describe two
  separate trees, not one tree. A search or clearance that starts at one root
  cannot reach the nodes below the other root.

- If the Acyclicity Rule breaks: Imagine Node A links to Node B, and Node B links back to Node A. A search that keeps following those links, or a recursive clearance, can revisit the same nodes without finishing and exhaust call-stack space.

- If the Single-Parent Rule breaks: Even without a loop, if Node A and Node B both contain Node C, the structure is not a tree. A search may visit Node C twice. Clearing Node A also clears Node C, so Node B unexpectedly sees changed data and links. Node C still exists; its storage has not been released.

### How do we keep the invariant intact?

The examples check whether the chosen child position is empty. The programmer must also use initialized nodes, avoid cycles and shared children, and keep every linked node variable alive while its address is used. These small examples do not automatically validate the whole tree.

## Coding Plan

### Designing a node

- Store one integer named `data`.
- Store two pointers: one for the `left` child, one for the `right` child.

### Initializing a node

- Take an existing node variable.
- Save the data and set both the left and right links to `NULL`.

### Adding a child

- Check if the desired side (left or right) is currently empty.
- Put the child's address in that specific link.

### Finding a value

- Return `NULL` when the current link is empty.
- Return the current node when its data matches.
- Recursively search the left child.
- If not found there, recursively search the right child.

### Clearing a subtree

- Recursively clear the left child.
- Recursively clear the right child.
- Reset the node's data and empty its links.

The cleared node remains a live object. A data value of `0` does not mean that a node is absent; only a `NULL` link means no child.

### Removing a child

- Fully clear the selected child's subtree.
- Set the parent's link (left or right) to NULL.

## New C Syntax Explained

### A Pointer to the Same Structure Type

Inside `struct TreeNode`, the left and right pointers store the addresses of other nodes of the exact same type.

### `&` (The Address-Of Operator)

Since we are not dynamically requesting memory, we create nodes as regular variables (e.g., `struct TreeNode root;`). To link these variables together, we need to find exactly where they live in memory. Putting an `&` in front of a variable (like `&root`) gives you its memory address. The address may be used only while that local object remains alive.

### `NULL`

`NULL` means that a pointer does not currently identify an object. An unused child link contains `NULL`.

### Explicit `struct` Tags

By choosing not to use `typedef`, you must explicitly tell the compiler what kind of custom data type you are referencing. Every time you declare a node variable or pointer, you must write `struct TreeNode`.

### `.` and `->` (Accessing Fields)

`root.data` accesses a field in the node variable `root`. `node->data` accesses the same kind of field through the address stored in the pointer `node`.

### Recursive Functions

A recursive function needs a stopping case. The search and clearing functions stop when their current node pointer is `NULL`. Without a stopping case, calls could continue until the program runs out of call-stack space.

## C Code

### Designing the node

```c
#include <stddef.h>

struct TreeNode {
        int data;
        struct TreeNode *left;
        struct TreeNode *right;
};
```

### Initializing a node

```c
struct TreeNode root;
root.data = '*'; /* The root of the expression `(3 + 5) * 2` */

/* Set child links to empty */
root.left = NULL;
root.right = NULL;
```

The field has type `int`. C character constants such as `'*'` and `'+'` also
have integer type, so they can represent operators without relying on a
particular numeric character code.

### Building the complete example

```c
struct TreeNode three = { 3, NULL, NULL };
struct TreeNode five = { 5, NULL, NULL };
struct TreeNode plus = { '+', NULL, NULL };
struct TreeNode two = { 2, NULL, NULL };
struct TreeNode root = { '*', NULL, NULL };

if (plus.left == NULL) {
        plus.left = &three;
}
if (plus.right == NULL) {
        plus.right = &five;
}
if (root.left == NULL) {
        root.left = &plus;
}
if (root.right == NULL) {
        root.right = &two;
}
```

These five live local variables represent `(3 + 5) * 2`. The root stores
`'*'`; its left child stores `'+'` and its right child stores `2`. The `+`
node's left and right children store `3` and `5`, respectively.

### Finding a value recursively

```c
struct TreeNode* tree_find(struct TreeNode *node, int target)
{
        if (node == NULL) {
                return NULL;
        }
        if (node->data == target) {
                return node;
        }

        /* Search the left subtree first */
        struct TreeNode *found = tree_find(node->left, target);
        if (found != NULL) {
                return found;
        }

        /* If not found on the left, search the right subtree */
        return tree_find(node->right, target);
}
```

### Clearing a subtree

```c
void tree_clear(struct TreeNode *node)
{
        if (node == NULL) {
                return;
        }

        /* Clear children recursively */
        tree_clear(node->left);
        node->left = NULL;

        tree_clear(node->right);
        node->right = NULL;

        node->data = 0;
}
```

### Clearing a child

```c
/* Clear the left child and everything below it */
tree_clear(root.left);

/* Detach it cleanly so the tree rule is maintained */
root.left = NULL;
```

The resulting right-only shape can remain a structurally valid general binary
tree. It no longer represents the complete expression `(3 + 5) * 2`, because
the `*` operator is missing its left operand.
