# Bounds/Invariant Autopsy

`faulty_append.c` deliberately uses `size <= capacity` where a successful
append requires `size < capacity`.

The observation fixture has `int array[11]`, but only the first ten slots
belong to the list. Its usable capacity is 10. Slot 10 starts with the guard
value `-999` and is not an active list element.

Before running it:

1. Predict whether the faulty condition accepts a list with size 10.
2. Identify the array index written by the attempted append of `1100`.
3. Predict the new size and guard value.
4. Identify the earliest point when the list crosses its usable boundary.

From the parent `code` directory, run:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target autopsy
```

Or run:

```sh
make autopsy
```

The program prints size 11, capacity 10, and a guard overwritten with 1100.
Every access stays inside the actual 11-element array, so this demonstration
has no intentional out-of-bounds access or other undefined behavior.

The extra physical slot is an observation fixture, not a production fix.
With an ordinary ten-element array, writing index 10 would be out of bounds.
The correct repair is to reject a full append before writing anything.

Use `student/segfault_autopsy.md` to record the trigger, first invalid list
state, and observed symptom. Its filename is historical; this exercise does
not require a crash.
