# Module 11 Lesson Plan — Indexed-Heap Dijkstra

The required source is [student/lab.c](../student/lab.c). All functions are
supplied. Students predict, trace, test, compare, and revise their explanation.
Practical 2 is the sole Week 11 submission. The scan comparison belongs in
that artifact; it is not a second lab or extra homework assignment.

## 180-minute sequence

| Minutes | Activity and evidence |
|---:|---|
| 0–15 | Retrieve BFS. Contrast A,E: one edge/cost 14 with A,C,D,E: three edges/cost 6. Preserve first explanations. |
| 15–30 | Use informal best-total cards. Improve B9 to B5 through C and choose D4 next. |
| 30–50 | Reveal node IDs, adjacency lists, the separate weight matrix, `node_dist`, and the `-1` sentinel. |
| 50–70 | Trace the indexed minimum heap: `heap`, `comp`, `swap`, and the active inverse-position map. |
| 70–90 | Trace source insertion, root removal, strict relaxation, and in-place updates using the canonical graph. |
| 90–100 | Complete the three-target Cognitive Pause, preserve first responses, and label corrections. |
| 100–110 | Break and build reset. |
| 110–130 | Run supplied current-lab checks; inspect `test_lab_student.c` and author a focused regression. |
| 130–150 | Compare BFS, linear minimum-selection Dijkstra, and indexed-heap Dijkstra on the same loaded graph. |
| 150–170 | Check ties, a left-only child, a singleton, disconnection, repeated runs, and active maps. State caller assumptions and generalized cost. |
| 170–180 | Assemble and submit one Practical 2 evidence record; complete an exit explanation. |

Use [the delivery guide](../../Data_Structures_Course_2026_14_Week_Delivery_Guide.md)
for course timing. The lab is a reading/testing task, not implementation of
the optional parser, snapshot frontier, or path-reconstruction API.

## Before class

Run from the repository root:

```sh
make -C module_11_graph_dijkstra/code lab-compile core student-tests comparison
```

The `comparison` target supplies the same-graph BFS and linear-minimum-
selection references through `code/tests/compare_lab.c`; students do not
implement another algorithm to complete the comparison.

Keep the supplied `lab.c` unchanged. Prepare node-ID cards, distance cards,
and a live-prefix table. A driver includes the lab and receives the repository
root as an include path, because the lab includes Module 03's graph source.
Compile the driver once; do not separately compile a source it already includes.

For the shared fixture, call `alphabet_nodes_init`, set `nodes_size=6`, load
the directed adjacency lists below in their listed order, and set matching
matrix entries. Module 03's `edges_init()` installs a different undirected
fixture and is not part of this setup.

```text
A -> B 9, C 2, E 14
B -> D 1, E 8
C -> B 3, D 2
D -> E 2
E and F -> none
```

Use valid IDs 0–9, adjacency counts within their arrays, positive weights,
and candidate sums that fit in `int`. An absent adjacency entry is not an
edge, whatever value an unused matrix cell contains. The source does not
validate input or check arithmetic. Do not demonstrate invalid operations as
if they returned a defined rejection status.

## Reveal sequence

1. Preserve the informal objective and cost model before showing formal names.
2. Introduce weighted graph, path cost, tentative distance, and finalization.
3. Map every source name to the representation it actually addresses.
4. Show how the heap stores IDs while `node_dist` stores their changing keys.
5. Introduce the inverse map as the means to repair one queued node.
6. Trace one full run before generalizing the proof and cost.
7. Release textbook/models to correct preserved investigation responses.
8. Release driver/evidence materials for the same integrated Practical 2.

Stage A through E are teaching checkpoints. They do not create five separate
assignments or justify more than the 180-minute contact budget. Accept prose,
tables, accessible linear descriptions, or diagrams with equivalent evidence.

## Board trace

Write only live heap positions. Read every key through its stored node ID.

| After processing | Distances A..F | Live heap IDs |
|---|---|---|
| initialization | `0,-1,-1,-1,-1,-1` | `A` |
| A | `0,9,2,-1,14,-1` | `C,B,E` |
| C | `0,5,2,4,14,-1` | `D,E,B` |
| D | `0,5,2,4,6,-1` | `B,E` |
| B | `0,5,2,4,6,-1` | `E` |
| E | `0,5,2,4,6,-1` | empty |

Pause before each operation:

- Which node is at position 0, and what is its key?
- Does the neighbor have distance `-1`, a larger distance, or an equal/smaller one?
- Does this branch insert a new node or edit the existing queued node?
- Which inverse-map entries change during the swap?
- Which entries remain inside the active prefix?

The finalization order is A,C,D,B,E. F stays unreachable. Five nodes are added
and removed, two queued keys decrease, eight adjacency entries are inspected,
and the peak heap size is three. These are trace counts; the lab stores no
counter fields and no finalization-order array.

## Exactly three Cognitive Pause targets

Allow five minutes without notes/tools, followed by five minutes of calibration.
Use the locked state from [the pause](../student/cognitive_pause.md).

1. Distinguish the BFS route A,E, cost 14, from the manual cost witness A,C,D,E,
   cost 6.
2. After C, explain B9→5 in place, the live array `[D,E,B]`, and choosing D4.
3. Explain D's E14→6 update, B's rejected proposals D6/E13, F's `-1`, and
   the positive-weight/representable-sum assumptions.

The current lab does not store predecessors. A route named in this discussion
is a manually checked witness, not a returned path or reconstruction result.

## Likely misconceptions and neutral questions

| First thought | Question that exposes the representation |
|---|---|
| Heap position is the node ID. | After C, why does position 0 hold ID 3? Which arrays are indexed by which quantity? |
| Heap IDs are globally sorted by cost. | Is `[D,E,B]` valid with keys `[4,14,5]`? Which parent-child comparisons matter? |
| Decreasing B requires another insertion. | Which map entry locates the queued B, and where is the second B in the live array? |
| Every nonnegative map value means membership. | What map entry remains after root removal, and is that position still owned by the removed node? |
| `found` prevents updates to removed nodes. | Where does the loop read `found`? Which mathematical assumption prevents those improvements? |
| Equal priorities leave in insertion order. | Does the source store an arrival sequence? What happens when strict `comp` sees equal keys? |
| `min_dist` returns a path. | Which output arrays are actually written, and where would a predecessor be stored? |
| Invalid weights are rejected. | Which line checks weight sign or candidate overflow? Who must ensure valid input? |

Explain `heap_parent` as a heap-position helper. Module 03 already declares
an unrelated `parent[10]` array, so using a separate function name avoids a C
identifier conflict. The source's strict `<` comparator may swap equal keys;
that is legal heap behavior and carries no stability guarantee.

## Assessment and exit check

Use the current [rubric](../student/rubric.md). Require one focused original
regression and saved supplied-suite output, a complete canonical distance/heap
trace, active-map checks, a same-graph BFS/scan/heap comparison, and corrected
reasoning. Do not add parser, allocation, predecessor, path, or stale-entry
implementation tasks. The additional boundary fixtures support the same
artifact rather than another submission.

Exit prompt:

> B was first queued at cost 9 and later improved to 5. Why is there still
> only one live B, where does the map locate it, and why can a removed minimum
> not need another improvement under this lab's assumptions?

An adequate answer connects shared keys, map-preserving swaps, one-path heap
repair, and positive continuations. For generalized V and E, distinguish
`O(V + (V+E) log V)` work and `O(V)` heap-related state from the separate
`O(V²)` weight matrix and the literal ten-node bound.

## Optional reference boundary

The retained `code/starter`, `solution`, `support`, and `include` directories
implement a different dynamic lazy-duplicate API. Their parser, stable
snapshots, `SIZE_MAX`, failure statuses, predecessor reconstruction, and
stale-pop proof may be used after the required lesson. They do not describe
the supplied lab and do not enlarge Practical 2.
