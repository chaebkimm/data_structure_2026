# Instructor Answer Key — Module 4 Character Stack

## Macro-Question synthesis

A Stack permits access at one end, the top. Last in, first out (LIFO) means
that the newest remaining item leaves first. In the motivating function-call
story, 300 finishes before 200 resumes, then 100 resumes after 200 finishes.
Those IDs are abstract labels. The concrete character Stack uses `'A'`,
`'B'`, and `'C'`; do not put integer IDs such as 300 into `char` storage.

`student/lab.c` is the current source. Its character Stack grows toward
smaller indexes. The Stack ADT is the access rule, not this particular array
layout and not the runtime's bookkeeping for actual C calls.

## Stage A inquiry

The standard and linear formats ask the same questions. Preserve the initial
model before supplying formal vocabulary or code.

- The most recent unfinished caller resumes first: 200 after 300, then 100.
- Starts produce the abstract record 100; 100, 200; 100, 200, 300. Finishes
  remove 300, 200, then 100.
- Inspecting the newest item need not remove it. Removing the oldest first
  would violate the motivating return order.
- A full ten-position record cannot accept an eleventh item without a
  different storage policy. An empty record has no item to report.
- A suitable synthesis is “add and remove at the same end so that the newest
  unfinished work is handled first.” Name LIFO after this attempt.
- For the transfer brainstorm, `2*3` must finish before the surrounding
  subtraction and addition in `1-2*3+4`. Students need not invent the postfix
  algorithm before its representation is introduced.

## Stage B Cognitive Pause — exactly three targets

### Target 1: canonical trace

States below are logical bottom to top. `push` has no return value.

| Request | Returned character | State | `top` | Item count |
|---|---|---|---:|---:|
| start | none | empty | 10 | 0 |
| `push('A')` | none | A | 9 | 1 |
| `push('B')` | none | A, B | 8 | 2 |
| `push('C')` | none | A, B, C | 7 | 3 |
| `peek()` | C | A, B, C | 7 | 3 |
| `pop()` | C | A, B | 8 | 2 |
| `pop()` | B | A | 9 | 1 |
| `pop()` | A | empty | 10 | 0 |

### Target 2: boundaries

At `top == 0`, push returns without a write or index change. At `top == 10`,
peek and pop return `'\0'`; both preserve the array and `top`. There is no
output parameter whose old value is preserved. A caller assigning the
returned character receives `'\0'`.

### Target 3: expression transfer

Conversion produces `123*-4+` from `1-2*3+4`. `size` is seven; the terminating
`'\0'` is not a token. Evaluation computes `2*3 = 6`, `1-6 = -5`, and
`-5+4 = -1`. Characters wait in `stack`; numbers and intermediate results
occupy local `int values[10]`.

## Stage C investigation

The standard and linear worksheets have the same A–H sections. Use the
corresponding explanations below, accepting equivalent plain language.

### A. Canonical characters

Use the Stage B trace. After three pushes, `top == 7`, the count is three,
and `'C'` is at index 7. Bottom `'A'` remains at index 9. Peek leaves all
state unchanged. Pop order is C, B, A.

### B. Operation contracts and inactive slots

| Operation | When allowed | Action | Boundary behavior |
|---|---|---|---|
| `push(data)` | `top > 0` in a valid state | decrement `top`, write `stack[top]` | at full, no change and no return value |
| `peek()` | `top < 10` in a valid state | return `stack[top]` | at empty, return `'\0'` |
| `pop()` | `top < 10` in a valid state | save `stack[top]`, increment `top`, return saved character | at empty, return `'\0'` |

For valid states, `0 <= top <= 10`. The item count is `10 - top`. Active
indexes form the suffix `top` through 9; smaller indexes are inactive.
The next push writes at the old `top - 1`. Pop does not erase the old bits;
raising `top` makes that cell inactive. `size` does not control this Stack:
it counts characters already written to `postfix`. An intentionally stored
`'\0'` would be indistinguishable from the empty-read return by value alone;
`is_empty()` supplies the missing state distinction.

### C. Empty/full boundaries and fixed capacity

| Independent case | Return | Final `top` | Preserved state |
|---|---|---:|---|
| empty peek, `top = 10` | `'\0'` | 10 | all array cells |
| empty pop, `top = 10` | `'\0'` | 10 | all array cells |
| full push, `top = 0` | no value | 0 | all array cells |
| A, B with `top = 8`; pop | B | 9 | array cells, including old B |

A full push must stop before decrementing zero to -1. An empty read must
stop before indexing 10. Empty and full are valid states; arbitrary `top`
values outside 0–10 violate the invariant and are not repaired by the code.
The variable `capacity` is initialized to 10, but changing that variable
alone has no effect on the hardcoded empty check or array extent.

### D. Two expression phases

Conversion appends digits immediately and uses the operator Stack to delay
operators. When `+` arrives, waiting `*` and `-` each have precedence at least
as great as `+`, so both are appended before `+` is pushed.

| Read/work | Postfix so far | Operators, bottom to top | `top` | `size` |
|---|---|---|---:|---:|
| start | empty | empty | 10 | 0 |
| `1` | `1` | empty | 10 | 1 |
| `-` | `1` | `-` | 9 | 1 |
| `2` | `12` | `-` | 9 | 2 |
| `*` | `12` | `-`, `*` | 8 | 2 |
| `3` | `123` | `-`, `*` | 8 | 3 |
| `+` | `123*-` | `+` | 9 | 5 |
| `4` | `123*-4` | `+` | 9 | 6 |
| drain | `123*-4+` | empty | 10 | 7 |

The final terminator occupies `postfix[7]`. Resetting `size` before scanning
prevents appending to a previous conversion. Writing a fresh terminator
prevents stale characters from displaying after a shorter new expression.

Evaluation scans the seven postfix tokens:

| Token | Active `values`, bottom to top | `pos` | Work |
|---|---|---:|---|
| `1` | 1 | 1 | convert character to integer |
| `2` | 1, 2 | 2 | push number |
| `3` | 1, 2, 3 | 3 | push number |
| `*` | 1, 6 | 2 | `num2 = 3`, `num1 = 2` |
| `-` | -5 | 1 | `num2 = 6`, `num1 = 1` |
| `4` | -5, 4 | 2 | push number |
| `+` | -1 | 1 | `num2 = 4`, `num1 = -5` |

`pos` counts integers, with top number at `values[pos - 1]`. Each operator
pops the right operand into `num2` first, then the left into `num1`. The order
is observable for `-`, `/`, and `%`. Equal-precedence reduction is left to
right; for example, `8-3-2` produces `83-2-` and result 3.

The D3 classifications are:

| Input | Within assumptions? | Result if valid | Reason |
|---|---|---:|---|
| `"7"` | yes | 7 | one digit is a complete expression |
| `"1-2*3+4"` | yes | -1 | precedence and operand order |
| `"8/2/2"` | yes | 2 | equal precedence is left associative |
| `"7%4+1"` | yes | 4 | remainder precedes addition |
| `""` | no | — | nonempty input required |
| `"1+"` | no | — | right operand missing |
| `"12+3"` | no | — | multi-digit operands are outside the grammar |
| `"1 +2"` | no | — | spaces are outside the grammar |
| `"(1+2)"` | no | — | parentheses are outside the grammar |
| `"1/0"` | no | — | zero divisor |
| more than seven characters | no | — | input/output buffers need a terminator |

Core input assumptions are nonempty text of at most seven characters,
single digits alternating with `+ - * / %`, no spaces/parentheses/unary
operators/multi-digit operands, nonzero divisors, and representable `int`
intermediate results. The current program assumes these conditions; it does
not validate them. `1++2`, an empty expression, or a space is outside this
contract, not a promised safe rejection. Arithmetic checks, explicit errors,
and final operand-count validation are possible extensions.

### E. Physical slot versus logical item — instructor answer

For the autopsy fixture, the ten characters are eight `'?'` characters,
then `'*'` at index 8 and `'+'` at index 9; `top == 8`.

1. Active indexes are 8 and 9; logical bottom-to-top order is `+`, `*`.
2. Correct `stack[top]` reports `'*'`.
3. Faulty `stack[top - 1]` reports `'?'` from inactive index 7.
4. Index 7 is physically allocated but is outside the active suffix.
5. The repaired top expression is `stack[top]`, after checking nonempty.

The first broken rule is the top selection, even if no address diagnostic
appears and `top` is left unchanged. Use a different inactive/top character
pair for a regression test. Preserve predictions before showing these
answers; they do not belong in the Stage D diagram release.

### F. Costs

Push, peek, and pop are `O(1)` and shift no elements. Conversion is `O(n)`:
each token is scanned once and each operator is pushed/popped at most once.
Evaluation is `O(n)` with fixed work per token. Current reserved buffers are
fixed, so extra space is `O(1)` under the seven-character limit. A generalized
postfix buffer for arbitrary length would require `O(n)` output storage.

### G. Three meanings of stack

The Stack ADT is LIFO behavior. `char stack[10]` plus `top` is one explicit
representation. Runtime call-stack bookkeeping supports actual function
calls. A character such as `'A'` is a teaching label; storing it does not
create a runtime call frame. The variable's name does not enforce LIFO;
`push`, `peek`, and `pop` implement the access rule. The local integer
Stack is another explicit representation: `values[0..pos - 1]` is an active
prefix, whereas the character array has active suffix `stack[top..9]`.

### H. Exit ticket

A complete response identifies `stack[top]` as the top when `top < 10`,
`10 - top` as the count, downward push/upward pop, and empty `'\0'` versus
full no-op behavior. It separates `top`, postfix `size`, and integer `pos`,
states `1-2*3+4 -> 123*-4+ -> -1`, and names at least one assumption that is
not checked. Questions can be sorted into behavior, indexes, representation,
expression phases, C notation, or evidence needs.

## Current lab evidence and tests

The demo should report:

```text
infix: 1-2*3+4
postfix: 123*-4+
size: 7
result: -1
```

The current `code/tests/test_lab.c` exercises character LIFO, full/empty
boundaries, canonical conversion, precedence and operand order, repeated and
shorter conversions, and the distinction between character digits and numeric
results. Use `make lab-demo` and `make lab-tests` from `code`, or
`build.ps1 -Target lab` and `build.ps1 -Target lab-tests` on PowerShell.

Students add exactly three justified cases to the current lab test file:

1. a LIFO sequence, such as pop then push a different visible character;
2. a full/empty boundary case comparing `top` and all ten stored characters;
3. a valid expression case checking postfix, `size`, and numeric result.

Require rationale beyond repeating a supplied assertion. Suitable evidence
includes a return/state trace, array snapshot, both expression-phase tables,
actual build/test output, the predicted and observed autopsy result, and an
accurate limitation statement. An incorrect initial response is evidence to
revise, not a reason to penalize a learner who preserves and explains the
correction. Drawing quality and memorized terminology are not targets.

## Optional legacy comparison

The existing checked integer library can illustrate a different representation
and richer error contract after the core lab. Its active-prefix layout,
caller-provided arrays, output pointers, overflow rejection, and eight-core /
five-extension test totals do not apply to `student/lab.c`. Keep those tasks
optional and label them explicitly when used.
