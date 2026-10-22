# Keeping arrival order with linked nodes

## Starting question

Events arrive as 31, 8, 47. We must process the event that has waited longest.
How can we remove 31 without moving 8 and 47? Draw or describe your first
idea before reading further. A structured list of nodes and links is as valid
as a drawing.

## Values can live in separate places

An array places values in numbered neighboring slots. Another representation
puts each value in a separately allocated **node**. A node stores a value and
a **next pointer**, the address of the next node. `NULL` means no next node.
This one-way chain is a **singly linked list**. Following each `next` pointer
is traversal. Node addresses need not be adjacent or numerically ordered.

To remember both ends, keep `head` pointing to the oldest node and `tail`
pointing to the newest. Here `tail` is a node pointer, not an array index:

```text
head -> [31 | next] -> [8 | next] -> [47 | NULL] <- tail
size = 3
```

The rule “earliest added leaves first” is **first in, first out (FIFO)**.
A **Queue** promises FIFO regardless of representation. A Stack instead
removes the most recently added item first.

## Add at the tail, remove at the head

**Enqueue** adds one item. Allocate and initialize the new node first. If
allocation fails, preserve every existing link and the size. If the Queue is
empty, the new node becomes its head too. Otherwise connect the old tail's
`next` to the new node. Finally update `tail` and increment `size`.

**Dequeue** removes and reports the oldest item. First reject missing arguments
or an empty Queue. Save the head node's value and following link while the
node is still alive. Move `head` forward, decrement the size, and release the
old node once. Publish the saved integer to the caller. Reading the node
after release would be a use-after-free.

When the final node leaves, set **both `head` and `tail` to `NULL`**. Otherwise
the tail would refer to released storage, and a later enqueue could write
through a dangling pointer. **Peek** reads the oldest value without removing it.

| Operation | Logical values | Head value | Tail value | Size |
|---|---|---|---|---:|
| initialize | empty | none | none | 0 |
| enqueue 31 | 31 | 31 | 31 | 1 |
| enqueue 8 | 31, 8 | 31 | 8 | 2 |
| dequeue → 31 | 8 | 8 | 8 | 1 |
| dequeue → 8 | empty | none | none | 0 |
| enqueue 47 | 47 | 47 | 47 | 1 |

## Ownership and cleanup

Ownership means responsibility for releasing storage. The Queue owns every
reachable node. It returns integer values, not node ownership. Never copy a
live Queue struct as if it created a second chain: both copies would refer
to the same nodes. Do not put an output pointer inside Queue-owned storage.

The supplied `lq_destroy` walks the chain, saving `next` before releasing each
node. It restores the zero empty state and is safe to call again. Trace this
code rather than implementing a separate general list library.

The invariant is: an empty Queue has two null pointers and size zero; a
nonempty Queue has exactly `size` uniquely owned reachable nodes, and `tail`
is the last node with `next == NULL`. The supplied validator walks the chain
in O(n); keep it outside ordinary operation-cost measurements. It assumes
node pointers refer to live storage and cannot establish arbitrary pointer safety.

## The same FIFO behavior in a circular array

A supplied circular Queue stores a physical `head` index and `size`; its next
insertion index is `(head + size) % capacity`. This formula requires positive
capacity. Full and empty are distinguished by size. Here the tail position
is derived; it is not the linked Queue's stored tail pointer.

With capacity 4, enqueue 31, 8, 47, 19; dequeue twice; enqueue 62 and 5.
The physical array becomes `[62, 5, 47, 19]`, with head 2 and size 4.
The logical FIFO order is 47, 19, 62, 5. A further enqueue is rejected without
changing the Queue. Removed slots can retain stale values without being active.

| Property | Linked Queue | Supplied fixed circular Queue |
|---|---|---|
| Enqueue/dequeue link or index work | O(1) | O(1) |
| Allocation | One node per successful enqueue; allocator cost is separate | One backing allocation at initialization |
| Failure to add | Allocation failure or representable-size limit | Configured capacity reached |
| Storage | O(n) nodes, each with pointer overhead | O(capacity), including unused slots |
| Locality | Nodes may be scattered | Contiguous backing array |
| Cleanup | Release every node | Release backing array |

A linked Queue is not unlimited: memory and integer limits still apply.
Neither implementation is automatically thread safe or a durable event log.

## Final check and next week

Explain the pointer changes for empty → singleton → empty → singleton.
Then explain how both representations return the same arrival order. In BFS,
the Queue holds waiting vertices; graph discovery state will separately stop
cycles and duplicate scheduling. FIFO alone does not supply a visited set.
