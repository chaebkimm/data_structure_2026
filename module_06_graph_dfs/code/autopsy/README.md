# Isolated DFS Autopsy

`faulty_cycle_dfs.c` is a complete standalone program. It does not use the
student implementation and contains no undefined behavior.

Its directed graph is:

```text
0 -> 1 -> 2 -> 0
```

The program intends to visit each vertex once. It contains one intentional
traversal defect. A small call budget stops the program safely instead of
allowing uncontrolled recursion.

Before running it:

1. predict every printed line;
2. locate the earliest state decision that permits a repeated entry; and
3. describe the smallest correction and why it works.

The budget is a safety device, not the repair.
