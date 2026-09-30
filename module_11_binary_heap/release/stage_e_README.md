# Module 11 — Stage E: Lab and Evidence

Start with `student/lab.md`, then edit only:

- the three numbered `TODO` sections in
  `code/starter/alert_priority_queue.c`; and
- the three `TODO` test sections in `code/tests/test_student.c`.

`TODO` marks an unfinished section that the student must complete.

The Module 11 baseline public record, Queue fields, statuses, service operations,
error precedence, and failure promises are preserved. The only public API
addition is `alert_priority_queue_is_min_heap`.

Students complete:

1. the Heap-order checker;
2. insertion with geometric growth and sift-up; and
3. minimum extraction with root replacement and sift-down.

For every Queue with a valid visible shape, the checker examines all
non-root live records. It adds zero comparator calls when empty and otherwise
exactly `size - 1` to the shared saturating `comparison_count`, even if it
detects broken Heap order. Record checker/debug deltas separately from
normal-operation deltas.

The autopsy—a careful investigation after a failure—is standalone and stays
within checked fixed-array bounds.

Submit the files and evidence listed in the lab, then complete
`student/evidence_template.md`.

## Supplied scan comparison

The opening block introduced the Priority Queue ADT and stable tie rule.
Use the completed scan baseline to compare service order and work with the
Heap. The Stage E archive includes `code/baseline/` and its public tests.
Run `make baseline-core` from `code/`, or in the released package use
`powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 -Target baseline`.
The repository's canonical baseline is in `priority_queue_baseline/code/`;
its own instructor build can run `solution-core`.

Build the two backends separately with their corresponding headers. Record
zero baseline insertion comparisons and 21 baseline drain comparisons for
the canonical seven-record input, then compare Heap normal-operation
counts without checker calls. Submit one combined Module 11 result.
