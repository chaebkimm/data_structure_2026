# Instructor Technical Notes - Module 13

## Fixed scope

This module contains two bounded implementation clusters and one supplied
forward bridge:

1. a standalone owning singly linked list;
2. a fixed-array Disjoint-Set Union (DSU);
3. a read/test-only undirected incident-record to edge-list builder.

The linked list is not a new capstone graph backend. The capstone continues
using arrays of dynamic neighbor arrays.

Students do not design a complete generic list, recursive DSU, dynamic DSU,
edge builder, comparator, or Kruskal implementation.

## Public linked-list surface

The fixed bound is:

```c
#define LINKED_LIST_MAX_NODES 16U
```

State:

```c
typedef struct LinkedNode {
    int value;
    struct LinkedNode *next;
} LinkedNode;

typedef struct {
    LinkedNode *head;
    size_t size;
    size_t limit;
} LinkedList;
```

Statuses are exactly:

| Value | Name |
|---:|---|
| 0 | `LINKED_LIST_OK` |
| 1 | `LINKED_LIST_INVALID_ARGUMENT` |
| 2 | `LINKED_LIST_OUT_OF_RANGE` |
| 3 | `LINKED_LIST_FULL` |
| 4 | `LINKED_LIST_ALLOCATION` |
| 5 | `LINKED_LIST_INVALID_STATE` |
| other | status-name fallback `"LINKED_LIST_UNKNOWN_STATUS"` |

Public operations:

```c
linked_list_init
linked_list_is_valid
linked_list_get
linked_list_push_front
linked_list_remove_first
linked_list_destroy
linked_list_status_name
```

The testing build additionally exposes one-shot allocation failure and
live-node-count hooks.

## Linked-list lifecycle

`linked_list_init` accepts an ordinary uninitialized automatic object.
After checking the receiver and limit, it writes the complete canonical
state:

```text
head=NULL
size=0
limit=requested limit
```

Do not call init on a live owning list. Portable C cannot infer hidden
ownership from arbitrary uninitialized bytes or safely release a live
chain during reinitialization. Destroy first, then initialize again.

`linked_list_destroy(NULL)` is a no-op. A normal nonnull argument must be a
valid initialized or already-destroyed list. Destroy saves each successor
before release and restores:

```text
head=NULL
size=0
limit=0
```

Repeating destroy is safe. No operation may advertise that limit survives
destruction.

## Linked-list invariant

A valid initialized list satisfies:

1. `limit<=16`;
2. `size<=limit`;
3. `(size==0)` exactly matches `(head==NULL)`;
4. starting at head reaches exactly `size` nodes;
5. the next pointer after the last counted node is `NULL`;
6. no node repeats; and
7. one list exclusively owns all reachable nodes.

For a singly linked chain, an exact-size traversal followed by the required
`NULL` detects too-short, too-long, and repeated-node cycles in `O(n)`.
The checker still cannot prove that an arbitrary nonnull pointer is live,
points to enough storage, or has unique ownership.

Shallow copying `LinkedList second=first;` is forbidden. Both objects would
appear to own the same nodes.

## Shallow checks and actual costs

Push-front uses a constant-time shallow shape check:

- nonnull receiver;
- limit at most 16;
- size at most limit;
- head/zero-size correspondence.

This preserves an `O(1)` mutation core. It relies on the public precondition
that the list already satisfies the complete invariant. The full
`linked_list_is_valid` remains available for tests and diagnostic gates.

`get` and remove-first already traverse, so they may perform complete
validation without changing their `O(n)` bound. Destroy is `O(n)`.

Do not insert a full `O(n)` validator into push and continue to call the
public operation `O(1)`.

## Push-front contract

Order:

1. validate argument and shallow shape;
2. report full when `size==limit`;
3. request exactly one node;
4. on failure, preserve head, size, limit, identities, values, and links;
5. initialize value and next;
6. commit head;
7. increment size.

The allocation hook fails the next request once. Successful allocations
increment the live counter; each internal release decrements it.

## Get and remove-first contracts

`linked_list_get` requires a nonnull separate output and `index<size`.
Every error preserves its output.

`linked_list_remove_first` requires a nonnull `out_removed`.

- first match: relink, release one node, decrement size, write true;
- no match: return `LINKED_LIST_OK`, write false, preserve topology;
- duplicates: remove only the earliest traversal match;
- error: preserve list and output.

The output must not alias storage whose lifetime the operation may end.
Normal course clients use separate local output variables.

Safe middle deletion:

```text
save successor from live victim
repair live predecessor link
release victim
decrement size
publish true
```

Course code and explanations consistently use save, relink, release, then
decrement.

## Canonical linked-list fixture

Configured limit 4:

```text
push 31 allocates P
push 23 allocates Q
push 17 allocates R
head=R
R(17)->Q(23)->P(31)->NULL
size=3
```

Remove 23:

```text
comparison order R,Q
previous=R
victim=Q
successor=P
result R(17)->P(31)->NULL
size=2
```

Destroy releases R and P and returns the live-node count to its baseline.

## Autopsy isolation

The isolated faulty operation releases Q and then evaluates `Q->next`.
That evaluation is a use-after-free. The program is bounded to three
nodes, but undefined behavior may appear as a sanitizer report, access
violation, crash, or apparently successful output.

The autopsy source:

- builds as its own executable;
- never links the starter, solution, support, or normal tests;
- is not evidence that a crash must occur;
- is not submitted as repaired library code.

The earliest invalid lifetime action, not the most dramatic symptom, is the
assessment target.

## Public DSU surface

Bounds and sentinel:

```c
#define DSU_MAX_ELEMENTS 16U
#define DSU_NO_ELEMENT ((size_t)DSU_MAX_ELEMENTS)
```

State:

```c
typedef struct {
    size_t element_count;
    size_t component_count;
    size_t parent[16];
    size_t component_size[16];
} Dsu;
```

Statuses:

| Value | Name |
|---:|---|
| 0 | `DSU_OK` |
| 1 | `DSU_INVALID_ARGUMENT` |
| 2 | `DSU_OUT_OF_RANGE` |
| 3 | `DSU_FULL` |
| 4 | `DSU_INVALID_STATE` |
| other | status-name fallback `"DSU_UNKNOWN_STATUS"` |

Public operations:

```c
dsu_init
dsu_is_valid
dsu_make_set
dsu_find
dsu_connected
dsu_union
dsu_add_connection
dsu_status_name
```

DSU owns no dynamic allocation and needs no destroy.
Every required output pointer must refer to caller-owned storage outside
the `Dsu` object.

## DSU canonical state and invariant

`dsu_init` writes:

```text
element_count=0
component_count=0
parent[0..15]=16
component_size[0..15]=0
```

A valid DSU satisfies:

1. `element_count<=16`;
2. `component_count<=element_count`;
3. both counts are zero together;
4. every active parent is below element count;
5. following active parents reaches a self-parent root within at most
   `element_count` links;
6. each root's size equals its membership count;
7. each nonroot's size is zero;
8. component count equals root count; and
9. every inactive parent is 16 with size zero.

The full validator locates a root for every active ID and counts membership.
Its generalized worst case is `O(n^2)`. It is a bounded diagnostic,
separate from normal amortized operations.

## Make-set contract

`dsu_make_set` creates exactly `new_id=element_count`.

Before commit it checks:

- nonnull DSU and output;
- valid shallow counts;
- space below 16;
- target parent is inactive sentinel 16;
- target size is zero.

On success it writes self-parent, size one, increments both counts, and
publishes the new ID. Failure preserves DSU and output.

## Iterative two-pass find

The private locate pass is read-only:

1. reject invalid shallow state;
2. reject `element>=element_count` before indexing;
3. at each step read the current parent;
4. reject a parent outside the active range before using it;
5. accept only a self-parent entry with positive root size;
6. require each traversed nonroot size to be zero;
7. stop after at most `element_count` links.

Only after a root is proved does the second pass redirect the searched path
to that root. This sequencing gives failure preservation without copying
the complete DSU.

`dsu_find` publishes its representative only after compression succeeds.

## Connected, union, and add-connection

Connected and union locate both roots before compressing either path. If
the second lookup fails, the first path therefore remains unchanged.

Union:

1. if roots match, compress both paths and publish `merged=false`;
2. otherwise require at least two components;
3. require both root sizes positive;
4. check the size sum through subtraction before addition;
5. compress both input paths;
6. choose the larger root size;
7. on a tie choose the smaller root ID;
8. make the losing root point to the winner;
9. add sizes at the winner and zero the loser;
10. decrement component count and publish true.

`dsu_add_connection` returns `created_cycle=!merged`. This equivalence
applies to an incoming undirected relationship. Do not generalize it to
directed-cycle detection.

A successful same-set union may change parent links through compression.
It does not change the represented partition, root size, or component
count.

## Canonical A-H trace

Operation order:

```text
A-B, C-D, A-C, E-F, G-H, E-G, A-E
```

Exact final pre-find state:

```text
parent:         [A,A,A,C,A,E,E,G]
component_size: [8,0,0,0,0,0,0,0]
element_count:  8
component_count: 1
```

Find H:

```text
path H->G->E->A
parent after [A,A,A,C,A,E,A,A]
```

Union D-H:

```text
D path D->C->A
H path H->A
roots A,A
merged=false
parent after [A,A,A,A,A,E,A,A]
created_cycle=true when called as an undirected relationship
```

F remains below E because neither operation searches F.

## DSU complexity boundary

For a valid state generated through the API:

- init is `O(16)`, generalized `O(n)` for capacity initialization;
- make-set is `O(1)`;
- for state generated through union by size, height and one
  pre-amortization find/union are `O(log n)`;
- a manually forged diagnostic-valid chain can still make one root walk
  `O(n)`;
- path compression plus union by size gives amortized
  `O(alpha(n))` per operation across a sequence;
- storage is `O(n)`;
- full diagnostic validation is generalized `O(n^2)` here.

`alpha` is inverse Ackermann, an extraordinarily slow-growing function.
Students interpret the long-sequence average; they do not derive it and
must not call every individual operation guaranteed constant time.

## Supplied incident graph and edge list

Bounds:

```text
vertices:         at most 16
logical edges:    at most 120
incident records: exactly two per logical edge, at most 240
```

Every dense edge ID from zero through `logical_edge_count-1` occurs exactly
twice.

- ordinary edge: reciprocal endpoints and equal weight;
- self-loop: two identical endpoint records with equal weight;
- parallel edges: distinct edge IDs, even with identical endpoints/weight;
- inactive incident slots: exact zero records.

The validator rejects endpoint, count, ID, multiplicity, reciprocal, weight,
and inactive-state defects.

The builder:

- validates first;
- creates a local canonical candidate;
- normalizes endpoints to `u<=v`;
- emits one output per dense edge ID;
- keeps parallel IDs distinct;
- commits output only on success.

The builder scans the incident records once with bounded edge-ID scratch
state. Let `A` be stored incident-record count and `E` logical-edge count;
validation and building are `O(A+E)`. Students do not implement it.

The output validator checks size, canonical endpoints, unique dense IDs,
and zero inactive records.

## Relational comparator and qsort

The public comparator orders:

1. signed `int64_t` weight;
2. endpoint `u`;
3. endpoint `v`;
4. edge ID.

Every field uses relational less-than/greater-than checks. It never returns
a numeric-field subtraction. Tests at `INT64_MIN` and `INT64_MAX` protect
this rule.

Sorting validates before calling `qsort`, so invalid input remains
unchanged. Valid sorting is `O(E log E)` comparison work.

Canonical logical edges:

```text
ID 0 A-B weight 1
ID 1 A-B weight 4
ID 2 A-C weight 3
ID 3 B-C weight 2
ID 4 C-D weight 5
```

Sorted:

```text
ID 0, ID 3, ID 2, ID 1, ID 4
```

A Kruskal preview accepts IDs 0 and 3, then identifies ID 2 as the first
cycle-producing edge. The builder and comparator are read/test work only.

## Exactly three implementation TODO clusters

1. linked push-front, first-match removal, and destruction;
2. dense make-set and iterative two-pass find;
3. union by component size.

Do not split public student scope into an unbounded list library or add
edge-builder implementation.

## Exactly three student-test categories

1. list lifecycle and preserved failure;
2. make-set, exact compression, smaller-root tie, and invalid ID;
3. repeated relationship, self-loop, component counts, connected queries,
   and trust scope.

Visible core tests should cover every public status category and canonical
fixture. Private extensions should add:

- nulls and output preservation;
- limit 0 and 16;
- head/middle/tail and repeated duplicate removal;
- first forced allocation failure and recovery;
- destroy/null/double-destroy/live-counter baseline;
- malformed list shapes where safe to construct;
- DSU empty/full/inactive sentinel corruption;
- malformed parent bound, nonroot size, root size, cycle, and count;
- compression on first and second operands;
- union size ties in both argument orders;
- same-set compression side effects;
- incident count/ID/reciprocal/self-loop/parallel/inactive corruption;
- extreme comparator fields and status-name fallbacks.

## Security and claim boundary

All scenarios use synthetic authorized records.

Memory safety and invariant preservation do not establish input truth.
Shared DSU membership means only that processed undirected relationships
place two IDs in one modeled component. It does not prove:

- authorization;
- trust or compromise;
- an actual route;
- shortest path or minimum cost;
- resilience or redundancy;
- direction-sensitive connectivity; or
- efficient support for deleted relationships.

## Five release gates

1. **Stage A:** two informal prompts only. Withhold all embargoed formal
   names, code, formulas, method, and answers.
2. **Stage B:** reveal, exactly-three-target pause, and closed vocabulary.
3. **Stage C:** matching A-I worksheets; preserve A-F before Stage D.
4. **Stage D:** 1,050–1,200-word textbook and exact-equivalent models.
5. **Stage E:** lab/evidence/rubric/autopsy, public headers, starter files,
   supplied support, core/student tests, and student builds.

Stage E excludes instructor files, solution sources, private extension
tests, earlier stages, generated binaries, live data, capstone backend
migration, and normal linking of the faulty autopsy.

## Accessibility

- Standard and linear prompts use identical IDs, numbers, operation order,
  questions, and scoring.
- Every pointer or forest diagram has a table and exact linear equivalent.
- Do not rely on color, arrow shape, drawing quality, or spatial layout.
- Read arrays in explicit A-through-H order.
- Accept typed, spoken, tabular, or tactile-equivalent state descriptions.
- Provide extended-time or asynchronous pause using the same three targets.
- Sanitizer availability is not graded; accept debugger or supplied trace
  evidence.

## Instructor audit

- [ ] Destroy is all-zero, including `limit=0`.
- [ ] Init does not require a pre-zeroed automatic object and is never used
  to overwrite a live owning list.
- [ ] Absent removal is OK/false and preserves topology.
- [ ] Push's claimed `O(1)` excludes full validation.
- [ ] Complete list validation is `O(n)`.
- [ ] External DSU IDs are checked before indexing.
- [ ] Both DSU paths are located before either is compressed.
- [ ] Smaller root ID wins equal sizes.
- [ ] Pre-find, H-find, and D-H arrays are exact.
- [ ] Same-set union may compress but does not merge.
- [ ] DSU validator cost is not hidden in the amortized claim.
- [ ] Edge IDs are dense and occur exactly twice.
- [ ] Self-loop records are identical; parallel IDs survive.
- [ ] Comparator is relational at signed extremes.
- [ ] Textbook remains within 1,050–1,200 words.
- [ ] Pause has exactly three target headings.
- [ ] Stage A passes the embargo scan.
- [ ] Standard/linear facts, IDs, questions, and points match.
- [ ] Trust and deletion limitations are explicit.
