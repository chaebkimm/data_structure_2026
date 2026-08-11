# Week 7 — Queue and Circular Buffer: Vocabulary and Questions

[All-week vocabulary and question bank](../Data_Structures_Course_2026_Student_Question_Bank.md)

## Required scope for the 14-week course

Required work is the Module 7 core: model FIFO service, trace a fixed-capacity
circular buffer, implement and validate constant-time Queue operations, preserve
state and outputs on checked failure, and explain the selected retention policy.
Students submit **one ordinary Week 7 lab artifact**. Dynamically growing,
linked, and concurrent Queue implementations remain extension work.

## Vocabulary students will learn

| Term | Working meaning |
|---|---|
| data structure | A planned way to organize information. |
| abstract data type (ADT) | A collection described by its public operations and rules rather than one storage method. |
| Queue | An ADT that removes the earliest-added item first. |
| first in, first out (FIFO) | The Queue rule: earliest added is earliest removed. |
| front | The oldest current Queue item and the next one eligible for removal. |
| back | The newest current Queue item. |
| `enqueue` | Add an item at the back. |
| `peek` | Report the front item without removing it. |
| `dequeue` | Remove and report the front item. |
| empty | Having no current items. |
| full | Having a logical size equal to capacity. |
| underflow | An attempted report or removal when the Queue is empty. |
| overflow | An attempted insertion that cannot fit under the selected policy. |
| Stack | An ADT that removes the newest-added item first. |
| last in, first out (LIFO) | The Stack rule: newest added is earliest removed. |
| array | A numbered row of same-type values. |
| buffer | Bounded temporary storage. |
| circular buffer | An array Queue that reuses positions at the beginning after reaching the physical end. |
| physical index | One actual numbered position in the backing array. |
| logical order | The service order of current items, independent of their physical positions. |
| capacity | The fixed number of physical positions available in this Queue. |
| `head` | The physical index of the front item when the Queue is nonempty. |
| `size` | The number of current logical items. |
| tail | The next physical insertion position, calculated rather than stored here. |
| derived field/value | A value calculated from stored facts instead of stored separately. |
| remainder operator (`%`) | The C operator used to wrap a calculated position into the valid index range. |
| wrap-around | Continuing at index 0 after reaching the physical end of the array. |
| canonical empty state | The one required field arrangement restored whenever the Queue becomes empty. |
| invariant | A rule true in every valid completed Queue state. |
| validation | Checking whether visible fields obey all stated representation rules. |
| pointer | A C value that identifies a memory location. |
| `NULL` | The C pointer value meaning “points to no object.” |
| `size_t` | C's nonnegative whole-number type for counts and indexes. |
| allocation | A storage block obtained while the program runs. |
| ownership | Responsibility for releasing an allocation exactly once. |
| shallow copy | A field-only copy that copies a pointer without copying the allocation it identifies. |
| API | The public operations that other code may call. |
| contract | Rules stating what an operation accepts, changes, reports, and preserves. |
| output location | Caller-provided storage in which an operation writes a result. |
| failure preservation | A failed operation leaves the prior Queue state and protected output unchanged. |
| retention policy | The rule deciding what information is kept when the Queue is full. |
| reject newest | Refuse the attempted addition while preserving every current item. |
| discard oldest | Remove the longest-waiting item to make room for a new one. |
| backpressure | Ask the source to slow or stop producing work. |
| stale slot | A physical array value left behind after its logical item was removed. |
| regression test | A test retained so a repaired defect does not return. |
| `O(1)` | Work bounded by a fixed amount independent of Queue size. |
| `O(n)` | Work that may grow in proportion to `n` current items. |
| breadth-first search (BFS) | The coming exploration method that uses FIFO order to process shallower work first. |

### Optional vocabulary for extension questions

| Term | Working meaning |
|---|---|
| dynamically growing circular Queue | A circular Queue that allocates a larger buffer when its current buffer fills. |
| linked Queue | A Queue made from separately allocated nodes, usually with front and back pointers. |
| node | A separately stored item together with one or more links. |
| producer | Code or a thread that adds work to a Queue. |
| consumer | Code or a thread that removes work from a Queue. |
| synchronization | Coordination that prevents concurrent operations from corrupting shared state. |

## Anticipated student questions

### Meaning and mental model

- What behavior makes a collection a Queue regardless of its storage representation?
- Why does first-in, first-out remove the event that has waited longest?
- How does Queue order differ from Stack order for the same arrival sequence?
- Why can logical Queue order differ from left-to-right physical array order?

### Representation and invariants

- Which relationships among `data`, `capacity`, `head`, and `size` define a valid Queue?
- What is the required canonical state of an empty Queue after initialization or complete draining?
- How is the next tail position derived from `head`, `size`, and `capacity`?
- What visible properties can `event_queue_validate` check, and which allocation and ownership facts remain unprovable?

### Operations, C API, and ownership

- Why does positive-capacity initialization allocate once while enqueue and dequeue allocate nothing?
- Which object fields, array slots, and output values must remain unchanged when an operation fails?
- Why must a dequeue or peek output pointer not point inside the Queue’s owned allocation?
- What is the difference between `peek` and `dequeue` in both behavior and permitted state changes?

### Tracing

- How do I compute the physical position of logical item `k` using modular arithmetic?
- What fields and slots result after filling, dequeuing several items, wrapping, and enqueuing again?
- When the final item is removed, what canonical empty fields should be restored?
- What should a trace show when enqueue is attempted on a full Queue under the reject-newest policy?

### Tests and debugging

- Which three required student-test categories cover validation, reuse, and failure preservation?
- How can one test prove the Queue can fill, drain, wrap, and then repeat the cycle correctly?
- What test distinguishes a full Queue from an empty Queue when head and tail positions coincide?
- In the Queue Autopsy, which missing modulo or boundary check first produces an invalid physical index?

### Complexity

- Why are validation, enqueue, dequeue, and peek `O(1)` in this fixed-capacity design?
- Why would shifting all surviving events after every dequeue make removal `O(n)`?
- What storage cost is paid at initialization even when the Queue is initially empty?
- How would a linked Queue change capacity policy, allocation costs, locality, and ownership complexity?

### Cybersecurity and interpretation

- What information-loss risk comes with reject-newest, discard-oldest, and backpressure policies?
- Why is silently overwriting the oldest event inappropriate for this course’s contract?
- How could a wrap-around bug corrupt or misorder security-event records?
- Why do correct Queue mechanics not guarantee that incoming event codes are authentic or correctly prioritized?

### Assignment and evidence

- Which validation, enqueue, and dequeue TODOs are required in the Week 7 core?
- Must the student tests assert exact fields and physical slots as well as returned values?
- What warning, test, and autopsy evidence must accompany the Queue implementation?
- Why is there one ordinary Week 7 lab even though the Queue will immediately be reused in Week 8?

### Transfer and prerequisites

- Which array-index, invariant, ownership, and failure-preservation skills from Weeks 1 and 4 are reused here?
- How will FIFO ordering produce nondecreasing depth during tree level-order traversal?
- Why will graph BFS need both this Queue and a visited or distance record?
- Which circular-buffer defect might reappear as a Practical 2 repair question?

### Extension questions — optional

- How would a dynamically growing circular Queue preserve logical order during reallocation?
- How could a linked Queue achieve unbounded logical capacity, and what allocation failures would appear?
- What synchronization would a Queue need if producers and consumers ran concurrently?
- Are discard-oldest, backpressure, dynamic growth, and concurrent Queue implementations required for Week 7?

## Sources

- [14-week delivery guide](../Data_Structures_Course_2026_14_Week_Delivery_Guide.md)
- [Master spiral curriculum](../Data_Structures_Course_2026_Spiral_Curriculum.md)
- [Original Weeks 1–7 question bank](01_weeks_01_07_questions.md)
- [Module 7 package overview](../module_07_queue/README.md)
- [Module 7 vocabulary reference](../module_07_queue/student/vocabulary.md)
