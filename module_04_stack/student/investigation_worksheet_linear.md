# Stage C — Investigation: Linear Accessible Format

This version has the same questions and learning targets as the standard
investigation. No response table or drawing is required. Use a screen reader,
keyboard, speech input, or text-only response as needed.

Open this file after preserving the Cognitive Pause. Complete and preserve
Sections A through F before opening Stage D. Sections G and H may be completed
during the independent-work window.

## Quick reference

A Stack follows last in, first out (LIFO). The global `char stack[10]` is
empty at `top == 10` and full at `top == 0`. Active indexes run from `top`
through 9. The nonempty top is `stack[top]`, and item count is `10 - top`.
The global `size` counts postfix characters instead.

## A. Trace the canonical characters

Start empty. For each request, record the return, bottom-to-top logical
state, new `top`, and item count. `push` has no return value.

1. `push('A')`.
2. `push('B')`.
3. `push('C')`.
4. `peek()`.
5. `pop()`.
6. `pop()`.
7. `pop()`.

Then answer:

1. What is the greatest item count reached?
2. Which physical index stores `'C'` after the third push?
3. Why does `peek()` leave `'C'` present?
4. In what order do the three pops report characters?

Response:

## B. Apply the operation contracts

A contract states what a function accepts, changes, returns, and preserves.
These functions share global state; callers pass no array and receive no
replacement size.

For `push(char data)`, `peek()`, and `pop()`, state the successful steps and
return, the boundary result, and the state preserved at that boundary. Full
push has no return value; empty peek and pop return `'\0'`.

Then answer:

1. Why must `push` decrease `top` before writing?
2. Why must `pop` save the character before increasing `top`?
3. Does the old character disappear from storage after a pop?
4. What makes the former top cell inactive?
5. What ambiguity would appear if `'\0'` were an ordinary data item?

Response:

## C. Check empty and full boundaries

For each independent case, state its return, final `top`, and whether the
array changes. Assume valid `top` at entry.

1. Empty (`top == 10`); call `peek()`.
2. Empty (`top == 10`); call `pop()`.
3. Ten active characters (`top == 0`); call `push('K')`.
4. A, B bottom to top (`top == 8`); call `pop()`.

Then answer:

1. Which attempted write would occur if full push lacked its guard?
2. Which attempted read would occur if empty peek lacked its guard?
3. Set global `capacity` to 3 while retaining the ten-cell array. Does the
   current `is_full()` or `is_empty()` change behavior? Inspect `lab.c`.
4. Why avoid assigning global `top` outside `0..10`? Do equality checks
   validate every invalid index?

Response:

## D. Transfer the rule in two phases

Use `1-2*3+4` and an empty operator Stack. Inputs must be nonempty alternating
single digits and `+`, `-`, `*`, `/`, or `%`, at most seven characters plus
`'\0'`. Use no spaces, parentheses, unary signs, or multi-digit operands.
Divisors must be nonzero and arithmetic must fit `int`. These assumptions
are not implemented input validation.

### D1. Convert infix to postfix

Digits go directly to `postfix`. Before pushing an operator, pop waiting
operators of equal or greater precedence into the output. No integer
calculation occurs in this phase.

After each event, record the operator Stack bottom to top, `top`, the postfix
prefix, and `size`: start; read `1`; read `-`; read `2`; read `*`; read `3`;
read `+`; read `4`; drain operators and terminate output.

Why are both `*` and `-` removed when `+` arrives? Why does `'\0'` not
increase `size`? What prevents output from a previous conversion from being
appended to on a second valid call?

Response:

### D2. Evaluate the postfix result

The local integer array `values[10]` has an active prefix counted by `pos`,
which starts at 0. After each token, state the integer values bottom to top,
`pos`, and any calculation: `1`, `2`, `3`, `*`, `-`, `4`, `+`.

State the final returned integer. Why does `c - '0'` produce a number rather
than its character code? Why is `num2` popped before `num1`? Which expression
locates the top of the numeric Stack before a pop?

Response:

### D3. Separate assumptions from checks

Classify each case as within or outside the input assumptions. Give a result
only for valid cases, and explain the classification. Do not claim that
unsupported inputs are safely rejected or run them as normal tests.

1. `"7"`.
2. `"1-2*3+4"`.
3. `"8/2/2"`.
4. `"7%4+1"`.
5. `""`.
6. `"1+"`.
7. `"12+3"`.
8. `"1 +2"`.
9. `"(1+2)"`.
10. `"1/0"`.
11. More than seven input characters.

Name checks a future evaluator needs for malformed input, zero divisors,
and integer overflow. Which of these checks are absent from `lab.c`?

Response:

## E. Distinguish a physical slot from a logical item

The array has ten characters: indexes 0 through 7 each contain `'?'`, index 8
contains `'*'`, and index 9 contains `'+'`. Set `top` to 8.

1. Which indexes are active? Which are inactive?
2. Which character is the correct top?
3. What does the faulty expression `stack[top - 1]` read?
4. Why is that read inside the array but outside the logical Stack?
5. Which expression reads the correct top?
6. How could a wrong operator change a later calculation even though `top`
   remains unchanged?

Response:

## F. Connect cost to fixed storage

Let `n` be the number of valid expression tokens. `O(1)` means fixed work;
`O(n)` means work grows in proportion to `n`.

State the cost and a reason for each:

1. Successful or boundary `push`.
2. Successful or empty `peek`.
3. Successful or empty `pop`.
4. Infix-to-postfix conversion.
5. Postfix evaluation.
6. Storage with the current fixed arrays.

Why does no character Stack operation shift existing items? Why does the
conversion's inner pop loop still permit linear total work on valid input?
How does the seven-token maximum limit the examples you can run?

Response:

## G. Separate three uses of “stack”

The Stack ADT is a behavior rule. The runtime call stack commonly holds
bookkeeping for active function calls. The global `char stack[10]` and local
`int values[10]` are two array representations of the ADT.

1. Does storing `'A'` in the global array create a real C call frame?
2. Does the name `stack` make an array obey LIFO automatically?
3. Which functions enforce LIFO for the global character array?
4. How do active regions and index directions differ between `stack`
   and `values`?

Response:

## H. Exit ticket

1. Where is the top of the nonempty character Stack?
2. State LIFO in your own words.
3. Distinguish `peek` from `pop`.
4. What is returned and preserved after empty peek?
5. What is preserved after a full push?
6. Distinguish `top`, `size`, and `pos`.
7. State the input assumptions and one unchecked limitation.
8. State one question you still have.

Response:
