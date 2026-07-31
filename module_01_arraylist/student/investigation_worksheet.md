# Investigation Worksheet — Invariants, Operations, and Trade-offs

Name: ____________________________  
Date: ____________________________

Open this file after completing and preserving the Cognitive Pause.

## D. Valid and invalid states

For this table only, assume address `A` is live, uniquely owned, and points to
an allocation large enough for the stated capacity. For each state, mark valid
or invalid and explain.

| `data` | `size` | `capacity` | Valid? | Reason |
|---|---:|---:|---|---|
| `NULL` | 0 | 0 | | |
| `NULL` | 1 | 1 | | |
| address `A` | 3 | 4 | | |
| address `A` | 5 | 4 | | |
| address `A` | 0 | 4 | | |

Without the assumption above, what facts about address `A` cannot be proven
from the three field values alone?

____________________________________________________________________

Write the full invariant:

____________________________________________________________________

____________________________________________________________________

## E. Operation contracts

| Operation | Valid index/request | State changed | Work as list grows | Failure behavior |
|---|---|---|---|---|
| `get` | | | | |
| append with spare capacity | — | | | |
| append requiring growth | — | | | |
| insert | | | | |
| remove | | | | |

## F. Growth ordering

Number these append steps in a safe order:

___ increment `size`  
___ ensure capacity  
___ write the value at the old `size`  
___ validate the list/request

What must stay unchanged when growth fails?

____________________________________________________________________

Why is a temporary pointer used with `realloc`?

____________________________________________________________________

## G. Complexity

| Operation | Worst-case cost | Explanation |
|---|---:|---|
| `get` | | |
| append with spare capacity | | |
| one append that grows | | |
| geometric-growth append, amortized | | |
| insert at front | | |
| remove at front | | |

In one sentence, explain why “amortized `O(1)`” does not mean “every append is
`O(1)`.”

____________________________________________________________________

## H. Linked-node preview

Complete:

```c
typedef struct Node {
    int value;
    struct Node *____________;
} Node;
```

| Comparison | ArrayList | Linked nodes |
|---|---|---|
| Physical layout | | |
| Indexed access | | |
| Local insertion after a known position | | |
| Major pointer risk | | |

## I. Exit ticket

1. A valid element access requires `index __________________________`.
2. After successful moving growth, a saved pointer into the old allocation is
   __________________________.
3. A failed reserve operation must preserve _________________________.
4. One append can cost __________, while append is amortized __________ under
   geometric growth.
5. An ArrayList uses one contiguous block. Explain how separately linked
   objects can represent a hierarchy now and arbitrary graph relationships
   later:

   _________________________________________________________________

6. One question you still have:

____________________________________________________________________
