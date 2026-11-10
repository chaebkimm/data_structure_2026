# Chapter 7. Linking to the next item

We will build a list by storing the next item's location with each item. We will manage unused memory slots by linking them together. Then we will build a queue that removes items in the order they were stored.

## Thinking logically

### What does linking each item to the next look like?

Suppose each item records the location of the next item. Following this connection takes us to the next item, then the one after it. An item with no next item is the last. With suitable rules, we can form a sequence with a first item, a last item, and other items in between.

### How do we store the next item's location?

We store items in memory slots and use slot numbers to record the next item's location. If we number the slots starting at `0`, negative numbers are unused, so we can use `-1` to mean there is no next item.

### How do we visit all the linked items?

Start with the first item and follow each link to the next item. Stop when you reach the last item, whose next slot number is `-1`. Store the slot number of the first item separately.

### How do we insert an item between two linked items?

Suppose one item points to another. To insert a new item between them, first copy the second item's slot number into the new item's link. Then change the first item's link to point to the new item. If we reverse these steps, we overwrite the first item's link and can lose the second item's slot number.

### How do we unlink an item from the middle of a list?

Suppose three items are linked in order. To unlink the middle item, make the first item point directly to the third. Then set the middle item's next slot number to `-1`.

### Can several lists share the same memory space?

Suppose we store items from several lists in the same memory space. Link the items within each list, and keep a separate record of the slot number of each list's first item.

### How do we keep track of unused memory slots?

Link the unused slots together to form a list. To store a new item, take a slot from this list. After you unlink an item and finish using its slot, link the slot back into the list of unused slots.

### How do we take an unused slot?

We take a slot from the list of unused slots. Any slot in the list will do, so we take the first one because it is easiest to reach. We then record its next slot number as the new start of the list.

### How do we return a slot when we are done with it?

We link the slot back into the list of unused slots. It can go anywhere in the list, and the front is the easiest place to add it. First, we make the slot we are returning point to the current first slot. Then we record the returned slot's number as the new start of the list.

### How do we remove items in the order they were stored?

Link each new item after the last one and remove the first item each time. It works like a line of people who join at the back and leave from the front. Keeping track of the slot numbers of the first and last items makes it easy to add or remove an item.

## Calculating efficiency

### Memory efficiency for storing

Each item needs extra space to store the next item's slot number. To reach the linked items, we store the first item's slot number. In a queue, we also store the last item's slot number so we can add each new item directly at the back and keep the items in arrival order. The list of unused slots needs space for its own first slot number.

### Efficiency of following linked items in order

Start at the first item and follow each link to the next. We visit each item once, so the work is proportional to the number of items in the list. At each step, we replace the current slot number with the next one. The extra memory needed for traversal stays constant as the list grows.

### Efficiency of storing and linking an item

Before we use any slots, we link them all into a list of unused slots. We do this once per run, and the work is proportional to the total number of slots. After that, we can take the first unused slot, store an item there, and link it after a known slot by updating just a few slot numbers. This takes the same amount of work no matter how many items the list holds.

### Efficiency of unlinking an item and returning its slot

When we know the preceding item's slot number, we can unlink the item and return its slot to the front of the list of unused slots by updating just a few slot numbers. This takes the same amount of work no matter how many items the list holds.

## Glossary

### Node

One integer value together with the next node's index.

### Singly linked list

A sequence in which each node has one link to its successor.

### First node

The node from which the whole list is accessed; its index is saved separately.

### Predecessor

The node immediately before another node in the list.

### Successor

The node immediately after another node in the list.

### Traversal

Following successive links to visit the nodes of a list.

### Cycle

A path of links that returns to a node already visited.

### Node pool

A fixed array of nodes available for repeated use.

### Free list

The chain of available nodes reached from `free_head`.

### Allocation

Taking a node out of the free list and assigning it to a caller.

### Detached node

An allocated node outside every chain, with `next = -1`.

### Recycling

Returning an allocated, detached node to the free list.

### Ownership

Responsibility for keeping a node in exactly one state: free, in one active list, or detached for a caller.

### Stale index

An index retained after returning a node, which no longer identifies the old caller's record.

### Stack

A structure that removes the most recently added item first, following LIFO order.

### Queue

A structure that removes the earliest added item first, following FIFO order.

### Enqueue

Add a node at the queue's tail.

### Dequeue

Remove a node from the queue's head.

## Invariant

### What are the invariants (the golden rules) in this data structure?

- An absent link or endpoint is `-1`; a present one is an index from `0` through `CAPACITY - 1`.
- Every active list and the free list has no cycles and ends at `-1`.
- After initialization, each slot belongs to exactly one active list, the free list, or a caller as a detached node. A detached node has `next = -1`.
- An empty queue has both `qhead = -1` and `qtail = -1`. In a nonempty queue, `qtail` is the last node reached from `qhead`, and its `next` is `-1`.

### What is the benefit of the invariants?

Valid links and the absence of cycles let us visit each node in a list exactly once. Separate ownership lets several lists reuse the pool without changing one another's records. Correct queue endpoints let us add at the tail and remove at the head while preserving FIFO order.

### What happens if an invariant is broken?

An invalid index accesses memory outside the array. A cycle prevents traversal from ending. Returning an active node overwrites a link its list still needs; returning the same node twice can create a cycle in the free list.

Losing the index of a detached node leaves that slot unavailable. Using a stale index after recycling can change the free list or another caller's record. An incorrect queue tail can attach new nodes to the wrong chain.

### How do we keep the invariants intact?

Initialize before use, check returned indices, and preserve a successor before replacing its link. Detach a node before recycling it, read any needed data first, and return it exactly once. Use the queue helpers for queued nodes so both endpoints stay consistent.

These rules hold after each complete operation. The helpers do not check every index or ownership condition; callers must supply valid nodes.

## Coding plan

### Designing a node

Keep `data` and `next` in `struct Linked_Node`; store ten such nodes in a shared array. Keep each ordinary list's first index separately.

### Connecting and detaching nodes

For insertion, give the new node the predecessor's old successor before connecting the predecessor to it. For removal, save the successor's index, bypass it, clear its link, and return its index.

### Preparing the node pool

Connect all slots in array order and put `-1` in the last link. Keep the first available index in `free_head`. Use a local `static` flag so later initializer calls preserve existing lists.

### Allocating and recycling nodes

Allocate by taking the first free node and clearing its link. Check the returned index before assigning its data. Recycle an allocated, detached node by linking it before the current free head, then updating `free_head`.

### Using the nodes as a stack

Add by linking a new node before `first` and updating `first`. Remove by saving the old first node's value and successor, advancing `first`, isolating the old node, and recycling it. Check for allocation failure or an empty stack before changing links.

### Using the nodes as a queue

Keep `qhead` and `qtail`. Append an allocated, isolated node after the tail, setting both endpoints when the queue was empty. Remove the head, clear the tail if the queue becomes empty, and return the detached index. The caller reads its data and recycles it.

## New C syntax explained

### Naming an integer constant with `enum`

`enum { CAPACITY = 10 };` gives the integer constant 10 a name. We use that name in the array declaration and initialization loop so they agree on the pool's size.

### A local `static` variable

`static int initialized = 0;` creates a local variable that keeps its value between function calls. It is initialized once, rather than reset to 0 each time the function runs.

### `void` in a function declaration

In `int new_lnode(void)`, `void` means the function takes no arguments. In `void free_lnode(int node)`, the first `void` means the function returns no value. A plain `return;` ends such a function immediately.

### Chained assignment

`qhead = qtail = node;` assigns `node` to `qtail`, then assigns that same value to `qhead`. Both endpoints identify the single node in a newly nonempty queue.

### Returning a comparison

`return qhead == -1;` returns 1 when the comparison is true and 0 when it is false. An `if` condition treats a nonzero result as true.

## C code

### Node storage

```c
enum { CAPACITY = 10 };

struct Linked_Node {
        int data; // A stored value, not a node index.
        int next; // Next node's array index; -1 means no successor.
};
struct Linked_Node lnodes[CAPACITY];
```

### Connecting a node after its predecessor

```c
void simple_link_lnode_to_prev(int prev, int node) {
        // Requires valid, distinct indices: prev is an allocated non-queue node;
        // node is allocated, outside every chain, and has next = -1.
        lnodes[node].next = lnodes[prev].next; // Preserve the old successor first.
        lnodes[prev].next = node;
}
```

### Detaching the node after a predecessor

```c
int simple_delink_next_lnode_from_prev(int prev) {
        // Requires a valid, allocated non-queue predecessor.
        int node = lnodes[prev].next;
        if (node != -1) {
                lnodes[prev].next = lnodes[node].next; // Bypass the removed node.
                lnodes[node].next = -1; // Isolate it without returning it to the pool.
        }
        return node; // Return an index, or -1 when there was no successor.
}
```

### Initializing the node pool

```c
int free_head = -1;

void init_lnodes_pool(void) {
        static int initialized = 0; // Retain this flag between calls.
        if (initialized) {
                return; // Preserve any nodes already in use.
        }
        initialized = 1;

        for (int i = 0; i < CAPACITY - 1; i++) {
                lnodes[i].next = i + 1;
        }
        lnodes[CAPACITY - 1].next = -1; // End the free chain.
        free_head = 0;
}
```

### Allocating a node

```c
int new_lnode(void) {
        init_lnodes_pool(); // Only the first call builds the free chain.
        if (free_head == -1) {
                return -1; // No available slot; leave the pool unchanged.
        }
        int node = free_head;
        free_head = lnodes[free_head].next;
        lnodes[node].next = -1; // The caller receives an isolated node.
        return node; // Data is unchanged; the caller assigns its new value.
}
```

### Returning a node to the pool

```c
void free_lnode(int node) {
        if (node == -1) {
                return;
        }
        // Requires a valid allocated node outside every chain, with next = -1.
        lnodes[node].next = free_head; // Prepend the node; keep its data unchanged.
        free_head = node;
}
```

### Keeping the queue endpoints

```c
int qhead = -1;
int qtail = -1;

int is_empty_queue(void) {
        return qhead == -1; // The invariant also makes qtail -1 when empty.
}
```

### Adding a node to the queue

```c
void enqueue_lnode(int node) {
        if (node == -1) {
                return;
        }
        // Requires a valid allocated node outside every chain, with next = -1.
        if (is_empty_queue()) {
                qhead = qtail = node; // One node is both the first and the last.
        } else {
                lnodes[qtail].next = node;
                qtail = node;
        }
}
```

### Removing a node from the queue

```c
int dequeue_lnode(void) {
        if (is_empty_queue()) {
                return -1;
        }
        int oldest = qhead;
        qhead = lnodes[qhead].next;
        if (qhead == -1) {
                qtail = -1; // Removing the only node leaves both endpoints empty.
        }
        lnodes[oldest].next = -1;
        return oldest; // The caller reads the data, then recycles the detached node.
}
```
