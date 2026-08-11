# Module 12 Teaching Package

## Dijkstra with a Lazy-Duplicate Minimum Frontier

## 14-week delivery role - Week 10 Practical 2

This package supplies the **sole Week 10 submission** in the 14-week course.
Follow the [14-week delivery guide](../Data_Structures_Course_2026_14_Week_Delivery_Guide.md).
The required contact block is capped at 180 minutes and is one integrated
Practical 2 artifact, not a Dijkstra lab followed by a second practical.

For that bounded release, supply the validated text-weight parser, weighted-
graph setup, cleanup and integration scaffold, and Heap-backed frontier.
Students complete the Dijkstra run loop and bounded path reconstruction,
then place the BFS/linear-Priority-Queue/Heap comparison inside the same
practical evidence record. The supplied suite owns parser, allocation,
capacity, and validator coverage; students add one focused core regression
test. The complete Stage E archive remains an instructor resource and must
not become a separate lab or hidden asynchronous assignment.

This package is the Graph stage of the fourth
Linear → Tree → Graph spiral in **Data Structures Course 2026**.

## Beginner-first rule

Students are not expected to know weighted-graph vocabulary, tentative
distance, relaxation, stale entries, infinity sentinels, or Dijkstra's
algorithm before this module. Every student-facing technical term and symbol
is explained in ordinary language when first needed. Assessment rewards
correct reasoning and reproducible evidence, not memorized wording,
arithmetic speed, or drawing quality.

## Module question

> BFS minimizes the number of edges. How can we minimize total cost when
> different edges have different weights?

## Core learning targets

Students will be able to:

1. explain why minimum-hop BFS is insufficient for unequal costs;
2. interpret tentative distance and predecessor state;
3. parse a textual nonnegative weight before unsigned conversion;
4. apply strict relaxation;
5. explain why Dijkstra requires nonnegative weights;
6. use lazy duplicate frontier entries instead of decrease-key;
7. reject stale frontier snapshots before processing outgoing arcs;
8. guard candidate-cost addition against overflow and the reserved infinity
   value;
9. reconstruct a source-to-destination minimum-cost path;
10. report unreachable destinations without changing protected output;
11. verify an implementation against an independent reference; and
12. state complexity for the strategy actually implemented.

A **weighted graph** stores a numeric cost on each directed connection. A
**tentative distance** is the best source-to-vertex cost known so far; it may
improve later. **Relaxation** tests whether one more connection creates a
strictly smaller cost. Dijkstra repeatedly removes the smallest tentative
snapshot from a minimum frontier.

This package uses **lazy duplicates**. When a distance improves, a new
snapshot is inserted instead of editing an older Heap entry. On removal, a
snapshot is **stale** when its stored cost differs from the current distance;
stale snapshots are skipped before their outgoing arcs are inspected.

## Numeric and frontier contract

- Costs and distances use `size_t`.
- `SIZE_MAX` is the reserved `INF` value and never represents a reachable
  cost.
- A negative text weight is rejected before conversion to `size_t`.
- Before addition, the implementation checks the authoritative subtraction
  guard. Arithmetic overflow or a candidate exactly equal to `INF` returns
  `DIJKSTRA_COST_RANGE`.
- Every failure preserves the caller's result or path output.
- A run gives its dedicated frontier a limit of `arc_count + 1`: one source
  snapshot plus at most one successful relaxation per arc.
- The course graph is simple and directed, with at most 16 vertices and at
  most 240 arcs, so the frontier limit is at most 241. It does not inherit
  Module 11's 64-record teaching cap.

## Canonical six-vertex fixture

Letters map to vertex IDs in order: `A=0`, `B=1`, `C=2`, `D=3`, `E=4`,
`F=5`. Directed routes are inspected in the listed order:

```text
A -> B cost 9
A -> C cost 2
A -> E cost 14
B -> D cost 0
B -> E cost 8
C -> B cost 2
C -> D cost 2
D -> E cost 2
F has no route from A
```

The final minimum cost from A to E is 6. The reconstructed path is
`A, C, D, E`. The supplied stable frontier and this exact arc order produce:

```text
successful pushes        8
successful pops          8
stale pops skipped       3
peak frontier size       4
Heap record comparisons  17
```

F remains unreachable. A path request for F preserves the prior path output.

## Package map

```text
module_12_graph_dijkstra/
├── README.md
├── diagrams/
│   └── dijkstra_models.md
├── instructor/
│   ├── answer_key.md
│   ├── lesson_plan.md
│   └── technical_notes.md
├── student/
│   ├── cognitive_pause.md
│   ├── dijkstra_autopsy.md
│   ├── evidence_template.md
│   ├── inquiry_prompt.md
│   ├── inquiry_prompt_linear.md
│   ├── investigation_worksheet.md
│   ├── investigation_worksheet_linear.md
│   ├── lab.md
│   ├── representation_reveal.md
│   ├── rubric.md
│   ├── textbook.md
│   └── vocabulary.md
├── release/
│   ├── prepare_student_release.ps1
│   ├── release_manifest.md
│   ├── stage_a_README.md … stage_e_README.md
│   ├── student_build.ps1
│   ├── student_code_README.md
│   └── student_Makefile
├── dist/
│   └── module_12_stage_a_*.zip … module_12_stage_e_*.zip
└── code/
    ├── README.md
    ├── build.ps1
    ├── Makefile
    ├── include/
    │   ├── dijkstra.h
    │   ├── dijkstra_frontier.h
    │   └── weighted_graph.h
    ├── starter/dijkstra.c
    ├── solution/dijkstra.c
    ├── support/
    │   ├── dijkstra_frontier.c
    │   └── weighted_graph.c
    ├── tests/
    │   ├── test_core.c
    │   ├── test_extension.c
    │   └── test_student.c
    └── autopsy/
        ├── README.md
        └── faulty_overflow.c
```

The source package contains 42 files before the five generated archives are
created.

## Recommended release order

1. Run `release/prepare_student_release.ps1` only after all materials and
   tests pass.
2. Release Stage A before Meeting A. It withholds formal names,
   representations, formulas, code, and exact answers.
3. Release Stage B after each student preserves the initial route-cost model.
4. Release Stage C after the exactly-three-target Cognitive Pause and
   instructor comparison.
5. Release Stage D only after the student preserves Sections A through F of
   Stage C.
6. Release Stage E after retrieval and Stage D calibration in Meeting B.
7. Keep `instructor/`, `code/solution/`, and
   `code/tests/test_extension.c` instructor-only until revisions close.

## Week 10 Practical 2 submission

Students submit one integrated artifact containing:

- the bounded `code/starter/dijkstra.c` run-loop and reconstruction work;
- one focused student-authored core regression test plus saved output from
  the supplied suite;
- a complete canonical distance/predecessor/frontier trace;
- the reconstructed A-to-E path and independently checked cost;
- evidence for negative, unreachable, stale, and cost-range boundaries;
- a same-graph BFS, linear-Priority-Queue Dijkstra, and Heap-Dijkstra
  comparison, including call counts, API roles, and ADT-versus-implementation
  distinctions;
- the completed Practical 2 evidence record; and
- corrected Cognitive Pause.

The parser, Heap frontier, weighted-graph ownership, integration setup, and
their boundary tests are supplied in the Week 10 scaffold. The full autopsy
and additional Stage E tests are optional resources after the practical.

## Full-package TODO inventory

1. Parse and validate one textual weight before unsigned conversion.
2. Run Dijkstra with strict relaxation, guarded addition, lazy duplicate
   pushes, and stale-pop skipping.
3. Reconstruct a bounded predecessor path.

Weighted-graph ownership and the typed frontier are supplied.

For the 14-week path, TODO 1 is supplied complete, and setup/cleanup around
TODOs 2 and 3 is scaffolded. Students implement only the bounded algorithm
core and reconstruction described in the Week 10 submission above.

## Fixed course conventions

- Vertex IDs are `size_t` values 0 through 15; 16 is the no-vertex sentinel.
- The graph is a simple directed weighted adjacency list: no self-loops and
  no duplicate arcs.
- Active outgoing rows are deterministic and ordered by destination ID.
- Zero-cost arcs are valid. Negative textual costs are rejected before
  unsigned conversion.
- `INF == SIZE_MAX` is reserved. Overflow or candidate `INF` returns
  `DIJKSTRA_COST_RANGE` and preserves caller output.
- Relaxation uses strict `candidate < distance[v]`; an equal-cost route does
  not replace the predecessor.
- A popped snapshot is skipped when
  `popped_distance != distance[popped_vertex]`.
- The frontier compares distance first and earlier push sequence second.
- The frontier limit is exactly `arc_count + 1`, in the inclusive range
  1 through 241.
- Successful output is committed only after the complete run or
  reconstruction succeeds.
- Decrease-key, negative-edge algorithms, and live routing data are deferred.

## Cost

Let `V` be active vertices and `E` be stored directed arcs.

- Under this fixed 16-vertex contract, weighted adjacency-list validation
  initializes constant-size scratch tables and then scans `O(V + E)` graph
  state. A generalized `V`-by-`V` scratch table would instead add
  `O(V^2)` initialization.
- Lazy-duplicate Dijkstra is `O(V + E log(E + 1))`.
- Auxiliary state is `O(V + E)` because the frontier can hold `O(E)`
  snapshots.
- For a simple graph, this becomes `O(V + E log V)`.
- Full result validation is `O(V + E)` because it checks the bounded pop
  trace. After that validation, the predecessor-chain walk and reversal are
  `O(V)`, so the public reconstruction call is `O(V + E)`.

These bounds describe the implemented lazy strategy. They do not assume a
decrease-key operation or a 64-entry Heap.

## Relationship to the course spiral

- **Revisits:** BFS results, weighted route modeling, adjacency lists,
  Priority Queue behavior, binary Heap order, checked arithmetic, and
  predecessor paths.
- **Contrasts:** BFS minimizes edge count; Dijkstra minimizes additive
  nonnegative cost.
- **Introduces:** tentative distance, relaxation, stale lazy entries,
  guarded cost addition, and strategy-accurate complexity.
- **Forwards:** Prim reuses a lazy minimum frontier; later modules compare
  shortest-path and spanning-tree objectives.
