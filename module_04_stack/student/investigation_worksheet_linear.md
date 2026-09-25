# Stage C — Investigation: Linear Accessible Format

This version has the same questions and learning targets as the standard
investigation. No response table or drawing is required. Use a screen reader,
keyboard, speech input, or text-only response as needed.

Open this file after preserving the Cognitive Pause. Complete and preserve
Sections A through F before opening Stage D. Sections G and H may be completed
during the independent-work window.

## Quick reference

A Stack follows last in, first out (LIFO). The global `int stack[10]` is
empty at `size == 0` and full at `size == 10`. Active indexes run from 0
through `size - 1`. The nonempty top is `stack[size - 1]`, and item count is `size`.
Conversion uses local `pos` as its output cursor. Both phases reuse the same
Stack and global `size`, resetting that count at entry.

## A. Trace the canonical characters

Start empty. For each request, record the return, bottom-to-top logical
state, new `size`, and item count. `push` has no return value.

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

For `push(int data)`, `peek()`, and `pop()`, state the steps and return for a
valid call, its caller precondition, and the invalid index if that condition
fails. The operations do not check the full/empty predicates themselves.

Then answer:

1. Why must `push` write at `size` before increasing it?
2. Why does `pop` decrease `size` before reading `stack[size]`?
3. Does the old character disappear from storage after a pop?
4. What makes the former top cell inactive?
5. Why can a stored `'\0'` be a real item while `is_empty()` is false?

Response:

## C. Check empty and full boundaries

For each independent case, state the full/empty predicate result, an allowed
next operation, and the index an invalid call would select. These operations
have no guards. Diagnose invalid calls on paper; do not execute them.

1. Empty (`size == 0`); consider peek.
2. Empty (`size == 0`); consider pop.
3. Full (`size == 10`); consider push.
4. A, B bottom to top (`size == 2`); valid pop.

Then answer:

1. Which index would full push write? Is a no-op guaranteed?
2. Which index would empty peek/pop read? Is a sentinel result guaranteed?
3. If `capacity` is set to 3, what does `is_full()` report at `size == 3`?
   Does push consult that predicate or resize the array?
4. Why must callers maintain `0 <= size <= 10`? Do equality predicates
   validate every corrupted count?

Response:

## D. Transfer the rule in two phases

Use `1-2*3+4`. Inputs must have exactly seven characters: four single digits
alternating with three `+ - * / %` operators, plus `'\0'` in `eq[7]`.
No spaces, parentheses, unary signs, or multi-digit operands are supported.
Divisors must be nonzero and arithmetic must fit `int`. These are assumptions,
not validation checks. Both phases reset global `size` at entry.

### D1. Convert infix to postfix

Digits go directly to `eq_re`. Before pushing an operator, pop waiting
operators of equal or greater precedence into the output. No integer
calculation occurs in this phase. Reset `size` and push the bottom `'\0'`
sentinel before scanning; local output cursor `pos` starts at 0.

After each event, record the operator Stack bottom to top, `size`, the postfix
prefix, and `pos`: reset and push sentinel; read `1`; read `-`; read `2`; read `*`; read `3`;
read `+`; read `4`; drain final operator; drain sentinel and terminate output.

Why are both `*` and `-` removed when `+` arrives? Why does the stored
sentinel stop that loop? Why does its final write increase `pos` to 8
although there are seven tokens? What resets on a second valid call?

Response:

### D2. Evaluate the postfix result

`eval_postfix()` resets `size = 0` and reuses the global `int stack[10]`
without a sentinel. After each token, state the integer values bottom to top,
`size`, and any calculation: `1`, `2`, `3`, `*`, `-`, `4`, `+`.

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
3. `"8/2/2+1"`.
4. `"7%4+1*2"`.
5. `""`.
6. `"1+"`.
7. `"12+3"`.
8. `"1 +2"`.
9. `"(1+2)"`.
10. `"1/0+2*3"`.
11. More than seven input characters.

Name checks a future evaluator needs for malformed input, zero divisors,
and integer overflow. Which of these checks are absent from `lab.c`?

Response:

## E. Distinguish a physical slot from a logical item

The array has ten characters: index 0 contains `'+'`, index 1 contains `'*'`,
and indexes 2 through 9 contain `'?'`. Set `size` to 2.

1. Which indexes are active? Which are inactive?
2. Which character is the correct top?
3. What does the faulty expression `stack[size]` read?
4. Why is that read inside the array but outside the logical Stack?
5. Which expression reads the correct top?
6. How could a wrong operator change a later calculation even though `size`
   remains unchanged?

Response:

## F. Connect cost to fixed storage

Let `n` be the number of valid expression tokens. `O(1)` means fixed work;
`O(n)` means work grows in proportion to `n`.

State the cost and a reason for each:

1. Valid `push`.
2. Nonempty `peek`.
3. Nonempty `pop`.
4. Infix-to-postfix conversion.
5. Postfix evaluation.
6. Storage with the current fixed arrays.

Why does no integer Stack operation shift existing items? Why does the
conversion's inner pop loop still permit linear total work on valid input?
Why do the fixed seven-iteration loops exclude shorter expressions?

Response:

## G. Separate three uses of “stack”

The Stack ADT is a behavior rule. The runtime call stack commonly holds
bookkeeping for active function calls. The global `int stack[10]` is one
array representation of the ADT, reused for both expression phases.

1. Does storing `'A'` in the global array create a real C call frame?
2. Does the name `stack` make an array obey LIFO automatically?
3. Which functions enforce LIFO for the global character array?
4. How does the meaning of active items change between conversion and evaluation?

Response:

## H. Exit ticket

1. Where is the top of the nonempty integer Stack?
2. State LIFO in your own words.
3. Distinguish `peek` from `pop`.
4. Which predicate must a caller consult before an empty peek?
5. Why must a caller avoid full push?
6. Distinguish shared global `size`, conversion-local `pos`, and token length.
7. State the input assumptions and one unchecked limitation.
8. State one question you still have.

Response:
