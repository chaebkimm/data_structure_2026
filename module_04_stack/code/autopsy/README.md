# Stack-Top Autopsy

An **autopsy** is a careful examination of a supplied defect. This program is
separate from both the starter and solution. It uses a tiny fixed array, so
changing student code cannot change its result.

A stack's **logical elements** are the positions that currently belong to the
collection. If `size` is 2, those positions are indexes 0 and 1. An **index**
is a numbered array position. The next unused position is index 2.

`faulty_delimiters.c` deliberately reads `data[size]` as the top. The file
contains one extra physical cell filled with `?`, so this particular
demonstration remains inside the array. It is still logically wrong: the top
is the latest stored character at `data[size - 1]`.

Before running:

1. Draw the array after `(` and `[` are pushed.
2. Predict the correct and faulty top characters.
3. Predict whether the faulty validator accepts the valid text `([])`.
4. Predict the reported character index.

From the `code` directory, run:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target autopsy
```

Then complete `student/stack_autopsy.md`. Do not repair the supplied program
until your prediction and the observed output are both recorded.
