# Stage B — Five-Minute Cognitive Pause

Close notes after the representation reveal. Preserve first responses and add labeled corrections afterward. Indices select `lnodes[10]`; `-1` ends a chain.

## Target 1 — Preserve a successor

The list is 0→2→-1. Node 1 is allocated and detached. Trace both assignments in `link_lnode(0,1)`. Why does their order matter?

Response: ___________________________________________________________

## Target 2 — Detach before recycling

Start with 0(17)→1(23)→2(31)→-1 and free chain 3→4→5→6→7→8→9→-1. Trace `removed=delete_next_lnode(0)`, then `free_lnode(removed)`. Give `lnodes[0].next`, `lnodes[1].next`, and `free_head` after each call.

Response: ___________________________________________________________

## Target 3 — Apply the list at its ends

A linked Stack starts at 2(31)→1(23)→-1. Before recycling node 2, what data and next must the caller save, and what becomes first? In a separate linked Queue containing only 2(31), what value and head/tail result from public `dequeue()`?

Response: ___________________________________________________________

Label corrections `write order`, `detach/recycle`, or `caller precondition`. Cite the state or test that changed your answer.
