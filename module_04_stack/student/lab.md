# Lab — A Character Stack, Infix Conversion, and Postfix Evaluation

## Purpose

Trace and verify the implementation in [lab.c](lab.c). It first uses a
character Stack to convert infix to postfix, then uses a separate integer
Stack to evaluate postfix:

```text
1-2*3+4  →  123*-4+  →  -1
```

The source file is the core exercise. The older caller-owned integer Stack
and checked evaluator in `code/starter`, `code/solution`, and `code/include`
are optional legacy comparisons with different interfaces and guarantees.
They are not required implementations for this lab.

## 1. Read the stored state

```c
char stack[10];
int capacity = 10;
int top = 10;
char infix[8] = "1-2*3+4";
char postfix[8] = "";
int size = 0;
```

These are global objects. The character Stack grows toward lower indexes.
Its invariant is `0 <= top <= 10`; active cells occupy `top` through 9.
Empty means `top == 10`, full means `top == 0`, and a nonempty top is
`stack[top]`. The item count is `10 - top`.

`capacity` records the intended ten positions, but this implementation uses
literal `10` in its boundaries. Changing `capacity` alone has no effect on
the actual array or checks. The global `size` counts characters written to
`postfix`, excluding the terminating `'\0'`; it is not a Stack item count.

## 2. Trace the character Stack

| Function | Actual behavior |
|---|---|
| `is_full()` | Reports whether `top == 0` |
| `push(char data)` | If full, does nothing; otherwise decreases `top` and writes `stack[top]`; returns no value |
| `is_empty()` | Reports whether `top == 10` |
| `peek()` | If empty, returns `'\0'`; otherwise returns `stack[top]`; changes nothing |
| `pop()` | If empty, returns `'\0'`; otherwise saves `stack[top]`, increases `top`, and returns the saved character |

Begin with `top == 10` and trace:

```text
push('A'), push('B'), push('C'), peek(), pop(), pop(), pop()
```

Record each return, `top`, and logical state from bottom to top. Locate each
character physically as well: the logical order is not increasing array
index order. Show why pop can leave old characters in inactive cells.

Use ordinary nonzero character labels. A stored `'\0'` would be
indistinguishable from the empty return value using the return alone.

## 3. Trace infix-to-postfix conversion

`prec(op)` returns 1 for `+` or `-`, 2 for `*`, `/`, or `%`, and 0 otherwise.
`infix_to_postfix()` performs these steps:

1. Set `size = 0`; begin with the operator Stack already empty.
2. Read `infix` until its `'\0'` terminator.
3. Append each digit directly to `postfix`.
4. For an operator, pop waiting operators of equal or greater precedence
   into `postfix`, then push the incoming operator.
5. Drain the remaining operators at end of input.
6. Write `postfix[size] = '\0'` without counting that terminator.

For `1-2*3+4`, the completed output is `123*-4+`, `size` is 7, and `top` is
10. The `>=` comparison makes equal-precedence operators left associative.
This phase rearranges characters; it does not calculate the numeric answer.

Conversion resets the output count but does not reset `top` at entry. A
successful conversion drains the Stack, so another valid conversion starts
empty if no intervening character operations leave items there. Stale output
characters beyond the new terminator do not belong to the new result.

## 4. Trace postfix evaluation

`eval_postfix()` starts with a local `int values[10]` and `pos = 0`. This
Stack uses an active prefix, indexes 0 through `pos - 1`.

- `values[pos++] = c - '0'` pushes a numeric digit and increases the count.
- `values[--pos]` decreases the count before reading a popped value.
- At an operator, pop `num2` first, then `num1`.
- Push `calc(num1, num2, c)` as the replacement value.

`calc` supports `+`, `-`, `*`, integer `/`, and remainder `%`. Operand order
matters: the calculation is `num1 - num2` or `num1 / num2`, not its reverse.
The postfix trace calculates `2*3 = 6`, `1-6 = -5`, then `-5+4 = -1`.
The input operands are single digits, but intermediate values can be negative
or larger than 9 because `values` stores integers.

Evaluation processes exactly `size` tokens; it does not process the string
terminator. With valid postfix, one value remains before the final
`return values[--pos]`.

## 5. Keep the input assumptions visible

For this core exercise, use inputs with all these properties:

- a nonempty alternating sequence of single digit, operator, single digit,
  and so on;
- only `+`, `-`, `*`, `/`, and `%` operators;
- at most seven input characters, with space for `'\0'` in `infix[8]`;
- no whitespace, parentheses, unary signs, or multi-digit operands;
- nonzero divisors and arithmetic results representable as C `int`; and
- an empty character operator Stack at conversion entry.

The implementation does not validate this grammar, operand counts, zero
divisors, output bounds, or arithmetic overflow. Do not describe these as
checked rejections or claim that `calc`'s default return makes malformed
expressions safe. Such cases are discussion topics and possible extensions.
The full/empty guards apply to the character Stack only; the local `values`
operations have no corresponding guards.

## 6. Build and observe

`lab.c` has no `main`. The supplied driver `code/lab_demo.c` provides the
entry point and links the same source file. The supplied tests are in
`code/tests/test_lab.c`; they also link `student/lab.c` directly.

Run from the `module_04_stack/code` directory with GNU Make:

```sh
make lab-demo
make lab-tests
make autopsy
```

The default `make` target runs the lab demo. For PowerShell:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 -Target lab
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 -Target lab-tests
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 -Target autopsy
```

Predict the autopsy before running it. Use the build instructions in
`code/README.md` for compiler setup or supported diagnostic options.

Record the compiler and complete command with the output. The current
no-parameter definitions use `()`; under C11, writing `(void)` explicitly
states that a function takes no parameters and can resolve prototype
warnings. Record actual diagnostics instead of assuming a quiet run.

## 7. Add exactly three student tests

Keep the supplied tests intact and add three justified cases to
`code/tests/test_lab.c`. Use the existing harness style and make sure each
new case is called. State what additional claim each tests.

1. A character LIFO sequence with repeated values or interleaved push/pop.
2. A full/empty boundary or inactive-cell case that checks both the returned
   character, when applicable, and preserved `top` or array contents.
3. A valid expression or a sequence of valid conversions that checks the
   postfix text, `size`, terminator, final `top`, and integer result.

Choose cases that add evidence beyond the baseline tests. Reset the global
Stack deliberately between independent cases. Keep expression strings within
seven characters plus their terminator. Do not treat unsupported input as
though a safe rejection contract exists.

Run `make lab-tests` or the PowerShell `lab-tests` target again and preserve
the transcript. Then complete [stack_autopsy.md](stack_autopsy.md).

## 8. Explain costs and limits

Character `push`, `peek`, and `pop` each do a fixed amount of work: `O(1)`.
None shifts existing items. For `n` valid tokens, each operator is pushed and
popped at most once during conversion, giving `O(n)` total work. Evaluation
also takes `O(n)`. The present arrays have fixed bounds, so storage is `O(1)`;
the current input limit is seven tokens. If capacities were generalized to
grow with input, storage would be `O(n)` in the worst case.

Optional extensions include input validation, guarded operand operations,
zero-divisor checks, checked arithmetic, a consistent capacity constant, or
an explicit error status. Explain the new contract before claiming those
features. They are not guarantees of the current source.

## Required submission

1. The examined `student/lab.c`, including any instructor-assigned changes.
2. The extended `code/tests/test_lab.c` with exactly three justified new cases.
3. Reproducible demo and passing lab-test transcripts, including diagnostics.
4. The completed evidence record and Stack-Top Autopsy.
5. The preserved and corrected Cognitive Pause.

Completion means the traces and tests match the actual implementation,
full/empty character operations preserve their stated boundaries, both
expression phases are explained, and unsupported-input assumptions are
clearly distinguished from implemented checks.
