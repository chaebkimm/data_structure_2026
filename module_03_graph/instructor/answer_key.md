# Instructor Answer Key — Module 3

Keep this file instructor-only. Students preserve Stage A, Cognitive Pause,
Stage C, and autopsy predictions before seeing worked answers.

## Macro-question synthesis

A directed adjacency matrix stores one yes-or-no fact for every ordered pair
of active vertex IDs. Row identifies the source, column the destination.
Graphs allow several incoming edges and routes that return to an earlier
vertex, so they represent relationships that do not fit the Module 2 tree.

The implemented graph is fixed, directed, and unweighted. Comparisons with
other graph forms do not expand the four-function API.

## Stage A — Initial inquiry

### A. SNS follower network

```text
0 Mina -> 1 Joon -> 2 Sora -> 3 Dae
   ^                  |
   +------------------+

4 Hana <-> 5 Leo       6 Nuri (isolated)
```

An arrow runs from the follower to the followed account. The immediate
directed relationships are:

- Mina follows Joon: `0 -> 1`;
- Joon follows Sora: `1 -> 2`;
- Sora follows Mina: `2 -> 0`;
- Sora follows Dae: `2 -> 3`;
- Hana follows Leo: `4 -> 5`; and
- Leo follows Hana: `5 -> 4`.

Nuri has no incoming or outgoing follow. Do not add Dae's follow of Sora or
another unstated reverse edge.

### B. Direction

Starting at Mina, the repeating route is Mina -> Joon -> Sora -> Mina and
so on. Sora following Dae gives no evidence that Dae follows Sora. Hana
following Leo and Leo following Hana have opposite sources and destinations
and therefore require two separate facts.

### C. Tree limits

Sora following Mina creates the returning route Mina -> Joon -> Sora ->
Mina, which conflicts with a tree's no-cycle rule. If Mina also followed Dae,
then Mina and Sora would both have a relationship entering Dae. This shared
destination conflicts with the one-incoming-link tree rule.

### D–E. Storage brainstorm

The program must remember whether a relationship exists from each selected
source to each selected destination. Rows can name sources and columns can
name destinations. A missing relationship stores 0. Accept equivalent
plain-language models without requiring graph terms during Stage A.

## Stage B — Matrix reveal and Cognitive Pause

Canonical matrix:

```text
       to
       0  1  2  3  4  5  6
from 0 0  1  0  0  0  0  0
     1 0  0  1  0  0  0  0
     2 1  0  0  1  0  0  0
     3 0  0  0  0  0  0  0
     4 0  0  0  0  0  1  0
     5 0  0  0  0  1  0  0
     6 0  0  0  0  0  0  0
```

### Target 1

The requested rows are:

- row 0: `[0, 1, 0, 0, 0, 0, 0]`;
- row 2: `[1, 0, 0, 1, 0, 0, 0]`; and
- row 6: `[0, 0, 0, 0, 0, 0, 0]`.

Cells `[0][1]` and `[1][0]` represent different directed questions. Mina
follows Joon, so `[0][1]` is 1. Joon does not follow Mina, so `[1][0]` is 0.

### Target 2

Removing `2 -> 3` changes only `grid[2][3]` from 1 to 0. New row 2 is
`[1, 0, 0, 0, 0, 0, 0]`; Sora's out-degree is 1.

### Target 3

Consider each request independently from the original seven-account state:

| Addition | Result | Reason |
|---|---|---|
| `2 -> 2` | reject, return 0 | self-loop addition |
| `7 -> 1` | reject, return 0 | vertex 7 is inactive |
| `3 -> 0` | accept, return 1 | distinct active endpoints |

A rejection changes no metadata or cell. Successful `3 -> 0` sets only
`grid[3][0]` to 1. It means Dae follows Mina.

## Stage C — Investigation

### A1. Equivalent representations

Diagram:

```text
0 Mina -> 1 Joon -> 2 Sora -> 3 Dae
   ^                  |
   +------------------+

4 Hana <-> 5 Leo       6 Nuri (isolated)
```

Ordered edge set:

```text
{(0, 1), (1, 2), (2, 0), (2, 3), (4, 5), (5, 4)}
```

Matrix:

| From \ To | 0 | 1 | 2 | 3 | 4 | 5 | 6 |
|---:|---:|---:|---:|---:|---:|---:|---:|
| 0 | 0 | 1 | 0 | 0 | 0 | 0 | 0 |
| 1 | 0 | 0 | 1 | 0 | 0 | 0 | 0 |
| 2 | 1 | 0 | 0 | 1 | 0 | 0 | 0 |
| 3 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
| 4 | 0 | 0 | 0 | 0 | 0 | 1 | 0 |
| 5 | 0 | 0 | 0 | 0 | 1 | 0 | 0 |
| 6 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |

There are six arrows, six ordered pairs, and six cells containing 1.

### A2. Row and column

Row 2 asks which edges leave Sora. Its 1 cells are `grid[2][0]` and
`grid[2][3]`. Column 2 asks which edges enter Sora; its only 1 is
`grid[1][2]`.

`grid[0][1]` records only `0 -> 1`; it does not imply `1 -> 0`.
The reverse is absent in the supplied graph.

### B1. Degree

- Sora out-degree: 2, counting `grid[2][0]` and `grid[2][3]`.
- Mina in-degree: 1, counting `grid[2][0]` in column 0.

In-degree is conceptual here; there is no matching required function.

### B2. Removal

After removing `2 -> 3`:

```text
0 1 0 0 0 0 0
0 0 1 0 0 0 0
1 0 0 0 0 0 0
0 0 0 0 0 0 0
0 0 0 0 0 1 0
0 0 0 0 1 0 0
0 0 0 0 0 0 0
```

Only cell `[2][3]` changes. Sora's out-degree becomes 1. All other cells,
including reverse cell `[3][2]`, remain unchanged.

### B3. Idempotence

Setting an existing edge cell to 1 again produces the requested existing-edge
state. Setting an absent edge cell to 0 again produces the requested
absent-edge state. Both are successful requests returning 1, with no further
state change.

### C1. Active versus physical

For count 7, active IDs are 0 through 6. Index 7 is below the physical bound
16 but is not below `vertex_count`, so it cannot be used as an endpoint.

### C2. Completed-state classifications

| Stored fact | Classification | Rule |
|---|---|---|
| `grid[2][0] == 1` | valid | distinct active endpoints; edge `2 -> 0` |
| `grid[2][2] == 1` | invalid | active diagonal must remain zero |
| `grid[7][1] == 1` with count 7 | invalid | a cell involving an inactive ID must be zero |
| `grid[0][2] == 2` | invalid | every cell must be exactly 0 or 1 |

These are state classifications, not requests to pass malformed objects to
ordinary functions.

### C3. Full clearing and preservation

Initialization must clear all 16 rows and 16 columns so a previously stored
inactive cell cannot become a ghost edge if a later graph uses more vertices.

A rejected add or remove preserves the complete graph. A rejected out-degree
request preserves a non-null caller output. Initialization with count above
16 preserves a supplied graph.

### D1. Routes and cycles

One route from Mina to Dae is `0 -> 1 -> 2 -> 3`. Mina, Joon, and Sora form
`0 -> 1 -> 2 -> 0`. A later traversal must remember visited vertices or it could
revisit this cycle forever. This is conceptual preparation, not a required
Chapter 3 search algorithm.

### D2. Shared destination

If Mina also follows Dae, edges `0 -> 3` and `2 -> 3` are both valid graph
relationships. Dae then has two incoming edges, whereas the child-only tree
requires one incoming link for each non-root node.

### D3. Isolated active vertex

Nuri is isolated: row 6 and column 6 contain only zeros. Nuri's ID is still
below `vertex_count`. Before the removal, Dae's row is all zero, but Sora's
follow gives column 3 an incoming edge. Dae is therefore not isolated.
Index 7 is inactive and is not a vertex at all. Every physical cell involving
it must also be zero.

### E1. Directed, undirected, and weighted

A conceptual undirected relationship between 0 and 1 can be represented by
two matching opposite cells, both 1. The implemented structure has no kind
field and its mutation functions always update one directed cell; the
comparison does not add an undirected mode.

A binary cell stores follow existence only. An interaction count may exceed
1 and has a different meaning, so storing it requires a different contract.

### E2. Representation comparison

| Question | Matrix | Edge list | Adjacency list |
|---|---|---|---|
| one direct edge lookup | direct cell, `O(1)` | scan pairs, `O(E)` | scan source's list, commonly `O(out-degree)` |
| outgoing neighbors | scan row, `O(V)` | scan edges, `O(E)` | inspect source's list, `O(out-degree)` |
| storage with few edges | reserves pair grid, `O(V²)` conceptually | `O(E)` | `O(V + E)` |

For a small fixed graph with frequent direct-edge questions, the matrix is a
reasonable choice because lookup is direct. Its tradeoff is reserved storage
for every possible pair.

### E3. Transfer and boundary

1. Fixed ArrayList: event codes kept in numbered sequence.
2. Binary tree: hierarchy with meaningful left and right child positions.
3. Directed graph: follows among SNS accounts that may form cycles or share
   a destination.

A follow edge records only that one account follows another. It does not
prove friendship, permission to view a post, or that a post will appear in a
feed.

A suitable exit sentence is: “The matrix cell at row `from`, column `to`
records the directed edge `from -> to`; a valid completed graph also keeps
all cells binary, its diagonal zero, and inactive cells zero.”

## Stage D — Textbook components and feed reasoning

Release [the English textbook](../student/textbook.md) and
[the Korean textbook](../student/textbook_korean.md) only after the Stage C
attempt is preserved. These are worked conceptual answers, not additional
implementation or test requirements.

Use the original six-follow graph before removing `2 -> 3`:

| Rule | Components |
|---|---|
| Weak: ignore arrow direction while tracing paths | `{0, 1, 2, 3}`, `{4, 5}`, `{6}` |
| Strong: directed paths must connect every pair in both directions | `{0, 1, 2}`, `{3}`, `{4, 5}`, `{6}` |

Each group is maximal: no outside vertex can join while preserving the rule.
Maximal does not mean the largest group. `{4, 5}` cannot grow under either
rule even though another component contains more accounts.
Strong connectivity requires paths, not direct mutual follows between every
pair. Ignoring directions for weak connectivity leaves the follower graph
unchanged. Nuri is a singleton under either rule. Dae initially has no
outgoing edge but has an incoming edge, so Dae is not isolated. Dae cannot
reach Mina, Joon, or Sora and therefore forms a singleton strong component.
A singleton needs no self-loop because a path from a vertex to itself can
use zero edges.

After removing `2 -> 3`, Dae becomes isolated. Weak components become
`{0, 1, 2}`, `{3}`, `{4, 5}`, and `{6}`. The strong component memberships
stay the same. Sora's out-degree falls from 2 to 1.

For an illustrative feed before the unfollow, Mina directly follows Joon.
Joon's posts can be direct-follow candidates. Sora is in Mina's strong
component and could supply additional recommendation candidates. Dae is in
Mina's weak component but a different strong component and could supply
broader candidates. Public posts from Hana or Leo may match Mina's interests
even though those accounts are outside her weak component. Nuri's lack of
links motivates using stated interests or other signals for a new account.

Component labels are neither ranking scores nor access permissions. They do
not establish a dense group or common topic. A feed needs separate rules
for eligibility and ranking. An eligible post by Dae could rank above one by
Sora. For example, recency, relevance to Mina's interests, and past
interactions could affect the ranking; a component label supplies none of
those values. A path or component alone neither grants viewing permission
nor guarantees display.

Before the unfollow, Sora directly follows both Mina and Dae. Restricting
Sora's feed to her strong component `{0, 1, 2}` would omit Dae despite that
direct follow. Component membership should not be treated as a mandatory
boundary for all feed candidates. These possibilities do not claim that a
particular SNS uses component algorithms. The four-function C lab stores
follows; it does not compute components or construct a feed.

## Exact C contract answers

```c
#define GRAPH_MAX_VERTICES 16

struct DirectedGraph {
    size_t vertex_count;
    int grid[GRAPH_MAX_VERTICES][GRAPH_MAX_VERTICES];
};

int graph_init(struct DirectedGraph *graph, size_t vertex_count);
int graph_add_edge(struct DirectedGraph *graph, size_t from, size_t to);
int graph_remove_edge(struct DirectedGraph *graph, size_t from, size_t to);
int graph_out_degree(
    const struct DirectedGraph *graph,
    size_t vertex,
    size_t *out_degree
);
```

### Initialization

- Null graph: return 0.
- Count greater than 16: return 0 and preserve a supplied graph.
- Valid count including zero: clear all 256 cells, store count, return 1.

### Addition

Validate graph pointer, metadata, and both active endpoints before writing.
Reject equal endpoints with 0. For valid distinct endpoints, set exactly
`grid[from][to] = 1` and return 1, including when it was already 1.

### Removal

Validate pointer, metadata, and endpoints. For valid endpoints, including
equal endpoints, set exactly `grid[from][to] = 0` and return 1, including
when it was already 0.

### Out-degree

Reject a null output, null graph, invalid metadata, or inactive vertex with
0 and leave any non-null output unchanged. Count active-row cells exactly
equal to 1, commit the local result, and return 1.

### Direct lookup

There is no fifth query function. Establish a valid graph and check both IDs
against `vertex_count` before reading `grid[from][to]`. The read is
constant time and makes no change.

## Complexity answers

Let `V` be active count and `M = 16` be the fixed bound.

| Operation | Cost |
|---|---:|
| initialize | `O(M²)`, exactly 256 writes |
| add | `O(1)` |
| remove | `O(1)` |
| guarded direct lookup | `O(1)` |
| out-degree | `O(V)` |
| inspect active topology | `O(V²)` |
| fixed storage | `O(M²)`, 256 integers |

## Ghost-Connection Autopsy — instructor answers

This isolated regression fixture starts with four active vertices and
`grid[3][1] == 1`.
The first bad completed state occurs when faulty code changes only
`vertex_count` from 4 to 3. At that moment vertex 3 is inactive but
`grid[3][1]` remains 1.

Expected output:

```text
before shrinking: vertex 3 -> 1 = 1
after shrinking to 3 vertices:
vertex 3 is inactive: yes
inactive cell [3][1] is still 1
after growing back to 4 without clearing:
ghost connection 3 -> 1 reappears: yes
```

The capacity makes the access physically in bounds; it does not make vertex 3
active. The later change back to count 4 reveals the stale connection but is
not the first cause.

For this module, use `graph_init` for a new vertex count; it clears all 256
cells. A hypothetical resize operation would need its own contract that
clears every newly inactive row and column before committing a smaller count
and preserves state on failure. No such resize is a required API.

A regression can initialize four vertices, add `3 -> 1`, initialize the same
object with count 3, assert all 256 cells are zero, initialize with count 4,
and assert that `grid[3][1]` is still zero. This may be a rationale attached
to one of the three student tests; the autopsy does not require a fourth.

## Assessment alignment

| Criterion | Points |
|---|---:|
| Directed representation and vocabulary | 15 |
| Initialization | 20 |
| Directed edge operations | 20 |
| Out-degree and direct lookup | 15 |
| Invariants and boundary safety | 10 |
| Tests and tool evidence | 15 |
| Ghost autopsy and reflection | 5 |
| Total | 100 |

The three authored-test slots cover full initialization including inactive
cells; a coherent directed/idempotent/lookup/degree sequence; and rejected
self-loop/inactive mutation with a preserved graph or a rejected degree query
with a preserved output. Require distinct claims and rationales.

Accept standard or linear responses, everyday vocabulary, and approved
compiler, debugger, or instructor-CI evidence. Do not penalize an initial
misconception that was preserved and meaningfully corrected.
