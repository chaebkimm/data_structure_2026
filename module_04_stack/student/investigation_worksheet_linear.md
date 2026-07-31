# Stage C — Investigation: Linear Accessible Format

## How to use this version

This version has the same learning targets as the standard investigation. It
contains no response table or drawing requirement. It works with a **screen
reader**, software that reads on-screen text aloud, as well as keyboard
navigation, speech input, or a text-only response.

Open it after completing and preserving the Cognitive Pause.

The Stage C core is Sections A through F. Complete and preserve those
sections before opening Stage D. Sections G through I may be completed during
the announced independent-work window.

## Quick reference

A **Stack** is an abstract data type (ADT) that allows access at one end,
called the **top**. An ADT describes allowed operations and their rules
without requiring one storage method. **Last in, first out (LIFO)** means the
most recently added item is the first item that may be removed.

`push` adds one item at the top. `peek` reports the top without removing it.
`pop` removes and reports the top. **Underflow** means attempting `peek` or
`pop` while empty.

This module stores characters in an ArrayList backend. An **ArrayList** is a
resizable numbered sequence, and a **backend** is the lower-level storage
used to implement an ADT. `size` counts current items; `capacity` counts
allocated slots; `limit` is the greatest permitted size. When `size` is
greater than zero, the top is `data[size - 1]`.

## A. Translate the canonical trace

A **trace** is a step-by-step record of changing state. State Stack items
from bottom to top. Ordinary letters do not change the Stack.

Input:

```text
A(B[C]{D})
```

### A1. State sequence

Starting empty, state the action and resulting Stack after each of these
symbols in order: `A`, `(`, `B`, `[`, `C`, `]`, `{`, `D`, `}`, `)`.

Response:

### A2. Greatest size

What is the greatest size reached?

Response:

### A3. Exposed item

Immediately before `]`, what is at the top? Why does processing `]` reveal
`(` again?

Response:

### A4. Final check

What final state supports accepting the expression?

Response:

## B. Apply the core operation contracts

A **contract** states what an operation accepts, changes, reports, and
preserves. A **status code** is a named result reporting success or a kind of
failure. An **invariant** is a rule that holds in every valid completed
state.

The results are:

1. `STACK_OK`: success.
2. `STACK_INVALID_ARGUMENT`: a required Stack or output location is invalid.
3. `STACK_LIMIT`: `push` would exceed the explicit limit, or initialization
   requested a limit above 1024.
4. `STACK_UNDERFLOW`: `peek` or `pop` was requested while empty.
5. `STACK_ALLOCATION`: the ArrayList could not obtain needed storage.
6. `STACK_INVALID_STATE`: the stored fields break the Stack invariant.

An **output location** is caller-provided storage where an operation writes
its reported item. For `peek` or `pop`, that location must be separate from
the Stack's own character storage. The **caller** is the part of the program
that requests the operation.

The contracts are:

1. `char_stack_init` creates an empty character Stack with the stated limit.
2. `char_stack_validate` reports whether the visible invariant holds and
   changes nothing.
3. Successful `char_stack_push(item)` adds `item` as the new top and
   increases `size` by one. Failure leaves the prior Stack unchanged.
4. Successful `char_stack_peek(out_value)` copies the top into `out_value`
   without changing the Stack. Failure leaves both unchanged.
5. Successful `char_stack_pop(out_value)` copies the top into `out_value` and
   then decreases `size` by one. Failure leaves both unchanged.
6. `char_stack_destroy` releases owned ArrayList storage and resets the
   fields. A missing Stack pointer is a safe no-op.

For every case below, begin independently with:

```text
bottom to top: `(`, `[`
size: 2
limit: 3
```

### B1. Peek

State the status, reported item, and state after `peek`.

Response:

### B2. Pop

State the status, reported item, and state after `pop`.

Response:

### B3. One push

State the status and state after `push('{')`.

Response:

### B4. Two pushes

State what happens when `push('X')` and then `push('Y')` are requested.

Response:

### B5. Encapsulation

Why must `peek` leave `size` unchanged? Why must clients not read or write
`data[index]` directly?

Response:

## C. Reason about empty state and underflow

An empty Stack has `size` zero and no top. Its `capacity` may be zero or may
remain greater than zero after earlier use. Capacity does not tell whether
an item exists.

### C1. Peek while empty

State the required status, whether `data[size - 1]` may be read, and the
state afterward.

Response:

### C2. Pop while empty

State the required status, whether `data[size - 1]` may be read, and the
state afterward.

Response:

### C3. Zero limit

State the result of `push('(')` on an empty Stack whose limit is zero.

Response:

### C4. Explain the boundary

Why is `data[size - 1]` invalid when `size` is zero? Why is underflow a
checked error rather than a character result?

Response:

### C5. Spare storage

A Stack has `size` zero and `capacity` 8. Is it empty? Explain.

Response:

## D. Diagnose delimiter input

A **function** is a named block of computer instructions that performs one
task. A **delimiter validator** is a function that checks grouping marks. A
**mismatch** occurs when a closing delimiter does not partner with the
opening at the top. An **unmatched closing delimiter** appears when no
opening is available. A **leftover opening delimiter** remains when input
ends. A **depth-limit error** occurs before an opening would make the Stack
larger than its permitted limit.

The validator reports one `DelimiterStatus`: `DELIMITER_OK`,
`DELIMITER_INVALID_ARGUMENT`, `DELIMITER_UNMATCHED_CLOSE`,
`DELIMITER_MISMATCH`, `DELIMITER_UNCLOSED_OPEN`,
`DELIMITER_DEPTH_LIMIT`, or `DELIMITER_ALLOCATION`.

An **error index** is the numbered input position at which the problem is
reported. C begins indexes at zero. `size_t` is C's nonnegative count and
index type. Success writes `SIZE_MAX`, the greatest value `size_t` can hold,
to `out_error_index`; this means “no error index.” An unmatched closing,
mismatch, or depth-limit result reports the responsible delimiter's index.
An unclosed opening reports the input length, which marks the end. Invalid
arguments and allocation failure leave the output unchanged.

Use a nesting limit of 2. For each input, state the error index or
`SIZE_MAX`, the Stack state at the decision, and the exact status.

### D1. Input `A(B[C]{D})`

Response:

### D2. Input `A)B`

Response:

### D3. Input `A(B]`

Response:

### D4. Input `A(B`

Response:

### D5. Input `A([B{C}])`

Response:

### D6. Reason about detection

Why should `A(B]` be inspected before anything is removed? Why can `A(B`
be decided only after input ends? How does handling `peek` underflow avoid
an invalid `pop` for `A)B`?

Response:

## E. Preserve safety at the boundary

**Failure atomicity** means a failed operation leaves the prior valid state
unchanged. **Allocation failure** means the program could not obtain
requested memory. **Resource exhaustion** means input tries to consume more
of a limited resource than the application permits.

Begin with:

```text
bottom to top: `(`, `[`
size: 2
limit: 2
```

### E1. Limit failure

A push of `{` reports `STACK_LIMIT`. State every field or logical item
that must remain unchanged.

Response:

### E2. Allocation failure

Suppose growth is needed below the limit, but allocation fails. Why must the
old `data` address, size, capacity, and items remain usable?

Response:

### E3. Fail fast

Why should the delimiter validator reject at the first known failure instead
of continuing with unreliable state?

Response:

### E4. Security claim boundary

The expressions here are **synthetic**, meaning invented for safe practice.
A syntactically valid expression follows delimiter form. Does valid delimiter
form prove that a real security policy grants the intended permissions?
Explain.

Response:

## F. Separate the ADT from other meanings of “stack”

The same word appears in several computer-science phrases, but the phrases do
not name the same object.

A **runtime call stack** is bookkeeping commonly used by a C implementation
to manage active function calls. A **call frame** is the saved information
for one active call, such as where execution should return. **Recursion**
occurs when a function calls itself directly or through other functions.
Each active recursive call commonly needs another call frame.

**Stack memory** is an informal name for a memory region that many C
implementations use for function-call information and local variables. The C
language does not require every implementation to arrange memory identically.
A **buffer** is a bounded area that stores a sequence of values. A
**stack-buffer overflow** is an out-of-bounds write past a buffer placed in
that commonly named memory region.

### F1. Four meanings

For each phrase below, describe what it means and whether `CharStack`
operations control it:

1. Stack ADT.
2. Runtime call stack.
3. Stack memory.
4. Stack-buffer overflow.

Response:

### F2. Function calls

Does calling `char_stack_push` create a C function call frame? Explain.

Response:

### F3. Bounds safety

Does a correct Stack ADT automatically prevent every buffer overflow in a
program? Explain.

Response:

### F4. Saved work

How can recursion and an explicit Stack both remember unfinished work while
still being different mechanisms?

Response:

## G. Connect costs to the ArrayList backend

**Time complexity** describes how work grows as input grows. Let `n` mean
current Stack size. `O(1)` means a fixed amount of work. `O(n)` means work
may grow in proportion to `n`. **Amortized `O(1)`** means the average work
per operation stays constant across a long sequence, although an occasional
operation costs more.

**Geometric growth** means increasing capacity by a fixed factor, such as
doubling, when more room is needed. Let `m` be an expression's number of
characters.

### G1. Classify costs

Give the expected cost and one reason for each operation:

1. `peek`.
2. `pop` without shrinking storage.
3. `push` with spare capacity.
4. One `push` that grows the ArrayList.
5. A long sequence of geometrically growing pushes.
6. Validating an expression of length `m`.

Response:

### G2. Occasional growth

Why can one push cost more than the average push cost?

Response:

### G3. Whole input

Why is the complete validator `O(m)` even when its pushes are amortized
`O(1)`?

Response:

## H. Preview depth-first work

An **algorithm** is a precise step-by-step method. **Depth-first search
(DFS)** is a later algorithm for exploring tree nodes or graph vertices. A
tree node is one stored item in a tree. A graph vertex is one stored item in
a graph.

DFS can use the same LIFO contract to remember unfinished work: the most
recently saved node or vertex is selected next. Later modules provide
separately typed Stacks for `TreeNode *` values and vertex-ID values. A
**pointer** stores a memory address. `TreeNode *` is a pointer to one tree
node. A **vertex ID** is a small number naming one graph vertex.

This section is only a preview. Do not trace or implement DFS here.

### H1. Stable rule

Which part stays the same when a character Stack becomes a Stack of node
pointers: the LIFO contract or the item type?

Response:

### H2. Item type

Why is a character Stack not directly suitable for a `TreeNode *` pointer?

Response:

### H3. Transfer sentence

Complete: “The delimiter task and later DFS both need to remember
__________, but they store different kinds of __________.”

Response:

## I. Exit ticket

### I1. Stored top

Where is the top item in a nonempty ArrayList-backed Stack?

Response:

### I2. Access rule

State LIFO in your own words.

Response:

### I3. Inspect or remove

Distinguish `peek` from `pop`.

Response:

### I4. Underflow

What result should `pop` report on an empty Stack?

Response:

### I5. Input failures

Name the four malformed-input or resource cases from Section D.

Response:

### I6. Three counts

Why is `capacity` not the same as `size` or `limit`?

Response:

### I7. Open question

State one question you still have.

Response:
