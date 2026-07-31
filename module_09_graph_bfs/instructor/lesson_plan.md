# Instructor Lesson Plan — Module 9 Graph BFS

## Module question

> Which system is reachable in the fewest communication hops when
> relationships may branch, merge, and cycle?

Plan for approximately three contact hours across two meetings. Preserve
the five release gates. Times are adjustable; gates and conceptual targets
are not.

## Before class

1. Run the release-packaging script only after all files and tests are
   verified.
2. Keep Stage B closed until every student preserves Stage A.
3. Keep vocabulary closed until every student preserves the exactly-three
   Cognitive Pause targets.
4. Keep Stage D closed until Stage C Sections A–F are preserved.
5. Keep solution, private extension tests, and instructor materials private.
6. Prepare standard and linear versions together; they contain identical
   vertex IDs, edges, operation order, questions, and scoring.
7. Confirm that drawings, tables, numbered prose, typing, dictation, and
   tactile/verbal models are accepted.

## Meeting A — Model and reason

### 1. Retrieval without formal graph-BFS names — 8 minutes

Ask students to state:

- what a directed edge permits;
- why Module 6 needed one yes-or-no record per vertex;
- which item a Module 7 Queue removes;
- what a pending item meant in Module 8 tree BFS; and
- why a valid tree did not need discovery records.

Do not yet display BFS, Queue, frontier, distance, predecessor, adjacency
list, or complexity notation. Use ordinary language such as “waiting work”
and “number of links.”

### 2. Stage A initial inquiry — 15 minutes

Release one inquiry format. Students use:

```text
0:[1,2]  1:[3]  2:[3]  3:[4]  4:[1]  5:[]
```

They invent a repeatable nearer-first rule, identify the merge at 3, prevent
the cycle through 1, 3, and 4, and represent first arrival. Require
preservation of the initial response. Drawing quality and speed are not
assessed.

Observe rather than correct immediately:

- Does a student remember 3 when it first enters waiting work?
- Does 2 add a second 3?
- Does 4 cause a return to 1?
- Is vertex 5 incorrectly forced into a one-source result?
- Does the student record “previous vertex” and “link count” separately?

### 3. Pair comparison — 5 minutes

Partners identify one shared rule and one unresolved question. A partner
may read or transcribe without changing the author's reasoning.

### 4. Stage B formal reveal — 18 minutes

Release `representation_reveal.md`. Define every new word at first use:

- breadth-first search;
- source and hop;
- discovered and processed;
- frontier;
- distance and predecessor;
- unweighted;
- path reconstruction; and
- unreachable.

Use the five-vertex reveal fixture:

```text
0:[1,2]  1:[3]  2:[3,4]  3:[0]  4:[]
```

Build the state in this order:

1. enqueue source;
2. after success, discover it at distance 0;
3. dequeue and record;
4. inspect ascending outgoing neighbors;
5. for an unseen neighbor, enqueue first;
6. after success, fix discovery, distance, and predecessor.

At `2 -> 3`, stop and ask why a pending vertex already counts as
discovered. At `3 -> 0`, retrieve the cycle rule.

### 5. Exactly-three-target Cognitive Pause — 5 minutes

Read the starting definitions and pause graph aloud. Students then use no
notes, slides, vocabulary, classmates, or coding tools.

The three and only three target headings are:

1. trace Queue and state;
2. stop duplicate waiting work; and
3. reconstruct and report.

Approved extended time uses the identical graph and targets. Responses may
be drawn, typed, dictated, or given as numbered sentences.

### 6. Calibration — 10 minutes

Display the exact answer:

```text
initial [0]
after 0 [1,3]
after 1 [3,2,4]
after 3 [2,4,5]
order 0,1,3,2,4,5
path 0,3,5
vertex 6 unreachable
```

Students preserve the original and add labeled corrections:

```text
Queue
discovery
distance
predecessor
path
unreachable
```

An incorrect initial response is evidence for instruction, not a penalty
when meaningfully corrected.

### 7. Stage C Sections A–C — 25 minutes

Introduce the canonical eight-vertex graph. Complete only the first trace
row as entry support.

Students then:

- initialize source state;
- complete Queue states through vertex 6;
- explain each skipped edge;
- fill final discovered, distance, and predecessor arrays;
- reconstruct the path to 6; and
- explain why equal-hop alternatives do not make the stored answer wrong.

Use the hint ladder:

1. restate what discovered means;
2. identify the Queue front;
3. label the current vertex's distance;
4. check whether the destination was already enqueued;
5. compare one row with the reveal example.

### 8. Exit ticket — 4 minutes

Prompt:

> Why are FIFO order, unweighted edges, and enqueue-time discovery all
> needed for the minimum-hop claim?

Accept a correct causal explanation without requiring formal proof wording.

## Between meetings

Students complete and preserve Stage C Sections A–F before Stage D opens.
Sections D–F cover disconnected input, contracts, and representation cost.
Sections G–I remain later work.

Release Stage D only after the preserved core attempt. Ask students to add
corrections beside earlier work rather than erase it.

## Meeting B — Implement and verify

### 1. Retrieval and textbook calibration — 10 minutes

Without code, ask:

1. When does a vertex become discovered?
2. When does it enter visit order?
3. What does predecessor store?
4. How are source and unreachable distinguished?
5. Which representation scans missing possible edges?

Then permit the concise textbook and models.

### 2. Read the public result — 10 minutes

Students locate:

```text
vertex_count
source
visit_order and visit_count
discovered
distance
predecessor
```

Explain that sentinel 16 is outside every active identifier and possible
distance. Require the words “no predecessor” or “unreachable” in prose.

Review output preservation: every BFS and path function builds a local
candidate and commits only after success.

### 3. TODO 1: matrix BFS — 30 minutes

Students edit only the numbered matrix-BFS TODO. Work in small checks:

1. validate request and graph;
2. initialize the candidate;
3. successfully enqueue and then discover source;
4. dequeue and record;
5. scan row destinations low to high;
6. enqueue then discover an unseen destination;
7. map Queue limit failure;
8. commit on complete success.

The supplied Queue's full validator scans live identifiers. The traversal's
enqueue and dequeue operations use constant-time checks under the valid
Queue precondition; they do not rescan the frontier at every operation.

Run visible tests before proceeding.

### 4. TODO 2: path reconstruction — 18 minutes

Students:

- validate the result;
- reject an inactive destination;
- report unreachable without changing output;
- follow predecessors backward into bounded local storage;
- reverse into source-to-destination order; and
- commit only on success.

Test destination 6, source 0, and unreachable 7.

### 5. Representation bridge — 12 minutes

Show the same vertex-2 outgoing work:

```text
matrix: scan row cells 0 through 7; true at 4 and 5
list:   read two live entries, 4 and 5
```

Point to `data`, `size`, and `capacity`. The list is an array of dynamic
arrays, not a linked list. The support implementation owns growth, sorted
insertion, reciprocal undirected updates, and cleanup.

Separate:

- construction and allocation;
- explicit representation validation; and
- traversal over an already built graph.

### 6. TODO 3: list BFS — 20 minutes

Students reuse the matrix state machine and replace only neighbor
enumeration. Ascending list rows must give equal named result fields.

Build both canonical representations. Queue limit 3 succeeds. Queue limit 2
fails while vertex 1 attempts to add vertex 4 and preserves caller output.

### 7. Student tests — 18 minutes

Require exactly three independently meaningful categories:

1. cyclic/converging exact state;
2. reachable path plus unreachable preservation; and
3. disconnected sparse matrix/list equivalence.

Students state the claim before writing assertions.

### 8. Bounded Graph BFS Autopsy — 12 minutes

Students predict before running `faulty_frontier`.

Frozen fixture:

```text
0:[1,2]  1:[3,4]  2:[3,4]  3:[0]  4:[]
```

Focus on the first divergence:

```text
faulty after 2: [3,4,3,4]
```

The repair is discovery immediately after successful enqueue. The array
bounds and processing budget remain. Do not claim the observed equal-length
duplicates create a wrong hop distance.

### 9. Complexity and security synthesis — 8 minutes

Complete:

| Question | Matrix | Adjacency list |
|---|---:|---:|
| Representation | `O(V²)` | `O(V+E)` |
| Public BFS | `O(V²)` | `O(V+E)` |
| BFS auxiliary state | `O(V)` | `O(V)` |

Construction is separate. A matrix-to-list conversion that scans the full
matrix is `O(V²)`.

Close with:

> Minimum modeled hops is not a claim about authorization, vulnerability,
> exploitability, likelihood, compromise, or real risk.

## Formative checkpoints

Intervene if a student:

- marks only on dequeue;
- marks before a possibly failing enqueue;
- overwrites a predecessor through a later route;
- records on enqueue instead of dequeue;
- treats sentinel 16 as an active vertex;
- calls unreachable traversal a traversal failure;
- reverses neither the predecessor chain nor path output;
- calls dynamic arrays linked lists;
- includes graph construction in the `O(V+E)` traversal claim;
- claims a directed forest is a component decomposition; or
- treats hop count as a security score.

## Extension prompts

Use only after core correctness:

- How could descending neighbor order change predecessor ties?
- Why do minimum distances remain the same?
- Trace the paper-only undirected forest.
- Explain why a 16-vertex chain needs Queue limit 1 but a 16-vertex star
  needs 15.
- Compare explicit full Queue validation with constant-time Queue
  operations under a validated-state precondition.

Do not replace core work with extension work.

## Submission check

Students submit:

- completed three starter TODOs;
- exactly three student-test categories;
- saved visible and student-test output;
- canonical trace and matrix/list comparison;
- reconstructed-path certificate and unreachable evidence;
- list cleanup evidence;
- completed autopsy;
- corrected Cognitive Pause; and
- Queue-to-tree-BFS-to-graph-BFS synthesis.
