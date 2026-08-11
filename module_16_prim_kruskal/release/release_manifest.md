# Module 16 Staged Release Manifest

Run `prepare_student_release.ps1` from this directory to create five ZIP
archives in `../dist`. The script refuses to overwrite an existing archive.

## Stage A - Initial Site-Planning Inquiry

Release before Meeting A:

- standard initial prompt;
- linear accessible initial prompt.

All three Stage A files use ordinary site, two-way offer, price, route,
reached-site, separate-group, and connection language. They contain no
formal graph, MST, algorithm, representation, implementation, complexity,
code, completed selection, exact total, solution, or instructor material.

The standard and linear prompts preserve identical headings, offer IDs,
endpoint pairs, prices, questions, and scoring.

## Stage B - Representation and Cognitive Pause

Release after the initial response is preserved:

- representation reveal;
- exactly-three-target Cognitive Pause;
- vocabulary reference.

The vocabulary file remains closed until the pause response is preserved.
Approved extended-time and asynchronous versions use the same three targets.

## Stage C - Prim and Kruskal Investigation

Release after the pause and reference-model comparison:

- standard investigation worksheet;
- linear accessible investigation worksheet.

Both forms preserve identical identifiers, weights, algorithm states,
questions, and scoring. They supply questions, not the answer key.

## Stage D - Beginner Textbook and Models

Release after the Stage C core is completed and preserved:

- an ultra-concise, example-first textbook of 1,050 through 1,200 words;
- diagrams or tables with complete linear text equivalents.

## Stage E - Lab and Evidence

Release after retrieval and Stage D calibration:

- lab, rubric, evidence template, and MST Cycle Autopsy;
- public DSU, undirected edge-list, Prim-frontier, and minimum-spanning-
  forest headers;
- Prim and Kruskal starter implementations;
- supplied DSU, logical-edge builder/comparator, signed lazy minimum
  frontier, graph preparation, validation, and checked-total support;
- visible core tests and student-test template;
- student-only PowerShell and GNU Make build files; and
- a bounded, isolated, memory-safe faulty cycle check.

The canonical graph uses:

```text
0 A-B 4
1 A-C 4
2 B-C 1
3 B-D 5
4 C-D 2
5 C-E 3
6 D-E 3
7 A-E 10
```

Prim from A selects IDs `0, 2, 4, 5`. Kruskal selects IDs `2, 4, 5, 0`.
Both contain four edges, one component, and total weight 10.

The result contract accepts negative and zero weights, parallel edges, and
self-loops. A self-loop is ignored for selection. A disconnected input
produces one minimum tree per connected component. With `V` vertices and
`c` components, a valid forest contains `V - c` selected edges.

The Stage A inquiry may stop once every site is reached. Full Kruskal
examines every logical edge and preserves a complete decision ledger,
including later cycle and self-loop rejections.

## Stage E exclusions

Stage E excludes:

- `instructor/`;
- `code/solution/`;
- `code/tests/test_extension.c`;
- instructor build files, solution targets, and extension targets;
- answer keys and completed TODOs;
- Stages A through D;
- Dijkstra implementation, shortest-path reconstruction, and unrelated
  algorithms;
- advanced spanning-tree variants and resilience-augmentation algorithms;
- relative includes, source files, or compiled binaries from another module;
- real site, host, network, or alert data;
- file and network input clients; and
- generated binaries, build directories, partial archives, and any
  non-isolated faulty program.

The Stage E autopsy is a safe, deterministic logic example. It is compiled
as a separate executable and is never linked into normal tests.

## Stage A embargo

Scan all three Stage A files case-insensitively for formal terms and
variants, including:

```text
graph, vertex, vertices, edge, weighted, weight, undirected, directed,
adjacency, edge list, logical edge, multigraph, parallel edge, self-loop,
path, spanning tree, minimum spanning tree, minimum spanning forest, MST,
MSF, tree, forest, component, cycle, acyclic, Prim, Kruskal, algorithm,
frontier, cut, crossing edge, safe edge, key, parent, in_tree, stale,
lazy duplicate, Priority Queue, PQ, Heap, Union-Find, DSU, disjoint set,
representative, root, DSU find operation, union, path compression, sort,
qsort,
comparator, invariant, validator, certificate, representation, dense,
sparse, complexity, Big-O, logarithm, code, C programming, struct, API,
TODO, pseudocode, status, solution, answer key, instructor
```

The embargo targets the named DSU find operation, not the ordinary
instruction to find or identify a low-price route.

Also reject `O(...)` forms, formulas, fenced code, public API names,
completed selected-edge sets, exact final totals, and completed algorithm
traces. Ordinary site-planning words such as sites, two-way cable offers,
prices, routes, reached sites, separate groups, connect, link, lowest, and
smallest remain available.

## Archive inventory

The five archives contain exactly:

```text
module_16_stage_a_initial_inquiry.zip       3 entries
module_16_stage_b_representation_pause.zip 4 entries
module_16_stage_c_investigation.zip         3 entries
module_16_stage_d_textbook_models.zip       3 entries
module_16_stage_e_lab.zip                  22 entries
```

Ignoring generated `dist/` and `code/build/` contents, the source package
contains exactly 47 files: 26 Markdown, 3 PowerShell, 2 Makefiles, 12 C
files, and 4 headers.

## Instructor verification

Before release:

- build reference core tests, instructor extensions, and the isolated
  autopsy using `../code/README.md`;
- use strict warnings and sanitizers where the installed compiler supports
  them;
- verify the exact canonical fixture selections and total;
- verify singleton, connected, disconnected, equal-weight-alternative,
  parallel-edge, self-loop, negative-weight, and invalid-endpoint cases;
- verify a total greater than 32-bit range, order-independent cancellation,
  and preservation when the final mathematical total does not fit
  `int64_t`;
- verify Prim uses one forward-only restart cursor, selects the smallest
  unvisited vertex, and performs no full-edge scan for every popped vertex;
- verify stale-key and `in_tree` checks, including equal-weight parallel
  edges;
- verify Kruskal sorts relationally and never subtracts weights;
- verify every accepted edge merges two DSU representatives;
- verify result membership, unique selected IDs, acyclicity, component
  coverage, `V - c` edge count, and recomputed total;
- verify Prim and Kruskal totals agree without requiring identical edge
  order;
- confirm exactly three implementation TODO clusters and three student-test
  categories;
- confirm exactly three Cognitive Pause targets;
- confirm the Stage D textbook has 1,050 through 1,200 words;
- confirm the source inventory and archive entry counts above;
- compare every ZIP entry byte-for-byte with its listed source file;
- confirm Stage E contains none of its excluded material;
- confirm a second packaging attempt is rejected without changing archive
  hashes or leaving a partial file; and
- if byte-identical clean rebuilds are claimed, verify the fixed entry
  timestamp and stable mapping order on the supported .NET runtime.
