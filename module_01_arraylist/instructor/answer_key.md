# Instructor Answer Key — Module 1

## Macro-Question expert synthesis

An ArrayList stores a pointer to contiguous owned storage plus `size` and `capacity`. When append finds `size == capacity`, it computes a representable larger capacity, requests enough bytes, and commits the returned pointer and capacity only after successful allocation. Existing logical values are preserved, but the allocation may move, invalidating saved pointers into the old block. It then writes at the old `size` and increments `size`.

If contiguous growth is undesirable or unavailable, a linked representation stores values in separately allocated nodes connected by addresses. This avoids relocating one element block for local insertion, but adds link/allocation overhead, pointer ownership risks, weaker locality, and linear indexed access.

## Staged inquiry and investigation answers

### A. Retrieval

1. Valid indexes: `0`, `1`, `2`, `3`.
2. Third value: `events[2]`.
3. C does not automatically track how many slots the program considers logically occupied.
4. `events[4] = 52` attempts a one-past-the-end write and has undefined behavior.

### C. Representation

Minimum state:

1. address of element storage;
2. logical element count;
3. allocated element capacity.

Labels:

- `data`: owning pointer to contiguous element storage;
- `size`: logical element count;
- `capacity`: allocated element slots.

### D. Valid states

| `data` | `size` | `capacity` | Valid? | Reason |
|---|---:|---:|---|---|
| `NULL` | 0 | 0 | yes | Canonical empty state |
| `NULL` | 1 | 1 | no | Positive capacity/size without storage |
| address `A` | 3 | 4 | yes, assuming adequate owned allocation | `size <= capacity` |
| address `A` | 5 | 4 | no | More logical elements than slots |
| address `A` | 0 | 4 | yes, assuming adequate owned allocation | Empty logical list with reserved storage |

The fields alone cannot prove that `A` is live, suitably aligned, large
enough, uniquely owned, or that slots in `[0, size)` contain initialized
logical values.

Invariant:

- `size <= capacity`;
- zero capacity implies `data == NULL` and zero size under the course representation;
- positive capacity implies adequate uniquely owned storage;
- logical elements occupy `[0, size)`.

### E. Operation contracts

| Operation | Valid request | State change | Cost | Failure |
|---|---|---|---:|---|
| `get` | `index < size`, output nonnull | Output only | `O(1)` | List/output unchanged |
| append, spare capacity | Valid list | Writes then increments size | `O(1)` | List unchanged |
| append, growth | Valid/representable request | May move data; capacity and size grow | `O(n)` worst case | Entire list unchanged |
| insert | `index <= size` | May grow; shifts suffix right | `O(n)` | Entire list unchanged |
| remove | `index < size` | Shifts suffix left; decrements size | `O(n)` | Entire list/output unchanged |

### F. Safe ordering

1. validate;
2. ensure capacity;
3. write at old `size`;
4. increment `size`.

Failure must preserve `data`, all logical values, `size`, and `capacity`. A temporary pointer prevents loss of the old allocation address when `realloc` returns `NULL`.

### G. Costs

| Operation | Cost |
|---|---:|
| `get` | `O(1)` |
| append with space | `O(1)` |
| one growth append | `O(n)` |
| append amortized under geometric growth | `O(1)` |
| insert/remove at front | `O(n)` |

Amortized `O(1)` describes average cost over a long sequence; some individual growth appends copy `n` elements.

### H. Linked preview

Field: `next`.

| Comparison | ArrayList | Linked nodes |
|---|---|---|
| Layout | Contiguous block | Separate linked objects |
| Indexed access | `O(1)` | `O(n)` |
| Local insert after known position | Shifts later elements | Link change can be `O(1)` |
| Pointer risk | Stale aliases after growth | Broken links, leaks, dangling pointers |

## Cognitive Pause calibration

Starting state: `A`, size `3`, capacity `4`, `[11,22,33,_]`.

After `44`:

- address `A`;
- size `4`;
- capacity `4`;
- values `[11,22,33,44]`;
- `alias` still refers to live allocation `A`.

Before appending `55`:

- `size == capacity`, so growth is required;
- no out-of-bounds write has occurred.

After successful moving growth:

- address `B`;
- capacity `8` under doubling;
- values `[11,22,33,44,55]` followed by spare slots;
- size `5`;
- old `alias` must not be dereferenced.

If growth fails:

- address remains `A`;
- size remains `4`;
- capacity remains `4`;
- values remain `[11,22,33,44]`;
- original aliases remain valid because the old allocation remains live.

The invariant holds at entry and every return/externally visible state. Internal candidate state is not committed until success.

## Segfault Autopsy criteria

A complete response identifies:

- direct assignment can discard the only old pointer when a `realloc`-style call returns `NULL`;
- capacity is updated despite failed allocation;
- the subsequent write dereferences `NULL` or invalid storage;
- doubling zero remains zero;
- capacity and byte multiplication may overflow;
- post-increment can change `size` despite a failed/invalid write;
- the repair computes checked capacity/bytes, uses a temporary pointer, commits only after success, writes only after reserve, and increments size last;
- regression tests include forced allocation failure and zero/near-limit capacity behavior.

## Exit-ticket answers

1. Valid access: `index < size`.
2. Successful moving growth may invalidate old `data` and every address
   inside its former allocation.
3. Failed growth preserves pointer, logical values, size, and capacity.
4. Append worst case: `O(n)`; amortized with geometric growth: `O(1)`.
5. A node can store addresses of child objects to express hierarchy; allowing
   several relationship records per vertex generalizes the idea to graph
   adjacency independent of physical location.
6. Open questions vary and should be used for Module 2 entry support.
