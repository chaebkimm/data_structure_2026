# Chapter 8 — Processing data in stored order

Study queue → tree level order → graph BFS as one lesson and submit one artifact. The current PPTs use a 5×5 maze. Its C implementation stores `struct point` values directly in a linear array queue. Coordinates are written in field order `{y, x}`.

The English textbook follows the approved Korean chapter through `Thinking logically` → `Calculating efficiency` → `Glossary` → `Invariant` → `Coding plan` → `New C syntax explained` → `C code`. The invariant is the nondecreasing distance order of waiting nodes. The new syntax explanations cover two-dimensional initializer braces, whole-structure copying/passing/returning, and short-circuit logical OR. Use them with the queue/maze traces; they do not create extra assignments.

Extract the whole archive. Read `module_08_graph_bfs/student/textbook.md` or `textbook_korean.md`, then follow `student/lab.md`. From the archive root run:

```sh
make -C module_08_graph_bfs/code lecture
```

Or compile the supplied test harness:

```sh
cc -std=c11 -Wall -Wextra -pedantic \
  module_08_graph_bfs/code/tests/test_lecture.c -o /tmp/module08_lab
/tmp/module08_lab
```

PowerShell: `powershell -File module_08_graph_bfs/code/build.ps1 -Target lecture`. `make core` and `make student-tests` run the same harness. Expected output:

```text
PASS: array queue, iterator, maze distances, resets, and 12800 bordered-maze searches
```

`lab.c` has no `main`; the harness includes it. Compile only the harness. No other module's source is required. Keep the supplied lecture source and all four PPT Markdown files unchanged; add experiments and assertions in the harness.

Start `{1,1}` reaches eight passages. Target `{3,3}` has distance 4. Distances are marked before enqueue, so every reachable passage enters once. The queue finishes at `front=8`, `rear=7`; the next `bfs` call resets it and all distances. An in-bounds wall start leaves every distance at `INF=25`. Keep the wall border intact and supply only in-bounds starts.

Tree level order and circular queues are conceptual comparisons. The source computes distances; storing a previous coordinate to recover one route is an explained extension. It does not store predecessor lists or enumerate routes. Instructor answers and the optional checked matrix/list library are excluded from this archive.
