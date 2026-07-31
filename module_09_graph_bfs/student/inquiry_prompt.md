# Stage A — Initial Inquiry: Fewest Links First

Name: ____________________________  
Date: ____________________________

Use only this file during the initial inquiry. Preserve your first answers.
Later, add labeled corrections instead of erasing your first thinking.

A **graph** stores items and their direct relationships. Each item is a
**vertex**. A **directed edge** permits movement in one stated direction.
The notation `0 -> 1` means movement is permitted from vertex 0 to vertex 1.
A **route** is a sequence that follows the stated directions.
**Reachable** means at least one directed route leads to the vertex from the
beginning.

This graph is synthetic, meaning invented for safe practice. It does not
describe a live system or prove that real communication is possible.

## Starting relationships

```text
                 0 Gateway
                /         \
          1 Web             2 Admin
             \              /
                  3 Database
                       |
                  4 Monitor
                       |
                 back to 1

5 Archive has no entering or leaving edge.
```

Exact directed edges:

```text
0 -> 1
0 -> 2
1 -> 3
2 -> 3
3 -> 4
4 -> 1
```

When two choices are otherwise tied, choose the lower vertex number first.

## A. Read the relationships

### A1. Immediate choices

Which vertices may be entered directly from vertex 0?

____________________________________________________________________

### A2. Merging routes

Which vertex may be entered directly from both vertex 1 and vertex 2?

____________________________________________________________________

### A3. Repetition and separation

State one route that could repeat. Then name the separate vertex.

____________________________________________________________________

## B. Invent a nearer-first rule

The task begins at vertex 0. It must handle every reachable vertex requiring
fewer directed links before any reachable vertex requiring more links.

### B1. Repeatable rule

Invent a repeatable rule for choosing what to handle next.

____________________________________________________________________

____________________________________________________________________

### B2. Complete handling order

Apply your rule. List the vertex numbers in handling order.

____________________________________________________________________

### B3. Prevent repeated work

What one yes-or-no fact should be remembered about each vertex? When should
that fact change?

____________________________________________________________________

## C. Record unfinished work

List waiting items from next to be handled through last to be handled.

### C1. Beginning and after vertex 0

State the waiting sequence before anything is handled and immediately after
vertex 0 is handled.

____________________________________________________________________

### C2. After vertex 1

State the complete waiting sequence immediately after vertex 1 is handled.

____________________________________________________________________

### C3. After vertex 2

Vertex 2 also leads to vertex 3. State the complete waiting sequence and
explain whether another 3 should be added.

____________________________________________________________________

## D. Preserve first arrival

### D1. Link counts

For each vertex, record the smallest link count you currently believe is
needed from vertex 0. Write `not reached` when appropriate.

| Vertex | Smallest link count from 0 |
|---:|---|
| 0 | |
| 1 | |
| 2 | |
| 3 | |
| 4 | |
| 5 | |

### D2. Previous vertex

For vertices 1 through 4, record which vertex first led to each one under
your rule.

```text
vertex 1:
vertex 2:
vertex 3:
vertex 4:
```

### D3. Route to Monitor

Use those previous-vertex records to state one route from Gateway to
Monitor.

____________________________________________________________________

## E. Decide what one beginning can cover

### E1. Archive

Does work beginning at Gateway handle Archive? Explain from the edges.

____________________________________________________________________

### E2. Every vertex

If the task changes to “handle every vertex,” what action is needed after
the first waiting sequence becomes empty?

____________________________________________________________________

## F. Initial synthesis

### F1. Macro-question

> Which system is reachable using the fewest communication links when
> relationships may branch, merge, and repeat?

Your initial explanation:

____________________________________________________________________

____________________________________________________________________

### F2. Open question

What question does your current rule not settle?

____________________________________________________________________
