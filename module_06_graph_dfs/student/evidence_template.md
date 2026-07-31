# Module 6 Evidence Record

Complete this record after the Stage D notes and Stage E lab. You may replace
any table with a numbered list using the same headings.

Name: ____________________________  
Compiler used — the program that translates C into a runnable program:
____________________________

## 1. Core language

Depth-first search:

____________________________________________________________________

Visited state:

____________________________________________________________________

Marked versus recorded:

____________________________________________________________________

Frontier:

____________________________________________________________________

Reachable:

____________________________________________________________________

## 2. Course directed trace

Use the graph:

```text
0:[1,2]  1:[3]  2:[3]  3:[4]  4:[1]  5:[]
```

Recursive order from source 0:

____________________________________________________________________

Final visited set:

____________________________________________________________________

Edges skipped because their destinations are marked:

____________________________________________________________________

### Iterative states

A **Stack** is a last-in, first-out collection. List each Stack bottom to
top, from its oldest item to its newest item.

| Completed processing | Visited vertices | Complete Stack | Output |
|---|---|---|---|
| none; source pushed | | | |
| 0 | | | |
| 1 | | | |
| 3 | | | |
| 4 | | | |
| 2 | | | |

Why are destinations checked from high number to low number?

____________________________________________________________________

Why is a destination marked only after its push succeeds?

____________________________________________________________________

## 3. Recursive and explicit storage

**Recursion** occurs when a function calls itself. A **call frame** stores
information for one active call. An **explicit Stack** is a last-in,
first-out collection directly operated by the program.

How does each form remember unfinished graph work?

Recursive calls:

____________________________________________________________________

Explicit vertex-ID Stack:

____________________________________________________________________

## 4. Test evidence

An **allocation** is storage requested while a program runs. An allocation
failure means that requested storage was unavailable.

| Case | Expected result | Actual result | Pass? |
|---|---|---|---|
| Single vertex | | | |
| Directed cycle | | | |
| Course recursive DFS | | | |
| Course iterative DFS | | | |
| Isolated source 5 | | | |
| Inactive source | | | |
| Stack limit 2 | | | |
| Stack limit 1 | | | |
| Stack allocation failure | | | |
| Invalid graph | | | |
| Directed component rejection | | | |
| Two undirected components | | | |
| Empty undirected graph | | | |

### Exactly three student-authored tests

For each test, state the new claim it checks.

1. Traversal order or reachability with a cycle or disconnected case:

   __________________________________________________________________

2. Failure that preserves caller output:

   __________________________________________________________________

3. Undirected component count with an isolate or empty graph:

   __________________________________________________________________

## 5. Failure preservation and cleanup

**Failure preservation** means a failed operation leaves the caller's old
output unchanged. **Cleanup** means releasing temporary storage after use.
To destroy the Stack means to release the memory it owns and reset its
stored values.

What happened to a prepared old order after a Stack-limit failure?

____________________________________________________________________

How did you verify that iterative DFS destroyed its temporary Stack after a
later failure?

____________________________________________________________________

## 6. Connected components

A **connected component** is one separate group in an undirected graph whose
vertices have routes to one another.

For the undirected companion graph, list each component and the count:

____________________________________________________________________

Recursive whole-graph order, with `|` between components:

____________________________________________________________________

Iterative whole-graph order:

____________________________________________________________________

Why is component counting rejected for a directed graph?

____________________________________________________________________

## 7. Costs

Let `V` be vertex count and `E` be edge count. **Auxiliary space** is
temporary working storage separate from the graph and output.
**Big-O notation** writes a growth pattern as `O(...)`.

| Representation | Full DFS time | Auxiliary space | Reason |
|---|---:|---:|---|
| Adjacency matrix | | | |
| Adjacency lists | | | |

## 8. Graph DFS Autopsy

A **regression test** is kept to prevent a known defect from returning.

- predicted repeated entry pattern:
- observed entry pattern:
- earliest state or check causing repeated entry:
- smallest correction:
- regression test:

## 9. Tree-to-graph transfer

What saved-work idea remains the same?

____________________________________________________________________

Why does a graph need visited state when a valid tree did not?

____________________________________________________________________

Why may one graph source fail to cover every vertex?

____________________________________________________________________

## 10. Safe meaning

The graph is synthetic, meaning invented for practice. What does a recorded
route prove, and what does it not prove about a real system?

____________________________________________________________________

## 11. Correction note

My initial thinking:

____________________________________________________________________

The evidence that changed or strengthened it:

____________________________________________________________________
