# Lab — A Checked List in Ten Array Slots

## Purpose and scope

Use an ordinary C integer array, a current item count, and a fixed capacity.
Read and update by index, find the first matching value, append, insert, and
delete. Every operation is core.

The values are invented event codes. No live systems or sensitive data are
used. The lab requires only arrays, integer variables, conditions, loops,
and functions.

## Two 90-minute meetings

| Meeting | Activity | Minutes |
|---|---|---:|
| A — Conceptual stages | Initial inquiry, representation reveal, pause and correction, investigation, and exit ticket | 90 |
| B — Stage E lab | Retrieve the model; implement all core operations; complete tests, bounds autopsy, and submission evidence | 90 |
| **Total** | | **180** |

Stage D's textbook and notes become available after Meeting A's investigation
and exit ticket. Stage E's code and lab materials are released for Meeting B.
Keep either Stage D textbook available: its **Full C Code Explanation** is
optional help for a specific symbol or operation. Use the topic map in
Stage D's `notes.md` to find a starting point. Its practice questions are
not another required submission.

## Files

You receive:

- `code/include/int_list.h`
- `code/starter/int_list.c`
- `code/tests/test_core.c`
- `code/tests/test_extension.c`
- `code/tests/test_student.c`
- `code/autopsy/faulty_append.c`
- `code/build.ps1`
- `code/Makefile`

Edit only `code/starter/int_list.c` and `code/tests/test_student.c`. Do not
change the public header or supplied tests unless the instructor authorizes
it.

## Representation and API

To test the chapter's five-item starting state, use this initialized lab
fixture:

```c
int array[10] = {100, 200, 300, 400, 500};
int size = 5;
int capacity = 10;
```

The initializer gives the remaining slots zero values, but those slots are
not list items. `size`, not a special integer, determines list membership.

The header declares these five functions:

```c
int int_list_valid_index(int size, int capacity, int index);
int int_list_append(int array[], int size, int capacity, int value);
int int_list_insert(
    int array[], int size, int capacity, int index, int value
);
int int_list_remove(int array[], int size, int capacity, int index);
int int_list_find(
    const int array[], int size, int capacity, int value
);
```

`const` tells you that the search function does not change its array
parameter. Reading and updating remain direct `array[index]` operations after
a successful `int_list_valid_index` check.

### Required contract

- Valid counts satisfy `0 <= size <= capacity` and `capacity >= 0`.
- Current items occupy indexes 0 through `size - 1` in list order.
- An array argument must name an existing array with at least `capacity`
  slots. The functions cannot discover its declared length. Never claim a
  capacity larger than the real array.
- Capacity is fixed for each list. The main example uses 10; an edge test may
  use a smaller fixed usable bound, including zero.
- Append, insertion, and removal return the resulting count on success.
  Rejection returns the original count and leaves the entire array unchanged.
- The caller saves the returned count in `size`.
- Removal does not need to clear inactive tail values.
- All integer data values are valid, including zero, negative numbers, and
  duplicates.

## Reading the supplied C scaffold

The textbook puts its operations inside `main`; the lab gives each operation
a function that tests can call with different arrays and counts. The lab
name `capacity` has the same role as the textbook's `array_capacity`.

| Form in the lab | How to read it |
|---|---|
| `#include "int_list.h"` | Include this project's declarations so the compiler knows the function names and inputs. The quotation marks identify a project header. |
| `int int_list_append(...)` | Define a function that sends an integer result back to its caller. The names inside the parentheses are its parameters. |
| `int array[]` in a parameter list | Receive access to the caller's existing array. No new array is created or copied here, and the brackets do not tell the function its length. |
| `int size, int capacity` | Receive separate integer inputs. Each parameter is a local copy of the supplied integer value. |
| `const int array[]` | Receive array access that does not permit changing an element through this parameter. Search only reads. |
| `return size;` | End this function call and send the current local count back. It does not print the count or update the caller by itself. |
| `size = int_list_append(array, size, capacity, 600);` | Call with the current values, wait for the returned count, then store that count in the caller's `size`. Writes through the array parameter affect the caller's array. |
| `!condition` | Logical NOT: produce 1 when the condition is zero, or 0 when it is nonzero. The supplied `if (!int_list_valid_metadata(...))` rejects invalid counts. |
| `static int int_list_valid_metadata(...)` | A supplied helper whose name is private to this source file. You do not need to rewrite it. |
| `(void)index;` in a TODO body | A placeholder that tells the compiler the unused parameter is intentional. Replace it as you implement the body; it does not initialize or check the index. |

Each function has its own result convention. An index check returns `1` or
`0`; a mutation returns a count. The textbook's search loop finishes with
`index == size` when no item matches. The lab's `int_list_find` returns
`-1` for that case (and for invalid counts). Neither result is a valid index
to use in brackets.

In `tests/test_student.c`, edit the three marked test bodies. `bool` comes
from `<stdbool.h>` and holds a true/false result; return `true` only when
your test's claim holds, and `false` when it fails. You can use ordinary
`if` checks and return statements already covered in the chapter. Each
supplied `static bool test_student_case_1(void)` defines a private function
with no input parameters that reports whether its test passed.

The rest of that file is provided test-running code. Its `typedef` and
`TestFunction` let it call each named test; its counters and print statements
report the results. You may leave that code as supplied. If you inspect it,
`unsigned int` counts nonnegative values, `0U` and `1U` are unsigned integer
constants, `+=` adds and stores, `%u` displays such a count, and
`condition ? 0 : 1` selects the program's exit code. `(void)printf(...)`
discards the library function's return value after displaying text. These
details do not add implementation tasks to the lab.

## Core checkpoints

Edit the marked `TODO(core)` regions. The helper that checks size and capacity
is supplied. You do not need to rewrite it.

### 1. Check an index, then read or update

Complete `int_list_valid_index`. Return 1 only when the counts are valid and
`0 <= index < size`; otherwise return 0.

Use that check before reading or updating `array[index]` in a test. Reading
and updating do not change the count. An index inside the physical array can
still be outside the current list.

### 2. Append when space remains

Complete `int_list_append`.

- Reject invalid counts or a full list before any write.
- On success, write at the old `size` and return `size + 1`.
- On rejection, return the original `size` without changing an array element.

The caller uses the result like this:

```c
size = int_list_append(array, size, capacity, 600);
```

For an addition, an unchanged returned count means the request was rejected.

### 3. Insert at a chosen position

Complete `int_list_insert`.

- Permit indexes from 0 through `size`, including both endpoints.
- Require room for one more item.
- Complete every check before moving any values.
- Shift from the final current item toward the target index.
- Store the new value and return the increased count.

Inserting at `size` has the same list effect as appending.

### 4. Remove and compact

Complete `int_list_remove`.

- Require a current item index: `0 <= index < size`.
- Move each later current item one position toward index 0.
- Return the decreased count.
- Leave the inactive tail alone. It is no longer part of the list.

A rejected removal returns the original count and changes no array element.

### 5. Find the first matching value

Complete `int_list_find`.

- Scan current indexes from 0 upward.
- Return as soon as the first matching item is found.
- Return `-1` when the value is absent or the counts are invalid.
- Do not read unused slots or change the array.

The result is an index. A stored value of `-1` is not the same thing as the
search result `-1`.

### 6. Design three tests

Add three cases in `code/tests/test_student.c` that are not direct copies of
the supplied tests:

- one boundary or invalid-count/index case;
- one rejected-state or operation-sequence case; and
- one additional contract case, such as first-match behavior or shift order.

For each case, state the new claim it checks. Use initialized arrays when
comparing all slots before and after a rejection. Tests must respect the
actual array-length requirement.

## Optional additional edge cases

After the required core and student tests pass, you may run the extension
tests. They exercise additional boundaries and operation sequences using the
same five functions. Extension output is not part of the required submission;
insertion and removal are already required by the core tests.

## Build and test

From the `code` directory in PowerShell:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target starter -StudentTests
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target starter -Extensions
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target autopsy
```

When the compiler supports sanitizers, add `-Sanitize` to a test command. A
sanitizer checks for some invalid accesses while the program runs. The
execution-policy option applies only to this child PowerShell process.

In Git Bash, MSYS2, WSL, Linux, or macOS:

```sh
make starter-core
make starter-student-tests
make starter-extension
make autopsy
```

The Makefile defaults to GCC. Use `make CC=clang starter-core` for Clang.
If a local tool is unavailable, use approved debugger or instructor-CI
evidence. CI means another computer runs the submitted tests.

## Required submission

1. completed `int_list.c` with all five core functions;
2. a passing core-test transcript;
3. three passing student-authored tests with a rationale for each;
4. warning-enabled and approved diagnostic evidence;
5. completed evidence record;
6. Bounds and Invariant Autopsy;
7. corrected Cognitive Pause.

## Constraints and completion

- Do not change tests merely to turn failures into passes.
- Do not read unused slots as current list items.
- Do not use an integer value as an unused-slot marker.
- Do not write at index `capacity` or change the capacity to accept a request.
- Reject before writing or shifting when counts, index, or space are invalid.
- Keep the original array and count unchanged on rejection.

Completion means every core operation passes the supplied and student tests,
student-controlled code has no compiler warnings, and the written explanation
correctly distinguishes size, capacity, and current item indexes.
