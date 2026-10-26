# Stage B — Five-Minute Cognitive Pause

Close notes after the representation reveal. Preserve first responses and add labeled corrections afterward. Indices select `lnodes[10]`; `-1` ends a chain.

## Target 1 — Preserve a successor

The list is 0→2→-1. Node 1 is allocated and detached. Trace both assignments in `link_lnode(0,1)`. Why does their order matter?

Response: ___________________________________________________________

## Target 2 — Detach before recycling

Start with 0(17)→1(23)→2(31)→-1 and free chain 3→4→5→6→7→8→9→-1. Trace `removed=delete_next_lnode(0)`, then `free_lnode(removed)`. Give `lnodes[0].next`, `lnodes[1].next`, and `free_head` after each call.

Response: ___________________________________________________________

## Target 3 — Apply membership to a waiting list

All ten slots have been allocated. What does `new_lnode(8,-1)` return? Which state changes? Now consider a linked queue whose sole node is index 2 carrying 31. Compare `dequeue_lnode()` and `dequeue()` on that same singleton state in separate runs. Give each return, head/tail, and free-chain membership. Explain why public dequeue already recycles the slot and why its returned value must not be passed to free_lnode.

Response: ___________________________________________________________

Label corrections `write order`, `detach/recycle`, or `caller precondition`. Cite the state or test that changed your answer.
