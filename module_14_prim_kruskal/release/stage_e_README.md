# Stage E - Prim and Kruskal Lab

This archive is self-contained. It includes no solution or instructor file
and does not depend on an earlier module directory.

## Work sequence

1. Read `student/lab.md` and preserve predictions.
2. Build and run the visible starter core tests.
3. Complete the three marked implementation clusters in
   `code/starter/prim.c` and `code/starter/kruskal.c`.
4. Add the three required categories in `code/tests/test_student.c`.
5. Record results in `student/evidence_template.md`.
6. Run the bounded cycle autopsy and complete
   `student/mst_cycle_autopsy.md`.
7. Apply `student/rubric.md`.

PowerShell:

```powershell
Set-Location code
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -StudentTests
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target autopsy
```

GNU Make:

```text
make starter-core
make starter-student-tests
make autopsy
```

## Required input behavior

- The graph is weighted and undirected.
- Vertex IDs are **dense**, meaning they have no gaps from 0, and are bounded
  by 16 vertices.
- Parallel edges remain distinct by logical edge ID.
- Self-loops are valid input but are never selected.
- Negative weights are valid.
- Invalid endpoints are rejected before indexing.
- The supplied total helper computes the mathematical sum independently of
  selection order, permits cancellation, and publishes only a final value
  that fits `int64_t`, C's signed 64-bit whole-number type.
- A disconnected input produces a minimum spanning forest.

The canonical connected graph produces total weight 10 with four selected
edges. Prim and Kruskal agree on the total; they need not publish edges in
the same order.

The safe autopsy uses the triangle A-B weight 1, B-C weight 2, and A-C
weight 3. Comparing raw endpoints wrongly accepts all three edges, creates a
cycle, and reports total 6. Comparing Disjoint-Set Union representatives
skips A-C and reports total 3.

The initial inquiry may stop once every site has been reached. Full Kruskal
does not use that shortcut: it examines every logical edge and records every
later acceptance or rejection in its decision ledger.
