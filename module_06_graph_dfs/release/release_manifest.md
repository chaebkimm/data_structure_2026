# Module 6 Staged Release Manifest

Run `prepare_student_release.ps1` from this directory to create five ZIP
archives in `../dist`. The script refuses to overwrite an existing archive.

Stages A–C and E belong to the separate checked adjacency-matrix DFS
exercise. The current Stage D textbook and models instead follow the
array-based `student/lab.c` edge-list/BCC lab. Stage D is enrichment; it
does not specify Stage E's implementation or assessment contracts. Use
`student/lab.md` and the public headers for the checked exercise. The
current array-lab classroom path is listed in the [module overview](../README.md).

## Stage A — Route-Memory Inquiry

Release before Meeting A:

- standard initial prompt;
- linear accessible initial prompt.

This stage retrieves prior graph and branch-first ideas but contains no DFS
name, visited array, frontier, recursion or Stack procedure, code, exact
canonical answer, solution, or instructor material.

## Stage B — Representation and Cognitive Pause

Release after initial route-memory models are preserved:

- representation reveal;
- exactly-three-target Cognitive Pause;
- vocabulary reference.

The vocabulary file remains closed until the pause response is preserved.
Approved extended-time or asynchronous versions use the same three targets.

## Stage C — Graph DFS Investigation

Release after the pause and instructor comparison:

- standard investigation worksheet;
- linear accessible investigation worksheet.

Sections A through F are the Stage C core. They prompt matrix, recursive,
Stack, reachability, component, and cost reasoning without supplying the
answer key. Sections G through I are later extensions and reflection.

## Stage D — Beginner Textbook and Models

If assigning this enrichment, release after the student completes and
preserves the Stage C core:

- array-lab textbook: edge indexing, saved low-link values, and edge-block
  extraction;
- diagrams with exact text equivalents.

The current coding reference uses `init_edges_list()` to prepare discovery,
edge count, and symmetric lookup before indexing. `find_bcc()` then runs
low-link and extraction passes with a discovery reset between them.
The source reserves 45 edge records and nine 45-entry result rows, while
the reused pending-edge stack still has ten entries. These array-lab
limits do not change the checked matrix exercise's capacities.

The explicit stack in these files stores edge indices for block extraction.
Stage E uses a typed vertex-ID Stack for iterative DFS. The two teaching
paths have different outputs and contracts.

## Stage E — Lab and Evidence

Release after retrieval and any assigned Stage D enrichment in Meeting B:

- lab, rubric, evidence template, and Graph DFS Autopsy;
- public headers, supplied graph and vertex-Stack support, and starter DFS;
- supplied core and self-loop tests plus a student-test template;
- student-only PowerShell and GNU Make build files;
- bounded, solution-independent faulty-cycle autopsy.

Stage E excludes:

- `instructor/`;
- `code/solution/`;
- `code/tests/test_extension.c`;
- any instructor answer key;
- Stages A through D;
- any unbounded faulty program.

## Instructor verification

Before release, build the reference core tests, instructor extensions,
standalone self-loop test, and isolated autopsy with the commands in
`../code/README.md`. Use warning-enabled and sanitizer-enabled builds where
the installed compiler supports them.
