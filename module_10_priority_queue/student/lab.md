# Module 11 Lab — Trace and Test Indexed-Heap Dijkstra

Use [lab.c](lab.c) as the source of truth. All functions are supplied.
Predict their state, run the actual source through a separate assertion
driver, and explain observed results. There are no required implementation
TODOs and no required predecessor or path-reconstruction feature.

Practical 2 is the sole Week 11 submission. The inquiry, pause,
investigation, tests, and comparison are parts of that one artifact within
the 180-minute contact block. Stage letters mark teaching checkpoints,
not five assignments. The current release is one module archive.

## Build the actual lab

From the repository root:

```sh
make -C module_11_graph_dijkstra/code lab-compile core student-tests
```

From the module directory or the root of the extracted standalone archive:

```sh
make -C code lab-compile core student-tests
```

The supplied core driver includes `student/lab.c`. Add a focused original
regression to `code/tests/test_lab_student.c`, record commands and output,
and retain the unmodified supplied lab. A test driver supplies `main`;
`lab.c` does not contain one.

A driver in `code/tests/` can include `<assert.h>` and
`"../../student/lab.c"`. Compile that driver alone with the repository root
on the include search path (`-I.` from the root). This also resolves the
lab's `"module_03_graph/student/lab.c"` dependency. Do not separately compile
sources that the driver already includes; that would define globals and
functions twice. Use the current build instructions in
[code/README.md](../code/README.md) for compiler commands and Windows use.

## 1. Load the canonical directed graph

Call `alphabet_nodes_init()` to clear adjacency counts, then set
`nodes_size=6`. A=0 through F=5 are active in this fixture. Load the listed
outgoing neighbor IDs in this exact order and assign each listed weight in
`edge_length`:

| Node | Outgoing neighbors with weights |
| --- | --- |
| A | B:9, C:2, E:14 |
| B | D:1, E:8 |
| C | B:3, D:2 |
| D | E:2 |
| E | none |
| F | none |

Do not call Module 3's `edges_init()`; it builds a different undirected
fixture. The adjacency list determines edge existence. The cost matrix
only supplies weights for listed edges. Clear the matrix in your fixture
loader for repeatable tests, then fill every listed weight.

The lab does not validate input. Keep IDs within 0–9, adjacency counts
within their ten-slot lists, listed costs positive, and every candidate
sum within the `int` range.

## 2. Predict initialization and discovery

Before running, record the distances, `found`, live heap, and position map
after `init_dist(0)`. Explain why the heap contains the source even though
no edge has been inspected.

Trace processing A. Its neighbor order produces live heap `[C,B,E]` with
current costs 2, 9, 14. For each live slot assert:

```c
assert(node_heap_pos[heap[i]] == i);
```

For every existing child, assert the parent's current distance is no
greater than the child's. Equal costs are permitted by heap order even
though `comp` uses strict `<`.

## 3. Improve an existing waiting node

C is removed next. Before processing C, the remaining live heap is
`[B,E]`. C's first outgoing edge offers B cost `2+3=5`. `update_value`
changes B's existing entry. It does not insert a duplicate B.

C then discovers D at cost 4. Record the repaired heap `[D,E,B]`, its three
live map entries, and the distances `[0,5,2,4,14,-1]` for A through F.
Explain the difference between node D's ID 3 and heap position 0.

For `comp(0,2)`, identify both IDs and both costs. For a swap, show both
inverse-map changes. This distinguishes indexed priority updates from
comparing unrelated `node_dist` slots.

## 4. Finish the run

D lowers E from 14 to 6. B later offers D cost 6 and E cost 13, so neither
proposal changes state. E has no outgoing neighbors.

| Result to check | Expected value |
| --- | --- |
| final distances A through F | `[0,5,2,4,6,-1]` |
| finalization order when tracing the loop | A, C, D, B, E |
| final `found` A through F | `[1,1,1,1,1,0]` |
| final `size` | 0 |
| `add_node` calls, including the source | 5 |
| `remove_root` calls | 5 |
| `update_value` calls | 2 |
| outgoing-edge inspections | 8 |
| peak live heap size | 3 |

The lab does not return event counters or finalization order. Obtain
intermediate states with a debugger or a separate trace driver that calls
the same supplied operations in the same sequence. State your measurement
method. The supplied `min_dist(0)` must independently produce the final
arrays; a hand-written trace alone is not an algorithm test.

## 5. Check the actual heap contract

Test valid states for insertion, upward and downward repair, a parent with
only a left child, and singleton removal. Before removal ensure `size>0`;
before insertion ensure `size<10` and that the node is not already waiting.
Use a heap check based on distances, not numeric ID order.

`remove_root` swaps positions 0 and `--size`, then repairs downward. When a
singleton is removed, both child helpers report no child and repair ends.
The removed ID's map entry remains stale. Verify the inverse-map invariant
only for the live prefix; do not assert that removed nodes have map value
`-1`, and do not use a stale position for `update_value`.

The strict comparator offers no stable tie ordering. Test that equal keys
are all removed with valid heap order and nondecreasing distances. Do not
require insertion order or ID order for ties.

## 6. Write one focused original regression

Extend the supplied student driver with one test that would catch a
specific plausible defect. Suitable targets include:

- node IDs that differ from their heap positions;
- an improvement that must move a waiting node upward;
- singleton removal followed by reinitialization and reuse;
- an equal candidate that must not create another entry; or
- a disconnected node and a second run from a different source.

State the input, predicted result, assertions, and defect the test detects.
A second printout of the canonical fixture is not a focused regression.
The supplied suite covers broader boundaries and an independent shortest-
cost comparison; students do not implement the entire testing framework.

## 7. Compare objectives and queue implementations

On the canonical graph, BFS reaches E in one edge at cost 14. The
least-cost route A,C,D,E has three edges at cost 6, verified manually from
the input. The program stores distances only; it does not reconstruct
that route.

Run the supplied comparison from the module directory or extracted root:

```sh
make -C code comparison
```

`code/tests/compare_lab.c` supplies BFS hop distances, linear-minimum-selection
Dijkstra, and a call to the actual indexed heap on the same fixture. Use
this supplied linear reference to compare the same Dijkstra selection rule
with the indexed heap. Record distance
agreement and the operation each backend performs to locate its minimum.
Distinguish the Priority Queue ADT from FIFO ordering and from a heap's
array representation. Keep this comparison inside Practical 2.

## Evidence and limits

Submit the original test and saved output, canonical trace, active map and
heap checks, BFS/linear/heap comparison, corrected pause, assumptions, and
[evidence record](evidence_template.md). Use [the rubric](rubric.md) to
check the integrated artifact.

Do not run negative weights, overflowing signed sums, invalid IDs, empty
removals, or eleventh insertions as rejection tests: the source provides
no rejection mechanism. Explain these preconditions instead.

The separate lazy-duplicate implementation under `code/include`,
`code/starter`, `code/solution`, and `code/support` is optional reference
material. Its `size_t` parser, infinity sentinel, status preservation,
predecessor paths, stable snapshots, and allocation tests are not lab
requirements. The optional overflow example examines that separate numeric
contract; it does not add an overflow guard to this `int`-based source.
