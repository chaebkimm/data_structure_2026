# Student Textbook - Linked Lists and Disjoint-Set Union

## 1. Separate records, one sequence

A **node** is one separately stored object containing a value and a link. A
**memory address** identifies a storage location. A **pointer** is a C value
that stores an address.

A **singly linked list** connects each node only to the following node. Its
**head** pointer stores the first node's address. Each node's `next` field
stores the following address. `NULL` means that no node follows.

```c
typedef struct LinkedNode {
    int value;
    struct LinkedNode *next;
} LinkedNode;
```

The `*` marks a pointer type. In `node->next`, `->` accesses a field through
a pointer. A **traversal** begins at the head and follows `next` until
`NULL`. Nodes need not be adjacent in memory.

## 2. Build the canonical list

**Push-front** inserts before the current first node. Start with an empty
list whose limit is four. A **limit** is the configured maximum number of
live nodes.

```text
push 31: P(31) -> NULL
push 23: Q(23) -> P(31) -> NULL
push 17: R(17) -> Q(23) -> P(31) -> NULL
```

For one push, request a new node, store its value, point it to the old head,
and make it the new head. Increase the stored node count only after the
allocation succeeds. An **allocation** is storage reserved while a program
runs.

**Ownership** means responsibility for releasing storage. This list owns
every node reached from its head. Its **invariant**, or rule for every valid
state, says:

- the head is `NULL` exactly when the count is zero;
- exactly the counted number of distinct nodes is reached before `NULL`;
- the count does not exceed the limit;
- no link returns to an earlier node; and
- one list object owns the nodes.

Do not make a **shallow copy**, which copies the head address without
copying the nodes. Two apparent owners could release the same allocations.

## 3. Remove without losing the remainder

To remove the first value 23, traversal first reaches R and then Q.

```text
previous = R
victim = Q
successor = P
```

Save Q's successor while Q is alive. Change `R->next` to P. Then call
`free`, the C operation that releases one allocation, on Q and decrease the
count. The result is:

```text
R(17) -> P(31) -> NULL
```

Calling `free(Q)` and then reading `Q->next` is a **use-after-free**: Q's
lifetime already ended. A **dangling pointer** still stores a released
object's old address. A **memory leak** loses the only reachable address of
an allocation that should be released.

Duplicates are allowed, so removal stops at the first match. A missing
value reports false and changes nothing. A full-list push or failed
allocation also changes nothing. This is **failure preservation**.

To **destroy** the list, save the current node's successor, release the
current node, and continue from the saved address. Finally set the head to
`NULL` and set both the count and limit to zero.

## 4. A different relationship problem

Suppose undirected relationship reports arrive one at a time. “Undirected”
means the relationship works in both directions. Repeating a full graph
search after every report wastes work.

A **set** is a collection of distinct items. Sets are **disjoint** when
they share no item. **Disjoint-Set Union (DSU)**, also called
**Union-Find**, maintains disjoint connected groups. It does not store the
original routes.

This DSU supports at most 16 dense IDs. **Dense** means the active IDs are
consecutive numbers beginning at zero. Two arrays store its state:

- `parent[x]` stores the ID followed upward from `x`;
- `component_size[x]` stores a group size only when `x` is a root. A
  **component** is one connected group.

Brackets choose array position `x`. A **root**, or representative, has
itself as parent. A nonroot's component size is zero. Inactive parent
positions contain sentinel 16. A **sentinel** is a reserved marker.

The parent links form a **forest**, meaning several tree-shaped groups.

## 5. Make a set and find its root

**Make-set** creates the next dense ID:

```text
parent[x] = x
component_size[x] = 1
```

**Find** returns an ID's root. The course find is iterative: loops perform
the work instead of recursive self-calls. Its first pass follows at most
the active ID count, rejecting an invalid parent before using it as an
array position.

Its second pass performs **path compression**, redirecting each visited
nonroot to the root. After the seven canonical unions:

```text
parent: [A,A,A,C,A,E,E,G]
```

Finding H follows `H->G->E->A`. Compression produces:

```text
parent: [A,A,A,C,A,E,A,A]
```

C, D, and F were not on that find path, so their links do not change.
Every ID was already in A's group; compression changes shape, not
membership.

## 6. Union by component size

**Union** merges the groups containing two IDs. First find both roots.
**Union by component size** attaches the smaller group below the larger.
If sizes tie, this course attaches the larger root ID below the smaller
root ID. The winner receives the combined size; the loser receives zero.

For IDs A through H, process:

```text
A-B, C-D, A-C, E-F, G-H, E-G, A-E
```

The final root A has size eight:

```text
parent:         [A,A,A,C,A,E,E,G]
component_size: [8,0,0,0,0,0,0,0]
```

The remaining longer paths are intentional examples for later finds.

## 7. Detect a cycle-producing relationship

After finding H, process `union(D,H)`. Find follows `D->C->A` and compresses
D to A. H already points to A. Both roots are A, so union succeeds with
`merged=false`.

For a new undirected relationship, equal roots mean it is
**cycle-producing**. A **cycle** is a route that returns to an earlier ID.
The new D-H relationship closes a route already present; it does not merge
two groups.

Always reject an external ID before indexing either array. Shared DSU
membership means only that processed undirected relationships connect the
IDs. **Authorization** means permission to act. Shared membership is not
authorization or proof of trust. It also does not provide a route, a
shortest path, **resilience**—the ability to continue after failures—or
support for efficient relationship deletion.

## 8. Cost and the forward bridge

Linked-list push-front changes a constant number of fields, so its mutation
core is `O(1)`, read “constant time.” Searching, removal by value,
validation, and destruction are `O(n)`, meaning work can grow with node
count `n`.

DSU make-set is `O(1)`. With path compression and union by size, a long
sequence of finds and unions costs amortized `O(alpha(n))` per operation.
**Amortized** describes the average across a sequence. `alpha` is an
extraordinarily slow-growing function; no derivation is required. A
separate complete validator is not included in that bound.

The supplied pre-lab reads **incident records**, stored descriptions of
relationships touching one endpoint. **Reciprocal** records describe the
same undirected relationship from its two endpoints. The builder converts
them into an **edge list**, one record per logical relationship.
**Parallel edges** are distinct relationships with the same endpoints;
distinct IDs preserve them. A **weight** is a relationship's cost number. A
**relational comparator** tells `qsort`, C's supplied sorting operation,
which record comes first. It uses less-than and greater-than tests, never
subtraction.
**Kruskal's algorithm** is a later method that considers edges cheapest
first to build a minimum-cost connection structure without cycles; it uses
DSU to reject cycle-producing edges. Module 15's **AVL tree**, a search
tree kept height-balanced, will likewise change local links while
preserving a whole-structure rule.
