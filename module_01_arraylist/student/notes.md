# Student Notes — ArrayList and Linked-Node Preview

## Essential question

> How can a fixed block of C memory behave like a collection that grows, and what trade-offs change when elements are stored in separately allocated nodes?

## 1. The problem

A C array has a fixed allocation. A program that collects authentication events may not know in advance how many events will arrive.

Three unsafe responses are:

- write beyond the allocation;
- silently discard data without a stated policy;
- lose earlier values while trying to grow.

An ArrayList solves the representation problem by keeping a contiguous allocation plus explicit metadata.

```c
typedef struct {
    int *data;
    size_t size;
    size_t capacity;
} IntList;
```

- `data` is the address of the owned element allocation.
- `size` is the number of logical elements.
- `capacity` is the number of allocated element slots.

`capacity` is not a valid-index boundary for clients. Clients may read only indexes below `size`.

## 2. Representation invariant

A valid course `IntList` satisfies:

1. `size <= capacity`.
2. If `capacity == 0`, then `data == NULL` and `size == 0`.
3. If `capacity > 0`, then `data != NULL` and owns storage for at least `capacity` integers.
4. Logical elements occupy exactly `[0, size)`.
5. The allocation has one documented cleanup responsibility.

An invariant must hold before and after every publicly visible operation. During an operation, temporary state may exist, but a failure must return the object to a valid, usable state.

## 3. Core operation contracts

| Operation | Success condition | Effect | Failure effect |
|---|---|---|---|
| `int_list_init` | `list != NULL` | Creates the canonical empty state | No object is modified |
| `int_list_get` | Valid list, output pointer, `index < size` | Copies one value to the output | List and output remain unchanged |
| `int_list_reserve` | Valid list and representable request | Ensures `capacity >= requested`; never changes `size` | Entire prior list remains unchanged |
| `int_list_append` | Growth succeeds if needed | Writes at old `size`, then increments `size` | Entire prior list remains unchanged |
| `int_list_destroy` | `NULL` or a valid initialized/destroyed list | Frees owned storage and resets all fields | Passing `NULL` is a no-op |

Extension contracts:

- `insert` accepts `index <= size`.
- `remove` requires `index < size`.
- Removal does not shrink capacity in this module.

Lifecycle and ownership preconditions:

- initialize only an uninitialized or previously destroyed object;
- reinitializing a live list loses its allocation because `init` cannot
  discover that ownership portably;
- never pass arbitrary or uninitialized storage to `destroy`;
- never shallow-copy the struct, because both copies would appear to own the
  same allocation;
- a nonnull output pointer for `get` or `remove` must not point inside the
  list allocation.

## 4. Checked growth

Course growth begins at capacity four and then doubles geometrically.

Pseudocode:

```text
reserve(list, required):
    reject an invalid list

    if required <= capacity:
        succeed

    reject a required capacity that cannot fit in size_t bytes

    new_capacity = capacity, or 4 when capacity is zero

    while new_capacity < required:
        double when doubling is safe
        otherwise use required directly

    candidate = realloc(data, new_capacity * element_size)

    if candidate is NULL:
        fail with data, size, capacity, and values unchanged

    data = candidate
    capacity = new_capacity
    succeed
```

### Why a temporary pointer matters

Unsafe:

```c
list->data = realloc(list->data, new_bytes);
```

If `realloc` fails, it returns `NULL` and leaves the old allocation valid. The direct assignment loses the only saved address of that old allocation.

Safer:

```c
int *candidate = realloc(list->data, new_bytes);
if (candidate == NULL) {
    return INT_LIST_ERR_ALLOCATION;
}

list->data = candidate;
list->capacity = new_capacity;
```

The operation commits representation fields only after success.

## 5. Pointer stability

`realloc` may extend an allocation in place or move it. Correct code cannot assume either outcome.

After a successful growth, these may be stale:

- the previous value of `list->data`;
- `&list->data[0]`;
- any other saved pointer into the old allocation.

Use an index across a potentially growing call, then reacquire the address afterward.

The same non-alias rule applies to output parameters. For example, do not pass
`&list.data[k]` as `out_value`; a mutating operation could shift or relocate
that storage while also trying to write the result.

## 6. Operation costs

| Operation | Cost | Reason |
|---|---:|---|
| `get(index)` | `O(1)` | Address calculated directly |
| Append with spare capacity | `O(1)` | One write |
| One append that grows | `O(n)` | Existing elements may be copied |
| Long sequence of geometric-growth appends | amortized `O(1)` each | Total copying over the sequence is linear |
| Insert/remove near the front | `O(n)` | Later elements shift |
| Destroy | `O(1)` for an integer ArrayList | One allocation is released |

Amortized `O(1)` does not mean every append is constant time. It describes the average cost across a sequence under a geometric growth policy.

## 7. Linked-node preview

A singly linked node stores a value and the address of the next node:

```c
typedef struct Node {
    int value;
    struct Node *next;
} Node;
```

Nodes need not be adjacent in memory.

| Question | ArrayList | Linked nodes |
|---|---|---|
| Physical layout | One contiguous element block | Separate objects connected by addresses |
| Indexed access | `O(1)` | `O(n)` traversal |
| Local insertion after a known node | Requires shifting | Link change can be `O(1)` |
| Allocation behavior | Occasional larger reallocation | Usually one allocation per node |
| Locality | Usually strong | Usually weaker |
| Common pointer risk | Stale aliases after growth | Broken links, leaks, dangling pointers |

Neither representation is universally best. Choose from the required operations and workload.

## 8. Security and reliability connection

An ArrayList that passes bounds tests can still be unsafe if:

- capacity multiplication overflows;
- growth is unbounded and exhausts memory;
- allocation failure corrupts the object;
- stale pointers are reused after movement;
- cleanup is omitted.

The data structure enforces representation safety. The application must separately define retention limits, rejection, sampling, or backpressure.

## 9. Vocabulary

- **allocation:** a block of storage obtained from an allocator;
- **logical element:** a value currently belonging to the list;
- **capacity:** allocated element slots;
- **ownership:** responsibility for releasing a resource;
- **invariant:** a condition that must be true in every valid observable state;
- **failure atomicity:** an operation either completes or leaves the previous valid state unchanged;
- **stale pointer:** an address that no longer refers to a live intended object;
- **amortized analysis:** average cost across a sequence, accounting for occasional expensive operations.
