# Module 4 — Stage E: Lab and Evidence

Start with `student/lab.md`, then study and trace `student/lab.c`. This is the
program used throughout the module: a fixed character stack whose `size`
moves forward, infix-to-postfix conversion, and integer postfix evaluation.
The initial expression is `1-2*3+4`; its postfix form is `123*-4+` and its
result is `-1`.

Paths beginning with `student/` or `code/` in the lab materials are relative
to this package's root. Keep those two folders together after extraction.

From the `code` directory, run the demonstration with `make lab-demo` and the
supplied checks with `make lab-tests`. PowerShell users can run
`./build.ps1 -Target lab` and `./build.ps1 -Target lab-tests`. See
`code/README.md` for compiler setup and sanitizer options. `lab.c` has no
`main`; the demonstration and tests supply separate entry points.

Use valid expressions within the lab's documented limits. The source does
not yet validate malformed input, buffer limits, or zero divisors; identifying
those limits is part of the lab. Extend `code/tests/test_lab.c` with three
justified cases while preserving the supplied checks. The Stack-Top Autopsy
is a separate intentionally faulty program. Record a prediction before
running it.

Submit the source and evidence listed in the lab. This package includes the
current lab source, demonstration, supplied tests, and autopsy. Instructor
materials and the older caller-owned integer-stack exercise are excluded.
