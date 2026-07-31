# Stage C — Investigation Worksheet: Linear Accessible Format

## How to use this version

This version has the same targets as the standard investigation. It avoids
response tables, drawing requirements, and long blank lines. It is suitable
for a **screen reader**—software that reads on-screen text aloud—keyboard
navigation, speech input, or a response containing only text.

Open it after completing and preserving the Cognitive Pause.

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

A **representation** is a chosen way to store or show information. The same
binary tree can appear as a spoken description, a child-index list, or C
pointers.

Use these facts:

1. Index 0 has key 40, left child index 1, and right child index 2.
2. Index 1 has key 20, left child index 3, and right child index 4.
3. Index 2 has key 60 and no children.
4. Index 3 has key 10 and no children.
5. Index 4 has key 30 and no children.

### D1. Relationships

State every parent-to-child relationship.

Response:

### D2. Root pointer

Complete `TreeNode *root =` with the address of the root.

Response:

### D3. Child pointers from index 0

State the assignments for the left and right fields of `nodes[0]`.

Response:

### D4. Child pointers from index 1

State the assignments for the left and right fields of `nodes[1]`.

Response:

### D5. Expression meanings

Explain `nodes[1]`.

Response:

Explain `&nodes[1]`.

Response:

Explain `nodes[1].right`.

Response:

Explain `root->left`.

Response:

Explain `NULL`.

Response:

## E. Name and measure positions

A **path** is a sequence of connected nodes. An **ancestor** is a node above
another node on a path; a **descendant** is a node below it. **Depth** is the
number of links from the root to a node. The root has depth 0. **Height** is
the greatest number of downward links from a node to a leaf. A leaf has
height 0. A **subtree** is one node together with all its descendants.

### E1. Path

State the path from index 0 to index 4.

Response:

### E2. Depth

Give the depth of index 4.

Response:

### E3. Leaves

List every leaf index.

Response:

### E4. Height of index 1

Give the height of index 1.

Response:

### E5. Height of the root

Give the height of index 0.

Response:

### E6. Subtree

List the indexes in the subtree rooted at index 1.

Response:

## F. State the structural invariant

An **invariant** is a rule that must be true in every valid state. An
**active node** is an arena node claimed as part of the current tree. A node
is **reachable** when following child links from the root can arrive at it. A
**cycle** is a route that follows links and returns to a node already on that
same route. A **structurally valid tree** follows every shape rule below. A
**malformed tree** breaks at least one of those rules.

### F1. Complete the rules

Complete these eight statements:

1. If there are no active nodes, the root pointer is blank.
2. A nonempty tree has exactly one active blank node.
3. The root has blank parents.
4. Every other active node has exactly blank parent.
5. Every child pointer is `NULL` or points to an active node inside the arena.
6. Every active node is blank from the root.
7. No child-link route contains a blank.
8. A node’s left and right fields cannot name the same blank.

Response:

Each scenario below starts again from the valid five-node Stage B tree.

### F2. Base state

Classify the unchanged tree and explain.

Response:

### F3. Shared child

Index 4 remains the right child of index 1. The program also sets index 4 as
the left child of index 2. Classify the result and explain the whole-tree
rule involved.

Response:

### F4. Link back to the root

The program sets the left child of index 3 to index 0. Classify the result and
explain.

Response:

### F5. Active but unreachable

The program removes the link from index 1 to index 4 but still calls index 4
active. Classify the result and explain.

Response:

### F6. Self-link

The program sets the left child of index 2 to index 2 itself. Classify the
result and explain.

Response:

## G. Reason about the fixed arena

The **fixed arena** is the pre-created array `TreeNode nodes[5]`. “Fixed”
means this array is not resized during the activity. A **contract** is the
set of rules that code promises to follow. `free` is a C operation that
releases a separately requested memory block.

### G1. Arena child address

Is storing `&nodes[3]` in a child field safe under the course contract?
Explain.

Response:

### G2. Releasing one arena node

Is passing `&nodes[3]` to `free` safe? Explain.

Response:

### G3. Nearby memory

May the program assume index 2 is a child of index 1 merely because the
objects are nearby in memory? Explain.

Response:

### G4. Ended lifetime

Is it safe to use a child pointer after the whole arena’s lifetime has ended?
The **lifetime** is the time during which storage remains usable.

Response:

### G5. Outside address

Is an address outside the active part of the arena a valid child under this
module’s contract? Explain.

Response:

### G6. Physical and logical position

**Physical position** means where an object is stored in memory. **Logical
position** means the role created by links, such as “left child of the root.”
Explain why physical neighbors need not be logical parent and child.

Response:

## H. Compare local and global validation

**Validation** means checking whether stated rules are true. A **validator**
is code that performs validation. A local validator checks one node and its
immediate fields. A global validator checks the whole tree.

A local validator checks that both addresses are inside the active arena,
that the selected child field is `NULL`, and that the parent and child are
different nodes.

### H1. Escaping violations

Name three whole-tree violations that can still escape those local checks.

First violation:

Second violation:

Third violation:

### H2. Parent count

**Bookkeeping** means extra recorded facts used to complete a task. What can a
stored parent count for each index detect?

Response:

### H3. Seen mark

A `seen` mark records whether the validator has already reached a node. What
can this mark help detect?

Response:

### H4. Limits of an empty-slot check

Why can “the selected child slot is empty” never prove that the whole result
is a valid tree?

Response:

## I. Apply the global BST rule

A **binary search tree (BST)** is a binary tree in which every key in a
node’s left subtree is smaller than that node’s key and every key in its
right subtree is larger. This course rejects duplicate keys. **Reject** means
report that the request cannot be completed and leave the tree unchanged. A
**bound** is a limit a key must stay below or above. Ancestors create bounds
for descendants.

Structural validity and BST ordering are different checks. Here, **shape**
means the pattern made by child links. A **status code** is a named result
that reports success or a kind of failure.

- `TREE_ERR_INVALID_STRUCTURE` means the shape is malformed.
- `TREE_ERR_NOT_BST` means the shape is a valid tree, but its keys break BST
  ordering or the no-duplicate rule.

Every key-change scenario below keeps the links unchanged. Its shape remains
structurally valid; classify its BST ordering separately.

Use the Stage B tree: root key 50; left child key 30; right child key 70; key
20 is left of key 30; and key 40 is right of key 30.

### I1. Bound for key 70

Describe the allowed keys at index 2.

Response:

### I2. Bound for key 20

Describe the ancestor bounds at index 3.

Response:

### I3. Bound for key 40

Describe the ancestor bounds at index 4.

Response:

### I4. Change 20 to 25

Classify this independent change and explain.

Response:

### I5. Change 40 to 60

Classify this independent change and explain.

Response:

### I6. Change 40 to 30

Classify this independent change and explain the duplicate policy.

Response:

### I7. Change 70 to 50

Classify this independent change and explain the duplicate policy.

Response:

### I8. Immediate comparison

Why is comparing a node only with its immediate parent insufficient?

Response:

### I9. Correct failure result

For the change from 40 to 60, which status code should the BST validator
return, and why is `TREE_ERR_INVALID_STRUCTURE` the wrong result?

Response:

## J. Transfer from Tree to Graph

A **graph** is a general relationship structure. Its objects are called
**vertices**, and its links are called **edges**. Unlike a tree, a graph may
allow a vertex to have several **incoming relationships**, meaning several
links that point toward it. A graph may contain cycles and may provide
several routes to the same vertex.

### J1. Useful sharing

The shared-child case is invalid as a pure tree. Give a useful real situation
in which one item must be linked from two places.

Response:

### J2. Rules that change

Which tree-specific rules would a graph have to remove or replace?

Response:

### J3. Remembering reached vertices

Why would a graph-searching program need to remember which vertices it has
already reached?

Response:

### J4. Transfer sentence

Complete: “A tree is useful when ...; a graph is needed when ...”

Response:

## K. Exit ticket

### K1. Child field

Does a child field store the child object or its address?

Response:

### K2. No child

What pointer value means “no child”?

Response:

### K3. Parent rule

State the one-parent rule.

Response:

### K4. Global check

Give one rule that requires global validation.

Response:

### K5. BST rule

State the full BST left/right rule.

Response:

### K6. Duplicate

What happens when a duplicate key is requested?

Response:

### K7. Open question

What question do you still have?

Response:
