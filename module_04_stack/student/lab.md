# Lab — A Fixed Integer Stack and Checked Expression Evaluator

## Purpose

Implement a Stack of generic integers in caller-owned fixed storage. Then use
a number Stack and an operator Stack to evaluate the transfer expression
`1+2*3` with checked input and arithmetic.

The canonical Stack trace uses function IDs:

```text
push 100: return size 1; state 100
push 200: return size 2; state 100, 200
push 300: return size 3; state 100, 200, 300
peek: return 1 and report 300; state unchanged
pop: return size 2 and report 300; state becomes 100, 200
```

Every state is listed from bottom to top.

## Stack behavior and fixed representation

The Stack abstract data type follows last in, first out (LIFO). `push` adds at
the top. `peek` reports the top without removing it. `pop` removes and reports
the top. Underflow is a `peek` or `pop` request on an empty Stack.

This module represents a Stack with three separate pieces of caller state:

```c
int stack[10];
int size = 0;
int capacity = 10;
```

The operations accept any suitable caller-owned integer array. Function IDs
are only the canonical example; the stored integers are generic data.

An invariant is a rule that is true in every valid completed state:

```text
0 <= size <= capacity
```

The caller must pass the actual prepared capacity. The functions cannot infer
an array's physical length from an array parameter.

When `size > 0`, logical items occupy indexes 0 through `size - 1`, and the
top is `stack[size - 1]`. If `size < capacity`, `stack[size]` is allocated but
inactive. It is the next unused position, not the top.

## Public Stack operations

An API is the public set of functions other code may call.

```c
int int_stack_push(
    int stack[],
    int size,
    int capacity,
    int value
);

int int_stack_peek(
    const int stack[],
    int size,
    int capacity,
    int *out_value
);

int int_stack_pop(
    const int stack[],
    int size,
    int capacity,
    int *out_value
);
```

### `int_stack_push`

- Reject a missing array, invalid metadata, or a full Stack.
- On rejection, return the original size and change no array item.
- On success, write `value` at `stack[size]` and return `size + 1`.
- The caller saves the returned size.

### `int_stack_peek`

- Reject a missing array, missing output, invalid metadata, or empty Stack.
- The caller must provide output storage separate from the Stack array.
- On rejection, return 0 and leave the output unchanged.
- On success, copy `stack[size - 1]` to the output and return 1.
- Never change the array or size.

### `int_stack_pop`

- Reject a missing array, missing output, invalid metadata, or empty Stack.
- The caller must provide output storage separate from the Stack array.
- On rejection, return the original size and leave the output unchanged.
- On success, copy `stack[size - 1]` to the output and return `size - 1`.
- Do not erase the old top. The returned smaller size makes that position
  inactive.

No Stack operation creates, resizes, or releases the caller's array.

## Checked expression contract

```c
int expression_evaluate(const char expression[], int *out_result);
```

The evaluator returns 1 on success and writes the answer. It returns 0 on any
rejection and leaves the caller's result unchanged.

Accepted input follows all these rules:

- the string is nonempty;
- tokens alternate single digit, operator, single digit, and so on;
- the only operators are `+` and `*`;
- there are no spaces, parentheses, unary operators, or multi-digit numbers;
- `*` has greater precedence than `+`;
- equal precedence is processed from left to right;
- every internal number/operator push fits its ten-position Stack; and
- every addition and multiplication fits the C `int` range.

The expression string may be longer than ten characters. The limit applies to
simultaneous occupancy of each internal Stack, not directly to input length.

For `1+2*3`, the evaluator waits with `+`, calculates `2*3`, and then
calculates `1+6`. The result is 7.

Keep a local candidate result. Commit it to `*out_result` only after parsing,
Stack operations, final reduction, and overflow checks all succeed.

## Files

You receive public headers, starter files, tests, build tools, and an isolated
autopsy.

Edit only:

- `code/starter/int_stack.c`;
- `code/starter/expression_evaluator.c`; and
- `code/tests/test_student.c`.

Do not edit public headers, supplied core tests, autopsy files, or build files
unless the instructor explicitly authorizes it.

## Checkpoints

### 1. Read before editing

Read:

- `code/include/int_stack.h`;
- `code/include/expression_evaluator.h`;
- all TODO comments in both starter files; and
- the first failing public-test requirement.

### 2. Implement `push`

1. Check required pointers and `0 <= size <= capacity`.
2. Reject when `size == capacity` before indexing the array.
3. Write the new value at the old `size`.
4. Return the new size.
5. Confirm every rejection returns the original size without changing the
   array.

### 3. Implement `peek` and `pop`

1. Check the array, output, and metadata.
2. Reject underflow before calculating `size - 1`.
3. Read only `stack[size - 1]`.
4. Change the output only on success.
5. Make `peek` return 1 without changing size.
6. Make `pop` return the smaller size without erasing the array position.

### 4. Implement checked expression evaluation

1. Reject missing pointers and empty input.
2. Alternate between expecting a digit and expecting an operator.
3. Reject every character outside the exact grammar.
4. Store digit values in the number Stack and operator character values in the
   operator Stack.
5. Before pushing an operator, apply waiting operators with equal or greater
   precedence.
6. Pop the right operand before the left operand.
7. Check addition and multiplication before performing a C `int` operation
   that would overflow.
8. Apply all waiting operators at end of input.
9. Accept only one final number and no remaining operator.
10. Write the caller's result only after complete success.

### 5. Run supplied tests

From the `code` directory in PowerShell:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1
```

The starter is intentionally incomplete, so tests fail at first. Work from
the earliest failure. Do not edit a supplied test merely to make it pass.

### 6. Design exactly three student tests

Replace the three placeholder bodies in `code/tests/test_student.c`.

1. Canonical LIFO test: push 100, 200, and 300; verify peek and pop order.
2. Rejection test: check a full, empty, invalid-metadata, or missing-output
   case and verify state or output preservation.
3. Expression test: verify one valid precedence case and one rejected grammar
   or arithmetic case, including the unchanged-output promise on rejection.

Use cases that add evidence beyond the supplied tests. Explain each claim in
a comment.

### 7. Run student tests and the autopsy

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target starter -StudentTests
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target autopsy
```

Complete `student/stack_autopsy.md` after predicting the autopsy output.

When the compiler supports sanitizers:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target starter -Sanitize
```

For GNU Make in Git Bash, MSYS2, WSL, Linux, or macOS:

```sh
make starter-core
make starter-student-tests
make autopsy
```

## Cost targets

`push`, `peek`, and `pop` each inspect or change a fixed number of values, so
each takes `O(1)` time. None shifts existing items.

For input length `n`, expression evaluation scans the input and processes each
token a bounded number of times. It takes `O(n)` time. The evaluator uses one
ten-position integer array and one ten-position character array, so its Stack
storage is `O(1)` for this fixed contract.

## Safe scope

Use only instructor-provided or student-created expressions. The evaluator is
not a complete calculator or programming-language parser. It intentionally
rejects syntax outside its small stated grammar. Success proves only that the
input satisfies this exercise's rules and that its checked result fits `int`.

## Required submission

1. Completed fixed-Stack and evaluator starter files.
2. A passing supplied core-test transcript.
3. Three passing student-authored tests with a rationale for each.
4. Warning-enabled and approved diagnostic evidence.
5. Completed evidence record.
6. Stack-Top Autopsy.
7. Corrected Cognitive Pause.

Completion means the functions satisfy their contracts, student-controlled
code has no compiler warnings, rejected operations preserve required state,
and the explanation distinguishes a logical top from an inactive array slot.
