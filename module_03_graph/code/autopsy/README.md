# Ghost-Connection Autopsy

`faulty_ghost_connection.c` is a standalone, intentionally incorrect
training fixture. It demonstrates why inactive rows and columns must remain
zero in a fixed adjacency matrix.

Before running it:

1. Read the supplied source without running it.
2. Complete and preserve the predictions in `student/matrix_autopsy.md`.
3. Run the program and record its actual output beside the prediction.
4. Only then identify the first broken invariant and propose a repair.

From the parent `code` directory, run:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target autopsy
```

Or run `make autopsy`.

All indexes in this fixture are within the allocated matrix. The failure is
logical, not an out-of-bounds access. A crash is not the intended evidence.
