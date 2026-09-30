# Stage B — Formal Name and Stored Form

Open this file only after preserving the Stage A inquiry.

## 1. Name the access rule

An **abstract data type (ADT)** describes a collection by its allowed
operations and rules. A **Stack ADT** permits access at one end, the **top**.
Its rule is **last in, first out (LIFO)**: the item most recently added is the
first item that may be removed.

- `push` adds one item at the top.
- `peek` reports the top without removing it.
- `pop` removes and reports the top.

An empty Stack has no top. **Underflow** means asking to inspect or remove an
item from an empty Stack. The functions in `lab.c` do not check for it:
callers must ensure a top exists before calling peek or pop.

## 2. Store integers in a global fixed array

The current [lab.c](lab.c) declares:

```c
int stack[10];
int capacity = 10;
int top = -1;
```

These objects are global: the functions share one array and its top index.
The inquiry used function IDs 100, 200, and 300. The C lab uses character
labels `'A'`, `'B'`, and `'C'` to illustrate the same return order. Storing a
label does not create a real C function call.

This representation grows toward larger indexes:

- `top == -1` means empty; no top item exists.
- `top + 1 == capacity` means full (10 items in this lab).
- When nonempty, `stack[top]` holds the top item.
- Active items occupy indexes 0 through `top`; indexes from `top + 1` through 9 are inactive.
- The item count is `top + 1`.
- If there is room, the next push increases `top`, then writes at that index.

`capacity` is initialized to 10 and is used by the full check. The array
still has exactly ten cells; changing a variable cannot resize that array.
Conversion later uses a separate local output cursor `pos`; evaluation reuses
this same array and `top` for numeric values.

## 3. State the invariant and operation behavior

An **invariant** is a rule that remains true in every valid completed state:

```text
-1 <= top < capacity
active indexes: 0 through top, or none when top == -1
```

| Operation | Successful behavior | Boundary behavior |
|---|---|---|
| `push(int data)` | Write `stack[++top]`; no return value | Caller must ensure room |
| `peek()` | Return integer `stack[top]`; change nothing | Caller must ensure nonempty |
| `pop()` | Read integer `stack[top]`, then decrease `top` and return the value | Caller must ensure nonempty |

Pop leaves the old character in memory. The new `top` makes that cell
inactive. The full/empty predicates only report state; they are not guards
inside these operations. A full push or empty peek/pop accesses outside the
array and has undefined behavior, with no promised result or preserved state.

## 4. Trace the canonical function labels

Logical states below are written bottom to top. Physical array indexes run
in the same direction: after three pushes, `'A'` is at 0, `'B'` at 1, and
`'C'` at 2. The top index is `top == 2`; the next free position is `top + 1 == 3`.

| Request | Return | Logical state, bottom to top | `top` | Item count |
|---|---|---|---:|---:|
| start | none | empty | -1 | 0 |
| `push('A')` | none | A | 0 | 1 |
| `push('B')` | none | A, B | 1 | 2 |
| `push('C')` | none | A, B, C | 2 | 3 |
| `peek()` | `'C'` | A, B, C | 2 | 3 |
| `pop()` | `'C'` | A, B | 1 | 2 |
| `pop()` | `'B'` | A | 0 | 1 |
| `pop()` | `'A'` | empty | -1 | 0 |

## 5. Transfer the rule in two phases

The PPT first uses two Stacks to calculate directly: one holds waiting
operators and the other holds numbers. In `1-2*3+4`, `+` triggers `2*3 = 6`
and then `1-6 = -5` before `+` is stored. After 4 arrives, the final addition
gives -1. Writing operators at those calculation times gives postfix order.

The lab first converts **infix**, where operators appear between operands,
into **postfix**, where an operator follows its two operands:

```text
1-2*3+4  →  123*-4+  →  -1
  infix      postfix    result
```

`convert_to_postfix()` uses the global integer Stack for waiting operators.
Digits go directly to `postfix`. `*`, `/`, and `%` have precedence 2; `+` and
`-` have precedence 1. Waiting operators of equal or greater precedence move
to the output before the incoming operator is pushed. This preserves left
associativity: equal-precedence operators are applied from left to right.

Conversion starts with `top = -1` and local `pos = 0`. It reads `eq[i]`
until the input terminator. Its operator loop checks `!is_empty()` before
`peek()`. If the waiting operator has lower precedence, `break` exits that
loop; otherwise it is popped to output. Equal precedence is emitted first.
The final drain empties the Stack, then `postfix[pos++] = '\0'` terminates
the output. For `1-2*3+4`, `pos` advances from 7 to 8 at that final write,
while `top` stays -1. No sentinel is pushed.

`eval_postfix()` resets `top = -1` and reuses the same `int stack[10]` for
numeric operands/results. Digits become numbers with `c - '0'`. At an
operator, pop right operand `num2` before left operand `num1`, then push
`calc(num1, num2, c)`. The loop stops before the output terminator. For the
canonical expression, its final `pop()` returns -1 and leaves `top == -1`.

A separate function, `infix_to_postfix_parentheses()`, reads `eq_paren`
and writes to the same `postfix`. It pushes `(` as a boundary. At `)`, a
nonempty loop pops each item first. If that item is `(`, `break` leaves the
loop without writing it; otherwise the operator is written. With
`eq_paren = "1+(2+3)"`, conversion produces `123++`, then explicitly writes
the terminator at index 5. It ends with `pos == 6` and `top == -1`.
Evaluation returns 6.

Provide a nonempty valid expression of at most seven characters and its
terminator within the eight-cell buffer. Single-digit operands use binary
`+ - * / %` operators. The plain converter accepts no parentheses; the
dedicated converter accepts balanced groups. Shorter expressions such as
`7` and `1+2` work because the loops stop at `'\0'`. Use no spaces, unary
signs, or multi-digit operands. Divisors must be nonzero and arithmetic must
fit `int`. The source assumes these conditions without validating them.

## 6. Prepare for the Cognitive Pause

Make sure you can trace `'A'`, `'B'`, and `'C'`; locate `stack[top]`; explain
full and empty behavior; and distinguish conversion from evaluation. Open
`vocabulary.md` only after preserving the five-minute response.

One question:

____________________________________________________________________
