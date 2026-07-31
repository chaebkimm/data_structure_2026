# Instructor Answer Key - Module 5 Tree DFS

## Macro-Question synthesis

> If we follow one branch as far as possible, how do we remember every branch
> to which we must return?

A strong answer says that recursive traversal leaves active calls waiting
while a child subtree is processed. Each call frame remembers the current
node and what instruction follows the child call. An iterative traversal
stores postponed node pointers in an explicit Stack. Both create last-in,
first-out access to unfinished work, but the C runtime manages call frames
while program code manages the explicit Stack.

The method stops at a `NULL` child pointer. A pure tree is acyclic and has no
shared node, so repeatedly following children eventually reaches `NULL`.

---

## Stage A inquiry

The standard and linear files have the same targets. The IDs below use the
linear file's explicit numbering and map in order to the standard file's
response spaces. Stage A precedes formal traversal vocabulary. Accept plain
language that expresses the behavior.

### A. Read the tree

#### A1. All keys

Accept `50, 30, 20, 40, 70` in any order because the question asks for
membership, not a visit order.

#### A2. Root

`50`.

#### A3. Leaves

`20, 40, 70`. A leaf has no children.

#### A4. Marked keys

`30, 40, 70`.

### B. Invent a visiting rule

#### B1. Repeatable rule

Canonical response:

> At a node, write its key. Then apply the same rule to its left child, if it
> exists, and then its right child, if it exists. Stop at a missing child.

Before formal vocabulary opens, students might invent another repeatable
left-preferring order, such as completing a left child before writing its
parent. Accept it if it starts from the root location, reaches every node
exactly once, states a safe stop, and treats left before right consistently.
Record the canonical node-first route for later comparison; do not retroactively
mark a coherent initial model as dishonest.

#### B2. Visit sequence

For the canonical node-first rule:

```text
50, 30, 20, 40, 70
```

If B1 states a different valid rule, evaluate B2 against that stated rule.

#### B3. Completeness

A strong answer says the method handles both child positions of every reached
node, stops only at missing positions, and uses each real child link once.
Because the supplied structure is one pure tree rooted at `50`, every node is
reachable through exactly one parent route and none is missed or repeated.

### C. Remember choices not yet taken

#### C1. Remaining work

At key `20`, the immediate leaf has no children, but these parts remain:

- return through key `30` and handle its right subtree rooted at `40`;
- finish the call/work associated with `30`; and
- return through key `50` and handle its right subtree rooted at `70`.

#### C2. Remembered information

Accept either of these equivalent models:

- remember the active ancestors and which instruction/child comes next; or
- remember postponed node pointers, especially `40` and `70`.

The essential idea is that completing `20` does not erase the knowledge of
the two earlier right choices.

#### C3. Nested unfinished work

Yes. The work associated with `30` can be completed, including key `40`,
while the older work associated with `50` is still waiting for key `70`.
The newer unfinished branch completes before the older postponed branch.

### D. Report selected nodes

#### D1. Report

```text
30, 40, 70
```

Under the canonical node-first traversal, this is also their report order.

#### D2. Same relationships

No. The `left` and `right` relationships describe the tree. Changing the
visit task from "write every key" to "write only marked keys" changes the
reporting condition, not the structure. The traversal still reaches
unmarked nodes because their descendants may be marked.

### E. Consider stopping conditions

#### E1. Missing child

Do nothing for that position and return to the most recent unfinished real
node or choice. Later vocabulary names the missing pointer `NULL` and this
immediate return the recursive base case.

#### E2. Leaf

After performing the visit task, treat both missing child positions as
finished and return to the newest unfinished ancestor/choice. When no
unfinished choice remains, the whole method is complete.

#### E3. Safe stopping

Following a missing position as though it contained another node would fail
to make progress, could attempt to read an object that does not exist, and
could prevent termination. In C, dereferencing `NULL` is invalid.

### F. Macro-Question

Canonical Stage A language:

> Begin at the root. At each real item, perform the task, remember choices
> that must be handled later, and prefer the left choice before the right.
> A missing child ends that branch. Return to the newest unfinished choice
> until none remain.

Do not require the words recursion, frame, DFS, preorder, or Stack at Gate A.

### G. Open question

Answers vary. Useful questions ask how the computer stores return points,
whether reporting occurs before or after children, how much memory is needed,
or what changes if a path reconnects to an earlier item.

---

## Stage B Cognitive Pause

The pause has exactly three targets. Do not use this key, the vocabulary
file, hints, or correctness feedback until the student's response is
preserved.

### Target 1 - Apply three orders

The pause tree is:

```text
       12
      /  \
     5    17
    / \
   2   9
```

1. Preorder, node-left-right:

   ```text
   12, 5, 2, 9, 17
   ```

2. Inorder, left-node-right:

   ```text
   2, 5, 9, 12, 17
   ```

3. Postorder, left-right-node:

   ```text
   2, 9, 5, 17, 12
   ```

### Target 2 - Explain active calls

1. The call whose argument is key `20` asks to process its left child. That
   child pointer is `NULL`, so the new base-case call returns immediately.
   It records no visit and makes no further child call.
2. Active calls whose node arguments are non-`NULL`, oldest to newest:

   ```text
   50, 30, 20
   ```

3. The frame for `30` must remember that after its left subtree returns, its
   right subtree rooted at `40` remains. The frame for `50` must remember that
   after its left subtree rooted at `30` returns, its right subtree rooted at
   `70` remains.

A full event diagram may show a short-lived `NULL` call above the `20` call.
Do not count it in the explicitly requested list of non-`NULL` calls.

### Target 3 - Trace explicit storage

Stack contents are bottom to top:

1. After popping/visiting `50`, then pushing `70` and `30`:

   ```text
   70, 30
   ```

2. Pop/visit `30`, leaving `70`; then push `40` and `20`:

   ```text
   70, 40, 20
   ```

3. A Stack removes the most recently pushed remaining item. Pushing the right
   child first and the left child second puts the left child on top, so the
   left child comes out next.

---

## Stage C investigation

The standard and linear worksheets are prompt-for-prompt equivalent. Sections
A-F are the required core; G-I are later extension and reflection.

### A. Trace the three DFS orders

#### A1. Preorder

```text
50, 30, 20, 40, 70
```

#### A2. Inorder

```text
20, 30, 40, 50, 70
```

This sequence is increasing because the course tree satisfies strict-BST
ordering.

#### A3. Postorder

```text
20, 40, 30, 70, 50
```

#### A4. Flagged preorder

```text
30, 40, 70
```

The `TreeOrder` first records all five key/flag pairs in preorder. Reading
that complete output and filtering copied true flags reports the three keys
above. An unflagged node can have flagged descendants: unflagged root `50`
leads to all three flagged nodes. Therefore filtering may omit a record from
the report but may not prune that node's entire subtree.

#### A5. Empty traversal

The successful result is:

```text
out_order->count == 0
status == TREE_DFS_OK
```

No `TreeVisit` record is required for a `NULL` root.

### B. Explain recursive saved work

#### B1. Base case

The call receiving the missing left child of `20` has `node == NULL`. It
returns immediately without dereferencing the pointer, recording a node, or
calling itself again. Without this base case, the procedure would not stop
safely at the end of a branch.

#### B2. Active calls

Oldest to newest:

```text
50, 30, 20
```

#### B3. Saved work

- Frame `30` is waiting for the left-subtree call through `20` to return;
  afterward it must process the right subtree rooted at `40` and then return.
- Frame `50` is waiting for the entire left subtree through `30` to return;
  afterward it must process the right subtree rooted at `70` and then return.

#### B4. Moving the visit

The left and right fields never change. Every version makes the same child
calls in left-then-right order. Only the time at which the current node is
copied changes:

- before both calls gives preorder;
- between the calls gives inorder; and
- after both calls gives postorder.

### C. Trace iterative preorder

#### C1. First two states

Bottom to top:

```text
after visiting 50: 70, 30
after visiting 30: 70, 40, 20
```

#### C2. Right before left

The Stack is last in, first out. The right pointer is pushed first; the left
pointer is pushed second and becomes the top. The next pop therefore selects
left.

#### C3. Complete iterative trace

The initial Stack contains `50`.

| Popped key | Recorded order after visit | Stack after child pushes, bottom to top |
|---:|---|---|
| 50 | `50` | `70, 30` |
| 30 | `50, 30` | `70, 40, 20` |
| 20 | `50, 30, 20` | `70, 40` |
| 40 | `50, 30, 20, 40` | `70` |
| 70 | `50, 30, 20, 40, 70` | empty |

Missing children are not pushed.

#### C4. Stack limit

Pushing a non-`NULL` root into a zero-limit Stack fails with
`TREE_DFS_LIMIT`. The caller's prior `TreeOrder`, including its `count` and
all item bytes, remains unchanged.

A `NULL` root with limit zero is different: no pointer must be pushed, so it
succeeds with an empty order.

#### C5. Two different mechanisms

Recursive preorder uses active function calls, commonly represented by
runtime-managed call frames. Iterative preorder uses a program-controlled
`const TreeNode *` Stack and calls its explicit operations. Both remember
unfinished work with last-in, first-out behavior, but the explicit Stack is
an ordinary data object; it is not the C runtime's call-management
mechanism.

### D. Apply the public contracts

#### D1. Type roles

- `TreeNode` is one live tree object containing a key, flag, and two child
  pointers.
- `TreeVisit` is one copied observation containing a key and flag.
- `TreeOrder` is a fixed array of at most 64 visit records plus their count.

Copying the small observable values lets a completed order remain meaningful
without owning, modifying, or prolonging a node's dynamic allocation. The
tree remains responsible for node lifetime.

#### D2. Status matching

1. traversal succeeds: `TREE_DFS_OK`;
2. required output pointer is `NULL`: `TREE_DFS_INVALID_ARGUMENT`;
3. more than 64 visits: `TREE_DFS_LIMIT`;
4. node allocation for insertion fails: `TREE_DFS_ALLOCATION`;
5. insertion requests an existing key: `TREE_DFS_DUPLICATE`;
6. search reaches `NULL`: `TREE_DFS_NOT_FOUND`.

#### D3. Unchanged traversal output

Return `TREE_DFS_LIMIT`. The two prior records, `count`, and every other byte
of the caller's `TreeOrder` remain exactly as before the call. A partial
traversal is not committed.

#### D4. Unchanged search output

Return `TREE_DFS_NOT_FOUND`. The sentinel stored in `out_node` remains
unchanged; the function does not replace it with `NULL`.

#### D5. Boundary distinction

The fixed 64-visit limit is the maximum number of completed node records that
fit in `TreeOrder` and applies to every traversal. The caller-selected
`stack_limit` bounds how many postponed node pointers the iterative method
may hold at once. It may be any value from 0 through 64. A tree with at most
64 nodes can still fail iterative traversal if its needed simultaneous Stack
size exceeds the selected limit. A requested `stack_limit` above 64 also
returns `TREE_DFS_LIMIT`; it does not enlarge `TreeOrder`.

### E. Search a strict binary search tree

#### E1. Found path

```text
compare 40 with 50: lower, go left
compare 40 with 30: higher, go right
compare 40 with 40: equal, found
```

Compared keys: `50, 30, 40`. Final status: `TREE_DFS_OK`.

#### E2. Missing path

```text
compare 35 with 50: lower, go left
compare 35 with 30: higher, go right
compare 35 with 40: lower, go left
40's left child is NULL
```

Compared keys: `50, 30, 40`. Final status:
`TREE_DFS_NOT_FOUND`. The output pointer remains unchanged.

#### E3. Strict insertion

Return `TREE_DFS_DUPLICATE`. A strict BST contains no duplicate keys. The
function detects equality before requesting a node and changes no link, key,
flag, or ownership state.

#### E4. Search versus full traversal

Strict ordering proves that a lower target cannot occur in the right subtree
and a higher target cannot occur in the left subtree, so search eliminates
one whole side at each comparison. A general traversal has no target-key
rule that makes an unvisited subtree irrelevant; it must process both.

### F. Release owned nodes safely

#### F1. Child before parent

Postorder release sequence:

```text
20, 40, 30, 70, 50
```

While a parent still exists, its `left` and `right` fields remain available
for locating owned children. After both child subtrees are destroyed, the
parent can be released without losing the only route to a child.

#### F2. Unsafe early release

After key `50` is freed, the address no longer identifies a live
`TreeNode`. Evaluating `50->left` through that dangling pointer is a
use-after-free and has undefined behavior. It also risks losing the child
address and leaking the remaining nodes.

#### F3. Root reset

The old root address becomes dangling after destruction. Writing `NULL`
prevents accidental reuse, represents the empty tree, and lets a later
destroy of that empty tree succeed safely.

#### F4. Complexity

Each real node performs a fixed amount of visit work, so visiting all `n`
nodes is `O(n)` time.

Module 2 defines height `h` as the greatest number of downward child links on
a root-to-leaf path. A root-only tree has `h == 0`. A deepest route can have
at most `h + 1` simultaneous non-`NULL` calls or pending Stack items. That
literal bound is `O(h + 1)` and is conventionally reported as `O(h)`
auxiliary space. Balanced trees keep `h` small; a skewed `n`-node tree has
`h == n - 1`.

#### F5. Reliability boundary

No. The limit bounds a teaching implementation and the traversal reports
synthetic flags. It does not authenticate real data, follow operating-system
semantics, validate authorization rules, handle races or aliases, or prove
that a real policy grants the intended permissions.

### G. Design tests - later extension

#### G1. Shape coverage

One acceptable concrete set is:

| Shape | Example | Preorder | Inorder | Postorder |
|---|---|---|---|---|
| empty | `NULL` | empty | empty | empty |
| one node | `10` | `10` | `10` | `10` |
| only-left chain | `30 ->left 20 ->left 10` | `30, 20, 10` | `10, 20, 30` | `10, 20, 30` |
| only-right chain | `10 ->right 20 ->right 30` | `10, 20, 30` | `10, 20, 30` | `30, 20, 10` |
| course tree | canonical five nodes | `50, 30, 20, 40, 70` | `20, 30, 40, 50, 70` | `20, 40, 30, 70, 50` |

Other key choices are correct when the links and expected sequences agree.
Tests must also compare copied `flagged` values, not only keys.

#### G2. Failure preservation

One strong test:

1. Fill every byte of a `TreeOrder` with a known sentinel pattern.
2. Copy it to a separate `before` object.
3. Call `tree_preorder_iterative` with the nonempty course root and
   `stack_limit == 0`.
4. Require `TREE_DFS_LIMIT`.
5. Require a byte-for-byte comparison of the output with `before` to be
   equal.

An alternative can force pointer-Stack allocation failure under
`TREE_DFS_TESTING` and make the same preservation checks.

#### G3. Agreement

Run recursive and iterative preorder on the same valid tree with a sufficient
Stack limit. Compare their statuses, counts, and every output record's key
and flag. Do not inspect recursive call frames, pointer-Stack capacity, or
allocation addresses; those are different implementations behind the same
observable traversal contract.

### H. Transfer from a tree to a graph - later extension

#### H1. Shared target

With two incoming routes, a pure tree method has no record that the first
route already processed the target. It follows the second route and visits
the same object again. Destruction would be more dangerous because it could
attempt to release the shared object twice.

#### H2. Link back

A link to an ancestor creates a cycle. Following children returns to an
already active node rather than eventually reaching `NULL`, so the recursive
or iterative method can repeat forever or exhaust its working-storage limit.

#### H3. Visited tracking

Before exploring a reached node, check whether its identity is in the visited
set. If present, do not explore it again. If absent, add it before following
outgoing relationships. This makes a shared target's later route stop and
also breaks a cycle when it returns to an already recorded node.

### I. Exit reflection - later extension

#### I1. Three orders

- preorder: node, left subtree, right subtree;
- inorder: left subtree, node, right subtree;
- postorder: left subtree, right subtree, node.

#### I2. Two ways to remember

- A recursive call frame is runtime-managed information for one active
  function call.
- The explicit TreeNode-pointer Stack is a program-controlled object that
  stores postponed node addresses.
- The Stack ADT is the general last-in, first-out behavior contract,
  independent of a particular item type or storage backend.

The explicit pointer Stack is one implementation/use of the Stack ADT. It is
not the runtime call stack.

#### I3. Safe cleanup

Postorder handles both child subtrees while the parent's links are still
readable, then releases the parent. It therefore preserves access to every
owned descendant until that descendant has been released.

#### I4. Open question

Answers vary. Use them to plan review of call events, visit placement,
Stack-state direction, ownership, or the graph boundary.

---

## Canonical API reference

### Status enumeration

Exact public order:

```text
TREE_DFS_OK
TREE_DFS_INVALID_ARGUMENT
TREE_DFS_LIMIT
TREE_DFS_ALLOCATION
TREE_DFS_DUPLICATE
TREE_DFS_NOT_FOUND
```

### Constructor and detached-node release

```c
TreeDfsStatus tree_node_create(
    int key,
    bool flagged,
    TreeNode **out_node
);

void tree_node_release(TreeNode *node);
```

On successful create, fields are the supplied key/flag and two `NULL` child
pointers. Invalid output and forced allocation failure leave `out_node`
unchanged. The returned node is detached and caller-owned until ownership is
transferred into a tree. `tree_node_release(NULL)` is a no-op and releases
one node only; it does not traverse children.

### Supplied strict-BST insertion

```c
TreeDfsStatus tree_bst_insert(
    TreeNode **root,
    int key,
    bool flagged
);
```

It goes left for lower, right for higher, rejects equality, and allocates
only after an empty link is found. Duplicate and allocation failures leave
the tree unchanged. This is an inspect-and-test baseline; student insertion
implementation returns in Module 14.

### Traversals

```c
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
```

All accept a `NULL` root as a successful empty traversal. All copy both key
and flag. All leave output unchanged on failure. The iterative version
accepts `stack_limit` from 0 through 64 and destroys its temporary pointer
Stack after every successful initialization.

### Strict-BST search

```c
TreeDfsStatus tree_bst_search(
    const TreeNode *root,
    int target,
    const TreeNode **out_node
);
```

It reports only success or not found after valid arguments. `out_node`
changes only on success.

### Postorder destruction

```c
TreeDfsStatus tree_destroy_postorder(TreeNode **root);
```

A `NULL` pointer-to-root is invalid. An already empty `*root` succeeds. A
successful call releases the whole valid owned tree in postorder and sets
`*root = NULL`.

### Public testing hooks

When `TREE_DFS_TESTING` is defined, Stage E's public headers expose one-shot
allocation-failure controls and a live-node counter. Correct public tests may
use them to prove failure preservation and cleanup. Normal builds do not
expose them. The reference solution and extension tests remain private.

---

## Iterative-order autopsy

The faulty program pushes the left child before the right child. The Stack
then removes the right child first.

### Prediction

Faulty output:

```text
50, 70, 30, 40, 20
```

### First bad decision

Immediately after visiting `50`, it pushes `30` and then `70`. Because `70`
is newest, it is selected next. The first wrong observed visit is therefore
`70`, but the earlier cause is the child push order.

### Repair

Push right before left:

```text
if right exists: push right
if left exists: push left
```

Correct output:

```text
50, 30, 20, 40, 70
```

Do not reverse the completed output as a repair. That would conceal the
wrong exploration decisions and would not generalize safely.

### Regression evidence

A strong test:

- uses a root with both children and a left child that also has both
  children;
- compares the complete output, not only the first or last key;
- expects `50, 30, 20, 40, 70`; and
- has a behavioral name such as
  `left_first_preorder_pushes_right_before_left`.
