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

| Request | Returned integer code | State | `size` | Item count |
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

At `size == 10`, `is_full()` is true; an invalid push would write index 10.
At `size == 0`, `is_empty()` is true; invalid peek reads index -1, and invalid
pop decrements toward -1 before its out-of-bounds read. These calls have
undefined behavior, with no promised return or final state. Predicates report
boundaries; callers must prevent invalid operations. Diagnose them on paper.

### Target 3: expression transfer

Conversion produces `123*-4+` from `1-2*3+4`. It resets `size`, sets local
`pos = 0`, and pushes a real `'\0'` sentinel. The final drain writes that
sentinel to `eq_re[7]`, leaving `size == 0` and `pos == 8`. Seven tokens precede
the terminator. Evaluation resets `size` again and reuses `int stack[10]`
for integers: `2*3 = 6`, `1-6 = -5`, then `-5+4 = -1`. The final pop returns
-1 and empties the Stack.

## Stage C investigation

The standard and linear worksheets have the same A–H sections. Use the
corresponding explanations below, accepting equivalent plain language.

### A. Canonical characters

Use the Stage B trace. After three pushes, `size == 3`, the count is three,
and `'C'` is at index 2. Bottom `'A'` remains at index 0. Peek leaves all
state unchanged. Pop order is C, B, A.

### B. Operation contracts and inactive slots

| Operation | When allowed | Action | If precondition fails |
|---|---|---|---|
| `push(int data)` | room remains, `size < 10` | write `stack[size++]` | at full, index 10 is outside storage |
| `peek()` | `size > 0` | return integer `stack[size - 1]` | at empty, index -1 is outside storage |
| `pop()` | `size > 0` | decrement `size`, return integer `stack[size]` | at empty, index -1 is outside storage |

With `capacity == 10`, maintain `0 <= size <= capacity`. The count is `size`,
and active indexes form the prefix 0 through `size - 1`. The next push writes
at the old count; pop decrements before reading. No old bits are erased.
A stored `'\0'` is an active item like any other integer value, not an
empty-read signal. Local conversion cursor `pos` counts output writes,
including the sentinel, rather than Stack items.

### C. Empty/full boundaries and fixed capacity

For an empty Stack, `is_empty()` is true and push is allowed; peek and pop
are invalid. For a full Stack, `is_full()` is true and peek/pop are allowed;
push is invalid. The predicates preserve state but do not guard operations.
A valid pop from A, B returns B and leaves `size == 1`, with the former B
cell unchanged and inactive.

If `capacity` is 3 and `size` is 3, `is_full()` is true. Push nevertheless
writes index 3 and increments `size`, because it never calls the predicate.
The ten-cell allocation is unchanged. Equality predicates cannot validate
all corrupted counts; callers maintain the invariant.

### D. Two expression phases

Conversion resets `size`, initializes local `pos = 0`, and pushes `'\0'`.
Digits go directly to `eq_re`. Incoming `+` emits waiting `*` and `-` because
their precedence is greater or equal, then stops at the precedence-0 sentinel.

| Read/work | Visible postfix | Stack, bottom to top | `size` | `pos` |
|---|---|---|---:|---:|
| reset and push sentinel | empty | `'\0'` | 1 | 0 |
| `1` | `1` | `'\0'` | 1 | 1 |
| `-` | `1` | `'\0'`, `-` | 2 | 1 |
| `2` | `12` | `'\0'`, `-` | 2 | 2 |
| `*` | `12` | `'\0'`, `-`, `*` | 3 | 2 |
| `3` | `123` | `'\0'`, `-`, `*` | 3 | 3 |
| `+` | `123*-` | `'\0'`, `+` | 2 | 5 |
| `4` | `123*-4` | `'\0'`, `+` | 2 | 6 |
| drain `+` | `123*-4+` | `'\0'` | 1 | 7 |
| drain sentinel | `123*-4+` terminated | empty | 0 | 8 |

The final sentinel write terminates `eq_re` at index 7 and increments `pos`
to 8. The token length is 7. A later supported conversion resets both
`size` and local `pos`, even if earlier work left active Stack items.

Evaluation resets `size = 0` and reuses the same integer array, without
pushing a sentinel. It scans exactly seven postfix tokens:

| Token | Active `stack`, bottom to top | `size` | Work |
|---|---|---:|---|
| `1` | 1 | 1 | `push(c - '0')` converts a character to an integer |
| `2` | 1, 2 | 2 | push number |
| `3` | 1, 2, 3 | 3 | push number |
| `*` | 1, 6 | 2 | right `num2 = 3`, left `num1 = 2` |
| `-` | -5 | 1 | right `num2 = 6`, left `num1 = 1` |
| `4` | -5, 4 | 2 | push number |
| `+` | -1 | 1 | right `num2 = 4`, left `num1 = -5` |
| final pop | empty | 0 | return -1 |

The nonempty top remains `stack[size - 1]`. Pop order is observable for
`-`, `/`, and `%`. Equal-precedence reduction is left to right; for example,
`8-3-2+1` produces `83-2-1+` and result 4.

The D3 classifications are:

| Input | Within assumptions? | Result if valid | Reason |
|---|---|---:|---|
| `"7"` | no | — | shorter than the fixed seven-token scan |
| `"1-2*3+4"` | yes | -1 | precedence and operand order |
| `"8/2/2+1"` | yes | 3 | division is left associative |
| `"7%4+1*2"` | yes | 5 | remainder and multiplication precede addition |
| `""` | no | — | shorter than seven tokens |
| `"1+"` | no | — | too short and missing an operand |
| `"12+3"` | no | — | too short and multi-digit operands unsupported |
| `"1 +2"` | no | — | too short and spaces unsupported |
| `"(1+2)"` | no | — | too short and parentheses unsupported |
| `"1/0+2*3"` | no | — | zero divisor |
| more than seven characters | no | — | exceeds fixed expression buffers |

Core input has exactly seven characters: four single digits alternating with
three `+ - * / %` operators, plus the terminator in `eq[7]`. No spaces,
parentheses, unary operators, or multi-digit operands are supported. Divisors
are nonzero and intermediates fit `int`. The source does not validate these
conditions: an early terminator or unsupported character has precedence 0
and can pop the sentinel, leading to an empty peek. These are limitations,
not promised safe rejections. General parsing and checked arithmetic are
extensions.

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

The Stack ADT is LIFO behavior. `int stack[10]` plus shared `size` is one
explicit representation, reused across the two expression phases. Runtime
call-stack bookkeeping supports actual C calls. A character such as `'A'`
is a teaching label; storing it does not create a call frame. The variable
name does not enforce LIFO; `push`, `peek`, and `pop` implement that rule.

### H. Exit ticket

A complete response identifies the nonempty top as `stack[size - 1]`, the
count as `size`, and the unchecked boundary preconditions. It distinguishes
shared Stack count `size`, local output cursor `pos`, and seven-token length;
explains the stored sentinel and shared-array resets; states
`1-2*3+4 -> 123*-4+ -> -1`; and identifies at least one missing check.
Questions can be sorted into behavior, indexes, representation, expression
phases, C notation, or evidence needs.

## Current lab evidence and tests

The demo should report:

```text
infix: 1-2*3+4
postfix: 123*-4+
result: -1
```

The current `code/tests/test_lab.c` exercises integer LIFO, full/empty
boundaries, canonical conversion, precedence and operand order, repeated seven-character
conversions with shared-state resets, and the distinction between character digits and numeric
results. Use `make lab-demo` and `make lab-tests` from `code`, or
`build.ps1 -Target lab` and `build.ps1 -Target lab-tests` on PowerShell.

Students add exactly three justified cases to the current lab test file:

1. a LIFO sequence, such as pop then push a different visible character;
2. a boundary-predicate or valid-operation case comparing `size` and all
   ten stored integers, without invoking undefined behavior;
3. a seven-character expression case checking `eq_re`, its terminator, final
   `size`, and numeric result.

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
