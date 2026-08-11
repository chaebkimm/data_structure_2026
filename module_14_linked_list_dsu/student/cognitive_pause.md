# Stage B - Five-Minute Cognitive Pause

Read the locked definitions and states before timing begins. Then use no
notes, slides, vocabulary file, classmates, or coding tools. Preserve the
first response when correction begins.

A linked list owns nodes reached from `head`. A node must not be read after
it is released. DSU stores a parent forest. `find` follows parents to a
self-parent root, then compresses the visited path. Union by component size
attaches the smaller root below the larger; the smaller root ID wins an
equal-size tie.

IDs are ordered `A,B,C,D,E,F,G,H`.

## Target 1 - Delete 23 without losing ownership

Use this locked list:

```text
head=R, size=3, limit=4
R: value 17, next Q
Q: value 23, next P
P: value 31, next NULL
```

State:

1. the victim, live predecessor, and successor;
2. what must be saved before any release;
3. the safe relink-and-release order;
4. the exact final chain and size; and
5. why releasing Q and then reading `Q->next` is invalid.

Response:

____________________________________________________________________

____________________________________________________________________

## Target 2 - Follow and compress H

Use this locked DSU state after the seven canonical unions:

```text
parent:         [A,A,A,C,A,E,E,G]
component_size: [8,0,0,0,0,0,0,0]
components:     1
```

Run `find(H)`. State:

1. the exact first-pass path from H to its root;
2. every parent entry changed by the second pass;
3. the complete resulting parent array; and
4. why the component size and membership do not change.

Response:

____________________________________________________________________

____________________________________________________________________

## Target 3 - Decide the D-H relationship and limit the claim

Begin with the state after Target 2:

```text
parent:         [A,A,A,C,A,E,A,A]
component_size: [8,0,0,0,0,0,0,0]
components:     1
```

Process `union(D,H)`. State:

1. D's path and any compression;
2. both returned roots;
3. whether a merge occurs and why the new undirected relationship is
   cycle-producing;
4. the complete final parent array; and
5. one DSU limitation or trust warning.

Response:

____________________________________________________________________

____________________________________________________________________

## Compare after time is called

Preserve the original response. Label corrections `ownership order`,
`compression`, `same set`, `cycle`, or `scope`.

The evidence that changed or strengthened my thinking was:

____________________________________________________________________
