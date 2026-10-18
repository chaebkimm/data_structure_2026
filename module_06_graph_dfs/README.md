# Module 6 Teaching Package — Graph DFS and Blocks

The [concept slides](student/ppt_material.md) drive the question-led
lesson. Their diagram displays the completed visit numbers 1–7 of a
fixed DFS. Refer to vertices by visit number and retrace from visit 1
with ascending diagram neighbors. The current [lab.c](student/lab.c)
and [lab slides](student/ppt_lab_material.md) retain the original A–J
coding example with a separate reference trace.
The revised lab slides order each call as preorder work, a neighbor loop,
then postorder work. They teach `init_visit()` separately before edge
storage and explain the boundary pop using inner blocks already removed
by deeper child-return comparisons. The lab's behavior is unchanged.

## Current teaching path

- [English textbook](student/textbook.md) and [Korean textbook](student/textbook_korean.md).
- [Bilingual workbook](student/class_material.md): neighbor questions,
  timing, three representations, pair collection, earliest reconnection,
  full pair stacks/two blocks, review, coding evidence, and mini-quiz submission activity.
- [Chapter guide](../instructor_guide/chapter_06.md) and
  [lesson plan](instructor/lesson_plan.md): two 90-minute meetings in slide order.
- [Models](diagrams/dfs_models.md): visit-numbered graph, traversal,
  complete pending pairs, two blocks, and original source reference.
- [Answer key](instructor/answer_key.md) and [technical notes](instructor/technical_notes.md):
  concept/coding values, resets, capacities, and costs.
- [Original driver](code/lecture/lab_demo.c) for original A–J verification.
- [Optional slide driver](code/lecture/ppt_demo.c) for an independent C experiment.

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

Review graph storage/addition/deletion, block definition/finding, and
Chapter 5 tree reconstruction. Complete the instructor's mini-quiz and
submit through the classroom instructions, as requested by the final slide.

## Coding verification: original A–J source

From `code`, run:

```sh
make lecture
```

Plain `make` runs the same original driver. Run `make lab-tests` for nine
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
