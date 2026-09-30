# Technical Notes — Module 4 Integer Stack and Postfix Evaluation

## Source and teaching boundary

The current teaching source is `student/lab.c`. One global `int stack[10]`
holds operator character codes during conversion, then numeric values during
evaluation. Each phase resets global `top` and reuses that same storage.
The older caller-owned `int_stack_*` and checked `expression_evaluate` library
under `code/include`, `code/starter`, and `code/solution` is an optional legacy
comparison with different contracts and tests.

```c
int stack[10];
int capacity = 10;
int top = -1;
char eq[8] = "1-2*3+4";
char postfix[8] = "";
char eq_paren[8] = "1+(2+3)";
```

## The forward representation and exact operations

With `capacity == 10`, valid caller-maintained state satisfies
`-1 <= top < capacity`. The active prefix is indexes 0 through `top`;
the nonempty top is `stack[top]`. `top` records the last active index; `top + 1` is both the active count and
next insertion index. Logical bottom-to-top order follows increasing indexes.
Popping leaves old bits in an inactive cell.

| Operation | Source behavior | Caller precondition |
|---|---|---|
| `is_full()` | returns `top + 1 == capacity` | state is valid |
| `push(int data)` | `stack[++top] = data` | room remains in the array |
| `is_empty()` | returns `top == -1` | state is valid |
| `peek()` | returns integer `stack[top]` | `top >= 0` |
| `pop()` | returns integer `stack[top--]` | `top >= 0` |

The predicates do not guard the operations. A full push writes outside the
ten-cell array; empty peek/pop read index -1. These calls have undefined
behavior, not a promised no-op or special empty-read result. Keep them as paper
diagnoses and exercise predicates/valid transitions in tests. `capacity`
changes the full predicate only; it does not resize storage or stop push.

## One Stack, two expression phases, and a local cursor

The PPT first motivates the algorithm through a direct calculation with
conceptual operator and value Stacks. For incoming `+` in `1-2*3+4`, calculate
`2*3 = 6`, then `1-6 = -5`, before saving `+`. Reading 4 and performing the
last addition gives -1. Recording this calculation order gives `123*-4+`.
The lab separates conversion and evaluation so it can reuse one array.

| State | Meaning |
|---|---|
| `stack[10]`, global `top` | operators and any opening parentheses in conversion; numeric operands/results in evaluation |
| `eq[8]` | up to seven plain infix characters and a terminator |
| `eq_paren[8]` | up to seven infix characters, including balanced parentheses, and a terminator |
| `postfix[8]`, local conversion cursor `pos` | postfix output; `pos` advances for every write, including the terminator |

## Phase 1: infix to postfix

Conversion initializes local `pos = 0` and resets `top = -1`.
`convert_to_postfix()` scans `eq[i]` until the null terminator. Digits go
straight to `postfix`. The operator loop checks `!is_empty()` before
`peek()`. It breaks when `prec(op) < prec(c)`; otherwise it pops to output.
Equality does not break, preserving left associativity. The incoming
operator is pushed after the loop.

`prec` uses `switch`: grouped `case` labels for `* / %` return 2, grouped
labels for `+ -` return 1, and `default` returns 0. Each branch returns
immediately. Conversion's `break` exits the nearest operator loop; it does
not exit the enclosing input scan. No bottom sentinel is stored.

| Read/work | Visible postfix | Stack, bottom to top | `top` | `pos` |
|---|---|---|---:|---:|
| reset to empty | empty | empty | -1 | 0 |
| `1` | `1` | empty | -1 | 1 |
| `-` | `1` | `-` | 0 | 1 |
| `2` | `12` | `-` | 0 | 2 |
| `*` | `12` | `-`, `*` | 1 | 2 |
| `3` | `123` | `-`, `*` | 1 | 3 |
| `+`: pop `*`, pop `-`, push `+` | `123*-` | `+` | 0 | 5 |
| `4` | `123*-4` | `+` | 0 | 6 |
| drain `+` | `123*-4+` | empty | -1 | 7 |
| write terminator | `123*-4+` terminated | empty | -1 | 8 |

After draining `+`, the Stack is empty with `top == -1` and `pos == 7`.
The separate `postfix[pos++] = '\0'` writes the terminator at index 7 and
advances `pos` to 8; token length remains 7. `pos` is local and cannot be read by
the driver after return. Repeated supported conversions reset `top` and
`pos`; shorter valid strings terminate at their actual output length.

## Phase 2: postfix evaluation

Evaluation resets `top = -1` and processes `postfix[i]` while it is not
`'\0'`. Digits become numbers through `push(c - '0')`. Each operator pops
right operand `num2` first, then left operand `num1`, and pushes
`calc(num1, num2, c)`. All pops read `stack[top]` before decrementing `top`.

| Token | Active `stack`, bottom to top | `top` | Calculation |
|---|---|---:|---|
| `1` | 1 | 0 | digit |
| `2` | 1, 2 | 1 | digit |
| `3` | 1, 2, 3 | 2 | digit |
| `*` | 1, 6 | 1 | `2 * 3 = 6` |
| `-` | -5 | 0 | `1 - 6 = -5` |
| `4` | -5, 4 | 1 | digit |
| `+` | -1 | 0 | `-5 + 4 = -1` |
| final `pop()` | empty | -1 | return -1 |

The terminator at index 7 is excluded. Integer storage preserves negative
or multidigit intermediate values; no separate local value array exists.

## Grouped input through the dedicated converter

`infix_to_postfix_parentheses()` resets `pos = 0` and `top = -1`, then
reads `eq_paren` until `'\0'`. An opening `(` is pushed as a precedence-0
boundary. An ordinary incoming operator breaks its reduction loop when `(`
is on top. At `)`, the loop first checks nonempty, then pops into `op`.
If `op == '('`, `break` stops the loop after removing that opening
parenthesis. Otherwise the popped operator is emitted.

For `1+(2+3)`, after the first three characters the Stack contains outer
`+` and `(`, with `top == 1` and output `1`. The inner `+` is pushed above
`(`; after `3`, output is `123` and `top == 2`. Reading `)` emits the inner
`+` and pops `(`, leaving outer `+` with `top == 0`. The final drain emits
outer `+`, leaving `top == -1` and `pos == 5`. The separate terminator
assignment writes `postfix[5] = '\0'` and leaves `pos == 6`. Evaluation
returns 6 and empties the Stack.

Neither parenthesis belongs to valid postfix output. An unmatched `)` can
be silently consumed after draining operators; the nonempty guard prevents
conversion from popping an empty Stack. An unmatched `(` can be written
into the output. Balanced groups with valid contents remain a precondition,
and evaluation still has no operand-count guard.

## Input assumptions and unchecked cases

Core runs require a nonempty valid expression of at most seven input
characters followed by `'\0'` within its eight-cell buffer. Shorter valid
expressions are supported. Use single digits and binary `+ - * / %` operators.
Only the dedicated converter accepts parentheses, and they must be balanced.
There are no spaces, unary operators, or multi-digit operands. Divisors must
be nonzero and intermediate results representable as C `int`. Integer `/`
truncates toward zero; `%` is the corresponding remainder operation.

These are caller assumptions. Conversion guards its reads with
`!is_empty()`, but does not reject unsupported characters or unbalanced
groups. Unsupported characters can enter postfix output. The input
terminator is excluded by each scan condition. Missing operands can
underflow evaluation; extra operands have no final-count check. Output
bounds, zero divisors, and signed overflow are not validated. The primitive
Stack operations do not enforce their own preconditions. Discuss proposed
validation as extensions and keep unsupported runs out of normal tests.

## Costs and storage

Valid push, peek, and pop do constant work, `O(1)`, without shifting. Each
input character is scanned once and each waiting operator is pushed/popped at
most once, giving `O(n)` conversion and evaluation for the generalized
algorithm. This source bounds input length by seven characters and reserves fixed
storage, `O(1)`. Parentheses add scanning and Stack operations, but each
opening parenthesis is pushed and popped once, so the total remains linear.
A generalized postfix buffer would need space proportional to input length.

## Stack-Top Autopsy — instructor only

The isolated fixture has ten characters:

```text
index:   0  1  2  3  4  5  6  7  8  9
stack:   +  *  ?  ?  ?  ?  ?  ?  ?  ?
top: 1
```

The active prefix is indexes 0 and 1. Correct `stack[top]` reads `'*'`;
faulty `stack[top + 1]` reads `'?'` at inactive index 2. Both accesses are
inside the array in this fixture. At full capacity, the faulty expression
would read out-of-bounds `stack[10]`. Here the first broken rule is logical membership,
so a clean memory-sanitizer result cannot establish correctness. Preserve the
student's prediction before revealing this comparison. Keep these specific
answers out of the Stage D diagram release.

## Build and evidence

From `code`, run `make lab-demo` and `make lab-tests`, or use
`powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 -Target lab`
and `-Target lab-tests`. The demonstration links the current student source;
the tests exercise that same source. Record actual output rather than reusing
the legacy eight-core/five-extension totals.

Use warning-enabled C11 builds and supported sanitizers. The source's empty
parameter lists can trigger strict-prototype warnings; explain the diagnostic
and the C11 spelling `(void)` without silently changing the canonical source.
Integer-to-character assignments can also trigger narrowing warnings.
A clean valid-input run establishes evidence within the stated assumptions,
not a checked parser contract.
