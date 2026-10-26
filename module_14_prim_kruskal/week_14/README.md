# Week 14 — Union-Find and Kruskal

This unit follows searching, sorting, and consolidation in
[Module 13](../../module_13_search_sort_consolidation/README.md) in the
[14-week course](../../Data_Structures_Course_2026_14_Week_Delivery_Guide.md).
DSU is new learning here. Linked nodes were introduced through the
[Week 7 linked-list unit](../../module_07_linked_list/README.md);
BST and AVL were combined in Week 12.

The edge-ordering step connects to Module 13's sorting lesson. The safe
comparator and sorting code are supplied here so the implementation work
stays on component merging and edge selection.

Students read the [lesson](textbook.md), complete the [one lab](lab.md), and
submit DSU/Kruskal code, tests, and the folded synthesis/integration evidence.
Faculty use the [180-minute plan](instructor.md).

## Scaffold and release manifest

Run `python prepare_release.py` to create `dist/week_14_dsu_kruskal.zip`.
It materializes the following files into a self-contained student scaffold:

- This README, lesson, lab, and `MANIFEST.txt`.
- `code/dsu.c`: supplied initialization, make-set, helpers, validation, and
  wrappers; students complete **find** and **union**.
- `code/mst/starter/kruskal.c`: supplied graph conversion, sorting, DSU setup,
  checked totals, and result commit; students complete **select_sorted_edges**.
- `code/mst/include/` and `code/mst/support/`: supplied interfaces, edge builder,
  relational comparator, graph operations, checked arithmetic, and validation.
  The original supplied DSU backend is excluded so it cannot bypass the TODOs.
- `code/mst/supplied/prim.c`: complete instructor-provided comparison algorithm;
  no student TODOs. It is intentionally supplied as reference/demo code.
- `code/test_dsu.c`, `code/mst/tests/test_core.c`, `code/test_student.c`, and
  a student Makefile.

In this repository, `code/Makefile` refers to the existing package support
files and Kruskal starter rather than duplicating them. The archive rewrites
these paths to its local copies. Student code consists of two files: `dsu.c`
and the Kruskal starter. Faculty solutions and this instructor plan are not
included. The complete Module 7 List/DSU and Module 14 staged labs are optional;
do not assign them in addition to this scaffold.
