# Instructor Technical Notes — Module 1

## Canonical API decisions

The package uses a status enum rather than `bool` so students can distinguish invalid arguments, range errors, allocation failure, and overflow. No integer sentinel represents failure.

The struct is intentionally visible in Module 1 because students must model `data`, `size`, and `capacity`. Later courses may prefer an opaque type.

Core:

- `int_list_init`
- `int_list_destroy`
- `int_list_is_valid`
- `int_list_reserve`
- `int_list_get`
- `int_list_append`

Extension:

- `int_list_insert`
- `int_list_remove`

## Contract boundaries

- `int_list_init` is for an uninitialized or destroyed object. Reinitializing a live object would leak and cannot be detected portably.
- `destroy(NULL)` is a no-op.
- A second destroy is safe because the first resets the canonical state.
- `get` requires a nonnull output pointer, changes it only on success, and
  forbids that pointer from overlapping the list allocation.
- `remove` permits a null output pointer to discard the removed integer; a
  nonnull output pointer must not overlap the list allocation.
- `reserve` never shrinks.
- Removal never shrinks in this module.
- Shallow copying `IntList second = first;` is prohibited because it creates duplicate apparent ownership.
- External aliases into `data` are invalid across any call that may grow.

## What `int_list_is_valid` can prove

The helper checks only observable shape:

- nonnull list pointer;
- `size <= capacity`;
- zero-capacity/null-pointer correspondence.

It cannot prove:

- the allocation is actually large enough;
- the pointer is live;
- ownership is unique;
- logical slots contain initialized values.

Call it a shape validator, not a complete invariant proof.

## Growth details

The solution uses:

- initial capacity `4`;
- geometric doubling;
- `SIZE_MAX / sizeof *data` as maximum representable element capacity;
- checked `size + 1`;
- temporary `realloc` result;
- commit after success.

Tests assert content and invariant, not a particular address or a requirement that `realloc` move.

When compiled with `INT_LIST_TESTING`, the course allocator wrapper exposes
`int_list_test_fail_next_allocation`. The separate instructor test uses it to
force exactly one real reserve request to fail, then verifies unchanged
pointer, size, capacity, and values. Production and normal student builds do
not define the macro.

## Insert/remove details

The solution uses `memmove`, not `memcpy`, because shifted regions overlap.

Insertion:

- accepts `index <= size`;
- reserves before shifting;
- shifts `(size - index)` integers right;
- stores, then increments size.

Removal:

- requires `index < size`;
- copies the removed value before shifting when requested;
- shifts `(size - index - 1)` integers left;
- decrements size;
- does not shrink.

## Toolchain guidance

Preferred warnings for GCC/Clang:

```text
-std=c11 -Wall -Wextra -Wpedantic -Wconversion -Wshadow -g
```

Sanitizers where supported:

```text
-fsanitize=address,undefined -fno-omit-frame-pointer
```

MSVC Developer PowerShell:

```text
/nologo /std:c11 /W4 /Zi
```

Do not make sanitizer availability a grading requirement. Provide instructor CI or a debugger/invariant-check alternative.

## Autopsy isolation

`code/autopsy/faulty_append.c` is a self-contained separate executable. It
does not link the reference solution and must never be linked into normal
tests or submitted as library code. Its intentional invalid write may appear
as:

- AddressSanitizer error;
- access violation on Windows;
- segmentation fault on other platforms;
- or silent undefined behavior without instrumentation.

The learning target is the earliest invalid state, not obtaining a dramatic crash.

## Package validation checklist

- [ ] Solution compiles with strong warnings.
- [ ] Core tests pass.
- [ ] Extension tests pass.
- [ ] Forced allocation-failure test passes.
- [ ] Sanitizer run is clean for the solution.
- [ ] Autopsy builds separately.
- [ ] Autopsy is not registered as a passing normal test.
- [ ] Student starter compiles before TODO completion.
- [ ] Every diagram has a text equivalent.
- [ ] Student and instructor API names match.
- [ ] Lab, tests, and rubric agree on core versus extension scope.
- [ ] Five release archives contain only their documented student-facing
      stage and no solution or answer key.
