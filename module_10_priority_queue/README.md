# Chapter 10 — Priority Queues and Finding a Meeting Time

The required lesson follows the complete, self-contained [student/lab.c](student/lab.c), with the [concept slides](student/ppt_material.md) and [code slides](student/ppt_lab_material.md) as read-only references. Students predict, trace, and test a sorted-array priority queue, then find the earliest time when all users are online. There are no implementation TODOs.

Chapter 10 remains in its existing course-week slot. The source presentations say Week 12; their label does not reschedule the rest of the course. This is one ordinary lab artifact within 180 contact minutes, not Practical 2.

## Materials

| Material | Purpose |
| --- | --- |
| [English textbook](student/textbook.md) · [한국어 교재](student/textbook_korean.md) | Matching seven-section explanations and exact source excerpts |
| [Inquiry](student/inquiry_prompt.md) · [Linear format](student/inquiry_prompt_linear.md) | Preserve an initial meeting-time model before revealing names |
| [Representation](student/representation_reveal.md) · [Pause](student/cognitive_pause.md) | Connect IDs, indices, callbacks, and interval state |
| [Investigation](student/investigation_worksheet.md) · [Linear format](student/investigation_worksheet_linear.md) | Predict and trace the same operations in either response format |
| [Lab](student/lab.md) · [Evidence](student/evidence_template.md) · [Rubric](student/rubric.md) | One driver/evidence submission, worth 100 points |
| [Vocabulary](student/vocabulary.md) · [Defect analysis](student/priority_queue_autopsy.md) · [Models](diagrams/priority_queue_models.md) | Explain rules and bounded counterexamples |
| [Lesson plan](instructor/lesson_plan.md) · [Answers](instructor/answer_key.md) · [Technical notes](instructor/technical_notes.md) | Instructor preparation and calibration |
| [Build guide](code/README.md) · [Release manifest](release/release_manifest.md) | Build and distribute the actual lab |
| [Legacy archive](legacy/README.md) | Superseded material, excluded from the required lesson and release |

## Actual source contract

The queue has `CAPACITY = 10`, starts at `front = 0, rear = -1`, and stores live values at `queue[front..rear]`. `compare(x,y)` reports that x has strictly higher priority. Insertion shifts lower-priority items and preserves insertion order for ties. Removal advances `front` without shifting or reusing consumed slots. Callers must provide a valid comparator, space at `rear + 1`, and a nonempty queue before removal. There are no full/empty checks or rejection statuses.

`timelogs[3][6]` supplies three chronological, nonoverlapping, nonempty, nonnegative `[login,logout)` intervals for each of three users. Equal logout/login endpoints do not overlap. `users` stores current login, logout, and zero-based epoch. Only the removed user's state changes before reinsertion. `survey()` initializes all users and the queue on every call, returning the earliest meeting time or `-1` on exhaustion. Exhaustion increments the epoch beyond its last valid index but retains old endpoint fields.

The sample returns **12**, with six successful advances, nine insertions and seven removals. A returned result leaves two IDs queued and one removed ID selected. Final indices are `front = 7, rear = 8`.

## Build and release

From the repository root:

```sh
make -C module_10_priority_queue/code lab-compile core student-tests comparison
python3 module_10_priority_queue/release/prepare_student_release.py
```

The release is `dist/module_10_priority_queue.zip`; existing destinations are never overwritten. Compile each test driver alone because it includes the actual lab. No other module is needed. Add one original regression to the student driver; the supplied smoke test is not that evidence.

## Costs

For U users and A successful advances, sorted-queue survey work is `O(U² + AU)`. A linear logout-scan reference costs `O(U + AU)`; the queue is not an asymptotic speedup for this application. At most U IDs are live, but cumulative writes require up to `U * E` slots for E intervals per user. The actual bound is nine writes into ten slots. Heap implementations and Dijkstra are outside the required Chapter 10 lesson.
