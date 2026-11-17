# Chapter 10 — Vocabulary

Read the informal explanation before using the formal name. Code names below belong to the current lab.

| Term | Meaning in this lesson |
| --- | --- |
| FIFO | Remove in arrival order; the earlier queue rule being recalled. |
| Priority queue | Remove an item with highest priority under a comparison rule. |
| Comparator | A function returning nonzero when its first argument has strictly higher priority. |
| Sorted insertion | Shift lower-priority live items right to open the correct position. |
| Stable ties | Equal-priority items retain their order of insertion into the queue. |
| `front` | Index of the first live item; incremented by removal. |
| `rear` | Index of the last live item; incremented by insertion. |
| Live range | Positions front through rear; count rear - front + 1. |
| Empty state | front == rear + 1; initially 0 and -1. |
| Cumulative insertion count | All insertions since queue initialization; equals rear + 1. |
| Caller precondition | A condition callers must ensure because the source does not check it. |
| User ID | Row number identifying one user; the queue stores this ID. |
| Half-open interval | [login,logout): online at login, offline at logout. |
| Epoch | Zero-based selected interval number, stored in users[id].epoch. |
| Candidate | Greatest current login; meeting_time in survey. |
| Blocking interval | An interval whose logout is at or before the candidate. |
| Exhaustion | No next interval exists; next_epoch returns -1 after incrementing epoch. |
| Function pointer | Stores a function address; compare selects the priority rule. |
| Function address | &earlier_logout, passed to init_queue. |
| Invariant | A state relationship preserved by each valid operation. |
| Independent oracle | A different calculation used to check results, here interval-combination enumeration. |

The abstract priority queue need not preserve ties, but this source does. Reinserting an ID counts as a new arrival to the queue. A heap, inverse position map, graph distance, and relaxation are not needed for this chapter's implementation.
