# Instructor Technical Notes — Module 1

## Canonical representation

Module 1 uses a plain fixed array and two integer counts:

```c
int array[10];
int size = 0;
int array_capacity = 10;
```

The normal teaching capacity is ten. Size counts active items, which occupy
the gapless prefix `[0, size)`. The capacity never changes during an
operation. Full append and insertion requests fail without changing size or
any array element.

No wrapper struct is needed. The public header keeps the existing
`int_list.h` filename, and both implementations remain named `int_list.c`.

## Textbook and lab bridge

The English and Korean textbooks retain the original chapter and add
**Full C Code Explanation** as an optional eleven-topic reference. Its
complete program is copied into `code/lecture/simplified_array_list.c` and
can be run with `make lecture` or `build.ps1 -Target lecture`. It uses the
chapter's five-item initial list and prints the read value, search result,
and final five-item list. Keep this example at Stage D or later.

The textbook's operations run together in `main`; the lab makes reusable
functions with array access, copied integer inputs, and returned counts.
In particular, the textbook loop represents an unsuccessful search with
`index == size`, while `int_list_find` returns `-1`. Both preserve the same
first-match behavior, but neither absence result may be used to read an
item. Teach the lab's return contract explicitly rather than changing the
textbook's completed example.

The lab also checks metadata supplied by callers, whereas the complete
textbook program establishes valid counts itself. Smaller three-item inquiry
and test fixtures remain useful for applying the same invariant. The
student notes provide an optional appendix topic map; the lab separately
explains the required function and test-body syntax. Do not require students
to finish every reference topic before attempting the lab.

## Public API

```c
int int_list_valid_index(int size, int capacity, int index);
int int_list_append(int array[], int size, int capacity, int value);
int int_list_insert(
    int array[], int size, int capacity, int index, int value
);
int int_list_remove(int array[], int size, int capacity, int index);
int int_list_find(const int array[], int size, int capacity, int value);
```

All five functions support the core operations. Checked read and update use
`int_list_valid_index` followed by direct bracket access:

```c
if (int_list_valid_index(size, array_capacity, pos)) {
    int data = array[pos];
    array[pos] = 500;
}
```

The mutators return the resulting size. The caller must retain it:

```c
size = int_list_append(array, size, array_capacity, 400);
size = int_list_insert(array, size, array_capacity, 1, 600);
size = int_list_remove(array, size, array_capacity, 1);
```

## Metadata and array contract

Valid metadata satisfies `0 <= size && size <= capacity`. This includes the
empty zero-capacity case, although ordinary class examples use capacity ten.
The caller supplies a live array with at least `capacity` actual positions.
The helpers cannot infer the physical extent of a C array argument.

Negative size, negative capacity, or size greater than capacity is invalid
metadata. On such input:

- `int_list_valid_index` returns `0`;
- `int_list_find` returns `-1`; and
- append, insert, and remove return the original size and change no array
  element.

No status enum is used. The result is either a validity flag, an index, or a
size count. In particular, `-1` is a search result, not a valid array index.

## Operation contracts

### Checked read and update

`int_list_valid_index` returns `1` exactly when metadata is valid and
`0 <= index && index < size`; otherwise it returns `0`.

A check against capacity alone is insufficient: positions at or beyond size
are not active list items. Read and update do not change size or capacity.
An invalid position must never be used in a bracket access.

### Linear first-match search

`int_list_find` scans indexes zero through `size - 1` in order. It returns
the first index whose value equals the target, or `-1` if no active value
matches. Duplicate values are allowed; the earliest active match wins.

The function does not read inactive positions and does not change the array.
The `const` array parameter expresses that read-only intent.

### Append

Append requires valid metadata and `size < capacity`. It writes the value at
`array[size]` and returns `size + 1`. It does not move existing active items.

A full list returns its original size without writing. In particular, the
test must be strict: `size < capacity`, not `size <= capacity`.

### Insert

Insertion requires valid metadata, `0 <= index && index <= size`, and
`size < capacity`. The end position `index == size` is allowed.

Validate every condition before moving an element. Shift right from back to
front, write the new item at the selected index, and return `size + 1`.
One suitable loop starts at `size` and continues while `i > index`, copying
`array[i - 1]` into `array[i]`.

Moving front to back overwrites values that still need to be copied. Full or
invalid requests must preserve the entire backing array, including inactive
positions.

### Remove

Removal requires valid metadata and `0 <= index && index < size`. Shift all
later active items left from front to back and return `size - 1`.

Clearing the former last slot is not required. That position lies outside
the new active prefix, so any retained value is not another list item.
Removing the last item requires no shifts.

## Complexity

Let `n` be the number of active items. The teaching capacity is fixed at ten;
the table describes how the work depends on the active count.

| Operation | Work | Additional array storage |
|---|---:|---:|
| checked indexed read/update | `O(1)` | `O(1)` |
| first-match search | `O(n)` worst case | `O(1)` |
| append | `O(1)` | `O(1)` |
| insert at index `i` | `O(n - i)` shifts; `O(n)` worst case | `O(1)` |
| remove at index `i` | `O(n - i - 1)` shifts; `O(n)` worst case | `O(1)` |
| reject a full append/insert | `O(1)` | `O(1)` |

Index and capacity checks happen before any mutation. They do not depend on
the number of active values.

## Core versus extension

Read, update, find, append, insert, and remove are all core. The extension
suite adds only boundary and sequence evidence for those same operations,
such as:

- duplicate-value first-match selection;
- negative or inconsistent metadata;
- empty and full states;
- insertion at the front and at the end;
- removal followed by an append into the reopened position; and
- repeated operations that must preserve order and the active-prefix rule.

Do not present insert or remove as optional implementation work.

## Toolchain guidance

Preferred GCC/Clang warnings:

```text
-std=c11 -Wall -Wextra -Wpedantic -Wconversion -Wshadow -g
```

Runtime checks where supported:

```text
-fsanitize=address,undefined -fno-omit-frame-pointer
```

Microsoft C uses `/nologo /std:c11 /W4 /Zi`. Provide instructor CI or a
debugger/invariant-check alternative when a local sanitizer is unavailable.

## Bounds and Invariant Autopsy

`code/autopsy/faulty_append.c` is a standalone demonstration. It uses an
eleven-position backing array, a usable capacity of ten, and guard `-999` in
physical slot ten. The deliberately wrong `size <= capacity` test permits a
full append to overwrite that guard with `1100` and report size eleven.

The write remains inside the demonstration's actual backing array. The
observed failure is the list contract: the guard changed and
`size > capacity`. A sanitizer need not report a memory violation, and a
crash is neither required nor expected.

The correct repair is a strict capacity check before writing. The extra
guard position is an observation device, not added usable capacity or a
production repair. Keep the autopsy separate from the normal test suite.

## Package validation checklist

- [ ] Solution compiles with strong warnings.
- [ ] Core tests cover every required operation and pass.
- [ ] Extension tests add edge and sequence cases and pass.
- [ ] Runtime checks are clean for the reference implementation.
- [ ] The guarded autopsy builds and prints its expected invariant failure.
- [ ] The starter compiles before TODO completion.
- [ ] The lecture copy matches the complete textbook program and expected output.
- [ ] Stage D includes both textbook languages and their optional C reference.
- [ ] No obsolete test target is mentioned in release build files.
- [ ] Every diagram has a text equivalent.
- [ ] Student and instructor API names match the header.
- [ ] Lab, tests, and the 100-point rubric agree on core scope.
- [ ] Five staged releases contain only their documented student materials,
      with no solution or answer key.
