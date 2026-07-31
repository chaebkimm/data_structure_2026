# Instructor Lesson Plan - Module 15 Prim and Kruskal

## Module question

> How can we connect all monitoring sites at minimum total cost, and why is
> that different from finding the cheapest route from one source?

## Five-gate control

1. Gate A releases only the ordinary-language inquiry.
2. Gate B releases representation, the three-target pause, and vocabulary.
3. Gate C releases paired investigation worksheets after pause correction.
4. Gate D releases textbook and models after Sections A through F are
   preserved.
5. Gate E releases lab, evidence, rubric, autopsy, headers, starter code, and
   visible tests after retrieval.

Do not display formal names, exact answers, formulas, or code before their
gate.

## Before class

- Confirm standard and linear headings, IDs, values, tasks, and scoring
  match.
- Confirm the Stage A embargo scan is empty.
- Confirm the canonical Prim and Kruskal traces and all counters.
- Build solution, starter compile, extensions, student template, and
  isolated autopsy.
- Prepare one visible graph model and its exact linear equivalent.
- Keep all site and cost data synthetic.
- Offer typed, dictated, tactile, verbal, tabular, and drawing-equivalent
  responses.
- Do not grade visual neatness or arithmetic speed.

## Meeting A - Discover and formalize, 90 minutes

### 1. Gate A retrieval - 8 minutes

Release only the initial inquiry. Students preserve individual answers.
Read the eight offers aloud once without commentary.

### 2. One route versus one network - 12 minutes

Students price A-C-E, then combine the cheapest A-routes to B through E.
Ask:

- Which job is centered on A?
- Which job asks only that all sites can reach one another?
- Why is a line reused by several routes purchased once?

Do not name Dijkstra, MST, Prim, or Kruskal yet.

### 3. Two informal construction rules - 15 minutes

Trace the reached-sites rule, then the separate-groups rule. Preserve
disagreement at equal weights.

Expected ordinary-language checkpoints:

```text
grow:  IDs 0,2,4,5, total10
merge: IDs 2,4,5, skip6, ID0, total10
```

Stage A may stop the second rule once all sites join. Explain later that the
formal Kruskal implementation scans all edges for a complete ledger.

### 4. Gate B representation reveal - 20 minutes

Introduce one term at a time:

1. graph, vertex, undirected edge, signed weight;
2. path, connected, cycle, tree;
3. spanning tree, MST, component, forest, MSF;
4. logical edge, edge list, incident and adjacency records;
5. Dijkstra shortest-path tree versus MST;
6. Prim cut, crossing edge, key, parent, and frontier;
7. lazy Heap snapshots, strict tie, and stale check;
8. Kruskal sorted edges and DSU roots;
9. structural versus minimum validation; and
10. resilience and bridge.

Require students to restate that a Prim key is one edge weight, not a source
distance.

### 5. Exactly-three-target Cognitive Pause - 5 minutes

No notes, vocabulary, classmates, or coding tools. Extended-time versions
use the same three targets and fixtures:

1. source paths versus network total;
2. complete lazy Prim trace; and
3. Kruskal, isolated F, and resilience.

### 6. Pause calibration - 10 minutes

Display:

```text
Target1: edge sums13/10; A-C costs4/5; selected count4
Target2: IDs0,2,4,5; total10; stale C4,D5,E10
Target3: sorted add/skip ledger; with F, c=2 and selected4
```

Students retain first attempts and label corrections.

### 7. Gate C investigation start - 15 minutes

Complete Sections A and B1 together. Then begin the exact Prim trace.
Require a distinction among:

- incident scan;
- eligible crossing test;
- strict key improvement;
- stale pop; and
- already-in-tree pop.

Students finish and preserve Sections A through F before Meeting B.

### 8. Exit ticket - 5 minutes

Prompt:

> Why can a shortest-path tree have a larger selected-edge sum than an MST,
> and why can an MST contain a nonshortest route from A?

## Between meetings

Review Sections A through F for:

- objective separation;
- exact canonical trace;
- strict equality;
- representative-root decision;
- negative and disconnected rules;
- structural versus minimum validation;
- order-independent total; and
- honest resilience limits.

Return one focused feedback note. Do not release Stage D until the preserved
core is present.

## Meeting B - Implement and verify, 90 minutes

### 1. Gate D retrieval - 10 minutes

Before opening the textbook, retrieve:

1. `V-c`;
2. Dijkstra distance versus Prim key;
3. Prim stale condition and strict tie;
4. Kruskal root comparison;
5. negative-weight rule;
6. canonical totals; and
7. one resilience limitation.

Use the textbook and models only to correct gaps.

### 2. Finish exact traces - 12 minutes

Complete the canonical Kruskal ledger and the boundary fixture:

```text
boundary Prim IDs2,1,3
boundary Kruskal IDs1,3,2
components3, selected3, total2
```

Then compare the all-weight-1 square, where valid edge sets differ but both
totals are 3.

### 3. Gate E public contract - 10 minutes

Review:

- four headers and fixed limits;
- graph helpers and dense logical IDs;
- result fields and inactive zero records;
- exact statuses;
- output-last preservation;
- supplied indexed adjacency, Heap, DSU, sorting, and total logic; and
- explicit `O(V + E + EV)` validation, whose minimum-cost phase is
  `O(EV)`.

### 4. Implementation cluster 1 - 12 minutes

In `starter/prim.c`, complete restart, pop, stale-first filter,
already-selected filter, and selected-edge storage. Test empty, singleton,
then the first three canonical pops.

### 5. Implementation cluster 2 - 14 minutes

Complete indexed incident scanning, strict improvement, and
push-before-commit. Run the canonical test after each checkpoint. Require
exact counters before proceeding.

### 6. Implementation cluster 3 - 12 minutes

In `starter/kruskal.c`, complete full sorted scanning, self-loop counting,
root comparison, storage, and union. Use the triangle before the full
canonical graph.

### 7. Three tests and explicit validation - 8 minutes

Students state each claim before assertions:

1. Prim lazy trace and restart;
2. Kruskal filtering and ties; and
3. boundaries, preservation, and cross-validation.

Call `mst_forest_validate` explicitly. Do not hide it in timed algorithm
metrics.

### 8. Numeric boundary and safe autopsy - 6 minutes

Retrieve:

```text
large MST total 4,000,000,000
INT64_MAX + 1 - 1 has fitting mathematical total INT64_MAX
```

Then run the isolated endpoint-versus-root autopsy. Students name the first
wrong decision and add a structural regression assertion.

### 9. Recommendation and resilience exit - 6 minutes

Students submit a four-sentence memo naming representation, density,
conversion cost, actual complexity, and resilience limitation. Close with
the macro-question.

## Formative misconceptions

Intervene when a student:

- calls a Prim key a source distance;
- claims a shortest-path tree must minimize its edge sum;
- chooses globally cheapest edges without a cycle check;
- compares raw Kruskal endpoints instead of representative roots;
- rejects a negative MST edge;
- selects a negative self-loop;
- collapses parallel IDs;
- changes a key on equality;
- checks membership before stale key and changes required counters;
- scans the flat incident array per vertex and still claims the indexed
  bound;
- stops formal Kruskal early but reports a complete ledger;
- requires Prim and Kruskal edge IDs to match under ties;
- treats `V-c` alone as a validity proof;
- claims structural validity proves minimum cost;
- adds signed weights in array order and rejects a fitting canceled total;
- subtracts comparator weights;
- hides full validation inside normal complexity;
- calls a disconnected result one spanning tree; or
- claims an MST supplies backup service or trustworthy data.

## Extension prompts

Use only after core correctness:

- When do distinct weights guarantee a unique MST?
- How could selected-edge IDs be canonicalized after either algorithm?
- How can a matrix implementation change dense-graph cost?
- How could the exchange validator be accelerated with path-maximum
  preprocessing?
- What extra requirement would ensure no selected edge is a bridge?
- How does a directed minimum arborescence differ from an MST?

## Submission check

Require:

- preserved Stage A and pause;
- exact canonical and boundary traces;
- exact Prim and Kruskal counters;
- three implementation clusters;
- exactly three tests;
- structural and minimum validation evidence;
- fitting and out-of-range numeric evidence;
- completed safe autopsy;
- representation/density memo;
- cost-versus-resilience statement; and
- corrected final synthesis.
