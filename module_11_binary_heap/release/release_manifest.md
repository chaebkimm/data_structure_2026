# Module 11 Staged Release Manifest

Run `prepare_student_release.ps1` from this directory to create five ZIP
archives in `../dist`. The script refuses to overwrite an existing archive.

## Stage A — Compact Urgent-Work Inquiry

Release before Meeting A:

- standard initial prompt;
- linear accessible initial prompt.

This stage retrieves compact-placement, urgent-next, and local-repair
reasoning but contains no formal structure or abbreviated name, tree or
storage vocabulary, parent/child language, index formulas, operation names,
ordering-rule name, invariant name, complexity formula, code, exact method,
solution, or instructor material.

## Stage B — Representation and Cognitive Pause

Release after initial models are preserved:

- representation reveal;
- exactly-three-target Cognitive Pause;
- vocabulary reference.

The vocabulary file remains closed until the pause response is preserved.
Approved extended-time or asynchronous versions use the same three targets.

## Stage C — Binary Heap Investigation

Release after the pause and instructor comparison:

- standard investigation worksheet;
- linear accessible investigation worksheet.

Sections A through F are the Stage C core. Sections G through I are later
testing, autopsy, and synthesis work. The files supply questions, not the
answer key.

## Stage D — Beginner Textbook and Models

Release after the student completes and preserves the Stage C core:

- ultra-concise, example-first textbook;
- diagrams with exact indexed, tree, and linear text equivalents.

## Stage E — Lab and Evidence

Release after retrieval and Stage D calibration in Meeting B:

- lab, rubric, evidence template, and Binary Heap Autopsy;
- the Module 10 stable minimum Priority Queue interface plus the one public
  `alert_priority_queue_is_min_heap` extension;
- Heap-backed starter implementation with the 64-record course limit;
- visible core tests and student-test template;
- student-only PowerShell and GNU Make build files;
- separately reported checker/debug and normal-operation comparison deltas;
  and
- bounded, solution-independent sift-down autopsy.

Stage E excludes:

- `instructor/`;
- `code/solution/`;
- `code/tests/test_extension.c`;
- instructor build files, solution targets, and extension targets;
- answer keys and completed TODOs;
- Stages A through D;
- the Module 10 unsorted-array solution;
- bottom-up heapify, decrease-key, arbitrary deletion, Dijkstra, and Prim
  implementations; and
- real alert records, live input, generated binaries, build directories,
  partial archives, and unsafe or unbounded faulty code.

## Instructor verification

Before release, build the reference core tests, instructor extensions, and
isolated autopsy with the commands in `../code/README.md`. Use
warning-enabled and sanitizer-enabled builds where the installed compiler
supports them.

Verify all of the following:

- the public API matches Module 10 except for
  `alert_priority_queue_is_min_heap`;
- a valid-shape checker call adds zero comparisons when empty and otherwise
  exactly `size - 1`;
- normal-operation measurements exclude separately measured checker calls;
- the five archives contain exactly 3, 4, 3, 3, and 14 entries;
- every ZIP entry exactly matches its listed source file;
- Stage E contains none of its excluded materials; and
- a second packaging attempt is rejected without changing any archive.
