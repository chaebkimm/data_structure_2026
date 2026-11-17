# Chapter 10 Lab — Trace and Test Priority Selection

Use the complete [lab.c](lab.c) without modification. Submit one driver/evidence artifact in the 180-minute block. There are no required heap, graph, allocation, parser, or implementation TODOs. Start with the [inquiry](inquiry_prompt.md), then use the [investigation](investigation_worksheet.md) or its linear format.

## Build the supplied source

From the repository root:

```sh
make -C module_10_priority_queue/code lab-compile core student-tests comparison
```

From the module directory or extracted student release:

```sh
make -C code lab-compile core student-tests comparison
```

The drivers include lab.c once. Compile each driver alone, with the student directory on the include path. Do not link lab.c again. The self-contained source has no main and no external module dependency. PowerShell commands and sanitizer flags are in [the code guide](../code/README.md).

## 1. Predict queue behavior

Trace init_queue, enqueue and dequeue with integers 7, 2, 5. Remove once, insert 1, and finish removing. Record the live range after each operation. Explain the pos > front guard, strict comparison, stable ties, and why consumed positions are never reused. Treat capacity and nonempty removal as caller preconditions, not rejection tests.

## 2. Trace the supplied survey

Record the three original log rows and every user's current epoch/login/logout. Initialize the candidate to 5 and remove ID 2 first. Trace six advances until the candidate is 12 and the next logout is 13. Count nine insertions and seven removals, leaving front 7, rear 8, live IDs [2,1], and selected ID 0 outside the queue. Confirm with an independent survey() call. See the [models](../diagrams/priority_queue_models.md).

Explain why candidate >= earliest logout requires advancing, including equality. Explain why the candidate never decreases and why a removed ID must be reinserted after its logout changes. At success, show the three intervals that contain 12.

## 3. Add one original regression

Extend code/tests/test_lab_student.c with a focused prediction and assertions. Choose a defect such as accepting endpoint equality, lowering the candidate after a late update, breaking stable ties, shifting consumed positions, or failing to reset survey state. Explain which incorrect behavior your test distinguishes. The supplied smoke test alone is not original evidence.

Keep every row at exactly three chronological nonoverlapping intervals with nonnegative endpoints and login < logout. Adjacent intervals may touch. Save the original timelogs, load your fixture, run the assertions, then restore the sample. Never enqueue after cumulative capacity is exhausted or dequeue an empty queue.

## 4. Check failure and repeatability

Use an initial-overlap fixture and a no-overlap fixture. On exhaustion, next_epoch increments epoch beyond the last valid interval and returns -1 without updating endpoints. Do not index the log using that exhausted epoch. A new survey call resets all users and queue indices. The input log is not cleared or changed by survey.

## 5. Compare and explain costs

The comparison driver runs the actual lab and a fresh linear logout scan on the same schedules. Both are checked against an independent enumeration of all interval combinations. Do not replace actual-source tests with a manually copied survey loop.

For U users, E intervals each, and A advances, give O(k) worst-case insertion into k live items, O(1) removal, O(U² + AU) survey work, and U + A <= U * E cumulative insertions. Contrast the scan's O(U + AU) work without claiming the sorted queue is faster. The source's literal bounds are U=3, E=3 and CAPACITY=10.

## Submission

Use the [evidence template](evidence_template.md). Include preserved predictions and corrections, the canonical state trace, actual commands/output, one original regression and its defect explanation, boundary/reset evidence, the comparison, and input/storage/cost limits. The [rubric](rubric.md) totals 100 points. The [bounded defect analysis](priority_queue_autopsy.md) supplies reasoning prompts within this same artifact.
