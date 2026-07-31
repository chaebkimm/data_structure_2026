# Module 13 C Package

This package returns to pointer-linked ownership, then uses two fixed arrays
to maintain changing groups.

A **linked list** stores separate nodes joined by addresses. A
**Disjoint-Set Union (DSU)** stores nonoverlapping groups and quickly reports
whether two identifiers share a group. An **invariant** is a rule that must
remain true whenever an operation finishes.

## Linked-list contract

`LinkedList` owns at most sixteen nodes. `head` points to the first node;
`NULL` means no node. A valid list obeys all of these rules:

- `size <= limit <= 16`;
- `head == NULL` exactly when `size == 0`;
- following `next` reaches exactly `size` nodes and then `NULL`;
- those nodes belong to this list and are not freed elsewhere.

`linked_list_init` may initialize an ordinary uninitialized automatic
object because it does not read old fields. Do not call it on a live list:
the function cannot portably discover that hidden ownership, so replacing a
live head would leak its nodes. Destroy the old list first.

Duplicate values are allowed. `linked_list_remove_first` removes only the
first match. An absent value returns `LINKED_LIST_OK` and `false`.

The canonical insertion trace is:

```text
push 31       31
push 23       23 -> 31
push 17       17 -> 23 -> 31
remove 23     17 -> 31
```

`push_front` checks the bound before requesting storage. It allocates and
fills a new node before changing the list, so allocation failure preserves
every old link. Deletion and destruction save `next` before releasing the
current node.

The test-only allocator hook fails exactly the next node allocation once.
The live-node counter supports deterministic leak checks.

## DSU contract

The DSU uses dense identifiers `0` through `element_count - 1`.
`dsu_make_set` creates the next identifier. Inactive `parent` slots contain
`DSU_NO_ELEMENT`, which is 16.

Each component is a parent tree:

- a **root**, the component's representative, is its own parent;
- `component_size` is positive at roots and zero at nonroots;
- a root's size equals the number of elements that reach it;
- the number of roots equals `component_count`.

`dsu_find` is iterative. Its first pass locates a valid root. Its second pass
changes every parent on that path to point directly to the root. This
shortening is **path compression**.

`dsu_union` attaches the smaller component below the larger one. Equal-size
components use the smaller root ID as the winner. This deterministic rule
makes traces reproducible. `dsu_connected`, `dsu_union`, and
`dsu_add_connection` locate both endpoint paths before either is compressed;
a malformed second path therefore cannot leave a partial change.

For IDs `0` through `7`, perform:

```text
(0,1) (2,3) (0,2) (4,5) (6,7) (4,6) (0,4)
```

The result is:

```text
parent:         0 0 0 2 0 4 4 6
component_size: 8 0 0 0 0 0 0 0
```

`find(7)` changes parents 7 and 6 to 0. A later `union(3,7)` reports no
merge and compresses 3 to 0.

`dsu_add_connection` reports a cycle when the endpoints were already in the
same component. This includes a self-loop and a repeated parallel
relationship. Shared DSU membership describes modeled connectivity; it does
not grant trust, authorization, or permission.

## Supplied edge-list pre-lab

The supplied incident graph represents each logical undirected edge with
exactly two reciprocal records. A self-loop has two identical records.
Distinct IDs preserve genuine parallel edges.

The ordinary A-through-D fixture contains:

```text
ID 0 A-B weight 1
ID 1 A-B weight 4
ID 2 A-C weight 3
ID 3 B-C weight 2
ID 4 C-D weight 5
sorted IDs: 0, 3, 2, 1, 4
```

Extension tests add a self-loop and signed `INT64_MIN`/`INT64_MAX`
boundaries.

The builder validates all records, emits one canonical `u <= v` edge per
dense ID, and commits the caller output last. The public `qsort` comparator
orders by:

1. signed 64-bit weight;
2. endpoint `u`;
3. endpoint `v`;
4. logical edge ID.

Every comparison uses `<` and `>` rather than subtraction, so
`INT64_MIN` and `INT64_MAX` cannot cause comparator arithmetic overflow.
This pre-lab builds and sorts records only; it does not select a spanning
tree.

## Errors and preserved outputs

Required output pointers are checked before work begins. Out-of-range IDs
are rejected before array indexing. Except for successful path compression,
every reported error preserves the complete receiver and caller output.

`linked_list_destroy` has no status return. `NULL` and repeated destroy are
safe; every other argument must satisfy the list invariant.

## Cost

Let `n` be list nodes, `V` active DSU elements, `A` incident records, and
`E` logical edges.

- list `push_front`: `O(1)`;
- list get, remove, validate, and destroy: `O(n)`;
- DSU make-set: `O(1)`;
- DSU find, connected, and union: amortized `O(alpha(V))`, nearly constant
  over an operation sequence;
- one DSU operation uses `O(1)` additional storage and no recursion;
- edge-list validation/build: `O(A + E)`;
- the course sorting model: `O(E log E)` comparisons and `O(1)` comparator
  work.

The complete DSU diagnostic performs bounded parent walks and is kept
separate from normal-operation cost measurements.

## Student-controlled work

The starter has exactly three numbered task clusters:

1. linked-list push, first-match deletion, and destruction;
2. make-set and iterative two-pass find; and
3. union by component size.

The student test template adds exactly three categories: list ownership,
DSU compression, and relationship/cycle reasoning. List diagnostics, DSU
helpers and wrappers, the edge pre-lab, core tests, extension tests, and
status helpers are supplied.

## Build commands

The default build uses the completed reference solution:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 -Extensions
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 -Sanitize
```

The starter compiles but its tests fail until the three clusters are
completed:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target starter
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target starter -StudentTests
```

The ordinary autopsy target is inspect-only:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target autopsy
```

`-Target autopsy -UnsafeAutopsy -Sanitize` compiles, but does not run, the
actual isolated use-after-free.

With GNU Make:

```sh
make
make solution-extension
make starter-compile
make autopsy
make autopsy-unsafe
```
