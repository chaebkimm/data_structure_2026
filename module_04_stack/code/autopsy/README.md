# Stack-Top Autopsy

An **autopsy** examines a supplied defect. This standalone program uses the
same downward-growing character representation as `student/lab.c`, but its
intentional defect is isolated from the lab functions.

The array has ten allocated positions. With `top == 8`, only indexes 8 and
9 are active. The correct read uses `stack[top]`; the faulty function reads
`stack[top - 1]`. In this fixture that wrong index stays inside the array,
so the experiment is deterministic and memory-safe even though it reads an
inactive cell.

Before running, inspect `faulty_top.c` and record:

1. The active indexes and logical order from bottom to top.
2. The correct and faulty indexes and their predicted characters.
3. Why an allocated array position can still be outside the logical Stack.
4. Why subtracting one from an index named `top` differs from subtracting
   one from an item count such as `pos` in the evaluator.

From `code`, run `make autopsy`, or:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 -Target autopsy
```

Preserve predictions before recording output in the student autopsy sheet.
The deliberate defect is not a replacement for `peek` in the actual lab.
