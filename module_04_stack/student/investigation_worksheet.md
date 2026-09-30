# Stage C — Investigation Worksheet: Integer Stack and Expressions

Name: ____________________________  
Date: ____________________________

Open this file after completing and preserving the Cognitive Pause. The core
is Sections A through F. Preserve these responses before opening Stage D.
Sections G and H may be completed during the independent-work window.

## Quick reference

A Stack follows last in, first out (LIFO). In the global `int stack[10]`,
empty means `top == -1`, full means `top == 9`, and active items occupy
indexes 0 through `top`. The nonempty top is `stack[top]`. Item count is
`top + 1`. Conversion uses local `pos` as its output cursor. Both phases reuse the same
Stack and global `top`, resetting `top` to -1 at entry.

## A. Trace the canonical characters

Start empty. Write logical states from bottom to top, following increasing
physical index order. `push` has no return value.

| Request | Return | Logical state after request | New `top` | Item count |
|---|---|---|---:|---:|
| start | none | empty | -1 | 0 |
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
receive a replacement top index.

| Operation | Steps and return for a valid call | Caller precondition | Invalid index if precondition fails |
|---|---|---|---|
| `push(int data)` | | | |
| `peek()` | | | |
| `pop()` | | | |

1. Why must `push` increase `top` before writing `stack[top]`?
2. Why does `pop` read `stack[top]` before decreasing `top`?
3. After a pop, does the old character disappear from physical storage?
4. What makes that former top cell inactive?
5. Why can a stored integer `0` be a real item even though `is_empty()` is false?

Response:

____________________________________________________________________

## C. Check empty and full boundaries

Consider each row independently. The predicates report state; push, peek,
and pop have no guards. Diagnose invalid accesses on paper without running them.

| Starting state | Predicate result | Allowed next operation | Index an invalid call would select |
|---|---|---|---|
| empty (`top == -1`); consider peek | | | |
| empty (`top == -1`); consider pop | | | |
| full (`top == 9`); consider push | | | |
| A, B bottom to top (`top == 1`); valid pop | | | |

1. Which index would full push write? Is a no-op guaranteed?
2. Which index would empty peek/pop read? Is a special empty-read result guaranteed?
3. If global `capacity` is set to 3, what does `is_full()` report at
   `top == 2`? Does `push` consult that predicate or resize the array?
4. Why must callers maintain `-1 <= top < 10`? Do equality predicates
   validate every corrupted top index?

Response:

____________________________________________________________________

## D. Transfer the rule in two phases

Use `1-2*3+4` first. Inputs must be nonempty valid expressions of at most
seven characters plus a terminator within the eight-cell buffer. Use
single-digit operands and binary `+ - * / %` operators. The plain converter
reads `eq`; the dedicated parentheses converter reads `eq_paren` and accepts
balanced groups. Both write `postfix`, and all scans stop at `'\0'`.
No spaces, unary signs, or multi-digit operands are supported. Divisors must
be nonzero and arithmetic must fit `int`. These are assumptions, not validation
checks. Both phases reset global `top = -1` at entry.

### D1. Convert infix to postfix

Digits go directly to `postfix`. Before pushing an operator, pop waiting
operators of equal or greater precedence into the output. List the operator
Stack bottom to top, starting empty with `top = -1` and local `pos = 0`.
Check `!is_empty()` before peeking; break when the waiting operator has
lower precedence. No arithmetic happens in this phase.

| Event | Operator Stack | `top` | Postfix prefix | `pos` |
|---|---|---:|---|---:|
| reset to empty | empty | -1 | empty | 0 |
| read `1` | | | | |
| read `-` | | | | |
| read `2` | | | | |
| read `*` | | | | |
| read `3` | | | | |
| read `+` | | | | |
| read `4` | | | | |
| drain final operator | | | | |
| write explicit terminator | | | | |

Why are both `*` and `-` removed when `+` arrives? How do `!is_empty()`
and the lower-precedence `break` stop the operator loop? Why does the
explicit terminator write increase `pos` from 7 to 8 while `top` stays -1?
What resets on a second valid call?

Response:

____________________________________________________________________

### D2. Evaluate the postfix result

`eval_postfix()` resets `top = -1` and reuses global `int stack[10]`,
starting empty. List numeric values bottom to top.

| Postfix event | Integer values | `top` after token | Calculation |
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

### D3. Trace a grouped expression

Use `eq_paren = "1+(2+3)"` with `infix_to_postfix_parentheses()`.
Record the operator Stack, `top`, output prefix, and `pos` after each
character, after the final drain, and after the explicit terminator write.
An opening `(` is pushed. At `)`, the loop checks for a nonempty Stack,
then pops into `op`. If `op == '('`, it breaks without writing the item;
otherwise it emits that operator and continues.

1. Why does the inner `+` remain above `(` until the closing parenthesis?
2. Why are neither `(` nor `)` present in the postfix output?
3. What are the final output, its token length, terminator index, and `top`?
4. What does `eval_postfix()` return, and what is `top` afterward?

Response:

____________________________________________________________________

### D4. Separate assumptions from checks

For each case, classify it as within the exercise's input assumptions or
outside them. Specify the converter and give the result only for valid cases.
Do not claim that an unsupported input is safely rejected, and do not run
it as a normal test.

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
| `"(1+2"` | | | |
| `"1/0+2*3"` | | | |
| more than seven input characters | | | |

Name checks a future general-purpose evaluator would need for malformed
input, zero divisors, and integer overflow. Which of these checks are absent
from this `lab.c`?

Response:

____________________________________________________________________

## E. Distinguish a physical slot from a logical item

Consider this deliberately prepared array with `top == 1`:

```c
int stack[10] = {'+', '*', '?', '?', '?', '?', '?', '?', '?', '?'};
```

1. Which indexes are active? Which are inactive?
2. Which character is the correct top?
3. What does the faulty expression `stack[top + 1]` read?
4. Why is that read inside the array but outside the logical Stack?
5. Which expression reads the correct top?
6. How could a wrong operator change a later expression calculation even if
   the faulty read leaves `top` unchanged?

Response:

____________________________________________________________________

## F. Connect cost to fixed storage

Let `n` count the characters read by a phase, including input parentheses
during conversion and excluding the terminator. `O(1)` means fixed work;
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
Why do the null-terminated loops now accept shorter valid expressions?

Response:

____________________________________________________________________

## G. Separate three uses of “stack”

The Stack ADT is a behavior rule. The runtime call stack commonly holds
bookkeeping for active function calls. This lab's global `int stack[10]` is
one array representation of the ADT, reused for both expression phases.

1. Does storing `'A'` in the global array create a real C call frame?
2. Does naming an array `stack` make it obey LIFO automatically?
3. Which functions enforce LIFO for the global integer array?
4. How does the meaning of active items change between conversion and evaluation?

Response:

____________________________________________________________________

## H. Exit ticket

1. Where is the top of the nonempty integer Stack?
2. State LIFO in your own words.
3. Distinguish `peek` from `pop`.
4. Which predicate must a caller consult before an empty peek?
5. Why must a caller avoid full push?
6. Distinguish shared global `top`, conversion-local `pos`, and token length.
7. State the expression input assumptions and one unchecked limitation.
8. State one question you still have.

Response:

____________________________________________________________________
