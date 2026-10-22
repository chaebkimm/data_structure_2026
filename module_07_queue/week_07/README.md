# Week 7 — Linked Lists and Queue

This is the required Week 7 path in the
[13-week course](../../Data_Structures_Course_2026_13_Week_Delivery_Guide.md).
Read the [lesson](textbook.md), complete the [single lab](lab.md), and use
`code/` for the linked-Queue assignment. Faculty use the
[instructor plan](instructor.md). The original Module 7 circular-Queue lab
is a resource for comparison, not an additional assignment.

Required outcomes: explain FIFO; trace singly linked nodes and ownership;
implement enqueue-at-tail and dequeue-at-head; explain supplied traversal and
destruction; test empty/singleton/reuse/allocation failure; and compare a
linked Queue with a supplied circular-array Queue. General list insertion,
arbitrary deletion, doubly linked lists, and concurrent Queues are optional.

## Files and release

- `textbook.md`, `lab.md`: student lesson and one assignment.
- `code/linked_queue.h`, `support.h`, `support.c`, `Makefile`: supplied API,
  allocation/cleanup helpers, peek, validator, and build commands.
- `code/starter/linked_queue.c`: exactly two implementation TODOs.
- `code/tests/`: supplied core tests and student-test template.
- `code/solution/`: instructor-only reference; exclude from student release.

Use `python prepare_release.py` after the inquiry and correction gates.
It creates `dist/week_07_linked_queue.zip` with an explicit file manifest;
it does not relabel an original staged archive. The release excludes this
instructor plan and the solution. For the circular comparison, separately
supply the original [Module 7 reference](../code/solution/event_queue.c)
and [API](../code/include/event_queue.h) after students predict the wrap trace.
