# Chapter 2. Organizing Data in a Hierarchy

## Thinking Logically

### What does hierarchical data look like?

Consider `(3 + 5) * 2`. Add `3` and `5`, then multiply their result by `2`.
The final multiplication depends on the addition below it. A tree can store
this relationship. An expression tree stores operators as branch points and
numbers at the ends of the branches.

We will first connect nodes by hand. Then we will build a tree from the text
`3+5*2` and calculate its value. Without parentheses, multiplication comes
first, so this second expression has a different tree and gives `13`.

### What should each item remember?

Each item needs to store its own actual data (such as a math operator or a number) and the exact locations of the items sitting directly beneath it. To keep things simple, each node only looks downward at its own pieces; it has no idea what larger equation is sitting above it.

### Simple example

In a tree representing an expression, if we use only binary operators such as `+` or `*`, every operator needs exactly two links for its operands. Numbers are calculated as they are, so they do not need any links. If we treat both operators and numbers as the same kind of abstract item, each item only needs a maximum of two links.

### How do we add a new item?

For a binary operator, attach each number or sub-expression to its
corresponding operand position. Left and right must stay distinct because operand order matters for operators such as `-` and `/`.

### How do we build a complete equation?

To build `(3 + 5) * 2` by hand, create nodes for `3`, `5`, and `+`. Link the
two numbers below `+`. Then link this group and the number `2` below `*`.
A completed operator needs both operand subtrees. Its storage can be reserved
before either subtree is finished; the links are filled as construction
continues.

### How do we calculate the final answer?

You start at the very top, but you cannot immediately do the math because the top operator needs the answers from the branches below it. The computer must travel down to the bottom leaves, retrieve the plain numbers, and bring those answers back up one level at a time, applying the operators as it climbs back to the root.

### How can one function handle a whole subtree?

The calculation below an operator is the same kind of problem as the whole
calculation. Ask a function to calculate the left subtree, then the right
subtree, and combine the two returned values. A function that calls itself
on a smaller problem uses recursion.

Each call receives its own node pointer and has its own local variables.
When the left call returns, the parent call resumes with the left result.
It still has work to do on the right. A number is the stopping case, also
called the base case: return the number without making another call.
Every child call moves down a finite tree, so it eventually reaches a leaf.

For `(3 + 5) * 2`, the call on `*` waits for the call on `+`. The `+` call
receives `3` and `5` from its children and returns `8`. The `*` call then
receives `2` from its right child and returns `16`.

### What does going down one branch first mean?

The calculation finishes the left subtree before starting the right
subtree. Following one branch deeply before returning to an unfinished
branch is depth-first search, or DFS. When the goal is to process every
node, we also call it a traversal.

The point at which we process the current node determines the recorded
order. Checking the current node before its children is preorder. Applying
an operator after both children have returned is postorder. The search
later in this chapter uses the first order; expression evaluation uses the
second. Chapter 5 compares preorder, inorder, and postorder using explicit
stacks and loops. Here, function calls remember the unfinished work.

### How can text decide the links?

For `3+5*2`, linking each next operator above everything built so far would
produce `(3+5)*2`. That changes the answer from `13` to `16`. We must let a
tighter operation finish before attaching it as an operand of a looser one.
The rule that `*` and `/` bind more tightly than `+` and `-` is operator
precedence.

Assign precedence `2` to `*` and `/`, and precedence `1` to `+` and `-`.
The function `expr_tree(q, min)` builds a subtree from the remaining text.
The value `min` is the lowest operator precedence that this call may
consume. A lower-precedence operator belongs to an earlier call, so the
current call returns without consuming that operator. Turning text into
this structure is parsing; this method is called precedence climbing.

Our first parser accepts one digit per operand and the binary operators
`+`, `-`, `*`, and `/`. Input contains no spaces, parentheses, unary signs,
or multi-digit numbers. Thus `3+5*2` is accepted, while `(3+5)*2` remains a
tree we build by hand. A later extension could add a separate step for
reading a number or a parenthesized group.

### Where does the next call start reading?

Keep one pointer at the next unread character. Each call advances that same
pointer when it consumes a character. The parameter `q` points to this
pointer, so a child call can move the reading position seen by its caller.
There is no separate queue object. Consuming the front of the remaining
input means advancing the pointer by one character.

For `3+5*2`, the calls behave as follows. Each call first reads one number.

| Call | Action | Next unread input |
| --- | --- | --- |
| `expr_tree(&cursor, 1)` | Read `3`; consume `+`; begin its right operand with minimum `2` | `5*2` |
| Right call, minimum `2` | Read `5`; consume `*`; begin its right operand with minimum `3` | `2` |
| Right call, minimum `3` | Read `2`; reach the end; return the leaf | End |
| Resume minimum `2` | Link `5` and `2` below `*`; return that subtree | End |
| Resume minimum `1` | Link `3` and the `*` subtree below `+`; return the root | End |

The result has `+` at the root because addition is the final operation.

```text
        +
       / \
      3   *
         / \
        5   2
```

### Why pass the operator precedence plus one?

Subtraction of equal precedence must group from the left. In `8-3-2`, the
answer is `(8-3)-2 = 3`, not `8-(3-2) = 7`. This grouping rule is called
left associativity.

After the outer call consumes the first `-`, it calls the right parser with
minimum `2`. That call reads `3`, sees another `-` of precedence `1`, and
returns without consuming it. The outer call builds `8-3`, then consumes the
second `-` and attaches the previous tree on its left. Passing
`precedence(op) + 1` enforces this rule for all four supported operators.
Passing only `precedence(op)` would let the right call take equal-precedence
operators and would group subtraction and division incorrectly.

### How do the answers return through the parsed tree?

The evaluator does not need to compare precedence again. The tree already
records which operands belong to each operator. It follows the links and
waits for child results.

| Current call | Work before returning | Returned value |
| --- | --- | --- |
| Leaf `3` | No child calls | `3` |
| Leaf `5` | No child calls | `5` |
| Leaf `2` | No child calls | `2` |
| Operator `*` | Combine left `5` and right `2` | `10` |
| Operator `+` | Combine left `3` and right `10` | `13` |

The calls enter nodes in the order `+, 3, *, 5, 2`. They finish their
calculations in the order `3, 5, 2, *, +`. Entering an operator's call does
not mean that its arithmetic can happen yet. For `-` and `/`, keep the left
result as the left operand when combining results.

### What happens when we throw away a branch?

Because a node only looks down, it cannot unhook itself from the operation above it. You must ask the parent to clear the selected child's sub-expression, then set that left or right link to `NULL`. Clearing resets the nodes' data and links. It does not release their storage or end their lifetimes.

### How do we describe an item's position?

You trace the path from the final, outermost operation at the very top down to the specific item. Counting the steps on that downward route tells you exactly how deeply buried that part of the expression is.

### How do we find a specific piece of data?

You start at the very top. If it isn't what you are looking for, you search the entire left side of the equation. If you still don't find it, you search the entire right side. You keep repeating this left-then-right checking process until you find a match.

## Calculating Efficiency

### How much memory does one item use?

Every item takes up a fixed, predictable amount of room: space for its data (a number or symbol), plus space for a left and right pointer. Even a plain number at the bottom reserves the space for those two pointers. Also, when searching or calculating deeply through the expression, the computer uses a little bit of temporary memory to keep track of its place. This temporary memory grows based on how deep the branches go.

### How fast is creating or adding one item?

Setting up a new empty item is instantly fast. Hooking it up to an empty left or right spot is also instantly fast because you are just updating one single location, regardless of how massive the entire equation is.

### How fast is finding a value?

Because the data isn't sorted in a clever sequence, the computer might have to open every single node in the worst-case scenario. The time it takes grows steadily in proportion to the total number of items you have stored in the tree.

### How fast is throwing away a whole branch?

Unhooking a single sub-expression from its parent is instantly fast. However, going through and wiping out all the nodes sitting below it takes time. The amount of work grows in proportion to how many items are being thrown away.

### How much work do parsing and evaluation require?

The parser consumes five characters and creates five nodes for `3+5*2`.
The evaluator visits three numbers and applies two operators. For an
accepted expression with `n` characters, there are `n` nodes. Each character
is consumed once, and every node is evaluated once. Both operations take
`O(n)` time. A look at an operator followed by a return does not restart the
scan; the shared reading position never moves backward.

The unfinished evaluation calls follow one root-to-leaf path. If the tree
has height `h`, measured in child links, at most `h + 1` nonempty calls are
active together. This is `O(h + 1)` temporary space, often written `O(h)`
for nontrivial trees. A chain can require space proportional to `n`.
The parser also keeps a bounded set of unfinished calls. With just these
two precedence levels, its calls can nest only at minimum values `1`, `2`,
and `3`, even when the resulting tree is tall.

The example reserves all 20 node slots in advance. `node_count` tells us
how many slots have been used; it does not change the array capacity. A full
tree with binary operators has an odd number of nodes, so the largest
accepted expression in this array uses 19 slots. A larger input is rejected
before an access outside the array.

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

### Base Case

A case that returns without another recursive call. Evaluation stops at a
number; search and clearance stop at `NULL`.

### Depth-First Search (DFS)

Following a branch deeply before returning to unfinished branches. A full
tree traversal processes all nodes this way.

### Preorder and Postorder

Preorder processes the current node before its children. Postorder processes
it after both child subtrees. Both can follow a left-first DFS route.

### Precedence and Associativity

Precedence decides which operators bind more tightly. Associativity decides
how operators of equal precedence group. Our four operators group from the
left.

### Parser and Reading Position

A parser turns input text into a structured representation. The reading
position, or cursor, points to the next character the parser has not consumed.

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

### What must the expression builder preserve?

Every completed operator has exactly two children. Every number has none.
Each new node comes from a fresh array slot; a node is linked in only one
operand position. The array exists for the entire program, so its addresses
remain valid after a parser call returns. A local node inside the parser
would stop existing when that call returned.

During `expr_tree`, `node` identifies the completed expression built so far
in that call. The reading position identifies the first unconsumed
character. A parent can be temporarily incomplete while its right subtree
is being built, but only a completed tree is returned on success.

This small builder reuses one global array. Starting another build replaces
the previous contents, so use the current tree before building another.
On invalid input or exhausted capacity, the wrapper returns `NULL` and
resets `node_count` to zero. It does not preserve an earlier tree. Evaluation
does not change any node and leaves the caller's result unchanged on failure.

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

### Building from an expression string

The parser uses the same node structure as the manually linked tree.

- Start the shared reading position at the beginning and reset `node_count`.
- Require a digit, reserve a checked array slot, and store its numeric value.
- Read the next operator without consuming it yet.
- Return if its precedence is below this call's minimum.
- Otherwise consume the operator and reserve a parent whose left child is the current tree.
- Build its right child recursively with minimum `precedence(op) + 1`.
- Continue with that completed parent as the current tree.
- Reject invalid input, a missing operand, or insufficient node capacity.

### Evaluating an expression tree

The evaluator receives one subtree and a place for its answer.

- Return the stored number at a leaf.
- Evaluate the left child and then the right child into separate local values.
- Apply the current operator to those values in left/right order.
- Reject a missing child, unsupported operator, or division by zero.
- Write the caller's answer only after the current calculation succeeds.

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

The evaluator has a different successful stopping case: a number leaf.
An empty child under an operator is an error. The parser stops normally at
the end of the text or before an operator below its minimum precedence.
Each recursive parser call follows a consumed operator and must read a
number, so it works on a shorter remaining input.

### `char **q`, `*q`, and `**q`

We need a child call to change the caller's reading position. If `cursor`
has type `char *`, then `&cursor` has type `char **` and is passed as `q`.
`*q` is the shared reading pointer. `**q` is the character at that position.
`(*q)++` moves the shared pointer one character forward; `q++` would move
the pointer to the pointer, which is not our goal.

The expression `*(*q)++` reads the current character and advances the shared
pointer. C stores the text digit `'5'` as a character code. Subtracting `'0'`
converts it to the numeric value `5`, because digit codes are consecutive in
C. The parser stores `*(*q)++ - '0'` at a leaf to match the numeric operands
in our manually built trees. Operators remain character constants in the
`int data` field.

### A result pointer and a success value

The evaluator returns `1` for success and `0` for failure. Its `double *out`
parameter points to where the numeric answer should be stored. `double`
allows a fractional result, so `3/2` evaluates to `1.5`. A local answer is
written to `*out` only when no error occurred. In `if (!eval_tree(...))`,
the `!` tests whether the call reported failure.

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

### Reserving nodes and comparing operators

We can now replace manual linking with the parser from the plan. The array
holds the physical nodes. The recursive calls hold pointers into that array.
A checked helper initializes each fresh slot. Returning from a call does
not destroy an array element.

```c
/* One expression at a time; these nodes live for the whole program. */
struct TreeNode nodes[20];
int node_count = 0;

struct TreeNode *new_node(int data)
{
    if (node_count == 20) {
        return NULL;
    }
    struct TreeNode *node = &nodes[node_count++];
    node->data = data;
    node->left = node->right = NULL;
    return node;
}

int precedence(char op)
{
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}
```

### Building the expression recursively

The first digit becomes the current subtree. Each accepted operator becomes
a parent with that subtree on the left. The right recursive call decides
how much of the remaining input belongs below the new parent's right link.
An invalid character is rejected before it can be treated as an operator.

```c
/* q points to a shared cursor; call through build_expression below. */
struct TreeNode *expr_tree(char **q, int min)
{
    if (**q < '0' || **q > '9') {
        return NULL;
    }

    struct TreeNode *node = new_node(*(*q)++ - '0');
    if (node == NULL) return NULL;

    while (**q != '\0') {
        char op = **q;
        int level = precedence(op);
        if (level == 0) return NULL; /* Not a supported operator. */
        if (level < min) break;     /* Leave it for the caller. */

        (*q)++;
        struct TreeNode *parent = new_node(op);
        if (parent == NULL) return NULL;
        parent->left = node;
        parent->right = expr_tree(q, level + 1);
        if (parent->right == NULL) return NULL;
        node = parent;
    }
    return node;
}

struct TreeNode *build_expression(char *text)
{
    node_count = 0;
    if (text == NULL) return NULL;

    char *cursor = text;
    struct TreeNode *root = expr_tree(&cursor, 1);
    if (root == NULL || *cursor != '\0') {
        node_count = 0;
        return NULL;
    }
    return root;
}
```

Call `build_expression`, which resets the array position and passes minimum
`1` to the parser. Do not start at an arbitrary array position or reuse a
previous root after another build. `NULL` means the build failed; partially
written slots are not a completed expression tree.

### Evaluating children before the operator

The leaf case returns a number immediately. Each operator call keeps its
own `left` and `right` results, then applies its operation. These statements
force the left call to finish before the right call begins.

```c
/* Only finite, unshared expression trees; this is not a graph validator. */
int eval_tree(const struct TreeNode *node, double *out)
{
    if (node == NULL || out == NULL) return 0;

    if (node->left == NULL && node->right == NULL) {
        if (node->data < 0 || node->data > 9) return 0;
        *out = node->data;
        return 1;
    }
    if (node->left == NULL || node->right == NULL) return 0;

    double left;
    double right;
    if (!eval_tree(node->left, &left)) return 0;
    if (!eval_tree(node->right, &right)) return 0;

    double result;
    switch (node->data) {
    case '+': result = left + right; break;
    case '-': result = left - right; break;
    case '*': result = left * right; break;
    case '/':
        if (right == 0.0) return 0;
        result = left / right;
        break;
    default: return 0;
    }
    *out = result;
    return 1;
}
```

In particular, `left - right` and `left / right` preserve the operand
positions stored in the tree. A failure in a descendant changes only local
result variables in its ancestors; the caller's output is assigned only
after the entire calculation succeeds. The function assumes finite,
unshared child links and does not detect cycles.

### Running the parser and evaluator together

The complete example is saved in
[`code/lecture/expression_tree.c`](../code/lecture/expression_tree.c). It
includes `<stdio.h>` for printing and `binary_tree.h` for the same node
structure shown above. The earlier manual-link fragments and this program
are separate examples. The existing lab still implements `tree_find` and
`tree_clear`; the lecture program supplies the expression-building example.

```c
int main(int argc, char **argv)
{
    char example[] = "3+5*2";
    char *text = argc > 1 ? argv[1] : example;
    struct TreeNode *root = build_expression(text);
    if (root == NULL) {
        puts("Invalid expression or node array full.");
        return 1;
    }

    double answer;
    if (!eval_tree(root, &answer)) {
        puts("Invalid expression tree or division by zero.");
        return 1;
    }
    printf("%s = %g\n", text, answer);
    return 0;
}
```

Run these commands from `module_02_binary_tree/code` with a C compiler.

```sh
mkdir -p build
cc -std=c11 -Wall -Wextra -Wpedantic -Wconversion -Wshadow -Iinclude \
  lecture/expression_tree.c -o build/expression_tree
./build/expression_tree
./build/expression_tree '8-3-2'
./build/expression_tree '8/4/2'
./build/expression_tree '3/2'
```

The outputs are `3+5*2 = 13`, `8-3-2 = 3`, `8/4/2 = 1`, and `3/2 = 1.5`.
Before running, draw each tree and predict the order in which its operators
finish. Then try `3+`, `12`, and `3/0`. The first two fail during parsing;
the last produces a tree but fails during evaluation. A plain `0` is a
valid one-node expression.

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
