# Chapter 10. Binary Heaps and Common On-Times

This chapter follows the supplied [lab.c](lab.c). Read the
[Korean edition](textbook_korean.md) if preferred. The older alert Priority
Queue library is an optional reference; its record types, stable ties,
growth rules, and comparison counter do not describe this lab.

## Thinking Logically

### How can we keep the next value ready?

Suppose the values 7, 3, 5, 1, 9, and 4 arrive in that order. We repeatedly
need the smallest value. A FIFO Queue would give us 7 first because 7
arrived first. A Stack would give us 4 first because 4 arrived last.
Neither rule selects 1.

An unsorted array can find the smallest of six values by scanning five
other positions. The next removal repeats the search. Keeping the whole
array sorted would make the smallest value easy to find, but a new value
could require moving many existing values. We want a weaker ordering rule
that keeps the smallest value ready and limits how much each change repairs.

A collection that selects its next item by a ranking rule is a **priority
queue**. We can implement that behavior in several ways. This lab uses a
**binary heap**, a compact tree arrangement of array positions. First we
will explain the arrangement and its rule.

### How do array positions become a tree?

Place position 0 above positions 1 and 2. Place positions 3 and 4 below 1,
and positions 5 and 6 below 2. Continue filling each level from left to
right before starting another level. This is a **complete binary tree**.
A node is one live array position. A parent is the position immediately
above a child. The top position is the **root**.

The lab reserves `int heap[10]`. The integer `size` counts live values;
only positions 0 through `size - 1` belong to the current tree. Reserving
ten positions does not make all ten live. The relationships are:

```text
parent of i: (i - 1) / 2, when i > 0
left child:  2 * i + 1, if smaller than size
right child: 2 * i + 2, if smaller than size
```

Integer division discards the remainder. The helpers `parent`, `left`,
and `right` return `-1` for a missing relative. That marker is a position
result, not a value stored in the heap. Stored values may be negative,
including -1. Never use a missing position to index `heap`.

For six live positions, position 2 has left child 5 and no right child.
Appending at position `size` preserves the complete shape.

### What ordering rule puts the smallest value at the root?

Require each parent's value to be no greater than either child's value.
Following any path upward can only keep or decrease the value. The root
therefore holds a smallest value. This is the **min-heap order invariant**:
a condition every completed heap operation must preserve.

Siblings need not be sorted. The entire left subtree need not be smaller
than the right subtree. For example, `[1,3,4,7,9,5]` obeys min-heap order,
although its array values are not sorted. A binary search tree uses a
different ordering rule for finding arbitrary keys.

`init_heap()` sets `size = 0` and `is_min_heap = 1`. It does not erase the
reserved array. With the flag set to 1, `comp(i,j)` checks
`heap[i] <= heap[j]`. Set the flag to 0 to check `heap[i] >= heap[j]` instead.
This reverse rule is **max-heap order** and puts a largest value at the root.
The name `is_min_heap` is a mode flag; it is not a checking function.

### How do we select between missing or equal positions?

A downward repair must choose an existing child before comparing its value.
`proper_parent(i,j)` returns the position that should be above the other
under the current rule. If both positions are missing, it returns -1.
If only one is missing, it returns the existing position. Otherwise it
uses `comp(i,j)`.

Equal values satisfy either comparison direction. The first argument wins.
Thus comparing a parent first stops an unnecessary swap on equality;
comparing the left child first chooses it when the child values tie.
This local choice does not preserve insertion order among equal items.
The lab stores no arrival sequence.

### Where can adding one value break the order?

The existing heap is already ordered. Appending a new value changes only
its relationship to its parent. If the new value belongs above that parent,
swap the two values and repeat from the parent's position. Stop when the
parent wins or the new value reaches the root. This is **upward repair**,
also called sift-up. The lab calls it `heapify_up`.

Predict the live array after every `add` before running the source:

| Added value | Live array after upward repair |
| --- | --- |
| 7 | `[7]` |
| 3 | `[3,7]` |
| 5 | `[3,7,5]` |
| 1 | `[1,3,5,7]` |
| 9 | `[1,3,5,7,9]` |
| 4 | `[1,3,4,7,9,5]` |

`add(data)` performs `int i = size++;`, writes `heap[i]`, then calls
`heapify_up(i)`. Postfix increment gives `i` the old size and increases the
live count. The caller must ensure `size < 10` before adding. There is no
full check, growth, or failure status inside `add`.

### How does removing the root preserve the shape?

Removing position 0 directly would leave a hole at the top. Save its value,
move the final live value to position 0, and reduce `size`. The live positions
remain a complete tree. Only the replacement root may violate the order.

Choose the better existing child. If that child belongs above the current
value, swap them and continue from the child's position. Stop when the
current value wins. This is **downward repair**, or sift-down, implemented
by `heapify_down`.

From `[1,3,4,7,9,5]`, `remove_root()` saves 1 and moves 5 from position 5
to position 0. The reduced live array is `[5,3,4,7,9]`. Choose child 3,
swap with 5, then stop because 5 is no greater than children 7 and 9:

```text
[5,3,4,7,9] -> [3,5,4,7,9]
returned value: 1
```

The lab uses prefix decrement in `heap[--size]`: decrease the live count
before reading the final value. A one-value removal reduces size to zero
and copies `heap[0]` to itself. The source still calls `heapify_down(0)`.
Both children return -1, so `proper_parent(0,-1)` returns 0 without comparing
values, and the loop stops. Removing from an already empty heap is invalid;
the caller must check `size > 0`. An inactive slot may retain an old value.

### Can we build a heap without adding values one at a time?

An input array may already contain every value. Its last positions are
leaves, with no child relationships to repair. Work backward through the
parents. At each parent, the child subtrees have already been repaired, so
a downward repair is enough. This is **bottom-up heap construction**.

Load `[7,3,5,1,9,4]` into the live prefix and set `size = 6`. In min mode,
`heapify()` visits positions 2, 1, and 0:

```text
start:     [7,3,5,1,9,4]
repair 2:  [7,3,4,1,9,5]
repair 1:  [7,1,4,3,9,5]
repair 0:  [1,3,4,7,9,5]
```

Changing `is_min_heap` changes comparisons but moves no values. Rebuild
before relying on the new order. Changing the last array's flag to 0 and
calling `heapify()` produces `[9,7,5,1,3,4]`. The next removal returns 9.
Empty and one-value heaps require no bottom-up repairs.

### When are ten devices on at the same time?

Now each device has periods when it is on. We need the earliest time that
belongs to an on-period for every device. For one currently selected period
per device, everyone must have started, and no one may have stopped.
The latest start is the earliest candidate time. The earliest stop is the
last time that candidate may reach.

Call these bounds `L` and `R`. The selected periods overlap exactly when
`L <= R`. The lab treats intervals as **closed**: both endpoints belong to
the period, so equality counts. The earliest time in that overlap is `L`.

Use this input throughout the interval investigation:

| Device ID | On-periods |
| --- | --- |
| 0 | `[1,3]`, `[7,10]` |
| 1 | `[2,5]`, `[8,12]` |
| 2–9, each | `[4,9]` |

The initial latest start is 4. The initial earliest stop is 3. There is no
common time in the selected periods. Device 0's period ending at 3 cannot
reach time 4. Move device 0 to its next period, `[7,10]`.
Now the bounds are 7 and 5. Move device 1 to `[8,12]`. The bounds become
8 and 9, giving earliest common on-time 8.

### How are the periods stored?

We need to remember each device's current period without copying its entire
schedule into a heap. `toggle_info[10][10]` contains ten rows, one per ID.
Each row holds up to five on/off pairs. For ID 0, the first four entries
are `1,3,7,10`. `interval_size[0]` is 2, the number of pairs, not 4.

`epoch[id]` is the current interval number, starting at 0. It is not an
elapsed-time counter. `get_on_time(id)` reads entry `2 * epoch[id]`.
`get_off_time(id)` reads the following entry. Unused entries in a row are
not additional periods.

Before a run, load all ten IDs with one to five intervals each. Use
nonnegative integer times with `on <= off`, ordered so each next on-time
is greater than the previous off-time. These assumptions make `-1` an
unambiguous failure result and let us advance through time. The source
does not validate counts, endpoint order, or whether input was loaded.
Zero-length intervals `[t,t]` are allowed under the closed convention.

### Why keep the same IDs in two heaps?

We need two extremes: the latest current on-time and the earliest current
off-time. One ordering cannot expose both at the root. The lab therefore
keeps two full heaps, each containing every ID exactly once.

`max_on_heap.array` stores IDs ranked by their current on-times, largest
first. `min_off_heap.array` stores IDs ranked by current off-times, smallest
first. A root value is an ID. Call its time reader to obtain the endpoint.
These arrays never add or remove IDs during the search. They do not use the
ordinary heap's `size` or `is_min_heap`.

Both objects have type `struct Heap_Full`. Each object contains an array
and two **function pointers**, fields that select functions to call.
`int (*comp)(int x, int y)` selects a comparison function taking two IDs.
`void (*swap)(int i, int j)` selects a swap function taking two positions.
`_heap->comp(...)` calls the comparison belonging to the heap pointed to
by `_heap`. The two comparators read current times through `epoch`.

`_proper_parent` takes positions, fetches their IDs from that heap's array,
and passes the IDs to its comparator. Distinguish a position, an ID, an
interval number, and a time in every trace. Equal time keys may choose
among several equally ranked IDs. Neither numeric ID nor arrival order is
a promised tie rule.

### How do we find an ID after it has moved?

Changing one device's epoch changes its key in both heaps. The device may
occupy different positions in those arrays. Searching both arrays would
repeat a scan. Instead, keep an **inverse position map** for each heap:
the ID indexes an array whose stored value is that ID's heap position.

```text
max_on_heap.array[_max_heap_pos[id]] == id
min_off_heap.array[_min_heap_pos[id]] == id
```

`__swap__` exchanges IDs in one heap and updates both affected map entries.
For example, swapping positions `i` and `j` containing IDs `x` and `y`
requires `pos[x] = j` and `pos[y] = i`. `_swap_max` and `_swap_min` select
the matching array and map. Heap order alone is insufficient: a stale map
could direct the next repair to a different device.

`_reheapify` compares the changed position with its parent. If the position
is the root or the parent still wins, it repairs downward. Otherwise it
repairs upward. Before the change, the rest of the heap was ordered; only
the changed key can require repair. In this application's chronological
advance, on-times increase and may rise in the max heap; off-times increase
and may sink in the min heap. The shared helper supports either direction.

The fixed heaps always have ten positions. `_left(4)` returns 9 and
`_right(4)` returns -1. Positions 5–9 are leaves. `_heapify` starts at 5;
that first downward call does nothing, then positions 4 through 0 repair.
Do not replace these fixed-size helpers with the variable-size helpers in
your trace.

### Why is advancing the earliest stop safe?

When `L > R`, some device's currently selected period ends before another
selected period starts. No future common time can use that ending period.
Every earlier period was already ruled out by the same argument. Discarding
an ID's earliest-ending current period therefore cannot skip a solution.
If several devices tie for earliest off-time, advancing any one is safe.

`all_on_time()` calls `_init_heaps()` to reset all epochs to zero, initialize
the ID permutations and maps, install function pointers, and build both
heaps. It does not load interval input or initialize the ordinary heap.

While the current periods do not overlap, it takes the min-off root ID
and increments that ID's epoch. If the epoch equals `interval_size[id]`,
the schedule is exhausted and it returns -1 before reading that nonexistent
period. Otherwise it repairs min-off at `_min_heap_pos[id]` and max-on at
`_max_heap_pos[id]`, then checks again.

For the shared fixture, preserve this trace:

| State | `epoch[0]` | `epoch[1]` | Latest on `L` | Earliest off `R` | Action |
| --- | --- | --- | --- | --- | --- |
| Initial | 0 | 0 | 4 | 3 | Advance ID 0 |
| First repair | 1 | 0 | 7 | 5 | Advance ID 1 |
| Second repair | 1 | 1 | 8 | 9 | Return 8 |

Every call restarts from the first intervals. A failed run leaves an epoch
at its interval count and may leave keys unrepaired. Do not inspect current
periods after -1. Start another `all_on_time()` run, or reload valid input
and call `_init_heaps()` before a manual experiment.

## Calculating Efficiency

### How much work does one repair perform?

Repeatedly scanning the six-value array makes five comparisons for the first
minimum. A heap reads its root directly. An upward or downward repair follows
one path. A tree with full levels of 1, 2, 4, and 8 positions reaches 15
values in four levels. Doubling the number of values adds roughly one level.
This growth is logarithmic, written `O(log n)` for `n` live values.

Root inspection is `O(1)`. `add` and `remove_root` each perform at most a
heap-height repair, so their generalized worst cost is `O(log n)`.
There is no allocation or resizing in this lab. A parent comparison and
choosing among at most two children take constant work.

### Why does bottom-up construction take linear work?

Most positions are near the bottom. About half are leaves and need no
repair. About a quarter can move down only one level, about an eighth at
most two, and so on. The total work is bounded by a constant multiple of
`n`, rather than giving every node the root's full height. Bottom-up
`heapify` therefore takes `O(n)` work. Building with `n` separate additions
has an `O(n log n)` worst bound. Draining a heap also has an `O(n log n)`
worst bound.

### What does an interval advance save?

A scan-based interval solver finds both bounds by reading all `n` schedules
after each advance. Two heaps build in `O(n)` work. Reading their two roots
is constant work, and changing one epoch needs two `O(log n)` repairs.
Each inverse map finds the changed ID's position in constant work.

With `a` successful advances, the generalized total is
`O(n + a log n)`. An exhausted final advance adds constant work. If `m` is
the total number of intervals across the schedules, there are at most
`m - n` successful advances and at most one final exhaustion attempt.
Thus `O(n + m log n)` is a convenient looser bound. Loading all interval
input costs `O(m)` separately. A scan alternative takes `O(n(a + 1))` work.

The exact lab fixes ten IDs, at most five intervals each, and therefore at
most forty successful advances. A repair in a ten-position heap can traverse
at most three edges. These bounded runs are constant-sized; the formulas
above describe how the method would scale if its fixed arrays and helpers
were generalized. Generalizing requires changing the size logic too.

### Which storage is reserved?

The ordinary heap reserves ten integers plus its size and mode. The interval
application reserves 100 input integers, ten counts, ten epochs, two ten-ID
heap arrays, two ten-entry inverse maps, and four function-pointer fields.
The operations use loops and a fixed number of local variables.
There is no dynamic allocation or recursive repair.

For generalized `n` schedules with `m` total intervals, input storage is
`O(m)` and heap/map/epoch working storage is `O(n)`. Additional local storage
per operation is `O(1)`. A full heap-order or inverse-map checker written in
your test driver visits `O(n)` entries. Its work is separate from the
one-path repair; this lab supplies no comparison counter or checker API.

## Glossary

These names refer to the representations and actions already traced.

| Term | Meaning in this lab |
| --- | --- |
| Priority queue / 우선순위 큐 | Select the next item using a stated ranking rule |
| Complete binary tree / 완전 이진 트리 | Fill levels from top to bottom, each from left to right |
| Binary heap / 이진 힙 | Complete tree with parent/child ordering |
| Root / root | Position 0, holding an extreme value or an extreme-key ID |
| Min/max heap / 최소·최대 힙 | Parents rank by smaller/larger values respectively |
| Invariant / 불변식 | A relationship that completed operations preserve |
| Sift-up/down / 위·아래 복구 | Restore order along one upward/downward path |
| Bottom-up heapify / 아래에서 위로 힙 구성 | Repair parents after their child subtrees |
| Comparator / 비교 함수 | Decide which of two values or IDs should be above the other |
| Closed interval / 닫힌 구간 | Include both the on-time and off-time |
| Epoch / 현재 구간 번호 | Per-ID index selecting an on/off pair |
| Function pointer / 함수 포인터 | A field holding the function to call |
| Inverse position map / 역위치 배열 | Map an ID back to its position in a particular heap |
| Reheapify / 변경 위치 복구 | Choose upward or downward repair after a key change |
| Exhaustion / 구간 소진 | Advancing beyond an ID's final available interval |

## Coding Plan

Connect each supplied function to a state change before writing tests.

1. Identify the live prefix and initialize ordinary min mode.
2. Trace relative-position helpers, comparison, missing positions, and swaps.
3. Trace downward repair, then bottom-up construction.
4. Trace root replacement and upward repair after appending.
5. Load ten valid schedules and connect `epoch` to the two time readers.
6. Distinguish positions from IDs in the full-heap comparators.
7. Trace function-pointer calls and swaps that update inverse positions.
8. Trace full-heap construction, root access, and direction selection.
9. Trace the overlap check, epoch advance, exhaustion, and both repairs.
10. Write an assertion driver with independent order/map checks and a small
    scan or brute-force interval oracle.

The lab supplies all these operations. Students write a separate driver and
three original test groups, described in [lab.md](lab.md). Use valid caller
states; do not execute empty removal or an eleventh insertion as a rejection
test. Keep those invalid calls as written precondition examples.

## C Code

The following is the exact supplied `lab.c`, in its original order. The
first block of functions implements the variable-size integer heap. The
remaining functions implement two fixed, full heaps over schedule IDs.
The source has no `main`; include it once from a separate test driver and
compile only that driver. The [lab](lab.md) gives the build commands.

```c
int heap[10];
int size;
int is_min_heap;

void init_heap() {
    size = 0;
    is_min_heap = 1;
}
int parent(int i) {return i <= 0 ? -1 : (i - 1) / 2;}
int left(int i) {return 2 * i + 1 >= size ? -1 : 2 * i + 1;}
int right(int i) {return 2 * i + 2 >= size ? -1 : 2 * i + 2;}
int comp(int i, int j) {
    return is_min_heap ? heap[i] <= heap[j] : heap[i] >= heap[j];
}
int proper_parent(int i, int j) {
    if (i == -1 && j == -1) {
        return -1;
    } else if (i == -1 || j == -1) {
        return i == -1 ? j : i;
    }
    return comp(i, j) ? i : j;
}
void swap_data(int i, int j) {
    int old_i_val = heap[i];
    int old_j_val = heap[j];
    heap[i] = old_j_val;
    heap[j] = old_i_val;
}
void heapify_down(int i) {
    while (i != -1) {
        int child = proper_parent(left(i), right(i));
        if (proper_parent(i, child) == i) {break;}
        swap_data(i, child);
        i = child;
    }
}
void heapify() {
    for (int i = parent(size - 1); i >= 0; i--) {
        heapify_down(i);
    }
}
int remove_root() {
    int root = 0;
    int data = heap[root];
    heap[root] = heap[--size];
    heapify_down(root);
    return data;
}
void heapify_up(int i) {
    while (i > 0) {
        int p = parent(i);
        if (proper_parent(p, i) == p) {break;}
        swap_data(i, p);
        i = p;
    }
}
void add(int data) {
    int i = size++;
    heap[i] = data;
    heapify_up(i);
}

int toggle_info[10][10];
int interval_size[10];
int epoch[10];

int get_on_time(int id) {
    return toggle_info[id][epoch[id] * 2];
}

int get_off_time(int id) {
    return toggle_info[id][epoch[id] * 2 + 1];
}

int _comp_on_max(int id_x, int id_y) {
    int on_time_x = get_on_time(id_x);
    int on_time_y = get_on_time(id_y);
    return on_time_x >= on_time_y;
}

int _comp_off_min(int id_x, int id_y) {
    int off_time_x = get_off_time(id_x);
    int off_time_y = get_off_time(id_y);
    return off_time_x <= off_time_y;
}

struct Heap_Full {
    int array[10];
    int (*comp)(int x, int y); 
    void (*swap)(int i, int j);
} max_on_heap, min_off_heap;

int _proper_parent(struct Heap_Full *_heap, int i, int j) {
    if (i == -1 && j == -1) {return -1;}
    else if (i == -1) {return j;}
    else if (j == -1) {return i;}
    else {
        int *arr = _heap->array;
        return _heap->comp(arr[i], arr[j]) ? i : j;
    }
}

int _parent(int i) {return i == 0 ? -1 : (i - 1) / 2;}
int _left(int i) {return i >= 5 ? -1 : 2 * i + 1;}
int _right(int i) {return i >= 4 ? -1 : 2 * i + 2;}

int _max_heap_pos[10];
int _min_heap_pos[10];

void __swap__(int i, int j, int *_arr, int *_heap_pos) {
    int x = _arr[i]; /* _heap_pos[x] == i */
    int y = _arr[j]; /* _heap_pos[y] == j */
    _arr[i] = y;
    _arr[j] = x;
    _heap_pos[x] = j;
    _heap_pos[y] = i;
}
void _swap_max(int i, int j) {__swap__(i, j, max_on_heap.array, _max_heap_pos);}
void _swap_min(int i, int j) {__swap__(i, j, min_off_heap.array, _min_heap_pos);}

void _heapify_down(struct Heap_Full *_heap, int i) {
    int leaf_start = 5;
    while (i < leaf_start) {
        int child = _proper_parent(_heap, _left(i), _right(i));
        int pp = _proper_parent(_heap, i, child);
        if (pp == i) {break;}
        _heap->swap(i, child);
        i = child;        
    }
}

void _heapify(struct Heap_Full *_heap) {
    for (int i = 5; i >= 0; i--) {
        _heapify_down(_heap, i);
    }
}

void _init_heaps() {
    for (int i = 0; i < 10; i++) {
        epoch[i] = 0;
        max_on_heap.array[i] = i;
        _max_heap_pos[i] = i;
        min_off_heap.array[i] = i;
        _min_heap_pos[i] = i;
    }
    max_on_heap.comp = _comp_on_max;
    max_on_heap.swap = _swap_max;
    min_off_heap.comp = _comp_off_min;
    min_off_heap.swap = _swap_min;
    _heapify(&max_on_heap);
    _heapify(&min_off_heap);
}

int _get_root(struct Heap_Full *_heap) {
    return _heap->array[0];
}

void _heapify_up(struct Heap_Full *_heap, int i) {
    while (i > 0) {
        int pp = _proper_parent(_heap, _parent(i), i);
        if (pp == _parent(i)) {break;}
        _heap->swap(i, _parent(i));
        i = _parent(i);
    }
}

void _reheapify(struct Heap_Full *_heap, int i) {
    int pp = _proper_parent(_heap, _parent(i), i);
    if (i == 0 || pp == _parent(i)) {_heapify_down(_heap, i);}
    else {_heapify_up(_heap, i);}
}

int check_all_on() {
    int last_on_id = _get_root(&max_on_heap);
    int first_off_id = _get_root(&min_off_heap);
    return get_on_time(last_on_id) <= get_off_time(first_off_id);
}

int all_on_time() {
    _init_heaps();
    while (!check_all_on()) {
        int id = _get_root(&min_off_heap);
        if (++epoch[id] == interval_size[id]) {return -1;}
        _reheapify(&min_off_heap, _min_heap_pos[id]);
        _reheapify(&max_on_heap, _max_heap_pos[id]);
    }
    int last_on_id = _get_root(&max_on_heap);
    return get_on_time(last_on_id);
}
```
