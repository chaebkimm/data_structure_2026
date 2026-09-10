# Chapter 2. Organizing Data in a Hierarchy

## Thinking Logically

### What does hierarchical data look like?

A tree can store structural information, such as operator precedence in the expression `1 + 2 * 3`.

### How do we store the structural information?

In the expression `2 * 3`, the `*` operator multiplies `2` and `3`, so it stores `2` on the left and `3` on the right. In the expression `1 + 2 * 3`, the `+` operator adds `1` to the result of the multiplication, so it stores `1` on the left and the `*` node on the right.

### How do we calculate the expression stored hierarchically?

In the expression `2 * 3`, the `*` operator multiplies `2` and `3`, which is `6`. In the expression `1 + 2 * 3`, the `+` operator adds `1` to the result of the `*` operator (`6`), which results in `7`.

### How do we access the entire expression?

In the expression `2 * 3`, since the `*` operator stores the information for `2` and `3`, we access the whole expression through the `*` operator. In the expression `1 + 2 * 3`, the `+` operator stores the information for `1` and the `*` operator, and the `*` operator stores the information for `2` and `3`. Therefore, we access the whole expression through the `+` operator.

### What do we store for each operator or number?

We store the actual characters, such as `1` or `*`, and the information for the left and right sides of the operator.

### How do we connect an item to this data structure?

An item can be connected to the left or right side of the operator in the data structure. Alternatively, the root used to access the data structure can be connected to the left or right side of a new operator.

### A simple example

Let's consider a valid expression consisting of single digits and the `+` and `*` operators. Start with a digit, then follow each operator with one digit. Use no spaces or parentheses and at most 19 characters, leaving room for the string's ending `\0` in `eq[20]`. Assume that every intermediate result and the final answer fit in an `int`; the example does not check these input conditions.

### How do we calculate the result of the operation?

For numbers, such as `1` or `2`, the result is the same as the corresponding integer value. For operators, such as `+` or `*`, the result is calculated by performing the operation on the results of the left and right sides, which are calculated recursively prior to the operation.

### What is the hierarchical characteristic of a term with zero or more `*`s?

We group a sequence like `1 * 2 * 3` from left to right as `(1 * 2) * 3`. The first `*` node becomes the left child of the second `*` node. For a longer sequence, each new `*` becomes a parent of the term built so far.

### How do we build the hierarchy of a term with zero or more `*`s?

We can build the hierarchy by keeping track of the root to access the expression that has been processed so far. Initially, the root is the first number. As we encounter a `*` while scanning the expression, the old root becomes the left side of the `*`, the next number becomes the right side of the `*`, and the `*` becomes the new root.

### How do we build the hierarchy of an expression with `*`s and `+`s?

Because `*` has a higher operator precedence than `+`, we can treat the expression as a sum of terms. Initially, the root is the first term. As we encounter a `+` while scanning the expression, the old root becomes the left side of the `+`, the next term becomes the right side of the `+`, and the `+` becomes the new root.

## Calculating Efficiency

### How much memory does one item use?

Every item takes up space for its data (a number or symbol), plus space for left and right information.

### How much memory is used for iterating over items?

When searching or calculating deeply through the expression, the computer uses temporary memory to keep track of its place. This temporary memory grows based on how deep the branches go.

### How fast is creating or adding one item?

Setting up a new empty item takes constant time. Hooking it up to an empty left or right spot also takes constant time because you are just updating one single location, regardless of how massive the entire equation is.

### How fast is iterating over items?

The time it takes grows in proportion to the total number of items stored in the tree.

## Glossary

### Node

One object that stores data and links to related nodes.

### Tree

A hierarchy in which a node may have children.

### Binary Tree

A hierarchy in which every node has at most two children, specifically distinguished as left and right.

### Expression Tree

A tree that represents an expression. In this chapter's example, an operator node has two operand children and a number node is a leaf.

### Root

The top node (usually the final operation to be evaluated in an expression).

### Parent

A node that is directly above another node in the hierarchy.

### Child

A node that is directly below a parent node.

### Sibling

A different node that shares the same parent.

### Ancestor

An ancestor is a node earlier on the path from the root to another node. Ancestors still exist even though our nodes do not store upward links.

### Descendant

A node found below a given node by following one or more child links.

### Leaf

A node with no children.

### Subtree

One node together with all of its descendants (a standalone sub-expression).

### Recursion

A technique in which a function calls itself on a smaller part of the same problem. A tree function can process one node and then call itself on each child subtree.

### Base Case

A case that returns without another recursive call. Evaluation stops at a number.

## Invariant

### What is the invariant (the golden rule) in this data structure?

- The Root Rule: A nonempty tree has exactly one root at the very top.

- The Single-Parent Rule: Every node below the root appears in exactly one child position. Two parent nodes cannot share the exact same child node, and one parent cannot use the exact same node as both its left and right child.

- The Acyclicity Rule (No Loops): A node cannot be placed inside itself, and you can never create an endless loop where following child links downward leads you back to where you started.

### What happens if an invariant is broken?

- If the Root Rule breaks: A search that starts at one root cannot reach the nodes below the other root.

- If the Single-Parent Rule breaks: A search may visit a node twice.

- If the Acyclicity Rule breaks: A search may get stuck in an infinite loop.

### How do we keep the invariant intact?

Each new parent joins the existing subtree to newly built nodes, preserving a tree without cycles or shared children. The programmer must use initialized nodes and valid indices into the live `nodes` array.

## Coding Plan

All nodes live in the `nodes` array. A link or root is an integer index into that array: `nodes[root]` is the node at the root of the current subtree. The value `-1` means no child; `0` is a valid index for the first node.

### Designing a node

- Store one character named `data`, such as `2`, `+`, or `*`.
- Store two indices: one for the `left` child, one for the `right` child.

### Reserving and initializing a node

- Use the next unused array position, recorded by `size`.
- Save the data and set both the left and right indices to `-1`.
- Advance `size` and return the position just reserved as the new node's index.

### Adding a child

- Choose an empty child position, whose index is `-1`.
- Store the child's index in the parent's `left` or `right` field.

### Building a term from an expression string

The shared variable `pos` marks the next unread character in `eq`. To consume a character means to read it and advance `pos`.

1. Consume a digit, reserve its node, and make its index the current root.
2. While the next character is `*`, consume it and reserve an operator node.
3. Consume the following digit and reserve its node.
4. Link the old root on the operator's left and the new digit on its right.
5. Make the operator the current root and repeat from step 2.
6. Return the root when the next character is not `*`, leaving that character unread.

### Building a sum of terms from an expression string

For valid input, the final unread character is `\0`.

1. Build a complete term and make its index the current root.
2. While the next character is `+`, consume it and reserve an operator node.
3. Build the next complete term.
4. Link the old root on the operator's left and the new term on its right.
5. Make the operator the current root and repeat from step 2.
6. Return the root when the next character is not `+`.

### Evaluating an expression tree

1. At a digit leaf, convert its character to an integer by subtracting `'0'`
   and return that value. This is the base case.
2. At an operator, evaluate the left child and then the right child into
   separate local values.
3. Apply the current operator to those values and return the calculated result.

## New C Syntax Explained

### Defining a `struct` tag

A custom data type can be defined with the `struct` keyword and a tag, where the members are declared in the following curly braces `{}`. For example, `struct TreeNode { char data; int left; int right; };`

### Using a `struct` tag

The tag tells the compiler what kind of custom data type you are referencing. Every time you declare a node variable, you write `struct TreeNode`.

### `.` (Accessing Fields)

`nodes[root].data` accesses the `data` field of the node at index `root`. The brackets select an array element, and the dot selects one of its fields.

### Recursive Functions

A recursive function calls itself on a smaller part of the same problem. A recursive function needs a base case. Without a base case, calls could continue infinitely. The evaluator has a number node as a base case.

## C Code

### Designing a node

The same structure represents a digit leaf or an operator with two children.

```c
struct TreeNode {
        char data; /* A digit character, '+', or '*'. */
        int left;  /* Left child's index in nodes, or -1 if absent. */
        int right; /* Right child's index in nodes, or -1 if absent. */
};
```

### Reserving nodes

`size` counts the used nodes and also identifies the next unused position. The array is declared outside the functions, so its nodes remain available after a function returns.

```c
/* One expression at a time; these nodes live for the whole program. */
struct TreeNode nodes[20];
int size = 0;

int new_node(char data)
{
        nodes[size].data = data;
        /* A newly reserved node has no children yet. */
        nodes[size].left = nodes[size].right = -1;
        return size++; /* Advance size; the returned value is its old index. */
}
```

### Building a term

`term()` builds one digit followed by zero or more `*`-digit pairs. In `eq[pos++]`, the old value of `pos` selects the character, then `pos` advances. Checking `eq[pos]` in the loop leaves the character unread.

```c
char eq[20] = "1+2*3"; /* No spaces; the string ends with '\0'. */
int pos = 0;          /* Index of the next unread character. */

int term(void)
{
        /* Begin with the first digit as a one-node subtree. */
        int root = new_node(eq[pos++]);
        while (eq[pos] == '*') {
                int op = new_node(eq[pos++]);  /* Consume '*'. */
                int num = new_node(eq[pos++]); /* Consume the next digit. */
                /* Group the term built so far with the next digit. */
                nodes[op].left = root;
                nodes[op].right = num;
                root = op; /* The new operator is now the subtree's root. */
        }
        /* Leave '+' or '\0' unread for the caller. */
        return root;
}
```

### Building a sum of terms

`terms()` calls `term()` for each operand of `+`. Both functions share `pos`, so each call continues where the preceding call stopped.

```c
int terms(void)
{
        int root = term();
        while (eq[pos] == '+') {
                int op = new_node(eq[pos++]); /* Consume '+'. */
                /* Finish the next term, including all its multiplications. */
                int next_term = term();
                nodes[op].left = root;
                nodes[op].right = next_term;
                root = op; /* The new '+' joins the two subtrees. */
        }
        return root; /* Index of the whole expression's root. */
}
```

### Evaluating children before the operator

`node` is an index, while the return value is the subtree's answer. Subtracting `'0'` converts a stored digit such as `'3'` to the integer `3`, because C's digit character codes are consecutive. This evaluator assumes a completed tree from valid input; it does not validate malformed trees.

```c
int eval_tree(int node)
{
        /* Base case: a digit leaf already supplies its numeric answer. */
        if (nodes[node].data >= '0' && nodes[node].data <= '9') {
                return nodes[node].data - '0';
        }

        /* A valid tree contains only digits and the two supported operators. */
        if (nodes[node].data != '+' && nodes[node].data != '*') return -1;

        /* Each call keeps its own results; the left call finishes first. */
        int left = eval_tree(nodes[node].left);
        int right = eval_tree(nodes[node].right);

        /* Combine the returned values without changing the stored operator. */
        if (nodes[node].data == '+') return left + right;
        if (nodes[node].data == '*') return left * right;

        return -1;
}
```

### Running the example

`main` starts the program, builds the tree once, and prints the result returned by the evaluator.

```c
#include <stdio.h> /* Declares printf. */

int main(void)
{
        int root = terms();           /* Build the tree and keep its root index. */
        int answer = eval_tree(root); /* Evaluate the tree from that index. */
        printf("%s = %d\n", eq, answer);
        return 0;
}
```

The output is `1+2*3 = 7`. In `printf`, `%s` prints the expression string, `%d` prints the integer answer, and `\n` ends the line. The root stores `'+'`; its right child stores `'*'`, whose children store `'2'` and `'3'`.
