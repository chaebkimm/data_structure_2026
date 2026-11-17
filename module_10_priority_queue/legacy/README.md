# Archived Chapter 10 Materials

These files preserve the superseded indexed-heap Dijkstra teaching package and alternative priority-queue/heap examples. They are historical references, excluded from the current lesson, default builds and student release. The active package now follows the unchanged sorted-array meeting-time lab.

## Layout

- student/, instructor/, diagrams/ and README.md.pre-alignment contain the former teaching documents, including the graph autopsy and alternative _lab_*.c examples.
- code/ retains the earlier Dijkstra library headers, support, starter, solution, autopsy, drivers and build recipes.
- release/ retains the former release tooling and templates.
- dist/ retains the old module_11_graph_dijkstra.zip without altering its bytes.

Original relative directory layout is preserved. Historical names and week labels are not current instructions. The previous top-level README snapshot is README.md.pre-alignment; this index replaces its copied name.

## Source and build boundary

No user-owned lab.c or presentation file was moved, copied into this archive, or modified. The historical teaching drivers test an indexed-heap source that is not the current student/lab.c. Those drivers are retained as historical evidence and are not runnable against the new lab. Missing historical source links are shown as text instead of being redirected to an unrelated implementation.

The separate Dijkstra library under code/include, support, starter and solution retains its own API. Its library drivers test_core.c, test_extension.c and test_student.c belong to that API, not the active teaching lab. The old Makefile's lab/core/student/comparison targets must not be used as current build instructions. The retained distribution ZIP is the original historical package, not the new release.

Use [the current package](../README.md), [current textbook](../student/textbook.md), and [current build guide](../code/README.md) for Chapter 10.
