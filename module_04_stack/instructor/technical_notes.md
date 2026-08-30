# Technical Notes - Module 4 Character Stack

## Scope

The production model is a dynamically stored character Stack ADT with an
explicit maximum size. **Dynamically stored** means that the implementation
requests and resizes storage while the program runs. The public behavior is
LIFO: the last character pushed is the first character popped.

**Public** means visible to the other code that uses this module. A
**pointer** is a value storing a memory address, and **contiguous storage**
places values in one unbroken memory region.

The implementation revisits Module 1's contiguous storage, separate size and
capacity, bounds checks, and unchanged state after rejection. Checked growth
and ownership of a replaceable array are new requirements here, not
prerequisites from Chapter 1. Students do not build a generic `void *`
container or a linked-node backend.

The parser recognizes only six delimiter characters:

```text
( ) [ ] { }
```

All other characters are ignored. Therefore
`delimiter_validate` reports only delimiter structure; it does not establish
that an expression is meaningful, authorized, or safe to execute.

## Canonical public model

The public maximum is:

```c
#define CHAR_STACK_MAX_LIMIT 1024U
```

The field order and types are:

```c
typedef struct {
    char *data;
    size_t size;
    size_t capacity;
    size_t limit;
} CharStack;
```

`data` points to the owned contiguous buffer. `size` counts occupied
characters. `capacity` counts available character slots. `limit` is the
policy maximum for that particular stack.

The stack statuses, in public order, are:

```c
typedef enum {
    STACK_OK = 0,
    STACK_INVALID_ARGUMENT,
    STACK_LIMIT,
    STACK_UNDERFLOW,
    STACK_ALLOCATION,
    STACK_INVALID_STATE
} StackStatus;
```

The delimiter statuses, in public order, are:

```c
typedef enum {
    DELIMITER_OK = 0,
    DELIMITER_INVALID_ARGUMENT,
    DELIMITER_UNMATCHED_CLOSE,
    DELIMITER_MISMATCH,
    DELIMITER_UNCLOSED_OPEN,
    DELIMITER_DEPTH_LIMIT,
    DELIMITER_ALLOCATION
} DelimiterStatus;
```

The exact public declarations are:

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

DelimiterStatus delimiter_validate(
    const char *text,
    size_t depth_limit,
    size_t *out_error_index
);
const char *delimiter_status_name(DelimiterStatus status);
```

`out_error_index` is changed only on delimiter success or a structural
delimiter result. It receives `SIZE_MAX` on success, the offending closing
index for unmatched close or mismatch, the string length for unclosed open,
and the rejected opening index for depth limit. Invalid arguments and
allocation failure leave it unchanged.

## State invariant

An **invariant** is a rule that must hold whenever a completed object is
offered to a public operation. The validator should accept exactly the
documented initialized states and reject contradictory field combinations.
The central relationships are:

```text
size <= capacity <= limit <= 1024
capacity == 0 exactly when data == NULL
```

When `size > 0`, the top is `data[size - 1]`. Unused slots from `size`
through `capacity - 1` have no public value requirement.

Do not read through `data` merely to validate where the pointer came from.
Standard C cannot determine from an arbitrary non-`NULL` pointer whether it
came from a live compatible allocation. The validator checks representable
field relationships; ownership and lifetime remain caller obligations. A
**lifetime** is the period during which an object exists and may be used.

An invalid existing object returns `STACK_INVALID_STATE`. A missing required
pointer argument returns `STACK_INVALID_ARGUMENT`. Keep these
categories distinct.

## Initialization and destruction

Initialization validates its arguments before writing any field. A
successful lazy initialization records:

```text
data = NULL
size = 0
capacity = 0
limit = requested limit
```

Call `char_stack_init` only for an uninitialized or previously destroyed
object. It does not release an existing live allocation before replacing the
fields, so using it to reinitialize a live Stack would lose the owned
address.

**Lazy** means storage is not requested until the first push. This makes
initialization independent of allocation success and gives an empty stack a
small canonical state. Limits from zero through 1024 are accepted. A larger
limit returns `STACK_LIMIT`; a `NULL` stack pointer returns
`STACK_INVALID_ARGUMENT`. Either failure leaves the caller's object
unchanged.

`char_stack_destroy` releases the buffer owned by the object and resets all
fields to the header's documented destroyed state. Destroy must be safe for
every valid initialized state, including a zero-capacity stack. Do not teach
that arbitrary uninitialized bytes can safely be destroyed; the caller must
first provide an initialized or otherwise documented state.

Copying a `CharStack` with ordinary structure assignment copies its pointer
but not the allocated character array. The two copies would then claim the
same storage. Treat a live `CharStack` as non-copyable unless a future API
defines an explicit **deep copy**, an operation that requests separate
storage and copies every character.

## Push and growth

`char_stack_push` follows this order:

1. reject a `NULL` stack pointer;
2. validate the existing stack state;
3. if `size == limit`, return `STACK_LIMIT`;
4. if `size == capacity`, calculate a legal new capacity;
5. request the new storage using a temporary pointer;
6. only after success, store the pointer and capacity in the stack;
7. store the new character at `data[size]`;
8. increase `size`; and
9. return `STACK_OK`.

The capacity sequence begins at 4 and is clipped to the stack's limit:

```text
new_capacity = min(4, limit)               when capacity == 0
new_capacity = min(capacity * 2, limit)    otherwise
```

Because the public limit is at most 1024, doubling a valid capacity cannot
approach `SIZE_MAX`, the greatest `size_t` value. Still teach the general
habit of clipping before committing arithmetic in production containers.

Use a temporary result for `realloc`. `realloc` is the C library operation
that may resize an allocated region and return its new address. On failure
it returns `NULL` while the original region remains valid. Assigning its
result directly to `stack->data` would lose the original address and violate
ownership. The checked implementation returns `STACK_ALLOCATION`
without changing `data`, `size`, `capacity`, `limit`, or existing
characters.

## Pop and peek

Both operations first reject missing pointers, then validate the stack, then
check `size`.

- Empty pop or peek returns `STACK_UNDERFLOW`.
- Neither operation invents a special failure character because every
  `char` value could be legitimate data.
- On failure, the caller's output character remains unchanged.
- Successful peek copies `data[size - 1]` to the output and changes no stack
  field.
- Successful pop first calculates the top result, then decreases size and
  writes the output only on the successful path.

The implementation need not shrink capacity after pop. Retaining the buffer
makes pop constant work and permits later pushes to reuse the slots.
The caller must provide an output location outside this Stack's owned
character allocation; the API does not check output-to-buffer aliasing.
**Aliasing** means two access paths refer to the same storage.

## Failure atomicity

**Failure atomicity** means a failed operation appears not to have happened:
the observable object state and any checked output are unchanged. Require
tests for:

- initialization with a `NULL` argument or an excessive limit, checking the
  distinct statuses and unchanged object;
- push at the configured limit;
- push when a growth request fails;
- pop and peek on an empty stack;
- any operation on an invalid existing state; and
- a `NULL` caller-provided output.

For a failed growth, compare not only the four public fields but also every
character below `size`. A pointer equality check alone is insufficient
evidence.

## Delimiter algorithm

Maintain one `CharStack` containing only unmatched opening delimiters.

```text
for each input character:
    if it is (, [, or {:
        push it
    else if it is ), ], or }:
        if the stack is empty:
            report unmatched close
        peek at the newest unmatched opening
        if the types do not match:
            report mismatch
        pop the matched opening

after the scan:
    if the stack is not empty:
        report unclosed opening
    report success
```

The public implementation may use `peek` underflow to detect an unmatched
close. A push limit result maps to `DELIMITER_DEPTH_LIMIT`; an allocation
result maps to `DELIMITER_ALLOCATION`. Any impossible internal Stack status should be
handled conservatively according to the checked reference contract, not
silently converted to valid input.

Destroy the temporary stack on every path after successful initialization.
A single cleanup section is often easier to audit than many duplicated
destroy calls. "Cleanup" means releasing resources before returning.

### Canonical diagnoses

| Input and condition | Result | Detection point |
|---|---|---|
| `A(B[C]{D})` | `DELIMITER_OK` | End, with empty stack |
| `A)B` | `DELIMITER_UNMATCHED_CLOSE` | `)` while stack is empty |
| `A(B]` | `DELIMITER_MISMATCH` | `]` while top is `(` |
| `A(B` | `DELIMITER_UNCLOSED_OPEN` | End, with `(` still stored |
| `A([B{C}])`, limit 2 | `DELIMITER_DEPTH_LIMIT` | `{` would create size 3 |

The valid expression's stack states after delimiters are:

```text
(       -> (
[       -> ([
]       -> (
{       -> ({
}       -> (
)       -> empty
```

Its maximum stack size is 2.

## Operation costs

**Operation cost** describes how work changes as the input grows.
`O(1)` means a fixed amount of work. `O(s)` means work proportional to
current stack size `s`; `O(m)` means work proportional to expression length
`m`. **Amortized** means an occasional expensive operation is averaged
across a sequence of operations.

| Operation | Time | Additional storage | Reason |
|---|---:|---:|---|
| Validate stack fields | `O(1)` | `O(1)` | A fixed number of field checks |
| Initialize | `O(1)` | `O(1)` initially | Lazy initialization requests no buffer |
| Peek | `O(1)` | `O(1)` | Read one top character |
| Pop | `O(1)` | `O(1)` | Read one character and reduce size |
| Push without growth | `O(1)` | `O(1)` | Write one character |
| One push with growth | `O(s)` worst case | New capacity | Resizing may copy `s` existing characters |
| Push over a sequence | `O(1)` amortized | Up to the limit | Doubling makes growth infrequent |
| Delimiter validation | `O(m)` | `O(d)` | Scan `m` characters; store at most depth `d` |

Here `d` is the greatest number of unmatched openings at one time and is
bounded by `limit`. The parser does not require work proportional to
`m * m` merely because a push can occasionally resize. **Geometric growth**
means multiplying capacity by a fixed factor; it keeps total copying
proportional to `m` over the scan.

## Four meanings that must remain separate

| Term | Meaning | Who manages it | Relevant failure |
|---|---|---|---|
| Stack ADT | LIFO behavior through push, pop, and peek | The program through this API | Checked limit or underflow status |
| ArrayList backend | Resizable contiguous character storage | The `CharStack` implementation | Allocation failure or invalid fields |
| Runtime call stack | Saved call frames for active functions | Compiler and C runtime | Excessive call depth may exhaust runtime space |
| Stack buffer | A local fixed-size array often stored in one call frame | The function containing the array | Out-of-bounds access can overwrite memory |

A **call frame** stores information needed for one active function call.
Recursion creates more active calls and therefore more frames. The explicit
`CharStack` does not automatically create call frames. Conversely, a
function can use the runtime call stack without operating a Stack ADT.

Use precise phrases:

- "ADT limit reached" for `STACK_LIMIT`;
- "runtime call-stack exhaustion" for excessive recursion; and
- "stack-buffer out-of-bounds write" for overwriting a local array.

## Later transfer without early teaching

In Module 5, a stack can hold postponed tree work while one branch is
followed deeply. In Module 6, a stack can hold graph vertices waiting for
depth-first exploration; graph search also needs a separate visited record
because graphs can contain cycles. These are previews only. Do not require
students to write tree or graph DFS here.

The later typed stacks may hold `TreeNode *` values or vertex indexes rather
than `char` values. They preserve the same LIFO ADT contract without forcing
students to design a generic untyped container.

## Test priorities

The public and instructor tests together should cover:

1. initialization at small and maximum legal limits;
2. complete-field preservation after invalid initialization;
3. first growth, repeated growth, and final clipping to limit;
4. LIFO order across mixed push, peek, and pop;
5. empty underflow with unchanged output;
6. limit rejection with unchanged state;
7. invalid-state rejection;
8. allocation failure during initial and later growth;
9. destruction and the documented reset state;
10. empty and delimiter-free expressions;
11. the canonical valid expression;
12. unmatched close, mismatch, unclosed open, depth limit, and allocation
    mapping; and
13. status-name coverage, including an unknown enumeration value. An
    **enumeration** is a C type limited to named choices.

The allocation-failure control is compiled only when
`CHAR_STACK_TESTING` is defined. Student core-test builds use that controlled
hook, while ordinary and student-authored-test builds do not. Extension tests
and the solution remain instructor-only.

## Instructor implementation audit

- [ ] Public constants, enumeration order, fields, and signatures match the
      student materials.
- [ ] `limit` never exceeds 1024.
- [ ] No function reads `data[size - 1]` when `size == 0`.
- [ ] Growth begins at 4 and is clipped to `limit`.
- [ ] A temporary pointer protects the old allocation during resize.
- [ ] Every checked output remains unchanged on failure.
- [ ] Every failed mutating operation preserves all four fields and data.
- [ ] Delimiter status mapping distinguishes all four malformed categories.
- [ ] Every initialized parser stack is destroyed on every return path.
- [ ] Complexity claims say amortized `O(1)` for push, not worst-case `O(1)`.
- [ ] Security language limits the parser claim to delimiter structure.
- [ ] DFS appears only as forward transfer.
