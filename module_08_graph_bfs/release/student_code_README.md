# Module 8 Combined Lab Build

From this directory run `make core` or `powershell -File ./build.ps1`. The default builds ../student/lab_driver.c and runs queue, tree BFS, and maze BFS checks. `make student-tests` runs the same driver with your added assertions. Module 2 and Module 7 dependencies live at the archive root. Compile only the driver; other C files are included sources.

The linked queue-node slot and its payload ID are distinct. Both searches receive payload IDs from public dequeue; that operation recycles its node before returning. The canonical maze makes 20 insertions/removals with a peak of four pending entries; all supplied starts peak at six. Before independent BFS initialize the otherwise unowned pool and set head=tail=-1; maze runs also call init_info. Array front/rear resets belong only to the array comparisons.

The linked public interface is `bool enqueue(value)` and `int dequeue()`.
Enqueue reports false without mutation on pool exhaustion. Dequeue requires
nonempty input, returns the value, and recycles automatically. Payload -1 is
valid. Save enqueue's result outside assert so NDEBUG retains the operation.
Linear array comparisons use enqueue_linear/dequeue_linear and matching
is_empty_linear/is_full_linear names; circular comparison names are unchanged.
Initialize the otherwise unowned pool with init_lnodes_pool and reset head/tail.
