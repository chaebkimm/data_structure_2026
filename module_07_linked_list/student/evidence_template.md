# Module 07 Evidence Record

Name: ____________________ Date: ____________________ Revision: ____________________

Use [lab.c](lab.c). Preserve first predictions and add corrections. Keep indices separate from values.

## 1. Pool and list trace

Initialize, allocate 17,23,31 with next `-1`, and link 0→1→2→-1.

| Checkpoint | First index | Active chain | Free head | Free chain | Detached indices |
|---|---|---|---|---|---|
| initialization | | | | | |
| three allocations and links | | | | | |
| `removed=delete_next_lnode(0)` | | | | | |
| `free_lnode(removed)` | | | | | |
| `reused=new_lnode(8,-1)` | | | | | |

State the removed index, its old next, and the reused node's data/next: ____________________
Account for all ten indices without overlap or cycles: ____________________

## 2. Insertion and traversal

From 0→2→-1 and detached node 1, record both writes of `link_lnode(0,1)`. Preserve a paper prediction for the reversed order. Explain why the caller retains the first-node index.

Prediction / observed links / correction: ____________________

## 3. Boundaries and ownership

- Ten allocations followed by exhaustion; unchanged fields: ____________________
- Deletion after a tail; unchanged fields: ____________________
- Out-of-range recycling; unchanged fields: ____________________
- Why a live or already-free node cannot be recycled: ____________________
- Missing return versus double return: ____________________
- Two lists' separate first indices and disjoint shared-pool slots: ____________________
- Return A's slot 0, reuse it for 8 before B's slot 1; exact chains: ____________________
- Why stale reads/writes through A's old index now access B: ____________________
- Safe first-node removal by the caller: ____________________

## 4. Original tests and build evidence

| Test group | Assertion | Expected result | Observed result |
|---|---|---|---|
| allocation/exhaustion and shared pool | | | |
| insertion/traversal and first insertion | | | |
| detachment/recycling/reuse, including linked Stack and Queue | | | |

Compiler and commands: ____________________
Output or attachment: ____________________

## 5. Diagnosis, costs, and revision

- Autopsy's first broken precondition and repair: ____________________
- Fixed work for known-predecessor mutations: ____________________
- Work for traversal, i-th-node access, initialization, and one extra integer link per slot: ____________________
- Preserved first prediction and labeled correction: ____________________
- Evidence supporting the correction: ____________________

## 6. Linked Stack as a list example

Use a separate unowned pool and `first=-1`. Record each `new_lnode(value,first)` result for 17,23,31, the guarded update to first, and chain 2→1→0→-1. Before each removal, check nonempty, save old data/next, update first, and recycle. Record LIFO outputs 31,23,17, all free slots after draining, and unchanged Stack state on allocation exhaustion. These are caller actions, not a new supplied Stack API.

Prediction / trace / observed test / correction: ____________________

## 7. Linked Queue as a list example

Record public enqueue of 17,23,31, each boolean result, public dequeue values, endpoint changes, and internal free-chain recycling. Compare the raw helper's returned index with the public wrapper's returned value in separate runs. Include singleton transitions, full enqueue returning false unchanged, reuse behind waiting nodes, a payload of -1, and why enqueue must execute outside assert. Module 8 changes the value to a vertex ID without changing these wrappers.

Prediction / trace / observed test / correction: ____________________
