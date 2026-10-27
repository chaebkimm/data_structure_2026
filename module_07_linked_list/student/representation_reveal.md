# Stage B — Formal Names and Representations

Open after preserving the initial inquiry. This representation follows
[lab.c](lab.c) and the [concept slides](ppt_material.md).

## 1. A linked list can store integer links

We want to change reading order without moving the other records.
A **node** contains data and a link. A **singly linked list** follows one
`next` link per node. Here links are integer array indices, not addresses:

```c
struct Linked_Node {
    int data;
    int next;
};
struct Linked_Node lnodes[10];
```

`lnodes[0].data` reads the data at slot 0; `lnodes[0].next` identifies its
successor. Valid indices are 0–9; `-1` is a **sentinel** meaning no node.
Never use it as a subscript. The caller keeps a standalone list's first
index. For `first=0` with records `{17,1}`, `{23,2}`, `{31,-1}` at indices
0,1,2, traversal reads 17,23,31. Links determine logical order. This list
has no cycle: every node eventually reaches `-1`. An empty list has `first=-1`.

## 2. Local list changes have separate jobs

We can insert 23 between 17 and 31 by changing two links.
`link_lnode(prev,node)` inserts an allocated detached node after `prev`:
it stores the old successor in `lnodes[node].next`, then changes
`lnodes[prev].next`. For 0→2→-1 and detached node 1, the writes make
`lnodes[1].next=2`, then `lnodes[0].next=1`. Reversing the writes makes
node 1 point to itself and loses node 2 from this traversal.
Both indices must be valid, distinct allocated nodes; the new node must
be outside all active chains. The function does not search or update first.

`delete_next_lnode(prev)` bypasses and returns the successor, or `-1` if none.
It leaves the returned node's `next` unchanged and does not recycle it.
For 0→1→2→-1, deletion after 0 returns 1 and leaves 0→2→-1.
The caller retains the removed index until using or recycling it.

## 3. Separate nodes change the costs

Once the predecessor is known, insertion writes two links and deletion
bypasses one node. No surviving data needs to shift. Finding a predecessor
or the i-th node can still require following all earlier links. Each of
the ten slots also stores one integer `next` in addition to its integer data.

Separate lists need not reserve separate array regions. Each keeps its
own first index and takes any available slot from a shared collection.
The active chains must remain disjoint. A free slot cannot belong to an
active list at the same time.

## 4. The pool tracks available slots

We need to find an unused slot without scanning the whole array.
A **pool** is a bounded collection of reusable slots. Available slots form
a **free chain** using the same next fields.
`init_lnodes_pool()` zeros data, links all ten slots, and sets `free_head=0`.
The free chain is `0→1→2→3→4→5→6→7→8→9→-1`.
Initialize only when no live list or detached allocation uses the pool.

`new_lnode(value,next_value)` removes the first free index, stores both
arguments, and returns the index. Use next `-1` for a detached node.
Exhaustion returns `-1` without changing any field. Check before indexing.
`free_lnode(index)` returns a detached allocated slot to the beginning of
the free chain. It does not call C's `free` or erase the stored data.

Allocated slots belong to one active chain or are temporarily **detached**
and held by a caller. If a detached slot is never returned, the allocator
cannot use it. Returning an active slot or returning the same slot twice
breaks the chains. The range check in `free_lnode` cannot detect either error.

After a return, stop accessing the slot through the old caller index.
The slot can already be free or belong to another list. For example, let
A own 0(17), B own 1(23), and `free_head=2`. After A detaches and returns 0,
B can allocate 8 before node 1 and receive index 0. A's old index now reads
8. Writing either its data or next changes B. These accesses may stay
inside the array bounds, so a clean memory-sanitizer run does not prove ownership.

## 5. First-node changes make a linked Stack

To take the latest value first, add and remove at the same end. The first
index is enough. This is a **linked Stack**, with last-in-first-out order.
There are no supplied Stack push/pop functions; these are caller actions.

Start a fresh unowned pool and `first=-1`. For each value, call
`node=new_lnode(value,first)`. If it succeeds, set `first=node`.
If it fails, leave first unchanged. Adding 17,23,31 gives
2(31)→1(23)→0(17)→-1.

Before removal, check `first != -1`. Save the old first index, its data,
and its next. Update first to that saved next, then recycle the old node.
The returned values are 31,23,17. After draining, first is `-1` and all ten
slots are free. Saving next after recycling would read a free-chain link
instead of the Stack successor. Saving data before returning the slot also
avoids reading a value replaced by a later owner.

## 6. The same list becomes a linked Queue

Use `init_lnodes_pool(); head = tail = -1;` only when no live user owns a pool slot. `enqueue(value)` allocates a detached node, appends it, and returns `true`. Pool exhaustion returns `false` without changing the pool or queue. `dequeue()` returns the oldest **value** and recycles its node internally. The caller must check `is_empty_queue()` before calling it and must not recycle the returned value as if it were a slot index.

The node helpers expose the implementation: `enqueue_lnode(index)` appends an allocated detached slot whose `next` must be `-1`; `dequeue_lnode()` detaches and returns an index without recycling it, or returns `-1` without changes when empty. Raw callers read `lnodes[index].data` before `free_lnode(index)`. Public `dequeue()` performs those steps itself. It asserts nonempty rather than returning an empty status. With `NDEBUG`, the assertion is removed, so the caller's nonempty precondition still applies.

A queued value of `-1` is valid. It is not an empty marker in the value interface. Check the queue state, not the returned payload. Store the result of `enqueue(value)` before checking it; `assert(enqueue(value))` would remove the insertion when assertions are disabled.

| Action after a fresh reset | Return | `head` | `tail` | Live slots | `free_head` |
| --- | --- | ---: | ---: | --- | ---: |
| `enqueue(17)` | `true` | 0 | 0 | 0 → -1 | 1 |
| `enqueue(23)` | `true` | 0 | 1 | 0 → 1 → -1 | 2 |
| `enqueue(31)` | `true` | 0 | 2 | 0 → 1 → 2 → -1 | 3 |
| `dequeue()` | 17 | 1 | 2 | 1 → 2 → -1 | 0 |
| `enqueue(8)` | `true` | 1 | 0 | 1 → 2 → 0 → -1 | 3 |
| drain 23, 31, 8 | values | -1 | -1 | empty | 0 (all ten free) |
