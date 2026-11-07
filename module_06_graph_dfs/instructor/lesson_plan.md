# Module 6 Lesson Plan — Grouping connections in a graph

## Materials and scope

Follow the seven sections of the [English textbook](../student/textbook.md)
and [Korean textbook](../student/textbook_korean.md), using the
[bilingual workbook](../student/class_material.md) for predictions and evidence.
Use the [models](../diagrams/dfs_models.md), [concept slides](../student/ppt_material.md),
and [lab slides](../student/ppt_lab_material.md) at the matching topics.
The [chapter guide](../../instructor_guide/chapter_06.md) supplies teaching questions;
the [answer key](answer_key.md) follows the workbook's seven sections.

Two meetings total 180 minutes. The conceptual graph uses completed visit
numbers 1–7, replayed from visit 1 with ascending diagram neighbors. The C
lab's A–J graph uses stored insertion order and has a separate trace.

## Meeting A — 90 minutes

1. **Thinking logically: storage and exploration (20 minutes).** Review
   adjacency lists, then introduce an edge list and an adjacency matrix.
   Ask where 3–6 is stored, how absent edge 1–7 would be added, and which
   references disappear when vertex 7 is removed. Start DFS at visit 1;
   distinguish discovery numbers from storage indices.
2. **Thinking logically: neighbor cases and timing (20 minutes).** At
   visit 3 classify ancestor 1, parent 2, new child 4, processed descendant
   6 after 4 returns, and new child 7. Test the parent before the ancestor
   case. Place work at preorder, before child entry, after each child
   returns, and at postorder. Collect ten edges once despite twenty
   neighbor entries. Explain the symmetric lookup and its `-1` marker.
3. **Thinking logically: low-links and blocks (30 minutes).** Trace visit
   6's value from 6 to 3, unchanged by neighbor 4, then through 5 and 4.
   Finish with values 1/1/1/3/3/3/2. Define maximal blocks using internally
   vertex-disjoint paths, including the bridge case. Trace the textbook's
   five stack steps. Equality closes at 4 → 3 and 2 → 1; pop through the
   boundary edge. Distinguish the two five-edge blocks from one connected
   component and distinguish pending edges from active calls.
4. **Calculating efficiency (15 minutes).** Compare storage, traversal
   memory, adding an item, and traversal time in that order. Count seven
   vertex entries and twenty neighbor inspections per pass; three passes
   give 21 and 60. Lookup initialization writes 49 cells for this graph.
   Trace peak six calls and eight pending edges. Explain why reserved
   `edges[45]` does not enlarge `stack[10]`.
5. **Glossary (5 minutes).** Ask pairs to explain the workbook's six term
   pairs with examples. Require the difference between connected components
   and edge blocks, and between a cut vertex and a bridge.

## Meeting B — 90 minutes

1. **Retrieval and invariant (25 minutes).** Start with the workbook's
   three retrieval targets without sources. Preserve answers before
   corrections. State the accounting rule after each push or complete
   pop-and-store: every handled edge appears exactly once, pending or
   assigned. Count a forming result row as assigned. Check 8 = 3 + 5
   after the first block and 10 = 0 + 10 at completion.
   At visit 4's postorder, before parent 3 compares, split older prefix
   `1–2, 2–3, 1–3` from suffix `3–4, 4–5, 5–6, 3–6, 4–6`.
   The suffix belongs with its incoming edge; it closes only after return.
   At visit 3, suffix `2–3, 1–3, 3–7, 2–7` excludes older `1–2`,
   although that edge belongs to the same BCC. Ask what duplication,
   excluded boundaries, or changed traversal order would break.
2. **Coding plan (15 minutes).** Explicitly switch to the original A–J
   graph. Map preparation, edge recording, low-link calculation, grouping,
   and reading results to the wrappers. Locate all three DFS passes.
   `init_visit()` resets time, discovery, and parents, preserving low-links.
   Edge indexing precedes grouping; the graph, root, and neighbor order
   must remain consistent. Identify the missing result reset before reuse.
3. **New C syntax explained (15 minutes).** Work through two-dimensional
   indexing, prefix/postfix increments, chained assignment, `continue`,
   `do ... while`, and includes. Ask why equality falls through to
   `close_bcc()`, why the boundary is stored before stopping, and why the
   review copy of `save_back_num()` is already supplied by the include.
4. **C code and evidence (30 minutes).** Read the annotated snippets in
   textbook order. Predict the A–J driver, then run both drivers. A reaches
   A–F: eight records give result lengths 1/6/1. The conceptual driver gives
   two five-edge blocks. Resolve raw row indices into endpoint pairs and
   label lookup/intermediate-stack checks as hand, source, or debugger
   evidence. Compare 16 neighbor entries and 100 lookup writes in the A–J
   setup with the conceptual example. Record command and diagnostics.
5. **Explain and correct (5 minutes).** Revisit the initial predictions.
   Require one correction supported by a branch, number, or code statement.
   Any separately assigned mini-quiz follows the classroom instructions.

## Evidence and assignment boundary

From the repository root, run:

```sh
make -C module_06_graph_dfs/code lecture lecture-ppt
```

The lab has no `main()`; each driver supplies it. Valid simple undirected
input and fitting capacities are preconditions. The stack and edge helpers
are unchecked, and `find_bcc()` is used once in a fresh program.

The checked matrix starter, tests, staged worksheets, rubric, and legacy
lab guide retain their own contracts. Stage D reading enrichment does not
change Stage E's matrix exercise or the assessment schedule. Chapter 5
tree reconstruction remains an optional, separate retrieval activity.
