# Stage B — Formal Names and Representations

Open after preserving the initial inquiry. Use [lab.c](lab.c), [concept slides](ppt_material.md), and [lab slides](ppt_lab_material.md).

## 1. Acyclic chains and a saved first index

A **node** stores data and a link. In a **singly linked list**, one next link leads to the following node. Here links are integer indices into ten `struct Linked_Node` records, not addresses. Indices 0–9 differ from stored data; **sentinel** -1 means no node and must never be subscripted. The caller saves `first` separately. An empty list has first=-1; every active chain ends at -1 without revisiting a node.

For first=0, records 0={17,1}, 1={23,2}, 2={31,-1} read 17,23,31. Changing links changes logical order without shifting the surviving data.

## 2. Safe insertion and detachment

`simple_link_lnode_to_prev(prev,node)` requires valid distinct allocated non-queue predecessor and isolated unreferenced allocation. In 0→2→-1 with isolated 1, first copy 0.next=2 into 1.next, then set 0.next=1. Reversing those writes creates 1.next=1 and loses 2 from this traversal.

`simple_delink_next_lnode_from_prev(prev)` bypasses the successor and clears the removed node's next to -1. It returns the index, or -1 after a tail, without recycling. In 0→1→2→-1, deletion after 0 leaves 0→2→-1 and isolated allocated 1. Neither primitive searches, updates first, or repairs queue endpoints.

## 3. Advantages, costs, and shared slots

Known-predecessor changes use fixed work and shift no surviving data. Finding that predecessor or the i-th node may follow O(n) links. Every slot needs an extra integer next link. Several disjoint lists can draw any free slot without fixed per-list partitions, but all live and detached allocations together fit in ten slots.

## 4. Free-chain lifecycle

`init_lnodes_pool()` initializes links only on its first call. Its function-local `static initialized` flag survives later calls, including calls from `new_lnode()`. First initialization builds 0→1→2→3→4→5→6→7→8→9→-1 and sets `free_head=0`; it does not assign data fields. Global data begins at zero by C static-storage rules, while reused data remains until a caller writes it. Later initialization calls change nothing and cannot reset or recover an exhausted pool. Use a new process for an independent pristine fixture, or recycle every owned node before continuing; an all-free chain need not be in ascending order.

`new_lnode()` takes the free head, isolates it, and returns its index. It leaves data unchanged; check the index, then write data. Exhaustion returns -1 unchanged. `free_lnode(node)` prepends an allocated unreferenced isolated slot to the free chain, without erasing data. The sentinel -1 is a no-op; other range and ownership preconditions are unchecked.

An unreturned detached allocation consumes capacity. Returning a live node or returning one twice can corrupt links. After return, stop using its old owner's index: another list can allocate that slot and replace its data. A range check or a clean sanitizer run cannot prove ownership.

## 5. Linked Stack

There is no supplied Stack API. To prepend, call `node=new_lnode()` and check success, then write its data, set `lnodes[node].next=first`, and finally set `first=node`. Prepending 17,23,31 in a pristine process gives 2(31)→1(23)→0(17)→-1. Before removal check `first != -1`; save the old index, data, and next, advance `first`, set `lnodes[old].next=-1`, then recycle. The outputs are 31,23,17. Clearing next is required because `free_lnode` accepts only isolated allocations. Never recover data or next through a recycled old index.

## 6. Linked Queue

The supplied queue operates on **node indices**. `enqueue_lnode(node)` appends a valid allocated, unreferenced, isolated node (`next == -1`). Allocate first with `new_lnode()`, check for `-1`, write `lnodes[node].data=value`, then append. `enqueue_lnode(-1)` is a no-op; the void function does not report allocation failure.

`dequeue_lnode()` returns the oldest **index**, isolates that node with `next=-1`, and leaves it allocated to the caller. Empty removal returns `-1` without changes. On success, copy `lnodes[node].data`, then call `free_lnode(node)` exactly once. Neither queue operation allocates or recycles automatically. There are no supplied value-based `enqueue(value)` or `dequeue()` wrappers.

The endpoints are `qhead` and `qtail`. Both are `-1` when empty; otherwise `qtail` is reachable from `qhead` and `lnodes[qtail].next == -1`. The first append sets both; the final removal clears both. A payload of `-1` is valid: only the returned node index is the empty marker.

| Action in a pristine process | Result | `qhead` | `qtail` | Queue | `free_head` |
| --- | --- | ---: | ---: | --- | ---: |
| allocate 0, write 17, append 0 | void | 0 | 0 | 0→-1 | 1 |
| allocate 1, write 23, append 1 | void | 0 | 1 | 0→1→-1 | 2 |
| allocate 2, write 31, append 2 | void | 0 | 2 | 0→1→2→-1 | 3 |
| `node=dequeue_lnode()` | index 0; next=-1 | 1 | 2 | 1→2→-1 | 3 |
| copy data 17; `free_lnode(0)` | caller recycles | 1 | 2 | 1→2→-1 | 0 |
| allocate 0, write 8, append 0 | void | 1 | 0 | 1→2→0→-1 | 3 |
| dequeue/copy/recycle remaining | values 23,31,8 | -1 | -1 | empty | 0 |

The final free chain is 0→2→1→3→4→5→6→7→8→9→-1. All ten slots are free; their order need not match initialization.

## 7. Invariants versus preconditions

An **invariant** is a rule of every valid completed representation. A **precondition** is what the caller must establish before an operation. For example, enqueue requires a valid allocated isolated node; after enqueue, it belongs to the queue and the endpoint invariants hold.

- Every active list and the free chain are acyclic, end at `-1`, and contain only indices 0–9.
- Every slot belongs exactly once to the free chain, one active list, or a caller-held isolated allocation. Active lists are disjoint; every standalone list has its own saved first index.
- A caller-held node ready for insertion, enqueue, or recycling has `next == -1` and no incoming live link.
- The queue is empty exactly when both endpoints are `-1`; otherwise the tail is reachable and ends at `-1`.
- Save payload/successor before recycling, then stop using the old owner's index. Index range alone does not establish ownership.
