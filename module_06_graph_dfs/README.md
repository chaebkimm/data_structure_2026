# Module 6 Teaching Package — Grouping connections in a graph

The [English textbook](student/textbook.md) and [Korean textbook](student/textbook_korean.md)
set the lesson's seven-section sequence: Thinking logically, Calculating
efficiency, Glossary, Invariant, Coding plan, New C syntax explained, and
C code. Use the [concept slides](student/ppt_material.md) and
[lab slides](student/ppt_lab_material.md) alongside matching questions.

The conceptual graph uses completed DFS visit numbers 1–7. Replay from
visit 1 with ascending diagram neighbors. The [lab](student/lab.c) uses
a separate A–J graph and stored neighbor insertion order.

## Current teaching path

- [Bilingual workbook](student/class_material.md): seven sections of
  predictions, graph traces, efficiency counts, vocabulary comparisons,
  invariant checkpoints, a coding plan, syntax questions, and code evidence.
- [Chapter guide](../instructor_guide/chapter_06.md) and
  [lesson plan](instructor/lesson_plan.md): the same sequence across two
  90-minute meetings.
- [Models](diagrams/dfs_models.md): conceptual graph, tree/back edges,
  pending stacks, blocks, and the separate alphabet example.
- [Answer key](instructor/answer_key.md): answers in workbook order.
- [Technical notes](instructor/technical_notes.md): detailed correctness,
  reset behavior, capacity limits, and reference outputs.
- [Vocabulary](student/vocabulary.md): current graph/block terms followed
  by the separate legacy matrix exercise's vocabulary.
- [Alphabet driver](code/lecture/lab_demo.c) and
  [conceptual-graph driver](code/lecture/ppt_demo.c): separate executable examples.

## Primary concept diagram

Review Chapter 3's adjacency lists, then introduce edge lists and adjacency
matrices in Chapter 6. Chapter 3 did not teach those two representations.

Endpoint visit pairs are 1–2, 1–3, 2–3, 2–7, 3–4, 3–6, 3–7, 4–5, 4–6, 5–6.
The diagram's numbers are visit numbers. Blank circles ask students to fill
numbers at a stage; highlighted connections show progress.

Visit 3 encounters ancestor 1, parent 2, children 4/7, and processed
descendant 6. Collect each connection once from child/ancestor encounters.
Earliest reconnection values for visits 1–7 are 1/1/1/3/3/3/2. The stack
emits `[4–6,3–6,5–6,4–5,3–4]` and `[2–7,3–7,1–3,2–3,1–2]`, five
pairs each, sharing visit 3. Explain the parent's boundary comparison
immediately after each child returns, including the equality case.

Explain storage/addition/deletion, low-link values, block boundaries, and
the accounting/postorder invariants. Chapter 5 reconstruction and any
instructor-assigned mini-quiz remain separate review activities.

## Coding verification: original A–J source

From the repository root, run both examples:

```sh
make -C module_06_graph_dfs/code lecture lecture-ppt
```

Plain `make` from `code` runs the alphabet driver. Run `make lab-tests` there for nine
array-lab regression checks, including both supplied graphs, inclusive
boundaries, root branches, and the separate record/result/stack limits.

The original driver initializes A–J, then calls `init_edges_list(0)` and
`find_bcc(0)` in a fresh process. A reaches A–F; eight records produce
`[1]`, `[7,6,5,4,3,2]`, `[0]`, sizes 1/6/1, with an empty stack.
These original C rows differ from the concept graph's two blocks.
`init_edges_list()` resets discovery/parents, clears the edge count and
active lookup, then indexes the reached edges. `find_bcc()` computes
low-link values and replays discovery for extraction: three DFS passes
across the two wrappers. The low-link and extraction passes must reproduce
the same starting vertex and neighbor order.
The wrappers process one starting group and `find_bcc()` is marked for one
call. Validation, whole-graph extraction, and repeatability remain extensions.
The current lab reserves `edges[45]`, `bcc[9][45]`, and `bcc_size[9]`.
The imported `stack[10]` still limits simultaneously pending edge indices
to ten; record capacity alone does not make every ten-vertex graph fit.

The optional slide driver uses neutral A–G data at internal indices 0–6,
but prints edge endpoints from actual visit numbers 1–7. See technical notes
for its independent compile/run command. Array indices, C record IDs,
and the distinction from visit numbers belong to this coding experiment.

## Legacy checked-DFS exercise

The matrix API, starter, support, solution, and matrix tests keep separate
contracts. [code/README.md](code/README.md) and [student/lab.md](student/lab.md)
describe status codes, typed vertex-stack DFS, failure preservation,
and three TODOs for that exercise.

Older inquiry/worksheet/pause files, evidence template, rubric, autopsy,
and Practical 1 schedule retain legacy scope. The
[release manifest](release/release_manifest.md) separates matrix Stages
A–C/E from Stage D textbook/model enrichment; Stage D does not change
Stage E's contract. Use the current bilingual workbook for this lesson.
