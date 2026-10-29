# Current Module 7 Build Helpers

The complete [student/lab.c](../student/lab.c) defines no `main`; tests provide
drivers. From this code directory run:

```sh
make lab-compile
make core
make student-tests
```

PowerShell: `./build.ps1`, `./build.ps1 -StudentTests`, and optionally
`./build.ps1 -Sanitize`.

Add three original safe groups: allocation/exhaustion,
insertion/traversal, and detachment/recycling/reuse including shared-list
reuse, linked Stack LIFO, and linked Queue endpoints/FIFO. The pool has ten
nodes shared across its users. `new_lnode()` returns an isolated node index
or `-1`; the caller writes `data`. List helpers are
`simple_link_lnode_to_prev` and `simple_delink_next_lnode_from_prev`.
Deletion isolates its returned node without recycling it.

The Stack uses a caller-owned first index. Guard empty removal, save the
value and successor, advance first, isolate the removed node, and recycle it.
The Queue uses `qhead`/`qtail`; `enqueue_lnode(index)` transfers ownership to
the Queue, while `dequeue_lnode()` returns an isolated allocation to its
caller (or `-1` when empty). Read the payload and recycle separately.
A payload of `-1` is valid; distinguish it from the index sentinel.

`init_lnodes_pool()` initializes once and preserves every later state.
Independent tests must return all allocations rather than call it to reset
storage. Out-of-range indices, double recycling, live-node recycling, and
stale access are outside the unchecked helpers' contract. Only the `-1`
no-op is guaranteed for `free_lnode` and `enqueue_lnode`.

Tests keep operations and checks active under `NDEBUG`. The release does
not require or include the optional pointer-list or DSU library. Module 8
adds a value interface around these node operations for BFS.
