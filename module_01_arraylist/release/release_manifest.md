# Module 1 Staged Release Manifest

Run `prepare_student_release.ps1` from this directory to create five ZIP
archives in `../dist`. The script validates required sources and refuses to
overwrite an existing archive.

## Stage A — Initial Inquiry

Release before Meeting A:

- standard initial prompt; and
- linear accessible initial prompt.

This stage contains no vocabulary reference, completed model, notes, answer
key, code, or solution.

## Stage B — Fixed-Array Model and Cognitive Pause

Release after students preserve their initial model:

- instructor-authorized representation reveal;
- vocabulary reference for the revealed model; and
- three-target Cognitive Pause on active indexes, order, and full capacity.

Withhold expert calibration until every student completes the initial
response, including approved extended-time or asynchronous equivalents.

## Stage C — Investigation

Release after the timed pause and expert calibration:

- standard investigation worksheet;
- linear accessible investigation worksheet.

The prompts cover size versus capacity, checked reads/updates, first-match
search, append, right-shift insertion, left-shift removal, and unchanged
state after rejection. They do not provide the answer key.

## Stage D — Calibrated Notes

Release after the Meeting A investigation and exit ticket:

- revised fixed-array Chapter 1 textbook;
- student summary and lab bridge; and
- fixed-array diagrams with text equivalents.

These diagrams do not include a worked Stage E autopsy. Keep its faulty-code
prediction and repair answers out of Stage D materials.

## Stage E — Lab and Evidence

Release for Meeting B:

- lab, 100-point rubric, evidence template, and Bounds and Invariant Autopsy;
- public header and plain-array starter implementation;
- supplied core tests, extra edge/sequence tests, and student-test template;
- student-only PowerShell and GNU Make build files; and
- standalone guarded autopsy.

All six operations are core: checked indexed read, update, first-match find,
append, insert, and remove. Extensions add tests only.

Stage E excludes `instructor/`, `code/solution/`, and every answer key.

## Instructor verification

Before release, validate the reference implementation and guarded autopsy:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File ..\code\build.ps1 `
  -Target solution
powershell -NoProfile -ExecutionPolicy Bypass -File ..\code\build.ps1 `
  -Target solution -Extensions
powershell -NoProfile -ExecutionPolicy Bypass -File ..\code\build.ps1 `
  -Target autopsy
```

Run sanitizer-enabled equivalents when supported. The guarded autopsy
demonstrates a logical bounds violation without a real out-of-bounds access.
