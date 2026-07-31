# Module 7 Staged Release Manifest

Run `prepare_student_release.ps1` from this directory to create five ZIP
archives in `../dist`. The script refuses to overwrite an existing archive.

## Stage A — Arrival-Order Inquiry

Release before Meeting A:

- standard initial prompt;
- linear accessible initial prompt.

This stage retrieves waiting-order and numbered-slot reasoning but contains
no Queue/FIFO names, operation names, circular-buffer fields, remainder
formula, code, exact method, solution, or instructor material.

## Stage B — Representation and Cognitive Pause

Release after initial models are preserved:

- representation reveal;
- exactly-three-target Cognitive Pause;
- vocabulary reference.

The vocabulary file remains closed until the pause response is preserved.
Approved extended-time or asynchronous versions use the same three targets.

## Stage C — Circular Queue Investigation

Release after the pause and instructor comparison:

- standard investigation worksheet;
- linear accessible investigation worksheet.

Sections A through F are the Stage C core. Sections G through I are later
testing, autopsy, and synthesis work. The files supply questions, not the
answer key.

## Stage D — Beginner Textbook and Models

Release after the student completes and preserves the Stage C core:

- ultra-concise, example-first textbook;
- diagrams with exact indexed and linear text equivalents.

## Stage E — Lab and Evidence

Release after retrieval and Stage D calibration in Meeting B:

- lab, rubric, evidence template, and Queue Autopsy;
- public header and starter Queue implementation;
- visible core tests and student-test template;
- student-only PowerShell and GNU Make build files;
- bounded, solution-independent faulty-wrap autopsy.

Stage E excludes:

- `instructor/`;
- `code/solution/`;
- `code/tests/test_extension.c`;
- answer keys and completed TODOs;
- Stages A through D;
- real logs, network input, generated binaries, and unbounded faulty code.

## Instructor verification

Before release, build the reference core tests, instructor extensions, and
isolated autopsy with the commands in `../code/README.md`. Use
warning-enabled and sanitizer-enabled builds where the installed compiler
supports them.
