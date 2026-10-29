# Stage B — Five-Minute Cognitive Pause

Close notes after the representation reveal. Preserve first responses, then add labeled corrections. Three targets; indices select lnodes[10], -1 ends a chain.

## Target 1 — Preserve a successor

For 0→2→-1 and allocated isolated 1, trace both writes of `simple_link_lnode_to_prev(0,1)`. Why does their order matter?

Response: ___________________________________________________________

## Target 2 — Detach before recycling

For 0(17)→1(23)→2(31)→-1 and free 3→4→5→6→7→8→9→-1, trace `removed=simple_delink_next_lnode_from_prev(0)` then `free_lnode(removed)`. Give 0.next, 1.next, and free_head after each. What does subsequent `new_lnode()` leave in data, and who writes the new payload?

Response: ___________________________________________________________

## Target 3 — Apply the list at its ends

A Stack is 2(31)→1(23)→-1. What must be saved, advanced, and cleared before recycling 2? A separate Queue contains only node 2 holding 31. Give `dequeue_lnode()`'s returned index, next, qhead/qtail, and unchanged free head; who copies data and recycles? Why does another `init_lnodes_pool()` call not reset either experiment?

Response: ___________________________________________________________

Label corrections `write order`, `detach/recycle`, or `caller precondition`. Cite a trace/test.
