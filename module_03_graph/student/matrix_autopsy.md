# Ghost-Connection Autopsy — An Inactive Cell Was Not Clean

An **autopsy** traces a bad state back to the first broken rule. This supplied
program is a safe observation fixture: every access stays inside a physical
16-by-16 array. The problem is logical, not a C out-of-bounds access.

## Incident

The graph begins with four active vertices and one directed edge. A faulty
count-only change reduces the active count to three without clearing the row
and column that became inactive. A later count-only change returns to four, so
the stale edge appears again even though no one added it at that time.

The source is `code/autopsy/faulty_ghost_connection.c`.

## Before running

Read the short source, but do not run it yet. Predict:

1. which stored cell is the first invalid value;
2. why that cell is physically in bounds but logically inactive;
3. which edge will appear when the vertex count increases; and
4. which textbook invariant was broken first.

Preserve your prediction:

____________________________________________________________________

## Observe

From the `code` directory, run:

```sh
make autopsy
```

On PowerShell, use the matching autopsy target documented by the instructor.
Record only what the program prints; do not repair the supplied fixture yet.

____________________________________________________________________

## Incident report

### 1. First bad completed state

Identify the earliest assignment after which an inactive row or column no
longer contains only `0`.

____________________________________________________________________

### 2. Broken invariant

State the inactive-row-and-column rule in your own words. Explain why capacity
16 does not make every index active.

____________________________________________________________________

### 3. Delayed symptom

Explain why increasing `vertex_count` reveals the connection later. Separate
the cause from the later observation.

____________________________________________________________________

### 4. Repair

Describe where the invalid write must be rejected or cleared. A repair must
leave the graph unchanged after a rejected operation and must keep every
inactive row and column zero.

____________________________________________________________________

### 5. Regression test

Write one test claim that would fail for the faulty program and pass after the
repair. Include the state that must remain unchanged.

____________________________________________________________________

## Conclusion

The first broken rule was ___________________________________________.

The delayed observation was ________________________________________.

The evidence connecting them was ___________________________________.
