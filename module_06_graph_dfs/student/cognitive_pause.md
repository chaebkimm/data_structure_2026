# Stage B — Five-Minute Cognitive Pause

Read the starting definitions with the instructor before timing begins.
Then use no notes, slides, classmates, or coding tools for five minutes.
You may draw, type, dictate, or answer in numbered sentences.

An approved extended-time version, or one completed at another approved
time, uses the same graph and three targets. Speed, handwriting, and drawing
quality are not assessed. Preserve your first response when correction
begins.

## Starting definitions

A **graph** stores items and direct relationships. A **vertex** is one item.
A **directed edge** is a relationship that works in one direction.
**Depth-first search (DFS)** follows one available route deeply before
returning to an unfinished choice. The **source** is the starting vertex. An
**out-neighbor** is the destination of an edge leaving the current vertex.

A **visited array** stores one yes-or-no value per vertex. **Discovered**
means first reached. **Scheduled** means arranged for work. **Recorded**
means appended to output. To **mark** means to change a visited value to
true. A **recursive call** is a function call made by that same function. It
marks and records its vertex on entry.

An **explicit Stack** is a last-in, first-out collection directly operated
by the program. Its **frontier** contains marked vertices still waiting to
be processed. `push` adds one item; `pop` removes the newest item. The
iterative method records on pop and marks only after a successful push.

## Pause graph

This graph has five vertices and these directed edges:

```text
0 → 1
0 → 2
1 → 3
3 → 1
2 → 4
```

Equivalent outgoing-neighbor lists:

```text
0:[1, 2]   1:[3]   2:[4]   3:[1]   4:[]
```

In words, 0 leads to 1 and 2; 1 leads to 3; 3 leads back to 1; 2 leads to 4;
and 4 has no outgoing edge.

## Target 1 — Trace recursive DFS

Start at vertex 0. Mark and record a vertex on entry. Check possible
destinations from lower number to higher number.

1. Write the complete recorded order.
2. State the final set of marked vertices.

Response:

____________________________________________________________________

____________________________________________________________________

## Target 2 — Stop the repeated route

Recursive DFS reaches the edge `3 → 1`.

1. What is the value of `visited[1]` at that moment?
2. What exact action does the method take for this edge?
3. What route would repeat if the check were missing?

Response:

____________________________________________________________________

____________________________________________________________________

## Target 3 — Trace the explicit frontier

Start by pushing 0 and marking it after the push succeeds. Pop and record one
vertex at a time. Check possible destinations from higher number to lower
number. Push an unmarked destination, then mark it only after that push
succeeds. List every Stack from bottom to top.

1. Give visited vertices, complete Stack state, and output after processing
   0.
2. Give the same three facts after processing 1.
3. Explain why checking destinations in decreasing order makes the
   lower-numbered destination leave the Stack first.

Response:

____________________________________________________________________

____________________________________________________________________

## Compare after time is called

**Calibration** means comparing an initial answer with an accurate answer.
When the instructor releases that answer:

1. preserve your initial response;
2. check reasoning that remains correct;
3. label each correction `recursive order`, `cycle check`, or
   `frontier order`; and
4. finish the sentence below.

Correction:

____________________________________________________________________

The evidence that changed or strengthened my thinking was:

____________________________________________________________________
