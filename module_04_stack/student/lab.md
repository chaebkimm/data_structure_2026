# Lab — An Integer Stack, Infix Conversion, and Postfix Evaluation

## Purpose

Use the rules and terminology in the
[Korean textbook](textbook_korean.md) to trace and verify the implementation
in [lab.c](lab.c). It uses one global
integer Stack first to convert infix to postfix, then reuses it to evaluate
postfix:

```text
1-2*3+4  →  123*-4+  →  -1
```

The textbook first calculates directly with an operator Stack and a number Stack.
When `+` arrives, it reduces `2*3` to 6 and then `1-6` to -5 before storing
`+`. Postfix records that calculation order. This source separates recording
the order from carrying out the arithmetic.

The source file is the core exercise. The older caller-owned integer Stack
and checked evaluator in `code/starter`, `code/solution`, and `code/include`
are optional legacy comparisons with different interfaces and guarantees.
They are not required implementations for this lab.

The [lab lecture source](ppt_lab_material.md) guides the code-reading order:
array Stack, operator precedence and `switch`, `while` and `&&`, conversion,
then evaluation. The grouped-expression section extends that sequence.

## Connect the textbook to the lab

Use these terms in your explanations and trace records:

| Textbook term | Meaning in this lab |
|---|---|
| 데이터 | A stored data value; the array holds integers |
| 마지막 데이터 | The most recently added data value still in the Stack, at `stack[top]` |
| 추가 (`push`) | Increase `top`, then store data at `stack[top]` |
| 확인 (`peek`) | Return the last data value without changing the stored state |
| 삭제 (`pop`) | Read `stack[top]`, decrease `top`, and return the removed data value |
| 규칙 | Only the last data value can be inspected or removed; other active data stays in place |

Before running the code, connect the textbook's expression models on paper:

1. Add parentheses to `1-2*3+4` so that each operation is grouped according
   to precedence and left associativity. When a closing parenthesis arrives,
   identify the most recently opened group and the result that replaces it.
2. Trace the same calculation with a separate operator Stack and number
   Stack. When `+` arrives, identify every waiting operation that must finish
   before `+` can be added.
3. Write each operator at the moment that calculation would happen. Compare
   the resulting postfix expression with `postfix` after conversion.

Then trace the dedicated parentheses converter with `1+(2+3)`. It records
the grouped addition before the outer addition: `123++`, which evaluates to 6.
The two converter functions and their input assumptions are described below.

## 1. Read the stored state

```c
int stack[10];
int capacity = 10;
int top = -1;
char eq[8] = "1-2*3+4";
char postfix[8] = "";
char eq_paren[8] = "1+(2+3)";
```

The functions share these global objects. `stack` holds integer values; character
labels and operators can also be stored as their integer character codes.
It grows toward higher indexes. With `capacity == 10`, maintain
`-1 <= top < capacity`: active cells occupy 0 through `top`, empty is
`top == -1`, and full is `top + 1 == capacity`. The item count and next insertion index
are both `top + 1`; the last data value in a nonempty Stack is `stack[top]`.

`capacity` is used by `is_full()` only. Changing it does not resize the array
or make `push` stop. `eq` holds infix input and `postfix` holds postfix output.
Conversion uses a local output cursor `pos`, separate from the shared top index.

## 2. Trace the shared integer Stack

| Function | Actual behavior and required state |
|---|---|
| `is_full()` | Reports whether `top + 1 == capacity`; changes nothing |
| `push(int data)` | `stack[++top] = data`: increase `top`, then write at the new index; caller must ensure room |
| `is_empty()` | Reports whether `top == -1`; changes nothing |
| `peek()` | Returns integer `stack[top]`; caller must ensure nonempty; changes nothing |
| `pop()` | Returns integer `stack[top--]`: read at the old `top`, then decrease `top`; caller must ensure nonempty |

These operations contain no boundary guards. A full push selects `stack[10]`;
an empty peek or pop selects `stack[-1]`. Those calls have undefined behavior,
so no return value or preserved final state is promised. Diagnose them on paper;
use the predicates to avoid invalid calls in runnable tests.

Begin with `top == -1` and trace:

```text
push('A'), push('B'), push('C'), peek(), pop(), pop(), pop()
```

Record each return, `top`, and logical state from first to last. Locate each
label physically: the logical order follows increasing array index order.
Explain why pop leaves old values in inactive cells. A stored `0` or `'\0'`
is ordinary data; it is not an empty-read result.

## 3. Trace infix-to-postfix conversion

`prec(op)` uses `switch` to select an operator group: `*`, `/`, and `%`
return 2; `+` and `-` return 1; `default` returns 0. Each matching case
returns immediately. The function does not validate expression syntax.

Before tracing, read the two conditions. `while (!is_empty())` checks for
a stored item before its body runs. In `c >= '0' && c <= '9'`, both
comparisons must be true; if the first is false, the second is not evaluated.

`convert_to_postfix()` performs these steps:

1. Initialize local `pos = 0` and reset global `top = -1`.
2. Read `eq[i]` while `eq[i] != '\0'`; stop before the input terminator.
3. Append each digit directly with `postfix[pos++] = c`.
4. For an operator, check `!is_empty()` before inspecting the top. If
   `prec(op) < prec(c)`, `break` exits that operator-pop loop. Otherwise,
   append the popped operator and repeat. Then push the incoming operator.
5. Pop and append all remaining operators while the Stack is nonempty.
6. Write `postfix[pos++] = '\0'` explicitly after the Stack is empty.

The nonempty check prevents an empty `peek()`. The `break` preserves a
waiting operator of lower precedence for later. Equal precedence does not
break the loop, so equal-precedence operators are emitted from left to right.
There is no bottom sentinel in this implementation.

For `1-2*3+4`, the Stack begins empty. It holds at most two operators,
`-` and `*`, with `top == 1`. Incoming `+` emits both before being pushed.
The final drain emits `+`, producing `123*-4+`, with `top == -1` and
`pos == 7`. The separate terminator write stores `'\0'` at `postfix[7]`
and advances `pos` to 8. Token length stays 7.

Conversion rearranges characters without calculating a numeric answer.
Each call resets `top` and the local cursor. For an output of `m` tokens,
the final explicit write stores `'\0'` at `postfix[m]` and leaves
`pos == m + 1`. There is no global output-length variable.

## 4. Trace postfix evaluation

`eval_postfix()` resets global `top = -1` and reuses the same `int stack[10]`
for numeric operands and intermediate results.
It reads while `postfix[i] != '\0'`:

- `push(c - '0')` stores a digit's numeric value.
- An operator first calls `pop()` for right operand `num2`, then for left
  operand `num1`.
- `push(calc(num1, num2, c))` stores the replacement value.

`calc` supports `+`, `-`, `*`, integer `/`, and remainder `%`. Order matters for
subtraction, division, and remainder. The canonical trace calculates `2*3 = 6`,
`1-6 = -5`, then `-5+4 = -1`. Intermediate values can be negative or larger
than 9 because the shared array stores integers.

The loop excludes the terminator, wherever it appears. For the canonical
result, the terminator is `postfix[7]`. With valid postfix, one number
remains before the final `return pop()`, which returns -1 and leaves `top == -1`.

## 5. Keep grouped operations together

`infix_to_postfix_parentheses()` reads `eq_paren` until `'\0'` and writes
into the same `postfix` buffer. It begins with `pos = 0` and `top = -1`.

- A digit goes directly to the output.
- An opening `(` is pushed. Its precedence is 0, so an ordinary incoming
  operator breaks the reduction loop when `(` is on top.
- At `)`, the function repeats only while nonempty. It first pops into `op`.
  If `op == '('`, `break` exits the loop; the opening parenthesis has already
  been removed and is not written. Other popped operators go to the output.
- An ordinary operator uses the same guarded precedence loop as the plain
  converter. Equal or greater precedence is emitted before the new operator.
- The final drain emits remaining operators. A separate assignment writes
  the output terminator.

For `1+(2+3)`, after reading `3` the Stack contains outer `+`, `(`, inner
`+`, with `top == 2`. The closing `)` emits the inner `+`, then pops and
discards `(`. The final drain emits the outer `+`, producing `123++` with
`pos == 5` and `top == -1`. The explicit terminator write stores `'\0'`
at `postfix[5]` and advances `pos` to 6. Evaluation computes `2+3 = 5`,
then `1+5 = 6`; its final pop also leaves `top == -1`.

Use balanced parentheses with valid contents. The function does not check
matching groups. An unmatched `)` can be silently consumed after draining
operators; the nonempty guard prevents conversion from popping an empty
Stack. An unmatched `(` can appear in postfix output. Neither behavior is
safe validation, and malformed postfix can still underflow evaluation.

## 6. Keep the input assumptions visible

For this core exercise, use inputs with all these properties:

- a nonempty valid expression of at most seven input characters, followed
  by `'\0'` within the eight-cell input buffer;
- single-digit operands and binary `+`, `-`, `*`, `/`, or `%` operators;
- no parentheses in `eq` for `convert_to_postfix()`; balanced parentheses
  are allowed in `eq_paren` for `infix_to_postfix_parentheses()`;
- no whitespace, unary signs, or multi-digit operands; and
- nonzero divisors and arithmetic results representable as C `int`.

Shorter expressions such as `7` and `1+2` are supported. All expression scans
stop at the null terminator. The code does not validate grammar,
operand counts, zero divisors, output bounds, or arithmetic overflow. Do not
claim safe rejection or assume `calc`'s default return makes malformed input
safe. Conversion and evaluation reset `top` themselves; previous active
data values are discarded by that reset.

## 7. Build and observe

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
warnings. Integer-to-character conversions can also produce narrowing
warnings. Record actual diagnostics instead of assuming a quiet run.

## 8. Add exactly three student tests

Keep the supplied tests intact and add three justified cases to
`code/tests/test_lab.c`. Use the existing harness style and make sure each
new case is called. State what additional claim each tests.

1. An integer LIFO sequence with repeated values or interleaved push/pop;
   character labels may be stored as integer codes.
2. A full/empty predicate or valid boundary-operation case that checks the
   count and array contents without calling push when full or reading when empty.
3. A valid expression or a sequence of valid conversions that checks the
   `postfix` text, terminator at the actual output length, final `top`,
   and integer result. Include a shorter or grouped expression if it adds
   evidence beyond the supplied cases.

Choose cases that add evidence beyond the baseline tests. Reset the global
Stack deliberately between independent cases. Keep expression strings within
seven characters plus their terminator. Choose the converter that supports
the syntax. Do not treat unsupported input as though a safe rejection
contract exists.

Run `make lab-tests` or the PowerShell `lab-tests` target again and preserve
the transcript. Then complete [stack_autopsy.md](stack_autopsy.md).

## 9. Explain costs and limits

Valid `push`, `peek`, and `pop` calls each do a fixed amount of work: `O(1)`.
None shifts existing data. For `n` valid input characters, each operator or
opening parenthesis is pushed and popped at most once during conversion,
giving `O(n)` total work. Evaluation takes linear work in its postfix token
count. The present arrays have fixed bounds, so storage is `O(1)`;
the current input limit is seven characters, including any parentheses.
If capacities were generalized to grow with input, storage would be `O(n)` in the worst case.

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
Stack callers respect the unchecked operation preconditions, both
expression phases are explained, and unsupported-input assumptions are
clearly distinguished from implemented checks.
