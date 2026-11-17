# Chapter 10 Lesson Plan — Priority Selection and a Meeting Time

One 180-minute block produces one ordinary lab artifact. The source functions are complete. Keep lab.c and presentations unchanged. The presentations say Week 12; the package remains Chapter 10 in the existing delivery-guide slot. Both textbook languages follow the same seven sections.

## Before class

Run `make -C module_10_priority_queue/code lab-compile core student-tests comparison` from the repository root. Use the [technical notes](technical_notes.md) and [answer key](answer_key.md). Prepare three user cards, their nine half-open intervals, a queue row with explicit indices, and a separate out_id card. Do not use a heap or the archived graph lesson as the required source.

## Teaching sequence

| Minutes | Activity |
| --- | --- |
| 0–15 | Recall FIFO; preserve the inquiry's initial selection and meeting model. |
| 15–35 | Derive priority selection and sorted insertion using queue values and indices. |
| 35–60 | Trace insertion/removal, stable ties, live suffix and cumulative capacity. |
| 60–80 | Reveal timelogs/users, IDs versus positions, callbacks and function addresses. |
| 80–90 | Complete the three-target pause; preserve responses and label corrections. |
| 90–100 | Break and build setup. |
| 100–125 | Trace the three-user survey, strict overlap, six advances and exhaustion. |
| 125–150 | Run supplied checks and write one original regression against the actual source. |
| 150–165 | Compare linear selection, combination oracle, generalized costs and storage. |
| 165–180 | Assemble evidence, correct reasoning and complete the exit explanation. |

## Neutral prompts

- Which value is an ID, which is a position, and which is a time?
- Which existing items does strict comparison shift, including a tie?
- What does pos > front protect after a removal?
- Does removing an item create space at rear + 1?
- Why can a changed logout be reinserted without repairing every queued item?
- Which interval cannot contain a meeting when candidate equals its logout?
- Why does login 11 leave candidate 12 unchanged?
- Which field changes when next_epoch returns -1?
- Why does a successful run still have live queued users?
- What work does the sorted queue save on removal and add on insertion?

## Assessment and support

Use the same [100-point rubric](../student/rubric.md) for standard and linear response formats. Accept equivalent spoken, dictated, tactile or typed evidence. Require the canonical trace, an actual survey call, one original regression, boundary/reset evidence and an honest same-input comparison. Supplied counts are observations, not source counters.

The exit explanation connects greatest login, earliest logout, strict overlap and safe interval advancement. Correct answers state that the queue takes O(U² + AU), the scan takes O(U + AU), and unreused queue slots must cover total insertions. Keep all work inside one artifact. Archived examples do not add homework or another implementation.
