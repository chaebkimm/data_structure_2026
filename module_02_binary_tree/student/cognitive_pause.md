# Stage B — Five-Minute Cognitive Pause

Read the starting state and definitions with the instructor before timing
begins. When the instructor starts the timer, use no notes, slides, neighbors,
or coding tools for five minutes. You may draw, type, dictate, or respond in
numbered sentences.

An approved extended-time or asynchronous version uses the same starting
state and the same three targets. Speed, handwriting, and drawing quality are
not assessed. Preserve your initial response when correction begins.

## Starting state

An **array** is a numbered row of matching stored items. A **node** is one
stored item in the tree, and `nodes` is the five-node array below. An
**index** is a numbered array position beginning at zero. A **key** is the
number stored in a node for identification or comparison. A **child** is a
node directly below another node. An **address** identifies a location in
memory, and a **child field** stores a child’s address. `NULL` means “no
child,” and a dash below represents `NULL`.

| Index | Key | Left child index | Right child index |
|---:|---:|---:|---:|
| 0 | 50 | 1 | 2 |
| 1 | 30 | 3 | 4 |
| 2 | 70 | — | — |
| 3 | 20 | — | — |
| 4 | 40 | — | — |

Text-only equivalent:

- Index 0 has key 50 and children 1 and 2.
- Index 1 has key 30 and children 3 and 4.
- Indexes 2, 3, and 4 have no children.
- The root pointer stores `&nodes[0]`. A **pointer** stores a memory address,
  and the **root** is the one starting node.

A **leaf** is a node with no children.

In the C expressions below, `&nodes[i]` means “the address of the node at
index `i`,” and the dot selects a named field inside a directly named node.

## Complete exactly three targets

### Target 1 — Translate the representation

State:

- the key stored at the root;
- the two addresses stored in the root’s child fields; and
- all leaf indexes.

Response:

____________________________________________________________________

### Target 2 — Test a structural change

A **local check** examines only the node being changed and its immediate
fields. A **global check** examines the whole structure. A structurally valid
tree has one root with no **parent**, meaning no node directly above it.
Every other node has exactly one parent, every node can be reached from the
root, and no child-link route forms a **cycle** by returning to an earlier
node on that route.

Suppose the program performs:

```c
nodes[3].left = &nodes[0];
```

The left field at index 3 was empty. Is checking that empty field enough to
prove that the whole result is still a tree? Classify the result and name one
whole-tree rule that it follows or breaks.

Response:

____________________________________________________________________

### Target 3 — Test global search ordering

A **binary tree** is a tree with at most two child positions per node. A
**binary search tree**, shortened to **BST**, is a binary tree with a global
key rule: every key anywhere in a node’s left **subtree** is smaller than the
node’s key, and every key anywhere in its right subtree is larger. A subtree
is a node together with everything below it. This course rejects
**duplicates**, meaning a key already present cannot be added again.

Structural validity and BST ordering are separate checks. **Shape** means the
pattern made by the child links. **Malformed** means that the shape breaks a
structural tree rule. A **validator** is code that checks rules. The course
validator reports `TREE_ERR_INVALID_STRUCTURE` for a malformed shape. A
structurally valid tree whose keys break BST ordering reports
`TREE_ERR_NOT_BST`. A **status code** is a named result that tells whether a
check succeeded or why it failed.

Keep every link unchanged but replace the key at index 4 with `60`. Decide
whether the result is a valid BST even though 60 is larger than its immediate
parent’s key, 30. Also state whether replacing it with another `50` would be
accepted under the course duplicate rule.

Response:

____________________________________________________________________

## Calibration

When the instructor reveals the expert model:

1. preserve your initial response;
2. place a check beside reasoning that remains correct;
3. label each correction `address`, `structure`, or `ordering`; and
4. finish the sentence below.

Correction:

____________________________________________________________________

The evidence that changed my model was:

____________________________________________________________________
