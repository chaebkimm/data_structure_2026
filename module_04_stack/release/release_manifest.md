# Module 4 Staged Release Manifest

Run `prepare_student_release.ps1` from this directory to create five ZIP
archives in `../dist`. The script checks that every source exists, rejects a
duplicate source or destination path within a stage, and refuses to overwrite
an existing archive. It validates all stages before creating an archive and
cleans up partial output if archive creation fails.

## Stage A — Initial Function-Return Inquiry

Release before Meeting A:

- standard initial prompt;
- linear accessible initial prompt.

This stage contains no formal Stack/LIFO vocabulary, representation answer,
code, solution, or instructor material.

## Stage B — Representation and Cognitive Pause

Release after initial return-order models are preserved:

- fixed character-array representation reveal;
- exactly-three-target Cognitive Pause; and
- vocabulary reference, opened only after the pause response is preserved.

The reveal connects the abstract function-return trace to characters
`'A'`, `'B'`, and `'C'` in `lab.c`'s concrete `char stack[10]`. Its active range
is `stack[0]` through `stack[size - 1]` when nonempty, with `0 <= size <= capacity`. The pause preserves
return-order reasoning, boundary decisions, and expression-precedence
transfer. Approved timing or response accommodations retain those same
targets.

## Stage C — Fixed Stack Investigation

Release after the pause and instructor calibration:

- standard investigation worksheet;
- linear accessible investigation worksheet.

This stage asks about LIFO operations, forward-moving `size`, fixed storage,
boundary behavior, operator precedence, postfix evaluation, and inactive
slots without supplying instructor answers. The postfix token count `postfix_size`
and the evaluator's local next-free position `size` are separate from the
character Stack's global `size`. Both Stacks use the same count convention.

## Stage D — Textbook and Models

Release after the student completes and preserves Sections A through F of the
Stage C investigation:

- English beginner textbook chapter, `textbook.md`;
- Korean edition of the same chapter, `textbook_korean.md`; and
- diagrams with exact text equivalents.

Choose either language edition; reading both is optional. Both editions
follow the worked expression `1-2*3+4` → `123*-4+` → `-1`. Stage D contains
no autopsy answer or private instructor material.

## Stage E — Lab and Evidence

Release for Meeting B:

- current `student/lab.c`;
- lab, rubric, evidence template, and Stack-Top Autopsy prompt;
- `code/lab_demo.c`, which supplies the demonstration's `main`;
- `code/tests/test_lab.c`, with six baseline groups and space for three
  justified student tests;
- student-only PowerShell and GNU Make build files plus the code README; and
- isolated `code/autopsy/faulty_top.c` and its README.

The lab source has no `main`. From the extracted `code` directory, the
default build runs the demonstration; `make lab-tests` or
`./build.ps1 -Target lab-tests` runs the supplied checks. The autopsy remains
a separate target. Tests cover supported inputs and do not imply that the
source validates malformed expressions, buffer limits, or zero divisors.

Stage E excludes:

- `instructor/` and all answer keys;
- the older integer-stack headers, starter, and solution;
- the older `test_core.c`, `test_student.c`, and `test_extension.c`;
- earlier inquiry, pause, investigation, and textbook materials; and
- generated build artifacts.

## Instructor verification

Before release:

1. Run the lab demonstration and supplied lab tests using `../code/README.md`.
2. Build and run the isolated Stack-Top Autopsy after recording its prediction.
3. Review compiler output. The current `lab.c` uses old-style empty parameter
   lists and may produce prototype warnings. With `-Wshadow`, local `value_size`
   also warns because it hides global `size`; do not describe the source as
   warning-clean.
4. Inspect all five source/entry lists for unique, existing paths.
5. Verify Stage A has no formal vocabulary and Stage D has no autopsy answer.
6. Inspect Stage E contents for instructor files and older exercise files,
   then build and run its demonstration, tests, and autopsy after extraction.
7. Remove generated `build/`, partial archives, and test ZIPs after
   verification.
