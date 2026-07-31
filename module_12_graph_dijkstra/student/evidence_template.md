# Module 12 Evidence Record

Name: ____________________________
Date: ____________________________
Compiler or instructor CI: __________________________________________

CI means a separate computer that automatically builds and tests submitted
code.

## 1. Preserved reasoning

- Stage A response location: _________________________________________
- Three-target pause location: _____________________________________
- Correction labels: _______________________________________________
- Evidence that changed my model: __________________________________

## 2. Canonical input

```text
vertex IDs:
source:
directed weighted edges:
weight meaning:
```

Why are the weights additive and synthetic?

____________________________________________________________________

## 3. BFS contrast

```text
BFS path A to E:
edge count:
total cost:
lower-cost Dijkstra path:
edge count:
total cost:
```

## 4. Exact Dijkstra trace

```text
finalized order:
final distances A through F:
final predecessors A through F:
relaxation attempts:
successful relaxations:
pushes:
pops:
stale skips:
peak frontier:
Heap record comparisons:
```

Equal D proposal and strict action:

____________________________________________________________________

## 5. Snapshot evidence

```text
first B snapshot:
improved B snapshot:
first E snapshot:
second E snapshot:
final E snapshot:
stale snapshots:
```

Why stale snapshots are skipped before edge scanning:

____________________________________________________________________

## 6. Path reconstruction

```text
backward E chain:
forward E path:
independent cost sum:
source-to-source path:
F status:
```

How the predecessor certificate is checked:

____________________________________________________________________

## 7. Numeric and input safety

Negative-text rejection evidence: __________________________________

```text
INF definition:
addition guard:
candidate-equals-INF action:
range status:
```

The **caller** is code requesting work; **output** is where its answer is
written.

How status failure preserves caller output:

____________________________________________________________________

## 8. Three unfinished coding tasks (TODOs)

A **TODO** is a marked task that is not finished yet.

### TODO 1 - parse weight text

Smallest relevant test: ____________________________________________

How negative text is rejected before unsigned conversion:

____________________________________________________________________

### TODO 2 - Dijkstra loop

Smallest relevant test: ____________________________________________

How strict relaxation, stale skipping, and cleanup are proved:

____________________________________________________________________

### TODO 3 - reconstruct path

Smallest relevant test: ____________________________________________

How malformed or unreachable results preserve output:

____________________________________________________________________

## 9. Exactly three original tests

### Test 1 - parser and range preservation

Claim and key assertions: __________________________________________

### Test 2 - lazy stale trace and equal predecessor

Claim and key assertions: __________________________________________

### Test 3 - paths, source, unreachable, and preservation

Claim and complete preservation snapshot: __________________________

## 10. Build and comparison evidence

A **backend** is the storage method behind a collection.

Warning-enabled command: ___________________________________________

Core-test result: __________________________________________________

Student-test result: _______________________________________________

Linear-backend result and count: ___________________________________

Heap-backend result and count: _____________________________________

## 11. Spiral 4 synthesis

An **abstract data type (ADT)** states what operations do without requiring
one storage method. An **application programming interface (API)** is the
set of named operations code calls. An **implementation** is the code and
storage choice that performs those operations.

Use the same canonical graph and source A:

```text
BFS path with weights ignored:
BFS enqueue/dequeue counts and API names:
linear-Priority-Queue Dijkstra path:
linear insert/extract-min counts:
linear pre-removal sizes and comparison sum:
linear API names:
Heap Dijkstra path:
Heap push/pop and comparison counts:
Heap API names:
```

Shared Priority Queue ADT behavior:

____________________________________________________________________

Linear-only and Heap-only implementation details:

____________________________________________________________________

Why the small-fixture comparison does not replace the growth analysis:

____________________________________________________________________

## 12. Complexity and storage limits

A **capacity** is the maximum number of records storage can hold. A
**parallel edge** repeats a start/end pair; a **self-loop** returns to its
starting vertex; a **simple graph** has neither. **Decrease-key** means
lowering a priority already stored in a Queue. **Auxiliary state** is extra
storage beyond the input.

```text
lazy Heap time:
auxiliary state:
simple-graph time:
linear lazy time:
```

Why no decrease-key bound is claimed:

____________________________________________________________________

Explain possible 241 snapshot insertions versus capacity 64:

____________________________________________________________________

Honest action on Queue `FULL`:

____________________________________________________________________

## 13. Safe overflow autopsy

```text
frozen dist:
weight:
old destination distance:
faulty wrapped candidate:
correct guard result:
correct status:
```

Exact repair and regression:

____________________________________________________________________

## 14. Integrity and model scope

Two integrity failures this module can detect:

____________________________________________________________________

Four facts the result cannot prove about real work or security:

____________________________________________________________________

What F's `INF` means:

____________________________________________________________________

## 15. Final synthesis

In three sentences, connect BFS's goal, strict relaxation, lazy snapshots,
and reconstructed modeled cost.

____________________________________________________________________

____________________________________________________________________
