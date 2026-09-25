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
int size = 0;
```

These objects are global: the functions share one array and its item count.
The inquiry used function IDs 100, 200, and 300. The C lab uses character
labels `'A'`, `'B'`, and `'C'` to illustrate the same return order. Storing a
label does not create a real C function call.

This representation grows toward larger indexes:

- `size == 0` means empty; no top item exists.
- `size == capacity` means full (10 items in this lab).
- When nonempty, `stack[size - 1]` holds the top item.
- Active items occupy indexes 0 through `size - 1`; indexes from `size` through 9 are inactive.
- The item count is `size`.
- If there is room, the next push writes at `size`, then increases `size`.

`capacity` is initialized to 10 and is used by the full check. The array
still has exactly ten cells; changing a variable cannot resize that array.
Conversion later uses a separate local output cursor `pos`; evaluation reuses
this same array and `size` for numeric values.

## 3. State the invariant and operation behavior

An **invariant** is a rule that remains true in every valid completed state:

```text
0 <= size <= capacity
active indexes: 0 through size - 1, or none when size == 0
```

| Operation | Successful behavior | Boundary behavior |
|---|---|---|
| `push(int data)` | Write `stack[size++]`; no return value | Caller must ensure room |
| `peek()` | Return integer `stack[size - 1]`; change nothing | Caller must ensure nonempty |
| `pop()` | Decrease `size`, then return integer `stack[size]` | Caller must ensure nonempty |

Pop leaves the old character in memory. The new `size` makes that cell
inactive. The full/empty predicates only report state; they are not guards
inside these operations. A full push or empty peek/pop accesses outside the
array and has undefined behavior, with no promised result or preserved state.

## 4. Trace the canonical function labels

Logical states below are written bottom to top. Physical array indexes run
in the same direction: after three pushes, `'A'` is at 0, `'B'` at 1, and
`'C'` at 2. The next free position is `size == 3`.

| Request | Return | Logical state, bottom to top | `size` | Item count |
|---|---|---|---:|---:|
| start | none | empty | 0 | 0 |
| `push('A')` | none | A | 1 | 1 |
| `push('B')` | none | A, B | 2 | 2 |
| `push('C')` | none | A, B, C | 3 | 3 |
| `peek()` | `'C'` | A, B, C | 3 | 3 |
| `pop()` | `'C'` | A, B | 2 | 2 |
| `pop()` | `'B'` | A | 1 | 1 |
| `pop()` | `'A'` | empty | 0 | 0 |

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

`infix_to_postfix()` uses the global integer Stack for waiting operators.
Digits go directly to `eq_re`. `*`, `/`, and `%` have precedence 2; `+` and
`-` have precedence 1. Waiting operators of equal or greater precedence move
to the output before the incoming operator is pushed. This preserves left
associativity: equal-precedence operators are applied from left to right.

Conversion first resets `size`, initializes local `pos = 0`, and pushes
`'\0'`. That stored sentinel has lower precedence than supported operators,
so the operator-pop loop stops before the Stack becomes empty. After exactly
seven input characters, the final drain includes this sentinel: it writes
`eq_re[7] = '\0'`, leaves `size == 0`, and advances `pos` to 8.

`eval_postfix()` resets `size = 0` and reuses the same `int stack[10]` for
numeric operands/results, without a sentinel. Digits become numbers with
`c - '0'`. At an operator, pop right operand `num2` before left operand
`num1`, then push `calc(num1, num2, c)`. The seven-token loop excludes the
terminator. Its final `pop()` returns -1 and leaves `size == 0`.

Provide exactly seven characters: four single digits alternating with three
`+ - * / %` operators, plus a terminator in `eq[7]`. Use no spaces,
parentheses, unary signs, or multi-digit operands. Divisors must be nonzero
and arithmetic must fit `int`. Shorter expressions are unsupported. The
current source assumes these conditions without validating them.

## 6. Prepare for the Cognitive Pause

Make sure you can trace `'A'`, `'B'`, and `'C'`; locate `stack[size - 1]`; explain
full and empty behavior; and distinguish conversion from evaluation. Open
`vocabulary.md` only after preserving the five-minute response.

One question:

____________________________________________________________________
