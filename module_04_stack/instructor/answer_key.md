# Instructor Answer Key — Module 4 Integer Stack

## Macro-Question synthesis

A Stack permits access at one end, the top. Last in, first out (LIFO) means
that the newest remaining item leaves first. In the motivating function-call
story, 300 finishes before 200 resumes, then 100 resumes after 200 finishes.
Those IDs are abstract labels. Trace `'A'`, `'B'`, and `'C'` as character
labels stored in the integer array; the array can also hold integer IDs.

`student/lab.c` is the current source. Its integer Stack grows toward
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

| Request | Returned integer code | State | `top` | Item count |
|---|---|---|---:|---:|
| start | none | empty | -1 | 0 |
| `push('A')` | none | A | 0 | 1 |
| `push('B')` | none | A, B | 1 | 2 |
| `push('C')` | none | A, B, C | 2 | 3 |
| `peek()` | C | A, B, C | 2 | 3 |
| `pop()` | C | A, B | 1 | 2 |
| `pop()` | B | A | 0 | 1 |
| `pop()` | A | empty | -1 | 0 |

### Target 2: boundaries

At `top == 9`, `is_full()` is true; an invalid push would write index 10.
At `top == -1`, `is_empty()` is true; invalid peek reads index -1, and invalid
pop reads index -1 before decrementing `top`. An invalid full push increments
`top` to 10 before writing outside storage. These calls have
undefined behavior, with no promised return or final state. Predicates report
boundaries; callers must prevent invalid operations. Diagnose them on paper.

### Target 3: expression transfer

Conversion produces `123*-4+` from `1-2*3+4`. It resets `top`, sets local
`pos = 0`, and starts with an empty Stack. The final drain emits the last
operator, leaving `top == -1` and `pos == 7`. The explicit assignment
`postfix[pos++] = '\0'` then writes the terminator at `postfix[7]` and
advances `pos` to 8. Seven tokens precede the terminator. Evaluation resets `top` again and reuses `int stack[10]`
for integers: `2*3 = 6`, `1-6 = -5`, then `-5+4 = -1`. The final pop returns
-1 and empties the Stack.

## Stage C investigation

The standard and linear worksheets have the same A–H sections. Use the
corresponding explanations below, accepting equivalent plain language.

### A. Canonical characters

Use the Stage B trace. After three pushes, `top == 2`, the count is three,
and `'C'` is at index 2. Bottom `'A'` remains at index 0. Peek leaves all
state unchanged. Pop order is C, B, A.

### B. Operation contracts and inactive slots

| Operation | When allowed | Action | If precondition fails |
|---|---|---|---|
| `push(int data)` | room remains, `top + 1 < 10` | write `stack[++top]` | at full, index 10 is outside storage |
| `peek()` | `top >= 0` | return integer `stack[top]` | at empty, index -1 is outside storage |
| `pop()` | `top >= 0` | read `stack[top]`, decrement `top`, and return the integer | at empty, index -1 is outside storage |

With `capacity == 10`, maintain `-1 <= top < capacity`. The count is `top + 1`,
and active indexes form the prefix 0 through `top`. The next push increases `top` before writing;
pop reads the current top before decrementing. No old bits are erased.
A stored integer `0` is an active item like any other integer value, not an
empty-read signal. Local conversion cursor `pos` counts output writes,
including the explicit terminator, rather than Stack items.

### C. Empty/full boundaries and fixed capacity

For an empty Stack, `is_empty()` is true and push is allowed; peek and pop
are invalid. For a full Stack, `is_full()` is true and peek/pop are allowed;
push is invalid. The predicates preserve state but do not guard operations.
A valid pop from A, B returns B and leaves `top == 0`, with the former B
cell unchanged and inactive.

If `capacity` is 3 and `top` is 2, `is_full()` is true. Push nevertheless
increments `top` to 3 and writes index 3, because it never calls the predicate.
The ten-cell allocation is unchanged. Equality predicates cannot validate
all corrupted top indexes; callers maintain the invariant.

### D. Two expression phases

Conversion resets `top = -1` and initializes local `pos = 0`. Digits go
directly to `postfix`. Before peeking, the operator loop checks
`!is_empty()`. It breaks if the waiting operator has lower precedence;
otherwise it emits that operator. Incoming `+` emits waiting `*` and `-`,
then the empty check stops the loop before `+` is pushed.

| Read/work | Visible postfix | Stack, bottom to top | `top` | `pos` |
|---|---|---|---:|---:|
| reset to empty | empty | empty | -1 | 0 |
| `1` | `1` | empty | -1 | 1 |
| `-` | `1` | `-` | 0 | 1 |
| `2` | `12` | `-` | 0 | 2 |
| `*` | `12` | `-`, `*` | 1 | 2 |
| `3` | `123` | `-`, `*` | 1 | 3 |
| `+` | `123*-` | `+` | 0 | 5 |
| `4` | `123*-4` | `+` | 0 | 6 |
| drain `+` | `123*-4+` | empty | -1 | 7 |
| write terminator | `123*-4+` terminated | empty | -1 | 8 |

The explicit final write terminates `postfix` at index 7 and increments `pos`
to 8. The token length is 7. A later supported conversion resets both
`top` and local `pos`, even if earlier work left active Stack items.

Evaluation resets `top = -1` and reuses the same integer array. It scans until `postfix[i] == '\0'`; this example has seven tokens:

| Token | Active `stack`, bottom to top | `top` | Work |
|---|---|---:|---|
| `1` | 1 | 0 | `push(c - '0')` converts a character to an integer |
| `2` | 1, 2 | 1 | push number |
| `3` | 1, 2, 3 | 2 | push number |
| `*` | 1, 6 | 1 | right `num2 = 3`, left `num1 = 2` |
| `-` | -5 | 0 | right `num2 = 6`, left `num1 = 1` |
| `4` | -5, 4 | 1 | push number |
| `+` | -1 | 0 | right `num2 = 4`, left `num1 = -5` |
| final pop | empty | -1 | return -1 |

The nonempty top remains `stack[top]`. Pop order is observable for
`-`, `/`, and `%`. Equal-precedence reduction is left to right; for example,
`8-3-2+1` produces `83-2-1+` and result 4.

For the grouped-expression trace in D3, `infix_to_postfix_parentheses()`
reads `eq_paren = "1+(2+3)"`:

| Event | Operator Stack, bottom to top | `top` | Postfix prefix | `pos` |
|---|---|---:|---|---:|
| reset to empty | empty | -1 | empty | 0 |
| `1` | empty | -1 | `1` | 1 |
| outer `+` | `+` | 0 | `1` | 1 |
| `(` | `+`, `(` | 1 | `1` | 1 |
| `2` | `+`, `(` | 1 | `12` | 2 |
| inner `+` | `+`, `(`, `+` | 2 | `12` | 2 |
| `3` | `+`, `(`, `+` | 2 | `123` | 3 |
| `)` emits inner `+`, discards `(` | `+` | 0 | `123+` | 4 |
| drain outer `+` | empty | -1 | `123++` | 5 |
| write terminator | empty | -1 | `123++` terminated | 6 |

`(` has precedence 0, so the inner `+` triggers `break` and leaves it
stored. At `)`, the loop checks nonempty, then pops into `op`. An operator
is emitted; a popped `(` triggers `break` without being written. The final
drain empties the Stack before a separate assignment writes the terminator. The output has five tokens and a terminator at `postfix[5]`.
Evaluation calculates `2+3 = 5`, then `1+5 = 6`, and its final pop leaves
`top == -1`. Matching groups are assumed, not checked.

The D4 classifications are:

| Input | Within assumptions? | Result if valid | Reason |
|---|---|---:|---|
| `"7"` | yes | 7 | plain converter stops at the terminator |
| `"1-2*3+4"` | yes | -1 | precedence and operand order |
| `"8/2/2+1"` | yes | 3 | division is left associative |
| `"7%4+1*2"` | yes | 5 | remainder and multiplication precede addition |
| `""` | no | — | no operand; evaluation would pop an empty Stack |
| `"1+"` | no | — | missing an operand |
| `"12+3"` | no | — | multi-digit operands unsupported |
| `"1 +2"` | no | — | spaces unsupported |
| `"(1+2)"` | yes with the dedicated converter | 3 | balanced group in `eq_paren`; unsupported by the plain converter |
| `"(1+2"` | no | — | opening parenthesis has no matching close |
| `"1/0+2*3"` | no | — | zero divisor |
| more than seven characters | no | — | exceeds fixed expression buffers |

Core input is a nonempty valid expression of at most seven characters plus
a terminator within the eight-cell input buffer. All expression scans stop
at `'\0'`, so shorter valid expressions work. Use single-digit operands and
binary `+ - * / %` operators. The plain converter reads `eq` without
parentheses; the dedicated converter reads balanced groups from `eq_paren`.
No spaces, unary operators, or multi-digit operands are supported. Divisors
are nonzero and intermediates fit `int`. The source does not validate these
conditions. The conversion loops check nonempty before reading the Stack,
but this does not validate grammar. Unsupported characters can enter the
output, an unmatched `)` can be silently consumed, and an unmatched `(`
can be drained to output. The resulting postfix can underflow evaluation.
These are limitations, not promised safe rejections.
General parsing and checked arithmetic are extensions.

### E. Physical slot versus logical item — instructor answer

For the autopsy fixture, index 0 contains `'+'`, index 1 contains `'*'`,
and indexes 2 through 9 contain `'?'`; `top == 1`.

1. Active indexes are 0 and 1; logical bottom-to-top order is `+`, `*`.
2. Correct `stack[top]` reports `'*'`.
3. Faulty `stack[top + 1]` reports `'?'` from inactive index 2.
4. Index 2 is physically allocated but is outside the active prefix.
5. The repaired top expression is `stack[top]`, after checking nonempty.

At full capacity, the same faulty expression selects `stack[10]`, which is
out of bounds. In the fixture, the first broken rule is the top selection,
even if no address diagnostic appears and `top` is left unchanged. Use a different inactive/top character
pair for a regression test. Preserve predictions before showing these
answers; they do not belong in the Stage D diagram release.

### F. Costs

Push, peek, and pop are `O(1)` and shift no elements. Conversion is `O(n)`:
each input character is scanned once, and each operator or opening
parenthesis is pushed/popped at most once.
Evaluation is `O(n)` with fixed work per token. Current reserved buffers are
fixed, so extra space is `O(1)` under the seven-character limit. A generalized
postfix buffer for arbitrary length would require `O(n)` output storage.

### G. Three meanings of stack

The Stack ADT is LIFO behavior. `int stack[10]` plus shared top index `top` is one
explicit representation, reused across the two expression phases. Runtime
call-stack bookkeeping supports actual C calls. A character such as `'A'`
is a teaching label; storing it does not create a call frame. The variable
name does not enforce LIFO; `push`, `peek`, and `pop` implement that rule.

### H. Exit ticket

A complete response identifies the nonempty top as `stack[top]`, the
count as `top + 1`, and the unchecked boundary preconditions. It distinguishes
shared top index `top`, item count `top + 1`, local output cursor `pos`, and
actual token length; explains guarded operator loops, the explicit terminator, and shared-array resets; states
`1-2*3+4 -> 123*-4+ -> -1` and the dedicated
`1+(2+3) -> 123++ -> 6` conversion; and identifies at least one missing check.
Questions can be sorted into behavior, indexes, representation, expression
phases, C notation, or evidence needs.

## Current lab evidence and tests

The demo should report:

```text
infix: 1-2*3+4
postfix: 123*-4+
result: -1
infix with parentheses: 1+(2+3)
postfix: 123++
result: 6
```

The parentheses example produces `123++` and 6. Its terminator
is at index 5, and conversion and evaluation both finish with `top == -1`.

The current `code/tests/test_lab.c` exercises integer LIFO, full/empty
boundaries, canonical conversion, precedence and operand order, repeated
conversions with shared-state resets, shorter null-terminated inputs, balanced
parentheses, and the distinction between character digits and numeric
results. Use `make lab-demo` and `make lab-tests` from `code`, or
`build.ps1 -Target lab` and `build.ps1 -Target lab-tests` on PowerShell.

Students add exactly three justified cases to the current lab test file:

1. a LIFO sequence, such as pop then push a different visible character;
2. a boundary-predicate or valid-operation case comparing `top` and all
   ten stored integers, without invoking undefined behavior;
3. a valid expression case checking `postfix`, its actual terminator, final
   `top`, and numeric result.

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
