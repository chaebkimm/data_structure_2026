# Stage B — Formal Names and Representations

Open after preserving the initial inquiry. This representation follows
[lab.c](lab.c).

## 1. A linked list can store integer links

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
index. For first=0 with records `{17,1}`, `{23,2}`, `{31,-1}` at indices
0, 1, 2, traversal visits 17,23,31. Links determine logical order.

## 2. The pool tracks available slots

A **pool** is a bounded collection of reusable slots. `init_lnodes_pool()` zeros
data, links all ten slots, and sets `free_head=0`. The free chain is
`0→1→2→3→4→5→6→7→8→9→-1`.

`new_lnode(value, -1)` pops the first free index, writes data, sets `next=-1`,
and returns it. Exhaustion returns `-1` without changing state.
`free_lnode(index)` pushes a detached slot onto the free chain; it does not
call C's `free` or erase data.

Free and allocated slots partition the pool. An allocated slot can be in
one active chain or be temporarily **detached**, held by its caller. Free
and active chains must not overlap or cycle. A range check cannot detect
double recycling.

## 3. Local list changes have separate jobs

`link_lnode(prev,node)` inserts an allocated detached node after `prev`:
it stores the old successor in `lnodes[node].next`, then changes
`lnodes[prev].next`. It does not search or change a first-node variable.

`delete_next_lnode(prev)` bypasses and returns the successor, or `-1` if none.
It leaves the returned node's `next` unchanged and does not recycle it.
For 0→1→2→-1, deletion after 0 returns 1 and leaves 0→2→-1. Only the
caller's later `free_lnode(1)` makes slot 1 available again.

The caller supplies the second argument of `new_lnode(data_value, next_value)`. Use `-1` for a detached allocation. Supplying an existing valid successor supports prepending a new node without moving older records.

A standalone list's first index belongs to its caller. `init_lnodes_pool()` rebuilds the free chain and must never run while a live list still uses the pool.

## 4. The same list becomes a linked queue

Use `init_lnodes_pool(); head = tail = -1;` only when no live user owns a pool slot. `enqueue(value)` allocates a detached node, appends it, and returns `true`. Pool exhaustion returns `false` without changing the pool or queue. `dequeue()` returns the oldest **value** and recycles its node internally. The caller must check `is_empty_queue()` before calling it and must not recycle the returned value as if it were a slot index.

The node helpers expose the implementation: `enqueue_lnode(index)` appends an allocated detached slot; `dequeue_lnode()` detaches and returns an index without recycling it, or returns `-1` without changes when empty. Raw callers read `lnodes[index].data` before `free_lnode(index)`. Public `dequeue()` performs those steps itself. It asserts nonempty rather than returning an empty status. With `NDEBUG`, the assertion is removed, so the caller's nonempty precondition still applies.

A queued value of `-1` is valid. It is not an empty marker in the value interface. Check the queue state, not the returned payload. Store the result of `enqueue(value)` before checking it; `assert(enqueue(value))` would remove the insertion when assertions are disabled.

| Action after a fresh reset | Return | `head` | `tail` | Live slots | `free_head` |
| --- | --- | ---: | ---: | --- | ---: |
| `enqueue(17)` | `true` | 0 | 0 | 0 → -1 | 1 |
| `enqueue(23)` | `true` | 0 | 1 | 0 → 1 → -1 | 2 |
| `enqueue(31)` | `true` | 0 | 2 | 0 → 1 → 2 → -1 | 3 |
| `dequeue()` | 17 | 1 | 2 | 1 → 2 → -1 | 0 |
| `enqueue(8)` | `true` | 1 | 0 | 1 → 2 → 0 → -1 | 3 |
| drain 23, 31, 8 | values | -1 | -1 | empty | 0 (all ten free) |
