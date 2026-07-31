# Stage C — Investigation Worksheet: Tree Rules and BST Ordering

Name: ____________________________  
Date: ____________________________

Open this file after completing and preserving the Cognitive Pause.

## Quick reference

An **object** is one stored item that groups related values. A **node** is one
object in the tree. A **key** is its stored number. An **array** is a numbered
row of matching objects, and an **index** is an array position beginning at
zero. An **address** identifies a memory location, and a **pointer** stores an
address. A **field** is one named value inside an object. A **type** describes
the kind of value C stores; `TreeNode` is the C name for the node type used
here. A **parent** is directly above a node; a
**child** is directly below it. The **root** is the one starting node. A
**leaf** has no children. A **binary tree** gives each node at most two child
positions, named left and right. `NULL` is the pointer value meaning “no
object here.” In C, `&nodes[i]` means the address of index `i`, the dot
selects a field from a directly named node, and the arrow selects a field by
following a pointer.

## D. Translate among three representations

The same binary tree can appear as a drawing, a child-index table, or C
pointers. A **representation** is a chosen way to store or show information.

Given:

| Index | Key | Left child index | Right child index |
|---:|---:|---:|---:|
| 0 | 40 | 1 | 2 |
| 1 | 20 | 3 | 4 |
| 2 | 60 | — | — |
| 3 | 10 | — | — |
| 4 | 30 | — | — |

1. State or draw every parent-to-child relationship.

   _________________________________________________________________

2. Complete the pointer assignments:

```c
TreeNode *root = _________________________________________________;
nodes[0].left  = _________________________________________________;
nodes[0].right = _________________________________________________;
nodes[1].left  = _________________________________________________;
nodes[1].right = _________________________________________________;
```

3. Explain each expression:

| Expression | Meaning |
|---|---|
| `nodes[1]` | |
| `&nodes[1]` | |
| `nodes[1].right` | |
| `root->left` | |
| `NULL` | |

## E. Name and measure positions

A **path** is a sequence of connected nodes. An **ancestor** is a node above
another node on a path; a **descendant** is a node below it. **Depth** is the
number of links from the root to a node. The root has depth 0. **Height** is
the greatest number of downward links from a node to a leaf. A leaf has
height 0. A **subtree** is one node together with all its descendants.

Use the table in section D.

1. Write the path from index 0 to index 4. __________________________
2. Give the depth of index 4. ______________________________________
3. List every leaf index. __________________________________________
4. Give the height of index 1. ____________________________________
5. Give the height of the root. ___________________________________
6. List the indexes in the subtree rooted at index 1. ______________

## F. State the structural invariant

An **invariant** is a rule that must be true in every valid state. For this
module, an **active node** is an arena node that is claimed as part of the
current tree. A node is **reachable** when repeatedly following child links
from the root can arrive at it. A **cycle** is a route that follows links and
returns to a node already on that same route. A **structurally valid tree**
follows every shape rule below. A **malformed tree** breaks at least one of
those rules.

Complete the binary-tree structural invariant:

1. If there are no active nodes, the root pointer is __________________.
2. A nonempty tree has exactly one active __________________ node.
3. The root has __________________ parents.
4. Every other active node has exactly __________________ parent.
5. Every child pointer is `NULL` or points to an __________________
   node inside the arena.
6. Every active node is __________________ from the root.
7. No child-link route contains a __________________.
8. A node’s left and right fields cannot name the same ______________.

Each case below begins with the valid five-node tree from Stage B. Classify
the proposed change independently.

| Proposed change | Valid tree? | Whole-tree reason |
|---|---|---|
| No change | | |
| Set `nodes[2].left = &nodes[4]` while index 4 remains the right child of index 1 | | |
| Set `nodes[3].left = &nodes[0]` | | |
| Set `nodes[1].right = NULL` but still call index 4 active | | |
| Set `nodes[2].left = &nodes[2]` | | |

## G. Reason about the fixed arena

The **fixed arena** is the pre-created array `TreeNode nodes[5]`. “Fixed”
means that this array is not resized during the activity. A **contract** is
the set of rules that code promises to follow. `free` is a C operation that
releases a separately requested memory block. **Lifetime** means the time
during which storage remains usable.

Mark each statement safe or unsafe, then explain.

| Statement | Safe or unsafe? | Reason |
|---|---|---|
| Store `&nodes[3]` in a child field | | |
| Pass `&nodes[3]` to `free` | | |
| Assume index 2 is a child of index 1 because the two objects are nearby in memory | | |
| Use a child pointer after the whole arena’s lifetime has ended | | |
| Store an address outside the active part of the arena as a child | | |

**Physical position** means where an object is stored in memory. **Logical
position** means the role created by links, such as “left child of the root.”
In one sentence, explain why physical neighbors need not be logical
parent and child:

____________________________________________________________________

## H. Compare local and global validation

**Validation** means checking whether stated rules are true. A **validator**
is code that performs validation. A local validator checks one node and its
immediate fields. A global validator checks the whole tree.

Before assigning a child, a local validator can check:

- the parent address is inside the active arena;
- the child address is inside the active arena;
- the chosen child field is `NULL`; and
- the parent and child are not the same node.

Name three violations that can still escape those local checks:

1. _________________________________________________________________
2. _________________________________________________________________
3. _________________________________________________________________

**Bookkeeping** means extra recorded facts used to complete a task. A
whole-tree validator may keep a parent count for each arena index and a
`seen` mark showing whether a node has already been reached.

What can a parent count detect? ____________________________________

What can a `seen` mark help detect? _________________________________

Why can “the selected child slot is empty” never prove that the whole result
is a valid tree?

____________________________________________________________________

## I. Apply the global BST rule

A **binary search tree (BST)** is a binary tree with this global rule at every
node:

- every key in its left subtree is smaller than its key;
- every key in its right subtree is larger than its key.

The course rejects duplicate keys. **Reject** means report that the operation
cannot be completed and leave the tree unchanged. A **bound** is a limit a key
must stay below or above. Ancestors create bounds for every descendant.

Structural validity and BST ordering are different checks. Here, **shape**
means the pattern made by child links. A **status code** is a named result
that reports success or a kind of failure:

- `TREE_ERR_INVALID_STRUCTURE` means the shape is malformed.
- `TREE_ERR_NOT_BST` means the shape is a valid tree, but its keys break BST
  ordering or the no-duplicate rule.

Every case below keeps the links unchanged. Its shape therefore remains
structurally valid; classify its BST ordering separately.

For the Stage B tree, complete the allowed-key descriptions:

| Index | Position | Allowed key description |
|---:|---|---|
| 0 | root | no ancestor bound |
| 1 | left of key 50 | less than 50 |
| 2 | right of key 50 | |
| 3 | left of key 30, inside key 50’s left subtree | |
| 4 | right of key 30, inside key 50’s left subtree | |

Classify each independent key change:

| Change | Valid BST? | Reason |
|---|---|---|
| Change index 3 from 20 to 25 | | |
| Change index 4 from 40 to 60 | | |
| Change index 4 from 40 to 30 | | |
| Change index 2 from 70 to 50 | | |

Why is comparing a node only with its immediate parent insufficient?

____________________________________________________________________

For the change from 40 to 60, which status code should the BST validator
return, and why is `TREE_ERR_INVALID_STRUCTURE` the wrong result?

____________________________________________________________________

## J. Transfer from Tree to Graph

A **graph** is a general relationship structure. Its objects are called
**vertices**, and its links are called **edges**. Unlike a tree, a graph may
allow a vertex to have several **incoming relationships**, meaning several
links that point toward it. A graph may also contain cycles and several
possible routes to the same vertex.

1. The shared-child case in section F is invalid as a pure tree. What useful
   real situation might require one item to be linked from two places?

   _________________________________________________________________

2. Which tree-specific rules would a graph have to remove or replace?

   _________________________________________________________________

3. Why would a graph-searching program need to remember which vertices it
   has already reached?

   _________________________________________________________________

Complete the transfer sentence:

> A tree is useful when ____________________________________________;
> a graph is needed when __________________________________________.

## K. Exit ticket

1. A child field stores the child object or its address? ______________
2. What value means “no child”? ____________________________________
3. State the one-parent rule. ______________________________________
4. Give one rule that requires global validation. ____________________
5. State the full BST left/right rule. _______________________________
6. What happens when a duplicate key is requested? __________________
7. One question you still have: ____________________________________
