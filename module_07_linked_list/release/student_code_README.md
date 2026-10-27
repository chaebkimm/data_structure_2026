# Current Module 7 Build Helpers

The complete [student/lab.c](../student/lab.c) defines no `main`; tests provide drivers. From this code directory run:

```sh
make lab-compile
make core
make student-tests
```

PowerShell: `./build.ps1`, `./build.ps1 -StudentTests`, and optionally `./build.ps1 -Sanitize`.

Add three original safe groups: allocation/exhaustion, insertion/traversal, and detachment/recycling/reuse including shared-list reuse, linked Stack LIFO, and linked Queue endpoints/FIFO. The pool has ten nodes shared across its users; allocation takes both data and next arguments. Check return indices and retain the caller's first-node index. The stack is a caller-side example using those primitives. Check empty before removing its first node, save the value and successor before recycling, and stop using the old slot after recycling. The release does not require or include the optional pointer-list or DSU library.

The linked queue example is included in the same `student/lab.c`. Its caller checks bool enqueue status and queue emptiness. Public dequeue returns a value and recycles internally; raw node helpers expose indices and separate recycling. Initialize the unused pool and reset `head = tail = -1` for an independent run. Module 8 reuses these functions.

Use `init_lnodes_pool()` for an otherwise unowned pool and reset head/tail. A dequeued payload of -1 is valid; check emptiness separately. Keep required queue calls outside assert, since NDEBUG removes assertions.
