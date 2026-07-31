# Module 14 Staged Release Manifest

Run `prepare_student_release.ps1` from this directory to create five ZIP
archives in `../dist`. The script refuses to overwrite an existing archive.

## Stage A - Records and Arrival Order

Release before Meeting A:

- standard initial prompt;
- linear accessible initial prompt.

All three Stage A files use ordinary record, number, arrangement, route, and
arrival-order language. They contain no formal representation name,
implementation vocabulary, formula, code, completed repair, exact result,
solution, or instructor material.

## Stage B - Representation and Cognitive Pause

Release after initial models are preserved:

- representation reveal;
- exactly-three-target Cognitive Pause;
- vocabulary reference.

The vocabulary file remains closed until the pause response is preserved.
Approved extended-time or asynchronous versions use the same three targets.

## Stage C - BST-to-AVL Investigation

Release after the pause and reference-model comparison:

- standard investigation worksheet;
- linear accessible investigation worksheet.

Both worksheet forms preserve identical keys, insertion orders,
measurements, rotation cases, questions, and scoring. The files supply
questions, not the answer key.

## Stage D - Beginner Textbook and Models

Release after the student completes and preserves the Stage C core:

- an ultra-concise, example-first textbook of 1,050 through 1,200 words;
- diagrams with exact strict-order, height, balance, rotation, validation,
  measurement, and cost linear equivalents.

## Stage E - Lab and Evidence

Release after retrieval and Stage D calibration in Meeting B:

- lab, rubric, evidence template, and Tree-Rotation Autopsy;
- public tree-model, BST-baseline, and AVL-tree headers;
- AVL rotation and AVL insertion starter implementations;
- supplied baseline, measurement, allocation-hook, validation, and cleanup
  support;
- visible core tests and student-test template;
- student-only PowerShell and GNU Make build files; and
- the bounded, isolated faulty-left-rotation program.

The required tree contract uses strict unique `int` keys and at most 64 live
nodes. Null edge-height is `-1`, leaf edge-height is `0`, and balance factor
is left height minus right height. An AVL node must have factor `-1`, `0`, or
`1`.

Canonical rotation cases are:

```text
LL: 30, 20, 10
RR: 10, 20, 30
LR: 30, 10, 20
RL: 10, 30, 20
```

Every result has root 20, children 10 and 30, root height 1, and leaf heights
0.

The mixed order is:

```text
8, 4, 12, 2, 6, 10, 14, 1, 3, 5, 7, 9, 11, 13, 15
```

Ascending and descending plain BSTs have edge-height 14; their required
deepest and missing searches each take 15 comparisons. The mixed plain BST
has edge-height 3; its required searches each take 4 comparisons. All three
AVL results have root 8, edge-height 3, and four comparisons for the
corresponding searches.

Stage E excludes:

- `instructor/`;
- `code/solution/`;
- `code/tests/test_extension.c`;
- instructor build files, solution targets, and extension targets;
- answer keys and completed TODOs;
- Stages A through D;
- full AVL deletion;
- unrelated graph or minimum-spanning-tree implementations;
- live host or network input, file clients, and network clients; and
- generated binaries, build directories, partial archives, and any
  non-isolated faulty program.

The Stage E autopsy is the sole intentional pointer-link defect. It is
compiled as a separate executable and is never linked into normal tests.
Ordinary autopsy commands define `AUTOPSY_INSPECT_ONLY` and run safely. The
explicit unsafe target requires sanitizers, compiles the actual faulty
branch, and never runs it automatically.

## Stage A embargo

Scan all three Stage A files case-insensitively for formal terms and variants,
including:

```text
BST, AVL, binary search tree, tree, node, root, key,
left child, right child, child, subtree, inorder,
height, balance, balance factor, rotation, rotate,
LL, RR, LR, RL, skew,
algorithm, complexity, Big-O, logarithm, validator, invariant,
allocation, malloc, free, pointer, struct, NULL,
code, API, TODO, pseudocode, solution, answer key, instructor,
denial of service, DoS, attacker
```

Also reject `O(...)` forms, formulas, fenced code, public names, exact
completed rewiring, exact completed shapes, and supplied measurement answers.
The standard and linear prompts must preserve identical records, arrival
orders, numbers, questions, and scoring.

## Archive inventory

The five archives contain exactly:

```text
module_14_stage_a_initial_inquiry.zip       3 entries
module_14_stage_b_representation_pause.zip 4 entries
module_14_stage_c_investigation.zip         3 entries
module_14_stage_d_textbook_models.zip       3 entries
module_14_stage_e_lab.zip                  18 entries
```

The source package contains exactly 43 files before `dist`: 26 Markdown, 3
PowerShell, 2 Makefiles, 9 C files, and 3 headers.

## Instructor verification

Before release:

- build reference core tests, instructor extensions, and the isolated
  autopsy using the commands in `../code/README.md`;
- verify ordinary autopsy targets run only `AUTOPSY_INSPECT_ONLY` and unsafe
  targets compile with sanitizers without executing the resulting binary;
- use strict warnings and sanitizers where the installed compiler supports
  them;
- verify duplicate, full-capacity, and allocation failures preserve the
  complete prior state;
- verify null height `-1`, leaf height `0`, and left-minus-right factors;
- verify all four canonical triples and exact final root, children, and
  heights;
- verify the exact 15-key heights and comparison counts;
- verify all validators accept the canonical states and reject isolated
  ordering, stored-height, balance, size, and shape faults;
- verify the supplied bounded full validators are documented as `O(n^2)`;
- confirm exactly three implementation TODO clusters and three student-test
  TODO categories;
- confirm exactly three Cognitive Pause targets;
- confirm the Stage D textbook meets its assigned word range;
- confirm the five archive entry counts are 3, 4, 3, 3, and 18;
- compare every ZIP entry byte-for-byte with its listed source file;
- confirm Stage E contains none of its excluded material; and
- confirm a second packaging attempt is rejected without changing archive
  hashes or leaving a partial file.
