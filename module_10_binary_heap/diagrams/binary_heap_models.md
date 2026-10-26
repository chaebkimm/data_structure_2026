# Module 10 Board Models — The Current `lab.c`

Use these states with [the student lab](../student/lab.md). Ask for a
prediction before revealing the next state. Positions and values are
separate labels.

## How does the live array map to a tree?

Only positions below `size` exist in the simple Heap. Six values occupy
this complete shape; position 2 has only left child 5.

```text
                 0:1
               /     \
            1:3       2:4
           /   \     /
        3:7    4:9  5:5

position:  0 1 2 3 4 5
value:     1 3 4 7 9 5
```

The minimum is at the root. Values 5 and 7 demonstrate that array order is
not globally sorted. For nonroot `i`, parent is `(i-1)/2`. Potential children
are `2*i+1` and `2*i+2`; missing-child helpers return `-1`.

## Which swaps occur during insertion?

Start with `init_heap()` and append each value before repairing upward.

| Added value | Parent tests after append | Final live array |
| ---: | --- | --- |
| 7 | none | `[7]` |
| 3 | position 0 | `[3,7]` |
| 5 | position 0 | `[3,7,5]` |
| 1 | positions 1, 0 | `[1,3,5,7]` |
| 9 | position 1 | `[1,3,5,7,9]` |
| 4 | positions 2, 0 | `[1,3,4,7,9,5]` |

The added 1 follows positions 3→1→0. The added 4 follows 5→2 and stops
when compared with position 0. `comp` accepts equality, so a tied child
does not displace its parent. The source does not store arrival order.

## Why choose the better child?

Remove the root from the six-value minimum Heap. Save 1, decrement size,
and move the former last value 5 into position 0.

```text
before:       [1,3,4,7,9,5], size6
replacement:  [5,3,4,7,9],   size5
choose3:      [3,5,4,7,9],   size5
stop: parent5 precedes both7 and9
```

Choosing child 4 instead would leave child 3 preceding the new root 4.
A position with only a left child makes no nonexistent-right read.
For a singleton removal, size becomes 0 and both child helpers return `-1`.
`proper_parent(0,-1)` returns 0 without a comparison, so the source stops.

## What does bottom-up building visit?

Load the original six values directly. The last internal position is 2.

```text
initial:             [7,3,5,1,9,4]
heapify_down(2):     [7,3,4,1,9,5]
heapify_down(1):     [7,1,4,3,9,5]
heapify_down(0):     [1,3,4,7,9,5]
```

Changing `is_min_heap` to 0 does not move data. A following `heapify()`
rebuilds the six values as `[9,7,5,1,3,4]`. Root inspection now gives 9.

## Which intervals are currently selected?

Each ID has one selected closed interval. Use all ten rows.

| ID | Epoch 0 | Epoch 1 |
| --- | --- | --- |
| 0 | `[1,3]` | `[7,10]` |
| 1 | `[2,5]` | `[8,12]` |
| 2–9 | `[4,9]` | absent |

`max_on_heap.array` and `min_off_heap.array` contain IDs. Each comparator
looks up that ID's endpoint through `epoch`. These arrays always contain
ten IDs. They do not use the simple Heap's `size` or `is_min_heap`.

```text
_latest_on_time = get_on_time(max_on_heap.array[0])
_earliest_off_time = get_off_time(min_off_heap.array[0])
shared closed times exist when latest_on_time <= earliest_off_time
```

The underscored bound labels above are explanatory notation, not source
variables. The source obtains the bounds inside `check_all_on()`.

## Where do all ten IDs move?

The following are exact source states, including its first-argument tie
choices. Equal-time IDs could form other valid Heaps under another
implementation; Heap order alone does not determine their positions.

| State | Maximum-on ID array | Minimum-off ID array |
| --- | --- | --- |
| after `_init_heaps()` | `[3,7,2,8,4,5,6,1,0,9]` | `[0,1,2,3,4,5,6,7,8,9]` |
| advance ID 0 | `[0,3,2,7,4,5,6,1,8,9]` | `[1,3,2,7,4,5,6,0,8,9]` |
| advance ID 1 | `[1,0,2,3,4,5,6,7,8,9]` | `[3,7,2,8,4,5,6,0,1,9]` |

Read the next table by ID rather than by Heap position.

| State | `_max_heap_pos[0..9]` | `_min_heap_pos[0..9]` |
| --- | --- | --- |
| after initialization | `[8,7,2,0,4,5,6,1,3,9]` | `[0,1,2,3,4,5,6,7,8,9]` |
| advance ID 0 | `[0,7,2,1,4,5,6,3,8,9]` | `[7,0,2,1,4,5,6,3,8,9]` |
| advance ID 1 | `[1,0,2,3,4,5,6,7,8,9]` | `[7,8,2,0,4,5,6,1,3,9]` |

Verify `array[pos[id]]==id` in both Heaps after each swap. Position 4 has
only left child 9 in a ten-position Heap; positions 5 through 9 are leaves.
`_heapify`'s initial visit to position 5 does nothing.

## Why advance the earliest ending interval?

No selected interval ending before the latest start can contain a common
answer. Advance the earliest-ending ID and update its two keys.

| Selected epochs | Largest on-time | Smallest off-time | Decision |
| --- | ---: | ---: | --- |
| all 0 | 4 | 3 | ID 0 advances |
| ID 0 at 1; others 0 | 7 | 5 | ID 1 advances |
| IDs 0,1 at 1; others 0 | 8 | 9 | return 8 |

For closed endpoints, ID 1's second interval `[9,12]` makes the final
bounds `(9,9)` and the answer 9. If ID 0 has only `[1,3]` while every other
ID has `[4,9]`, advancing ID 0 exhausts its row and returns `-1`.
The exhausted epoch equals its count; do not read its times afterward.

## Which work grows?

A repair follows one tree path. A complete tree adds a level when its
capacity roughly doubles. Generalized repair is `O(log n)` and root
inspection is `O(1)`. Bottom-up building is `O(n)` because most positions
are near the leaves. A full diagnostic scan of order and maps is `O(n)`.

For `n` IDs and `r` successful interval advances, construction plus repairs
costs `O(n+r log n)`; one extra failed advance may terminate the run.
The actual source fixes ten IDs and at most five intervals per ID. Its
reserved arrays and path lengths are bounded constants. Keep that physical
limit separate from the generalized growth explanation.
