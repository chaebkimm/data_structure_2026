# Module 3 Evidence Record

Complete this record after the Stage E lab. A numbered list may replace any
table if it uses the same headings.

Name: ____________________________  
Compiler or approved CI: ____________________________

## 1. One graph in three forms

Show the Web/App/Database graph as a diagram or line-by-line arrow description,
the directed edge set, and three active matrix rows. Explain why they agree.

____________________________________________________________________

## 2. Stored representation

Complete the meaning of each field or name:

- `vertex_count`:
- `grid[from][to]`:
- `GRAPH_MAX_VERTICES`:

Why are `grid[from][to]` and `grid[to][from]` separate facts?

____________________________________________________________________

## 3. Invariant evidence

State the rules for the vertex count and active indexes, values in grid cells,
inactive rows and columns, and diagonal cells. For one rejected request, state
what remained unchanged.

____________________________________________________________________

## 4. Core operation trace

| Step | Expected evidence | Actual evidence | Pass? |
|---|---|---|---|
| Initialize three vertices | Full grid is zero | | |
| Add `0 → 1`, `1 → 2`, `1 → 0` | Canonical active matrix | | |
| Guarded lookup of one directed edge | Correct `0` or `1` | | |
| Count App out-degree | Correct row count | | |
| Remove `1 → 2` | Only selected cell changes | | |
| Count App out-degree again | Correct new count | | |
| Reject a self-loop or inactive index | State/output preserved | | |

## 5. Exactly three student-authored tests

For each test, record a distinct claim and why it adds evidence.

1. Test and rationale:

   ____________________________________________________________________

2. Test and rationale:

   ____________________________________________________________________

3. Test and rationale:

   ____________________________________________________________________

## 6. Cost and representation choice

- one direct edge lookup:
- one add or remove:
- one out-degree count:
- physical storage:

Give one situation in which an edge list or adjacency list could avoid unused
matrix cells:

____________________________________________________________________

## 7. Ghost-connection autopsy

- first invalid cell:
- invariant broken:
- delayed symptom:
- repair:
- regression claim:

## 8. Model boundary and transfer

Why does a stored permission edge not prove that communication occurred or
that a service was exploited?

____________________________________________________________________

Choose a fixed ArrayList, a binary tree, or a directed graph for each and give
one reason: an ordered event sequence; a left/right hierarchy; communication
permissions that can contain shared destinations or cycles.

____________________________________________________________________

## 9. Correction note

My initial model:

____________________________________________________________________

The evidence that changed or strengthened it:

____________________________________________________________________
