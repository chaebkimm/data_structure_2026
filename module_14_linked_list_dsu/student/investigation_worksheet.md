# Stage C - Linked-List and DSU Investigation

Name: ____________________________
Date: ____________________________

Use this standard-format worksheet after the Cognitive Pause and
instructor comparison. Preserve Sections A through F before opening Stage
D. Sections G through I are later work.

All records and relationships are synthetic. IDs are ordered
`A,B,C,D,E,F,G,H`.

## A. Read the linked representation - 10 points

Use:

```text
head=R, size=3, limit=4
R: value 17, next Q
Q: value 23, next P
P: value 31, next NULL
```

### A1. Traverse - 3 points

Write the node labels and values in traversal order. State where traversal
stops.

____________________________________________________________________

### A2. Interpret symbols - 3 points

In plain language, explain `LinkedNode *head`, `R->next`, and `NULL`.

____________________________________________________________________

### A3. Check the invariant - 4 points

Use the five course list rules to justify whether the locked state is
valid. State what the list owns.

____________________________________________________________________

## B. Trace safe list mutations - 15 points

### B1. Reconstruct the pushes - 5 points

Starting empty with limit 4, push 31, then 23, then 17. For each success,
state the allocated symbolic node, its `next`, the head, and size.

____________________________________________________________________

### B2. Remove the first 23 - 6 points

State the comparison order, predecessor, victim, and successor. Number the
save, relink, release, and count-change actions. Draw the exact final
state.

____________________________________________________________________

### B3. Destroy - 4 points

From `R(17)->P(31)->NULL`, trace the saved successor and released node on
each iteration. State the exact all-zero final `head`, `size`, and `limit`.

____________________________________________________________________

## C. Diagnose ownership and failure - 10 points

### C1. Find the lifetime error - 4 points

Analyze:

```c
free(victim);
successor = victim->next;
previous->next = successor;
```

Identify the first invalid action, name the defect, and repair the order.

____________________________________________________________________

### C2. Preserve failures - 3 points

For allocation failure, full limit, and absent value, list every public
field or reachable value that must remain unchanged.

____________________________________________________________________

### C3. Separate safety from meaning - 3 points

Give one example each of a memory-safety claim, an ownership claim, a
representation-integrity claim, and an application claim the list cannot
prove.

____________________________________________________________________

## D. Build and read the DSU forest - 15 points

### D1. Make eight singleton sets - 4 points

Write `parent`, `component_size`, `element_count`, and `component_count` after
make-set creates A through H. State the inactive parent sentinel.

____________________________________________________________________

### D2. Trace the seven unions - 8 points

Apply union by component size. On equal sizes, the smaller root ID wins.

```text
A-B, C-D, A-C, E-F, G-H, E-G, A-E
```

After each operation, state the roots compared, winning root, complete
parent array, complete component-size array, and component count.

| After operation | Roots compared | Winning root | `parent` | `component_size` | Components |
|---|---|---|---|---|---:|
| `A-B` | | | | | |
| `C-D` | | | | | |
| `A-C` | | | | | |
| `E-F` | | | | | |
| `G-H` | | | | | |
| `E-G` | | | | | |
| `A-E` | | | | | |

### D3. State the DSU invariant - 3 points

Explain the root rule, nonroot-size rule, parent bound, component-count
rule, and what following parents must eventually reach.

____________________________________________________________________

## E. Compress and classify - 15 points

Use the locked state:

```text
parent:         [A,A,A,C,A,E,E,G]
component_size: [8,0,0,0,0,0,0,0]
components:     1
```

### E1. Find H - 6 points

Trace both iterative passes. Write the exact path, every changed entry, the
complete final parent array, and the unchanged size array.

____________________________________________________________________

### E2. Union D and H - 6 points

Starting after E1, trace both root searches, any compression, `merged`,
component count, and the exact final parent array. Explain the
cycle-producing result for an undirected relationship.

____________________________________________________________________

### E3. Reject before indexing - 3 points

For `element_count=8`, classify IDs 7, 8, and 16. Explain why range
checking must occur before reading either array and what a failed call
preserves.

____________________________________________________________________

## F. Analyze cost, scope, and the spiral - 10 points

### F1. Match actual costs - 4 points

State and explain the cost of each operation below.

| Operation | Cost |
|---|---:|
| linked push-front mutation core | |
| search/remove by value | |
| destroy or full list validation | |
| create all singleton DSU sets | |
| optimized find/union over a long sequence | |

Define “amortized” and explain `alpha(n)` without deriving it.

### F2. Do not hide validator cost - 2 points

Why would running a complete diagnostic validator before every operation
change the advertised operation cost?

____________________________________________________________________

### F3. Connect local changes to global invariants - 2 points

Compare a list relink, DSU path compression, and DSU root attachment.
State what local field changes and what whole-structure meaning remains
valid.

____________________________________________________________________

### F4. Limit DSU claims - 2 points

State why shared membership is not authorization, trust, a route, a
shortest path, resilience, or efficient deletion support.

____________________________________________________________________

## G. Design exactly three tests - later work - 9 points

### G1. List lifecycle and preservation - 3 points

Add one test covering meaningful behavior from empty state through
destruction, including one unchanged failure.

____________________________________________________________________

### G2. Creation, compression, tie, and invalid ID - 3 points

Add one test checking exact state, the smaller-root tie, and
failure/output preservation.

____________________________________________________________________

### G3. Relationship cycles and scope - 3 points

Add one test covering a repeated relationship, a self-loop, connected
queries—which report whether two IDs share a root—component counts, and
the trust limitation.

____________________________________________________________________

## H. Complete the isolated autopsy - later work - 6 points

### H1. Earliest invalid action - 2 points

State the first lifetime violation in the supplied faulty program.

____________________________________________________________________

### H2. Repair and evidence - 2 points

Give the corrected order and record sanitizer, debugger, or instructor
trace evidence.

____________________________________________________________________

### H3. Regression - 2 points

State the expected chain, size, and allocation count for a regression test.

____________________________________________________________________

## I. Read the edge pre-lab and synthesize - later work - 10 points

The supplied builder receives incident records with dense edge IDs. Each
logical undirected edge has exactly two reciprocal records; a self-loop has
two identical records. Different IDs preserve parallel edges.

Main fixture:

```text
A-B weight 1, ID 0
A-B weight 4, ID 1
A-C weight 3, ID 2
B-C weight 2, ID 3
C-D weight 5, ID 4
```

### I1. Build one logical edge list - 3 points

Explain why ten incident records produce five output records and why both
A-B records survive.

____________________________________________________________________

### I2. Sort safely - 3 points

An **endpoint** is one end of a relationship. **Normalized endpoints**
place the smaller ID first. Write the sorted order by signed 64-bit weight,
normalized endpoints, then ID. Explain why a relational comparator must
not subtract, including at
`INT64_MIN`, the smallest signed 64-bit value, and `INT64_MAX`, the
largest.

____________________________________________________________________

### I3. Preview Kruskal - 2 points

Using the sorted order, identify the first relationship whose endpoints
already share a DSU root. This is a read/test pre-lab; do not implement
Kruskal.

____________________________________________________________________

### I4. Exit synthesis - 2 points

Answer:

> How can careful local link changes preserve a correct whole structure,
> and how will DSU support a later graph algorithm?

____________________________________________________________________
