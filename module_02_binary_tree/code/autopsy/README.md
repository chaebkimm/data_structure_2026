# Isolated Link Autopsy

`faulty_links.c` is an observation exercise. It is separate from the library
and normal tests. The program uses only a fixed local array: it never reads
or writes beyond the array's valid positions.

Before running it:

1. Draw the four array slots and every stored address.
2. Predict the three printed counts without executing the program.
3. Mark how many times each address will be encountered by `count_from`.

`count_from` uses **recursion**, meaning that a function calls itself, to
perform a **traversal**, meaning a systematic visit through linked nodes. You
trace this supplied function; you do not implement recursion in this module.

From the `code` directory—the parent of this `autopsy` directory—run:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target autopsy
```

Afterward, explain:

- why two printed quantities differ;
- which rule of the course's pure-tree model is relevant;
- why checking only the newly selected child position is insufficient; and
- what a whole-structure checker would need to remember.

Do not change the program until the prediction and observed result have both
been recorded.
