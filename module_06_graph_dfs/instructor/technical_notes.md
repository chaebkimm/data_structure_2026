# Module 6 Technical Notes — Visit-numbered Concepts and Array Lab

## Concept source and numbering

[Concept slides](../student/ppt_material.md) drive the question-led lesson.
The diagram shows the completed visit numbering of a fixed DFS, 1–7.
Refer to vertices by visit number; retrace from visit 1 with ascending
diagram neighbors. Its endpoint visit pairs are:

```text
1–2, 1–3, 2–3, 2–7, 3–4, 3–6, 3–7, 4–5, 4–6, 5–6
```

Blank circles and partial highlights are board prompts for visit numbers
and processed connections at a stage. They do not change the graph.
An unexplored neighbor is a new tree child. Recognize the parent before
smaller visit numbers identify non-parent ancestors; larger visit numbers
identify processed descendants. At visit 3, neighbors 1/2/4/6/7 are
ancestor/parent/child/descendant/child at their actual encounter times.
These four cases assume simple undirected input, not a general directed
classifier.

Each call proceeds through preorder work, the neighbor loop, and postorder
work in that order. Entry assigns a visit number before any neighbor scan;
set the child's parent before descending.
After return, resume the paused neighbor scan. Postorder follows the
complete scan. Collect only child tree pairs and non-parent ancestor back
pairs. Concept diagrams and stacks use endpoint visit pairs, never edge IDs.

## Earliest reconnection and blocks

Begin from the current visit number. Compare ancestor visit numbers on
back connections and child earliest values after return. The result is
the earliest visit reachable by tree descent and at most one back connection,
including self. A processed descendant cannot lower the current value.

```text
visit number          1 2 3 4 5 6 7
parent visit          – 1 2 3 4 5 3
earliest reconnection 1 1 1 3 3 3 2
```

Visit 6's connection to visit 3 lowers 6 to 3; neighbor 4 cannot lower 3.
That value propagates from child 6 to parent 5, then to parent 4.
In a maximal block with at least three vertices, every pair has two paths
with no shared internal vertex; endpoints may be shared. Different blocks
can share boundary vertices but no edge. This graph gives:

```text
right: 3–4, 3–6, 4–5, 4–6, 5–6
left:  1–2, 1–3, 2–3, 2–7, 3–7
```

Both have five pairs and share visit 3. The pending stack contains pairs
not yet assigned to a block. Push each child pair before descent and each
ancestor pair when scanned. Immediately after a child returns, its parent
compares the child's earliest number with its own visit number. A smaller
value leaves the suffix pending; otherwise pop through and including the
parent–child pair. Equality closes the right block at
4 → 3 (3 ≥ 3) and left block at 2 → 1 (1 ≥ 1). Visit 1's own return
emits no further row. Peak pending count is eight; peak call depth six.
Twenty neighbor entries are scanned per pass, sixty across three passes.

## Edge-stack invariant and correctness checkpoint

At checkpoints after a push or a pop-and-store step, every undirected edge
handled in the extraction pass occurs exactly once in one of two disjoint
places: the pending stack or an assigned block. Assigned includes entries
already written to a row still being formed. Unhandled edges belong to
neither place. The stack, bottom to top, preserves the recording order of
the still-unassigned edges; popping visits that order in reverse.

- **Initialization:** on the fresh single-call run, no extraction edge has
  been handled, the stack is empty, and no result edge has been assigned.
- **Maintenance:** the tree-child and non-parent-ancestor branches each
  push one previously unhandled edge. Reverse parent/descendant entries
  do not push. Each pop-and-store transfers one edge from pending to
  assigned without duplication or loss. A returned subtree may already
  have emitted inner blocks, so only its remaining unassigned edges are
  candidates for the enclosing block.
- **Boundary:** immediately after a child returns, the parent compares the
  child's earliest number with its own visit number. Strictly smaller
  means the remaining edges still reconnect above this parent and stay
  pending. Otherwise the remaining suffix through and including the
  parent–child pair forms the next block. Inner blocks have already been
  removed by deeper child-return comparisons. Every remaining suffix edge
  belongs to the boundary edge's eventual BCC, and the qualifying comparison
  prevents that branch from bypassing the parent to an earlier ancestor.
  Thus no separate inner block remains to mix into the completed suffix.
  Equality reconnects to the parent but cannot bypass it, so it closes too.
- **Termination:** the reached component's every edge has been handled
  once, and each root-child boundary closes its remaining suffix. The
  empty stack therefore leaves every reached edge assigned exactly once.
  An isolated root contributes no edge block. The boundary argument is
  needed for the block grouping; counting alone proves no loss/duplication.

On the fixed visit-numbered graph, closing the right block after 4 returns
leaves three pending pairs and five assigned of eight handled. After 3
returns to 2 there are five pending and five assigned of ten handled: the
five-edge right block in that returned subtree has already been removed.
After 2 returns to 1, pending is zero and assigned is ten.

### Postorder before the parent's comparison / 부모 비교 전 postorder

Fix the checkpoint just before a nonroot `_find_bcc(v)` returns, after its
complete neighbor scan and every decision for its children. Every edge
in this completed DFS branch has been handled and is pending or assigned.
The incoming parent edge is still on the stack. The suffix from it through the top
contains exactly that edge and the branch's unassigned edges, all in the
same eventual BCC as the incoming edge. Inner blocks have already been
removed. This is a statement about the suffix, not the entire pending
stack or a necessarily complete BCC. An older prefix may contain other
BCCs, or more edges of the same BCC; future scans may add more of that BCC.

루트가 아닌 노드의 postorder는 모든 이웃과 자식의 그룹 처리를 마치고 부모에게
돌아가기 직전이다. 이 가지의 간선은 대기 또는 결과에 모두 배정되어 있다.
들어온 부모 간선부터 맨 위까지 남은 구간만 보면, 모두 그 부모 간선과 같은
최종 BCC다. 스택 아래의 오래된 구간이나 완성된 BCC 전체와 혼동하지 않는다.

At visit 4's postorder, before parent 3's `3 ≥ 3` test, the whole stack is:

```text
older prefix: 1–2, 2–3, 1–3
branch suffix: 3–4, 4–5, 5–6, 3–6, 4–6  <- top
```

The suffix is the right block; the prefix belongs to the left block.
Parent 3 closes the suffix only after 4 returns. At visit 3's postorder,
the branch suffix is `2–3, 1–3, 3–7, 2–7`; the older `1–2` below it is
also in the left block. Thus four branch edges are pending within a
five-edge pending stack. Parent 2's `1 < 2` keeps them pending. A root
has no incoming edge: its postorder follows all root-child closures,
so the stack is empty.

In C, pending is `stack[0..top]`. Stored edge indices in `bcc` represent
assigned edges. Inside `close_bcc()`, count the entries already written to
the current row even though `bcc_size[cur]` is set only after its pop loop.
State the invariant after `bcc[cur][pos++] = edge`, not between `pop()`
and that store. The boundary is `tree_edge`, pushed before the recursive
call; the parent tests `back_num[adj] < visit_num[node]` after that call.
The `do ... while` stores the boundary before stopping. No parent index
of -1 is needed. This reasoning assumes the same DFS numbering in the
saved low-link and extraction passes and a fresh result state.

Capacity is a separate precondition. Logical conservation of edges does
not prevent an unchecked write beyond `stack[10]`; the maximum pending
count must fit ten even with `edges[45]` and `bcc[9][45]`.

## Storage and review

Chapter 3 taught only adjacency lists. Review that representation here;
edge lists and adjacency matrices are new Chapter 6 material.

Neighbor lists store an undirected connection at both endpoints. An edge
list stores one pair; a presence matrix sets both symmetric cells. Addition
and deletion must preserve those relationships and handle duplicates.
Deleting a vertex removes all incident connections from the stored graph.
These are three representation choices, not three structures required by
all graph implementations.

Review storage/addition/deletion, block definition/finding, and Chapter 5
preorder/inorder reconstruction. The final mini-quiz heading prompts the
student to submit using classroom instructions. See the [answer key](answer_key.md)
for the review and the [workbook](../student/class_material.md) for the activity.

## Coding source and preconditions

[student/lab.c](../student/lab.c) is the current authoritative source for
C behavior. It includes Module 3 graph globals/algorithms and Module 4's
integer stack. It has no entry point. The
[original lecture driver](../code/lecture/lab_demo.c) initializes A–J,
not the new visit-numbered slide graph. [Lab slides](../student/ppt_lab_material.md)
explain this implementation separately from the revised concept prompts.

Assume a valid root in `0..nodes_size-1`, nonempty simple undirected graph,
symmetric valid stored lists, and fitting fixed capacities. Self-loop
branches are empty. Parallel and directed inputs are outside the contract.
No checks enforce these assumptions; globals change directly without
status codes, allocations, or failure-preservation guarantees.

The revised lab slides introduce `init_visit()` before edge-list storage.
Teach it as shared traversal preparation: time 0, active discovery cells 0,
and active parents -1. It does not clear edge storage, lookup, low-link
values, the pending stack, or block results. The four indexing-wrapper
steps are that preparation, record-count reset, active lookup initialization,
and recursive indexing. `find_bcc()` reuses the same preparation before
low-link calculation and again before extraction.

`_edge_iteration_()` is a template that numbers visits and assigns parents;
its comments do not record or push edges. `_init_edges_list()` and
`_find_bcc()` specialize its child/ancestor branches. Extraction adds the
boundary comparison immediately after each recursive child call returns.
The indexing child order is `add_edge(node, adj)`, parent assignment,
then recursion. The extraction child order is push, parent assignment,
then recursion. `add_edge()` records existing adjacency and writes the
same index to both endpoint lookup cells; it does not modify neighbor lists.
Static zero lookup initialization is insufficient because index 0 is valid;
`init_edges_list()` resets discovery and parents, clears `edges_size`,
sets the active lookup to -1, then calls `_init_edges_list(start_node)`.
Its source parameter is `start_node`; the edge-list slide uses `root`.

## Coding resets and single-call scope

| State | Meaning | Reset in lab |
| --- | --- | --- |
| `visit_time`, `visit_num` | discovery, zero unvisited | `init_visit()` |
| `parent` | DFS parent, root -1 | `init_visit()` |
| `back_num` | saved low-link values | reached cells overwritten by `save_back_num()` |
| `edges_size` | active records | `init_edges_list()` |
| `edge_index` | symmetric record lookup | active V×V region set to -1 by `init_edges_list()` |
| `top` | active stack end | `find_bcc()` sets -1 |
| `current_bcc` | active result count | no wrapper reset |
| `bcc_size`, `bcc` | row lengths and indices | emitted rows overwritten; no full reset |

Use a fresh process: `alphabet_nodes_init()`, `edges_init()`,
`init_edges_list(0)`, then `find_bcc(0)`. Repeated `edges_init()` appends
neighbors unless lists are reinitialized. Repeated extraction appends rows
unless results are managed explicitly. Reindexing another component changes
the meaning of existing row indices; a whole-graph extension needs persistent
edge identities, component traversal, and explicit result ownership/resets.

`init_edges_list()` prepares edge identities but does not compute low-link
values or clear block results. `find_bcc()` assumes the reached edges have
already been indexed. It computes low-link values, empties the stack, resets discovery
and parents, then extracts using the same root/order. It retains `back_num`;
`_find_bcc()` does not recompute it. Changing root, adjacency, or stored
order between passes invalidates saved-number comparisons. Three overall
passes are indexing, low-link, and extraction.

Immediately after each child call, `_find_bcc()` compares
`back_num[adj] < visit_num[node]`. A true comparison uses `continue` to
leave that branch's edges pending. Otherwise `close_bcc(tree_edge)` emits
the suffix. Its `do ... while` stores the boundary edge before testing,
so the boundary is included. Declare `edge` outside the loop for use in
its condition. The comparison runs in the parent and never indexes the
root's parent -1. Root children can emit rows; the root's own return emits
none. An isolate emits no edge row.

## Original A–J reference and cost

```text
discovery: A=1 B=2 C=3 D=4 E=5 F=6
parent:    A=-1 B=0 C=1 D=1 E=3 F=4
low:       A=1 B=2 C=3 D=2 E=2 F=2
edges:     0:A→B 1:B→C 2:B→D 3:D→E 4:E→B 5:E→F 6:F→B 7:F→D
blocks:    [1] | [7,6,5,4,3,2] | [0]
sizes:     1,6,1
final:     edges_size=8 current_bcc=3 top=-1
```

G/H/I/J remain unvisited; G–H is unindexed. The whole graph has four
connected groups; A processes only A–F. Its three edge groups share B.
The peak pending stack is seven and call path A/B/D/E/F has five vertices.
Each pass reads sixteen neighbor entries. The active ten-vertex lookup
reset writes 100 cells. Thus the complete pipeline is `O(V² + E_R)`;
the adjacency-list traversal itself is `O(R + E_R)`.

Generalized recursive and pending storage is `O(R + E_R)`; lookup storage
is `O(V²)`. Active records and emitted results each contain `E_R` edge
entries overall. A rectangular result table with V rows and E columns
reserves `O(VE)` cells even when only `E_R` cells hold results.
Actual arrays are fixed:
`nodes[10]`, `edges[45]`, `stack[10]`, `edge_index[10][10]`,
`bcc[9][45]`, and `bcc_size[9]`. The result table reserves 405 cells plus
nine lengths. A simple undirected graph with ten vertices
has at most `10 * 9 / 2 = 45` edges. A reached connected group with `R`
vertices has at most `R - 1` edge blocks, so nine rows cover the ten-vertex
bound; an isolate has no edge block. These record/result capacities do
not enlarge the imported ten-entry stack. Extraction is valid only when
the maximum simultaneously pending edge count also fits ten entries.
Raw `push()`, `pop()`, and `add_edge()` are unchecked.

## Verification and optional slide experiment

Run `make lecture` from `module_06_graph_dfs/code` for original A–J output.
Preserve compiler/command/diagnostics and compare to the reference above.
The driver prints final tables, not intermediate stacks or lookup cells.
Warnings from unchanged dependencies should be reported, not edited away.
Run `make lab-tests` for nine array-lab checks covering both supplied graphs,
the strict/equal boundary cases, root branches, and record/result/stack limits.

The optional [slide driver](../code/lecture/ppt_demo.c) creates the slide
graph adjacency for the same current lab. From the repository root, compile and run:

```sh
cc -std=c11 -I. module_06_graph_dfs/code/lecture/ppt_demo.c -o /tmp/ppt_demo
/tmp/ppt_demo
```

Expect the slide values and two five-edge groups above. Interpret any
printed numeric edge IDs through that driver's records. It stores neutral
A–G data at indices 0–6, while printed edge endpoints come from actual
visit numbers 1–7. Internal indices and record IDs belong to this coding
experiment; concept endpoint pairs use visit numbers. This independent
experiment does not change the original driver's graph or output.

## Legacy package boundary

The checked matrix/typed-vertex-stack API in `code/include`, `support`,
`starter`, `solution`, matrix tests, and older staged worksheets retains
its own public contracts. It does not define this unchecked array lab.
