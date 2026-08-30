# Stage C — Investigation: Linear Accessible Format

This version has the same targets as the standard investigation without
response tables or drawing requirements. Use a screen reader, keyboard,
speech input, or a plain-text response.

Open it after preserving the Cognitive Pause and completing calibration.

## Quick reference

Each `struct TreeNode` variable stores `data`, `left`, and `right`.
A pointer stores an address. `&root` is the address of the variable `root`.
A dot selects a field of a variable; `->` selects a field through a pointer.
`NULL` means that no node is linked at that side.

All ordinary examples use initialized local nodes that remain alive
throughout the activity. A general binary tree may use zero, one, or two
child positions. A completed expression tree additionally uses two children
for each binary operator and none for each numeric operand. Data does not
sort the nodes.

## Student information

Name:

Date:

## D. Translate among representations

Use these facts about the independent transfer tree
`(8 - 3) * (4 + 2)`:

- `root` stores `'*'`; its left link is `&minus` and right link is `&plus`.
- `minus` stores `'-'`; its left link is `&eight` and right link is `&three`.
- `plus` stores `'+'`; its left link is `&four` and right link is `&two`.
- `eight` stores `8`; both links are `NULL`.
- `three` stores `3`; both links are `NULL`.
- `four` stores `4`; both links are `NULL`.
- `two` stores `2`; both links are `NULL`.

### D1. Connections

Describe each connection, including its side.

Response:

### D2. Assignments

Complete `root.left = ...`, `root.right = ...`, `minus.right = ...`, and
`plus.left = ...` for this state.

Response:

### D3. C expression meanings

Explain `root`, `&root`, `root.left`, `root.left->data`, and `NULL`.

Response:

## E. Name positions

A path follows connected nodes. An ancestor occurs earlier on the path from
the root; a descendant occurs below a node. Depth counts links from the
root. Height is the greatest number of downward links to a leaf. A leaf has
no children. A subtree contains one node and all its descendants.

Use the section D tree.

1. Write the data path from `root` to `four`.
2. Give the depth of `four`.
3. List the leaf variables.
4. Give the height of `minus`, then of `root`.
5. List the variables in the subtree rooted at `minus`.

Response:

## F. Separate an invariant from a local check

An invariant is a rule followed by every valid state. A precondition is a
condition the caller must ensure before using an operation.

### F1. Complete the rules

- The section D root has blank incoming child links.
- Every other node has exactly blank incoming child link.
- Following child links must never return to an earlier node on the same
  route. Such a route is a blank.
- Every linked object must be initialized and still blank.

Response:

### F2. Proposed connections

Consider each request separately. `n7` is a fresh, initialized, unlinked
node. Say whether the request is permitted. If not, explain whether an
empty-side check is enough to prevent it or the caller must check the wider
relationships. If it is permitted as a general tree change, also state
whether the result remains a completed expression tree.

1. Put `&n7` in `two.left` under the general tree contract.
2. Put `&n7` in `root.left` without replacing its child.
3. Also put `&three` in `four.left`.
4. Put `&root` in `eight.left`.
5. Put `&n7` in both sides of `two`.

Response:

These are paper reasoning cases. Do not run search or clearing on a cyclic
or shared structure as an ordinary test. The two functions do not validate
arbitrary relationships.

## G. Reason about node lifetime

A local node exists until its declaring block finishes. Clearing a node
resets its fields; it does not end that lifetime.

Classify each action as safe or unsafe, then explain.

1. Initialize data and both links before attaching a fresh node.
2. Follow a node whose child links were never initialized.
3. Inspect `minus.data` after `tree_clear(&minus)`, while its block is still
   active.
4. Follow a saved address after the local node's declaring function has
   returned.

Response:

Does passing a node's address to another function extend its lifetime?

Response:

## H. Keep the chosen side

In a separate valid example, `parent.left` is `NULL` and `parent.right`
is `&n8`. Both objects are initialized and alive.

1. Is `parent` a leaf? Explain.
2. A fresh node `n4` is attached on the left. State both links afterward.
3. The left branch is then cleared and detached. State both links afterward.
   Why must `&n8` remain on the right?

Response:

## I. Trace recursive search

Search checks the current node, then its left subtree, then its right
subtree. It stops at the first match. Start again with section D.

1. List the complete order in which node data is checked.
2. List the values checked by `tree_find(&root, 4)`. Which address is
   returned?
3. What does `tree_find(&root, 404)` return?
4. In a separate case, `two.data` is changed to `4`. Which node does a search
   for `4` return, and why?
5. Would changing `eight.data` to `900` break a tree rule? Why may search not
   use numeric comparisons to skip a subtree?

Response:

## J. Trace clearing and caller detachment

Start again with section D. The caller runs
`tree_clear(root.left);` followed by `root.left = NULL;`.

1. Which node variables have their data reset? State their final data and
   links. What remains in `root.right`?
2. If the caller only ran `tree_clear(&minus)`, would `root.left` change?
   Explain why clearing and detaching are different actions.
3. After the two-line removal, may the caller still inspect or reinitialize
   `minus` while its declaring block is active? Explain.

Response:

### J4. Count the work

Let `n` be the number of searched nodes and `k` the number of nodes in the
selected subtree. Give the work in fields or nodes and explain for each
operation:

1. Initialize one node.
2. Attach a fresh node to a known empty side.
3. Search for a missing value.
4. Clear a subtree.
5. Detach an already cleared child.

Response:

Why can a deeper recursive search need more temporary call storage?

Response:

## K. Transfer to a different relationship model

A graph is a more general relationship structure that may allow shared items
or cycles. Give one useful situation where two items should lead to the same
object. Why would our unshared-tree precondition no longer fit?

Response:

## L. Exit ticket

1. What does a child link store?
2. Can the right side be used while the left side is empty?
3. Who ensures that no node is shared or part of a cycle?
4. Does clearing a node end its lifetime?
5. Which link must the caller change to remove a cleared left child?

Response:
