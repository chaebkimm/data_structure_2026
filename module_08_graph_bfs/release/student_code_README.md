# Chapter 8 Lecture Lab Build

Run `make lecture`, `make core`, or `powershell -File ./build.ps1 -Target lecture` from this directory. The default target runs the same lecture checks. `tests/test_lecture.c` includes the unchanged `../student/lab.c` and supplies `main`. Compile only the test file; no other module is a dependency.

The harness checks the array FIFO, four-direction iterator, canonical distances and order, repeated searches, wall starts, isolated starts, and 12,800 bordered-maze cases against independent expected distances. `make student-tests` is an alias; add one original valid experiment to the harness and record its predicted and observed result.

The queue stores `{y,x}` coordinates, starts at `front=0,rear=-1`, and removes in arrival order. For the canonical start `{1,1}`, target `{3,3}` has distance 4; eight passages enter and leave the queue. The final indices are `front=8,rear=7`. A new `bfs` call resets all search state. Wall starts are allowed if in bounds and leave all distances `INF`; the outer border must remain walls. Queue mutations and coordinate reads do not perform their own capacity or bounds checks.

Tree level order, circular queue reuse, and one-parent path reconstruction are discussed in the textbook. They are not extra implementations required to build this source.
