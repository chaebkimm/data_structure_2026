# Module 3 Staged Release Manifest

Run `prepare_student_release.ps1` from this directory to create five ZIP
archives in `../dist`. The script refuses to overwrite an existing archive.

## Stage A — Initial Relationship Inquiry

Release before Meeting A:

- standard initial prompt;
- linear accessible initial prompt.

This stage contains no formal graph names, representation answer, matrix,
code, solution, or instructor material.

## Stage B — Representation and Cognitive Pause

Release after initial relationship models are preserved:

- representation reveal;
- three-target Cognitive Pause;
- vocabulary reference containing the formal rules.

Students open the vocabulary reference only after preserving the timed
response. Withhold the instructor explanation until each student has
completed the initial response, including approved extended-time or
asynchronous equivalents.

## Stage C — Graph Investigation

Release after the timed pause and instructor relationship explanation:

- standard investigation worksheet;
- linear accessible investigation worksheet.

This stage prompts representation, direction, symmetry, vocabulary, and
trade-off reasoning without supplying the answer key.

## Stage D — Beginner Notes and Models

Release after the student has completed and preserved the Stage C core:

- example-first beginner notes;
- diagrams with text equivalents.

## Stage E — Lab and Evidence

Release for Meeting B:

- lab, rubric, evidence template, and Matrix Symmetry Autopsy;
- public header and starter implementation;
- supplied core tests and student-test template;
- student-only PowerShell and GNU Make build files;
- solution-independent faulty-matrix autopsy.

Stage E excludes:

- `instructor/`;
- `code/solution/`;
- `code/tests/test_extension.c`;
- any instructor answer key;
- earlier inquiry materials.

## Instructor verification

Before release, build the reference core tests and isolated autopsy with the
commands documented in `../code/README.md`. Run warning-enabled and
sanitizer-enabled builds where the installed compiler supports them.
