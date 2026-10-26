# Safe Kruskal Cycle Autopsy

The three already sorted offers are `A-B` with weight 1, `B-C` with weight
2, and `A-C` with weight 3.

The faulty rule accepts an edge whenever its two endpoint numbers differ.
That only rejects a self-loop. After the first two edges, A and C have
different numbers but already belong to the same connected group. Accepting
the third edge therefore creates a cycle.

The runnable demonstration is fully bounded and contains no undefined
behavior:

```text
Faulty raw-endpoint rule: 3 edges, total 6, cycle: yes
Correct representative rule: 2 edges, total 3, cycle: no
```

The repair uses `find` to obtain each endpoint's current representative
root. It stores and joins an edge only when those roots differ.
