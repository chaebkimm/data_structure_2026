# Stage B - Formal Names and Representations

Open this file only after preserving Stage A.

## 1. Name the record structure

A **memory address** identifies a storage location. A **pointer** is a C
value that stores an address. A **node** is one separately allocated object
containing a value and a link.

A **singly linked list** is a sequence of nodes in which each node stores a
pointer to the next node. “Singly” means links go only toward the next
node. The list's **head** pointer stores the address of its first node.
`NULL` is C's marker meaning “no object here.”

```c
typedef struct LinkedNode {
    int value;
    struct LinkedNode *next;
} LinkedNode;

typedef struct {
    LinkedNode *head;
    size_t size;
    size_t limit;
} LinkedList;
```

`size_t` is C's nonnegative whole-number type for sizes and indexes.
In a declaration, `*` marks a pointer type. In `node->next`, the arrow
`->` means “access the `next` field through the pointer `node`.” A
**traversal** visits nodes by beginning at `head` and repeatedly following
`next`.

The course list holds at most 16 nodes. `size` counts reachable nodes.
`limit` is the configured maximum from 0 through 16.

## 2. State ownership and the invariant

An **allocation** is storage reserved while a program runs. **Ownership**
is responsibility for releasing that storage. This list owns every node
reachable from `head`.

An **invariant** is a rule true in every valid state. The symbol `==` means
equal. The symbol `<=` means no greater than. A valid course list satisfies
all of these:

1. `head == NULL` exactly when `size == 0`;
2. following `next` reaches exactly `size` distinct owned nodes, then
   `NULL`;
3. `size <= limit <= 16`;
4. no link returns to an earlier node; and
5. the list has one owner.

A **shallow copy** copies pointer values without copying the pointed-to
nodes. Shallow-copying this list is forbidden because two list objects
would appear to own the same nodes.

## 3. Change links in a safe order

`malloc` is a C library operation that requests an allocation. `free`
releases one allocation. **Push-front** inserts a new node before the
current head:

1. request the new node;
2. if the request fails, change nothing;
3. store the value;
4. set the new node's `next` to the old head;
5. set `head` to the new node; and
6. increase `size`.

The canonical pushes create:

```text
R(17) -> Q(23) -> P(31) -> NULL
```

To remove Q, save `Q->next` before releasing Q. Repair the surviving link
`R->next`, then release Q. Duplicates are allowed; removal deletes the
first matching value. A full-list or allocation push error preserves the
previous state. A missing-value removal is successful with an output of
false, meaning no node was removed, and also preserves every link.

To **destroy** a list is to release every owned node. Save the next pointer
before each `free`, then reset `head`, `size`, and `limit` to zero. This is
the exact all-zero destroyed state.

## 4. Name three ownership failures

A **memory leak** is an allocation that should be released but is no longer
reachable. A **dangling pointer** stores the address of an object whose
lifetime has ended. A **use-after-free** reads or writes an object after
`free` ended its lifetime.

Freeing Q and then reading `Q->next` is a use-after-free even if a run
appears to work. The faulty program is isolated from all normal builds.

## 5. Represent changing groups with arrays

A **set** is a collection of distinct items. Sets are **disjoint** when no
item belongs to two sets. A **connected component** is a group joined by
the processed undirected relationships.

**Disjoint-Set Union (DSU)**, also called **Union-Find**, maintains these
groups. An **array** is a numbered row of values. This DSU uses dense IDs:
the active IDs are consecutive numbers beginning at zero.

`parent[x]` stores the ID above `x`. Brackets select array position `x`.
Following parent values forms a **forest**, meaning several tree-shaped
groups. Each group has a **root**, or representative, whose parent is
itself. `component_size[root]` stores that root's group size. A nonroot
stores size zero. The sentinel value 16 marks an inactive array position.

## 6. Make, find, and merge sets

**Make-set** creates the next dense ID as a one-item set:

```text
parent[x] = x
component_size[x] = 1
```

In this pseudocode, `=` means store the right-side value in the left-side
location.

**Find** follows parent values to return an item's root. The course find is
iterative, meaning it uses loops rather than recursive self-calls. Its first
pass locates a root with a strict step bound. Its second pass performs
**path compression** by changing visited parent entries to point directly
to that root. Compression changes the shape, not group membership.

**Union** merges the groups containing two IDs. **Union by component size**
attaches the smaller root below the larger root. If sizes tie, the smaller
root ID wins. Only the winning root stores the combined size.

If both finds return the same root, union succeeds with `merged=false`.
For a new undirected relationship, that result is **cycle-producing**:
there was already a route between its endpoints, so adding the relationship
closes a cycle.

## 7. Limit the result

DSU answers whether two active IDs share a processed undirected component.
It does not return a route, a shortest route, a weighted cost, resilience,
meaning the ability to continue after failures, or support deletion
efficiently. Shared membership never proves trust or **authorization**,
permission to perform an action.

Keep `vocabulary.md` closed until all three Cognitive Pause targets are
preserved.
