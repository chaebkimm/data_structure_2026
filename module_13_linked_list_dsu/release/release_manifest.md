# Module 13 Staged Release Manifest

Run `prepare_student_release.ps1` from this directory to create five ZIP
archives in `../dist`. The script refuses to overwrite an existing archive.

## Stage A — Records and Changing Groups

Release before Meeting A:

- standard initial prompt;
- linear accessible initial prompt.

This stage uses ordinary card, arrow, relationship, and group language. It
contains no formal linked-list, ownership, Union-Find, parent-forest,
edge-list, sorting, invariant, complexity, API, code, repair, or exact-result
language. It supplies no completed card state, parent array, component-size
array, method, answer key, solution, or instructor material.

## Stage B — Representation and Cognitive Pause

Release after initial models are preserved:

- representation reveal;
- exactly-three-target Cognitive Pause;
- vocabulary reference.

The vocabulary file remains closed until the pause response is preserved.
Approved extended-time or asynchronous versions use the same three targets.

## Stage C — Linked-List and Union-Find Investigation

Release after the pause and instructor comparison:

- standard investigation worksheet;
- linear accessible investigation worksheet.

Sections A through F are the Stage C core. Sections G through I are later
testing, prelab, autopsy, and synthesis work. The files supply questions, not
the answer key.

## Stage D — Beginner Textbook and Models

Release after the student completes and preserves the Stage C core:

- an ultra-concise, example-first textbook of 1,050 through 1,200 words;
- diagrams with exact node-link, ownership, parent-array, compression,
  component-size, and edge-record linear text equivalents.

## Stage E — Lab and Evidence

Release after retrieval and Stage D calibration in Meeting B:

- lab, rubric, evidence template, and Linked-List Autopsy;
- public linked-list, DSU, and undirected edge-list headers;
- linked-list and DSU starter implementations;
- supplied undirected logical-edge builder and relational `qsort` comparator;
- visible core tests and student-test template;
- student-only PowerShell and GNU Make build files; and
- the bounded, isolated faulty linked-deletion program.

The canonical linked list has configured limit 4 and three live nodes:
`17 -> 23 -> 31`. Deleting 23 leaves `17 -> 31`. Destruction restores the
exact all-zero state: null head, size 0, and limit 0.

For IDs A through H, unions
`A-B, C-D, A-C, E-F, G-H, E-G, A-E` produce:

```text
parent          [A, A, A, C, A, E, E, G]
component_size  [8, 0, 0, 0, 0, 0, 0, 0]
```

Finding H compresses the parent array to
`[A, A, A, C, A, E, A, A]`. D-H then performs no merge, identifies a
cycle-producing relationship, and compresses D.

Stage E excludes:

- `instructor/`;
- `code/solution/`;
- `code/tests/test_extension.c`;
- instructor build files, solution targets, and extension targets;
- answer keys and completed TODOs;
- Stages A through D;
- full Prim, Kruskal, or minimum-spanning-tree implementations;
- graph traversal implementations;
- a capstone migration to linked adjacency;
- unrelated linked-list and dynamic-connectivity extensions;
- live host or network input; file or network clients; and
- generated binaries, build directories, partial archives, and any
  non-isolated faulty program.

The Stage E autopsy is the sole intentional memory defect. It is compiled as
a separate executable and is never linked into normal tests. Ordinary
autopsy commands define `AUTOPSY_INSPECT_ONLY` and run safely. The explicit
unsafe target uses sanitizers, compiles the actual faulty branch, and never
runs it automatically.

## Stage A embargo

Scan all three Stage A files case-insensitively for formal terms and
variants, including:

```text
linked list, singly linked, node, pointer, address, head, tail, NULL,
struct, malloc, free, ownership, leak, dangling, use-after-free,
push_front, remove_first, list_destroy, traversal,
DSU, disjoint set, Union-Find, make_set, find, union,
parent, component_size, component size, size array, root, representative,
tree, forest, path compression, component, connectivity, cycle,
graph, vertex, edge, adjacency, edge list,
Kruskal, minimum spanning tree, MST, qsort, comparator,
invariant, amortized, inverse Ackermann, alpha,
complexity, API, TODO, pseudocode, solution, answer key, instructor
```

Also reject Big-O forms, formulas, C syntax, fenced code, public names,
completed repair steps, exact parent arrays, and exact component-size arrays.
The standard and linear prompts must preserve identical IDs, relationship
order, numbers, questions, and scoring.

## Archive inventory

The five archives contain exactly:

```text
module_13_stage_a_initial_inquiry.zip       3 entries
module_13_stage_b_representation_pause.zip 4 entries
module_13_stage_c_investigation.zip         3 entries
module_13_stage_d_textbook_models.zip       3 entries
module_13_stage_e_lab.zip                  18 entries
```

The source package contains exactly 43 files before `dist`: 26 Markdown, 3
PowerShell, 2 Makefiles, 9 C files, and 3 headers.

## Instructor verification

Before release:

- build reference core tests, instructor extensions, and the isolated autopsy
  using the commands in `../code/README.md`;
- verify ordinary autopsy targets run only `AUTOPSY_INSPECT_ONLY` and unsafe
  targets compile with sanitizers without executing the resulting binary;
- use strict warnings and sanitizers where the installed compiler supports
  them;
- verify the canonical limit is 4, forced allocation failure has one spare
  slot, and destruction clears head, size, and limit to zero;
- verify the exact parent and component-size traces above;
- verify invalid IDs are rejected before indexing and outputs are preserved
  on failure;
- verify every logical edge ID has exactly two validated incident records;
- verify self-loops use two identical records and parallel IDs survive;
- verify the comparator handles `INT64_MIN` and `INT64_MAX` without
  subtraction;
- confirm exactly three implementation TODO clusters and three student-test
  TODO categories;
- confirm exactly three Cognitive Pause targets;
- confirm the Stage D textbook has 1,050 through 1,200 words;
- confirm the five archive entry counts are 3, 4, 3, 3, and 18;
- compare every ZIP entry byte-for-byte with its listed source file;
- confirm Stage E contains none of its excluded material; and
- confirm a second packaging attempt is rejected without changing archive
  hashes or leaving a partial file.
