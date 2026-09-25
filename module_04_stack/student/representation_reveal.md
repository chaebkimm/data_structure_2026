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
item from an empty Stack. The functions in `lab.c` return `'\0'` in that case.
This is a character result, not a separate success flag.

## 2. Store characters in a global fixed array

The current [lab.c](lab.c) declares:

```c
char stack[10];
int capacity = 10;
int top = 10;
```

These objects are global: the functions share one array and one top index.
The inquiry used function IDs 100, 200, and 300. The C lab uses character
labels `'A'`, `'B'`, and `'C'` to illustrate the same return order. Storing a
label does not create a real C function call.

This representation grows toward smaller indexes:

- `top == 10` means empty; do not read `stack[10]`.
- `top == 0` means full.
- When nonempty, `stack[top]` holds the top item.
- Active items occupy indexes `top` through 9; indexes below `top` are inactive.
- The item count is `10 - top`.
- If there is room, the next push writes at `top - 1`, after decreasing `top`.

`capacity` describes the intended ten positions, but the current operations
use the literal `10`. Changing `capacity` alone does not resize the array or
change their boundaries. The global `size` introduced later counts postfix
characters; it does not count items in this Stack.

## 3. State the invariant and operation behavior

An **invariant** is a rule that remains true in every valid completed state:

```text
0 <= top <= 10
active indexes: top through 9, or none when top == 10
```

| Operation | Successful behavior | Boundary behavior |
|---|---|---|
| `push(data)` | Decrease `top`, then write `stack[top]`; no return value | If full, return without changing `top` or the array |
| `peek()` | Return `stack[top]`; change nothing | If empty, return `'\0'`; change nothing |
| `pop()` | Read `stack[top]`, increase `top`, return the saved character | If empty, return `'\0'`; change nothing |

Pop leaves the old character in memory. The new `top` makes that cell
inactive. These checks assume `top` already satisfies the invariant; they do
not repair arbitrary changes to the global index.

## 4. Trace the canonical function labels

Logical states below are written bottom to top. Physical array indexes run
in the other direction: after three pushes, `'A'` is at 9, `'B'` at 8, and
`'C'` at 7.

| Request | Return | Logical state, bottom to top | `top` | Item count |
|---|---|---|---:|---:|
| start | none | empty | 10 | 0 |
| `push('A')` | none | A | 9 | 1 |
| `push('B')` | none | A, B | 8 | 2 |
| `push('C')` | none | A, B, C | 7 | 3 |
| `peek()` | `'C'` | A, B, C | 7 | 3 |
| `pop()` | `'C'` | A, B | 8 | 2 |
| `pop()` | `'B'` | A | 9 | 1 |
| `pop()` | `'A'` | empty | 10 | 0 |

## 5. Transfer the rule in two phases

The lab first converts **infix**, where operators appear between operands,
into **postfix**, where an operator follows its two operands:

```text
1-2*3+4  →  123*-4+  →  -1
  infix      postfix    result
```

`infix_to_postfix()` uses the global character Stack for waiting operators.
Digits go directly to `postfix`. `*`, `/`, and `%` have precedence 2; `+` and
`-` have precedence 1. Waiting operators of equal or greater precedence move
to the output before the incoming operator is pushed. This preserves left
associativity: equal-precedence operators are applied from left to right.

`eval_postfix()` then uses a separate local `int values[10]`. Its `pos` is a
count that grows upward. Digits become numbers with `c - '0'`. For an
operator, the right operand `num2` is removed before the left operand `num1`.
`calc(num1, num2, c)` computes the result, which is put back into `values`.

For this exercise, provide a nonempty alternating sequence of single digits
and `+`, `-`, `*`, `/`, or `%`, at most seven characters in `infix[8]`. Use no
spaces, parentheses, unary signs, or multi-digit operands. Divisors must be
nonzero and all arithmetic must fit `int`. Begin conversion with the operator
Stack empty. These are input assumptions: the current code does not validate
malformed input, zero divisors, or integer overflow.

## 6. Prepare for the Cognitive Pause

Make sure you can trace `'A'`, `'B'`, and `'C'`; locate `stack[top]`; explain
full and empty behavior; and distinguish conversion from evaluation. Open
`vocabulary.md` only after preserving the five-minute response.

One question:

____________________________________________________________________
