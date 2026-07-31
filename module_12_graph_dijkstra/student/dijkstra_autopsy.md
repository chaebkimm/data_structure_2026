# Dijkstra Autopsy - Wrapped Candidate Cost

## Purpose

Investigate one bounded arithmetic defect. Every array position remains
valid; the failure is a false path cost. Preserve predictions before running
the supplied `faulty_overflow.c`.

## Frozen state

`size_t` is C's nonnegative whole-number type. `SIZE_MAX` is its largest
value and is reserved as `INF`. A **candidate** is a proposed new path cost.

```text
dist[u] = SIZE_MAX - 3
weight(u,v) = 5
old dist[v] = 20
```

The faulty version adds before checking the range. Unsigned arithmetic wraps
past `SIZE_MAX`, producing candidate 1.

The correct version must return `DIJKSTRA_COST_RANGE`, preserve the old
distance and predecessor, and publish no snapshot.

## 1. Predict before running

Mathematical sum:

____________________________________________________________________

Faulty stored candidate:

____________________________________________________________________

**Strict relaxation** accepts only a smaller candidate. Does the faulty
strict relaxation accept that candidate? Why?

____________________________________________________________________

Faulty new distance, predecessor, and **frontier** (pending-work) change:

____________________________________________________________________

## 2. Locate the first divergence

Complete:

> The faulty version forms _________________________________________
> before checking _________________________________________________.

Why is a small wrapped result not evidence of a cheap path?

____________________________________________________________________

## 3. Apply the correct guard

Complete:

```text
INF - dist[u] =
weight <= INF - dist[u] =
```

Why must the program return `DIJKSTRA_COST_RANGE`?

____________________________________________________________________

Why would silently leaving `dist[v]` at `INF` overstate "unreachable"?

____________________________________________________________________

## 4. Run the supplied program

From the code directory, run the documented autopsy build target.

Saved output location: ______________________________________________

Observed faulty candidate: _________________________________________

Observed faulty relaxation decision: _______________________________

Observed correct status: ___________________________________________

Did observation match prediction? __________________________________

## 5. State the exact repair

Put these decisions in order:

1. handling `dist[u] == INF`;
2. checking subtraction before addition;
3. rejecting a candidate equal to reserved `INF`;
4. forming the candidate;
5. applying strict relaxation; and
6. publishing output only after complete success.

**Output** is where the operation writes its answer.

____________________________________________________________________

____________________________________________________________________

## 6. Design a regression test

A **regression test** remains after repair so the defect does not return.

Input and preserved output marker:

____________________________________________________________________

Expected status and unchanged fields:

____________________________________________________________________

Why the faulty version fails:

____________________________________________________________________

## 7. Keep stale checking separate

In the canonical run, current `dist[B]` is 4 when snapshot `B/9` is removed.
Why must it be skipped even after candidate arithmetic is repaired?

____________________________________________________________________

Which stated complexity argument depends on skipping stale snapshots before
scanning outgoing edges?

____________________________________________________________________

## 8. Separate memory safety, integrity, and meaning

An **array bound** is the limit on valid array positions. **Integrity** means
stored state still obeys its required rules.

Why can the faulty program remain within every array bound?

____________________________________________________________________

Why is the wrapped result still an integrity failure?

____________________________________________________________________

Why does correct arithmetic still not prove that a real inspection time is
authentic, static, or additive?

____________________________________________________________________
