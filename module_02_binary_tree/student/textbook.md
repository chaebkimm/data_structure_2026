# Student Notes — Storing Items Above and Below Other Items

## Essential question

> How can one stored item identify items below it, and what rules keep those
> relationships organized?

## 1. One hierarchy

Suppose five numbered items must be arranged in levels. A hierarchy places
items above or below other items. One stored item in our hierarchy is a node,
and its stored number is its key.

```text
50
├─ left: 30
│  ├─ left: 20
│  └─ right: 40
└─ right: 70
```

The companion tree-model file contains a diagram and an exact text
equivalent.

A nonempty tree has one starting node called the root. Here, key 50 is the
root. A parent is directly above a node, and a child is directly below one.
Key 30 is the parent of keys 20 and 40. A leaf has no children, so keys 20,
40, and 70 are leaves.

A binary tree gives every node at most two child positions: left and right.
The positions have different names even when a node has only one child.

## 2. Reading the tree

A path is a list of nodes joined by child links. One path is:

```text
50 → 30 → 40
```

Depth counts links from the root to a node. Key 40 has depth 2. Height counts
the greatest number of downward links from a node to a leaf. The root has
height 2.

An ancestor is a node above another node on a path. Keys 50 and 30 are
ancestors of key 40. A subtree is one node together with every node below it.
The subtree starting at key 30 contains keys 30, 20, and 40.

## 3. The same tree in memory

An array is a numbered row of matching items. An index is one array
position; C begins with index 0. Suppose C stores this array under the name
`nodes`.

| Index | Key | Left-child index | Right-child index |
|---:|---:|---:|---:|
| 0 | 50 | 1 | 2 |
| 1 | 30 | 3 | 4 |
| 2 | 70 | none | none |
| 3 | 20 | none | none |
| 4 | 40 | none | none |

An address identifies a location in memory. A pointer stores an address.
`NULL` is a special pointer value meaning “no stored item.”

The root pointer stores `&nodes[0]`. Read that expression as “the address of
the node at index 0.” A field is one named part of a stored node. The root's
left and right fields store `&nodes[1]` and `&nodes[2]`. Every missing child
field stores `NULL`.

Read the following C code for its field meanings. You do not need to memorize
the syntax yet.

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

A `struct` groups named fields. A type describes the kind of value C stores.
The words `typedef ... TreeNode` tell C to use `TreeNode` as this type's
short name.

- `int key` stores a whole number.
- The `*` in `TreeNode *` marks a pointer. `left` and `right` store child
  addresses, not complete child nodes.
- An arena is prepared storage for items. `nodes` points to the first node
  in this module's fixed array.
- `size_t` is a nonnegative whole-number type. `count` records how many
  array nodes belong to the arena.
- `root` stores the starting node's address, or `NULL` for an empty tree.

The fixed array does not resize. Its node addresses therefore remain stable
while the array exists.

The array order does not create tree relationships. The stored child
pointers do. For example, indexes 3 and 4 are next to each other in memory,
but neither is the other's parent.

## 4. Representation invariant

When `count` is greater than zero, an active node is any element from
`nodes[0]` through `nodes[count - 1]`. When `count` is zero, there are no
active nodes. A node is reachable when starting at the root and following
child pointers can arrive at it. A cycle is a path that returns to a node
already on that path.

An invariant is a rule that must be true in every valid completed tree.

The empty tree has `nodes == NULL`, `count == 0`, and `root == NULL`. A valid
nonempty course tree satisfies:

1. `nodes` is not `NULL`, and `root` points to exactly one active node.
2. The root has no parent.
3. Every other active node has exactly one parent.
4. Every child field is `NULL` or exactly equals `&nodes[i]` for an active
   index `i`.
5. Every active node is reachable from the root.
6. No path contains a cycle.
7. Every node has at most two children, stored in `left` and `right`.
8. One node's left and right fields do not point to the same child.

The five-node example passes every rule. Small changes show why whole-tree
rules matter:

In `nodes[3].left`, the dot selects the `left` field of the node at index 3.

- `nodes[3].left = &nodes[0]` creates the cycle
  `50 → 30 → 20 → 50` and gives the root a parent.
- Pointing both key 30 and key 70 to key 40 gives key 40 two parents.
- Clearing the link from key 30 to key 40 leaves active node 40 unreachable.

A candidate is a structure still being built and not yet approved. A
candidate may temporarily have unreachable nodes. Validate it before calling
it a completed tree.

## 5. Local operations and whole-tree checks

A function is a named block of code that performs one task. A validator is a
function that checks stated rules. A contract states what a function accepts,
changes, reports, and preserves. An output is an answer written into a
variable supplied by the caller—the code that asked the function to run.

`TreeSide` names the left and right choices. `TreeStatus` names success or a
kind of failure. A status code is one of these named results.
`TREE_NO_INDEX` means that a requested parent or child is absent.

| Function | Successful effect | Failure promise |
|---|---|---|
| `tree_arena_init` | Copies keys, clears child links, and selects the root | Leaves the arena and storage unchanged |
| `tree_node_is_leaf` | Reports whether both child fields are `NULL` | Leaves its output unchanged |
| `tree_node_child_count` | Reports 0, 1, or 2 non-`NULL` children | Leaves its output unchanged |
| `tree_assign_child` | Fills one empty left or right child field | Leaves the arena unchanged |
| `tree_immediate_family` | Reports parent, left-child, and right-child indexes | Leaves its output unchanged |
| `tree_validate_structure` | Reports whether every tree invariant holds | Does not change the tree |
| `tree_validate_bst` | Reports whether structure and key ordering both hold | Does not change the tree |
| `tree_status_name` | Returns readable text for a status code | Returns readable text for an unknown status value |

`tree_assign_child` performs a local check: it checks that the arena and root
are usable, then checks the requested indexes, side, empty child position,
and whether a node would become its own child before changing one pointer.
Success does not prove that the child lacks another parent or that a longer
cycle is absent.

`tree_validate_structure` performs a whole-tree check. Students call this
supplied validator after assigning all links; they do not implement its
node-visiting steps in this module. `tree_immediate_family` also requires a
valid tree. Nodes store no parent pointer, so the function examines arena
links to find the parent. For index 1 in the running example, it reports
parent index 0, left-child index 3, and right-child index 4.

## 6. Binary search tree seed

A binary search tree, shortened to BST, adds a global key-ordering rule.
Global means that the rule applies to entire subtrees:

- every key in a node's entire left subtree is lower than that node's key;
- every key in its entire right subtree is higher.

The five-node example is a BST. Key 40 is higher than 30 and, because it is
inside key 50's left subtree, also lower than 50.

Changing key 40 to 60 passes the immediate comparison with parent 30 but
breaks the limit inherited from root 50. Changing it to 50 creates a
duplicate key. The course uses strict ordering, so equal keys are rejected.

Tree shape and BST ordering are separate:

- `TREE_ERR_INVALID_STRUCTURE` means the links do not form a valid tree.
- `TREE_ERR_NOT_BST` means the links form a valid tree, but a key breaks the
  ordering rule.

The supplied BST validator carries lower and upper limits through the tree.
Students trace those limits, but formal traversal—a planned procedure for
visiting nodes—waits for a later module. Students recognize and validate BSTs
here. Later modules teach procedures for visiting nodes, finding keys, adding
nodes, and reorganizing uneven trees.

## 7. Operation costs

Time complexity describes how work grows. Let `n` mean the active node count:

- `O(1)` means a fixed amount of work;
- `O(n)` means work may grow with the node count;
- `O(n²)` means up to `n × n` work.

| Operation in the supplied code | Cost | Reason |
|---|---:|---|
| Leaf or child-count query | `O(1)` | Reads two child fields |
| Arena initialization | `O(n)` | Copies keys and clears links |
| Local child assignment | `O(n)` | Checking that the root is an exact array element may scan the array |
| Structural validation | `O(n²)` | Child-address checks may each scan the array |
| Immediate-family or BST validation | `O(n²)` | Each first validates the structure |

The fixed limit of 32 nodes keeps these scans bounded, meaning they never
exceed the stated maximum. The growth categories still help us compare
designs.

## 8. Arena safety and tree-to-graph connection

The caller creates the fixed node array. `TreeArena` borrows it; it does not
own it. The node addresses remain stable only while that array exists.

This module does not use `malloc` to request a memory block, `realloc` to
resize such a block, or `free` to release it. Never pass one element address
such as `&nodes[2]` to `free`.

A graph is a more general collection of items and relationships. Its items
are called vertices and its direct relationships are called edges.
Two vertices linking to the same vertex, or a link returning to an earlier
vertex, breaks the course tree invariant, but a graph may allow both.

The numbers in this example are synthetic, meaning invented for safe
teaching. They do not describe a live computer hierarchy.

## 9. Vocabulary

- **binary tree:** a hierarchy with at most two child positions per node;
- **root:** the one starting node in a nonempty tree;
- **leaf:** a node with no children;
- **pointer:** a value that stores a memory address;
- **arena:** prepared fixed storage for this module's nodes;
- **reachable:** able to be reached from the root by following child links;
- **cycle:** a path that returns to a node already on that path;
- **invariant:** a rule every valid completed structure must satisfy;
- **BST:** a binary tree with strict lower-left and higher-right key order;
- **validator:** a function that checks stated rules.

**Key sentence:** child pointers create the shape, but only whole-tree rules
prove that the shape is a valid tree.
