# Module 8 Combined Lab Build

From this directory run `make core` or `powershell -File ./build.ps1`. The default builds ../student/lab_driver.c and runs queue, tree BFS, and maze BFS checks. `make student-tests` runs the same driver with your added assertions. Module 2 and Module 7 dependencies live at the archive root. Compile only the driver; other C files are included sources.

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
