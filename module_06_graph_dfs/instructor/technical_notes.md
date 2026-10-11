# Module 6 Technical Notes — Array DFS and BCC Lab

## Source and preconditions

[student/lab.c](../student/lab.c) is the authority for the current textbook
and lecture. It includes the Module 3 graph globals/algorithms and Module 4
integer stack. It has no entry point. See the
[lecture driver](../code/lecture/lab_demo.c) and `make lecture`.

Preconditions: a valid root in `0..nodes_size-1`, a nonempty simple
undirected graph with symmetric valid adjacency lists, and fitting fixed
capacities. Neighbor order is the stored order. Self-loops are ignored;
parallel edges and directed inputs are outside the algorithm's contract.
No checks enforce these assumptions. Globals change directly; there are no
status codes, allocations, or transactional output guarantees.

## State and reset responsibilities

| State | Meaning | Reset performed by lab |
| --- | --- | --- |
| `visit_time`, `visit_num` | first-entry numbering, zero unvisited | `init_visit()` |
| `parent` | DFS parent, root -1 | `init_visit()` |
| `back_num` | saved low-link values | reached entries overwritten by `save_back_num()` |
| `edges_size` | active edge record count | `init_edges_list()` |
| `edge_index` | symmetric endpoint-to-index lookup | active V×V region set to -1 by `init_edges_list()` |
| `top` | last active stack index | set to -1 by `find_bcc()` |
| `current_bcc` | active result-row count | no wrapper reset; initially zero |
| `bcc_size`, `bcc` | active lengths and edge-index rows | emitted rows written; no full reset |

The source says `/* called once */`. For the lecture, use a fresh process,
initialize the graph once, call `init_edges_list(root)`, then
`find_bcc(root)`. Repeated `edges_init()` appends duplicate neighbor entries.
Repeated `find_bcc()` appends result rows unless callers manage them.

Reindexing another component overwrites `edges` and lookup indices. Old
result rows would then refer to different edge records. A whole-graph
extension needs persistent edge identities, traversal of every unvisited
component, and explicit result resets/ownership. Merely wrapping both
functions in an all-root loop does not produce a coherent global result.

## Neighbor classification and low-link invariant

`_init_edges_list()` records a tree edge before entering an unvisited child.
It skips the parent entry. It records a back edge only from descendant to
ancestor, then skips the larger-discovery reverse entry. Both lookup
directions receive one index. Discovery-number inequalities in
`GraphEdge`'s comments describe these recorded orientations; they are not
a general classifier for directed graphs.

The included `save_back_num()` initializes low and discovery together,
propagates a child's low value after its return, and takes a non-parent
visited neighbor's discovery number when it is smaller. A visited
descendant cannot lower the current value. The result is the minimum
number accessible through tree descent and at most one back edge,
including the current vertex itself.

`find_bcc()` computes low-link values first, resets discovery and parents,
and repeats the same root and adjacency order for extraction. The second
pass must reproduce discovery numbers: changing root, graph, or neighbor
order invalidates comparisons with the saved values. `_find_bcc()` does
not update `back_num`.

## Block extraction invariant

The pending-edge stack contains unassigned tree and back edges. Each
reached undirected edge is pushed exactly once. On a qualifying return,
the parent tree edge remains in the stack and bounds the suffix belonging
to the current block.

For a non-root child u with parent p:

```text
low[u] < discovery[p]  → keep pending edges
low[u] >= discovery[p] → pop through edge (p,u), inclusive
```

The `do ... while` stores the boundary edge before testing for it.
Short-circuit `parent[node] == -1 || ...` keeps the root from reading
`visit_num[-1]`. Root children emit their own blocks; root postorder
itself emits none. An isolate therefore emits no edge block.

Equality is necessary for blocks. A bridge instead satisfies strict
`low[u] > discovery[p]`. A non-root p is a cut vertex if any DFS child
satisfies `low[u] >= discovery[p]`; a root needs at least two DFS children.
These are explanation aids: the lab does not output separate bridge or
cut-vertex arrays.

## Exact root-A reference

```text
discovery: A=1 B=2 C=3 D=4 E=5 F=6
parent:    A=-1 B=0 C=1 D=1 E=3 F=4
low:       A=1 B=2 C=3 D=2 E=2 F=2
edges:     0:A-B 1:B-C 2:B-D 3:D-E 4:E-B 5:E-F 6:F-B 7:F-D
blocks:    [1] | [7,6,5,4,3,2] | [0]
sizes:     1,6,1
final:     edges_size=8 current_bcc=3 top=-1
```

G/H/I/J remain unvisited; G–H is not indexed. The whole graph has four
connected components, but only A–F is processed. B is its cut vertex;
A–B and B–C are its bridges. The peak edge stack has seven entries, and
peak recursive depth is five vertices (A/B/D/E/F).

## Complexity and capacity

Let V be active vertices, R reached vertices, and E_R reached undirected
edges. Each of the three DFS passes takes `O(R + E_R)`. Each edge is
pushed/popped once in extraction. Discovery resets take `O(V)`; resetting
`edge_index` takes `O(V²)`. Thus the complete pipeline takes
`O(V² + E_R)`. The adjacency-list DFS core itself is linear in reached
vertices and edges.

Generalized working storage is `O(R + E_R)` for recursive calls and pending
edges. The symmetric lookup requires `O(V²)` storage, and edge records and
active block entries require `O(E_R)` output storage. Actual arrays are
fixed: `nodes[10]`, `edges[10]`, `stack[10]`, `edge_index[10][10]`, and
`bcc[10][45]`. Forty-five result columns do not increase the ten-edge or
ten-stack limits. `push()`/`pop()` and `add_edge()` are unchecked.

## Verification

Run the lecture target from `code` with a C11 compiler. The lecture output
must agree with the reference above. Compare hand traces for a chain,
a triangle (equality closure), a branching root, G–H, and an isolated
root. Reset all test-owned result state between independent cases.
Sanitizers can check valid executions; they do not make raw helpers checked.
Warnings from the included lab sources should be reported, not silently
edited out of the source used as authority.

## Legacy package boundary

`code/include`, `code/support`, `code/starter`, `code/solution`, the existing
matrix tests, and staged student worksheets belong to the earlier checked
matrix/typed-vertex-stack package. Its public headers remain authoritative
for that package. They do not define the current array lecture's behavior.
