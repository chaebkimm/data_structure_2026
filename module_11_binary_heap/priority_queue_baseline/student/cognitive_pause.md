# Stage B — Five-Minute Cognitive Pause

Read the starting definitions with the instructor before timing begins.
Then use no notes, slides, classmates, vocabulary file, or coding tools for
five minutes. You may draw, type, dictate, or answer in numbered sentences.
Preserve your first response when correction begins.

A smaller priority number leaves first. When priorities tie, the smaller
arrival sequence leaves first. `peek-min` reports without removal.
`extract-min` removes and reports. A scan of five live records makes four
comparisons.

For each target, return to this exact starting state:

```text
capacity 8
size 5
next_sequence 5
comparison_count 0

index 0: id54 priority3 sequence0
index 1: id81 priority1 sequence1
index 2: id12 priority2 sequence2
index 3: id27 priority1 sequence3
index 4: id68 priority4 sequence4
indexes 5 through 7: inactive
```

## Target 1 — Select without removing

Apply one `peek-min`.

State:

1. the reported alert;
2. why id27 does not replace that alert;
3. the final comparison count; and
4. which logical fields and records remain unchanged.

Response:

____________________________________________________________________

____________________________________________________________________

## Target 2 — Extract, swap, and insert

Return to the starting state. Apply one `extract-min`, then insert alert
id35 with priority 1.

State:

1. the extracted alert;
2. every active physical record after both operations;
3. final size, capacity, `next_sequence`, and `comparison_count`; and
4. which alert would leave next without applying another operation.

Response:

____________________________________________________________________

____________________________________________________________________

## Target 3 — Separate ties from policy

Return to the starting state.

Explain:

1. why arrival-sequence tie behavior does not stop id68 from waiting
   indefinitely while priority-1 alerts keep arriving;
2. why a caller must not silently edit id54's stored priority; and
3. one explicit policy a real client could use to address either concern.

Response:

____________________________________________________________________

____________________________________________________________________

## Compare after time is called

Preserve the original response. Label corrections `comparison`,
`swap-with-last`, `sequence`, or `policy`.

The evidence that changed or strengthened my thinking was:

____________________________________________________________________
