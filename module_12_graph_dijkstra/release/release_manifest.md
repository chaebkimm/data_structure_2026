# Module 12 Staged Release Manifest

Run `prepare_student_release.ps1` from this directory to create five ZIP
archives in `../dist`. The script refuses to overwrite an existing archive.

## Stage A — Least-Total-Cost Inquiry

Release before Meeting A:

- standard initial prompt;
- linear accessible initial prompt.

This stage retrieves route, link-count, and total-cost reasoning but contains
none of these formal terms or variants: Dijkstra, BFS, breadth-first, graph,
vertex, edge, weighted, weight, adjacency, Priority Queue, PQ, Heap,
frontier, tentative, distance, predecessor, relaxation, stale, decrease-key,
source, destination, nonnegative, infinity, INF, shortest path, or
minimum-cost path. It also contains no API or type names, complexity
notation, logarithm, formula, code, TODO, exact method or answer, solution,
or instructor material.

## Stage B — Representation and Cognitive Pause

Release after initial models are preserved:

- representation reveal;
- exactly-three-target Cognitive Pause;
- vocabulary reference.

The vocabulary file remains closed until the pause response is preserved.
Approved extended-time or asynchronous versions use the same three targets.

## Stage C — Dijkstra Investigation

Release after the pause and instructor comparison:

- standard investigation worksheet;
- linear accessible investigation worksheet.

Sections A through F are the Stage C core. Sections G through I are later
testing, autopsy, and synthesis work. The files supply questions, not the
answer key.

## Stage D — Beginner Textbook and Models

Release after the student completes and preserves the Stage C core:

- ultra-concise, example-first textbook;
- diagrams with exact labeled, tabular, and linear text equivalents.

## Stage E — Lab and Evidence

Release after retrieval and Stage D calibration in Meeting B:

- lab, rubric, evidence template, and Dijkstra Autopsy;
- public weighted-graph, typed-frontier, and Dijkstra headers;
- supplied weighted-graph ownership and lazy minimum-frontier support;
- starter text parser, Dijkstra loop, and path reconstruction;
- visible core tests and student-test template;
- student-only PowerShell and GNU Make build files; and
- bounded, solution-independent unsigned-overflow autopsy.

The canonical six-vertex run must report cost 6 and path `A,C,D,E`, with
exactly 8 pushes, 8 pops, 3 stale pops, peak frontier size 4, and 17 Heap
record comparisons.

Stage E excludes:

- `instructor/`;
- `code/solution/`;
- `code/tests/test_extension.c`;
- instructor build files, solution targets, and extension targets;
- answer keys and completed TODOs;
- Stages A through D;
- Module 9 BFS/matrix/Queue implementation;
- Module 11 solution code or its 64-record teaching limit;
- decrease-key, Bellman–Ford, Floyd–Warshall, A*, Prim, and unrelated
  algorithms or clients; and
- real map, network, or alert data; file/network input; generated binaries;
  build directories; partial archives; signed-overflow examples; and unsafe
  or unbounded faulty code.

## Instructor verification

Before release, build the reference core tests, instructor extensions, and
isolated autopsy with the commands in `../code/README.md`. Use
warning-enabled and sanitizer-enabled builds where the installed compiler
supports them.

Verify all of the following:

- `INF` is exactly `SIZE_MAX` and is never published as a reachable cost;
- negative text is rejected before unsigned conversion;
- overflow or candidate `INF` returns `DIJKSTRA_COST_RANGE` while preserving
  output;
- the run frontier limit is exactly `arc_count + 1` and never exceeds 241;
- the canonical fixture and five exact metrics match;
- complexity matches the lazy-duplicate implementation;
- the five archives contain exactly 3, 4, 3, 3, and 18 entries;
- every ZIP entry exactly matches its listed source file;
- Stage E contains none of its excluded materials; and
- a second packaging attempt is rejected without changing any archive.
