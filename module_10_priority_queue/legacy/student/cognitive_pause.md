# Stage B — Five-Minute Cognitive Pause

Read the locked facts before timing starts. Then close notes, slides,
vocabulary, classmates' work, and coding tools. Preserve the first response
when correction begins. Exactly three targets follow.

The directed routes are:

```text
A->B 9   A->C 2   A->E 14
B->D 1   B->E 8
C->B 3   C->D 2
D->E 2
```

IDs are A=0 through F=5. Each listed weight is positive. `node_dist[v]` is
the best cost known so far; `-1` means no route discovered. `heap` contains
node IDs, and `node_heap_pos` maps waiting IDs back to heap slots.

## Target 1 — Separate edge count from total cost

Compare A to E with A to C to D to E.

1. Give each route's edge count and total cost.
2. State what BFS minimizes.
3. Explain why its answer need not minimize total cost here.

Response: ___________________________________________________________

Response: ___________________________________________________________

## Target 2 — Change an existing waiting node

Use this locked state immediately after C's outgoing edges are processed:

```text
node_dist A..F: [0,5,2,4,14,-1]
heap node IDs:  [D,E,B]
heap positions: 0 1 2
```

1. Explain why B appears once even though its distance changed from 9 to 5.
2. Give `node_heap_pos[B]` and the next node to remove.
3. Explain what `comp(0,2)` compares. Use node IDs and costs, not only slots.

Response: ___________________________________________________________

Response: ___________________________________________________________

## Target 3 — Finalize, improve, and state the assumptions

D is removed next. Its edge offers E a total of 6. B is then removed and
offers D a total of 6 and E a total of 13.

1. State which proposals change a distance and which do nothing.
2. State F's final distance and what it means for this stored graph.
3. Explain why positive weights prevent a later improvement to a finalized
   node. Does the C source check weights or protect `int` addition?

Response: ___________________________________________________________

Response: ___________________________________________________________

## Correction record

After the instructor comparison, preserve each first response and add:

- original claim: ___________________________________________________
- source state or observation: ______________________________________
- corrected explanation: ____________________________________________

Do not add path-reconstruction or lazy-snapshot tasks. This pause checks the
state and operations actually present in `lab.c`.
