# Module 11 Student Code — Indexed-Heap Dijkstra

The required implementation is the complete `../student/lab.c`, not a
starter API. Both drivers include it directly. Its own include loads
`../module_03_graph/student/lab.c` through the archive-root include path.
Keep these directories together and compile each driver alone.

Use a C11 compiler and GNU Make from this directory:

```sh
make lab-compile
make core
make student-tests
make comparison
```

Override the compiler with `make CC=clang core`. To enable runtime checks:

```sh
make CC=clang BUILD_DIR=build-sanitize CFLAGS='-std=c11 -Wall -Wextra -Wpedantic -g -fsanitize=address,undefined -fno-omit-frame-pointer' core student-tests
```

PowerShell users can run:

```powershell
.\build.ps1 -CompileOnly
.\build.ps1
.\build.ps1 -StudentTests
.\build.ps1 -Sanitize
```

The script selects an installed C compiler. The supplied source uses
empty-parameter function declarations; record compiler warnings without
modifying it to conceal them. Neither invalid input nor overflowing signed
addition is an allowed test case for this lab.

`tests/compare_lab.c` supplies BFS hop distances and linear-minimum-selection
Dijkstra on the same fixture, then checks the actual indexed-heap costs.
The comparison prints measured linear selection work; heap event totals
come from the source trace, not exported counters.

`tests/test_lab.c` checks the actual heap and shortest-distance behavior,
including inverse positions only for live entries and an independent
shortest-distance reference. Add your own focused tests in
`tests/test_lab_student.c` and submit the driver plus saved output.

Pending heap values are node IDs, priorities live in `node_dist`, and
`node_heap_pos` locates each live ID. Removed map entries are stale. Equal
priorities have no stable order. The run uses positive `int` edge costs,
leaves unreachable distances at `-1`, and records finalization in `found`.
It exposes no predecessor path, parser, status code, allocation contract,
or range guard. The optional lazy-duplicate library in the repository is
not included in this student release.
