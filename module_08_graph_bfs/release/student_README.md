# Module 8 — Queues, Tree BFS, and Graph BFS

Teach and submit queue → tree BFS → graph BFS as one Week 8 artifact. This archive preserves repository-relative include paths. From the archive root read `module_08_graph_bfs/student/lab.md` and both textbooks. Run:

```sh
make -C module_08_graph_bfs/code core
```

Or compile only the combined driver from the archive root:

```sh
cc -std=c11 -Wall -Wextra -pedantic -I . \
  module_08_graph_bfs/student/lab_driver.c -o /tmp/module08_lab
/tmp/module08_lab
```

PowerShell: `powershell -File module_08_graph_bfs/code/build.ps1`. Expected output: `PASS: linked queues, tree BFS, mapping, canonical maze, and independent searches`.

The imported Module 7 linked queue is the worklist for both BFS functions. Local linear/circular queue[25] arrays are representation comparisons. The circular convention holds 24 values. Tree BFS reuses Module 2's F-root tree: F, A, G, B, C, D, E. Maze BFS reuses that linked queue and stores all shortest predecessors. Goal (5,5) from(1,1) has distance 8 and three shortest routes. Follow caller boundary checks and recycle ownership between independent runs. The Module 7 linked-node pool and Module 2 tree source are supplied dependencies. No instructor answers or optional checked-library scaffold are included.

The linked queue-node slot and its payload ID are distinct. Both searches receive payload IDs from the Module 8 `queue.c` value adapter `dequeue()`; it calls Module 7's index-returning `dequeue_lnode()`, reads the payload, and recycles the isolated node before returning. The canonical maze makes 20 insertions/removals with a peak of four pending entries; all supplied starts peak at six. Call `init_lnodes_pool()` once; later calls preserve the pool. Drain/recycle every owner before an independent BFS and require `qhead == qtail == -1`; maze runs also call `init_info()`. Array front/rear resets belong only to the array comparisons.

Module 8's local value interface in `student/queue.c` is `bool enqueue(value)`
and `int dequeue(void)`, built on Module 7's unchanged node operations.
Enqueue reports false without mutation on pool exhaustion. Dequeue requires
nonempty input, returns the value, and recycles automatically. Payload -1 is
valid. Save enqueue's result outside assert so NDEBUG retains the operation.
Linear array comparisons use enqueue_linear/dequeue_linear and matching
is_empty_linear/is_full_linear names; circular comparison names are unchanged.
The pool initializer cannot reset live ownership; return every allocation
between independent runs. The imported queue endpoints are `qhead`/`qtail`.
