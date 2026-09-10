# Chapter 5. Traversing a Tree with a Stack

## Thinking Logically

### How do we return to an unfinished branch without recursion?

Chapter 2 built an expression tree using loops and evaluated it recursively. Each
unfinished call remembered where to continue after a child returned. Chapter
4 introduced a stack that stores values and takes the newest value out first.
We can now store the unfinished tree work in that stack ourselves.

Use `3+5*2` as another example of Chapter 2's expression-tree idea. Its tree has five nodes.

```text
        +
       / \
      3   *
         / \
        5   2
```

After reaching `3`, we still need to reach `*` and its children. A variable
that only holds `3` cannot recover the root because the nodes have no parent
links. We must save an address before leaving an unfinished branch.

Following one branch before returning to the remaining branches is
**depth-first search (DFS)**. Chapter 2's evaluator followed this pattern. Processing
every node in a chosen order is a **traversal**. This chapter implements three
DFS traversal orders using loops and an explicit stack. None of the three
traversal functions calls itself.

In this chapter, to **visit** a node means to print its stored symbol once.
Reading a node address or placing it on the stack does not yet visit it.
That distinction matters when we postpone printing a parent.

### What changes when we print the parent first, between, or last?

The expression tree has a current node, a left subtree, and a right subtree.
We keep the left subtree before the right subtree. We choose when to print
the current node relative to those two subtrees.

| Order | Position of the current node | Symbols for `3+5*2` |
| --- | --- | --- |
| Preorder | Current, left subtree, right subtree | `+ 3 * 5 2` |
| Inorder | Left subtree, current, right subtree | `3 + 5 * 2` |
| Postorder | Left subtree, right subtree, current | `3 5 2 * +` |

The node's first arrival and its printing time need not be the same moment.
For example, postorder reaches `+` first but prints `+` last.

### How do we print the current node before its children?

We can print a node as soon as we take its address from the stack. Its
children become future work. To process the left child next, push the right
child first and the left child second. The left child is then on top.

This is **preorder traversal**. Start by pushing the root. Repeatedly pop,
print, and push the existing children. Do not push `NULL`.

In every stack below, the bottom is on the left and the **top is on the
right**. Each table row shows the state after the listed action.

| Action | Stack, bottom → top | Symbols printed so far |
| --- | --- | --- |
| Push root `+` | `[+]` | Empty |
| Pop and print `+`; push `*`, then `3` | `[*, 3]` | `+` |
| Pop and print `3`; it has no children | `[*]` | `+ 3` |
| Pop and print `*`; push `2`, then `5` | `[2, 5]` | `+ 3 *` |
| Pop and print `5` | `[2]` | `+ 3 * 5` |
| Pop and print `2` | `[]` | `+ 3 * 5 2` |

The stack holds roots of subtrees that have not started. Each popped root is
printed before its children. Pushing right before left places the entire
left subtree's work above the waiting right subtree. Reversing the two
pushes would produce `+ * 2 5 3` on this tree.

### How do we delay printing a parent until its left subtree is finished?

Preorder prints `+` too early for the usual expression order. We need to
reach the left subtree while keeping the unprinted parent available.

Keep a `current` pointer. While `current` is not `NULL`, push its address and
move left. When the left path ends, pop one saved node and print it. Set
`current` to that node's right child. Repeat the same steps.

This is **inorder traversal**. The stack holds nodes whose own symbols have
not been printed. Printing a popped node is safe because its left subtree
has just finished. Its right subtree still needs work.

| Action | `current` | Stack, bottom → top | Symbols printed so far |
| --- | --- | --- | --- |
| Start at root | `+` | `[]` | Empty |
| Push `+`; move left | `3` | `[+]` | Empty |
| Push `3`; move left | `NULL` | `[+, 3]` | Empty |
| Pop and print `3`; move right | `NULL` | `[+]` | `3` |
| Pop and print `+`; move right | `*` | `[]` | `3 +` |
| Push `*`; move left | `5` | `[*]` | `3 +` |
| Push `5`; move left | `NULL` | `[*, 5]` | `3 +` |
| Pop and print `5`; move right | `NULL` | `[*]` | `3 + 5` |
| Pop and print `*`; move right | `2` | `[]` | `3 + 5 *` |
| Push `2`; move left | `NULL` | `[2]` | `3 + 5 *` |
| Pop and print `2`; move right | `NULL` | `[]` | `3 + 5 * 2` |

An empty stack alone does not end this algorithm. After printing `+`, the
stack is empty but `current` still points to `*`. Stop only when `current`
is `NULL` **and** the stack is empty.

### How do we know whether a parent's right subtree has finished?

Printing a parent after its left subtree is still too early for evaluation.
The parent operator also needs the right subtree's result. We must keep the
parent on the stack until both sides have finished.

Again, push nodes while moving left. At the end of a left path, inspect the
top node without removing it. If its right subtree still needs work, move
right and keep the parent waiting. Otherwise, pop and print the parent.

This is **postorder traversal**. We need one more pointer,
`last_visited`, to remember the last node printed. Completing a subtree in
postorder prints that subtree's root last. Therefore, when inspecting a
waiting parent, `last_visited == parent->right` tells us that its right
subtree has finished.

If the right child is `NULL`, there is no right subtree to process. If the
right child exists and differs from `last_visited`, enter it. In both cases,
the left subtree has already finished when we reach this decision.

| Action | `current` | Stack, bottom → top | `last_visited` | Symbols printed so far |
| --- | --- | --- | --- | --- |
| Start at root | `+` | `[]` | `NULL` | Empty |
| Push `+`, then `3`, moving left each time | `NULL` | `[+, 3]` | `NULL` | Empty |
| `3` has no right child: pop and print it | `NULL` | `[+]` | `3` | `3` |
| Inspect `+`: its right child `*` is unfinished | `*` | `[+]` | `3` | `3` |
| Push `*`, then `5`, moving left each time | `NULL` | `[+, *, 5]` | `3` | `3` |
| `5` has no right child: pop and print it | `NULL` | `[+, *]` | `5` | `3 5` |
| Inspect `*`: its right child `2` is unfinished | `2` | `[+, *]` | `5` | `3 5` |
| Push `2`; move left | `NULL` | `[+, *, 2]` | `5` | `3 5` |
| `2` has no right child: pop and print it | `NULL` | `[+, *]` | `2` | `3 5 2` |
| Inspect `*`: `last_visited` is its right child; pop and print | `NULL` | `[+]` | `*` | `3 5 2 *` |
| Inspect `+`: `last_visited` is its right child; pop and print | `NULL` | `[]` | `+` | `3 5 2 * +` |

Compare node **addresses**, not stored symbols. Two different nodes can both
store `'*'`. Equal symbols do not show which subtree has finished.

### Why does each node appear exactly once?

The input must be a valid tree. It has no cycles and no child shared by two
parents. Every non-root node therefore has exactly one incoming child link.
The traversal must keep those links and node lifetimes unchanged.

Preorder schedules each child once when its parent is popped. Inorder
removes a parent before entering its right subtree, so that parent cannot
schedule the same right subtree again. Postorder keeps a parent until the
right child is `NULL` or that right subtree's root was last printed. This
check prevents reentering a completed right subtree.

These are the rules that must remain true during each loop, or its
**invariants**. They let each algorithm account for the waiting work without
adding a visited marker to every tree node.

An empty tree prints nothing. A single node is pushed and popped once. Do
not call `pop` or `peek` on an empty stack. In inorder and postorder, entering
the branch for `current == NULL` while the outer loop still runs guarantees
that a saved node exists.

### How do these orders connect to expression trees?

Preorder puts an operator before its operands. It can guide a copy operation
that creates each parent before connecting its copied children. Saving an
arbitrary binary tree also needs enough information to recover missing
children; a bare list of symbols does not always preserve the shape.

Inorder places an operator between its operands. Printing symbols alone does
not always preserve grouping. A tree for `(3+5)*2` also has the inorder
sequence `3 + 5 * 2`, although its value is `16` rather than `13`. A formatter
must add parentheses where the tree's grouping requires them.

Postorder gives `3 5 2 * +` for the running tree. Both operands precede each
operator. An evaluator can read this sequence with a stack of numbers: push
`3`, `5`, and `2`; apply `*` to `5` and `2` and push `10`; then apply `+` to
`3` and `10` to get `13`. Pop the right operand before the left operand.
Their positions matter for subtraction and division.

The node stack chooses the order in which nodes are visited. A value stack
would hold intermediate arithmetic results. The C example below prints the
three orders; loop-based construction and recursive evaluation were the main work of
Chapter 2.

## Calculating Efficiency

### How many stack operations does each traversal perform?

The running tree has five nodes. Each traversal pushes five node addresses,
pops five addresses, and prints five symbols. Postorder also inspects a
waiting parent before deciding whether to enter its right subtree or print
it. Each right subtree is entered only once, so those inspections add a
bounded amount of work per node.

For a tree with `n` nodes, each traversal performs work proportional to `n`.
Its running time is `O(n)`. This count treats printing one stored character
as one fixed-size action.

### How many addresses must be remembered at the same time?

The three algorithms need different kinds of waiting work, even on the same
tree. Count the largest number of addresses present in each trace.

| Traversal | Largest stack in the running example | Maximum used entries |
| --- | --- | --- |
| Preorder | `[*, 3]` or `[2, 5]` | 2 |
| Inorder | `[+, 3]` or `[*, 5]` | 2 |
| Postorder | `[+, *, 5]` or `[+, *, 2]` | 3 |

The tree's height is two edges. A root-to-leaf path can therefore contain
three nodes. More generally, a tree of height `h` has at most `h + 1` nodes
on such a path. Inorder saves unfinished ancestors. Postorder saves the
unfinished path. Preorder saves at most one waiting sibling per level plus
the next node to process.

Thus these algorithms use at most `O(h + 1)` stack entries. For nontrivial
trees this is commonly written `O(h)`. A chain can require `n` entries in
inorder or postorder, depending on its direction. Preorder needs only one
entry on a chain because no sibling branch is waiting. Height gives an upper
bound; it does not force every traversal to fill that many entries.

The sample reserves an array of 100 pointers because
`TREE_DFS_POOL_CAPACITY` is 100. That array occupies room for all 100 pointers
even when only two are in use. Distinguish the fixed reserved storage from
the number of used entries. For a configurable capacity `C`, reserved stack
storage is `O(C)`. The two extra pointers in postorder take constant space.

### What happens when the fixed stack fills?

Check capacity before storing the next address. A rejected `push` changes
neither the stored addresses nor `size`. The traversal then returns `false`.
Its tree remains unchanged, but symbols printed before the failure remain
on the screen. The example does not roll back console output.

A valid tree with at most 100 nodes fits this sample's stack. A larger tree
may also fit if its waiting work stays small, but that is not guaranteed.
Removing recursion does not remove the need to store unfinished work.

## Glossary

The names below refer to the actions already traced in this chapter.

| Term | Meaning |
| --- | --- |
| Traversal | Processing every node in a chosen order. |
| Visit | Performing the selected action on a node; here, printing its symbol. |
| Depth-first search | Finishing one branch before returning to remaining branches. |
| Iterative traversal | A traversal implemented with loops instead of recursive traversal calls. |
| Explicit stack | A stack whose storage, pushes, and pops appear in our code. |
| Preorder | Current node, left subtree, right subtree. |
| Inorder | Left subtree, current node, right subtree. |
| Postorder | Left subtree, right subtree, current node. |
| `current` | The root of the next subtree to enter. |
| `last_visited` | In postorder, the address of the last node printed. |
| Loop invariant | A rule about stored state and unfinished work that remains true as the loop runs. |

## Coding Plan

The code follows the same five-node tree and the same stack orientation as
the hand traces.

1. Store `const Node *` addresses in a fixed array. Track the used entries
   with `size`. Make `push` reject a full array before changing it. Call
   `pop` and `peek` only when the stack is nonempty.
2. Implement preorder by pushing the root, then popping and printing one
   node at a time. Push an existing right child before an existing left
   child.
3. Implement inorder with `current`. Save nodes while moving left. Pop and
   print a node only after the left path ends. Continue at its right child.
4. Implement postorder with `current` and `last_visited`. Inspect the top
   before popping it. Keep the parent waiting while its right subtree runs.
5. Build `3+5*2` with local nodes and run all three traversals. Compare the
   output and maximum stack sizes with the hand traces. Check an empty tree,
   a single node, and a tree with only one child at each level.

## C Code

### How does the stack store node addresses?

The complete program is
[`code/lecture/iterative_traversals.c`](../code/lecture/iterative_traversals.c).
It includes the existing `tree_dfs.h`, whose `Node` contains `char data`,
`left`, and `right`. This module stores a digit as a character token such as
`'3'`, as Chapter 2 does. This module's child links are pointers, while
Chapter 2's child links are array indices. The lecture sample builds its own nodes
and does not pass one module's node type to another module's functions.

A `const Node *` lets the traversal read a node without changing that node
through the pointer. The stack holds copies of addresses; it does not copy
the nodes.

```c
#include "tree_dfs.h"

#include <stdbool.h>
#include <stdio.h>

typedef struct {
    const Node *items[TREE_DFS_POOL_CAPACITY];
    size_t size;
} NodeStack;

static bool push(NodeStack *stack, const Node *node)
{
    if (stack->size == TREE_DFS_POOL_CAPACITY) return false;
    stack->items[stack->size++] = node;
    return true;
}

/* Call pop and peek only when size is greater than zero. */
static const Node *pop(NodeStack *stack)
{
    return stack->items[--stack->size];
}

static const Node *peek(const NodeStack *stack)
{
    return stack->items[stack->size - 1U];
}
```

The Boolean result of `push` reports whether the address was stored. Every
traversal checks it. `NodeStack stack = {0}` initializes an empty stack.

### How does preorder make the left child next?

The two child pushes are in the reverse of their processing order. That
places the left child on top of the waiting right child.

```c
static bool preorder(const Node *root)
{
    NodeStack stack = {0};

    if (root == NULL) return true;
    if (!push(&stack, root)) return false;

    while (stack.size > 0U) {
        const Node *node = pop(&stack);
        printf("%c ", node->data);

        if (node->right != NULL && !push(&stack, node->right)) return false;
        if (node->left != NULL && !push(&stack, node->left)) return false;
    }
    return true;
}
```

### How does inorder return to an unprinted parent?

The inner loop saves the left path. The outer loop continues as long as
there is either a subtree to enter or a saved node to resume.

```c
static bool inorder(const Node *root)
{
    NodeStack stack = {0};
    const Node *current = root;

    while (current != NULL || stack.size > 0U) {
        while (current != NULL) {
            if (!push(&stack, current)) return false;
            current = current->left;
        }

        current = pop(&stack);
        printf("%c ", current->data);
        current = current->right;
    }
    return true;
}
```

### How does postorder keep the parent until both sides finish?

Looking at the top with `peek` preserves the parent while its right subtree
runs. Only the branch that prints the node removes it from the stack and
updates `last_visited`.

```c
static bool postorder(const Node *root)
{
    NodeStack stack = {0};
    const Node *current = root;
    const Node *last_visited = NULL;

    while (current != NULL || stack.size > 0U) {
        if (current != NULL) {
            if (!push(&stack, current)) return false;
            current = current->left;
        } else {
            const Node *node = peek(&stack);

            if (node->right != NULL && last_visited != node->right) {
                current = node->right;
            } else {
                printf("%c ", node->data);
                last_visited = pop(&stack);
            }
        }
    }
    return true;
}
```

### How do we run the same tree through all three loops?

The following local nodes stay alive throughout `main`. Traversal changes
only its local stack and pointers. A stack-capacity failure stops the program
with a nonzero exit status.

```c
int main(void)
{
    Node three = {'3', NULL, NULL};
    Node five = {'5', NULL, NULL};
    Node two = {'2', NULL, NULL};
    Node times = {'*', &five, &two};
    Node plus = {'+', &three, &times};

    printf("preorder: ");
    if (!preorder(&plus)) return 1;
    printf("\ninorder: ");
    if (!inorder(&plus)) return 1;
    printf("\npostorder: ");
    if (!postorder(&plus)) return 1;
    putchar('\n');
    return 0;
}
```

From `module_05_tree_dfs/code`, compile and run the standalone program:

```sh
cc -std=c11 -Wall -Wextra -Wpedantic -Wconversion -Wshadow \
    -Iinclude lecture/iterative_traversals.c -o /tmp/tree_dfs_lecture
/tmp/tree_dfs_lecture
```

The output is:

```text
preorder: + 3 * 5 2
inorder: 3 + 5 * 2
postorder: 3 5 2 * +
```

Each printed line also has a trailing space after the last symbol. The three
orders agree with the hand traces.

The separate existing lab package uses `tree_copy_preorder`,
`tree_print_inorder`, and `tree_evaluate_postorder` for expression-tree
applications. Its current reference implements those operations recursively
and accepts digit leaves with `+` and `*`. The standalone program above is
the implementation for this textbook's stack-based traversal lesson.
