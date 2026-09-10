# Stage B — How the Expression Tree Is Stored

Open this file only when the instructor releases the representation.

A representation is a chosen way to store information. Chapter 2 stores all
nodes in one array and uses integer indices to connect them.

## 1. Name the stored pieces

A node groups a character with two child positions:

```c
struct TreeNode {
    char data; /* A digit character, '+', or '*'. */
    int left;  /* Child index; -1 means no child. */
    int right; /* Child index; -1 means no child. */
};

struct TreeNode nodes[20]; /* Storage for one expression. */
int size = 0;             /* Used nodes and next unused index. */
char eq[20] = "1+2*3";    /* Characters followed by '\0'. */
int pos = 0;              /* Next unread character in eq. */
```

The array brackets select a node; the dot selects one of its fields.
`nodes[1].right` stores an index, not a copy of a node. `-1` means no child.
Index `0` is valid. A root is also an index; it need not be zero.

Label `data`, `left`, `right`, `size`, and `pos` in your own words.

## 2. Reserve nodes, then connect them

`new_node(char data)` uses the next unused position, stores the character,
sets both child indices to `-1`, advances `size`, and returns the reserved
index. Its nodes remain available after the function returns because the
array is declared outside the functions.

```c
/* Suppose indices 0 and 1 already hold initialized nodes. */
nodes[1].left = 0; /* The node at index 0 becomes index 1's left child. */
```

A link does not require neighboring array positions. Nodes are reserved in
reading order, while links record the expression's hierarchy.

## 3. Read the complete example

The tree for `1+2*3` has `size == 5` and `root == 1`:

| Index | `data` | `left` | `right` |
|---|---|---:|---:|
| 0 | `'1'` | -1 | -1 |
| 1 | `'+'` | 0 | 3 |
| 2 | `'2'` | -1 | -1 |
| 3 | `'*'` | 2 | 4 |
| 4 | `'3'` | -1 | -1 |

Text equivalent: index 1 holds `'+'`, with left child 0 and right child 3.
Index 3 holds `'*'`, with left child 2 and right child 4. Indices 0, 2, and 4
are digit leaves. Thus `nodes[nodes[root].right].data` is `'*'`.

## 4. Build terms before adding them

A term is one digit followed by zero or more `*`-digit pairs. `term()` builds
one term and leaves the following `'+'` or `'\0'` unread. `terms()` builds a
sum of complete terms. Both functions share `pos`, the next unread character.
Reading `eq[pos]` inspects a character; consuming it also advances `pos`.

At each new operator, the old subtree becomes its left child, the newly
built operand becomes its right child, and the operator becomes the new
root. Building an entire multiplication term before attaching it to `'+'`
preserves precedence. Repeating this step groups equal operators from left
to right.

## 5. Evaluate children before their operator

`eval_tree(int node)` receives a node index and returns an integer answer.
At a digit leaf, subtract `'0'` from `data` and return that value. At an
operator, evaluate the left child and then the right child, combine their
returned values, and return the result. Recursion means that the evaluator
calls itself on a smaller subtree.

For `1+2*3`, the multiplication returns 6 and the addition returns 7. The
stored characters remain `'*'` and `'+'`; results are local values returned
by function calls.

## 6. Keep the tree and input rules

In a completed expression tree:

1. One root reaches all of its nodes.
2. Every other node occurs in exactly one child position.
3. No downward route returns to an earlier node on that route.
4. Every child index selects an initialized node in `nodes[0]` through
   `nodes[size - 1]`.
5. Digits are leaves; each operator has two operand children.

A general binary tree permits zero, one, or two children. A completed
expression using these binary operators needs two children at each operator.
Our construction joins disjoint subtrees under fresh parents. It does not
check arbitrary malformed trees.

The input is assumed valid and nonempty: single digits alternate with `+` or
`*`, with no spaces or parentheses, at most 19 characters, and every
intermediate and final result fits in `int`. The final `\0` fits in `eq[20]`.
The caller resets `size` and `pos` before each independent build. Such a reset
starts a new expression; saved indices from the previous build must not be
used as its tree.

One representation question to bring to the Cognitive Pause:

____________________________________________________________________
