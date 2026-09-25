# Technical Notes — Module 4 Character Stack and Postfix Evaluation

## Source and teaching boundary

The current teaching source is `student/lab.c`. It uses a global, fixed
character Stack, converts infix text to postfix text, then evaluates that
postfix text with a separate local integer array. Treat these as two phases.
The older caller-owned `int_stack_*` and checked `expression_evaluate` library
under `code/include`, `code/starter`, and `code/solution` is an optional legacy
comparison. Its contracts and test results do not describe `student/lab.c`.

```c
char stack[10];
int capacity = 10;
int size = 0;
```

The declared `capacity` is initialized to 10 and controls the full check.
The array declaration still fixes the allocation at ten cells; changing
`capacity` does not resize it. Use character labels
`'A'`, `'B'`, and `'C'` for its canonical trace.

## The forward representation

For states reached through the Stack operations:

```text
0 <= size <= capacity
active indexes:       0 through size - 1, when size > 0
inactive indexes:     size through 9, when size < 10
top item:             stack[size - 1], only when size > 0
number of items:      size
next push position:   size, only when size < capacity
empty:                size == 0
full:                 size == capacity
```

`size` is both the next insertion index and the active item count. At full
capacity its value 10 is not an array element. Bottom-to-top logical order
runs from index 0 through `size - 1`. An old character can remain in an
inactive cell after pop.

The implementation guards ordinary empty and full requests. It does not
validate arbitrary externally corrupted `size` values; the invariant is a
precondition on shared state. Reset `size` to 0 before an independent Stack
experiment and begin conversion with an empty operator Stack.

## Exact operation behavior

| Operation | Ordinary success | Boundary behavior |
|---|---|---|
| `is_full()` | reports whether `size == capacity` | reads state only |
| `push(char data)` | writes `stack[size]`, then increments `size` | at full, returns without changing state; return type is `void` |
| `is_empty()` | reports whether `size == 0` | reads state only |
| `peek()` | returns `stack[size - 1]`; changes nothing | at empty, returns `'\0'`; changes nothing |
| `pop()` | decrements `size`, reads `stack[size]`, returns that character | at empty, returns `'\0'`; changes nothing |

There are no output pointers and no returned size. The null character is a
sentinel for an empty read. If a caller intentionally pushes `'\0'`, the
return alone cannot distinguish that stored character from empty; use
`is_empty()` to establish state. The core examples store visible characters.

Full must be checked before writing: `stack[10]` is outside the array.
Empty must be checked before peek selects `size - 1` or pop decreases `size`:
otherwise the index would be -1.

## Three arrays, three meanings of position

| State | Meaning | Direction of growth |
|---|---|---|
| `stack[10]`, `size` | waiting character operators; global `size` is the next insertion index and count | toward larger indexes |
| `postfix[8]`, global `postfix_size` | output characters; `postfix_size` excludes the terminator | toward larger indexes |
| local `values[10]`, `size` | numeric operands/results; `size` is their current count | toward larger indexes |

Do not call global `postfix_size` the character Stack size. Both Stacks use the
same next-free convention, but their `size` variables are separate. The
local `value_size` hides global `size` inside `eval_postfix()`; its current number
is at `values[value_size - 1]` when the local count is positive.

## Phase 1: infix to postfix

`infix_to_postfix()` resets `postfix_size` to zero, scans to the input's `'\0'`,
appends digits directly, and uses the character Stack for waiting operators.
Before pushing an incoming operator, it appends every waiting operator whose
precedence is greater than or equal to that operator's precedence. The `>=`
comparison preserves left associativity, including for subtraction and
division. End of input drains waiting operators. `postfix[postfix_size] = '\0'`
terminates the text without increasing `postfix_size`.

`prec` returns 1 for `+` and `-`, 2 for `*`, `/`, and `%`, and 0 otherwise.
For valid operators, an empty `peek()` returns `'\0'` with lower precedence,
so reduction stops. This is not a general input-validation check.

| Read/work | Postfix so far | Operators, bottom to top | `size` | `postfix_size` |
|---|---|---|---:|---:|
| start | empty | empty | 0 | 0 |
| `1` | `1` | empty | 0 | 1 |
| `-` | `1` | `-` | 1 | 1 |
| `2` | `12` | `-` | 1 | 2 |
| `*` | `12` | `-`, `*` | 2 | 2 |
| `3` | `123` | `-`, `*` | 2 | 3 |
| `+`: pop `*`, pop `-`, push `+` | `123*-` | `+` | 1 | 5 |
| `4` | `123*-4` | `+` | 1 | 6 |
| drain `+` | `123*-4+` | empty | 0 | 7 |

The eighth output position holds the terminator. A second valid conversion
starts with `postfix_size = 0`; the preceding conversion has emptied the operator
Stack. Explicit termination also removes stale suffix text when the new
expression is shorter.

## Phase 2: postfix evaluation

`eval_postfix()` starts a fresh local `values[10]` and `value_size = 0`. A digit
becomes a number through `c - '0'`. For each operator:

1. `values[--value_size]` gives the right operand, saved as `num2`;
2. the next `values[--value_size]` gives the left operand, saved as `num1`;
3. `calc(num1, num2, c)` computes in that order; and
4. `values[value_size++]` stores the result and increases the count.

| Token | Active numbers, bottom to top | `value_size` | Calculation |
|---|---|---:|---|
| `1` | 1 | 1 | digit |
| `2` | 1, 2 | 2 | digit |
| `3` | 1, 2, 3 | 3 | digit |
| `*` | 1, 6 | 2 | `2 * 3 = 6` |
| `-` | -5 | 1 | `1 - 6 = -5` |
| `4` | -5, 4 | 2 | digit |
| `+` | -1 | 1 | `-5 + 4 = -1` |

The loop processes `postfix_size` tokens, excluding `'\0'`. The final return reads
the remaining number. Integers, including negative intermediate results, stay
in `values`; they are not stored in the character Stack.

## Input assumptions and unchecked cases

Core runs assume a nonempty expression of at most seven characters, with
single digits alternating with `+`, `-`, `*`, `/`, or `%`. There are no spaces,
parentheses, unary operators, or multi-digit operands. Divisors must be
nonzero and intermediate results must be representable as C `int`. Integer
`/` truncates toward zero; `%` is the corresponding remainder operation.

These are caller assumptions, not checks that the source performs. In
particular:

- an unsupported character has precedence zero and can cause the conversion
  loop to keep popping an empty Stack and write beyond the output array;
- missing operands or empty input can make evaluation read before `values`;
- extra operands are not rejected by a final-count check;
- division/remainder by zero and signed overflow are not checked; and
- output and numeric pushes have no independent capacity checks.

Describe proposed validation and checked arithmetic as extensions. Do not
promise a rejected-input result, status return, or preserved output parameter
that this source does not provide. Keep unsafe cases as paper diagnoses in
the core lesson; run supplied valid-input and Stack-boundary tests.

## Costs and storage

Push, peek, and pop do constant work, `O(1)`, without shifting. In conversion,
each input character is scanned once and each operator is pushed/popped at
most once. Evaluation scans each postfix token once. Thus both phases are
`O(n)` in token count. The current buffers impose a seven-character input
limit and fixed reserved storage, `O(1)` for this program. A generalized
postfix buffer would need space proportional to expression length.

## Stack-Top Autopsy — instructor only

The isolated fixture has ten characters:

```text
index:   0  1  2  3  4  5  6  7  8  9
stack:   +  *  ?  ?  ?  ?  ?  ?  ?  ?
size: 2
```

The active prefix is indexes 0 and 1. Correct `stack[size - 1]` reads `'*'`;
faulty `stack[size]` reads `'?'` at inactive index 2. Both accesses are
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
`-Wshadow` also reports the local `value_size` hiding the global `size`; these remain
separate objects for the integer and character Stacks.
A clean valid-input run establishes evidence within the stated assumptions,
not a checked parser contract.
