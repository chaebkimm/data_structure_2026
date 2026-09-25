# Lab — An Integer Stack, Infix Conversion, and Postfix Evaluation

## Purpose

Trace and verify the implementation in [lab.c](lab.c). It uses one global
integer Stack first to convert infix to postfix, then reuses it to evaluate
postfix:

```text
1-2*3+4  →  123*-4+  →  -1
```

The PPT first calculates directly with an operator Stack and a value Stack.
When `+` arrives, it reduces `2*3` to 6 and then `1-6` to -5 before storing
`+`. Postfix records that calculation order. This source separates recording
the order from carrying out the arithmetic.

The source file is the core exercise. The older caller-owned integer Stack
and checked evaluator in `code/starter`, `code/solution`, and `code/include`
are optional legacy comparisons with different interfaces and guarantees.
They are not required implementations for this lab.

## 1. Read the stored state

```c
int stack[10];
int capacity = 10;
int size = 0;
char eq[8] = "1-2*3+4";
char eq_re[8] = "";
```

The functions share these global objects. `stack` holds integer values; character
labels and operators can also be stored as their integer character codes.
It grows toward higher indexes. With `capacity == 10`, maintain
`0 <= size <= capacity`: active cells occupy 0 through `size - 1`, empty is
`size == 0`, and full is `size == capacity`. The count and next insertion index
are both `size`; the nonempty top is `stack[size - 1]`.

`capacity` is used by `is_full()` only. Changing it does not resize the array
or make `push` stop. `eq` holds infix input and `eq_re` holds postfix output.
Conversion uses a local output cursor `pos`, separate from the shared Stack count.

## 2. Trace the shared integer Stack

| Function | Actual behavior and required state |
|---|---|
| `is_full()` | Reports whether `size == capacity`; changes nothing |
| `push(int data)` | `stack[size++] = data`: write at the old index, then increase `size`; caller must ensure room |
| `is_empty()` | Reports whether `size == 0`; changes nothing |
| `peek()` | Returns integer `stack[size - 1]`; caller must ensure nonempty; changes nothing |
| `pop()` | Returns integer `stack[--size]`: decrease `size`, then read; caller must ensure nonempty |

These operations contain no boundary guards. A full push selects `stack[10]`;
an empty peek or pop selects `stack[-1]`. Those calls have undefined behavior,
so no return value or preserved final state is promised. Diagnose them on paper;
use the predicates to avoid invalid calls in runnable tests.

Begin with `size == 0` and trace:

```text
push('A'), push('B'), push('C'), peek(), pop(), pop(), pop()
```

Record each return, `size`, and logical state from bottom to top. Locate each
label physically: the logical order follows increasing array index order.
Explain why pop leaves old values in inactive cells. A stored `0` or `'\0'`
is an ordinary item; it is not an empty-read result.

## 3. Trace infix-to-postfix conversion

`prec(op)` returns 1 for `+` or `-`, 2 for `*`, `/`, or `%`, and 0 otherwise.
`infix_to_postfix()` performs these steps:

1. Initialize local `pos = 0`, reset global `size = 0`, then `push('\0')`.
2. Read exactly seven positions, `eq[0]` through `eq[6]`.
3. Append each digit directly with `eq_re[pos++] = c`.
4. For an operator, pop waiting operators of equal or greater precedence
   into `eq_re`, then push the incoming operator.
5. Drain every remaining Stack item, including the bottom `'\0'` sentinel.

The sentinel has precedence 0, below every supported operator. It stops the
operator-pop loop before an empty peek. It remains a real active item during
conversion and contributes one to `size`. The final drain writes it to
`eq_re[7]`, terminating the string. Because that write also increments `pos`,
`pos` ends at 8 while the postfix token length is 7 and global `size` is 0.
There is no global output-length variable.

For `1-2*3+4`, the output is `123*-4+`. The `>=` comparison gives equal-precedence
operators left associativity. This phase rearranges characters; it does not
calculate the numeric answer. Each call resets both the Stack count and local
cursor, so a later supported seven-character conversion starts afresh.

## 4. Trace postfix evaluation

`eval_postfix()` resets global `size = 0` and reuses the same `int stack[10]`
for numeric operands and intermediate results. It does not push a sentinel.
For exactly seven tokens, `eq_re[0]` through `eq_re[6]`:

- `push(c - '0')` stores a digit's numeric value.
- An operator first calls `pop()` for right operand `num2`, then for left
  operand `num1`.
- `push(calc(num1, num2, c))` stores the replacement value.

`calc` supports `+`, `-`, `*`, integer `/`, and remainder `%`. Order matters for
subtraction, division, and remainder. The canonical trace calculates `2*3 = 6`,
`1-6 = -5`, then `-5+4 = -1`. Intermediate values can be negative or larger
than 9 because the shared array stores integers.

The loop excludes `eq_re[7]`, the terminator. With valid postfix, one number
remains before the final `return pop()`, which returns -1 and leaves `size == 0`.

## 5. Keep the input assumptions visible

For this core exercise, use inputs with all these properties:

- exactly seven characters: four single digits alternating with three
  binary operators;
- only `+`, `-`, `*`, `/`, and `%` operators;
- a terminating `'\0'` in `eq[7]`, within `eq[8]`;
- no whitespace, parentheses, unary signs, or multi-digit operands; and
- nonzero divisors and arithmetic results representable as C `int`.

Shorter valid mathematical expressions are outside this implementation:
both loops still process seven positions. The code does not validate grammar,
operand counts, zero divisors, output bounds, or arithmetic overflow. Do not
claim safe rejection or assume `calc`'s default return makes malformed input
safe. Conversion and evaluation reset `size` themselves; previous active
items are discarded by that reset.

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
warnings. Integer-to-character conversions can also produce narrowing
warnings. Record actual diagnostics instead of assuming a quiet run.

## 7. Add exactly three student tests

Keep the supplied tests intact and add three justified cases to
`code/tests/test_lab.c`. Use the existing harness style and make sure each
new case is called. State what additional claim each tests.

1. An integer LIFO sequence with repeated values or interleaved push/pop;
   character labels may be stored as integer codes.
2. A full/empty predicate or valid boundary-operation case that checks the
   count and array contents without calling push when full or reading when empty.
3. A valid expression or a sequence of valid conversions that checks the
   `eq_re` text, terminator at index 7, final `size`, and integer result.

Choose cases that add evidence beyond the baseline tests. Reset the global
Stack deliberately between independent cases. Keep expression strings at exactly
seven characters plus their terminator. Do not treat unsupported input as
though a safe rejection contract exists.

Run `make lab-tests` or the PowerShell `lab-tests` target again and preserve
the transcript. Then complete [stack_autopsy.md](stack_autopsy.md).

## 8. Explain costs and limits

Valid `push`, `peek`, and `pop` calls each do a fixed amount of work: `O(1)`.
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
Stack callers respect the unchecked operation preconditions, both
expression phases are explained, and unsupported-input assumptions are
clearly distinguished from implemented checks.
