# Chapter 6. Grouping connections in a graph

Teach the revised [English textbook](../module_06_graph_dfs/student/textbook.md)
and [Korean textbook](../module_06_graph_dfs/student/textbook_korean.md) in
their seven-section order. Use the [bilingual workbook](../module_06_graph_dfs/student/class_material.md)
for predictions and corrections, and the [lesson plan](../module_06_graph_dfs/instructor/lesson_plan.md)
for two 90-minute meetings. The [concept slides](../module_06_graph_dfs/student/ppt_material.md)
and [lab slides](../module_06_graph_dfs/student/ppt_lab_material.md) support
matching questions within this sequence.

## 1. Thinking logically

Begin with: “How can we record every connection once, then group connections
that hold together when one vertex is removed?” Build on Chapter 3's
adjacency lists, Chapter 4's stack, and Chapter 5's entry/return timing.

Use the textbook's seven-vertex graph. Numbers 1–7 identify vertices by
completed DFS visit order, rather than C array positions. Replay from
visit 1 using ascending diagram neighbors. Preserve predictions before
showing completed values.

```text
1–2, 1–3, 2–3, 2–7, 3–4, 3–6, 3–7, 4–5, 4–6, 5–6
```

1. Compare neighbor lists, edge records, and a presence matrix. Ask how
   3–6 is stored, how absent edge 1–7 is added, and which references are
   removed with vertex 7. Distinguish an adjacency matrix from a lookup
   of recorded edge indices.
2. At visit 3, classify ancestor 1, parent 2, new child 4, descendant 6
   after 4 returns, and new child 7. Test the parent before interpreting
   a smaller number as an ancestor back edge. The graph is simple and
   undirected; these are not general directed-edge classification rules.
3. Place discovery at preorder, tree-edge work before recursion, completed
   branch work immediately after child return, and postorder after every
   neighbor finishes. Record each tree edge and ancestor back edge once.
4. Trace visit 6's low-link value: begin at 6, lower it to 3 through 6 → 3,
   and keep 3 when examining 6 → 4. Pass the result through 5 and 4.
   Final values are 1/1/1/3/3/3/2 for visits 1–7.
5. Define maximal blocks with two internally vertex-disjoint paths between
   every pair when at least three vertices are present. Include bridges
   as single-edge blocks; an isolate has no edge to group.
6. Trace the textbook's five stack steps. Compare a child's low-link with
   its parent's visit number after return. A smaller value stays pending;
   equality or a larger value closes through the incoming tree edge,
   including that boundary.

| Return | Comparison | Completed block, pop order |
| --- | --- | --- |
| 6 → 5 | 3 < 5 | none |
| 5 → 4 | 3 < 4 | none |
| 4 → 3 | 3 ≥ 3 | 4–6, 3–6, 5–6, 4–5, 3–4 |
| 7 → 3 | 2 < 3 | none |
| 3 → 2 | 1 < 2 | none |
| 2 → 1 | 1 ≥ 1 | 2–7, 3–7, 1–3, 2–3, 1–2 |

Two five-edge blocks share cut vertex 3. The connected component contains
all seven vertices. Root 1 has one DFS child and is not a cut vertex;
its own return emits no further block.

## 2. Calculating efficiency

Use the textbook's four headings: storage, traversal memory, adding an
item, and traversal time. Fixed arrays reserve their full capacities.
A pair table grows quadratically even if few edges are present. A new
record and two lookup writes take constant time with available capacity;
a new matrix row and column require work proportional to the vertex count.

The conceptual graph has seven entries and twenty neighbor inspections
per pass, or 21 and 60 across three passes. Initializing its active lookup
writes 49 cells. Peak recursion follows 1/2/3/4/5/6, and the peak edge
stack holds eight edges. Generalized traversal is `O(R + E_R)`; including
lookup preparation makes the full pipeline `O(V² + E_R)`.

Distinguish allocated slots from active entries. `edges[45]` and
`bcc[9][45]` cover the maximum records and edge-block rows for ten vertices,
but the imported `stack[10]` still limits simultaneously pending edges.

## 3. Glossary

Have students explain the workbook's term pairs using the graph. Focus on
visit number versus array index; tree versus back edge; presence matrix
versus edge lookup; connected component versus block; cut vertex versus
bridge; and call stack versus pending-edge stack. Use the textbook's short
definitions as feedback after students attempt their own explanations.

## 4. Invariant

Ask the same four questions as the textbook: What are the rules? What do
they guarantee? What breaks when they fail? How do we preserve them?

After each push or completed pop-and-store step, every handled edge appears
exactly once, either pending or assigned. Assigned includes a row still
being filled. Check identities as well as counts. Initialization starts
with empty collections; pushes add one new edge; pop-and-store transfers
one edge. The first completed block leaves 8 = 3 + 5, and completion gives
10 = 0 + 10. An empty stack alone does not establish correct grouping.

Stop at non-root postorder before the parent compares. At vertex 4, older
prefix `1–2, 2–3, 1–3` lies below suffix `3–4, 4–5, 5–6, 3–6, 4–6`.
Only the suffix belongs with incoming edge 3–4. Parent 3 closes it after
return. At vertex 3, suffix `2–3, 1–3, 3–7, 2–7` omits older edge 1–2,
although that edge is in the same eventual block. The suffix need not be
the entire block or the whole stack.

루트가 아닌 노드가 부모에게 돌아가기 직전, 들어온 부모 간선부터 맨 위까지
남은 구간은 그 부모 간선과 같은 최종 블록에 속한다. 부모는 복귀 후 빽 번호를
비교한다. 전체 스택이나 완성된 블록 전체와 구별한다.

Deeper comparisons already removed separate inner blocks. The remaining
suffix becomes a whole block when the low-link comparison prevents
reconnection above the parent. Equality reconnects to the parent but
cannot bypass it. Preserve that boundary inclusively and keep the same
root/order between saved low-links and extraction. Fitting capacities are
an additional precondition.

## 5. Coding plan

Explicitly switch to the original A–J graph in the [lab](../module_06_graph_dfs/student/lab.c).
It includes Chapter 3's graph storage and Chapter 4's integer stack.
Explain preparation, edge indexing, low-link calculation, pending-edge
grouping, and result reading before following individual statements.

`init_edges_list()` resets visits/parents, clears the edge count, fills
lookup cells with `-1`, and indexes the starting component. `find_bcc()`
resets visits, saves low-links, resets the stack and visits, then groups
edges while retaining `back_num`. There are three DFS passes across the
two wrappers. Reproduce the same root and neighbor order.

Neither wrapper sweeps other components. `find_bcc()` does not clear the
result count or rows; repeated calls need explicit management. Reindexing
another component also changes the meaning of old edge indices.

## 6. New C syntax explained

Use the workbook's short expressions before the full code. Explain
row/column indexing, prefix versus postfix increments, chained assignment,
`continue`, `do ... while`, and included source definitions.

Ask why `continue` advances the neighbor loop, why `edge` is declared
outside `do`, and why the boundary is written before the condition ends
the loop. The textbook's `save_back_num()` is a review of an already
included function, so students must not create a duplicate definition.

## 7. C code

Read snippets in textbook order: dependencies, visit reset, neighbor
classification, edge storage, edge indexing, lookup preparation, low-link
review, result rows, grouping, and wrappers. Preserve the distinction
between stored vertex indices, visit numbers, and edge indices.

Predict before running both drivers from the repository root:

```sh
make -C module_06_graph_dfs/code lecture lecture-ppt
```

A reaches A–F with visits 1–6 and lows 1/2/3/2/2/2. Eight records produce
rows `[1]`, `[7,6,5,4,3,2]`, `[0]`, of lengths 1/6/1; all three blocks
share B. G–H and isolated I/J are unreached. The source graph has four
connected components. Peak calls are five, pending edges seven, neighbor
inspections sixteen per pass, and lookup writes one hundred.

The conceptual driver uses A–G data at indices 0–6 and prints actual
visit-number endpoints 1–7. Its two rows are `[7,6,5,4,3]` and
`[9,8,2,1,0]`. Both drivers finish with an empty stack.

Record commands and compiler diagnostics. Label lookup and intermediate
stack claims as source, hand-trace, or debugger evidence because the
drivers print final tables. Use the [answer key](../module_06_graph_dfs/instructor/answer_key.md)
and [technical notes](../module_06_graph_dfs/instructor/technical_notes.md)
for detailed checks.

Finish with retrieval of three targets: neighbor cases at 3, equality
closing at 4 → 3, and saved work in calls versus the edge stack. Preserve
first answers and require evidence for corrections. Optional Chapter 5
reconstruction and instructor-assigned mini-quizzes remain separate from
the seven-section reading. The legacy checked matrix assignment retains
its own contracts and assessment schedule.
