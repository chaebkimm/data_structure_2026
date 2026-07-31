# Priority Queue Autopsy — Latest Tie Wins

## Purpose

Investigate a bounded comparison defect without causing invalid memory
access. Preserve each prediction before running the supplied faulty
program. The program uses only four initialized records and checked loop
bounds.

## Frozen fixture

Physical insertion order is:

```text
index 0: id80 priority2 sequence0
index 1: id91 priority1 sequence1
index 2: id17 priority1 sequence2
index 3: id44 priority3 sequence3
```

The correct rule is:

```text
smaller priority first
when priorities tie, smaller arrival sequence first
```

The faulty scan instead replaces its candidate whenever:

```text
later.priority <= candidate.priority
```

The symbol `<=` means “smaller than or equal to.” The faulty rule ignores
arrival sequence.

## 1. Predict before running

Correctly selected alert ID: ________________________________________

Faulty selected alert ID: __________________________________________

At which index does the correct and faulty decision first differ?

____________________________________________________________________

Why is this a service-rule defect even though all memory accesses remain
inside the array?

____________________________________________________________________

## 2. Record the expected scan

For each later index, state whether the correct comparator replaces the
current candidate.

| Compared index | Candidate before | Replace? | Candidate after | Reason |
|---:|---:|:---:|---:|---|
| 1 | 0 | | | |
| 2 | | | | |
| 3 | | | | |

Exact linear equivalent: compare index 1 with candidate 0, then index 2
with the current candidate, then index 3. Record candidate and reason after
each comparison.

## 3. Run the bounded program

Use the provided build target:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target autopsy
```

Saved output location: ______________________________________________

Observed selected alert: ____________________________________________

Did the observation match the prediction? ___________________________

## 4. Identify the first invalid assumption

Complete:

> The faulty program assumes that _________________________________,
> but the public tie contract requires _____________________________.

Why would choosing the smallest alert ID also be an incorrect repair?

____________________________________________________________________

## 5. State the exact repair

Write the two-part comparator in words or C-like pseudocode. Do not merely
change `<=` to `<`; the repair must make the sequence tie rule explicit.

____________________________________________________________________

____________________________________________________________________

## 6. Design a regression test

A **regression test** is retained so a repaired defect does not return.
Use at least three equal-priority alerts whose IDs are not in arrival order.

Input:

____________________________________________________________________

Expected extraction records:

____________________________________________________________________

Why this test fails under the faulty rule:

____________________________________________________________________

## 7. Separate correctness from safety

State why the bounded guard makes this autopsy memory-safe.

____________________________________________________________________

State why memory safety alone does not make its service order correct.

____________________________________________________________________

Finally, explain why correct course ordering still does not prove that a
real alert's priority is accurate or fair.

____________________________________________________________________
