# Stage B — Formal Name and Stored Form

Open this file only after preserving the Stage A inquiry.

## 1. Name the access rule

An **abstract data type (ADT)** describes a collection by the operations it
allows and the rules those operations follow. It does not require one
particular way to store the collection.

A **Stack ADT** allows access at one end only. That accessible end is the
**top**. Its access rule is **last in, first out (LIFO)**: the item added most
recently is the first item that may be removed.

The three central operations are:

- **push:** add one item at the top;
- **peek:** inspect the top item without removing it; and
- **pop:** remove the top item and report it.

An **empty Stack** contains no items. It has no top item. **Underflow** is an
attempt to `peek` or `pop` when the Stack is empty. Checked operations report
underflow instead of reading invalid storage.

## 2. Store characters in an ArrayList backend

A **character** is one symbol such as `(` or `A`. C uses the type `char` for
a character. An **ArrayList** is a resizable numbered sequence. A
**backend** is the lower-level storage used to implement an ADT.

This module uses an ArrayList-backed character Stack:

```c
typedef struct {
    char *data;
    size_t size;
    size_t capacity;
    size_t limit;
} CharStack;
```

Read this C only for the field meanings; there is no need to memorize the
syntax yet.

- A **struct** groups named values called **fields**.
- A **pointer** stores a memory address. `char *data` stores the address of
  the ArrayList's character storage.
- `size_t` is a nonnegative whole-number C type used for counts and indexes.
- `size` is the number of characters currently in the Stack.
- `capacity` is the number of character slots currently reserved in memory.
- `limit` is the greatest permitted Stack size for this task.
- An **index** is a numbered position. C begins indexes at zero.

When `size > 0`, the top item is:

```text
data[size - 1]
```

The bottom item is at `data[0]`. A **client** is a program part that uses the
Stack. Clients use Stack operations; they do not index `data` directly. This
separation lets the access rule stay the same if the backend later changes.

## 3. State the valid-storage rules

**State** is the information currently stored. An **invariant** is a rule
that is true in every valid completed state. A valid course `CharStack`
satisfies:

1. `size <= capacity`.
2. `capacity <= limit <= 1024`.
3. If `capacity == 0`, then `data == NULL` and `size == 0`.
4. If `capacity > 0`, then `data` identifies storage for at least `capacity`
   characters.
5. Current Stack items occupy exactly `data[0]` through
   `data[size - 1]`.
6. If `size > 0`, `data[size - 1]` is the top item.
7. If `size == 0`, there is no top item.

`NULL` is a pointer value meaning “no storage address.” Rule 5 describes no
indexes when `size == 0`.

The **nesting limit** is the maximum number of unresolved openings the
delimiter checker permits. The later timed activity uses limit 2. A push that
would make `size` greater than the stated limit is rejected before the state
changes.

## 4. Trace the three operations

The following state lists items from bottom to top. This example uses
ordinary characters so the later delimiter task remains yours to solve.

| Request | Reported item | State from bottom to top |
|---|---|---|
| start | none | empty |
| `push('X')` | none | `X` |
| `push('Y')` | none | `X`, `Y` |
| `peek` | `Y` | `X`, `Y` |
| `pop` | `Y` | `X` |

After the two pushes, `size` is 2 and `data[size - 1]` is `Y`. `peek`
reports `Y` but leaves it present. `pop` reports the same item and removes
it, exposing `X`.

## 5. Check closing delimiters

A **validator** is a procedure that checks stated rules. A **procedure** is
a named sequence of steps. The delimiter validator reads left to right:

1. Ignore ordinary characters.
2. For an opening delimiter, push it. If the push would exceed the nesting
   limit, report a depth-limit error without changing the Stack.
3. For a closing delimiter, request `peek`.
   - If it reports underflow, report an **unmatched closing delimiter**.
   - Otherwise, use the reported top opening.
4. If the top opening is not the partner of the closing delimiter, report a
   **mismatch** without popping it.
5. If they match, pop the opening.
6. After the final input character, accept only if the Stack is empty.
   A nonempty Stack contains a **leftover opening delimiter**.

The matching pairs are `(` with `)`, `[` with `]`, and `{` with `}`.

## 6. Prepare for the Cognitive Pause

Make sure you can read a bottom-to-top state list, locate
`data[size - 1]`, and apply the six general rules to new input. Do not open
`vocabulary.md` until the five-minute individual response has been completed
and preserved.

One question:

____________________________________________________________________
