# Module 10 C Lab

The required source is [student/lab.c](../student/lab.c). It is complete and
has no `main`. The tests include it once, then supply a driver. Do not also
compile the source separately into the same executable.

The first part stores at most ten integers in `heap[10]`. `init_heap()`
selects minimum order; `is_min_heap = 0` selects maximum order. Rebuild with
`heapify()` after changing the mode of a nonempty heap. `add` appends and
repairs upward. `remove_root` replaces the root and repairs downward. The
caller must prevent adding when `size == 10` and removing when `size == 0`.
There are no allocation, status, arrival-sequence, or comparison-counter
contracts in this source.

The second part stores the ten IDs in each of two fixed heaps.
`max_on_heap` selects the latest current starting time; `min_off_heap`
selects the earliest current ending time. `epoch[id]` chooses an interval.
The swaps update both the heap arrays and their inverse position maps.
`_reheapify` repairs the position of an ID whose key changed.

`all_on_time()` finds the earliest common time in ten sequences of closed
intervals. Supply all ten IDs with one through five intervals each. Use
nonnegative times, `on <= off`, and strictly separated chronological
intervals (`previous off < next on`). Equality between the maximum on time
and minimum off time counts as a common time. The function resets epochs,
advances the ID with the earliest current off time, and returns `-1` if that
ID has no interval left. After failure its exhausted epoch is one-past-last;
do not read that interval. A fresh `all_on_time()` call resets all epochs.

## Build the current lab

From the module directory:

```sh
make -C code lab-compile
make -C code core
make -C code student-tests
```

`make -C code` runs both test drivers. Override `CC`, `CFLAGS`, `LAB_DIR`, or
`BUILD_DIR` when needed. For runtime memory and undefined-behavior checks:

```sh
make -C code core student-tests BUILD_DIR=build-sanitize CFLAGS='-std=c11 -Wall -Wextra -Wpedantic -Wconversion -Wshadow -g -fsanitize=address,undefined -fno-omit-frame-pointer'
```

PowerShell users can run:

```powershell
./code/build.ps1
./code/build.ps1 -StudentTests
./code/build.ps1 -Sanitize
```

The script chooses Clang, GCC, or Microsoft C from `PATH`. `-CompileOnly`
builds the chosen test driver without running it. Sanitizer builds use a
separate `build-sanitize` directory.

The supplied core driver checks integer min/max order, duplicates,
bottom-up construction, mode changes, single-left-child and singleton
cases, inverse maps, both repair directions, the chapter examples, closed
endpoint overlap, multiple epochs, exhaustion, and 1,000 deterministic
comparisons with a simple time-scan reference. The student driver contains
a smoke test; add the three original groups requested in the
[lab](../student/lab.md). Tests use valid caller states.

The supplied C11 source uses six no-argument definitions written as `()`.
Some compilers warn that these lack prototypes. The teaching source is
preserved; do not describe a warning-enabled build as warning-free.

## Optional alert Priority Queue reference

The existing `include/`, `starter/`, `solution/`, original `test_core.c`,
`test_extension.c`, `test_student.c`, and `autopsy/` belong to the older
stable alert-record API. Its allocation, 64-record limit, statuses,
arrival sequences, checker, and counter are separate from the current lab.
The nested [scan baseline](../priority_queue_baseline/README.md) is also
optional. Build those libraries separately with their corresponding headers:

```sh
make -C code baseline-core
make -C code solution-core solution-extension
make -C code autopsy
```

The retained `starter-*` targets exercise the optional incomplete library.
PowerShell supports `-Target starter`, `-Target solution`, or
`-Target autopsy`; `-Extensions` applies to the library targets. None of
these optional library implementation tasks is a Week 10 requirement.
