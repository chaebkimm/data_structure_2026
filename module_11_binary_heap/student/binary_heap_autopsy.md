# Binary Heap Autopsy - Wrong Child Chosen

## Purpose

Investigate a bounded sift-down defect without any invalid memory access.
Preserve each prediction before running the supplied faulty program.

## Frozen valid Heap

```text
index 0: 5/5/0
index 1: 41/41/1
index 2: 17/17/2
index 3: 55/55/3
index 4: 70/70/4
```

The notation is `ID/P/S`. Smaller priority comes first; a tied priority uses
smaller sequence. Extracting 5 makes final record 70 the sift-down
candidate. The new live size is 4.

The correct repair compares both root children, chooses the better child,
and then compares that child with candidate 70.

The faulty repair always chooses the left child when both exist. Its arrays
and loop limits remain checked.

## 1. Predict before running

Correct first chosen child ID: ______________________________________

Why that child comes before the other child:

____________________________________________________________________

Correct final active ID array:

____________________________________________________________________

Faulty final active ID array:

____________________________________________________________________

## 2. Locate the first divergence

Complete:

> At root position 0, the correct repair ____________________________,
> but the faulty repair ____________________________________________.

Why is choosing the left child automatically not a Heap rule?

____________________________________________________________________

## 3. Record both bounded routes

Correct candidate route and comparisons:

____________________________________________________________________

Faulty candidate route and comparisons:

____________________________________________________________________

Which direct relationship fails in the faulty final state?

____________________________________________________________________

## 4. Run the supplied program

From the code directory:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target autopsy
```

Saved output location: ______________________________________________

Observed extracted priority: _______________________________________

Observed faulty priorities: ________________________________________

Observed checker answer: ___________________________________________

Did observation match prediction? __________________________________

## 5. State the exact repair

Write the required decision order:

1. what to do when there is no left child;
2. what to do when only the left child exists;
3. how to choose when both children exist; and
4. when to move the selected child upward.

____________________________________________________________________

____________________________________________________________________

## 6. Design a regression test

A **regression test** remains after repair so the defect does not return.
Use the frozen five-record state or another valid Heap whose right child
comes before its left child, then extract once.

Input:

____________________________________________________________________

Expected output and final active array:

____________________________________________________________________

Why the faulty version fails:

____________________________________________________________________

## 7. Separate safety, integrity, and meaning

Why is every access in the bounded program memory-safe?

____________________________________________________________________

Why is the faulty result still an integrity failure?

____________________________________________________________________

Why does the repaired course ordering still not prove that a real alert's
priority is accurate?

____________________________________________________________________
