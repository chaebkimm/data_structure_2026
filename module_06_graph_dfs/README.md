# Module 6 Teaching Package — Graph DFS and Biconnected Components

The current textbook and lecture follow [student/lab.c](student/lab.c).
The lab includes Module 3's undirected adjacency-list graph and discovery/
low-link algorithms, and Module 4's unchecked integer stack. Recursion
explores vertices; the explicit stack stores edge indices awaiting block
assignment.

## Current teaching path

- [Textbook](student/textbook.md): neighbor classification, edge indexing,
  saved low-link values, and postorder block extraction.
- [Lecture material](student/ppt_material.md): Korean slide-ready notes and
  the exact root-A edge/stack trace.
- [Chapter guide](../instructor_guide/chapter_06.md): board walkthrough and
  common mistakes.
- [Lesson plan](instructor/lesson_plan.md): two 90-minute meetings.
- [Technical notes](instructor/technical_notes.md) and
  [answer key](instructor/answer_key.md): contracts, resets, reference output,
  and capacity assumptions.
- [Models](diagrams/dfs_models.md): graph, DFS edges, pending stack, and blocks.
- [Lecture driver](code/lecture/lab_demo.c): runs the unchanged lab and
  prints its active results.

From `code`, run:

```sh
make lecture
```

The lab has no `main()`. The driver initializes A–J, builds the supplied
nine-edge graph, and calls `init_edges_list(0)` then `find_bcc(0)` in a
fresh process.

## Learning targets

Students explain how discovery numbers stop repeated recursion, classify
five neighbor cases in a simple undirected graph, index each reached edge
once, propagate low-link values, and use an edge stack to emit blocks.
They distinguish connected groups of vertices from blocks of edges,
explain equality at block boundaries, and identify reset/capacity limits.

Root A reaches A–F. Eight indexed edges produce rows `[1]`,
`[7,6,5,4,3,2]`, and `[0]`, with sizes 1/6/1 and an empty final stack.
G–H and isolated I/J are outside this run. The wrappers handle one starting
component and `find_bcc()` is marked for one call. Input validation,
whole-graph extraction, and repeatability are extensions.

## Legacy checked-DFS exercise

The matrix-based `code/include`, `code/support`, `code/starter`,
`code/solution`, and existing tests retain their separate public API.
[code/README.md](code/README.md) and [student/lab.md](student/lab.md) describe
that exercise, including status codes, typed vertex-stack DFS, failure
preservation, and the three TODOs.

The staged inquiry/worksheet/pause files, evidence template, rubric,
autopsy, release scripts, and course-wide Practical 1 delivery schedule
also remain on that legacy track. Use their existing release gates if
assigning it. Those contracts and assessments do not describe
`student/lab.c`. This revision updates the textbook and lecture path;
it does not migrate the assessment or release archives.
