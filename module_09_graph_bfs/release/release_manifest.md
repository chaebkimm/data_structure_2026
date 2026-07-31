# Module 9 Staged Release Manifest

Run `prepare_student_release.ps1` from this directory to create five ZIP
archives in `../dist`. The script refuses to overwrite an existing archive.

## Stage A — Fewest-Link Inquiry

Release before Meeting A:

- standard initial prompt;
- linear accessible initial prompt.

This stage retrieves graph-link and waiting-work reasoning but contains no
formal BFS state, Queue vocabulary, discovery/distance/predecessor names,
adjacency-list representation, complexity formulas, code, exact method,
solution, or instructor material.

## Stage B — Representation and Cognitive Pause

Release after initial models are preserved:

- representation reveal;
- exactly-three-target Cognitive Pause;
- vocabulary reference.

The vocabulary file remains closed until the pause response is preserved.
Approved extended-time or asynchronous versions use the same three targets.

## Stage C — Graph BFS Investigation

Release after the pause and instructor comparison:

- standard investigation worksheet;
- linear accessible investigation worksheet.

Sections A through F are the Stage C core. Sections G through I are later
testing, autopsy, and synthesis work. The files supply questions, not the
answer key.

## Stage D — Beginner Textbook and Models

Release after the student completes and preserves the Stage C core:

- ultra-concise, example-first textbook;
- diagrams with exact numbered and linear text equivalents.

## Stage E — Lab and Evidence

Release after retrieval and Stage D calibration in Meeting B:

- lab, rubric, evidence template, and Graph BFS Autopsy;
- public matrix, dynamic-neighbor-array, BFS, and typed Queue headers;
- supplied representation, validation, ownership, and Queue support;
- starter BFS/path implementation;
- visible core tests and student-test template;
- student-only PowerShell and GNU Make build files;
- bounded, solution-independent discovery-timing autopsy.

Stage E excludes:

- `instructor/`;
- `code/solution/`;
- `code/tests/test_extension.c`;
- answer keys and completed TODOs;
- Stages A through D;
- optional forest code, real network input, generated binaries, and
  unbounded faulty code.

## Instructor verification

Before release, build the reference core tests, instructor extensions, and
isolated autopsy with the commands in `../code/README.md`. Use
warning-enabled and sanitizer-enabled builds where the installed compiler
supports them. Verify that every ZIP entry exactly matches its listed source
file and that a second packaging attempt is rejected.
