# Instructor Answer Key - Module 4 Stack ADT

## Macro-Question synthesis

A **stack** is a collection with one accessible end, called the **top**.
Its rule is **last in, first out (LIFO)**: the most recently added item that
remains in the collection is the first item removed.

For nested delimiters, the newest unmatched opening must be checked first.
The stack stores openings in their arrival order and exposes them in the
reverse order needed for closing. This is the access rule the program should
enforce.

The Stack **abstract data type (ADT)** is this behavior contract. An ADT
defines allowed operations and results independently of storage. The
ArrayList is the **backend**, meaning the hidden resizable storage used by
this implementation.

## Stage A inquiry

### A. Inspect one candidate expression

For:

```text
A(B[C]{D})
```

- opening delimiters, in input order: `(`, `[`, `{`;
- closing delimiters, in input order: `]`, `}`, `)`;
- matching pairs: `[` with `]`, `{` with `}`, and `(` with `)`.

The grouping is complete because every closing delimiter matches the newest
unresolved opening, no closing arrives while there is no opening available,
and no opening remains after the final character.

### B. Track unfinished groups

List unresolved openings from oldest to newest, which is also bottom to top
in the later stack model.

| Symbol just read | Before | Action | After |
|---|---|---|---|
| `A` | empty | ignore ordinary character | empty |
| `(` | empty | remember `(` | `(` |
| `B` | `(` | ignore ordinary character | `(` |
| `[` | `(` | remember `[` after `(` | `(`, `[` |
| `C` | `(`, `[` | ignore ordinary character | `(`, `[` |
| `]` | `(`, `[` | match and remove newest `[` | `(` |
| `{` | `(` | remember `{` after `(` | `(`, `{` |
| `D` | `(`, `{` | ignore ordinary character | `(`, `{` |
| `}` | `(`, `{` | match and remove newest `{` | `(` |
| `)` | `(` | match and remove newest `(` | empty |

When a closing delimiter arrives, check the most recent unresolved opening.
Checking an older opening would allow crossed pairs such as `([)]`, which
are not properly nested.

### C. Challenge your rule

| Expression | First decisive place | Judgment | Reason |
|---|---|---|---|
| `A(B[C]{D})` | End of input | complete | Every pair matches and no opening remains |
| `A)B` | `)` at index 1 | malformed: unmatched close | No opening is available |
| `A(B]` | `]` at index 3 | malformed: mismatch | The newest opening is `(`, not `[` |
| `A(B` | End at index 3, the string length | malformed: unclosed opening | `(` remains unresolved |

An **index** is a numbered position beginning at zero. Some failures are
known during the scan, such as an unmatched close or mismatch. An unclosed
opening can remain plausible until the input ends, so that failure is known
only then.

### D. Add a resource boundary

With a maximum of two unresolved openings, `A([B{C}])` is rejected at `{`,
index 4. Just before `{`, the stored openings are `(`, `[`. Accepting `{`
would create size 3. The already stored information must remain unchanged.

A declared boundary gives predictable resource use and lets the program
reject safely before storage consumption exceeds policy. Available machine
memory does not replace an application's stated input limit.

### E. Macro-Question

A representative response is:

> Preserve unresolved items in arrival order, but permit access only to the
> newest unresolved item. Add, inspect, and remove at that same end.

After formal vocabulary is released, this becomes the LIFO rule.

### F. Tracking brainstorm

- When an opening arrives, remember its exact kind and its relative order.
- Before accepting a close, an unresolved opening must exist and the newest
  one must be the matching kind.
- After the final character, no unresolved opening may remain.
- Student questions vary. Use them to select support about empty input,
  crossed pairs, end-of-input checks, limits, or storage failure rather than
  scoring a guessed implementation.

## Stage B Cognitive Pause

### Target 1 - Complete trace

Only delimiter characters change the stack:

| Delimiter | State from bottom to top | `size` |
|---|---|---:|
| `(` | `(` | 1 |
| `[` | `(`, `[` | 2 |
| `]` | `(` | 1 |
| `{` | `(`, `{` | 2 |
| `}` | `(` | 1 |
| `)` | empty | 0 |

The greatest size is 2 and the final state is empty.

### Target 2 - Two closing failures

- For `A(B]`, failure is known at `]`. Just before it is handled, the state
  is `(` and the next accessible item is `(`. Because `]` requires `[`, the
  result is a mismatch.
- For `A)B`, failure is known at `)`. The stack is empty, so there is no next
  accessible item. The result is an unmatched closing delimiter.

### Target 3 - Boundary and final state

- With limit 2, `A([B{C}])` fails at `{`. The unchanged state is `(`, `[`.
  A third push would exceed the nesting limit, so this is a depth-limit
  failure.
- `A(B` reaches the end with state `(`. No closing delimiter caused a
  mismatch, but one opening remains, so this is an unclosed or leftover
  opening.

## Stage C investigation

The standard and linear worksheets have the same sections. Linear
subquestion labels such as A1-A4 correspond to the numbered or tabular
prompts under the same letter below.

### A. Translate the canonical trace

| Symbol | Action | State from bottom to top | `size` |
|---|---|---|---:|
| start | none | empty | 0 |
| `A` | ignore | empty | 0 |
| `(` | push `(` | `(` | 1 |
| `B` | ignore | `(` | 1 |
| `[` | push `[` | `(`, `[` | 2 |
| `C` | ignore | `(`, `[` | 2 |
| `]` | matching peek, then pop `[` | `(` | 1 |
| `{` | push `{` | `(`, `{` | 2 |
| `D` | ignore | `(`, `{` | 2 |
| `}` | matching peek, then pop `{` | `(` | 1 |
| `)` | matching peek, then pop `(` | empty | 0 |

1. Greatest size: `2`.
2. Immediately before `]`, the top is `[`.
3. Processing `]` pops `[`, so the older `(` becomes visible at the top
   again.
4. The final empty state shows that every opening was closed.

### B. Apply the core operation contracts

The exact public stack statuses are:

```text
STACK_OK
STACK_INVALID_ARGUMENT
STACK_LIMIT
STACK_UNDERFLOW
STACK_ALLOCATION
STACK_INVALID_STATE
```

Each row begins independently with bottom-to-top state `(`, `[`, size 2,
and limit 3.

| Request | Status | Reported item | State afterward |
|---|---|---|---|
| `peek` | `STACK_OK` | `[` | `(`, `[`, size 2 |
| `pop` | `STACK_OK` | `[` | `(`, size 1 |
| `push('{')` | `STACK_OK` | none | `(`, `[`, `{`, size 3 |
| `push('X')`, then `push('Y')` | first `STACK_OK`, then `STACK_LIMIT` | none | `(`, `[`, `X`, size 3; second push changes nothing |

`peek` leaves size unchanged because its contract inspects rather than
removes the top. Clients should not index `data` directly because doing so
bypasses LIFO access, boundary checks, failure reporting, and the freedom to
change the backend without changing client code. This separation is called
**encapsulation**: an object's implementation details are protected behind
its public operations.

### C. Reason about empty state and underflow

| Request | Result | Read `data[size - 1]`? | State afterward |
|---|---|---|---|
| `peek` | `STACK_UNDERFLOW` | no | unchanged empty state; output unchanged |
| `pop` | `STACK_UNDERFLOW` | no | unchanged empty state; output unchanged |
| `push('(')` with limit 0 | `STACK_LIMIT` | no | unchanged empty state |

1. When size is zero, there is no occupied index. Subtracting one from the
   unsigned `size_t` value also wraps to a very large number, so it cannot
   name the top.
2. No special character can unambiguously mean underflow because any `char`
   value could be legitimate stack data. A separate status reports failure
   safely.
3. Yes. Size, not capacity, says how many items exist. Capacity 8 means
   storage is available for reuse.

### D. Diagnose delimiter input

Use limit 2.

| Input | Error index or `SIZE_MAX` | State at decision | Status |
|---|---:|---|---|
| `A(B[C]{D})` | `SIZE_MAX` | empty at end | `DELIMITER_OK` |
| `A)B` | 1 | empty before `)` | `DELIMITER_UNMATCHED_CLOSE` |
| `A(B]` | 3 | `(` before `]` | `DELIMITER_MISMATCH` |
| `A(B` | 3 | `(` at end | `DELIMITER_UNCLOSED_OPEN` |
| `A([B{C}])` | 4 | `(`, `[` before `{` | `DELIMITER_DEPTH_LIMIT` |

For a mismatch, inspect before removing so the unmatched opening remains
available and state is not falsely advanced. `A(B` cannot be rejected while
more input might still supply `)`, so the final nonempty check is decisive.
For `A)B`, checking empty before peek or pop prevents an out-of-range read
and an underflowing removal.

### E. Preserve safety at the boundary

1. After the limit failure, `data` has the same address; size remains 2;
   capacity remains unchanged; limit remains 2; and the items remain `(`,
   `[`. No output or unused slot becomes part of the logical stack.
2. A temporary allocation result is checked before the object is changed.
   If growth fails, retaining the original pointer is necessary both to keep
   existing items usable and to release that owned storage later.
3. Once a known structural or resource failure occurs, later operations
   would no longer describe validation of the original input contract.
   Stopping also avoids acting on a fabricated or damaged state.
4. No. Delimiter validity proves only balanced grouping marks under this
   simplified rule. It does not prove policy meaning, authorization,
   identity, permissions, or safe real-world behavior.

### F. Separate the ADT from other meanings of "stack"

| Phrase | Meaning | Controlled by `CharStack` operations? |
|---|---|---|
| Stack ADT | LIFO collection behavior | yes, for this explicit object |
| Runtime call stack | Saved information for active function calls | no |
| Stack memory | Informal name for a region an implementation may use for calls and local objects | no |
| Stack-buffer overflow | An out-of-bounds write past a local buffer in that region | no |

1. Calling `char_stack_push` is a C function call, so an implementation may
   create or reuse a call frame for that call. However, the `CharStack`
   operation does not itself manage the runtime call stack. A **compiler**
   translates C into a runnable program, and its **optimization** may change
   the translated instruction arrangement while preserving behavior; that
   can remove a distinct frame.
2. No. A correct `CharStack` protects only its own documented operations.
   Unrelated arrays, pointers, and other program code can still access
   memory incorrectly.
3. Recursion saves unfinished work implicitly in runtime-managed call
   frames. An explicit Stack stores chosen work items through program-called
   push and pop operations. Both can produce LIFO behavior, but ownership,
   representation, and control differ.

### G. Connect costs to the ArrayList backend

`n` is current stack size and `m` is expression length.

| Operation | Expected cost | Reason |
|---|---:|---|
| `peek` | `O(1)` | Read one top slot |
| `pop` without shrinking | `O(1)` | Read one slot and reduce size |
| `push` with spare capacity | `O(1)` | Write one slot and increase size |
| one growing `push` | `O(n)` worst case | Resizing may copy `n` characters |
| long sequence of geometrically growing pushes | amortized `O(1)` per push | Infrequent doubling spreads copying across many pushes |
| validate expression of length `m` | `O(m)` | Each character is examined once; total geometric-growth copying is also linear |

One growing push can copy existing characters, so it costs more than a push
into spare capacity. The average remains constant across a long growth
sequence because each larger resize occurs less frequently.

The full validator is `O(m)` because it makes one left-to-right pass and its
stack operations have amortized constant cost. It uses `O(d)` additional
storage, where `d` is maximum unmatched-opening depth and is capped by the
requested limit.

### H. Preview depth-first work

1. The LIFO contract stays the same; the item type changes.
2. A `char` stores one character value, not a `TreeNode *` address. Treating
   one as the other violates the type and may lose information.
3. Representative completion: "The delimiter task and later DFS both need
   to remember unfinished work, but they store different kinds of items."

Do not require a DFS trace or implementation here.

### I. Exit ticket

1. The top is `data[size - 1]` when size is greater than zero.
2. LIFO means the newest remaining item leaves first.
3. `peek` reports the top without removing it; `pop` reports and removes it.
4. Empty pop reports `STACK_UNDERFLOW` and leaves its output unchanged.
5. Unmatched closing delimiter, mismatch, unclosed opening, and depth limit.
6. Size counts current items; capacity counts allocated slots; limit is the
   fixed policy maximum for allowed items.
7. Questions vary. Sort them into state, operation contract, memory,
   delimiter, or later-transfer support.

## Canonical API answers

### Initialization and validation

`char_stack_init(&stack, limit)` accepts limits from 0 through 1024. It
creates:

```text
data = NULL
size = 0
capacity = 0
limit = requested limit
```

Call it only for an uninitialized or previously destroyed object. It does
not free a live Stack's allocation before replacing the fields.

A larger requested limit returns `STACK_LIMIT`; a missing stack pointer
returns `STACK_INVALID_ARGUMENT`. Failure leaves the object unchanged.

`char_stack_validate` checks:

```text
size <= capacity <= limit <= 1024
capacity == 0 exactly when data == NULL
size == 0 whenever capacity == 0
```

A contradictory object returns `STACK_INVALID_STATE`. The validator cannot
prove that an arbitrary non-`NULL` pointer is live, large enough, or uniquely
owned.

### Push growth

The first needed capacity is 4, clipped to the limit. Later growth doubles
and is clipped again.

| Limit | Capacity sequence when needed |
|---:|---|
| 0 | remains 0; push returns `STACK_LIMIT` |
| 2 | `0 -> 2` |
| 6 | `0 -> 4 -> 6` |
| 20 | `0 -> 4 -> 8 -> 16 -> 20` |
| 1024 | `0 -> 4 -> 8 -> ... -> 1024` |

At the limit, push returns `STACK_LIMIT` without attempting growth. If
growth fails below the limit, it returns `STACK_ALLOCATION`. A temporary
pointer protects the original allocation until success is known.

### Pop and peek outputs

Both functions require a non-`NULL` `out_value` that points outside the
Stack's owned character storage. On
`STACK_INVALID_ARGUMENT`, `STACK_INVALID_STATE`, or `STACK_UNDERFLOW`, the
output remains unchanged. Successful peek leaves all stack fields and items
unchanged. Successful pop decreases size by one but does not shrink
capacity.

### Destroy and ownership

The stack owns the storage identified by `data`. **Ownership** means
responsibility for eventually releasing requested storage.
`char_stack_destroy` releases that buffer and resets `data` to `NULL` and
all numeric fields to zero. Passing `NULL` is a safe no-op. An ordinary
structure copy is not a second independent stack because it duplicates the
pointer rather than the owned characters.

### Delimiter output index

`delimiter_validate(text, depth_limit, &error_index)` uses:

| Result | `error_index` |
|---|---|
| `DELIMITER_OK` | `SIZE_MAX`, meaning no error position |
| `DELIMITER_UNMATCHED_CLOSE` | offending closing index |
| `DELIMITER_MISMATCH` | offending closing index |
| `DELIMITER_UNCLOSED_OPEN` | string length |
| `DELIMITER_DEPTH_LIMIT` | rejected opening index |
| `DELIMITER_INVALID_ARGUMENT` | unchanged |
| `DELIMITER_ALLOCATION` | unchanged |

A zero depth limit is valid. Empty or delimiter-free text succeeds with
`SIZE_MAX`. An opening encountered at limit zero produces
`DELIMITER_DEPTH_LIMIT` at that opening's index.

## Evidence-record reference

### Operation trace

| Step | Returned value | Stack bottom to top |
|---:|---|---|
| Start | none | empty |
| push `A` | none | `A` |
| push `B` | none | `A`, `B` |
| peek | `B` | `A`, `B` |
| pop | `B` | `A` |
| push `C` | none | `A`, `C` |
| pop | `C` | `A` |
| pop | `A` | empty |

### Strong student-authored test rationales

Require one nonduplicate test in each lab category:

1. a mixed LIFO sequence, such as push `A`, push `B`, pop `B`, push `C`,
   peek `C`, then pop `C` and `A`;
2. a boundary or failure-preservation case, such as limit 6 growing through
   capacities 4 and 6 before the seventh push preserves every field and
   item; and
3. a delimiter error with its exact index, such as `{)` reporting
   `DELIMITER_MISMATCH` at index 1 rather than unmatched close.

Other cases are acceptable when they satisfy the same three categories and
do not merely copy a supplied case. For example, a failed peek may use a
deliberately chosen output character to prove that the output is unchanged,
and a depth-limit test may check the rejected opening's exact index.

Tests should state the promise, expected result, observed result, and why the
case differs from the other two.

## Stack-top autopsy

The isolated program pushes `(` at index 0 and `[` at index 1. Its size is
2, so:

```text
data[0] = '('
data[1] = '['   <- correct top, data[size - 1]
data[2] = '?'   <- next unused position, read by the faulty peek
```

Expected output facts:

- `size: 2`;
- correct top: `[`;
- faulty top: `?`;
- the faulty validator says valid: `no`; and
- reported index: `2`.

For the valid text `([])`, the validator pushes `(` and `[`. When `]`
arrives at index 2, `faulty_peek` reads the unused `data[2]` question mark
instead of `data[1]`. It therefore invents a mismatch before removing
anything.

The first incorrect decision is the read from `data[size]`. It breaks the
top contract: occupied positions end at `size - 1`. The extra physical cell
keeps this training read inside the array, but it does not make that cell a
logical stack item. **Logical** means belonging to the collection according
to its current size.

Repair:

```c
return stack->data[stack->size - 1U];
```

This expression is legal only after checking that size is greater than zero.
A strong **regression test**, meaning a retained test that detects the
return of a repaired defect, pushes two distinct characters, requires peek
to report the second without changing size, then validates `([])`
successfully.

For the final distinction check, the explicit `TrainingStack` is the Stack
ADT being exercised. Its `data` field is a fixed-size array inside local
`TrainingStack` objects, so it is also commonly implemented as a local stack
buffer. The program calls functions, but it does not implement or control the
runtime call stack; C also does not require local objects to have one
particular physical placement.

## Forward-transfer answer

A stack can remember choices that have been discovered but not processed.
Because the most recently saved choice is selected next, exploration can
continue deeply along a recent branch and later return to earlier saved
choices. Tree and graph DFS use typed stacks suited to nodes or vertex IDs;
the LIFO rule transfers, while the stored item type changes. Graph DFS also
needs a separate visited record because a graph may contain cycles.
