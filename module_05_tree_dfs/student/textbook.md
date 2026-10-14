# Chapter 5. Depth-First Traversal and Expression Trees

We will trace a binary tree's three visit positions, replace recursive calls
with a progress-state stack, build an expression tree from postfix, and
write infix while preserving its grouping. These are the four steps in
[the lab slides](ppt_lab_material.md). Reconstruction from traversal orders
is an optional transfer exercise in [the general slides](ppt_material.md).

The classroom [`lab.c`](lab.c) reuses Chapter 2's `nodes[10]` and Chapter
4's integer stack. `alphabet_init()` and `tree_connect()` create the
`F`-rooted example: `F` has children `A, G`, `A` has `B, C`, and `B` has
`D, E`. Its reachable count is seven although `nodes_size == 10`. The
balanced `A`-rooted tree below is a separate conceptual example.

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

### What changes when we process a node's data first, between, or last?

When a node has two child subtrees, there are three possible times to process its data: before both child subtrees, between them, or after both are finished.

Suppose we always explore the left child subtree before the right child subtree. If we process the node's data first, we process its data, then the data of every node in the left child subtree, then the data of every node in the right child subtree. If we process the node's data in the middle, we process all the data in the left child subtree, then the node's data, then all the data in the right child subtree. If we process the node's data last, we process all the data in the left child subtree, then all the data in the right child subtree, then the node's data.

Therefore, processing each node's data first makes the root's data the first to be processed. Processing each node's data in the middle makes the leftmost node reached from the root the first to be processed. Processing each node's data last makes the root's data the last to be processed.

| Order | When to process the node's data | Processing sequence for the A–G tree |
| --- | --- | --- |
| Preorder | Before both child subtrees | A B D E C F G |
| Inorder | After the left child subtree, before the right | D B E A F C G |
| Postorder | After both child subtrees are finished | D E B F G C A |

### How can a stack store the state of work?

Imagine storing a work record for each node on a stack. Each record contains one node and its next task. The tasks process data at the times described above. After preorder processing, add the left child node to the stack. After inorder processing, add the right child node to the stack. After postorder processing, remove the current node from the stack.

To carry out a task, first read the current task from the record at the top of the stack. Update the record to the next step, then carry out the current task. The records below describe the work of ancestors waiting for the current subtree to finish.

The parent's work pauses while its child subtree is processed, so this works in the same way as the recursive approach.

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

### Optional transfer: how can traversal orders reconstruct a tree?

Let us reconstruct the same A–G tree from its processing orders.

Its orders are preorder ABDECFG, inorder DBEAFCG, and postorder DEBFGCA. With distinct node labels, preorder and inorder together uniquely determine the binary tree:

1. The first preorder label, A, is the root.
2. Split inorder at A: DBE belongs to the left subtree and FCG to the right subtree.
3. The left subtree has three nodes, so its preorder segment is BDE; the remaining segment CFG belongs to the right subtree.
4. Repeat on BDE and DBE: root B, left child D, right child E.
5. Repeat on CFG and FCG: root C, left child F, right child G.

Subtree sizes tell us where each preorder segment ends. Preorder alone cannot distinguish a sole left child from a sole right child. Repeated labels can make the inorder split ambiguous unless we have additional information identifying the nodes.

## Calculating Efficiency

### How much work do construction and traversal require?

Let `n` be the number of postfix tokens and `r` the number of nodes
reachable from the supplied root.

| Operation | Work | Time |
| --- | --- | --- |
| `alphabet_init()` | Initialize each node slot | `O(capacity)` |
| `tree_connect()` | Make the fixed example's six links | `O(1)` |
| `build_tree_from_postfix()` | Create and push each token; pop twice per operator | `O(n)` |
| `tree_traversal(root)` | Three visit positions per reachable node, plus empty-child calls | `O(r)` |
| `tree_traversal_with_stack(root)` | Three steps per reachable node, plus empty-child pops | `O(r)` |
| `write_infix(root)` | Write each reachable token, grouping parentheses, and a terminator | `O(r)` |

The implemented parentheses comparisons add constant work per child link;
the writer remains linear. Optional reconstruction by scanning an inorder
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
reserve ten node slots, ten stack entries, ten progress entries, and twenty
output characters regardless of how many are used.

### Which capacities must be checked when extending the lab?

The included `postfix[8]` holds at most seven tokens plus a terminator.
That valid input fits `nodes[10]`. The current writer adds grouping
parentheses, so output can be longer than input. For example, `1234+++`
has seven tokens but writes `1+(2+(3+4))`, twelve characters including
`'\0'`. It fits the current `infix[20]`.

For a full binary expression tree of `n` tokens, there are `(n - 1) / 2`
operator nodes. At most every non-root operator child can receive a pair of
parentheses, so for `n >= 3` the token, parenthesis, and terminator count
is at most `2n - 2`. Thus seven tokens need at most twelve cells. A digit
alone needs two. The current bounds suffice for these valid inputs, but
the code contains no capacity checks; revisit all limits when generalizing.

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

For a real root, the writer requires an expression tree: digit leaves and
supported binary operators with two valid children. `_write_infix()` returns
for a negative root, so `write_infix(-1)` creates an empty string. This guard
does not validate an operator's children: their data is read before recursive
calls. The alphabet tree is suitable for traversal, not for infix writing.
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
The wrapper establishes `infix_pos == 0` at the start of each complete
write, so repeated writes replace the string from its first cell.
Child calls preserve the prefix by writing at the shared next position;
resetting the position inside them would overwrite earlier characters.

## Coding Plan

1. Reuse Chapter 2's node representation and Chapter 4's stack operations.
2. Place a negative-index base case before accessing the recursive node.
3. Locate preorder, inorder, and postorder visit hooks around child calls.
   Add recording actions only when assigned; comments alone record nothing.
4. Replace recursive suspension with node indices and three progress steps.
   Trace empty-child entries as well as real nodes; reset progress before reuse.
5. Prepare valid `postfix`; create a node per token and pop right before left.
6. Give digits precedence 3 using `prec2()` and compare child and parent
   precedence to preserve grouping around recursive child writes.
7. Reset the output position at the start of `write_infix()`, share it in
   child calls, and append a terminator after the complete expression.
8. Optional: reconstruct the general slides' `A`-rooted tree from distinct
   preorder/inorder labels by splitting at each root and counting subtree nodes.

## C Code

### Which C syntax helps us express saved work?

Recursion remembers unfinished work in call frames. The stack version makes
node indices and progress explicit. The same source uses these forms:

| Syntax from the lab | Meaning in this chapter |
| --- | --- |
| `if (i < 0) { return; }` | Finish an empty-subtree call before accessing `nodes[i]`. |
| `tree_traversal(nodes[i].left);` | Process the subtree selected by the left-child index. |
| `int progress[10] = {0};` | Initialize every entry once; global changes remain between calls. |
| `int step = progress[i]++;` | Save old progress for this action, then advance the stored next step. |
| `switch (step)` and `case` | Select one traversal action using the old step. |
| `return;` inside a `case` | Finish the helper after one action; `break` would leave only the switch. |
| `tree_traversal_proceed(peek())` | Pass the current top node index to the one-step helper. |
| `while (!is_empty())` | Continue while unfinished stack entries remain. |
| `write_char(c)` | Write `infix[infix_pos++] = c`, advancing the shared output position. |
| `prec2(r) <= prec2(c)` | Group a right child of lower or equal precedence. |
| `'\0'` | Mark a C string's end, distinct from the visible digit `'0'`. |

For example, old progress 0 produces `step == 0` and `progress[i] == 1`.
The preorder step runs now; inorder is ready after the left subtree finishes.
The builder's `return pop();` returns a root index; the traversal helper's
`return;` returns without a result.

### How do the compilation directives reuse earlier definitions?

The classroom source includes the two earlier labs:

```c
#include "module_02_binary_tree/student/lab.c"
#define capacity stack_capacity
#include "module_04_stack/student/lab.c"
#undef capacity
```

The build supplies the repository root as an include-search directory.
Chapter 2 supplies nodes and their initialization/connect functions; Chapter
4 supplies the integer stack, `postfix`, conversion, and `prec()`. Both
sources define `capacity`, so the temporary macro gives the stack's variable
the distinct name `stack_capacity`. `#undef` ends the substitution. This
name adjustment occurs during preprocessing; it does not reset runtime state.
Direct inclusion of `.c` files is a classroom shortcut. Compile the driver
once, rather than linking additional copies of the included sources.

### Where are the three recursive visit positions?

These are the source's hooks, without an added recording action:

```c
void tree_traversal(int i) {
	if (i < 0) {
		return;
	}
	/* preorder */
	tree_traversal(nodes[i].left);
	/* inorder */
	tree_traversal(nodes[i].right);
	/* postorder */
}
```

To observe an order, record `nodes[i].data` at its matching comment. A trace
must append each symbol; one overwritten value keeps only the last symbol.
The original source does not declare visit globals.

### How does the explicit stack resume a node?

```c
int progress[10] = {0};

void tree_traversal_proceed(int i) {
	if (i < 0) {
		pop();
		return;
	}
	int step = progress[i]++;
	switch (step) {
	case 0: /* preorder */
		push(nodes[i].left);
		return;
	case 1: /* inorder */
		push(nodes[i].right);
		return;
	case 2: /* postorder */
		pop();
		return;
	}
}

void tree_traversal_with_stack(int root_index) {
	top = -1;
	push(root_index);
	while (!is_empty()) {
		tree_traversal_proceed(peek());
	}
}
```

Call the helper with the current top and a nonempty stack. It removes a
negative entry before reading progress. Reset `progress` to zero before
another traversal; the wrapper itself resets only `top`. Replacing nodes
with a newly built tree does not clear old progress for those slots.

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

Prepare nonempty valid postfix before this call. Conversion, evaluation,
construction, and iterative traversal reuse one stack sequentially. None
may rely on earlier stack contents surviving another operation's reset.
Construction records digit characters and child links, rather than values.

### How does the writer preserve grouping and restart its cursor?

```c
char infix[20] = "";
int infix_pos = 0;

int prec2(char c) {
	if (c >= '0' && c <= '9') {
		return 3;
	} else {
		return prec(c);
	}
}

void write_char(char c) { infix[infix_pos++] = c; }

void _write_infix(int i) {
	if (i < 0) {
		return;
	}
	char c = nodes[i].data;
	if (c >= '0' && c <= '9') {
		write_char(c);
		return;
	}
	char l = nodes[nodes[i].left].data;
	char r = nodes[nodes[i].right].data;

	/* preorder */
	if (prec2(l) < prec2(c)) {
		write_char('(');
	}
	_write_infix(nodes[i].left);

	/* inorder */
	if (prec2(l) < prec2(c)) {
		write_char(')');
	}
	write_char(c);

	if (prec2(r) <= prec2(c)) {
		write_char('(');
	}
	_write_infix(nodes[i].right);

	/* postorder */
	if (prec2(r) <= prec2(c)) {
		write_char(')');
	}
}

void write_infix(int root) {
	infix_pos = 0;
	_write_infix(root);
	write_char('\0');
}
```

`prec()` gives digits 0, while `prec2()` gives them 3. This makes the same
comparisons usable for both leaves and operator children without wrapping
digits. The left comparison is strict; the right comparison includes equal
precedence to preserve the tree under left associativity. Parentheses open
before a recursive child write and close afterward. `write_infix()` resets
the cursor only at the start of the complete write and explicitly terminates
its output. These behaviors are already implemented.

### How can we demonstrate the current lab?

`lab.c` has no `main`. The supplied
[`code/lecture/lab_demo.c`](../code/lecture/lab_demo.c) runs both traversals,
converts Chapter 4's expression, builds its tree, and performs several complete
writes. From `module_05_tree_dfs/code`, run:

```sh
make lecture
make lab-tests
```

PowerShell uses `./build.ps1 -Target lecture` and
`./build.ps1 -Target lab-tests`. Follow `code/README.md` for compiler and
include-path setup; record the complete commands and actual diagnostics.

Expected lecture output:

```text
Recursive traversal complete (visit comments).
Stack progress (A-G): 3 3 3 3 3 3 3
123*-4+ -> 1-2*3+4
Root: 6; nodes: 7; top: -1
1234+++ -> 1+(2+(3+4))
12+3* -> (1+2)*3
831-/ -> 8/(3-1)
```

The source's visit comments do not emit symbol traces. The progress line
shows completed states of reached nodes after one iterative run. The later
outputs demonstrate parentheses and repeated complete writes in one process.
The supplied lab tests exercise the same source directly; the separate
pointer-based copy/print/evaluation scaffold is optional and has a different
interface and failure contract.
