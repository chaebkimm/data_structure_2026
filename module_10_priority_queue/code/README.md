# Chapter 10 C Package — Sorted Priority Queue

Each driver includes [the exact teaching source](../student/lab.c) once. Compile the driver alone with the student include path. No graph source, library or external module is needed. The source has no main and no required TODOs.

## Make targets

From the repository root:

```sh
make -C module_10_priority_queue/code lab-compile core student-tests comparison
```

From the module or extracted student-release root:

```sh
make -C code lab-compile core student-tests comparison
```

Default make runs core and student-tests. lab-compile builds an object only. core checks queue ordering/ties, indices/capacity, user state, canonical trace, boundaries, repeats and 10,000 schedules against an independent interval-combination oracle. student-tests supplies a smoke check; add one original regression. comparison checks the actual survey against a local-epoch linear logout scan and the independent oracle on identical logs. It claims no asymptotic speedup.

Override CC, CFLAGS, CPPFLAGS, LAB_DIR or BUILD_DIR as needed. To check warnings and runtime bounds with Clang:

```sh
make -C code CC=clang BUILD_DIR=build-sanitize CFLAGS='-std=c11 -Wall -Wextra -Wpedantic -Wconversion -Wshadow -Werror -g -fsanitize=address,undefined -fno-omit-frame-pointer' lab-compile core student-tests comparison
```

Run this form from the module/release root; from the repository root use the full module code path. A separate build directory prevents reusing unsanitized binaries. Tests restore the supplied input after fixtures.

## PowerShell

From the module or release root, with Clang, GCC/MinGW-w64 or a Visual Studio developer environment:

```powershell
./code/build.ps1 -Target lab-compile
./code/build.ps1 -Target core
./code/build.ps1 -Target student-tests
./code/build.ps1 -Target comparison
./code/build.ps1 -Target core -Sanitize
```

The default -Target lab is an alias for core. -StudentTests alone selects the student driver for compatibility. -CompileOnly builds without running; lab-compile always builds only an object. MSVC uses AddressSanitizer when requested; Clang/GCC use address and undefined-behavior sanitizers. Runtime support depends on the compiler installation. Archived starter/solution/autopsy targets are not part of this script.

## Valid experiments

Before enqueue ensure rear+1<CAPACITY; before dequeue ensure front<=rear. Initialize a strict comparator first. Slots are not reused until initialization. Use all three users and three nonempty chronological [login,logout) intervals per user, with nonnegative times and no overlap within a row. Save and restore custom logs. Do not execute invalid operations to test hypothetical rejection statuses. On exhaustion, stop or restart with survey; epoch has already advanced past the final interval while endpoint fields retain their old values.

The supplied answer is 12, with final front=7/rear=8. Live count is two, while cumulative writes are nine. Costs are O(k) insertion, O(1) removal, O(U²+AU) survey, and up to UE queue slots for cumulative insertions. The standalone release contains both textbook languages, source, presentations, worksheets, diagrams and these build/test files; instructor keys and historical materials are excluded.
