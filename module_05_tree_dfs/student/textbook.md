# Chapter 5. Depth-First Traversal and Expression Trees

We will process a binary tree's data in three orders, replace recursive calls with an explicit stack, reconstruct a tree from traversal orders, and build an expression tree from postfix notation.

## Thinking Logically

### How do we follow the connections in a tree?

Exploring a whole tree can be broken into exploring smaller subtrees. Consider a tree whose root has two children, each of which also has two children.

```text
        A
       / \
      B   C
     / \ / \
    D  E F  G
```

To explore A's subtree, explore B's subtree and C's subtree. Apply the same idea at B: explore D's subtree and E's subtree. Applying the same exploration rule to smaller subtrees is recursion.

Use this rule wherever a subtree starts:

1. If the subtree is empty, finish exploring it and return.
2. Apply the same rule to the left subtree.
3. When the left exploration finishes, apply the same rule to the right subtree, then return.

An empty subtree contains no node to explore, so we return immediately. This is the base case that stops recursion.

Each step is responsible for its own subtree. The parent waits for the child's exploration to finish, then continues its remaining work. Finishing smaller subtrees finishes larger subtrees in turn, until exploration of the whole tree rooted at A is complete.

### How do we return after finishing a branch?

Suppose we explore the left side first. From A we descend to B, then D. D has no children, so we return to B. B still has its right side to explore, so we continue to E. After finishing E, we return to B, then A, where C is still waiting. We then explore C, going to F, returning to C, and continuing to G before returning through C to A.

At each descent, we must remember the parent and its remaining work. The most recently paused parent is the first one we return to. This is Chapter 4's last-in, first-out rule.

Following a branch as far as needed before returning to the remaining branches is depth-first search (DFS). The same reasoning applies to every subtree: explore its left side, explore its right side, and then return to its parent. An empty subtree has nothing to explore.

### What changes when we process the parent's data first, between, or last?

 Here, our example of processing data is recording the node's label. We can process the parent's data before exploring its children, between the two subtrees, or after both subtrees.

| Order | When to process the parent's data | Sequence for the A–G tree |
| --- | --- | --- |
| Preorder | Before either subtree | A B D E C F G |
| Inorder | After the left subtree, before the right | D B E A F C G |
| Postorder | After both subtrees | D E B F G C A |

Focus on the subtree rooted at B. Preorder records B, D, E; inorder records D, B, E; postorder records D, E, B. D and E are leaves, so each has only its own label to record. Applying the same rule at every node produces the complete traversal order.

Try predicting the three orders for the subtree rooted at C before checking them against the full-tree sequences. The connections stay the same; only the moment at which we process each parent's data changes.

### How can a stack remember unfinished work?

Imagine keeping a stack of cards. Each card names a node and says which part of its work comes next. Only the top card is active; the cards below it describe ancestors waiting for the current subtree to finish. The table compares all three possible times to process data. For one traversal order, process each node's data only at that order's chosen time.

| Next task on the top card | Data processing | What happens next |
| --- | --- | --- |
| Explore the left subtree | Preorder | Mark the parent ready for its middle processing step; add a card for the left child if present |
| Explore the right subtree | Inorder | Mark the parent ready for its final processing step; add a card for the right child if present |
| Finish this subtree | Postorder | Remove the parent's card |

Update the parent's reminder before descending. When the child's card is removed, the parent's card becomes active again with the correct next task already marked. If a child is absent, there is no subtree to explore, so we move directly to the next task.

| Action | Cards, bottom → top |
| --- | --- |
| Start at A | A |
| Process A's data in preorder; descend to B | A, B |
| Process B's data in preorder; descend to D | A, B, D |
| Process D's data at each order's chosen time; finish D | A, B |
| Process B's data in inorder; descend to E | A, B, E |
| Process E's data at each order's chosen time; finish E | A, B |
| Process B's data in postorder; return to A | A |
| Process A's data in inorder; descend to C | A, C |
| Process C's data in preorder; descend to F | A, C, F |
| Process F's data at each order's chosen time; finish F | A, C |
| Process C's data in inorder; descend to G | A, C, G |
| Process G's data at each order's chosen time; finish G | A, C |
| Process C's data in postorder; return to A | A |
| Process A's data in postorder; finish the tree | Empty |


A recursive description lets each subtree temporarily pause its parent's work. The cards make that same memory visible. Both follow the same branches and produce the same data processing orders.

### How can traversal orders reconstruct a tree?

Let us reconstruct the same A–G tree from its processing orders.

Its orders are preorder ABDECFG, inorder DBEAFCG, and postorder DEBFGCA. With distinct node labels, preorder and inorder together uniquely determine the binary tree:

1. The first preorder label, A, is the root.
2. Split inorder at A: DBE belongs to the left subtree and FCG to the right subtree.
3. The left subtree has three nodes, so its preorder segment is BDE; the remaining segment CFG belongs to the right subtree.
4. Repeat on BDE and DBE: root B, left child D, right child E.
5. Repeat on CFG and FCG: root C, left child F, right child G.

Subtree sizes tell us where each preorder segment ends. Preorder alone cannot distinguish a sole left child from a sole right child. Repeated labels can make the inorder split ambiguous unless we have additional information identifying the nodes.

### How can a stack build a tree from postfix notation?

Chapter 4 evaluated postfix expressions by keeping operands on a stack and replacing two operands with their calculated result. To build an expression tree, keep completed subtrees on the stack instead. An operand makes a leaf. An operator joins two subtrees under a new parent.

Keep the same A–G tree's connections, and give its nodes expression data:

| Node | Data | Role |
| --- | --- | --- |
| A | * | Multiply the results of B and C |
| B | + | Add D and E |
| C | - | Subtract G from F |
| D, E, F, G | 1, 2, 3, 4, respectively | Operand leaves |

The tree now represents `(1+2)*(3-4)`. Its postorder labels DEBFGCA become the postfix expression 12+34-*. Read that expression from left to right:

| Token | Action | Completed subexpressions, bottom → top |
| --- | --- | --- |
| 1 | Make leaf D | 1 |
| 2 | Make leaf E | 1, 2 |
| + | Take E as the right child and D as the left; join them under B | (1+2) |
| 3 | Make leaf F | (1+2), 3 |
| 4 | Make leaf G | (1+2), 3, 4 |
| - | Take G as the right child and F as the left; join them under C | (1+2), (3-4) |
| * | Take C as the right subtree and B as the left; join them under A | ((1+2)*(3-4)) |

The parenthesized expressions in the table describe the waiting trees. We are recording their structure, not calculating their values. At the end, exactly one complete tree remains: the same shape as our A–G tree.

The right subtree comes off the stack first because it was placed there later. For C, taking G first and F second preserves 3-4. Reversing those children would produce 4-3.

Postfix corresponds to postorder: each operator follows both of its subtrees. Knowing which tokens are operands and which are binary operators supplies enough structure to build the tree from this single order. Each operator needs two waiting subtrees; a complete expression must leave exactly one tree.

### Is inorder alone enough to express a tree's meaning?

Reading an expression tree in inorder places each operator between its operands. Our A–G tree's inorder labels are DBEAFCG. With the expression data above, that gives 1+2*3-4.

But the root A requires us to multiply the complete result of B by the complete result of C. We must first add 1 and 2, and subtract 4 from 3. Ordinary arithmetic precedence would instead multiply 2 and 3 first. To communicate the tree's meaning, we need `(1+2)*(3-4)`.

Inorder preserves the left-to-right order of data, but parentheses may be necessary to preserve the connections between them. When reading a tree as an expression, ask which operations the tree requires us to finish first.

### How do parentheses preserve grouping?

Parentheses tell the reader to finish a subtree before applying its parent operator. Whether they are needed depends on the operators' precedence and on which side the subtree occupies.

Multiplication, division, and remainder have higher precedence than addition and subtraction. An operand leaf needs no parentheses. For an operator child, use these rules:

| Child position | Put parentheses around the child subtree when… | Application to our tree |
| --- | --- | --- |
| Left | The child's operator has lower precedence than the parent's | B's addition needs (1+2) before A's multiplication |
| Right | The child's operator has lower or equal precedence to the parent's | C's subtraction needs (3-4) before A's multiplication |

Both children of A have lower precedence than A, so both subtrees need parentheses. Reading the left subtree, then A, then the right subtree gives (1+2)*(3-4).

Why does the right-side rule also include equal precedence? These operators group from left to right. A left child with equal precedence is already grouped first by the usual reading rules. A right child with equal precedence may need parentheses to keep its entire operation together before the parent uses its result. This matters especially for subtraction and division.

Our aim is to preserve the grouping represented by the tree, even when an arithmetic identity could simplify the expression. Place an opening parenthesis before reading a child subtree that needs one, and a closing parenthesis after finishing it.

## Calculating Efficiency

### How much work do construction and traversal require?

Let `n` be the number of postfix tokens and `r` the number of nodes
reachable from the supplied root.

| Operation | Work | Time |
| --- | --- | --- |
| `alphabet_init()` | Initialize each node slot | `O(capacity)` |
| `tree_connect()` | Make the fixed example's six links | `O(1)` |
| `build_tree_from_postfix()` | Create and push each token; pop twice per operator | `O(n)` |
| `tree_traversal(root)` | Three visits per reachable node, plus empty-child calls | `O(r)` |
| `tree_traversal_with_stack(root)` | Three steps per reachable node, plus empty-child pops | `O(r)` |
| `write_infix(root)` | Write each reachable token and a terminator | `O(r)` |

The proposed parentheses extension adds constant work per child link and
keeps the writer linear. Reconstruction by repeatedly scanning an inorder
segment for its root can take `O(r²)` in a skewed tree. A precomputed map
from distinct labels to inorder positions permits `O(r)` reconstruction.

### How much temporary storage is needed?

For height `h` measured in edges, the recursive traversal can keep `h + 1`
real-node calls active, plus one empty-child call. The recursive writer
only calls on real expression nodes. Both use `O(h + 1)` call-stack space.
The iterative traversal stores the current path plus at most one `-1`
sentinel, also `O(h + 1)` used stack entries. Its separate progress array
reserves one integer per node slot; a generalized version uses `O(r)`
progress storage in addition to its path stack.

Postfix construction can require `O(n)` stack entries. For `123*+`, the
maximum used depth is three, after the three digits. The classroom arrays
reserve ten node slots, ten stack entries, ten progress entries, and ten
output characters regardless of how many are used.

### Which capacities must be checked when extending the lab?

The included `postfix[8]` holds at most seven tokens plus a terminator.
The current writer emits one character per node, so that valid input fits
`nodes[10]` and produces at most eight output characters including `'\0'`.
The code relies on these limits rather than checking them.

Adding parentheses changes the output bound. For example, `1234+++` has
seven tokens but needs `1+(2+(3+4))`, twelve characters including `'\0'`.
That exceeds `infix[10]`. Enlarge the buffer or check remaining capacity
when implementing the extension.

The explicit traversal needs space for an absent-child sentinel as well
as the real path. A manually constructed chain of ten nodes would need
eleven stack entries, exceeding `stack[10]`. The supplied seven-node
alphabet tree fits. For general trees, increase capacity or skip pushing
negative children while still advancing the parent's progress.

## Glossary

| Term | Meaning in this chapter |
| --- | --- |
| Node index | An integer selecting an entry in `nodes`. |
| Root | The starting node index for a tree or subtree. |
| Leaf | A node whose two child indices are `-1`. |
| Visit | The selected action performed at a node. |
| Depth-first search | Finishing a branch before returning to remaining branches. |
| Preorder | Current node, left subtree, right subtree. |
| Inorder | Left subtree, current node, right subtree. |
| Postorder | Left subtree, right subtree, current node. |
| Call stack | Runtime storage for unfinished function calls. |
| Progress | The next traversal step to execute when a node becomes top again. |
| Sentinel | A special value, here `-1`, representing an absent child. |
| Postfix | Notation placing an operator after its operands. |
| Infix | Notation placing an operator between its operands. |
| Precedence | Priority between different operator levels. |
| Left associativity | Grouping equal-precedence operators from left to right. |
| Null terminator | The character `'\0'` marking the end of a C string. |

## Invariant

An **invariant** describes what stays true while an algorithm makes
progress. It helps us explain why the next step is valid and why finishing
produces the intended result. A **precondition** describes what must be
true before an operation starts. For example, starting with zeroed progress
is a precondition; keeping the stack consistent with that progress is an
invariant during traversal.

| Operation | What remains true during execution |
| --- | --- |
| Tree representation | Present child links select valid initialized nodes, absent links are `-1`, and links form a tree without cycles or shared children. |
| Recursive DFS | Each real-node call processes its own subtree; after a child call returns, that child's subtree is finished. |
| Stack DFS | Nonnegative stack entries are unfinished nodes on the current path, with progress recording where each will resume. A negative top represents an empty subtree and is removed immediately. |
| Postfix construction | After each token, every stack entry is the root of a complete expression subtree built from the processed prefix. |
| Infix writing | During the helper, the characters before `infix_pos` form the written prefix, and `infix_pos` is the next free position shared by child calls. |

### What must remain true about the tree?

A present child is a valid initialized index in `nodes`; an absent child
is `-1`. A tree has no cycles, and every non-root node has one parent.
`tree_traversal()` accepts a negative index as an empty subtree but does
not reject out-of-range positive indices or detect cycles. The stack
traversal similarly removes negative entries without visiting them.

The writer requires a nonempty expression tree: digit leaves and supported
binary operators with two valid children. It has no empty-tree guard.
The alphabet tree is suitable for traversal, not for infix writing.
Building an expression resets `nodes_size` and overwrites the shared node
array, replacing the earlier tree.

### What does each recursive call promise?

For a real node `i`, `tree_traversal(i)` processes exactly the subtree
rooted at `i`. The caller keeps its own node and its paused execution
position while a child call runs. When the left call returns, the entire
left subtree is finished, so the caller can perform its inorder visit.
When the right call returns, both subtrees are finished, so it can perform
its postorder visit. A call on a negative index finishes immediately
without accessing a node.

This promise applies recursively to every child call. The base case
handles empty subtrees, and the three visit positions preserve the chosen
orders as each larger subtree finishes.

### What does the traversal stack represent?

The nonnegative entries are unfinished nodes on the current root-to-node
path. For each such node, `progress[i]` records the next step: before
starting, 0; after scheduling the left child, 1; after scheduling the right
child, 2. Its postorder step advances progress to 3 and removes the node.
A negative top entry represents an empty subtree and is immediately popped.

Progress advances **before** a child is pushed. While the child is top,
the parent waits below it with the correct next step already recorded.
When the child is removed, reading the top again finds the parent ready
to resume. Advancing only after the child finished would require another
way to remember that the child had already been scheduled.

The tree must not share children between parents: this progress array
stores one state per node, not one state per occurrence. Keep pushes
within stack capacity. Starting with all progress entries zero is a
precondition. The invariant does not imply that the wrapper resets them;
the current wrapper leaves completed nodes at progress 3.

### What does the postfix stack represent?

After each processed token, each stack entry roots a complete subexpression
from the processed prefix. A digit adds a leaf; an operator replaces the
two most recent roots with their new parent.

Supply a well-formed, nonempty postfix expression with single-digit operands
and binary `+`, `-`, `*`, `/`, or `%`. Every operator needs two available
roots, and exactly one root must remain at the end. Spaces, unary operators,
and multidigit operands are unsupported. The builder treats every nondigit
as an operator and does not validate these conditions.

### What does the output position represent?

During `_write_infix()`, `infix[0]` through `infix[infix_pos - 1]` contain
the written prefix, and `infix_pos` selects the next free position. The
wrapper appends the terminator, so after writing `1+2*3`, `infix_pos` is 6.
The current wrapper assumes the position was zero before its one run.
That fresh position is a precondition, not a property the wrapper restores.
Child calls preserve the prefix by writing at the shared next position;
resetting the position inside them would overwrite earlier characters.

## Coding Plan

1. Reuse Chapter 2's node representation and Chapter 4's stack operations.
2. Place a negative-index base case before accessing the recursive node.
3. Put preorder, inorder, and postorder visits around the two child calls.
4. Replace recursive suspension with a stack and three progress steps.
   Trace empty-child entries as well as real nodes.
5. Reconstruct the slides' `A`-rooted tree from preorder and inorder by
   splitting at each root and counting subtree nodes.
6. Prepare `postfix`; create a node per token and pop right before left.
7. Write a parenthesis-free expression in inorder and terminate the string.
8. Extend the writer using the slides' precedence rules, excluding digits
   from parenthesis decisions and providing enough output space.
9. To support repeated runs, reset progress and the output position at the
   start of their respective wrappers.

## C Code

### Which C syntax helps us express saved work?

Several forms below appeared in earlier chapters. Here we combine them
to make traversal state explicit: recursion remembers unfinished work in
call frames, while the stack version stores node indices and progress.

| Syntax from the lab | Meaning in this chapter |
| --- | --- |
| `if (i < 0) { return; }` | A guard clause finishes an empty-subtree call before accessing `nodes[i]`. |
| `tree_traversal(nodes[i].left);` | A recursive call processes the subtree selected by the stored left-child index. |
| `int progress[10] = {0};` | Initializes all ten entries to zero. As a global array, it retains changes between calls; initialization does not happen again on each traversal. |
| `int step = progress[i]++;` | Copies the old progress into `step`, then increments the stored progress. The old value chooses the current action; the new value records where the node will resume. |
| `switch (step)` and `case` | Select one traversal action using the saved step. |
| `return;` inside a `case` | Exits the helper after one action. A `break` would exit only the `switch`; execution could continue after it. |
| `while (!is_empty())` | Repeats while unfinished stack entries remain. `!` turns a true empty result into false, and a false result into true. |
| `infix[infix_pos++] = c;` | Writes `c` at the current position, then advances the next-write position. |
| `'\0'` | The null character marking a C string's end, distinct from the visible digit character `'0'`. |

For example, if `progress[i]` is 0, `int step = progress[i]++;` leaves
`step == 0` and `progress[i] == 1`. Case 0 therefore runs now, and case 1
is ready when the parent resumes. If `infix_pos` is 2, the output assignment
writes to `infix[2]` and leaves `infix_pos == 3`.

The `return;` form belongs to a function returning `void`, where no result
value is returned. In contrast, the builder's `return pop();` returns the
root index to its caller.

### How do the compilation directives reuse earlier definitions?

The lab includes Chapter 2's tree and Chapter 4's stack using paths relative
to this file:

```c
#include "../../module_02_binary_tree/student/lab.c"
/* Both earlier labs use capacity; keep the stack's definition distinct. */
#define capacity stack_capacity
#include "../../module_04_stack/student/lab.c"
#undef capacity

int is_digit(char c) {
    return c >= '0' && c <= '9';
}
```

The first file supplies `nodes`, `nodes_size`, `alphabet_init()`, and
`tree_connect()`. The second supplies `stack`, `top`, `push()`, `peek()`,
`pop()`, `is_empty()`, `prec()`, and `postfix`. Both earlier files define
`capacity`; the temporary macro renames the stack's definition and its uses
to `stack_capacity`, avoiding a duplicate definition. The lab supplies
`is_digit()` for the writer. This direct `.c` inclusion is a classroom
shortcut; reusable projects should separate declarations into headers.

These directives run during preprocessing, before the C program executes.
`#include` inserts another file's source. `#define capacity stack_capacity`
temporarily replaces that identifier in the included stack source, and
`#undef capacity` ends the replacement for later source text. This name
adjustment supports compilation; traversal progress is handled by the
runtime statements above.

### Where are the three recursive visit positions?

This is the current lab implementation:

```c
int pre_data, in_data, post_data;

void tree_traversal(int i) {
    if (i < 0) {
        return;
    }
    pre_data = nodes[i].data;
    tree_traversal(nodes[i].left);
    in_data = nodes[i].data;
    tree_traversal(nodes[i].right);
    post_data = nodes[i].data;
}
```

The globals are `int` values holding character codes. Displaying them with
`%c` produces their corresponding symbols.

### How does the explicit stack resume a node?

```c
int progress[10] = {0};

void tree_traversal_proceed() {
    int i = peek();
    if (i < 0) {
        pop();
        return;
    }

    int step = progress[i]++;
    switch (step) {
        case 0:
            pre_data = nodes[i].data;
            push(nodes[i].left);
            return;
        case 1:
            in_data = nodes[i].data;
            push(nodes[i].right);
            return;
        case 2:
            post_data = nodes[i].data;
            pop();
            return;
    }
}

/* only single run */
void tree_traversal_with_stack(int root_index) {
    top = -1;
    push(root_index);
    while (!is_empty()) {
        tree_traversal_proceed();
    }
}
```

Call `tree_traversal_proceed()` only with a nonempty stack. For reuse, reset
`progress` before starting another traversal; the current wrapper does not.

### How does postfix construction connect the children?

```c
int build_tree_from_postfix() {
    top = -1;
    nodes_size = 0;
    for (int i = 0; postfix[i] != '\0'; i++) {
        char c = postfix[i];
        nodes[i].data = c;
        if (c >= '0' && c <= '9') {
            nodes[i].left = -1;
            nodes[i].right = -1;
        } else {
            nodes[i].right = pop();
            nodes[i].left = pop();
        }
        push(i);
        ++nodes_size;
    }
    return pop();
}
```

The builder resets the same shared stack used by expression conversion,
evaluation, and iterative traversal. These operations run sequentially;
none may rely on retaining earlier stack contents.

### How does the current writer emit an expression?

```c
char infix[10] = "";
int infix_pos = 0;

/* assume original equation did not have parenthesis*/
void _write_infix(int i) {
    char c = nodes[i].data;
    if (is_digit(c)) {
        infix[infix_pos++] = c;
        return;
    }
    _write_infix(nodes[i].left);
    infix[infix_pos++] = c;
    _write_infix(nodes[i].right);
}

/* only single run */
void write_infix(int root) {
    _write_infix(root);
    infix[infix_pos++] = '\0';
}
```

The supplied helper `int is_digit(char c)` returns
`c >= '0' && c <= '9'`. The quoted writer contains no precedence checks
or parenthesis output. When adding those checks, remember that the included
`prec()` returns 0 for digits; explicitly exclude digit children.

### How can we demonstrate the current lab?

`lab.c` has no `main`. The supplied
[`code/lecture/lab_demo.c`](../code/lecture/lab_demo.c) runs both traversals,
converts Chapter 4's default expression to postfix, builds its tree, and
writes the infix string once. From `module_05_tree_dfs/code`, run:

```sh
make lecture
```

To try the driver beside the lab, save this as `demo.c` in the `student`
directory. Compile only the driver, since it includes the lab already:

```c
#include <stdio.h>

/* Compile only this source; it includes the classroom lab. */
#include "lab.c"

int main(void) {
    alphabet_init();
    int root = tree_connect();
    tree_traversal(root);
    printf("Recursive last visits: %c %c %c\n",
           pre_data, in_data, post_data);

    tree_traversal_with_stack(root);
    printf("Stack last visits: %c %c %c\n",
           pre_data, in_data, post_data);

    convert_to_postfix();
    root = build_tree_from_postfix();
    write_infix(root);
    printf("%s -> %s\n", postfix, infix);
    printf("Root: %d; nodes: %d; top: %d\n", root, nodes_size, top);
    return 0;
}
```

From `module_05_tree_dfs/student`, compile and run:

```sh
cc -std=c11 -Wall -Wextra demo.c -o /tmp/tree_dfs_lab
/tmp/tree_dfs_lab
```

The expected output is:

```text
Recursive last visits: G G F
Stack last visits: G G F
123*-4+ -> 1-2*3+4
Root: 6; nodes: 7; top: -1
```

The visit lines report final globals, not complete traversal sequences.
The example performs one stack traversal and one infix write, respecting
the lab's single-run assumptions. To try `123*+` instead, replace
`convert_to_postfix();` with `strcpy(postfix, "123*+");` and add
`#include <string.h>`; it fits the existing buffer and yields `1+2*3`.
