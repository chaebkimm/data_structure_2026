# Chapter 5. Depth-First Traversal and Expression Trees

We will visit a tree in three orders, build an expression tree from postfix
notation, and write its infix form while preserving its grouping. The code
for this chapter is [`lab.c`](lab.c).

## Thinking Logically

### How do we follow a tree stored in an array?

Chapter 2 connected nodes through array indices. This lab uses the same
idea: each `struct TreeNode` contains a character and two integer child
indices. An absent child is `-1`. A root is also an index; following child
links from it determines which nodes belong to that tree.

`alphabet_init()` prepares ten nodes, `A` through `J`, with no children.
`tree_connect()` connects seven of them and returns index `5`, the node
containing `F`.

```text
          F [5]
         /     \
      A [0]   G [6]
      /   \
   B [1] C [2]
   /   \
D [3] E [4]
```

The brackets show array indices. The nodes stay in their original slots;
assigning a child link does not move a node. `H`, `I`, and `J` remain
unconnected. Although `size` is 10 after initialization, a traversal from
root `5` reaches only seven nodes.

### How do we return after finishing a branch?

A recursive call processes one subtree. While it runs, the caller waits
with its own node index and the place where execution will resume. When the
child call returns, the parent continues with its remaining work.

This follows the last-in, first-out rule from Chapter 4. The runtime's call
stack remembers the unfinished calls. Following one branch before returning
to another is **depth-first search (DFS)**. Processing the nodes in a chosen
order is a **traversal**.

`tree_traversal(i)` first handles the current node, recursively visits its
left child if one exists, handles the current node again, recursively visits
its right child if one exists, and handles the current node a third time.
These three positions let us observe three different traversal orders in
one function.

### What changes when we visit the parent first, between, or last?

A **visit** is the action we choose to perform on the current node. In this
lab, each visit assigns its character to one of three global variables.
The position of that assignment determines the order.

| Order | Assignment position | Assignment sequence for the alphabet tree |
| --- | --- | --- |
| Preorder | `pre_data`, before either child | `F A B D E C G` |
| Inorder | `in_data`, after the left child and before the right | `D B E A C F G` |
| Postorder | `post_data`, after both children | `D E B C A G F` |

For example, the call on `B` first assigns `B` to `pre_data`. It completes
the call on `D`, assigns `B` to `in_data`, completes the call on `E`, and
finally assigns `B` to `post_data`. Each leaf performs its three assignments
without making another call.

These variables hold only the most recently assigned character. The
function does not print or save an entire sequence. After
`tree_traversal(5)` finishes, `pre_data` and `in_data` contain `'G'`, while
`post_data` contains `'F'`. To observe the full sequences, trace the
assignments or set breakpoints at the three visit positions.

### How can a stack build a tree from postfix notation?

Chapter 4 used a stack to evaluate postfix expressions. A digit pushed a
number; an operator popped two values and pushed the calculated result.
Here, we push **node indices** instead. An operator connects two subtree
roots and pushes the new parent index. Construction records the expression
without calculating it.

The lab's input is `post_eq = "123*+"`. It means `1 + (2 * 3)`:

```text
        + [4]
       /     \
    1 [0]   * [3]
            /   \
         2 [1] 3 [2]
```

`eq_tree()` reads left to right. Each input character becomes a node at the
same array index as its position in `post_eq`. A digit becomes a leaf. An
operator takes two existing roots: the first pop supplies its **right**
child, and the second supplies its **left** child. The new root is then
pushed.

The stack below contains indices, with its top on the right.

| Input index and token | Action | Stack, bottom → top |
| --- | --- | --- |
| `0`: `'1'` | Make leaf 0; push 0 | `[0]` |
| `1`: `'2'` | Make leaf 1; push 1 | `[0, 1]` |
| `2`: `'3'` | Make leaf 2; push 2 | `[0, 1, 2]` |
| `3`: `'*'` | Pop right 2, then left 1; connect and push 3 | `[0, 3]` |
| `4`: `'+'` | Pop right 3, then left 0; connect and push 4 | `[4]` |

The returned root is `4`, `size` is 5, and the local stack's `top` is 0.
`size` counts constructed nodes; `top + 1` counts roots currently waiting
on the stack. These are different quantities.

Pop order matters. For postfix `12-`, the node must represent `1-2`.
Making the first popped root the left child would reverse the operands.

### Why is writing the symbols in inorder not always enough?

For the default tree, inorder produces `1+2*3`, which already has the
correct grouping because multiplication has higher precedence than
addition. But postfix `12+3*` builds a different tree whose root is `*`
and whose left subtree is `1+2`. Its infix form must be `(1+2)*3`.

Both trees have the same unparenthesized inorder symbols. Parentheses tell
the reader which operations belong together.

`write_infix(i)` writes a digit immediately. For an operator, it writes the
left expression, the operator, and the right expression. Before and after
each child expression, it adds parentheses when the child's grouping needs
them.

### How do precedence and the child's side determine parentheses?

`prec()` assigns the following comparison values:

| Token | Value returned by `prec` |
| --- | --- |
| `+`, `-` | 1 |
| `*`, `/`, `%` | 2 |
| Digit `0` through `9` | 3 |
| Anything else | 0 |

The value for a digit keeps an operand from being parenthesized. The value
0 is a fallback; it does not make an unsupported character valid input.

For a **left child**, add parentheses when the parent's precedence is
strictly greater than the child's. For a **right child**, add parentheses
when the parent's precedence is greater than or equal to the child's.

| Child position | Condition in the lab | Example |
| --- | --- | --- |
| Left | `prec(c) > prec(l_data)` | `(1+2)*3` |
| Right | `prec(c) >= prec(r_data)` | `1-(2-3)` |

Why are the comparisons different? The supported binary operators group
left to right at equal precedence. `(1-2)-3` can be written as `1-2-3`, but
`1-(2-3)` cannot. Likewise, the tree for `1/(2/3)` needs its right-side
parentheses.

The rule preserves the tree's grouping even when an arithmetic identity
could permit fewer parentheses. For example, postfix `123++` is written as
`1+(2+3)`. The formatter does not simplify expressions.

### How do we start and finish the output string?

Use `start_write_infix(root)` to format a complete expression. It resets
`pos` to 0, calls the recursive writer, and appends the terminating null
character `'\0'`. Each `infix[pos++] = ...` writes one character and advances
the next output position.

Resetting only the position would leave old trailing characters when the
new expression is shorter. The terminator marks the new end. For example,
formatting `123++` and then `12+` produces `1+(2+3)` and then `1+2`, without
retaining the old suffix. The wrapper also permits repeated formatting of
the same tree.

The recursive helper must not reset `pos`: all child calls contribute to
one output string. Because the wrapper uses `pos++` when writing `'\0'`,
its final `pos` counts that terminator as well. For `1+2*3`, `pos` ends at 6.

## Calculating Efficiency

### How much work does construction or traversal require?

Let `n` be the number of postfix tokens and `r` the number of nodes
reachable from the supplied root.

| Operation | Work performed | Time |
| --- | --- | --- |
| `alphabet_init()` | Initialize each of the `capacity` slots | `O(capacity)` |
| `tree_connect()` | Make the fixed example's six child links | `O(1)` |
| `eq_tree()` | Create and push one node per token; pop twice per operator | `O(n)` |
| `tree_traversal(root)` | Perform three visit assignments per reachable node | `O(r)` |
| `start_write_infix(root)` | Write each reachable token and any parentheses | `O(r)` |

Every child subtree is traversed once. Adding parentheses performs a
constant amount of extra work per child link, so it does not change the
formatter's linear running time.

### How much temporary storage is needed?

For a tree of height `h` edges, recursion can keep `h + 1` node calls active
at once. Both `tree_traversal()` and `write_infix()` therefore use
`O(h + 1)` call-stack space. This can grow to `O(r)` for a very unbalanced
tree; the recursion does not allocate one frame for every array slot in
advance.

The explicit stack in `eq_tree()` stores roots of completed subexpressions.
For `123*+`, its maximum used depth is three, immediately after reading the
three digits. A general postfix builder can require `O(n)` stack entries.
The lab reserves exactly ten integer entries regardless of how many it
uses. The node array also reserves ten slots, and the output reserves ten
characters.

### Why does the current output buffer fit?

`post_eq[6]` has room for at most five tokens and one terminator. A valid
binary expression of that length has at most two operators. At most one
operator can be a child of another, so the formatter adds at most one pair
of parentheses: five tokens plus two parentheses plus `'\0'` fit in eight
characters. Thus `infix[10]` is sufficient for the current input limit.

The code does not check capacity while writing. If the input array is
expanded or the writer receives a larger manually constructed expression
tree, its output capacity must be reconsidered; the ten-character buffer
is not a general bound for every tree that fits `nodes[10]`.

## Glossary

| Term | Meaning in this chapter |
| --- | --- |
| Node index | An integer selecting one entry in `nodes`. |
| Root | The starting node index for a tree or subtree. |
| Leaf | A node whose two child indices are `-1`. |
| Traversal | Processing nodes in a chosen order. |
| Visit | The selected action at a node; in `tree_traversal`, assigning its character. |
| Depth-first search | Finishing a branch before returning to remaining branches. |
| Preorder | Current node, left subtree, right subtree. |
| Inorder | Left subtree, current node, right subtree. |
| Postorder | Left subtree, right subtree, current node. |
| Call stack | Runtime storage for unfinished function calls. |
| Postfix | Notation that places an operator after its operands. |
| Infix | Notation that places an operator between its operands. |
| Precedence | The priority that determines grouping between different operator levels. |
| Left associativity | Grouping equal-precedence operators from left to right. |
| Null terminator | The character `'\0'` marking the end of a C string. |

## Invariant

### What must remain true about the tree?

A present child is a valid initialized index in `nodes`; an absent child is
`-1`. A tree has no cycles, and each non-root node has exactly one parent.
The recursive functions receive a valid root index. They do not accept
`-1` as an empty-tree argument or check for cycles.

`write_infix()` additionally requires an expression tree: digit leaves and
supported binary operators with two children. The alphabet tree is suitable
for `tree_traversal()`, but not for the infix writer.

Initialize the alphabet nodes before connecting them. When switching to
an expression, `eq_tree()` resets `size` and reuses the same node array.
The earlier alphabet tree is no longer available through its old links.

### What does the postfix stack represent?

After each processed token, every stack entry is the root of a complete
subexpression from the processed prefix. A digit contributes a new leaf.
An operator replaces the two most recent roots with their new parent.
Earlier roots remain below them.

The lab explicitly assumes a well-formed, nonempty postfix expression
using single-digit operands and binary `+`, `-`, `*`, `/`, or `%`. Every
operator must have two available roots, and exactly one root must remain
at the end. The input has no spaces, unary operators, or multidigit
operands and must fit in `post_eq` with its terminator. The builder relies
on these conditions rather than validating them.

### What does the output position represent?

While `write_infix()` runs, `infix[0]` through `infix[pos - 1]` contain the
characters written so far, and `pos` is the next free position. Child calls
continue at that position. The wrapper resets it before traversal and
terminates the completed string afterward.

## Coding Plan

1. Store ten `struct TreeNode` entries, using `-1` for absent children.
2. Initialize the alphabet nodes and connect the tree rooted at `F`.
3. Place the preorder, inorder, and postorder assignments around the two
   recursive child calls. Trace each assignment sequence separately.
4. Read `post_eq` from left to right. Create a node for every token and
   use a local stack of indices to connect operators to completed subtrees.
5. Define `prec()` for the supported operators and digit leaves.
6. Write the left subtree, current operator, and right subtree, using `>`
   on the left and `>=` on the right to decide parentheses.
7. Wrap the writer with a position reset and a final null terminator.
8. Compare the default, left-parenthesized, and right-parenthesized cases;
   then format a shorter expression to check that no old suffix remains.

## C Code

The following functions are the implementation in [`lab.c`](lab.c). Its
child links and temporary stack entries are integers, and its traversal
and formatting functions call themselves recursively.

### How are nodes initialized and connected?

```c
struct TreeNode {
    char data;
    int left;
    int right;
};

struct TreeNode nodes[10];
int capacity = 10;
int size = 0;

void alphabet_init() {
    size = capacity;
    for (int i = 0; i < capacity; i++) {
        nodes[i].data = 'A' + i;
        nodes[i].left = nodes[i].right = -1;
    }
}

int tree_connect() {
    int root = 0;
    nodes[root].left = 1;
    nodes[root].right = 2;
    nodes[1].left = 3;
    nodes[1].right = 4;
    nodes[5].left = root;
    root = 5;
    nodes[5].right = 6;
    return root;
}
```

### Where are the three visit positions?

```c
int pre_data, in_data, post_data;

void tree_traversal(int i) {
    pre_data = nodes[i].data;
    if (nodes[i].left != -1) {
        tree_traversal(nodes[i].left);
    }
    in_data = nodes[i].data;
    if (nodes[i].right != -1) {
        tree_traversal(nodes[i].right);
    }
    post_data = nodes[i].data;
}
```

The globals have type `int`, but these assignments store character codes.
Using `%c` in the demonstration below displays the corresponding symbols.

### How does postfix construction connect the children?

```c
char post_eq[6] = "123*+"; /* assume no malformed post_eq */

int eq_tree() {
    int stack[10];
    int top = -1;
    size = 0;
    for (int i = 0; post_eq[i] != '\0'; i++) {
        char c = post_eq[i];
        nodes[i].data = c;
        if (c >= '0' && c <= '9') {
            nodes[i].left = nodes[i].right = -1;
        } else {
            nodes[i].right = stack[top--];
            nodes[i].left = stack[top--];
        }
        stack[++top] = i;
        size++;
    }
    return stack[top];
}
```

`top = -1` marks an empty stack. `stack[++top]` increments the index before
selecting the new slot. `stack[top--]` reads the current top slot and then
decrements the index. The two pop statements execute in order, so the
right child is taken before the left child.

Digits remain characters such as `'2'`; construction does not convert
them with `c - '0'`. There is no expression evaluator in this lab.

### How are precedence and parentheses written?

```c
int prec(char op) {
    if (op == '+' || op == '-') {
        return 1;
    }
    else if (op == '*' || op == '/' || op == '%') {
        return 2;
    }
    else if (op >= '0' && op <= '9') {
        return 3;
    }
    return 0;
}

char infix[10] = "";
int pos = 0;

void write_infix(int i) {
    char c = nodes[i].data;
    if (c >= '0' && c <= '9') {
        infix[pos++] = c;
        return;
    }

    int l = nodes[i].left;
    char l_data = nodes[l].data;
    if (prec(c) > prec(l_data)) {
        infix[pos++] = '(';
    }
    write_infix(nodes[i].left);
    if (prec(c) > prec(l_data)) {
        infix[pos++] = ')';
    }

    infix[pos++] = c;

    int r = nodes[i].right;
    char r_data = nodes[r].data;
    if (prec(c) >= prec(r_data)) {
        infix[pos++] = '(';
    }
    write_infix(r);
    if (prec(c) >= prec(r_data)) {
        infix[pos++] = ')';
    }
}

void start_write_infix(int root) {
    pos = 0;
    write_infix(root);
    infix[pos++] = '\0';
}
```

`l` and `r` hold integer indices; `l_data` and `r_data` hold the characters
stored at those indices. The same condition appears before and after each
child call so that every opening parenthesis has a matching closing one.

### How do we run the lab and compare results?

`lab.c` defines the operations but has no `main`. A supplied version of the
driver is in [`code/lecture/lab_demo.c`](../code/lecture/lab_demo.c); run
`make lecture` from `module_05_tree_dfs/code` to build and execute it.

To try the example beside the lab instead, save the following as `demo.c`.
This small driver includes the lab once; do not also pass `lab.c` as a
separate source file when compiling this driver.

```c
#include <stdio.h>
#include <string.h>
#include "lab.c"

int main(void) {
    alphabet_init();
    int root = tree_connect();
    tree_traversal(root);
    printf("Last visits: %c %c %c\n", pre_data, in_data, post_data);

    root = eq_tree();
    start_write_infix(root);
    printf("%s -> %s\n", post_eq, infix);

    strcpy(post_eq, "12+3*");
    root = eq_tree();
    start_write_infix(root);
    printf("%s -> %s\n", post_eq, infix);

    strcpy(post_eq, "123--");
    root = eq_tree();
    start_write_infix(root);
    printf("%s -> %s\n", post_eq, infix);

    strcpy(post_eq, "12+");
    root = eq_tree();
    start_write_infix(root);
    printf("%s -> %s\n", post_eq, infix);
    return 0;
}
```

`strcpy` is declared in `<string.h>` and copies the source string including
its terminator. Each string above fits `post_eq[6]`. Rebuilding the tree
after each change replaces the previous expression's nodes.

From `module_05_tree_dfs/student`, compile and run:

```sh
cc -std=c11 -Wall -Wextra demo.c -o /tmp/tree_dfs_lab
/tmp/tree_dfs_lab
```

The output is:

```text
Last visits: G G F
123*+ -> 1+2*3
12+3* -> (1+2)*3
123-- -> 1-(2-3)
12+ -> 1+2
```

The first line reports the final contents of the three visit variables,
not three complete traversals. The remaining lines show precedence,
parentheses on both sides, and replacement by a shorter output string.
