# Stage C — Investigation Worksheet: LIFO State and Nested Input

Name: ____________________________  
Date: ____________________________

Open this file after completing and preserving the Cognitive Pause.

The Stage C core is Sections A through F. Complete and preserve those
sections before opening Stage D. Sections G through I may be completed during
the announced independent-work window.

## Quick reference

A **Stack** is an abstract data type (ADT) that allows access at one end,
called the **top**. An ADT describes allowed operations and their rules
without requiring one storage method. **Last in, first out (LIFO)** means the
most recently added item is the first item that may be removed.

- `push` adds one item at the top.
- `peek` reports the top item without removing it.
- `pop` removes and reports the top item.
- **underflow** means attempting `peek` or `pop` while empty.

This module stores characters in an ArrayList backend. An **ArrayList** is a
resizable numbered sequence, and a **backend** is the lower-level storage
used to implement an ADT. `size` counts current items; `capacity` counts
allocated slots; `limit` is the greatest permitted size. When `size > 0`,
the top is `data[size - 1]`.

## A. Translate the canonical trace

A **trace** is a step-by-step record of changing state. In this activity,
write every state from bottom to top. Ordinary letters do not change the
Stack.

Complete the trace for:

```text
A(B[C]{D})
```

| Symbol read | Delimiter action, if any | State from bottom to top | `size` |
|---|---|---|---:|
| start | none | empty | `0` |
| `A` | | | |
| `(` | | | |
| `B` | | | |
| `[` | | | |
| `C` | | | |
| `]` | | | |
| `{` | | | |
| `D` | | | |
| `}` | | | |
| `)` | | | |

1. What is the greatest size reached? ______________________________
2. Immediately before `]`, what is at the top? ______________________
3. Why does processing `]` reveal `(` again? _______________________
4. What final state supports accepting the expression? ______________

## B. Apply the core operation contracts

A **contract** states what an operation accepts, changes, reports, and
preserves. A **status code** is a named result reporting success or a kind of
failure. An **invariant** is a rule that holds in every valid completed
state. The course operations use these results:

- `STACK_OK`: the operation succeeded;
- `STACK_INVALID_ARGUMENT`: a required Stack or output location is missing or
  otherwise invalid;
- `STACK_LIMIT`: `push` would exceed the explicit limit, or initialization
  requested a limit above 1024;
- `STACK_UNDERFLOW`: `peek` or `pop` was requested while empty;
- `STACK_ALLOCATION`: the ArrayList could not obtain needed storage; and
- `STACK_INVALID_STATE`: the stored fields break the Stack invariant.

An **output location** is caller-provided storage where an operation writes
its reported item. For `peek` or `pop`, that location must be separate from
the Stack's own character storage. The **caller** is the part of the program
that requests the operation.

| Operation | Successful effect | Failure promise |
|---|---|---|
| `char_stack_init` | creates an empty character Stack with the stated limit | leaves the supplied object unchanged |
| `char_stack_validate` | reports that the visible invariant holds | does not change the Stack |
| `char_stack_push` | adds one item as the new top and increases `size` by 1 | leaves the entire prior Stack unchanged |
| `char_stack_peek` | copies the top into `out_value` | leaves the Stack and `out_value` unchanged |
| `char_stack_pop` | copies the top into `out_value`, then decreases `size` by 1 | leaves the Stack and `out_value` unchanged |
| `char_stack_destroy` | releases owned ArrayList storage and resets the fields | a missing Stack pointer is a safe no-op |

Begin each case with this state:

```text
bottom → `(`, `[` ← top
size = 2
limit = 3
```

Classify each case independently.

| Request | Status | Reported item, if any | State afterward |
|---|---|---|---|
| `peek` | | | |
| `pop` | | | |
| `push('{')` | | | |
| `push('X')`, then `push('Y')` | | | |

Why must `peek` leave `size` unchanged?

____________________________________________________________________

Why must clients not read or write `data[index]` directly?

____________________________________________________________________

## C. Reason about empty state and underflow

An empty Stack has `size == 0` and no top. Its `capacity` may be zero or may
remain greater than zero after earlier use. Capacity does not tell whether
an item exists.

For each request on an empty Stack, complete the result.

| Request | Required status | May it read `data[size - 1]`? | State afterward |
|---|---|---|---|
| `peek` | | | |
| `pop` | | | |
| `push('(')` when `limit == 0` | | | |

1. Why is `data[size - 1]` invalid when `size == 0`?

   _________________________________________________________________

2. Why is underflow a checked error rather than a character result?

   _________________________________________________________________

3. A Stack has `size == 0` and `capacity == 8`. Is it empty? Explain.

   _________________________________________________________________

## D. Diagnose delimiter input

A **function** is a named block of computer instructions that performs one
task. A **delimiter validator** is a function that checks grouping marks. A
**mismatch** occurs when a closing delimiter does not partner with the
opening at the top. An **unmatched closing delimiter** appears when no
opening is available. A **leftover opening delimiter** remains when input
ends. A **depth-limit error** occurs before an opening would make the Stack
larger than its permitted limit.

The validator reports one `DelimiterStatus` value:

- `DELIMITER_OK`;
- `DELIMITER_INVALID_ARGUMENT`;
- `DELIMITER_UNMATCHED_CLOSE`;
- `DELIMITER_MISMATCH`;
- `DELIMITER_UNCLOSED_OPEN`;
- `DELIMITER_DEPTH_LIMIT`; or
- `DELIMITER_ALLOCATION`.

An **error index** is the numbered input position at which the problem is
reported. C begins indexes at zero. `size_t` is C's nonnegative count and
index type. A successful validation writes `SIZE_MAX`, the greatest value
`size_t` can hold, to `out_error_index`; this means “no error index.” An
unmatched closing, mismatch, or depth-limit result reports the responsible
delimiter's index. An unclosed opening reports the input length, which marks
the end. Invalid arguments and allocation failure leave the output unchanged.

Use a nesting limit of 2. Diagnose each input independently.

| Input | Error index or `SIZE_MAX` | State at decision | Status |
|---|---:|---|---|
| `A(B[C]{D})` | | | |
| `A)B` | | | |
| `A(B]` | | | |
| `A(B` | | | |
| `A([B{C}])` | | | |

For `A(B]`, why should the validator inspect before removing?

____________________________________________________________________

For `A(B`, why can the validator decide only after the input ends?

____________________________________________________________________

For `A)B`, how does handling `peek` underflow avoid an invalid `pop`?

____________________________________________________________________

## E. Preserve safety at the boundary

**Failure atomicity** means a failed operation leaves the prior valid state
unchanged. **Allocation failure** means the program could not obtain
requested memory. **Resource exhaustion** means input tries to consume more
of a limited resource than the application permits.

Suppose the state is:

```text
bottom → `(`, `[` ← top
size = 2
limit = 2
```

1. A push of `{` reports `STACK_LIMIT`. State every field or logical item
   that must remain unchanged.

   _________________________________________________________________

2. Suppose growth is needed below the limit, but allocation fails. Why must
   the old `data` address, size, capacity, and items remain usable?

   _________________________________________________________________

3. Why should the delimiter validator reject at the first known failure
   instead of continuing with unreliable state?

   _________________________________________________________________

4. The expressions here are **synthetic**, meaning invented for safe
   practice. A syntactically valid expression follows delimiter form.
   Does valid delimiter form prove that a real security policy grants the
   intended permissions? Explain.

   _________________________________________________________________

## F. Separate the ADT from other meanings of “stack”

The word “stack” appears in several computer-science phrases, but the phrases
do not name the same object.

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

Complete the comparison:

| Phrase | What it describes | Controlled by `CharStack` operations? |
|---|---|---|
| Stack ADT | | |
| runtime call stack | | |
| stack memory | | |
| stack-buffer overflow | | |

1. Does calling `char_stack_push` create a C function call frame? Explain.

   _________________________________________________________________

2. Does a correct Stack ADT automatically prevent every buffer overflow in a
   program? Explain.

   _________________________________________________________________

3. How can recursion and an explicit Stack both remember unfinished work
   while still being different mechanisms?

   _________________________________________________________________

## G. Connect costs to the ArrayList backend

**Time complexity** describes how work grows as input grows. Let `n` mean the
current Stack size.

- `O(1)` means a fixed amount of work;
- `O(n)` means work may grow in proportion to `n`; and
- **amortized `O(1)`** means the average work per operation stays constant
  across a long sequence, although an occasional operation costs more.

**Geometric growth** means increasing capacity by a fixed factor, such as
doubling, when more room is needed. The expression length `m` is its number
of characters.

Use the ArrayList backend to complete the table.

| Operation | Expected cost | Reason |
|---|---:|---|
| `peek` | | |
| `pop` without shrinking storage | | |
| `push` with spare capacity | | |
| one `push` that grows the ArrayList | | |
| a long sequence of geometrically growing pushes | | |
| validating an expression of length `m` | | |

Why can one push cost more than the average push cost?

____________________________________________________________________

Why is the complete validator `O(m)` even when its pushes are amortized
`O(1)`?

____________________________________________________________________

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

1. Which part stays the same when a character Stack becomes a Stack of node
   pointers: the LIFO contract or the item type?

   _________________________________________________________________

2. Why is a character Stack not directly suitable for storing a
   `TreeNode *` pointer?

   _________________________________________________________________

3. Complete: “The delimiter task and later DFS both need to remember
   __________, but they store different kinds of __________.”

## I. Exit ticket

1. Where is the top item in a nonempty ArrayList-backed Stack?

   _________________________________________________________________

2. State the LIFO rule in your own words.

   _________________________________________________________________

3. Distinguish `peek` from `pop`.

   _________________________________________________________________

4. What result should `pop` report on an empty Stack?

   _________________________________________________________________

5. Name the four malformed-input or resource cases in Section D.

   _________________________________________________________________

6. Why is `capacity` not the same as `size` or `limit`?

   _________________________________________________________________

7. One question you still have:

   _________________________________________________________________
