# Module 13 Code

The complete [lab source](../student/lab.c) contains first-match linear/binary search and stable insertion/merge sorting. Read its caller contracts in the [lab](../student/lab.md). Compile a driver or test file only; it includes `lab.c`.

From the module root run `make -C code` for core oracle tests, student tests, and the canonical demo. Override `CC` and `CFLAGS` when needed. For sanitizer checks add `-fsanitize=address,undefined -fno-omit-frame-pointer` to the normal flags. The supplied tests compare results with an independent first-match scan and C library `qsort` using a non-overflowing comparator. They also check active-range boundaries and repeated calls. Integer output tests do not prove stability; use the tagged tie trace and exact source comparison from the textbook.

PowerShell users can run `powershell -File ./build.ps1`; choose `-Target core`, `-Target student`, or `-Target demo`, and add `-Sanitize` where supported.
