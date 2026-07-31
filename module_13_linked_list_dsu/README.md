# Module 13 Teaching Package

## Linked-List Retrieval Clinic and Union-Find Bridge

This package is the Linear stage of the fifth
Linear -> Tree -> Graph spiral in **Data Structures Course 2026**. It returns
to the linked-node preview from Module 1, then uses two fixed arrays to prepare
for Kruskal's cycle checks in Module 15.

## Beginner-first rule

Students are not expected to know linked-list vocabulary, ownership rules,
Union-Find, path compression, union by component size, inverse-Ackermann
analysis, logical edge IDs, or C sorting comparators before this module. Every
student-facing technical term and symbol is explained in ordinary language
when first needed. Assessment rewards safe reasoning and reproducible
evidence, not memorized wording, drawing quality, or speed.

## Module question

> As relationships arrive one at a time, how can we determine whether two
> vertices are already connected without searching the entire graph after
> every update?

## Core learning targets

Students will be able to:

1. trace separately allocated nodes joined by one-way links;
2. state the ownership and shape rules of a bounded singly linked list;
3. add one value at the front without losing the prior first node;
4. delete the first matching node after preserving every still-needed link;
5. destroy a list without reading a node after it has been freed;
6. diagnose a bounded use-after-free defect in isolated code;
7. interpret `parent[]` and `component_size[]` as a forest of sets;
8. perform make-set, iterative two-pass find, and union by component size;
9. recognize a relationship that would join two members already in one set;
10. test an instructor-supplied undirected edge-list builder and relational
    `qsort` comparator; and
11. explain what linked-list and Union-Find results do and do not establish.

A **singly linked list** stores each value in a separately allocated node.
Each node stores one link to the following node. **Ownership** means
responsibility for eventually releasing allocated storage.

**Union-Find**, also called a **disjoint-set union** or **DSU**, maintains
groups that do not overlap. A parent array encodes small trees. Following
parent entries reaches a **representative root**, an ID whose parent is
itself. A component-size array records the number of members only at roots.

## Linked-list contract

- `LINKED_LIST_MAX_NODES` is 16.
- Initialization chooses a list-specific limit from 0 through 16.
- Every valid list satisfies `size <= limit <= 16`.
- An initialized empty list has size 0, a null head, and its configured
  limit. The canonical destroyed state is exactly all zero: null head, size
  0, and limit 0.
- A nonempty valid list has exactly `size` reachable, uniquely owned nodes.
- The final node has a null following link; valid lists contain no cycle.
- `push_front` is `O(1)`. It fails without changing the list when the
  configured limit is full or allocation fails.
- The bounded deletion removes only the first matching value. A missing value
  leaves the list unchanged.
- Deletion and destruction save a node's following link before `free`.
- Successful destruction releases every owned node and restores the exact
  all-zero destroyed state: null head, size 0, and limit 0. Destroying that
  state again is safe.
- Shallow copying a live list is prohibited because it would create two
  apparent owners of the same nodes.
- The full shape validator is an explicit `O(n)` diagnostic. It is not hidden
  inside ordinary `push_front` cost.

The canonical retrieval list has configured limit 4. Its three live nodes
leave one spare slot for the forced-allocation-failure test:

```text
17 -> 23 -> 31 -> NULL
```

Deleting the first `23` produces:

```text
17 -> 31 -> NULL
```

The list size changes from 3 to 2, and the node containing 23 is released
exactly once.

## Union-Find contract

- Dense element IDs are `size_t` values from 0 through `element_count - 1`.
- `DSU_MAX_ELEMENTS` is 16.
- Make-set initializes each active ID as its own root with component size 1.
- For every active ID, `parent[id]` is in range.
- Repeated parent steps end at a root `r` satisfying `parent[r] == r`.
- Roots store their positive component size. Every nonroot stores 0 in
  `component_size[]`.
- The sum of root sizes equals the active element count.
- The number of roots equals the component count.
- Find is iterative and uses two passes. The first pass locates a valid root;
  the second redirects the visited path to that root.
- Union attaches the smaller component below the larger component.
- When component sizes are equal, the smaller root ID wins.
- A successful merge transfers the complete size to the winning root, writes
  0 in the losing root's size slot, and decreases the component count once.
- Union within one existing component succeeds with “not merged.” It may
  compress search paths but does not change membership or component count.
- Path compression changes parent entries only. It does not change component
  sizes, membership, or the number of components.
- Every external ID is rejected before array indexing. Caller output remains
  unchanged on failure.
- The full validator is diagnostic and is excluded from ordinary-operation
  complexity measurements.

Letters map to dense IDs `A=0` through `H=7`. Apply unions in this order:

```text
A-B, C-D, A-C, E-F, G-H, E-G, A-E
```

Union by component size with the smaller-ID tie rule produces:

```text
parent          [A, A, A, C, A, E, E, G]
component_size  [8, 0, 0, 0, 0, 0, 0, 0]
components      1
```

An iterative find on H compresses `H -> G -> E -> A`:

```text
parent          [A, A, A, C, A, E, A, A]
component_size  [8, 0, 0, 0, 0, 0, 0, 0]
```

Processing D-H next performs no merge because both roots are A. The search
compresses D to A, and the relationship is classified as cycle-producing.

## Supplied edge-list prelab

The prelab uses bounded instructor-supplied incident records; it does not
replace the capstone graph representation.

- Every logical edge ID has exactly two records.
- A non-self edge has reciprocal endpoint records with equal ID and weight.
- A self-loop has two identical records.
- Different IDs remain different logical edges, even when their endpoints and
  weights match. Genuine parallel edges are therefore preserved.
- The builder emits one canonical edge per logical ID with the smaller
  endpoint first.
- Its output is committed only after the complete input validates.
- The `qsort` comparator orders by signed 64-bit weight, endpoints, and then
  logical ID using relational comparisons. It never subtracts weights.

Students test this interface but do not implement Kruskal selection or a
minimum spanning tree in Module 13.

## Package map

```text
module_13_linked_list_dsu/
|-- README.md
|-- diagrams/
|   `-- linked_list_dsu_models.md
|-- instructor/
|   |-- answer_key.md
|   |-- lesson_plan.md
|   `-- technical_notes.md
|-- student/
|   |-- cognitive_pause.md
|   |-- evidence_template.md
|   |-- inquiry_prompt.md
|   |-- inquiry_prompt_linear.md
|   |-- investigation_worksheet.md
|   |-- investigation_worksheet_linear.md
|   |-- lab.md
|   |-- linked_list_autopsy.md
|   |-- representation_reveal.md
|   |-- rubric.md
|   |-- textbook.md
|   `-- vocabulary.md
|-- release/
|   |-- prepare_student_release.ps1
|   |-- release_manifest.md
|   |-- stage_a_README.md ... stage_e_README.md
|   |-- student_build.ps1
|   |-- student_code_README.md
|   `-- student_Makefile
|-- dist/
|   `-- module_13_stage_a_*.zip ... module_13_stage_e_*.zip
`-- code/
    |-- README.md
    |-- build.ps1
    |-- Makefile
    |-- include/
    |   |-- linked_list.h
    |   |-- dsu.h
    |   `-- undirected_edge_list.h
    |-- starter/
    |   |-- linked_list.c
    |   `-- dsu.c
    |-- solution/
    |   |-- linked_list.c
    |   `-- dsu.c
    |-- support/
    |   `-- undirected_edge_list.c
    |-- tests/
    |   |-- test_core.c
    |   |-- test_extension.c
    |   `-- test_student.c
    `-- autopsy/
        |-- README.md
        `-- faulty_linked_delete.c
```

The source package contains exactly 43 files before the five generated
archives: 26 Markdown files, 3 PowerShell files, 2 Makefiles, 9 C files, and
3 headers.

## Recommended release order

1. Run `release/prepare_student_release.ps1` only after all materials and
   tests pass.
2. Release Stage A before Meeting A. It withholds formal names,
   representations, formulas, code, and completed reasoning.
3. Release Stage B after each student preserves the initial card-and-group
   model.
4. Release Stage C after the exactly-three-target Cognitive Pause and
   instructor comparison.
5. Release Stage D only after the student preserves Sections A through F of
   Stage C.
6. Release Stage E after retrieval and Stage D calibration in Meeting B.
7. Keep `instructor/`, `code/solution/`, and
   `code/tests/test_extension.c` instructor-only until revisions close.

## Core submission

Students submit:

- completed `code/starter/linked_list.c`;
- completed `code/starter/dsu.c`;
- completed `code/tests/test_student.c`;
- reproducible core and student-test output;
- exactly three original tests in the required categories;
- before/after linked-list ownership diagrams;
- the canonical parent and component-size trace before and after compression;
- evidence for full-list, allocation, invalid-ID, and same-set boundaries;
- edge-builder and comparator prelab observations;
- a completed evidence record and Linked-List Autopsy; and
- a corrected Cognitive Pause.

## Exactly three implementation TODO clusters

1. Complete bounded linked-list front insertion, first-match deletion, and
   destruction while preserving ownership.
2. Complete make-set initialization and iterative two-pass find.
3. Complete union by component size, including the smaller-root tie rule and
   the already-together result.

The public headers and the undirected edge-list builder are supplied.

## Fixed course conventions

- Linked lists and DSU instances contain no more than 16 active items.
- A linked list has a configurable limit no larger than 16.
- List values are `int`; sizes and identifiers use `size_t`.
- List allocation belongs to the list until deletion or destruction.
- DSU identifiers are dense and bounds-checked before indexing.
- DSU uses `parent[]` plus `component_size[]`, not rank.
- Find is bounded, iterative, and two-pass.
- Equal-size union selects the smaller root ID.
- The prelab weight type is `int64_t`.
- Every logical edge has exactly two incident records, including a self-loop.
- The edge comparator is relational and deterministic.
- The supplied faulty deletion is an actual, bounded use-after-free example.
  It is a separate executable and is never linked into normal tests.
  Ordinary autopsy commands run only a safe inspection branch. The explicit
  unsafe target compiles with sanitizers and never runs automatically.
- Full Kruskal, Prim, MST construction, and capstone representation changes
  are deferred.

## Cost

Let `n` be the number of list nodes or DSU elements, `A` the number of
incident records, and `E` the number of logical edges.

- Linked-list front insertion is `O(1)`.
- Linked-list search/removal, destruction, and full validation are `O(n)`.
- DSU initialization is `O(n)`; one make-set action is `O(1)`.
- Across an optimized operation sequence, find and union take amortized
  `O(alpha(n))` time. `alpha` is the inverse-Ackermann function, which grows
  so slowly that it is below 5 for ordinary practical input sizes.
- DSU storage is `O(n)`.
- The supplied edge-list builder is `O(A + E)`.
- The course `qsort` step is `O(E log E)`.
- Explicit full validators are excluded from ordinary-operation measurements.

These bounds describe the supplied and required implementations, not a
naive parent-chain version.

## Security and interpretation boundary

Shared DSU membership means only that the accepted relationship stream places
two IDs in one connected component. It does not establish trust,
authorization, a route, a shortest path, or resilience. Standard Union-Find
also cannot remove an old relationship or reconstruct the relationship path.

## Relationship to the course spiral

- **Revisits:** Module 1 linked-node diagrams, ownership, allocation,
  components, bounds checks, and implicit trees.
- **Contrasts:** an ArrayList owns one contiguous block; a linked list owns
  separate nodes. A DSU answers membership, not traversal or path questions.
- **Introduces:** safe linked deletion, iterative path compression, union by
  component size, logical edge IDs, and relational sorting comparison.
- **Forwards:** Module 15 reuses DSU for Kruskal cycle checks and the supplied
  edge-list interface for sorted-edge processing.
