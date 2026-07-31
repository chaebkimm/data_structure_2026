# Instructor Technical Notes — Module 2

## Canonical representation

**Canonical** means the one standard form selected by the course.
**Representation** means the stored fields and the rules for interpreting
them. A C `struct` groups related fields inside one object. A **key** is the
integer stored in a node. A **pointer** is a variable storing a memory
address. `NULL` means “no object,” and `size_t` is a nonnegative whole-number
type used for counts and indexes. `bool` is a type whose values are `true`
and `false`.

```c
typedef struct TreeNode {
    int key;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

typedef struct {
    TreeNode *nodes;
    size_t count;
    TreeNode *root;
} TreeArena;
```

A **self-referential structure** is a `struct` containing a pointer to the
same structure type. It cannot directly contain another full `TreeNode`
because that would require an object of unlimited size. A pointer has a fixed
size and can store another node’s address.

`TreeArena` is a view of one fixed node array:

- `nodes` points to its first node;
- `count` is the number of nodes included in the candidate tree;
- `root` is `NULL` for the canonical empty tree or identifies one included
  node.

The arena never resizes. Its node addresses therefore remain stable while the
backing array exists.

## Ownership and lifetime

**Ownership** is responsibility for releasing a resource, such as memory
storage. `TreeArena` does
not own its array; the surrounding fixture owns the array. No node is
separately requested from the C memory manager, so no node, child pointer,
root pointer, or `arena.nodes` pointer is passed to `free`, the C function
that releases requested memory.

A **lifetime** is the period during which an object exists. The arena and all
node pointers must stop being used before the backing array’s lifetime ends.
Using an address after its object has ceased to exist creates a **dangling
pointer**, an address that no longer identifies a live object.

Initialize every node’s `left` and `right` fields to `NULL` before assigning
links. Uninitialized pointer bits must never be inspected as addresses.

Copying `TreeArena` copies only its pointers, not its nodes. Both copies then
refer to the same array, and either copy can change it. Avoid the copy unless
that shared view is intentional and documented.

## Course structural invariant

An **invariant** is a rule that must hold whenever a completed structure is
made available to other code.

Canonical empty tree:

```text
nodes = NULL, count = 0, root = NULL
```

Nonempty tree:

1. `nodes != NULL`;
2. `root` identifies exactly one element at an index from zero through
   `count - 1`;
3. every non-`NULL` child pointer identifies exactly one element of that same
   array;
4. the root has parent count zero;
5. every other node has parent count one;
6. every node is reachable from the root;
7. no cycle exists;
8. every node has at most two children;
9. one node's `left` and `right` fields do not identify the same child.

The two child fields enforce rule 8. They do not enforce rules 2–7 or 9.

A **candidate tree** is a partly built or not-yet-validated structure. It may
temporarily violate the completed-tree invariant. Keep it private until the
supplied validator accepts it. In a system where other code can see the tree
concurrently, build in separate storage or save old links and restore them
after validation failure. **Concurrently** means that more than one activity
could access the data during the same period.

## Course API

An **application programming interface (API)** is the collection of functions
that client code is allowed to call. **Client code** is code that calls these
functions. A **contract** specifies valid input, result, state change, and
failure behavior.

The exact course names and signatures are:

```c
TreeStatus tree_arena_init(
    TreeArena *arena,
    TreeNode *storage,
    const int *keys,
    size_t key_count,
    size_t root_index);

TreeStatus tree_node_is_leaf(
    const TreeNode *node,
    bool *out_is_leaf);

TreeStatus tree_node_child_count(
    const TreeNode *node,
    size_t *out_child_count);

TreeStatus tree_assign_child(
    TreeArena *arena,
    size_t parent_index,
    TreeSide side,
    size_t child_index);

TreeStatus tree_validate_structure(const TreeArena *arena);

TreeStatus tree_immediate_family(
    const TreeArena *arena,
    size_t node_index,
    TreeFamily *out_family);

TreeStatus tree_validate_bst(const TreeArena *arena);
const char *tree_status_name(TreeStatus status);
```

In these declarations, `const` states that the function promises not to
change an object through that particular pointer.

`tree_arena_init` copies `key_count` keys into caller-owned storage, clears
all child pointers, and selects the root by index. `TREE_ARENA_MAX_NODES` is
`32`. The canonical empty call uses a zero key count and
`TREE_NO_INDEX` as the root index. On failure, the arena and storage remain
unchanged.

For `tree_node_is_leaf` and `tree_node_child_count`:

- reject a `NULL` node or output pointer;
- change the output object only on success.

These are deliberately local questions. They inspect the two child addresses
and do not establish arena membership or whole-tree validity.

The family record contains indexes:

```c
typedef struct {
    size_t parent_index;
    size_t left_child_index;
    size_t right_child_index;
} TreeFamily;
```

`TREE_NO_INDEX` means that a relative is absent. Therefore the root’s
`parent_index` is `TREE_NO_INDEX`, as are both child indexes of a leaf.
`tree_immediate_family` first requires
`tree_validate_structure(arena) == TREE_OK`, because an invalid candidate may
not have one clear parent.

`TreeStatus` is a named result code. `TREE_OK` means success; the remaining
values distinguish a bad argument, an out-of-range index, an occupied child
position, a direct self-link, an invalid whole structure, and a tree that
fails BST ordering. `TREE_ERR_INVALID_STRUCTURE` means that the links do not
form a valid rooted binary tree. `TREE_ERR_NOT_BST` means that the links form
a valid tree but a key violates strict BST order or duplicates another key.
`tree_status_name` turns one result code into readable text.
`TreeSide` is a named choice between `TREE_SIDE_LEFT` and
`TREE_SIDE_RIGHT`.

## Arena-membership checking

A node is an arena member only if it equals one exact element address:

```c
node == &arena->nodes[i]
```

Scanning with pointer equality is clear and well-defined for this small fixed
arena. Do not teach a range test such as:

```c
node >= arena->nodes && node < arena->nodes + arena->count
```

Relational pointer comparisons are defined by C only when both pointers refer
within the same array object. A foreign pointer makes that comparison
unsuitable as a general membership validator.

Also reject an arena count greater than the fixture’s documented maximum
before scanning. A **fixture** is prepared test data. The `TreeArena` fields
alone cannot prove that its array truly contains `count` nodes; the
surrounding fixture contract must guarantee that extent.

## Local child assignment

`tree_assign_child` should check:

1. the arena container has a usable fixed array and root;
2. `side` is `TREE_SIDE_LEFT` or `TREE_SIDE_RIGHT`;
3. `parent_index` and `child_index` are lower than `arena->count`;
4. the two indexes differ;
5. the selected child field is `NULL`.

The function fills one empty slot with `&arena->nodes[child_index]`. It does
not clear or replace a link.

The local function must not claim to preserve the global tree invariant. It
cannot know from one parent alone whether the child already has another
parent or is an ancestor. Run the supplied structural validator on the
completed candidate. If editing an already valid tree, save the old child
pointer, assign the candidate link, validate, and restore the old pointer on
failure.

## Supplied structural validator

A **validator** is a function that reports whether stated rules hold. Supply
this implementation; students call it and interpret results.

Suggested internal phases:

1. check the canonical empty/nonempty shape;
2. map `root` and every child pointer to an exact arena index;
3. count incoming parent links for each node;
4. require zero incoming links for the root and exactly one for every other
   node;
5. follow links from the root with a private `seen` array;
6. reject a repeated node and require the reached count to equal `count`.

The `seen` array is **bookkeeping**, extra stored facts used while checking.
Use a documented fixed maximum or caller-supplied **scratch array**, temporary
storage used only while the function runs, so validation does not introduce
resizing. The validator internally follows links, but do not teach a
traversal order or ask students to implement the link-following algorithm in
this module. Later modules organize that work as depth-first search (DFS) and
breadth-first search (BFS), two different rules for choosing which
relationship to follow next.

Parent counts and reachability overlap deliberately:

- parent counts expose shared children and an incoming link to the root;
- reachability exposes disconnected nodes or a disconnected cycle;
- a repeated reached node exposes a cycle or shared path.

The course function returns `TREE_OK` for a valid structure and
`TREE_ERR_INVALID_STRUCTURE` for a rejected structure. Bad function
arguments retain their more specific status where the contract provides one.
Grading should also ask students to identify the violated rule from a
supplied small state.

## Supplied range-based BST validator

A **binary search tree (BST)** is a structurally valid binary tree whose keys
follow a global order. Every left-subtree key must be strictly lower and every
right-subtree key strictly higher. “Strictly” implements the course policy
that duplicate keys are rejected.

Validate structure before validating key order. Otherwise the range check
could follow a cycle forever or process one shared node more than once.

The supplied implementation carries an allowable open range. An **open
range** excludes its endpoints:

```text
lower < node->key < upper
```

- the left child inherits `lower` and receives `node->key` as its upper
  limit;
- the right child receives `node->key` as its lower limit and inherits
  `upper`.

The supplied implementation uses `has_lower_bound` and `has_upper_bound`
flags paired with `int` values. A flag records whether its bound currently
exists. This permits `INT_MIN` and `INT_MAX` as real keys instead of
mistaking either one for “no bound.”

The implementation stores pending node-and-range checks in one fixed local
array. A **pending check** is work recorded now and processed by a later loop
iteration. Do not name or classify its traversal order for students in this
module; formal traversal begins later.

The validator returns:

- `TREE_OK` when structure and ordering both pass;
- `TREE_ERR_INVALID_STRUCTURE` when the tree-link rules fail;
- `TREE_ERR_NOT_BST` when the link structure is valid but a range or
  duplicate-key check fails.

Do not weaken the check to immediate-child comparisons. The tree
`10 -> left 5 -> right 12` passes both immediate comparisons but violates the
root’s upper limit in the left subtree.

## Complexity language

**Time complexity** describes how work grows as input size grows. Let `n` be
the number of arena nodes.

- reading two child fields is constant work, written `O(1)`;
- `tree_node_is_leaf` and `tree_node_child_count` are `O(1)`;
- mapping one address back to an arena index is `O(n)`;
- `tree_assign_child` is `O(n)` in the supplied version because its container
  check confirms the root's arena membership with that scan;
- finding a parent without a parent field is `O(n)`;
- the supplied structural validator is `O(n²)` because up to `n` child links
  may each require an address-to-index scan of up to `n` nodes;
- `tree_immediate_family` and `tree_validate_bst` are also `O(n²)` because
  each first validates structure.

**Space complexity** describes extra storage. The structural validator’s
parent-count and seen arrays use `O(n)` extra storage. Keep this explanation
informal; formal traversal analysis returns later.

The raised `²` means “multiplied by itself.” The fixed maximum of 32 nodes
keeps the simple equality scans bounded and beginner-readable.

## Testing priorities

Public tests should include:

- canonical empty arena;
- one-node leaf;
- node with only a left child;
- node with only a right child;
- node with two children;
- `NULL` arguments;
- unchanged output after a rejected query;
- invalid `TreeSide`;
- parent or child index equal to `count`;
- occupied child slot;
- direct self-link rejection;
- root immediate family;
- non-root immediate family.

Instructor structural tests should include:

- valid five-node tree;
- root outside arena;
- child outside arena;
- shared child;
- incoming link to root;
- self-cycle and deeper cycle;
- unreachable node;
- disconnected cycle;
- count/root mismatches.

BST tests should include:

- empty tree under the chosen contract;
- one node with `INT_MIN` or `INT_MAX`;
- valid balanced and skewed examples;
- immediate violation;
- deep violation;
- duplicate at the root and duplicate deeper in the tree.

BST tests should assert `TREE_ERR_NOT_BST` for ordering and duplicate
failures, not the broader `TREE_ERR_INVALID_STRUCTURE`.

The reference solution should compile with warnings enabled. A warning is a
compiler message about code that may be mistaken even when compilation can
continue.

## Deferred topics

Explicitly defer:

- named orders for visiting tree nodes: preorder, inorder, and postorder;
- DFS and BFS;
- recursive student implementations;
- dynamic allocation, which requests memory while a program runs, for
  individual nodes;
- freeing a tree;
- BST insertion and search implementation;
- tree-balancing changes, later called rotations and AVL balancing.

These are later returns in the spiral. The Module 2 BST is a recognition and
validation preview only.

## Tree → Graph transfer

Make the bridge explicit:

| Tree rule | What a graph may allow |
|---|---|
| One root | Any chosen starting vertex, or none |
| One parent for each non-root node | Several incoming relationships |
| No cycles | Cycles |
| Every node reachable from root | Disconnected groups |
| Left/right child roles | A general collection of neighboring vertices |

A **vertex** is a graph object. An **edge** is a graph relationship. Once
cycles are allowed, later search code needs a visited record to avoid
processing the same vertex repeatedly.

## Instructor validation checklist

- [ ] Every new term is explained on first use.
- [ ] Every visual has a text equivalent.
- [ ] Fixed arena use contains no allocation or `free`.
- [ ] Node addresses remain stable because no resize occurs.
- [ ] Local assignment is not presented as global validation.
- [ ] Structural validator is supplied, not student-implemented.
- [ ] BST validator checks inherited ranges and rejects duplicates.
- [ ] No formal traversal is required.
- [ ] Public tests and written contracts agree.
- [ ] The final prompt explicitly transfers tree restrictions into graph
      possibilities.
