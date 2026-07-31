# Instructor Answer Key — Module 2

## Macro-Question synthesis

A **hierarchy** arranges objects above or below other objects. A **pointer**
stores the address of another object. A **parent** is directly above a
**child**, so a parent pointer can identify children that are elsewhere in
memory. The **root** is the one starting node. The pointers create a
hierarchy only when all of these rules hold for the completed structure:

1. the root has no parent;
2. every other node has exactly one parent;
3. every node can be reached from the root;
4. no path returns to a node already on that path;
5. every non-`NULL` child address names an active arena node;
6. every node has at most two children; and
7. one node's left and right fields do not name the same child.

If a child may have several parents, links may return backward, or some links
cross branches, the relationships are better modeled as a **graph**, a
collection of objects and less-restricted relationships.

## Stage A inquiry

### Original hierarchy

```text
Security Lab
├── Logs
│   ├── Login Events
│   └── Firewall Events
└── Reports
    ├── Daily Summary
    └── Incident Summary
```

- single starting item: `Security Lab`;
- bottom items: `Login Events`, `Firewall Events`, `Daily Summary`, and
  `Incident Summary`;
- one valid route: `Security Lab → Logs → Login Events`. Any complete route
  from the start to one of the four bottom items is correct.

### Proposed changes

1. Putting `Firewall Events` below both `Logs` and `Reports` gives it two
   immediate items above it. Its one parent is no longer clear, so the result
   is not a pure tree.
2. Linking `Login Events` back to `Security Lab` creates a route that can
   repeat forever and gives the starting item an incoming relationship.
3. Once detached, `Daily Summary` cannot be reached from `Security Lab`.

Any two accurate original rules earn credit: one starting item, no parent for
that start, one parent for every other item, all items reachable from the
start, no returning route, or at most two immediate lower items in this
example.

### Storage brainstorm

- Store an address for each immediate lower item.
- Store `NULL` when a child position is empty.
- Related items need not be adjacent in memory; stored addresses create the
  relationship.
- Open questions vary. Use them to plan pointer, `NULL`, or structural
  support rather than scoring a predicted answer.

## Entry retrieval

1. An ArrayList places values in one contiguous block, meaning one unbroken
   region of memory.
2. A linked relationship stores another object’s address.
3. `NULL` represents the absence of a linked object.
4. The object at the next memory address does not automatically become a
   child. A child pointer must explicitly store its address.
5. An **arena** in this module is one fixed array containing all nodes. It
   avoids resizing, so node addresses remain stable during the exercise.

## Vocabulary checks

- **root:** the one starting node; it has no parent;
- **parent:** a node with a direct link to a child;
- **child:** the node identified by a parent’s left or right pointer;
- **leaf:** a node whose left and right pointers are both `NULL`;
- **path:** a sequence of nodes connected by links;
- **depth:** number of links from the root to a named node;
- **height:** greatest number of downward links from a named node to a leaf;
- **subtree:** a named node and every descendant below it;
- **descendant:** any node below another node, not only a direct child.

For the course convention, a leaf has height zero. The empty-child position
below a leaf is not counted as a node.

## Stage B Cognitive Pause

### Target 1 — Representation

- root key: `50`;
- root left address: `&nodes[1]`;
- root right address: `&nodes[2]`;
- leaf indexes: `2`, `3`, and `4`.

### Target 2 — Structural change

`nodes[3].left = &nodes[0]` uses an in-arena address and an empty local slot,
but the completed result is invalid. Following child links from index `0` to
index `1`, then index `3`, returns to index `0`. This is a cycle. It also
gives the root a parent.

### Target 3 — BST order

Changing index `4` from key `40` to `60` leaves the shape structurally valid
but breaks BST ordering. Index `4` remains inside the entire left subtree of
key `50`, so it must be lower than `50`. The expected status is
`TREE_ERR_NOT_BST`.

Changing index `4` to `50` is also rejected with `TREE_ERR_NOT_BST` because
the course duplicate policy uses strict lower-than and higher-than
comparisons.

## Stage D diagram translation

An **index** is an array position, numbered from zero in C.

| Parent node | Left pointer | Right pointer |
|---|---|---|
| `nodes[0]`, key `50` | `&nodes[1]` | `&nodes[2]` |
| `nodes[1]`, key `30` | `&nodes[3]` | `&nodes[4]` |
| `nodes[2]`, key `70` | `NULL` | `NULL` |
| `nodes[3]`, key `20` | `NULL` | `NULL` |
| `nodes[4]`, key `40` | `NULL` | `NULL` |

`arena.root` is `&nodes[0]`.

## Stage C investigation

### D. Translate three representations

The relationships are:

```text
index 0, key 40
├── left: index 1, key 20
│   ├── left: index 3, key 10
│   └── right: index 4, key 30
└── right: index 2, key 60
```

Pointer completions:

```c
TreeNode *root = &nodes[0];
nodes[0].left  = &nodes[1];
nodes[0].right = &nodes[2];
nodes[1].left  = &nodes[3];
nodes[1].right = &nodes[4];
```

| Expression | Meaning |
|---|---|
| `nodes[1]` | the complete node object at index `1`, with key `20` |
| `&nodes[1]` | the address of that node |
| `nodes[1].right` | the right-child pointer stored in that node; here it is `&nodes[4]` |
| `root->left` | the left-child pointer in the object identified by `root`; here it is `&nodes[1]` |
| `NULL` | no object or no child |

### E. Name and measure positions

1. Path from index `0` to index `4`: `0, 1, 4`.
2. Depth of index `4`: `2`.
3. Leaves: indexes `2`, `3`, and `4`.
4. Height of index `1`: `1`.
5. Height of root: `2`.
6. Subtree rooted at index `1`: indexes `1`, `3`, and `4`.

### F. Structural invariant

The blanks are:

1. `NULL`;
2. `root`;
3. `zero`;
4. `one`;
5. `active`;
6. `reachable`;
7. `cycle`;
8. `child` or `node`.

| Proposed change | Valid tree? | Reason |
|---|---|---|
| No change | yes | All five nodes satisfy the completed-tree rules |
| Index `2` also points to index `4` | no | Index `4` has two incoming parent links |
| Index `3` points back to index `0` | no | A cycle is created and the root receives a parent link |
| Detach index `4` but still call it active | no | Index `4` is unreachable and has no parent |
| Index `2` points to itself | no | The self-link is a one-node cycle |

### G. Fixed-arena reasoning

| Statement | Judgment | Reason |
|---|---|---|
| Store `&nodes[3]` in a child field | memory-safe address, subject to structure validation | The address is inside the live arena; the relationship still needs a valid-tree check |
| Pass `&nodes[3]` to `free` | unsafe | The node was not obtained as a separate allocation |
| Infer a relationship from nearby memory | unsafe reasoning | Pointers, not physical adjacency, define relationships |
| Use a child pointer after arena lifetime | unsafe | The pointer no longer identifies a live object |
| Store an address outside the active arena | not allowed by this tree contract | Merely storing a live outside address is memory-safe, but it is not a valid child and the validator rejects the structure |

Physical position describes where bytes are stored. Logical position
describes the role established by links; therefore neighboring array objects
need not be parent and child.

### H. Local and whole-tree validation

Three examples that escape local checks are:

1. a child already has a parent elsewhere;
2. a longer path returns to an ancestor and forms a cycle;
3. a different active node becomes unreachable.

BST ordering is another whole-tree rule, but it is checked separately from
shape.

A parent-count record detects no-parent, multiple-link, and incoming-root
defects. A `seen` record helps detect repeated or unreachable nodes. An empty
selected slot describes only that slot; it says nothing about links stored
by other nodes.

### I. Global BST rule

Allowed-key descriptions for the Stage B tree:

| Index | Allowed key description |
|---:|---|
| 0 | no ancestor bound |
| 1 | lower than `50` |
| 2 | higher than `50` |
| 3 | lower than `30`, and therefore also lower than `50` |
| 4 | higher than `30` and lower than `50` |

| Independent change | Valid BST? | Reason |
|---|---|---|
| `20` to `25` at index `3` | yes | `25` remains lower than `30` and `50` |
| `40` to `60` at index `4` | no | `60` exceeds the inherited upper bound `50` |
| `40` to `30` at index `4` | no | Strict ordering rejects equality with its parent |
| `70` to `50` at index `2` | no | Strict ordering rejects equality with the root |

Immediate comparison is insufficient because every ancestor can add a lower
or upper limit. The `40`-to-`60` case returns `TREE_ERR_NOT_BST`: its links
still form a valid tree, so `TREE_ERR_INVALID_STRUCTURE` would describe the
wrong kind of defect.

### J. Tree → Graph

Useful shared relationships include one library used by two programs, one
course counted in two degree plans, or one service reached by two processes.
A graph removes the tree’s one-parent restriction and may permit cycles,
cross-links, several routes, and disconnected groups. It records visited
vertices so returning links do not cause endless repeated work.

A representative transfer sentence is:

> A tree is useful when each non-root item belongs in exactly one hierarchical
> position; a graph is needed when shared, crossing, or returning
> relationships are meaningful.

### K. Exit ticket

1. A child field stores an address.
2. `NULL` means no child.
3. The root has no parent; every other node has exactly one incoming parent
   link.
4. Accept one: one parent, reachability, no cycles, in-arena pointers, or BST
   range order.
5. Every left-subtree key is lower and every right-subtree key higher than the
   current key.
6. A duplicate is rejected with `TREE_ERR_NOT_BST` after structure passes.
7. Questions vary and guide the next support.

## Structural invariant cases

An **invariant** is a rule that must hold whenever the completed tree is made
available for use.

| Case | Valid? | Reason |
|---|---|---|
| Five-node example above | yes | One root, one parent for each other node, all reachable, no cycle, at most two children |
| Both `nodes[1].right` and `nodes[2].left` point to `nodes[4]` | no | Node `4` has two parents |
| `nodes[3].left` points to `nodes[0]` | no | The link returns to the root, creating a cycle and giving the root a parent |
| No pointer identifies `nodes[4]` | no | Node `4` is unreachable from the root |
| `arena.root` is `NULL` while `count` is five | no | A nonempty arena has no starting node |
| A child pointer identifies an object outside `arena.nodes` | no | Every non-`NULL` child must identify a node in the arena |
| One node's left and right fields identify the same child | no | The child has two incoming links even though both come from one node |
| Empty arena with `nodes == NULL`, `count == 0`, `root == NULL` | yes | This is the course’s canonical empty-tree state |

The two pointer fields enforce “at most two children” by representation.
They do not enforce any of the other global rules.

## Local function answers

### Checked leaf

A valid request reports true only when:

```c
node->left == NULL && node->right == NULL
```

`tree_node_is_leaf` checks that the node and output pointers are non-`NULL`.
It is a local question and therefore does not prove that the node belongs to
a valid arena. On failure, it does not change the caller’s output value.

### Checked child count

`tree_node_child_count` starts at zero and adds one for each non-`NULL` child
pointer. The only successful results are `0`, `1`, and `2`. Like the leaf
query, it checks its two pointer arguments but does not validate an arena.

### Immediate family

For node index `1`, key `30`, `tree_immediate_family` reports:

- `parent_index = 0`, key `50`;
- `left_child_index = 3`, key `20`;
- `right_child_index = 4`, key `40`.

For root index `0`, key `50`, it reports:

- `parent_index = TREE_NO_INDEX`;
- `left_child_index = 1`, key `30`;
- `right_child_index = 2`, key `70`.

For leaf index `4`, key `40`, it reports:

- `parent_index = 1`, key `30`;
- `left_child_index = TREE_NO_INDEX`;
- `right_child_index = TREE_NO_INDEX`.

Because `TreeNode` has no parent field, finding the parent requires checking
the left and right pointers of arena nodes. If `n` is the number of nodes,
this may inspect up to `n` nodes. `TREE_NO_INDEX` is a special `size_t` value
meaning “no related node.”

### Local child assignment

`tree_assign_child` receives parent and child array indexes plus a
`TreeSide`. It can prove:

- the arena exists;
- both indexes are inside the arena;
- the selected side is left or right;
- the destination child position is available under the course contract;
- the parent is not being assigned directly as its own child.

It cannot by itself prove:

- that the proposed child lacks another parent;
- that the child is not an earlier ancestor;
- that every arena node remains reachable;
- that the keys obey BST order.

Those are whole-tree facts, so the completed candidate must be passed to
`tree_validate_structure` before it is accepted.

## BST preview

A **binary search tree (BST)** is a binary tree with this global rule:

- every key in a node’s entire left subtree is lower than the node’s key;
- every key in its entire right subtree is higher than the node’s key.

“Global” means the rule applies to all descendants, not only direct children.
This course rejects duplicate keys, so both comparisons are strict.

### Valid example

The five-node example is valid. The node with key `40` is in the right
subtree of `30`, so it must be greater than `30`. It is also in the left
subtree of `50`, so it must be lower than `50`. It satisfies the allowable
range `30 < key < 50`.

### Deep violation

```text
10
└── left: 5
    └── right: 12
```

The immediate relation `5 < 10` is correct, and `12 > 5` is correct. The tree
is still not a BST because `12` occurs inside the left subtree of `10`, where
every key must be lower than `10`.

### Duplicate

```text
8
└── right: 8
```

This is rejected. A right-subtree key must be strictly greater than `8`.

`tree_validate_bst` reports `TREE_ERR_NOT_BST` for this duplicate and for the
deep ordering violation. This result says the structure is a valid binary
tree but is not a valid binary search tree. It reports
`TREE_ERR_INVALID_STRUCTURE` instead when the links already violate a tree
rule, such as one-parent or no-cycle.

### Why ranges work

The root begins with no lower or upper restriction beyond the `int` type.
Moving left adds the current key as an exclusive upper limit. Moving right
adds it as an exclusive lower limit. **Exclusive** means the limit itself is
not allowed, which rejects duplicates.

Students need to interpret this supplied validator, not implement or classify
its link-following mechanism in Module 2.

## Operation-cost answers

**Operation cost** describes how the amount of work changes as input grows.
`O(1)` means a fixed amount of work. `O(n)` means work can grow in proportion
to `n`, the node count.

| Operation | Cost | Reason |
|---|---:|---|
| Arena initialization | `O(n)` | It copies `n` keys and clears `n` pairs of links |
| Checked leaf | `O(1)` | It checks two pointer fields |
| Checked child count | `O(1)` | It checks two pointer fields |
| Local child assignment | `O(n)` in the supplied version | Its container check scans up to `n` addresses to confirm that the root belongs to the arena |
| Immediate-family report | `O(n²)` in the supplied version | It first runs structural validation, then scans for the parent |
| Structural validation | `O(n²)` in the supplied version | Each of up to `n` links may require a scan of up to `n` arena addresses |
| BST validation | `O(n²)` in the supplied version | It validates structure and maps child addresses back to indexes |

Do not require students to derive traversal-based proofs yet. It is enough to
connect repeated scans with growing work. The raised `²` means “multiplied by
itself”: `n²` means up to `n × n` comparison opportunities. The course arena
is capped at 32 nodes, favoring clear checks over a more advanced lookup
structure.

## Ownership and lifetime answer

The arena points into an already created array. It is **non-owning**, meaning
it may use that storage but is not responsible for releasing it. Students
must not call `free` on `arena.nodes`, `arena.root`, or any child pointer.

All tree use must stop before the array’s lifetime ends. A **lifetime** is the
period during which an object exists and its address may be used.

## Tree Structure Autopsy

The four links are:

| Parent index | Side | Child index |
|---:|---|---:|
| `0` | left | `1` |
| `0` | right | `2` |
| `1` | left | `3` |
| `2` | right | `3` |

The first three assignments form a valid four-node tree. The fourth
assignment, `nodes[2].right = &nodes[3]`, is the first invalid completed
state because index `3` already has index `1` as a parent.

Each local assignment uses in-range addresses, avoids a direct self-link, and
fills an empty field. Only comparison with other parents reveals the shared
child.

Expected output facts:

- arena slots: `4`;
- branch-count result: `5`;
- times key `40` is encountered: `2`;
- the two printed child addresses for index `3` are equal.

The counting function reaches index `3` once through index `1` and again
through index `2`; it counts routes, not distinct arena nodes.

A pure-tree repair removes either incoming link to index `3` and then requires
`tree_validate_structure(...) == TREE_OK`. A graph is the appropriate later
model if both relationships are meaningful.

Strong regression tests:

1. build the shared-child candidate and require
   `TREE_ERR_INVALID_STRUCTURE`;
2. remove one of the two links, require `TREE_OK`, and confirm that a
   distinct-node count is four.

## Tree → Graph transfer

A tree gives every non-root node exactly one parent and forbids cycles. A
graph permits more general relationships:

- two objects may both link to one shared object;
- a link may cross from one branch to another;
- a path may return to an earlier object;
- some objects may not be reachable from a chosen start.

In graph language, objects are often called **vertices**, and relationships
are called **edges**. Later graph searches need a “visited” record so a cycle
does not cause repeated processing forever.

## Exit-ticket answers

1. A pointer field stores a child’s address; it does not contain the child
   object.
2. `NULL` means the selected child is absent.
3. A local assignment cannot prove one-parent, reachability, cycle, or BST
   rules for the whole structure.
4. Duplicate BST keys are rejected.
5. Arena nodes are never individually freed.
6. Shared or backward relationships motivate a graph.
