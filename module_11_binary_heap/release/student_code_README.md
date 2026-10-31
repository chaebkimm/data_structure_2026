# Build the Module 10 Lab

The tests include [student/lab.c](../student/lab.c) once and supply `main`.
The source is complete. Add three original groups to
`tests/test_lab_student.c` using the [lab](../student/lab.md).

From the extracted root:

```sh
make -C code lab-compile
make -C code core
make -C code student-tests
```

For supported compilers, use a separate sanitizer build:

```sh
make -C code core student-tests BUILD_DIR=build-sanitize CFLAGS='-std=c11 -Wall -Wextra -Wpedantic -Wconversion -Wshadow -g -fsanitize=address,undefined -fno-omit-frame-pointer'
```

PowerShell: run `./code/build.ps1`, `./code/build.ps1 -StudentTests`, or
`./code/build.ps1 -Sanitize`. `-CompileOnly` builds without running the
selected test driver. The script selects Clang, GCC, or Microsoft C.

The core driver tests integer min/max order, construction and mode changes,
duplicates, one-child and singleton boundaries, dual-heap inverse maps and
both repair directions, the chapter examples, closed endpoints, repeated
epochs, exhaustion, and 1,000 deterministic checks against a simple time
scan. The student driver has a passing smoke test, not three completed
original groups.

Use only valid caller states: at most ten integers; nonempty root removal;
all ten IDs with one through five nonnegative, chronological, strictly
separated closed intervals each. The source does not validate those
conditions. After an exhausted search returns `-1`, do not read the
one-past-last epoch. A fresh search resets epochs.

The source uses six `()` function definitions that may produce prototype
warnings under C11. Its bytes are preserved. No allocation, arrival
sequence, stable FIFO tie, status, or comparison counter is provided here.
