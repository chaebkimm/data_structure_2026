# Stage C — Investigation: Indexed-Heap Dijkstra (Linear Form)

Name: ____________________________  Date: ____________________________

Preserve Sections A through F before opening the worked textbook trace.
Sections G through I complete the same Practical 2 artifact. The numbered
prompts and assessment match the standard worksheet; tables are expanded
into sequential text.

## Fixture and source reference

Use A=0, B=1, C=2, D=3, E=4, F=5, with A as source. Process outgoing edges
in this order:

1. A to B costs 9; A to C costs 2; A to E costs 14.
2. B to D costs 1; B to E costs 8.
3. C to B costs 3; C to D costs 2.
4. D to E costs 2.
5. E and F have no outgoing edges.

`node_dist[v]` is the best cost found; `-1` marks no discovered route.
`heap` stores waiting node IDs. `node_heap_pos` maps a waiting ID to its
slot. `found` becomes 1 when a node is removed. All listed costs are
positive. Keep candidate sums within `int`.

## A. Contrast connection count with total cost

**A1.** Ignoring weights, give the BFS route from A to E and its edge count.

Response: ___________________________________________________________

**A2.** Add the weights along that BFS route.

Response: ___________________________________________________________

**A3.** Give the edge count and cost of A,C,D,E. Explain why fewer edges
need not mean a smaller cost.

Response: ___________________________________________________________

**A4.** State what BFS minimizes and what Dijkstra minimizes. What do the
invented weights model, and what real-world claims do they not establish?

Response: ___________________________________________________________

## B. Predict and trace the actual operations

**B1.** Record distances A through F, `found`, and the live heap after
`init_dist(0)`. What resets, and what graph input remains unchanged?

Response: ___________________________________________________________

**B2.** Trace all three discoveries from A, including the intermediate
heaps, comparisons, swaps, and live inverse-map entries.

Response: ___________________________________________________________

**B3.** Remove C and process its edges. Explain how B's old cost changes,
which existing slot is repaired, and how D is inserted. Record distances,
live heap, and live map entries after C.

Response: ___________________________________________________________

**B4.** Finish the run. Record state after every removed node's outgoing
edges have been processed. Also record final `found` and final heap size.
For each line give distances A through F, live heap IDs, and new `found`
entry:

- Initialized: ______________________________________________________
- After A: __________________________________________________________
- After C: __________________________________________________________
- After next removal: _______________________________________________
- After next removal: _______________________________________________
- After last removal: _______________________________________________

**B5.** Count insertions including the source, removals, priority updates,
outgoing-edge inspections, successful edge changes, and peak live heap
size. Explain how you obtained counts the source does not return.

Response: ___________________________________________________________

## C. Check IDs, positions, and local order

**C1.** Immediately after C, identify the node IDs and costs compared by
`comp(0,2)`. Why would comparing `node_dist[0]` and `node_dist[2]` be wrong?

Response: ___________________________________________________________

**C2.** State the inverse-map equation for each live slot. Show both map
changes for one swap and state the parent/child distance condition.

Response: ___________________________________________________________

**C3.** Trace removal of D: saved ID, exchanged slots, new size, and repairs.
Which removed-node map entry is now stale? Why must a live-node invariant
check not demand `-1` for every removed ID?

Response: ___________________________________________________________

**C4.** Predict singleton removal and an equal-key example. Explain why
empty repair is safe here and why equal priorities have no stable order.

Response: ___________________________________________________________

## D. Explain strict relaxation and finalization

**D1.** State the three actions for an undiscovered neighbor, a strictly
smaller candidate, and an equal or larger candidate. Why is an existing
waiting node not inserted twice?

Response: ___________________________________________________________

**D2.** Trace D's proposal to E: old cost, candidate, mapped slot, repair
direction, and final live heap.

Response: ___________________________________________________________

**D3.** Compute B's later proposals to D and E. For each, explain why the
algorithm changes or keeps its distance.

Response: ___________________________________________________________

**D4.** Why can a removed node's distance not improve with positive weights?
Where is `found` written, and where is it read? Why does the source not
need a stale-snapshot test?

Response: ___________________________________________________________

## E. State the actual contract

**E1.** List valid ID, adjacency-count, weight, heap-operation, and integer-
addition preconditions. Which are checked by the source?

Response: ___________________________________________________________

**E2.** Why are an eleventh insertion, empty removal, invalid neighbor, and
overflowing signed sum not valid rejection tests for this lab?

Response: ___________________________________________________________

**E3.** State F's final distance and `found` value. Explain their meaning
for this graph without claiming more about an external system.

Response: ___________________________________________________________

**E4.** Does this source return a path or store a predecessor? Verify the
cost of A,C,D,E manually and label that verification accurately.

Response: ___________________________________________________________

## F. Compare implementations and costs

**F1.** On the same graph, compare BFS, a supplied linear-priority-queue
Dijkstra reference, and indexed-heap Dijkstra. Separate the objective,
Priority Queue ADT, minimum-selection operation, and storage representation.

Response: ___________________________________________________________

**F2.** For generalized `V` and `E`, bound insertions, removals, updates,
repair length, and auxiliary storage. Account separately for the input
cost matrix and the actual fixed ten-node bounds.

Response: ___________________________________________________________

**F3.** Distinguish one-path heap repair from a full invariant scan. How do
you keep test instrumentation from being reported as algorithm work?

Response: ___________________________________________________________

## G. Test the supplied source

**G1.** Describe one focused original regression: input, predicted output,
assertions, and the specific defect it would expose.

Response: ___________________________________________________________

**G2.** Record commands and output for the actual-lab compile, core tests,
and student tests. Identify which results use an independent reference,
and verify the driver includes the supplied `lab.c`.

Response: ___________________________________________________________

**G3.** Run again from a different source or with a different valid graph.
What proves that distances, heap state, and `found` are reinitialized?

Response: ___________________________________________________________

## H. Investigate one bounded defect

**H1.** Use the [autopsy](dijkstra_autopsy.md). Preserve a prediction,
identify the first wrong comparison or swap, and explain the repair using
IDs, positions, and the live prefix. Use paper or a separate scratch copy;
keep the supplied lab unchanged.

Response: ___________________________________________________________

## I. Revise and synthesize

**I1.** Quote an original claim, cite an observed state that changed it, and
write the corrected claim.

Response: ___________________________________________________________

**I2.** Which Module 10 heap and inverse-map ideas transfer directly? What
new meaning does the distance array give the comparison?

Response: ___________________________________________________________

**I3.** Locate all required evidence in one Practical 2 submission. Explain
why the optional lazy-duplicate parser/path library is a separate design,
not extra implementation work for this lab.

Response: ___________________________________________________________
