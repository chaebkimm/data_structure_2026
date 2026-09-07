# Stack-Top Autopsy

An **autopsy** is a careful examination of a supplied defect. This program is
separate from both the starter and solution, so changing student code cannot
change its result.

The fixed array contains four allocated integer slots. Its current `size` is
two, so only indexes 0 and 1 are active Stack values. Indexes 2 and 3 are
allocated but inactive. Reading either inactive slot stays within the array,
but it does not read a logical Stack value.

`faulty_top.c` deliberately reads `stack[size]`. Before running:

1. Draw the array and label active and inactive slots.
2. Predict the correct top value from `stack[size - 1]`.
3. Predict the value the faulty read obtains from `stack[size]`.
4. Explain why the faulty read is memory-safe in this fixture but still breaks
   the Stack invariant.

From the `code` directory, run:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target autopsy
```

or:

```sh
make autopsy
```

Record the prediction before running the program. Do not repair the supplied
program until both the prediction and observed output have been preserved.
