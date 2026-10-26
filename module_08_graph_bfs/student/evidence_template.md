# Module 8 Evidence — Queues, Tree BFS, and Graph BFS

Name: ____________________  Date: ____________________

Use [lab.c](lab.c), the [lab instructions](lab.md), and the [class workbook](class_material.md). Preserve predictions and add corrections beside them. Code, tests, traces, and explanations form one submission.

## Queue and tree evidence before the maze

| Required trace | First prediction | Observed result and correction |
| --- | --- | --- |
| Linked queue: enqueue values17/23/31, check Boolean results, receive values and observe automatic recycling | | |
| Linear: 25 writes, then drain; full and empty together | | |
| Circular: 24 values, remove2, append2 across wraparound | | |
| Tree: pending queue after F, A, G, B, all7 output labels and depths | | |
| Empty and single-node tree with independent resets | | |

Explain Boolean enqueue failure, raw index versus public payload returns, automatic public recycling, valid payload -1, caller nonempty checks, and 24 usable circular positions. Record that enqueue executes outside assert. Explain why the tree needs no discovery array under its valid-tree assumptions while a general graph does. Add one original queue assertion, one tree assertion, and one maze assertion with the claim each checks. Include all three parts in one submission.


## 1. Which source and setup did I run?

Record queue.c, tree_bfs.c, maze lab.c, driver path, build command, and observed result. Explain the Module 2 tree and Module 7 pool dependencies and the shared consumer/import guard.

```text
source and preparation:
driver:
build command:
run command and output:
metadata reset:
queue reset:
valid-start and border assumptions:
```

## 2. How does a coordinate enter the queue?

Record both directions of the mapping. Explain why `maze[y][x]` uses a different written order from `{x, y}`.

```text
start {1,1} -> index:
target {5,5} -> index:
points[25] -> coordinate:
distance 25 means:
active points slots:
```

## 3. What waits after each passage is processed?

Use start `{1,1}` and right/left/down/up order. Record queue contents from oldest to newest. Trace at least through index 17, then record the complete dequeue order in coordinates or IDs. A trace is evidence in the workbook; the source has no `visit_order` field. The driver records payload IDs around the original linked methods and checks every slot returns to the free pool.

| Dequeued cell and distance | Queue after its four candidates | New distances or predecessors |
| --- | --- | --- |
| Initial state | | |
| `{1,1}` | | |
| `{1,2}` | | |
| `{2,2}` | | |
| `{1,3}` | | |
| `{3,2}` | | |
| Remaining cells, attached trace | | |

```text
complete dequeue order:
reached passage count (distance below 25):
head/tail after completion, returned free-slot count, total insertions/removals, peak pending:
```

## 4. Which branch applies to a neighbor?

For each source branch, provide an actual pair from the trace. Record the current distance, neighbor distance before the check, predecessor effect, and whether enqueue occurs. Handle a wall before these three comparisons.

| Condition | Example and initial distances | Changed metadata | Enqueued? |
| --- | --- | --- | --- |
| `neighbor_distance <= cur_distance` | | | |
| `neighbor_distance == cur_distance + 1` | | | |
| Otherwise: first discovery | | | |

Explain how setting a distance below 25 before enqueue prevents a second enqueue while a passage is still waiting. Explain why an additional shortest predecessor is retained rather than skipped.

## 5. What do the final predecessor lists prove?

For start `{1,1}`, record target `{5,5}`'s distance and active `prev` entries. Also inspect `{3,5}` and explain why the number of target parents need not equal the number of complete shortest routes.

```text
target distance:
target prev_size and ordered prev entries:
{3,5} prev_size and ordered prev entries:
backward sequence using prev[0]:
forward route:
number of moves and adjacent-passage checks:
number of all shortest routes and reasoning:
source distance and prev_size:
```

## 6. Can another person repeat my checks?

Provide assertions or equivalent observations for all three categories. State the expected result before recording the actual result.

| Check | Setup | Expected | Actual | Explanation or correction |
| --- | --- | --- | --- | --- |
| Distance and source-only route | | | | |
| Equal-distance merge without duplicate queue entries | | | | |
| Independent repeated search with both resets | | | | |
| Isolated valid start; goal remains an unreachable passage | | | | |

The supplied driver temporarily sets `maze[2][1]=0` to isolate the valid start `{1,1}` while preserving the zero border. Record that the still-open target `{5,5}` retains distance 25, zero predecessors, and zero routes. Only the start enters the queue. The driver restores the passage and reruns the canonical fixture. Include this supplied unreachable-passage check in the required evidence. Other maze generalizations are optional. Distance 25 alone does not distinguish an unreachable passage from a wall.

## 7. How much work and storage are needed?

Count concrete operations before attaching cost names.

```text
cells initialized in this fixture:
reachable passages dequeued:
neighbor candidates checked:
initialization cost for R rows and C columns:
traversal cost for V_reached passages:
reserved metadata and queue space:
why all-route enumeration can cost more than BFS:
```

Explain why a maze grid is not a `V × V` adjacency matrix. Explain the separate bounds: ten pool slots cover peak pending entries (four canonical, at most six over the supplied starts); distance sentinel 25 exceeds any simple shortest route length in a 5 × 5 interior. Total discoveries do not equal required linked-pool capacity. Finish with one corrected prediction and a comparison between FIFO search and DFS's LIFO choice.
