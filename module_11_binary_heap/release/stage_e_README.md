# Module 11 — Stage E: Lab and Evidence

Start with `student/lab.md`, then edit only:

- the three numbered `TODO` sections in
  `code/starter/alert_priority_queue.c`; and
- the three `TODO` test sections in `code/tests/test_student.c`.

`TODO` marks an unfinished section that the student must complete.

The Module 10 public record, Queue fields, statuses, service operations,
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
