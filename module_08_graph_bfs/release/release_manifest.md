# Module 8 Current Student Release

Run `python3 release/prepare_student_release.py` from this module, or the PowerShell wrapper, to create `dist/module_08_graph_bfs.zip`. Use --output to choose another new path. Existing archives are never overwritten.

The single archive teaches queues, tree BFS, and graph BFS in that order and supports one submission. It includes current bilingual textbooks, workbook, concept/lab slides, lab/evidence/rubric/vocabulary, and exact canonical queue.c, tree_bfs.c, maze lab.c, and lab_driver.c. It includes Module 2's tree and Module 7's linked queue and node pool at their repository-relative paths. Its code/Makefile and build.ps1 build only the required combined driver. MANIFEST.txt lists every member. Instructor materials, solutions, optional checked-library scaffolds, and old staged worksheets are excluded.

Extract the archive as a whole and run `make -C module_08_graph_bfs/code core` from its root. The combined driver checks queue boundaries/recycling/wraparound, exact tree order/empty/single-node cases, maze mappings/distances/all predecessors/three routes, and independent runs. Instructor release verification also builds with sanitizers where available.

Stage A–E README files describe optional facilitation checkpoints. The current packager produces one combined archive, not the previous five checked-graph archives. Do not distribute an older Stage E archive as the required Week 8 lab.

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
