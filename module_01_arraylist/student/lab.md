# Lab — Safe Authentication-Event ArrayList

## Purpose

Translate the textbook's dynamic-array model into the supplied `IntList`
interface. Implement checked access and append, finish the scaffolded growth
path, and verify the result with tests.

The textbook supplies the conceptual model: stored items occupy consecutive
positions from index 0, additions grow the memory space before an out-of-range
write, and old values keep their order. This lab adds API-specific safety
contracts needed by the repository implementation. Treat those contracts as
engineering extensions, not as missing prerequisites from the textbook.

The values represent synthetic authentication-event codes. No live systems or sensitive data are used.

## Files

You receive:

- `code/include/int_list.h`
- `code/starter/int_list.c`
- `code/tests/test_core.c`
- `code/tests/test_extension.c`
- `code/tests/test_student.c`
- `code/build.ps1`
- `code/Makefile`

Work in `code/starter/int_list.c` and `code/tests/test_student.c`. Do not change
the public header or instructor tests unless the instructor explicitly
authorizes it.

## Public API

```c
typedef struct {
    int *data;
    size_t size;
    size_t capacity;
} IntList;

typedef enum {
    INT_LIST_OK = 0,
    INT_LIST_ERR_INVALID_ARGUMENT,
    INT_LIST_ERR_OUT_OF_RANGE,
    INT_LIST_ERR_ALLOCATION,
    INT_LIST_ERR_OVERFLOW
} IntListStatus;

IntListStatus int_list_init(IntList *list);
void int_list_destroy(IntList *list);
bool int_list_is_valid(const IntList *list);
IntListStatus int_list_reserve(IntList *list, size_t minimum_capacity);
IntListStatus int_list_get(
    const IntList *list,
    size_t index,
    int *out_value
);
IntListStatus int_list_append(IntList *list, int value);
IntListStatus int_list_insert(
    IntList *list,
    size_t index,
    int value
);
IntListStatus int_list_remove(
    IntList *list,
    size_t index,
    int *out_value
);
```

`insert` and `remove` are extension functions. The core test target does not require them.

## Required representation contract

- `size <= capacity`.
- `capacity == 0` means `data == NULL` and `size == 0`.
- Positive capacity means `data` owns enough space for at least `capacity` integers.
- Only `[0, size)` contains logical elements.
- A failed operation leaves the prior valid list unchanged.
- Destroy releases the allocation and resets all fields.
- No saved interior pointer is used across a potentially growing operation.
- Call `int_list_init` only on an uninitialized or previously destroyed object.
  Reinitializing a live list loses its allocation.
- Call `int_list_destroy` only with `NULL` or a valid initialized/destroyed
  object; an arbitrary or uninitialized pointer is not safe.
- Do not shallow-copy an `IntList`. Two structs containing the same owning
  pointer would create duplicate cleanup responsibility.
- A nonnull `out_value` for `get` or `remove` must not point inside the list's
  allocation.

## Core checkpoints

### 1. Initialize, validate, and destroy

Confirm the starter implementations match the documented canonical empty state. Explain why `destroy(NULL)` is a no-op and why normal callers should pass only valid list objects.

### 2. Checked access

Complete `int_list_get`.

- Reject `NULL` arguments.
- Reject an invalid list.
- Require `index < size`.
- Change `*out_value` only on success.
- Never inspect an allocated-but-unused slot.

### 3. Reserve/growth

Complete the allocator-call step in `int_list_reserve`, then explain the
provided capacity-selection scaffold.

- Return success without allocation when capacity is already sufficient.
- Use initial capacity four and geometric doubling.
- Reject element or byte counts that overflow.
- Replace the allocator wrapper's `NULL` placeholder with the currently owned
  allocation so successful growth preserves existing values.
- Change `data` and `capacity` only after success.
- Never change `size`.

The course wrapper delegates to `realloc` in normal builds and lets an
instructor test force one deterministic failure. Do not bypass it.

### 4. Append

Complete `int_list_append`.

1. Validate the list.
2. Check whether `size + 1` is representable.
3. Reserve before writing.
4. Write at the old `size`.
5. Increment `size` only after the write.

### 5. Run core tests

Core tests cover:

- canonical initialization;
- access on an empty list;
- first append;
- spare-capacity append;
- first and repeated growth;
- value preservation;
- invalid argument/range behavior;
- explicit reserve;
- overflow rejection with state preservation;
- cleanup and reset.

An instructor-only target additionally forces the real reserve path to report
allocation failure and checks that pointer, size, capacity, and values are all
unchanged.

### 6. Design three tests

Inspect the supplied tests, then complete the three generic functions in
`code/tests/test_student.c` with cases that are not direct copies. Together,
your tests must include:

- one boundary or malformed-input path not already asserted directly;
- one state-preservation or sequence property;
- one additional API-contract risk you identify and justify.

For each test, record why the case adds evidence beyond the supplied core
tests. Merely renaming or repeating a visible test does not count. If your
test initializes a list, clean it up on every return path.

## Extension checkpoints

After the core submission works:

### Insert

- Allow `index <= size`.
- Reserve first.
- Shift `[index, size)` one position right with `memmove`.
- Store the new value and then increment `size`.

### Remove

- Require `index < size`.
- Copy the removed value when `out_value != NULL`.
- Shift later elements one position left.
- Decrement `size`.
- Do not shrink in this module.

Run `test_extension`.

## Build and test

### PowerShell

From the `code` directory:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target starter -StudentTests
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target starter -Extensions
```

When Clang or GCC supports sanitizers:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target starter -Sanitize
```

The execution-policy option applies only to this child PowerShell process.

### GNU Make in Git Bash, MSYS2, WSL, Linux, or macOS

```sh
make starter-core
make starter-student-tests
make starter-extension
```

The Makefile uses POSIX shell commands and defaults to GCC. For Clang, use
`make CC=clang starter-core`. If sanitizers are unavailable locally, submit
the strongest warning/debugger evidence your approved environment supports.
Instructor CI output is an acceptable accessibility/toolchain alternative.

## Required evidence

Submit:

1. completed `int_list.c`;
2. core test transcript;
3. three passing student-authored tests with a rationale for each;
4. warning and sanitizer/debugger evidence;
5. completed evidence template, including a bounded-ingestion policy;
6. Segfault Autopsy;
7. corrected Cognitive Pause.

## Constraints

- Do not change tests merely to turn failures into passes.
- Do not read unused slots.
- Do not use a sentinel integer to report failure.
- Do not assign `realloc` directly to `list->data`.
- Do not grow by exactly one slot per append.
- Do not use live authentication logs.

## Completion criteria

Core completion requires:

- all core tests pass;
- no compiler warnings in student-controlled code;
- no detected invalid access, use-after-free, or leak in the tested path;
- written invariant and failure explanation are accurate.
