# Instructor Answer Key — Module 4 Character Stack

## Macro-Question synthesis

A Stack permits access at one end, the top. Last in, first out (LIFO) means
that the newest remaining item leaves first. In the motivating function-call
story, 300 finishes before 200 resumes, then 100 resumes after 200 finishes.
Those IDs are abstract labels. The concrete character Stack uses `'A'`,
`'B'`, and `'C'`; do not put integer IDs such as 300 into `char` storage.

`student/lab.c` is the current source. Its character Stack grows toward
larger indexes. The Stack ADT is the access rule, not this particular array
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

| Request | Returned character | State | `size` | Item count |
|---|---|---|---:|---:|
| start | none | empty | 0 | 0 |
| `push('A')` | none | A | 1 | 1 |
| `push('B')` | none | A, B | 2 | 2 |
| `push('C')` | none | A, B, C | 3 | 3 |
| `peek()` | C | A, B, C | 3 | 3 |
| `pop()` | C | A, B | 2 | 2 |
| `pop()` | B | A | 1 | 1 |
| `pop()` | A | empty | 0 | 0 |

### Target 2: boundaries

At `size == 10`, push returns without a write or index change. At `size == 0`,
peek and pop return `'\0'`; both preserve the array and `size`. There is no
output parameter whose old value is preserved. A caller assigning the
returned character receives `'\0'`.

### Target 3: expression transfer

Conversion produces `123*-4+` from `1-2*3+4`. `postfix_size` is seven; the terminating
`'\0'` is not a token. Evaluation computes `2*3 = 6`, `1-6 = -5`, and
`-5+4 = -1`. Characters wait in `stack`; numbers and intermediate results
occupy local `int values[10]`.

## Stage C investigation

The standard and linear worksheets have the same A–H sections. Use the
corresponding explanations below, accepting equivalent plain language.

### A. Canonical characters

Use the Stage B trace. After three pushes, `size == 3`, the count is three,
and `'C'` is at index 2. Bottom `'A'` remains at index 0. Peek leaves all
state unchanged. Pop order is C, B, A.

### B. Operation contracts and inactive slots

| Operation | When allowed | Action | Boundary behavior |
|---|---|---|---|
| `push(data)` | `size < capacity` in a valid state | write `stack[size]`, increment `size` | at full, no change and no return value |
| `peek()` | `size > 0` in a valid state | return `stack[size - 1]` | at empty, return `'\0'` |
| `pop()` | `size > 0` in a valid state | decrement `size`, read `stack[size]`, return that character | at empty, return `'\0'` |

For valid states, `0 <= size <= capacity`. The item count is `size`. Active
indexes form the prefix 0 through `size - 1`; indexes from `size` through 9
are inactive.
The next push writes at the old `size`. Pop does not erase the old bits;
lowering `size` makes that cell inactive. `postfix_size` does not control this Stack:
it counts characters already written to `postfix`. An intentionally stored
`'\0'` would be indistinguishable from the empty-read return by value alone;
`is_empty()` supplies the missing state distinction.

### C. Empty/full boundaries and fixed capacity

| Independent case | Return | Final `size` | Preserved state |
|---|---|---:|---|
| empty peek, `size = 0` | `'\0'` | 0 | all array cells |
| empty pop, `size = 0` | `'\0'` | 0 | all array cells |
| full push, `size = 10` | no value | 10 | all array cells |
| A, B with `size = 2`; pop | B | 1 | array cells, including old B |

A full push must stop before writing at index 10. An empty peek or pop
must stop before selecting index -1. Empty and full are valid states; arbitrary `size`
values outside 0–10 violate the invariant and are not repaired by the code.
The variable `capacity` is initialized to 10 and controls the full check.
If it is set to 3 while empty, pushes can activate only indexes 0 through 2; the
array still has ten allocated cells. Changing the variable does not resize
the array or validate corrupted state.

### D. Two expression phases

Conversion appends digits immediately and uses the operator Stack to delay
operators. When `+` arrives, waiting `*` and `-` each have precedence at least
as great as `+`, so both are appended before `+` is pushed.

| Read/work | Postfix so far | Operators, bottom to top | `size` | `postfix_size` |
|---|---|---|---:|---:|
| start | empty | empty | 0 | 0 |
| `1` | `1` | empty | 0 | 1 |
| `-` | `1` | `-` | 1 | 1 |
| `2` | `12` | `-` | 1 | 2 |
| `*` | `12` | `-`, `*` | 2 | 2 |
| `3` | `123` | `-`, `*` | 2 | 3 |
| `+` | `123*-` | `+` | 1 | 5 |
| `4` | `123*-4` | `+` | 1 | 6 |
| drain | `123*-4+` | empty | 0 | 7 |

The final terminator occupies `postfix[7]`. Resetting `postfix_size` before scanning
prevents appending to a previous conversion. Writing a fresh terminator
prevents stale characters from displaying after a shorter new expression.

Evaluation scans the seven postfix tokens:

| Token | Active `values`, bottom to top | `value_size` | Work |
|---|---|---:|---|
| `1` | 1 | 1 | convert character to integer |
| `2` | 1, 2 | 2 | push number |
| `3` | 1, 2, 3 | 3 | push number |
| `*` | 1, 6 | 2 | `num2 = 3`, `num1 = 2` |
| `-` | -5 | 1 | `num2 = 6`, `num1 = 1` |
| `4` | -5, 4 | 2 | push number |
| `+` | -1 | 1 | `num2 = 4`, `num1 = -5` |

`value_size` counts integers, with top number at `values[value_size - 1]`. Each operator
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

For the autopsy fixture, index 0 contains `'+'`, index 1 contains `'*'`,
and indexes 2 through 9 contain `'?'`; `size == 2`.

1. Active indexes are 0 and 1; logical bottom-to-top order is `+`, `*`.
2. Correct `stack[size - 1]` reports `'*'`.
3. Faulty `stack[size]` reports `'?'` from inactive index 2.
4. Index 2 is physically allocated but is outside the active prefix.
5. The repaired top expression is `stack[size - 1]`, after checking nonempty.

At full capacity, the same faulty expression selects `stack[10]`, which is
out of bounds. In the fixture, the first broken rule is the top selection,
even if no address diagnostic appears and `size` is left unchanged. Use a different inactive/top character
pair for a regression test. Preserve predictions before showing these
answers; they do not belong in the Stage D diagram release.

### F. Costs

Push, peek, and pop are `O(1)` and shift no elements. Conversion is `O(n)`:
each token is scanned once and each operator is pushed/popped at most once.
Evaluation is `O(n)` with fixed work per token. Current reserved buffers are
fixed, so extra space is `O(1)` under the seven-character limit. A generalized
postfix buffer for arbitrary length would require `O(n)` output storage.

### G. Three meanings of stack

The Stack ADT is LIFO behavior. `char stack[10]` plus `size` is one explicit
representation. Runtime call-stack bookkeeping supports actual function
calls. A character such as `'A'` is a teaching label; storing it does not
create a runtime call frame. The variable's name does not enforce LIFO;
`push`, `peek`, and `pop` implement the access rule. The local integer
Stack is another explicit representation: `values[0..value_size - 1]` is an active
prefix, as is the character array `stack[0..size - 1]`. These arrays have
separate `size` variables; the local integer count hides the global name
inside `eval_postfix()`.

### H. Exit ticket

A complete response identifies `stack[size - 1]` as the top when `size > 0`,
`size` as the count, increasing `size` on push/decreasing `size` on pop, and empty `'\0'` versus
full no-op behavior. It separates global `size`, postfix `postfix_size`, and local integer `value_size`,
states `1-2*3+4 -> 123*-4+ -> -1`, and names at least one assumption that is
not checked. Questions can be sorted into behavior, indexes, representation,
expression phases, C notation, or evidence needs.

## Current lab evidence and tests

The demo should report:

```text
infix: 1-2*3+4
postfix: 123*-4+
postfix_size: 7
result: -1
```

The current `code/tests/test_lab.c` exercises character LIFO, full/empty
boundaries, canonical conversion, precedence and operand order, repeated and
shorter conversions, and the distinction between character digits and numeric
results. Use `make lab-demo` and `make lab-tests` from `code`, or
`build.ps1 -Target lab` and `build.ps1 -Target lab-tests` on PowerShell.

Students add exactly three justified cases to the current lab test file:

1. a LIFO sequence, such as pop then push a different visible character;
2. a full/empty boundary case comparing `size` and all ten stored characters;
3. a valid expression case checking postfix, `postfix_size`, and numeric result.

Require rationale beyond repeating a supplied assertion. Suitable evidence
includes a return/state trace, array snapshot, both expression-phase tables,
actual build/test output, the predicted and observed autopsy result, and an
accurate limitation statement. An incorrect initial response is evidence to
revise, not a reason to penalize a learner who preserves and explains the
correction. Drawing quality and memorized terminology are not targets.

## Optional legacy comparison

The existing checked integer library can illustrate a different representation
and richer error contract after the core lab. Its caller-provided arrays,
output pointers, overflow rejection, and eight-core/five-extension test
totals do not apply to `student/lab.c`. Keep those tasks
optional and label them explicitly when used.
