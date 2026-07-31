# Lab — A Character Stack and Delimiter Checker

## Purpose

Build a stack of characters, then use it to check whether `()`, `[]`, and
`{}` are properly nested.

Start with this example:

```text
text: a[(b)]
read `[`: push `[`
read `(`: push `(`
read `)`: peek reports `(`, so pop it
read `]`: peek reports `[`, so pop it
result: valid
```

The latest opening delimiter must close first. That is exactly the rule a
stack provides.

## Three meanings of “stack”

These phrases are related but not interchangeable:

1. The **Stack abstract data type (ADT)** is the behavior studied here. An
   abstract data type defines operations and rules without requiring one
   storage method. Its rule is **last-in, first-out (LIFO)**: the last value
   added is the first value removed.
2. The **runtime call stack** is bookkeeping commonly used by C systems to
   manage active function calls. This lab does not implement or control it.
3. A **stack buffer** is a fixed-size local array that is commonly stored in a
   function's runtime call-stack memory. It does not grow like `CharStack`.

In this lab, “Stack” means the ADT unless another meaning is stated.

## The five Stack ideas

- **Push** adds a value at the top.
- **Pop** removes and reports the top value.
- **Peek** reports the top without removing it.
- **Underflow** means trying to pop or peek when the stack is empty.
- **Top** means the newest logical value.

If the stack contains:

```text
data: [ 'A' ][ 'B' ][ 'C' ][ unused ]
index:    0      1      2       3
size: 3
```

then the top is `data[size - 1]`, or `data[2]`. `data[size]` is the next
unused position, not the top.

## How this Stack is stored

`CharStack` is backed by the same growable-array idea used for an ArrayList.
A **growable array** owns a block of memory that can be replaced by a larger
block when it fills.

```c
typedef struct {
    char *data;
    size_t size;
    size_t capacity;
    size_t limit;
} CharStack;
```

- `data` points to the owned character array.
- `size` is the number of logical characters.
- `capacity` is the number of character slots currently reserved in memory.
- `limit` is the greatest permitted size.

An **invariant** is a rule that must remain true between public operations.
This lab requires:

```text
0 <= size <= capacity <= limit <= 1024
```

It also requires:

- `capacity == 0` means `data == NULL` and `size == 0`;
- positive capacity means `data != NULL`;
- logical characters occupy indexes `0` through `size - 1`;
- the top is `data[size - 1]` when `size > 0`; and
- a failed operation leaves the previous valid stack unchanged.

`char_stack_validate` checks these visible field relationships. It cannot
prove that a non-null pointer still refers to live memory or that only one
object owns that memory.

## Growth rule

The first allocation requests capacity 4. Later growth doubles capacity:

```text
0 → 4 → 8 → 16 → ...
```

Growth is **clipped** to `limit`, meaning it stops exactly at the limit when
doubling would go beyond it. A stack whose limit is 10 grows:

```text
0 → 4 → 8 → 10
```

An **allocation** is a block of memory reserved for a program. `realloc` is a
C library function that attempts to resize one. It can fail and return
`NULL`. Store its result in a temporary pointer:

```c
char *candidate = realloc(old_pointer, new_bytes);
```

Commit `candidate` to `stack->data` only after success. A **commit point** is
the moment new state becomes official. Assigning `realloc` directly to
`stack->data` can lose the old allocation when growth fails.

Pop never shrinks storage in this module. Removing a value changes `size`,
but it preserves `data` and `capacity`.

## Public operations

An **API** is the set of public types and functions other code may use.

```c
StackStatus char_stack_init(CharStack *stack, size_t limit);
StackStatus char_stack_validate(const CharStack *stack);
StackStatus char_stack_push(CharStack *stack, char value);
StackStatus char_stack_pop(CharStack *stack, char *out_value);
StackStatus char_stack_peek(
    const CharStack *stack,
    char *out_value
);
void char_stack_destroy(CharStack *stack);
const char *stack_status_name(StackStatus status);
```

A **status** is a named result. `STACK_OK` means success. The other values
report an invalid argument, a limit reached by `push`, an initialization
limit above 1024, underflow, allocation failure, or invalid representation
state.

An **output parameter** is a pointer through which a function reports an
additional result. `pop` and `peek` change `*out_value` only on success.
Their output pointer must not point anywhere inside the stack's allocation.

Initialization and cleanup rules:

- `limit` may be zero and may not exceed `CHAR_STACK_MAX_LIMIT` (`1024`);
- call `char_stack_init` only on an uninitialized or destroyed object;
- reinitializing a live stack would lose its allocation;
- call `char_stack_destroy` only on `NULL`, an initialized stack, or an
  already destroyed stack;
- destroy releases storage and resets all four fields;
- do not make a **shallow copy**, meaning a second struct copy that contains
  the same owning pointer.

## Delimiter checker

A **delimiter** is a character that marks a boundary. This checker recognizes
three opening delimiters and their matching closers:

```text
( matches )
[ matches ]
{ matches }
```

A pair is **nested** when one complete pair appears inside another, as in
`{[()]}`.

The checker scans a **C string**, a character sequence ending with the special
zero character `'\0'`.

```c
DelimiterStatus delimiter_validate(
    const char *text,
    size_t depth_limit,
    size_t *out_error_index
);
```

The **depth** is the number of opening delimiters not yet closed. Push each
opening delimiter. For a closing delimiter:

1. peek at the latest opening;
2. report an unmatched close if the stack is empty;
3. report a mismatch if the two characters are not a pair; and
4. pop only after a successful match.

Use only the public Stack functions inside the checker. Do not inspect
`stack.data`, `stack.size`, or other Stack fields there.

Indexes begin at zero. The output rule is:

| Result | `out_error_index` |
|---|---:|
| `DELIMITER_OK` | `SIZE_MAX`, a marker meaning “no error index” |
| `DELIMITER_UNMATCHED_CLOSE` | closing-delimiter index |
| `DELIMITER_MISMATCH` | closing-delimiter index |
| `DELIMITER_UNCLOSED_OPEN` | text length |
| `DELIMITER_DEPTH_LIMIT` | opening index that would exceed the limit |
| invalid argument or allocation failure | unchanged |

Characters other than `()[]{}` are ignored.

## Files

You receive public headers, starter files, tests, build tools, and an isolated
autopsy.

Edit only:

- `code/starter/char_stack.c`;
- `code/starter/delimiter_validator.c`; and
- `code/tests/test_student.c`.

Do not edit public headers, the supplied core tests, autopsy files, or build
files unless the instructor explicitly authorizes it.

## Checkpoints

### 1. Read before editing

Read:

- `code/include/char_stack.h`;
- `code/include/delimiter_validator.h`;
- the TODO comments in both starter files; and
- the first failing public-test requirement.

### 2. Finish Stack growth and push

- Validate before using the representation.
- Report `STACK_LIMIT` before writing when `size == limit`.
- Select capacity 4 or doubled capacity, clipped to `limit`.
- Call the supplied allocation wrapper with the old pointer.
- Keep the result in `candidate`.
- Commit `data` and `capacity` only after successful allocation.
- Write at the old `size`, then increase `size`.

The supplied wrapper normally calls `realloc`. Public tests can make its next
call fail once so that failure preservation is observable.

### 3. Finish pop and peek

- Reject a null output pointer.
- Validate the stack.
- Report underflow before reading an empty stack.
- Read only `data[size - 1]`.
- Change the output only on success.
- Make peek leave every stack field unchanged.
- Make pop decrease `size` without shrinking.

### 4. Finish delimiter matching

Complete `delimiters_match` for the three exact pairs.

Then complete the scan:

- call `char_stack_push` for an opener;
- map `STACK_LIMIT` to `DELIMITER_DEPTH_LIMIT` at the current index;
- leave the caller's output unchanged on allocation failure;
- use peek, pair comparison, and pop for a closer; and
- use `char_stack_peek` after the scan to distinguish an empty stack from an
  unclosed opening delimiter.

Always destroy the temporary Stack created by the checker before returning
after successful initialization.

### 5. Run core tests

From the `code` directory:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1
```

The starter is intentionally incomplete, so tests fail at first. Work from
the earliest failure. Do not edit a supplied test just to make it pass.

### 6. Design three tests

Complete `code/tests/test_student.c`.

Together, your tests must add:

- one LIFO sequence;
- one boundary or failure-preservation case; and
- one delimiter result with its exact error index.

Explain in comments what each test adds beyond the visible tests. Clean up
every initialized stack on every return path.

### 7. Run your tests and the autopsy

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

## Cost target

`peek` and `pop` take **O(1)** time: their work does not grow with stack size.
Most pushes also take O(1). A growth push copies or moves more storage, but
geometric doubling makes push **amortized O(1)**—constant average work across
a long sequence.

For text length `n` and greatest nesting depth `d`, delimiter validation takes
O(n) time and O(d) additional memory.

## Safe scope and policy boundary

Use only instructor-provided or student-created synthetic strings.
**Synthetic** means made for the exercise rather than taken from a live
system. Do not paste passwords, tokens, private source code, production
configuration, or live logs into the lab.

This checker answers only whether three delimiter kinds are nested according
to its simple rules. It does not understand quoted strings, comments, escapes,
or a complete programming language. A passing result does not prove that text
is correct, trustworthy, or secure. The depth limit is a bounded-resource
policy, not an exploit detector or security guarantee.

## Completion criteria

- core and student-authored tests pass;
- warning-enabled compilation reports no warning in student-controlled code;
- the Stack invariant and top index are correct;
- failures preserve stack state and required outputs;
- the checker reports each required index exactly; and
- the autopsy explanation identifies the first broken rule.
