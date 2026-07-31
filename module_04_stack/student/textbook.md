# Student Notes — Remembering Unfinished Work

## Essential question

> If the most recently opened task must be completed first, what access rule
> should a program enforce?

## 1. The problem

A program is a group of instructions a computer can run. Its state is
the information it currently remembers.

Suppose a program reads this expression, a sequence of symbols:

```text
A(B[C]{D})
```

The marks `(`, `[`, and `{` begin groups. The marks `)`, `]`, and `}` end
groups. A mark with this job is a delimiter.

When `]` arrives, the program must remember that `[` is the opening still
waiting to be completed. It must not match `]` with the earlier `(`.
One variable is not enough because several openings may be unresolved at
once.

## 2. One access rule

A data structure is a planned way to organize information. An abstract data
type, shortened to ADT, describes a collection through its allowed operations
and rules. It does not require one particular storage method.

A **Stack ADT** gives access at one end only. That end is the **top**.
The rule is **last in, first out (LIFO)**: the item added most recently is
the first item that may be removed.

Three operations, or tasks supplied by the structure, define the basic
behavior:

- `push` adds one item at the top;
- `peek` reports the top item without removing it; and
- `pop` removes and reports the top item.

An empty Stack has no items and no top. **Underflow** means attempting
`peek` or `pop` while empty. Checked operations report this condition rather
than reading a nonexistent item.

## 3. Trace the expression

A trace is a step-by-step record of changing state. The table lists Stack
items from bottom to top. Ordinary letters do not change the Stack.

| Symbol | Action | State from bottom to top |
|---|---|---|
| start | none | empty |
| `A` | ignore | empty |
| `(` | `push('(')` | `(` |
| `B` | ignore | `(` |
| `[` | `push('[')` | `(`, `[` |
| `C` | ignore | `(`, `[` |
| `]` | matching `peek`, then `pop` | `(` |
| `{` | `push('{')` | `(`, `{` |
| `D` | ignore | `(`, `{` |
| `}` | matching `peek`, then `pop` | `(` |
| `)` | matching `peek`, then `pop` | empty |

The greatest size is 2. The final Stack is empty. Therefore
`A(B[C]{D})` has complete, correctly nested delimiters.

Notice the LIFO pattern. `[` was added after `(`, so `[` had to be removed
first. Later, `{` was added above `(` and removed before `(`.

## 4. Store the Stack in an ArrayList

A character is one symbol. C is the programming language used in this
course, and its `char` type stores a character.

An **ArrayList** is a resizable numbered sequence. A backend is the
lower-level storage used to implement an ADT. This module uses an
ArrayList-backed character Stack.

Read this C only for the field meanings. You do not need to memorize its
punctuation or wording yet.

```c
typedef struct {
    char *data;
    size_t size;
    size_t capacity;
    size_t limit;
} CharStack;
```

A struct groups named values called fields. A type tells C what
kind of value is stored. `typedef` creates the short type name `CharStack`.

An address identifies a location in computer memory. A pointer stores
an address, so `char *data` points to the character storage. `NULL` is a
pointer value meaning “no storage address.”

An index is a numbered position; C begins at zero. `size_t` is a
nonnegative whole-number type used for counts and indexes.

- `size` counts characters currently in the Stack.
- An allocation is a block of computer memory obtained for a program.
  `capacity` counts character slots in the current allocation.
- `limit` is the greatest Stack size permitted for this task.

When `size > 0`, the top item is exactly:

```text
data[size - 1]
```

For example, when the stored items are `(`, `[`, the size is 2 and the top
is `data[1]`, which stores `[`.

## 5. The invariant and contracts

An **invariant** is a rule true in every valid completed state. A valid
course `CharStack` satisfies:

1. `size <= capacity <= limit <= 1024`.
2. If `capacity == 0`, then `data == NULL` and `size == 0`.
3. If `capacity > 0`, `data` identifies storage for at least `capacity`
   characters.
4. When `size > 0`, current items occupy exactly indexes 0 through
   `size - 1`. When `size == 0`, no index is occupied.
5. If `size > 0`, `data[size - 1]` is the top.
6. If `size == 0`, there is no top.

A **contract** states what an operation accepts, changes, reports, and
preserves. A function is a named block of instructions that performs one
task. The caller is the part of the program asking it to run. An output
location is caller-provided storage where a function writes a result. The
output location for `peek` or `pop` must be separate from the Stack's own
character storage.

| Operation | Successful effect | Failure promise |
|---|---|---|
| `char_stack_init` | creates an empty Stack with the stated limit | leaves the supplied object unchanged |
| `char_stack_validate` | reports that the visible invariant holds | does not change the Stack |
| `char_stack_push` | adds one item; increases `size` by 1 | leaves the whole prior Stack unchanged |
| `char_stack_peek` | copies the top to its output | leaves the Stack and output unchanged |
| `char_stack_pop` | copies the top to its output; decreases `size` by 1 | leaves the Stack and output unchanged |
| `char_stack_destroy` | releases owned storage and resets all fields | a missing Stack pointer is a safe no-op |
| `stack_status_name` | returns readable text for a Stack status | returns readable text for an unknown status |

A status code is a named result reporting success or one failure:

- `STACK_OK`: success;
- `STACK_INVALID_ARGUMENT`: a required Stack or output location is invalid;
- `STACK_LIMIT`: `push` would exceed the explicit limit, or initialization
  requested a limit above 1024;
- `STACK_UNDERFLOW`: `peek` or `pop` was requested while empty;
- `STACK_ALLOCATION`: needed ArrayList storage could not be obtained; and
- `STACK_INVALID_STATE`: the stored fields break the Stack invariant.

`char_stack_validate` checks the visible field relationships above. C cannot
prove from an arbitrary pointer value alone that storage is still usable,
large enough, or owned by only this object.

**Failure atomicity** means a failed operation leaves the entire prior valid
state unchanged. A failed push must not lose old items or change `size`,
`capacity`, or `data`.

Ownership means responsibility for eventually releasing requested storage.
`CharStack` owns the allocation identified by `data`, so
`char_stack_destroy` must release it once. Copying only the four struct fields
would duplicate the pointer, not the owned allocation; such a shallow copy
must not be destroyed as an independent Stack.

Clients—the program parts using the Stack—must call its operations instead of
indexing `data` directly. This preserves LIFO behavior and keeps backend
details inside the Stack implementation.

## 6. Validate nested delimiters

A validator is a function that checks stated rules. It reads input from
left to right:

1. Ignore ordinary characters.
2. Push each opening delimiter.
3. For a closing delimiter, request `peek`. If it reports
   `STACK_UNDERFLOW`, reject the unmatched closing delimiter.
4. Otherwise, reject if the closing mark does not match the opening at the
   top.
5. Pop only after a match.
6. After all characters, accept only if the Stack is empty.

The matching pairs are `()`, `[]`, and `{}`.

Use an explicit **nesting limit**, the maximum number of unresolved openings
allowed at once. With limit 2, the running expression is accepted because
its greatest size is 2.

An interface states what other program parts may call. The course interface
is:

```c
DelimiterStatus delimiter_validate(
    const char *text,
    size_t depth_limit,
    size_t *out_error_index
);
```

A `DelimiterStatus` is the named C type for one validator result, such as
success, mismatch, or depth-limit failure.

A C string is a character sequence ending with a special zero character.
`text` points to that sequence. `const` promises that this function does not
change the input characters. The accepted `depth_limit` range is 0 through
1024.

An error index is the numbered input position at which a problem is
reported. `out_error_index` points to the caller's output location.
Successful validation writes `SIZE_MAX`, the greatest value `size_t` can
hold, used here to mean “no error index.” An unmatched closing, mismatch, or
depth-limit result writes the responsible delimiter's index. An unclosed
opening writes the string length, which marks the end of the input. Invalid
arguments and allocation failure leave the output unchanged.

Four small failures show why every check matters:

| Input | Error index | Status |
|---|---:|---|
| `A(B[C]{D})` | `SIZE_MAX` | `DELIMITER_OK` |
| `A)B` | `1` | `DELIMITER_UNMATCHED_CLOSE` |
| `A(B]` | `3` | `DELIMITER_MISMATCH` |
| `A(B` | `3` | `DELIMITER_UNCLOSED_OPEN` |
| `A([B{C}])`, limit 2 | `4` | `DELIMITER_DEPTH_LIMIT` |

An empty string or a string containing only ordinary characters is valid for
any allowed limit, including zero. It needs no push and ends with an empty
Stack.

The depth-limit push fails before changing the state. At that moment the
Stack remains `(`, `[` from bottom to top.

Malformed input breaks the stated form rules. Rejecting it at the first
known failure avoids continuing with unreliable state. The temporary Stack
created by the validator must still be destroyed so its owned storage is
released.

## 7. Cost

Time complexity describes how work grows. Let `n` be Stack size and `m`
be expression length.

- `O(1)` means a fixed amount of work.
- `O(n)` means work may grow with `n`.
- Amortized `O(1)` means constant average work across a long sequence,
  although an occasional operation is more expensive.

Geometric growth increases capacity by a fixed factor, such as doubling.

| Task | Cost | Reason |
|---|---:|---|
| `peek` | `O(1)` | reads `data[size - 1]` |
| `pop` | `O(1)` | reads one item and decreases `size` |
| push with spare capacity | `O(1)` | writes one item |
| one push that grows storage | `O(n)` | existing characters may be copied |
| long sequence of geometrically growing pushes | amortized `O(1)` each | occasional copying is spread across the sequence |
| delimiter validation | `O(m)` | each input character is handled once |

Course growth begins at capacity 4 and then doubles. It is clipped—reduced
when necessary—to the explicit limit. Thus, limit 2 produces the capacity
sequence `0 → 2`, while limit 6 produces `0 → 4 → 6`.

## 8. Four different uses of “stack”

These phrases share a word but do not name the same thing.

- The Stack ADT is the collection we design and use through `push`,
  `peek`, and `pop`.
- A **runtime call stack** is bookkeeping commonly used by the tools that
  execute C to manage function calls that have begun but not finished.
- A call frame is saved information for one such unfinished function call.
- Stack memory is an informal name for a memory region many
  systems use for call information and local variables. A local variable is
  named storage belonging to one function call. C does not require every
  system to arrange memory identically.
- A buffer is a bounded area that stores a sequence of values. A
  **stack-buffer overflow** is a write past the permitted end of such a
  buffer in the commonly named stack-memory region.

Calling `push` may itself involve a normal function call, but a `CharStack`
item is not a call frame. A correct Stack ADT also does not automatically
prevent unrelated buffer mistakes elsewhere in a program.

Recursion occurs when a function calls itself directly or through other
functions. Recursive calls commonly use runtime call frames. An explicit
Stack ADT can also remember unfinished work, but it is a separate data
structure controlled by the program.

## 9. Forward link: depth-first exploration

An algorithm is a precise, step-by-step method. **Depth-first search
(DFS)** is a later algorithm for exploring tree nodes or graph vertices. A
tree node is one stored tree item. A graph vertex is one stored graph item.

DFS can use LIFO storage for unfinished work. Later modules provide a Stack
whose item type is `TreeNode *` and another whose item type is a vertex ID,
a small number naming one graph vertex.

Only the connection belongs here: the LIFO contract transfers, while the
stored item type changes. The DFS steps and trace wait for Modules 5 and 6.

## 10. Reliability boundary

The nesting limit is a **resource boundary**, a stated limit on time or
storage use. It prevents deeply nested input from consuming unbounded Stack
storage. Running out of permitted storage is resource exhaustion.

The training expressions are synthetic, meaning invented for safe
practice. Correct delimiters prove only that grouping marks are well formed.
They do not prove that a real security policy grants intended permissions or
is safe.

**Key sentence:** a Stack exposes only its most recently added item; checked
operations and an explicit limit make that rule safe to use.
