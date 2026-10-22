# Week 7 — Linked Lists and Queue: Vocabulary and Questions

[All-week bank](../Data_Structures_Course_2026_Student_Question_Bank.md)

## Required scope for the 13-week course

Implement a singly linked Queue in one lab; trace supplied destruction and compare the supplied circular-array Queue. General list mutations and a second Queue implementation are optional.

## Vocabulary students will learn

| Term | Working meaning |
|---|---|
| Queue | An ADT that removes the earliest-added item first. |
| FIFO | First in, first out; arrival order determines removal order. |
| Stack / LIFO | Removes the most recently added item first. |
| ADT | Public behavior independent of storage representation. |
| singly linked list | Nodes joined by one-way next links. |
| node | An allocated object containing a value and a next pointer. |
| pointer | A value representing an object address. |
| NULL | A pointer value referring to no object. |
| next | The pointer to the following node. |
| head | In the linked Queue, a pointer to the oldest node. |
| tail | In the linked Queue, a stored pointer to the last node. |
| size | The number of active Queue items. |
| enqueue | Append at the linked tail. |
| dequeue | Remove the linked head and return its value. |
| peek | Read the oldest item without removing it. |
| empty | No nodes; both pointers are NULL and size is zero. |
| singleton | Exactly one node, referenced by both head and tail. |
| invariant | A rule true in every valid observable state. |
| traversal | Following next links through the chain. |
| allocation | Reserving storage for a new node. |
| ownership | Responsibility for releasing allocated storage. |
| free / release | End an allocation lifetime exactly once. |
| destruction | Release every node and restore the empty state. |
| dangling pointer | A pointer whose referenced object is no longer alive. |
| use-after-free | Accessing an object after releasing it. |
| memory leak | Owned allocation lost without release. |
| shallow copy | Copying pointers without duplicating the owned nodes. |
| failure preservation | A failed operation keeps Queue state and caller output unchanged. |
| circular buffer | An array Queue that reuses earlier positions. |
| physical index | An actual position in the circular backing array. |
| logical order | The FIFO order independent of physical storage. |
| derived tail index | The circular Queue insertion position (head + size) % capacity. |
| capacity | The configured number of slots in the supplied circular Queue. |
| wraparound | Continuing at slot zero after the final slot. |
| locality | How close accessed storage locations are in memory. |
| frontier | Items scheduled for later processing, used in next week's BFS. |

## Anticipated student questions

### Meaning and representation

- What behavior makes both the linked and circular representations Queues?
- How do FIFO and LIFO differ for the same arrivals?
- Why do linked-node addresses not need to be adjacent?
- How do head, tail, next, and size describe the linked Queue?
- Why does a singleton have the same head and tail pointer?

### Operations and ownership

- Why must allocation succeed before enqueue changes any existing links?
- Which pointers change when adding to an empty Queue?
- Which pointer changes when adding to a nonempty Queue?
- Why must dequeue save the value and following link before release?
- Why must removing the final node clear both head and tail?
- Why does the Queue return an integer instead of transferring a node?
- Why can copying a live Queue struct cause double release?
- How does supplied destruction visit and release every node?
- Why must an output pointer refer to storage outside the Queue?

### Tracing, tests, and debugging

- What changes during empty → singleton → empty → singleton?
- How can allocation failure be tested without relying on real memory exhaustion?
- What state and links must stay unchanged after failed enqueue?
- What must remain unchanged after empty dequeue?
- Which later write becomes unsafe if final dequeue leaves a dangling tail?
- How do the three original tests add evidence beyond the supplied fixture?
- How can live-node counts and sanitizers help check cleanup?

### Circular comparison and costs

- Why can circular physical order differ from logical FIFO order?
- When is the circular tail-index formula valid?
- How does size distinguish full from empty in a circular Queue?
- How does a linked tail pointer differ from the circular derived tail index?
- Why do both implementations avoid shifting surviving values?
- Why is linked pointer work constant per operation but traversal O(n)?
- Why is the O(n) validator excluded from an O(1) operation claim?
- How do allocation costs, pointer overhead, and locality differ?
- Why does a linked Queue still have memory and representable-size limits?

### Assignment and transfer

- Which two functions are the required Week 7 TODOs?
- Why are peek, destruction, and validation supplied?
- Do I implement the circular Queue or a complete general list library?
- Which code, tests, traces, and correction evidence form the one artifact?
- Why does BFS need discovery state in addition to FIFO ordering?
- Why does a correct Queue not guarantee authentic, persistent event records?

## Sources

- [Week 7 lesson, lab, and release](../module_07_queue/week_07/README.md)
- [13-week delivery guide](../Data_Structures_Course_2026_13_Week_Delivery_Guide.md)
