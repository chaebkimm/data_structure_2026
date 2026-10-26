# Week 14 lab — DSU and Kruskal in one artifact

Read [the lesson](textbook.md). DSU is introduced in this lab; no earlier DSU
submission is assumed. Work from the combined release in [the manifest](README.md).

## Exactly three TODOs

1. Complete `dsu_find` in `code/dsu.c`: use the supplied bounded root locator,
   then the supplied compression helper; publish the representative last.
2. Complete `dsu_union` in that file: locate both roots before mutation,
   compress, handle same-set success without a merge, and merge by component
   size with smaller-root-ID ties. Maintain sizes and component count.
3. Complete `select_sorted_edges` in `code/mst/starter/kruskal.c` in the
   release (the repository source is `../code/starter/kruskal.c` relative to
   this week's directory). Track examinations, self-loop skips, cycle skips,
   selected edges, and final component count.

Make-set, graph construction/loading, sorting, totals, diagnostic validation,
and Prim are supplied. Do not implement them or submit a separate list repair.
Use Module 13's sorting reasoning to explain the edge order; no new sorting
implementation is part of this artifact.

From `code/` run:

```sh
make starter-compile
make starter-core
make student-tests
```

Starter compilation is expected to pass and behavioral tests to fail before
completion. In the repository, edit the existing Module 14 Kruskal starter
alongside this week's `dsu.c`; in the release, edit the local copied starter.
The full supplied MST suite also runs the supplied Prim comparison. A failure
there is evidence to inspect DSU/support integration, not a Prim assignment.

Add three student cases: a same-component union that preserves component count;
a disconnected graph producing V−c selected edges; and parallel edges or a
self-loop that proves a cycle-producing/heavier edge is not accepted.
Use different data from the canonical fixture. Include an invalid-ID failure
preservation assertion. Run the supplied tests for ties, negative weights,
empty/singleton input, invalid endpoints, and checked large totals.

On supported toolchains run memory/undefined-behavior checks:

```sh
make starter-core BUILD_DIR=build-sanitize CFLAGS='-std=c11 -Wall -Wextra -Wpedantic -g -fsanitize=address,undefined -fno-omit-frame-pointer'
```

## One submission

Include the two completed C files, student tests, compiler/test output, a
parent/size trace before and after compression, and an edge-decision ledger.
Explain V−c, the distinction from Dijkstra, and one supplied Prim observation.

Fold in a short individual synthesis: identify the invariant linking DSU
membership to accepted edges, then select hash or AVL lookup for one stated
workload. Do not repeat a full AVL/Hash lab.

For the capstone checkpoint, integrate this backend into the existing project,
run one connected and one disconnected synthetic fixture, and record interface,
ownership, and validation evidence. Earlier BFS/Dijkstra/index work is already
assembled before this week. Report integration blockers explicitly rather than
starting a new toolkit in this class. The cumulative report and defense use
the separate final-assessment period.

| Criterion | Weight |
|---|---:|
| DSU/Kruskal invariants and trace | 20% |
| Functional correctness and boundary cases | 25% |
| Bounds, arithmetic, and state preservation | 20% |
| Tests and reproducible evidence | 15% |
| Complexity and representation selection | 10% |
| Individual synthesis and interpretation | 10% |

This is one weekly programming artifact. Capstone integration/report/defense
are assessed under their own criteria; algorithm correctness is not scored
twice. Prim implementation and the original complete package labs are optional.
