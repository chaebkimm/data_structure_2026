# Module 1 C Code

This lab uses a plain fixed-capacity array and two separate integers:

```c
int array[10];
int size = 0;
int capacity = 10;
```

The active list is `array[0]` through `array[size - 1]`. Valid metadata
satisfies `0 <= size <= capacity`. Capacity is a fixed usable bound, not an
instruction to grow the array. Smaller fixed capacities are valid too.

## Core operations

Complete the five functions in `starter/int_list.c`:

- `int_list_valid_index`: check metadata and an active index;
- `int_list_append`: place a value at the current end;
- `int_list_insert`: shift a suffix right before inserting;
- `int_list_remove`: shift a suffix left after removing; and
- `int_list_find`: return the first matching active index, or `-1`.

Read and update values directly with `array[index]` after a successful index
check. These operations, including insertion and removal, are all core work.
Extension tests add boundaries and longer sequences, not new operations.

Mutating functions return the new size. The caller must save it:

```c
size = int_list_append(array, size, capacity, 100);
size = int_list_append(array, size, capacity, 200);
size = int_list_append(array, size, capacity, 300);

if (int_list_valid_index(size, capacity, 1)) {
    array[1] = 500;
}

size = int_list_remove(array, size, capacity, 1);
size = int_list_insert(array, size, capacity, 1, 600);
/* Active values are now 100, 600, 300. */
```

An invalid or full mutation returns the original size and changes no array
element. Removal does not need to erase the inactive tail. Searches inspect
only the active prefix.

Every array argument must be a live array with at least `capacity` elements.
The functions cannot determine its actual physical extent. Pointer validation,
storage growth, and cleanup are not student tasks in this module.

## Targets

- `starter-core`: compile the scaffold and run the core tests;
- `starter-student-tests`: run three student-designed placeholders;
- `starter-extension`: run extra checks against the starter;
- `solution-core`: run the reference core tests;
- `solution-extension`: run reference boundary and sequence tests; and
- `autopsy`: build and run the memory-safe bounds/invariant demonstration.

The default target is the starter core. It intentionally fails until the
TODOs are implemented.

## PowerShell

Run from this `code` directory:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target starter -StudentTests
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target solution
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target solution -Extensions
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target autopsy
```

The process-scoped execution-policy flag does not change the user or machine
policy. Add `-Sanitize` when the installed compiler supports it. The script
searches for Clang, GCC, and then MSVC; MSVC needs a Developer PowerShell or
Command Prompt.

## GNU Make

```sh
make starter-core
make starter-student-tests
make solution-core
make solution-extension
make autopsy
```

The Makefile is intended for Git Bash, MSYS2, WSL, Linux, or macOS. It
defaults to `gcc`; override it with `make CC=clang solution-core` if needed.
The autopsy intentionally breaks a logical capacity rule, but its observation
guard keeps every memory access inside the physical array.

## Manual GCC or Clang build

```sh
mkdir -p build
cc -std=c11 -Wall -Wextra -Wpedantic -Wconversion -Wshadow -g \
  -Iinclude solution/int_list.c tests/test_core.c \
  -o build/solution_core

./build/solution_core
```

Add `-fsanitize=address,undefined -fno-omit-frame-pointer` to check memory
accesses and undefined behavior during a GCC or Clang run.

## Manual Microsoft C build

From a Developer PowerShell:

```powershell
New-Item -ItemType Directory -Force build | Out-Null
cl /nologo /std:c11 /W4 /Zi /Iinclude `
  solution\int_list.c tests\test_core.c `
  /Fe:build\solution_core.exe

.\build\solution_core.exe
```

## Expected reference output

Core:

```text
PASS checked index and metadata
PASS append and caller size update
PASS direct checked read and update
PASS find first active match
PASS insert front, middle, and end
PASS remove front, middle, and end
PASS textbook operation trace
PASS rejected mutations preserve entire array

8 core test(s), 0 failure(s)
```

The extension suite reports five passing boundary and sequence tests.
