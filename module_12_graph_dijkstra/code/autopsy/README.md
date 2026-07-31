# Safe overflow autopsy

This isolated program is memory-safe and intentionally wrong in one logical
step. Its fixed local values are:

```text
distance = SIZE_MAX - 3
weight = 5
old neighbor distance = 20
```

C defines unsigned `size_t` arithmetic to wrap modulo one more than
`SIZE_MAX`. The unchecked sum therefore wraps to `1`. Because `1 < 20`, the
faulty code would claim a false improvement.

The correct pre-addition guard asks whether:

```text
distance != SIZE_MAX
weight <= SIZE_MAX - distance
```

Here the second condition is `5 <= 3`, which is false. Module 12 reports
`DIJKSTRA_COST_RANGE` and leaves the old neighbor distance at `20`. A safe
sum equal to reserved `DIJKSTRA_INF` is rejected in the same way.

Expected architecture-independent facts in the output:

```text
weight: 5
unchecked candidate: 1
faulty relaxation: YES
guarded status: DIJKSTRA_COST_RANGE
guarded neighbor distance: 20
```

The printed numeric `distance` differs between 32-bit and 64-bit systems
because their `SIZE_MAX` values differ.
