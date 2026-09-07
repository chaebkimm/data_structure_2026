# Instructor Answer Key — Module 4 Fixed-Capacity Stack

## Macro-Question synthesis

A **Stack** permits access at one end, called the **top**. Its rule is **last
in, first out (LIFO)**: the most recently added item that remains is the first
item removed. If Function 100 starts 200 and Function 200 starts 300, then
300 finishes first, 200 resumes next, and 100 resumes after 200 finishes.

The Stack **abstract data type (ADT)** is this behavior contract. This module
represents it with a caller-owned fixed integer array, a logical `size`, and a
physical `capacity`. The representation is not the ADT itself.

## Stage A inquiry

The standard and linear inquiry prompts contain the same questions.

### A. Follow three function calls

- After Function 300 finishes, Function 200 resumes because it is the most
  recent unfinished caller.
- After Function 200 finishes, Function 100 resumes.

### B. Track unfinished functions

List IDs from earliest to most recent:

| Event | Before | Change | After |
|---|---|---|---|
| Start 100 | empty | add 100 | 100 |
| 100 starts 200 | 100 | add 200 | 100, 200 |
| 200 starts 300 | 100, 200 | add 300 | 100, 200, 300 |
| 300 finishes | 100, 200, 300 | remove 300 | 100, 200 |
| 200 finishes | 100, 200 | remove 200 | 100 |
| 100 finishes | 100 | remove 100 | empty |

The most-recent end changes at every start and finish.

### C. Test the access rule

1. Inspect 300 without removing it.
2. Remove 300 next.
3. Reject an inspection or removal from the empty record; do not invent an
   ID or change an output.
4. Removing 100 first would resume the oldest unfinished caller while its
   nested calls remain unfinished, reversing the required return order.

### D. Add a fixed boundary

- A ten-position record already containing ten IDs rejects ID 400.
- The ten stored IDs and count ten remain unchanged.
- A failed inspection leaves the output sentinel equal to 999.

### E. Macro-Question

A representative pre-vocabulary response is:

> Add, inspect, and remove at the same end so that the newest unfinished item
> is handled before older unfinished items.

After Stage B, name this LIFO.

### F. Transfer brainstorm

The value 1 and operator `+` wait while `2*3` is completed. A most-recent-first
rule lets the later higher-precedence work be completed before returning to
the waiting addition. Initial questions vary; use them to diagnose confusion
about precedence, stored values, or the exact grammar rather than scoring a
guessed algorithm.

## Stage B Cognitive Pause

### Target 1 — canonical trace

States are bottom to top.

| Request | Function return | Output | State | New size |
|---|---:|---:|---|---:|
| start | none | none | empty | 0 |
| `push(100)` | 1 | none | 100 | 1 |
| `push(200)` | 2 | none | 100, 200 | 2 |
| `push(300)` | 3 | none | 100, 200, 300 | 3 |
| `peek` | 1 | 300 | 100, 200, 300 | 3 |
| `pop` | 2 | 300 | 100, 200 | 2 |
| `pop` | 1 | 200 | 100 | 1 |
| `pop` | 0 | 100 | empty | 0 |

The greatest size is three. Immediately after the third push, 300 is at
index two.

### Target 2 — boundaries and preservation

1. A capacity-three Stack containing 100, 200, 300 rejects `push(400)`,
   returns the original size three, and preserves all array values.
2. Empty peek returns zero and leaves the output 999.
3. Empty pop returns the original size zero and leaves the output 999.

### Target 3 — expression transfer

`2*3` is applied before `1+...` because multiplication has higher precedence.
The result is seven. `1++2` is rejected because two operators occur where a
digit is required; every preexisting evaluator output remains unchanged.

## Stage C investigation

The standard and linear worksheets have the same sections. Linear labels such
as A1–A4 correspond to the same-letter standard prompts.

### A. Canonical function IDs

Use the Stage B trace above.

1. Greatest size: `3`.
2. Index storing 300: `2`.
3. Peek leaves 300 present because it reads but does not remove the top and
   does not change size.
4. Pop order: `300, 200, 100`.

### B. Operation contracts

| Operation | Success | Rejection | Rejection preserves |
|---|---|---|---|
| `push` | writes at old `stack[size]`; returns `size + 1` | returns original size | every array position |
| `peek` | writes `stack[size - 1]`; returns 1 | returns 0 | array and output |
| `pop` | writes `stack[size - 1]`; returns `size - 1` | returns original size | array and output |

Pop receives a const array because logical removal changes only the caller's
saved size. It does not erase the old top cell; those bits become inactive.

Size is passed by value, so the caller's variable changes only when the
caller assigns the returned size after a successful push or pop.

### C. Empty, full, and invalid cases

Start each row independently; use output 999 where required.

| Starting state and request | Accepted? | Return | Final output | Final state |
|---|---|---:|---:|---|
| empty, capacity 10; peek | no | 0 | 999 | empty; array unchanged |
| empty, capacity 10; pop | no | 0 | 999 | empty; array unchanged |
| 100, 200, 300; size 3, capacity 3; push 400 | no | 3 | none | all three values unchanged |
| size 4, capacity 3; push 400 | no | 4 | none | array unchanged; invalid metadata remains caller's responsibility |
| size 2, capacity 1; peek | no | 0 | 999 | array unchanged; invalid metadata rejected |
| 100, 200; size 2, capacity 10; pop | yes | 1 | 200 | logical Stack 100; array bits unchanged |

Explanations:

1. In a full Stack, `stack[size]` equals `stack[capacity]`, one position past
   the stated boundary. Reject before writing.
2. With size zero, no index belongs to the logical Stack; `size - 1` is `-1`.
3. The functions must honor the passed capacity three. A C array parameter
   does not carry the physical array length, so only the caller can ensure the
   capacity is truthful.

### D. `1+2*3`

| Input event | Number Stack | Operator Stack | Calculation |
|---|---|---|---|
| start | empty | empty | none |
| read `1` | 1 | empty | none |
| read `+` | 1 | `+` | none |
| read `2` | 1, 2 | `+` | none |
| read `*` | 1, 2 | `+`, `*` | none |
| read `3` | 1, 2, 3 | `+`, `*` | none |
| end, apply `*` | 1, 6 | `+` | `2 * 3 = 6` |
| end, apply `+` | 7 | empty | `1 + 6 = 7` |

Input classifications:

| Input | Decision | Result | Reason |
|---|---|---:|---|
| `"7"` | accept | 7 | one digit is a complete expression |
| `"1+2*3"` | accept | 7 | valid grammar and precedence |
| `""` | reject | none | expression is empty |
| `"1++2"` | reject | none | digit required after first `+` |
| `"12+3"` | reject | none | operator required after `1`; multi-digit operands are outside grammar |
| `"1 +2"` | reject | none | spaces are outside grammar |
| `"(1+2)"` | reject | none | parentheses are outside grammar |
| result outside `int` | reject | none | checked arithmetic boundary |

Check overflow before performing the signed C operation and before committing
the calculation. A failed expression leaves the caller's prior output
unchanged.

### E. Physical slot versus logical item

For `[10, 20, 777, 888]`, size two, capacity four:

1. Logical indexes: zero and one.
2. Correct top: 20.
3. `stack[size]` reads 777 at index two.
4. Index two is less than capacity but not less than size, so it is physically
   allocated and logically inactive.
5. Correct expression: `stack[size - 1]`, after proving size is positive.

A caller expecting a paused function ID could treat 777 as a real unfinished
function and make a false resume decision. Leaving size equal to two does not
repair the incorrect reported value.

### F. Costs

| Work | Cost | Reason |
|---|---:|---|
| successful or rejected push | `O(1)` | fixed checks and at most one write |
| successful or rejected peek | `O(1)` | fixed checks and at most one read |
| successful or rejected pop | `O(1)` | fixed checks and at most one read |
| evaluate length `n` | `O(n)` | scan each character; push/apply each token a bounded number of times |
| two ten-position arrays | `O(1)` | capacity is fixed by the contract |

No Stack operation shifts items because all access occurs at the last logical
index.

### G. Three uses of “stack”

1. Storing integer 100 does not create a real C call frame. It stores a label
   chosen for the teaching model.
2. The variable name `stack` does not enforce LIFO. Behavior comes from
   restricting access through the operation contracts.
3. `int_stack_push`, `int_stack_peek`, and `int_stack_pop` enforce the
   caller-owned array's LIFO access.

The runtime may use call-stack bookkeeping while the C functions run, but
that object is not the explicit Stack ADT managed by these operations.

### H. Exit ticket

1. Top: `stack[size - 1]` when `size > 0`.
2. LIFO: the newest remaining item leaves first.
3. Peek reports without removal; pop reports and logically removes.
4. Rejected peek preserves the entire array and caller output.
5. Rejected push preserves the entire array and returns original size.
6. Grammar: a nonempty alternating sequence beginning and ending with one
   digit, using only `+` and `*`, with no spaces or other syntax; operations
   and arithmetic must pass fixed-capacity and `int` checks.
7. Questions vary. Sort them into behavior, representation, boundary,
   expression, C implementation, or evidence needs.

## Public implementation reference

### Metadata check

```c
size >= 0 && capacity >= 0 && size <= capacity
```

This check does not discover a physical array length. Missing required
pointers are separate rejection conditions.

### Push decision

Reject when metadata is invalid, `size == capacity`, or `stack == NULL`.
Otherwise write `stack[size] = value` and return `size + 1`.

### Peek decision

Reject with zero when metadata is invalid, size is zero, or either required
pointer is null. Otherwise read a local candidate from `stack[size - 1]`,
write the output, and return one.

### Pop decision

Use the same rejection checks. On success, read `stack[size - 1]`, write the
output, and return `size - 1`. Do not modify the array.

## Evaluator reference

The parser begins expecting a digit. A valid digit is converted with
`current - '0'`. After a digit, expect only `+` or `*`. Before pushing the
current operator, apply every waiting operator whose precedence is greater
than or equal to the current precedence. Equality is what enforces left
associativity.

When applying an operator:

1. select the top operator without retiring it;
2. pop the right operand from a local working size;
3. pop the left operand;
4. check the operation against `INT_MAX`;
5. calculate only after the check;
6. push the candidate result; and
7. commit the resulting number size and retire the operator only after all
   prior steps succeed.

Because digits and the two accepted operations produce nonnegative values,
the reference overflow checks are:

```text
left <= INT_MAX - right                for addition
left == 0 or right <= INT_MAX / left  for multiplication
```

After the final reductions, require one number. Only then write the caller's
output and return one. Any earlier rejection returns zero without the final
write.

## Evidence-record reference

Strong evidence includes:

- the exact 100, 200, 300 trace with returns and outputs;
- the invariant and active/inactive index ranges;
- full, empty, and invalid-metadata snapshots that remain unchanged;
- output sentinels that prove failed peek, pop, and evaluation did not write;
- a complete `1+2*3` two-Stack trace;
- exact grammar and overflow boundaries;
- three distinct student-test rationales; and
- warning-enabled build output plus approved diagnostics.

Accept ordinary-language explanations when they preserve these technical
claims.

## Three student-authored tests

Require exactly one nonduplicate test in each category:

1. **LIFO:** push 100, 200, 300; verify peek 300 and pop order 300, 200, 100,
   or extend that sequence with a new push after a pop.
2. **Rejection/preservation:** use full push, empty peek/pop, invalid metadata,
   or a missing output and compare the entire array or output sentinel.
3. **Expression:** add a valid precedence/left-associativity case or reject
   malformed/overflow input while proving the result sentinel is unchanged.

Each comment should name the promise, expected result, observed result, and
why the case adds evidence beyond supplied tests.

## Stack-Top Autopsy

Expected predictions and observations:

```text
size: 2
capacity: 4
correct top stack[size - 1]: 20
faulty top stack[size]: 777
faulty read selected the next inactive slot: yes
```

The first broken rule is the logical top expression, not a later caller
decision. Complete the index statement as:

```text
top index = size - 1
next unused index = size
```

The read is physically safe in the fixture because index two is less than
capacity four. It is logically wrong because index two is not less than size
two. A memory sanitizer need not report it.

Repair:

```c
*out_value = stack[size - 1];
```

The operation must first prove valid metadata, a nonempty state, and valid
required pointers. A strong regression fixture deliberately places different
values at the top and next inactive position, peeks, requires the top value,
and verifies no mutation.

For the final distinction, the explicit Stack ADT and caller-owned fixed array
are both central to the autopsy. C function calls may also involve a runtime
call stack, but the exercise neither represents nor controls it.

## Expected reference test output

Core:

```text
PASS push adds at the top
PASS peek reads without mutation
PASS pop reports LIFO without erasing
PASS full push preserves array
PASS empty and zero capacity fail safely
PASS invalid arguments preserve state
PASS expression precedence and associativity
PASS invalid expressions preserve result

8 core test(s), 0 failure(s)
```

Extension:

```text
PASS every capacity through ten
PASS deterministic stack model
PASS valid expression table and long input
PASS invalid expression table
PASS checked integer overflow

5 extension test(s), 0 failure(s)
```

The long valid extension expression demonstrates that ten positions limit
simultaneous Stack occupancy rather than total input length.
