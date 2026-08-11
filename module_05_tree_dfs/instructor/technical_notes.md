# Technical Notes - Module 5 Tree DFS

## Scope

This module implements depth-first traversal for a valid, heap-owned binary
tree. It revisits Module 2's node links and strict-BST ordering, then reuses
Module 4's Stack contract with a new item type: `const TreeNode *`.

The teaching fixture is synthetic:

```text
                 50
               /    \
             30      70*
            /  \
          20   40*
```

Key `30` is also flagged. Parent/child text equivalent: root `50`; left child
`30` with children `20` and `40`; right child `70`; flags are true at `30`,
`40`, and `70`.

This module does not traverse a real filesystem or authorization policy.
It assumes a valid tree whose child links are acyclic and do not share a
node. Structural validation, graph visited tracking, general parsing,
concurrent mutation, and adversarial pointer provenance are outside the lab.

## Canonical public model

The public header is `code/include/tree_dfs.h`:

```c
#define TREE_DFS_MAX_NODES 64U

typedef struct TreeNode {
    int key;
    bool flagged;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

typedef struct {
    int key;
    bool flagged;
} TreeVisit;

typedef struct {
    TreeVisit items[TREE_DFS_MAX_NODES];
    size_t count;
} TreeOrder;

typedef enum {
    TREE_DFS_OK = 0,
    TREE_DFS_INVALID_ARGUMENT,
    TREE_DFS_LIMIT,
    TREE_DFS_ALLOCATION,
    TREE_DFS_DUPLICATE,
    TREE_DFS_NOT_FOUND
} TreeDfsStatus;
```

`TreeVisit` copies observable teaching data; it does not retain a pointer
whose lifetime could end later. `TreeOrder.count` is the number of initialized
records in `items` and must be from zero through 64.

The status order, spelling, and full `TREE_DFS_` prefix are public contract.

The exact public declarations are:

```c
TreeDfsStatus tree_node_create(
    int key,
    bool flagged,
    TreeNode **out_node
);

void tree_node_release(TreeNode *node);

TreeDfsStatus tree_bst_insert(
    TreeNode **root,
    int key,
    bool flagged
);

TreeDfsStatus tree_preorder_recursive(
    const TreeNode *root,
    TreeOrder *out_order
);

TreeDfsStatus tree_inorder_recursive(
    const TreeNode *root,
    TreeOrder *out_order
);

TreeDfsStatus tree_postorder_recursive(
    const TreeNode *root,
    TreeOrder *out_order
);

TreeDfsStatus tree_preorder_iterative(
    const TreeNode *root,
    size_t stack_limit,
    TreeOrder *out_order
);

TreeDfsStatus tree_bst_search(
    const TreeNode *root,
    int target,
    const TreeNode **out_node
);

TreeDfsStatus tree_destroy_postorder(TreeNode **root);

const char *tree_dfs_status_name(TreeDfsStatus status);
```

Testing builds alone expose:

```c
void tree_dfs_test_fail_next_node_allocation(void);
size_t tree_dfs_test_live_node_count(void);
```

They are guarded by `TREE_DFS_TESTING` and are not part of an ordinary build.

## Starter assignment boundary

Keep the division of work explicit:

- supplied support: constructor, detached-node release, strict-BST insertion,
  typed node-pointer Stack, and status-name functions;
- supplied traversal examples: recursive inorder and recursive postorder;
- student work: recursive preorder, iterative preorder, the scaffolded
  strict-BST search decisions, and postorder whole-tree destruction using
  supplied `tree_node_release`; and
- later return: student implementation of insertion and balancing in
  Module 15.

Do not describe supplied postorder traversal as supplied postorder
destruction. They share visit/release placement, but destruction is one of
this module's four starter tasks.

## Tree preconditions

Traversal, search, and destruction assume:

1. every non-`NULL` pointer identifies a live `TreeNode`;
2. following child links cannot return to an earlier node;
3. no node is reached through more than one child field;
4. the tree is not modified during a traversal or search;
5. traversal contains no more than 64 nodes when success is expected;
6. BST search and insertion receive strict-BST ordering; and
7. whole-tree destruction receives nodes owned through that root.

These functions do not prove those conditions. A cycle never reaches a
`NULL` base case and can recurse indefinitely. A shared node can be visited
or released twice. A pointer to an unrelated or expired object has undefined
behavior in C. These are representation/precondition failures, not additional
`TreeDfsStatus` cases.

Aliases or symbolic links can lead to an already reachable object. Once that
is allowed, the model is a graph. Module 6 adds visited tracking so a vertex
is processed at most once.

## Canonical orders and visit semantics

A **visit** means copying `key` and `flagged` into the next `TreeVisit`.
Visit placement defines the order:

| Order | Recursive sequence | Canonical keys |
|---|---|---|
| preorder | node, left subtree, right subtree | `50, 30, 20, 40, 70` |
| inorder | left subtree, node, right subtree | `20, 30, 40, 50, 70` |
| postorder | left subtree, right subtree, node | `20, 40, 30, 70, 50` |

Filtering the preorder records for `flagged == true` gives:

```text
30, 40, 70
```

Inorder is increasing for this fixture because it is a valid strict BST.
Inorder does not generally sort an arbitrary binary tree.

## Recursive traversal contract

Each recursive helper begins:

```c
if (node == NULL) {
    return TREE_DFS_OK;
}
```

`NULL` is a valid empty subtree, not an error. It is the base case that ends
one branch. A public traversal with `root == NULL` and non-`NULL` output
returns `TREE_DFS_OK` and writes an empty `TreeOrder`.

At key `20`, the active calls with non-`NULL` node arguments are:

```text
oldest -> newest: 50, 30, 20
```

A subsequent call with the missing left child has a `NULL` argument and
returns immediately. A full call-event diagram may show that call, but it
must not be counted when a question explicitly asks for active non-`NULL`
calls.

The public functions build a local candidate:

```c
TreeOrder candidate = {0};
```

Only after the complete helper returns `TREE_DFS_OK` is the candidate copied
to `*out_order`. Therefore:

- `out_order == NULL` returns `TREE_DFS_INVALID_ARGUMENT`;
- the 65th attempted visit returns `TREE_DFS_LIMIT`; and
- every failure leaves the caller's entire `TreeOrder` unchanged.

Each helper also increments a separate reached-node count immediately after
the `NULL` check and before following either child. The 65th non-`NULL` node
therefore returns `TREE_DFS_LIMIT` before deeper recursion, including for
inorder and postorder where the visit itself occurs later.

Do not append directly to `out_order` and then attempt to restore it after a
deep failure. The candidate-and-commit structure makes output atomicity clear
and testable.

## Explicit pointer Stack

`code/include/tree_node_stack.h` defines a separately typed Stack:

```c
#define TREE_NODE_STACK_MAX_LIMIT 64U

typedef struct {
    const TreeNode **data;
    size_t size;
    size_t capacity;
    size_t limit;
} TreeNodeStack;

typedef enum {
    NODE_STACK_OK = 0,
    NODE_STACK_INVALID_ARGUMENT,
    NODE_STACK_LIMIT,
    NODE_STACK_UNDERFLOW,
    NODE_STACK_ALLOCATION,
    NODE_STACK_INVALID_STATE
} NodeStackStatus;
```

Its exact operations are:

```c
NodeStackStatus tree_node_stack_init(
    TreeNodeStack *stack,
    size_t limit
);

NodeStackStatus tree_node_stack_validate(
    const TreeNodeStack *stack
);

NodeStackStatus tree_node_stack_push(
    TreeNodeStack *stack,
    const TreeNode *node
);

NodeStackStatus tree_node_stack_pop(
    TreeNodeStack *stack,
    const TreeNode **out_node
);

void tree_node_stack_destroy(TreeNodeStack *stack);

const char *node_stack_status_name(NodeStackStatus status);
```

A testing build also exposes:

```c
void tree_node_stack_test_fail_next_allocation(void);
```

The Stack owns its growable array of pointers. It never owns or releases the
nodes those pointers identify. A `const TreeNode *` permits reading the node
through that pointer but not changing it through that pointer.

The completed Stack invariant is:

1. `limit <= TREE_NODE_STACK_MAX_LIMIT`;
2. `size <= capacity`;
3. `capacity <= limit`;
4. `capacity == 0` exactly when `data == NULL`; and
5. every occupied item is a non-`NULL` pointer supplied by a successful
   push.

The validator checks the field relationships in items 1-4. `push` separately
rejects a `NULL` node with `NODE_STACK_INVALID_ARGUMENT`.

Capacity grows lazily `0 -> 4 -> 8 -> ...`, clipped to `limit`. A zero limit
is valid. A push at the limit returns `NODE_STACK_LIMIT`. A failed
reallocation returns `NODE_STACK_ALLOCATION`; the old pointer array, size,
capacity, limit, and items remain unchanged. `pop` from empty returns
`NODE_STACK_UNDERFLOW` and leaves its output unchanged.

The Stack object must be destroyed on every path after successful
initialization. Destroy releases only the pointer array, then sets `data` to
`NULL` and all numeric fields to zero.

## Iterative preorder contract

`tree_preorder_iterative` accepts `stack_limit` from zero through 64.
Initialization above 64 maps to `TREE_DFS_LIMIT`.

The algorithm is:

```text
initialize pointer Stack
if root is non-NULL:
    push root
while pop succeeds:
    record popped node
    if right is non-NULL: push right
    if left is non-NULL: push left
destroy pointer Stack
commit candidate output only on success
```

The Stack is last in, first out, so right is pushed before left. Required
bottom-to-top snapshots are:

```text
after 50: 70, 30
after 30: 70, 40, 20
```

The visit sequence is `50, 30, 20, 40, 70`, matching recursive preorder.

Boundary behavior:

| Input or event | Result |
|---|---|
| `out_order == NULL` | `TREE_DFS_INVALID_ARGUMENT` |
| `root == NULL`, `stack_limit` from 0 through 64 | `TREE_DFS_OK`, empty order |
| nonempty root, `stack_limit == 0` | `TREE_DFS_LIMIT` |
| stack limit above 64 | `TREE_DFS_LIMIT` |
| explicit Stack growth failure | `TREE_DFS_ALLOCATION` |
| invalid internal Stack state or another impossible Stack error | conservatively `TREE_DFS_INVALID_ARGUMENT` |
| attempted 65th visit | `TREE_DFS_LIMIT` |

Every non-success result leaves `out_order` unchanged. The temporary Stack is
destroyed after successful initialization even when push, pop, allocation,
or output-limit handling fails.

The loop treats `NODE_STACK_UNDERFLOW` as normal completion because it means
there is no postponed node left. Other Stack failures are not completion.

## Constructor, insertion, and ownership

`tree_node_create` dynamically allocates one detached node:

```text
key = requested key
flagged = requested Boolean
left = NULL
right = NULL
```

`out_node == NULL` returns `TREE_DFS_INVALID_ARGUMENT`. Allocation failure
returns `TREE_DFS_ALLOCATION`. In both cases, the caller's output remains
unchanged. On success, the caller owns the detached node and must either
release it with `tree_node_release` or transfer ownership into a tree.

`tree_node_release` frees exactly one node and does not follow child links.
Passing `NULL` is a no-op. It is suitable for a detached node. Calling it on
a linked parent without first preserving and handling its children would
lose access to owned storage.

`tree_bst_insert` is instructor supplied. It:

1. rejects `root == NULL` with `TREE_DFS_INVALID_ARGUMENT`;
2. follows left for a smaller key and right for a larger key;
3. returns `TREE_DFS_DUPLICATE` before allocating when the key exists;
4. creates a new leaf only after finding the empty child position; and
5. changes the selected link only after allocation succeeds.

Thus duplicate and allocation failures preserve the entire tree. Empty-tree
insertion changes `*root` from `NULL` to the new leaf. The insertion baseline
is inspected and tested here; students implement insertion and balancing in
Module 15.

Module 2 used pointers into a caller-owned fixed arena; those nodes were not
individually freed. Module 5 nodes are individually allocated, owned through
the root after insertion, and individually released during destruction.
Mixing the two ownership models is an error.

## Strict-BST search

The search loop maintains one current pointer:

```text
while current is non-NULL:
    if target < current.key: current = current.left
    else if target > current.key: current = current.right
    else: report current and succeed
report not found
```

Canonical paths include:

| Target | Examined keys | Result |
|---:|---|---|
| 40 | `50, 30, 40` | `TREE_DFS_OK`, points to key 40 |
| 70 | `50, 70` | `TREE_DFS_OK`, points to key 70 |
| 35 | `50, 30, 40` then `NULL` left | `TREE_DFS_NOT_FOUND` |
| 90 | `50, 70` then `NULL` right | `TREE_DFS_NOT_FOUND` |

`out_node == NULL` returns `TREE_DFS_INVALID_ARGUMENT`. Success writes the
found address. Invalid argument and not found leave the caller's output
unchanged, even if its prior value is non-`NULL`.

Search correctness requires strict-BST ordering. On an arbitrary binary tree,
choosing one child by key can skip a matching node.

## Postorder destruction

Whole-tree destruction is:

```text
destroy(node):
    if node is NULL: return
    destroy(node.left)
    destroy(node.right)
    release node
```

The canonical release order is:

```text
20, 40, 30, 70, 50
```

The child pointers are read while the parent still exists. After both
subtrees are destroyed, the parent can be released without losing an owned
child address. `tree_destroy_postorder(NULL)` returns
`TREE_DFS_INVALID_ARGUMENT`. A non-`NULL` pointer-to-root whose value is
already `NULL` succeeds. Every success sets `*root = NULL`.

This destroy operation assumes a valid, wholly owned, acyclic, non-sharing
tree. It does not allocate, and under that precondition it has no partial
failure case after argument validation.

It does not impose the 64-record traversal limit because it produces no
`TreeOrder`. Its recursive depth is therefore bounded by caller input, and
the caller must keep tree height within the available C runtime call stack.
The supplied insertion baseline does not enforce that environmental limit.
Production cleanup for untrusted depths would need an explicit bound or a
different implementation.

## Failure atomicity summary

| Operation | Failure | Caller-visible preservation |
|---|---|---|
| `tree_node_create` | invalid output or allocation | `out_node` unchanged |
| `tree_bst_insert` | invalid root pointer, duplicate, allocation | root and all links/nodes unchanged |
| recursive traversal | invalid output or more than 64 visits | `out_order` unchanged |
| iterative preorder | invalid output, Stack limit/allocation, more than 64 visits | `out_order` unchanged; temporary Stack destroyed |
| `tree_bst_search` | invalid output or missing key | `out_node` unchanged |
| pointer-Stack push | invalid state/item, limit, allocation | Stack unchanged |
| pointer-Stack pop | invalid output/state or underflow | Stack and output unchanged |

`tree_destroy_postorder` is intentionally different: success consumes the
owned tree and sets the root to `NULL`.

## Complexity

Let:

- `n` be the number of tree nodes; and
- `h` be the greatest number of downward child links on a root-to-leaf path,
  preserving Module 2's height convention.

A one-node tree therefore has height zero. The greatest number of
simultaneous non-`NULL` recursive calls or explicit pending items is at most
`h + 1`. Courses conventionally report that auxiliary-space growth as
`O(h)`; `O(h + 1)` is the literal bound that also describes the one-node
case.

| Operation | Time | Auxiliary space | Reason |
|---|---:|---:|---|
| recursive preorder/inorder/postorder | `O(n)` | `O(h)` | one visit per node; at most one active call per level |
| iterative preorder | `O(n)` | `O(h)` | each node is pushed and popped once; postponed siblings are bounded by height |
| strict-BST search | `O(h)` | `O(1)` | one path, iterative current pointer |
| supplied strict-BST insertion | `O(h)` | `O(1)` | one path plus one allocation |
| postorder destruction | `O(n)` | `O(h)` | each node released once; recursive call depth follows height |
| report flags from a completed order | `O(n)` | `O(1)` beyond the order | inspect each visit record once |

For a balanced tree, `h` grows roughly like `log n`. For a completely skewed
nonempty tree, `h == n - 1`, so recursion or the explicit Stack can require
`O(n)`
auxiliary space. `O(h)` is therefore both more precise and more informative
than claiming constant space.

The explicit Stack can occasionally copy its pointer array during geometric
growth. Across the full sequence, pushes remain amortized `O(1)`, so total
iterative traversal time remains `O(n)`.

## Status-name behavior

`tree_dfs_status_name` returns:

| Status | Text |
|---|---|
| `TREE_DFS_OK` | `ok` |
| `TREE_DFS_INVALID_ARGUMENT` | `invalid argument` |
| `TREE_DFS_LIMIT` | `tree or Stack limit reached` |
| `TREE_DFS_ALLOCATION` | `allocation failed` |
| `TREE_DFS_DUPLICATE` | `duplicate key` |
| `TREE_DFS_NOT_FOUND` | `key not found` |
| unknown enumeration value | `unknown TreeDfsStatus` |

`node_stack_status_name` uses its separate NodeStack names and should also
return a stable unknown-status string. Tests should compare published exact
text only where the header/package presents it as exact output.

## Public tests, instructor tests, and hooks

Public tests cover representative contract behavior without revealing every
instructor check. The list below is the recommended full verification matrix,
not a claim that every item is automated in the bundled files. Instructor
CI or code review may add cases, but must not test unpublished assumptions.

1. exact canonical preorder, inorder, postorder, and copied flag values;
2. `NULL` root as a successful empty traversal;
3. one-node, balanced, left-skewed, and right-skewed trees;
4. recursive/iterative preorder equivalence;
5. iterative Stack limits 0, exact-needed, one below needed, and 64;
6. a limit above 64;
7. traversal of 64 nodes and rejection of an attempted 65th visit;
8. unchanged nonzero sentinel `TreeOrder` after every traversal failure;
9. found root, internal, and leaf BST targets;
10. missing smaller, between-key, and larger BST targets with unchanged
    non-`NULL` output sentinel;
11. constructor field initialization and unchanged output on forced failure;
12. insertion into empty/nonempty trees, duplicate rejection before
    allocation, and allocation-failure preservation;
13. pointer-Stack invariant, lazy growth, clipped growth, zero limit,
    underflow, invalid state, allocation failure, and output preservation;
14. postorder destruction of empty, one-node, balanced, and skewed trees;
15. root reset and zero live-node count after destruction;
16. status-name coverage including unknown enumeration values; and
17. the autopsy regression: iterative preorder must be
    `50, 30, 20, 40, 70`, not `50, 70, 30, 40, 20`.

The failure-next-allocation hooks are one-shot and testing only. The live-node
counter is evidence for test fixtures, not a production ownership system.
Tests clean up allocated fixtures whenever the structure is still known to
be valid. After a student-controlled destroy call fails, the harness stops
that test without traversing the possibly freed or partly freed tree; trying
to clean it again could cause a double release.

The bundled live-node checks prove that destruction releases every owned
node and resets the root. They do not reveal release order. Assess the
child-before-parent order through the source review and the required
postorder trace rather than adding a production-style logging dependency.

## Autopsy reference

The faulty implementation pushes left before right:

```text
visit 50
push 30
push 70
pop 70 next
```

Its observed order is:

```text
50, 70, 30, 40, 20
```

The first incorrect decision is `push left` before `push right` after
visiting `50`. The Stack faithfully removes the newest pointer first. Repair
the decision by pushing right, then left. A strong regression test compares
the entire canonical order and is named for the behavioral rule, such as
`left_first_preorder_pushes_right_before_left`.

## Instructor implementation audit

- [ ] Header and implementation use `TREE_DFS_MAX_NODES == 64U`.
- [ ] Public status names and enumeration order match exactly.
- [ ] `TreeVisit` copies both key and flag.
- [ ] Every traversal accepts `NULL` root as empty.
- [ ] Recursive helpers test `NULL` before dereferencing.
- [ ] Candidate output is committed only on full traversal success.
- [ ] The 65th visit returns `TREE_DFS_LIMIT`.
- [ ] Iterative `stack_limit` accepts zero and rejects values above 64.
- [ ] Iterative preorder pushes right before left.
- [ ] The temporary pointer Stack is destroyed on every initialized path.
- [ ] The pointer Stack owns only its pointer array, never tree nodes.
- [ ] Constructor and Stack allocation failures are reproducible only in
      testing builds.
- [ ] Duplicate insertion allocates nothing and changes no link.
- [ ] Missing search leaves output unchanged.
- [ ] Destruction releases children before parent and resets the root.
- [ ] Tests clean up every successfully allocated fixture.
- [ ] No example claims safety for cycles, sharing, aliases, symbolic links,
      or hostile pointers.
- [ ] No example treats a synthetic flag report as a real security decision.
