# Module 1 Memory Models

Every visual below has a text equivalent so students may use a diagram, structured table, tactile representation, or verbal description.

## 1. Empty valid list

```mermaid
flowchart LR
    L["IntList<br/>data = NULL<br/>size = 0<br/>capacity = 0"]
```

Text equivalent:

| Object | Field | Value | Meaning |
|---|---|---:|---|
| `IntList` | `data` | `NULL` | No allocation is owned |
| `IntList` | `size` | `0` | No logical elements |
| `IntList` | `capacity` | `0` | No allocated element slots |

## 2. Partially occupied allocation

```mermaid
flowchart LR
    L["IntList<br/>data = A<br/>size = 3<br/>capacity = 4"] --> A["one contiguous allocation A<br/>[0]=11 | [1]=22 | [2]=33 | [3]=unused"]
```

Text equivalent:

| Index | `0` | `1` | `2` | `3` |
|---|---:|---:|---:|---|
| Slot | `11` | `22` | `33` | unused |
| Logical element? | yes | yes | yes | no |

Valid indexes are `0` through `size - 1`. Capacity describes allocated slots, not initialized logical elements.

## 3. Full list before growth

```mermaid
flowchart LR
    L["IntList<br/>data = A<br/>size = 4<br/>capacity = 4"] --> A["one contiguous allocation A<br/>[0]=11 | [1]=22 | [2]=33 | [3]=44"]
```

An append cannot write index `4` yet. Index `4` is one past the four-slot allocation.

## 4. Failure-atomic growth

```mermaid
flowchart TD
    S["Old valid state<br/>data = A, size = 4, capacity = 4"]
    C["Compute checked new capacity and byte count"]
    R["candidate = realloc(A, bytes)"]
    F{"candidate == NULL?"}
    K["Keep A, size, capacity, and contents unchanged<br/>return allocation error"]
    M["Commit data = candidate<br/>commit capacity = 8"]
    W["Write value at data[4]<br/>then set size = 5"]
    S --> C --> R --> F
    F -- yes --> K
    F -- no --> M --> W
```

The important idea is **commit after success**. A failed append must leave the previous valid list usable.

## 5. Successful moving growth

Before:

| Field | Value |
|---|---|
| `data` | address `A` |
| `size` | `4` |
| `capacity` | `4` |
| elements | `[11, 22, 33, 44]` |

After appending `55`, if allocation moves:

| Field | Value |
|---|---|
| `data` | new address `B` |
| `size` | `5` |
| `capacity` | at least `5`; course policy normally produces `8` |
| elements | `[11, 22, 33, 44, 55, unused, unused, unused]` |

An alias such as `int *alias = &list.data[1]` pointed inside allocation `A`. If growth moves storage to `B`, `alias` is stale and must not be dereferenced. Reacquire the location as `&list.data[1]`.

## 6. Linked-node preview

```mermaid
flowchart LR
    H["head"] --> N1["Node<br/>value = 11"]
    N1 --> N2["Node<br/>value = 22"]
    N2 --> N3["Node<br/>value = 33"]
    N3 --> X["NULL"]
```

Text equivalent:

| Logical position | Object | Stored value | Link |
|---:|---|---:|---|
| 0 | node at address `P` | `11` | address `Q` |
| 1 | node at address `Q` | `22` | address `R` |
| 2 | node at address `R` | `33` | `NULL` |

Linked nodes need not be physically adjacent. They avoid moving all later elements during a local link change, but they give up direct index arithmetic and add pointer/ownership risks. Full linked-list implementation returns in Module 14.

## 7. Representation invariant

A valid course `IntList` satisfies all of the following:

1. `size <= capacity`.
2. If `capacity == 0`, then `data == NULL` and `size == 0`.
3. If `capacity > 0`, then `data != NULL` and owns storage for at least `capacity` integers.
4. Logical elements occupy exactly indexes `[0, size)`.
5. The list has one cleanup responsibility for the owned allocation.
