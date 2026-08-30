# Stage C — Investigation: Binary-Tree Operations

Name: ____________________________
Date: ____________________________

Open this file after preserving the Cognitive Pause and completing calibration.

## Quick reference

Each `struct TreeNode` variable stores `data`, `left`, and `right`.
A pointer stores an address. `&root` means the address of the variable
`root`. A dot selects a field of a variable; `->` selects a field through
a pointer. `NULL` means that no node is linked at that side.

All ordinary examples below use initialized local nodes that remain alive
throughout the activity. A general binary tree may use zero, one, or two
child positions. A completed expression tree additionally uses two children
for each binary operator and none for each numeric operand. Data does not
sort the nodes.

## D. Translate among representations

The table describes `(8 - 3) * (4 + 2)`, an independent transfer tree.

| Local variable | Data | Left address | Right address |
|---|---:|---|---|
| `root` | `'*'` | `&minus` | `&plus` |
| `minus` | `'-'` | `&eight` | `&three` |
| `plus` | `'+'` | `&four` | `&two` |
| `eight` | `8` | `NULL` | `NULL` |
| `three` | `3` | `NULL` | `NULL` |
| `four` | `4` | `NULL` | `NULL` |
| `two` | `2` | `NULL` | `NULL` |

1. Draw the tree or describe each connection, including its side.

   _________________________________________________________________

2. Complete the assignments that describe this state:

```c
root.left = ________________________________________________________;
root.right = _______________________________________________________;
minus.right = ______________________________________________________;
plus.left = ________________________________________________________;
```

3. Explain each C expression:

| Expression | Meaning |
|---|---|
| `root` | |
| `&root` | |
| `root.left` | |
| `root.left->data` | |
| `NULL` | |

## E. Name positions

A path follows connected nodes. An ancestor occurs earlier on the path from
the root; a descendant occurs below a node. Depth counts links from the
root. Height is the greatest number of downward links to a leaf. A leaf has
no children. A subtree contains one node and all its descendants.

Use the section D tree.

1. Write the data path from `root` to `four`. ______________________
2. Give the depth of `four`. ______________________________________
3. List the leaf variables. ________________________________________
4. Give the height of `minus`, then of `root`. _____________________
5. List the variables in the subtree rooted at `minus`. ____________

## F. Separate an invariant from a local check

An invariant is a rule followed by every valid state. A precondition is a
condition the caller must ensure before using an operation.

Complete the rules:

- The section D root has __________ incoming child links.
- Every other node has exactly __________ incoming child link.
- Following child links must never return to an earlier node on the same
  route. Such a route is a __________.
- Every linked object must be initialized and still __________.

Consider each request separately. `n7` is a fresh, initialized, unlinked
node. Say whether the request is permitted. If not, explain whether an
empty-side check is enough to prevent it or the caller must check the wider
relationships. If it is permitted as a general tree change, also state
whether the result remains a completed expression tree.

| Proposed connection | Permitted? | Reason and responsibility |
|---|---|---|
| Put `&n7` in `two.left` under the general tree contract | | |
| Put `&n7` in `root.left` without replacing its child | | |
| Also put `&three` in `four.left` | | |
| Put `&root` in `eight.left` | | |
| Put `&n7` in both sides of `two` | | |

These are paper reasoning cases. Do not run search or clearing on a cyclic
or shared structure as an ordinary test. The two functions do not validate
arbitrary relationships.

## G. Reason about node lifetime

A local node exists until its declaring block finishes. Clearing a node
resets its fields; it does not end that lifetime.

Classify each action as safe or unsafe, then explain.

| Action | Safe or unsafe? | Reason |
|---|---|---|
| Initialize data and both links before attaching a fresh node | | |
| Follow a node whose child links were never initialized | | |
| Inspect `minus.data` after `tree_clear(&minus)`, while its block is still active | | |
| Follow a saved address after the local node's declaring function has returned | | |

Does passing a node's address to another function extend its lifetime?

____________________________________________________________________

## H. Keep the chosen side

In a separate valid example, `parent.left` is `NULL` and `parent.right`
is `&n8`. Both objects are initialized and alive.

1. Is `parent` a leaf? Explain. ____________________________________
2. A fresh node `n4` is attached on the left. State both links afterward.

   _________________________________________________________________

3. The left branch is then cleared and detached. State both links afterward.
   Why must `&n8` remain on the right?

   _________________________________________________________________

## I. Trace recursive search

Search checks the current node, then its left subtree, then its right
subtree. It stops at the first match. Start again with section D.

1. List the complete order in which node data is checked.

   _________________________________________________________________

2. List the values checked by `tree_find(&root, 4)`. Which address is
   returned?

   _________________________________________________________________

3. What does `tree_find(&root, 404)` return? ________________________

4. In a separate case, `two.data` is changed to `4`. Which node does a search
   for `4` return, and why?

   _________________________________________________________________

5. Would changing `eight.data` to `900` break a tree rule? Why may search not
   use numeric comparisons to skip a subtree?

   _________________________________________________________________

## J. Trace clearing and caller detachment

Start again with section D. The caller removes the left branch:

```c
tree_clear(root.left);
root.left = NULL;
```

1. Which node variables have their data reset? State their final data and
   links. What remains in `root.right`?

   _________________________________________________________________

2. If the caller only ran `tree_clear(&minus)`, would `root.left` change?
   Explain why clearing and detaching are different actions.

   _________________________________________________________________

3. After the two-line removal, may the caller still inspect or reinitialize
   `minus` while its declaring block is active? Explain.

   _________________________________________________________________

4. Count the work. Let `n` be the number of searched nodes and `k` the
   number of nodes in the selected subtree.

| Operation | Work in fields or nodes | Reason |
|---|---|---|
| Initialize one node | | |
| Attach a fresh node to a known empty side | | |
| Search for a missing value | | |
| Clear a subtree | | |
| Detach an already cleared child | | |

Why can a deeper recursive search need more temporary call storage?

____________________________________________________________________

## K. Transfer to a different relationship model

A graph is a more general relationship structure that may allow shared
items or cycles. Give one useful situation where two items should lead to
the same object. Why would our unshared-tree precondition no longer fit?

____________________________________________________________________

## L. Exit ticket

1. What does a child link store? ___________________________________
2. Can the right side be used while the left side is empty? ________
3. Who ensures that no node is shared or part of a cycle? ___________
4. Does clearing a node end its lifetime? __________________________
5. Which link must the caller change to remove a cleared left child?

   _________________________________________________________________
