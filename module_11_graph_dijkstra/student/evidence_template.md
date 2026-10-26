# Module 11 — Practical 2 Evidence Record

Name: ____________________________  Date: ____________________________
Compiler and version: ________________________________________________

Submit one integrated Week 11 artifact. Refer to existing worksheet
responses instead of copying them again. Stages A–E are checkpoints in the
same practical, not extra submissions. The supplied `student/lab.c` remains
unchanged; include your separate test-driver changes and saved output.

## 1. Preserve prediction and correction

- Initial inquiry location: __________________________________________
- Three-target pause and labeled corrections: ________________________
- Investigation Sections A–F: ________________________________________
- One original claim changed by evidence: ____________________________
- Observation and revised claim: _____________________________________

## 2. State the input and what it models

```text
node IDs and active count:
source:
adjacency lists in inspected order:
positive edge weights:
meaning and units of the synthetic costs:
```

Identify the fixture loader. Explain why adjacency lists, rather than zero
or nonzero matrix cells alone, define edge existence. Confirm you did not
load Module 3's unrelated `edges_init()` fixture for the canonical run.

Input setup location: ________________________________________________

## 3. Record the canonical state

```text
final node_dist A..F:
final found A..F:
final heap size:
observed finalization order and measurement method:
add_node calls, including source:
remove_root calls:
update_value calls:
outgoing-edge inspections:
successful edge changes, excluding source insertion:
peak live heap size:
```

Attach the state after A, C, D, B, and E. Mark the two in-place improvements
and distinguish them from first discoveries. The lab returns arrays, not
trace counters; identify debugger or driver observations accurately.

Trace location: _____________________________________________________

## 4. Prove that positions and IDs stay connected

Provide one state in which a node's ID differs from its heap position.
Explain the costs read by `comp(0,2)` immediately after C. Show one swap's
two inverse-map updates and a live parent/child order check.

```text
live heap IDs:
corresponding distances:
node_heap_pos for each live ID:
checked invariant:
```

Explain why removed map entries may be stale. Do not claim that a non-`-1`
map entry proves membership. Describe singleton behavior and the absence
of a stable tie-order promise.

Heap evidence location: ______________________________________________

## 5. Explain the relaxation decisions

```text
first discovery action:
strictly better known cost action:
equal or larger candidate action:
C's proposal to B:
D's proposal to E:
B's later proposals to D and E:
```

Why can no finalized node improve under the positive-weight assumptions?
Where does the source write `found`, and does it read it? Why is there no
stale-snapshot branch?

Explanation location: ________________________________________________

## 6. Run the actual source and one focused regression

Record the root command and its output:

```sh
make -C module_11_graph_dijkstra/code lab-compile core student-tests
```

From the module directory or the root of the extracted standalone archive:

```sh
make -C code lab-compile core student-tests
```

- Supplied-suite output location: ____________________________________
- Driver includes the actual lab at: _________________________________
- Independent reference used by the suite: ___________________________
- Original test input and prediction: ________________________________
- Assertions and observed result: ____________________________________
- Specific defect the test would detect: _____________________________
- Repeated-run or different-source evidence: __________________________

The original test should isolate one core mistake. Do not add an invalid
input and expect rejection from functions that have no validation API.
Keep full heap-check scans separate from operation counts.

## 7. Compare BFS, linear selection, and heap selection

```text
BFS route to E, edge count, and manually summed cost:
manually verified least-cost route and cost:
linear-Priority-Queue Dijkstra distances:
indexed-heap Dijkstra distances:
how each implementation selects its next item:
Priority Queue ADT behavior versus storage representation:
```

The lab supplies distances only. Label any listed route as a manual
certificate, not a path reconstructed by `min_dist`.

Comparison evidence location: ________________________________________

## 8. State limits and costs

List valid IDs, adjacency lengths, positive listed weights, live-heap
operation preconditions, and representable candidate sums. State that the
source does not validate them or guard addition.

```text
generalized V and E:
insert/remove/update bounds:
one-path repair cost:
full invariant-scan cost:
algorithm time:
auxiliary state:
input cost-matrix storage:
actual fixed array bounds:
```

Limits and analysis location: ________________________________________

## 9. Locate the bounded defect analysis

Choose a position/ID error from [the autopsy](dijkstra_autopsy.md). Preserve
a prediction and name the first divergent comparison or swap, the violated
invariant, and a test that exposes it. This is a short part of the same
evidence record.

Autopsy location: ____________________________________________________

## Submission check

The artifact contains the source-based trace, actual-source test output,
one focused original regression, queue comparison, assumptions, complexity,
and corrected reasoning. The optional lazy-duplicate parser/path library
has a separate contract; its unfinished starter tasks are not added Week
11 work.
