# Stage E - C Lab: Linked Ownership and Disjoint Sets

## Purpose

This lab has two bounded parts:

1. complete three operations in a supplied singly linked-list
   **scaffold**, partly finished code that provides the surrounding
   structure; and
2. complete a Disjoint-Set Union (DSU) over fixed arrays.

The linked list is a standalone ownership clinic. The capstone graph keeps
its array of dynamic neighbor arrays.

## Supplied limits and state

`LINKED_LIST_MAX_NODES` and `DSU_MAX_ELEMENTS` are both 16.

The list stores:

```c
LinkedNode *head;
size_t size;
size_t limit;
```

The configured limit is 0 through 16. Destroy restores the exact all-zero
state: `head=NULL`, `size=0`, and `limit=0`.

Initialization may be the first operation on an ordinary uninitialized
local variable, called an **automatic object** in C. Do not initialize a
live owning list: C cannot discover and release that hidden ownership
portably. Destroy it first, then initialize it again.

DSU stores:

```c
size_t element_count;
size_t component_count;
size_t parent[16];
size_t component_size[16];
```

Inactive parent positions contain sentinel 16. Students do not allocate
DSU storage.

## Required failure behavior

- Validate every external ID before indexing an array.
- A failed or full push preserves the complete list. An absent removal is
  successful with `out_removed=false` and preserves every link.
- A failed DSU call preserves DSU state and every output.
- Every output pointer must point to a separate variable owned by the code
  requesting the operation, outside the list, its nodes, and the DSU.
- A same-set union is successful, writes `merged=false`, may compress the
  two searched paths, and does not change component membership or count.
- Never shallow-copy a live owning list.
- Normal builds never contain the faulty autopsy operation.

The supplied diagnostic **validators**, functions that check structure
rules, are separate from the normal operation costs. They can check bounded
visible relationships, but cannot prove an arbitrary pointer is live or
uniquely owned.

To **commit** means to make a completed state change final and visible.

## Files and builds

Read `code/README.md` before editing. Student work is limited to the three
numbered TODO clusters in the starter sources and the three numbered test
sections in `tests/test_student.c`.

PowerShell:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 -StudentTests
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 -Sanitize
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 -StudentTests -Sanitize
```

GNU Make:

```text
make starter-core
make starter-student-tests
```

Follow the sanitizer guidance in `code/README.md`. Use the warning-enabled
build when sanitizers are unavailable.

A **sanitizer** is a runtime checker for errors such as invalid memory
access. If one is unavailable, use the approved debugger or instructor
trace alternative described later.

## TODO 1 - Linked-list push, removal, and destruction

Complete the linked-list cluster.

### Push-front

1. reject an invalid argument or invalid configured limit;
2. report full when `size == limit`;
3. request one node;
4. preserve the list if allocation fails;
5. point the new node to the old head;
6. commit the new head and increment size.

### Remove first matching value

1. traverse at most the current size;
2. keep both a current node and its live predecessor;
3. when the first match is found, save its successor;
4. repair either `head` or the predecessor's link;
5. release the victim;
6. decrement size;
7. preserve the list when the value is absent.

Duplicates are valid. Remove only the first match.

### Destroy

For each node, save `next` before `free`. At completion set `head=NULL` and
set both `size=0` and `limit=0`. Passing a null list pointer is a no-op;
every other input must be initialized or already destroyed.

Canonical checkpoint:

```text
limit 4
push 31 -> P
push 23 -> Q
push 17 -> R
remove 23
result: R(17) -> P(31) -> NULL, size 2
destroy: head NULL, size 0, limit 0
```

## TODO 2 - DSU make-set and find

### Make-set

Create the next dense ID `x=element_count`.

1. reject a null DSU or an element count already at 16;
2. set `parent[x]=x`;
3. set `component_size[x]=1`;
4. increment both `element_count` and `component_count`;
5. leave inactive positions canonical.

### Iterative two-pass find

1. reject a null output and an ID outside `[0,element_count)`;
2. first follow parent entries without mutation;
3. check every parent before using it as an index;
4. stop after at most `element_count` steps and reject a malformed cycle;
5. after a valid root is known, walk the path again;
6. point each visited nonroot directly to the root;
7. commit the output only on success.

The notation `[0,element_count)` includes zero and stops just before
`element_count`.

For the canonical state, `find(H)` follows `H,G,E,A` and produces:

```text
parent: [A,A,A,C,A,E,A,A]
```

## TODO 3 - DSU union

Complete union by component size.

1. validate both external IDs before array access;
2. locate both roots using the supplied checked helper;
3. compress both searched paths only after both root searches succeed;
4. if roots match, succeed with `merged=false`;
5. otherwise attach the smaller component root below the larger;
6. for equal sizes, let the smaller root ID win;
7. write the sum only to the winning root and zero the losing root's size;
8. decrement `component_count`;
9. write `merged=true`.

The maximum count of 16 makes size addition representable.

After canonical `find(H)`, `union(D,H)` compresses D to A, reports no
merge, and produces:

```text
parent: [A,A,A,A,A,E,A,A]
```

For an incoming undirected relationship, no merge means that relationship
is cycle-producing.

## Exactly three student-authored test categories

### Test 1 - List lifecycle and failure preservation

Cover empty behavior, canonical pushes, head, middle, and tail removal,
duplicate first-match behavior, absent removal, full limit, forced
allocation failure, destruction, and return to the allocation baseline.

### Test 2 - Creation, compression, tie, and invalid IDs

Cover dense creation through H, the exact H path and post-compression
array, the smaller-root equal-size rule, inactive sentinel slots, invalid-ID
rejection before indexing, and unchanged state/output on failure.

### Test 3 - Relationship cycles and scope

Run `A-B,C-D,A-C,E-F,G-H,E-G,A-E`, verify the exact arrays and component
count, then process the repeated D-H relationship and a self-loop. Check
the first cycle result, unchanged component count, connected queries
(calls that report whether two IDs share a root), final compression, and
the warning that shared membership does not grant trust.

Each test must add a meaningful assertion not already supplied.

## Supplied edge-list pre-lab

Read and test the supplied incident-record builder; do not implement it.
Each logical undirected edge has a dense edge ID and exactly two reciprocal
records. A **self-loop**, a relationship from one endpoint back to itself,
also has two identical records. Distinct IDs preserve parallel edges.

The builder validates the complete input and emits one canonical record per
edge ID. `qsort` is C's library function for arranging array records. Its
**comparator** is the function that tells `qsort` which record comes first.
This comparator orders `int64_t`, C's signed 64-bit whole-number type,
then normalized endpoints and edge ID. An **endpoint** is one end of a
relationship; normalized endpoints place the smaller ID first. The
comparator uses relational comparisons and never subtracts.

The A-through-D fixture contains two parallel A-B edges. Supplied boundary
tests include a self-loop and `INT64_MIN`/`INT64_MAX`, the smallest and
largest `int64_t` values.

Record:

- emitted logical-edge count: _______________________________________
- sorted fixture order: _____________________________________________
- first cycle-producing sorted edge: ________________________________

This is a short Kruskal pre-lab, not another implementation assignment.

## Actual costs

Let `n` mean list nodes or active DSU IDs, as stated.

- linked push-front mutation core: `O(1)`;
- search, remove-by-value, full list validation, and destroy: `O(n)`;
- DSU storage and creating all `n` singleton sets: `O(n)`;
- find/union with compression and size rule: amortized `O(alpha(n))`.

Amortized means average work over a long operation sequence. `alpha` grows
extraordinarily slowly. Do not call the operations literally constant and
do not include a separate full diagnostic scan in this bound.

## Security and scope

All records and device relationships are synthetic. Bounds checks prevent
invalid IDs from indexing arrays. Ownership discipline prevents leaks,
dangling links, and use-after-free in valid operations.

Shared DSU membership is not authorization, trust, a route, a shortest
path, resilience, or deletion support. A correct data structure preserves
modeled state; it does not prove that the model or input is trustworthy.

## Submission

Submit:

- completed three starter TODO clusters;
- exactly three original tests;
- saved warning-enabled and available sanitizer results;
- canonical list before/after ownership diagram;
- exact DSU union, H-find, and D-H arrays;
- completed evidence record and linked-list autopsy;
- supplied edge pre-lab observations;
- corrected Cognitive Pause; and
- one DSU limitation and trust warning.
