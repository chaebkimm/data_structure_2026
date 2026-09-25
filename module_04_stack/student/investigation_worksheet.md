# Stage C — Investigation Worksheet: Integer Stack and Expressions

Name: ____________________________  
Date: ____________________________

Open this file after completing and preserving the Cognitive Pause. The core
is Sections A through F. Preserve these responses before opening Stage D.
Sections G and H may be completed during the independent-work window.

## Quick reference

A Stack follows last in, first out (LIFO). In the global `int stack[10]`,
empty means `size == 0`, full means `size == 10`, and active items occupy
indexes 0 through `size - 1`. The nonempty top is `stack[size - 1]`. Item count is
`size`. Conversion uses local `pos` as its output cursor. Both phases reuse the same
Stack and global `size`, resetting that count at entry.

## A. Trace the canonical characters

Start empty. Write logical states from bottom to top, following increasing
physical index order. `push` has no return value.

| Request | Return | Logical state after request | New `size` | Item count |
|---|---|---|---:|---:|
| start | none | empty | 0 | 0 |
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

| Operation | Steps and return for a valid call | Caller precondition | Invalid index if precondition fails |
|---|---|---|---|
| `push(int data)` | | | |
| `peek()` | | | |
| `pop()` | | | |

1. Why must `push` write at `size` before increasing it?
2. Why does `pop` decrease `size` before reading `stack[size]`?
3. After a pop, does the old character disappear from physical storage?
4. What makes that former top cell inactive?
5. Why can a stored `'\0'` be a real item even though `is_empty()` is false?

Response:

____________________________________________________________________

## C. Check empty and full boundaries

Consider each row independently. The predicates report state; push, peek,
and pop have no guards. Diagnose invalid accesses on paper without running them.

| Starting state | Predicate result | Allowed next operation | Index an invalid call would select |
|---|---|---|---|
| empty (`size == 0`); consider peek | | | |
| empty (`size == 0`); consider pop | | | |
| full (`size == 10`); consider push | | | |
| A, B bottom to top (`size == 2`); valid pop | | | |

1. Which index would full push write? Is a no-op guaranteed?
2. Which index would empty peek/pop read? Is a sentinel result guaranteed?
3. If global `capacity` is set to 3, what does `is_full()` report at
   `size == 3`? Does `push` consult that predicate or resize the array?
4. Why must callers maintain `0 <= size <= 10`? Do equality predicates
   validate every corrupted count?

Response:

____________________________________________________________________

## D. Transfer the rule in two phases

Use `1-2*3+4`. Inputs must have exactly seven characters: four single digits
alternating with three `+ - * / %` operators, plus `'\0'` in `eq[7]`.
No spaces, parentheses, unary signs, or multi-digit operands are supported.
Divisors must be nonzero and arithmetic must fit `int`. These are assumptions,
not validation checks. Both phases reset global `size` at entry.

### D1. Convert infix to postfix

Digits go directly to `eq_re`. Before pushing an operator, pop waiting
operators of equal or greater precedence into the output. List the operator
Stack bottom to top, including the bottom `'\0'` sentinel pushed after
resetting `size`. Local `pos` starts at 0. No arithmetic happens in this phase.

| Event | Operator Stack | `size` | Postfix prefix | `pos` |
|---|---|---:|---|---:|
| reset, then push sentinel | `'\0'` | 1 | empty | 0 |
| read `1` | | | | |
| read `-` | | | | |
| read `2` | | | | |
| read `*` | | | | |
| read `3` | | | | |
| read `+` | | | | |
| read `4` | | | | |
| drain final operator | | | | |
| drain sentinel and terminate output | | | | |

Why are both `*` and `-` removed when `+` arrives? Why does the stored
sentinel stop that loop? Why does its final write increase `pos` to 8
although there are seven tokens? What resets on a second valid call?

Response:

____________________________________________________________________

### D2. Evaluate the postfix result

`eval_postfix()` resets `size = 0` and reuses global `int stack[10]`,
without a sentinel. List numeric values bottom to top.

| Postfix event | Integer values | `size` after token | Calculation |
|---|---|---:|---|
| read `1` | | | |
| read `2` | | | |
| read `3` | | | |
| read `*` | | | |
| read `-` | | | |
| read `4` | | | |
| read `+` | | | |

State the final returned integer. Why does `push(c - '0')` store
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
| `"8/2/2+1"` | | | |
| `"7%4+1*2"` | | | |
| `""` | | | |
| `"1+"` | | | |
| `"12+3"` | | | |
| `"1 +2"` | | | |
| `"(1+2)"` | | | |
| `"1/0+2*3"` | | | |
| more than seven input characters | | | |

Name checks a future general-purpose evaluator would need for malformed
input, zero divisors, and integer overflow. Which of these checks are absent
from this `lab.c`?

Response:

____________________________________________________________________

## E. Distinguish a physical slot from a logical item

Consider this deliberately prepared array with `size == 2`:

```c
int stack[10] = {'+', '*', '?', '?', '?', '?', '?', '?', '?', '?'};
```

1. Which indexes are active? Which are inactive?
2. Which character is the correct top?
3. What does the faulty expression `stack[size]` read?
4. Why is that read inside the array but outside the logical Stack?
5. Which expression reads the correct top?
6. How could a wrong operator change a later expression calculation even if
   the faulty read leaves `size` unchanged?

Response:

____________________________________________________________________

## F. Connect cost to fixed storage

Let `n` be the number of valid expression tokens. `O(1)` means fixed work;
`O(n)` means work grows in proportion to `n`.

| Work | Cost | Reason |
|---|---:|---|
| Valid `push` | | |
| Nonempty `peek` | | |
| Nonempty `pop` | | |
| Infix-to-postfix conversion | | |
| Postfix evaluation | | |
| Storage with the current fixed arrays | | |

Why does no integer Stack operation shift existing items? Why does the
conversion's inner pop loop still permit linear total work on valid input?
Why do the fixed seven-iteration loops exclude shorter expressions?

Response:

____________________________________________________________________

## G. Separate three uses of “stack”

The Stack ADT is a behavior rule. The runtime call stack commonly holds
bookkeeping for active function calls. This lab's global `int stack[10]` is
one array representation of the ADT, reused for both expression phases.

1. Does storing `'A'` in the global array create a real C call frame?
2. Does naming an array `stack` make it obey LIFO automatically?
3. Which functions enforce LIFO for the global character array?
4. How does the meaning of active items change between conversion and evaluation?

Response:

____________________________________________________________________

## H. Exit ticket

1. Where is the top of the nonempty integer Stack?
2. State LIFO in your own words.
3. Distinguish `peek` from `pop`.
4. Which predicate must a caller consult before an empty peek?
5. Why must a caller avoid full push?
6. Distinguish shared global `size`, conversion-local `pos`, and token length.
7. State the expression input assumptions and one unchecked limitation.
8. State one question you still have.

Response:

____________________________________________________________________
