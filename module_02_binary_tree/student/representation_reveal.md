# Stage B — How the Hierarchy Is Stored

Open this file only when the instructor releases the representation.

**Representation** means a chosen way to store or show information.

## 1. Name the stored pieces

A **data structure** is a planned way to organize information in a program.
An **object** is one stored item that groups related values. A **node** is one
object in a data structure whose objects are connected by stored
relationships. Here, every node stores a number and up to two relationships
to other nodes.

Before reading the C representation, use these new terms:

- A **type** tells C what kind of value is stored and which operations make
  sense for it. `int` is C’s type for whole numbers.
- A **variable** is named storage for a value.
- A **struct** is a C type that groups related variables.
- A **field** is one named variable inside a struct.
- A **key** is the value used to identify or compare a node.
- An **address** is a value that identifies a location in memory.
- A **pointer** is a variable that stores an address.
- `NULL` is a special pointer value meaning “no object here.”
- `typedef` gives a type a shorter name. Here it creates the name `TreeNode`.
- **Self-referential** means that the type contains pointers to its own type.
  A node does not contain two complete child nodes; it contains their
  addresses.

```c
typedef struct TreeNode {
    int key;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;
```

Label each field in your own words:

```text
key:   _____________________________________________________________
left:  _____________________________________________________________
right: _____________________________________________________________
```

## 2. Prepare the storage

An **array** is a numbered row of same-type objects. An **index** is an
object’s numbered position, beginning at zero. An **arena** is a prepared
storage area from which a program uses objects. A **fixed arena** is an array
whose size does not change during the activity.

```c
TreeNode nodes[5] = {
    {50, NULL, NULL},
    {30, NULL, NULL},
    {70, NULL, NULL},
    {20, NULL, NULL},
    {40, NULL, NULL}
};
```

All five nodes are **active**, meaning they belong to the current structure.
The expression `nodes[1]` means the node object at index 1. The expression
`&nodes[1]` means the address of that object.

The **root** is the one starting node. The links are created separately:

```c
TreeNode *root = &nodes[0];

nodes[0].left  = &nodes[1];
nodes[0].right = &nodes[2];
nodes[1].left  = &nodes[3];
nodes[1].right = &nodes[4];
```

The dot in `nodes[0].left` selects a field from a directly named object. The
arrow in `root->left` selects a field by following a pointer. In this example,
`root->left` and `nodes[0].left` read the same field.

## 3. Translate the same state

A **child** is a node directly below another node. Its **parent** is the node
directly above it. The root has no parent. A **leaf** is a node with no
children. A **binary tree** is a hierarchy in which each node has at most two
child positions, named left and right.

The code above is also described by this child-index table. A dash means
“no child,” which becomes `NULL` in C.

| Index | Key | Left child index | Right child index |
|---:|---:|---:|---:|
| 0 | 50 | 1 | 2 |
| 1 | 30 | 3 | 4 |
| 2 | 70 | — | — |
| 3 | 20 | — | — |
| 4 | 40 | — | — |

Text-only description:

- Root index 0, key 50, has left child index 1 and right child index 2.
- Index 1, key 30, has left child index 3 and right child index 4.
- Index 2, key 70, has no children.
- Index 3, key 20, has no children.
- Index 4, key 40, has no children.

The child relationship comes from stored addresses, not from nearby array
positions. Related nodes do not have to be next to one another in memory.

## 4. Who controls the storage?

**Ownership** means responsibility for deciding how long storage remains
usable and when it is released. `free` is a C operation that releases a block
of memory that the program requested separately. The whole `nodes` array owns
the node storage in this activity. An individual address such as `&nodes[3]`
was not obtained as a separate block, so it must not be passed to `free`.

The arena’s **lifetime** is the time during which its storage remains usable.
Every pointer into the arena is usable only during that lifetime.

## 5. Prepare for the Cognitive Pause

Confirm that you can read the table and the four child assignments. Do not
solve possible structural or ordering changes until the pause is released.

One representation question:

____________________________________________________________________
