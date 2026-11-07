# Module 6 Answer Key — Grouping connections in a graph

This key follows the seven sections of the [bilingual workbook](../student/class_material.md)
and [textbook](../student/textbook.md). Sections 1–4 use the conceptual
graph numbered by its completed DFS visits 1–7. Sections 5–7 connect the
method to the separate A–J graph in the [lab](../student/lab.c).

## 1. Thinking logically

### Storage and exploration

| Representation | Store 3–6 | Add absent 1–7 | Delete 3–6 |
| --- | --- | --- | --- |
| Neighbor lists | 6 in 3's list and 3 in 6's list | append each endpoint to the other's list | remove both entries |
| Edge list | one endpoint-pair record | append one record | remove its record |
| Adjacency matrix | both symmetric cells set | set both 1/7 cells | clear both 3/6 cells |

Vertex 7 has incident edges 2–7 and 3–7. Removing it removes both records,
its neighbor list, its entries in other lists, and its matrix row/column.
If records or vertex slots move, update all affected indices and lookup
entries. Run DFS afresh after graph changes. The lab's `add_edge()` records
existing adjacency; it does not implement a general graph-editing interface.

### Neighbor cases and action timing

| Encounter at visit 3 | Kind | Explore again? | Evidence |
| --- | --- | --- | --- |
| 3 → 1 | non-parent ancestor | no | smaller number; parent is 2 |
| 3 → 2 | parent | no | reverse of the incoming tree edge |
| 3 → 4 | new tree child | yes | unvisited when examined |
| 3 → 6 after 4 returns | processed descendant | no | 6 was reached through 4 and 5 |
| 3 → 7 | new tree child | yes | still unvisited at this encounter |

The parent also has a smaller visit number, so its case must be excluded
before recognizing ancestor back edges. Number a vertex at preorder.
Record/push a tree edge and set the child's parent before recursion.
Handle a back edge toward an ancestor without recursion. After a child
returns, use its completed low-link value and decide whether to close a
block before scanning the next neighbor. Postorder follows all neighbors.
These cases assume simple undirected input.

### Recording each edge once

```text
0: 1→2 tree     1: 2→3 tree     2: 3→1 back
3: 3→4 tree     4: 4→5 tree     5: 5→6 tree
6: 6→3 back     7: 6→4 back     8: 3→7 tree
9: 7→2 back
```

Here 0–9 are edge-record indices; the endpoints are visit numbers. The
connections remain undirected. Reverse parent/descendant entries create
no new records. Both endpoint orders locate one record. Zero is a valid
edge index, so `-1` marks no record. A presence matrix answers whether an
edge exists, whereas this lookup identifies its recorded edge index.

### Low-link values

| Visit number | Parent visit number | Low-link |
| --- | --- | --- |
| 1 | none | 1 |
| 2 | 1 | 1 |
| 3 | 2 | 1 |
| 4 | 3 | 3 |
| 5 | 4 | 3 |
| 6 | 5 | 3 |
| 7 | 3 | 2 |

At 6, neighbor 3 lowers the initial value 6 to 3. Neighbor 4 cannot lower
3. That value propagates through 5 and 4 after their child calls return.
Vertex 7 reconnects to 2. Vertex 3 connects directly back to 1 and passes
that value to 2. Include the vertex's own number among the candidates;
exclude the parent edge.

### Blocks and stack trace

The blocks contain edges among 3/4/5/6 and among 1/2/3/7. They share cut
vertex 3 and no edge. The paths 3–6 and 3–4–6 share only their endpoints;
the two-path property must hold for every pair in each maximal block.
Removing 3 leaves connected vertices 1/2/7 and 4/5/6 as separate groups.
A bridge forms a single-edge block. An isolate has no edge to assign.

Stacks below are bottom to top. Return rows include the parent's comparison.

| Event | Pending edges | New block, pop order |
| --- | --- | --- |
| Scan 6 → 4 after 6 → 3 | 1–2, 2–3, 1–3, 3–4, 4–5, 5–6, 3–6, 4–6 | none |
| Return 6 → 5 | same eight | none; 3 < 5 |
| Return 5 → 4 | same eight | none; 3 < 4 |
| Return 4 → 3 | 1–2, 2–3, 1–3 | 4–6, 3–6, 5–6, 4–5, 3–4 |
| Scan 7 → 2 | 1–2, 2–3, 1–3, 3–7, 2–7 | none |
| Return 7 → 3, then 3 → 2 | same five | none; 2 < 3, then 1 < 2 |
| Return 2 → 1 | empty | 2–7, 3–7, 1–3, 2–3, 1–2 |

Equality closes a block: 4's branch reconnects to parent 3 but cannot
bypass it to an earlier ancestor. Pop through 3–4, including that edge.
Likewise 1 ≥ 1 closes the root child's block through 1–2. Excluding the
boundary leaves it for the wrong block. The root checks each child by the
same rule; its own return emits no additional block. Here root 1 has one
DFS child and is not a cut vertex.

## 2. Calculating efficiency

### Storage

Adjacency-list storage grows with vertices and edges; edge records need
two endpoint indices per edge. A matrix or pair lookup reserves `V²`
cells. Fixed arrays reserve all their cells: `edges[45]`,
`edge_index[10][10]`, `bcc[9][45]`, and `bcc_size[9]` do not shrink to the
active counts. The result table reserves 405 edge-index cells, although
the conceptual example uses ten entries in two rows.

### Traversal memory

Peak active calls follow 1/2/3/4/5/6: six calls. Peak pending count is
eight, after processing 6 → 4. Recursive calls remember unfinished scans;
the edge stack stores edges awaiting assignment. Generalized call space
is `O(R)` and pending space is `O(E_R)`. The imported `stack[10]` must fit
the peak independently of the 45-record edge capacity.

### Adding an item

With space available, appending an edge record, updating its two lookup
cells, appending two neighbor entries, or setting two matrix cells takes
constant time. Preparing an entire row and column for a new vertex takes
work proportional to `V`.

### Traversal work

The workbook counts are 7, 20, 21, 60, and 49. One adjacency-list pass is
`O(R + E_R)`. Three passes keep that growth rate, and pushing/popping each
edge once adds `O(E_R)`. Preparing the whole active lookup costs `O(V²)`,
so the complete pipeline is `O(V² + E_R)`. A single starting vertex only
explores its reachable component.

## 3. Glossary

1. **Visit number / array index:** discovery order versus a stored vertex's
   location. In the conceptual driver, array index 0 receives visit number 1.
2. **Tree / back edge:** first discovery of a child versus a non-parent
   connection from descendant to ancestor, such as 3 → 1.
3. **Adjacency matrix / edge lookup:** whether a pair is connected versus
   which recorded edge represents it. An unreached existing edge can have
   lookup `-1` in a pass confined to another component.
4. **Connected component / block:** a maximal connected vertex group versus
   an edge group with no separating vertex internally. Blocks can share a
   cut vertex. This graph has one connected component and two edge blocks.
5. **Cut vertex / bridge:** a vertex whose removal increases the component
   count versus an edge whose removal does so. Vertex 3 is a cut vertex in
   the conceptual graph; A–B is a bridge in the alphabet graph.
6. **Call stack / pending-edge stack:** active function state versus edge
   indices waiting to be grouped. They are separate stored objects.

## 4. Invariant

| Checkpoint | Handled | Pending | Assigned |
| --- | --- | --- | --- |
| Start | 0 | 0 | 0 |
| First pop stored | 8 | 7 | 1 |
| First block completed | 8 | 3 | 5 |
| After 3 returns to 2 | 10 | 5 | 5 |
| Finished | 10 | 0 | 10 |

Each handled edge must have one identity in exactly one collection.
Assigned includes entries of a row still being filled. Check after a
complete pop-and-store, not while the removed edge is only in a local
variable. Counts alone cannot detect a duplicate replacing a missing edge.

At 4's postorder, older prefix `1–2, 2–3, 1–3` lies below suffix
`3–4, 4–5, 5–6, 3–6, 4–6`. The suffix belongs to the incoming edge's
block. Parent 3 has not yet compared; it closes after 4 returns. At 3's
postorder, suffix `2–3, 1–3, 3–7, 2–7` belongs with incoming edge 2–3,
but older 1–2 also belongs to that eventual block. A suffix need not yet
contain the whole block or describe the whole stack.

Deeper comparisons already removed separate inner blocks. Remaining
branch edges stay with the incoming edge when they can reconnect above
the current vertex. The closing low-link comparison establishes when the
remaining suffix is a whole block; the accounting rule establishes that
no edge is lost or duplicated. Root postorder has an empty pending stack.

Duplicate pushing breaks uniqueness. Excluding a boundary leaves it for
a later block. Changing root or neighbor order after the low-link pass
can make summaries refer to different DFS branches. Preserve the rules
by initializing, handling each connection once, storing each popped edge,
including the boundary, and replaying the same root/order. Valid indices
and fitting capacities remain separate preconditions.

## 5. Coding plan

`alphabet_nodes_init()` and `edges_init()` prepare the A–J graph once.
`init_edges_list(start_node)` resets visit state, clears the edge count,
fills the active lookup with `-1`, and records the reached edges.
`find_bcc(start_node)` resets visits, saves low-links, empties the edge
stack, resets visits again while preserving low-links, and groups edges.
These two wrappers perform three DFS passes: recording, low-links, grouping.

`init_visit()` clears `visit_time` and `visit_num`, and sets parents to
`-1`. It preserves `back_num`, edge records, lookup cells, and results.
`find_bcc()` does not clear `current_bcc`, `bcc`, or `bcc_size`; another
call appends rows unless the caller manages results. Reindexing another
component changes the meaning of old row indices. A whole-graph extension
requires consistent edge identities and explicit result management.

## 6. New C syntax explained

- `edge_index[u][v]` selects one cell by endpoint indices; `bcc[row][pos]`
  stores an edge index in a result row.
- Prefix `++visit_time` increments before use, so visits start at 1.
  Postfix `edges_size++` uses the old count, so edge indices start at 0.
- Chained assignment increments the counter once and stores the same
  number in both `back_num[i]` and `visit_num[i]`.
- `continue` advances to the next neighbor; it does not return from DFS.
- `bcc[cur][pos++] = edge` stores at the current position, then advances it.
- `do ... while` runs at least once and stores the boundary before its
  condition stops the loop. `edge` is declared outside so the condition
  can read it; the trailing semicolon is required.
- `#include` inserts the earlier source before compilation. Its globals
  and functions are already defined, including `save_back_num()`. The
  textbook review copy must not be pasted as another definition.

## 7. C code

The alphabet driver gives:

```text
vertex       A B C D E F
visit_num    1 2 3 4 5 6
parent      -1 0 1 1 3 4
back_num     1 2 3 2 2 2
edges        0:A→B 1:B→C 2:B→D 3:D→E 4:E→B 5:E→F 6:F→B 7:F→D
bcc rows     [1] | [7,6,5,4,3,2] | [0]
bcc_size     1,6,1
edges_size=8 current_bcc=3 top=-1
```

Both B–E lookup directions equal 4. G–H is unreached, so its lookup is
`-1`; G/H/I/J stay unvisited. The whole graph has four connected components.
Resolve the rows into B–C, the six edges among B/D/E/F, and A–B. These
three blocks share B. The A-rooted passes each inspect 16 neighbor entries;
lookup preparation writes 100 cells. Peak active calls are five and peak
pending edges seven.

The second driver uses the conceptual graph with indices 0–6 and A–G data.
Its visits are 1–7, lows 1/1/1/3/3/3/2, and rows
`[7,6,5,4,3]`, `[9,8,2,1,0]` of length five each. Endpoint output uses
visit numbers. Both drivers finish with `top == -1`.

From the repository root:

```sh
make -C module_06_graph_dfs/code lecture lecture-ppt
```

The drivers print final values, not intermediate stacks or lookup cells.
Record actual command/diagnostics and identify source, hand-trace, or
debugger evidence. The three retrieval answers are neighbor classification,
equality closing at 4 → 3 through 3–4, and the distinct work saved by
recursive calls and pending edges.

Optional Chapter 5 review: preorder `ABDECFG` splits inorder at root A
into `DBE | A | FCG`. Subtree sizes select preorder `BDE` and `CFG`;
postorder is `DEBFGCA`, assuming distinct labels. Any assigned mini-quiz
uses classroom submission instructions. The checked matrix starter keeps
its separate assignment contracts.
