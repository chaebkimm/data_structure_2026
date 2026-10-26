# Instructor Plan — Module 13: Searching, Sorting, and Consolidation

Use the complete [lab.c](../student/lab.c), [English textbook](../student/textbook.md) or [Korean textbook](../student/textbook_korean.md), [workbook](../student/class_material.md), [concept slides](../student/ppt_material.md), and [lab slides](../student/ppt_lab_material.md). This lesson has one 180-minute budget and one submission. Students trace/test supplied code and justify choices rather than implement four new algorithms from scratch.

## Before class

Run `make -C code` from the module root. Prepare six indexed cards 31,23,17A,8,17B,42. Labels A/B identify equal records only on paper; the C lab stores integers. Prepare independent value copies, a six-slot scratch area, and a workload table with preparation/query/update/order/space columns. Preserve predictions before showing results. Accept structured text or oral explanation instead of drawings.

## 180-minute sequence

| Activity | Minutes | Required evidence |
| --- | ---: | --- |
| Retrieval and linear/binary first-match search | 35 | Original index 2, sorted index 1, half-open interval trace and final check |
| Insertion and merge sorting | 55 | Five ordered prefixes, eight shifts, split/merge/scratch trace, equal-record stability reasoning |
| Build and focused tests | 25 | Supplied core plus three original search/sorting/boundary groups, predicted/observed output |
| Consolidation and workload selection | 45 | Six scenarios comparing preparation/query/update/order/storage and a justified alternative |
| Correction and single submission | 20 | Concrete counts, one preserved correction, complete evidence checklist, Module 14 ordering transfer |
| **Total** | **180** | |

Use a five-minute individual pause near the end of the search/sorting work. Its time is included above. Ask exactly three targets: (1) the next binary range on equality and the final check; (2) the 17A/17B insertion/merge choice and why integer output alone is insufficient; (3) one query versus many fixed-snapshot queries including preparation. Preserve answers before calibration. Do not add another pause or submission outside the budget.

## Which question starts the lesson?

Ask, “Where is the first 17 in these six records, and what would we have to change to exclude several candidate positions at once?” Start with the original input. Let students articulate the need for order before naming binary search. Do not present the sorted index as the original record's identity.

For insertion sort, ask what must be saved before larger values move. For merge sort, ask where output can be written without overwriting unread input. Reveal stable tie choices only after students predict the positions of A and B.

## Consolidation boundaries

Students use the [lab's six scenarios](../student/lab.md), not a new implementation project. For each, require a chosen method and a competing method with preparation, query, update, ordering, and storage assumptions. Retrieve fixed-array/list/hash/AVL/heap/frontier invariants. If using an existing capstone example, annotate its current workload and representation; do not assign a second integration build here. Module 14 retains DSU/MST teaching and the final integration checkpoint.

A sorted linked list still pays to reach its middle. A heap answers minimum selection, not arbitrary-key lookup. Hash expected bounds need distribution assumptions; AVL logarithmic paths need maintained balance. BFS/DFS/Dijkstra answer relationship or path questions, not the same query as exact-key search. Treat those distinctions as the core consolidation evidence.

## Check and release

Use the [answer key](answer_key.md) and [technical notes](technical_notes.md). Assess the [single rubric](../student/rubric.md). The [release packager](../release/prepare_student_release.py) excludes faculty files. Extract and run it before distribution. General-purpose sorting libraries, quicksort/radix/heap-sort implementation, record-valued sorting, and DSU/MST code are extension topics; none gates core credit.
