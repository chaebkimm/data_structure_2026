# Module 11 Autopsy — Confusing a Node with Its Heap Position

Use one case below for a short part of the integrated Practical 2 evidence.
Predict first, then identify the first divergent operation. Work on paper
or in a separate bounded scratch example. Keep the supplied `lab.c`
unchanged. Both cases use allocated positions 0–9; no invalid memory access
is required to explain the defect.

## Case A. Compare IDs through their heap slots

Freeze this valid minimum heap with `size=3`:

```text
heap[0..2] = [4,1,3]
node_dist[4] = 2
node_dist[1] = 5
node_dist[3] = 9
node_heap_pos[4] = 0
node_heap_pos[1] = 1
node_heap_pos[3] = 2
```

For this example also set `node_dist[0]=30` and `node_dist[2]=1`. These
nodes are not in the live heap. Those values must not determine its order.

The correct comparison is:

```c
int comp(int i, int j) {
    return node_dist[heap[i]] < node_dist[heap[j]];
}
```

The faulty scratch comparison is:

```c
int faulty_comp(int i, int j) {
    return node_dist[i] < node_dist[j];
}
```

### Predict

1. Which node IDs does `comp(0,1)` rank, and what is its result?
2. What unrelated values does `faulty_comp(0,1)` rank?
3. During upward repair from position 1, does the faulty test stop or swap?
4. What parent/child relation is violated immediately after that action?

Prediction: _________________________________________________________

### Locate the first divergence

Complete:

> The function receives heap ____________________, but the faulty version
> uses them as graph ____________________. The first wrong decision is
> ________________________________________________________________.

### Check and explain

Give an assertion that the faulty state violates. Why would a test using
only `heap[i] == i` fail to expose this bug? Show one swap's required map
changes. State why sorting node numbers is unrelated to selecting the
smallest current distance.

Evidence: ___________________________________________________________

## Case B. Remove heap position zero

Use the same live heap `[4,1,3]`, and set inactive `heap[4]=6` for a bounded
scratch example. Consider this faulty removal:

```c
int node = heap[0];
int last = --size;
swap(node, last);  /* wrong: node is an ID */
heapify_down(0);
```

### Predict

1. What are `node` and `last`?
2. Which two slots does the faulty call exchange?
3. Is the saved node still in the new live prefix after repair?
4. Which ID was dropped from the live prefix without being returned?

Prediction: _________________________________________________________

### Repair the first wrong operation

The source correctly calls:

```c
swap(0, --size);
```

Explain why both arguments are positions. Trace the correct new live heap
and its live inverse-map entries. The removed node's map entry may remain
stale; no supplied operation requires it to become `-1`.

Evidence: ___________________________________________________________

## Write the regression

For your chosen case, record the fixture, predicted outcome, assertion,
and specific broken line it exposes. Check actual `lab.c` independently
rather than presenting a scratch failure as a failure of the supplied
correct source.

Test location: ______________________________________________________

## Keep numeric contracts separate

The lab assumes positive listed weights and candidate sums within `int`;
it has no validator or overflow guard. Do not execute signed overflow as a
rejection demonstration. Explain that limitation from the source.

`code/autopsy/faulty_overflow.c` is an optional example for the separate
lazy-duplicate library's unsigned numeric contract. Its wrapped `size_t`
sum and `DIJKSTRA_COST_RANGE` correction do not describe checks performed
by this indexed lab, and are not an additional required task.
