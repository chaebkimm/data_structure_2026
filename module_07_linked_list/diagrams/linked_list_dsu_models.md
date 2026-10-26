# Module 07 Models — Index Links

The historical filename is retained for existing links. These models follow `student/lab.c`.

## 1. Two chains share one pool

```text
first = 0
active: 0(17) → 1(23) → 2(31) → -1
free_head = 3
free:   3 → 4 → 5 → 6 → 7 → 8 → 9 → -1
```

The physical pool is `lnodes[10]`. Each slot belongs to the free chain, one active chain, or a caller-held detached allocation. Links determine order.

## 2. Preserve the old successor

```text
before: 0 → 2 → -1; detached: 1
first write: lnodes[1].next = 2
second write: lnodes[0].next = 1
after: 0 → 1 → 2 → -1
```

## 3. Detach, recycle, then reuse

```text
delete_next_lnode(0): returns 1; active 0 → 2 → -1
                     lnodes[1].next stays 2; free_head stays 3
free_lnode(1):        free 1 → 3 → 4 → 5 → 6 → 7 → 8 → 9 → -1
new_lnode(8,-1):      returns 1; data=8,next=-1; free_head=3
```

The reused node remains detached until the caller links it. Allocation stores its supplied next argument. A range check cannot detect a slot returned twice.

## 4. A linked queue keeps both ends

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

In the singleton example, raw `dequeue_lnode()` returns the slot and leaves it allocated; public `dequeue()` returns 31 and recycles that slot. Both reset endpoints. Do not double-recycle after public removal. Module 8 calls the value interface with tree/vertex IDs. The shared ten-slot pool limits simultaneous ownership, and pool initialization does not reset queue endpoints.
