# Chapter 6. Graph DFS, Edge Storage, and Blocks

Teach in the question order of the
[concept slides](../module_06_graph_dfs/student/ppt_material.md), with the
[bilingual workbook](../module_06_graph_dfs/student/class_material.md) and
[models](../module_06_graph_dfs/diagrams/dfs_models.md).
The [lesson plan](../module_06_graph_dfs/instructor/lesson_plan.md) allocates
90 + 90 minutes. The final coding exercise follows the current
[lab](../module_06_graph_dfs/student/lab.c) and
[lab slides](../module_06_graph_dfs/student/ppt_lab_material.md).

## Starting question

> At visit 3, which neighbor needs a new exploration, which connection
> was already handled, and which connection returns to an ancestor?

The diagram's numbers 1–7 are visit numbers from its completed fixed DFS.
Refer to vertices by these numbers and retrace from visit 1 with ascending
diagram neighbors. Preserve predictions before revealing completed traces.

```text
1–2, 1–3, 2–3, 2–7, 3–4, 3–6, 3–7, 4–5, 4–6, 5–6
```

## Question-led board walkthrough

1. Retrieve endpoints, neighbor lists, tree/back connections, and visit/
   earliest-reconnection numbers. At visit 3 identify ancestor 1, parent 2,
   child 4, descendant 6 after 4 returns, and child 7. The parent also has
   a smaller visit number, so recognize it before the ancestor case.
2. Number at entry, set a child's parent before descending, resume the
   paused scan on return, and use postorder after all neighbors. Blank
   circles ask students to fill visit numbers at the current stage;
   partially highlighted connections show progress through the same graph.
3. Review Chapter 3's adjacency lists. Introduce endpoint-pair edge lists
   and adjacency matrices as new Chapter 6 representations, then compare them.
   Ask where 3–6 is stored, how each representation inserts/deletes it,
   and what deleting the vertex at visit 3 must remove. Keep both directions
   consistent in lists/matrices and one record per undirected pair.
4. Collect a child connection before descent and a non-parent ancestor
   connection without repeated descent. Skip parent/descendant reverse
   entries. Write pairs with the smaller endpoint visit number first.
5. Ask for visit 6's earliest number. Begin at 6; 6 → 3 lowers it to 3.
   The later 6 → 4 cannot lower 3. Propagate this value through visit 5
   to visit 4. Final values are 1/1/1/3/3/3/2 for visits 1–7.
6. Predict maximal blocks with two internally vertex-disjoint paths
   between every pair. Push pairs on the edge stack. Immediately after a
   child returns, its parent compares the child's earliest number with
   its own visit number. Equality or a larger value closes a block; pop
   through the parent–child pair, including it. Two five-edge blocks share visit 3.

| Return | Comparison | Emitted visit pairs, removal order |
| --- | --- | --- |
| 6 → 5 | 3 < 5 | none |
| 5 → 4 | 3 < 4 | none |
| 4 → 3 | 3 ≥ 3 | 4–6, 3–6, 5–6, 4–5, 3–4 |
| 7 → 3 | 2 < 3 | none |
| 3 → 2 | 1 < 2 | none |
| 2 → 1 | 1 ≥ 1 | 2–7, 3–7, 1–3, 2–3, 1–2 |

Visit 1's own return emits no further group; the stack finishes empty.
Use the workbook's exact three-target retrieval pause. Require one
correction supported by a number, pair, or timing statement.

## Edge-stack invariant checkpoint

Use workbook 6.1 after the trace. At every push or completed pop-and-store
checkpoint, each handled undirected edge is exactly once either pending
or assigned, with no overlap. Assigned includes edges already stored in
the result row being formed. Stack order is the recording order of still
unassigned edges; removal is LIFO. Parent/descendant reverse entries never
push again.

Ask students to explain initialization with empty sets, maintenance by
adding one new edge or transferring one edge to a result row, and
termination with every reached edge assigned and an empty pending stack.
The low-link boundary argument additionally establishes the grouping:
after a child returns, its parent closes the remaining unassigned suffix
through and including the parent–child pair when the child's earliest
number is at least the parent's visit number. A smaller value leaves it
pending; equality closes it. Inner blocks may already have been removed.

After 4 returns and closes its block, eight edges have been handled:
three pending and five assigned. After 3 returns to 2, ten have been
handled: five pending and five assigned. The right block is already
assigned even though it lies in the returned subtree. After 2 returns
to 1, zero are pending and all ten are assigned. Keep fitting the fixed
stack as a separate capacity precondition, outside the logical invariant.

## Midterm review and mini-quiz

Explain graph storage/insertion/deletion in all three representations,
then block definition and finding. Removing a vertex removes all incident
connections from the rest of the stored graph.

Cross-reference [Chapter 5](chapter_05.md): preorder `ABDECFG` and inorder
`DBEAFCG` split at A into `DBE | A | FCG`; their sizes select preorder
`BDE` and `CFG`. Repeat and verify postorder `DEBFGCA` for this separate tree.
The final slide requests mini-quiz submission. Students complete the
instructor's questions, check their reasoning, and submit through classroom
instructions. The workbook supplies the activity prompt.

## Coding connection: original A–J source

Only here introduce C names, internal indices, and record IDs. `lab.c`
includes the Chapter 3 A–J graph and Chapter 4 integer stack; it does not
initialize the slide graph. Read `_edge_iteration_()` before specializing
its child/ancestor positions with `add_edge()` or `push()`. Child order is
record or push, assign parent, recurse. `add_edge()` records existing
adjacency, without constructing it. The source names the `init_edges_list()`
parameter `start_node`; its slide excerpt uses `root`.
That wrapper resets discovery/parents, clears the record count, fills the
active lookup with -1, then indexes the reached edges. `find_bcc()` performs
the low-link pass, empties the stack, and resets discovery for the extraction
pass while retaining `back_num`. The latter two passes must reproduce the
same start and neighbor order. After each child call, strict `<` leaves
its pending suffix on the stack; otherwise the inclusive pop closes a block.

Map the invariant to `stack[0..top]` and the stored edge indices in `bcc`.
Within `close_bcc()`, entries already stored at `bcc[cur][0..pos-1]` count
as assigned before `bcc_size[cur]` is finalized. Check after the store
following each `pop()`. The parent-side comparison is
`back_num[adj] < visit_num[node]`, immediately after `_find_bcc(adj)`.
The `tree_edge` boundary was pushed before descent. Preserve the same
saved-number traversal and fresh result-state assumptions.

Run `make lecture` from `module_06_graph_dfs/code` in a fresh process.
A reaches A/B/C/D/E/F, discovery 1–6, earliest 1/2/3/2/2/2.
Eight records produce rows `[1]`, `[7,6,5,4,3,2]`, `[0]`, sizes 1/6/1,
sharing B. G–H and I/J are outside this start's reach. The body-first pop
loop includes the parent edge. Low-link computation and extraction must
reproduce the same numbering.

The optional [slide driver](../module_06_graph_dfs/code/lecture/ppt_demo.c)
stores neutral A–G data at internal indices 0–6 and prints edge endpoints
from actual visit numbers 1–7. Its two five-edge rows verify the concept
trace independently, without changing original A–J output.

Use the [answer key](../module_06_graph_dfs/instructor/answer_key.md) and
[technical notes](../module_06_graph_dfs/instructor/technical_notes.md).
The full array pipeline is `O(V² + E_R)` including lookup initialization;
traversal is `O(R + E_R)`. Unchecked capacities and missing result-count
reset limit the source to its supplied one-call scope. The matrix starter
retains separate legacy assignment contracts.
The updated arrays reserve `edges[45]`, `bcc[9][45]`, and `bcc_size[9]`.
The imported `stack[10]` still requires at most ten pending edge indices.
Distinguish the ten-vertex maximum of 45 simple undirected edges and nine
edge blocks from the stack's separate capacity.

## Neutral questions for common first thoughts

- “Every smaller-numbered neighbor is an ancestor back connection.” Is it the parent?
- “3 → 6 is a new child.” When is that neighbor checked?
- “The blank circle changes the graph.” Which visit numbers are filled at this stage?
- “Every endpoint entry creates a pair.” Which reverse direction was already processed?
- “Visit 6's earliest number is 4.” Which earlier visit can 6 reach directly?
- “The edge stack stores nodes.” Which endpoint pair waits at the top?
- “Every edge in a returned subtree is still pending.” Which inner block was already assigned?
- “A popped edge disappears until the row is finished.” Where has that edge already been stored?
- “Equality leaves the group pending.” Can this branch reconnect above its parent?
- “The new slide graph changes the original lab output.” Which input does each driver initialize?
