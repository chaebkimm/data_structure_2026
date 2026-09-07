# Technical Notes — Module 4 Fixed Integer Stack

## Scope

The production model for this module is a Stack ADT represented by a
caller-owned fixed integer array and two separate metadata values. The Stack
functions borrow fixed storage; they never change its extent or clear it.

```c
int stack[10];
int size = 0;
int capacity = 10;
```

The example capacity is ten, but the three public Stack functions operate on
any caller-supplied nonnegative capacity that accurately describes the
prepared array. The element values are generic integers. Function IDs 100,
200, and 300 are the canonical teaching data, not a restriction on values.

The transfer application is a deliberately narrow expression evaluator. It
does not accept whitespace, parentheses, signs, multi-digit values,
subtraction, division, variables, or general programming-language syntax.

## Exact public API

```c
int int_stack_push(int stack[], int size, int capacity, int value);

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

int expression_evaluate(const char expression[], int *out_result);
```

There is no public Stack structure or status enumeration. Size is threaded
through push and pop returns; peek and evaluator use Boolean-style 1/0
results.

## Numerical invariant and physical precondition

Valid metadata satisfies exactly:

```text
0 <= size <= capacity
```

This numerical relationship cannot prove the physical length of an array
received through a C parameter. The caller must ensure that `capacity`
matches the number of usable positions. Passing a larger number can permit an
out-of-bounds access that the callee cannot detect.

The operation contracts also require a non-`NULL` array pointer. Peek and pop
require a non-`NULL` output pointer. The header requires the output location
to be separate from the Stack array. Keep this caller obligation explicit;
the functions do not attempt to diagnose aliasing.

Empty and full are valid completed states:

- `size == 0` means no top exists, so peek and pop reject underflow;
- `size == capacity` means push rejects before writing; and
- capacity zero is valid metadata, but no push can succeed.

Negative size, negative capacity, or size greater than capacity is invalid
metadata. Because a rejected push/pop returns the original size, an invalid
negative or excessive size is returned unchanged.

## Logical index ranges

For a valid state:

```text
logical items:       stack[0] through stack[size - 1]
top when nonempty:   stack[size - 1]
inactive positions:  stack[size] through stack[capacity - 1]
next push position:  stack[size] when size < capacity
```

An inactive position may contain any prior or prepared integer bits. Physical
allocation does not confer logical membership. This distinction is the basis
of the Stack-Top Autopsy.

## `int_stack_push`

Required order:

1. validate `size` and `capacity`;
2. reject a full Stack;
3. reject a missing array;
4. write `value` at the old `size`; and
5. return `size + 1`.

The first three checks may be combined because none mutates state. On every
rejection, return the original size and leave every supplied array position
unchanged. On success, only the old `stack[size]` position changes.

Checking full before indexing is essential. In a full state,
`stack[capacity]` is one position past the caller's stated boundary.

## `int_stack_peek`

Reject invalid metadata, empty state, a missing array, or a missing output.
Return zero and preserve the output. On success:

```c
int result = stack[size - 1];
*out_value = result;
return 1;
```

The local candidate makes the commit point visible. Peek does not change the
array or metadata. Because size is passed by value, it could not change the
caller's size directly in any case.

Do not calculate `size - 1` before proving `size > 0`. With signed `int`, an
empty state would produce `-1`; indexing with that value is outside the
array.

## `int_stack_pop`

Pop uses the same validation and top read as peek. On success, it writes the
former top to the output and returns `size - 1`. It receives `const int
stack[]` because logical removal requires no array write.

The old top bits remain in the array. Once the caller saves the smaller
returned size, that position is inactive and is no longer observable through
the Stack contract. A later successful push may overwrite it.

On rejection, pop returns the original size and preserves the output. Notice
that an empty pop returns zero, which is also the size after popping a
one-item Stack. This API communicates its primary result as a size, not a
distinct status. A caller must establish whether a pop was permitted from
the prior state.

## Failure preservation

For this module, a rejection must occur before any promised observable write:

| Operation | Rejection return | Preserved information |
|---|---:|---|
| `push` | original size | every array position |
| `peek` | 0 | entire array and `*out_value` |
| `pop` | original size | entire array and `*out_value` |
| `expression_evaluate` | 0 | `*out_result` |

Tests should seed inactive cells and output variables with distinctive values
so that an accidental write is visible. Comparing only logical values is not
enough to prove the stronger “array unchanged” push contract.

## Evaluator grammar

The exact accepted language is:

```text
expression := digit (('+' | '*') digit)*
digit      := '0' | '1' | ... | '9'
```

The string must be nonempty and null-terminated. Tokens alternate digit,
operator, digit, and so on. `*` has precedence two and `+` precedence one.
Operators with equal precedence associate from left to right.

C guarantees that the character codes for `'0'` through `'9'` are
consecutive. Therefore `current - '0'` portably converts a validated digit to
its numeric value; the implementation need not assume ASCII code 48.

## Two internal fixed Stacks

The evaluator maintains:

```c
int numbers[10];
char operators[10];
int number_size = 0;
int operator_size = 0;
```

Both are fixed, local, ten-position Stack representations. Operator character
values are stored in a character array, while their access still follows the
same LIFO rule. Every number push uses `int_stack_push`; every operator push
checks `operator_size` before writing.

Ten limits simultaneous occupancy, not input length. An expression containing
more than ten total tokens may succeed because reductions pop values and
reuse positions. With this two-operator grammar and eager reductions, live
occupancy remains small, but the capacity checks are still part of the
contract and protect the algorithm if its scheduling changes.

## Parser state machine

Begin with `expecting_number = 1`.

- When expecting a number, accept exactly one digit, push its integer value,
  and switch to expecting an operator.
- When expecting an operator, accept only `+` or `*`, reduce every waiting
  operator whose precedence is equal or greater, push the current operator,
  and switch to expecting a number.
- At the null terminator, reject an empty string or a state still expecting a
  number. Otherwise reduce all waiting operators.
- Accept only if exactly one number remains and no operator remains.

The equal-precedence comparison is `>=`, not `>`. That choice produces left
associativity. For example, `2*3*4` reduces `2*3` before pushing the second
`*`.

## Applying one operator

Reduction follows this order:

1. select the current top operator without retiring it;
2. pop the right operand from the working number size;
3. pop the left operand;
4. perform the checked calculation;
5. push the candidate result; and
6. only after all of those steps succeed, commit the number size and retire
   the selected operator by decreasing the operator size.

The order matters for noncommutative operators even though the current
grammar happens to contain only commutative `+` and `*`. Teaching the stable
left/right convention avoids a hidden defect if the exercise is extended.

The local working number size may change while a reduction is attempted, but
the evaluator commits the shared sizes only after every expected return is
confirmed. A failure from an internal operation rejects the whole expression.

## Checked `int` arithmetic

All accepted operands and intermediate results are nonnegative. The solution
can therefore use these checks before the C operation:

```text
addition:       left <= INT_MAX - right
multiplication: left == 0 or right <= INT_MAX / left
```

Performing a signed operation first and checking afterward is not valid;
signed integer overflow has undefined behavior in C. Compute into a local
candidate only after the inequality succeeds.

The evaluator keeps the caller result untouched during parsing and
reduction. It writes `*out_result` only after exactly one valid checked result
remains. This single final commit proves output preservation for malformed
input, capacity rejection, and overflow.

## Worked trace: `1+2*3`

| Event | Numbers, bottom to top | Operators, bottom to top | Work |
|---|---|---|---|
| start | empty | empty | none |
| read `1` | 1 | empty | push digit |
| read `+` | 1 | `+` | no waiting operator |
| read `2` | 1, 2 | `+` | push digit |
| read `*` | 1, 2 | `+`, `*` | `+` has lower precedence |
| read `3` | 1, 2, 3 | `+`, `*` | push digit |
| end, apply `*` | 1, 6 | `+` | `2 * 3 = 6` |
| end, apply `+` | 7 | empty | `1 + 6 = 7` |

The final output is committed only after the last row passes all checks.

## Complexity

- push, peek, and pop each do a fixed number of checks and at most one array
  read or write: `O(1)` time;
- no Stack operation shifts an existing item;
- each expression character is scanned once, and each operator is pushed and
  applied at most once: `O(n)` time for input length `n`; and
- the two ten-position arrays use `O(1)` extra storage under this fixed
  contract.

Every push does fixed work; there is no variable-cost storage change to
average across operations.

## Stack-Top Autopsy

The isolated fixture uses:

```text
stack:   [10][20][777][888]
index:     0   1   2    3
size: 2
capacity: 4
```

The intentionally faulty operation reads `stack[size]`, which reports 777.
The correct top is `stack[size - 1]`, which reports 20. Because index two is
inside the physical array, address diagnostics need not report a violation.
The first defect is logical: the operation reads the next inactive slot.

Keep the autopsy solution-independent. Students predict, run, preserve the
observation, name the first broken rule, repair the one-line expression, and
design a regression case using distinct top and inactive values.

## Testing expectations

The reference core covers eight claims:

1. push adds at the top;
2. peek reads without mutation;
3. pop reports LIFO without erasing;
4. full push preserves the array;
5. empty and zero-capacity cases fail safely;
6. invalid arguments preserve state;
7. expression precedence and associativity; and
8. invalid expressions preserve the result.

The instructor extension suite covers capacities zero through ten, a
deterministic model trace, valid cases including a long input, invalid syntax,
and checked overflow. The starter must remain warning-clean but intentionally
fail until students complete its TODOs.

## Portability and build discipline

The required language level is C11. The supported warning set is:

```text
-Wall -Wextra -Wpedantic -Wconversion -Wshadow
```

Use AddressSanitizer and UndefinedBehaviorSanitizer where supported. A clean
sanitizer run strengthens physical-safety evidence; it does not prove the
logical top contract, which is why the memory-safe autopsy remains necessary.
