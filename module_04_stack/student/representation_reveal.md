# Stage B — Formal Name and Stored Form

Open this file only after preserving the Stage A inquiry.

## 1. Name the access rule

An **abstract data type (ADT)** describes a collection by its allowed
operations and rules. It does not require one storage method.

A **Stack ADT** allows access at one end, called the **top**. Its rule is
**last in, first out (LIFO)**: the item added most recently is the first item
that may be removed.

- `push` adds one item at the top.
- `peek` reports the top item without removing it.
- `pop` removes and reports the top item.

An empty Stack has no top. **Underflow** is a request to `peek` or `pop` an
empty Stack. The checked functions reject underflow without changing a
caller-provided output value.

## 2. Store integer values in a fixed array

This module uses a caller-owned array of ten integers:

```c
int stack[10];
int size = 0;
int capacity = 10;
```

The **caller** is the code that creates the array and asks a function to use
it. Caller-owned means the Stack functions borrow the array; they do not
create, resize, release, or copy it.

The array stores generic integer data. Function IDs 100, 200, and 300 are the
canonical example, but the same operations can store other integers.

- `size` is the number of logical items currently in the Stack.
- `capacity` is the number of prepared array positions.
- Logical items occupy indexes 0 through `size - 1`.
- Positions from `size` through `capacity - 1` are allocated but inactive.
- When `size > 0`, the top is `stack[size - 1]`.
- When `size < capacity`, `stack[size]` is the next unused position.

## 3. State the valid rules

An **invariant** is a rule that is true in every valid completed state.

```text
0 <= size <= capacity
```

The caller must also pass the capacity that matches the prepared array. The
functions can check the two numbers, but they cannot discover the physical
length of an array received through a function parameter.

A rejected operation preserves observable information:

- rejected `push` returns the original size and changes no array cell;
- rejected `peek` returns 0 and leaves its output unchanged; and
- rejected `pop` returns the original size and leaves its output unchanged.

Successful `peek` returns 1. Successful `pop` reports the former top and
returns `size - 1`. Pop does not need to erase the newly inactive position.
For `peek` and `pop`, the caller must provide output storage separate from the
Stack array.

## 4. Trace the canonical function IDs

List states from bottom to top.

| Request | Function return | Output value | State | `size` |
|---|---:|---:|---|---:|
| start | none | none | empty | 0 |
| `push(100)` | 1 | none | 100 | 1 |
| `push(200)` | 2 | none | 100, 200 | 2 |
| `push(300)` | 3 | none | 100, 200, 300 | 3 |
| `peek` | 1 | 300 | 100, 200, 300 | 3 |
| `pop` | 2 | 300 | 100, 200 | 2 |
| `pop` | 1 | 200 | 100 | 1 |
| `pop` | 0 | 100 | empty | 0 |

The inactive array cells may still contain old integer bits. They are not
Stack items because `size` excludes them.

## 5. Transfer the rule to `1+2*3`

An expression evaluator can use a fixed integer Stack for numbers and a fixed
character Stack for operators. `*` has higher precedence than `+`, so `2*3`
is completed before the waiting addition. The result is 7.

The transfer exercise accepts only a nonempty alternating sequence of one
digit and one operator. The only operators are `+` and `*`. It accepts no
spaces, parentheses, unary operators, or multi-digit numbers. Each internal
Stack has ten positions, and each push checks for available space. Input
length is not otherwise capped. Any malformed input, full internal Stack, or
integer overflow is rejected, and the caller's result remains unchanged.

## 6. Prepare for the Cognitive Pause

Make sure you can trace 100, 200, and 300; locate `stack[size - 1]`; and state
what a rejected operation preserves. Do not open `vocabulary.md` until the
five-minute response has been completed and preserved.

One question:

____________________________________________________________________
