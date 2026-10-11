# Chapter 6. Graph DFS, Edge Lists, and Biconnected Components

Teach from [lab.c](../module_06_graph_dfs/student/lab.c), the
[textbook](../module_06_graph_dfs/student/textbook.md), and the
[lecture material](../module_06_graph_dfs/student/ppt_material.md).
The lab reuses the Module 3 undirected adjacency-list graph and Module 4
integer stack. The explicit stack holds edge indices; recursion explores
vertices.

## Starting question

> We already know how to visit a connected graph. How can we collect its
> edges into groups that meet only at separating vertices?

Retrieve discovery numbers, DFS parents, and `save_back_num()` from Module
3 before introducing a new edge index or block rule. Preserve predictions
before revealing the output.

## Board walkthrough

Use A–J, indices 0–9, and the unchanged input pairs:

```text
A-B, B-C, B-D, B-E, B-F, D-E, D-F, E-F, G-H
I and J are isolated.
```

Start at A. Follow stored neighbor order, not a new sorting rule.

1. Mark on recursive entry. Enter A, B, C, D, E, F.
2. Classify the neighbor cases: new child, parent, ancestor, descendant,
   self. Record only child and ancestor edges.
3. Give A–B index 0, B–C index 1, B–D index 2, D–E index 3, E–B index 4,
   E–F index 5, F–B index 6, and F–D index 7.
4. Trace low-link values: A=1, B=2, C=3, D=2, E=2, F=2.
5. Push tree edges before recursion and back edges toward ancestors.
6. At each non-root return, pop through the parent edge when
   `back_num[node] >= visit_num[parent[node]]`.

| Return | Comparison | Block indices, in pop order |
| --- | --- | --- |
| C to B | `3 >= 2` | `[1]` |
| F to E | `2 < 5` | none |
| E to D | `2 < 4` | none |
| D to B | `2 >= 2` | `[7, 6, 5, 4, 3, 2]` |
| B to A | `2 >= 1` | `[0]` |

The blocks are B–C, the six edges among B/D/E/F, and A–B.
B is the shared cut vertex. A is not a cut vertex: its DFS root has one
child. Root A does not reach G–H, I, or J. An isolated root emits no edge
block in this implementation.

## Code walkthrough

Read the functions in this order:

1. `add_edge()`: one record and two symmetric lookup cells.
2. `init_visit()`: discovery and parent reset, without clearing low-link
   values or block results.
3. `_init_edges_list()` and `init_edges_list()`: edge classification and
   index preparation.
4. Included `save_back_num()`: entry, child-return, and non-parent-neighbor
   updates.
5. `_find_bcc()`: edge pushes and postorder block extraction.
6. `find_bcc()`: low-link pass, stack reset, discovery reset, extraction
   pass in the same order.

Run `make lecture` from `module_06_graph_dfs/code`. The driver includes the
unchanged lab. Expect eight indexed edges, three rows of sizes 1/6/1, and
an empty stack.

## Common mistakes and useful questions

- Treating the stack as pending vertices: ask students to resolve each
  pushed integer through `edges[index]`.
- Treating the parent entry as a back edge: ask which edge has already been
  recorded and why both endpoint lists contain it.
- Using `>` instead of `>=` to close a block: revisit D's value 2 and B's
  discovery number 2. Strict `>` is the bridge condition.
- Popping until the parent edge but excluding it: read the `do ... while`
  body before its condition.
- Calling `_find_bcc()` before indexing or saving low-link values: identify
  the unprepared lookup/value used by the next operation.
- Assuming repeatability: locate `current_bcc` and ask where it is reset.
- Counting three blocks as three connected components: identify the shared
  vertex B and the four whole-graph connected groups.

## Cost and contract check

Adjacency-list passes cost `O(R + E_R)` for reached vertices and edges.
Initializing the entire active edge-index table costs `O(V²)`. The complete
pipeline costs `O(V² + E_R)`. Recursive calls use `O(R)` working space;
the pending-edge stack uses `O(E_R)` in a generalized implementation.

The actual lab uses unchecked fixed arrays and is marked for one call.
Assume a valid nonempty simple undirected graph, symmetric lists, a valid
root, and fitting capacities. Do not teach allocation errors or unchanged
outputs as guarantees of this source. The matrix/typed-stack starter and
its Practical 1 assessment documents remain a separate legacy track.

## Final check

> Explain why D's equality case closes a block, what the pop loop includes,
> and why the same root and neighbor order must be used in both BCC passes.

Require the exact condition, inclusion of the parent edge, and reuse of
saved low-link values with reproduced discovery numbers.
