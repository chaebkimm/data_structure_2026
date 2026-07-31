# Stage B - Five-Minute Cognitive Pause

Read the locked definitions and states before timing begins. Then use no
notes, slides, vocabulary file, classmates, or coding tools. Preserve the
first response when correction begins.

BFS processes edge-count layers. Dijkstra's algorithm processes the current
smallest tentative distance. A successful strict relaxation uses
`candidate < dist[v]`. A removed snapshot is stale when its saved distance
does not equal the current distance.

The canonical graph uses source A and these directed weighted edges:

```text
A->B 9   A->C 2   A->E 14
B->D 0   B->E 8
C->B 2   C->D 2
D->E 2
```

F is unreachable from A. `INF` means no finite representable path is known.

## Target 1 - Separate edge count from total cost

Compare:

```text
A,E       1 edge    cost 14
A,C,D,E   3 edges   cost 6
```

State:

1. which route the prior layer method selects;
2. what BFS minimizes; and
3. why that answer does not minimize total cost here.

Response:

____________________________________________________________________

____________________________________________________________________

## Target 2 - Finalize and relax strictly

Use this locked state after C is finalized:

```text
dist:     A=0, B=4, C=2, D=4, E=14, F=INF
pred:     A=-, B=C, C=A, D=C, E=A, F=-
frontier: B/4, D/4, B/9, E/14
```

Remove `B/4`. State:

1. why B becomes finalized before D;
2. why B to D with weight 0 causes no update or insertion;
3. E's new distance and predecessor; and
4. the resulting frontier.

Response:

____________________________________________________________________

____________________________________________________________________

## Target 3 - Skip, reconstruct, and limit the claim

Use this locked late state:

```text
dist:     A=0, B=4, C=2, D=4, E=6, F=INF
pred:     A=-, B=C, C=A, D=C, E=D, F=-
frontier: B/9, E/12, E/14
```

State:

1. why `B/9` is stale and what the algorithm does;
2. the backward and forward predecessor path for E;
3. the independently added path cost; and
4. what F's `INF` does and does not prove.

Response:

____________________________________________________________________

____________________________________________________________________

## Compare after time is called

Preserve the original response. Label corrections `BFS goal`,
`tentative/finalized`, `strict tie`, `stale`, `path`, or `scope`.

The evidence that changed or strengthened my thinking was:

____________________________________________________________________
