# Module 6 Lesson Plan — Question-led Graph DFS

## Materials and scope

Follow [concept slides](../student/ppt_material.md), the
[bilingual workbook](../student/class_material.md),
[models](../diagrams/dfs_models.md), and
[chapter guide](../../instructor_guide/chapter_06.md).
Use [lab slides](../student/ppt_lab_material.md) and the current
[lab](../student/lab.c) for the final coding connection.
Two meetings total 180 minutes. The completed concept diagram is numbered
by visits 1–7 from a fixed DFS; refer to vertices by those visit numbers.
Retrace from visit 1 with ascending diagram neighbors. Original A–J coding
verification retains its stored insertion order and separate reference.

## Meeting A — 90 minutes

1. **Retrieve and classify (25 minutes).** Review endpoints, neighbor lists,
   tree/back connections, and visit/earliest-reconnection numbers. Preserve
   predictions. At visit 3 classify ancestor 1, parent 2, new child 4,
   processed descendant 6 after 4 returns, and new child 7. Recognize the
   parent before interpreting a smaller visit number as a back connection.
2. **Locate action timing (20 minutes).** Assign the number at entry, set
   a child's parent before descent, resume the parent's scan after return,
   and identify postorder after all neighbors. Annotate the blank circles
   with visit numbers and highlight handled connections at each stage.
3. **Review lists and introduce two representations (25 minutes).** Review
   the adjacency lists taught in Chapter 3. Introduce Chapter 6's new
   endpoint-pair edge list and symmetric adjacency matrix for the same graph.
   Compare neighbor scanning, separate connection records, and direct pair
   lookup. Practice adding/deleting 3–6 and removing a vertex's incident pairs.
4. **Deduplicate (20 minutes).** Collect only at child entry and non-parent
   ancestor encounters. Write ten canonical endpoint visit pairs in order.
   Explain why 1 → 3 adds nothing when visit 1 eventually resumes.

## Meeting B — 90 minutes

1. **Retrieve earliest reconnection (15 minutes).** Ask for visit 6's value
   before revealing 3. Trace 6 → 3 lowering 6 to 3 and 6 → 4 leaving it
   unchanged. Propagate through visits 5 and 4. Finish with
   1/1/1/3/3/3/2 for visits 1–7.
2. **Find two blocks (25 minutes).** Define maximal groups with two
   internally vertex-disjoint paths between every pair. Predict two
   five-edge blocks sharing visit 3. Trace the full endpoint-pair stack
   at every event. At 4 → 3, equality 3 ≥ 3 emits the right block;
   at 2 → 1, equality 1 ≥ 1 emits the left block. Include the boundary pair.
   Distinguish unfinished calls from pending connections.
   Use workbook 6.1 to state the invariant: every handled edge is exactly
   once either pending or assigned, including the result row being formed.
   Check empty initialization, push/pop-and-store preservation, and final
   empty-stack coverage. At 3 → 2, ask why the right block is already
   assigned while five pairs remain pending; a returned subtree need not
   leave all its edges on the stack. Explain why the qualifying suffix
   includes its boundary and why equality closes it.
   Add the postorder checkpoint **before** the node returns and its parent
   compares: after all neighbors and child boundaries, every branch edge
   is pending or assigned. For a nonroot node, the suffix from its incoming
   parent edge through the top is exactly that edge and its branch's
   unassigned edges, all in the same eventual BCC as the incoming edge.
   At visit 4, separate older prefix `1–2, 2–3, 1–3` from suffix
   `3–4, 4–5, 5–6, 3–6, 4–6`; parent 3 closes only after return.
   At visit 3, suffix `2–3, 1–3, 3–7, 2–7` excludes older `1–2`,
   which is in the same BCC. The whole stack need not be one BCC, and a
   suffix need not yet be the full BCC. Root postorder has an empty stack.
   판서 확인: 부모에게 복귀하기 전, 들어온 부모 간선부터 위의 구간은 모두
   그 부모 간선과 같은 최종 BCC다. 전체 스택이나 완성된 BCC와 구별한다.
3. **Retrieve and review (15 minutes).** Use exactly the workbook's three
   targets for a five-minute retrieval pause and preserve first answers.
   Review graph storage/addition/deletion and block definition/finding.
   Reconstruct Chapter 5's separate tree from preorder `ABDECFG` and
   inorder `DBEAFCG`; verify postorder `DEBFGCA`.
4. **Connect to C and run (25 minutes).** Explicitly switch to A–J. Read
   `_edge_iteration_()` before indexing/extraction specializations. Follow
   record/push, parent assignment, recursion, then the parent's immediate
   child-return comparison and inclusive boundary pop when required.
   Match `init_edges_list()`'s discovery/count/lookup preparation and
   `find_bcc()`'s five actions. Identify indexing, low-link calculation,
   and extraction as three passes. Read the strict `<` continuation and
   inclusive boundary pop after each child returns. Predict then run
   `make lecture`: original eight records give sizes 1/6/1. The optional
   [slide driver](../code/lecture/ppt_demo.c) uses internal indices 0–6 with
   A–G data but prints actual visit-number endpoints for the two five-edge blocks.
5. **Explain, check, and submit quiz (10 minutes).** Count 16 neighbor
   entries per original A-started pass, three passes, 100 lookup writes,
   five peak calls, and seven pending pairs. Compare `edges[45]`,
   `bcc[9][45]`, and `bcc_size[9]` with the reused `stack[10]`;
   45 records do not enlarge the pending stack. Locate the one-call reset
   limitation and require a source-backed correction. Follow the final
   slide's mini-quiz submission prompt using the instructor's classroom
   instructions; no external submission is performed by these materials.

## Evidence and assignment boundary

Use the workbook and [answer key](answer_key.md). Keep concept visit pairs
separate from C indices and original A–J rows. The lab has no entry point;
the driver supplies it. Fixed arrays and stack helpers are unchecked.

The checked matrix starter, tests, older staged worksheets, rubric,
lab guide, and Practical 1 schedule retain separate legacy contracts.
Stage D textbook/model enrichment does not change Stage E's matrix exercise.
This lesson does not alter the assessment schedule.
