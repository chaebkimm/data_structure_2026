# Stage C — Investigation Worksheet: Character Stack and Expressions

Name: ____________________________  
Date: ____________________________

Open this file after completing and preserving the Cognitive Pause. The core
is Sections A through F. Preserve these responses before opening Stage D.
Sections G and H may be completed during the independent-work window.

## Quick reference

A Stack follows last in, first out (LIFO). In the global `char stack[10]`,
empty means `top == 10`, full means `top == 0`, and active items occupy
indexes `top` through 9. The nonempty top is `stack[top]`. Item count is
`10 - top`. The global `size` counts postfix characters instead.

## A. Trace the canonical characters

Start empty. Write logical states from bottom to top, not in increasing
physical index order. `push` has no return value.

| Request | Return | Logical state after request | New `top` | Item count |
|---|---|---|---:|---:|
| start | none | empty | 10 | 0 |
| `push('A')` | | | | |
| `push('B')` | | | | |
| `push('C')` | | | | |
| `peek()` | | | | |
| `pop()` | | | | |
| `pop()` | | | | |
| `pop()` | | | | |

1. What is the greatest item count reached?
2. Which physical index stores `'C'` after the third push?
3. Why does `peek()` leave `'C'` present?
4. In what order do the three pops report characters?

Response:

____________________________________________________________________

## B. Apply the operation contracts

A contract states what a function accepts, changes, returns, and preserves.
The lab functions use shared global state; callers do not pass arrays or
receive a replacement size.

| Operation | Successful steps and return | Boundary result | What is preserved at the boundary? |
|---|---|---|---|
| `push(char data)` | | full: no return value | |
| `peek()` | | empty: `'\0'` | |
| `pop()` | | empty: `'\0'` | |

1. Why must `push` decrease `top` before writing?
2. Why must `pop` save the character before increasing `top`?
3. After a pop, does the old character disappear from physical storage?
4. What makes that former top cell inactive?
5. What ambiguity would appear if `'\0'` were used as an ordinary data item?

Response:

____________________________________________________________________

## C. Check empty and full boundaries

Consider each row independently. Assume valid `top` values at entry.

| Starting state and request | Return | Final `top` | Array changed? |
|---|---|---:|---|
| empty (`top == 10`); `peek()` | | | |
| empty (`top == 10`); `pop()` | | | |
| ten active characters (`top == 0`); `push('K')` | | | |
| A, B bottom to top (`top == 8`); `pop()` | | | |

1. Which attempted write would occur if a full push lacked its guard?
2. Which attempted read would occur if empty peek lacked its guard?
3. The global `capacity` is set to 3 while the array still has ten cells.
   Does the current `is_full()` or `is_empty()` change behavior? Inspect
   the actual expressions in `lab.c` and explain.
4. Why must callers avoid assigning arbitrary values outside `0..10` to
   the global `top`? Do the equality checks validate every invalid index?

Response:

____________________________________________________________________

## D. Transfer the rule in two phases

Use `1-2*3+4`. Start with an empty operator Stack. The input assumptions are:
a nonempty alternating sequence of single digits and `+`, `-`, `*`, `/`, or
`%`; at most seven characters plus `'\0'`; no spaces, parentheses, unary
signs, or multi-digit operands; nonzero divisors; and arithmetic within `int`.
These assumptions are not input validation implemented by the current code.

### D1. Convert infix to postfix

Digits go directly to `postfix`. Before pushing an operator, pop waiting
operators of equal or greater precedence into the output. List the operator
Stack bottom to top. No integer calculation happens in this phase.

| Event | Operator Stack | `top` | Postfix prefix | `size` |
|---|---|---:|---|---:|
| start | empty | 10 | empty | 0 |
| read `1` | | | | |
| read `-` | | | | |
| read `2` | | | | |
| read `*` | | | | |
| read `3` | | | | |
| read `+` | | | | |
| read `4` | | | | |
| drain operators and terminate output | | | | |

Why are both `*` and `-` removed when `+` arrives? Why does `'\0'` not
increase `size`? What prevents an earlier conversion's output from being
appended to on a second valid call?

Response:

____________________________________________________________________

### D2. Evaluate the postfix result

`values[10]` is a local integer array. `pos` counts its active prefix and
starts at 0. List numeric values bottom to top.

| Postfix event | Integer values | `pos` after token | Calculation |
|---|---|---:|---|
| read `1` | | | |
| read `2` | | | |
| read `3` | | | |
| read `*` | | | |
| read `-` | | | |
| read `4` | | | |
| read `+` | | | |

State the final returned integer. Why does `values[pos++] = c - '0'` store
numbers rather than character codes? Why is `num2` popped before `num1`?
Which expression locates the top of this numeric Stack before a pop?

Response:

____________________________________________________________________

### D3. Separate assumptions from checks

For each case, classify it as within the exercise's input assumptions or
outside them. Give the result only for valid cases. Do not claim that an
unsupported input is safely rejected, and do not run it as a normal test.

| Input | Within assumptions? | Result, if valid | Reason |
|---|---|---:|---|
| `"7"` | | | |
| `"1-2*3+4"` | | | |
| `"8/2/2"` | | | |
| `"7%4+1"` | | | |
| `""` | | | |
| `"1+"` | | | |
| `"12+3"` | | | |
| `"1 +2"` | | | |
| `"(1+2)"` | | | |
| `"1/0"` | | | |
| more than seven input characters | | | |

Name checks a future general-purpose evaluator would need for malformed
input, zero divisors, and integer overflow. Which of these checks are absent
from this `lab.c`?

Response:

____________________________________________________________________

## E. Distinguish a physical slot from a logical item

Consider this deliberately prepared array with `top == 8`:

```c
char stack[10] = {'?', '?', '?', '?', '?', '?', '?', '?', '*', '+'};
```

1. Which indexes are active? Which are inactive?
2. Which character is the correct top?
3. What does the faulty expression `stack[top - 1]` read?
4. Why is that read inside the array but outside the logical Stack?
5. Which expression reads the correct top?
6. How could a wrong operator change a later expression calculation even if
   the faulty read leaves `top` unchanged?

Response:

____________________________________________________________________

## F. Connect cost to fixed storage

Let `n` be the number of valid expression tokens. `O(1)` means fixed work;
`O(n)` means work grows in proportion to `n`.

| Work | Cost | Reason |
|---|---:|---|
| Successful or boundary `push` | | |
| Successful or empty `peek` | | |
| Successful or empty `pop` | | |
| Infix-to-postfix conversion | | |
| Postfix evaluation | | |
| Storage with the current fixed arrays | | |

Why does no character Stack operation shift existing items? Why does the
conversion's inner pop loop still permit linear total work on valid input?
How does the fixed maximum of seven tokens limit the examples you can run?

Response:

____________________________________________________________________

## G. Separate three uses of “stack”

The Stack ADT is a behavior rule. The runtime call stack commonly holds
bookkeeping for active function calls. This lab's global `char stack[10]` is
one array representation of the ADT. The local `int values[10]` is another.

1. Does storing `'A'` in the global array create a real C call frame?
2. Does naming an array `stack` make it obey LIFO automatically?
3. Which functions enforce LIFO for the global character array?
4. How do the active regions and index directions differ between `stack`
   and `values`?

Response:

____________________________________________________________________

## H. Exit ticket

1. Where is the top of the nonempty character Stack?
2. State LIFO in your own words.
3. Distinguish `peek` from `pop`.
4. What is returned and preserved after empty peek?
5. What is preserved after a full push?
6. Distinguish `top`, `size`, and `pos`.
7. State the expression input assumptions and one unchecked limitation.
8. State one question you still have.

Response:

____________________________________________________________________
