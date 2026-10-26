# Module 10 — Reveal the Heap Representation

We want the next smallest or largest value ready without scanning every
stored value after each change. Use [lab.c](lab.c) to test the model.

## Why arrange an array as a tree?

Fill each level from left to right. The live values occupy one compact
prefix of `heap[10]`. This is a complete binary tree stored in an array.
The root is position 0. `size` counts live values, not the last position.

```text
position:           0
                  /   \
                 1     2
                / \   / \
               3   4 5   6
```

For a live nonroot position `i`, the parent is `(i-1)/2` using integer
division. Potential children are `2*i+1` and `2*i+2`. A child exists only
below `size`. The simple helpers return `-1` for a missing relationship.
`parent(i)` also returns `-1` when `i<=0`.

## Which value belongs above another?

A minimum Heap keeps every parent no larger than its children. A maximum
Heap keeps every parent no smaller. `is_min_heap` selects these rules.
`init_heap()` chooses minimum mode and sets size to 0.

`comp(i,j)` compares values at positions. `proper_parent(i,j)` returns the
better position while avoiding the `-1` sentinel. On equal values it keeps
the first argument. This local choice does not provide stable arrival order.
Neither Heap rule globally sorts the array or provides BST search order.

## How much order needs repair?

Appending affects the new value's path toward the root. `heapify_up` swaps
along that path. Root removal moves the last live value to position 0 and
`heapify_down` follows the better existing child. With values
`7,3,5,1,9,4`, successive additions yield `[1,3,4,7,9,5]`. Removing the root
returns 1 and leaves `[3,5,4,7,9]`.

`heapify()` repairs all internal positions from the bottom upward. It also
rebuilds after changing `is_min_heap`. The source does not check full
insertion or empty removal: callers need `size<10` and `size>0` respectively.

## Why store IDs in a second Heap design?

A device's current time changes when its selected interval changes. Keep
its ID in each Heap and look up its selected endpoint during comparison.
`epoch[id]` selects endpoint columns `2*epoch[id]` and `2*epoch[id]+1`.

Each `struct Heap_Full` contains ten IDs, a comparison function pointer,
and a swap function pointer. `max_on_heap` keeps the largest on-time at its
root. `min_off_heap` keeps the smallest off-time at its root. Both Heaps
contain every ID exactly once. There is no live-size field in this design.

The helpers `_left` and `_right` assume ten live positions. Position 4 has
only left child 9. Positions 5 through 9 are leaves. `_heapify` starts at
5, where repair does nothing, then processes 4 through 0.

## Where did a changed ID move?

Look up its current position instead of searching the array. The inverse
maps are `_max_heap_pos` and `_min_heap_pos`. `__swap__` swaps two stored IDs
and updates both corresponding map entries. A correct order with a broken
map is still an incorrect indexed Heap.

`_proper_parent` takes positions but passes the stored IDs to the Heap's
comparator. `_reheapify` takes a position. It chooses upward repair only
when that position outranks its parent; otherwise it repairs downward.

## When do the ten intervals intersect?

All devices are on when the latest selected start is no later than the
earliest selected end. The intervals are closed, so equality counts.
`check_all_on()` tests this relation using the two roots.

`all_on_time()` initializes both Heaps, advances the ID with the smallest
selected off-time whenever the relation fails, and repairs that ID in both
Heaps. It returns the largest selected on-time on success. If that ID has
no later interval, it returns `-1` immediately after advancing the epoch.
That terminal epoch cannot be read as a valid interval.

Load all ten IDs with one to five valid intervals ordered with each prior off-time strictly before the next on-time.
Use nonnegative endpoints to keep `-1` distinct from an answer. There is no
input validation in the supplied source. See the [lab](lab.md) for the shared
fixture and the [diagrams](../diagrams/binary_heap_models.md) for exact states.
