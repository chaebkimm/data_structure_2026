# Linked-List Autopsy — Recycle Before Detaching

Use [lab.c](lab.c). Predict the wrong sequence on paper; it is outside the caller contract. The old code/autopsy executable belongs to the optional pointer library.

## 1. Predict the defect

```text
first=0
lnodes[0]={17,1}; lnodes[1]={23,2}; lnodes[2]={31,-1}
free_head=3; free 3→4→5→6→7→8→9→-1
```

```c
int victim = lnodes[0].next;
free_lnode(victim); /* wrong: referenced and not isolated */
int removed = simple_delink_next_lnode_from_prev(0);
```

Does the active list still reach 31? Which index becomes both allocated/active and free? Record 0.next, 1.next, and free_head after each statement.

Prediction: _________________________________________________________

## 2. Find the earliest broken precondition

A recyclable node must be an allocated unreferenced isolated slot. The wrong first call violates both incoming-link and next=-1 requirements. Recycling overwrites 1.next with the free head, so later deletion copies 3 into 0.next instead of old successor 2, then clears 1.next=-1. The invalid result can remain inside the array, so a clean sanitizer run does not establish ownership.

Earliest broken rule and lost successor: ______________________________

## 3. Repair and verify

```c
int removed = simple_delink_next_lnode_from_prev(0);
if (removed != -1) {
    int value = lnodes[removed].data;
    /* Use the saved value before returning ownership. */
    (void)value;
    free_lnode(removed);
}
```

Give both chains and removed next=-1 after detachment; then give the free-chain link written on return. Detachment isolates but does not recycle. Another init call cannot reset a damaged pool: its static guard makes it a no-op. Use a valid new process/fixture for the repair.

Response: ___________________________________________________________

## 4. Nearby paper diagnoses

1. After correct return, a second return of 1 creates what link? Which ownership/isolation rules fail? There is no general bounds/membership validator.
2. Reverse insertion writes for 0→2→-1 and isolated 1. Give the self-link and lost successor.
3. Can new_lnode find a detached allocation that was never returned?
4. A returns singleton 0; B reallocates 0, writes 8, and prepends it to B's 1. What does A's stale index now select? Why can old writes damage B?
5. A Stack advances first but calls free_lnode(old) without clearing old.next. Which precondition is missing? Give guard/save/advance/isolate/recycle order.
6. A caller treats dequeue_lnode's index as a payload or assumes automatic recycling. Which observation distinguishes returned ownership from a free slot?

Response: ___________________________________________________________

## 5. Regression evidence

Assert repaired exact chains, no repeated/overlapping indices, next=-1 on detached nodes, retained data before explicit assignment, two disjoint lists sharing slots, safe LIFO drain, and FIFO dequeue/copy/recycle. Execute only repaired valid calls; bound wrong traces on paper.

First broken precondition: ____________________ Repaired state: ____________________ Test/result: ____________________ Why no crash is insufficient: ____________________
