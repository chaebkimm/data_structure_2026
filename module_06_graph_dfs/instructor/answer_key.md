# Module 6 Lecture Answer Key — Graph DFS and BCC

These answers match [lab.c](../student/lab.c), the
[textbook](../student/textbook.md), and [lecture material](../student/ppt_material.md).
Use the graph initialized by the included Module 3 source and root 0 (A).

## Reachability and edge indexing

A enters A/B/C/D/E/F in that order, with discovery numbers 1–6.
G/H/I/J remain zero. The full graph's connected components are A–F, G–H,
I, and J: four groups. One call processes only its starting group.

| Index | Record | Kind |
| ---: | --- | --- |
| 0 | A → B | tree |
| 1 | B → C | tree |
| 2 | B → D | tree |
| 3 | D → E | tree |
| 4 | E → B | back |
| 5 | E → F | tree |
| 6 | F → B | back |
| 7 | F → D | back |

Both endpoint orders map to the same record. For example,
`edge_index[1][4] == edge_index[4][1] == 4`.
`edge_index[6][7] == -1` in this run. The parent entry is skipped before
comparing discovery numbers, so a tree edge is not recorded twice.

## Low-link values

| Vertex | Discovery | Parent index | Low |
| --- | ---: | ---: | ---: |
| A | 1 | -1 | 1 |
| B | 2 | 0 | 2 |
| C | 3 | 1 | 3 |
| D | 4 | 1 | 2 |
| E | 5 | 3 | 2 |
| F | 6 | 4 | 2 |

F's edge to B lowers its value to 2. Its edge to D has discovery 4 and
cannot lower 2. E already reaches B directly and also receives 2 from F.
D receives 2 from E. C has no non-parent connection and retains 3.

## Blocks and stack answers

C returns with `3 >= 2`; pop edge 1 only. F returns with `2 < 5`, and E
with `2 < 4`; neither emits a row. D returns with `2 >= 2`; pop edges
7/6/5/4/3/2. B returns with `2 >= 1`; pop edge 0. Root A returns without
another row.

```text
bcc[0] = [1]                 → B-C
bcc[1] = [7,6,5,4,3,2]       → six edges among B/D/E/F
bcc[2] = [0]                 → A-B
bcc_size starts [1,6,1]
current_bcc = 3
edges_size = 8
top = -1
```

The boundary edge is included because the pop and store occur before the
loop condition. Equality closes a block because reconnecting to B is not
reconnecting above B. Strict `>` would identify a bridge, and would miss
D's block boundary here.

The explicit stack stores edge indices. The recursive call stack stores
unfinished vertex scans. The maximum pending edge count is seven; the
maximum active call path is A/B/D/E/F, five vertices.

B is the cut vertex shared by all three blocks. A is not a cut vertex;
as root it has only one DFS child. A–B and B–C are bridges. These
properties are inferred from the trace, not separate lab outputs.

## Wrapper and reuse answers

`init_edges_list(0)` creates usable indices before `find_bcc(0)` pushes
those indices. `find_bcc()` first saves low-link values, then clears the
stack and resets discovery/parent state before extraction. It retains
`back_num`. The same root and stored order reproduce discovery numbers.

`current_bcc` is not reset by `find_bcc()`. Its one-call comment is part
of the teaching scope. Repeated runs need explicit result management.
Reindexing a different component also changes the meaning of existing
indices; a whole-graph extension must preserve a consistent edge list.

## Fresh-case predictions

| Simple undirected input | Edge-block result |
| --- | --- |
| Single isolated root | zero indexed edges, zero rows |
| Chain 0–1–2, root 0 | two one-edge rows, last tree edge first |
| Triangle 0–1–2–0, lists inserted in that order | one three-edge row; equality at root-child return |
| Root 0 with edges 0–1 and 0–2 | two one-edge rows; root is a cut vertex |
| Supplied graph, root G (6) in a fresh run | one edge G–H, one row `[0]` |
| Supplied graph, root I (8) in a fresh run | no edge rows |

These cases assume independent initialized state and adequate capacity.
Changing DFS order can change edge IDs and row order while retaining the
same undirected block partition.

## Cost answers

A–F has six reached vertices and eight undirected edges: sixteen stored
neighbor entries per pass. Three passes remain `O(R + E_R)` for traversal
work. The lookup initialization writes 100 cells for ten active vertices,
so the entire pipeline is `O(V² + E_R)`. Generalized calls and pending
edges use `O(R + E_R)` working space. The lab itself reserves fixed arrays.

The old matrix/typed-vertex-stack starter is a separate exercise. Its
status codes, failure preservation, and three TODOs are not answers to
this lab's lecture questions.
