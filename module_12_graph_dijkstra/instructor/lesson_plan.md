# Instructor Lesson Plan - Module 12 Dijkstra

## 14-week delivery override - Week 10 Practical 2 (180 minutes)

This is the authoritative required sequence for the 14-week course; see the
[delivery guide](../../Data_Structures_Course_2026_14_Week_Delivery_Guide.md).
Practical 2 is the sole Week 10 submission. Prepare a bounded release in
which the weight parser, weighted-graph setup/cleanup and integration frame,
Heap frontier, and their boundary tests are supplied. Do not assign the
untouched Stage E package, its autopsy, or its extra tests as separate work.

| Required contact activity | Minutes |
|---|---:|
| Retrieve BFS versus weighted-cost objectives | 12 |
| Trace the canonical tentative-distance and predecessor states | 18 |
| Formalize strict relaxation, stale entries, and the nonnegative rule | 15 |
| Cognitive Pause and immediate calibration | 10 |
| Read the supplied parser/frontier/integration contracts | 10 |
| Complete the bounded Dijkstra run loop | 30 |
| Complete bounded path reconstruction | 18 |
| Break and build reset | 10 |
| Run supplied boundary tests and author one focused core regression | 22 |
| Compare BFS, linear-Priority-Queue Dijkstra, and Heap Dijkstra | 20 |
| Assemble range, preservation, complexity, and scope evidence | 10 |
| Submit the single Practical 2 artifact and exit check | 5 |
| **Total** | **180** |

The comparison synthesis belongs inside Practical 2. The fuller two-meeting
sequence retained below is an optional instructor resource only; it neither
extends the contact budget nor creates asynchronous student requirements.

## Module question

> BFS minimizes the number of edges. How can we minimize total cost when
> different edges have different weights?

## Five-gate control

1. Gate A releases only the informal inquiry.
2. Gate B releases formal representation after first models are preserved.
3. Gate C releases investigation after the three-target pause.
4. Gate D releases textbook/models after Sections A through F are preserved.
5. Gate E releases lab, tests, evidence, and autopsy after retrieval.

Do not display answers, formal state names, or code before their gate.

## Before class

- Verify standard and linear headings/tasks match.
- Verify Stage A forbidden-vocabulary scan is empty.
- Confirm canonical edges, states, and counters.
- Build core, solution, student-template, and autopsy targets.
- Prepare one visible and one exact linear route model.
- Keep all fixtures synthetic.
- Arrange typed, dictated, tactile, verbal, and drawing-equivalent response
  options.

## Optional full-package resource sequence - Meeting A

### 1. Gate A retrieval - 8 minutes

Release the inquiry only. Briefly retrieve the prior layer method without
naming the new algorithm. Students preserve individual answers.

### 2. Few links versus few minutes - 12 minutes

Students find the direct A,E route, then add its 14 minutes. They separately
add A,C,D,E to 6.

Ask:

- What did the layer rule optimize?
- Which assumption failed when link times differed?

Do not reveal Dijkstra vocabulary yet.

### 3. Best-total cards - 15 minutes

Students make informal cards:

```text
after A: B9/A, C2/A, E14/A
after C: B4/C, D4/C
```

Require a reason for choosing C/2 next.

### 4. Old and equal cards - 10 minutes

Compare:

```text
B/9 versus B/4
D existing 4 versus B proposal 4
E existing 14 versus B proposal 12
```

Preserve disagreement about equality for later calibration.

### 5. Gate B formal reveal - 24 minutes

Introduce one term at a time:

1. weight and path cost;
2. Dijkstra and nonnegative precondition;
3. tentative and finalized distance;
4. predecessor and `INF`;
5. Frontier and stable Heap snapshot;
6. strict relaxation;
7. lazy duplicate and stale;
8. numeric guard; and
9. reconstruction.

Use “finalized” consistently. Do not add “settled.”

### 6. Exactly-three-target Cognitive Pause - 5 minutes

Students use no notes or tools. Extended time uses the identical fixture and
targets.

Required targets:

1. BFS goal versus cost;
2. pop B/4 and apply strict equality;
3. skip B/9 and reconstruct E.

### 7. Pause calibration - 12 minutes

Display:

```text
Target 1: A,E is 1 edge/14; A,C,D,E is 3 edges/6
Target 2: D unchanged; E=12/B; frontier D4,B9,E12,E14
Target 3: B9 stale; A,C,D,E cost6; F model-only INF
```

Students retain first attempts and label corrections.

### 8. Gate C canonical trace - 25 minutes

Complete every pop and state transition. Stop at:

- C improving B and D;
- stable B/D tie;
- B's equal zero-edge proposal;
- E improving 14 to 12 to 6;
- three stale skips.

Require exact counters:

```text
attempts 8, successes 7
pushes 8, pops 8
stale 3, peak 4
Heap comparisons 17
```

### 9. Exit ticket - 6 minutes

Prompt:

> Why does equality cause no update, and why does a stale snapshot cause no
> edge scan?

## Optional full-package resource sequence - Between meetings

Students preserve Sections A through F. Review work for the objective,
tentative/finalized distinction, strict comparison, stale test, and numeric
guard. Do not grade drawing quality.

## Optional full-package resource sequence - Meeting B

### 1. Gate D retrieval - 12 minutes

Before opening notes, retrieve:

1. BFS versus Dijkstra goal;
2. strict relaxation;
3. stale condition;
4. nonnegative requirement;
5. overflow guard;
6. E predecessor chain; and
7. actual lazy complexity.

Use textbook and models only to correct gaps.

### 2. Gate E public contracts - 12 minutes

Review:

- `WeightedGraph` ownership and validation;
- parser status distinctions;
- supplied `DijkstraFrontier` limit 241;
- result fields and inactive sentinels;
- output-last preservation; and
- cleanup on every exit.

### 3. TODO 1 parser - 20 minutes

Implement and test:

```text
"  +0 " success
"14" success
"-1" negative
"" and "4x" malformed
overflow and SIZE_MAX out of range
```

Require output markers before each failure test.

### 4. TODO 2 Dijkstra loop - 32 minutes

Work in checkpoints:

1. local canonical initialization;
2. source push;
3. pop trace;
4. stale-before-scan branch;
5. finalization;
6. guarded strict relaxation;
7. push-before-distance/predecessor commit;
8. counter/peak capture;
9. failure mapping and cleanup; and
10. output-last commit.

Run the smallest canonical test after each checkpoint.

### 5. TODO 3 reconstruction - 20 minutes

Test E, A, F, invalid destination, repeated predecessor, and missing-source
chain. Verify output preservation.

Emphasize that result-only validation cannot prove predecessor edges
existed. Graph-aware tests must check each edge and independently sum cost.

### 6. Exactly three student tests - 18 minutes

Require:

1. parser and range preservation;
2. lazy stale trace and equal predecessor; and
3. paths, source, unreachable, and preservation.

Do not accept three renamed canonical copies.

### 7. Spiral 4 synthesis - 18 minutes

Define an **abstract data type (ADT)** as the behavior promised independent
of storage, and an **application programming interface (API)** as the named
operations code calls. An **implementation** is the code and storage choice
that carries out those operations.

Using the same canonical graph and source A:

1. run full BFS while ignoring weights;
2. run Dijkstra with Module 10's unsorted linear Priority Queue;
3. run Dijkstra with the Heap Frontier;
4. compare paths, add/remove calls, record comparisons, and API calls; and
5. label shared ADT behavior versus implementation-specific details.

Expected comparison:

```text
BFS:     A,E       5 enqueue, 5 dequeue
linear:  A,C,D,E   8 insert, 8 extract-min, 14 comparisons
Heap:    A,C,D,E   8 push, 8 pop, 17 comparisons
```

Retrieve the linear pre-removal sizes
`1,3,4,4,4,3,2,1`, whose `(size-1)` counts sum to 14. Map
`insert`/`extract-min` to Heap `push`/`pop`. Stable-min behavior belongs to
the Priority Queue ADT; unsorted scanning and Heap sifting belong to their
implementations. Emphasize that this small fixture does not make the Heap's
comparison count smaller.

Contrast:

```text
BFS                     O(V+E), different goal
linear lazy backend     O(V+E^2)
Heap lazy backend       O(V + E log(E+1))
simple Heap case        O(V + E log V)
auxiliary state         O(V+E)
```

No decrease-key is implemented. Debug Heap checking is separate work.

### 8. Bounded overflow autopsy - 10 minutes

Students predict before running:

```text
SIZE_MAX-3 + 5 wraps to 1
1 < 20 causes false relaxation
correct status DIJKSTRA_COST_RANGE
```

Separate arithmetic correctness, memory bounds, stale checking, and model
meaning.

### 9. Capacity and scope - 8 minutes

Retrieve:

```text
16*15 = 240 arcs
source + successful relaxations <= 241 snapshot insertions
Module 11 cap 64
Module 12 cap 241
```

Any smaller configured limit returns `DIJKSTRA_LIMIT`. Discuss synthetic
weights, authenticity, changing conditions, parallel work, fairness, and
security limits.

## Formative misconceptions

Intervene when a student:

- claims BFS minimizes unequal total weight;
- calls a discovered distance finalized;
- finalizes a stale snapshot;
- scans edges before stale checking;
- updates predecessor on equality;
- treats vertex ID as an equal-distance tie-break;
- rejects a zero-weight edge;
- accepts negative text into an unsigned type;
- adds before checking the range;
- stores `DIJKSTRA_INF` as a finite candidate;
- confuses cost-range failure with unreachable;
- claims the returned path is unique;
- trusts a predecessor chain without a bound;
- claims result-only validation proves graph edges;
- quotes a decrease-key bound;
- includes debug checking in normal Heap comparisons;
- assumes capacity 64 covers 240 arcs; or
- treats modeled output as operational truth.

## Extension prompts

Use only after core correctness:

- What result changes if equal relaxation is allowed?
- Why can zero-weight cycles remain safe under strict relaxation?
- How would direct-array Dijkstra differ from a linear lazy Queue?
- What contract would be needed for time-changing weights?
- Why does Bellman-Ford permit negative edges?
- How could a graph-aware result validator strengthen the certificate?

## Submission check

For the 14-week path, require only the single Practical 2 artifact:

- preserved Stage A and Cognitive Pause;
- canonical BFS/Dijkstra contrast;
- exact arrays, trace, and seven counters;
- bounded Dijkstra loop and path reconstruction;
- one focused student core regression plus the supplied suite output;
- negative/range/output-preservation evidence;
- E/A/F reconstruction evidence;
- linear/Heap actual complexity;
- 241-versus-64 explanation; and
- bounded integrity/security claims.

The parser implementation, full autopsy, and additional Stage E tests are
optional resources and are not a second submission.
