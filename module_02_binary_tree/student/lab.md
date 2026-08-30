# Lab — Build, Search, and Clear a Binary Tree

## Purpose and scope

Use local node variables with a data field and two child links. Build the
five-node expression tree for `(3 + 5) * 2`, search it recursively, and clear
a selected subtree. Then use small generic binary-tree boundary cases to test
the same representation and functions.

All of those operations are core. Only search and clearing are packaged as
public functions. Initialization, attachment, and caller detachment remain
direct C operations.

## Two 90-minute meetings

| Meeting | Work | Minutes |
|---|---|---:|
| A — Conceptual stages | Inquiry, representation reveal, Cognitive Pause, calibration, investigation, and exit ticket | 90 |
| B — Stage E lab | Direct node operations, two recursive functions, tests, autopsy, and submission evidence | 90 |
| **Total** | | **180** |

Stage D's textbook and diagrams follow the Meeting A investigation and exit
ticket. Stage E's lab and code are released for Meeting B.

## Files

You receive:

- `code/include/binary_tree.h`
- `code/starter/binary_tree.c`
- `code/tests/test_core.c`
- `code/tests/test_student.c`
- `code/autopsy/faulty_cascade.c`
- `code/build.ps1`
- `code/Makefile`

Edit only `code/starter/binary_tree.c` and `code/tests/test_student.c`.
Do not change the header or supplied tests unless the instructor authorizes
it. The header declares the shared node type and function contracts.

## Representation and the two-function API

Each node groups one value with its two downward connections.

```c
struct TreeNode {
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
};

struct TreeNode *tree_find(struct TreeNode *node, int target);
void tree_clear(struct TreeNode *node);
```

Use the full name `struct TreeNode`. A pointer stores a node address.
`NULL` means that no node is linked at that position. `void` means that
`tree_clear` returns no value.

### Caller preconditions

A precondition is a condition the caller must ensure before an operation.

- Initialize every node's data and both links before using its address.
- Keep every linked local variable alive throughout the operation.
- Build a finite tree with no cycles or shared child objects.
- Each non-root node has exactly one incoming child link. Do not put the
  same child in both sides of a parent.
- Attach only a fresh, unlinked node or a disjoint valid subtree.
- Check that the selected side is empty before attaching.

A general binary-tree node may have zero, one, or two children. In the
completed expression fixture, each operator has two operand children and
each number has none. The API does not enforce or evaluate that extra
expression rule.

The two functions do not validate arbitrary relationships. A side being
empty does not prove that a proposed link satisfies the global tree rules.
An address does not remain usable after its local variable's block ends.

## Core checkpoints

The starter marks two `TODO(core)` regions: one in each recursive function.
Their `NULL` base cases are supplied. A base case finishes without another
recursive call.

### 1. Initialize and link ordinary node variables

Use direct field assignments, as in the textbook:

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

The dot selects a field of a variable. `&plus` is the address of `plus`.
The assignment links the existing object; it does not copy it.
The `int` data field can store C character constants such as `'*'` and `'+'`;
use those portable literals instead of numeric character codes.

For the canonical example, initialize five local nodes and construct these
relationships:

| Variable and data | Left child | Right child |
|---|---|---|
| `root`, `'*'` | `&plus` | `&two` |
| `plus`, `'+'` | `&three` | `&five` |
| `three`, `3` | none | none |
| `five`, `5` | none | none |
| `two`, `2` | none | none |

The values do not impose a sorting rule. Left and right preserve operand
positions. A right-only child is valid in a general binary tree, although it
is not a completed binary operator. A guarded assignment to an occupied side
leaves the existing link and all nodes unchanged. It does not replace or move
a child.

### 2. Complete recursive search

Complete `tree_find`.

- Check the current node's data first.
- If it does not match, search the entire left subtree.
- Return a left-side match immediately.
- Otherwise search the right subtree.
- Return the first matching node address, or `NULL` if the target is absent.
- Do not change any node.

A search from `NULL` returns `NULL`. Duplicate, zero, and negative data
values are valid. Check a returned pointer before using `->` to read one
of its fields.

Trace the canonical search for `2` before running the tests. Its complete
check order is `'*'`, `'+'`, `3`, `5`, `2`. Explain why a missing value may
require visiting every node. You do not need to memorize a traversal label.

### 3. Complete recursive clearing

Complete `tree_clear`.

- Clear the left and right subtrees.
- Set both child links to `NULL`.
- Set the current node's data to 0.

Keep a child address available until that subtree has been cleared.
`tree_clear(NULL)` does nothing. Every cleared local node remains alive
until its declaring block finishes.

Clearing is not the same as ending an object's lifetime. A cleared node is
still a node with data 0 and no children. Zero is not an empty-node marker.

### 4. Remove a child through its caller

A child has no upward field. Clearing the child cannot change the outside
parent's link. The caller performs both actions:

```c
tree_clear(root.left);
root.left = NULL;
```

In the canonical tree, this removes the branch beginning at `plus`. The right
link still identifies `two`. Its side and its subtree must remain unchanged.
The remaining right-only shape is a valid general binary tree but no longer a
completed representation of the original expression.

Inspect the cleared variables while they are still alive. Distinguish those
objects from the nodes still reachable through `root`. Do not move the
right child into the empty left position.

### 5. Design three student tests

Replace the three placeholder bodies in `code/tests/test_student.c`.
Return 1 when a test passes and 0 when it fails. Leave the supplied test
runner unchanged.

1. Search: use a new boundary, repeated-value case, or unsorted arrangement
   that checks the current-left-right search order.
2. Direct operations: initialize local nodes and test chosen-side linking,
   an occupied-side guard, or caller detachment.
3. Clearing: test a subtree and show that still-live cleared nodes can be
   inspected or reinitialized without changing the opposite branch.

Use fixtures or sequences that add evidence beyond the supplied tests.
Explain each test's claim. Keep all node variables alive through the checks.

Do not pass actual cycles, shared structures, or ended-lifetime addresses to
the recursive functions in ordinary tests. Reason about such invalid input
on paper; the isolated autopsy provides one controlled sharing example.

## Optional additional cases

After the required tests pass, the instructor may separately release extra
valid fixtures and longer traces using the same two functions and direct
operations. These are not included in the Stage E package. Use the matching
tests and build commands supplied with that optional release. No additional
algorithms or functions are required.

## Build and test

From the `code` directory in PowerShell:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target starter -StudentTests
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target autopsy
```

When supported, add `-Sanitize` to a test command. A sanitizer checks some
invalid memory accesses while a program runs. It does not prove that every
logical tree rule is satisfied. The execution-policy option applies only
to this child PowerShell process.

In Git Bash, MSYS2, WSL, Linux, or macOS:

```sh
make starter-core
make starter-student-tests
make autopsy
```

The Makefile defaults to GCC. Use `make CC=clang starter-core` for Clang.

If a local diagnostic tool is unavailable, use approved debugger or
instructor-CI evidence. CI means another computer runs the submitted tests.

## Required submission

1. Completed `code/starter/binary_tree.c` with both recursive functions.
2. A passing supplied core-test transcript.
3. Three passing student-authored tests with a rationale for each.
4. Warning-enabled and approved diagnostic evidence.
5. Completed evidence record.
6. Tree Structure Autopsy.
7. Corrected Cognitive Pause.

Completion means the two functions and direct-operation tests satisfy the
contracts, student-controlled code has no compiler warnings, and the
explanation distinguishes clearing, detaching, and node lifetime.
