# Instructor Technical Notes — Module 2

## Scope and exact public contract

The header is `code/include/binary_tree.h`. The implementations are
`code/starter/binary_tree.c` and `code/solution/binary_tree.c`.

```c
struct TreeNode {
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
};

struct TreeNode *tree_find(struct TreeNode *node, int target);
void tree_clear(struct TreeNode *node);
```

These are the only two required library functions. Use the explicit
`struct TreeNode` spelling. Do not add a type alias, status enum, wrapper
object, constructor, side-operation helper, or whole-tree validator.

The representation has two downward pointers and no stored upward link.
Left and right are independent named positions. A right-only node is valid.
No numerical ordering is implied by a node's position.

The canonical fixture is the expression `(3 + 5) * 2`: `root` stores `'*'`,
its left child `plus` stores `'+'` with children `three` and `five`, and its
right child `two` stores `2`. Its current-left-right sequence is
`'*', '+', 3, 5, 2`. Character constants have type `int`, so operators and
numbers use the same field without relying on ASCII numbers. This expression
uses two children for each binary operator, but the representation and API
remain generic binary-tree tools and accept valid one-child fixtures.

## Caller preconditions

For each nonempty tree or subtree passed to a function:

1. every reachable address refers to an initialized, live node object;
2. the reachable structure is finite and acyclic;
3. each reachable non-root node has exactly one incoming tree link;
4. no node is shared by two child positions; and
5. local variables remain in scope throughout all uses of their addresses.

`NULL` is a valid empty-tree input to both functions. Arbitrary invalid or
expired addresses are not validated. A successful search is not proof that
the whole structure met its preconditions.

Before direct attachment, the caller additionally establishes that the child
is fresh or otherwise unlinked and that the proposed attachment preserves
the whole-tree rules. Checking only an empty side cannot discover an incoming
link elsewhere or a longer cycle.

Do not run ordinary recursive operations on intentionally cyclic examples.
Use paper traces to explain why a missing base-case path would fail to stop.

## Local objects and initialization

The textbook initializes already existing variables:

```c
struct TreeNode root;
struct TreeNode plus;

root.data = '*';
root.left = NULL;
root.right = NULL;

plus.data = '+';
plus.left = NULL;
plus.right = NULL;
```

`root` is the object; `&root` is its address. A pointer such as
`struct TreeNode *p = &root;` allows `p->data` to select the same field as
`root.data`.

Initialize both child links before searching or clearing. Reinitializing a
node that still has children would discard its links without recursively
resetting those descendants; that is not the required branch-clearance
operation.

The variable's storage duration, not a tree operation, controls its lifetime.
Do not return the address of an automatic local node from a function whose
scope then ends.

## Guarded selected-side attachment

For an initialized, unlinked child whose lifetime is sufficient:

```c
if (root.left == NULL) {
    root.left = &plus;
}
```

This example changes only the selected left field when it is empty. An
occupied left field remains unchanged; the example does not silently
replace it or fall back to the right side. Use the symmetric test when the
caller selects the right side.

This is a direct C pattern, not a library function or a global structural
validation algorithm. Its local work is `O(1)` under the stated construction
preconditions.

## Recursive search

`tree_find(node, target)`:

1. returns `NULL` for an empty current pointer;
2. returns the current node's address when its data equals the target;
3. searches the complete left subtree;
4. returns a nonempty left result immediately; and
5. searches and returns the right result only after the left search failed.

The order is current-left-right (preorder in formal traversal terminology).
Chapter 2 assesses the sequence, not memorization of that later label. The
result is an address, not a data value or a new object. A missing value returns
`NULL`. Duplicate values are legal, and the first preorder match wins.

Search must not mutate any node. Zero is ordinary data: a node containing
zero is a legitimate match for target zero, including a previously cleared
node that is still alive.

In the canonical expression tree, searching for `2` checks
`'*', '+', 3, 5, 2` and returns `&two`. Searching for `5` returns `&five`
without visiting `two`, while a missing target checks all five nodes. The
expression shape is semantic structure rather than numerical search ordering,
so a data comparison cannot justify skipping either subtree.

## Recursive clearance

`tree_clear(node)` is a no-op for `NULL`. For a nonempty subtree it:

1. recursively clears the left descendants;
2. recursively clears the right descendants; and
3. leaves the current node with data zero and both links `NULL`.

A link may be reset after its recursive call, as in the textbook. The
essential requirement is to retain access to every descendant until it has
been cleared. Resetting both child links before traversing them loses the
routes to those nodes.

After a valid call, every formerly reachable node has data zero and two
empty child links. Each local object still exists for the remainder of its
scope. Repeatedly clearing an already cleared node is safe and leaves the
same state.

Clearance does not discover or change an incoming link outside its argument
subtree. For example, `tree_clear(root.left)` resets the left branch but
does not by itself change `root.left`.

## Selected-side removal

The caller removes a left branch with the textbook's two actions:

```c
tree_clear(root.left);
root.left = NULL;
```

For the right branch, use `root.right` consistently. A missing selected
branch is safe because clearing `NULL` does nothing.

The opposite side is unchanged. A right-only result is valid, so removing
left never moves right into left. No count or contiguous-prefix rule exists
for these two named links.

When this operation removes the plus branch from the canonical fixture, the
remaining links are a valid generic binary tree but no longer a completed
binary expression: the `'*'` node has only its right operand.

The caller may inspect a reset local variable or initialize and link it again
while it remains alive and unlinked. That is different from following an
address after the variable's scope has ended.

## Complexity and resource limits

Let `n` be the number of nodes reachable from the starting node, `k` the
size of a selected branch, and `h` the longest downward path in links.

| Operation | Time | Additional call-stack space |
|---|---:|---:|
| initialize one existing node | `O(1)` | `O(1)` |
| inspect left/right or attach to an empty selected side | `O(1)` | `O(1)` |
| recursive search | `O(n)` worst case | `O(h + 1)` |
| clear a whole tree | `O(n)` | `O(h + 1)` |
| clear and detach a branch | `O(k)` | proportional to branch height plus one |
| detach a known side without clearance | `O(1)` | `O(1)` |

Each node has fixed representation size. The additional space is the pending
recursive calls, not extra node storage. Deep finite trees can still exhaust
the runtime call stack; use bounded classroom fixtures rather than claiming
unlimited recursion.

## Safe invariant autopsy

`code/autopsy/faulty_cascade.c` is standalone. It provides the correct
clearance routine so the exercise isolates the malformed relationship.

Its six local nodes form the intentionally malformed expression
`(3 + 5) * (5 - 2)`: both `plus.right` and `minus.left` store the address of
one `shared_five` object. That sharing violates the tree precondition even
though the relationship has no cycle. All objects remain alive, so the
observation is an invariant failure rather than an expired-address error.
Clearing and detaching the plus branch resets `shared_five`; the minus branch
still reaches that same live, cleared object. Do not change the correct
recursive algorithm to conceal the invalid fixture.

Only the instructor answer key supplies the worked prediction and repair
discussion. Student-facing Stage D diagrams teach correct operations without
this fixture's answers.

## Toolchain and validation

Preferred GCC/Clang flags:

```text
-std=c11 -Wall -Wextra -Wpedantic -Wconversion -Wshadow -g
```

Supported runtime checks:

```text
-fsanitize=address,undefined -fno-omit-frame-pointer
```

Microsoft C uses `/nologo /std:c11 /W4 /Zi`. Provide instructor CI or a
debugger/invariant-check alternative when local runtime checks are
unavailable. A sanitizer may remain silent on the autopsy because all node
addresses remain live; tool silence does not establish a tree invariant.

Before release, verify:

- both reference functions and supplied tests compile without warnings;
- null, missing, duplicate, zero-data, and recursive cases pass;
- direct examples preserve an occupied side and the unselected side;
- clearance resets all selected nodes but does not detach an outside link;
- all three student-test categories align with the 100-point rubric;
- the starter compiles with exactly two implementation TODOs;
- all release paths use `binary_tree.h` and `binary_tree.c`;
- vocabulary appears only from Stage B onward;
- Stage D contains no worked autopsy prediction; and
- Stage E excludes the solution, instructor extension tests, and answer key.
