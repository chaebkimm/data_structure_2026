# Instructor Lesson Plan - Module 4: Stack Abstract Data Type

## Purpose and limits

This module introduces a **stack**, a collection in which only one end is
available for adding, inspecting, and removing items. That available end is
the **top**. Students begin with behavior, then implement a character stack
whose storage reuses the resizable-array ideas from Module 1.

An **abstract data type (ADT)** describes permitted operations and their
behavior without requiring one storage method. A **backend** is the storage
method hidden behind that behavior. This module's backend is an
ArrayList-style contiguous array: its elements occupy one unbroken region of
memory and its capacity can grow.

By the end of the module, students should be able to:

1. state the last-in, first-out rule independently of the backend;
2. trace `push`, `pop`, and `peek` without reading below the top;
3. implement and test a checked ArrayList-backed `CharStack`;
4. use that stack to validate nested parentheses, brackets, and braces;
5. explain underflow, a nesting-depth limit, ownership, and failure
   atomicity; and
6. distinguish the Stack ADT from the C runtime call stack and a stack
   buffer.

The delimiter exercise is a small input-validation model, not a complete
programming-language or security-policy parser. A **parser** is code that
examines input according to structural rules. Students preview how a stack
will support later depth-first exploration, but do not implement depth-first
search (DFS) in this module.

## Beginner language sequence

Introduce each term immediately before students need it. Repeat a short
definition when a term returns in a later stage.

| Term | First-use explanation |
|---|---|
| collection | Several values treated as one managed group |
| stack | A collection whose available end is called the top |
| top | The one end where stack items are added, inspected, or removed |
| last-in, first-out (LIFO) | The most recently added remaining item is removed first |
| push | Add one item at the top |
| pop | Remove and report the top item |
| peek | Report the top item without removing it |
| trace | A written record of state after each operation |
| state | The values currently stored in an object |
| underflow | An attempt to pop or peek when the stack is empty |
| abstract data type (ADT) | A behavior contract independent of storage details |
| contract | What an operation accepts, returns, changes, and preserves |
| application programming interface (API) | The public types and function names other code may use |
| function | A named block of instructions that performs one task |
| caller | The code that asks a function to run |
| output | A result written into caller-provided storage |
| status code | A named result reporting success or one kind of failure |
| backend | The hidden storage method used to implement an ADT |
| ArrayList-backed | Stored in a resizable contiguous array |
| contiguous | Occupying one unbroken region of memory |
| computer memory | Storage the program uses for instructions and values while running |
| pointer | A value that stores a memory address |
| `data` | The pointer to the stack's allocated character array, or `NULL` when none exists |
| `size` | The number of characters currently in the stack |
| `capacity` | The number of characters that fit before storage must grow |
| `limit` | The greatest size this stack is allowed to reach |
| invariant | A rule that must hold whenever a completed object is used |
| ownership | Responsibility for eventually releasing requested storage |
| allocation | A region of memory requested while the program runs |
| allocation failure | A request for memory that cannot be satisfied |
| failure atomicity | If an operation fails, the object remains exactly as it was before the call |
| resource boundary | A stated limit on storage or time use |
| delimiter | A symbol such as `(`, `)`, `[`, `]`, `{`, or `}` that marks a boundary |
| opening delimiter | One of `(`, `[`, or `{` |
| closing delimiter | One of `)`, `]`, or `}` |
| matching pair | An opening and closing delimiter of the same kind |
| nesting | Placing one matched region inside another |
| malformed input | Input that breaks a required structural rule |
| depth limit | The greatest permitted number of unmatched openings at one time |
| runtime call stack | Bookkeeping commonly used by a C implementation for active function calls |
| call frame | Saved information for one active function call |
| stack buffer | A local fixed-size array commonly stored in a call frame |
| recursion | A function directly or indirectly calling itself |
| depth-first search (DFS) | A later procedure that follows one branch deeply before returning |
| time complexity | A description of how work changes as input grows |
| `O(1)` | A fixed amount of work |
| `O(n)` | Work that may grow with an input amount called `n` |
| amortized `O(1)` | Constant average work across many operations, including occasional expensive growth |
| synthetic | Invented for a safe learning exercise rather than copied from an operating system |
| header file | A C file that declares public types and functions |
| implementation file | A C file containing the instructions inside functions |
| public test | A check visible to students |
| reference solution | The instructor's completed implementation |
| regression test | A retained check that detects the return of a repaired defect |

Do not use "stack overflow" without qualification. It may mean exceeding an
ADT limit, exhausting runtime call-stack space through deep calls, or
overwriting a local buffer. Those are different events with different
causes.

## Five release gates

A **release gate** is a planned point at which the instructor gives students
the next materials. Preserve a student's initial reasoning before showing a
formal model.

| Gate | Release point | Give students | Keep back |
|---|---|---|---|
| A - Inquiry | Start of Meeting A | Standard or linear inquiry prompt | Formal stack vocabulary, LIFO rule, code, answers |
| B - Representation | After each student preserves an initial model | Representation reveal and exactly-three-target Cognitive Pause; vocabulary opens only after the pause response is preserved | Vocabulary during the pause; investigation answers, textbook, code |
| C - Investigation | After the five-minute pause and brief comparison | Standard or linear investigation worksheet | Textbook, completed models, code |
| D - Calibrated explanation | After the student preserves the Stage C core | Beginner-first notes and equivalent stack models | Lab package and instructor materials |
| E - Lab and evidence | After retrieval and Gate D calibration in Meeting B | Lab, evidence form, rubric, autopsy, public header, starter, public tests, student-test template, and build files | Reference solution, instructor tests, answer key |

The answer key, reference solution, and instructor-only tests remain private
until the instructor-selected review point. An accommodation may change the
clock, response mode, or room; it should not reverse the sequence of attempt,
preserve, and compare.

The Stage C core is Sections A through F. Sections G through I can continue
in the independent completion window.

---

# Meeting A - Discover LIFO and Nested Matching (90 minutes)

## Macro-Question

> If the most recently opened task must be completed first, what access rule
> should the structure enforce?

| Minutes | Activity | Instructor move | Evidence |
|---:|---|---|---|
| 0-5 | Welcome and boundary | State that students are discovering an access rule before receiving its name. State that DFS is only previewed. | Student restates the boundary |
| 5-20 | Gate A inquiry | Release one inquiry format. Require a preserved first response before discussion. | Initial access model |
| 20-29 | Compare everyday models | Use a stack of cards or trays. Ask which item can leave without moving another. Avoid treating every physical stack as a perfect software model. | One justified removal |
| 29-40 | Gate B representation reveal | Define stack, top, LIFO, push, pop, peek, ADT, and backend. Connect `top` to `data[size - 1]` only when `size > 0`. | Labeled state model |
| 40-45 | Five-minute Cognitive Pause | Give exactly the three targets below. Do not add hints or a fourth task during the timer. | Individual three-target response |
| 45-54 | Compare and correct | Students preserve original marks, then annotate corrections. Read every delimiter aloud for nonvisual access. | Corrected trace |
| 54-65 | Operation traces | Trace mixed push, pop, and peek. Ask what changes and what remains unchanged. Name empty-stack rejection as underflow. | Operation table |
| 65-77 | Nested delimiter model | Map an opening delimiter to push and a matching closing delimiter to peek then pop. Use `A(B[C]{D})`. | Complete valid trace |
| 77-84 | Malformed cases | Contrast unmatched close, mismatch, leftover opening, and depth limit. Ask at what exact character each is known. | Four diagnoses |
| 84-87 | Separate meanings of stack | Contrast the ADT, its backend, the runtime call stack, and a stack buffer. | Four-way statement |
| 87-90 | Exit and Gate C | Release the investigation. Ask which opening symbol must be compared with a closing symbol and why. | Two-sentence exit response |

## Stage B Cognitive Pause - exactly three targets

Read the convention before starting: write stack contents from bottom to top,
left to right. The rightmost stored character is the top.

Students receive exactly these targets:

1. Trace `A(B[C]{D})`. Record the stack after every delimiter and report the
   maximum size reached and final state.
2. Diagnose `A(B]` and `A)B`. For each, identify the symbol where failure is
   known, name mismatch or unmatched closing delimiter, and record the stack
   state immediately before that symbol is handled.
3. With limit `2`, diagnose `A([B{C}])` at `{`, then diagnose `A(B` at end of
   input. Record the unchanged stack `(`, `[` for the first and the final
   stack `(` for the second. Explain why the first is a depth-limit failure
   and the second is a leftover opening.

Do not answer questions during the five minutes except to repeat the
directions or provide an approved access accommodation. Do not add another
target.

## Meeting A checks

Before moving on, verify that students can state:

- LIFO means the newest remaining item is the next removable item;
- the top is `data[size - 1]` only when `size` is greater than zero;
- `push` changes the top, `pop` removes it, and `peek` does not remove it;
- an empty `pop` or `peek` is underflow, not a character result;
- a closing delimiter must match the newest unmatched opening delimiter;
- an error detected during the scan differs from an unclosed opening found
  only at end of input;
- the ADT behavior does not require a particular backend; and
- an ADT stack is not the runtime call stack or a local stack buffer.

---

# Meeting B - Implement a Checked Character Stack (90 minutes)

## Coding question

> How can every stack operation either complete its contract or leave the
> stack unchanged?

| Minutes | Activity | Instructor move | Evidence |
|---:|---|---|---|
| 0-8 | Retrieval | Without notes, trace push `(`, push `[`, peek, pop, push `{`. Then compare. | Retrieval trace |
| 8-14 | Gate D calibration | Use the textbook and models to correct terms. Emphasize top and empty-state rules. | Annotated correction |
| 14-20 | Gate E orientation | Release the lab. Define header, implementation, public test, and reference solution before naming files. | Package map |
| 20-31 | State and invariant | Label `data`, `size`, `capacity`, and `limit`. Check the invariant before discussing operations. | Valid/invalid state table |
| 31-42 | Initialization and ownership | Establish the empty initialized state and the one matching destroy responsibility. State that initialization is only for an uninitialized or destroyed object; it does not replace a live allocation. Explain that the `CharStack` owns its character buffer. | Ownership sentence |
| 42-58 | Push and growth | Begin capacity at 4, clipped to the limit. Double when full, clip again, and store the new pointer in the stack only after allocation succeeds. | Completed push plus growth trace |
| 58-67 | Pop and peek | Check validity and nonempty state before reading `data[size - 1]`. Delay caller-output writes until success is certain. | Passing boundary tests |
| 67-73 | Failure atomicity review | Compare snapshots before and after limit, underflow, invalid-state, and simulated allocation failures. | Preservation explanation |
| 73-83 | Delimiter validator | Connect opening to push, closing to peek/match/pop, end-of-input to empty check, and stack status to delimiter status. Destroy temporary storage on every exit. | Parser tests |
| 83-87 | Cost and vocabulary | Derive constant-time pop/peek, amortized constant-time push, linear parser time, and depth-bounded storage. | Cost table |
| 87-89 | Safe autopsy or fault case | Predict before running. Require an exact first broken contract and a regression test. | Prediction and observation |
| 89-90 | Submission check | Review required code, tests, trace, evidence form, and distinctions statement. | Completion checklist |

## Canonical representation

The shared model is an ArrayList-backed `CharStack` with these fields:

```c
#define CHAR_STACK_MAX_LIMIT 1024U

char *data;
size_t size;
size_t capacity;
size_t limit;
```

For a nonempty valid stack, the top character is:

```c
data[size - 1U]
```

`size_t` is an unsigned integer type used for sizes and indexes. A
**pointer** stores an address. `NULL` means that no allocated character array
is currently attached.

The public Stack statuses are:

```text
STACK_OK
STACK_INVALID_ARGUMENT
STACK_LIMIT
STACK_UNDERFLOW
STACK_ALLOCATION
STACK_INVALID_STATE
```

The public delimiter statuses are:

```text
DELIMITER_OK
DELIMITER_INVALID_ARGUMENT
DELIMITER_UNMATCHED_CLOSE
DELIMITER_MISMATCH
DELIMITER_UNCLOSED_OPEN
DELIMITER_DEPTH_LIMIT
DELIMITER_ALLOCATION
```

The public functions are:

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

`out_error_index` is the caller-provided location for the input index at
which a delimiter failure is detected. On success it receives `SIZE_MAX`, a
special `size_t` value used here to mean "no error index." Invalid arguments
and allocation failure leave it unchanged.

Do not permit students to rename statuses or access the stack's array as a
substitute for calling `push`, `pop`, and `peek`.

## Required invariant

An initialized completed stack must satisfy all of these:

1. `limit` is from zero through the public maximum of 1024;
2. `size <= capacity`;
3. `capacity <= limit`;
4. `capacity == 0` exactly when `data == NULL`; and
5. when `size > 0`, the top is `data[size - 1]`.

A zero limit is valid: the stack remains empty and every push returns
`STACK_LIMIT`. A destroyed stack has `data == NULL` and all three numeric
fields equal to zero, which is also a valid empty state.

## Growth model

When the stack needs its first character slot, capacity begins at 4, or at
the limit if the limit is below 4. Later growth doubles capacity but never
exceeds the limit. Examples:

| Limit | Capacity sequence as needed |
|---:|---|
| 2 | `0 -> 2` |
| 6 | `0 -> 4 -> 6` |
| 20 | `0 -> 4 -> 8 -> 16 -> 20` |

Do not grow when `size == limit`; return `STACK_LIMIT`. If storage growth
fails, return `STACK_ALLOCATION` and preserve all four fields and
all existing characters.

## Delimiter-status mapping

| Event | Delimiter result |
|---|---|
| `text == NULL`, `out_error_index == NULL`, or depth limit above 1024 | `DELIMITER_INVALID_ARGUMENT`; output unchanged |
| Closing delimiter with no unmatched opening | `DELIMITER_UNMATCHED_CLOSE`; output is closing index |
| Closing delimiter differs from newest unmatched opening | `DELIMITER_MISMATCH`; output is closing index |
| End of input with an opening still stored | `DELIMITER_UNCLOSED_OPEN`; output is string length |
| Opening delimiter would exceed the nesting limit | `DELIMITER_DEPTH_LIMIT`; output is opening index |
| Character-stack storage request fails | `DELIMITER_ALLOCATION`; output unchanged |
| Complete scan ends with an empty stack | `DELIMITER_OK`; output is `SIZE_MAX` |

Non-delimiter characters are ignored by this simplified validator. They are
not proof that the entire expression has meaningful syntax.

## Hint ladder

Reveal only one hint at a time:

1. What is the stack state before this operation?
2. Is the stack empty, and which index would name the top?
3. Does this operation change `size`, or only report a character?
4. Which invariant must be checked before reading from `data`?
5. Has the stack reached its limit?
6. Is more capacity needed before writing the new character?
7. Can the operation calculate a candidate result before changing the
   caller's stack or output?
8. For a delimiter, is this character opening, closing, or neither?
9. If it closes, what is the newest unmatched opening?
10. Has every temporary resource been released on this return path?

Stop after the first hint that restores productive work. Record the hint
level for instructional planning, not as a penalty.

## Common misconceptions

| Misconception | Diagnostic question | Correction |
|---|---|---|
| The first pushed item leaves first | "Which item is at the top now?" | A stack is last-in, first-out. |
| The top is `data[size]` | "What is the greatest occupied zero-based index?" | It is `size - 1` when nonempty. |
| Peek removes the item | "What field should peek change?" | A successful peek changes only its caller-provided output. |
| Pop from empty returns a special character | "Could that character also be valid data?" | Report `STACK_UNDERFLOW`; do not invent a character to stand for failure. |
| `capacity` is the item count | "How many slots are occupied?" | `size` counts items; `capacity` counts available slots. |
| Limit and capacity are identical | "Can capacity grow while the policy limit stays fixed?" | Capacity is current storage; limit is the allowed maximum size. |
| Failed growth may update capacity | "Did new storage actually become available?" | Failure atomicity requires the original state to remain unchanged. |
| Any earlier opening may match a close | "Which opening is newest and still unmatched?" | Nested matching requires the top opening. |
| Mismatch and unmatched close are the same | "Was the stack empty?" | Empty means unmatched close; a wrong nonempty top means mismatch. |
| End of input means success | "Is an opening still stored?" | A nonempty stack means an unclosed opening. |
| The ADT is the runtime call stack | "Who controls each structure?" | Program code operates the ADT; the C runtime manages active calls. |
| A stack-buffer bug is an ADT-limit result | "Was a local array overwritten?" | Buffer overwrite and a checked `STACK_LIMIT` are different. |
| Every push is constant work | "Can growth copy existing characters?" | Most pushes are constant; an occasional growth can copy `size` items. |

## Accessibility and pacing

- Pair every vertical stack drawing with a bottom-to-top text row and an
  operation table.
- Never use color alone to distinguish opening types or error classes.
- Read `data[size - 1]` aloud as "data at index size minus one."
- Read each delimiter by name: left parenthesis, right bracket, and so on.
- Permit cards, tactile tiles, typing, handwriting, dictation, or spoken
  traces.
- Supply the linear inquiry and investigation versions when spatial layout
  is a barrier.
- During the Cognitive Pause, read the convention and all three targets,
  allow an approved extended timer, and do not add help beyond access needs.
- Grade state reasoning and contract behavior, not drawing quality, visual
  alignment, typing speed, or memory for punctuation names.
- Announce the independent completion window before coding begins.

## Evidence collected

1. preserved Gate A access-rule model;
2. exactly-three-target Cognitive Pause with visible corrections;
3. canonical push/pop/peek state trace;
4. invariant and ownership explanation;
5. checked Stack API implementation and public-test results;
6. parser diagnoses for valid input and four malformed categories;
7. original boundary and failure-preservation tests;
8. operation and parser cost explanation;
9. ADT/backend/runtime-call-stack/stack-buffer distinction; and
10. one sentence previewing how a stack can remember postponed branches.

## After Meeting B - transparent completion window

The meetings establish the model and every core operation, but they need not
contain all debugging and documentation. Allow about 60-90 additional
minutes for students to finish starter tasks, run public tests, write
original tests, complete the autopsy, and submit the evidence form. Offer a
staffed lab period or equivalent remote support. Keep the due window visible
from Gate E onward and apply documented accommodations.

## Instructor readiness checklist

- [ ] Stage A does not reveal "stack," "LIFO," or the formal operation names.
- [ ] The Stage B pause contains exactly three targets.
- [ ] `A(B[C]{D})` is traced correctly before malformed inputs are compared.
- [ ] Top is never evaluated as `data[size - 1]` when `size == 0`.
- [ ] ArrayList retrieval is brief and explicitly connected to Module 1.
- [ ] All API names and statuses match the public header.
- [ ] Growth starts at 4, is clipped to `limit`, and never exceeds 1024.
- [ ] Failed operations preserve stack state and caller outputs.
- [ ] Every delimiter return path destroys its temporary character stack.
- [ ] The four meanings of "stack" remain distinct.
- [ ] DFS is previewed without assigning traversal implementation.
- [ ] Visual models have equivalent text or table forms.
- [ ] The completion window and help route are announced.
