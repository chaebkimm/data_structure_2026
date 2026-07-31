# Module 9 Evidence Template

Name: ____________________________  
Date: ____________________________

**Evidence** is information supporting a claim. Record exact states,
statuses, outputs, commands, and observations so another person can repeat
your checks.

## 1. BFS model

Define in your own words:

```text
breadth-first search:
discovered:
processed:
frontier:
distance:
predecessor:
```

Why must discovery occur immediately after successful enqueue?

____________________________________________________________________

## 2. Canonical trace

For source 0 in the eight-vertex canonical graph:

```text
initial Queue:
Queue after 0:
Queue after 1:
Queue after 2:
Queue after 3:
Queue after 4:
Queue after 5:
Queue after 6:
maximum pending count:
```

Final result:

```text
visit_count:
visit_order:
discovered[0..7]:
distance[0..7]:
predecessor[0..7]:
```

## 3. Duplicate-work evidence

For each edge, state whether its destination is pending or processed when
checked and explain why no new enqueue occurs:

```text
2 -> 4:
4 -> 6:
5 -> 4:
6 -> 1:
```

Which result fields remain permanent after first discovery?

____________________________________________________________________

## 4. Path certificate

A **path certificate** is a path whose endpoints, consecutive edges, and
hop count can be checked.

```text
destination:
backward predecessor sequence:
forward path:
hop count:
stored distance:
edge checks:
```

State one different equal-hop route and explain why the returned route is
still correct.

____________________________________________________________________

## 5. Unreachable and disconnected evidence

Record the destination-7 path call:

```text
starting output path:
status:
ending output path:
preserved?
```

For the separate undirected paper graph:

```text
forest order:
roots:
component sets:
component count:
```

Why would the same component claim be unsafe for a directed forest?

____________________________________________________________________

## 6. Matrix/list comparison

| Named result | Matrix | Adjacency list | Equal? |
|---|---|---|---|
| vertex count and source | | | |
| visit count and order | | | |
| all discovered values | | | |
| all distance values | | | |
| all predecessor values | | | |

For vertex 2:

```text
matrix cells inspected:
true matrix cells:
live list entries:
```

Why must construction cost remain separate from traversal cost?

____________________________________________________________________

## 7. Contract and Queue-limit evidence

| Case | Starting output | Status | Ending output | Claim |
|---|---|---|---|---|
| canonical matrix, limit 3 | | | | |
| canonical list, limit 3 | | | | |
| canonical matrix, limit 2 | | | | |
| canonical list, limit 2 | | | | |
| nonempty graph, limit 0 | | | | |
| requested limit 17 | | | | |
| invalid source | | | | |
| malformed graph | | | | |

At limit 2, name the attempted enqueue that fails:

____________________________________________________________________

Why does candidate-and-commit preserve the caller's old output?

____________________________________________________________________

## 8. Storage and cleanup evidence

```text
matrix allocation count:
adjacency-list rows allocated:
list validation result:
list state after destroy:
live row count after destroy, when testing support is available:
```

Who owns the neighbor-row allocations?

____________________________________________________________________

Why does the vertex Queue require no destroy call?

____________________________________________________________________

## 9. Student-authored tests

### Test 1 — Cycle and merge state

Claim, graph, operations, expected result, and actual result:

____________________________________________________________________

### Test 2 — Reachable, source, and unreachable paths

Claim, operations, expected result, and actual result:

____________________________________________________________________

### Test 3 — Representation equality and Queue boundary

Claim, operations, expected result, and actual result:

____________________________________________________________________

## 10. Tool evidence

```text
compiler and version:
exact core-test command:
core-test result:
exact student-test command:
student-test result:
warnings:
sanitizer result, if available:
```

If a tool was unavailable, name the approved equivalent evidence:

____________________________________________________________________

## 11. Graph BFS Autopsy

```text
predicted faulty Queue after 2:
observed faulty Queue after 2:
predicted removal order:
observed removal order:
observed predecessor[3]:
observed predecessor[4]:
first broken decision:
violated invariant:
smallest repair:
regression test:
```

Why did checked bounds not guarantee correct scheduling?

____________________________________________________________________

## 12. Cost, transfer, and correction

| Method | Time | Auxiliary space |
|---|---:|---:|
| matrix BFS | | |
| adjacency-list BFS | | |
| path reconstruction | | |

Explain how pending work differs in an event Queue, tree BFS, and graph BFS.

____________________________________________________________________

Correct this incomplete claim:

> FIFO always finds a shortest path.

____________________________________________________________________

State two real-world claims that minimum modeled hops does not prove.

____________________________________________________________________

My preserved Stage A claim:

____________________________________________________________________

My labeled correction and supporting evidence:

____________________________________________________________________
