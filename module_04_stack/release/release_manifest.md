# Module 4 Staged Release Manifest

Run `prepare_student_release.ps1` from this directory to create five ZIP
archives in `../dist`. The script checks that every source exists, rejects a
duplicate source or destination path within a stage, and refuses to overwrite
an existing archive.

## Stage A — Initial Function-Return Inquiry

Release before Meeting A:

- standard initial prompt;
- linear accessible initial prompt.

This stage contains no formal Stack/LIFO vocabulary, representation answer,
code, solution, or instructor material.

## Stage B — Representation and Cognitive Pause

Release after initial return-order models are preserved:

- fixed integer-array representation reveal;
- exactly-three-target Cognitive Pause; and
- vocabulary reference, opened only after the pause response is preserved.

The pause targets the 100, 200, 300 trace, rejection preservation, and the
`1+2*3` transfer. Approved timing or response accommodations retain those same
targets.

## Stage C — Fixed Stack Investigation

Release after the pause and instructor calibration:

- standard investigation worksheet;
- linear accessible investigation worksheet.

This stage asks about LIFO operations, `0 <= size <= capacity`, the logical
top, rejection preservation, expression precedence, fixed storage, and the
inactive-slot defect without supplying instructor answers.

## Stage D — Textbook and Models

Release after the student completes and preserves Sections A through F of the
Stage C investigation:

- beginner textbook chapter;
- diagrams with exact text equivalents.

Stage D contains no autopsy answer, reference implementation, extension test,
or instructor material.

## Stage E — Lab and Evidence

Release for Meeting B:

- lab, rubric, evidence template, and Stack-Top Autopsy prompt;
- `int_stack.h` and `expression_evaluator.h`;
- starter `int_stack.c` and `expression_evaluator.c`;
- eight supplied core tests and three student-test placeholders;
- student-only PowerShell and GNU Make build files; and
- the solution-independent `faulty_top.c` autopsy program and its README.

Stage E excludes:

- `instructor/` and all answer keys;
- `code/solution/`;
- `code/tests/test_extension.c`;
- earlier inquiry, pause, investigation, and textbook materials; and
- any completed student test or generated build artifact.

## Instructor verification

Before release:

1. build and run the reference core and extension suites using
   `../code/README.md`;
2. build and run the isolated Stack-Top Autopsy;
3. confirm the starter is warning-clean and intentionally incomplete;
4. inspect all five source/entry lists for unique, existing paths;
5. verify Stage A has no formal vocabulary and Stage D has no autopsy answer;
6. inspect Stage E archive contents for solution, instructor, and extension
   leaks; and
7. remove generated `build/`, partial archives, and test ZIPs after
   verification.
