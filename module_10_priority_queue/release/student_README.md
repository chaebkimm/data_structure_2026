# Chapter 10 Student Release — Priority Queues and Meeting Time

Start with student/inquiry_prompt.md or its linear response format. Preserve predictions, then open the representation reveal, pause, investigation and textbooks. English is student/textbook.md; Korean is student/textbook_korean.md. The required source is student/lab.c. It and the presentations are supplied unchanged. Presentation labels say Week 12; package numbering remains Chapter 10.

Submit one driver/evidence artifact, using student/lab.md, evidence_template.md and rubric.md. The implementation is complete; add one original regression to code/tests/test_lab_student.c. No heap or graph implementation is required.

From this extracted directory:

```sh
make -C code lab-compile core student-tests comparison
```

PowerShell users can run ./code/build.ps1 with -Target lab-compile, core, student-tests or comparison. See code/README.md for sanitizer commands. Compile drivers alone because they include the self-contained source; no original repository checkout or external module is needed.

MANIFEST.txt lists each included file's SHA-256. The sample result is 12. Login is included and logout excluded; equality fails. Queue slots must cover total insertions since initialization. Current lesson files are the only required materials; no instructor keys, archive, binaries or alternative implementation is included.
