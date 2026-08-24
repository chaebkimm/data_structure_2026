# Module 1 Staged Release Manifest

Run `prepare_student_release.ps1` from this directory to create five ZIP
archives in `../dist`. The script refuses to overwrite an existing archive.

## Stage A — Initial Inquiry

Release before Meeting A:

- standard initial prompt;
- linear accessible initial prompt;
- optional vocabulary support.

This stage contains no notes, expert diagram, answer key, code, or solution.

## Stage B — Memory Model and Cognitive Pause

Release after students have constructed their initial model:

- instructor-authorized memory-space reveal;
- four-target Cognitive Pause.

Withhold expert calibration until each student has completed the initial
response, including approved extended-time or asynchronous equivalents.

## Stage C — Investigation

Release after the timed Cognitive Pause and expert growth calibration:

- standard investigation worksheet;
- linear accessible investigation worksheet.

This stage supplies prompts, not expert answers.

## Stage D — Calibrated Notes

Release after the Meeting A investigation and exit ticket:

- frozen Chapter 1 textbook;
- student summary and lab bridge;
- memory-model diagrams and text equivalents.

## Stage E — Lab and Evidence

Release for Meeting B:

- lab, rubric, evidence template, and Segfault Autopsy prompt;
- public header and starter implementation;
- supplied core/extension tests and student-test template;
- student-only PowerShell and GNU Make build files;
- solution-independent faulty autopsy executable.

Stage E excludes:

- `instructor/`;
- `code/solution/`;
- the deterministic instructor allocation-failure test;
- earlier inquiry answers and the instructor answer key.

## Instructor-only verification

Before release, validate the full package with:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File ..\code\build.ps1 `
  -Target solution
powershell -NoProfile -ExecutionPolicy Bypass -File ..\code\build.ps1 `
  -Target solution -Extensions
powershell -NoProfile -ExecutionPolicy Bypass -File ..\code\build.ps1 `
  -Target solution -AllocationFailure
```

Run sanitizer-enabled equivalents when the local toolchain supports them.
