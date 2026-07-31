# Graph DFS Autopsy

Complete this work before editing or running the isolated faulty program.

**Depth-first search (DFS)** follows one route deeply before returning to an
unfinished choice. A **directed edge** works in one direction. A **cycle**
is a route that returns to an earlier vertex.

The program uses this directed three-vertex cycle:

```text
0 → 1
1 → 2
2 → 0
```

Equivalent outgoing-neighbor lists:

```text
0:[1]   1:[2]   2:[0]
```

In words, 0 leads to 1, 1 leads to 2, and 2 leads back to 0.

The intended DFS records each vertex once:

```text
0, 1, 2
```

Open `code/autopsy/faulty_cycle_dfs.c`. Do not run it yet.

A **step budget** is a fixed maximum number of actions allowed in this
demonstration. The faulty program stops when its budget is exhausted, so the
demonstration cannot continue making calls without a bound.

## 1. Prediction

Write the `enter` lines you expect before the budget message. Describe the
repeated pattern rather than guessing only the final line.

____________________________________________________________________

Why does the cycle cause another call at its return edge?

____________________________________________________________________

## 2. First broken decision

Identify the earliest state or check decision that causes a vertex to be
entered again. Explain how the cycle reaches that decision.

____________________________________________________________________

## 3. Smallest fix

State the smallest change that makes the intended one-entry-per-vertex
output occur.

____________________________________________________________________

Why does that change stop new work at the edge back to vertex 0?

____________________________________________________________________

## 4. Regression test

A **regression test** is a test kept to prevent a known defect from
returning.

Give one three-cycle test with its exact expected output and a check that no
vertex appears twice.

____________________________________________________________________

## 5. Run and compare

Now run:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target autopsy
```

Observed `enter` pattern:

____________________________________________________________________

Did it match the prediction? If not, what evidence changed your thinking?

____________________________________________________________________

The isolated file does not call or grade your implementation. Its only
purpose is to make one repeated-entry defect visible and safely bounded.
