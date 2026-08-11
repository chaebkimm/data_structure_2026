# Student Code Package

You will complete exactly three numbered `TODO` clusters:

1. in `starter/linked_list.c`, complete bounded front insertion,
   first-match deletion, and destruction;
2. in `starter/dsu.c`, complete make-set initialization and iterative
   two-pass find; and
3. in `starter/dsu.c`, complete union by component size, including the
   deterministic tie rule and already-together result.

You will also complete exactly three test categories in
`tests/test_student.c`. Do not change public headers, supplied support, or
supplied core tests.

## Linked-list contract

The maximum supported limit is 16 nodes. Each initialized list chooses its
own limit from 0 through 16.

- An initialized empty list has size 0, a null head, and its configured
  limit.
- A valid nonempty list owns exactly `size` reachable nodes.
- The final following link is null.
- Front insertion succeeds completely or preserves the prior list.
- A full configured limit and a failed allocation are reported without
  changing any list field or node.
- Deletion removes only the first matching value.
- Save every still-needed following link before freeing a node.
- Destruction releases every owned node and restores the exact all-zero
  state: null head, size 0, and limit 0.

The full validator is a separate linear-time diagnostic. It is not part of
the constant-time front-insertion measurement.

The required example has configured limit 4. Its three live nodes leave one
spare slot so a forced allocation failure reaches allocation rather than the
full-limit boundary:

```text
before: 17 -> 23 -> 31 -> NULL
delete: 23
after:  17 -> 31 -> NULL
```

## Union-Find contract

The DSU supports at most 16 dense IDs. Dense means that an instance with
eight elements uses IDs 0 through 7 without gaps.

Make-set gives each ID:

```text
parent[id] = id
component_size[id] = 1
```

A root is an ID whose parent is itself. Only roots store positive component
sizes; a nonroot stores zero. Find uses no recursion:

1. follow parent entries to a valid root; then
2. walk the same path again and redirect its members to that root.

Union attaches the smaller component below the larger. If sizes are equal,
the smaller root ID wins. A same-component union reports success with no
merge; its successful searches may still compress parent paths.

Map `A=0` through `H=7` and apply:

```text
A-B, C-D, A-C, E-F, G-H, E-G, A-E
```

Required state:

```text
parent          [A, A, A, C, A, E, E, G]
component_size  [8, 0, 0, 0, 0, 0, 0, 0]
components      1
```

Finding H compresses `H -> G -> E -> A`:

```text
parent          [A, A, A, C, A, E, A, A]
component_size  [8, 0, 0, 0, 0, 0, 0, 0]
```

D-H then performs no merge, classifies the relationship as
cycle-producing, and compresses D to A.

## Supplied edge-list prelab

`support/undirected_edge_list.c` is complete. Every logical edge ID must have
exactly two incident records:

- reciprocal records for a non-self edge;
- two identical records for a self-loop.

Different logical IDs preserve parallel edges. The builder emits one
canonical edge per ID. The supplied `qsort` comparator compares signed
64-bit weights, endpoints, and then ID relationally. It never subtracts
weights, so extreme values do not trigger subtraction overflow.

Test this support as directed. Do not implement Kruskal selection or a
minimum spanning tree.

## Build and run

Run the public core tests from this directory:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1
```

Run your three test categories:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -StudentTests
```

Add `-Sanitize` when the selected compiler supports sanitizers.

The isolated source contains an intentional use-after-free. The ordinary
autopsy command defines `AUTOPSY_INSPECT_ONLY`, describes the defect, performs
the corrected order, and exits safely:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target autopsy
```

To compile the actual faulty branch, both explicit permission and sanitizers
are required:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target autopsy -UnsafeAutopsy -Sanitize
```

That command prints the binary path but deliberately does not run it. Do not
run the binary outside an instructor-controlled disposable environment.
Never link either autopsy mode into a core or student-test build.

GNU Make users can run:

```sh
make starter-core
make starter-student-tests
make autopsy
make autopsy-unsafe
```

`make autopsy` runs only the safe inspection branch.
`make autopsy-unsafe` adds `SANITIZER_FLAGS`, compiles the actual defect, and
prints its path without running it.

The starter is intentionally incomplete. A failed first core-test run is
expected. Fix the earliest failed requirement without weakening a test or
changing supplied interfaces.
