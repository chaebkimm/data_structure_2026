# Stage C - Prim and Kruskal Investigation

Name: ____________________________
Date: ____________________________

Use this linear-format worksheet after the Cognitive Pause. Preserve
Sections A through F before opening Stage D. Sections G through I are later
work. All graphs and weights are synthetic.

## Quick reference

`V` means vertex count, `E` means logical undirected-edge count, and `c`
means component count. A spanning forest has `V-c` selected edges.

Prim's `key[v]` is one cheapest known crossing-edge weight, not a
source-to-vertex path cost. Kruskal accepts a sorted edge only when its
endpoint DSU roots differ.

A **signed weight** may be negative, zero, or positive. **Normalized
endpoints** place the smaller vertex ID first. An **incident record** is one
stored view of an edge from one endpoint. **Stable** means earlier
equal-ranked work leaves first.

The canonical graph has these logical edges:

1. ID 0 joins A and B with weight 4.
2. ID 1 joins A and C with weight 4.
3. ID 2 joins B and C with weight 1.
4. ID 3 joins B and D with weight 5.
5. ID 4 joins C and D with weight 2.
6. ID 5 joins C and E with weight 3.
7. ID 6 joins D and E with weight 3.
8. ID 7 joins A and E with weight 10.

Prim starts at A, scans incident records by edge ID, changes a key only on a
strictly smaller proposal, and uses stable insertion order for equal Heap
keys. Kruskal sorts by signed weight, normalized endpoints, then edge ID.

## A. Separate objectives and representations - 12 points

### A1. Show two representations - 4 points

Write the canonical graph as one logical edge list and as adjacency rows for
A through E. Explain why an ordinary undirected edge appears once in the
edge list but twice among incident adjacency records.

Response: ___________________________________________________________

### A2. Contrast shortest paths and minimum connection - 5 points

Dijkstra from A records `AB, AC, CD, CE`. Find its selected-edge sum and
its A-to-C path cost. Then find a lower-total spanning tree and state its
A-to-C path cost. Explain why each result can be correct for a different
goal.

Response: ___________________________________________________________

### A3. State the input contract - 3 points

State how this module treats a negative weight, self-loop, parallel edge,
invalid endpoint, and directed connection. Explain why preserving logical
edge IDs matters.

Response: ___________________________________________________________

## B. Trace lazy key-based Prim - 16 points

### B1. Initialize at A - 4 points

Record `key`, `parent`, and `in_tree` for A through E before the first pop.
Then process A and show the resulting frontier in expected removal order.

Response: ___________________________________________________________

### B2. Complete every pop - 8 points

Complete the full canonical trace. A snapshot is stale when its saved key
differs from the current key. A record for a vertex already selected is
also skipped.

For each of eight pops, record the saved vertex/key, whether it is current,
stale, or already selected, the selected edge if any, every key/parent
change, and the frontier afterward.

Pop 1: ______________________________________________________________

Pop 2: ______________________________________________________________

Pop 3: ______________________________________________________________

Pop 4: ______________________________________________________________

Pop 5: ______________________________________________________________

Pop 6: ______________________________________________________________

Pop 7: ______________________________________________________________

Pop 8: ______________________________________________________________

Record the selected IDs, total, pushes, pops, stale pops,
already-selected pops, frontier peak, incident scans, eligible crossing
tests, and key improvements.

Explain why the D-to-E proposal of 3 does not replace E's existing key and
parent.

Response: ___________________________________________________________

### B3. Restart for a forest - 4 points

Use six vertices A through F with these logical edges:

1. ID 0 joins A and B with weight 4.
2. ID 1 joins B and C with weight -2.
3. ID 2 joins A and C with weight 3.
4. ID 3 joins D and E with weight 1.
5. ID 4 also joins D and E with weight 1.
6. ID 5 joins E to itself with weight -9.

F is isolated. Trace Prim's ascending-ID restarts, strict parallel-edge tie,
and self-loop handling. Record selected IDs, component roots, component
count, selected count, total, and the `V-c` check.

Response: ___________________________________________________________

## C. Trace sorted-edge Kruskal - 16 points

### C1. Sort the canonical edges - 4 points

Sort all eight logical edges by signed weight, normalized first endpoint,
normalized second endpoint, then edge ID. Show every comparison field needed
to resolve a tie.

Response: ___________________________________________________________

### C2. Complete the DSU decision ledger - 8 points

Process all eight canonical edges, even after enough edges have been
selected. Record roots before the decision, add or skip, groups afterward,
and running total.

Edge 1: _____________________________________________________________

Edge 2: _____________________________________________________________

Edge 3: _____________________________________________________________

Edge 4: _____________________________________________________________

Edge 5: _____________________________________________________________

Edge 6: _____________________________________________________________

Edge 7: _____________________________________________________________

Edge 8: _____________________________________________________________

Record selected IDs, examined-edge count, cycle-skip count, self-loop-skip
count, component count, and final total.

Response: ___________________________________________________________

### C3. Keep sorting and arithmetic safe - 4 points

Explain why a comparator must use less-than and greater-than checks rather
than subtracting signed 64-bit weights. Then explain why Kruskal still
examines self-loops and parallel IDs as distinct input records.

Response: ___________________________________________________________

## D. Validate structure and minimum cost - 16 points

### D1. Check the structural certificate - 5 points

A **certificate** is stored evidence that another operation can check. List
the checks for graph counts, selected input IDs, endpoints, duplicate IDs,
self-loops, cycles, component membership, `V-c`, inactive fields, and total
weight. Explain why selected count alone is insufficient.

Response: ___________________________________________________________

### D2. Check minimum cost separately - 4 points

An **exchange check** considers replacing a selected edge. For every
unselected non-loop edge, compare its weight with the greatest edge weight
on the selected path between its endpoints. State what a smaller, equal, or
larger unselected weight implies.

Apply that check to every unselected canonical edge.

Response: ___________________________________________________________

### D3. Observe different valid tie results - 4 points

Use this all-weight-1 square:

1. ID 0 joins A and D with weight 1.
2. ID 1 joins C and D with weight 1.
3. ID 2 joins A and B with weight 1.
4. ID 3 joins B and C with weight 1.

Run deterministic Prim from A and deterministic Kruskal under the stated
tie rules. Record both selected ID sets and totals. Explain what must agree
and what may differ.

Response: ___________________________________________________________

### D4. Interpret negative and disconnected input - 3 points

Run Kruskal on the six-vertex boundary graph from B3. Explain the sorted
self-loop decision, parallel-edge decision, negative-edge decision, forest
count, and why Dijkstra's negative-weight rule is different.

Response: ___________________________________________________________

## E. Analyze cost, representation, and resilience - 12 points

### E1. State actual costs - 4 points

Let `V` mean vertices and `E` mean logical edges. `O(n)` means work can grow
with all `n` items; `O(log n)` grows with the number of repeated halvings.
**Auxiliary state** means extra storage beyond the input.

Explain these four costs:

1. indexed-adjacency lazy Prim:
   `O(V + E log(E + 1))`;
2. Prim auxiliary state: `O(V + E)`;
3. Kruskal sorting: `O(E log E)`; and
4. Kruskal DSU work: near-linear after sorting.

Why would rescanning all incident records for every selected vertex add an
unadvertised `O(VE)` term?

Response: ___________________________________________________________

### E2. Choose by representation and density - 4 points

An edge list stores one logical record per edge. An adjacency list groups
incident edges by vertex. A matrix uses a row and column position for every
vertex pair. **Sparse** means relatively few possible edges are present;
**dense** means many are present.

Recommend and justify:

1. Kruskal or Prim for an already sorted edge list;
2. Kruskal or Prim for an indexed adjacency list;
3. Heap Prim or matrix Prim for a very dense simple graph; and
4. any conversion cost that must be included.

Response: ___________________________________________________________

### E3. Analyze resilience honestly - 4 points

For one canonical MST, remove BC. State the resulting groups. Then add one
unselected edge and state exactly which single-edge failures gain a backup
route. Explain why one extra edge need not protect the whole network and why
minimum cost does not prove resilience, genuine authorized input, enough
link capacity, or security. Link capacity means how much a link can carry.

Response: ___________________________________________________________

## F. Preserve numeric and spiral contracts - 8 points

### F1. Accumulate a mathematical total - 4 points

Use triangle weights:

1. A-B has weight 2,000,000,000.
2. B-C has weight 2,000,000,000.
3. A-C has weight 2,100,000,000.

Find the MST and explain why a signed 32-bit total is insufficient.

`INT64_MAX` is the largest signed 64-bit value. A selected set may contain
weights `INT64_MAX`, `1`, and `-1`. Explain why the mathematical total fits
even though that array order first forms a running subtotal outside the
signed 64-bit range. State why total validation must be order-independent.
The **caller** is code requesting work; explain why a truly out-of-range
final total must preserve caller output.

Response: ___________________________________________________________

### F2. Connect the final spiral - 4 points

Define the distinct roles of the Heap, DSU, Dijkstra distance, Prim key, and
AVL invariant. Then state how local decisions in Prim and Kruskal preserve a
global minimum-connection goal without proving trust or resilience.

Response: ___________________________________________________________

## G. Design exactly three tests - later work - 9 points

### G1. Prim lazy trace and restart - 3 points

Design one test category covering the exact canonical Prim result and
counters, strict equal-key behavior, all obsolete-pop kinds, and the
six-vertex restart fixture.

Response: ___________________________________________________________

### G2. Kruskal filtering and ties - 3 points

Design one test category covering the exact canonical ledger, all-weight-1
square, negative edge, parallel IDs, self-loop, cycle skips, and comparator
extremes.

Response: ___________________________________________________________

### G3. Boundaries, preservation, and cross-validation - 3 points

**Cross-validation** compares independent methods on the same input. An
**allocation** is storage reserved while a program runs.

Design one test category covering singleton and empty boundaries, invalid
endpoints/state, limits, allocation failure, order-independent totals,
out-of-range totals, structural and minimum-result corruption, unchanged
failure output, and Prim/Kruskal total agreement.

Response: ___________________________________________________________

## H. Complete the bounded cycle autopsy - later work - 6 points

### H1. Locate the first wrong decision - 2 points

For sorted edges AB1, BC2, AC3, explain why testing raw endpoint inequality
accepts one edge that representative-root comparison must reject.

Response: ___________________________________________________________

### H2. Repair and verify - 2 points

State the correct find, compare, select, and union order. Record the expected
selected IDs, total, component count, and validator result.

Response: ___________________________________________________________

### H3. Add a regression - 2 points

A **regression test** remains after repair so the defect does not return.

Design a regression test that distinguishes the faulty three-edge result
from the correct two-edge result without relying only on total weight.

Response: ___________________________________________________________

## I. Synthesize - later work - 5 points

### I1. Select an algorithm - 2 points

Write a concise recommendation for Prim or Kruskal for one supplied
representation and density. Include conversion cost and the actual
implemented complexity.

Response: ___________________________________________________________

### I2. State the integrity boundary - 2 points

**Integrity** means stored state obeys its required rules.

Distinguish a structurally valid forest, a minimum forest, and a resilient
or trustworthy real system.

Response: ___________________________________________________________

### I3. Answer the module question - 1 point

> How can we connect all monitoring sites at minimum total cost, and why is
> that different from finding the cheapest route from one source?

Response: ___________________________________________________________
