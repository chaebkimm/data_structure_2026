# Module 6 Lesson Plan — Graph DFS and Edge Blocks

## Outcomes and materials

Use the [lab](../student/lab.c), [lecture material](../student/ppt_material.md),
[textbook](../student/textbook.md), [models](../diagrams/dfs_models.md), and
[chapter guide](../../instructor_guide/chapter_06.md). Students reuse Module
3 discovery/low-link state and Module 4's stack to index undirected edges
and extract biconnected components. The two meetings total 180 minutes.

## Meeting A — 90 minutes

1. **Retrieve the graph (15 minutes).** Preserve predictions. Build A–J
   from the included graph lab. Read insertion-order neighbor lists. Find
   four connected groups and predict which vertices root A can reach.
2. **Classify neighbors (20 minutes).** Trace recursive entry and the five
   neighbor cases. Distinguish a parent reverse entry from a back edge to
   another ancestor. Explain the simple-undirected assumption.
3. **Index edges (20 minutes).** Follow `init_edges_list(0)`. Give each
   reached connection one index and both lookup directions the same value.
   Check the eight records and the missing G–H index.
4. **Retrieve low-link values (25 minutes).** Trace `save_back_num()` from
   Module 3. Track F's connections to B and D, child-return propagation,
   and the final values 1/2/3/2/2/2. Preserve a hand trace before comparison.
5. **Exit prediction (10 minutes).** Identify B as a separating vertex.
   Predict which edges belong together and how a stack might hold them
   until a branch's postorder processing.

## Meeting B — 90 minutes

1. **Retrieve and introduce blocks (15 minutes).** Define edge blocks,
   one-edge bridge blocks, shared cut vertices, and no row for isolates.
   Distinguish vertex components from edge blocks.
2. **Trace the edge stack (25 minutes).** Push child tree edges and ancestor
   back edges. Trace every stack row in the lecture material. At C, D,
   and B returns, pop inclusive of the parent edge. Explain equality at D.
3. **Read the two-pass wrapper (15 minutes).** Follow `find_bcc()` resets.
   Explain why `back_num` survives the second `init_visit()` and why the
   same graph/root/order must reproduce discovery numbers. Count indexing
   as a separate third DFS pass in the overall pipeline.
4. **Predict, run, compare (15 minutes).** Run `make lecture` in `code`.
   Compare printed tables to the predictions. Locate the source statement
   explaining any revision. Do not execute unchecked invalid-input cases.
5. **Check scope and cost (10 minutes).** Count 16 neighbor entries per
   reached-component pass, 100 lookup initialization cells, seven peak
   pending edges, and five peak active calls. Inspect capacity and reset
   assumptions, including the `/* called once */` comment.
6. **Explain and revise (10 minutes).** Ask why C closes a one-edge block,
   D closes on equality, and G–H is absent. Require one evidence-based
   revision and an explanation of what a whole-graph extension must manage.

## Scope and assessment boundary

The lecture uses the unchanged array-based `student/lab.c`. Its existing
functions are the reading and tracing target; it is not a three-TODO
matrix-DFS assignment. The lab has no `main()`, so the lecture driver
provides initialization and printing.

The checked matrix starter, its tests, staged inquiry worksheets, rubric,
lab guide, and Practical 1 delivery schedule are a separate legacy track.
If that track is assigned, use its own contracts and release gates. Do not
apply its allocation/status or failure-preservation requirements to this
array lab. Updating the course-wide assessment schedule is outside this
lecture revision.
