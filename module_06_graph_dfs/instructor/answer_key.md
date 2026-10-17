# Module 6 Answer Key — Visit-numbered Slides and Original Coding Lab

Use [concept slides](../student/ppt_material.md), the
[bilingual workbook](../student/class_material.md), and
[models](../diagrams/dfs_models.md). Sections 1–8 answer the fixed DFS
whose completed visit numbers are 1–7. Section 9 uses the current C lab with the original A–J graph.

## 1–2. Classification and timing

The diagram's numbers are visit numbers from the completed fixed DFS.
Retrace from visit 1, checking diagram neighbors in ascending order.
Refer to every vertex by its visit number.

| Visit number | Parent visit number | Earliest reconnection |
| ---: | --- | ---: |
| 1 | none | 1 |
| 2 | 1 | 1 |
| 3 | 2 | 1 |
| 4 | 3 | 3 |
| 5 | 4 | 3 |
| 6 | 5 | 3 |
| 7 | 3 | 2 |

| Encounter at visit 3 | Kind | Explore again? | Evidence at that time |
| --- | --- | --- | --- |
| 3 → 1 | non-parent ancestor | no | 1 < 3; parent visit is 2 |
| 3 → 2 | parent | no | this is the already-processed tree connection |
| 3 → 4 | new tree child | yes | not yet explored when reached from 3 |
| 3 → 6, after 4 returns | processed descendant | no | 6 > 3; collected from 6 |
| 3 → 7 | new tree child | yes | not yet explored until this encounter |

A parent has a smaller visit number too. Test its role first so the
reverse tree entry is not mistaken for a new ancestor back connection.

Assign the visit number at entry; set a child's parent before descent.
Visit 3 waits for visit 4's whole exploration, then resumes at neighbor 6,
and afterward checks 7. Postorder follows the entire neighbor scan.
Calls remember the current vertex, paused neighbor position, and return
work. Blank circles ask for the visit numbers reached at a stage;
partial highlights show progress through the same graph.

## 3. Three representations and editing

Adjacency lists are review from Chapter 3, which taught only that graph
representation. Edge lists and adjacency matrices are introduced in Chapter 6.

| Representation | Store/add 3–6 | Delete 3–6 | Delete a vertex |
| --- | --- | --- | --- |
| Neighbor lists | store 6 in 3's list and 3 in 6's list; avoid duplicates | remove both entries | remove its list and all occurrences in other lists |
| Endpoint-pair edge list | one record 3–6; avoid a second record for 6–3 | remove that record | remove every incident pair |
| Adjacency matrix | set both cells for endpoint visits 3/6 | clear both symmetric cells | clear/remove its row and column |

Neighbor lists support scanning one vertex's neighbors. Edge records
support separate per-edge information. Matrices support direct endpoint
lookup, at quadratic storage cost. Deleting a vertex must also remove
its connections from the rest of the stored graph.

## 4. Collect once

Endpoint visit-number pairs in collection order:

| Order | Pair | Kind |
| ---: | --- | --- |
| 1 | 1–2 | tree |
| 2 | 2–3 | tree |
| 3 | 1–3 | back, processed 3 → 1 |
| 4 | 3–4 | tree |
| 5 | 4–5 | tree |
| 6 | 5–6 | tree |
| 7 | 3–6 | back, processed 6 → 3 |
| 8 | 4–6 | back, processed 6 → 4 |
| 9 | 3–7 | tree |
| 10 | 2–7 | back, processed 7 → 2 |

Collect child pairs before descent and non-parent ancestor pairs without
repeated descent. Skip reverse parent/descendant directions. When visit 1
finally checks 3, the larger visit number identifies the processed
reverse side of 1–3. Ten pairs come from twenty neighbor entries.

## 5. Earliest reconnection

Final values are in the first table. Visit 6 begins with value 6.
Connection 6 → 3 lowers it to 3; 6 → 4 cannot lower 3.
Visit 5 receives 3 from child 6, then visit 4 receives 3 from child 5.
The value 3 denotes reconnection to visit 3.

Visit 3 reaches visit 1 directly and keeps value 1 after its children
return. Visit 7 reconnects to visit 2 and obtains 2. Visit 2 receives 1
from child 3; visit 1 remains at 1. Compare ancestor visit numbers on back
connections and children's earliest numbers only after their return.

## 6. Complete pending pairs and two blocks

Write every stack bottom to top; blocks are in removal order.

| Event | Complete pending pairs | New block |
| --- | --- | --- |
| Enter visit 3 | 1–2, 2–3 | none |
| Scan 3 → 1 | 1–2, 2–3, 1–3 | none |
| Scan 6 → 4 after 6 → 3 | 1–2, 2–3, 1–3, 3–4, 4–5, 5–6, 3–6, 4–6 | none |
| Finish visit 6 | 1–2, 2–3, 1–3, 3–4, 4–5, 5–6, 3–6, 4–6 | none; 3 < 5 |
| Finish visit 5 | 1–2, 2–3, 1–3, 3–4, 4–5, 5–6, 3–6, 4–6 | none; 3 < 4 |
| Finish visit 4 | 1–2, 2–3, 1–3 | 4–6, 3–6, 5–6, 4–5, 3–4 |
| Scan 7 → 2 | 1–2, 2–3, 1–3, 3–7, 2–7 | none |
| Finish visit 7 | 1–2, 2–3, 1–3, 3–7, 2–7 | none; 2 < 3 |
| Finish visit 3 | 1–2, 2–3, 1–3, 3–7, 2–7 | none; 1 < 2 |
| Finish visit 2 | empty | 2–7, 3–7, 1–3, 2–3, 1–2 |
| Finish visit 1 | empty | none |

Visit 4's earliest number equals parent visit 3: 3 ≥ 3. Its branch can
reconnect to visit 3 but cannot bypass it to an earlier visit. Close here.
Visit 2's earliest number equals parent visit 1: 1 ≥ 1, closing the remaining
block. Excluding equality misses both closures. Include the boundary pair.

The blocks are `{3–4,3–6,4–5,4–6,5–6}` and
`{1–2,1–3,2–3,2–7,3–7}`. Both contain five pairs and share visit 3,
with no shared edge. Removing that vertex leaves triangles on visits
1/2/7 and 4/5/6. One connected vertex group contains two edge blocks.
Each block has two internally vertex-disjoint paths between every pair.
Peak pending count is eight; the deepest active path is visits 1/2/3/4/5/6,
six calls.

### 6.1. Edge-stack invariant

At each push or completed pop-and-store checkpoint, every handled
undirected edge appears exactly once either pending or assigned; these
sets are disjoint. Count stored entries of a row still being formed as
assigned. Bottom to top is the recording order of unassigned edges;
removal is LIFO. Reverse parent and descendant entries never push again.

| Checkpoint | Handled | Pending | Assigned, including forming row |
| --- | ---: | ---: | ---: |
| Start extraction | 0 | 0 | 0 |
| After 4 returns and its block closes | 8 | 3 | 5 |
| After 3 returns to 2 | 10 | 5 | 5 |
| After 2 returns and its block closes | 10 | 0 | 10 |

Initially all counts are zero. Pushing a newly handled edge adds it only
to pending; popping and storing transfers it to assigned. No reverse scan
adds a duplicate. During the first right-block pop, 4–6 has moved to the
forming row: seven pairs remain pending and one is assigned. Five such
steps include boundary 3–4, leaving three pending and five assigned.

When 3 returns to 2, the right block has already been emitted within 3's
subtree. Only its five still-unassigned pairs remain pending; they stay
because 1 < 2. On 2's return, 1 ≥ 1 closes that suffix including 1–2.
In general the qualifying parent's pop uses the remaining unassigned
suffix, not every edge in the returned subtree. Inner blocks have been
removed. Equality permits reconnection to the parent but none above it.

Once the reached component is fully scanned, root-child closures leave
the stack empty; the invariant then gives exactly one assignment per
reached edge. The low-link boundary argument justifies why each assigned
group is a block. The invariant alone is a conservation statement.
Separately require the peak pending count to fit `stack[10]`; a 45-record
edge array does not establish that capacity precondition.

## 7. Exact three-target retrieval pause

1. **Classification:** visit 3 sees ancestor 1, parent 2, children 4/7,
   and descendant 6 by the time that neighbor is scanned.
2. **Earliest/boundary:** visit 6's earliest is 3. Visit 4 closes on
   3 ≥ 3, including the boundary pair 3–4.
3. **Saved work:** calls remember unfinished scans; the edge stack stores
   pairs awaiting a block. They serve different purposes.

Preserve initial answers, then require a correction supported by a number,
encounter, or boundary. Drawing speed is not assessed.

## 8. Midterm review and mini-quiz

Use the editing table for graph storage/addition/deletion. Explain maximality,
internal vertex-disjoint paths, shared boundary vertices, entry/ancestor
pushes, and the parent's earliest-number comparison immediately after each
child returns.

Chapter 5's separate tree has preorder `ABDECFG`, so root A splits inorder
`DBE | A | FCG`. Subtree lengths select preorder `BDE` and `CFG`.
Repeating gives B with D/E and C with F/G. Postorder is `DEBFGCA`.
Distinct labels are required for this reconstruction argument.

The final slide asks students to submit the instructor-provided mini-quiz.
Use the classroom submission instructions; the workbook records answers
and checks. This is a student activity prompt, not a submission performed
by these materials.

## 9. Coding key — original A–J graph

Use [lab.c](../student/lab.c), [lab slides](../student/ppt_lab_material.md),
and the [original driver](../code/lecture/lab_demo.c). That driver creates
A–J with the Chapter 3 initializers and retains stored insertion order.

`_edge_iteration_()` numbers vertices and sets parents; its comments do
not record edges or emit blocks. `_init_edges_list()` adds `add_edge()`
to child/ancestor positions. The child sequence is add, set parent, recurse.
`add_edge()` writes an edge record and both symmetric lookup cells, without
changing adjacency lists. `init_edges_list()` resets discovery/parents,
clears `edges_size`, fills the active lookup with -1, then calls the
indexing helper. Index 0 is a valid record. Source parameter `start_node` is `root`
in that wrapper's slide excerpt.

```text
vertex       A B C D E F
visit_num    1 2 3 4 5 6
parent      -1 0 1 1 3 4
back_num     1 2 3 2 2 2
edges        0:A→B 1:B→C 2:B→D 3:D→E 4:E→B 5:E→F 6:F→B 7:F→D
bcc rows     [1] | [7,6,5,4,3,2] | [0]
bcc_size     1,6,1
edges_size=8 current_bcc=3 top=-1
```

Both B–E lookup directions equal 4; G–H lookup is -1 in this A-started run.
G/H/I/J stay unvisited. The whole source graph has four connected groups.
Resolve rows into `{B–C}`, `{F–D,F–B,E–F,E–B,D–E,B–D}`, `{A–B}`.
Their shared vertex is B. These are source results, not the slide graph's blocks.

`find_bcc()` performs `init_visit()`, `save_back_num(start_node)`,
`top = -1`, `init_visit()` again, then `_find_bcc(start_node)`.
The second reset retains `back_num`; extraction must reproduce the same
root/order numbering. The wrapper relies on `init_edges_list()` having
already indexed reached edges; indexing, low-link calculation, and
extraction are three separate passes. At C, pop `[1]`; at D, equality 2 ≥ 2 pops the six-edge
row; at B, pop `[0]`. The parent compares the child's saved low-link value
after the recursive call. A strict `<` continues the scan without closing;
equality or a larger value calls `close_bcc(tree_edge)`.
The `do ... while` stores before testing, including
the boundary edge. Root A's own return emits no extra row.

`make lecture` prints final discovery/parent/low/edge/block/stack tables,
not lookup cells or intermediate stacks. Record actual compiler/command
and diagnostics; label hand/source checks. Row sizes can be counted from
printed entries. Three passes inspect 16 neighbor entries each; resetting
the ten-vertex lookup writes 100 cells. Complete cost is `O(V² + E_R)`;
traversal is `O(R + E_R)`. Peak calls are five, pending edges seven.
Actual capacities are `edges[45]`, `bcc[9][45]`, `bcc_size[9]`, and
the imported `stack[10]`. Ten vertices allow at most 45 simple undirected
edges and nine edge blocks. Those larger record/result arrays do not
enlarge the ten-entry pending stack. The wrapper leaves `current_bcc`, `bcc_size`, and
`bcc` uncleared. Reuse needs result management; reindexing another group
also changes record identities. Raw input and capacity checks are absent.

The optional [slide driver](../code/lecture/ppt_demo.c) explicitly supplies
the slide graph adjacency to the same current lab. Run it independently
using the command in the technical notes; expect two rows of five visit-number
endpoint pairs. Internally it uses indices 0–6 with neutral A–G data;
printed endpoints use actual visit numbers 1–7.
The original lecture driver remains the reference for A–J verification.
The checked matrix package has separate contracts and assessment tasks.
